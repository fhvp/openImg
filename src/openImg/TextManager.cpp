
#include "stdafx.h"
#include "resource.h"
#include "TextManager.h"
#include "MOBPlatform.h"

CTextManager::CTextManager(int _x, int _y)
{
	this->m_hBitmap = NULL;
	this->m_hDC = CreateCompatibleDC(NULL);

	this->m_state = CLASS_STATE_RUN;

	if (MakeBitMap(_x, _y) == MOB_FAILED)
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
	
	if (MakeBitMap(this->m_size.x, this->m_size.y) == MOB_FAILED)
	{
		//Error
		this->m_state = CLASS_STATE_ERROR;
	}
}

STATE CTextManager::MakeBitMap(int _x, int _y)
{
	if (this->m_state == CLASS_STATE_ERROR)
		return MOB_FAILED;

	memset(&this->m_bitmapInfo, 0x00, sizeof(BITMAPINFO));
	this->m_bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->m_bitmapInfo.bmiHeader.biWidth = _x;
	this->m_bitmapInfo.bmiHeader.biHeight = (-_y);		//flip 비트맵 뒤집어지는 효과
	this->m_bitmapInfo.bmiHeader.biPlanes = 1;
	this->m_bitmapInfo.bmiHeader.biBitCount = 24;
	this->m_bitmapInfo.bmiHeader.biCompression = BI_RGB;
	this->m_bitmapInfo.bmiHeader.biSizeImage = (((_x * 24 + 31) & ~31) >> 3) * _y;
	this->m_bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	this->m_bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	this->m_bitmapInfo.bmiHeader.biClrImportant = 0;
	this->m_bitmapInfo.bmiHeader.biClrUsed = 0;

	this->m_hBitmap = ::CreateDIBSection(this->m_hDC, &this->m_bitmapInfo, DIB_RGB_COLORS, (void**)&this->m_pBitmap, NULL, 0);
	
	if (this->m_hBitmap == NULL)
	{
		AfxMessageBox(_T("Text를 만드는데 실패하였습니다."));
		return MOB_FAILED;
	}

	SelectObject(this->m_hDC, this->m_hBitmap);

	return MOB_SUCCEED;
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

void CTextManager::SetTextInputBoxPoint(int _bitmapX, int _bitmapY)
{
	this->m_originInputPoint.x = _bitmapX;
	this->m_originInputPoint.y = _bitmapY;
}

void CTextManager::MoveTextInputBoxPoint(int _screenX, int _screenY)
{
	this->m_originInputPoint.x = _screenX - this->m_bitmap0Point.x;
	this->m_originInputPoint.y = _screenY - this->m_bitmap0Point.y;
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

		//CFont* oldFont = (CFont*)SelectObject(this->m_hDC, _font);
		//COLORREF oldColor = SetTextColor(this->m_hDC, RGB(255, 0, 0));

		CFont* oldFont = pDC->SelectObject(_font);

		SetBkMode(this->m_hDC, TRANSPARENT);
		pDC->SetTextColor(RGB(255, 0, 0));
		DrawText(this->m_hDC, _string, -1, &rect, DT_LEFT);


		//Reset Font
		//SelectObject(this->m_hDC, oldFont);
		//SetTextColor(this->m_hDC, oldColor);
	}
}

