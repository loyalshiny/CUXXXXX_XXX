// DlgLoadPortSetting.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgLoadPortSetting.h"
#include "afxdialogex.h"
#include <windows.h>
CBtnEnh* m_pbtnenhPanel;
// DlgLoadPortSetting 대화 상자

IMPLEMENT_DYNAMIC(DlgLoadPortSetting, CDialogEx)

DlgLoadPortSetting::DlgLoadPortSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOADPORT_SETTING, pParent)
{

	g_nPort = 0;
}

DlgLoadPortSetting::~DlgLoadPortSetting()
{
}

void DlgLoadPortSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MSCOMM1, m_ComOp[1]);
	DDX_Control(pDX, IDC_MSCOMM2, m_ComOp[2]);
	DDX_Control(pDX, IDC_MSCOMM3, m_ComOp[3]);
	DDX_Control(pDX, IDC_MSCOMM4, m_ComOp[4]);
	DDX_Control(pDX, IDC_MSCOMM5, m_ComOp[5]);
	DDX_Control(pDX, IDC_MSCOMM6, m_ComOp[6]);
	DDX_Control(pDX, IDC_MSCOMM7, m_ComRp[1]);
	DDX_Control(pDX, IDC_MSCOMM8, m_ComRp[2]);
	DDX_Control(pDX, IDC_MSCOMM9, m_ComRp[3]);
	DDX_Control(pDX, IDC_MSCOMM10, m_ComRp[4]);
	DDX_Control(pDX, IDC_MSCOMM11, m_ComRp[5]);
	DDX_Control(pDX, IDC_MSCOMM12, m_ComRp[6]);
	
	DDX_Control(pDX, IDC_COMBO_COM, m_ComboOC);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboOP);
	DDX_Control(pDX, IDC_COMBO_COM2, m_ComboRC);
	DDX_Control(pDX, IDC_COMBO_PORT2, m_ComboRP);
}


BEGIN_MESSAGE_MAP(DlgLoadPortSetting, CDialogEx)
	ON_WM_TIMER()
	ON_CBN_DROPDOWN(IDC_COMBO_PORT, &DlgLoadPortSetting::OnCbnDropdownComboPort)
	ON_CBN_DROPDOWN(IDC_COMBO_COM, &DlgLoadPortSetting::OnCbnDropdownComboCom)
	ON_BN_CLICKED(IDC_OPENER_OPEN, &DlgLoadPortSetting::OnBnClickedOpenerOpen)
	ON_BN_CLICKED(IDC_OPENER_SET, &DlgLoadPortSetting::OnBnClickedOpenerSet)
	ON_CBN_SELCHANGE(IDC_COMBO_COM, &DlgLoadPortSetting::OnCbnSelchangeComboCom)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, &DlgLoadPortSetting::OnCbnSelchangeComboPort)
	ON_CBN_DROPDOWN(IDC_COMBO_COM2, &DlgLoadPortSetting::OnCbnDropdownComboCom2)
	ON_BN_CLICKED(IDC_RFID_SET, &DlgLoadPortSetting::OnBnClickedRfidSet)
	ON_BN_CLICKED(IDC_RFID_OPEN, &DlgLoadPortSetting::OnBnClickedRfidOpen)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT2, &DlgLoadPortSetting::OnCbnSelchangeComboPort2)
END_MESSAGE_MAP()


// DlgLoadPortSetting 메시지 처리기


BOOL DlgLoadPortSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	g_nOpPort =0;
	g_nOpComport = 0;
	SetTimer(0, 500, NULL);
	SetBackgroundColor(SILVER);
	OnInititalComportOpener();
	OnInititalComportRfid();

	getSerialPort(1);
	getSerialPort(2);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgLoadPortSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgLoadPortSetting::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}



