// DlgGem.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "framework.h"
#include "CUON.h"
#include "DlgGem.h"
#include "afxdialogex.h"
#include "DlgGemParameter.h"
#define MAX 256 // 버퍼크기 지정

// DlgGem 대화 상자입니다.

IMPLEMENT_DYNAMIC(DlgGem, CDialogEx)

DlgGem::DlgGem(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgGem::IDD, pParent)
{
	m_nControlState=0;
	m_nPrevControlState = 0;
	m_nDefaultControlState = 0;
	m_nProcessMode_Control = 0;
	m_nProcessMode_Base = 0;
	m_nPrevProcessMode_Control = 0;
	m_nPrevProcessMode_Base = 0;
	m_nProcessState = 0;
	m_nPrevProcessState = 0;
	m_nRunModeState = 0;
	m_nPrevRunModeState = 0;
	m_nOperationMode = 0;
	m_nPrevOperationMode = 0;
	m_nOperatonMode = 0;
	m_nPrevOperatonMode = 0;
	
	short nCntSVID = 0;
	short nCntCEID = 0;
	int nSVIDSlot[400] = { 0 };
	int nSVIDPort[400] = { 0 };
	int nCEID[400] = { 0 };
	int eMemoryBufPoint[100][16] = { 0 };
	int nSVID[400] = { 0 };
}

DlgGem::~DlgGem()
{
}

void DlgGem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EZGEMCTRL, m_gem);
	DDX_Control(pDX, IDC_LIST1, m_listLog);
}


BEGIN_MESSAGE_MAP(DlgGem, CDialogEx)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &DlgGem::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &DlgGem::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_LOCAL, &DlgGem::OnBnClickedButtonLocal)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE, &DlgGem::OnBnClickedButtonRemote)
	ON_BN_CLICKED(IDC_BUTTON_OFFLINE, &DlgGem::OnBnClickedButtonOffline)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETER, &DlgGem::OnBnClickedButtonParameter)
	
	ON_BN_CLICKED(IDOK, &DlgGem::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgGem::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgGem 메시지 처리기입니다.


void DlgGem::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CheckGemEmemory();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL DlgGem::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(SILVER);
	nCntCEID = 0;
	nCntSVID = 0;
	SetTimer(0, 100, NULL);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgGem::PreTranslateMessage(MSG* pMsg)
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


void DlgGem::GemStart()
{
	theApp.ReadConfigFile();

	ReadDataBaseCEID();
	ReadDataBaseSVID();
	InitGem();

	if (m_gem.Start() == 0 /*&& m_nDefaultCommState == 1 */)
	{

		m_gem.EnableCommunication();

		if (m_GemLogConfig.m_nDefaultControlState == CONTROL_OFFLINE)	m_gem.GoOffline();
		else if (m_GemLogConfig.m_nDefaultControlState == CONTROL_ONLINE_LOCAL) m_gem.GoOnlineLocal();
		else if (m_GemLogConfig.m_nDefaultControlState == CONTROL_ONLINE_REMOTE) m_gem.GoOnlineRemote();
		else
		{
			AddLog("CAN NOT SELECT ONLINE");
		}

		GetDlgItem(IDC_BUTTON_LOCAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_REMOTE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OFFLINE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);



		//	m_gem.GoOnlineRemote();

		AddLog("GEM PROCESS STARTED");
	}

	//================================================
	//	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}
void DlgGem::InitGem()
{
	CString strPath;
	strPath = "..\\..\\..\\LOG\\GEMLOG";

	ShowConfig();

	AddSVID();
	AddCEID();
	/*	AddALID();
		AddECID();

		m_strModelName = "CUTEA-120";
		m_strSoftRev = "20180302";

		m_gem.SetModelName(m_strModelName);
		m_gem.SetSoftwareRev(m_strSoftRev);*/


		//== TIME FORMAT YYYYMMDD HHMMSS : 14
		//== TIME FORMAT YYYYMMDD HHMMSSCC : 16
	m_gem.SetTimeFormat(14);

	m_gem.SetPassiveMode(TRUE);
	m_gem.SetHostMode(FALSE);



	_mkdir(strPath);
	m_gem.SetLogFile(strPath + "\\GEM.LOG", TRUE);
	m_gem.SetLogRetention(m_GemLogConfig.m_nLogRetention);	// 로그 보유기간 30일
	m_gem.SetFormatFile("FORMAT.SML");			//FORMAT 화일 설정
	m_gem.SetFormatCheck(TRUE);					//FORMAT CHECK 유/무 설정

	m_gem.SetEstablishCommRetryTimer(5);		//일반 일일때 값 2



	//=============================================================
	m_gem.SetPort(m_GemLogConfig.m_nPort);
	m_gem.SetDeviceID(m_GemLogConfig.m_nDeviceID);
	m_gem.SetT3(m_GemLogConfig.m_nT3);
	m_gem.SetT5(m_GemLogConfig.m_nT5);
	m_gem.SetT6(m_GemLogConfig.m_nT6);
	m_gem.SetT7(m_GemLogConfig.m_nT7);
	m_gem.SetT8(m_GemLogConfig.m_nT8);

	m_gem.SetRetry(m_GemLogConfig.m_nRetry);
	m_gem.SetLinkTestInterval(m_GemLogConfig.m_nLinkInterval);

	m_gem.SetHostMode(FALSE);
	m_gem.SetPassiveMode(TRUE);
	//==============================================================




	/////////////////////////////////////////////////////////////////////////
	//		각종 ID의 Format 설정
	//		54 = U4, 52 = U2, 51 = U1
	m_gem.SetFormatCodeALID(54);
	m_gem.SetFormatCodeCEID(54);
	m_gem.SetFormatCodeDATAID(54);
	m_gem.SetFormatCodeECID(54);
	m_gem.SetFormatCodeRPTID(54);
	m_gem.SetFormatCodeSVID(54);
	m_gem.SetFormatCodeTRACEID(54);

	//== Recipe List Requst 

	m_gem.DisableAutoReply(7, 1);
	m_gem.DisableAutoReply(7, 3);
	m_gem.DisableAutoReply(7, 5);

	m_gem.DisableAutoReply(1, 1);//DECA NOT USED

	m_gem.DisableAutoReply(7, 17);
	m_gem.DisableAutoReply(7, 19);
	m_gem.DisableAutoReply(7, 20);
	m_gem.DisableAutoReply(7, 23);
	m_gem.DisableAutoReply(7, 25);
	m_gem.DisableAutoReply(3, 17);
	m_gem.DisableAutoReply(10, 1);



	/////////////////////////////////////////////////////////////////////////
	// S2F41 OnRemoteCommand - Can recevied into Function RCMD

/*	m_gem.AddRemoteCommand(	RCMD_START		);
	m_gem.AddRemoteCommand(	RCMD_STOP 		);
	m_gem.AddRemoteCommand(	RCMD_LOGIN		);
	m_gem.AddRemoteCommand(	RCMD_LOOUT		);

	m_gem.AddRemoteCommand(	RCMD_LOAD_CARRIER			    		);
	m_gem.AddRemoteCommand(	RCMD_UNLOAD_CARRIER						);
	m_gem.AddRemoteCommand(	RCMD_REJECT_CARRIER			    		);
	m_gem.AddRemoteCommand(	RCMD_PROCESS_CARRIER					);

	m_gem.AddRemoteCommand(	RCMD_START_WAFER					);
	m_gem.AddRemoteCommand(	RCMD_ABORT_WAFER					);
	m_gem.AddRemoteCommand(	RCMD_CHANGE_MODE					);

	m_gem.AddRemoteCommand(	RCMD_LOAD_WAFER_RECIPE      		);//RCMD_LOAD_CARRIER_RECIPE
	m_gem.AddRemoteCommand(	RCMD_SET_WAFER_APC_PARAMETERS 		);


	//	m_gem.AddRemoteCommand(	RCMD_ABORT_CARRIER						);


	m_gem.AddRemoteCommand(	RCMD_START_INPUT						);
	m_gem.AddRemoteCommand(	RCMD_STOP_INPUT                 		);
	m_gem.AddRemoteCommand(	RCMD_STOP_INPUT_AFTER_N_WAFERS          );
	m_gem.AddRemoteCommand(	RCMD_STOP_OUTPUT                		);
	m_gem.AddRemoteCommand(	RCMD_STOP_OUTPUT_AFTER_N_WAFERS 		);
	m_gem.AddRemoteCommand(	RCMD_START_OUTPUT						);
	m_gem.AddRemoteCommand(	RCMD_SPLIT		);


	m_gem.AddRemoteCommand(	RCMD_START_TRANSFER				);
	m_gem.AddRemoteCommand(	RCMD_SELECT_IN_WAFERS			);
	m_gem.AddRemoteCommand(	RCMD_SELECT_IN_SLOT		        );
	m_gem.AddRemoteCommand(	RCMD_SELECT_IN_AUTO				);
	m_gem.AddRemoteCommand(	RCMD_SELECT_OUT_SLOT			);
	m_gem.AddRemoteCommand(	RCMD_SELECT_OUT_AUTO			);*/

	//	m_gem.SetCurrentStatusValue( SVID_TAPE_BAC , m_strTapeTag );
	//	m_gem.SetCurrentStatusValue( SVID_TAPE_CHANGED_TIME , m_strTapeTime );
	//	SetDlgItemText( IDC_EDIT_LAMI_TAPE_TAG , m_strTapeTag );

//	SetProcessState( PROCESS_STATE_NON_SCHEDULED_TIME );

}

long DlgGem::GetAsciiItem(long lMsgId, CString* strBuff)
{
	char buff[0xFFFF];
	memset(buff, '\0', 0xFFFF);

	BSTR bstrBuff;
	long nSize = m_gem.GetAsciiItem(lMsgId, &bstrBuff);
	WideCharToMultiByte(CP_ACP, 0, bstrBuff, nSize, buff, nSize, NULL, NULL);
	CString strTemp = (CString)buff;
	strTemp.TrimRight();
	*strBuff = strTemp;
	SysFreeString(bstrBuff);

	return nSize;
}


void DlgGem::AddLog(CString strLog)
{
	//===================================================
	m_listLog.AddString(strLog);
	int nCnt = 0;

	nCnt = m_listLog.GetCount();

	while (nCnt > MAX_LOG_COUNT)
	{
		m_listLog.DeleteString(0);
		nCnt = m_listLog.GetCount();
	}
	m_listLog.SetCurSel(nCnt - 1);

}
void DlgGem::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GemStart();
	m_gem.EnableCommunication();
}

void DlgGem::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

//	SetDlgItemText(IDC_STATIC_CONNECT, (LPCTSTR)"DISCONNECT");
//	SetDlgItemText(IDC_STATIC_CONTROL, (LPCTSTR)"OFFLINE");

	Main.m_nControlMode = CONTROL_OFFLINE;
	Main.m_nControlConnect = CONTROL_DISCONNECTED;

	m_GemReportTable.m_bStarted = FALSE;
	m_gem.Stop();
	GemParameterSave();
}
void DlgGem::OnBnClickedButtonLocal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_gem.GoOnlineLocal();
}


