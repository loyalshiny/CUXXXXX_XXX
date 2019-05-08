#pragma once

// DlgLogin 대화 상자

class DlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLogin)

public:
	DlgLogin(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgLogin();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString m_strUserID[20];
	CString m_strUserLevel[20];
	CListBox m_UserList;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	
	DECLARE_EVENTSINK_MAP()
	void ClickLoginEnter();

	CToolTipCtrl m_tooltip;
	short nRows;
	afx_msg void OnLbnSelchangeUserList();
};
