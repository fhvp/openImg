
/**********************************************************
* Include
**********************************************************/
#include "MOBClass.h"

/**********************************************************
* Static Variable & Function
**********************************************************/
CMOBClass* CMOBClass::m_instance = 0x00;

CMOBClass* CMOBClass::Instance()
{
	if (CMOBClass::m_instance == 0x00)
		CMOBClass::m_instance = new CMOBClass();
	return CMOBClass::m_instance;
}

/**********************************************************
* CMOBPrimitive Function
**********************************************************/
CMOBPrimitive::CMOBPrimitive()
{

}

CMOBPrimitive::~CMOBPrimitive()
{

}

void CMOBPrimitive::release()
{

}

u16 CMOBPrimitive::Encode(char* _dataBlock)
{
	return MOB_FAILURE;
}

u16 CMOBPrimitive::Decode(char* _dataBlock)
{
	return MOB_FAILURE;
}

/**********************************************************
* CMOBClass Function
**********************************************************/
CMOBClass::CMOBClass()
{

}

CMOBClass::~CMOBClass()
{

}

STATE CMOBClass::INIT()
{
	return MOB_SUCCEED;
}

STATE CMOBClass::open()
{
	return MOB_SUCCEED;
}
