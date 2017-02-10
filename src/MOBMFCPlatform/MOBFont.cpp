
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
		16,						// 글자높이
		9,						// 글자너비
		0,						// 출력각도
		0,						// 기준 선에서의각도
		FW_HEAVY,				// 글자굵기
		FALSE,					// Italic 적용여부
		FALSE,					// 밑줄적용여부
		FALSE,					// 취소선적용여부
		DEFAULT_CHARSET,		// 문자셋종류
		OUT_DEFAULT_PRECIS,		// 출력정밀도
		CLIP_DEFAULT_PRECIS,	// 클리핑정밀도
		DEFAULT_QUALITY,		// 출력문자품질
		DEFAULT_PITCH,			// 글꼴Pitch
		_T("굴림체")			// 글꼴
	);

	// Body

#ifdef _UNICODE
	this->m_bodyFont.CreateFontW(
#else _UNICODE
	this->m_bodyFont.CreateFontA(
#endif _UNICODE
		15,						// 글자높이
		8,						// 글자너비
		0,						// 출력각도
		0,						// 기준 선에서의각도
		FW_NORMAL,				// 글자굵기
		FALSE,					// Italic 적용여부
		FALSE,					// 밑줄적용여부
		FALSE,					// 취소선적용여부
		DEFAULT_CHARSET,		// 문자셋종류
		OUT_DEFAULT_PRECIS,		// 출력정밀도
		CLIP_DEFAULT_PRECIS,	// 클리핑정밀도
		DEFAULT_QUALITY,		// 출력문자품질
		DEFAULT_PITCH,			// 글꼴Pitch
		_T("굴림체")			// 글꼴
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