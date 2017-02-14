
// openImgDlg.h : ��� ����
//

#pragma once

#include "MOBCommon.h"
#include <string.h>
#include "afxwin.h"


#define INPUT_IMAGE			"��������"

enum MessageFlag
{
	OUTPUT_MESSAGE,
	INPUT_MESSAGE
};

enum BlearFilterSplitFlag
{
	FILTER_SPLIT_GAUSSIAN_NORMAL,
	FILTER_SPLIT_GAUSSIAN_LARGE,
};

enum UnsharpFilterSplitFlag
{
	FILTER_SPLIT_UNSHARP_NORMAL,
	FILTER_SPLIT_UNSHARP_LARGE
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
	template <typename T>
	void ShowImage(const T _name, int flag = OUTPUT_MESSAGE);
	template <typename K>
	void DestroyImage(const K _name);

	STATE OpenImage(char* _filePath);
	void ConvertImage(CIplImageDB* _pIplImage);


// �����Դϴ�.
protected:
	void*						m_iplImage;	//CIplImageDB for IplImageDB.h
	HICON						m_hIcon;
	CButton						m_cbOriginalImg;
	CSplitButton				m_blearFilterSplit;
	UCHAR						m_blearFilterSplitItem;	//BlearFilterSplitFlag
	CSplitButton				m_unsharpFilterSplit;
	UCHAR						m_unsharpFilterSplitItem;	//UnsharpFilterSplitFlag

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
	afx_msg void OnBnClickedFilterSplit();
	afx_msg void OnBnClickedGaussianFilterNormal();
	afx_msg void OnBnClickedGaussianFilterLarge();
	afx_msg void OnBnClickedUnsharpFilterSplit();
	afx_msg void OnBnClickedUnsharpFilterNormal();
	afx_msg void OnBnClickedUnsharpFilterLarge();
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedResize();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedClose();
};
