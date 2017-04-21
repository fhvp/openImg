
#ifndef __TEXT_MANAGER_H__
#define __TEXT_MANAGER_H__

#include "afxwin.h"
#include "MOBDefs.h"

enum TextState {
	CLASS_STATE_ERROR = 0x00,
	CLASS_STATE_RUN
};

class CTextManager
{
private:
	HBITMAP						m_hBitmap;
protected:
	//Variable
	UCHAR						m_state;
	HDC							m_hDC;
	BITMAPINFO					m_bitmapInfo;
	BYTE*						m_pBitmap;

	BOOL						m_textMode;

	POINT						m_size;	//Bitmap Size
	POINT						m_bitmap0Point;	//Bitmap Zero Point
	POINT						m_originInputPoint;
public:
	

private:
protected:
	//STATE MakeBitMap(int _x, int _y);
public:
	CTextManager(int _x, int _y);
	~CTextManager();

	void Initialize();

	HDC GetDC();
	void* GetBitmap();

	STATE DeleteALL();
	void SetTextMode(BOOL _textMode) { this->m_textMode = _textMode; }
	BOOL GetTextMode() { return this->m_textMode; }

	void SetBitmapWindowPoint(int _bitmapX_0, int _bitmapY_0);

	//void SetTextInputBoxPoint(int _bitmapX, int _bitmapY);
	void MoveTextInputBoxPoint(int _screenX, int _screenY);
	POINT GetTextInputBoxPoint();

	POINT GetSize();
	

protected:
	

public:
	void CapturedDialog(HDC _hdc, int _x, int _y);
	void CapturedDialog(CString _string, CFont* _font, int _x, int _y);

};



#endif /*__TEXT_MANAGER_H__*/