#include "honlinemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HOnlineMainWindow w;
    w.show();

    //1.加载数据库信息 要调kernel模块
    //2.
    return a.exec();
}
