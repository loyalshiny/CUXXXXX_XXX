#pragma once


// TitleCuon 대화 상자

class TitleCuon : public CDialogBar
{
	DECLARE_DYNAMIC(TitleCuon)

public:
	TitleCuon(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TitleCuon();
	HBRUSH  m_hBrush;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TITLE_CUON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateCmdUI(CCmdUI* pCmdUI);
	afx_msg LRESULT OnInitDialog(WPARAM, LPARAM);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SYstemMonitor(void);
	DECLARE_EVENTSINK_MAP()
	void ClickTopLogin();
};
