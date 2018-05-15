#include "honlinerefreshthread.h"
#include "honlinewindow.h"
#include "publicdata.h"
#include "hgraph.h"
#include "hiconobj.h"
#include "hiconsymbol.h"
#include "honlinerefreshthread.h"
#include "hkernelapi.h"
#include "honlinescene.h"
#include <QDebug>
#include <QTimer>

HWork::HWork(HOnlineWindow* pParent)
:m_pOnlineWindow(pParent)
{

}

void HWork::on_time()
{
    qDebug()<<"HWork::on_time" << QThread::currentThreadId();
    for(int i = 0; i < m_pOnlineWindow->m_pIconObjList.count();i++)
    {
        HIconObj* pObj = (HIconObj*)m_pOnlineWindow->m_pIconObjList[i];
        if(pObj)
        {
            //updateIconObj(iconObj);
            int nCurPattern = pObj->getIconSymbol()->getCurrentPattern();
            quint8 btCateType = pObj->getObjType();
            quint8 btType = (quint8)pObj->getDynamicObj()->getValueType();
            quint16 wStation = pObj->getDynamicObj()->getDBStation();
            quint16 wPoint = pObj->getDynamicObj()->getDBPoint();
            ushort wAttr = pObj->getDynamicObj()->getDBAttr();
            //遥信
            if(TEMPLATE_TYPE_DIGITAL == btCateType)
            {
                DBHANDLE dbHandle = getDbHandle(wStation,btType,wPoint,TYPE_DB_REALTIME);
                if(!isValidDbHandle(dbHandle))
                    return;
/*
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
                    */
                quint8 m_btValue = 0;
                if(wAttr == ATTR_DGT_VALUE)
                {
                    if(!getAttr(dbHandle,ATTR_DGT_VALUE,&m_btValue))
                        return;
                }
                else if(ATTR_DGT_4_STATE_VALUE == wAttr)
                {
                    if(!getAttr(dbHandle,ATTR_DGT_4_STATE_VALUE,&m_btValue))
                        return;
                }

                if(m_btValue > 3) m_btValue = 3;

                /*
                if(ENABLE_REPAIR == m_nPFlags)
                {
                    pObj->setLineColorName(QColor(Qt::red).name());
                    pObj->setFillColorName(QColor(Qt::red).name());
                }
                */
                //读取配置文件获取不同颜色的配置

                //关键地方，画面变位的地方
                if(nCurPattern != m_btValue)
                {
                    pObj->getIconSymbol()->setCurrentPattern(m_btValue);
                    //是不是需要刷新pObj这块区域
                    if(m_pOnlineWindow && m_pOnlineWindow->onlineScene())
                        m_pOnlineWindow->onlineScene()->invalidate(pObj->boundingRect(),QGraphicsScene::ItemLayer);
                }
            }
        }
    }
    //emit p_Thread->update();
}


HOnlineRefreshThread::HOnlineRefreshThread(HOnlineWindow* ow)
    :m_pOnlineWindow(ow)
{

}

void HOnlineRefreshThread::run()
{
    //测试，检查独立进程是否启动工作
    qDebug()<<"HOnlineRefreshThread id" << QThread::currentThreadId();
    HWork work(m_pOnlineWindow);
    work.p_Thread = this;
    QTimer timer;
    connect(&timer,SIGNAL(timeout()),&work,SLOT(on_time()));
    timer.start(5000);
    exec();
}
