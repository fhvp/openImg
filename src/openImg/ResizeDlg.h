#pragma once
#include "afxwin.h"


// CResizeDlg 대화 상자입니다.

class CResizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResizeDlg)

public:
	CResizeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CResizeDlg();

// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocusEdit(UINT _parmCtrlId);
	afx_msg void OnBnClickedOk();
};
