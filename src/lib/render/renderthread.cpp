#include "renderthread.h"
#include <QDebug>

RenderThread::RenderThread(QOpenGLWidget* sharedWidget) {
    m_thread = new QThread();
    this->moveToThread(m_thread);

    connect(m_thread, &QThread::finished, this, &QThread::deleteLater);
    connect(this, &RenderThread::triggerRun, this, &RenderThread::onRun, Qt::QueuedConnection);
    connect(this, &RenderThread::triggerRunSync, this, &RenderThread::onSyncRunTask, Qt::BlockingQueuedConnection);

    auto sharedContext = sharedWidget->context();
    m_glContext = new QOpenGLContext();
    m_glContext->setShareContext(sharedContext);
    m_glContext->setFormat(QSurfaceFormat::defaultFormat());
    m_glContext->create();
    m_glContext->moveToThread(m_thread);

    qInfo() << "surface format: " << sharedContext->format();
    m_surface.setFormat(QSurfaceFormat::defaultFormat());
    m_surface.create();
    m_surface.moveToThread(m_thread);

    m_thread->start();
}

RenderThread::~RenderThread() {
    join(true);

    if (m_glContext != nullptr) {
        m_glContext->deleteLater();
        m_glContext = nullptr;
    }
}

void RenderThread::join(bool dropPendingTasks) {
    if (m_thread) {
        if (dropPendingTasks) {
            dropAllTasks();
        }

        m_thread->quit();
        m_thread->wait();
        m_thread = nullptr;
    }
}



void RenderThread::runOnRenderThread(Task&& task) {
    appendTask(task);
    bool running = true;
    m_runningMutex.lock();
    running = m_isRunning;
    m_runningMutex.unlock();
    if (!running) {
        emit triggerRun();
    }
}

void RenderThread::syncRunOnRenderThread(std::function<void()> func) {
    assert(func);
    m_syncRunFunc = func;
    emit triggerRunSync();
    assert(m_syncRunFunc == nullptr);
}

void RenderThread::onRun() {
    m_runningMutex.lock();
    m_isRunning = true;
    m_runningMutex.unlock();

    makeCurrent();
    runAllTasks();
    doneCurrent();

    m_runningMutex.lock();
    m_isRunning = false;
    m_runningMutex.unlock();
}

void RenderThread::onSyncRunTask() {
    if (m_syncRunFunc) {
        makeCurrent();
        runAllTasks();
        m_syncRunFunc();
        doneCurrent();
        m_syncRunFunc = nullptr;
    }
}

void RenderThread::dropAllTasks() {
    std::lock_guard<std::mutex> lockGuard(m_tasksMutex);
    m_tasksOnRenderThread.clear();
}

void RenderThread::runAllTasks() {
    std::list<Task> tasksOnRenderThread;
    {
        std::lock_guard<std::mutex> lockGuard(m_tasksMutex);
        tasksOnRenderThread = m_tasksOnRenderThread;
        m_tasksOnRenderThread.clear();
    }

    qInfo() << "render task size: " << tasksOnRenderThread.size();
    for (const auto& task : tasksOnRenderThread) {
        if (task.func) {
            task.func();
        }
        // assert(m_tasksOnRenderThread.size() < 100);
    }
}

void RenderThread::appendTask(const Task& task) {
    std::lock_guard<std::mutex> lockGuard(m_tasksMutex);
    bool bExist = false;
    for (const auto& renderTask : m_tasksOnRenderThread) {
        if (task.id == renderTask.id && task.id == CanvasRender) {
            bExist = true;
            break;
        }
    }

    if (!bExist) {
        m_tasksOnRenderThread.push_back(task);
    }
}

void RenderThread::makeCurrent() {
    m_glContext->makeCurrent(&m_surface);
}

void RenderThread::doneCurrent() {
    m_glContext->doneCurrent();
}
