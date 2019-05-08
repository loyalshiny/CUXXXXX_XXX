// DlgMain.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include "btnenh.h"
#define WINDOW_WIDTH 1100
// DlgMain 대화 상자

IMPLEMENT_DYNAMIC(DlgMain, CDialogEx)

DlgMain::DlgMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{
	m_bStartEvent = FALSE;
	m_bHomeEvent = FALSE;
	m_bStopEvent = FALSE;
	m_bResetEvent = FALSE;
	Col = 0;
	Row = 0;
}

DlgMain::~DlgMain()
{

}

void DlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgMain, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &DlgMain::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgMain::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgMain 메시지 처리기

void DlgMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	OnMotorHomeDisplay();
//	OnButtonDisplay();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL DlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(SILVER);
	cFont.CreateFont(15,                     // 글자높이
		5,                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		0,						// 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("Tahoma")           // 글꼴
	);

	OnButtonCheck();
	
	SetTimer(0, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
BEGIN_EVENTSINK_MAP(DlgMain, CDialogEx)

END_EVENTSINK_MAP()
BOOL DlgMain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//m_toolTip.RelayEvent(pMsg);
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void DlgMain::OnMotorHomeDisplay()
{
	
	CClientDC  dc(this);

	int nValue = 0;
	dc.SelectObject(cFont);
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			nValue = (k * 16) + i;
			if (nValue > Main.nMotorCnt)break;
			if (PollingBit(wEmemoryRead[38+k], i) )
			{	
				dc.FillSolidRect(&rect[nValue], (DKGREEN));				
				dc.DrawText(TEXT(m_MotorTable[nValue].strMotorName), &rect[nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

			}
			else if (!PollingBit(wEmemoryRead[38 + k], i))
			{
				dc.FillSolidRect(&rect[nValue], (SILVER));
				dc.DrawText(TEXT(m_MotorTable[nValue].strMotorName), &rect[nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

			}
		}
	}
}



void DlgMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int dev = 0;
	int yHeight = 35;
	int mtCnt = 0;
	int nCols = 0;
	
	if (Main.nMotorCnt <= 10){Row = 1; nCols = Main.nMotorCnt % 10;}
	else if (10 < Main.nMotorCnt && Main.nMotorCnt <= 20) { Row = 2; nCols = Main.nMotorCnt % 10; }
	else if (20 < Main.nMotorCnt && Main.nMotorCnt <= 30) { Row = 3; nCols = Main.nMotorCnt % 10; }
	else if (30 < Main.nMotorCnt && Main.nMotorCnt <= 40) { Row = 4; nCols = Main.nMotorCnt % 10; }
	
	for (int k = 0; k < Row; k++)
	{
		if (k < Row-1 ){Col = 10;dev = WINDOW_WIDTH / Col;}
		else if (k == Row-1 && nCols != 0){Col = Main.nMotorCnt % 10;dev = WINDOW_WIDTH / Col;}
		else if (k == Row - 1 && nCols == 0){Col = 10;dev = WINDOW_WIDTH / Col;}
		for (int i = 0; i < Col; i++)
		{
			if (i > 10)return;
			rect[mtCnt] = CRect(dev * i + 2, 2 + (k * 35), (dev * 1) + (dev * i), 35 + (k * 35));
			mtCnt += 1;
		}
	}
}


void DlgMain::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgMain::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void DlgMain::OnButtonDisplay()
{
	if (E50803 && !m_bHomeEvent)
	{
		m_bHomeEvent = TRUE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_HOME))->SetBackColor(BLUE);
	}
	else if (!E50803 && m_bHomeEvent)
	{
		m_bHomeEvent = FALSE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_HOME))->SetBackColor(SILVER);
	}


	if (E50804_AUTORUN && !m_bStartEvent)
	{
		m_bStartEvent = TRUE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_START))->SetBackColor(GREEN);
	}
	else if (!E50804_AUTORUN && m_bStartEvent)
	{
		m_bStartEvent = FALSE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_START))->SetBackColor(SILVER);
	}

	if (E50805 && !m_bStopEvent)
	{
		m_bStopEvent = TRUE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_STOP))->SetBackColor(RED);
	}
	else if (!E50805 && m_bStopEvent)
	{
		m_bStopEvent = FALSE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_STOP))->SetBackColor(SILVER);
	}

	if (E50806 && !m_bResetEvent)
	{
		m_bResetEvent = TRUE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_RESET))->SetBackColor(YELLOW);
	}
	else if (!E50806 && m_bResetEvent)
	{
		m_bResetEvent = FALSE;
		((CBtnEnh*)GetDlgItem(IDC_MAIN_RESET))->SetBackColor(SILVER);
	}
}
void DlgMain::OnButtonCheck()
{
	((CBtnEnh*)GetDlgItem(IDC_MAIN_HOME))->SetPicture("..\\..\\Button\\HOME.png");
	((CBtnEnh*)GetDlgItem(IDC_MAIN_RESET))->SetPicture("..\\..\\Button\\RESET.png");
	((CBtnEnh*)GetDlgItem(IDC_MAIN_START))->SetPicture("..\\..\\Button\\START.png");
	((CBtnEnh*)GetDlgItem(IDC_MAIN_STOP))->SetPicture("..\\..\\Button\\STOP.png");

	if (SystemINIFiles.m_strLanguage == "ENGLISH")
	{
		((CBtnEnh*)GetDlgItem(IDC_MAIN_HOME))->SetCaption("INITIAL");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_RESET))->SetCaption("RESET");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_START))->SetCaption("START");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_STOP))->SetCaption("STOP");
		((CBtnEnh*)GetDlgItem(IDC_LAST_WORK))->SetCaption("LAST WORK");
		((CBtnEnh*)GetDlgItem(IDC_WORKEND))->SetCaption("WORK END");

	}
	else if (SystemINIFiles.m_strLanguage == "KOREAN")
	{
		((CBtnEnh*)GetDlgItem(IDC_MAIN_HOME))->SetCaption("초기화");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_RESET))->SetCaption("리셋");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_START))->SetCaption("시작");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_STOP))->SetCaption("정지");
		((CBtnEnh*)GetDlgItem(IDC_LAST_WORK))->SetCaption("마지막 작업");
		((CBtnEnh*)GetDlgItem(IDC_WORKEND))->SetCaption("작업 종료");
	}

}