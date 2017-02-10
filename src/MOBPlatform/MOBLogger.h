/*
 * CMOBLogger.h
 *
 *  Created on: 2015. 10. 16.
 *      Author: jghan
 */
/**********************************************************
 * Job Log
 **********************************************************
	15.10.16	New Platform File

 **********************************************************/
#ifndef __2015_06_25_MOBLOGGER_H__
#define __2015_06_25_MOBLOGGER_H__
/**********************************************************
 * Include
 **********************************************************/
#include "MOBPlatform.h"
#include "MOBLayer.h"

/**********************************************************
 * User Log Function & Defines
 **********************************************************/
enum LEVEL
{
	MOB_LEVEL_DEBUG			= 1,
	MOB_LEVEL_SUCCESS		= 2,
	MOB_LEVEL_ERROR			= 3
};

/**********************************************************
 * Configuration Function
 **********************************************************/

/**********************************************************
 * User Function Class
 **********************************************************/
class CMOBLogger : public CMOBPlatform
{
private:
	static CMOBLogger*			m_instance;
protected:
public:

private:
protected:
	CMOBLogger();
	virtual ~CMOBLogger();

public:
	virtual STATE INIT();
	static CMOBLogger* Instance();

	static char* HexLog(void* _buf, int _size);
	static STATE Write(LAYER _src, char* _format, ...);
	static char* Write(LEVEL _level, char* _format, ...);
	static STATE Write(LAYER _src, LEVEL _level, char* _format, ...);
};

/**********************************************************
 * Void
 **********************************************************/
#define HEXLOG					(CMOBLogger::HexLog)
#define MOB_DEBUG 				(CMOBLogger::Write)
#define MOB_LOGVIEW_M			(CMOBLogger::Write)

#define BIGGER(v1,v2)			(int)(v1 >= v2 ? v1 : v2)
#define SMALLER(v1,v2)			(int)(v1 >= v2 ? v2 : v1)

#endif __2015_06_25_MOBLOGGER_H__
