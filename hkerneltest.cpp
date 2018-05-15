#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif
#include "hkerneltest.h"
#include "ui_hkerneltest.h"
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QContextMenuEvent>
#include <QMenu>
#include <QInputDialog>
#include <QTimer>
#include <QDebug>
#include "hupdatethread.h"
#define YX_HEAD 6
#define YC_HEAD 4
typedef struct _dbAttr
{
    quint16 wStation;
    quint16 wPointID;
}DBATTR;

HKernelTest::HKernelTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HKernelTest)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinMaxButtonsHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    nType = 0;
    initKernelTest();
    initWindow();

    //QTimer* timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    //timer->start(3000);
    m_pThread = new HUpdateThread(this);
    connect(m_pThread, &HUpdateThread::update, this, &HKernelTest::update);
    //connect(m_pThread, &HUpdateThread::finished, workerThread, &QObject::deleteLater);
    m_pThread->start();

    setWindowTitle("实时库状态一览图");

}

HKernelTest::~HKernelTest()
{
    delete ui;
    if(m_pThread)
    {
        m_pThread->terminate();
    }

    while(!m_pDigitalList.isEmpty())
        delete m_pDigitalList.takeFirst();

    while(!m_pAnalogueList.isEmpty())
        delete m_pAnalogueList.takeFirst();
}

void HKernelTest::initWindow()
{
    QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0,"实时库");
    QTreeWidgetItem* yx = new QTreeWidgetItem;
    root->addChild(yx);
    yx->setText(0,"遥信");
    yx->setData(0,Qt::UserRole,0);
    QTreeWidgetItem* yc = new QTreeWidgetItem;
    root->addChild(yc);
    yc->setText(0,"遥测");
    yc->setData(0,Qt::UserRole,1);
    ui->treeWidget->expandItem(root);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->treeWidget,SIGNAL(itemSelectionChanged()),this,SLOT(typeChanged()));
    connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(setValue()));
    ui->treeWidget->setCurrentItem(yx);
}

void HKernelTest::typeChanged()
{
    QTreeWidgetItem* item = (QTreeWidgetItem*)ui->treeWidget->currentItem();
    if(item)
        nType = item->data(0,Qt::UserRole).toInt();
    else
        nType = 0;
    QStringList headList;
    ui->tableWidget->clear();
    if(nType == 0)
    {
        ui->tableWidget->setColumnCount(YX_HEAD);
        headList<<"遥信名称"<<"遥信点号"<<"遥信设备"<<"遥信值"<<"遥信双位置点"<<"电压等级";
        //这种方法表头算0行，而且自动列也是自动增加0列为计数列
        for(int i = 0; i < YX_HEAD;i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(headList[i]);
            ui->tableWidget->setHorizontalHeaderItem(i,item);
            if(i == 0)
                ui->tableWidget->setColumnWidth(i,240);
            else
                ui->tableWidget->setColumnWidth(i,150);
        }
        ui->tableWidget->setRowCount(m_pDigitalList.count());
        for(int i = 0; i < m_pDigitalList.count();i++)
        {
            DIGITAL* digital = (DIGITAL*)m_pDigitalList[i];
            if(digital)
            {
                for(int j = 0; j < YX_HEAD;j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    if(!item) continue;
                    item->setData(Qt::UserRole,digital->wDigitalID);
                    if(j == 0)
                        item->setText(QString(digital->szDigitalOriginalName));
                    else if(j == 1)
                        item->setText(QString("%1").arg(digital->wDigitalID));
                    else if(j == 2)
                        item->setText(digital->szEquipmentID);
                    else if(j == 3)
                        item->setText(QString("%1").arg(digital->btRunValue));
                    else if(j == 4)
                        item->setText(QString("%1").arg(digital->wDoubleDgtID));
                    else if(j == 5)
                        item->setText(QString("%1kV").arg(digital->nPowerGrade/1000));
                    ui->tableWidget->setItem(i,j,item);

                }
            }
        }
    }
    else if(nType == 1)
    {
        ui->tableWidget->setColumnCount(YC_HEAD);
        headList<<"遥测名称"<<"遥测点号"<<"遥测值"<<"电压等级";
        for(int i = 0; i < YC_HEAD;i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(headList[i]);
            ui->tableWidget->setHorizontalHeaderItem(i,item);
        }
        ui->tableWidget->setRowCount(m_pAnalogueList.count());
        for(int i = 0; i < m_pAnalogueList.count();i++)
        {
            ANALOGUE* analogue = (ANALOGUE*)m_pAnalogueList[i];
            if(analogue)
            {
                for(int j = 0; j < YC_HEAD;j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    if(!item) continue;
                    item->setData(Qt::UserRole,analogue->wAnalogueID);
                    if(j == 0)
                        item->setText(QString(analogue->szAnalogueOriginalName));
                    else if(j == 1)
                        item->setText(QString("%1").arg(analogue->wAnalogueID));
                    else if(j == 2)
                        item->setText(QString("%1").arg(analogue->fValue));
                    else if(j == 3)
                        item->setText(QString("%1kV").arg(analogue->nPowerGrade/1000));

                    ui->tableWidget->setItem(i,j,item);


                }
            }
        }
    }
}

