#ifndef HONLINEMGR_H
#define HONLINEMGR_H

#include <QObject>
#include <QRectF>
#include "hiconapi.h"
class HOnlineScene;
class HOnlineView;
class HOnlineDoc;
class HIconGraphicsItem;
class HBaseObj;
class HGraph;

/*
 * 图形绘图工具 管理总类，对各种管理类之间的转换调用进行控制。
 * 包含了各种管理类，绘制类，图形类的对象。
 * 彼此之间的调用都在这里进行转换。
 *
*/
class HOnlineMgr : public QObject
{
    Q_OBJECT
public:
    HOnlineMgr();


    //
    HOnlineScene* onlineScene();
    virtual void setOnlineView(HOnlineView* view);
    HOnlineView* onlineView();
    HOnlineDoc* onlineDoc();

public:

    //启动时加载数据库
    void loadStation();

    //启动时加载画面信息
    void loadGraphs();

    //判断graph文件名是否存在
    bool findGraphByName(const QString&);

    //打开画面
    bool Open(const QString&,int);

    //
    void setDrawShape(DRAWSHAPE ds);

    //
    DRAWSHAPE getDrawShape();

    //设置逻辑界面大小
    void setLogicRect(const QRectF& rect);

    QRectF getLogicRect();

    //刷新view
    void refreshView();

    //清空scene上面所有的Item
    void openGraphScene();

    //清除online上的item
    void delGraphSceneItem();


protected:
    HOnlineDoc* pOnlineDoc;

    HOnlineScene* pOnlineScene;

    HOnlineView* pOnlineView;

private:
    DRAWSHAPE drawShape;
    QRectF logicRectF;  //scene的大小
    HGraph* pTempGraph; //临时画面文件
    QString strGraphFile;

};

#endif // HGRAPHEDITORMGR_H
