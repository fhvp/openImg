
/**********************************************************
* Include
**********************************************************/
#include "stdafx.h"
#include "IplImageDB.h"


/**********************************************************
* Definition
**********************************************************/
#define DEFAULT_WIDTH			1024
#define DEFAULT_HIGHT			768

/**********************************************************
* Function
**********************************************************/
CIplImageDB::CIplImageDB()
{
	this->m_inImgIpl = NULL;
	this->m_outImgIpl = NULL;
	this->m_brightness = 1.0;
	this->m_contrast = 0x00;
	this->m_saturation = 0x00;
	this->m_isChanged = false;
	this->m_resize = 0.0;
}

CIplImageDB::~CIplImageDB()
{

}

void CIplImageDB::SetResize(int _width, int _height)
{
	double wResult = 0.0;
	double hResult = 0.0;

	if (_width > DEFAULT_WIDTH)
	{
		wResult = _width / DEFAULT_WIDTH;
	}

	if (_height > DEFAULT_HIGHT)
	{
		hResult = _height / DEFAULT_WIDTH;
	}

	this->m_resize = wResult >= hResult ? wResult : hResult;
}

void CIplImageDB::Clear()
{
	this->m_brightness = 1.0;
	this->m_contrast = 0x00;
	this->m_saturation = 0x00;
	this->m_isChanged = false;
}

void CIplImageDB::Delete()
{
	if (this->m_inImgIpl != NULL)
		cvReleaseImage(&this->m_inImgIpl);
	this->m_inImgIpl = NULL;

	if (this->m_outImgIpl != NULL)
		cvReleaseImage(&this->m_outImgIpl);
	this->m_outImgIpl = NULL;
}