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
#include <QTimer>
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

    m_pOnlineScene = new HOnlineScene(m_pWfSystemMgr);
    m_pOnlineView->setScene(m_pOnlineScene);

    //启动线程
    m_pOnlineRefreshThread = new m_pOnlineRefreshThread(this);
    m_pOnlineRefreshThread->start();

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
     * 1.获取当前所有需要刷新的测点主要是（遥信、遥测），显示patterID
     * 2.实时库获取当前测点的状态
     * 3.如果状态不一致则需要修改patterID
     * 4.如果是遥测则直接刷新新值
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
    int curPattern = pObj->getIconSymbol()->getCurrentPattern();
    quint8 btType = (quint8)pObj->getObjType();
    quint16 wStation = pObj->getDynamicObj()->getDBStation();
    quint16 wPoint = pObj->getDynamicObj()->getDBPoint();
    //遥信
    if(TEMPLATE_TYPE_DIGITAL == btType)
    {

    }
}
