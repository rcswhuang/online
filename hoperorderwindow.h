#ifndef HOPERORDERWINDOW_H
#define HOPERORDERWINDOW_H

#include <QDialog>

namespace Ui {
class operorderWindow;
}
/*
 * 操作票预演窗口：两部分
 * 1.左边是编辑窗口
 * 2.右边是viewer窗口
*/
class HOperorderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HOperorderWindow(QWidget *parent = 0);
    ~HOperorderWindow();

private:
    Ui::operorderWindow *ui;
};

#endif // HOPERORDERWINDOW_H