void DlgGem::OnBnClickedButtonRemote()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_gem.GoOnlineRemote();
}


void DlgGem::OnBnClickedButtonOffline()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTip;
	CString strControl = "";
	CString strPrevControl = "";
	if (E90310_LOTSTART) { AfxMessageBox("Already Working can't Control ", MB_OK | MB_ICONWARNING);	return; }

	if (m_nControlState != CONTROL_OFFLINE)
	{
		m_nPrevControlState = m_nControlState;
		strPrevControl.Format("%d", m_nPrevControlState);
		//m_gem.SetCurrentStatusValue(SVID_PreviousControlState, strPrevControl);
		m_gem.SetCurrentStatusValue(SVID_PREVIOUS_CONTROL_STATE, strPrevControl);
		//=================================================
	}

	UINT nPrevState = m_nControlState;
	m_nControlState = CONTROL_OFFLINE;
	strControl.Format("%d", m_nControlState);

	m_gem.SetCurrentStatusValue(SVID_CONTROL_STATE, strControl);
	m_gem.SetCurrentStatusValue(SVID_CURRENT_CONTROL_STATE, strControl);
	if (nPrevState != CONTROL_OFFLINE)	// 기존상태와 같으면 보고하지 않는다.
	{
		SendEventReport(CEID_CONTROL_STATE_CHANGED);
		//	SendEvent(CEID_CONTROL_STATE_CHANGED);

	}

	m_gem.GoOffline();

	Main.m_nControlMode = CONTROL_OFFLINE;
	m_GemReportTable.m_bStarted = FALSE;

	GetDlgItem(IDC_BUTTON_OFFLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REMOTE)->EnableWindow(TRUE);

	//SetDlgItemText(IDC_STATIC_CONTROL, (LPCTSTR)"OFFLINE");
}

void DlgGem::AddCEID()
{
	for (int i = 0; i < nCntCEID; i++) {
		m_gem.AddCEID(nCEID[i], strCEIDMsg[i], "");
	}
}
void DlgGem::AddSVID()
{
	for (int i = 0; i < nCntSVID; i++) {
		m_gem.AddSVID(nSVID[i], strSVIDMsg[i], strSVIDType[i], "");
	}
}
void DlgGem::UpdateSVID(int nSvid)
{
	short nCnt = 0;
	CString m_strMeterial = "", m_strID = "", m_strSlotNo = "", m_strPortNo = "", strTemp = "";
	int m_nSlot = 0, m_nPort = 0, m_SlotNo = 0, m_PortNo = 0;


	for (int i = 0; i < nCntSVID; i++) {
		if (nSvid == nSVID[i]) {
			nCnt = i;
			m_strMeterial = strSVIDMeterial[nCnt];
			m_strID = strSVIDId[nCnt];
			m_nSlot = nSVIDSlot[nCnt];
			m_nPort = nSVIDPort[nCnt];
		}
	}

	if (m_strID == "WAFER_ID") {
		m_SlotNo = (int)wEmemoryGEMRead[m_nSlot];
		m_PortNo = (int)wEmemoryGEMRead[m_nPort];
		m_strSlotNo.Format("WAFER%d", m_SlotNo);
		m_strPortNo.Format("PORT%d", m_PortNo);
		strTemp = ReadWaferIDListFile(m_strPortNo, m_strSlotNo);
		m_gem.SetCurrentStatusValue(nSvid, strTemp);
	}

	else if (m_strID == "CARRIER_ID") {
		m_SlotNo = (int)wEmemoryGEMRead[m_nSlot];
		m_PortNo = (int)wEmemoryGEMRead[m_nPort];
		m_strSlotNo.Format("CARRIER%d", m_SlotNo);
		m_strPortNo.Format("PORT%d", m_PortNo);
		strTemp = ReadWaferIDListFile(m_strPortNo, m_strSlotNo);
		m_gem.SetCurrentStatusValue(nSvid, strTemp);
	}

	else if (m_strID == "FOUP_ID") {
		m_strSlotNo = "ID";
		m_strPortNo.Format("PORT%d", m_nPort);
		strTemp = ReadWaferIDListFile(m_strPortNo, m_strSlotNo);
		m_gem.SetCurrentStatusValue(nSvid, strTemp);
	}

	else if (m_strID == "SLOT_NO") {
		m_SlotNo = (int)wEmemoryGEMRead[m_nSlot];
		m_PortNo = (int)wEmemoryGEMRead[m_nPort];
		m_strSlotNo.Format("%d", m_SlotNo);
		strTemp = m_strSlotNo;
		m_gem.SetCurrentStatusValue(nSvid, strTemp);
	}

	else if (m_strID == "PORT_NO") {
		m_strPortNo.Format("%d", m_nPort);
		strTemp = m_strPortNo;
		m_gem.SetCurrentStatusValue(nSvid, strTemp);
	}
}

void DlgGem::CheckGemEmemory()
{
	int CEID = 0;
	for (int i = 0; i < 49; i++)
	{
		for (int j = 0; j < 16; j++) {
			if (PollingBit(wEmemoryGEMRead[i], j) != 0 && !m_GemEvent[i].b_Bit[j] && eMemoryBufPoint[i][j]) {
				m_GemEvent[i].b_Bit[j] = TRUE;
				CEID = eMemoryBufPoint[i][j];
				if (CEID > 0)SendEventReport(CEID);
			}
			else if (!PollingBit(wEmemoryGEMRead[i], j))m_GemEvent[i].b_Bit[j] = FALSE;
		}
	}

}
void DlgGem::ReadDataBaseCEID()
{
	int strBuf = 0, strBit = 0, nCount = 0;
	CString strMsg = "", strQuery = "";

	strQuery = "SELECT * FROM GEM_CEID";
	CADORecordset rs(theApp.m_pDatabase);
	rs.Open(strQuery, CADORecordset::openQuery);
	while (!rs.IsEOF())
	{
		rs.GetFieldValue("CEID", nCount);
		rs.GetFieldValue("BUF", strBuf);
		rs.GetFieldValue("POINT", strBit);
		rs.GetFieldValue("MSG", strMsg);
		strCEIDMsg[nCntCEID] = strMsg;
		nCEID[nCntCEID] = nCount;
		eMemoryBufPoint[strBuf][strBit] = nCount;
		nCntCEID++;
		rs.MoveNext();
	}
}
void DlgGem::ReadDataBaseSVID()
{
	int strBuf = 0, strBit = 0;
	CString strMsg = "";
	CString strQuery = "";

	strQuery = "SELECT * FROM GEM_SVID";
	CADORecordset rs(theApp.m_pDatabase);
	rs.Open(strQuery, CADORecordset::openQuery);
	while (!rs.IsEOF())
	{
		rs.GetFieldValue("SVID", nSVID[nCntSVID]);
		rs.GetFieldValue("METERIAL", strSVIDMeterial[nCntSVID]);
		rs.GetFieldValue("ID", strSVIDId[nCntSVID]);
		rs.GetFieldValue("SLOT", nSVIDSlot[nCntSVID]);
		rs.GetFieldValue("PORT", nSVIDPort[nCntSVID]);
		rs.GetFieldValue("MSG", strSVIDMsg[nCntSVID]);
		rs.GetFieldValue("TYPE", strSVIDType[nCntSVID]);
		nCntSVID++;
		rs.MoveNext();
	}
}

void DlgGem::SendEventReport(long lCEID)
{

	CString strSVIDValueList = _T("");
	long nCnt = 0;
	long ArrayReport[0xFF];
	memset(ArrayReport, '\0', 0xFF);
	CString strLog, strTime,strRptID = _T(""), strCeid = _T("");
	CTime time = CTime::GetCurrentTime();

	char szLog[0xFF];
	//sprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d ", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	sprintf(szLog, "%02d:%02d:%02d ", time.GetHour(), time.GetMinute(), time.GetSecond());

	strCeid.Format("[CEID]_%ld", lCEID);
	AddLog(szLog + strCeid);

	nCnt = m_gem.GetEventReport(lCEID, ArrayReport);
	for (int i = 0; i < nCnt; i++)
	{
		
		long lRptID = 0;
		lRptID = ArrayReport[i];

		strRptID.Format("[EVENT]_%ld", lRptID);
		AddLog(szLog + strRptID);
		if (lRptID != 0)
		{
			long nCntSVID = 0;
			long ArraySVID[0xFF];
			memset(ArraySVID, '\0', 0xFF);
			nCntSVID = m_gem.GetReport(lRptID, ArraySVID);
			for (int j = 0; j < nCntSVID; j++)
			{
				//UpdateSVID(short nCnt , CString strSvid);
				CString strTempList = _T("");
				//=======================================
				long nSVID = 0;
				nSVID = ArraySVID[j];
				UpdateSVID(nSVID);
				CString strSVIDNumber = _T("");
				CString strSVIDValue = _T("");
				CString strSVIDName = _T("");
				strSVIDNumber.Format("%ld", nSVID);
				strSVIDValue = m_gem.GetCurrentStatusValue(nSVID);
				strSVIDName = m_gem.GetSVName(nSVID);
				strTempList.Format("[SVID]_%s_%s_(%s)", strSVIDNumber, strSVIDName, strSVIDValue);
				AddLog(szLog + strTempList);
				strSVIDValueList += strTempList;
			}
		}
	}
	//AddLog( szLog+strSVIDValueList );
	m_gem.SendEventReport(lCEID);
}


