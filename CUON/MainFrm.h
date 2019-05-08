
// MainFrm.h: CMainFrame 클래스의 인터페이스
//
#include "TitleCuon.h"
#pragma once
class CCUONView;
class CMainFrame : public CFrameWnd
{
	
protected: // serialization 에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	TitleCuon				m_wndTitleCuon;
	int						m_FormNo;
	WORD					CurrentActiveView;
// 작업입니다.
public:
	CCUONView* m_pMainView;
	CCUONView* GetMainView() { return m_pMainView; }
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnFormChange(WPARAM wParam, LPARAM lParam);
};


