#pragma once
#include "vsflexgrid.h"
#include "btnenh.h"

// DlgSystemMotor 대화 상자

class DlgSystemMotor : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSystemMotor)

public:
	DlgSystemMotor(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgSystemMotor();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM_MOTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	VARIANT g_row;
	VARIANT g_col;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void MotorViewUpdate(CString strMotorNo);
	void OnMotoreDataSave();
	CVsflexgrid m_MotorGrid;
	CVsflexgrid m_MotorGrid2;
	DECLARE_EVENTSINK_MAP()
	void ClickMotorGrid();
	void ClickMotorGrid2();
	short nMotorNo;
	void ClickMotorSave();
//	int IOReadCW[50];
//	int IOReadCCW[50];
	int IOReadCW[50];
	int IOReadCCW[50];
	void ClickMotorButJogSpeedHi();
	void ClickMotorButJogSpeedMid();
	void ClickMotorButJogSpeedLow();
	void MotorStateCheck(short nMotorNo);
	void MotorNameUpdate();
};
