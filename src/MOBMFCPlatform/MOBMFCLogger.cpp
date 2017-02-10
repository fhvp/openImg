
/**********************************************************
* Include
**********************************************************/
#include "stdafx.h"
#include "MOBMFCLogger.h"

/**********************************************************
* Define Variable
**********************************************************/
wchar_t gWcharBuffer[1024] = { 0x00, };
char gCharBuffer[1024] = { 0x00, };

/**********************************************************
* Static Variable & Function
**********************************************************/
CMOBMFCLogger* CMOBMFCLogger::m_instance = 0x00;

CMOBMFCLogger* CMOBMFCLogger::Instance()
{
	if (CMOBMFCLogger::m_instance == 0x00)
		CMOBMFCLogger::m_instance = new CMOBMFCLogger();
	return CMOBMFCLogger::m_instance;
}

/**********************************************************
* CMOBMFCLogger Class
**********************************************************/
CMOBMFCLogger::CMOBMFCLogger()
{

}

CMOBMFCLogger::~CMOBMFCLogger()
{

}

STATE CMOBMFCLogger::INIT()
{
	return MOB_SUCCEED;
}

wchar_t* CMOBMFCLogger::Write(LEVEL _level, char* _format, ...)
{
	char buffer[1024] = { 0x00, };
	char* wr_ptr = (char*)buffer;

	va_list ap;
	va_start(ap, _format);
	wr_ptr += vsprintf_s(wr_ptr, 1022, _format, ap);
	va_end(ap);

	wr_ptr[0] = 0x00;

	size_t size = 0x00;
	mbstowcs_s(&size, gWcharBuffer, buffer, 1024);

	return gWcharBuffer;
}

char* CMOBMFCLogger::WtoM(wchar_t* _data, size_t _size /*= 1024*/)
{
	WideCharToMultiByte(CP_ACP, 0, _data, -1, gCharBuffer, _size, NULL, NULL);
	return gCharBuffer;
}

char* CMOBMFCLogger::WStoM(CStringW _data, size_t _size /*= 1024*/)
{
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)_data, -1, gCharBuffer, _size, NULL, NULL);
	return gCharBuffer;
}
