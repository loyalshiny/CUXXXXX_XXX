
// CUONView.h: CCUONView 클래스의 인터페이스
//

#pragma once

#include "btnenh.h"
#include "DlgMain.h"
#include "DlgGem.h"
#include "DlgLoadPort.h"
#include "DlgLoadPortSetting.h"
#include "DlgSystemSetting.h"
#include "DlgErrorDisplay.h"
#include "DlgLog.h"
class CCUONDoc;
class LClsock;
class LSvSock;

class CCUONView : public CFormView
{

public: // serialization에서만 만들어집니다.
	CCUONView() noexcept;
	DECLARE_DYNCREATE(CCUONView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CUON_FORM };
#endif

// 특성입니다.
public:
	CCUONDoc* GetDocument() const;

	LClsock* m_pClientSock;

	HBRUSH				m_hBrush;
	DlgMain*			m_pDlgMain;
	DlgGem*				m_pDlgGem;
	DlgLoadPort*		m_pDlgLoadPort;
	DlgLoadPortSetting* m_pDlgLoadPortSetting;
	DlgSystemSetting*	m_pDlgSystemSetting;
	DlgErrorDisplay*	m_pDlgErrorDisplay;
	DlgLog*				m_pDlgLog;
	
	
	CBtnEnh m_MainExit;


//	void OnButtonDisplay();
	void OnMotorDataRead();
	void MemoryInitialize();
	void OnButtonCheck();
	int GetAlarmFromTable(_tAlarm* pAlarm);
	int GetOperatorFromTable(_tOperation* pOperation);
	void OperatorList();
// 작업입니다.
public:

	

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CCUONView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_EVENTSINK_MAP()
	void ClickMainExit();
	void OnDialogClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ClickButAuto();
	void ClickButGem();
	void ClickButSystem();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void ClickButLog();
};

#ifndef _DEBUG  // CUONView.cpp의 디버그 버전
inline CCUONDoc* CCUONView::GetDocument() const
   { return reinterpret_cast<CCUONDoc*>(m_pDocument); }
#endif

