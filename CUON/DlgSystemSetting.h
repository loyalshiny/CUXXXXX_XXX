#pragma once
#include "DlgSystemInterface.h"
#include "DlgSystemMotor.h"
#include "DlgSystemRcp.h"
#include "DlgSystemUser.h"
// DlgSystemSetting 대화 상자

class DlgSystemSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSystemSetting)

public:
	DlgSystemSetting(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgSystemSetting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void InitializeSubDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	short PreSel;
	short Sel;

	DlgSystemInterface* m_pDlgSystemInterface;
	DlgSystemMotor* m_pDlgSystemMotor;
	DlgSystemRcp* m_pDlgSystemRcp;
	DlgSystemUser* m_pDlgSystemUser;

	void OnDialogClear();
	void OnButtonCheck();
	DECLARE_EVENTSINK_MAP()
	void ClickSystemRcp();
	void ClickSystemMotor();
	void ClickSystemInterface();
	void ClickSystemComm();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void ClickSystemUser();
};
