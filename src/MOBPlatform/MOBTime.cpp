
/**********************************************************
* Include
**********************************************************/
#include "MOBTime.h"
#include <time.h>


/**********************************************************
* Static Variable & Function
**********************************************************/
CMOBTime* CMOBTime::instance = 0x00;

CMOBTime* CMOBTime::Instance()
{
	if (CMOBTime::instance == 0x00)
		CMOBTime::instance = new CMOBTime();
	return CMOBTime::instance;
}

/**********************************************************
* CMOBTime Function
**********************************************************/
CMOBTime::CMOBTime()
{

}

CMOBTime::~CMOBTime()
{

}

STATE CMOBTime::INIT()
{
	return MOB_SUCCEED;
}

STATE CMOBTime::GetLocalTime(MOBTime* _time)
{
	time_t t;
	struct tm stm;

	t = time(NULL);
	localtime_s(&stm, &t);

	this->TranslateTime(&stm, _time);

	return MOB_SUCCEED;
}

STATE CMOBTime::TranslateTime(void* _tm, MOBTime* _time)
{
	struct tm* stm = (tm*)_tm;

	_time->m_year = stm->tm_year + 1900;
	_time->m_month = stm->tm_mon + 1;
	_time->m_day = stm->tm_mday;

	_time->m_wday = stm->tm_wday + 1;

	_time->m_hour = stm->tm_hour;
	_time->m_min = stm->tm_min;
	_time->m_sec = stm->tm_sec;

	return MOB_SUCCEED;
}