//更新值
void HKernelTest::update()
{
    qDebug()<<"which thread update ：" << QThread::currentThreadId();
 /*   for(int i = 0; i < m_pDigitalList.count();i++)
    {
        DIGITAL* digital = (DIGITAL*)m_pDigitalList[i];
        if(digital)
        {
            DBHANDLE dbHandle;
            dbHandle = getDbHandle(digital->wStationID,TYPE_DIGITAL,digital->wDigitalID,TYPE_DB_REALTIME);
            if(!isValidDbHandle(dbHandle))
                continue;
            uchar nValue;
            getAttr(dbHandle,ATTR_DGT_4_STATE_VALUE,&nValue);
            digital->btRunValue = nValue;
        }
    }

    for(int i = 0; i < m_pAnalogueList.count();i++)
    {
        ANALOGUE* analogue = (ANALOGUE*)m_pAnalogueList[i];
        if(analogue )
        {
            DBHANDLE dbHandle;
            dbHandle = getDbHandle(analogue->wStationID,TYPE_ANALOGUE,analogue->wAnalogueID,TYPE_DB_REALTIME);
            if(!isValidDbHandle(dbHandle))
                continue;
            float fValue;
            getAttr(dbHandle,ATTR_ANA_VALUE,&fValue);
            analogue->fValue = fValue;
        }
    }*/

    if(nType == 0)
    {
        for(int i = 0; i < m_pDigitalList.count();i++)
        {
            DIGITAL* digital = (DIGITAL*)m_pDigitalList[i];
            if(digital)
            {
                QTableWidgetItem* item = ui->tableWidget->item(i,3);//只改值
                item->setText(QString("%1").arg(digital->btRunValue));

            }
        }
    }
    else if(nType == 1)
    {
        for(int i = 0; i < m_pAnalogueList.count();i++)
        {
            ANALOGUE* analogue = (ANALOGUE*)m_pAnalogueList[i];
            if(analogue)
            {
                QTableWidgetItem* item = ui->tableWidget->item(i,2);
                item->setText(QString("%1").arg(analogue->fValue));
            }
        }
    }
}

