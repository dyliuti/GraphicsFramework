#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLWidget>
#include <QThread>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include "boarddefine.h"

class BOARD_EXPORT RenderThread : public QObject {
    Q_OBJECT
   public:
    explicit RenderThread(QOpenGLWidget* sharedWidget);
    ~RenderThread();
    enum RenderType {
        TaskRender,
        CanvasRender
    };
    struct Task {
        std::shared_ptr<std::function<void()>> taskPtr;
        std::function<void()> task;
        int id = 0;

        bool operator<(const Task& b) {
            return this->id < b.id;
        };

        bool operator==(const Task& task) {
            return this->id == task.id;
        };
    };

    template <class T>
    static Task makeTask(T&& func, RenderType id = TaskRender) {
        Task t;
        t.id = id;
        typedef typename std::decay<T>::type RealT;
        if constexpr (std::is_same_v<RealT, decltype(t.taskPtr)>) {
            t.taskPtr = std::forward<T>(func);
        } else {
            t.task = std::forward<T>(func);
        }

        return t;
    }

    template <class T>
    inline void runOnRenderThread(T&& func, RenderType id = TaskRender) {
        runOnRenderThread(makeTask(func, id));
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
    void run();
    void syncRunTask();

   signals:
    void triggerRun();
    void triggerRunSync();

   protected:
    QThread* m_thread{};
    QOpenGLContext* m_glContext{};
    QOffscreenSurface m_surface;
    std::function<void()> m_syncRunFunc;
    std::mutex m_tasksMutex;
    std::list<Task> m_tasksOnRenderThread;
    // sync run
    std::mutex m_runningMutex;
    bool m_isRunning = false;
};

#endif  // RENDERTHREAD_H
