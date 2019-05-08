
// CUONView.cpp: CCUONView 클래스의 구현
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CUON.h"
#endif

#include "PlcThread.h"
#include "CUONDoc.h"
#include "CUONView.h"
#include "MainFrm.h"
#include "DlgLogin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCUONView

IMPLEMENT_DYNCREATE(CCUONView, CFormView)//gkdldua

BEGIN_MESSAGE_MAP(CCUONView, CFormView)
	ON_WM_CTLCOLOR()
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CCUONView::OnSelchangeTab1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CCUONView::OnBnClickedButton1)
END_MESSAGE_MAP()

// CCUONView 생성/소멸
///
//
///
CCUONView::CCUONView() noexcept
	: CFormView(IDD_CUON_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pDlgMain = NULL;
	m_pDlgGem = NULL;
	m_pDlgSystemSetting = NULL;
	m_pClientSock = NULL;
	m_pDlgLoadPort = NULL;
	m_pDlgLoadPortSetting = NULL;
	m_pDlgErrorDisplay = NULL;
	m_pDlgLog = NULL;
	m_hBrush = (HBRUSH) ::CreateSolidBrush(RGB(128,128,128));
}

CCUONView::~CCUONView()
{
	DeleteObject(m_hBrush);
}

void CCUONView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_EXIT, m_MainExit);

}

BOOL CCUONView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs 를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CCUONView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	CString strTemp;
	SystemINIFiles.m_fSatus = FALSE;
	if (SystemINIFiles.m_fConn == FALSE && SystemINIFiles.m_fActive == FALSE)AfxBeginThread(RUNTIME_CLASS(CPlcThread));

	OnButtonCheck();
	OperatorList();
	GetAlarmFromTable(m_aAlarm);			
	GetOperatorFromTable(m_aOperation);	// Operator data Read; 

	m_RecipeTable.Name = ((CCUONApp*)AfxGetApp())->m_Recipename;
	m_RecipeTable.WaferSize = ((CCUONApp*)AfxGetApp())->m_Recipesize;
	Main.m_UserPassword = ((CCUONApp*)AfxGetApp())->m_UserPassword;
	Main.m_UserID = ((CCUONApp*)AfxGetApp())->m_UserID;			////Recipe Number Read
	Main.m_UserLevel = ((CCUONApp*)AfxGetApp())->m_UserLevel;

	gRecipeLoad();
	gRecipeFileLoad(m_RecipeTable.Name);

	gMotorLoad();
	gMotorFileLoad("M1");

	MemoryInitialize();

	m_pDlgMain = new DlgMain;
	m_pDlgMain->Create(IDD_DIALOG_MAIN,this);
	m_pDlgMain->MoveWindow(0, 0, 1278, 844);
	m_pDlgMain->ShowWindow(SW_SHOW);
	
	m_pDlgGem = new DlgGem;
	m_pDlgGem->Create(IDD_DIALOG_GEM, this);
	m_pDlgGem->MoveWindow(0, 0, 1278, 844);
	m_pDlgGem->ShowWindow(SW_HIDE);

	m_pDlgSystemSetting = new DlgSystemSetting;
	m_pDlgSystemSetting->Create(IDD_DIALOG_SYSTEM_SETTING, this);
	m_pDlgSystemSetting->MoveWindow(0, 0, 1278, 844);
	m_pDlgSystemSetting->ShowWindow(SW_HIDE);

	m_pDlgErrorDisplay = new DlgErrorDisplay;
	m_pDlgErrorDisplay->Create(IDD_DIALOG_ERROR_DISPLAY, this);
	m_pDlgErrorDisplay->ShowWindow(SW_HIDE);
	//m_pDlgErrorDisplay->MoveWindow(0, 100, 1078, 844);

	m_pDlgLog = new DlgLog;
	m_pDlgLog->Create(IDD_DIALOG_LOG, this);
	m_pDlgLog->MoveWindow(0, 0, 1278, 844);
	m_pDlgLog->ShowWindow(SW_HIDE);

	int a = 0;
	((CButton*)GetDlgItem(IDC_BUT_AUTO))->SetCheck(1);
	
	SetTimer(0, 1000, NULL);

}


// CCUONView 진단

