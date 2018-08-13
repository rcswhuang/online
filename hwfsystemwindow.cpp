#include "hwfsystemwindow.h"
#include "ui_wfsystemwindow.h"
#include "honlinetreewidget.h"
#include "hgraphicsview.h"
#include "hwfsystemmgr.h"
#include "hgraphframe.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include "hkerneltest.h"
HWfSystemWindow::HWfSystemWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::wfSystemWindow)
{
    ui->setupUi(this);
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    setWindowTitle(tr("MDI"));
    setUnifiedTitleAndToolBarOnMac(true);

    connect(ui->actionOnline,SIGNAL(triggered(bool)),this,SLOT(createOnlineWindow()));
}

HWfSystemWindow::HWfSystemWindow(HWfSystemMgr *mgr,QWidget *parent) :
    QMainWindow(parent),ui(new Ui::wfSystemWindow),m_pWfSystemMgr(mgr)
{
     ui->setupUi(this);
     m_pWfSystemMgr->setWfSystemWindow(this);
     mdiArea = new QMdiArea;
     mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     setCentralWidget(mdiArea);

     setWindowTitle(tr("MDI"));
     setUnifiedTitleAndToolBarOnMac(true);
     initMainWindow();
     connect(ui->actionOnline,SIGNAL(triggered(bool)),this,SLOT(createOnlineWindow()));
     connect(ui->actionOrder,SIGNAL(triggered(bool)),this,SLOT(createKernelTest()));
}

HWfSystemWindow::~HWfSystemWindow()
{
    delete ui;
}

QDialog *HWfSystemWindow::activeMdiChild() const
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
          return qobject_cast<QDialog *>(activeSubWindow->widget());
      return 0;
}

QMdiSubWindow *HWfSystemWindow::findMdiChild(const QString &fileName) const
{
    return NULL;
}


void HWfSystemWindow::createOnlineWindow()
{

    //还需要设置一下sceneRect的大小

    //connect()
}

void HWfSystemWindow::createKernelTest()
{
    HKernelTest* kertest = new HKernelTest;
    kertest->show();
}

/* 1.刷新树形界面，保证树形打开的是根画面，
 * 2.树形根画面节点调用后，发射打开画面信号，调MainWindow打开窗口，显示画面
 * 3.显示画面窗口调用scene来完成
 */
void HWfSystemWindow::initMainWindow()
{
    //左边树结构
    m_pOnlineTreeWidget = new HOnlineTreeWidget(m_pWfSystemMgr);
    ui->dockWidget->setWidget(m_pOnlineTreeWidget);
    connect(m_pOnlineTreeWidget,SIGNAL(graphOpen(const QString&,const int)),this,SLOT(Open(const QString&,const int)));//打开
}

/*
 * 函数:Open()
 * 功能:打开某一幅画面
 * 备注:只针对画面浏览窗口
*/
void HWfSystemWindow::Open(const QString &graphName, const int graphID)
{
    if(!m_pWfSystemMgr)
        return;
    m_pWfSystemMgr->openOnlineGraph(graphName,graphID);
}
