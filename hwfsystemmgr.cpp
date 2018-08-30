#include "hwfsystemmgr.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QMdiArea>
#include "honlineapi.h"
#include "hkernelapi.h"
#include "hwfsystemdoc.h"
#include "hgraphicsscene.h"
#include "hgraph.h"
#include "hwfsystemwindow.h"
#include "hgraphframe.h"
#include "hopterm.h"
//图形文件管理总类
HWfSystemMgr::HWfSystemMgr()
{
    m_wfSystemDoc = new HWfSystemDoc(this);
    Q_ASSERT(m_wfSystemDoc);

    /*
    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    logicRectF.setX(0-(width-2)/2);
    logicRectF.setY(0-(height-100)/2);
    logicRectF.setWidth(width-2);
    logicRectF.setHeight(height-100/2);
    */
    m_pOnlineWindow = NULL;

}

//启动时加载数据库
void HWfSystemMgr::loadInstance()
{


}

void HWfSystemMgr::exitInstance()
{

}

void HWfSystemMgr::loadIconTemplates()
{
    if(!m_wfSystemDoc)
        return;
    m_wfSystemDoc->loadIconTemplate();
}

//启动时加载画面信息
void HWfSystemMgr::loadGraphs()
{
    if(!m_wfSystemDoc)
        return;
    m_wfSystemDoc->loadAllGraph();
}

bool HWfSystemMgr::loadDB()
{

}

bool HWfSystemMgr::loadData()
{
    if(!dbDataInit())
        return false;
}

bool HWfSystemMgr::loadPointTerm()
{
    DATAFILEHEADER dataFileHandle;
    memset(&dataFileHander,0,sizeof(DATAFILEHEADER));
    //测点类型
    int fd = openDB(FILE_TYPE_POINTTERM);
    if(fd != (int)-1)
    {
        loadDataFileHeader(fd,&dataFileHandle);
        for(int i = 0; i < dataFileHandle.wTotal;i++)
        {
            HPointTerm* pPointTerm = new HPointTerm;
            if(false == loadDBRecord(fd,++i,pPointTerm->pointTerm))
            {
                delete pPointTerm;
                return false;
            }
            m_pPointTermList.append(pPointTerm);
        }
        closeDB(FILE_TYPE_POINTTERM);
    }
    return true;
}

HPointTerm* HWfSystemMgr::findPointTerm(QString name)
{
    QList<HPointTerm*>::iterator it = m_pPointTermList.begin();
    for(;it != m_pPointTermList.end();it++)
    {
        HPointTerm* pPt = *it;
        if(pPt->getPointTermName() == name)
            return pPt;
    }
    return NULL;
}

HPointTerm* HWfSystemMgr::findPointTerm(ushort id)
{
    QList<HPointTerm*>::iterator it = m_pPointTermList.begin();
    for(;it != m_pPointTermList.end();it++)
    {
        HPointTerm* pPt = *it;
        if(pPt->getPointTermID() == id)
            return pPt;
    }
    return NULL;
}

bool HWfSystemMgr::loadOpTerm()
{
    //有子文件必须要datafileheader结构 如厂站，操作术语
    //如果没有子文件 则不需要。
    DATAFILEHEADER fileHandle;
    memset(&fileHandle,0,sizeof(DATAFILEHEADER));
    int fd = createDB(FILE_TYPE_OPTERMGROUP);
    if(fd != (int)-1)
    {
        for(int i = 0; i < m_pOpTermGroupList.count();i++)
        {
            HOpTermGroup* pOpTermGroup = (HOpTermGroup*)m_pOpTermGroupList[i];
            if(pOpTermGroup)
            {
                if(false == loadDBRecord(fd,++fileHandle,&pOpTermGroup->opTermGroup))
                {
                    delete pOpTermGroup;
                    pOpTermGroup = NULL;
                    break;
                }
                if(false == pOpTermGroup->loadData(fileHandle))
                {
                    delete pOpTermGroup;
                    pOpTermGroup = NULL;
                    break;
                }
            }
        }
        //操作术语组
        loadDataFileHeader(fd,&dataFileHandle);
        dataFileHandle.wTotal = fileHandle.wOpTermGroup;
        saveDataFileHeader(fd,&dataFileHandle);
        closeDB(FILE_TYPE_OPTERMGROUP);
    }
    return;
}

