
#ifndef __2016_01_28_MOB_MFC_LOGGER_H__
#define __2016_01_28_MOB_MFC_LOGGER_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBPlatform.h"
#include "MOBLogger.h"

/**********************************************************
* CMOBMFCLogger Class
**********************************************************/
class CMOBMFCLogger : public CMOBPlatform
{
private:
	static CMOBMFCLogger*			m_instance;
protected:
public:

private:
protected:
	CMOBMFCLogger();
	virtual ~CMOBMFCLogger();
public:
	static CMOBMFCLogger* Instance();
	virtual STATE INIT();

	static wchar_t* Write(LEVEL _level, char* _format, ...);
	static char* WtoM(wchar_t* _data, size_t _size = 1024);
	static char* WStoM(CStringW _data, size_t _size = 1024);
};

/**********************************************************
* Macro Define Function
**********************************************************/
#define MOB_LOGVIEW_W			(CMOBMFCLogger::Write)
#define WTOM					(CMOBMFCLogger::WtoM)
#define WSTOM					(CMOBMFCLogger::WStoM)

#endif __2016_01_28_MOB_MFC_LOGGER_H__