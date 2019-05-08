// DlgGemParameter.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CUON.h"
#include "DlgGemParameter.h"
#include "afxdialogex.h"


// DlgGemParameter 대화 상자

IMPLEMENT_DYNAMIC(DlgGemParameter, CDialogEx)

DlgGemParameter::DlgGemParameter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GEM_PARAMETER, pParent)
{
	m_strIP = "";
	m_strPort = "";
	m_strDeviceID = "";
	m_strT3 = "";
	m_strT5 = "";
	m_strT6 = "";
	m_strT7 = "";
	m_strT8 = "";
	m_strLinkTest = "";
	m_strRetryLimit = "";
}

DlgGemParameter::~DlgGemParameter()
{
}

void DlgGemParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_DEVICEID, m_strDeviceID);
	DDX_Text(pDX, IDC_EDIT_T3, m_strT3);
	DDX_Text(pDX, IDC_EDIT_T5, m_strT5);
	DDX_Text(pDX, IDC_EDIT_T6, m_strT6);
	DDX_Text(pDX, IDC_EDIT_T7, m_strT7);
	DDX_Text(pDX, IDC_EDIT_T8, m_strT8);
	DDX_Text(pDX, IDC_EDIT_LINKTEST, m_strLinkTest);
	DDX_Text(pDX, IDC_EDIT_RETRYLIMIT, m_strRetryLimit);
}


BEGIN_MESSAGE_MAP(DlgGemParameter, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgGemParameter::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgGemParameter::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgGemParameter 메시지 처리기

BOOL DlgGemParameter::OnInitDialog()
{
	CDialog::OnInitDialog();
	ShowConfig();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgGemParameter::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::PreTranslateMessage(pMsg);
}

void DlgGemParameter::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_strPort == "")
	{
		AfxMessageBox("Port cannot be empty !");
		GetDlgItem(IDC_EDIT_PORT)->SetFocus();
		return;
	}
	if (m_strDeviceID == "")
	{
		AfxMessageBox("Device ID cannot be empty !");
		GetDlgItem(IDC_EDIT_DEVICEID)->SetFocus();
		return;
	}
	if (m_strT3 == "")
	{
		AfxMessageBox("T3 timeout cannot be empty !");
		GetDlgItem(IDC_EDIT_T3)->SetFocus();
		return;
	}
	if (m_strT5 == "")
	{
		AfxMessageBox("T5 timeout cannot be empty");
		GetDlgItem(IDC_EDIT_T5)->SetFocus();
		return;
	}
	if (m_strT6 == "")
	{
		AfxMessageBox("T6 timeout cannot be empty");
		GetDlgItem(IDC_EDIT_T6)->SetFocus();
		return;
	}
	if (m_strT7 == "")
	{
		AfxMessageBox("T7 timeout cannot be empty");
		GetDlgItem(IDC_EDIT_T7)->SetFocus();
		return;
	}
	if (m_strT8 == "")
	{
		AfxMessageBox("T8 timeout cannot be empty");
		GetDlgItem(IDC_EDIT_T8)->SetFocus();
		return;
	}
	if (m_strLinkTest == "")
	{
		AfxMessageBox("Linktest interval cannot be empty !");
		GetDlgItem(IDC_EDIT_LINKTEST)->SetFocus();
		return;
	}
	if (m_strRetryLimit == "")
	{
		AfxMessageBox("Retry limit cannot be empty !");
		GetDlgItem(IDC_EDIT_RETRYLIMIT)->SetFocus();
		return;
	}

	GemParameterSave();
	CDialogEx::OnOK();
}

void DlgGemParameter::GemParameterSave()
{
	CString strTemp = _T("");
	CString strECID = _T("");
	CString strValue = _T("");
	//PORT ID
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(strTemp);
	m_GemLogConfig.m_nPort = atoi(strTemp);

	//----------------------------------------------------------------------------------------

	//DEVICE ID
	GetDlgItem(IDC_EDIT_DEVICEID)->GetWindowText(strTemp);
	m_GemLogConfig.m_nDeviceID = atoi(strTemp);


	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_LINKTEST)->GetWindowText(strTemp);
	m_GemLogConfig.m_nLinkInterval = atoi(strTemp);

	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_RETRYLIMIT)->GetWindowText(strTemp);
	m_GemLogConfig.m_nRetry = atoi(strTemp);


	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_T3)->GetWindowText(strTemp);
	m_GemLogConfig.m_nT3 = atoi(strTemp);


	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_T5)->GetWindowText(strTemp);
	m_GemLogConfig.m_nT5 = atoi(strTemp);


	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_T6)->GetWindowText(strTemp);
	m_GemLogConfig.m_nT6 = atoi(strTemp);


	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_T7)->GetWindowText(strTemp);
	m_GemLogConfig.m_nT7 = atoi(strTemp);


	//----------------------------------------------------------------------------------------
	GetDlgItem(IDC_EDIT_T8)->GetWindowText(strTemp);
	m_GemLogConfig.m_nT8 = atoi(strTemp);




	//=== set retention ====//



	theApp.WriteConfigFile();

}


void DlgGemParameter::ShowConfig()
{

	theApp.ReadConfigFile();

	CString strTemp = _T("");
	strTemp.Format("%ld", m_GemLogConfig.m_nPort);
	SetDlgItemText(IDC_EDIT_PORT, strTemp);

	//DEVICE ID
	strTemp.Format("%d", m_GemLogConfig.m_nDeviceID);
	SetDlgItemText(IDC_EDIT_DEVICEID, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nLinkInterval);
	SetDlgItemText(IDC_EDIT_LINKTEST, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nRetry);
	SetDlgItemText(IDC_EDIT_RETRYLIMIT, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nT3);
	SetDlgItemText(IDC_EDIT_T3, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nT5);
	SetDlgItemText(IDC_EDIT_T5, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nT6);
	SetDlgItemText(IDC_EDIT_T6, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nT7);
	SetDlgItemText(IDC_EDIT_T7, strTemp);
	//----------------------------------------------------------------------------------------
	strTemp.Format("%d", m_GemLogConfig.m_nT8);
	SetDlgItemText(IDC_EDIT_T8, strTemp);
	//----------------------------------------------------------------------------------------
}

void DlgGemParameter::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
