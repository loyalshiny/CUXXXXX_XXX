// DlgSystemUser.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgSystemUser.h"
#include "afxdialogex.h"


// DlgSystemUser 대화 상자

IMPLEMENT_DYNAMIC(DlgSystemUser, CDialogEx)

DlgSystemUser::DlgSystemUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYSTEM_USER, pParent)
{

}

DlgSystemUser::~DlgSystemUser()
{
}

void DlgSystemUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_GRID, m_UserGrid);
}


BEGIN_MESSAGE_MAP(DlgSystemUser, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DlgSystemUser 메시지 처리기


BOOL DlgSystemUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(SILVER);
	OnButtonCheck();
	//
	m_UserGrid.put_Cols(1);
	m_UserGrid.put_ColWidth(0, 8500);										//
	m_UserGrid.put_Rows(m_UserTable.UserCnt);
	for (int i = 0; i < m_UserTable.UserCnt; i++)
	{
		m_UserGrid.put_RowHeight(i, 800);
		m_UserGrid.put_TextMatrix(i, 0, m_UserTable.UserID[i]);
	}
	//
	//SetDlgItemText(IDC_EDIT1, SystemINIFiles.m_strSerialNo);
	//SetDlgItemText(IDC_EDIT2, SystemINIFiles.m_strModel);
	//SetDlgItemText(IDC_EDIT3, SystemINIFiles.m_strSoftVer);
	//SetDlgItemText(IDC_EDIT4, SystemINIFiles.m_strCustomerName);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgSystemUser::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgSystemUser::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}
void DlgSystemUser::OnButtonCheck()
{

	if (SystemINIFiles.m_strLanguage == "ENGLISH")
	{
		((CBtnEnh*)GetDlgItem(IDC_USER_SAVE))->SetCaption("SAVE");
		((CBtnEnh*)GetDlgItem(IDC_USER_NEW))->SetCaption("NEW");
		((CBtnEnh*)GetDlgItem(IDC_USER_CREATE))->SetCaption("CREATE");
		((CBtnEnh*)GetDlgItem(IDC_USER_CANCEL))->SetCaption("CANCEL");
		((CBtnEnh*)GetDlgItem(IDC_USER_DELETE))->SetCaption("DELETE");

	}
	else if (SystemINIFiles.m_strLanguage == "KOREAN")
	{
		((CBtnEnh*)GetDlgItem(IDC_USER_SAVE))->SetCaption("저장");
		((CBtnEnh*)GetDlgItem(IDC_USER_NEW))->SetCaption("새 레시피");
		((CBtnEnh*)GetDlgItem(IDC_USER_CREATE))->SetCaption("만들기");
		((CBtnEnh*)GetDlgItem(IDC_USER_CANCEL))->SetCaption("취소");
		((CBtnEnh*)GetDlgItem(IDC_USER_DELETE))->SetCaption("삭제");
	}

}