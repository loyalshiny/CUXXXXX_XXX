#pragma once
#include "mscomm.h"

// DlgLoadPortSetting 대화 상자

class DlgLoadPortSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLoadPortSetting)

public:
	DlgLoadPortSetting(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgLoadPortSetting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOADPORT_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnCbnDropdownComboPort();
	afx_msg void OnCbnDropdownComboCom();
	short g_nOpPort;
	short g_nOpComport;
	CString g_strOpPort;
	CString g_strOpComport;
	void OpenerCommPortOpen(short nComPort, short nLoadPort);
	void OpenerCommPortClose(short nComPort, short nLoadPort);
	void RfidCommPortOpen(short nComPort, short nLoadPort);
	void RfidCommPortClose(short nComPort, short nLoadPort);
	void getSerialPort(short nSelect);
	void OnInititalComportOpener();
	void OnInititalComportRfid();
	int OnComportNumberTransfer(CString strComport);
	void OnCheckOpenerComPort(/*short nComPort, short nLoadPort*/);
	void OnCheckRfidComPort(/*short nComPort, short nLoadPort*/);

	
	
	
	CMSComm	m_ComOp[20];
	CMSComm	m_ComRp[20];
	CComboBox m_ComboOC;
	CComboBox m_ComboOP;
	CComboBox m_ComboRC;
	CComboBox m_ComboRP;
	afx_msg void OnBnClickedOpenerOpen();
	afx_msg void OnBnClickedOpenerSet();
	
	afx_msg void OnCbnSelchangeComboCom();
	int g_nPort;
	afx_msg void OnCbnSelchangeComboPort();
	
	afx_msg void OnCbnDropdownComboCom2();
	afx_msg void OnBnClickedRfidSet();
	afx_msg void OnBnClickedRfidOpen();
	afx_msg void OnCbnSelchangeComboPort2();
};
