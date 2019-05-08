// DlgSystemMotor.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgSystemMotor.h"
#include "afxdialogex.h"


// DlgSystemMotor 대화 상자

IMPLEMENT_DYNAMIC(DlgSystemMotor, CDialogEx)

DlgSystemMotor::DlgSystemMotor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYSTEM_MOTOR, pParent)
{

	IOReadCW[50] = 0;
	IOReadCCW[50] = 0;
}

DlgSystemMotor::~DlgSystemMotor()
{
}

void DlgSystemMotor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOTOR_GRID, m_MotorGrid);
	DDX_Control(pDX, IDC_MOTOR_GRID2, m_MotorGrid2);
}


BEGIN_MESSAGE_MAP(DlgSystemMotor, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &DlgSystemMotor::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgSystemMotor::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgSystemMotor 메시지 처리기


BOOL DlgSystemMotor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(SILVER);
	((CBtnEnh*)GetDlgItem(IDC_MOTOR_INCH))->SetCaption(m_RecipeTable.Data[0]);
	nMotorNo = 0;
	Main.nCurrentMotorNo = nMotorNo;

	int j, k = 0;
	j = 78;
	k = 79;
	for (int i = 0; i < 40; i++)
	{
		IOReadCW[i] = j;
		j += 16;

		IOReadCCW[i] = k;
		k += 16;
	}

	MotorViewUpdate("M1");
	SetTimer(0, 100, NULL);SetTimer(1, 1000, NULL);

	g_row	= { 1 },
	g_col	= { 1 };
	m_MotorGrid2.Select(0, 1, g_row, g_col);
	if (SystemINIFiles.m_strLanguage == "ENGLISH")((CBtnEnh*)GetDlgItem(IDC_MOTOR_SAVE))->SetCaption("SAVE");
	else if (SystemINIFiles.m_strLanguage == "KOREAN")((CBtnEnh*)GetDlgItem(IDC_MOTOR_SAVE))->SetCaption("저장");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgSystemMotor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	MotorStateCheck(nMotorNo);
	
	if(nIDEvent == 1)MotorNameUpdate();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL DlgSystemMotor::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString Add = 0;
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	
	if (pMsg->message == WM_LBUTTONDOWN)
		{

			if (pMsg->hwnd == GetDlgItem(IDC_MOTOR_BUT_CCW)->m_hWnd)
			{
				Add = m_MotorTable[nMotorNo].strBit + "15";
				SetCIOBit(atoi(Add));

				m_aBitCIO[IOReadCCW[nMotorNo ]].m_buttype = BUT_INVERT;
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_MOTOR_BUT_CW)->m_hWnd)
			{
				Add = m_MotorTable[nMotorNo].strBit + "14";
				SetCIOBit(atoi(Add));
				m_aBitCIO[IOReadCW[nMotorNo ]].m_buttype = BUT_INVERT;
			}

		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			m_aBitCIO[IOReadCCW[nMotorNo ]].m_buttype = BUT_MOMENTARY;				   /// mtrpara[1] == Elevator Jog
			m_aBitCIO[IOReadCW[nMotorNo ]].m_buttype = BUT_MOMENTARY;				   ///
		}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgSystemMotor::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgSystemMotor::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void DlgSystemMotor::MotorViewUpdate(CString strMotorNo)
{
	CString strTemp, strWaferSize;
	
	short nCnt = 0;
	strTemp = strMotorNo;
	strTemp.Replace("M", "");
	nMotorNo = atoi(strTemp)-1;
	Main.nCurrentMotorNo = nMotorNo;
	
	m_MotorGrid.put_Cols(1+ Main.nWaferSizeCnt);
	m_MotorGrid.put_ColWidth(0, 4000);										//
	m_MotorGrid.put_RowHeight(0, 800);
	m_MotorGrid.put_Rows(m_MotorTable[nMotorNo].nMotorParaCnt+1);
	
	for (int j = 0; j < Main.nWaferSizeCnt; j++)
	{
		m_MotorGrid.put_TextMatrix(0, j + 1, Main.strWaferSize[j]);
		for (int i = 0; i < m_MotorTable[nMotorNo].nMotorParaCnt ; i++)
		{
			m_MotorTable[nMotorNo].Data[i] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[i], Main.strWaferSize[j], strMotorNo);
			m_MotorGrid.put_RowHeight(i+1, 800);
			m_MotorGrid.put_ColWidth(j+1, 2000);
			m_MotorGrid.put_TextMatrix(i+1, 0, m_MotorTable[nMotorNo].strParaName[i]);						
			m_MotorGrid.put_TextMatrix(i+1, j+1, m_MotorTable[nMotorNo].Data[i]);
		}
	}
	MotorNameUpdate();	
}
void DlgSystemMotor::MotorNameUpdate()
{
	short nCnt = 0;
	CString strMotorNo;
	m_MotorGrid2.put_Cols(3);
	m_MotorGrid2.put_ColWidth(0, 700);
	m_MotorGrid2.put_ColWidth(1, 5300);
	m_MotorGrid2.put_ColWidth(2, 1500);
	m_MotorGrid2.put_RowHeight(0, 800);
	m_MotorGrid2.put_Rows(Main.nMotorCnt);

	for (int j = 0; j < 40; j++)
	{
		if (m_MotorTable[j].strMotorName != "")
		{
			strMotorNo.Format("M%d", j+1);
			m_MotorGrid2.put_RowHeight(nCnt, 800);
			m_MotorGrid2.put_TextMatrix(nCnt, 0, strMotorNo);						//레시피 파라메터 명칭 PUT matrix
			m_MotorGrid2.put_TextMatrix(nCnt, 1, m_MotorTable[j].strMotorName);						//레시피 파라메터 명칭 PUT matrix
			if (mtrpara[j].hsen_level)m_MotorGrid2.put_TextMatrix(nCnt, 2, "READY");
			else if (!mtrpara[j].hsen_level)m_MotorGrid2.put_TextMatrix(nCnt, 2, "NOT RDY");
			nCnt++;
		}
	}
}
void DlgSystemMotor::OnMotoreDataSave()
{

	CString strValue, strResult, strTemp, strWaferSize;
	int nRow = m_MotorGrid2.get_RowSel();
	int nCol = m_MotorGrid2.get_ColSel();
	strValue = m_MotorGrid2.get_TextMatrix(nRow, 0);
	strResult = strValue;
	BOOL CHECK = 0;
	
	DlgBox dlg;
	if(SystemINIFiles.m_strLanguage == "ENGLISH")dlg.m_Msg = "Do You Want Save Recipe ?";
	else if(SystemINIFiles.m_strLanguage == "KOREAN")dlg.m_Msg = "레시피를 저장 하시겠습니까 ?";


	dlg.m_bConfirm = 1;
	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}
	for (int i = 0; i < Main.nWaferSizeCnt; i++)
	{
		strWaferSize = m_MotorGrid.get_TextMatrix(0, i+1);
		if (strWaferSize == m_RecipeTable.Data[0])
		{
			for (int j = 0; j < m_MotorTable[nMotorNo].nMotorParaCnt; j++)
			{
				strTemp = m_MotorGrid.get_TextMatrix(j+1, i+1);
				CHECK = GetNumberCheck(strTemp);
				if (GetNumberCheck(strTemp) == TRUE && strTemp !="")/*m_MotorTable[nMotorNo].strType[j] == "VALUE")*/ { AfxMessageBox("Value Unacceptable"); m_MotorGrid.ShowCell(j + 1, i + 1); m_MotorGrid.Select(j+1 , i + 1, g_row, g_col); return; }

				m_MotorTable[nMotorNo].Data[j] = strTemp;
				gWriteMotorFile(m_MotorTable[nMotorNo].strParaName[j], m_RecipeTable.Data[0], strTemp, strResult);
				gWriteMotorFile(m_MotorTable[nMotorNo].strParaName[j], "MIN", m_MotorTable[nMotorNo].strMin[j], strResult);
				gWriteMotorFile(m_MotorTable[nMotorNo].strParaName[j], "MAX", m_MotorTable[nMotorNo].strMax[j], strResult);
				
			}
		}	
	}
	gMotorFileSave(strResult);
	MessageBox(_T("Data Save successfully"));
}


