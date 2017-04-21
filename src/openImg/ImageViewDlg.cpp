// ImageViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "openImg.h"
#include "ImageViewDlg.h"
#include "afxdialogex.h"
#include "BitmapManager.h"

// CImageViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageViewDlg, CDialogEx)

CImageViewDlg::CImageViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageViewDlg::IDD, pParent)
{
	this->m_size.x = 0x00;
	this->m_size.y = 0x00;

	this->m_hBitmap = NULL;
	memset(&this->m_bitmapInfo, 0x00, sizeof(BITMAPINFO));
	this->m_pBitmap = NULL;
}

CImageViewDlg::~CImageViewDlg()
{

}

void CImageViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageViewDlg, CDialogEx)

END_MESSAGE_MAP()


// CImageViewDlg 메시지 처리기입니다.
void CImageViewDlg::SetSize(int _sizeX, int _sizeY)
{
	int nCaption = GetSystemMetrics(SM_CYCAPTION);
	int nCxdge = GetSystemMetrics(SM_CXEDGE);
	int nCyedge = GetSystemMetrics(SM_CYEDGE);

	this->m_size.x = _sizeX;
	this->m_size.y = _sizeY;

	this->m_windowSize.x = _sizeX + nCxdge * 2;
	this->m_windowSize.y = _sizeY + nCaption + nCyedge * 2;

	this->SetWindowPos(NULL, 0, 0, this->m_windowSize.x, this->m_windowSize.y, SWP_NOMOVE);
}

STATE CImageViewDlg::SetImgName(const char* _name)
{
	if (_name == 0x00)
		return MOB_FAILED;

	this->m_name = _name;

	this->SetWindowTextW(this->m_name);

	return MOB_SUCCEED;
}

STATE CImageViewDlg::MakeBitmap()
{
	if (this->GetSafeHwnd() == NULL)
		return MOB_FAILED;

	this->m_pBitmap = CBitmapManager::Instance()->MakeBitMap(::GetDC(this->GetSafeHwnd()), &this->m_hBitmap, &this->m_bitmapInfo, this->m_size.x, this->m_size.y);
	if (this->m_pBitmap == NULL)
	{
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}

void CImageViewDlg::ShowImage(BYTE* _matData, int _channels /*= 3*/)
{
	if (_matData == NULL)
		return;

	UCHAR* data = this->m_pBitmap;
	int length = this->m_size.x * this->m_size.y * _channels;

	for (int index = 0x00; index < length; index += _channels)
	{
		data[index + 0] = _matData[index + 0];
		data[index + 1] = _matData[index + 1];
		data[index + 2] = _matData[index + 2];
	}

	this->GetDC()->SetStretchBltMode(COLORONCOLOR);

	::StretchDIBits(::GetDC(this->GetSafeHwnd()), 0, 0, this->m_size.x, this->m_size.y, 0, 0, this->m_size.x, this->m_size.y, this->m_pBitmap, &this->m_bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}