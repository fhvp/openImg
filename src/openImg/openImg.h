
// openImg.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CopenImgApp:
// �� Ŭ������ ������ ���ؼ��� openImg.cpp�� �����Ͻʽÿ�.
//

class CopenImgApp : public CWinApp
{
public:
	CopenImgApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CopenImgApp theApp;