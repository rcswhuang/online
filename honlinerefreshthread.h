#ifndef HONLINEREFRESHTHREAD_H
#define HONLINEREFRESHTHREAD_H

/*
 * 界面状态刷新多线程类
*/
#include <QThread>
class HOnlineWindow;
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE
class HOnlineRefreshThread : public QThread
{
public:
    HOnlineRefreshThread(HOnlineWindow* onlineWindow);

public:
    virtual void run();
private:
    HOnlineWindow* m_pOnlineWindow;
};

#endif // HONLINEREFRESHTHREAD_H
