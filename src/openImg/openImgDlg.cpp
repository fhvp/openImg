
// openImgDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "openImg.h"
#include "openImgDlg.h"
#include "afxdialogex.h"

#include "MOBCommon.h"

#include "MOBMFCLogger.h"

#ifdef OPENCV
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"	//cv::Mat
#include "opencv2/imgproc/imgproc.hpp"	//cv::equalizeHist

#include "IplImageDB.h"
#include "TextManager.h"

//Chiled Dlg
#include "ResizeDlg.h"
#include "TextFontDlg.h"
#include "TextInputDlg.h"
#include "ImageViewDlg.h"

using namespace cv;
#endif /*OPENCV*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CopenImgDlg ��ȭ ����

CopenImgDlg* CopenImgDlg::m_instance = 0x00;

CopenImgDlg* CopenImgDlg::Instance()
{
	if (CopenImgDlg::m_instance == NULL)
		CopenImgDlg::m_instance = new CopenImgDlg();
	return CopenImgDlg::m_instance;
}

CopenImgDlg::CopenImgDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CopenImgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->m_iplImage = NULL;
}

CopenImgDlg::~CopenImgDlg()
{
	if (this->m_iplImage != NULL)
	{
		CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

		DestroyImage(INPUT_IMAGE);
		DestroyImage(pIplImage->m_name);

		SAFE_DELETE(this->m_iplImage);
	}
}

void CopenImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ORIGINAL_IMG, m_cbOriginalImg);
	DDX_Control(pDX, IDC_BLEAR_FILTER_SPLIT, m_blearFilterSplit);
	DDX_Control(pDX, IDC_UNSHARP_FILTER_SPLIT, m_unsharpFilterSplit);
}

BEGIN_MESSAGE_MAP(CopenImgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_EQUALIZE, &CopenImgDlg::OnBnClickedEqualize)
	ON_BN_CLICKED(IDC_BRIGHT_DOWN, &CopenImgDlg::OnBnClickedBrightDown)
	ON_BN_CLICKED(IDC_BRIGHT_UP, &CopenImgDlg::OnBnClickedBrightUp)
	ON_BN_CLICKED(IDC_INIT, &CopenImgDlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_ORIGINAL_IMG, &CopenImgDlg::OnBnClickedOriginalImg)
	ON_BN_CLICKED(IDC_CONTREST_DOWN, &CopenImgDlg::OnBnClickedContrestDown)
	ON_BN_CLICKED(IDC_CONTREST_UP, &CopenImgDlg::OnBnClickedContrestUp)
	ON_BN_CLICKED(IDC_SAVE, &CopenImgDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_SATURATION_DOWN, &CopenImgDlg::OnBnClickedSaturationDown)
	ON_BN_CLICKED(IDC_SATURATION_UP, &CopenImgDlg::OnBnClickedSaturationUp)
	//ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CLOSE, &CopenImgDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_RESIZE, &CopenImgDlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_BLEAR_FILTER_SPLIT, &CopenImgDlg::OnBnClickedFilterSplit)
	ON_COMMAND(ID_GAUSSIAN_FILTER_NORMAL, &CopenImgDlg::OnBnClickedGaussianFilterNormal)
	ON_COMMAND(ID_GAUSSIAN_FILTER_LARGE, &CopenImgDlg::OnBnClickedGaussianFilterLarge)
	ON_BN_CLICKED(IDC_UNSHARP_FILTER_SPLIT, &CopenImgDlg::OnBnClickedUnsharpFilterSplit)
	ON_COMMAND(ID_UNSHARP_FILTER_NORMAL, &CopenImgDlg::OnBnClickedUnsharpFilterNormal)
	ON_COMMAND(ID_UNSHARP_FILTER_LARGE, &CopenImgDlg::OnBnClickedUnsharpFilterLarge)
	ON_BN_CLICKED(IDC_TEXT, &CopenImgDlg::OnBnClickedText)
	ON_MESSAGE(MSG_TEXT_INPUT, &CopenImgDlg::OnCallBackTextInput)
	ON_MESSAGE(MSG_MOVE_INPUT_TEXT_BOX, &CopenImgDlg::OnCallBackMoveTextInput)
END_MESSAGE_MAP()


// CopenImgDlg �޽��� ó����

