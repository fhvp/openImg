

#ifndef __IMAGE_VIEW_DLG_H__
#define __IMAGE_VIEW_DLG_H__

#include "MOBDefs.h"
#include "Resource.h"
// CImageViewDlg 대화 상자입니다.

class CImageViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageViewDlg)
private:
protected:
	CString						m_name;

	POINT						m_size;
	POINT						m_windowSize;

	//Bitmap Image
	HBITMAP						m_hBitmap;
	BITMAPINFO					m_bitmapInfo;
public:
	BYTE*						m_pBitmap;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMAGE_VIEW };



private:
protected:
public:
	CImageViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageViewDlg();

	void SetSize(int _sizeX, int _sizeY);
	STATE SetImgName(const char* _name);
	STATE MakeBitmap();

	void ShowImage(BYTE* _matData, int _channels = 3);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
};

#endif /*__IMAGE_VIEW_DLG_H__*/