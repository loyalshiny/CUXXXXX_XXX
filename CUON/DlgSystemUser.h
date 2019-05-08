#pragma once


// DlgSystemUser 대화 상자

class DlgSystemUser : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSystemUser)

public:
	DlgSystemUser(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgSystemUser();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CVsflexgrid m_UserGrid;
	void OnButtonCheck();

};
