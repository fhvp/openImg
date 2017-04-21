
#include "stdafx.h"
#include "resource.h"
#include "TextManager.h"
#include "MOBPlatform.h"
#include "BitmapManager.h"


CTextManager::CTextManager(int _x, int _y)
{
	this->m_hBitmap = NULL;
	this->m_hDC = CreateCompatibleDC(NULL);

	this->m_state = CLASS_STATE_RUN;

	this->m_pBitmap = CBitmapManager::Instance()->MakeBitMap(this->m_hDC, &this->m_hBitmap, &this->m_bitmapInfo, _x, _y);
	if (this->m_pBitmap == NULL)
	{
		//Error
		this->m_state = CLASS_STATE_ERROR;
	}

	this->m_size.x = _x;
	this->m_size.y = _y;
	this->m_bitmap0Point.x = 0x00;
	this->m_bitmap0Point.y = 0x00;
	this->m_originInputPoint.x = 0x00;
	this->m_originInputPoint.y = 0x00;
}

CTextManager::~CTextManager()
{
	this->DeleteALL();

	this->m_state = CLASS_STATE_ERROR;
}

void CTextManager::Initialize()
{
	DeleteObject(this->m_hBitmap);
	
	this->m_pBitmap = CBitmapManager::Instance()->MakeBitMap(this->m_hDC, &this->m_hBitmap, &this->m_bitmapInfo, this->m_size.x, this->m_size.y);
	if (this->m_pBitmap == NULL)
	{
		//Error
		this->m_state = CLASS_STATE_ERROR;
	}
}

HDC CTextManager::GetDC()
{
	if (this->m_state == CLASS_STATE_RUN)
		return this->m_hDC;

	return MOB_FAILURE;
}

void* CTextManager::GetBitmap()
{
	if (this->m_state == CLASS_STATE_RUN)
		return this->m_pBitmap;

	return MOB_FAILURE;
}

STATE CTextManager::DeleteALL()
{
	if (this->m_hBitmap != NULL)
		DeleteObject(this->m_hBitmap);

	if (this->m_state == CLASS_STATE_RUN)
		DeleteDC(this->m_hDC);

	this->m_hDC = NULL;

	return MOB_SUCCEED;
}

void CTextManager::SetBitmapWindowPoint(int _bitmapX_0, int _bitmapY_0)
{
	this->m_bitmap0Point.x = _bitmapX_0;
	this->m_bitmap0Point.y = _bitmapY_0;
}

//void CTextManager::SetTextInputBoxPoint(int _bitmapX, int _bitmapY)
//{
//	this->m_originInputPoint.x = _bitmapX;
//	this->m_originInputPoint.y = _bitmapY;
//}

void CTextManager::MoveTextInputBoxPoint(int _screenX, int _screenY)
{
	this->m_originInputPoint.x = _screenX;// - this->m_bitmap0Point.x;
	this->m_originInputPoint.y = _screenY;// - this->m_bitmap0Point.y;
}

POINT CTextManager::GetTextInputBoxPoint()
{
	return this->m_originInputPoint;
}

POINT CTextManager::GetSize()
{
	return this->m_size;
}

void CTextManager::CapturedDialog(HDC _hdc, int _x, int _y)
{
	//Captured
	::BitBlt(this->m_hDC, this->m_originInputPoint.x, this->m_originInputPoint.y, _x, _y, _hdc, 0, 0, SRCCOPY);
}

void CTextManager::CapturedDialog(CString _string, CFont* _font, int _x, int _y)
{
	if (_string.GetLength())
	{
		CDC* pDC = CDC::FromHandle(this->m_hDC);
		CRect rect(this->m_originInputPoint.x + 4, this->m_originInputPoint.y + 5, this->m_originInputPoint.x + _x - 2, this->m_originInputPoint.y + _y - 2);

		CFont* oldFont = pDC->SelectObject(_font);

		SetBkMode(this->m_hDC, TRANSPARENT);
		COLORREF oldColor = pDC->SetTextColor(RGB(255, 0, 0));
		DrawText(this->m_hDC, _string, -1, &rect, DT_LEFT);

		//Reset Font
		SelectObject(this->m_hDC, oldFont);
		SetTextColor(this->m_hDC, oldColor);
	}
}

