#pragma once


// DlgMain 대화 상자

class DlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMain)

public:
	DlgMain(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgMain();
	CToolTipCtrl m_toolTip;
	void OnMotorHomeDisplay();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CFont          cFont;
	CRect rect[40];

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	short Col;
	short Row;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void OnButtonDisplay();
	void OnButtonCheck();
	bool m_bStartEvent;
	bool m_bHomeEvent;
	bool m_bResetEvent;
	bool m_bStopEvent;
};