BOOL CopenImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//Initialize
	this->m_blearFilterSplit.SetDropDownMenu(IDR_FILTER_BLEAR_MENU, 0);

	this->m_blearFilterSplitItem = FILTER_SPLIT_GAUSSIAN_NORMAL;

	this->m_unsharpFilterSplit.SetDropDownMenu(IDR_FILTER_SHARP_MENU, 0);

	this->m_unsharpFilterSplitItem = FILTER_SPLIT_UNSHARP_NORMAL;

	this->m_textManager = NULL;
	this->m_textFontDlg = NULL;
	this->m_textInputDlg = NULL;

	//Create New Image View Dialog
	//this->m_imageView = new CImageViewDlg();
	//this->m_imageView->Create(IDD_IMAGE_VIEW, NULL);
	//this->m_imageView->ShowWindow(SW_HIDE);

	//Disable Text
	//GetDlgItem(IDC_TEXT)->EnableWindow(FALSE);

	this->m_imagehWnd = NULL;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CopenImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CopenImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CopenImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CopenImgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CopenImgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	int i = 0x00;

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			break;
		case VK_ESCAPE:
			return true;

		default:
			i = pMsg->wParam;
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

//void CopenImgDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}

template <typename T>
void CopenImgDlg::ShowImage(const T _name, int flag /*= OUTPUT_MESSAGE*/)
{
	CIplImageDB* pIplImage = 0x00;
	pIplImage = (CIplImageDB*)this->m_iplImage;

	if (this->m_iplImage != NULL)
	{
		//Show Text
		ShowText(flag);

		switch (flag)
		{
		case 0:

			if (pIplImage->m_resize != 0.0)
			{
				resize(pIplImage->m_outMat, pIplImage->m_resizeMat, Size(pIplImage->m_outMat.cols / pIplImage->m_resize, pIplImage->m_outMat.rows / pIplImage->m_resize), 0, 0, CV_INTER_NN);
				imshow(_name, pIplImage->m_resizeMat);
				
				//this->m_imageView->ShowImage(pIplImage->m_outMat.data, pIplImage->m_outMat.channels());
			}
			else
			{
				//test1
				imshow(_name, pIplImage->m_outMat);

//				this->m_imageView->ShowImage(pIplImage->m_outMat.data, pIplImage->m_outMat.channels());
			}
			break;
		default:
			if (pIplImage->m_resize != 0.0)
			{
				resize(pIplImage->m_inMat, pIplImage->m_resizeMat, Size(pIplImage->m_inMat.cols / pIplImage->m_resize, pIplImage->m_inMat.rows / pIplImage->m_resize), 0, 0, CV_INTER_NN);
				imshow(_name, pIplImage->m_resizeMat);

				//this->m_imageView->ShowImage(pIplImage->m_outMat.data, pIplImage->m_outMat.channels());
			}
			else
			{
				imshow(_name, pIplImage->m_inMat);

				//this->m_imageView->ShowImage(pIplImage->m_outMat.data, pIplImage->m_outMat.channels());
			}
			break;
		}
		waitKey(100);
	}
}

template <typename K>
void CopenImgDlg::DestroyImage(const K _name)
{
	destroyWindow(_name);
}

void CopenImgDlg::ShowText(int flag /*= OUTPUT_MESSAGE*/)
{
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		if (pIplImage->m_textMat.data == NULL)
			return;

		UCHAR* data = pIplImage->m_textMat.data;
		int length = pIplImage->m_outMat.rows * pIplImage->m_outMat.cols * pIplImage->m_outMat.channels();

		for (int index = 0x00; index < length; index += pIplImage->m_outMat.channels())
		{
			if (data[index + 0] != 0x00 || data[index + 1] != 0x00 || data[index + 2] != 0x00)
			{
				pIplImage->m_outMat.data[index + 0] = data[index + 0];
				pIplImage->m_outMat.data[index + 1] = data[index + 1];
				pIplImage->m_outMat.data[index + 2] = data[index + 2];
			}
		}
	}
}

void CopenImgDlg::ConvertImage(CIplImageDB* _pIplImage)
{
	if (_pIplImage != NULL)
	{
		Mat mat;
		std::vector<Mat> channels;

		//_pIplImage->m_outMat = _pIplImage->m_midMat.clone();

		//First
		add(_pIplImage->m_midMat, _pIplImage->getContrast(), _pIplImage->m_outMat);
		multiply(_pIplImage->m_outMat, _pIplImage->getBrightness(), _pIplImage->m_outMat);

		//Saturation
		cvtColor(_pIplImage->m_outMat, mat, CV_RGB2HSV);
		split(mat, channels);

		add(channels[1], _pIplImage->getSaturation(), channels[1]);	//Only used S(HSV) channel

		merge(channels, mat);
		cvtColor(mat, _pIplImage->m_outMat, CV_HSV2RGB);
	}
}

