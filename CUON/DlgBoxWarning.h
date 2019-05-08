#pragma once


// DlgBoxWarning 대화 상자

class DlgBoxWarning : public CDialogEx
{
	DECLARE_DYNAMIC(DlgBoxWarning)

public:
	DlgBoxWarning(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgBoxWarning();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOX_WARNING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	DECLARE_EVENTSINK_MAP()
	void ClickWarningClose();
	void ClickWarningOk();
};
