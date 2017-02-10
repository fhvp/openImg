/*
 * MOBUserFunction.c
 *
 *  Created on: 2015. 6. 25.
 *      Author: jghan
 */
/**********************************************************
 * Include
 **********************************************************/
#include "MOBLogger.h"

//Platform
#include "MOBLayer.h"
//#include "MOBMutex.h"

#include <stdio.h>
#include <stdarg.h>
#include <afx.h>	//TRACE

/**********************************************************
 * Define Variable
 **********************************************************/
const char* LayerName[] =
{
	"   ",		// 0
	"GUI",		// 1
	"   ",		// 2
	"PHY",		// 3
	"MAC",		// 4
	"RLC",		// 5
	"RRC",		// 6
	"   ",		// 7
	"   ",		// 8
	"   ",		// 9
	"   ",		//10
	" DM",		//11
	"   ",		//12
	"   ",		//13
	"TIME",		//14
	"Platform",	//15
	"TEST"		//16
};

const char LayerPrint[] =
{
	0x01,		//0x00, 0
	0x01,		//0x00, 1
	0x01,		//0x00, 2
	0x01,		//"PHY", 3
	0x01,		//"MAC", 4
	0x01,		//"RLC", 5
	0x01,		//"RRC", 6
	0x01,		//0x00, 7
	0x01,		//0x00, 8
	0x01,		//0x00, 9
	0x01,		//0x00, 10
	0x01,		//0x00, 11
	0x01,		//0x00, 12
	0x01,		//0x00, 13
	0x01,		//"TIME", 14
	0x01,		//"Platform", 15
	0x01		//"TEST" 16
};

const char* levelName[] =
{
	"DEBUG",	// 0
	"SUCCE",	// 1
	"ERROR",	// 2
	"   ",		// 3
	"   ",		// 4
	"   ",		// 5
	"   ",		// 6
	"   ",		// 7
	"   ",		// 8
	"   ",		// 9
	"   ",		//10
	"   ",		//11
	"   ",		//12
	"   ",		//13
	"   ",		//14
	"   ",		//15
	"   "		//16
};

const char levelPrint[] =
{
	0x01,		//"DEBUG", 0
	0x01,		//"SUCCE", 1
	0x01,		//"ERROR", 2
	0x01,		//"0x00", 3
	0x01,		//"0x00", 4
	0x01,		//"0x00", 5
	0x01,		//"0x00", 6
	0x01,		//"0x00", 7
	0x01,		//"0x00", 8
	0x01,		//"0x00", 9
	0x01,		//"0x00", 10
	0x01,		//"0x00", 11
	0x01,		//"0x00", 12
	0x01,		//"0x00", 13
	0x01,		//"0x00", 14
	0x01,		//"0x00", 15
	0x01		//"0x00" 16
};

/**********************************************************
* Static Variable & Function
**********************************************************/
CMOBLogger* CMOBLogger::m_instance = 0x00;

CMOBLogger* CMOBLogger::Instance()
{
	if (CMOBLogger::m_instance == 0x00)
		CMOBLogger::m_instance = new CMOBLogger();
	return (CMOBLogger*)CMOBLogger::m_instance;
}

/**********************************************************
 * Memory Register
 **********************************************************/
// Log Data Buffer
char gHexDataBuffer[512] = {0x00, };
char gLogViewBuffer[2048] = { 0x00, };

/**********************************************************
 * Configuration Function
 **********************************************************/


/**********************************************************
 * Default CMOBLogger Function
 **********************************************************/
CMOBLogger::CMOBLogger()
{

}

CMOBLogger::~CMOBLogger()
{

}

STATE CMOBLogger::INIT()
{
	return MOB_SUCCEED;
}

/**********************************************************
* CMOBLogger Function
**********************************************************/
char* CMOBLogger::HexLog(void* _buf, int _size)
{
	gHexDataBuffer[0] = 0x00;
	char* wr_ptr = gHexDataBuffer;
	char* data = (char*)_buf;

	int i = 0x00;
	for (i = 0; i < SMALLER(_size, sizeof(gHexDataBuffer)); i++)
	{
		wr_ptr += sprintf_s(wr_ptr, sizeof(gHexDataBuffer), "%02x ", (char*)(data[i] & 0xFF));
	}

	return gHexDataBuffer;
}

STATE CMOBLogger::Write(LAYER _src, char* _format, ...)
{
	//Mutex.Lock( &SetFormatToLog );
	if( LayerPrint[_src] == 0x00 )
	{
		return MOB_FAILED;
	}

	char buf[1024] = { 0x00, };
	char* wr_ptr = buf;

	wr_ptr += sprintf_s(wr_ptr, 16, "[%8s] ", LayerName[_src]);

	va_list ap;
	va_start( ap, _format );
	wr_ptr += vsprintf_s(wr_ptr, 1008, _format, ap);
	va_end( ap );

	printf("%s", buf);
	//Mutex.Unlock( &SetFormatToLog );

	return MOB_SUCCEED;
}

char* CMOBLogger::Write(LEVEL _level, char* _format, ...)
{
	//char buffer[1024] = { 0x00, };
	char* wr_ptr = (char*)gLogViewBuffer;

	va_list ap;
	va_start(ap, _format);
	wr_ptr += vsprintf_s(wr_ptr, 1022, _format, ap);
	va_end(ap);

	wr_ptr[0] = 0x00;

	size_t size = 0x00;

	return gLogViewBuffer;
}


STATE CMOBLogger::Write(LAYER _src, LEVEL _level, char* _format, ...)
{
	if (LayerPrint[_src] == 0x00)
		return MOB_FAILED;

	if (levelPrint[_level] == 0x00)
		return MOB_FAILED;

	char buf[1024] = { 0x00, };
	char* wr_ptr = buf;

	if (_level == 0x00) // DEBUG
		wr_ptr += sprintf_s(wr_ptr, 16, "[%8s] ", LayerName[_src]);

	va_list ap;
	va_start(ap, _format);
	wr_ptr += vsprintf_s(wr_ptr, 1008, _format, ap);
	va_end(ap);

	printf("%s", buf);

	return MOB_SUCCEED;
}