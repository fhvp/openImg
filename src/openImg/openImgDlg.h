
// openImgDlg.h : ��� ����
//

#pragma once

#include "MOBCommon.h"
#include <string.h>


#define INPUT_IMAGE			"��������"

enum MessageFlag
{
	OUTPUT_MESSAGE,
	INPUT_MESSAGE
};

class CIplImageDB;

// CopenImgDlg ��ȭ ����
class CopenImgDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CopenImgDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CopenImgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OPENIMG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	void* m_iplImage;	//CIplImageDB for IplImageDB.h


protected:
	template <typename T>
	void ShowImage(const T _name, int flag = OUTPUT_MESSAGE);
	template <typename K>
	void DestroyImage(const K _name);

	STATE OpenImage(char* _filePath);
	void ConvertImage(CIplImageDB* _pIplImage);

// �����Դϴ�.
protected:
	HICON m_hIcon;
	CButton m_cbOriginalImg;

	// ������ �޽��� �� �Լ�
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedEqualize();
	afx_msg void OnBnClickedBrightDown();
	afx_msg void OnBnClickedBrightUp();
	afx_msg void OnBnClickedContrestDown();
	afx_msg void OnBnClickedContrestUp();
	afx_msg void OnBnClickedOriginalImg();
	afx_msg void OnBnClickedSaturationDown();
	afx_msg void OnBnClickedSaturationUp();
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedResize();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedClose();
};
