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
    return NULL;
}

HOpSheetInfo* HOpSheetInfoList::findOpSheetInfo(QString name)
{
    return NULL;
}

bool HOpSheetInfoList::loadOpSheetInfo(int nNum)
{
    return false;
}

bool HOpSheetInfoList::saveOpSheetInfo()
{
    return false;
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
    return false;
}

bool HOpSheetStep::setAttr(ushort wAttr,void* pVal,size_t size)
{
    return false;
}

void HOpSheetStep::setStepIndex(int step)
{

}

int HOpSheetStep::getStepIndex()
{
    return 0;
}

HOpSheetStep* HOpSheetStep::setOpSheetStep(HOpSheetStep* item)
{
    return NULL;
}

HOpSheetStep* HOpSheetStep::getOpSheetStep(HOpSheetStep* item)
{
    return NULL;
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
    return false;
}

void HOpSheetStep::clearInterrupt()
{

}

bool HOpSheetStep::isRemoteOp()
{
    return false;
}

bool HOpSheetStep::isLocalOp()
{
    return false;
}

bool HOpSheetStep::isLockType()
{
    return false;
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
    return false;
}

bool HOpSheet::setAttr(ushort wAttr,void* pVal,size_t size)
{
    return false;
}

void HOpSheet::clearOpSheetSteps()
{

}

HOpSheetStep* HOpSheet::addOpSheetStep()
{
    return NULL;
}

HOpSheetStep* HOpSheet::insertOpSheetItem(int row)
{
    return NULL;
}

HOpSheetStep* HOpSheet::getOpSheetStep(int row)
{
    return NULL;
}

bool HOpSheet::moveOpSheetStep(int row,bool bup)
{
    return false;
}

bool HOpSheet::delOpSheetStep(int row)
{
    return false;
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
    return false;
}

void HOpSheet::clearInterrupt()
{

}

bool HOpSheet::isModify()
{
    return false;
}

void HOpSheet::setModify(bool modify)
{

}

//数据库部分
bool HOpSheet::loadOpSheet(ushort wOpSheetID)
{
    return false;
}

bool HOpSheet::saveOpSheet()
{
    return false;
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
