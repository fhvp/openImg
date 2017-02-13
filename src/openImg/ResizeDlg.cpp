// ResizeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "openImg.h"
#include "ResizeDlg.h"
#include "afxdialogex.h"


// CResizeDlg ��ȭ �����Դϴ�.

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


// CResizeDlg �޽��� ó�����Դϴ�.

void CResizeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	SetDlgItemInt(IDC_EDIT_COLS, this->m_cols);
	SetDlgItemInt(IDC_EDIT_ROWS, this->m_rows);
}

BOOL CResizeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	this->m_rows = GetDlgItemInt(IDC_EDIT_ROWS);
	this->m_cols = GetDlgItemInt(IDC_EDIT_COLS);

	CDialogEx::OnOK();
}
