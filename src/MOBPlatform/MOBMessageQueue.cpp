
/**********************************************************
* include
**********************************************************/
#include "MOBMessageQueue.h"

/**********************************************************
* CMOBMessageQueue Class Function
**********************************************************/
CMOBMessageQueue::CMOBMessageQueue()
{
	this->INIT();
}

CMOBMessageQueue::~CMOBMessageQueue()
{

}

STATE CMOBMessageQueue::INIT()
{
	return MOB_SUCCEED;
}

STATE CMOBMessageQueue::enqueue(CMOBMessageBlock* _newItem)
{
	if (_newItem == 0x00)
		return MOB_FAILED;

	this->m_tail = _newItem;

	if (this->m_head == 0x00) //New Item
		this->m_head = _newItem;
	else
	{
		//this->m_head
	}

	return MOB_SUCCEED;
}

STATE CMOBMessageQueue::dequeue()
{
	if (this->m_head == 0x00)
		return MOB_FAILED;

	if (this->m_head != 0x00)
	{
		MOBMessageBlock* mMB = this->m_head;

		this->m_head = mMB->next();
	}

	return MOB_SUCCEED;
}