#ifdef _DEBUG
void CCUONView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCUONView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCUONDoc* CCUONView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCUONDoc)));
	return (CCUONDoc*)m_pDocument;
}
#endif //_DEBUG


// CCUONView 메시지 처리기


HBRUSH CCUONView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return m_hBrush;
}
void CCUONView::OnButtonCheck()
{
	if (gReadInterfaceFile("MAIN", "LOG") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_BUT_LOG))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("MAIN", "RECIPE") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_BUT_RECIPE))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("MAIN", "CST") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_BUT_CST))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("MAIN", "SECS_GEM") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_BUT_GEM))->ShowWindow(SW_HIDE);
	if (gReadInterfaceFile("MAIN", "CAMERA") != "ENABLE")((CBtnEnh*)GetDlgItem(IDC_BUT_CAMERA))->ShowWindow(SW_HIDE);

	if (SystemINIFiles.m_strLanguage == "ENGLISH")
	{
		((CBtnEnh*)GetDlgItem(IDC_BUT_AUTO))->SetCaption("AUTO MODE");
		((CBtnEnh*)GetDlgItem(IDC_BUT_SYSTEM))->SetCaption("SYSTEM SETTING");
		((CBtnEnh*)GetDlgItem(IDC_BUT_LOG))->SetCaption("LOG");
		((CBtnEnh*)GetDlgItem(IDC_BUT_RECIPE))->SetCaption("RECIPE");
		((CBtnEnh*)GetDlgItem(IDC_BUT_CST))->SetCaption("CST");
		((CBtnEnh*)GetDlgItem(IDC_BUT_GEM))->SetCaption("SECS/GEM");
		((CBtnEnh*)GetDlgItem(IDC_BUT_CAMERA))->SetCaption("CAMERA");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_EXIT))->SetCaption("EXIT");
	}
	else if(SystemINIFiles.m_strLanguage =="KOREAN")
	{
		((CBtnEnh*)GetDlgItem(IDC_BUT_AUTO))->SetCaption("자동 모드");
		((CBtnEnh*)GetDlgItem(IDC_BUT_SYSTEM))->SetCaption("시스템	설정");
		((CBtnEnh*)GetDlgItem(IDC_BUT_LOG))->SetCaption("작업 내역");
		((CBtnEnh*)GetDlgItem(IDC_BUT_RECIPE))->SetCaption("레시피");
		((CBtnEnh*)GetDlgItem(IDC_BUT_CST))->SetCaption("카세트");
		((CBtnEnh*)GetDlgItem(IDC_BUT_GEM))->SetCaption("SECS/GEM");
		((CBtnEnh*)GetDlgItem(IDC_BUT_CAMERA))->SetCaption("카메라");
		((CBtnEnh*)GetDlgItem(IDC_MAIN_EXIT))->SetCaption("종료");
	}
	((CBtnEnh*)GetDlgItem(IDC_MAIN_EXIT))->SetPicture("..\\..\\Button\\EXIT.png");
	

}
void CCUONView::OnMotorDataRead()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	mtrpara[0].hsen_level = M1HOME;
	mtrpara[0].plmt_level = M1PLMT;
	mtrpara[0].nlmt_level = M1NLMT;
	mtrpara[0].inpos_enb = M1BUSY;
	mtrpara[1].hsen_level = M2HOME;
	mtrpara[1].plmt_level = M2PLMT;
	mtrpara[1].nlmt_level = M2NLMT;
	mtrpara[1].inpos_enb = M2BUSY;
	mtrpara[2].hsen_level = M3HOME;
	mtrpara[2].plmt_level = M3PLMT;
	mtrpara[2].nlmt_level = M3NLMT;
	mtrpara[2].inpos_enb = M3BUSY;
	mtrpara[3].hsen_level = M4HOME;
	mtrpara[3].plmt_level = M4PLMT;
	mtrpara[3].nlmt_level = M4NLMT;
	mtrpara[3].inpos_enb = M4BUSY;

	mtrpara[4].hsen_level = M5HOME;
	mtrpara[4].plmt_level = M5PLMT;
	mtrpara[4].nlmt_level = M5NLMT;
	mtrpara[4].inpos_enb = M5BUSY;
	mtrpara[5].hsen_level = M6HOME;
	mtrpara[5].plmt_level = M6PLMT;
	mtrpara[5].nlmt_level = M6NLMT;
	mtrpara[5].inpos_enb = M6BUSY;
	mtrpara[6].hsen_level = M7HOME;
	mtrpara[6].plmt_level = M7PLMT;
	mtrpara[6].nlmt_level = M7NLMT;
	mtrpara[6].inpos_enb = M7BUSY;
	mtrpara[7].hsen_level = M8HOME;
	mtrpara[7].plmt_level = M8PLMT;
	mtrpara[7].nlmt_level = M8NLMT;
	mtrpara[7].inpos_enb = M8BUSY;

	mtrpara[8].hsen_level = M9HOME;
	mtrpara[8].plmt_level = M9PLMT;
	mtrpara[8].nlmt_level = M9NLMT;
	mtrpara[8].inpos_enb = M9BUSY;
	mtrpara[9].hsen_level = M10HOME;
	mtrpara[9].plmt_level = M10PLMT;
	mtrpara[9].nlmt_level = M10NLMT;
	mtrpara[9].inpos_enb = M10BUSY;
	mtrpara[10].hsen_level = M11HOME;
	mtrpara[10].plmt_level = M11PLMT;
	mtrpara[10].nlmt_level = M11NLMT;
	mtrpara[10].inpos_enb = M11BUSY;
	mtrpara[11].hsen_level = M12HOME;
	mtrpara[11].plmt_level = M12PLMT;
	mtrpara[11].nlmt_level = M12NLMT;
	mtrpara[11].inpos_enb = M12BUSY;

	mtrpara[12].hsen_level = M13HOME;
	mtrpara[12].plmt_level = M13PLMT;
	mtrpara[12].nlmt_level = M13NLMT;
	mtrpara[12].inpos_enb = M13BUSY;
	mtrpara[13].hsen_level = M14HOME;
	mtrpara[13].plmt_level = M14PLMT;
	mtrpara[13].nlmt_level = M14NLMT;
	mtrpara[13].inpos_enb = M14BUSY;
	mtrpara[14].hsen_level = M15HOME;
	mtrpara[14].plmt_level = M15PLMT;
	mtrpara[14].nlmt_level = M15NLMT;
	mtrpara[14].inpos_enb = M15BUSY;
	mtrpara[15].hsen_level = M16HOME;
	mtrpara[15].plmt_level = M16PLMT;
	mtrpara[15].nlmt_level = M16NLMT;
	mtrpara[15].inpos_enb = M16BUSY;

	mtrpara[16].hsen_level = M17HOME;
	mtrpara[16].plmt_level = M17PLMT;
	mtrpara[16].nlmt_level = M17NLMT;
	mtrpara[16].inpos_enb = M17BUSY;
	mtrpara[17].hsen_level = M18HOME;
	mtrpara[17].plmt_level = M18PLMT;
	mtrpara[17].nlmt_level = M18NLMT;
	mtrpara[17].inpos_enb = M18BUSY;
	mtrpara[18].hsen_level = M19HOME;
	mtrpara[18].plmt_level = M19PLMT;
	mtrpara[18].nlmt_level = M19NLMT;
	mtrpara[18].inpos_enb = M19BUSY;
	mtrpara[19].hsen_level = M20HOME;
	mtrpara[19].plmt_level = M20PLMT;
	mtrpara[19].nlmt_level = M20NLMT;
	mtrpara[19].inpos_enb = M20BUSY;

	mtrpara[20].hsen_level = M21HOME;
	mtrpara[20].plmt_level = M21PLMT;
	mtrpara[20].nlmt_level = M21NLMT;
	mtrpara[20].inpos_enb = M21BUSY;
	mtrpara[21].hsen_level = M22HOME;
	mtrpara[21].plmt_level = M22PLMT;
	mtrpara[21].nlmt_level = M22NLMT;
	mtrpara[21].inpos_enb = M22BUSY;
	mtrpara[22].hsen_level = M23HOME;
	mtrpara[22].plmt_level = M23PLMT;
	mtrpara[22].nlmt_level = M23NLMT;
	mtrpara[22].inpos_enb = M23BUSY;
	mtrpara[23].hsen_level = M24HOME;
	mtrpara[23].plmt_level = M24PLMT;
	mtrpara[23].nlmt_level = M24NLMT;
	mtrpara[23].inpos_enb = M24BUSY;

	mtrpara[24].hsen_level = M25HOME;
	mtrpara[24].plmt_level = M25PLMT;
	mtrpara[24].nlmt_level = M25NLMT;
	mtrpara[24].inpos_enb = M25BUSY;
	mtrpara[25].hsen_level = M26HOME;
	mtrpara[25].plmt_level = M26PLMT;
	mtrpara[25].nlmt_level = M26NLMT;
	mtrpara[25].inpos_enb = M26BUSY;
	mtrpara[26].hsen_level = M27HOME;
	mtrpara[26].plmt_level = M27PLMT;
	mtrpara[26].nlmt_level = M27NLMT;
	mtrpara[26].inpos_enb = M27BUSY;
	mtrpara[27].hsen_level = M28HOME;
	mtrpara[27].plmt_level = M28PLMT;
	mtrpara[27].nlmt_level = M28NLMT;
	mtrpara[27].inpos_enb = M28BUSY;

	mtrpara[28].hsen_level = M29HOME;
	mtrpara[28].plmt_level = M29PLMT;
	mtrpara[28].nlmt_level = M29NLMT;
	mtrpara[28].inpos_enb = M29BUSY;
	mtrpara[29].hsen_level = M30HOME;
	mtrpara[29].plmt_level = M30PLMT;
	mtrpara[29].nlmt_level = M30NLMT;
	mtrpara[29].inpos_enb = M30BUSY;
	mtrpara[30].hsen_level = M31HOME;
	mtrpara[30].plmt_level = M31PLMT;
	mtrpara[30].nlmt_level = M31NLMT;
	mtrpara[30].inpos_enb = M31BUSY;
	mtrpara[31].hsen_level = M32HOME;
	mtrpara[31].plmt_level = M32PLMT;
	mtrpara[31].nlmt_level = M32NLMT;
	mtrpara[31].inpos_enb = M32BUSY;

	mtrpara[32].hsen_level = M33HOME;
	mtrpara[32].plmt_level = M33PLMT;
	mtrpara[32].nlmt_level = M33NLMT;
	mtrpara[32].inpos_enb = M33BUSY;
	mtrpara[33].hsen_level = M34HOME;
	mtrpara[33].plmt_level = M34PLMT;
	mtrpara[33].nlmt_level = M34NLMT;
	mtrpara[33].inpos_enb = M34BUSY;
	mtrpara[34].hsen_level = M35HOME;
	mtrpara[34].plmt_level = M35PLMT;
	mtrpara[34].nlmt_level = M35NLMT;
	mtrpara[34].inpos_enb = M35BUSY;
	mtrpara[35].hsen_level = M36HOME;
	mtrpara[35].plmt_level = M36PLMT;
	mtrpara[35].nlmt_level = M36NLMT;
	mtrpara[35].inpos_enb = M36BUSY;

	mtrpara[36].hsen_level = M37HOME;
	mtrpara[36].plmt_level = M37PLMT;
	mtrpara[36].nlmt_level = M37NLMT;
	mtrpara[36].inpos_enb = M37BUSY;
	mtrpara[37].hsen_level = M38HOME;
	mtrpara[37].plmt_level = M38PLMT;
	mtrpara[37].nlmt_level = M38NLMT;
	mtrpara[37].inpos_enb = M38BUSY;
	mtrpara[38].hsen_level = M39HOME;
	mtrpara[38].plmt_level = M39PLMT;
	mtrpara[38].nlmt_level = M39NLMT;
	mtrpara[38].inpos_enb = M39BUSY;
	mtrpara[39].hsen_level = M40HOME;
	mtrpara[39].plmt_level = M40PLMT;
	mtrpara[39].nlmt_level = M40NLMT;
	mtrpara[39].inpos_enb = M40BUSY;
}

