#include "honlinedoc.h"
#include "publicdata.h"
#include "honlinemgr.h"
#include "hgraph.h"
#include "hicontemplate.h"
#include "hstation.h"
#include "hgraphhelper.h"
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QProcessEnvironment>
//图形文件存储类
HOnlineDoc::HOnlineDoc(HOnlineMgr* mgr)
    :pOnlineMgr(mgr)
{
    pCurGraph = NULL;
}

HOnlineDoc::~HOnlineDoc()
{

}

//加载厂站信息
void HOnlineDoc::loadStation()
{
    //读取厂站信息
    /*
    FILEHANDLE fileHandle;
    memset(&fileHandle,0,sizeof(FILEHANDLE));
    DATAFILEHEADER dataFileHandle;

    openDB(FILE_TYPE_STATION);
    loadDataFileHeader(FILE_TYPE_STATION,&dataFileHandle);
    //int wStation = 0;
    for(int i = 0 ; i < dataFileHandle.wTotal; i++)
    {
        HStation* pStation = new HStation;
        if(!pStation)
            break;

        if ( false == loadDBRecord(FILE_TYPE_STATION, ++fileHandle.wStation, &pStation->station ) )
        {
            delete pStation;
            pStation=NULL;
            break;
        }
        if(false == pStation->loadData(fileHandle))
        {
            delete pStation;
            pStation = NULL;
            break;
        }
        pStationList.append(pStation);
    }
    closeDB(FILE_TYPE_STATION);
    */
}


//厂站ID获取厂站
HStation* HOnlineDoc::getStation(quint16 wStationID)
{
    for(int i = 0; i < pStationList.count();i++)
    {
        HStation* pStation = pStationList[i];
        if(wStationID == pStation->getNo())
            return pStation;
    }
    return NULL;
}

//厂站地址获取厂站
HStation* HOnlineDoc::getRtu(quint16 wStationAddress)
{
    for(int i = 0; i < pStationList.count();i++)
    {
        HStation* pStation = pStationList[i];
        if(wStationAddress == pStation->getAddress())
            return pStation;
    }
    return NULL;
}

//索引厂站
HStation* HOnlineDoc::findStation(int nIndex)
{
    return pStationList.value(nIndex);
}


//加载画面信息
void HOnlineDoc::loadAllGraph()
{
    HGraphHelper::Instance()->loadAllGraph(&pGraphList);

    //设置当前画面为根画面
    pCurGraph = findRootGraph();
}

void HOnlineDoc::saveAllGraph()
{
    HGraphHelper::Instance()->saveAllGraph(&pGraphList,getCurGraph());
}

//查找根画面
HGraph* HOnlineDoc::findRootGraph()
{
    HGraph* pRootGraph = NULL;
    for(int i = 0; i < pGraphList.count();i++)
    {
        HGraph* pGraph = (HGraph*)pGraphList[i];
        if(pGraph && pGraph->bStart)
        {
            pRootGraph = pGraph;
            break;
        }
    }
    return pRootGraph;
}

//按照ID查找画面
HGraph* HOnlineDoc::findGraph(int graphID)
{
    HGraph *graph = NULL;
    QList<HGraph*>::Iterator graphIterator;
    for(graphIterator = pGraphList.begin();graphIterator != pGraphList.end();graphIterator++)
    {
        graph = *graphIterator;
        if(graph->getGraphID() == graphID)
            return graph;
    }
    return NULL;
}

HGraph* HOnlineDoc::findGraph(const QString& graphName)
{
    HGraph *graph = NULL;
    QList<HGraph*>::Iterator graphIterator;
    for(graphIterator = pGraphList.begin();graphIterator != pGraphList.end();graphIterator++)
    {
        graph = *graphIterator;
        if(graph->getGraphName() == graphName)
            return graph;
    }
    return NULL;
}

//打开画面
bool HOnlineDoc::openGraph(const QString& name,const int id)
{
    HGraph* graph = findGraph(id);
    if(!graph)
        return false;
    pCurGraph = graph;
    return true;
}

HGraph* HOnlineDoc::getCurGraph()
{
    return pCurGraph;
}
