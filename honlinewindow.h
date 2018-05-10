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
class HWfSystemDoc;
class HOnlineRefreshThread;
class HIconObj;
QT_BEGIN_NAMESPACE
class QTimer;
class QList;
QT_END_NAMESPACE
class HOnlineWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HOnlineWindow(QWidget *parent = 0);
    HOnlineWindow(HWfSystemMgr* mgr,QWidget *parent = 0);
    ~HOnlineWindow();
public:

    void openOnlineGraph(const QString &graphName, const int graphID);

    //刷新online view
    void refreshOnlineView();

    //加载online图元
    void openOnlineScene();

    //清除online上的item
    void clearOnlineSceneItem();

    //设置HIconObj绘制相关属性
    void updateIconObj(HIconObj* pObj);

public slots:
    void updateOnlineView();

private:
    QRect logicRect;
private:
    Ui::HOnlineWindow *ui;
    HOnlineRefreshThread* m_pOnlineRefreshThread;
    HOnlineView* m_pOnlineView;
    HOnlineScene* m_pOnlineScene;
    HWfSystemMgr* m_pWfSystemMgr;
    QList<HIconObj*> m_pIconObjList;
};

#endif // HONLINEWINDOW_H
