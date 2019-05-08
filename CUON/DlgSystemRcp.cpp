// DlgSystemRcp.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgSystemRcp.h"
#include "afxdialogex.h"


// DlgSystemRcp 대화 상자

IMPLEMENT_DYNAMIC(DlgSystemRcp, CDialogEx)

DlgSystemRcp::DlgSystemRcp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYSTEM_RCP, pParent)
{

}

DlgSystemRcp::~DlgSystemRcp()
{
}

void DlgSystemRcp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RCP_GRID, m_RcpGrid);
	DDX_Control(pDX, IDC_RCP_GRID2, m_RcpGrid2);
}


BEGIN_MESSAGE_MAP(DlgSystemRcp, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &DlgSystemRcp::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgSystemRcp::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgSystemRcp 메시지 처리기


BOOL DlgSystemRcp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(SILVER);
	gRecipeLoad();
	RecipeViewUpdate(m_RecipeTable.Name);
	SetTimer(0, 100, NULL);

	g_row = { 1 },
	g_col = { 1 };
	for (int j = 0; j < m_RecipeTable.nRcpCnt; j++)
	{
		if (m_RecipeTable.Name == m_RecipeTable.strRcpName[j])m_RcpGrid2.Select(j, 0, g_row, g_col);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgSystemRcp::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	((CBtnEnh*)GetDlgItem(IDC_RCP_NAME))->SetCaption(m_RecipeTable.Name);
	CDialogEx::OnTimer(nIDEvent);
}


BOOL DlgSystemRcp::PreTranslateMessage(MSG* pMsg)
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



void DlgSystemRcp::RecipeViewUpdate(CString strRcp)
{
	// TODO: 여기에 구현 코드 추가.
	
	

	m_RcpGrid.put_Cols(2);
	m_RcpGrid.put_ColWidth(0, 4000);										//
	m_RcpGrid.put_ColWidth(1, 2500);										//
	m_RcpGrid.put_Rows(m_RecipeTable.nRcpParaCnt);

	for (int i = 0; i < m_RecipeTable.nRcpParaCnt; i++)
	{
		m_RcpGrid.put_RowHeight(i, 800);
		m_RcpGrid.put_TextMatrix(i, 0, m_RecipeTable.strParaName[i]);						//레시피 파라메터 명칭 PUT matrix
		m_RcpGrid.put_TextMatrix(i, 1, m_RecipeTable.Data[i]);
	}

	m_RcpGrid2.put_Cols(1);
	m_RcpGrid2.put_ColWidth(0, 9000);
	m_RcpGrid2.put_RowHeight(0, 800);
	m_RcpGrid2.put_Rows(m_RecipeTable.nRcpCnt);

	for (int j = 0; j < m_RecipeTable.nRcpCnt; j++)
	{
		m_RcpGrid2.put_RowHeight(j, 800);
		m_RcpGrid2.put_TextMatrix(j, 0, m_RecipeTable.strRcpName[j]);						//레시피 파라메터 명칭 PUT matrix
	}
}


BEGIN_EVENTSINK_MAP(DlgSystemRcp, CDialogEx)
	ON_EVENT(DlgSystemRcp, IDC_RCP_GRID, DISPID_CLICK, DlgSystemRcp::ClickRcpGrid, VTS_NONE)
	ON_EVENT(DlgSystemRcp, IDC_RCP_GRID2, DISPID_CLICK, DlgSystemRcp::ClickRcpGrid2, VTS_NONE)
	ON_EVENT(DlgSystemRcp, IDC_RCP_SAVE, DISPID_CLICK, DlgSystemRcp::ClickRcpSave, VTS_NONE)
	ON_EVENT(DlgSystemRcp, IDC_RCP_CHANGE, DISPID_CLICK, DlgSystemRcp::ClickRcpChange, VTS_NONE)
END_EVENTSINK_MAP()


void DlgSystemRcp::ClickRcpGrid()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue, strMsg;

	CString strMotorvalue = "0.00";
	int nRow = m_RcpGrid.get_RowSel();
	int nCol = m_RcpGrid.get_ColSel();

	//if ((Main.m_UserLevel != "ENGINEER") && (Main.m_UserLevel != "SUPPLIER")) return;
	//	if(m_SetDeviceNo != nCol) return;

	strValue = m_RcpGrid.get_TextMatrix(nRow, nCol);
	if (m_RecipeTable.strType[nRow] != "VALUE")	//파라 type 이 LIST 인 경우
	{
		DlgSelect dlg;
		dlg.strnumMsg = strValue;
		dlg.nRow = nRow;
		dlg.strType = m_RecipeTable.strType[nRow];
		if (dlg.DoModal() == IDOK) {
			if (dlg.strnumMsg == "") return;

			strValue = dlg.strnumMsg;
			m_RcpGrid.put_TextMatrix(nRow, nCol, strValue);
		}
	}
	else
	{
		DlgNumberPad dlg;
		dlg.strnumMsg = strValue;

		dlg.strMin = m_RecipeTable.strMin[nRow];
		dlg.strMax = m_RecipeTable.strMax[nRow];
		if (dlg.DoModal() == IDOK) {
			if (dlg.strnumMsg == "") return;
			strValue = dlg.strnumMsg;
			m_RecipeTable.strMin[nRow] = dlg.strMin;
			m_RecipeTable.strMax[nRow] = dlg.strMax;
			if (m_RecipeTable.strMin[nRow] != "" && atof(strValue) < atof(m_RecipeTable.strMin[nRow])) { strMsg.Format("%s \nMinimum value error , [Min value = %s]", m_RecipeTable.strParaName[nRow], m_RecipeTable.strMin[nRow]); AfxMessageBox(strMsg); return; }
			else if (m_RecipeTable.strMax[nRow] != "" && atof(strValue) > atof(m_RecipeTable.strMax[nRow])) { strMsg.Format("%s \nMaximum value error , [Max value = %s]", m_RecipeTable.strParaName[nRow], m_RecipeTable.strMax[nRow]); AfxMessageBox(strMsg); return; }

			m_RcpGrid.put_TextMatrix(nRow, nCol, strValue);
		}
	}
}


