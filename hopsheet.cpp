#include "hopsheet.h"
///////////////////////////////////////////////////////////////////////////////
//
HOpSheetInfo::HOpSheetInfo()
{

}

HOpSheetInfo::~HOpSheetInfo()
{

}

void HOpSheetInfo::loadFromDb(int row)
{

}

void HOpSheetInfo::saveToDb(int row)
{

}

HOpSheetInfo* HOpSheetInfo::setOpSheetInfo(HOpSheetInfo* info)
{
    return NULL;
}

HOpSheetInfo* HOpSheetInfo::getOpSheetInfo(HOpSheetInfo* info)
{
    return NULL;
}

bool HOpSheetInfo::getAttr(ushort wAttr,void* pVal,size_t size)
{
    return false;
}

bool HOpSheetInfo::setAttr(ushort wAttr,void* pVal,size_t size)
{
    return false;
}

void HOpSheetInfo::copyTo(HOpSheetInfo* info)
{

}

void HOpSheetInfo::copyFrom(HOpSheetInfo* info)
{

}

bool HOpSheetInfo::checkExist()
{
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////
HOpSheetInfoList::HOpSheetInfoList()
{

}

HOpSheetInfoList::~HOpSheetInfoList()
{

}

void HOpSheetInfoList::clear()
{

}

HOpSheetInfo* HOpSheetInfoList::findOpSheetInfo(int id)
{

}

HOpSheetInfo* HOpSheetInfoList::findOpSheetInfo(QString name)
{

}

bool HOpSheetInfoList::loadOpSheetInfo(int nNum)
{

}

bool HOpSheetInfoList::saveOpSheetInfo()
{

}

///////////////////////////////////////////////////////////////////////////////////////////
HOpSheetStep::HOpSheetStep()
{

}

HOpSheetStep::~HOpSheetStep()
{

}

void HOpSheetStep::loadFromDb(int row)
{

}

void HOpSheetStep::saveToDb(int row)
{

}

bool HOpSheetStep::getAttr(ushort wAttr,void* pVal,size_t size)
{

}

bool HOpSheetStep::setAttr(ushort wAttr,void* pVal,size_t size)
{

}

void HOpSheetStep::setStepIndex(int step)
{

}

int HOpSheetStep::getStepIndex()
{

}

HOpSheetStep* HOpSheetStep::setOpSheetStep(HOpSheetStep* item)
{

}

HOpSheetStep* HOpSheetStep::getOpSheetStep(HOpSheetStep* item)
{

}

void HOpSheetStep::start(int row)
{

}

void HOpSheetStep::stop()
{

}

void HOpSheetStep::isRunning()
{

}

void HOpSheetStep::setInterrupt(int row)
{

}

bool HOpSheetStep::isInterrupt(int row)
{

}

void HOpSheetStep::clearInterrupt()
{

}

bool HOpSheetStep::isRemoteOp()
{

}

bool HOpSheetStep::isLocalOp()
{

}

bool HOpSheetStep::isLockType()
{

}

///////////////////////////////////////////////////////////////////////
HOpSheet::HOpSheet()
{

}

HOpSheet::~HOpSheet()
{

}

bool HOpSheet::getAttr(ushort wAttr,void* pVal,size_t size)
{

}

bool HOpSheet::setAttr(ushort wAttr,void* pVal,size_t size)
{

}

void HOpSheet::clearOpSheetSteps()
{

}

HOpSheetStep* HOpSheet::addOpSheetStep()
{

}

HOpSheetStep* HOpSheet::insertOpSheetItem(int row)
{

}

HOpSheetStep* HOpSheet::getOpSheetStep(int row)
{

}

bool HOpSheet::moveOpSheetStep(int row,bool bup)
{

}

bool HOpSheet::delOpSheetStep(int row)
{

}

void HOpSheet::start(int row)
{

}

void HOpSheet::stop()
{

}

void HOpSheet::isRunning()
{

}

void HOpSheet::setInterrupt(int row)
{

}

bool HOpSheet::isInterrupt(int row)
{

}

void HOpSheet::clearInterrupt()
{

}

bool HOpSheet::isModify()
{

}

void HOpSheet::setModify(bool modify)
{

}

//数据库部分
bool HOpSheet::loadOpSheet(ushort wOpSheetID)
{

}

bool HOpSheet::saveOpSheet()
{

}

void HOpSheet::close()
{

}

void HOpSheet::copyTo(HOpSheetInfo* pOpSheetInfo)
{

}

void HOpSheet::copyFrom(HOpSheetInfo* pOpSheetInfo)
{

}
