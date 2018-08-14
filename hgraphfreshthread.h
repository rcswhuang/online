#ifndef HONLINEREFRESHTHREAD_H
#define HONLINEREFRESHTHREAD_H

/*
 * 界面状态刷新多线程类
*/
#include <QThread>
class HGraphFrame;
class HGraphRefreshThread;
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE
class HWork : public QObject
{
    Q_OBJECT
public:
    HWork(HGraphFrame* pParent);
public slots:
    void on_time();
public:
    HGraphFrame* m_pGraphFrame;
    HGraphRefreshThread *p_Thread;
};

class HGraphRefreshThread : public QThread
{
    Q_OBJECT
public:
    HGraphRefreshThread(HGraphFrame* onlineWindow);

public:
    virtual void run();

signals:
    void update();

private:
    HGraphFrame* m_pGraphFrame;
};

#endif // HONLINEREFRESHTHREAD_H
