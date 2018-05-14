#ifndef HONLINEREFRESHTHREAD_H
#define HONLINEREFRESHTHREAD_H

/*
 * 界面状态刷新多线程类
*/
#include <QThread>
class HOnlineWindow;
class HOnlineRefreshThread;
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE
class HWork : public QObject
{
    Q_OBJECT
public:
    HWork(HOnlineWindow* pParent);
public slots:
    void on_time();
public:
    HOnlineWindow* m_pOnlineWindow;
    HOnlineRefreshThread *p_Thread;
};

class HOnlineRefreshThread : public QThread
{
    Q_OBJECT
public:
    HOnlineRefreshThread(HOnlineWindow* onlineWindow);

public:
    virtual void run();

signals:
    void update();

private:
    HOnlineWindow* m_pOnlineWindow;
};

#endif // HONLINEREFRESHTHREAD_H
