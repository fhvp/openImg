
/**********************************************************
* Include
**********************************************************/
#include "stdafx.h"
#include "IplImageDB.h"


/**********************************************************
* Function
**********************************************************/
CIplImageDB::CIplImageDB()
{
	//memset(this->m_path, 0x00, MAX_FILE_PATH);
	this->m_inImgIpl = NULL;
	this->m_outImgIpl = NULL;
	this->m_brightness = 1.0;
	this->m_contrast = 0x00;
	this->m_saturation = 0x00;
	this->m_isChanged = false;
}

CIplImageDB::~CIplImageDB()
{

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