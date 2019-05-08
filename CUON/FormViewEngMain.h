#pragma once
#include <afxext.h>

class FormViewEngMain :	public CFormView
{
	DECLARE_DYNCREATE(FormViewEngMain)
public:
	FormViewEngMain();
	~FormViewEngMain();
	HBRUSH  m_hBrush;
public:
	enum { IDD = IDD_FORMVIEW_ENGMAIN };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_EVENTSINK_MAP()


	void ClickEngMainRcp();
	void ClickEngMainMotor();
	void ClickEngMainConfig();
	void ClickEngMainSelect();
	void ClickEngMainManual();
	void ClickEngMainUser();
	void ClickEngMainTape();
	void ClickEngMainClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void ClickEngMainUi();
};

