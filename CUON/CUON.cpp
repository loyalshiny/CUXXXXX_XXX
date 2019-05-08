
// CUON.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CUON.h"
#include "MainFrm.h"

#include "CUONDoc.h"
#include "CUONView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCUONApp

BEGIN_MESSAGE_MAP(CCUONApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCUONApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CCUONApp 생성

CCUONApp::CCUONApp() noexcept
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 애플리케이션을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CUON.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CCUONApp 개체입니다.

CCUONApp theApp;


// CCUONApp 초기화

BOOL CCUONApp::InitInstance()
{
	CWinApp::InitInstance();

	////
	m_nLastAlid = 0;
	m_strLastAlarmDate = "";
	m_strLastAlarmTime = "";
	m_MDBfilePath = "";
	m_DiscofilePath = "";
	

	////////  REGISTER READ   
	


	char szBuff[0xFF];	memset(szBuff, '\0', 0xFF);

	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_NAME", szBuff, 0xFF))
	{
		m_Recipename = szBuff;
		//		m_StartInfo.m_RecipeName = szBuff;
		m_Recipename.TrimLeft();
		m_Recipename.TrimRight();

		m_Recipename;

		if (m_Recipename == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_NAME", "300MM");
			m_Recipename = "300MM";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_NAME", "300MM");
		m_Recipename = "300MM";

	}

	memset(szBuff, '\0', 0xFF);

	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_SIZE", szBuff, 0xFF))
	{
		m_Recipesize = szBuff;
		//		m_StartInfo.m_RecipeName = szBuff;
		m_Recipesize.TrimLeft();
		m_Recipesize.TrimRight();

		m_Recipesize;

		if (m_Recipesize == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_SIZE", "8INCH");
			m_Recipesize = "8INCH";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_SIZE", "8INCH");
		m_Recipesize = "8INCH";

	}

	

	memset(szBuff, '\0', 0xFF);

	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_ID", szBuff, 0xFF))
	{
		m_UserID = szBuff;
		m_UserID.TrimLeft();
		m_UserID.TrimRight();
		if (m_UserID == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_ID", "1234");
			m_UserID = "1234";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_ID", "1234");
		m_UserID = "1234";
	}

	memset(szBuff, '\0', 0xFF);

	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_LEVEL", szBuff, 0xFF))
	{
		m_UserLevel = szBuff;
		m_UserLevel.TrimLeft();
		m_UserLevel.TrimRight();

		if (m_UserLevel == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_LEVEL", "SUPPLY");
			m_UserLevel = "SUPPLY";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_LEVEL", "SUPPLY");
		m_UserLevel = "SUPPLY";
	}

	memset(szBuff, '\0', 0xFF);

	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_PASSWORD", szBuff, 0xFF))
	{
		m_UserPassword = szBuff;
		m_UserPassword.TrimLeft();
		m_UserPassword.TrimRight();
		if (m_UserPassword == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_PASSWORD", "1");
			m_UserPassword = "1234";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_USER_PASSWORD", "1");
		m_UserPassword = "1";
	}

	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_YEAR", szBuff, 0xFF))
	{
		m_Year = szBuff;
		m_Year.TrimLeft();
		m_Year.TrimRight();
		if (m_Year == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_YEAR", "2013");
			m_Year = "2013";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_YEAR", "2013");
		m_Year = "2013";
	}

	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_MONTH", szBuff, 0xFF))
	{
		m_Month = szBuff;
		m_Month.TrimLeft();
		m_Month.TrimRight();
		if (m_Month == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_MONTH", "01");
			m_Month = "01";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_MONTH", "01");
		m_Month = "01";
	}

	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_DAY", szBuff, 0xFF))
	{
		m_Day = szBuff;
		m_Day.TrimLeft();
		m_Day.TrimRight();
		if (m_Day == "")
		{
			RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_DAY", "01");
			m_Day = "01";
		}
	}
	else
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_DAY", "01");
		m_Day = "01";
	}

	//
	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "EQMODEL", szBuff, 0xFF))
	{
		SystemINIFiles.m_strModel = szBuff;
		SystemINIFiles.m_strModel.TrimLeft();
		SystemINIFiles.m_strModel.TrimRight();
	}
	//
	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "EQSN", szBuff, 0xFF))
	{
		SystemINIFiles.m_strSerialNo = szBuff;
		SystemINIFiles.m_strSerialNo.TrimLeft();
		SystemINIFiles.m_strSerialNo.TrimRight();
	}
	//
	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "CUSTOMER", szBuff, 0xFF))
	{
		SystemINIFiles.m_strCustomerName = szBuff;
		SystemINIFiles.m_strCustomerName.TrimLeft();
		SystemINIFiles.m_strCustomerName.TrimRight();
	}
	//
	/*memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "SFOFTVER", szBuff, 0xFF))
	{
		SystemINIFiles.m_strSoftVer = szBuff;
		SystemINIFiles.m_strSoftVer.TrimLeft();
		SystemINIFiles.m_strSoftVer.TrimRight();
	}*/
	SystemINIFiles.m_strSoftVer = gReadInterfaceFile("VERSION", "VER" );
	///
	//
	memset(szBuff, '\0', 0xFF);
	if (RegReadString(HKEY_CURRENT_USER, REGISTRY_KEY, "LANGUAGE", szBuff, 0xFF))
	{
		SystemINIFiles.m_strLanguage = szBuff;
		SystemINIFiles.m_strLanguage.TrimLeft();
		SystemINIFiles.m_strLanguage.TrimRight();
	}
	else if (SystemINIFiles.m_strLanguage == "")
	{
		RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "LANGUAGE", "ENGLISH");
		SystemINIFiles.m_strLanguage = "ENGLISH";
	}
	///
	
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.
	

	// 애플리케이션의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCUONDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CCUONView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	
	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	ReadConfig();

	char szMsg[LEN_GENERAL];	//	Message string

	if (ReadConfig() < 0)
	{
		strcpy(szMsg, "PLC Startup Failure (SYSTEM.ini).");
		//MessageBox( szMsg, "PLC Connection Fail", MB_OK );
		AfxMessageBox(szMsg, MB_OK);
		//	PostQuitMessage(0);
	}
	/*////////////////////////////////////////////////////////////////////////////*/
	CString strPath;

	strPath = "..\\..\\DATA\\SYSTEMFILES\\DataBase.mdb";
	m_pDatabase = new CADODatabase();
	m_pDatabase->SetConnectionString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + strPath + ";User Id=;Password=;");

	if (!m_pDatabase->Open())
	{
		AfxMessageBox("Can't open database file.");
		m_pDatabase->Close();
		Main.IsDBLoaded = 0;
		delete m_pDatabase;
		m_pDatabase = NULL;
	}
	else
	{
		Main.IsDBLoaded = 1;
	}
	/*////////////////////////////////////////////////////////////////////////////*/
	ReadConfigFile();

	
	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	//
	DlgLogin dlg;
	if (dlg.DoModal() == IDCANCEL)return 0;
	
	//
	
	//if (dlg.DoModal == IDOK) return FALSE;


	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CCUONApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CCUONApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CCUONApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCUONApp 메시지 처리기