bool HWfSystemMgr::loadPlugin()
{

}

HWfSystemDoc* HWfSystemMgr::wfSystemDoc()
{
    return m_wfSystemDoc;
}

//判断graph文件名是否存在
bool HWfSystemMgr::findGraphByName(const QString& graphName)
{
    if(!m_wfSystemDoc)
        return false;
    HGraph* graph = m_wfSystemDoc->findGraph(graphName);
    if(!graph)
        return false;
    return true;
}


void HWfSystemMgr::setWfSystemWindow(HWfSystemWindow* pWindow)
{
    m_pWfSystemWindow = pWindow;
}

//创建画面浏览窗口
void HWfSystemMgr::createOnlineWindow(QMdiArea* mdiArea)
{
    if(m_pOnlineWindow)
    {
        m_pOnlineWindow->showMaximized();
        return;
    }
    m_pOnlineWindow = new HGraphFrame(this);
    mdiArea->addSubWindow(m_pOnlineWindow);
    m_pOnlineWindow->showMaximized();
}

//
void HWfSystemMgr::openOnlineGraph(const QString &graphName, const int graphID)
{
    if(!m_pOnlineWindow)
        createOnlineWindow(m_pWfSystemWindow->getMdiArea());
    m_pOnlineWindow->openGraph(graphName,graphID);
}

bool HWfSystemMgr::Open(const QString& graphName,int id)
{
    if(!m_wfSystemDoc)
        return false;
    return m_wfSystemDoc->openGraph(graphName,id);
}

HOpSheetInfo* HWfSystemMgr::findOpSheetInfo(ushort wOpSheetID)
{
    HOpSheetInfo* pOpSheetInfo = NULL;
    QList<HOpSheetInfo*>::iterator it = m_pOpSheetInfoList.begin();
    for(;it != m_pOpSheetInfoList.end();++it)
    {
        pOpSheetInfo = *it;
        ushort wID;
        pOpSheetInfo->getAttr(OPSHEET_ATTR_ID,&wID);
        if(wID == wOpSheetID)
            return pOpSheetInfo;
    }
    return NULL;
}

HOpSheetInfo* HWfSystemMgr::findOpSheetInfo(QString name)
{
    return NULL;
}

bool HWfSystemMgr::loadOpSheetInfo()
{
    DATAFILEHEADER dataFileHandle;
    openDB(FILE_TYPE_OPSHEETINFO);
    loadDataFileHeader(FILE_TYPE_OPSHEETINFO,&dataFileHandle);
    HOpSheetInfo* pOpSheetInfo;
    for(int i = 0; i < dataFileHandle.wTotal;i++)
    {
        pOpSheetInfo = new HOpSheetInfo;
        if(false == loadDBRecord(FILE_TYPE_OPSHEETINFO,++i,&pOpSheetInfo->m_opSheetInfo))
        {
            delete pOpSheetInfo;
            continue;
        }
        ushort wID;
        pOpSheetInfo->getAttr(OPSHEET_ATTR_ID,&wID);
        if(!pOpSheetInfo->checkExist() || findOpSheetInfo(wID))
        {
            delete pOpSheetInfo;
            pOpSheetInfo = NULL;
            continue;
        }
        m_pOpSheetInfoList.append(pOpSheetInfo);

    }
    closeDB(FILE_TYPE_OPSHEETINFO);
    return true;
}

bool HWfSystemMgr::saveOpSheetInfo()
{
    createDB(FILE_TYPE_OPSHEETINFO);
    DATAFILEHEADER dataFileHandle;
    loadDataFileHeader(FILE_TYPE_OPSHEETINFO,&dataFileHandle);
    dataFileHandle.wTotal = m_pOpSheetInfoList.count();
    saveDataFileHeader(FILE_TYPE_OPSHEETINFO,&dataFileHandle);
    HOpSheetInfo* pOpSheetInfo;
    for(int i = 0; i < m_pOpSheetInfoList.count();i++)
    {
        pOpSheetInfo = m_pOpSheetInfoList[i];
        if(false == saveDBRecord(FILE_TYPE_OPSHEETINFO,++i,&pOpSheetInfo->m_opSheetInfo))
        {
            return false;
        }
    }
    closeDB(FILE_TYPE_OPSHEETINFO);
    return true;
}
