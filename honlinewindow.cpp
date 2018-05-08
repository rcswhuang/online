#include "honlinewindow.h"
#include "ui_onlinewindow.h"
#include "honlineview.h"
#include "honlinescene.h"
#include "hwfsystemmgr.h"

HOnlineWindow::HOnlineWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HOnlineWindow)
{
    ui->setupUi(this);
    m_pWfSystemMgr = NULL;
    initOnlineWindow();
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
}
