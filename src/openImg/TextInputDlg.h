#pragma once
#include "afxwin.h"

#include <vector>

// CTextInputDlg 대화 상자입니다.

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
	CTextInputDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTextInputDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEXT_INPUT };
		
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
};