void DlgLoadPortSetting::getSerialPort(short nSelect)
{
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	if(nSelect == 1)m_ComboOC.ResetContent();
	else if (nSelect == 2)m_ComboRC.ResetContent();

	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));



	//hKey - 레지스터키 핸들  
	//index - 값을 가져올 인덱스.. 다수의 값이 있을 경우 필요  
	//szName - 항목값이 저장될 배열  
	//dwSize - 배열의 크기  
	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		index++;


		//szName-레지터스터 항목의 이름  
		//dwType-항목의 타입, 여기에서는 널로 끝나는 문자열  
		//szData-항목값이 저장될 배열  
		//dwSize2-배열의 크기  
		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		if (nSelect == 1)m_ComboOC.AddString(CString(szData));
		else if (nSelect == 2)m_ComboRC.AddString(CString(szData));
		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}
	RegCloseKey(hKey);
}

void DlgLoadPortSetting::OnInititalComportOpener()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	CString strData;
	CString strComport;
	
	for (int i = 0; i < 6; i++)
	{
		strTemp.Format("PORT%d",i+1);
		strData = ReadComportSettingFile("OPENER", strTemp);
		if (strData != "")OpenerCommPortOpen(OnComportNumberTransfer(strData), i + 1);
	}
}

void DlgLoadPortSetting::OnInititalComportRfid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	CString strData;
	CString strComport;

	for (int i = 0; i < 6; i++)
	{
		strTemp.Format("PORT%d", i + 1);
		strData = ReadComportSettingFile("RFID", strTemp);
		if (strData != "")RfidCommPortOpen(OnComportNumberTransfer(strData), i + 1);
	}
}
void DlgLoadPortSetting::OpenerCommPortOpen(short nComPort, short nLoadPort)
{
	m_ComOp[nLoadPort].SetCommPort(nComPort);
	m_ComOp[nLoadPort].SetSettings("9600, N, 8, 1");
	m_ComOp[nLoadPort].SetInputLen(1);
	m_ComOp[nLoadPort].SetInputMode(0);
	m_ComOp[nLoadPort].SetRTSEnable(TRUE);
	m_ComOp[nLoadPort].SetRThreshold(1);
	m_ComOp[nLoadPort].SetPortOpen(true);
}

void DlgLoadPortSetting::RfidCommPortOpen(short nComPort, short nLoadPort)
{
	m_ComRp[nLoadPort].SetCommPort(nComPort);
	m_ComRp[nLoadPort].SetSettings("9600, N, 8, 1");
	m_ComRp[nLoadPort].SetInputLen(1);
	m_ComRp[nLoadPort].SetInputMode(0);
	m_ComRp[nLoadPort].SetRTSEnable(TRUE);
	m_ComRp[nLoadPort].SetRThreshold(1);
	m_ComRp[nLoadPort].SetPortOpen(true);

	
}
void DlgLoadPortSetting::OpenerCommPortClose(short nComPort, short nLoadPort)
{

	m_ComOp[nLoadPort].SetPortOpen(FALSE);
}
void DlgLoadPortSetting::RfidCommPortClose(short nComPort, short nLoadPort)
{

	m_ComRp[nLoadPort].SetPortOpen(FALSE);
}
int DlgLoadPortSetting::OnComportNumberTransfer(CString strComport)
{
	char ch;
	CString strResult= "";
	if (strComport != "")
	{
		for (int i = 0; i < strComport.GetLength(); i++)
		{
			ch = strComport.GetAt(i);
			if (ch >= '0' && ch <= '9')
				strResult += ch;
		}
	}
	return atoi(strResult);
}

void DlgLoadPortSetting::OnCbnDropdownComboCom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	getSerialPort(1);
}
void DlgLoadPortSetting::OnCbnDropdownComboCom2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	getSerialPort(2);
}





void DlgLoadPortSetting::OnBnClickedOpenerOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	short nLP = 0;
	short nCP = 0;
	int nSel;
	CString strTemp;
	CString strData;
	nLP = m_ComboOP.GetCurSel();
	nSel = m_ComboOC.GetCurSel();
	m_ComboOC.GetLBText(nSel, strTemp);
	nCP = OnComportNumberTransfer(strTemp);

	GetDlgItemText(IDC_OPENER_OPEN, strData);
	if (strData == "OPEN")
	{
		OpenerCommPortOpen(nCP, nLP + 1);
		OnCheckOpenerComPort();
	}else if (strData == "CLOSE")
	{
		OpenerCommPortClose(nCP, nLP + 1);
		OnCheckOpenerComPort();
	}
}


