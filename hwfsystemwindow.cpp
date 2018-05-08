#include "hwfsystemwindow.h"
#include "ui_wfsystemwindow.h"
#include "honlinetreewidget.h"
#include "honlineview.h"
#include "hwfsystemmgr.h"
#include "honlinewindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
HWfSystemWindow::HWfSystemWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::wfSystemWindow)
{
    ui->setupUi(this);
    m_pOnlineWindow = NULL;
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
     m_pOnlineWindow = NULL;
     mdiArea = new QMdiArea;
     mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     setCentralWidget(mdiArea);

     setWindowTitle(tr("MDI"));
     setUnifiedTitleAndToolBarOnMac(true);

     connect(ui->actionOnline,SIGNAL(triggered(bool)),this,SLOT(createOnlineWindow()));
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
    if(m_pOnlineWindow)
    {
        m_pOnlineWindow->showMaximized();
        return;
    }
    m_pOnlineWindow = new HOnlineWindow;
    mdiArea->addSubWindow(m_pOnlineWindow);
    m_pOnlineWindow->showMaximized();
    //还需要设置一下sceneRect的大小

    //connect()


}

/* 1.刷新树形界面，保证树形打开的是根画面，
 * 2.树形根画面节点调用后，发射打开画面信号，调MainWindow打开窗口，显示画面
 * 3.显示画面窗口调用scene来完成
 */
void HWfSystemWindow::initOnlineMainWindow()
{
    //左边树结构
    m_pOnlineTreeWidget = new HOnlineTreeWidget(NULL);
    ui->dockWidget->setWidget(m_pOnlineTreeWidget);
    connect(m_pOnlineTreeWidget,SIGNAL(graphOpen(const QString&,const int)),this,SLOT(Open(const QString&,const int)));//打开
}

/*
void HWfSystemWindow::Open(const QString &graphName, const int graphID)
{
    if(!m_pOnlineMgr)
        return;
    m_pOnlineMgr->clearOnlineSceneItem();
    m_pOnlineMgr->Open(graphName,graphID);
    m_pOnlineMgr->openOnlineScene();
    m_pOnlineMgr->refreshView();
}*/
