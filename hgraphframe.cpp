#include "hgraphframe.h"
#include "publicdata.h"
#include "hgraphicsview.h"
#include "hgraphicsscene.h"
#include "hwfsystemdoc.h"
#include "hwfsystemmgr.h"
#include "hgraph.h"
#include "hiconobj.h"
#include "hgraphfreshthread.h"
#include "hkernelapi.h"
#include <QTimer>
#include <QScrollBar>
#include <QDesktopWidget>
#include <QApplication>
HGraphFrame::HGraphFrame(HFrame *parent) :
    HFrame(parent)
{
    m_pWfSystemMgr = NULL;
    initGraphFrame();
    setWindowTitle("画面浏览");
}

HGraphFrame::HGraphFrame(HWfSystemMgr* mgr,HFrame *parent):
    HFrame(parent),m_pWfSystemMgr(mgr)
{
    logicRect = QRect(-500,-500,1000,1000);
    initGraphFrame();
}

HGraphFrame::~HGraphFrame()
{
}

void HGraphFrame::initGraphFrame()
{
    m_pGraphicsView = new HGraphicsView(this);
    m_pGraphicsView->setObjectName(QStringLiteral("画图系统"));
    m_pGraphicsView->setFrameShape(QFrame::NoFrame);
    m_pGraphicsView->setFrameShadow(QFrame::Plain);
    m_pGraphicsView->setLineWidth(0);
    centerLayout->addWidget(m_pGraphicsView);

    m_pGraphicsScene = new HGraphicsScene(this);
    m_pGraphicsView->setScene(m_pGraphicsScene);
    m_pGraphicsView->setSceneRect(logicRect);

    QScrollBar* pBar = m_pGraphicsView->horizontalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }
    pBar = m_pGraphicsView->verticalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }

    //启动线程
    m_pGraphRefreshThread = new HGraphRefreshThread(this);
    //m_pOnlineRefreshThread->start();
    connect(m_pGraphRefreshThread, &HGraphRefreshThread::update, this, &HGraphFrame::updatePoints);
    //connect(m_pThread, &HUpdateThread::finished, workerThread, &QObject::deleteLater);
    m_pGraphRefreshThread->start();
}

//设置scene窗口
QRect HGraphFrame::getLogicRect()
{
    return logicRect;
}

HGraphicsView* HGraphFrame::graphicsView()
{
 if(m_pGraphicsView)
     return m_pGraphicsView;
 return NULL;
}

HGraphicsScene* HGraphFrame::graphicsScene()
{
    if(m_pGraphicsScene)
        return m_pGraphicsScene;
    return NULL;
}

void HGraphFrame::openGraph(const QString &graphName, const int graphID)
{
    if(!m_pWfSystemMgr || !m_pWfSystemMgr->wfSystemDoc())
        return;
    HGraph* graph = m_pWfSystemMgr->wfSystemDoc()->findGraph(graphID);
    if(!graph) return;
    m_pGraphicsScene->setGraph(graph);
    //int nWidth = graph->getGraphWidth();
    //int nHeight = graph->getGraphHeight();
    //logicRect = QRect(-nWidth/2,-nHeight/2,nWidth,nHeight);
    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    logicRect.setX(0-(width-2)/2);
    logicRect.setY(0-(height-100)/2);
    logicRect.setWidth(width-2);
    logicRect.setHeight(height-100/2);


    //测试下面语句是否可行 如不可行,用下下面语句 ----huangw
    //m_pOnlineView->updateSceneRect(logicRect);
    m_pGraphicsView->setSceneRect(logicRect);
    clearGraphicsSceneItem();
    openGraphicsScene();

    refreshGraphicsView();
}

//刷新online view
void HGraphFrame::refreshGraphicsView()
{
    if(!m_pGraphicsView)
        return;
    m_pGraphicsView->refresh();
}

//加载online图元
void HGraphFrame::openGraphicsScene()
{
    if(!m_pGraphicsScene)
        return;
    m_pGraphicsScene->openGraphicsSceneItems();
}

//清除online上的item
void HGraphFrame::clearGraphicsSceneItem()
{
    if(!m_pGraphicsScene)
        return;
    m_pGraphicsScene->delGraphicsSceneItems();
}

void HGraphFrame::updatePoints()
{
    m_pGraphicsView->refresh();
}
