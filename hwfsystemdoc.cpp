#include "hwfsystemdoc.h"
#include "publicdata.h"
#include "hwfsystemmgr.h"
#include "hgraph.h"
#include "hicontemplate.h"
#include "hstation.h"
#include "hgraphhelper.h"
//#include "hbaseobj.h"
//#include "hiconobj.h"
//#include "hiconsymbol.h"
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

void HWfSystemDoc::loadIconTemplate()
{
    HGraphHelper::Instance()->loadIconTemplate(&m_pIconTemplateList);
}

//加载画面信息
void HWfSystemDoc::loadAllGraph()
{
    HGraphHelper::Instance()->loadAllGraph(&pGraphList);

    //设置当前画面为根画面
    pCurGraph = getRootGraph();

    //刷新模板
    updateGraphList();
}

//更新所有画面里面的模板信息
void HWfSystemDoc::updateGraphList()
{
    for(int i = 0; i < pGraphList.count();i++)
    {
        HGraph* pGraph = (HGraph*)pGraphList[i];
        if(!pGraph) continue;
        HIconTemplate* findTemp = NULL;
        for(int j = 0; j < pGraph->pIconTemplateList.count();j++)
        {
            HIconTemplate* pGraphTemp = (HIconTemplate*)pGraph->pIconTemplateList[j];
            if(!pGraphTemp)
                continue;
            findTemp = findIconTemplate(pGraphTemp->getUuid().toString());
            if(findTemp)
            {
                findTemp->copyTo(pGraphTemp);
            }
            for(int k = 0; k < pGraph->getObjList().count();k++)
            {
                HBaseObj* pObj = (HBaseObj*)pGraph->getObjList().at(k);
                if(pObj->getShapeType() == enumComplex)
                {
                    HIconObj* pObj1 = (HIconObj*)pObj;//
                    if(!pObj1->iconTemplate()->getUuid().toString().compare(findTemp->getUuid().toString()))
                    {
                        findTemp->getSymbol()->copyTo(pObj1->getIconSymbol());
                        pObj1->updateResize();
                        int a = 0;
                    }
                }
            }
        }
    }
}

//寻找模板
HIconTemplate* HWfSystemDoc::findIconTemplate(const QString &uuid)
{
    for(int i = 0; i < m_pIconTemplateList.count();i++)
    {
        HIconTemplate* iconTemplate = (HIconTemplate*)m_pIconTemplateList[i];
        if(iconTemplate->getUuid().toString() == uuid)
            return iconTemplate;
    }
    return NULL;
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
