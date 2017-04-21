// TextDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "openImg.h"
#include "TextFontDlg.h"
#include "afxdialogex.h"


#define DEFAULT_TEXT		L"abAB123�ѱ�"

// CTextFontDlg ��ȭ �����Դϴ�.

CTextFontDlg* CTextFontDlg::m_instance = NULL;

CTextFontDlg* CTextFontDlg::Instance()
{
	if (CTextFontDlg::m_instance == NULL)
		CTextFontDlg::m_instance = new CTextFontDlg();
	return CTextFontDlg::m_instance;
}

IMPLEMENT_DYNAMIC(CTextFontDlg, CDialogEx)

CTextFontDlg::CTextFontDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextFontDlg::IDD, pParent)
{
	this->m_hWndInputDlg = NULL;
}

CTextFontDlg::~CTextFontDlg()
{
}

void CTextFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_FONT_COMBO, m_fontCombo);
	DDX_Control(pDX, IDC_TEXT_SIZE_COMBO, m_sizeCombo);
	DDX_Control(pDX, IDC_SAMPLE_TEXT, m_sampleText);
}


BEGIN_MESSAGE_MAP(CTextFontDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_CBN_CLOSEUP(IDC_TEXT_FONT_COMBO, &CTextFontDlg::OnCbnCloseupTextFontComob)
	ON_CBN_CLOSEUP(IDC_TEXT_SIZE_COMBO, &CTextFontDlg::OnCbnCloseupTextSizeCombo)
	ON_CBN_DROPDOWN(IDC_TEXT_SIZE_COMBO, &CTextFontDlg::OnCbnDropdownTextSizeCombo)
	ON_BN_CLICKED(IDC_TEXT_BOLD, &CTextFontDlg::OnBnClickedTextBold)
	ON_BN_CLICKED(IDC_TEXT_ITLIC, &CTextFontDlg::OnBnClickedTextItlic)
	ON_BN_CLICKED(IDC_TEXT_UNDERLINE, &CTextFontDlg::OnBnClickedTextUnderline)
	ON_MESSAGE(MSG_CALL_INPUT_DLG, &CTextFontDlg::OnCallInputDlg)
	ON_BN_CLICKED(IDC_TEXT_COLOR, &CTextFontDlg::OnBnClickedTextColor)
END_MESSAGE_MAP()


// CTextFontDlg �޽��� ó�����Դϴ�.
BOOL CALLBACK CTextFontDlg::OnCallBackFontList(LPLOGFONTW lplf, LPTEXTMETRICW lptm, DWORD dwType, LPARAM lpData)
{
	((CStringArray*)lpData)->Add(lplf->lfFaceName);

	return TRUE;
}

BOOL CTextFontDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//Set System Font for Combo Box
	int index;
	HDC hDC;
	LPLOGFONTW logFont;
	CStringArray csArrayFontList;
	CString beforFont;
	CString fontSize;

	hDC = ::GetWindowDC(NULL);
	ZeroMemory(&logFont, sizeof(LPLOGFONTW));
	csArrayFontList.RemoveAll();

	EnumFontFamiliesEx(hDC, logFont, (FONTENUMPROCW)OnCallBackFontList, (LPARAM)&csArrayFontList, (DWORD)0);

	::ReleaseDC(NULL, hDC);

	int fontCount = csArrayFontList.GetSize();
	//LPCTSTR lpStringFont[2048];

	for (index = 0x00; index < fontCount; index++)
	{
		if (beforFont != csArrayFontList.GetAt(index))
		{
			//lpStringFont[index] = csArrayFontList.GetAt(index);
			this->m_fontCombo.AddString(csArrayFontList.GetAt(index));

			beforFont = csArrayFontList.GetAt(index);
		}
	}

	for (index = 0x00; index < 30; index++)
	{
		fontSize.Format( _T("%d"), (index * 2) + 6);
		this->m_sizeCombo.AddString(fontSize);
	}

	//Default Item
	this->m_fontCombo.SetWindowTextW(DEFAULT_FONT);
	this->m_sizeCombo.SetWindowTextW(DEFAULT_FONT_SIZE);

	//Init
	this->m_beforFont = DEFAULT_FONT;
	this->m_beforSize = DEFAULT_FONT_SIZE;

	//Set Combo Box into Edit Box ID

	CWnd* cWndFontEdit = this->GetDlgItem(IDC_TEXT_FONT_COMBO);
	m_hWndFontEdit = ::FindWindowEx(cWndFontEdit->m_hWnd, NULL, L"Edit", NULL);
	
	CWnd* cWndSizeEdit = this->GetDlgItem(IDC_TEXT_SIZE_COMBO);
	m_hWndSizeEdit = ::FindWindowEx(cWndSizeEdit->m_hWnd, NULL, L"Edit", NULL);

	this->m_bold = FW_NORMAL;
	this->m_itlic = FALSE;
	this->m_underline = FALSE;

	//SetFont();
	this->m_currentColor = RGB(0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTextFontDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CTextFontDlg::OnCbnCloseupTextFontComob()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int index = this->m_fontCombo.GetCurSel();

	if (index == -1)
		return;

	this->m_fontCombo.GetLBText(index, this->m_beforFont);

	//AfxMessageBox(this->m_beforFont);

	SetFont();
}

void CTextFontDlg::OnCbnCloseupTextSizeCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = this->m_sizeCombo.GetCurSel();

	if (index == -1)
		return;

	this->m_sizeCombo.GetLBText(index, this->m_beforSize);

	//AfxMessageBox(this->m_beforSize);

	SetFont();
}

