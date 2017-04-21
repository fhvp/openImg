
#ifndef __BITMAP_MANAGER_H__
#define __BITMAP_MANAGER_H__

#include "MOBDefs.h"


class CBitmapManager
{
private:
	static CBitmapManager*				m_instance;
protected:
public:

private:
protected:
	CBitmapManager();
public:
	static CBitmapManager* Instance();

	virtual ~CBitmapManager();

	BYTE* MakeBitMap(HDC _hDC, HBITMAP* _hBitmap, BITMAPINFO* _bitmapInfo, int _x, int _y);
};


#endif /*__BITMAP_MANAGER_H__*/