void CCUONView::MemoryInitialize()
{

	int  BitTouchAdd;

	for (int i = 0; i < MAX_IOCOUNT_48; i++)	/// input & output Initial
	{
		wInOutput[i] = 0x00000;
	}

	for (int k = 0; k < MAX_TOUCHCOUNT_62; k++) 	  /////// Touch Button Signal Initial
	{
		for (int y = 0; y < MAXBITCOUNT_16; y++)
		{
			BitTouchAdd = (k * MAXBITCOUNT_16) + y;
			m_aBitCIO[BitTouchAdd].szIOName = (k * 100) + 100000 + y;
			m_aBitCIO[BitTouchAdd].m_remember = 0;
			m_aBitCIO[BitTouchAdd].m_active = 0;
			m_aBitCIO[BitTouchAdd].m_buttype = 0;
			m_aOperation[BitTouchAdd].m_nActiv = 0;
			m_aOperation[BitTouchAdd].m_nBackup = 0;
		}
		wTouchInput[k] = 0x0000;
	}



	//==============================================================================
	//=================== Touch bit Gem
	for (int k = 0; k < MAX_GEMCIOCOUNT_10; k++)
	{
		for (int y = 0; y < MAXBITCOUNT_16; y++)
		{
			BitTouchAdd = (k * MAXBITCOUNT_16) + y;
			m_aBitCIOGem[BitTouchAdd].szIOName = (k * 100) + 130000 + y;
			m_aBitCIOGem[BitTouchAdd].m_remember = 0;
			m_aBitCIOGem[BitTouchAdd].m_active = 0;
			m_aBitCIOGem[BitTouchAdd].m_buttype = 0;
			wTouchCIOGem[k] = 0x0000;
		}
	}



	//===========================================
	// inverbit memory Initialize

	for (int i = 0; i < MAX_INVERTCOUNTS_7; i++)
	{
		for (int j = 0; j < MAXBITCOUNT_16; j++)
		{
			InvertButton[(i * 16) + j].bitActive = 0;
			InvertButton[(i * 16) + j].nAddr = ADDR_INVERT_548 + i;
			InvertButton[(i * 16) + j].bitno = j;
		}
	}
	///////////////////////////////////////////////

	//===========================================
	// ComboBox memory Initialize

	for (int i = 0; i < MAX_COMBOCOUNTS_12; i++)
	{
		m_ComOpboTable[i].Combo_Active = 0;
		m_ComOpboTable[i].Combo_nAddr = ADDR_COMBO_588 + i;
	}

	//===========================================
	// Alarm memory Initialize
	int nActiveNo = 0;
	for (int i = 0; i < MAX_ALARMCOUNT_59; i++)
	{
		for (int j = 0; j < MAXBITCOUNT_16; j++)
		{
			nActiveNo = (i * MAXBITCOUNT_16) + j;
			m_aAlarm[nActiveNo].m_nBackup = 0;
			m_aAlarm[nActiveNo].m_nActiv = 0;
		}
	}
	////////////////////////////////////////////
}

