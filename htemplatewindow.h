#ifndef HTEMPLATEWINDOW_H
#define HTEMPLATEWINDOW_H

#include <QDialog>

namespace Ui {
class HTemplateWindow;
}
/*
 * 模板票窗口:2个部分
 * 左边：编辑模板票部分
 * 右边：view窗口
*/
class HTemplateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HTemplateWindow(QWidget *parent = 0);
    ~HTemplateWindow();

private:
    Ui::HTemplateWindow *ui;
};

#endif // HTEMPLATEWINDOW_H
