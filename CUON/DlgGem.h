#pragma once
#include "afxwin.h"
#include "ezgem.h"

// DlgGem 대화 상자입니다.

class DlgGem : public CDialogEx
{
	DECLARE_DYNAMIC(DlgGem)

public:
	DlgGem(CWnd* pParent = NULL);   // 표준 생성자입니다.

	void AddCEID();
	void AddSVID();
	void GemStart();
	//	void GemStop();
	void InitGem();
	void ReadConfigFile();
	long GetAsciiItem(long lMsgId, CString* strBuff);
	void AddLog(CString strLog);

	void ShowConfig();

	void SendEventReport(long lCEID);
	void ReadDataBaseCEID();
	void ReadDataBaseSVID();
	void CheckGemEmemory();
	void UpdateSVID(int nSvid);
	void GemParameterSave();

	void OnS7F25(long lMsgId);
	void OnS7F23(long lMsgId);
	void OnS7F19(long lMsgId);
	void OnS7F17(long lMsgId);
	void SendS7F23();
	void OnS1F1(long lMsgId);

	void OnS7F1(long lMsgId);
	void OnS7F2(long lMsgId);
	void OnS7F3(long lMsgId);
	void OnS7F5(long lMsgId);
	void OnS7F4(long lMsgId);
	void OnS7F6(long lMsgId);
	void OnS3F17(long lMsgld);

	void OnS14F3(long lMsgId);//20171018 추가

	void SendS7F3(CString strppID);
	void SendS7F5(CString strppID);
	/////
	int  nCEID[400];
	CString  strCEIDMsg[400];
	int eMemoryBufPoint[100][16];
	short nCntCEID;
	/////
	int			nSVID[400];
	CString		strSVIDMsg[400];
	CString		strSVIDMeterial[400];
	CString		strSVIDId[400];
	CString		strSVIDType[400];
	short		nCntSVID;
	int			nSVIDSlot[400];
	int			nSVIDPort[400];

	//////////////////////////////////////////////////////////////////////////
	UINT	m_nControlState;
	UINT	m_nPrevControlState;
	UINT	m_nDefaultControlState;

	UINT	m_nProcessMode_Control;
	UINT	m_nProcessMode_Base;

	UINT	m_nPrevProcessMode_Control;
	UINT	m_nPrevProcessMode_Base;

	SHORT	m_nProcessState;
	SHORT	m_nPrevProcessState;

	SHORT	m_nRunModeState;
	SHORT	m_nPrevRunModeState;

	SHORT	m_nOperationMode;
	SHORT	m_nPrevOperationMode;

	UINT	m_nOperatonMode;
	UINT	m_nPrevOperatonMode;


	CString 	m_strModelName;
	CString 	m_strSoftRev;
	CString 	m_strHostStopReason;
	CString 	m_strHostErrCode;
	CString 	m_strHostErrDesc;


	///////////////// HSMS PARAM (ECID VARIABLES) ////

	////
	virtual ~DlgGem();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_GEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CListBox m_listLog;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEZGEM m_gem;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonLocal();
	afx_msg void OnBnClickedButtonRemote();
	afx_msg void OnBnClickedButtonOffline();
	afx_msg void OnBnClickedButtonParameter();
	DECLARE_EVENTSINK_MAP()
	void OnConnectedEzgemctrl();
	void OnDisconnectedEzgemctrl();
	void OnDateTimeSetRequestEzgemctrl(long lMsgId, LPCTSTR strNewDateTime);
	void OnEstablishCommRequestEzgemctrl(long lMsgId);
	void OnOnlineRequestEzgemctrl(long lMsgId);
	void OnOfflineRequestEzgemctrl(long lMsgId);
	void OnRemoteCommandEzgemctrl(long lMsgId, LPCTSTR strCommand, short nParamCount);
	void OnNewEquipConstEzgemctrl(long lMsgId, short nCount);
	void OnTerminalMessageSingleEzgemctrl(long lMsgId, LPCTSTR strMsg, short nCode);
	void OnTerminalMessageMultiEzgemctrl(long lMsgId, short nCode, short nCount);
	void OnMsgRequestedEzgemctrl(long lMsgId);
	void OnOnlineLocalEzgemctrl();
	void OnOnlineRemoteEzgemctrl();
	void OnSecsMsgInEzgemctrl(short nStream, short nFunction, short nWbit, long lSysByte);
	void OnSecsMsgOutEzgemctrl(short nStream, short nFunction, short nWbit, long lSysByte);
	void OnVariableInDeadBandEzgemctrl(long VID, short LimitID);


	//	void OnCommEstablishedEzgemctrl();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