BEGIN_EVENTSINK_MAP(CCUONView, CFormView)
	ON_EVENT(CCUONView, IDC_MAIN_EXIT, DISPID_CLICK, CCUONView::ClickMainExit, VTS_NONE)
	ON_EVENT(CCUONView, IDC_BUT_AUTO, DISPID_CLICK, CCUONView::ClickButAuto, VTS_NONE)
	ON_EVENT(CCUONView, IDC_BUT_GEM, DISPID_CLICK, CCUONView::ClickButGem, VTS_NONE)
	ON_EVENT(CCUONView, IDC_BUT_SYSTEM, DISPID_CLICK, CCUONView::ClickButSystem, VTS_NONE)

	ON_EVENT(CCUONView, IDC_BUT_LOG, DISPID_CLICK, CCUONView::ClickButLog, VTS_NONE)
END_EVENTSINK_MAP()



void CCUONView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnMotorDataRead();
	CFormView::OnTimer(nIDEvent);
}

void CCUONView::ClickMainExit()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	DlgBox dlg;

	if(SystemINIFiles.m_strLanguage == "ENGLISH")dlg.m_Msg = "Do You Wnat Exit..?";
	else if(SystemINIFiles.m_strLanguage == "KOREAN")dlg.m_Msg = "프로그램을 종료 하시겠습니까..?";

	dlg.m_bConfirm = 1;
	if (dlg.DoModal() == IDOK)
	{
		AfxGetMainWnd()->PostMessage(WM_QUIT);
	}
}
void CCUONView::OnDialogClear()
{
	m_pDlgMain->ShowWindow(SW_HIDE);
	m_pDlgGem->ShowWindow(SW_HIDE);
	m_pDlgSystemSetting->ShowWindow(SW_HIDE);
	m_pDlgLog->ShowWindow(SW_HIDE);
}



