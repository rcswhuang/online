#ifndef HWFSYSTEMMGR_H
#define HWFSYSTEMMGR_H

#include <QObject>
#include <QRectF>
#include "hiconapi.h"

class HIconGraphicsItem;
class HBaseObj;
class HGraph;

class HOnlineWindow;
class HOperOrderWindow;
class HWfSystemDoc;
//class HTemplateWindow;

/*
 * 图形绘图工具 管理总类，对各种管理类之间的转换调用进行控制。
 * 包含了各种管理类，绘制类，图形类的对象。
 * 彼此之间的调用都在这里进行转换。
 *
*/
class HWfSystemMgr : public QObject
{
    Q_OBJECT
public:
    HWfSystemMgr();

public:
    HWfSystemDoc* wfSystemDoc();
    HOnlineWindow* onlineWindow();
public:

    //启动时加载数据库
    void loadStation();

    //启动时加载画面信息
    void loadGraphs();

    //判断graph文件名是否存在
    bool findGraphByName(const QString&);

    //打开画面
    bool Open(const QString&,int);

    //设置逻辑界面大小
    void setLogicRect(const QRectF& rect);

    QRectF getLogicRect();



public:
    //刷新online view
    void refreshOnlineView();

    //加载online图元
    void openOnlineScene();

    //清除online上的item
    void clearOnlineSceneItem();


protected:

private:
    QRectF logicRectF;  //scene的大小
    QString strGraphFile;
    HWfSystemDoc* m_wfSystemDoc;
    HOnlineWindow* m_pOnlineWindow;


};

#endif // HWFSYSTEMMGR_H
