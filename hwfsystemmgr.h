#ifndef HWFSYSTEMMGR_H
#define HWFSYSTEMMGR_H

#include <QObject>
#include <QRectF>
#include "hiconapi.h"
#include "hopsheet.h"

class QMdiArea;


class HIconGraphicsItem;
class HBaseObj;
class HGraph;
class HWfSystemDoc;

class HWfSystemWindow;
class HGraphFrame;
class HOperOrderWindow;
class HPointTerm;
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
    HGraphFrame* onlineWindow();
public:

    //启动各种dll库
    void loadInstance();

    //退出dll库
    void exitInstance();

    bool loadDB();
    bool loadData();
    bool loadPointTerm();//测点
    bool loadOpTerm();//操作术语
    bool loadPlugin();//主要是动态加载

    //启动时加载模板列表
    void loadIconTemplates();

    //启动时加载画面信息
    void loadGraphs();

    //判断graph文件名是否存在
    bool findGraphByName(const QString&);

    //打开画面
    bool Open(const QString& graphName,int id);
//创建窗口类
public:
    //设置MainWindow窗口
    void setWfSystemWindow(HWfSystemWindow* pWindow);

    //创建在线浏览窗口
    void createOnlineWindow(QMdiArea* area);

    void openOnlineGraph(const QString &graphName, const int graphID);

public:
    //测点类型相关
    HPointTerm* findPointTerm(ushort id);
    HPointTerm* findPointTerm(QString name);
    //操作票相关
    HOpSheetInfo* findOpSheetInfo(int id);
    HOpSheetInfo* findOpSheetInfo(QString name);
    bool loadOpSheetInfo();
    bool saveOpSheetInfo();
    HOpSheetInfo* addOpSheet();
    bool delOpSheet(ushort wOpSheetID);
    ushort getPreOpSheet(ushort wOpSheetID);
    ushort getNextOpSheet(ushort wOpSheetID);



protected:
    QList<HOpSheetInfo*> m_pOpSheetInfoList;
    QList<OPTERMGROUP*> m_pOpTermGroupList;
    QList<HPointTerm*> m_pPointTermList;

private:
    QString strGraphFile;
    HWfSystemDoc* m_wfSystemDoc;
    HGraphFrame* m_pOnlineWindow;
    HWfSystemWindow* m_pWfSystemWindow;


};

#endif // HWFSYSTEMMGR_H