int CCUONApp::ReadConfig()
{
	char	szFile[LEN_GENERAL];	//	ini file path
	char	szSection[LEN_COMMON], szKey[LEN_COMMON], szTemp[LEN_GENERAL];	//	ini file key

	int		nTemp;
	CString	sAppPath;

	CString strPath;
	strPath = SYSTEM_INI_FILE;


	strcpy(szFile, strPath);
	//	Read equipment communication information.
	strcpy(szSection, "PLC");
	strcpy(szKey, "IP");
	::GetPrivateProfileString(szSection, szKey, "", szTemp, sizeof(szTemp), szFile);
	if (strlen(szTemp) == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_sIP = szTemp; }

	strcpy(szKey, "Port");
	nTemp = ::GetPrivateProfileInt(szSection, szKey, 0, szFile);
	if (nTemp == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_nPort = nTemp; }


	strcpy(szSection, "TOUCHLOG");
	strcpy(szKey, "MAXCOUNT");
	nTemp = ::GetPrivateProfileInt(szSection, szKey, 0, szFile);
	if (nTemp == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_nOperationMaxCount = nTemp; }

	strcpy(szSection, "ALARMLOG");
	strcpy(szKey, "MAXCOUNT");
	nTemp = ::GetPrivateProfileInt(szSection, szKey, 0, szFile);
	if (nTemp == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_nAlarmMaxCount = nTemp; }

	strcpy(szSection, "WORKLOG");
	strcpy(szKey, "MAXCOUNT");
	nTemp = ::GetPrivateProfileInt(szSection, szKey, 0, szFile);
	if (nTemp == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_nProductMaxCount = nTemp; }


	/*strcpy(szSection, "CUSTOMER");
	strcpy(szKey, "NAME");
	::GetPrivateProfileString(szSection, szKey, "", szTemp, sizeof(szTemp), szFile);
	if (strlen(szTemp) == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_strCustomerName = szTemp; }

	strcpy(szSection, "CUSTOMER");
	strcpy(szKey, "PLACE");
	::GetPrivateProfileString(szSection, szKey, "", szTemp, sizeof(szTemp), szFile);
	if (strlen(szTemp) == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_strCustomerPlace = szTemp; }

	strcpy(szSection, "CUSTOMER");
	strcpy(szKey, "SERIALNO");
	::GetPrivateProfileString(szSection, szKey, "", szTemp, sizeof(szTemp), szFile);
	if (strlen(szTemp) == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_strSerialNo = szTemp; }

	strcpy(szSection, "CUSTOMER");
	strcpy(szKey, "SOFTVER");
	::GetPrivateProfileString(szSection, szKey, "", szTemp, sizeof(szTemp), szFile);
	if (strlen(szTemp) == 0) { return EHI_READ_START_INFO; }
	else { SystemINIFiles.m_strSoftVer = szTemp; }*/


	return EHI_NO_ERR;
}
// CCUON_SOLUTIONApp 메시지 처리기
// CCUONApp 메시지 처리기

