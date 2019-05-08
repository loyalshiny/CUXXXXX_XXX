// DlgLogin.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// DlgLogin 대화 상자

IMPLEMENT_DYNAMIC(DlgLogin, CDialogEx)

DlgLogin::DlgLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	
{
	CString m_strUserID[20] = { 0 };
	CString m_strUserLevel[20] = { 0 };
	nRows = 0;
}

DlgLogin::~DlgLogin()
{
}

void DlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
}


BEGIN_MESSAGE_MAP(DlgLogin, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &DlgLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgLogin::OnBnClickedCancel)

	ON_LBN_SELCHANGE(IDC_USER_LIST, &DlgLogin::OnLbnSelchangeUserList)
END_MESSAGE_MAP()


// DlgLogin 메시지 처리기


BOOL DlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(SILVER);
	//
	HFONT hNewFont;

	hNewFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_MODERN, "Tahoma");
	GetDlgItem(IDC_USER_LIST)->SendMessage(WM_SETFONT, (WPARAM)hNewFont, (LPARAM)TRUE);

	//m_UserList.AddString("SSD");
	for (int i = 0; i < m_UserTable.UserCnt; i++)
	{
		m_UserList.InsertString(i,m_UserTable.UserID[i]);
		if (m_UserTable.UserID[i] == Main.m_UserID)nRows = i;
		
	}
	((CBtnEnh*)GetDlgItem(IDC_LOGIN_ID))->SetCaption(Main.m_UserID);
	((CBtnEnh*)GetDlgItem(IDC_LOGIN_LEVEL))->SetCaption(Main.m_UserLevel);

	m_tooltip.Create(this);
	m_tooltip.AddTool(GetDlgItem(IDC_USER_LIST), "리스트 : ㅁㅁㅁㅁ");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_tooltip.RelayEvent(pMsg);
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)//ClickLoginEnter();
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


void DlgLogin::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgLogin::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

BEGIN_EVENTSINK_MAP(DlgLogin, CDialogEx)
	ON_EVENT(DlgLogin, IDC_LOGIN_ENTER, DISPID_CLICK, DlgLogin::ClickLoginEnter, VTS_NONE)
END_EVENTSINK_MAP()


void DlgLogin::ClickLoginEnter()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CString strTemp,strPass;

	strPass = m_UserTable.UserPass[nRows];
	GetDlgItemText(IDC_LOGIN_PASS, strTemp);
	if (strPass == strTemp)
	{
		Main.m_UserID = m_UserTable.UserID[nRows];
		Main.m_UserLevel = m_UserTable.UserLevel[nRows];
		Main.m_UserPassword = m_UserTable.UserPass[nRows];
		
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_ID", Main.m_UserID);
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_LEVEL", Main.m_UserLevel);
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_PASSWORD", Main.m_UserPassword);

		EndDialog(IDOK);
	}
	else MessageBox("좆까");
	//if (a == 1)EndDialog(IDOK);
}


void DlgLogin::OnLbnSelchangeUserList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	nRows = m_UserList.GetCurSel();

	((CBtnEnh*)GetDlgItem(IDC_LOGIN_ID))->SetCaption(m_UserTable.UserID[nRows]);
	((CBtnEnh*)GetDlgItem(IDC_LOGIN_LEVEL))->SetCaption(m_UserTable.UserLevel[nRows]);
}