BEGIN_EVENTSINK_MAP(DlgSystemMotor, CDialogEx)
ON_EVENT(DlgSystemMotor, IDC_MOTOR_GRID, DISPID_CLICK, DlgSystemMotor::ClickMotorGrid, VTS_NONE)
ON_EVENT(DlgSystemMotor, IDC_MOTOR_GRID2, DISPID_CLICK, DlgSystemMotor::ClickMotorGrid2, VTS_NONE)
ON_EVENT(DlgSystemMotor, IDC_MOTOR_SAVE, DISPID_CLICK, DlgSystemMotor::ClickMotorSave, VTS_NONE)
ON_EVENT(DlgSystemMotor, IDC_MOTOR_BUT_JOG_SPEED_HI, DISPID_CLICK, DlgSystemMotor::ClickMotorButJogSpeedHi, VTS_NONE)
ON_EVENT(DlgSystemMotor, IDC_MOTOR_BUT_JOG_SPEED_MID, DISPID_CLICK, DlgSystemMotor::ClickMotorButJogSpeedMid, VTS_NONE)
ON_EVENT(DlgSystemMotor, IDC_MOTOR_BUT_JOG_SPEED_LOW, DISPID_CLICK, DlgSystemMotor::ClickMotorButJogSpeedLow, VTS_NONE)
END_EVENTSINK_MAP()