static void OnMouseCallback(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_FLAG_LBUTTON)
	{
		if (CopenImgDlg::Instance()->m_textManager != NULL)
		{
			//Text Mode
			if (CopenImgDlg::Instance()->m_textManager->GetTextMode() == TRUE)
			{
				//Add Dialog Box
				POINT point;
				RECT rect;
				int ptX, ptY;

				GetCursorPos(&point);

				//CopenImgDlg::Instance()->GetTextDlg()->GetClientRect(&rect);

				if (point.x - 200 > 0) ptX = point.x - 200;
				else ptX = 0;

				if (point.y - 160 > 0) ptY = point.y - 160;
				else ptY = 0;

				CopenImgDlg::Instance()->GetTextFontDlg()->ShowWindow(SW_SHOW);
				CopenImgDlg::Instance()->GetTextFontDlg()->SetWindowPos(&CWnd::wndTopMost, ptX, ptY, 0, 0, SWP_NOSIZE);
				//CopenImgDlg::Instance()->m_textManager->SetTextInputBoxPoint(x, y);
				CopenImgDlg::Instance()->m_textManager->SetTextMode(false);
				CopenImgDlg::Instance()->m_textManager->SetBitmapWindowPoint(point.x - x, point.y - y);

				//CTextInputDlg* textInputDlg = new CTextInputDlg();
				//textInputDlg->Create(IDD_TEXT_INPUT, CopenImgDlg::Instance());
				//textInputDlg->ShowWindow(SW_SHOW);
				//textInputDlg->SetWindowPos(NULL, point.x, point.y, 0, 0, SWP_NOSIZE);


				CTextInputDlg* textInputDlg = new CTextInputDlg();
				textInputDlg->Create(IDD_TEXT_INPUT, CWnd::FromHandle(CopenImgDlg::Instance()->GetImagehWnd()));
				textInputDlg->ShowWindow(SW_SHOW);
				textInputDlg->SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);
			}
		}
	}

}

//Drag & Drop
void CopenImgDlg::OnDropFiles(HDROP hDropInfo)
{
	char szFilePath[MAX_FILE_PATH];
	CIplImageDB* pIplImage = 0x00;
	int result;

	//Check DB
	if (this->m_iplImage != NULL)
	{
		pIplImage = (CIplImageDB*)this->m_iplImage;

		if (pIplImage->getChanged() == true)
		{
			result = AfxMessageBox(L"���� ������ �ֽ��ϴ�. �����Ͻðڽ��ϱ�?", MB_YESNOCANCEL);
			switch (result)
			{
			case IDYES:
				OnBnClickedSave();
				break;
			case IDCANCEL:
				return;
			default:
				break;
			}
		}

		//Delete Text Manager
		if (this->m_textManager != NULL)
		{
			this->m_textManager->DeleteALL();
			SAFE_DELETE(this->m_textManager);
		}

		DestroyImage(pIplImage->m_name);

		//Delete
		pIplImage->Delete();

		SAFE_DELETE(pIplImage);

		this->m_iplImage = NULL;
	}

	//New DB
	//pIplImage = new CIplImageDB();

	::DragQueryFile(hDropInfo, 0/*File Index*/, (LPWSTR)szFilePath, MAX_FILE_PATH);

	//Open Image
	OpenImage(WTOM((LPWSTR)szFilePath, MAX_FILE_PATH));

	CDialogEx::OnDropFiles(hDropInfo);

	// ��ӵ� ���� ���ֱ�
	DragFinish(hDropInfo);
}

