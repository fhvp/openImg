
/**********************************************************
* Include
**********************************************************/
#include "MOBList.h"
#include "MOBLayer.h"
#include "MOBLogger.h"

/**********************************************************
* ListItem
**********************************************************/
ListItem::ListItem()
{

}

ListItem::~ListItem()
{

}

/**********************************************************
* Default CMOBList Function
**********************************************************/
CMOBList::CMOBList()
{

}

CMOBList::~CMOBList()
{

}

STATE CMOBList::INIT()
{
	return MOB_SUCCEED;
}

/**********************************************************
* CMOBList Function
**********************************************************/
ListItem* CMOBList::Find(u16 _index)
{
// 	std::list<ListItem*>::iterator iter;
// 	ListItem* item;
// 	for (iter = this->m_list.begin(); iter != this->m_list.end(); ++iter)
// 	{
// 		item = *iter;
// 
// 		if (item->m_index == _index)
// 		{
// 			return item;
// 		}
// 	}
	return MOB_FAILURE;
}

void CMOBList::Insert(ListItem* _data)
{
	//this->m_list.push_back(_data);
}

STATE CMOBList::Delete(u16 _index)
{
// 	std::list<ListItem*>::iterator iter;
// 	ListItem* item;
// 	for (iter = this->m_list.begin(); iter != this->m_list.end(); ++iter)
// 	{
// 		item = *iter;
// 
// 		if (item->m_index == _index)
// 		{
// 			m_list.remove(item);
// 			return MOB_SUCCEED;
// 		}
// 	}
// 
// 	MOB_DEBUG( MOB_LAYER_PLATFORM, "List Item Delete Failed!!\n" );
// 	return MOB_FAILED;
	return MOB_SUCCEED;
}