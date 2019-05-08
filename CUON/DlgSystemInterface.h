#pragma once
#include "vsflexgrid.h"
#include "btnenh.h"

// DlgSystemInterface 대화 상자

class DlgSystemInterface : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSystemInterface)

public:
	DlgSystemInterface(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgSystemInterface();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM_INTERFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CVsflexgrid m_InterGrid;
	CVsflexgrid m_InterGrid2;
	CComboBox m_InterfaceList;
	DECLARE_EVENTSINK_MAP()
	void ClickInterfaceSave();
	void InterfaceViewUpdate(CString strSelect);
	CComboBox m_InterfaceCombo;
	afx_msg void OnCbnSelchangeInterfaceCombo();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_InterCombo1;
	void SaveFile();
	short g_nCols;
	void ClickInterfaceGrid();
};
