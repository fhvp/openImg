
/**********************************************************
* Include
**********************************************************/
#include "MOBPath.h"

#include <stdio.h>
#include <direct.h>	//getcwd
#include <string.h>

#include "MOBLayer.h"
#include "MOBLogger.h"

/**********************************************************
* Global Variable
**********************************************************/
CMOBPath* CMOBPath::m_instance = 0x00;

/**********************************************************
* Define Variable
**********************************************************/
#define MAX_PATH_LEN		256

/**********************************************************
* Default CMOBPath Function
**********************************************************/
CMOBPath::CMOBPath()
{

}

CMOBPath::~CMOBPath()
{

}

STATE CMOBPath::INIT()
{
	return MOB_SUCCEED;
}

CMOBPath* CMOBPath::Instance()
{
	if (CMOBPath::m_instance == 0x00)
	{
		CMOBPath::m_instance = new CMOBPath();
	}
	return (CMOBPath*)CMOBPath::m_instance;
}

/**********************************************************
* CMOBPath Function
**********************************************************/
char* CMOBPath::cut(char* _buf, char* _split)
{
	return strstr(_buf, _split);
}

STATE CMOBPath::GetPath(char* _buf)
{
	_getcwd( _buf, MAX_PATH_LEN );

	return MOB_SUCCEED;
}

STATE CMOBPath::GetPath(char* _buf, char* _split)
{
	if (_split == 0x00)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Split Data is NULL!!\n");
		return MOB_FAILED;
	}

	this->GetPath(_buf);

	STATE result = this->SplitPath(_buf, _split);

	return result;
}

PROPOSITION CMOBPath::IsText(char* _buf, char* _text)
{
	if( _buf == 0x00 || _text == 0x00 )
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Data is Empty!! Buffer : %s, Text : %s\n", _buf, _text);
		return MOB_FALSE;
	}

	char* ptr = this->cut(_buf, _text);

	if (ptr == MOB_FAILURE)
		return MOB_FALSE;
	return MOB_TRUE;
}

STATE CMOBPath::SetPath(char* _buf, char* _text)
{
	int size = strlen(_buf) + strlen(_text);
	strcat_s(_buf, size+1, _text);

	return MOB_SUCCEED;
}

STATE CMOBPath::SplitPath(char* _buf, char* _split, WAY _way /*= MOB_LEFT*/)
{
	if (_buf == 0x00 || _split == 0x00)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Split Path!! Path : %s, Split text : %s\n", _buf, _split);
		return MOB_FAILED;
	}

	char* ptr = _buf;
	char* buf = 0x00;

	while( 1 )
	{
		ptr = cut(ptr, _split);
		if ( ptr == NULL)
			break;
		buf = ptr;
		ptr++;
	}

	int len = strlen(buf);

	switch (_way)
	{
	case WAY::MOB_LEFT:
		memset(buf, 0x00, len);
		break;
	case WAY::MOB_RIGHT:
		memcpy(_buf, &buf[strlen(_split)], len);
		memset(&_buf[len], 0x00, strlen(&_buf[len]));
		break;
	default:
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}
