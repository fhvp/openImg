
/*
* MOBLayer.h
*
*  Created on: 2015. 10. 26.
*      Author: jghan
*/

#ifndef __2015_10_21_MOBCLASS_H__
#define __2015_10_21_MOBCLASS_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBPlatform.h"
#include "MOBLayer.h"

/**********************************************************
* class
**********************************************************/
class CMOBPrimitive
{
	//Variable
private:
protected:
public:

	//Variable
private:
protected:
public:
	CMOBPrimitive();
	virtual ~CMOBPrimitive();

	virtual void release();
	virtual u16 Encode(char* _dataBlock);
	virtual u16 Decode(char* _dataBlock);
};

class CMOBClass : public CMOBPlatform
{
	//Variable
private:
	static CMOBClass*			m_instance;
	LAYER						m_platformID;
protected:
public:

	//Variable
private:
protected:
public:
	CMOBClass();
	virtual ~CMOBClass();

	virtual STATE INIT();
	static CMOBClass* Instance();

	virtual STATE open();
	virtual LAYER PlatformID() { return m_platformID; }
	virtual void PlatformID(LAYER _platformID) { m_platformID = _platformID; }
};

#endif __2015_10_21_MOBCLASS_H__