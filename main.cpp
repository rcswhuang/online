#include "honlinemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HOnlineMainWindow w;
    w.show();

    return a.exec();
}
