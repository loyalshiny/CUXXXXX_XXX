#pragma once


// DlgNumberPad 대화 상자

class DlgNumberPad : public CDialogEx
{
	DECLARE_DYNAMIC(DlgNumberPad)

public:
	DlgNumberPad(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgNumberPad();

	CString strnumMsg;
	CString strMorterPosition;
	CString strMin;
	CString strMax;
	BOOL    m_butClick;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NUMBER_PAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickTenkey1();
	void ClickTenkey2();
	void ClickTenkey3();
	void ClickTenkey4();
	void ClickTenkey5();
	void ClickTenkey6();
	void ClickTenkey7();
	void ClickTenkey8();
	void ClickTenkey9();
	void ClickTenkey0();
	void ClickTenkeyDot();
	void ClickTenkeyClose();
	void ClickTenkeyCopy();
	void ClickTenkeyClear();
	void ClickTenkeyDash();
	void ClickTenkeyEnter();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
