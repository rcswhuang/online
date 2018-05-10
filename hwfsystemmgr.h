#ifndef HWFSYSTEMMGR_H
#define HWFSYSTEMMGR_H

#include <QObject>
#include <QRectF>
#include "hiconapi.h"
class QMdiArea;


class HIconGraphicsItem;
class HBaseObj;
class HGraph;
class HWfSystemDoc;

class HWfSystemWindow;
class HOnlineWindow;
class HOperOrderWindow;

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

    //启动各种dll库
    void loadInstance();

    //退出dll库
    void exitInstance();

    //启动时加载画面信息
    void loadGraphs();

    //判断graph文件名是否存在
    bool findGraphByName(const QString&);

//创建窗口类
public:
    //创建在线浏览窗口
    void createOnlineWindow(QMdiArea* area);

public:
    void openOnlineGraph(const QString &graphName, const int graphID);


protected:

private:
    QString strGraphFile;
    HWfSystemDoc* m_wfSystemDoc;
    HOnlineWindow* m_pOnlineWindow;
    HWfSystemWindow* m_pWfSystemWindow;


};

#endif // HWFSYSTEMMGR_H
