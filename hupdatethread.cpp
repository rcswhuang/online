#include "hupdatethread.h"
#include <QDebug>
#include <QTimer>
HTWork::HTWork(HKernelTest* pParent)
:p_kernelTest(pParent)
{

}

void HTWork::on_time()
{
    qDebug()<<"HWork::on_time" << QThread::currentThreadId();
    for(int i = 0; i < p_kernelTest->m_pDigitalList.count();i++)
    {
        DIGITAL* digital = (DIGITAL*)p_kernelTest->m_pDigitalList[i];
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

    for(int i = 0; i < p_kernelTest->m_pAnalogueList.count();i++)
    {
        ANALOGUE* analogue = (ANALOGUE*)p_kernelTest->m_pAnalogueList[i];
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
    }

    emit p_Thread->update();
}



HUpdateThread::HUpdateThread(HKernelTest* parent)
    :p_kernelTest(parent)
{

}


void HUpdateThread::run()
{
    //测试，检查独立进程是否启动工作
    qDebug()<<"HUpdateThread id" << QThread::currentThreadId();
    QTimer timer;
    HTWork work(p_kernelTest);
    work.p_Thread = this;
    connect(&timer,SIGNAL(timeout()),&work,SLOT(on_time()));
    timer.start(1000);
    exec();
}