void DlgSystemMotor::ClickMotorGrid()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue, strMsg,strWaferSize, strMotorvalue;
	int nRow, nRows;
	strMotorvalue = "0.00";
	nRows = m_MotorGrid.get_RowSel();
	nRow = nRows - 1;

	int nCol = m_MotorGrid.get_ColSel();
	

	//if ((Main.m_UserLevel != "ENGINEER") && (Main.m_UserLevel != "SUPPLIER")) return;
	//	if(m_SetDeviceNo != nCol) return;

	strValue = m_MotorGrid.get_TextMatrix(nRows, nCol);
	if (m_MotorTable[nMotorNo].strType[nRow] != "VALUE" && nCol == 0)	//파라 type 이 LIST 인 경우
	{
		DlgBox dlg;
		if(SystemINIFiles.m_strLanguage == "ENGLISH")dlg.m_Msg = "Do You Wnat"+ m_MotorTable[nMotorNo].strParaName[nRow-1] + "Position Move..?";
		else if(SystemINIFiles.m_strLanguage == "KOREAN")dlg.m_Msg = m_MotorTable[nMotorNo].strParaName[nRow-1] + "포지션으로 이동 하시겠습니까..?";

		dlg.m_bConfirm = 1;
		if (dlg.DoModal() == IDOK)
		{
			SetCIOBit(atoi(m_MotorTable[nMotorNo].strCioBit[nRow ]));
		}
	}
	else
	{
		strWaferSize = m_MotorGrid.get_TextMatrix(0, nCol);
		if (strWaferSize != m_RecipeTable.Data[0])return;

		DlgNumberPad dlg;
		strMotorvalue.Format("%8.2f", mtrpara[nMotorNo].current_pos);

		dlg.strnumMsg = strValue;
		dlg.strMorterPosition = strMotorvalue;
		dlg.strMin = m_MotorTable[nMotorNo].strMin[nRow];
		dlg.strMax = m_MotorTable[nMotorNo].strMax[nRow];
		if (dlg.DoModal() == IDOK) {
			if (dlg.strnumMsg == "") return;
			strValue = dlg.strnumMsg;
			m_MotorTable[nMotorNo].strMin[nRow ] = dlg.strMin;
			m_MotorTable[nMotorNo].strMax[nRow ] = dlg.strMax;
			if (m_MotorTable[nMotorNo].strMin[nRow ] != "" && atof(strValue) < atof(m_MotorTable[nMotorNo].strMin[nRow])) { strMsg.Format("%s \nMinimum value error , [Min value = %s]", m_MotorTable[nMotorNo].strParaName[nRow ], m_MotorTable[nMotorNo].strMin[nRow ]); AfxMessageBox(strMsg); return; }
			else if (m_MotorTable[nMotorNo].strMax[nRow ] != "" && atof(strValue) > atof(m_MotorTable[nMotorNo].strMax[nRow])) { strMsg.Format("%s \nMaximum value error , [Max value = %s]", m_MotorTable[nMotorNo].strParaName[nRow ], m_MotorTable[nMotorNo].strMax[nRow ]); AfxMessageBox(strMsg); return; }
			m_MotorGrid.put_TextMatrix(nRows, nCol, strValue);
		}
	}
}


