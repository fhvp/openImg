
/**********************************************************
* Include
**********************************************************/
#include "stdafx.h"
#include "MOBFont.h"

/**********************************************************
* Static Variable & Function
**********************************************************/
CMOBFont* CMOBFont::m_instance = 0x00;

CMOBFont* CMOBFont::Instance()
{
	if (CMOBFont::m_instance == 0x00)
		CMOBFont::m_instance = new CMOBFont();
	return CMOBFont::m_instance;
}

/**********************************************************
* CMOBFont Class Function
**********************************************************/
CMOBFont::CMOBFont()
{
	this->INIT();
}

CMOBFont::~CMOBFont()
{
	this->m_titleFont.DeleteObject();
	this->m_bodyFont.DeleteObject();
}

void CMOBFont::INIT()
{
	//Title
#ifdef _UNICODE
	this->m_titleFont.CreateFontW(
#else _UNICODE
	this->m_titleFont.CreateFontA(
#endif _UNICODE
		16,						// ���ڳ���
		9,						// ���ڳʺ�
		0,						// ��°���
		0,						// ���� �������ǰ���
		FW_HEAVY,				// ���ڱ���
		FALSE,					// Italic ���뿩��
		FALSE,					// �������뿩��
		FALSE,					// ��Ҽ����뿩��
		DEFAULT_CHARSET,		// ���ڼ�����
		OUT_DEFAULT_PRECIS,		// ������е�
		CLIP_DEFAULT_PRECIS,	// Ŭ�������е�
		DEFAULT_QUALITY,		// ��¹���ǰ��
		DEFAULT_PITCH,			// �۲�Pitch
		_T("����ü")			// �۲�
	);

	// Body

#ifdef _UNICODE
	this->m_bodyFont.CreateFontW(
#else _UNICODE
	this->m_bodyFont.CreateFontA(
#endif _UNICODE
		15,						// ���ڳ���
		8,						// ���ڳʺ�
		0,						// ��°���
		0,						// ���� �������ǰ���
		FW_NORMAL,				// ���ڱ���
		FALSE,					// Italic ���뿩��
		FALSE,					// �������뿩��
		FALSE,					// ��Ҽ����뿩��
		DEFAULT_CHARSET,		// ���ڼ�����
		OUT_DEFAULT_PRECIS,		// ������е�
		CLIP_DEFAULT_PRECIS,	// Ŭ�������е�
		DEFAULT_QUALITY,		// ��¹���ǰ��
		DEFAULT_PITCH,			// �۲�Pitch
		_T("����ü")			// �۲�
	);

}

CFont* CMOBFont::GetTitleFont()
{
	return &this->m_titleFont;
}


CFont* CMOBFont::GetBodyFont()
{
	return &this->m_bodyFont;
}