BEGIN_EVENTSINK_MAP(DlgGem, CDialogEx)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 1, DlgGem::OnConnectedEzgemctrl, VTS_NONE)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 2, DlgGem::OnDisconnectedEzgemctrl, VTS_NONE)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 3, DlgGem::OnDateTimeSetRequestEzgemctrl, VTS_I4 VTS_BSTR)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 4, DlgGem::OnEstablishCommRequestEzgemctrl, VTS_I4)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 5, DlgGem::OnOnlineRequestEzgemctrl, VTS_I4)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 6, DlgGem::OnOfflineRequestEzgemctrl, VTS_I4)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 7, DlgGem::OnRemoteCommandEzgemctrl, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 8, DlgGem::OnNewEquipConstEzgemctrl, VTS_I4 VTS_I2)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 13, DlgGem::OnTerminalMessageSingleEzgemctrl, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 14, DlgGem::OnTerminalMessageMultiEzgemctrl, VTS_I4 VTS_I2 VTS_I2)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 15, DlgGem::OnMsgRequestedEzgemctrl, VTS_I4)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 16, DlgGem::OnOnlineLocalEzgemctrl, VTS_NONE)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 17, DlgGem::OnOnlineRemoteEzgemctrl, VTS_NONE)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 24, DlgGem::OnSecsMsgInEzgemctrl, VTS_I2 VTS_I2 VTS_I2 VTS_I4)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 25, DlgGem::OnSecsMsgOutEzgemctrl, VTS_I2 VTS_I2 VTS_I2 VTS_I4)
	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 22, DlgGem::OnVariableInDeadBandEzgemctrl, VTS_I4 VTS_I2)
	//	ON_EVENT(DlgGem, IDC_EZGEMCTRL, 9, DlgGem::OnCommEstablishedEzgemctrl, VTS_NONE)
END_EVENTSINK_MAP()


void DlgGem::OnConnectedEzgemctrl()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	SetDlgItemText(IDC_STATIC_CONNECT, "CONNECTED");
//	SetDlgItemText(IDC_STATIC_CONTROL, "OFFLINE");

	Main.m_nControlConnect = CONTROL_CONNECTED;
}


void DlgGem::OnDisconnectedEzgemctrl()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	SetDlgItemText(IDC_STATIC_CONNECT, "DISCONNECTED");
//	SetDlgItemText(IDC_STATIC_CONTROL, "OFFLINE");
	m_GemReportTable.m_bStarted = FALSE;

	Main.m_nControlConnect = CONTROL_DISCONNECTED;
}


void DlgGem::OnDateTimeSetRequestEzgemctrl(long lMsgId, LPCTSTR strNewDateTime)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//	m_gem.AcceptAndSetNewDateTime(lMsgId, strNewDateTime);		// 실제로 SYSTEM시간이 바뀜.
	//==== 2014 06 12
	// 년 1970 이하
	// 월 12 이상
	// 일 31 이상
	// 시 24 이상
	// 분 60 이상
	// 초 60 이상
	// 일 경우 nAck 

	CString strTime = _T("");
	BOOL	bAck = TRUE;
	strTime = strNewDateTime;
	INT nCnt = strTime.GetLength();

	char pnWbuf[0xFF];
	memset(pnWbuf, 0x00, 0xFF);
	memcpy(pnWbuf, strNewDateTime, nCnt);

	for (int i = 0; i < nCnt; i++)
	{
		INT nNumber = 0;
		if (pnWbuf[i] < ASCII_CODE_0 || pnWbuf[i] > ASCII_CODE_9) bAck = FALSE;
	}

	if (!bAck)
	{
		//==== 0 -9 이외의 값이 온 경우...
		m_gem.DenyNewDateTimeSet(lMsgId);
		return;

	}


	//  CString strTime = _T("");
	//  BOOL  bAck = TRUE;

	//  strTime = strNewDateTime;
	CString strYear = _T(""), strMonth = _T(""), strDay = _T(""), strHour = _T(""), strMinute = _T(""), strSecond = _T("");

	strYear = strTime.Left(4);
	strMonth = strTime.Mid(4, 2);
	strDay = strTime.Mid(6, 2);

	strHour = strTime.Mid(8, 2);
	strMinute = strTime.Mid(10, 2);
	strSecond = strTime.Mid(12, 2);

	AddLog(strYear + strMonth + strDay + strHour + strMinute + strSecond);

	if (strYear < "1970")
	{
		bAck = FALSE;
		AddLog(strYear);
	}

	if (strMonth > "12")
	{
		bAck = FALSE;
		AddLog(strMonth);
	}

	if (strDay > "31")
	{
		bAck = FALSE;
		AddLog(strDay);
	}

	if (strHour > "23")
	{
		bAck = FALSE;
		AddLog(strHour);
	}

	if (strMinute > "59")
	{
		bAck = FALSE;
		AddLog(strMinute);
	}

	if (strSecond > "59")
	{
		bAck = FALSE;
		AddLog(strSecond);
	}
	//========================================================

	// 아래에서 타임을 세팅하고 응답 메세지 (S2F32)를 HOST로 전송

	if (bAck)           m_gem.AcceptAndSetNewDateTime(lMsgId, strNewDateTime);              // 실제로 SYSTEM시간이 바뀜.

	else m_gem.DenyNewDateTimeSet(lMsgId);
}


void DlgGem::OnEstablishCommRequestEzgemctrl(long lMsgId)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DlgGem::OnOnlineRequestEzgemctrl(long lMsgId)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_gem.AcceptOnlineRequest(lMsgId);

	CString strPrevState, strState;


	if (m_nPrevControlState == CONTROL_ONLINE_LOCAL)
	{
		m_nControlState = CONTROL_ONLINE_LOCAL;
	}
	else if (m_nPrevControlState == CONTROL_ONLINE_REMOTE)
	{
		m_nControlState = CONTROL_ONLINE_REMOTE;
	}


	m_nPrevControlState = CONTROL_OFFLINE;

	strState.Format("%d", m_nControlState);
	strPrevState.Format("%d", m_nPrevControlState);

	m_gem.SetCurrentStatusValue(SVID_CONTROL_STATE, strState);
	m_gem.SetCurrentStatusValue(SVID_CURRENT_CONTROL_STATE, strState);
	m_gem.SetCurrentStatusValue(SVID_PREVIOUS_CONTROL_STATE, strPrevState);

	m_gem.SetEquipConstValue(1, strState);



	if (m_nControlState == CONTROL_OFFLINE)
	{

		m_gem.AcceptOnlineRequest(lMsgId);

		if (m_nPrevControlState == CONTROL_ONLINE_REMOTE) OnBnClickedButtonRemote();
		else if (m_nPrevControlState == CONTROL_ONLINE_LOCAL) OnBnClickedButtonLocal();
	}
	else
	{
		m_gem.DenyOnlineRequest(lMsgId);
	}
}


void DlgGem::OnOfflineRequestEzgemctrl(long lMsgId)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strTip;
	CString strControl = "";
	CString strPrevControl = "";

	m_nPrevControlState = m_nControlState;
	m_nControlState = CONTROL_OFFLINE;

	strControl.Format("%d", m_nControlState);
	strPrevControl.Format("%d", m_nPrevControlState);

	m_gem.SetCurrentStatusValue(SVID_CONTROL_STATE, strControl);
	m_gem.SetCurrentStatusValue(SVID_CURRENT_CONTROL_STATE, strControl);
	SendEventReport(CEID_CONTROL_STATE_CHANGED);

	m_gem.GoOffline();

	GetDlgItem(IDC_BUTTON_OFFLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REMOTE)->EnableWindow(TRUE);

//	SetDlgItemText(IDC_STATIC_CONTROL, (LPCTSTR)"OFFLINE");
}


void DlgGem::OnRemoteCommandEzgemctrl(long lMsgId, LPCTSTR strCommand, short nParamCount)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}


void DlgGem::OnNewEquipConstEzgemctrl(long lMsgId, short nCount)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strMessage = _T("");
	CString strValue = _T("");

	BOOL	bGemInit = FALSE;

	long ECID = 0;
	for (int i = 0; i < nCount; i++)
	{
		ECID = m_gem.GetNewEquipConst(lMsgId, i);
		CString strValue = m_gem.GetNewEquipConstValue(lMsgId, i);

		switch (ECID)
		{


		case ECID_DEFAULT_CONTROL_STATE:
			m_GemLogConfig.m_nDefaultControlState = atoi(strValue);
			break;

		case ECID_T3:
			m_GemLogConfig.m_nT3 = atoi(strValue);
			break;

		case ECID_T5:
			m_GemLogConfig.m_nT5 = atoi(strValue);
			break;

		case ECID_T6:
			m_GemLogConfig.m_nT6 = atoi(strValue);
			break;

		case ECID_T7:
			m_GemLogConfig.m_nT7 = atoi(strValue);
			break;

		case ECID_T8:
			m_GemLogConfig.m_nT8 = atoi(strValue);
			break;

		case ECID_LINKTEST:
			m_GemLogConfig.m_nLinkInterval = atoi(strValue);
			break;

		case ECID_RETRY:
			m_GemLogConfig.m_nRetry = atoi(strValue);
			break;

			//	case ECID_COMMUNICATION_REQUEST :
			//		m_GemLogConfig.m_nCommReqeustTimeout = atoi( strValue );
			//		break;


		}
	}
	GemParameterSave();
	m_gem.AcceptNewEquipConst(lMsgId);
	AddLog("ECID :" + strMessage);
}


