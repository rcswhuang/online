#include "hopsheet.h"
#include "honlineapi.h"
///////////////////////////////////////////////////////////////////////////////
//
HOpSheetInfo::HOpSheetInfo()
{
    memset(&m_opSheetInfo,0,sizeof(OPSHEETINFO));
    m_opSheetInfo.wStationID = (ushort)-1;
    m_opSheetInfo.wGroupID = (ushort)-1;
    m_opSheetInfo.wOpSheetID = (ushort)-1;
    m_opSheetInfo.wOpSheetNo = (ushort)-1;
    qstrcpy(m_opSheetInfo.szOpSheetTitle,"新票");
    qstrcpy(m_opSheetInfo.szOpSheetDescripe,"新票");
    qstrcpy(m_opSheetInfo.szOpSheetTask,"");
    m_opSheetInfo.btOpSheetType = OPSHEET_TYPE_TEMP;
    m_opSheetInfo.nOpSheetSteps = 0;
}

HOpSheetInfo::~HOpSheetInfo()
{

}

void HOpSheetInfo::setOpSheetInfo(OPSHEETINFO* info)
{
    if(!info) return;
    memcpy(&m_opSheetInfo,info,sizeof(OPSHEETINFO));
}

void HOpSheetInfo::getOpSheetInfo(OPSHEETINFO* info)
{
    if(!info) return;
    memcpy(info,&m_opSheetInfo,sizeof(OPSHEETINFO));
}

bool HOpSheetInfo::getAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal)
        return false;
    switch(wAttr)
    {
    case OPSHEET_ATTR_ID      : *((ushort*)pVal) = m_opSheetInfo.wOpSheetID;break;
    case OPSHEET_ATTR_NO      : *((ushort*)pVal) = m_opSheetInfo.wOpSheetNo;break;
    case OPSHEET_ATTR_TASKTYPE: *((ushort*)pVal) = m_opSheetInfo.btOpSheetTaskType;break;
    case OPSHEET_ATTR_STID    : *((ushort*)pVal) = m_opSheetInfo.wStationID;break;
    case OPSHEET_ATTR_GROUPID : *((ushort*)pVal) = m_opSheetInfo.wGroupID;break;
    case OPSHEET_ATTR_TYPE    : *((ushort*)pVal) = m_opSheetInfo.btOpSheetType;break;
    case OPSHEET_ATTR_STEPS   :	*((int*)pVal) = m_opSheetInfo.nOpSheetSteps;break;
    case OPSHEET_ATTR_TITLE   :	qstrcpy((char*)pVal,m_opSheetInfo.szOpSheetTitle);break;
    case OPSHEET_ATTR_DESCRIBE:	qstrcpy((char*)pVal,m_opSheetInfo.szOpSheetDescripe);break;
    case OPSHEET_ATTR_TASK    : qstrcpy((char*)pVal,m_opSheetInfo.szOpSheetTask);break;
    case OPSHEET_ATTR_OPERATOR: qstrcpy((char*)pVal,m_opSheetInfo.szOperator);break;
    case OPSHEET_ATTR_GUARDIAN:	qstrcpy((char*)pVal,m_opSheetInfo.szGuardian);break;
    case OPSHEET_ATTR_EDITOR  :	qstrcpy((char*)pVal,m_opSheetInfo.szEditor);break;
    case OPSHEET_ATTR_MAKETIME:*((time_t*)pVal) = m_opSheetInfo.tOperTime;break;
    default: return false;
    }
    return true;
}

bool HOpSheetInfo::setAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal)
        return false;
    switch(wAttr)
    {
    case OPSHEET_ATTR_ID      : m_opSheetInfo.wOpSheetID = *((ushort*)pVal);break;
    case OPSHEET_ATTR_NO      : m_opSheetInfo.wOpSheetNo = *((ushort*)pVal);break;
    case OPSHEET_ATTR_TASKTYPE: m_opSheetInfo.btOpSheetTaskType = *((ushort*)pVal);break;
    case OPSHEET_ATTR_STID    : m_opSheetInfo.wStationID = *((ushort*)pVal);break;
    case OPSHEET_ATTR_GROUPID : m_opSheetInfo.wGroupID = *((ushort*)pVal);break;
    case OPSHEET_ATTR_TYPE    : m_opSheetInfo.btOpSheetType = *((ushort*)pVal);break;
    case OPSHEET_ATTR_STEPS   :	m_opSheetInfo.nOpSheetSteps = *((int*)pVal);break;
    case OPSHEET_ATTR_TITLE   :
        qstrncpy(m_opSheetInfo.szOpSheetTitle,(char*)pVal,OPERASHEETNAMELEN-1);
        m_opSheetInfo.szOpSheetTitle[OPERASHEETNAMELEN-1] = 0;
        break;
    case OPSHEET_ATTR_DESCRIBE:
        qstrncpy(m_opSheetInfo.szOpSheetDescripe,(char*)pVal,OPERASHEETDESCRIBELEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERASHEETDESCRIBELEN-1] = 0;
        break;
    case OPSHEET_ATTR_TASK    :
        qstrncpy(m_opSheetInfo.szOpSheetTask,(char*)pVal,OPERASHEETTASKLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERASHEETTASKLEN-1] = 0;
        break;
    case OPSHEET_ATTR_OPERATOR:
        qstrncpy(m_opSheetInfo.szOperator,(char*)pVal,OPERATORLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERATORLEN-1] = 0;
        break;
    case OPSHEET_ATTR_GUARDIAN:
        qstrncpy(m_opSheetInfo.szGuardian,(char*)pVal,OPERATORLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERATORLEN-1] = 0;
        break;
    case OPSHEET_ATTR_EDITOR  :
        qstrncpy(m_opSheetInfo.szEditor,(char*)pVal,OPERATORLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERATORLEN-1] = 0;
        break;
    case OPSHEET_ATTR_MAKETIME:m_opSheetInfo.tOperTime = *((time_t*)pVal);break;
    default: return false;
    }
    return true;
}

void HOpSheetInfo::copyTo(HOpSheetInfo* info)
{
    if(!info) return;
    memcpy(&m_opSheetInfo,&info->m_opSheetInfo,sizeof(OPSHEETINFO));
}

void HOpSheetInfo::copyFrom(HOpSheetInfo* info)
{
    if(!info) return;
    memcpy(&info->m_opSheetInfo,&m_opSheetInfo,sizeof(OPSHEETINFO));
}

bool HOpSheetInfo::checkExist()
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
    m_pOpSheetInfo = NULL;
    bModify = false;
}

HOpSheet::~HOpSheet()
{
    clearOpSheetSteps();
    if(m_pOpSheetInfo)
    {
        delete m_pOpSheetInfo;
        m_pOpSheetInfo = NULL;
    }
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
