
/**********************************************************
* Include
**********************************************************/
#include "MOBFile.h"
#include "MOBLogger.h"
#include "MOBLayer.h"
#include "MOBPath.h"
#include <string.h>

/**********************************************************
* Global Variable
**********************************************************/
CMOBFile* CMOBFile::m_instance = 0x00;

/**********************************************************
* Class Function
**********************************************************/
CMOBFile::CMOBFile()
{
	this->INIT();
}

CMOBFile::~CMOBFile()
{

}

STATE CMOBFile::INIT()
{
	return MOB_SUCCEED;
}

CMOBFile* CMOBFile::Instance()
{
	if (CMOBFile::m_instance == 0x00)
	{
		CMOBFile::m_instance = new CMOBFile();
	}

	return CMOBFile::m_instance;
}

MOBFile* CMOBFile::FileOpen(char* _path, char* _fileName, char* _openType)
{
	MOBFile* file = new MOBFile;

	memset(file, 0x00, sizeof(MOBFile));

	char fileName[256] = {0x00,};

	sprintf_s(fileName, sizeof(fileName), "%s\\%s", _path, _fileName);
	fopen_s(&file->m_file, fileName, _openType);

	if(file->m_file == NULL)
	{
		MOB_DEBUG( MOB_LAYER_PLATFORM, "Can not Open File!! Path : %s, Name : %s, OpenType : %s\n", _path, _fileName, _openType );
		delete file;
		return MOB_FAILURE;
	}

	memcpy( file->m_fileName, fileName, sizeof(fileName) );

	return file;
}

MOBFile* CMOBFile::FileOpen(char* _fileName, char* _openType)
{
	MOBFile* file = new MOBFile;

	memset(file, 0x00, sizeof(MOBFile));

	fopen_s(&file->m_file, _fileName, _openType);

	if (file->m_file == NULL)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Open File!! Name : %s, OpenType : %s\n", _fileName, _openType);
		return MOB_FAILURE;
	}

	memcpy(file->m_fileName, _fileName, sizeof(file->m_fileName));

	return file;
}

STATE CMOBFile::FileOpen(MOBFile* _mFile, char* _openType)
{
	fopen_s(&_mFile->m_file, _mFile->m_fileName, _openType);

	if (_mFile->m_file == NULL)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Open File!! Name : %s, OpenType : %s\n", _mFile->m_fileName, _openType);
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}

STATE CMOBFile::Gets(char* _buf, u32 _bufSize, MOBFile* _file)
{
	if (feof(_file->m_file))
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "File Error!! Function is %s\n", _MOBFILE_FUNCTION_GETS_);
		return MOB_FAILED;
	}

	if (fgets(_buf, _bufSize, _file->m_file) == NULL)
	{
		return MOB_FAILED;
	}

	if (_buf[strlen(_buf) - 2] == '\n\n')
	{
		_buf[strlen(_buf) - 2] = 0x00;
	}

	return MOB_SUCCEED;
}

STATE CMOBFile::Puts(MOBFile* _file, char* _buf)
{
	if (feof(_file->m_file))
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "File Error!! Function is %s\n", _MOBFILE_FUNCTION_PUTS_);
		return MOB_FAILED;
	}

	fputs(_buf, _file->m_file);

	this->Flush(_file);
	return MOB_SUCCEED;
}

int CMOBFile::Read(MOBFile* _file, char* _buf, int _bufSize)
{
	if (feof(_file->m_file))
	{
		//MOB_DEBUG(MOB_LAYER_PLATFORM, "File Error!! Function is %s\n", _MOBFILE_FUNCTION_GETS_);
		return MOB_FAILURE;
	}

	fseek(_file->m_file, (long)_file->m_ptr, SEEK_SET);
	int length = fread(_buf, 1, _bufSize, _file->m_file);
	_file->m_ptr += length;
	return length;
}

STATE CMOBFile::Write(MOBFile* _file, char* _buf, int _size)
{
	if (feof(_file->m_file))
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "File Error!! Function is %s\n", _MOBFILE_FUNCTION_PUTS_);
		return MOB_FAILED;
	}

	fwrite(_buf, 1, _size, _file->m_file);

	this->Flush(_file);
	return MOB_SUCCEED;
}

STATE CMOBFile::Flush(MOBFile* _file)
{
	if (feof(_file->m_file))
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "File Error!! Function is %s\n", _MOBFILE_FUNCTION_FLUSH_);
		return MOB_FAILED;
	}

	fflush(_file->m_file);
	return MOB_SUCCEED;
}

STATE CMOBFile::FileClose(MOBFile* _file)
{
	if (_file->m_file == 0x00)
	{
		return MOB_FAILED;
	}

	fclose(_file->m_file);
	return MOB_SUCCEED;
}