void DlgGem::OnTerminalMessageSingleEzgemctrl(long lMsgId, LPCTSTR strMsg, short nCode)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DlgGem::OnTerminalMessageMultiEzgemctrl(long lMsgId, short nCode, short nCount)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DlgGem::OnMsgRequestedEzgemctrl(long lMsgId)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SHORT nStream = 0, nFunction = 0, nWbit = 0;
	long lLength = 0;

	m_gem.GetMsgInfo(lMsgId, &nStream, &nFunction, &nWbit, &lLength);


	//== Recipe List Request's Reply =====
	//	if( nStream == 7 && nFunction == 19 )OnMsgRequestRecipeList( lMsgId );

	//== Recipe List Request's Reply =====
	if (nStream == 1 && nFunction == 1)
	{
		//	OnS1F1( lMsgId );
	}
	if (nStream == 7 && nFunction == 1)
	{
		//	OnS7F1( lMsgId );
	}
	else if (nStream == 7 && nFunction == 2)
	{
		//	OnS7F2( lMsgId );
	}
	else if (nStream == 7 && nFunction == 3)
	{
		//	OnS7F3( lMsgId );
	}
	else if (nStream == 7 && nFunction == 5)
	{
		//		OnS7F5( lMsgId );
	}
	//== 20151001
	else if (nStream == 7 && nFunction == 4)
	{
		//	OnS7F4( lMsgId );
	}
	//== 20151001
	else if (nStream == 7 && nFunction == 6)
	{
		//	OnS7F6( lMsgId );
	}
	else if (nStream == 7 && nFunction == 17)
	{
		//	OnS7F17( lMsgId );
	}
	else if (nStream == 7 && nFunction == 19)
	{
		//	OnS7F19( lMsgId );
	}
	else if (nStream == 7 && nFunction == 23)
	{
		//	OnS7F23( lMsgId );
	}
	else if (nStream == 7 && nFunction == 24)
	{
		m_gem.CloseMsg(lMsgId);
	}
	else if (nStream == 7 && nFunction == 25)
	{
		//	OnS7F25( lMsgId );
	}
	else if (nStream == 3 && nFunction == 17)
	{
		OnS3F17(lMsgId);
	}
	else if (nStream == 14 && nFunction == 3)
	{
		//	OnS14F3( lMsgId );
	}
	else
	{
		//	m_gem.AbortMsg( lMsgId );
	}
}


void DlgGem::OnOnlineLocalEzgemctrl()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strTip;
	CString strControl = "";
	CString strPrevControl = "";

	if (m_nControlState != CONTROL_ONLINE_LOCAL)
	{
		m_nPrevControlState = m_nControlState;
		strPrevControl.Format("%d", m_nPrevControlState);
		//m_gem.SetCurrentStatusValue(SVID_PREV_CONTROLSTATE, strPrevControl);
	}
	m_nPrevControlState = m_nControlState;
	UINT nPrevState = m_nControlState;
	m_nControlState = CONTROL_ONLINE_LOCAL;
	strControl.Format("%d", m_nControlState);

	m_gem.SetCurrentStatusValue(SVID_CONTROL_STATE, strControl);
	m_gem.SetCurrentStatusValue(SVID_CURRENT_CONTROL_STATE, strControl);
	//=============================================================
	CString strPrevState = _T("");

	strPrevState.Format("%d", m_nPrevControlState);
	m_gem.SetCurrentStatusValue(SVID_PREVIOUS_CONTROL_STATE, strPrevState);
	//==============================================================
	if (nPrevState != CONTROL_ONLINE_LOCAL)	// 기존상태와 같으면 보고하지 않는다.
	{
		SendEventReport(CEID_CONTROL_STATE_CHANGED);
	}
	m_GemReportTable.m_bStarted = TRUE;//20151214  FALSE -> TRUE
//	::SetDlgItemText(this->m_hWnd, IDC_STATIC_CONTROL, "ONLINE/LOCAL");

	strTip.Format("CONNECTED\nONLINE/LOCAL\n%s\n%d", m_gem.GetIP(), m_gem.GetPort());

	//SetTooltipText(strTip);

	GetDlgItem(IDC_BUTTON_OFFLINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOCAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REMOTE)->EnableWindow(TRUE);

	Main.m_nControlMode = CONTROL_ONLINE_LOCAL;
	//m_nDefaultControlState = CONTROL_ONLINE_LOCAL;
//	GemParameterSave();
}


void DlgGem::OnOnlineRemoteEzgemctrl()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strTip;
	CString strControl = "";
	CString strPrevControl = "";

	if (m_nControlState != CONTROL_ONLINE_REMOTE)
	{
		m_nPrevControlState = m_nControlState;
		strPrevControl.Format("%d", m_nPrevControlState);
		//m_gem.SetCurrentStatusValue(SVID_PREV_CONTROLSTATE, strPrevControl);
	}
	m_nPrevControlState = m_nControlState;

	UINT nPrevState = m_nControlState;
	m_nControlState = CONTROL_ONLINE_REMOTE;
	strControl.Format("%d", m_nControlState);

	m_gem.SetCurrentStatusValue(SVID_CONTROL_STATE, strControl);
	m_gem.SetCurrentStatusValue(SVID_CURRENT_CONTROL_STATE, strControl);

	//=============================================================
	CString strPrevState = _T("");

	strPrevState.Format("%d", m_nPrevControlState);
	m_gem.SetCurrentStatusValue(SVID_PREVIOUS_CONTROL_STATE, strPrevState);

	if (nPrevState != CONTROL_ONLINE_REMOTE)	// 기존상태와 같으면 보고하지 않는다.
	{
		SendEventReport(CEID_CONTROL_STATE_CHANGED);
	}

	m_GemReportTable.m_bStarted = TRUE;
//	::SetDlgItemText(this->m_hWnd, IDC_STATIC_CONTROL, "ONLINE/REMOTE");

	//strTip.Format("CONNECTED\nONLINE/REMOTE\n%s\n%d", m_gem.GetIp(), m_gem.GetPort());

	//SetTooltipText(strTip);

	GetDlgItem(IDC_BUTTON_OFFLINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REMOTE)->EnableWindow(FALSE);

	//m_nDefaultControlState = CONTROL_ONLINE_REMOTE;
	Main.m_nControlMode = CONTROL_ONLINE_REMOTE;
	//	GemParameterSave();	
}


void DlgGem::OnSecsMsgInEzgemctrl(short nStream, short nFunction, short nWbit, long lSysByte)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strLog, strTime;
	CTime time = CTime::GetCurrentTime();

	char szLog[0xFF];
	sprintf(szLog, "%02d:%02d:%02d (HOST->EQ) S%dF%d", time.GetHour(), time.GetMinute(), time.GetSecond(), nStream, nFunction);

	AddLog(szLog);
}


void DlgGem::OnSecsMsgOutEzgemctrl(short nStream, short nFunction, short nWbit, long lSysByte)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strLog, strTime;
	CTime time = CTime::GetCurrentTime();

	char szLog[0xFF];
	sprintf(szLog, "%02d:%02d:%02d (EQ->HOST) S%dF%d", time.GetHour(), time.GetMinute(), time.GetSecond(), nStream, nFunction);
	AddLog(szLog);
}


void DlgGem::OnVariableInDeadBandEzgemctrl(long VID, short LimitID)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strTemp;
	strTemp.Format("%d", VID);
	strTemp.Format("%d", LimitID);
	// 확인 창 디스플레이
	m_gem.SendEventReport(CEID_RECIPE_MODIFYED);  /// Gem Recipe Update  ECID 1010	
}


void DlgGem::OnBnClickedButtonParameter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DlgGemParameter dlg;
	//	CDlgBox dlg;
	if (dlg.DoModal() == IDOK)
	{
		GemParameterSave();
		MessageBox("Parameter saved. \r\n\r\nRestart to apply now.");
	}
}
void DlgGem::GemParameterSave()
{

	// TODO: Add your control notification handler code here
	CString strTemp = _T("");
	CString strECID = _T("");
	CString strValue = _T("");
	//PORT ID


	strTemp.Format("%ld", m_GemLogConfig.m_nPort);
	SetDlgItemText(IDC_EDIT_PORTID, strTemp);
	//----------------------------------------------------------------------------------------
	//DEVICE ID
	strTemp.Format("%d", m_GemLogConfig.m_nDeviceID);
	SetDlgItemText(IDC_EDIT_DEVID, strTemp);

	//----------------------------------------------------------------------------------------


	strTemp.Format("%d", m_GemLogConfig.m_nLinkInterval);
	m_gem.SetEquipConstValue(ECID_LINKTEST, strTemp);
	if (strTemp != m_gem.GetCurrentECValue(ECID_LINKTEST))
	{
		//		strECID.Format("%d", ECID_LINKTEST);
		//		m_gem.SetCurrentStatusValue(SVID_ECID, strECID);
		//		m_gem.SetCurrentStatusValue(SVID_ECVAL, strTemp);
		//		SendEventReport(CEID_ECID_CHANGE);	// OPERATOR CHANGED EQUIPMENT CONSTANT

	}


	//----------------------------------------------------------------------------------------

	strTemp.Format("%d", m_GemLogConfig.m_nRetry);
	m_gem.SetEquipConstValue(ECID_RETRY, strTemp);


	//=== set retention ====//



	theApp.WriteConfigFile();

	m_gem.SetPort(m_GemLogConfig.m_nPort);
	m_gem.SetDeviceID(m_GemLogConfig.m_nDeviceID);
	m_gem.SetT3(m_GemLogConfig.m_nT3);
	m_gem.SetT5(m_GemLogConfig.m_nT5);
	m_gem.SetT6(m_GemLogConfig.m_nT6);
	m_gem.SetT7(m_GemLogConfig.m_nT7);
	m_gem.SetT8(m_GemLogConfig.m_nT8);
	m_gem.SetLinkTestInterval(m_GemLogConfig.m_nLinkInterval);
	m_gem.SetRetry(m_GemLogConfig.m_nRetry);


	char szValue[0xFF];
	sprintf(szValue, "%d", m_GemLogConfig.m_nDefaultControlState);
	m_gem.SetEquipConstValue(ECID_DEFAULT_CONTROL_STATE, szValue);
}
void DlgGem::ShowConfig()
{
	theApp.ReadConfigFile();

	CString strTemp = _T("");
	strTemp.Format("%ld", m_GemLogConfig.m_nPort);
	SetDlgItemText(IDC_EDIT_PORT, strTemp);

	//DEVICE ID
	strTemp.Format("%d", m_GemLogConfig.m_nDeviceID);
	SetDlgItemText(IDC_EDIT_DEVID, strTemp);

	if (m_GemLogConfig.m_bLogEnable > 0)
	{

		m_gem.EnableLog();
	}
	else
	{

		m_gem.DisableLog();
	}

}