void HKernelTest::initKernelTest()
{
    //dbDataInit();
    quint16 wStationNum = getStationNum();
    for( quint16 i = 0; i < wStationNum; i++ )
    {
        DBHANDLE dbHandle = ::findDbHandle( 0, TYPE_NULL, i );
        if( !::isValidDbHandle(dbHandle) )
            continue;

        quint16 wStationNo;
        getAttr( dbHandle, ATTR_ST_NO, &wStationNo );
        quint16 wDgtNum = 0;
        getAttr( dbHandle, ATTR_ST_TOTALDGT, &wDgtNum );
        if( wDgtNum > 0)
        {
            DBHANDLE dbHandle1;
            for( quint16 j = 0; j < wDgtNum; j++ )
            {

                dbHandle1 = ::findDbHandle( wStationNo, TYPE_DIGITAL, j );
                if( !::isValidDbHandle(dbHandle1) )
                    continue;
                DIGITAL* pDigital = new DIGITAL;
                if(!pDigital) continue;
                pDigital->wStationID = wStationNo;
                ushort value;
                getAttr( dbHandle1, ATTR_DGT_NO, &value );
                pDigital->wDigitalID = value;
                int nvalue;
                getAttr( dbHandle1, ATTR_DGT_POWERGRADE, &nvalue );
                pDigital->nPowerGrade = nvalue;
                getAttr( dbHandle1, ATTR_DGT_DOUBLEDGTID, &value );
                pDigital->wDoubleDgtID = value;
                uchar btvalue;
                getAttr( dbHandle1, ATTR_DGT_4_STATE_VALUE, &btvalue );
                pDigital->btRunValue = btvalue;
                char    szDigitalOriginalName[DIGITALNAMELEN];
                getAttr( dbHandle1, ATTR_DGT_ORINAME, szDigitalOriginalName );
                qstrcpy(pDigital->szDigitalOriginalName,szDigitalOriginalName);
                char    szEquipmentID[EQUIPMENTLEN];
                getAttr( dbHandle1, ATTR_DGT_EQUIPMENTID, szEquipmentID );
                qstrcpy(pDigital->szEquipmentID,szEquipmentID);
                m_pDigitalList.append(pDigital);
            }
        }
        quint16 wAnaNum = 0;
        getAttr( dbHandle, ATTR_ST_TOTALANA, &wAnaNum );
        if(wAnaNum > 0 )
        {
            DBHANDLE dbHandle1;
            for( quint16 j = 0; j < wAnaNum; j++ )
            {
                dbHandle1 = ::findDbHandle( wStationNo, TYPE_ANALOGUE, j );
                if( !::isValidDbHandle(dbHandle1) )
                    continue;
                ANALOGUE* pAna = new ANALOGUE;
                if(!pAna) continue;
                pAna->wStationID = wStationNo;
                ushort value;
                getAttr( dbHandle1, ATTR_ANA_NO, &value );
                pAna->wAnalogueID = value;
                int nvalue;
                getAttr( dbHandle1, ATTR_ANA_POWERGRADE, &nvalue );
                pAna->nPowerGrade = nvalue;
                float fvalue;
                getAttr( dbHandle1, ATTR_ANA_VALUE, &fvalue );
                pAna->fValue = fvalue;
                char   szAnalogueOriginalName[ANALOGUENAMELEN];
                getAttr( dbHandle1, ATTR_ANA_ORINAME, szAnalogueOriginalName);
                qstrcpy(pAna->szAnalogueOriginalName,szAnalogueOriginalName);
                m_pAnalogueList.append(pAna);
            }
        }

    }
}

void HKernelTest::contextMenuEvent(QContextMenuEvent *event)
{
    return;
}

void HKernelTest::setValue()
{
    QTableWidgetItem* item = ui->tableWidget->currentItem();
    if(!item) return;
    if(nType == 0)
    {
        int row = item->column();
        if(item->column() != 3) return;
        int nValue = QInputDialog::getInt(this, tr("遥信"),tr("遥信值:"),0,0,3);
        //item->setText(QString("%1").arg(nValue));
        quint16 wDigitalID = item->data(Qt::UserRole).toUInt();
        for(int i = 0; i < m_pDigitalList.count();i++)
        {
            DIGITAL* digital = (DIGITAL*)m_pDigitalList[i];
            if(digital && digital->wDigitalID == wDigitalID)
            {
                DBHANDLE dbHandle;
                dbHandle = getDbHandle(digital->wStationID,TYPE_DIGITAL,wDigitalID,TYPE_DB_REALTIME);
                if(!isValidDbHandle(dbHandle))
                    continue;
                setAttr(dbHandle,ATTR_DGT_4_STATE_VALUE,&nValue);
            }
        }
    }
    else if(nType == 1)
    {
        int row = item->column();
        if(item->column() != 2) return;
        float fValue = QInputDialog::getDouble(this, tr("遥测"),tr("遥测量:"),0);
        //item->setText(QString("%1").arg(nValue));
        quint16 wAnalogueID = item->data(Qt::UserRole).toUInt();
        for(int i = 0; i < m_pAnalogueList.count();i++)
        {
            ANALOGUE* analougue = (ANALOGUE*)m_pAnalogueList[i];
            if(analougue && analougue->wAnalogueID == wAnalogueID)
            {
                DBHANDLE dbHandle;
                dbHandle = getDbHandle(analougue->wStationID,TYPE_ANALOGUE,wAnalogueID,TYPE_DB_REALTIME);
                if(!isValidDbHandle(dbHandle))
                    continue;
                setAttr(dbHandle,ATTR_ANA_VALUE,&fValue);
            }
        }
    }
}
