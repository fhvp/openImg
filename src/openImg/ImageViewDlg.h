

#ifndef __IMAGE_VIEW_DLG_H__
#define __IMAGE_VIEW_DLG_H__

#include "MOBDefs.h"
#include "Resource.h"
// CImageViewDlg ��ȭ �����Դϴ�.

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
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IMAGE_VIEW };



private:
protected:
public:
	CImageViewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageViewDlg();

	void SetSize(int _sizeX, int _sizeY);
	STATE SetImgName(const char* _name);
	STATE MakeBitmap();

	void ShowImage(BYTE* _matData, int _channels = 3);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
};

#endif /*__IMAGE_VIEW_DLG_H__*/