void DlgLoadPortSetting::OnBnClickedOpenerSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel;
	CString strComport;
	CString strPort;
	nSel = m_ComboOC.GetCurSel();
	m_ComboOC.GetLBText(nSel, strComport);
	
	nSel = m_ComboOP.GetCurSel();
	m_ComboOP.GetLBText(nSel, strPort);

	WriteComportSettingFile("OPENER", strPort, strComport);
}

void DlgLoadPortSetting::OnBnClickedRfidOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	short nLP = 0;
	short nCP = 0;
	int nSel;
	CString strTemp;
	CString strData;
	nLP = m_ComboRP.GetCurSel();
	nSel = m_ComboRC.GetCurSel();
	m_ComboRC.GetLBText(nSel, strTemp);
	nCP = OnComportNumberTransfer(strTemp);

	GetDlgItemText(IDC_RFID_OPEN, strData);
	if (strData == "OPEN")
	{
		RfidCommPortOpen(nCP, nLP + 1);
		OnCheckRfidComPort();
	}
	else if (strData == "CLOSE")
	{
		RfidCommPortClose(nCP, nLP + 1);
		OnCheckRfidComPort();
	}
}


void DlgLoadPortSetting::OnBnClickedRfidSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel;
	CString strComport;
	CString strPort;
	nSel = m_ComboRC.GetCurSel();
	m_ComboRC.GetLBText(nSel, strComport);

	nSel = m_ComboRP.GetCurSel();
	m_ComboRP.GetLBText(nSel, strPort);

	WriteComportSettingFile("RFID", strPort, strComport);
}




void DlgLoadPortSetting::OnCbnDropdownComboPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void DlgLoadPortSetting::OnCbnSelchangeComboCom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void DlgLoadPortSetting::OnCbnSelchangeComboPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCheckOpenerComPort();
}
void DlgLoadPortSetting::OnCbnSelchangeComboPort2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCheckRfidComPort();
}

void DlgLoadPortSetting::OnCheckOpenerComPort(/*short nComPort, short nLoadPort*/)
{
	CString strData;
	CString strTemp;
	int nSelPort;
	int nSel;
	short nComPort;
	short nCheck = 0;
	nSelPort = m_ComboOP.GetCurSel();
	m_ComboOP.GetLBText(nSelPort, strTemp);
	strData = ReadComportSettingFile("OPENER", strTemp);

	nSel = m_ComboOC.FindString(0, strData);
	m_ComboOC.SetCurSel(nSel);

	if (strData != "")
	{
		nComPort = OnComportNumberTransfer(strData);
		nCheck = m_ComOp[nSelPort + 1].GetPortOpen();
	}
	else nCheck = 0;
	if (nCheck)
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_OPENER_LED);
		m_pbtnenhPanel->SetBackColor(GREEN);
		GetDlgItem(IDC_OPENER_OPEN)->SetWindowText("CLOSE");
	}
	else
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_OPENER_LED);
		m_pbtnenhPanel->SetBackColor(RED);
		GetDlgItem(IDC_OPENER_OPEN)->SetWindowText("OPEN");
	}
}

void DlgLoadPortSetting::OnCheckRfidComPort(/*short nComPort, short nLoadPort*/)
{
	CString strData;
	CString strTemp;
	int nSelPort;
	int nSel;
	short nComPort;
	short nCheck = 0;
	nSelPort = m_ComboRP.GetCurSel();
	m_ComboRP.GetLBText(nSelPort, strTemp);
	strData = ReadComportSettingFile("RFID", strTemp);

	nSel = m_ComboRC.FindString(0, strData);
	m_ComboRC.SetCurSel(nSel);

	if (strData != "")
	{
		nComPort = OnComportNumberTransfer(strData);
		nCheck = m_ComRp[nSelPort + 1].GetPortOpen();
	}
	else nCheck = 0;
	if (nCheck)
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_RFID_LED);
		m_pbtnenhPanel->SetBackColor(GREEN);
		GetDlgItem(IDC_RFID_OPEN)->SetWindowText("CLOSE");
	}
	else
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_RFID_LED);
		m_pbtnenhPanel->SetBackColor(RED);
		GetDlgItem(IDC_RFID_OPEN)->SetWindowText("OPEN");
	}
}



