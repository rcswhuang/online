#ifndef HONLINEWINDOW_H
#define HONLINEWINDOW_H

#include <QDialog>
#include <QList>
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
QT_END_NAMESPACE
class HOnlineWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HOnlineWindow(QWidget *parent = 0);
    HOnlineWindow(HWfSystemMgr* mgr,QWidget *parent = 0);
    ~HOnlineWindow();
public:
    //初始化窗口
    void initOnlineWindow();

    void openOnlineGraph(const QString &graphName, const int graphID);

    //刷新online view
    void refreshOnlineView();

    //加载online图元
    void openOnlineScene();

    //清除online上的item
    void clearOnlineSceneItem();

    //设置HIconObj绘制相关属性
    void updateIconObj(HIconObj* pObj);

    //设置scene窗口
    QRect getLogicRect();

    //获取view
    HOnlineView* onlineView();

    //获取scene
    HOnlineScene* onlineScene();

public slots:
    void updatePoints();

public:
    QList<HIconObj*> m_pIconObjList;
private:
    QRect logicRect;
    Ui::HOnlineWindow *ui;
    HOnlineRefreshThread* m_pOnlineRefreshThread;
    HOnlineView* m_pOnlineView;
    HOnlineScene* m_pOnlineScene;
    HWfSystemMgr* m_pWfSystemMgr;

};

#endif // HONLINEWINDOW_H