void CCUONView::ClickButAuto()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgMain->ShowWindow(SW_SHOW);
}


void CCUONView::ClickButGem()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgGem->ShowWindow(SW_SHOW);
}


void CCUONView::ClickButSystem()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgSystemSetting->ShowWindow(SW_SHOW);	
	m_pDlgSystemSetting->m_pDlgSystemRcp->OnButtonCheck();
}


void CCUONView::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//OnDialogClear();
	//m_pDlgErrorDisplay->SetErrText(LastErrorNo, LastErrorCode, 0);
	//m_pDlgErrorDisplay->ShowWindow(SW_SHOW);

	//DlgErrorDisplay dlg;
	DlgBoxWarning dlg;
	//DlgLogin dlg;
	//dlg.m_nErrorCode = LastErrorCode;
	//dlg.m_nErrorNo = LastErrorNo;
	//dlg.SetErrText(LastErrorNo, LastErrorCode, 1);
	dlg.DoModal();
}


BOOL CCUONView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CFormView::PreTranslateMessage(pMsg);
}


int CCUONView::GetAlarmFromTable(_tAlarm* pAlarm)
{
	CString	sSQL = "";
	CString	sValue = "";
	int		i, nCount=0;
	CADORecordset rs(theApp.m_pDatabase);
	if (!rs.Open("SELECT * FROM  ALARM_DEFINE ORDER BY alid ASC", CADORecordset::openQuery)) return FALSE;

	for( i = 0, rs.MoveFirst(); !rs.IsEOF(); rs.MoveNext(), i++ )
	{
		rs.GetFieldValue("alid", sValue);
		(pAlarm + i)->m_nId = atoi(sValue);  sValue = "";
		rs.GetFieldValue("alcd", sValue);
		(pAlarm + i)->m_nAlcd = atoi(sValue);  sValue = "";
		rs.GetFieldValue("altx", sValue);
		strcpy( (pAlarm + i)->m_szText, sValue ); sValue = "";
		rs.GetFieldValue("enabled", sValue );
		(pAlarm + i)->m_nEnabled = atoi(sValue);  sValue = "";
		rs.GetFieldValue("caution", sValue);
		strcpy( (pAlarm + i)->m_szCauText, sValue ); sValue = "";
		rs.GetFieldValue("action", sValue);
		strcpy( (pAlarm + i)->m_szActText, sValue ); sValue = "";

		nCount++;
	}
	return TRUE;
}

