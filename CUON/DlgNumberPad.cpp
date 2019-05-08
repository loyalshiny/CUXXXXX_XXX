// DlgNumberPad.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgNumberPad.h"
#include "afxdialogex.h"
#include "btnenh.h"

// DlgNumberPad 대화 상자

IMPLEMENT_DYNAMIC(DlgNumberPad, CDialogEx)

DlgNumberPad::DlgNumberPad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NUMBER_PAD, pParent)
{
	m_butClick = FALSE;
}

DlgNumberPad::~DlgNumberPad()
{
}

void DlgNumberPad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgNumberPad, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgNumberPad::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgNumberPad::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgNumberPad 메시지 처리기


void DlgNumberPad::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


BOOL DlgNumberPad::OnInitDialog()
{
	CDialog::OnInitDialog();
	CBtnEnh* m_pbtnenhPanel;
	SetBackgroundColor(SILVER);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_NUMBER_MSG);
	m_pbtnenhPanel->SetCaption(strnumMsg);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_NUMBER_CUR);
	if (strMorterPosition == "")strMorterPosition = "00.00";
	m_pbtnenhPanel->SetCaption(strMorterPosition);

	SetDlgItemText(IDC_EDIT_MIN, strMin);
	SetDlgItemText(IDC_EDIT_MAX, strMax);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
// DlgNumberPad 메시지 처리기입니다.
BEGIN_EVENTSINK_MAP(DlgNumberPad, CDialog)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_1, DISPID_CLICK, DlgNumberPad::ClickTenkey1, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_2, DISPID_CLICK, DlgNumberPad::ClickTenkey2, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_3, DISPID_CLICK, DlgNumberPad::ClickTenkey3, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_4, DISPID_CLICK, DlgNumberPad::ClickTenkey4, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_5, DISPID_CLICK, DlgNumberPad::ClickTenkey5, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_6, DISPID_CLICK, DlgNumberPad::ClickTenkey6, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_7, DISPID_CLICK, DlgNumberPad::ClickTenkey7, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_8, DISPID_CLICK, DlgNumberPad::ClickTenkey8, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_9, DISPID_CLICK, DlgNumberPad::ClickTenkey9, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_0, DISPID_CLICK, DlgNumberPad::ClickTenkey0, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_DOT, DISPID_CLICK, DlgNumberPad::ClickTenkeyDot, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_CLOSE, DISPID_CLICK, DlgNumberPad::ClickTenkeyClose, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_COPY, DISPID_CLICK, DlgNumberPad::ClickTenkeyCopy, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_CLEAR, DISPID_CLICK, DlgNumberPad::ClickTenkeyClear, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_DASH, DISPID_CLICK, DlgNumberPad::ClickTenkeyDash, VTS_NONE)
	ON_EVENT(DlgNumberPad, IDC_TENKEY_ENTER, DISPID_CLICK, DlgNumberPad::ClickTenkeyEnter, VTS_NONE)
END_EVENTSINK_MAP()


void DlgNumberPad::ClickTenkey1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('1');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('2');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey3()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('3');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey4()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('4');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey5()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('5');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey6()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('6');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey7()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('7');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey8()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('8');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey9()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('9');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkey0()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('0');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkeyDot()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_butClick) { ClickTenkeyClear(); m_butClick = TRUE; }
	strnumMsg.operator +=('.');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkeyClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


void DlgNumberPad::ClickTenkeyCopy()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	strnumMsg = strMorterPosition;
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkeyClear()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	strnumMsg.Format("");
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkeyDash()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	strnumMsg.operator +=('.');
	SetDlgItemText(IDC_NUMBER_MSG, strnumMsg);
}


void DlgNumberPad::ClickTenkeyEnter()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT_MIN, strMin);
	GetDlgItemText(IDC_EDIT_MAX, strMax);

	if (GetNumberCheck(strMin) || GetNumberCheck(strMin))MessageBox("Check Min Max Value.");
	if (!GetNumberCheck(strnumMsg) && (strnumMsg.GetLength() > 0))EndDialog(IDOK);
	else MessageBox("Check The Value.");
}


void DlgNumberPad::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgNumberPad::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL DlgNumberPad::PreTranslateMessage(MSG* pMsg)
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
