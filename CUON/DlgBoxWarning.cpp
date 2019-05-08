// DlgBoxWarning.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgBoxWarning.h"
#include "afxdialogex.h"


// DlgBoxWarning 대화 상자

IMPLEMENT_DYNAMIC(DlgBoxWarning, CDialogEx)

DlgBoxWarning::DlgBoxWarning(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOX_WARNING, pParent)
{

}

DlgBoxWarning::~DlgBoxWarning()
{
}

void DlgBoxWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgBoxWarning, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &DlgBoxWarning::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &DlgBoxWarning::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgBoxWarning 메시지 처리기


BOOL DlgBoxWarning::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(WHITE);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgBoxWarning::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgBoxWarning::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


void DlgBoxWarning::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void DlgBoxWarning::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
BEGIN_EVENTSINK_MAP(DlgBoxWarning, CDialogEx)
	ON_EVENT(DlgBoxWarning, IDC_WARNING_CLOSE, DISPID_CLICK, DlgBoxWarning::ClickWarningClose, VTS_NONE)
	ON_EVENT(DlgBoxWarning, IDC_WARNING_OK, DISPID_CLICK, DlgBoxWarning::ClickWarningOk, VTS_NONE)
END_EVENTSINK_MAP()


void DlgBoxWarning::ClickWarningClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	EndDialog(IDOK);
}


void DlgBoxWarning::ClickWarningOk()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	EndDialog(IDOK);
}
