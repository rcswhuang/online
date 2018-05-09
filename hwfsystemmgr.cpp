#include "hwfsystemmgr.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include "honlineview.h"
#include "hwfsystemdoc.h"
#include "honlinescene.h"
#include "hgraph.h"
//图形文件管理总类
HWfSystemMgr::HWfSystemMgr()
    :logicRectF(-500,-500,1000,1000)
{
    m_wfSystemDoc = new HWfSystemDoc(this);
    Q_ASSERT(m_wfSystemDoc);

   // pCommand = new QUndoStack(this);

    //pTempGraph = new HGraph("");

    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    logicRectF.setX(0-(width-2)/2);
    logicRectF.setY(0-(height-100)/2);
    logicRectF.setWidth(width-2);
    logicRectF.setHeight(height-100/2);

    //pOnlineScene = new HOnlineScene(this);
    //pOnlineView = NULL;
   // drawShape = enumSelection;

}

//启动时加载数据库
void HWfSystemMgr::loadStation()
{
    if(!m_wfSystemDoc)
        return;
    m_wfSystemDoc->loadStation();
}

//启动时加载画面信息
void HWfSystemMgr::loadGraphs()
{
    if(!m_wfSystemDoc)
        return;
    m_wfSystemDoc->loadAllGraph();
}

/*
HOnlineScene* HWfSystemMgr::onlineScene()
{
    return pOnlineScene;
}
*/
/*
void HWfSystemMgr::setOnlineView(HOnlineView* view)
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
}*/
/*
HOnlineView* HWfSystemMgr::onlineView()
{
    return pOnlineView;
}
*/

HWfSystemDoc* HWfSystemMgr::wfSystemDoc()
{
    return m_wfSystemDoc;
}

//设置逻辑界面大小
void HWfSystemMgr::setLogicRect(const QRectF& rect)
{
    logicRectF = rect;
}

QRectF HWfSystemMgr::getLogicRect()
{
    return logicRectF;
}

//判断graph文件名是否存在
bool HWfSystemMgr::findGraphByName(const QString& graphName)
{
    if(!m_wfSystemDoc)
        return false;
    HGraph* graph = m_wfSystemDoc->findGraph(graphName);
    if(!graph)
        return false;
    return true;
}

bool HWfSystemMgr::Open(const QString& graphName,int id)
{
    if(!m_wfSystemDoc)
        return false;
    return m_wfSystemDoc->openGraph(graphName,id);
}



void HWfSystemMgr::refreshOnlineView()
{
    if(!m_pOnlineWindow)
        return;
    m_pOnlineWindow->refresh();
}

void HWfSystemMgr::openOnlineScene()
{
    if(!m_pOnlineWindow)
        return;
    m_pOnlineWindow->openOnlineSceneItems();
}

void HWfSystemMgr::clearOnlineSceneItem()
{
    if(!m_pOnlineWindow)
        return;
    m_pOnlineWindow->delOnlineSceneItems();
}