void DlgGem::OnS7F17(long lMsgId)
{
	/*
	 *

	S7F17
	<L[n]
		<A "PPID">
	>.
	 */
	 /*	CStringArray *pRecipeList= new CStringArray();

		 INT nCnt = 0;
		 CString strPPID = _T("");
		 BOOL    bExistPPID = TRUE;
		 SHORT   nAck = 0x00;
		 BOOL    bDeleted = FALSE;

		 nCnt = m_gem.GetListItemOpen( lMsgId );
		 if( nCnt == 0 )
		 {
			 bExistPPID = TRUE;
			 nAck = 0x00;
		 }
		 else
		 {
			 for( int i = 0; i< nCnt ; i++ )
			 {
				 BOOL bE = FALSE;
				 strPPID = _T("");
				 GetAsciiItem( lMsgId, &strPPID );

				 if( strPPID == "" )
				 {

					 bExistPPID = FALSE;
					 nAck = 0x04;
					 break;
				 }

				 pRecipeList->Add( strPPID );

				 bE = GetRecipeExist( strPPID );
				 long nE = RecipeIDReturn( strPPID );
				 //if( !bE ) bExistPPID = FALSE;

				 if( nE == 0 ) bExistPPID = FALSE;

			 }
		 }

		 if( bExistPPID )
		 {
			 //Delete All Recipe
			 if( nCnt == 0 )
			 {
				 //DeleteRecipeAll();
				 //
				 RecipeAllDeleteReturn();


			 }
			 else
			 {
				 for( int j = 0; j< nCnt ; j++)
				 {
					 CString strDeletePPID = _T("");
					 strDeletePPID = pRecipeList->GetAt( j );

					 //Delete 1 Recipe
				 //	DeleteRecipe( strDeletePPID );
					 bDeleted = Recipe1DeleteReturn(strDeletePPID);

				 }
			 }
		 }

		 m_gem.GetListItemClose( lMsgId );

		 long rMsgId = m_gem.CreateReplyMsg( lMsgId );

		 if( bExistPPID ) nAck = 0x00;
		 else nAck = 0x04;

		 m_gem.AddBinaryItem( rMsgId, &nAck , 1 );

		 m_gem.SendMsg( rMsgId );

		 pRecipeList->RemoveAll();
		 pRecipeList = NULL;
		 delete pRecipeList;


		 if(bDeleted && (nAck == 0x00))
		 {
			 Main.m_strRecipename = strPPID;

			 m_gem.SetCurrentStatusValue( SVID_PPCHANGE_NAME , strPPID );
			 m_gem.SetCurrentStatusValue( SVID_PPCHANGE_STATE , RECIPE_DELETION );
			 SendEvent(CEID_PROCESS_PROGRAM_CHANGED);
		 }*/


}

void DlgGem::OnS7F19(long lMsgId)
{
	/*

	  S7F19
	  S7F20
	  <L[n]
			<A "RECIPE NAME">
			>
		*/


		//== Real Recipe Name from  MDB==
		/*

		  long rMsgId = m_gem.CreateReplyMsg( lMsgId );
		  m_gem.OpenListItem( rMsgId );

			CString strName = _T("");
			CString strQuery = _T("");
			strQuery= "SELECT * FROM PARAMETER_ENG07";
			CADORecordset rs(theApp.m_pDatabase);
			rs.Open(strQuery,CADORecordset::openQuery);

			  while(!rs.IsEOF())
			  {
			  //SELECT * FROM PARAMETER_ENG07 WHERE RECIPE_NAME
			  rs.GetFieldValue("RECIPE_NAME", strName);
			  if( strName.GetLength() > 0)
			  {
			  m_gem.AddAsciiItem( rMsgId , strName, strName.GetLength() );
			  }
			  rs.MoveNext();
			  }

				m_gem.CloseListItem( rMsgId );
				m_gem.SendMsg( rMsgId );


					for( int i = 0 ; i< 100 ; i++)
					{
					if( m_pStructureRecipe[i].m_strRecipeName != "" )
					{
					CString strPPID = _T("");

					  strPPID = m_pStructureRecipe[i].m_strRecipeName;
					  m_gem.AddAsciiItem( rMsgId , strPPID, strPPID.GetLength() );
					  }
					  }
		*/

		/*	long rMsgId = m_gem.CreateReplyMsg( lMsgId );
			m_gem.OpenListItem( rMsgId );
			//===================================
			CString strName = _T("");
			CString strQuery = _T("");
			strQuery= "SELECT * FROM PARAMETER_ENG07";
			CADORecordset rs(theApp.m_pDatabaseRcp);
			rs.Open(strQuery,CADORecordset::openQuery);

				  while(!rs.IsEOF())
				  {
					  //SELECT * FROM PARAMETER_ENG07 WHERE RECIPE_NAME
					  rs.GetFieldValue("RECIPE_NAME", strName);
					  if( strName.GetLength() > 0)
					  {
						  m_gem.AddAsciiItem( rMsgId , strName, strName.GetLength() );
					  }
					  rs.MoveNext();
				  }
				  //===========================================
				  m_gem.CloseListItem( rMsgId );
				  m_gem.SendMsg( rMsgId );


		}


		void DlgGem::OnS7F23(long lMsgId)
		{

			BOOL bExist = FALSE;

			CString strPPID = _T(""), strMDLN = _T(""), strSOFTREV = _T("");
			CString strPara = _T(""),strParaValue[50];
			for (int ncnt=0;ncnt<50;ncnt++)
			{
				strParaValue[ncnt] = "";
			}

			double dParamTime = 0, dParamAmount = 0;
			short  sParam = 0;
			int    iParam = 0, nAllZero = 0;
			INT nCnt = 0;

			m_gem.GetListItemOpen( lMsgId );
				GetAsciiItem( lMsgId, &strPPID );
				GetAsciiItem( lMsgId, &strMDLN );
				GetAsciiItem( lMsgId, &strSOFTREV );

				bExist = GetRecipeExist( strPPID );
				long nE = RecipeIDReturn( strPPID );


					nCnt = m_gem.GetListItemOpen( lMsgId );

					for( int i = 0; i < nCnt ; i++ )
					{
						CString strCCODE = _T("");


						m_gem.GetListItemOpen( lMsgId );

							GetAsciiItem( lMsgId, &strCCODE );
							if( strCCODE == CCODE_MAC_SLOT_COUNT	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU4Item( lMsgId, &dParamAmount);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[0] = strPara;

							}else if( strCCODE ==  CCODE_LAVEL_ANGLE_SELECT	 )
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU4Item( lMsgId, &strPara+1);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[1] = strPara;
							}else if( strCCODE == CCODE_OPPTAPE_ROTATE_COUNT	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[2] = strPara;
							}else if( strCCODE == CCODE_PARAMETER1	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[3] = strPara;
							}else if( strCCODE == CCODE_PARAMETER2	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[4] = strPara;
							}else if( strCCODE == CCODE_PARAMETER3	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[5] = strPara;
							}else if( strCCODE == CCODE_PARAMETER4	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[6] = strPara;
							}else if( strCCODE == CCODE_PARAMETER5	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[7] = strPara;
							}else if( strCCODE == CCODE_PARAMETER6	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[8] = strPara;
							}else if( strCCODE == CCODE_PARAMETER7	)
							{
								m_gem.GetListItemOpen( lMsgId );
								//m_gem.GetU1Item( lMsgId, &sParam);
								GetAsciiItem( lMsgId, &strPara );
								m_gem.GetListItemClose( lMsgId);
								strParaValue[9] = strPara;
							}

						m_gem.GetListItemClose( lMsgId );
					}

					m_gem.GetListItemClose( lMsgId );




			if( nE != 0 )
			{

				//============================================================
				// Update

				CString strFSize,strUVTime,strUVDosage,strWorkSel;

				strFSize = m_RecipeTable.WaferSize;


				strUVTime.Format("%4.2f",dParamTime);
				strUVDosage.Format("%4.2f",dParamAmount);

				RecipeDataSave(nE,strPPID,"DISABLE",strParaValue[0],strParaValue[1],strParaValue[2],strParaValue[3],strParaValue[4],strParaValue[5],strParaValue[6],strParaValue[7],strParaValue[8],strParaValue[9]);
				//
				Main.m_strRecipename = strPPID;

				m_gem.SetCurrentStatusValue( SVID_PPCHANGE_NAME , strPPID );
				m_gem.SetCurrentStatusValue( SVID_PPCHANGE_STATE , RECIPE_EDITING );
				SendEvent(CEID_PROCESS_PROGRAM_CHANGED);

				AddLog( "RecipeDataSave:" + strPPID );
			}
			else if( strPPID != ""  )
			{
				CString strFSize;

				strFSize = m_RecipeTable.WaferSize;


				//==
				RecipeDataCreate(strPPID,"DISABLE",strParaValue[0],strParaValue[1],strParaValue[2],strParaValue[3],strParaValue[4],strParaValue[5],strParaValue[6],strParaValue[7],strParaValue[8],strParaValue[9]);
				Main.m_strRecipename = strPPID;

				m_gem.SetCurrentStatusValue( SVID_PPCHANGE_NAME , strPPID );
				m_gem.SetCurrentStatusValue( SVID_PPCHANGE_STATE , RECIPE_CREATION );
				SendEvent(CEID_PROCESS_PROGRAM_CHANGED);

				AddLog( "RECIPE CREATE :" + strPPID );

			}
			else
			{
				AddLog( "RECIPE CREATE FAIL :" + strPPID );
			}
			m_gem.GetListItemClose( lMsgId );

			long rMsgId = m_gem.CreateReplyMsg( lMsgId );


			//=====================
			SHORT	sACKC = 0;
			//============ 보내온 레시피의 이름이 없거나, 두개의 값이 다 0인 경우 =====
			strPPID.Replace(" ", "");
			if( strPPID == "" ) sACKC = 0x04;


			m_gem.AddBinaryItem( rMsgId , &sACKC , 1 );

			m_gem.SendMsg( rMsgId );*/

}

