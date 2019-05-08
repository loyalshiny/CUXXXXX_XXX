// DlgSystemSetting.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgSystemSetting.h"
#include "afxdialogex.h"


// DlgSystemSetting 대화 상자

IMPLEMENT_DYNAMIC(DlgSystemSetting, CDialogEx)

DlgSystemSetting::DlgSystemSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYSTEM_SETTING, pParent)
{
	PreSel = 0;
	Sel = 0;
	m_pDlgSystemRcp = NULL;
	m_pDlgSystemMotor = NULL;
	m_pDlgSystemInterface = NULL;
	m_pDlgSystemUser = NULL;
}

DlgSystemSetting::~DlgSystemSetting()
{
}

void DlgSystemSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(DlgSystemSetting, CDialogEx)
	ON_WM_TIMER()

	ON_BN_CLICKED(IDOK, &DlgSystemSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgSystemSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgSystemSetting 메시지 처리기


BOOL DlgSystemSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(SILVER);
	((CButton*)GetDlgItem(IDC_SYSTEM_RCP))->SetCheck(1);
	InitializeSubDialog();
	m_pDlgSystemRcp->ShowWindow(SW_SHOW);
	OnButtonCheck();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgSystemSetting::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


BOOL DlgSystemSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void DlgSystemSetting::OnDialogClear()
{
	m_pDlgSystemRcp->ShowWindow(SW_HIDE);
	m_pDlgSystemMotor->ShowWindow(SW_HIDE);
	m_pDlgSystemInterface->ShowWindow(SW_HIDE);
	m_pDlgSystemUser->ShowWindow(SW_HIDE);
}

BEGIN_EVENTSINK_MAP(DlgSystemSetting, CDialogEx)
	ON_EVENT(DlgSystemSetting, IDC_SYSTEM_RCP, DISPID_CLICK, DlgSystemSetting::ClickSystemRcp, VTS_NONE)
	ON_EVENT(DlgSystemSetting, IDC_SYSTEM_MOTOR, DISPID_CLICK, DlgSystemSetting::ClickSystemMotor, VTS_NONE)
	ON_EVENT(DlgSystemSetting, IDC_SYSTEM_INTERFACE, DISPID_CLICK, DlgSystemSetting::ClickSystemInterface, VTS_NONE)
	ON_EVENT(DlgSystemSetting, IDC_SYSTEM_COMM, DISPID_CLICK, DlgSystemSetting::ClickSystemComm, VTS_NONE)
	ON_EVENT(DlgSystemSetting, IDC_SYSTEM_USER, DISPID_CLICK, DlgSystemSetting::ClickSystemUser, VTS_NONE)
END_EVENTSINK_MAP()


void DlgSystemSetting::ClickSystemRcp()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgSystemRcp->ShowWindow(SW_SHOW);
}


void DlgSystemSetting::ClickSystemMotor()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgSystemMotor->ShowWindow(SW_SHOW);
}


void DlgSystemSetting::ClickSystemInterface()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgSystemInterface->ShowWindow(SW_SHOW);
}

void DlgSystemSetting::ClickSystemUser()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgSystemUser->ShowWindow(SW_SHOW);
}

void DlgSystemSetting::ClickSystemComm()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DlgSystemSetting::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgSystemSetting::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
void DlgSystemSetting::OnButtonCheck()
{
	if (gReadInterfaceFile("SYSTEM_SETTING", "RECIPE") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_RCP))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "MOTOR") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MOTOR))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "MANUAL") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MANUAL))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "SELECT") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_SELECT))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "CONFIG") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_CONFIG))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "USER") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_USER))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "IO_CHECK") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_IO))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "MOTOR_CHECK") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MOTOCHECK))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("SYSTEM_SETTING", "TAPE") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_SYSTEM_TAPE))->ShowWindow(SW_HIDE);

	if (SystemINIFiles.m_strLanguage == "ENGLISH")
	{
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_RCP))->SetCaption("RECIPE");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MOTOR))->SetCaption("MOTOR");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MANUAL))->SetCaption("MANUAL");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_SELECT))->SetCaption("SELECT");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_CONFIG))->SetCaption("CONFIG");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_USER))->SetCaption("USER");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_IO))->SetCaption("I/O CHECK");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MOTOCHECK))->SetCaption("MOTOR CHECK");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_TAPE))->SetCaption("TAPE SETTING");
	}
	else if (SystemINIFiles.m_strLanguage == "KOREAN")
	{
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_RCP))->SetCaption("레시피");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MOTOR))->SetCaption("모터");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MANUAL))->SetCaption("매뉴얼");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_SELECT))->SetCaption("SELECT");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_CONFIG))->SetCaption("CONFIG");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_USER))->SetCaption("사용자");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_IO))->SetCaption("I/O 체크");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_MOTOCHECK))->SetCaption("모터 체크");
		((CBtnEnh*)GetDlgItem(IDC_SYSTEM_TAPE))->SetCaption("TAPE 설정");
	}

}


void DlgSystemSetting::InitializeSubDialog()
{
	m_pDlgSystemRcp = new DlgSystemRcp;
	m_pDlgSystemRcp->Create(IDD_DIALOG_SYSTEM_RCP, this);
	m_pDlgSystemRcp->MoveWindow(0, 41, 1278, 847);

	m_pDlgSystemMotor = new DlgSystemMotor;
	m_pDlgSystemMotor->Create(IDD_DIALOG_SYSTEM_MOTOR, this);
	m_pDlgSystemMotor->MoveWindow(0, 41, 1278, 847);

	m_pDlgSystemInterface = new DlgSystemInterface;
	m_pDlgSystemInterface->Create(IDD_DIALOG_SYSTEM_INTERFACE, this);
	m_pDlgSystemInterface->MoveWindow(0, 41, 1278, 847);

	m_pDlgSystemUser = new DlgSystemUser;
	m_pDlgSystemUser->Create(IDD_DIALOG_SYSTEM_USER, this);
	m_pDlgSystemUser->MoveWindow(0, 41, 1278, 847);
}