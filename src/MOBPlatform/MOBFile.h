/*
* MOBFile.h
*
*  Created on: 2015. 9. 17.
*      Author: jghan
*/

#ifndef __2015_11_04_MOBFILE_H__
#define __2015_11_04_MOBFILE_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBPlatform.h"
#include <stdio.h>

/**********************************************************
* Define
**********************************************************/
#define MOB_FILE_READ_ONLY					"r"
#define MOB_FILE_WRITE_ONLY					"w"
#define MOB_FILE_APPEND						"a"
#define MOB_FILE_READ						"r+"
#define MOB_FILE_WRITE						"w+"
#define MOB_FILE_TEXT						"t"
#define MOB_FILE_BINARY						"b"
#define MOB_FILE_WRITE_BINARY				"wb"
#define MOB_FILE_READ_BINARY				"rb"

#define _MOBFILE_FUNCTION_GETS_				"Gets(char* _buf, u32 _bufSize, MOBFile* _file)"
#define _MOBFILE_FUNCTION_PUTS_				"Puts(MOBFile* _file, char* _buf)"
#define _MOBFILE_FUNCTION_FILEOPEN_			"FileOpen(char* _path, char* _fileName, char* _openType)"
#define _MOBFILE_FUNCTION_FILECLOSE_		"FileClose"
#define _MOBFILE_FUNCTION_FLUSH_			"Flush"
/**********************************************************
* Structure
**********************************************************/
typedef struct  
{
	char						m_fileName[256];
	FILE*						m_file;
	unsigned long long			m_ptr;
}MOBFile;

/**********************************************************
* Class
**********************************************************/
class CMOBFile : CMOBPlatform
{
	//Variable
private:
	static CMOBFile*			m_instance;
protected:
public:

	//Function
private:
protected:
	CMOBFile();
	virtual ~CMOBFile();
public:
	virtual STATE INIT();
	static CMOBFile* Instance();

	MOBFile* FileOpen(char* _path, char* _fileName, char* _openType);
	MOBFile* FileOpen(char* _fileName, char* _openType);
	STATE FileOpen(MOBFile* _mFile, char* _openType);

	STATE Gets(char* _buf, u32 _bufSize, MOBFile* _file);
	STATE Puts(MOBFile* _file, char* _buf);

	int Read(MOBFile* _file, char* _buf, int _bufSize);
	STATE Write(MOBFile* _file, char* _buf, int _size);

	STATE FileClose(MOBFile* _file);

	STATE Flush(MOBFile* _file);
};

#endif __2015_11_04_MOBFILE_H__