void DlgSystemMotor::ClickMotorGrid2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue,strResult, strTemp;
	int nRow = m_MotorGrid2.get_RowSel();
	int nCol = m_MotorGrid2.get_ColSel();
	if (nCol != 1)return;
	strValue = m_MotorGrid2.get_TextMatrix(nRow, 0);
	//strValue.Replace("M", "");

	gMotorFileLoad(strValue);
	MotorViewUpdate(strValue);
}


void DlgSystemMotor::ClickMotorSave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnMotoreDataSave();
}


void DlgSystemMotor::ClickMotorButJogSpeedHi()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	mtrpara[nMotorNo ].JogSpedMode = 2;
	mtrpara[nMotorNo ].JogSpedActiv = 1;
}


void DlgSystemMotor::ClickMotorButJogSpeedMid()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	mtrpara[nMotorNo ].JogSpedMode = 1;
	mtrpara[nMotorNo ].JogSpedActiv = 1;
}


void DlgSystemMotor::ClickMotorButJogSpeedLow()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	mtrpara[nMotorNo ].JogSpedMode = 0;
	mtrpara[nMotorNo ].JogSpedActiv = 1;
}
void DlgSystemMotor::MotorStateCheck(short nMotorNo)
{
	CBtnEnh* m_pbtnenhPanel;
	CString strTemp;
	INT nValue;

	nValue = (int)wEmemoryMotorSpeedRead[ADDR_SPEED_50 + nMotorNo ];
	if (nValue == 2)
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_HI);
		m_pbtnenhPanel->SetBackColor(DKGREEN);
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_MID);
		m_pbtnenhPanel->SetBackColor(DKGRAY);
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_LOW);
		m_pbtnenhPanel->SetBackColor(DKGRAY);

	}
	else if (nValue == 1)
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_HI);
		m_pbtnenhPanel->SetBackColor(DKGRAY);
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_MID);
		m_pbtnenhPanel->SetBackColor(DKGREEN);
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_LOW);
		m_pbtnenhPanel->SetBackColor(DKGRAY);

	}
	else
	{
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_HI);
		m_pbtnenhPanel->SetBackColor(DKGRAY);
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_MID);
		m_pbtnenhPanel->SetBackColor(DKGRAY);
		m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_JOG_SPEED_LOW);
		m_pbtnenhPanel->SetBackColor(DKGREEN);
	}

	strTemp.Format("%8.2f", mtrpara[nMotorNo ].current_pos);
	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_CUR_POS);
	m_pbtnenhPanel->SetCaption(strTemp);



	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_LIMIT_CCW);
	if (mtrpara[nMotorNo ].nlmt_level) m_pbtnenhPanel->SetBackColor(GREEN);
	else m_pbtnenhPanel->SetBackColor(DKGRAY);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_LIMIT_CW);
	if (mtrpara[nMotorNo ].plmt_level) m_pbtnenhPanel->SetBackColor(GREEN);
	else m_pbtnenhPanel->SetBackColor(DKGRAY);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_HOME);
	if (mtrpara[nMotorNo ].hsen_level) m_pbtnenhPanel->SetBackColor(GREEN);
	else m_pbtnenhPanel->SetBackColor(DKGRAY);


	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_CCW);
	m_pbtnenhPanel->SetCaption("JOG- "+m_MotorTable[nMotorNo].strJog+"_CLR");
	if (PollingBit(wTouchInput[nMotorNo + 4], 15))m_pbtnenhPanel->SetBackColor(DKGREEN);
	else	m_pbtnenhPanel->SetBackColor(DKGRAY);

	m_pbtnenhPanel = (CBtnEnh*)GetDlgItem(IDC_MOTOR_BUT_CW);
	m_pbtnenhPanel->SetCaption("JOG+ "+m_MotorTable[nMotorNo].strJog + "_SET");
	if (PollingBit(wTouchInput[nMotorNo + 4], 14))m_pbtnenhPanel->SetBackColor(DKGREEN);
	else	m_pbtnenhPanel->SetBackColor(DKGRAY);

}