void CTextFontDlg::OnVkReturnTextFontComob()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString cStrFont;
	CWnd* cWndFontEdit = CWnd::FromHandle(this->m_hWndFontEdit);

	if (cWndFontEdit != NULL)
	{
		cWndFontEdit->GetWindowTextW(cStrFont);

		//Find same text for ComboBox item list
		int result = this->m_fontCombo.FindStringExact(-1, cStrFont);

		if (result != -1)
		{
			this->m_beforFont = cStrFont;
			this->m_fontCombo.GetLBText(result, this->m_beforFont);
		}
		else
		{
			result = this->m_fontCombo.FindStringExact(-1, this->m_beforFont);
			AfxMessageBox(L"��Ȯ�ϰ� �Է��ϼ���");

			this->m_fontCombo.GetLBText(result, this->m_beforFont);
			cWndFontEdit->SetWindowTextW(this->m_beforFont);
			((CEdit*)cWndFontEdit)->SetSel(0, -1, TRUE);
		}
	}

	SetFont();
}

void CTextFontDlg::OnVkReturnTextSizeComob()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString cStrSize;
	CWnd* cWndSizeEdit = CWnd::FromHandle(this->m_hWndSizeEdit);

	if (cWndSizeEdit != NULL)
	{
		cWndSizeEdit->GetWindowTextW(cStrSize);

		//Find same text for ComboBox item list
		int result = this->m_sizeCombo.FindStringExact(-1, cStrSize);

		if (result != -1)
		{
			this->m_beforSize = cStrSize;
			this->m_sizeCombo.GetLBText(result, this->m_beforSize);
			cWndSizeEdit->SetWindowTextW(this->m_beforSize);
		}
		else
		{
			this->m_beforSize = cStrSize;
			cWndSizeEdit->SetWindowTextW(this->m_beforSize);
		}
	}

	SetFont();
}

