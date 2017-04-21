#pragma once
#include "afxwin.h"


// CTextFontDlg ��ȭ �����Դϴ�.
#define DEFAULT_FONT			(L"����")
#define DEFAULT_FONT_SIZE		(L"12")

class CTextFontDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextFontDlg)

private:

protected:
	CTextFontDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

public:
	virtual ~CTextFontDlg();
	virtual BOOL OnInitDialog();

	static CTextFontDlg* Instance();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEXT_FONT };

private:
	static CTextFontDlg*			m_instance;

protected:
	CString						m_beforFont;
	CString						m_beforSize;

	int							m_bold;
	int							m_itlic;
	int							m_underline;

	//Combo Box(Edit Box) Control ID
	HWND						m_hWndFontEdit;
	HWND						m_hWndSizeEdit;

	//Dialog Box HWND
	HWND						m_hWndInputDlg;

	//Color
	COLORREF					m_currentColor;

public:
	CComboBox					m_fontCombo;
	CComboBox					m_sizeCombo;
	CRichEditCtrl				m_sampleText;


public:
	static BOOL CALLBACK CTextFontDlg::OnCallBackFontList(LPLOGFONTW lplf, LPTEXTMETRICW lptm, DWORD dwType, LPARAM lpData);
	void DeleteAll();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnVkReturnTextFontComob();
	void OnVkReturnTextSizeComob();
	void SetFont();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCbnCloseupTextFontComob();
	afx_msg void OnCbnCloseupTextSizeCombo();
	afx_msg void OnCbnDropdownTextSizeCombo();
	afx_msg void OnBnClickedTextBold();
	afx_msg void OnBnClickedTextItlic();
	afx_msg void OnBnClickedTextUnderline();
	afx_msg void OnBnClickedTextColor();
	afx_msg LRESULT OnCallInputDlg(WPARAM wParam, LPARAM lParam);
};
