#ifndef HONLINEDOC_H
#define HONLINEDOC_H

#include <QObject>
class HStation;
class HBaseObj;
class HIconGraphicsItem;
class HIconTemplate;
class QDomElement;
class HStation;
class HGraph;
class HOnlineMgr;

/*
 * 初始化 加载所有厂站的信息，所有画面的信息，所有模板的信息(考虑启动画面)
 * 初始化临时HGraph
 * 当新建一个新画面时，提供HGraph对象，初始化这个HGraph对象(包含背景等信息)，返回给HGraph
 *临时HGraph的内容提供给view/scene,供显示。
 * 打开画面，删除都是如此，代码此处实现，可以供其他对象调用对应接口
*/
class HOnlineDoc : QObject
{
public:
    HOnlineDoc(HOnlineMgr* mgr);
    virtual ~HOnlineDoc();

public:
    //加载厂站信息
    void loadStation();

    //厂站ID获取厂站
    HStation* getStation(quint16 wStationID);

    //厂站地址获取厂站
    HStation* getRtu(quint16 wStationAddress);

    //索引厂站
    HStation* findStation(int nIndex);

    //加载画面信息
    void loadAllGraph();

    //保存画面信息
    void saveAllGraph();

    //查找画面
    HGraph* findGraph(int graphID);

    //
    HGraph* findGraph(const QString& graphName);

    //打开画面
    bool openGraph(const QString& name,const int id);

    //获取当前画面
    HGraph* getCurGraph();

public:
    //厂站列表
    QList<HStation*> pStationList;

    //图形文件列表
    QList<HGraph*> pGraphList;

protected:

    HOnlineMgr* pOnlineMgr;

    //当前文件
    HGraph* pCurGraph;

};

#endif // HGRAPHEDITORDOC_H
