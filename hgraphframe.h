#ifndef HONLINEWINDOW_H
#define HONLINEWINDOW_H

#include "hframe.h"
#include <QList>
/*
 * 画面浏览主窗口：两部分
 * 显示graph
*/
class HGraphicsScene;
class HGraphicsView;
class HWfSystemMgr;
class HWfSystemDoc;
class HGraphRefreshThread;
class HIconObj;
QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE
class HGraphFrame : public HFrame
{
    Q_OBJECT

public:
    explicit HGraphFrame(HFrame *parent = 0);
    HGraphFrame(HWfSystemMgr* mgr,HFrame *parent = 0);
    ~HGraphFrame();
public:
    //初始化窗口
    void initGraphFrame();

    void openGraph(const QString &graphName, const int graphID);

    //刷新online view
    void refreshGraphicsView();

    //加载online图元
    void openGraphicsScene();

    //清除online上的item
    void clearGraphicsSceneItem();

    //设置HIconObj绘制相关属性
    void updateIconObj(HIconObj* pObj);

    //设置scene窗口
    QRect getLogicRect();

    //获取view
    HGraphicsView* graphicsView();

    //获取scene
    HGraphicsScene* graphicsScene();

public slots:
    void updatePoints();

public:
    QList<HIconObj*> m_pIconObjList;
private:
    QRect logicRect;
    HGraphRefreshThread* m_pGraphRefreshThread;
    HGraphicsView* m_pGraphicsView;
    HGraphicsScene* m_pGraphicsScene;
    HWfSystemMgr* m_pWfSystemMgr;
};

#endif // HONLINEWINDOW_H
