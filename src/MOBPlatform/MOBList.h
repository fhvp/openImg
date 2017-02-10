/*
* MOBLayer.h
*
*  Created on: 2015. 10. 21.
*      Author: jghan
*/

#ifndef __2015_10_21_MOBLIST_H__
#define __2015_10_21_MOBLIST_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBPlatform.h"
#include <list>

/**********************************************************
* Define Variable
**********************************************************/

/**********************************************************
* Class
**********************************************************/
class ListItem
{
	//Variable
private:
protected:
public:
	//u16								m_index;

	//Function
private:
protected:
public:
	ListItem();
	virtual ~ListItem();
};

//template <typename T>
class CMOBList : public CMOBPlatform
{
	//Variable
private:
protected:
public:
	//std::list<ListItem*>			m_list;

	//Function
private:
protected:
	CMOBList();
	virtual ~CMOBList();
public:
	virtual STATE INIT();
	static CMOBList* Instance();

	virtual ListItem* Find(u16 _index);
	virtual void Insert(ListItem* _data);
	virtual STATE Delete(u16 _index);
};

#endif __2015_10_21_MOBLIST_H__