STATE CopenImgDlg::OpenImage(char* _filePath)
{
	CIplImageDB* pIplImage = 0x00;

	//New DB
	pIplImage = new CIplImageDB();

	
	//pIplImage->m_inImgIpl = cvLoadImage(WTOM((LPWSTR)szFilePath, 256));
	pIplImage->m_inMat = imread(_filePath);

	if (/*pIplImage->m_inImgIpl*/pIplImage->m_inMat.data != NULL)
	{
		//Save File Path &* Name
		if (_filePath != NULL)
		{
			char* pathPtr = 0x00;
			char* namePtr = 0x00;
			
			pathPtr = (char*)strrchr(_filePath, '\\');
			namePtr = (char*)strrchr(_filePath, '\0');

			pIplImage->m_path = String(_filePath).substr(0, pathPtr - _filePath);
			//pIplImage->m_path.;

			pIplImage->m_name = pathPtr + 1;

			//memcpy(pIplImage->m_path, _filePath, (pathPtr - _filePath));
			//memcpy(pIplImage->m_name, pathPtr + 1, (namePtr - pathPtr));

		}

		//copy outMat
		pIplImage->m_outMat = pIplImage->m_inMat.clone();
		pIplImage->m_midMat = pIplImage->m_inMat.clone();	//Auto Control

		//Set Resize
		pIplImage->SetResize(pIplImage->m_inMat.cols, pIplImage->m_inMat.rows);

		//Save Image DB
		this->m_iplImage = pIplImage;

		//Saved Image View Bitmap
		//this->m_imageView->SetImgName(pIplImage->m_name.c_str());
		//this->m_imageView->SetSize(pIplImage->m_inMat.cols, pIplImage->m_inMat.rows);
		//this->m_imageView->MakeBitmap();
		//this->m_imageView->ShowWindow(SW_SHOW);

		ShowImage(pIplImage->m_name);
		//if (pIplImage->m_inMat.channels() == 1)
		//{
		//	pIplImage->m_gray = pIplImage->m_inMat;
		//	cvtColor(pIplImage->m_gray, pIplImage->m_inMat, CV_GRAY2RGB);
		//}
		//else if (pIplImage->m_inMat.channels() == 3)
		//{
		//	cvtColor(pIplImage->m_inMat, pIplImage->m_hsv, CV_RGB2HSV);
		//	cvtColor(pIplImage->m_inMat, pIplImage->m_gray, CV_RGB2GRAY);
		//}

		//Set Name
		if (this->m_imagehWnd != NULL)
			DeleteObject(this->m_imagehWnd);

		this->m_imagehWnd = (HWND)cvGetWindowHandle(pIplImage->m_name.c_str());

		//HDC hDC = ::GetDC(this->m_imagehWnd);

		namedWindow(pIplImage->m_name, 1);

		setMouseCallback(pIplImage->m_name, OnMouseCallback, NULL);

	}
	else
	{
		AfxMessageBox(_T("�׸� ������ ����� �ּ���"));
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}

void CopenImgDlg::OnBnClickedEqualize()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		Mat mat;
		std::vector<Mat> channels;

		cvtColor(pIplImage->m_midMat, mat, CV_RGB2HSV);
		split(mat, channels);

		equalizeHist(channels[2], channels[2]);	//Only used V(HSV) channel

		merge(channels, mat);
		cvtColor(mat, pIplImage->m_outMat, CV_HSV2RGB);

		pIplImage->m_midMat = pIplImage->m_outMat.clone();

		ShowImage(pIplImage->m_name);
		
		//Clear Detail Image Control Value
		pIplImage->Clear();

		pIplImage->setChanged();
	}
}

void CopenImgDlg::OnBnClickedBrightDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->subBrightness(0.02);

		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
}


void CopenImgDlg::OnBnClickedBrightUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->addBrightness(0.02);

		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedContrestDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->subContrast(3);

		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedContrestUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->addContrast(3);

		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedOriginalImg()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int state = 0x00;
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		state = this->m_cbOriginalImg.GetCheck();
		switch (state)
		{
		case BST_UNCHECKED:
			destroyWindow(INPUT_IMAGE);
			waitKey(10);
			break;
		case BST_CHECKED:
			ShowImage(INPUT_IMAGE, INPUT_MESSAGE);
			break;
		}
	}
}

void CopenImgDlg::OnBnClickedSaturationDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->subSaturation(3);

		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedSaturationUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->addSaturation(3);

		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedFilterSplit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	switch (this->m_blearFilterSplitItem)
	{
	case FILTER_SPLIT_GAUSSIAN_NORMAL:
		this->OnBnClickedGaussianFilterNormal();
		break;
	case FILTER_SPLIT_GAUSSIAN_LARGE:
		this->OnBnClickedGaussianFilterLarge();
		break;
	}
}

void CopenImgDlg::OnBnClickedGaussianFilterNormal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		GaussianBlur(pIplImage->m_midMat, pIplImage->m_midMat, Size(3, 3), CV_INTER_AREA);
		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
	this->m_blearFilterSplit.SetWindowTextW(L"�帮��");
	this->m_blearFilterSplitItem = FILTER_SPLIT_GAUSSIAN_NORMAL;
}

