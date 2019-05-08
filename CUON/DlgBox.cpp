// DlgBox.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgBox.h"
#include "afxdialogex.h"
#include "btnenh.h"

// DlgBox 대화 상자

IMPLEMENT_DYNAMIC(DlgBox, CDialogEx)

DlgBox::DlgBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOX, pParent)
{
	m_bConfirm = FALSE;
}

DlgBox::~DlgBox()
{
}

void DlgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(DlgBox, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &DlgBox::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgBox::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgBox 메시지 처리기


BOOL DlgBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(WHITE);
	

	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(DlgBox, CDialogEx)
	ON_EVENT(DlgBox, IDC_CONFIRM_CLOSE, DISPID_CLICK, DlgBox::ClickConfirmClose, VTS_NONE)
	ON_EVENT(DlgBox, IDC_CONFIRM_ENTER, DISPID_CLICK, DlgBox::ClickConfirmEnter, VTS_NONE)
END_EVENTSINK_MAP()




void DlgBox::ClickConfirmClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


void DlgBox::ClickConfirmEnter()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	EndDialog(IDOK);
}


void DlgBox::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgBox::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
