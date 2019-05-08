// DlgSelect.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgSelect.h"
#include "afxdialogex.h"
#include "btnenh.h"

// DlgSelect 대화 상자

IMPLEMENT_DYNAMIC(DlgSelect, CDialogEx)

DlgSelect::DlgSelect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECT, pParent)
{

}

DlgSelect::~DlgSelect()
{
}

void DlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT_LIST, m_SelectList);
}


BEGIN_MESSAGE_MAP(DlgSelect, CDialogEx)
	ON_WM_TIMER()
	ON_LBN_SELCHANGE(IDC_SELECT_LIST, &DlgSelect::OnLbnSelchangeSelectList)
	ON_BN_CLICKED(IDOK, &DlgSelect::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgSelect::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgSelect 메시지 처리기


BOOL DlgSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CBtnEnh* m_pbtnenhPanel;
	SetBackgroundColor(SILVER);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_SELECT_MSG);
	m_pbtnenhPanel->SetCaption(strnumMsg);
	LoadList(nRow,strType);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgSelect::PreTranslateMessage(MSG* pMsg)
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


void DlgSelect::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}




void DlgSelect::LoadList(short row,CString m_strType)
{
	// TODO: 여기에 구현 코드 추가.
	//CString m_strType;
	CString m_strTok;
	int i = 0;
	//m_strType = m_RecipeTable.strType[row];

	while (AfxExtractSubString(m_strTok, m_strType, i, ','))
	{
		m_SelectList.InsertString(i, m_strTok);
		i++;
	}
	
}


void DlgSelect::OnLbnSelchangeSelectList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CBtnEnh* m_pbtnenhPanel;

	int Sel = 0;
	CString strText;
	Sel = m_SelectList.GetCurSel();
	m_SelectList.GetText(Sel, strnumMsg);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_SELECT_MSG);
	m_pbtnenhPanel->SetCaption(strnumMsg);
	EndDialog(IDOK);
}

BEGIN_EVENTSINK_MAP(DlgSelect, CDialogEx)
	ON_EVENT(DlgSelect, IDC_SELECT_ENTER, DISPID_CLICK, DlgSelect::ClickSelectEnter, VTS_NONE)
	ON_EVENT(DlgSelect, IDC_SELECT_CLOSE, DISPID_CLICK, DlgSelect::ClickSelectClose, VTS_NONE)
END_EVENTSINK_MAP()


void DlgSelect::ClickSelectEnter()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	EndDialog(IDOK);
}


void DlgSelect::ClickSelectClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


void DlgSelect::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgSelect::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
