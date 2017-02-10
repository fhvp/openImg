/*
* MOBLayer.h
*
*  Created on: 2015. 10. 26.
*      Author: jghan
*/

#ifndef __2015_10_26_MOBMESSAGEBLOCK_H__
#define __2015_10_26_MOBMESSAGEBLOCK_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBLayer.h"

/**********************************************************
* Define Variable
**********************************************************/
#define MESSAGE_BLOCK_DATA						0
#define MESSAGE_BLOCK_IP						1


#define MESSAGE_BLOCK_SIZE_DATA					512
#define MESSAGE_BLOCK_SIZE_IP					1500


/**********************************************************
* CDataBlock
**********************************************************/
class CDataBlock
{
	//Variable
private:
protected:
	int											m_dataBlockType;
	int											m_rd_ptr;
	int											m_wr_ptr;
public:

	//Function
private:
protected:
	CDataBlock();
	virtual ~CDataBlock();
public:
	int type();
	void type(int _type);

	virtual char* rd_ptr();
	virtual void rd_ptr(int _size);
	virtual char* wr_ptr();
	virtual void wr_ptr(int _size);

	void reset();
	virtual int space();
	virtual void free();
};

/**********************************************************
* CData
**********************************************************/
class CData : public CDataBlock
{
	//Variable
private:
protected:
	char										m_data[MESSAGE_BLOCK_SIZE_DATA];
public:

	//Function
private:
protected:
	CData();
	virtual ~CData();
public:
	friend class CMOBDataBlock;

	char* rd_ptr() { return &this->m_data[this->m_rd_ptr]; }
	void rd_ptr(int _size) { this->m_rd_ptr = _size; }
	char* wr_ptr() { return &this->m_data[this->m_wr_ptr]; }
	void wr_ptr(int _size) { this->m_wr_ptr += _size; }

	int size() { return this->m_wr_ptr - this->m_rd_ptr; }
	void size(int _size) { this->m_wr_ptr += _size; }
	int space() { return MESSAGE_BLOCK_SIZE_DATA - this->m_wr_ptr; }
	virtual void free();
};

/**********************************************************
* CIp
**********************************************************/
class CIp : public CDataBlock
{
	//Variable
private:
protected:
	char										m_data[MESSAGE_BLOCK_SIZE_IP];
public:
	//Function
private:
protected:
	CIp();
	virtual ~CIp();
public:
	friend class CMOBDataBlock;
	
	char* rd_ptr() { return &this->m_data[this->m_rd_ptr]; }
	void rd_ptr(int _size) { this->m_rd_ptr = _size; }
	char* wr_ptr() { return &this->m_data[this->m_wr_ptr]; }
	void wr_ptr(int _size) { this->m_wr_ptr += _size; }

	int size() { return this->m_wr_ptr - this->m_rd_ptr; }
	void size(int _size) { this->m_wr_ptr += _size; }
	int space() { return MESSAGE_BLOCK_SIZE_IP - this->m_wr_ptr; }
	virtual void free();
};

/**********************************************************
* CMOBDataBlock
**********************************************************/
class CMOBDataBlock
{
	//Variable
private:
protected:
	int											m_type;
	CDataBlock*									m_data;
public:
	int											m_allocation;
	//Function
private:
protected:
	CMOBDataBlock(int _type);
	virtual ~CMOBDataBlock();
public:
	friend class CMOBMessageBlock;

	int GetType() { return this->m_type; }
	void free();
};

/**********************************************************
* CMOBMessageBlock
**********************************************************/
class CMOBPrimitive;
class CMOBMessageBlock;
typedef CMOBMessageBlock MOBMessageBlock;

class CMOBPrim;

class CMOBMessageBlock
{
	//Variable
private:
	int											m_referenceCount;
protected:
	CMOBDataBlock*								m_dataBlock;
	int											m_allocation;
	LAYER										m_srcLayer;

	CMOBMessageBlock*							m_next;
	CMOBMessageBlock*							m_prev;
	CMOBMessageBlock*							m_cont;
public:
	CMOBPrimitive*								m_prim;

	//Function
private:
protected:
public:
	CMOBMessageBlock(int _type = MESSAGE_BLOCK_DATA);
	virtual ~CMOBMessageBlock();

	static MOBMessageBlock* Alloc(int _type = MESSAGE_BLOCK_DATA);

	void setlayer(LAYER _layer);
	LAYER getlayer();

	void free();

	char* rd_ptr();
	void rd_ptr(int _size);

	char* wr_ptr();
	void wr_ptr(int _size);

	int size();
	void size(int _size);

	int space();

	void copy(const char* _data, int _size);

	CMOBMessageBlock* next();
	void next(CMOBMessageBlock* _mMB);
	CMOBMessageBlock* prev();
	void prev(CMOBMessageBlock* _mMB);

	CMOBMessageBlock* cont();
	void cont(CMOBMessageBlock* _mMB);

	bool is_reference();

	MOBMessageBlock& operator=(const MOBMessageBlock& _srcMB);
};

#endif __2015_10_26_MOBMESSAGEBLOCK_H__