
/**********************************************************
* Include
**********************************************************/
#include "MOBThread.h"

#include "MOBLayer.h"
#include "MOBLogger.h"

/**********************************************************
* Global Variable
**********************************************************/
CMOBThread* CMOBThread::m_instance = 0x00;

/**********************************************************
* Default CMOBThread Function
**********************************************************/
CMOBThread::CMOBThread()
{
	this->INIT();
	this->m_platformID = MOB_LAYER_NONE;
	this->m_threadState = THREAD_RUN;
}

CMOBThread::~CMOBThread()
{

}

STATE CMOBThread::INIT()
{
	return MOB_SUCCEED;
}

CMOBThread* CMOBThread::Instance()
{
	if (CMOBThread::m_instance == 0x00)
	{
		CMOBThread::m_instance = new CMOBThread();
	}
	return (CMOBThread*)CMOBThread::m_instance;
}

/**********************************************************
* CMOBThread Function
**********************************************************/
void CMOBThread::InitThread(int _priority /* = MOB_THREAD_PRIORITY_NORMAL*/)
{
	DWORD pThreadID;
	HANDLE pThread;

	pThread = CreateThread(NULL, 0, Thread_Service, this, 0, &pThreadID);

	if (pThread == NULL)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Make Thread!!!\n");
		return;
	}
	
	SetThreadPriority(pThread, _priority);
}

STATE CMOBThread::open()
{
	return MOB_SUCCEED;
}

STATE CMOBThread::run()
{
	return MOB_SUCCEED;
}

DWORD WINAPI CMOBThread::Thread_Service(LPVOID lParam)
{
	CMOBThread* This = (CMOBThread*)lParam;

	This->run();

	return 0x00;
}