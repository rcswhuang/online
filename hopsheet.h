#ifndef HOPSHEET_H
#define HOPSHEET_H

#include <QObject>
#include "publicdata.h"
//操作票信息类
class HOpSheetInfo: public QObject
{
    Q_OBJECT
public:
    HOpSheetInfo();
    ~HOpSheetInfo();
public:
    void setOpSheetInfo(OPSHEETINFO* info);
    void getOpSheetInfo(OPSHEETINFO* info);
    bool getAttr(ushort wAttr,void* pVal,size_t size = 0);
    bool setAttr(ushort wAttr,void* pVal,size_t size = 0);
    void copyTo(HOpSheetInfo* info);
    void copyFrom(HOpSheetInfo* info);

    bool checkExist();//判断文件是否存在

protected:
    OPSHEETINFO m_opSheetInfo;
};

/*
class HOpSheetInfoList : public QList<HOpSheetInfo>
{
public:
    HOpSheetInfoList();
    ~HOpSheetInfoList();
public:
    void clear();
    HOpSheetInfo* findOpSheetInfo(int id);
    HOpSheetInfo* findOpSheetInfo(QString name);
    bool loadOpSheetInfo(int nNum);
    bool saveOpSheetInfo();
};
*/

//操作票项类
class HOpSheetStep : public QObject
{
public:
    HOpSheetStep();
    ~HOpSheetStep();

public:
    void loadFromDb(int row);
    void saveToDb(int row);
    bool getAttr(ushort wAttr,void* pVal,size_t size = 0);
    bool setAttr(ushort wAttr,void* pVal,size_t size = 0);
    void setStepIndex(int step);
    int getStepIndex();
    HOpSheetStep* setOpSheetStep(HOpSheetStep* item);
    HOpSheetStep* getOpSheetStep(HOpSheetStep* item);

    void start(int row);
    void stop();
    void isRunning();
    void setInterrupt(int row);
    bool isInterrupt(int row);
    void clearInterrupt();

    bool isRemoteOp();
    bool isLocalOp();
    bool isLockType();

protected:
    OPSHEETSTEP opSheetItem;
    bool m_bInterrupt;
    bool m_bRunning;

};


//操作票类
class HOpSheet : public QObject
{
    Q_OBJECT
public:
    HOpSheet();
    ~HOpSheet();
public:
    bool getAttr(ushort wAttr,void* pVal,size_t size = 0);
    bool setAttr(ushort wAttr,void* pVal,size_t size = 0);

    void clearOpSheetSteps();
    HOpSheetStep* addOpSheetStep();
    HOpSheetStep* insertOpSheetItem(int row);
    HOpSheetStep* getOpSheetStep(int row);
    bool moveOpSheetStep(int row,bool bup);
    bool delOpSheetStep(int row);//删除行

    void start(int row);
    void stop();
    void isRunning();
    void setInterrupt(int row);
    bool isInterrupt(int row);
    void clearInterrupt();
    bool isModify();
    void setModify(bool modify = true);

    //数据库部分
    bool loadOpSheet(ushort wOpSheetID);//操作票ID
    bool saveOpSheet();
    void close();
    void copyTo(HOpSheetInfo* pOpSheetInfo);
    void copyFrom(HOpSheetInfo* pOpSheetInfo);
signals:

public slots:

protected:
    HOpSheetInfo* m_pOpSheetInfo;
    QList<HOpSheetStep*> m_pOpSheetItemList;
    bool bModify;
};

#endif // HOPSHEET_H
