// MOBMFCPlatform.h : MOBMFCPlatform DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMOBMFCPlatformApp
// �� Ŭ������ ������ ������ MOBMFCPlatform.cpp�� �����Ͻʽÿ�.
//

class CMOBMFCPlatformApp : public CWinApp
{
public:
	CMOBMFCPlatformApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