void CopenImgDlg::OnBnClickedGaussianFilterLarge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		GaussianBlur(pIplImage->m_midMat, pIplImage->m_midMat, Size(5, 5), CV_INTER_AREA);

		ConvertImage(pIplImage);
		ShowImage(pIplImage->m_name);
	}
	this->m_blearFilterSplit.SetWindowTextW(L"���帮��");
	this->m_blearFilterSplitItem = FILTER_SPLIT_GAUSSIAN_LARGE;
}

void CopenImgDlg::OnBnClickedUnsharpFilterSplit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	switch (this->m_unsharpFilterSplitItem)
	{
	case FILTER_SPLIT_UNSHARP_NORMAL:
		this->OnBnClickedUnsharpFilterNormal();
		break;
	case FILTER_SPLIT_UNSHARP_LARGE:
		this->OnBnClickedUnsharpFilterLarge();
		break;
	}
}

void CopenImgDlg::OnBnClickedUnsharpFilterNormal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

		filter2D(pIplImage->m_midMat, pIplImage->m_midMat, pIplImage->m_midMat.depth(), kernel);

		ConvertImage(pIplImage);
		ShowImage(pIplImage->m_name);
	}

	//Change Dialog Box(Split Button) Item
	if (this->m_unsharpFilterSplitItem != FILTER_SPLIT_UNSHARP_NORMAL)
	{
		this->m_unsharpFilterSplit.SetWindowTextW(L"�����ϰ�");
		this->m_unsharpFilterSplitItem = FILTER_SPLIT_UNSHARP_NORMAL;
	}
}

void CopenImgDlg::OnBnClickedUnsharpFilterLarge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		Mat kernel = (Mat_<char>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);

		filter2D(pIplImage->m_midMat, pIplImage->m_midMat, pIplImage->m_midMat.depth(), kernel);

		ConvertImage(pIplImage);
		ShowImage(pIplImage->m_name);
	}

	//Change Dialog Box(Split Button) Item
	if (this->m_unsharpFilterSplitItem != FILTER_SPLIT_UNSHARP_LARGE)
	{
		this->m_unsharpFilterSplit.SetWindowTextW(L"�������ϰ�");
		this->m_unsharpFilterSplitItem = FILTER_SPLIT_UNSHARP_LARGE;
	}
}

void CopenImgDlg::OnBnClickedResize()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		CResizeDlg resizeDlg;

		resizeDlg.m_cols = pIplImage->m_midMat.cols;
		resizeDlg.m_rows = pIplImage->m_midMat.rows;

		resizeDlg.DoModal();
		//resizeDlg->Create(IDD_RESIZE, this);
		//resizeDlg->ShowWindow(SW_SHOW);

		resizeDlg.m_cols;

		resize(pIplImage->m_outMat, pIplImage->m_outMat, Size(resizeDlg.m_cols, resizeDlg.m_rows), 0, 0, CV_INTER_CUBIC);
		resize(pIplImage->m_midMat, pIplImage->m_midMat, Size(resizeDlg.m_cols, resizeDlg.m_rows), 0, 0, CV_INTER_CUBIC);
		pIplImage->SetResize(pIplImage->m_midMat.cols, pIplImage->m_midMat.rows);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedInit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->m_outMat = pIplImage->m_inMat.clone();
		pIplImage->m_midMat = pIplImage->m_inMat.clone();
		pIplImage->Clear();

		pIplImage->SetResize(pIplImage->m_inMat.cols, pIplImage->m_inMat.rows);

		pIplImage->m_textMat = NULL;

		//Bitmap
		if (this->m_textManager != NULL)
			this->m_textManager->Initialize();

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;
	CString dir(pIplImage->m_path.begin());
	CString fne;
	CString defExt;

	if (pIplImage != NULL)
	{
		const char* pFne = (pIplImage->m_name.begin() + pIplImage->m_name.rfind('.', pIplImage->m_name.length())) + 1;
		if (strcmp(pFne, "jpg") == 0x00 || strcmp(pFne, "JPG") == 0x00 || strcmp(pFne, "jpeg") == 0x00 || strcmp(pFne, "JPEG") == 0x00)
		{
			defExt = L"jpg";
			fne = L"�̹��� ����(*.jpg, *.jpeg, *.JPG, *.JPEG)|*.jpg;*.jpeg;*.JPG;*.JPEG|��� ����(*.*)|*.*||";
		}
		else if (strcmp(pFne, "png") == 0x00 || strcmp(pFne, "PNG") == 0x00)
		{
			defExt = L"png";
			fne = L"�̹��� ����(*.png, *.PNG)|*.png;*.PNG|��� ����(*.*)|*.*||";
		}
		else if (strcmp(pFne, "bmp") == 0x00 || strcmp(pFne, "BMP") == 0x00)
		{
			defExt = L"bmp";
			fne = L"�̹��� ����(*.bmp, *.BMP)|*.bmp;*.BMP|��� ����(*.*)|*.*||";
		}

		CFileDialog fDlg(FALSE, defExt, CString(pIplImage->m_name.c_str()), OFN_OVERWRITEPROMPT, fne);
		fDlg.GetOFN().lpstrInitialDir = dir;

		if (fDlg.DoModal() == IDOK) {
			bool result = false;
			char mPath[1024] = { 0x00, };
			CString fileName = fDlg.GetPathName();
			
			WideCharToMultiByte(CP_ACP, 0, fileName, -1, mPath, /*fileName.GetLength()*/1024, NULL, NULL);
			result = imwrite(mPath, pIplImage->m_outMat);

			Sleep(100);
			if (result == true)
			{
				AfxMessageBox(L"����Ǿ����ϴ�");

				pIplImage->Clear();
				//pIplImage->m_inMat = pIplImage->m_outMat.clone();
				pIplImage->m_midMat = pIplImage->m_outMat.clone();
			}
		}
	}
}

