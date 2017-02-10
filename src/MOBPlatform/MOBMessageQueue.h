
#ifndef __2016_02_03_MOB_MESSAGE_QUEUE_H__
#define __2016_02_03_MOB_MESSAGE_QUEUE_H__

/**********************************************************
* include
**********************************************************/
#include "MOBPlatform.h"
#include "MOBMessageBlock.h"

/**********************************************************
* include
**********************************************************/
class CMOBMessageQueue : public CMOBPlatform
{
private:
protected:
	CMOBMessageBlock*			m_head;
	CMOBMessageBlock*			m_tail;
	u16							m_numOfBlock;
public:

private:
protected:
public:
	CMOBMessageQueue();
	virtual ~CMOBMessageQueue();

	virtual STATE INIT();

	STATE enqueue(CMOBMessageBlock* _newItem);
	STATE dequeue();
};

#endif __2016_02_03_MOB_MESSAGE_QUEUE_H__