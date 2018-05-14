#include "hwfsystemwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include "hwfsystemmgr.h"
int main(int argc, char *argv[])
{
    //1.加载数据库信息 要调kernel模块
    //2.
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    QPixmap pixmap(":/pixmaps/splash.jpg");

    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();

    HWfSystemMgr* pMgr = new HWfSystemMgr;
    pMgr->loadInstance();
    splash->showMessage(QStringLiteral("加载实时库信息"));
    qApp->processEvents();

    //loading all graphs
    pMgr->loadGraphs();
    splash->showMessage(QStringLiteral("加载所有画面信息"));
    qApp->processEvents();

    //加载插件信息
    HWfSystemWindow* w = new HWfSystemWindow(pMgr);
    w->show();
    splash->finish(w);
    return a.exec();
}
