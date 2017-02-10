/*
* MOBPath.h
*
*  Created on: 2015. 9. 17.
*      Author: jghan
*/

#ifndef __2015_10_15_MOBPATH_H__
#define __2015_10_15_MOBPATH_H__

#include "MOBPlatform.h"

enum WAY
{
	MOB_LEFT,
	MOB_RIGHT,
	MOB_TOP,
	MOB_BOTTOM
};

/**********************************************************
* Class
**********************************************************/
class CMOBPath : CMOBPlatform
{
//Variable
private:
	static CMOBPath*			m_instance;
protected:
public:

//Function
private:
protected:
	CMOBPath();
	virtual ~CMOBPath();

	char* cut(char* _buf, char* _split);
public:
	virtual STATE INIT();
	static CMOBPath* Instance();

	STATE GetPath(char* _buf);
	STATE GetPath(char* _buf, char* _split);
	PROPOSITION IsText(char* _buf, char* _text);
	STATE SetPath(char* _buf, char* _text);
	STATE SplitPath(char* _buf, char* _split, WAY _way = MOB_LEFT);
};

#endif __2015_10_15_MOBPATH_H__