// TextInput.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "openImg.h"
#include "TextInputDlg.h"
#include "afxdialogex.h"

#include "openImgDlg.h"
#include "TextFontDlg.h"
#include "TextManager.h"
#include "Resource.h"

// CTextInputDlg ��ȭ �����Դϴ�.

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


// CTextInputDlg �޽��� ó�����Դϴ�.


BOOL CTextInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//LONG lResult = SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	//if (!lResult)
	//{
	//	AfxMessageBox(L"�ؽ�Ʈ �ڽ� ����⿡ �����Ͽ����ϴ�.");
	//	return FALSE;
	//}

	//double alpha = 255;

	//SetLayeredWindowAttributes(RGB(255, 255, 255), alpha, LWA_COLORKEY | LWA_ALPHA);

	//this->m_editInputText.GetDC()->SetBkMode(TRANSPARENT);
	//this->m_editInputText.GetDC()->SelectStockObject(NULL_BRUSH);

	//�ڽ��� hWnd�� Font���� �˷��־� ���� ��� �� �� �ֵ��� ���� ���ϴ�.
	if (this->m_hWnd != NULL)
	{
		::PostMessage(CopenImgDlg::Instance()->GetTextFontDlg()->m_hWnd, MSG_CALL_INPUT_DLG, 0, (LPARAM)this->m_hWnd);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CTextInputDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
	if (lParam != NULL)
	{
		this->m_editInputText.SetFont(((CFont*)lParam), 1);
		this->m_editInputText.SetFocus();
	}

	return TRUE;
}

void CTextInputDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CTextInputDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//CopenImgDlg::Instance()->PostMessage(MSG_MOVE_INPUT_TEXT_BOX, 0, (LPARAM)&point);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CTextInputDlg::OnMove(int x, int y)
{
	CopenImgDlg::Instance()->PostMessage(MSG_MOVE_INPUT_TEXT_BOX, (WPARAM)x, (LPARAM)y);
	CDialogEx::OnMove(x, y);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