void CTextFontDlg::SetFont()
{
	CFont font;

	font.CreateFontW(
		_ttoi(this->m_beforSize),						// ���ڳ���
		0,												// ���ڳʺ�
		0,												// ��°���
		0,												// ���� �������ǰ���
		this->m_bold,									// ���ڱ���
		this->m_itlic,									// Italic ���뿩��
		this->m_underline,								// �������뿩��
		FALSE,											// ��Ҽ����뿩��
		DEFAULT_CHARSET,								// ���ڼ�����
		OUT_DEFAULT_PRECIS,								// ������е�
		CLIP_DEFAULT_PRECIS,							// Ŭ������ �е�
		DEFAULT_QUALITY,								// ��¹���ǰ��
		DEFAULT_PITCH,									// �۲�Pitch
		this->m_beforFont								// �۲�
		);

	//this->m_sampleText.SetFont(&font, TRUE);
	
	CHARFORMAT2 cFormat;

	this->m_sampleText.GetDefaultCharFormat(cFormat);

	cFormat.dwMask = CFM_ALL;// CFM_EFFECTS | CFM_COLOR | CFM_FACE | CFM_SIZE;
	cFormat.crTextColor = this->m_currentColor;
	cFormat.dwEffects = 0x00;
	cFormat.cbSize = sizeof(CHARFORMAT2);

	if (this->m_bold == FW_BOLD)
	{
		//cFormat.dwMask |= CFM_BOLD;
		cFormat.dwEffects |= CFE_BOLD;
	}
	if (this->m_itlic)
	{
		//cFormat.dwMask |= CFM_ITALIC;
		cFormat.dwEffects |= CFE_ITALIC;
	}
	if (this->m_underline)
	{
		//cFormat.dwMask |= CFM_UNDERLINE;
		cFormat.dwEffects |= CFE_UNDERLINE;
	}

	cFormat.yHeight = _ttoi(this->m_beforSize) * 13;
	cFormat.bCharSet = DEFAULT_CHARSET;

	wcscpy_s(cFormat.szFaceName, this->m_beforFont.GetBuffer(0));

	this->m_sampleText.SetFocus();
	this->m_sampleText.SetSel(0, -1);
	this->m_sampleText.SetDefaultCharFormat(cFormat);

	this->m_sampleText.ReplaceSel(DEFAULT_TEXT);

	//this->m_sampleText.SetWindowTextW(DEFAULT_TEXT);

	if (this->m_hWndInputDlg != NULL)
		::SendMessage(this->m_hWndInputDlg, MSG_SET_INPUT_FONT, (WPARAM)this->m_currentColor, (LPARAM)&cFormat/*font*/);

	font.Detach();
}

void CTextFontDlg::DeleteAll()
{

}

BOOL CTextFontDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			//Set Combo Box & Change Edit Box

			if (1)
			{
				if (pMsg->hwnd == this->m_hWndFontEdit)
					OnVkReturnTextFontComob();
				else if (pMsg->hwnd == this->m_hWndSizeEdit)
					OnVkReturnTextSizeComob();
			}
			
			return true;
		case VK_ESCAPE:
			//Close Dialog
			break;
		default:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTextFontDlg::OnCbnDropdownTextSizeCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int sizeValue = 0x00;
	CString cStrSize;

	CWnd* cWndSizeEdit = CWnd::FromHandle(this->m_hWndSizeEdit);

	if (cWndSizeEdit != NULL)
	{
		cWndSizeEdit->GetWindowTextW(cStrSize);

		sizeValue = _ttoi(cStrSize);

		if (sizeValue > 0x00)
			sizeValue -= 1;
		else
			sizeValue += 1;

		cStrSize.Format(L"%d", sizeValue);

		int result = this->m_sizeCombo.FindStringExact(-1, cStrSize);

		if (result != -1)
		{
			//to do...
			//this->m_sizeCombo.SetCurSel(result);
			//cWndSizeEdit->SetWindowTextW(this->m_beforSize);
		}
	}

}


void CTextFontDlg::OnBnClickedTextBold()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	if (this->m_bold == FW_NORMAL)
	{
		this->m_bold = FW_BOLD;
	}
	else
	{
		this->m_bold = FW_NORMAL;
	}
	
	SetFont();
}


void CTextFontDlg::OnBnClickedTextItlic()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (this->m_itlic == FALSE)
	{
		this->m_itlic = TRUE;
	}
	else
	{
		this->m_itlic = FALSE;
	}

	SetFont();
}


void CTextFontDlg::OnBnClickedTextUnderline()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (this->m_underline == FALSE)
	{
		this->m_underline = TRUE;
	}
	else
	{
		this->m_underline = FALSE;
	}

	SetFont();
}

void CTextFontDlg::OnBnClickedTextColor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog colorDialog(RGB(0, 0, 0), CC_RGBINIT);

	//colorDialog.m_nFlags |= CC_FULLOPEN;
	colorDialog.DoModal();

	this->m_currentColor = colorDialog.GetColor();

	SetFont();

	//if (this->m_hWndInputDlg != NULL)
	//	::PostMessage(this->m_hWndInputDlg, MSG_SET_INPUT_FONT, (WPARAM)this->m_currentColor, 0);
}

LRESULT CTextFontDlg::OnCallInputDlg(WPARAM wParam, LPARAM lParam)
{
	if (lParam != NULL)
	{
		this->m_hWndInputDlg = (HWND)lParam;
	}

	SetFont();

	return TRUE;
}
