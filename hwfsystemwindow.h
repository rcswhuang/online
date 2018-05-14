#ifndef HWFSYSTEMWINDOW_H
#define HWFSYSTEMWINDOW_H

#include <QMainWindow>

namespace Ui {
class wfSystemWindow;
}

class HOnlineWindow;
class HWfSystemMgr;
class HOnlineTreeWidget;
QT_BEGIN_NAMESPACE
class QMdiArea;
class QMdiSubWindow;
class QDialog;
QT_END_NAMESPACE
/*
 * 五防系统主窗口
 * 包含状态栏、规则、公式、网络
 * 画面浏览、画面预演、模板票编辑等公式
*/
class HWfSystemWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HWfSystemWindow(QWidget *parent = 0);
    HWfSystemWindow(HWfSystemMgr *Mgr,QWidget *parent = 0);
    ~HWfSystemWindow();

public:
    void initMainWindow();
    QMdiArea* getMdiArea(){return mdiArea;}

public slots:
    void Open(const QString&,const int);
    void createOnlineWindow();
    void createKernelTest();

private:
     QDialog *activeMdiChild() const;
     QMdiSubWindow *findMdiChild(const QString &fileName) const;

private:
    Ui::wfSystemWindow *ui;
    QMdiArea *mdiArea;
    //在线预览窗口
    //预演窗口、模板编辑窗口、网络报文监视窗口、串口报文监视窗口
    HWfSystemMgr* m_pWfSystemMgr;
    HOnlineTreeWidget* m_pOnlineTreeWidget;

};

#endif // HWFSYSTEMWINDOW_H
