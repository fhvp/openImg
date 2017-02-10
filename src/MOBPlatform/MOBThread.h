/*
* MOBLayer.h
*
*  Created on: 2015. 10. 21.
*      Author: jghan
*/

#ifndef __2015_10_21_MOBTHREAD_H__
#define __2015_10_21_MOBTHREAD_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBClass.h"
#include <windows.h>

/**********************************************************
* Define Variable
**********************************************************/
#define MOB_THREAD_PRIORITY_LOWEST			THREAD_PRIORITY_LOWEST
#define MOB_THREAD_PRIORITY_NORMAL			THREAD_PRIORITY_NORMAL
#define MOB_THREAD_PRIORITY_HIGHEST			THREAD_PRIORITY_HIGHEST


enum Thread_State
{
	THREAD_SLEEP =				0x00,
	THREAD_RUN =				0x01
};

/**********************************************************
* Class
**********************************************************/
class CMOBThread : public CMOBClass
{
	//Variable
private:
	static CMOBThread*			m_instance;
	LAYER						m_platformID;
protected:
	Thread_State				m_threadState;
public:

	//Function
private:
	static DWORD WINAPI Thread_Service(LPVOID lParam);
protected:
	CMOBThread();
	virtual ~CMOBThread();

	void InitThread(int _priority = MOB_THREAD_PRIORITY_NORMAL);
public:
	virtual STATE INIT();
	static CMOBThread* Instance();

	virtual STATE open();
	virtual STATE run();	//Thread Function
	virtual LAYER PlatformID() { return m_platformID; }
	virtual void PlatformID(LAYER _platformID) { m_platformID = _platformID; }
};

#endif __2015_10_21_MOBTHREAD_H__