#include "honlinemgr.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include "honlineview.h"
#include "honlinedoc.h"
#include "honlinescene.h"
#include "hgraph.h"
//图形文件管理总类
HOnlineMgr::HOnlineMgr()
    :logicRectF(-500,-500,1000,1000)
{
    pOnlineDoc = new HOnlineDoc(this);
    Q_ASSERT(pOnlineDoc);

   // pCommand = new QUndoStack(this);

    //pTempGraph = new HGraph("");

    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    logicRectF.setX(0-(width-2)/2);
    logicRectF.setY(0-(height-100)/2);
    logicRectF.setWidth(width-2);
    logicRectF.setHeight(height-100/2);

    pOnlineScene = new HOnlineScene(this);
    pOnlineView = NULL;
    drawShape = enumSelection;

}

//启动时加载数据库
void HOnlineMgr::loadStation()
{
    if(!pOnlineDoc)
        return;
    pOnlineDoc->loadStation();
}

//启动时加载画面信息
void HOnlineMgr::loadGraphs()
{
    if(!pOnlineDoc)
        return;
    pOnlineDoc->loadAllGraph();
}

HOnlineScene* HOnlineMgr::onlineScene()
{
    return pOnlineScene;
}

void HOnlineMgr::setOnlineView(HOnlineView* view)
{
    pOnlineView = view;
    pOnlineView->setScene(pOnlineScene);
    //pGraphEditorScene->setView(pGraphEditorView);
    QRectF rectF(logicRectF);
    pOnlineScene->setSceneRect(rectF);

    if(pTempGraph)
    {
       // p
    }

    QScrollBar* pBar = pOnlineView->horizontalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }
    pBar = pOnlineView->verticalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }
}

HOnlineView* HOnlineMgr::onlineView()
{
    return pOnlineView;
}

HOnlineDoc* HOnlineMgr::onlineDoc()
{
    return pOnlineDoc;
}

//设置逻辑界面大小
void HOnlineMgr::setLogicRect(const QRectF& rect)
{
    logicRectF = rect;
}

QRectF HOnlineMgr::getLogicRect()
{
    return logicRectF;
}

//判断graph文件名是否存在
bool HOnlineMgr::findGraphByName(const QString& graphName)
{
    if(!pOnlineDoc)
        return false;
    HGraph* graph = pOnlineDoc->findGraph(graphName);
    if(!graph)
        return false;
    return true;
}

bool HOnlineMgr::Open(const QString& graphName,int id)
{
    if(!pOnlineDoc)
        return false;
    return pOnlineDoc->openGraph(graphName,id);
}


void HOnlineMgr::refreshView()
{
    if(!pOnlineView)
        return;
    pOnlineView->refresh();
}

void HOnlineMgr::openOnlineScene()
{
    if(!pOnlineScene)
        return;
    pOnlineScene->openOnlineSceneItems();
}

void HOnlineMgr::clearOnlineSceneItem()
{
    if(!pOnlineScene)
        return;
    pOnlineScene->delOnlineSceneItems();
}