void DlgSystemRcp::ClickRcpGrid2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue;
	int nRow = m_RcpGrid2.get_RowSel();
	int nCol = m_RcpGrid2.get_ColSel();
	strValue = m_RcpGrid2.get_TextMatrix(nRow, nCol);


	gRecipeFileLoad(strValue);
	RecipeViewUpdate(strValue);
}


void DlgSystemRcp::ClickRcpSave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue, strTemp;
	int nRow = m_RcpGrid2.get_RowSel();
	int nCol = m_RcpGrid2.get_ColSel();
	strValue = m_RcpGrid2.get_TextMatrix(nRow, nCol);

	DlgBox dlg;
	if(SystemINIFiles.m_strLanguage == "ENGLISH")dlg.m_Msg = "Do You Save Recipe..?";
	else if(SystemINIFiles.m_strLanguage == "KOREAN")dlg.m_Msg = "레시피를 저장 하시겠습니까..?";

	dlg.m_bConfirm = 1;

	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	for (int j = 0; j < m_RecipeTable.nRcpParaCnt; j++)
	{
		strTemp = m_RcpGrid.get_TextMatrix(j, 1);
		//NUMBER = 0, STRING = 1
		if (GetNumberCheck(strTemp) == FALSE && m_RecipeTable.strType[j] != "VALUE") { AfxMessageBox("Value Unacceptable"); m_RcpGrid.ShowCell(j, 1); m_RcpGrid.Select(j , 1, g_row, g_col); return; }
		else if (GetNumberCheck(strTemp) == TRUE && m_RecipeTable.strType[j] == "VALUE") { AfxMessageBox("Value Unacceptable"); m_RcpGrid.ShowCell(j, 1); m_RcpGrid.Select(j , 1, g_row, g_col); return; }

		m_RecipeTable.Data[j] = strTemp;
		gWriteRecipeFile(m_RecipeTable.strParaName[j], "DATA", strTemp, strValue);
		gWriteRecipeFile(m_RecipeTable.strParaName[j], "MIN", m_RecipeTable.strMin[j], strValue);
		gWriteRecipeFile(m_RecipeTable.strParaName[j], "MAX", m_RecipeTable.strMax[j], strValue);
	}
	gRecipeFileChange(strValue);
	MessageBox(_T("Data Save successfully"));
}


void DlgSystemRcp::ClickRcpChange()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue;
	int nRow = m_RcpGrid2.get_RowSel();
	int nCol = m_RcpGrid2.get_ColSel();
	strValue = m_RcpGrid2.get_TextMatrix(nRow, nCol);

	DlgBox dlg;
	if(SystemINIFiles.m_strLanguage == "ENGLISH")dlg.m_Msg = "Do You Change Recipe..?";
	else if(SystemINIFiles.m_strLanguage == "KOREAN")dlg.m_Msg = "레시피를 변경 하시겠습니까..?";

	dlg.m_bConfirm = 1;
	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}
	gRecipeFileChange(strValue);
	MessageBox(_T("Data CHange successfully"));
}


void DlgSystemRcp::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgSystemRcp::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
void DlgSystemRcp::OnButtonCheck()
{

	if (SystemINIFiles.m_strLanguage == "ENGLISH")
	{
		((CBtnEnh*)GetDlgItem(IDC_RCP_SAVE))->SetCaption("SAVE");
		((CBtnEnh*)GetDlgItem(IDC_RCP_CHANGE))->SetCaption("CHANGE");
		((CBtnEnh*)GetDlgItem(IDC_RCP_NEW))->SetCaption("NEW USER");
		((CBtnEnh*)GetDlgItem(IDC_RCP_CREATE))->SetCaption("CREATE");
		((CBtnEnh*)GetDlgItem(IDC_RCP_CANCEL))->SetCaption("CANCEL");
		((CBtnEnh*)GetDlgItem(IDC_RCP_DELETE))->SetCaption("DELETE");

	}
	else if (SystemINIFiles.m_strLanguage == "KOREAN")
	{
		((CBtnEnh*)GetDlgItem(IDC_RCP_SAVE))->SetCaption("저장");
		((CBtnEnh*)GetDlgItem(IDC_RCP_CHANGE))->SetCaption("변경");
		((CBtnEnh*)GetDlgItem(IDC_RCP_NEW))->SetCaption("새 레시피");
		((CBtnEnh*)GetDlgItem(IDC_RCP_CREATE))->SetCaption("만들기");
		((CBtnEnh*)GetDlgItem(IDC_RCP_CANCEL))->SetCaption("취소");
		((CBtnEnh*)GetDlgItem(IDC_RCP_DELETE))->SetCaption("삭제");
	}

	if ((Main.m_UserLevel != "ENGINEER") && (Main.m_UserLevel != "SUPPLIER"))
	{
		GetDlgItem(IDC_RCP_NEW)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_CHANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_RCP_CREATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_CANCEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_EDIT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_RCP_NEW)->EnableWindow(TRUE);
		GetDlgItem(IDC_RCP_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_RCP_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_RCP_CHANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_RCP_CREATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_CANCEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_RCP_EDIT)->EnableWindow(FALSE);
	}

}