void DlgGem::SendS7F23()
{
	/*	long lMsgId = m_gem.CreateMsg( 7, 23, TRUE );

		m_gem.OpenListItem( lMsgId );

		CString strPPID = _T("");
		CString strPara = _T(""),strParaValue[MAX_RECIPECNTS_10];
		for (int ncnt=0;ncnt<MAX_RECIPECNTS_10;ncnt++)
		{
			strParaValue[ncnt] = "";
		}

		strPPID = m_RecipeTable.Name;

		CADORecordset rs(theApp.m_pDatabase);
		CString strQuery = "SELECT * FROM PARAMETER_ENG07 WHERE RECIPE_NAME='" + strPPID + "'";
		CString strTime,strDosage,strWorkSel;
		if (!rs.Open(strQuery, CADORecordset::openQuery))
		{
			m_gem.CloseListItem( lMsgId );
			m_gem.SendMsg( lMsgId );

			return ;
		}
		if (!rs.IsEOF())
		{
			CString strValue;


			m_gem.AddAsciiItem( lMsgId, strPPID , strPPID.GetLength());

			for (int i=0;i<MAX_RECIPECNTS_10;i++)
			{
				rs.GetFieldValue(i+3, strValue);
				strParaValue[i] = strValue;
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
			}



			m_gem.OpenListItem( lMsgId );

	//========
				m_gem.OpenListItem( lMsgId );
					//=== CCODE = TIME ==================

					CString strCCODE = CCODE_MAC_SLOT_COUNT;
					strValue = strParaValue[0];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
					m_gem.OpenListItem( lMsgId );
						m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
					m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//=============
				m_gem.OpenListItem( lMsgId );
						//=== CCODE = AMOUNT_OF_LIGHT
						strCCODE = CCODE_LAVEL_ANGLE_SELECT;
						strValue = strParaValue[1];
						m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
						m_gem.OpenListItem( lMsgId );
							m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
						m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_OPPTAPE_ROTATE_COUNT;
				strValue = strParaValue[2];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER1;
				strValue = strParaValue[3];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER2;
				strValue = strParaValue[4];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER3;
				strValue = strParaValue[5];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER4;
				strValue = strParaValue[6];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER5;
				strValue = strParaValue[7];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER6;
				strValue = strParaValue[8];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//==========
				m_gem.OpenListItem( lMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER7;
				strValue = strParaValue[9];
					m_gem.AddAsciiItem( lMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( lMsgId );
				m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( lMsgId );

				m_gem.CloseListItem( lMsgId );
	//===========

				//============
				m_gem.CloseListItem( lMsgId );



		}

		m_gem.CloseListItem( lMsgId );


		m_gem.SendMsg( lMsgId );*/



}
void DlgGem::OnS7F25(long lMsgId)
{
	/*	BOOL bExist = FALSE;
		CString strPPID = _T("");
		GetAsciiItem( lMsgId , &strPPID );

		bExist = GetRecipeExist( strPPID );
		long nE = RecipeIDReturn( strPPID );
		CString strPara = _T(""),strParaValue[MAX_RECIPECNTS_10];
		for (int ncnt=0;ncnt<MAX_RECIPECNTS_10;ncnt++)
		{
			strParaValue[ncnt] = "";
		}

		long rMsgId = m_gem.CreateReplyMsg( lMsgId );
		m_gem.OpenListItem( rMsgId );
		if( nE != 0 )
		{
			CADORecordset rs(theApp.m_pDatabase);
			CString strQuery = "SELECT * FROM PARAMETER_ENG07 WHERE RECIPE_NAME='" + strPPID + "'";
			CString strTime,strDosage,strWorkSel;
			if (!rs.Open(strQuery, CADORecordset::openQuery))
			{
				m_gem.CloseListItem( rMsgId );
				m_gem.SendMsg( rMsgId );

				return ;
			}
			if (!rs.IsEOF())
			{
				CString strValue;

				for (int i=0;i<MAX_RECIPECNTS_10;i++)
				{
					rs.GetFieldValue(i+3, strValue);
					strParaValue[i] = strValue;
					//m_gem.AddAsciiItem( lMsgId, strValue, strValue.GetLength());
				}


			}


			INT nNumber = 0;
			nNumber = GetRecipe( strPPID );
			m_gem.AddAsciiItem( rMsgId, strPPID, strPPID.GetLength());


			m_gem.AddAsciiItem( rMsgId, m_strModelName, m_strModelName.GetLength());

			m_gem.AddAsciiItem( rMsgId, m_strSoftRev, m_strSoftRev.GetLength());

			m_gem.OpenListItem( rMsgId );

				CString strCCODE = _T(""), strValue = _T("");


	//========
				m_gem.OpenListItem( rMsgId );
					//=== CCODE = TIME ==================

					strCCODE = CCODE_MAC_SLOT_COUNT;
					strValue = strParaValue[0];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
					m_gem.OpenListItem( rMsgId );
						m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
					m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//=============
				m_gem.OpenListItem( rMsgId );
						//=== CCODE = AMOUNT_OF_LIGHT
						strCCODE = CCODE_LAVEL_ANGLE_SELECT;
						strValue = strParaValue[1];
						m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
						m_gem.OpenListItem( rMsgId );
							m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
						m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_OPPTAPE_ROTATE_COUNT;
				strValue = strParaValue[2];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER1;
				strValue = strParaValue[3];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER2;
				strValue = strParaValue[4];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER3;
				strValue = strParaValue[5];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER4;
				strValue = strParaValue[6];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER5;
				strValue = strParaValue[7];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER6;
				strValue = strParaValue[8];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========
				m_gem.OpenListItem( rMsgId );
				//=== CCODE = AMOUNT_OF_LIGHT
				strCCODE = CCODE_PARAMETER7;
				strValue = strParaValue[9];
					m_gem.AddAsciiItem( rMsgId , strCCODE, strCCODE.GetLength());
				m_gem.OpenListItem( rMsgId );
				m_gem.AddAsciiItem( rMsgId, strValue, strValue.GetLength());
				m_gem.CloseListItem( rMsgId );

				m_gem.CloseListItem( rMsgId );
	//==========

	//============

			m_gem.CloseListItem( rMsgId );

		}
		m_gem.CloseListItem( rMsgId );

		m_gem.SendMsg( rMsgId );*/


}

void DlgGem::OnS1F1(long lMsgId)
{
	long rMsgId = m_gem.CreateReplyMsg(lMsgId);

	m_gem.OpenListItem(rMsgId);
	//====
	m_gem.AddAsciiItem(rMsgId, m_strModelName, m_strModelName.GetLength());
	m_gem.AddAsciiItem(rMsgId, m_strSoftRev, m_strSoftRev.GetLength());
	m_gem.CloseListItem(rMsgId);

	m_gem.SendMsg(rMsgId);

}

// 다운로드 할 레시피의 이름과 파일 길이 체크 ( HOST - > EQ )
void DlgGem::OnS7F1(long lMsgId)
{
	SHORT   nACK = 0x00;
	double nLength = 0;
	CString strPPID = _T("");
	m_gem.GetListItemOpen(lMsgId);
	GetAsciiItem(lMsgId, &strPPID);// nACK := 0 레시피를 다운 받을 수 있음. nACK := 3 
	m_gem.GetU4Item(lMsgId, &nLength); //nLength 파일의 바이트 , +- 10
	m_gem.GetListItemClose(lMsgId);
	// if(nLength  파일 사이즈 )
	//	{
	//		nACK = 0;
	//	}

	long rMsgId = m_gem.CreateReplyMsg(lMsgId);
	m_gem.AddBinaryItem(rMsgId, &nACK, 1);
	m_gem.SendMsg(rMsgId);
}

void DlgGem::OnS7F2(long lMsgId)
{
	SHORT   nACK = 0x00;
	m_gem.GetBinaryItem(lMsgId, &nACK);
	m_gem.CloseMsg(lMsgId);

	if (nACK == 0)
	{
		//PP보내는 부분 추가...	
	}
}
// 호스트에서 장비로 레시피 파일을 전송 
void DlgGem::OnS7F3(long lMsgId)
{
	/*	CString strPPID;
		SHORT   nACK = 0x00;
		SHORT   mAck = 0x00;


		m_gem.GetListItemOpen(lMsgId);
		GetAsciiItem(lMsgId, &strPPID);
		strPPID.MakeUpper();

		CString strTemp = strPPID;

		if(strPPID.GetLength() > 0) mAck = 0x01;

		if(mAck == 0x01)
		{
				//==============================================================
					// RCP 파일을 생성
			strPPID += ".RCP";
			m_gem.GetFileBinaryItem(lMsgId, "RECIPE\\"+strPPID);
			if(FileListCheck(strTemp))
			{
				//RCP 파일을 열어 MDB 파일에 추가
					UnFormattedRcipeDataSave(strPPID , TRUE);
			}else
			{
				// RCP 파일을 열어 MDB 파일에 추가
					UnFormattedRcipeDataSave(strPPID , FALSE);
			}

			}else nACK = 0x01;


			lMsgId = m_gem.CreateReplyMsg(lMsgId);
			m_gem.AddBinaryItem(lMsgId, &nACK, 1);
			m_gem.SendMsg(lMsgId);


			if( nACK == 0x00 )
			{
				// plc로 TKIN REQUEST 진행
			}
	}


	void DlgGem::OnS7F5(long lMsgId)
	{

		CString strPPID;
		SHORT   nAck = 0x00;

		GetAsciiItem(lMsgId, &strPPID);
		strPPID.MakeUpper();

		CString strPPName = strPPID;
		strPPName += ".RCP";


		if(!FileListCheck(strPPID))
		{
			MDBtoFILE(strPPID);
			long lReplyMsg = m_gem.CreateReplyMsg(lMsgId);
			m_gem.OpenListItem(lReplyMsg);
			m_gem.AddAsciiItem(lReplyMsg,strPPID,strPPID.GetLength());
			m_gem.AddFileBinaryItem(lReplyMsg,"RECIPE\\"+strPPName);
			m_gem.CloseListItem(lReplyMsg);

			m_gem.SendMsg(lReplyMsg);
		}else
		{
			long lReplyMsg = m_gem.CreateReplyMsg(lMsgId);
			m_gem.OpenListItem(lReplyMsg);
			m_gem.CloseListItem(lReplyMsg);

			m_gem.SendMsg(lReplyMsg);

		}*/
}

