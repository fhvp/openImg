
#ifndef __2015_12_22_MOBTIME_H__
#define __2015_12_22_MOBTIME_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBPlatform.h"

/**********************************************************
* MOBTime Structure
**********************************************************/
typedef struct
{
	u32							m_year;		// years
	u32							m_month;	// months since January - [1,12]
	u32							m_day;		// day of the month - [1,31]

	//u32							m_yday;		// days since January 1 - [0,365]
	u32							m_wday;		// days since Sunday - [1,7]

	u32							m_hour;		// hours since midnight - [0,23]
	u32							m_min;		// minutes after the hour - [0,59]
	u32							m_sec;		// seconds after the minute - [0,59]
}MOBTime;

/**********************************************************
* CMOBTime Class
**********************************************************/
class CMOBTime : public CMOBPlatform
{
private:
	static CMOBTime* instance;
protected:
public:

private:
protected:
	CMOBTime();
	~CMOBTime();
public:
	virtual STATE INIT();
	static CMOBTime* Instance();
	
	STATE GetLocalTime(MOBTime* _time);
	STATE TranslateTime(void* _tm, MOBTime* _time);
};

#endif __2015_12_22_MOBTIME_H__