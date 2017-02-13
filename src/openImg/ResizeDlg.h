#pragma once
#include "afxwin.h"


// CResizeDlg ��ȭ �����Դϴ�.

class CResizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResizeDlg)

public:
	CResizeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CResizeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RESIZE };

protected:
	CEdit			m_editCols;
	CEdit			m_editRows;
	UINT			m_focus;

public:
	int				m_cols;
	int				m_rows;

public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocusEdit(UINT _parmCtrlId);
	afx_msg void OnBnClickedOk();
};