//================================================================================
//== 20151001
void DlgGem::SendS7F3(CString strppID)
{
	//버튼을 눌렀을 때 해당 레시피를 HOST로 Upload시킴.

/*	long lMsgId = 0;
	CString strPpid = _T("");
	CString strPath = _T("");

	//FileListCheck(strppID);
	MDBtoFILE(strppID);

	strPpid = strppID;
	lMsgId = m_gem.CreateMsg( 7 , 3 , 1 );
	m_gem.OpenListItem( lMsgId );

		m_gem.AddAsciiItem( lMsgId , strPpid , strPpid.GetLength() );
		// 호스트로 전송될 strPpid 레시피의 이름.
		strPath = "RECIPE\\" + strPpid + ".RCP";
		m_gem.AddFileBinaryItem( lMsgId , strPath );
		// 해당 레시피의 경로.
		// RECIPEFOLDER\\RECIPE1.RCP 처럼 들어가야함.

	m_gem.CloseListItem( lMsgId );
	m_gem.SendMsg( lMsgId );*/
}

//== 20151001
void DlgGem::SendS7F5(CString strppID)
{
	// 버튼을 눌렀을 때 HOST로 특정 레시피를 요청. S7F6을 통해서 파일을 받음.
/*	long lMsgId = 0;
	CString strPpid = _T("");

	strPpid = strppID;
	// 요청할 레시피 이름 strPpid

	lMsgId = m_gem.CreateMsg( 7 , 5 , 1 );
	m_gem.AddAsciiItem( lMsgId , strPpid , strPpid.GetLength() );

	m_gem.SendMsg( lMsgId );*/


}

//== 20151001
void DlgGem::OnS7F4(long lMsgid)
{
	/*	short nAck = 0;
		m_gem.GetBinaryItem( lMsgid , &nAck );

		if( nAck == 0 )
		{
			AddLog( "호스트 에 레시피가 업로드 되었습니다." );
			Main.m_bRecipeUploadOK = TRUE;
			SetCIOBitGem(130303);
		}
		else
		{
			AddLog( "호스트에 레시피 업로드 작업이  실패 되었습니다." );
			Main.m_bRecipeUploadFAIL = TRUE;
		}*/
}
//== 20151001
void DlgGem::OnS7F6(long lMsgId)
{
	/*	CString strPpid = _T("");
		CString strPath = _T("");
		CString strTemp = _T("");
		INT		nCnt = 0;

		nCnt = m_gem.GetListItemOpen( lMsgId );

		if( nCnt > 0 )
		{
			GetAsciiItem( lMsgId , &strPpid );

			strPath = "RECIPE\\" + strPpid + ".RCP";
			m_gem.GetFileBinaryItem( lMsgId , strPath );
			strTemp = 	strPpid;
			   if(FileListCheck(strPath))
				{
						// RCP 파일을 열어 MDB 파일에 추가
						strTemp += ".RCP";
						UnFormattedRcipeDataSave(strTemp , TRUE);

				}else
				{
					// RCP 파일을 열어 MDB 파일에 추가
						strTemp += ".RCP";
						UnFormattedRcipeDataSave(strTemp , FALSE);
				}

			AddLog( strTemp + "호스트 에서 레시피를 다운 받았습니다." );
			Main.m_bRecipeDownloadOK = TRUE;
			SetCIOBitGem(130303);
		}
		else
		{
			AddLog( strTemp +"는 호스트에 존재하지 않는 레시피입니다." );
			Main.m_bRecipeDownloadFAIL = TRUE;
		}
		m_gem.GetListItemClose( lMsgId );
		m_gem.CloseMsg( lMsgId );*/

}

//================================================================================
// S14F3

