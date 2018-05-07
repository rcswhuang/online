#include "honlinemainwindow.h"
#include "ui_onlinemainwindow.h"
#include "honlinetreewidget.h"
#include "honlineview.h"
#include "honlinemgr.h"
HOnlineMainWindow::HOnlineMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HOnlineMainWindow)
{
    ui->setupUi(this);
}

HOnlineMainWindow::~HOnlineMainWindow()
{
    delete ui;
}

/* 1.刷新树形界面，保证树形打开的是根画面，
 * 2.树形根画面节点调用后，发射打开画面信号，调MainWindow打开窗口，显示画面
 * 3.显示画面窗口调用scene来完成
 */
void HOnlineMainWindow::initOnlineMainWindow()
{

    //左边树结构
    m_pOnlineTreeWidget = new HOnlineTreeWidget(NULL);
    ui->dockWidget->setWidget(m_pOnlineTreeWidget);
    connect(m_pOnlineTreeWidget,SIGNAL(graphOpen(const QString&,const int)),this,SLOT(Open(const QString&,const int)));//打开

    m_pOnlineView = new HOnlineView(ui->centralWidget);
    m_pOnlineView->setObjectName(QStringLiteral("画图系统"));
    m_pOnlineView->setFrameShape(QFrame::NoFrame);
    m_pOnlineView->setFrameShadow(QFrame::Plain);
    m_pOnlineView->setLineWidth(0);

    ui->verticalLayout->addWidget(m_pOnlineView);
    m_pOnlineMgr->setOnlineView(m_pOnlineView);
}

void HOnlineMainWindow::Open(const QString &graphName, const int graphID)
{
    if(!m_pOnlineMgr)
        return;
    m_pOnlineMgr->clearOnlineSceneItem();
    m_pOnlineMgr->Open(graphName,graphID);
    m_pOnlineMgr->openOnlineScene();
    m_pOnlineMgr->refreshView();
}
