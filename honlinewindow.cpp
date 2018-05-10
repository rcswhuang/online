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

    m_pOnlineScene = new HOnlineScene();
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
    m_pOnlineRefreshThread = new m_pOnlineRefreshThread(this);
    m_pOnlineRefreshThread->start();

}

void HOnlineWindow::openOnlineGraph(const QString &graphName, const int graphID)
{
    if(!m_pWfSystemMgr || !m_pWfSystemMgr->wfSystemDoc())
        return;
    HGraph* graph = m_pWfSystemMgr->wfSystemDoc()->findGraph(graphID);
    if(!graph) return;
    m_pOnlineScene->setGraph(graph);
    clearOnlineSceneItem();
    openOnlineScene();
    int nWidth = graph->getGraphWidth();
    int nHeight = graph->getGraphHeight();
    logicRect = QRect(-nWidth/2,-nHeight/2,nWidth,nHeight);
    //测试下面语句是否可行 如不可行,用下下面语句 ----huangw
    m_pOnlineView->updateSceneRect(logicRect);
    //m_pOnlineView->setSceneRect(logicRect);
    //refreshOnlineView();
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

void HOnlineWindow::updateOnlineView()
{
    /*
     * 在绘制HGraph文件过程中，m_pIconObjList只增加遥信遥测部分
    */
    for(int i = 0; i < m_pIconObjList.count();i++)
    {
        HIconObj* iconObj = (HIconObj*)m_pIconObjList[i];
        if(iconObj)
        {
            updateIconObj(iconObj);
        }
    }
}

void HOnlineWindow::updateIconObj(HIconObj *pObj)
{
    if(!pObj)
        return;
    //可以剥离出来独立dll来处理
    int nCurPattern = pObj->getIconSymbol()->getCurrentPattern();
    quint8 btType = (quint8)pObj->getObjType();
    quint16 wStation = pObj->getDynamicObj()->getDBStation();
    quint16 wPoint = pObj->getDynamicObj()->getDBPoint();
    ushort wAttr = pObj->getDynamicObj()->getDBAttr();
    //遥信
    if(TEMPLATE_TYPE_DIGITAL == btType)
    {
        DBHANDLE dbHandle = getDbHandle(wStation,btType,wPoint,TYPE_DB_REALTIME);
        if(!isValidDbHandle(dbHandle))
            return;

        int nPFlags;
        if(!getAttr(dbHandle,ATTR_DGT_PFLAG,&nPFlags))
            return;
        int m_nPFlags = 0;
        if(nPFlags & ENABLE_REPAIR)
            m_nPFlags = ENABLE_REPAIR;

        int nRFlags;
        if(!getAttr(dbHandle,ATTR_DGT_RFLAG,&nRFlags))
            return;

        int m_nRFlags = 0;
        if(nRFlags & RESULT_MANUAL)
            m_nRFlags = RESULT_MANUAL;
        else if(nRFlags & RESULT_ACK)
            m_nRFlags = RESULT_ACK;
        else if(nRFlags & RESULT_CHANGE)
            m_nRFlags = RESULT_CHANGE;
        else if(nRFlags & RESULT_ACCIDENT)
            m_nRFlags = RESULT_ACCIDENT;

        quint8 m_btValue = 0;
        if(wAttr == ATTR_DGT_VALUE)
        {
            if(!getAttr(dbHandle,ATTR_DGT_VALUE,&m_btValue))
                return false;

        }
        else if(ATTR_DGT_4_STATE_VALUE == wAttr)
        {
            if(!getAttr(dbHandle,ATTR_DGT_4_STATE_VALUE,&m_btValue))
                return false;
        }

        if(m_btValue > 3) m_btValue = 3;

        if(ENABLE_REPAIR == m_nPFlags)
        {
            pObj->setLineColorName(Qt::red);
            pObj->setFillColorName(Qt::red);
        }

        //关键地方，画面变位的地方
        if(nCurPattern != m_btValue)
        {
            pObj->getIconSymbol()->setCurrentPattern(m_btValue);
            //是不是需要刷新pObj这块区域
            m_pOnlineView->invalidateScene(pObj->boundingRect(),QGraphicsScene::ItemLayer);
        }
    }
}
