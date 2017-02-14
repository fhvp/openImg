
// openImgDlg.cpp : 구현 파일
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

//Chiled Dlg
#include "ResizeDlg.h"

using namespace cv;
#endif /*OPENCV*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopenImgDlg 대화 상자

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
END_MESSAGE_MAP()


// CopenImgDlg 메시지 처리기

BOOL CopenImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//Initialize
	this->m_blearFilterSplit.SetDropDownMenu(IDR_FILTER_BLEAR_MENU, 0);

	this->m_blearFilterSplitItem = FILTER_SPLIT_GAUSSIAN_NORMAL;

	this->m_unsharpFilterSplit.SetDropDownMenu(IDR_FILTER_SHARP_MENU, 0);

	this->m_unsharpFilterSplitItem = FILTER_SPLIT_UNSHARP_NORMAL;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CopenImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CopenImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CopenImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CopenImgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CopenImgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}

template <typename T>
void CopenImgDlg::ShowImage(const T _name, int flag/* = OUTPUT_MESSAGE*/)
{
	CIplImageDB* pIplImage = 0x00;
	pIplImage = (CIplImageDB*)this->m_iplImage;

	if (this->m_iplImage != NULL)
	{
		switch (flag)
		{
		case 0:
			if (pIplImage->m_resize != 0.0)
			{
				resize(pIplImage->m_outMat, pIplImage->m_resizeMat, Size(pIplImage->m_outMat.cols / pIplImage->m_resize, pIplImage->m_outMat.rows / pIplImage->m_resize), 0, 0, CV_INTER_NN);
				imshow(_name, pIplImage->m_resizeMat);
			}
			else
				imshow(_name, pIplImage->m_outMat);
			break;
		default:
			if (pIplImage->m_resize != 0.0)
			{
				resize(pIplImage->m_inMat, pIplImage->m_resizeMat, Size(pIplImage->m_inMat.cols / pIplImage->m_resize, pIplImage->m_inMat.rows / pIplImage->m_resize), 0, 0, CV_INTER_NN);
				imshow(_name, pIplImage->m_resizeMat);
			}
			else
				imshow(_name, pIplImage->m_inMat);
			break;
		}
		waitKey(10);
	}
}

template <typename K>
void CopenImgDlg::DestroyImage(const K _name)
{
	destroyWindow(_name);
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
			result = AfxMessageBox(L"변경 사항이 있습니다. 저장하시겠습니까?", MB_YESNOCANCEL);
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

	// 드롭된 정보 없애기
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

	}
	else
	{
		AfxMessageBox(_T("그림 파일을 등록해 주세요"));
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}


void CopenImgDlg::OnBnClickedEqualize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		GaussianBlur(pIplImage->m_midMat, pIplImage->m_midMat, Size(3, 3), CV_INTER_AREA);
		ConvertImage(pIplImage);

		ShowImage(pIplImage->m_name);
	}
	this->m_blearFilterSplit.SetWindowTextW(L"흐리게");
	this->m_blearFilterSplitItem = FILTER_SPLIT_GAUSSIAN_NORMAL;
}

void CopenImgDlg::OnBnClickedGaussianFilterLarge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		GaussianBlur(pIplImage->m_midMat, pIplImage->m_midMat, Size(5, 5), CV_INTER_AREA);

		ConvertImage(pIplImage);
		ShowImage(pIplImage->m_name);
	}
	this->m_blearFilterSplit.SetWindowTextW(L"더흐리게");
	this->m_blearFilterSplitItem = FILTER_SPLIT_GAUSSIAN_LARGE;
}

void CopenImgDlg::OnBnClickedUnsharpFilterSplit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

		filter2D(pIplImage->m_midMat, pIplImage->m_midMat, pIplImage->m_midMat.depth(), kernel);

		ConvertImage(pIplImage);
		ShowImage(pIplImage->m_name);
	}

	this->m_unsharpFilterSplit.SetWindowTextW(L"선명하게");
	this->m_unsharpFilterSplitItem = FILTER_SPLIT_UNSHARP_NORMAL;
}

void CopenImgDlg::OnBnClickedUnsharpFilterLarge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		Mat kernel = (Mat_<char>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);

		filter2D(pIplImage->m_midMat, pIplImage->m_midMat, pIplImage->m_midMat.depth(), kernel);

		ConvertImage(pIplImage);
		ShowImage(pIplImage->m_name);
	}
	this->m_unsharpFilterSplit.SetWindowTextW(L"더선명하게");
	this->m_unsharpFilterSplitItem = FILTER_SPLIT_UNSHARP_LARGE;
}

void CopenImgDlg::OnBnClickedResize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		pIplImage->m_outMat = pIplImage->m_inMat.clone();
		pIplImage->m_midMat = pIplImage->m_inMat.clone();
		pIplImage->Clear();

		pIplImage->SetResize(pIplImage->m_inMat.cols, pIplImage->m_inMat.rows);

		ShowImage(pIplImage->m_name);
	}
}

void CopenImgDlg::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			fne = L"이미지 파일(*.jpg, *.jpeg, *.JPG, *.JPEG)|*.jpg;*.jpeg;*.JPG;*.JPEG|모든 파일(*.*)|*.*||";
		}
		else if (strcmp(pFne, "png") == 0x00 || strcmp(pFne, "PNG") == 0x00)
		{
			defExt = L"png";
			fne = L"이미지 파일(*.png, *.PNG)|*.png;*.PNG|모든 파일(*.*)|*.*||";
		}
		else if (strcmp(pFne, "bmp") == 0x00 || strcmp(pFne, "BMP") == 0x00)
		{
			defExt = L"bmp";
			fne = L"이미지 파일(*.bmp, *.BMP)|*.bmp;*.BMP|모든 파일(*.*)|*.*||";
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
				AfxMessageBox(L"저장되었습니다");

				pIplImage->Clear();
				//pIplImage->m_inMat = pIplImage->m_outMat.clone();
				pIplImage->m_midMat = pIplImage->m_outMat.clone();
			}
		}
	}
}

void CopenImgDlg::OnBnClickedClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int result;
	CIplImageDB* pIplImage = (CIplImageDB*)this->m_iplImage;

	if (pIplImage != NULL)
	{
		if (pIplImage->getChanged() == true)
		{
			result = AfxMessageBox(L"변경 사항이 있습니다. 저장하시겠습니까?", MB_YESNOCANCEL);
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
	::SendMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}

