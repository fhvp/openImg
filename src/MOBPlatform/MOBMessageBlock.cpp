
/**********************************************************
* Include
**********************************************************/
#include "MOBMessageBlock.h"
#include "MOBClass.h"

#include <string.h>

/**********************************************************
* Global Variable
**********************************************************/

/**********************************************************
* Define Variable
**********************************************************/

/**********************************************************
* CDataBlock
**********************************************************/
CDataBlock::CDataBlock()
{
	this->m_dataBlockType = 0x00;
	this->m_rd_ptr = 0x00;
	this->m_wr_ptr = 0x00;
}

CDataBlock::~CDataBlock()
{
	this->m_dataBlockType = 0x00;
	this->m_rd_ptr = 0x00;
	this->m_wr_ptr = 0x00;
}

int CDataBlock::type()
{
	return this->m_dataBlockType;
}

void CDataBlock::type(int _type)
{
	this->m_dataBlockType = _type;
}

char* CDataBlock::rd_ptr()
{
	return 0x00;
}

void CDataBlock::rd_ptr(int _size)
{

}

char* CDataBlock::wr_ptr()
{
	return 0x00;
}

void CDataBlock::wr_ptr(int _size)
{

}

void CDataBlock::reset()
{
	this->m_rd_ptr = 0x00;
	this->m_wr_ptr = 0x00;
}

int CDataBlock::space()
{
	return 0x00;
}

void CDataBlock::free()
{
	
}

/**********************************************************
* CData
**********************************************************/
CData::CData()
{
	memset(this->m_data, 0x00, MESSAGE_BLOCK_SIZE_DATA);
	this->m_dataBlockType = MESSAGE_BLOCK_SIZE_DATA;
	this->reset();
}

CData::~CData()
{
	this->m_dataBlockType = 0x00;
}

void CData::free()
{
	delete this;
}

/**********************************************************
* CIp
**********************************************************/
CIp::CIp()
{
	memset(this->m_data, 0x00, MESSAGE_BLOCK_SIZE_IP);
	this->m_dataBlockType = MESSAGE_BLOCK_IP;
	this->reset();
}

CIp::~CIp()
{
	this->m_dataBlockType = 0x00;
}

void CIp::free()
{
	delete this;
}

/**********************************************************
* CMOBDataBlock
**********************************************************/
CMOBDataBlock::CMOBDataBlock(int _type)
{
	switch (_type)
	{
	case MESSAGE_BLOCK_DATA:
		this->m_data = new CData();
		break;
	case MESSAGE_BLOCK_IP:
		this->m_data = new CIp();
		break;
	default:
		break;
	}

	this->m_type = _type;
	this->m_allocation = MOB_SUCCESS;
}

CMOBDataBlock::~CMOBDataBlock()
{
	//if (this->m_allocation == MOB_SUCCEED)
	//	SAFE_DELETE(this->GetDataBlock());

	this->m_type = 0x00;
	this->m_allocation = 0x00;
}

void CMOBDataBlock::free()
{
	if (this->m_allocation == MOB_SUCCESS)
	{
		this->m_data->free();
	}

	this->m_allocation = 0x00;
}

/**********************************************************
* CMOBMessageBlock
**********************************************************/
CMOBMessageBlock::CMOBMessageBlock(int _type /*= MESSAGE_BLOCK_DATA*/)
{
	this->m_dataBlock = 0x00;
	this->m_prim = 0x00;

	this->m_dataBlock = new CMOBDataBlock(_type);
	this->m_allocation = MOB_SUCCESS;
	this->m_srcLayer = LAYER::MOB_LAYER_NONE;

	this->m_next = 0x00;
	this->m_prev = 0x00;
	this->m_cont = 0x00;
	this->m_referenceCount = 0x00;
}

CMOBMessageBlock::~CMOBMessageBlock()
{
	//this->free();

	this->m_dataBlock = 0x00;
	this->m_prim = 0x00;

	this->m_next = 0x00;
	this->m_prev = 0x00;
	this->m_cont = 0x00;
	this->m_referenceCount = 0x00;
}

MOBMessageBlock* CMOBMessageBlock::Alloc(int _type /*= MESSAGE_BLOCK_DATA*/)
{
	CMOBMessageBlock* mb = new CMOBMessageBlock(_type);

	//mb->m_dataBlock = new CMOBDataBlock(_type);
	
	return mb;
}

