// TextInput.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "openImg.h"
#include "TextInputDlg.h"
#include "afxdialogex.h"

#include "openImgDlg.h"
#include "TextFontDlg.h"
#include "TextManager.h"
#include "Resource.h"

// CTextInputDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTextInputDlg, CDialogEx)

CTextInputDlg::CTextInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextInputDlg::IDD, pParent)
{

}

CTextInputDlg::~CTextInputDlg()
{
}

void CTextInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_INPUT_EDIT, m_editInputText);
}


BEGIN_MESSAGE_MAP(CTextInputDlg, CDialogEx)
	ON_MESSAGE(MSG_SET_INPUT_FONT, &CTextInputDlg::OnSetFont)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CTextInputDlg 메시지 처리기입니다.

typedef BOOL(WINAPI *SetLayer)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

BOOL CTextInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//자신의 hWnd를 Font에게 알려주어 서로 통신 할 수 있도록 길을 엽니다.
	if (this->m_hWnd != NULL)
	{
		::PostMessage(CopenImgDlg::Instance()->GetTextFontDlg()->m_hWnd, MSG_CALL_INPUT_DLG, 0, (LPARAM)this->m_hWnd);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CTextInputDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (this->m_hWnd != NULL)
			{
				RECT rect;
				CString string;
				GetClientRect(&rect);
				
				this->m_editInputText.GetWindowText(string);
				this->m_editInputText.SetSel(-1, -1);
				GetDlgItem(IDC_TEXT_INPUT_EDIT)->SendMessage(WM_KILLFOCUS, NULL);
				//CopenImgDlg::Instance()->m_textManager->CapturedDialog(::GetDC(this->m_hWnd), rect.right, rect.bottom);
				CopenImgDlg::Instance()->m_textManager->CapturedDialog(string, this->m_editInputText.GetFont(), rect.right, rect.bottom);

				CopenImgDlg::Instance()->SendMessage(MSG_TEXT_INPUT, 0, 0);
			}
			pMsg->wParam = VK_ESCAPE;
			//return TRUE;
			break;
		case VK_ESCAPE:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

LRESULT CTextInputDlg::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	//if (lParam != NULL)
	//{
	//	this->m_editInputText.SetFont(((CFont*)lParam), 1);
	//	this->m_editInputText.SetFocus();
	//}
	
	if (wParam != NULL)
	{
		COLORREF currentColor;

		currentColor = (COLORREF)wParam;

		CHARFORMAT* cFormat = (CHARFORMAT*)lParam;

		//this->m_editInputText.GetSelectionCharFormat(cFormat);

		//cFormat.dwMask = CFM_COLOR;
		//cFormat.dwEffects = NULL;
		//cFormat.crTextColor = currentColor;

		this->m_editInputText.SetSelectionCharFormat(*cFormat/*cFormat*/);
	}

	return TRUE;
}

void CTextInputDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CTextInputDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CTextInputDlg::OnMove(int x, int y)
{
	CopenImgDlg::Instance()->SendMessage(MSG_MOVE_INPUT_TEXT_BOX, (WPARAM)x, (LPARAM)y);
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
