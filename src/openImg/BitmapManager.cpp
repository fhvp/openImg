
#include "stdafx.h"
#include "BitmapManager.h"


CBitmapManager* CBitmapManager::m_instance = 0x00;

CBitmapManager* CBitmapManager::Instance()
{
	if (CBitmapManager::m_instance == NULL)
		CBitmapManager::m_instance = new CBitmapManager();
	return CBitmapManager::m_instance;
}

CBitmapManager::CBitmapManager()
{

}

CBitmapManager::~CBitmapManager()
{

}

BYTE* CBitmapManager::MakeBitMap(HDC _hDC, HBITMAP* _hBitmap, BITMAPINFO* _bitmapInfo, int _x, int _y)
{
	BYTE* pBitmap = 0x00;
	if (_bitmapInfo == NULL)
		return 0x00;

	memset(_bitmapInfo, 0x00, sizeof(BITMAPINFO));
	_bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_bitmapInfo->bmiHeader.biWidth = _x;
	_bitmapInfo->bmiHeader.biHeight = (-_y);		//flip 비트맵 뒤집어지는 효과
	_bitmapInfo->bmiHeader.biPlanes = 1;
	_bitmapInfo->bmiHeader.biBitCount = 24;
	_bitmapInfo->bmiHeader.biCompression = BI_RGB;
	_bitmapInfo->bmiHeader.biSizeImage = (((_x * 24 + 31) & ~31) >> 3) * _y;
	_bitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	_bitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	_bitmapInfo->bmiHeader.biClrImportant = 0;
	_bitmapInfo->bmiHeader.biClrUsed = 0;

	*_hBitmap = ::CreateDIBSection(_hDC, _bitmapInfo, DIB_RGB_COLORS, (void**)&pBitmap, NULL, 0);

	if (*_hBitmap == NULL)
	{
		AfxMessageBox(_T("Text를 만드는데 실패하였습니다."));
		return 0x00;
	}

	SelectObject(_hDC, *_hBitmap);

	return pBitmap;
}
