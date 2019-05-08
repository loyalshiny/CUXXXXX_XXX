// DlgLog.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgLog.h"
#include "afxdialogex.h"


// DlgLog 대화 상자

IMPLEMENT_DYNAMIC(DlgLog, CDialogEx)

DlgLog::DlgLog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOG, pParent)
{

}

DlgLog::~DlgLog()
{
}

void DlgLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgLog, CDialogEx)
	ON_WM_TIMER()
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// DlgLog 메시지 처리기


BOOL DlgLog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(SILVER);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgLog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgLog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


//HBRUSH DlgLog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  여기서 DC의 특성을 변경합니다.
//
//	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
//	return hbr;
//}
