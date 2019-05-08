#pragma once
#include "vsflexgrid.h"
#include "btnenh.h"

// DlgSystemRcp 대화 상자

class DlgSystemRcp : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSystemRcp)

public:
	DlgSystemRcp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgSystemRcp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM_RCP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	VARIANT g_row;
	VARIANT g_col;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void RecipeViewUpdate(CString strRcp);
	CVsflexgrid m_RcpGrid;
	CVsflexgrid m_RcpGrid2;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnButtonCheck();
	DECLARE_EVENTSINK_MAP()
	void ClickRcpGrid();
	void ClickRcpGrid2();
	void ClickRcpSave();
	void ClickRcpChange();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
