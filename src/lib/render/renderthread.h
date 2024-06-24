#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include "render_global.h"
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLWidget>
#include <QThread>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>

class RENDER_EXPORT RenderThread : public QObject {
    Q_OBJECT
public:
    explicit RenderThread(QOpenGLWidget* sharedWidget);
    ~RenderThread();
    enum RenderType {
        TaskRender,
        CanvasRender
    };
    struct Task {
        std::function<void()> func;
        RenderType id = TaskRender;

        bool operator<(const Task& b)
        {
            return this->id < b.id;
        };

        bool operator==(const Task& task)
        {
            return this->id == task.id;
        };
    };

    template <class T>
    static Task makeTask(T&& func, RenderType id = TaskRender)
    {
        Task t;
        t.id = id;
        t.func = std::forward<T>(func);
        //        typedef typename std::decay<T>::type RealT;
        //        if constexpr (std::is_same_v<RealT, decltype(t.taskPtr)>) {
        //            t.taskPtr = std::forward<T>(func);
        //        } else {
        //            t.task = std::forward<T>(func);
        //        }

        return t;
    }

    template <class T>
    inline void runOnRenderThread(T&& func, RenderType id = TaskRender)
    {
        runOnRenderThread(makeTask(std::forward<T>(func), id));
    }

    void runOnRenderThread(Task&& task);
    void syncRunOnRenderThread(std::function<void()> func);
    void makeCurrent();
    void doneCurrent();
    void dropAllTasks();

protected:
    void join(bool dropPendingTasks);
    void runAllTasks();
    void appendTask(const Task& task);

protected slots:
    void onRun();
    void onSyncRunTask();

signals:
    void triggerRun();
    void triggerRunSync();

protected:
    QThread* m_thread {};
    QOpenGLContext* m_glContext {};
    QOffscreenSurface m_surface;
    std::function<void()> m_syncRunFunc;
    std::mutex m_tasksMutex;
    std::list<Task> m_tasksOnRenderThread;
    // sync run
    std::mutex m_runningMutex;
    bool m_isRunning = false;
};

#endif // RENDERTHREAD_H
