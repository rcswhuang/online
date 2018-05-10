#include "hwfsystemdoc.h"
#include "publicdata.h"
#include "hwfsystemmgr.h"
#include "hgraph.h"
#include "hicontemplate.h"
#include "hstation.h"
#include "hgraphhelper.h"
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QProcessEnvironment>
//图形文件存储类
HWfSystemDoc::HWfSystemDoc(HWfSystemMgr* mgr)
    :m_pWfSystemMgr(mgr)
{
    pCurGraph = NULL;
}

HWfSystemDoc::~HWfSystemDoc()
{

}

//加载画面信息
void HWfSystemDoc::loadAllGraph()
{
    HGraphHelper::Instance()->loadAllGraph(&pGraphList);

    //设置当前画面为根画面
    pCurGraph = getRootGraph();
}

//查找根画面
HGraph* HWfSystemDoc::getRootGraph()
{
    HGraph* pRootGraph = NULL;
    for(int i = 0; i < pGraphList.count();i++)
    {
        HGraph* pGraph = (HGraph*)pGraphList[i];
        if(pGraph /*&& pGraph->bStart*/)
        {
            pRootGraph = pGraph;
            break;
        }
    }
    return pRootGraph;
}

//按照ID查找画面
HGraph* HWfSystemDoc::findGraph(int graphID)
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

HGraph* HWfSystemDoc::findGraph(const QString& graphName)
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
bool HWfSystemDoc::openGraph(const QString& name,const int id)
{
    HGraph* graph = findGraph(id);
    if(!graph)
        return false;
    pCurGraph = graph;
    return true;
}

HGraph* HWfSystemDoc::getCurGraph()
{
    return pCurGraph;
}
