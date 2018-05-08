#ifndef HONLINEWINDOW_H
#define HONLINEWINDOW_H

#include <QDialog>

namespace Ui {
class HOnlineWindow;
}
/*
 * 画面浏览主窗口：两部分
 * 显示graph
*/
class HOnlineScene;
class HOnlineView;
class HWfSystemMgr;
class HOnlineWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HOnlineWindow(QWidget *parent = 0);
    HOnlineWindow(HWfSystemMgr* mgr,QWidget *parent = 0);
    ~HOnlineWindow();
    void initOnlineWindow();

private:
    Ui::HOnlineWindow *ui;
    HOnlineView* m_pOnlineView;
    HOnlineScene* m_pOnlineScene;
    HWfSystemMgr* m_pWfSystemMgr;
};

#endif // HONLINEWINDOW_H
