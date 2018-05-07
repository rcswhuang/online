#ifndef HONLINESCENE_H
#define HONLINESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
class HIconLineItem;
class HIconRectItem;
class HIconEllipseItem;
class HIconCircleItem;
class HIconPolygonItem;
class HIconPolylineItem;
class HIconArcItem;
class HIconPieItem;
class HIconTextItem;
class HIconComplexItem;
class HIconSelectionItem;
class HIconGraphicsItem;
class HIconItemGroup;
class HBaseObj;
class HOnlineMgr;
class HOnlineScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HOnlineScene(HOnlineMgr *mgr);

public:
    void openOnlineSceneItems();
    void delOnlineSceneItems();
    void addOnlineIconItem(HBaseObj* pObj,bool del = false);//obj->item
    void newOnlineIconObj();//新建obj
    void setItemCursor(QGraphicsSceneMouseEvent *mouseEvent);
    void setItemProperty(QGraphicsItem* item);
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
signals:
    void itemInserted(int);
    void mousePosChanged(QPointF logPos);

public:
    HOnlineMgr* pOnlineMgr;
    HIconLineItem* line;
    HIconRectItem* rectangle;
    HIconEllipseItem* ellipse;
    HIconCircleItem* circle;
    HIconPolygonItem* polygon;
    HIconPolylineItem* polyline;
    HIconArcItem* arc;
    HIconPieItem* pie;
    HIconTextItem* text;
    HIconSelectionItem* select;
    HIconItemGroup* group;
    HIconComplexItem* complex;

public:
    QList<HIconGraphicsItem*> dragMoveItems;
};

#endif // HGRAPHEDITORSCENE_H