int CCUONView::GetOperatorFromTable(_tOperation* pOperation)
{
	CString	sSQL = "";
	CString	sValue = "";
	int		i, nCount=0;
	//	Open database.
	CADORecordset rs(theApp.m_pDatabase);
	if (!rs.Open("SELECT * FROM TOUCH_DEFINE ", CADORecordset::openQuery)) return FALSE;

	for( i = 0, rs.MoveFirst(); !rs.IsEOF(); rs.MoveNext(), i++ )
	{
		rs.GetFieldValue("OPCODE", sValue);
		(pOperation + i)->m_nId = atoi(sValue);  //sValue = "";
		rs.GetFieldValue("OPTEXT", sValue);
		strcpy( (pOperation + i)->m_szText, sValue ); sValue = "";

		nCount++;
	}
	return TRUE;
}


void CCUONView::OperatorList()
{
	//
	CString	sSQL = "";
	CString	sValue = "";
	int		i, nCount = 0;
	//	Open database.
	CADORecordset rs(theApp.m_pDatabase);
	if (!rs.Open("SELECT * FROM USERID ", CADORecordset::openQuery)) return ;

	for (i = 0, rs.MoveFirst(); !rs.IsEOF(); rs.MoveNext(), i++)
	{
		rs.GetFieldValue("USER_ID", sValue);
		m_UserTable.UserID[nCount] = sValue;
		rs.GetFieldValue("USER_LEVEL", sValue);
		m_UserTable.UserLevel[nCount] = sValue;
		rs.GetFieldValue("USER_PASS", sValue);
		m_UserTable.UserPass[nCount] = sValue;
		nCount++;
	}
	m_UserTable.UserCnt = nCount;
	//
}



void CCUONView::ClickButLog()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnDialogClear();
	m_pDlgLog->ShowWindow(SW_SHOW);
}
