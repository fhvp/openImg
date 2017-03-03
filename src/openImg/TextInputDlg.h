#pragma once
#include "afxwin.h"

#include <vector>

// CTextInputDlg ��ȭ �����Դϴ�.

class CTextInputDB
{
private:
protected:
public:
};


class CTextInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextInputDlg)

private:
	POINT								m_point;

protected:
	CEdit								m_editInputText;

public:
	CTextInputDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTextInputDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEXT_INPUT };
		
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
};
