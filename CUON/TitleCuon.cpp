// TitleCuon.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "TitleCuon.h"
#include "afxdialogex.h"
#include "btnenh.h"

// TitleCuon 대화 상자

IMPLEMENT_DYNAMIC(TitleCuon, CDialogBar)

TitleCuon::TitleCuon(CWnd* pParent /*=nullptr*/)
	/*: CDialog(IDD_TITLE_CUON, pParent)*/
{
	m_hBrush = (HBRUSH) ::CreateSolidBrush(RGB(192, 192, 192));
}

TitleCuon::~TitleCuon()
{
	DeleteObject(m_hBrush);
}

void TitleCuon::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TitleCuon, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateCmdUI)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// TitleCuon 메시지 처리기^
LRESULT TitleCuon::OnInitDialog(WPARAM wParam, LPARAM lParam)
{

	if (!HandleInitDialog(wParam, lParam) || !UpdateData(FALSE))
	{


		SetTimer(0, 10, NULL);
		CBtnEnh* m_pIButtonTop;

		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_MONI1);
		m_pIButtonTop->SetPicture("..\\..\\Button\\MONI.png");

		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_MONI2);
		m_pIButtonTop->SetPicture("..\\..\\Button\\MONI.png");

		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_RESET);
		m_pIButtonTop->SetPicture("..\\..\\Button\\RESET.png");

		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_LIGHT);
		m_pIButtonTop->SetPicture("..\\..\\Button\\LIGHT2.png");


		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_LOGIN);
		m_pIButtonTop->SetPicture("..\\..\\Button\\LOGIN.png");
		
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_BUZZER);
		m_pIButtonTop->SetPicture("..\\..\\Button\\BUZZER2.png");

		

		//m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_KEYBOARD);
		//m_pIButtonTop->SetPicture("..\\..\\Button\\KEYBOARD.png");

		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_PLC_STAT);
		m_pIButtonTop->SetCaption("OFFLINE");
		m_pIButtonTop->SetBackColor(RED);//green

		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_GEM_STAT);
		m_pIButtonTop->SetCaption("OFFLINE");
		m_pIButtonTop->SetBackColor(RED);//red
		
		((CBtnEnh*)GetDlgItem(IDC_TOP_MODEL))->SetCaption(SystemINIFiles.m_strModel);
		((CBtnEnh*)GetDlgItem(IDC_TOP_SN))->SetCaption(SystemINIFiles.m_strSerialNo);
		((CBtnEnh*)GetDlgItem(IDC_TOP_SOFT))->SetCaption(SystemINIFiles.m_strSoftVer);
		((CBtnEnh*)GetDlgItem(IDC_TOP_CUSTOMER))->SetCaption(SystemINIFiles.m_strCustomerName);

		TRACE0("WARING");
		return FALSE;
	}

	return TRUE;
}
void TitleCuon::OnUpdateCmdUI(CCmdUI* pCmdUI) // 다이얼로그바 버튼 활성화 위해 추가
{
	pCmdUI->Enable(TRUE);
}
int TitleCuon::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}

HBRUSH TitleCuon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return m_hBrush;
}


void TitleCuon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SYstemMonitor();
	CDialogBar::OnTimer(nIDEvent);
}

void TitleCuon::SYstemMonitor()
{
	CBtnEnh* m_pIButtonTop;

	COleDateTime   m_DateTime;
	m_DateTime = COleDateTime::GetCurrentTime();
	CString strTempDate;


	strTempDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), m_DateTime.GetYear(), m_DateTime.GetMonth(), m_DateTime.GetDay(), m_DateTime.GetHour(), m_DateTime.GetMinute(), m_DateTime.GetSecond());
	
	m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_DATE);
	m_pIButtonTop->SetCaption(strTempDate);
	
	m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_RCP);
	m_pIButtonTop->SetCaption(m_RecipeTable.Name);

	SystemINIFiles.m_Date = strTempDate;

	((CBtnEnh*)GetDlgItem(IDC_TOP_ID))->SetCaption(Main.m_UserID);
	((CBtnEnh*)GetDlgItem(IDC_TOP_LEVEL))->SetCaption(Main.m_UserLevel);


	if (SystemINIFiles.m_fSatus == TRUE)
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_PLC_STAT);
		m_pIButtonTop->SetCaption("CONNECT");
		m_pIButtonTop->SetBackColor(GREEN);
	}
	else
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_PLC_STAT);
		m_pIButtonTop->SetCaption("DISCONNECT");
		m_pIButtonTop->SetBackColor(RED);
	}


	if (Main.m_nControlMode == CONTROL_ONLINE_REMOTE)
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_GEM_STAT2);
		m_pIButtonTop->SetCaption("REMOTE");
		m_pIButtonTop->SetBackColor(GREEN);
	}
	else if (Main.m_nControlMode == CONTROL_ONLINE_LOCAL)
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_GEM_STAT2);
		m_pIButtonTop->SetCaption("LOCAL");
		m_pIButtonTop->SetBackColor(YELLOW);
	}
	else if (Main.m_nControlMode == CONTROL_OFFLINE)
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_GEM_STAT2);
		m_pIButtonTop->SetCaption("OFFLINE");
		m_pIButtonTop->SetBackColor(BLUE);
	}


	if (Main.m_nControlConnect == CONTROL_CONNECTED)
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_GEM_STAT);
		m_pIButtonTop->SetCaption("CONNECT");
		m_pIButtonTop->SetBackColor(GREEN);
	}
	else if (Main.m_nControlConnect == CONTROL_DISCONNECTED)
	{
		m_pIButtonTop = (CBtnEnh*)GetDlgItem(IDC_TOP_GEM_STAT);
		m_pIButtonTop->SetCaption("DISCONNECT");
		m_pIButtonTop->SetBackColor(RED);
	}

	if (E90401_TOUCH_1)((CBtnEnh*)GetDlgItem(IDC_TOP_MONI1))->SetBackColor(BLUELED);
	else((CBtnEnh*)GetDlgItem(IDC_TOP_MONI1))->SetBackColor(SILVER);

	if (E90402_TOUCH_2)((CBtnEnh*)GetDlgItem(IDC_TOP_MONI2))->SetBackColor(BLUELED);
	else((CBtnEnh*)GetDlgItem(IDC_TOP_MONI2))->SetBackColor(SILVER);

	if (E90401_TOUCH_1)((CBtnEnh*)GetDlgItem(IDC_TOP_LIGHT))->SetPicture("..\\..\\Button\\LIGHT.png");
	else((CBtnEnh*)GetDlgItem(IDC_TOP_LIGHT))->SetPicture("..\\..\\Button\\LIGHT2.png");

	if (E90402_TOUCH_2)((CBtnEnh*)GetDlgItem(IDC_TOP_BUZZER))->SetPicture("..\\..\\Button\\BUZZER.png");
	else((CBtnEnh*)GetDlgItem(IDC_TOP_BUZZER))->SetPicture("..\\..\\Button\\BUZZER2.png");

}

BEGIN_EVENTSINK_MAP(TitleCuon, CDialogBar)
ON_EVENT(TitleCuon, IDC_TOP_LOGIN, DISPID_CLICK, TitleCuon::ClickTopLogin, VTS_NONE)
END_EVENTSINK_MAP()


void TitleCuon::ClickTopLogin()
{
	DlgBox dlg;
	if (dlg.DoModal() == IDCANCEL)return;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	DlgLogin dlg2;
	dlg2.DoModal();
	
	
}