void CopenImgDlg::OnBnClickedClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int result;
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		if (pIplImage->getChanged() == true)
		{
			result = AfxMessageBox(L"���� ������ �ֽ��ϴ�. �����Ͻðڽ��ϱ�?", MB_YESNOCANCEL);
			switch (result)
			{
			case IDYES:
				OnBnClickedSave();
				break;
			case IDCANCEL:
				return;
			default:
				break;
			}
		}
	}

	//Close
	destroyAllWindows();

	if (this->m_iplImage != NULL)
	{
		this->m_iplImage->Delete();
		SAFE_DELETE(this->m_iplImage);
	}

	if (this->m_textManager != NULL)
	{
		this->m_textManager->DeleteALL();
		SAFE_DELETE(this->m_textManager);
	}

	if (this->m_textFontDlg != NULL)
	{
		this->m_textFontDlg->DeleteAll();
		SAFE_DELETE(this->m_textFontDlg);
	}

	::PostMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}



void CopenImgDlg::OnBnClickedText()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;
	if (pIplImage == NULL)
		return;

	if (this->m_textManager == NULL)
	{
		this->m_textManager = new CTextManager(pIplImage->m_inMat.cols, pIplImage->m_inMat.rows);

		if (this->m_textFontDlg == NULL)
		{
			this->m_textFontDlg = CTextFontDlg::Instance();
			this->m_textFontDlg->Create(IDD_TEXT_FONT, this);
			this->m_textFontDlg->ShowWindow(SW_HIDE);
		}
	}

	this->m_textManager->SetTextMode(true);
}

LRESULT CopenImgDlg::OnCallBackTextInput(WPARAM wParam, LPARAM lParam)
{
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;
	
	if (pIplImage != NULL)
	{
		Mat mat(CopenImgDlg::Instance()->m_textManager->GetSize().y, CopenImgDlg::Instance()->m_textManager->GetSize().x, CV_8UC3, CopenImgDlg::Instance()->m_textManager->GetBitmap());

		pIplImage->m_textMat = mat.clone();

		ShowImage(pIplImage->m_name);

		this->m_textFontDlg->ShowWindow(SW_HIDE);
	}
	return TRUE;
}

LRESULT CopenImgDlg::OnCallBackMoveTextInput(WPARAM wParam, LPARAM lParam)
{
	this->m_textManager->MoveTextInputBoxPoint((int)wParam, (int)lParam);

	//if (point.x - 200 > 0) ptX = point.x - 200;
	//else ptX = 0;

	//if (point.y - 160 > 0) ptY = point.y - 160;
	//else ptY = 0;

	//CopenImgDlg::Instance()->GetTextFontDlg()->ShowWindow(SW_SHOW);
	//CopenImgDlg::Instance()->GetTextFontDlg()->SetWindowPos(&CWnd::wndTopMost, ptX, ptY, 0, 0, SWP_NOSIZE);
	return TRUE;
}

HWND CopenImgDlg::GetImagehWnd()
{
	return this->m_imagehWnd;
}