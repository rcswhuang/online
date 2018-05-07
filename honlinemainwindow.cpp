#include "honlinemainwindow.h"
#include "ui_onlinemainwindow.h"
#include "honlinetreewidget.h"
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


void HOnlineMainWindow::initOnlineMainWindow()
{

    //左边树结构
    pOnlineTreeWidget = new HOnlineTreeWidget(NULL);
    ui->dockWidget->setWidget(pOnlineTreeWidget);
    //connect(pGraphTreeWidget,SIGNAL(graphNew(const QString&)),this,SLOT(New(const QString&)));//新建
    //connect(pGraphTreeWidget,SIGNAL(graphOpen(const QString&,const int)),this,SLOT(Open(const QString&,const int)));//打开
    //connect(pGraphTreeWidget,SIGNAL(graphDel(const QString&,const int )),this,SLOT(Del(const QString&,const int)));//删除
    //connect(pGraphTreeWidget,SIGNAL(graphImport(const QString&)),this,SLOT(ImportFile(const QString&)));
    //connect(pGraphTreeWidget,SIGNAL(graphImportPath(const QString&)),this,SLOT(ImportGraphFolder(const QString&)));
}
