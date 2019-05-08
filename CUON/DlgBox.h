#pragma once


// DlgBox 대화 상자

class DlgBox : public CDialogEx
{
	DECLARE_DYNAMIC(DlgBox)

public:
	DlgBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgBox();

	CString m_Msg;
	BOOL	m_bConfirm;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_EVENTSINK_MAP()

	void ClickConfirmClose();
	void ClickConfirmEnter();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
