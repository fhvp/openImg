/*
* MOBLayer.h
*
*  Created on: 2015. 10. 22.
*      Author: jghan
*/

#ifndef __2015_10_21_MOBPLATFORM_H__
#define __2015_10_21_MOBPLATFORM_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBCommon.h"

/**********************************************************
* Define Variable
**********************************************************/
#ifndef SAFE_DELETE
#define SAFE_DELETE(_p)	{ if(_p != NULL){ delete _p; _p = NULL; } }
#endif

/**********************************************************
* Class
**********************************************************/
class CMOBPlatform
{
	//Variable
private:
protected:
public:

	//Function
private:
protected:
	CMOBPlatform();
	virtual ~CMOBPlatform();
public:
	virtual STATE INIT();
};

#endif __2015_10_21_MOBPLATFORM_H__