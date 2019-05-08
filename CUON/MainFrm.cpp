
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "CUON.h"

#include "MainFrm.h"

#include "CUONView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(UM_MENUCLICK, &CMainFrame::OnFormChange)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_BORDER | WS_DLGFRAME | WS_SYSMENU; //|WS_CAPTION|WS_THICKFRAME|WS_SYSMENU
//	cs.style &= ~WS_MAXIMIZEBOX; 
	cs.style &= ~WS_MAXIMIZEBOX;//| WS_MINIMIZEBOX;
	cs.style &= ~WS_CAPTION;
	cs.style = WS_POPUP; //이 옵션으로 바꾼다.
	cs.x = 0;
	cs.y = 0;
	cs.cx = 1280; //GetSystemMetrics(SM_CXSCREEN);
	cs.cy = 1024;  //GetSystemMetrics(SM_CYSCREEN);
	cs.lpszName = "Cuon System";

	CMenu* pMenu = new CMenu;	//delete menu function
	pMenu->Attach(cs.hMenu);
	pMenu->DestroyMenu();
	cs.hMenu = NULL;
	delete pMenu;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndTitleCuon.Create(this, IDD_TITLE_CUON, CBRS_TOP, IDD_TITLE_CUON);
	m_wndTitleCuon.EnableDocking(CBRS_ALIGN_ANY);
	m_wndTitleCuon.ShowWindow(SW_SHOW);

	return 0;
}

LRESULT CMainFrame::OnFormChange(WPARAM wParam, LPARAM lParam)

{
	RecalcLayout();
	return 0;
}