void CMOBMessageBlock::setlayer(LAYER _layer)
{
	this->m_srcLayer = _layer;
}

LAYER CMOBMessageBlock::getlayer()
{
	return this->m_srcLayer;
}

void CMOBMessageBlock::free()
{
	if (this->m_referenceCount != 0x00)
	{
		return;
	}

	if (this->m_allocation == MOB_SUCCESS)
	{
		this->m_dataBlock->free();
		SAFE_DELETE(this->m_dataBlock);
	}

	this->m_allocation = 0x00;
	delete this;
}

char* CMOBMessageBlock::rd_ptr()
{
	switch(this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		return ((CData*)this->m_dataBlock->m_data)->rd_ptr();
	case MESSAGE_BLOCK_IP:
		return ((CIp*)this->m_dataBlock->m_data)->rd_ptr();
	default:
		return MOB_FAILURE;
	}
}

void CMOBMessageBlock::rd_ptr(int _size)
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		((CData*)this->m_dataBlock->m_data)->rd_ptr(_size);
		break;
	case MESSAGE_BLOCK_IP:
		((CIp*)this->m_dataBlock->m_data)->rd_ptr(_size);
		break;
	default:
		break;
	}
}

char* CMOBMessageBlock::wr_ptr()
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		return ((CData*)this->m_dataBlock->m_data)->wr_ptr();
	case MESSAGE_BLOCK_IP:
		return ((CIp*)this->m_dataBlock->m_data)->wr_ptr();
	default:
		return MOB_FAILURE;
	}
}

void CMOBMessageBlock::wr_ptr(int _size)
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		((CData*)this->m_dataBlock->m_data)->wr_ptr(_size);
		break;
	case MESSAGE_BLOCK_IP:
		((CIp*)this->m_dataBlock->m_data)->wr_ptr(_size);
		break;
	default:
		break;
	}
}

int CMOBMessageBlock::size()
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		return ((CData*)this->m_dataBlock->m_data)->size();
	case MESSAGE_BLOCK_IP:
		return ((CIp*)this->m_dataBlock->m_data)->size();
	default:
		return MOB_FAILURE;
	}
}

void CMOBMessageBlock::size(int _size)
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		((CData*)this->m_dataBlock->m_data)->size(_size);
		break;
	case MESSAGE_BLOCK_IP:
		((CIp*)this->m_dataBlock->m_data)->size(_size);
		break;
	default:
		break;
	}
}

int CMOBMessageBlock::space()
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		return ((CData*)this->m_dataBlock->m_data)->space();
	case MESSAGE_BLOCK_IP:
		return ((CIp*)this->m_dataBlock->m_data)->space();
	default:
		return MOB_FAILURE;
	}
}

void CMOBMessageBlock::copy(const char* _data, int _size)
{
	switch (this->m_dataBlock->GetType())
	{
	case MESSAGE_BLOCK_DATA:
		memcpy(((CData*)this->m_dataBlock->m_data)->wr_ptr(), _data, _size);
		((CData*)this->m_dataBlock->m_data)->wr_ptr(_size);
		break;
	case MESSAGE_BLOCK_IP:
		memcpy(((CIp*)this->m_dataBlock->m_data)->wr_ptr(), _data, _size);
		((CIp*)this->m_dataBlock->m_data)->wr_ptr(_size);
		break;
	default:
		break;
	}
}

CMOBMessageBlock* CMOBMessageBlock::next()
{
	return this->m_next;
}

void CMOBMessageBlock::next(CMOBMessageBlock* _mMB)
{
	this->m_next = _mMB;
}

CMOBMessageBlock* CMOBMessageBlock::prev()
{
	return this->m_prev;
}

void CMOBMessageBlock::prev(CMOBMessageBlock* _mMB)
{
	this->m_prev = _mMB;
}

CMOBMessageBlock* CMOBMessageBlock::cont()
{
	return this->m_cont;
}

void CMOBMessageBlock::cont(CMOBMessageBlock* _mMB)
{
	this->m_cont = _mMB;
}

bool CMOBMessageBlock::is_reference()
{
	if (this->m_referenceCount == 0x00)
		return false;
	return true;
}

MOBMessageBlock& CMOBMessageBlock::operator = (const MOBMessageBlock& _srcMB)
{
	this->m_prim = _srcMB.m_prim;
	this->m_dataBlock = _srcMB.m_dataBlock;

	return *this;
}