void CCUONApp::ReadConfigFile()
{
	CString strPath;
	strPath = GEM_INI_FILE;

	char szValue[0xFF];
	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_PORT, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nPort = atol(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_DEVICEID, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nDeviceID = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_T3, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nT3 = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_T5, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nT5 = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_T6, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nT6 = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_T7, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nT7 = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_T8, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nT8 = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_LINKTEST, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nLinkInterval = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(HSMS, HSMS_RETRY, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nRetry = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, GEM_DEFAULT_CONTROLSTATE, "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nDefaultControlState = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "CommRequestTimeout", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nCommReqeustTimeout = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "MDLN", "", szValue, sizeof(szValue), strPath))
		sprintf(m_GemLogConfig.m_szModelName, szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "SOFTREV", "", szValue, sizeof(szValue), strPath))
		sprintf(m_GemLogConfig.m_szSoftRev, szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "TimeFormat", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nTimeFormat = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "MaxLogSize", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nMaxLogSize = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "LogRetension", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nLogRetention = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "ALogRetension", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nALogRetention = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "WLogRetension", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nWLogRetention = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "OLogRetension", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_nOLogRetention = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "LogEnable", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_bLogEnable = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "WLogEnable", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_bWLogEnable = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "OLogEnable", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_bOLogEnable = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(GEM_GEM, "ALogEnable", "", szValue, sizeof(szValue), strPath))
		m_GemLogConfig.m_bALogEnable = atoi(szValue);

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString("GEM", "DISCOPATH", "", szValue, sizeof(szValue), strPath))
		m_DiscofilePath = szValue;


	//	ZeroMemory(szValue, 0xFF);
	//	if (GetPrivateProfileString("GEM", "LASERPOWER","",szValue,sizeof(szValue), strPath))
	//	strReturn = szValue;
	//	m_GemLogConfig.m_strLaserPower = strReturn;
	//Main.m_strLaserPower= strReturn;

}

void CCUONApp::WriteConfigFile()
{
	char szValue[0xFF];
	CString strPath;
	strPath = GEM_INI_FILE;

	sprintf(szValue, "%ld", m_GemLogConfig.m_nPort);
	WritePrivateProfileString(HSMS, HSMS_PORT, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nDeviceID);
	WritePrivateProfileString(HSMS, HSMS_DEVICEID, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nLinkInterval);
	WritePrivateProfileString(HSMS, HSMS_LINKTEST, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nRetry);
	WritePrivateProfileString(HSMS, HSMS_RETRY, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nT3);
	WritePrivateProfileString(HSMS, HSMS_T3, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nT5);
	WritePrivateProfileString(HSMS, HSMS_T5, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nT6);
	WritePrivateProfileString(HSMS, HSMS_T6, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nT7);
	WritePrivateProfileString(HSMS, HSMS_T7, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nT8);
	WritePrivateProfileString(HSMS, HSMS_T8, szValue, strPath);

	sprintf(szValue, "%d", m_GemLogConfig.m_nDefaultControlState);
	WritePrivateProfileString(GEM_GEM, GEM_DEFAULT_CONTROLSTATE, szValue, strPath);

}



