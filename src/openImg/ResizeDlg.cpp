// ResizeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "openImg.h"
#include "ResizeDlg.h"
#include "afxdialogex.h"


// CResizeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CResizeDlg, CDialogEx)

CResizeDlg::CResizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResizeDlg::IDD, pParent)
{
	this->m_cols = 0x00;
	this->m_rows = 0x00;
	this->m_focus = 0x00;
}

CResizeDlg::~CResizeDlg()
{
}

void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COLS, m_editCols);
	DDX_Control(pDX, IDC_EDIT_ROWS, m_editRows);
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_EDIT_COLS, IDC_EDIT_ROWS, OnSetFocusEdit)

	ON_BN_CLICKED(IDOK, &CResizeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CResizeDlg 메시지 처리기입니다.

void CResizeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	SetDlgItemInt(IDC_EDIT_COLS, this->m_cols);
	SetDlgItemInt(IDC_EDIT_ROWS, this->m_rows);
}

BOOL CResizeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_KEYDOWN)
	{
		int ctrlId = GetFocus()->GetDlgCtrlID();

		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (ctrlId == IDC_EDIT_COLS)
			{
				this->m_editRows.SetFocus();
				//this->m_editRows.SetSel(0, -1, true);
				return true;
			}
			else if (ctrlId == IDC_EDIT_ROWS)
			{
				int newRows = GetDlgItemInt(IDC_EDIT_ROWS);
				if (newRows != this->m_rows)
				{
					this->m_focus = IDC_EDIT_COLS;
					OnSetFocusEdit(IDC_EDIT_ROWS);

					////Select All
					//((CEdit*)GetDlgItem(ctrlId))->SetFocus();
					//((CEdit*)GetDlgItem(ctrlId))->SetSel(0, -1, true);
					return true;
				}
			}
			break;
		}
	}

	//if (pMsg->message == WM_LBUTTONUP)
	//{
	//	int ctrlId = GetFocus()->GetDlgCtrlID();
	//	//Select All
	//	((CEdit*)GetDlgItem(ctrlId))->SetFocus();
	//	((CEdit*)GetDlgItem(ctrlId))->SetSel(0, -1, true);
	//}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CResizeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CResizeDlg::OnSetFocusEdit(UINT _parmCtrlId)
{
	int newRows = 0x00;
	int newCols = 0x00;
	double resize = 0.0;

	if (this->m_focus != _parmCtrlId)
	{
		newRows = GetDlgItemInt(IDC_EDIT_ROWS);
		newCols = GetDlgItemInt(IDC_EDIT_COLS);

		if (this->m_rows != newRows && newRows > 0x00)
		{
			resize = (double)(1 + (double)(newRows - this->m_rows) / this->m_rows);

			this->m_cols = round(this->m_cols * resize);
			this->m_rows = newRows;
		}
		else if (this->m_cols != newCols && newCols > 0x00)
		{
			resize = (double)(1 + (double)(newCols - this->m_cols) / this->m_cols);

			this->m_rows = round(this->m_rows * resize);
			this->m_cols = newCols;
		}

		SetDlgItemInt(IDC_EDIT_COLS, this->m_cols);
		SetDlgItemInt(IDC_EDIT_ROWS, this->m_rows);
		this->m_focus = _parmCtrlId;

		//Select All
		//((CEdit*)GetDlgItem(_parmCtrlId))->SetFocus();
		//((CEdit*)GetDlgItem(_parmCtrlId))->SetSel(0, -1, true);
	}
}

void CResizeDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	this->m_rows = GetDlgItemInt(IDC_EDIT_ROWS);
	this->m_cols = GetDlgItemInt(IDC_EDIT_COLS);

	CDialogEx::OnOK();
}
