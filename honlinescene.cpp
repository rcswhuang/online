#include "honlinescene.h"
#include "hwfsystemmgr.h"
#include "hwfsystemdoc.h"
#include "hicongraphicsitem.h"
#include "hiconlineitem.h"
#include "hiconrectitem.h"
#include "hiconellipseitem.h"
#include "hiconcircleitem.h"
#include "hiconpolygonitem.h"
#include "hiconpolylineitem.h"
#include "hiconarcitem.h"
#include "hiconpieitem.h"
#include "hicontextitem.h"
#include "hiconitemgroup.h"
#include "hiconshowpattern.h"
#include "hiconselectionitem.h"
#include "hiconcomplexitem.h"
#include "hiconapi.h"
#include "hiconsymbol.h"
#include "hgraph.h"
#include <QMimeData>
HOnlineScene::HOnlineScene(HWfSystemMgr *mgr)
    :m_pWfSystemMgr(mgr)
{
    //setAcceptDraps(true);
    complex = 0;
    rectangle = 0;
    line = 0;
    ellipse = 0;
    circle = 0;
    polygon = 0;
    polyline = 0;
    arc = 0;
    pie = 0;
    text = 0;
    select = 0;
    group = 0;
    if(m_pWfSystemMgr)
        setSceneRect(m_pWfSystemMgr->getLogicRect());
    setSceneRect(QRectF(0,0,600,800));
}

void HOnlineScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    //if(NULL == m_pWfSystemMgr)
   //     return;
    painter->save();
    painter->setBrush(backgroundBrush());
    QGraphicsScene::drawBackground(painter,rect);

    HGraph* pGraph = NULL;
    if(m_pWfSystemMgr && m_pWfSystemMgr->wfSystemDoc())
        pGraph = m_pWfSystemMgr->wfSystemDoc()->getCurGraph();
    QColor clr;
    if(pGraph)
    {
        clr = QColor(pGraph->getFillColor());
    }
    else
    {
        clr = QColor(Qt::darkGray);
    }
    QRectF rectF = QRectF(0,0,600,800);//m_pWfSystemMgr->getLogicRect();
    painter->fillRect(rectF,clr);
    painter->restore();
}


void HOnlineScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
   // if(!pOnlineMgr->onlineDoc() || !pOnlineMgr->onlineDoc()->getCurGraph())
   //     return;
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void HOnlineScene::setItemProperty(QGraphicsItem* item)
{
    if(!item) return;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    HBaseObj* pObj = pItem->getItemObj();
    DRAWSHAPE drawShape = pObj->getShapeType();
    if(drawShape == enumComplex)
    {

    }
    else
    {

    }
}


void HOnlineScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

void HOnlineScene::newOnlineIconObj()
{
    if(!m_pWfSystemMgr)
        return;
}

/*
 * 函数说明:加载图元到OnlineScene上面
 * 参数:pObj--图元 bdel：是否删除
*/
void HOnlineScene::addOnlineIconItem(HBaseObj* pObj,bool bdel)
{
    DRAWSHAPE drawShape = pObj->getShapeType();
    int nZValue = pObj->getStackOrder();
    if(drawShape == enumLine)
    {
        line = new HIconLineItem(QLineF(((HLine*) pObj)->getHeadPoint(),((HLine*)pObj)->getTailPoint()));
        line->setItemObj(pObj);
        line->setZValue(nZValue);
        addItem(line);

    }
    else if(drawShape == enumRectangle)
    {
        HRectangle* pObj1 = (HRectangle*)pObj;
        rectangle = new HIconRectItem(pObj1->getObjRect());
        rectangle->setItemObj(pObj);
        rectangle->setZValue(nZValue);
        addItem(rectangle);
    }
    else if(drawShape == enumEllipse)
    {
        HEllipse* pObj1 = (HEllipse*)pObj;
        ellipse = new HIconEllipseItem(pObj1->getObjRect());
        ellipse->setItemObj(pObj);
        ellipse->setZValue(nZValue);
        addItem(ellipse);
    }
    else if(drawShape == enumCircle)
    {
        HCircle* pObj1 = (HCircle*)pObj;
        circle = new HIconCircleItem(pObj1->getObjRect());
        circle->setItemObj(pObj);
        circle->setZValue(nZValue);
        addItem(circle);
    }
    else if(drawShape == enumPolygon)
    {
        HPolygon* pObj1 = (HPolygon*)pObj;
        polygon = new HIconPolygonItem(pObj1->pylist);
        polygon->setItemObj(pObj);
        polygon->setZValue(nZValue);
        addItem(polygon);
    }
    else if(drawShape == enumPolyline)
    {
        HPolyline* pObj1 = (HPolyline*)pObj;
        polyline = new HIconPolylineItem(pObj1->pylist);
        polyline->setItemObj(pObj);
        polyline->setZValue(nZValue);
        addItem(polyline);
    }
    else if(drawShape == enumArc)
    {
        HArc* pObj1 = (HArc*)pObj;
        arc = new HIconArcItem(pObj1->getObjRect());
        arc->setItemObj(pObj);
        arc->setZValue(nZValue);
        addItem(arc);
    }
    else if(drawShape == enumPie)
    {
        HPie* pObj1 = (HPie*)pObj;
        pie = new HIconPieItem(pObj1->getObjRect());
        pie->setItemObj(pObj);
        pie->setZValue(nZValue);
        addItem(pie);
    }
    else if(drawShape == enumText)
    {
        HText* pObj1 = (HText*)pObj;
        text = new HIconTextItem(pObj1->getObjRect());
        text->setItemObj(pObj);
        text->setZValue(nZValue);
        addItem(text);
    }
    else if(drawShape == enumComplex)
    {
        HIconObj* pObj1 = (HIconObj*)pObj;
        complex = new HIconComplexItem(pObj1->getObjRect().normalized());
        complex->setItemObj(pObj);
        complex->setZValue(nZValue);
        addItem(complex);
    }
    //if(complex != 0)
     //   complex->setAcceptDrops(true);
    if(bdel)
    {
        if(drawShape == enumLine && line != 0)
        {
            line = 0;
        }
        else if(drawShape == enumRectangle && rectangle != 0)
        {
            rectangle = 0;
        }
        else if(drawShape == enumEllipse && ellipse != 0)
        {
            ellipse = 0;
        }
        else if(drawShape == enumCircle && circle != 0)
        {
            circle = 0;
        }
        else if(drawShape == enumPolyline && polyline != 0)
        {
            polyline = 0;
        }
        else if(drawShape == enumPolygon && polygon !=0)
        {
            polygon = 0;
        }
        else if(drawShape == enumArc && arc !=0)
        {
            arc = 0;
        }
        else if(drawShape == enumPie && pie !=0)
        {
            pie = 0;
        }
        else if(drawShape == enumText && text != 0)
        {
            text = 0;
        }
        else if(drawShape == enumComplex && complex != 0)
        {
            complex = 0;
        }
    }
}

void HOnlineScene::openOnlineSceneItems()
{
    if(!m_pWfSystemMgr)
        return;
    /*if(!pOnlineMgr->onlineDoc())
        return;
    HGraph* pGraph = pOnlineMgr->onlineDoc()->getCurGraph();
    if(!pGraph)
        return;
    QList<HBaseObj*> pObjList = pGraph->getObjList();
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)pObjList[i];
        if(!pObj)
            continue;
        addOnlineIconItem(pObj,true);
    }*/
}

/*
 * 函数说明:在显示即将打开的画面之前，删除当前画面图元
*/
void HOnlineScene::delOnlineSceneItems()
{

}

void HOnlineScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
}
