#ifndef HONLINEMAINWINDOW_H
#define HONLINEMAINWINDOW_H

#include <QMainWindow>
class HOnlineTreeWidget;
namespace Ui {
class HOnlineMainWindow;
}

class HOnlineMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HOnlineMainWindow(QWidget *parent = 0);
    ~HOnlineMainWindow();

public:
    void initOnlineMainWindow();
private:
    Ui::HOnlineMainWindow *ui;
    HOnlineTreeWidget* pOnlineTreeWidget;
};

#endif // HONLINEMAINWINDOW_H