void DlgGem::OnS14F3(long lMsgId)
{
	/*	CStringArray *pObjId =new CStringArray();
		CStringArray *pAttrId =new CStringArray();
		CStringArray *pAttrData =new CStringArray();

		//CStringArray *pErrorCode =new CStringArray();

		CUIntArray *pErrorCode = new CUIntArray();
		CStringArray *pErrorText =new CStringArray();

		short nObjack = 0;

		CString strObjectSpec = "", strObjType = "", strObjId = "", strAttriID = "" , strAttriData = "";
		CString strTempLot , strTempResult , strTempPartId , strTempStepSeq ,  strTempLotType , strTempQty , strTempRecipeName , strTempWriteRfid;
		CString strLabelCnt, strSpecialLabel,strSboxLabel,strSummaryLabel;
		m_gem.GetListItemOpen( lMsgId );
			GetAsciiItem( lMsgId , &strObjectSpec ); // OBJSPC
			GetAsciiItem( lMsgId , &strObjType ); // OBJTYPE

			short nCntOfObjId = m_gem.GetListItemOpen( lMsgId );
			for( int i = 0 ; i < nCntOfObjId ; i++ )
			{
				GetAsciiItem( lMsgId , &strObjId );
				pObjId->Add( strObjId );
			}
			m_gem.GetListItemClose( lMsgId );

			short nCntOfAttri = m_gem.GetListItemOpen( lMsgId );
			for( int j = 0 ; j < nCntOfAttri ; j++ )
			{
				m_gem.GetListItemOpen( lMsgId );
					GetAsciiItem( lMsgId , &strAttriID );
					GetAsciiItem( lMsgId , &strAttriData );
					pAttrId->Add( strAttriID );
					pAttrData->Add( strAttriData);
				m_gem.GetListItemClose( lMsgId );
			}
			m_gem.GetListItemClose( lMsgId );
		m_gem.GetListItemClose( lMsgId );

		//============ 값을 비교 한 후 =============================
		nObjack = 0; // 0 : OK / 1 : ERROR
		short nCountError = 1; // error count
		CString strObjID = _T("");
		CString strAttrID = _T("");
		CString strAttrData = _T("");


		//== lotid 비교
		if(strObjectSpec != "LOT")
		{
			nObjack = 1;
			pErrorCode->Add( 1);
			pErrorText->Add("OBJSPEC ERROR");
		}

		//== object type lotinfo / printinfo만 받을 수 있음.
		if(strObjType != OBJTYPE_LOTINFO && strObjType != OBJTYPE_PRINTINFO && strObjType != OBJTYPE_SUMMARY_LABEL)
		{
			nObjack = 1;
			pErrorCode->Add( 2);
			pErrorText->Add("OBJTYPE ERROR");
		}

		//== objspec이 lot이 아닌 경우 / lotinfo or printinfo가 아닌 경우 받을 필요가 없음.
		if( nObjack == 0 )
		{
			for( i = 0 ; i < nCntOfObjId ; i++ )
			{
				strObjID = pObjId->GetAt(i);
				strObjID.TrimLeft();
				strObjID.TrimRight();
				if(strObjID == "")
				{
					nObjack = 1;
					pErrorCode->Add( 3);
					pErrorText->Add("OBJID ERROR");
				}
				//Main.LotID =strObjID;
				strTempLot =strObjID;
			}




			if( strObjType == "LOTINFO" )
			{

				for( i = 0 ; i < nCntOfAttri ; i++ )
				{
					strAttrID = pAttrId->GetAt(i);
					strAttrData = pAttrData->GetAt(i);

					strAttrData.TrimLeft();
					strAttrData.TrimRight();

					if(strAttrID == "RESULT")
					{
						if((strAttrData != "PASS") && (strAttrData != "FAIL"))
						{
							nObjack = 1;
							pErrorCode->Add( 4);
							pErrorText->Add("RESULT ERROR");
						}
						//Main.Result = strAttrData;
						strTempResult =  strAttrData;

					}
					else if(strAttrID == "CARRIERID")
					{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 5);
							pErrorText->Add("PARTID ERROR");
						}
						//Main.PartID = strAttrData;
						strTempPartId = strAttrData;

					}
					else if(strAttrID == "PARTID")
					{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 5);
							pErrorText->Add("PARTID ERROR");
						}
						//Main.PartID = strAttrData;
						strTempPartId = strAttrData;

					}
					else if(strAttrID == "LOTTYPE")
					{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 6);
							pErrorText->Add("LOTTYPE ERROR");
						}
						//Main.LotType = strAttrData;
						strTempLotType = strAttrData;
					}else if(strAttrID == "STEPSEQ")
					{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 7);
							pErrorText->Add("STEPSEQ ERROR");
						}
						//Main.StepSeq = strAttrData;
						strTempStepSeq = strAttrData;

					}else if(strAttrID == "QTY")
					{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 8);
							pErrorText->Add("QTY ERROR");
						}
						//Main.QTY = strAttrData;
						strTempQty = strAttrData;

					}else if(strAttrID == "RECIPEID")
						{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 9);
							pErrorText->Add("RECIPEID ERROR");
						}
						//Main.RecipeName = strAttrData;
						strTempRecipeName = strAttrData;

					}else if(strAttrID == "RFIDWRITE")
					{
						if(strAttrData == "")
						{
							nObjack = 1;
							pErrorCode->Add( 10);
							pErrorText->Add("RFIDWRITE ERROR");
						}


					}else
					{
						nObjack = 1;
						pErrorCode->Add( 10);
						pErrorText->Add("ATTRID ERROR");
					}
				}
			}

			else if( strObjType == OBJTYPE_PRINTINFO )
			{
				for( i = 0 ; i < nCntOfAttri ; i++ )
				{
					strAttrID = pAttrId->GetAt(i);
					strAttrData = pAttrData->GetAt(i);

					strAttrData.TrimLeft();
					strAttrData.TrimRight();

						if(strAttrID == "SBOX_LABEL")
						{
							if(strAttrData == "")
							{
								nObjack = 1;
								pErrorCode->Add( 1);
								pErrorText->Add("SBOX LABEL ERR");
							}

							strSboxLabel = strAttrData;
						}
						else if(strAttrID == "LABEL_CNT")
						{
							if(strAttrData == "")
							{
								nObjack = 1;
								pErrorCode->Add( 2);
								pErrorText->Add("LABEL CNT ERR");
							}

						}
						else if(strAttrID == "SPECIAL_LABEL")
						{

						}
						else if(strAttrID == "RESULT")
						{
							if(strAttrData == "")
							{
								nObjack = 1;
								pErrorCode->Add( 2);
								pErrorText->Add("LABEL CNT ERR");
							}

						}
						else
						{
							nObjack = 1;
							pErrorCode->Add( 10);
							pErrorText->Add("ATTRID ERROR");
						}

				}
			}
			else if( strObjType == OBJTYPE_SUMMARY_LABEL  )
			{
				for( i = 0 ; i < nCntOfAttri ; i++ )
				{
					strAttrID = pAttrId->GetAt(i);
					strAttrData = pAttrData->GetAt(i);

					strAttrData.TrimLeft();
					strAttrData.TrimRight();

						if(strAttrID == "SUMMARY_LABEL")
						{
							if(strAttrData == "")
							{
								nObjack = 1;
								pErrorCode->Add( 1);
								pErrorText->Add("SUMMARY LABEL ERR");
							}

							strSummaryLabel = strAttrData;
						}
				}
			}
		}

		 //== 2018 01 18 skpark S14F3이 OK인 경우에만 지역변수에서 글로벌 별수로 값을 세팅..
		 if( nObjack == 0 )
		 {
			if( strObjType == "LOTINFO" )
			{
				Main.LotID  =  strTempLot;
				Main.Result = strTempResult;
				Main.PartID = strTempPartId;
				Main.StepSeq = strTempStepSeq;
				Main.LotType = strTempLotType;
				Main.QTY = strTempQty;
				Main.RecipeName = strTempRecipeName;

			}
			else if( strObjType == "SBOX_LABELINFO" )
			{
				Main.WriteRfid = strSboxLabel;
			}
			else if( strObjType == "SUMMARY_LABELINFO" )
			{
				Main.WriteRfid = strSummaryLabel;
			}
		 }


		 //===========================================================================


		long rMsgId = m_gem.CreateReplyMsg( lMsgId );
		m_gem.OpenListItem( rMsgId );
			//=====================  OBJ갯수만큼 =======================================
			m_gem.OpenListItem( rMsgId );
			if( nObjack == 0 )  // OK인 경우 파라미터를 보냄.
			{
				for( int j = 0 ; j < nCntOfObjId ; j++ )
				{
					m_gem.OpenListItem( rMsgId );
						m_gem.AddAsciiItem( rMsgId , pObjId->GetAt(j) , pObjId->GetAt(j).GetLength() );
						m_gem.OpenListItem( rMsgId );
							for( int i = 0 ; i < nCntOfAttri ; i++ )
							{
								m_gem.OpenListItem( rMsgId );
								m_gem.AddAsciiItem( rMsgId , pAttrId->GetAt(i) , pAttrId->GetAt(i).GetLength() );     // 해당 OBJID의 ATTRID에 아래의 값을 세팅한다.
								m_gem.AddAsciiItem( rMsgId , pAttrData->GetAt(i) , pAttrData->GetAt(i).GetLength() ); // 즉, ex) LOTID에 해당 RESULT에 PASS를 세팅한다.
								m_gem.CloseListItem( rMsgId );
							}
						m_gem.CloseListItem( rMsgId );
					m_gem.CloseListItem( rMsgId );
				}
				//OK BIT TO PLC   20171018
			}
			m_gem.CloseListItem( rMsgId);
			//============================================================
			m_gem.OpenListItem( rMsgId );
				//m_gem.AddBinaryItem( rMsgId , &nObjack , 1); //0  OK, 1 FAIL
				m_gem.AddU1Item( rMsgId , &nObjack , 1); //0  OK, 1 FAIL
				m_gem.OpenListItem( rMsgId );
				if( nObjack != 0 )
				{
					 for( int k = 0 ; k < pErrorCode->GetSize() ; k++ )
					 {
						m_gem.OpenListItem( rMsgId );
							//m_gem.AddAsciiItem( rMsgId , pErrorCode->GetAt(k) , pErrorCode->GetAt(k).GetLength() );
							long nError = (long)pErrorCode->GetAt(k);
							m_gem.AddU2Item( rMsgId , &nError , 1 );
							m_gem.AddAsciiItem( rMsgId , pErrorText->GetAt(k) , pErrorText->GetAt(k).GetLength() );
						m_gem.CloseListItem( rMsgId );
					 }

					 //FAIL BIT TO PLC   20171018
				}
				m_gem.CloseListItem( rMsgId );
			m_gem.CloseListItem( rMsgId );
		 m_gem.CloseListItem( rMsgId );
		 m_gem.SendMsg( rMsgId );



		//== array 초기화

		if(pObjId)              delete pObjId;        pObjId = NULL;
		if(pAttrId)             delete pAttrId;       pAttrId = NULL;
		if(pAttrData)          delete pAttrData;    pAttrData = NULL;
		if(pErrorCode)       delete pErrorCode; pErrorCode = NULL;
		if(pErrorText)        delete pErrorText;  pErrorText = NULL;*/

}
void DlgGem::OnS3F17(long lMsgId)
{
	// TODO: Add your control notification handler code here
	//== 2018 01 18 skpark
	short nPortNo, ACK = 0;
	double DATAID = 0;
	CString strCarrierAction = _T("");
	CString strWaferNo = "";
	CString strCarrierID = _T(""), strTemp = _T(""), strCAttrId = _T(""), strCAttrData = _T("");   //CarrierID 는 CSTID(RFID)입니다.
	INT nCnt = 0;
	short nCapacity = 0, nSubStrateCount = 0, nSlot = 0;
	CString strUsage = _T(""), strLotId = _T(""), strWaferId = _T("");

	CStringArray* pAttrLotId = new CStringArray();
	CStringArray* pAttrWaferId = new CStringArray();
	CUIntArray* pAttrSlot = new CUIntArray();

	m_gem.GetListItemOpen(lMsgId);
	m_gem.GetU4Item(lMsgId, &DATAID);
	GetAsciiItem(lMsgId, &strCarrierAction);
	GetAsciiItem(lMsgId, &strCarrierID);
	m_gem.GetU1Item(lMsgId, &nPortNo); // m_gem.GetBinaryItem(lMsgId, &nPortNo);
	nCnt = m_gem.GetListItemOpen(lMsgId);

	for (int i = 0; i < nCnt; i++)
	{
		m_gem.GetListItemOpen(lMsgId);
		strCAttrId = "";
		GetAsciiItem(lMsgId, &strCAttrId);

		strCAttrId.MakeUpper();
		if (strCAttrId == "CAPACITY")
		{
			m_gem.GetBinaryItem(lMsgId, &nCapacity);
		}
		else if (strCAttrId == "SUBSTRATECOUNT")
		{
			m_gem.GetBinaryItem(lMsgId, &nSubStrateCount);
		}
		else if (strCAttrId == "CONTENTMAP")
		{
			INT nCntOfWafer = m_gem.GetListItemOpen(lMsgId);
			for (int j = 0; j < nCntOfWafer; j++)
			{
				m_gem.GetListItemOpen(lMsgId);
				GetAsciiItem(lMsgId, &strLotId);
				GetAsciiItem(lMsgId, &strWaferId);

				//if( strLotId != "" )
				//{
				pAttrLotId->Add(strLotId);
				pAttrWaferId->Add(strWaferId);
				//	WaferSlotCompare();
				//}
				strWaferNo.Format("P%d", j + 1);
				WriteWaferIDListFile("PORT1", strWaferNo, strWaferId);
				m_gem.GetListItemClose(lMsgId);
			}
			m_gem.GetListItemClose(lMsgId);
		}
		else if (strCAttrId == "SLOTMAP")
		{

			CString Map;
			INT nCntOfSlot = m_gem.GetListItemOpen(lMsgId);
			for (int k = 0; k < nCntOfSlot; k++)
			{

				m_gem.GetU1Item(lMsgId, &nSlot);
				pAttrSlot->Add(nSlot); //
			}

			m_gem.GetListItemClose(lMsgId);
		}
		else if (strCAttrId == "USAGE")
		{
			GetAsciiItem(lMsgId, &strUsage);
			//				if( strUsage != "PRODUCT" );
		}

		m_gem.GetListItemClose(lMsgId);

	}


	CString m_strWaferID, m_strSlotNo, m_strLotId;
	int Slot;
	UINT port = 0;

	CString strSlotNoList = _T("");

	for (int k = 0; k < 25; k++)
	{
		m_strWaferID = pAttrWaferId->GetAt(k);
		Slot = pAttrSlot->GetAt(k);
		m_strLotId = pAttrLotId->GetAt(k);
		m_strSlotNo.Format("%d", Slot);
		strSlotNoList += m_strSlotNo;
		strSlotNoList.Replace("2", "0");
		strSlotNoList.Replace("4", "1");
	}
	//	ACK = MappingDataCompare(port,strSlotNoList);



	m_gem.GetListItemClose(lMsgId);

	m_gem.GetListItemClose(lMsgId);
	m_gem.GetListItemClose(lMsgId);

	long lReplyMsg = m_gem.CreateReplyMsg(lMsgId);

	m_gem.OpenListItem(lReplyMsg);
	m_gem.AddU1Item(lReplyMsg, &ACK, 1);
	m_gem.OpenListItem(lReplyMsg);
	m_gem.CloseListItem(lReplyMsg);

	m_gem.SendMsg(lReplyMsg);

	if (pAttrLotId)				delete pAttrLotId;		pAttrLotId = NULL;
	if (pAttrWaferId)			delete pAttrWaferId;	pAttrWaferId = NULL;
	if (pAttrSlot)				delete pAttrSlot;		pAttrSlot = NULL;
}
//================================================================================

//void DlgGem::OnCommEstablishedEzgemctrl()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}

void DlgGem::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgGem::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
