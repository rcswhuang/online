#include "honlinewindow.h"
#include "ui_onlinewindow.h"
#include "publicdata.h"
#include "honlineview.h"
#include "honlinescene.h"
#include "hwfsystemdoc.h"
#include "hwfsystemmgr.h"
#include "hgraph.h"
#include "hiconobj.h"
#include "honlinerefreshthread.h"
#include "hkernelapi.h"
#include <QTimer>
#include <QScrollBar>
#include <QDesktopWidget>
HOnlineWindow::HOnlineWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HOnlineWindow)
{
    ui->setupUi(this);
    m_pWfSystemMgr = NULL;
    initOnlineWindow();
    setWindowTitle("画面浏览");
}

HOnlineWindow::HOnlineWindow(HWfSystemMgr* mgr,QWidget *parent):
    QDialog(parent),
    ui(new Ui::HOnlineWindow),m_pWfSystemMgr(mgr)
{
    ui->setupUi(this);
    logicRect = QRect(-500,-500,1000,1000);
    initOnlineWindow();
}

HOnlineWindow::~HOnlineWindow()
{
    delete ui;
}

void HOnlineWindow::initOnlineWindow()
{
    m_pOnlineView = new HOnlineView(this);
    m_pOnlineView->setObjectName(QStringLiteral("画图系统"));
    m_pOnlineView->setFrameShape(QFrame::NoFrame);
    m_pOnlineView->setFrameShadow(QFrame::Plain);
    m_pOnlineView->setLineWidth(0);
    ui->verticalLayout->addWidget(m_pOnlineView);

    m_pOnlineScene = new HOnlineScene(this);
    m_pOnlineView->setScene(m_pOnlineScene);
    m_pOnlineView->setSceneRect(logicRect);

    QScrollBar* pBar = m_pOnlineView->horizontalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }
    pBar = m_pOnlineView->verticalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }

    //启动线程
    m_pOnlineRefreshThread = new HOnlineRefreshThread(this);
    //m_pOnlineRefreshThread->start();
    connect(m_pOnlineRefreshThread, &HOnlineRefreshThread::update, this, &HOnlineWindow::updatePoints);
    //connect(m_pThread, &HUpdateThread::finished, workerThread, &QObject::deleteLater);
    m_pOnlineRefreshThread->start();
}

//设置scene窗口
QRect HOnlineWindow::getLogicRect()
{
    return logicRect;
}

HOnlineView* HOnlineWindow::onlineView()
{
 if(m_pOnlineView)
     return m_pOnlineView;
 return NULL;
}

HOnlineScene* HOnlineWindow::onlineScene()
{
    if(m_pOnlineScene)
        return m_pOnlineScene;
    return NULL;
}

void HOnlineWindow::openOnlineGraph(const QString &graphName, const int graphID)
{
    if(!m_pWfSystemMgr || !m_pWfSystemMgr->wfSystemDoc())
        return;
    HGraph* graph = m_pWfSystemMgr->wfSystemDoc()->findGraph(graphID);
    if(!graph) return;
    m_pOnlineScene->setGraph(graph);
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
    m_pOnlineView->setSceneRect(logicRect);
    clearOnlineSceneItem();
    openOnlineScene();

    refreshOnlineView();
}

//刷新online view
void HOnlineWindow::refreshOnlineView()
{
    if(!m_pOnlineView)
        return;
    m_pOnlineView->refresh();
}

//加载online图元
void HOnlineWindow::openOnlineScene()
{
    if(!m_pOnlineScene)
        return;
    m_pOnlineScene->openOnlineSceneItems();
}

//清除online上的item
void HOnlineWindow::clearOnlineSceneItem()
{
    if(!m_pOnlineScene)
        return;
    m_pOnlineScene->delOnlineSceneItems();
}

void HOnlineWindow::updatePoints()
{
    m_pOnlineView->refresh();
}
