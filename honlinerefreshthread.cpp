#include "honlinerefreshthread.h"
#include "honlinewindow.h"
#include <QDebug>
#include <QTimer>
HOnlineRefreshThread::HOnlineRefreshThread(HOnlineWindow* ow)
    :m_pOnlineWindow(ow)
{

}

void HOnlineRefreshThread::run()
{
    //测试，检查独立进程是否启动工作
    qDebug()<<"HOnlineRefreshThread id" << QThread::currentThreadId();
    QTimer timer;
    connect(&timer,SIGNAL(timeout()),m_pOnlineWindow,SLOT(updateOnlineView()));
    timer.start(1000);
    exec();
}
