// DlgSystemInterface.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgSystemInterface.h"
#include "afxdialogex.h"


// DlgSystemInterface 대화 상자

IMPLEMENT_DYNAMIC(DlgSystemInterface, CDialogEx)

DlgSystemInterface::DlgSystemInterface(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYSTEM_INTERFACE, pParent)
{
	g_nCols = 0;
}

DlgSystemInterface::~DlgSystemInterface()
{
}

void DlgSystemInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INTERFACE_GRID, m_InterGrid);


	DDX_Control(pDX, IDC_INTERFACE_COMBO, m_InterfaceCombo);
	DDX_Control(pDX, IDC_COMBO1, m_InterCombo1);
}


BEGIN_MESSAGE_MAP(DlgSystemInterface, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &DlgSystemInterface::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &DlgSystemInterface::OnBnClickedOk)

	ON_CBN_SELCHANGE(IDC_INTERFACE_COMBO, &DlgSystemInterface::OnCbnSelchangeInterfaceCombo)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgSystemInterface::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// DlgSystemInterface 메시지 처리기


BOOL DlgSystemInterface::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(SILVER);
	InterfaceViewUpdate("MAIN");
	if (SystemINIFiles.m_strLanguage == "ENGLISH") { ((CBtnEnh*)  GetDlgItem(IDC_INTERFACE_SAVE))->SetCaption("SAVE"); m_InterfaceCombo.SetCurSel(1);	}
	else if (SystemINIFiles.m_strLanguage == "KOREAN") { ((CBtnEnh*)  GetDlgItem(IDC_INTERFACE_SAVE))->SetCaption("저장"); m_InterfaceCombo.SetCurSel(0);	}

	m_InterCombo1.SetCurSel(0);
	

	SetDlgItemText(IDC_EDIT1, SystemINIFiles.m_strSerialNo);
	SetDlgItemText(IDC_EDIT2, SystemINIFiles.m_strModel);
	SetDlgItemText(IDC_EDIT3, SystemINIFiles.m_strSoftVer);
	SetDlgItemText(IDC_EDIT4, SystemINIFiles.m_strCustomerName);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgSystemInterface::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


BOOL DlgSystemInterface::PreTranslateMessage(MSG* pMsg)
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


void DlgSystemInterface::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void DlgSystemInterface::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


BEGIN_EVENTSINK_MAP(DlgSystemInterface, CDialogEx)
	ON_EVENT(DlgSystemInterface, IDC_INTERFACE_SAVE, DISPID_CLICK, DlgSystemInterface::ClickInterfaceSave, VTS_NONE)
	ON_EVENT(DlgSystemInterface, IDC_INTERFACE_GRID, DISPID_CLICK, DlgSystemInterface::ClickInterfaceGrid, VTS_NONE)
END_EVENTSINK_MAP()


void DlgSystemInterface::ClickInterfaceSave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	DlgBox dlg;
	if (SystemINIFiles.m_strLanguage == "ENGLISH")dlg.m_Msg = "Do You Save Data..?";
	else if (SystemINIFiles.m_strLanguage == "KOREAN")dlg.m_Msg = "데이터를 저장 하시겠습니까..?";
	dlg.m_bConfirm = 1;
	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	int nSel = 0;
	CString strTemp;
	nSel = m_InterfaceCombo.GetCurSel();
	m_InterfaceCombo.GetLBText(nSel, strTemp);
	RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "LANGUAGE", strTemp);

	GetDlgItemText(IDC_EDIT1, strTemp);
	RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "EQSN", strTemp);

	GetDlgItemText(IDC_EDIT2, strTemp);
	RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "EQMODEL", strTemp);

	GetDlgItemText(IDC_EDIT4, strTemp);
	RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CUSTOMER", strTemp);

	SaveFile();
	MessageBox(_T("Data Save successfully"));
}



void DlgSystemInterface::OnCbnSelchangeInterfaceCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

void DlgSystemInterface::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel = 0;
	CString strTemp;
	nSel = m_InterCombo1.GetCurSel();
	m_InterCombo1.GetLBText(nSel, strTemp);
	InterfaceViewUpdate(strTemp);
	
}

void DlgSystemInterface::InterfaceViewUpdate(CString strSelect)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	TCHAR s_section[4096] = { 0 }; //섹션 아래의 모든 값을 저장할 버퍼
	TCHAR s_key[256] = { 0x00, }; //한 줄을 읽어 저장할 버퍼(키)
	TCHAR s_data[256] = { 0x00, }; //한 줄을 읽어 저장할 버퍼(값)
	int key_pos = 0; //한 줄의 키의 인덱스 위치
	int data_pos = 0; //한 줄의 값의 인덱스 위치
	int nCnt = 0;
	CString strPath;
	BOOL bSection = false; // 한 줄을 모두 확인했으면 true하여, pos를 0으로 초기화해서 다음 줄을 읽을 준비
	bool bEqul = false; //'='으로 키와 값을 분리
	strPath = "..\\..\\DATA\\INTERFACE\\INTERFACE.INI";
	//
	m_InterGrid.put_Cols(2);
	m_InterGrid.put_ColWidth(0, 4500);										//
	m_InterGrid.put_ColWidth(1, 2700);

	//
	DWORD nSize = GetPrivateProfileSection(strSelect, s_section,  4096, strPath);
	for (int i = 0; i < (int)nSize; i++)
	{
		if (s_section[i] != '\0') //문자가 있을 경우
		{
			if (s_section[i] != '=')
			{
				if (bSection) {
					key_pos = 0;
					data_pos = 0;
					bSection = FALSE;
				}

				if (bEqul == false) //=이전 문자는 바로 키
				{
					memcpy(s_key + key_pos, s_section + i, sizeof(s_key + key_pos) - 2); //=이전값인 키를 저장
					key_pos++;
				}
				else  //=이후 문자는 바로 값
				{
					memcpy(s_data + data_pos, s_section + i, sizeof(s_data + data_pos) - 2);
					data_pos++;
				}
			}
			else //문자가 =인 경우
				bEqul = true;
		}
		else //없을경우 ( 키의 끝 / 섹터의 끝)
		{
			
			nCnt++;
			m_InterGrid.put_Rows(nCnt);
			m_InterGrid.put_RowHeight(nCnt -1, 800);

			strTemp = s_key;
			strTemp.Replace("=", "");
			m_InterGrid.put_TextMatrix(nCnt - 1,0, strTemp);
			m_InterGrid.put_TextMatrix(nCnt - 1, 1, s_data);

			s_key[i] = '\0';
			s_data[i] = '\0';
			memset(s_key, 0x00, sizeof(s_key));
			memset(s_data, 0x00, sizeof(s_data));
			bSection = true;
			bEqul = false;
		}
	}
	g_nCols = nCnt;
}

void DlgSystemInterface::SaveFile()
{
	int nSel = 0;
	CString strSection, strKey, strData;
	nSel = m_InterCombo1.GetCurSel();
	m_InterCombo1.GetLBText(nSel, strSection);

	for (int i = 0; i < g_nCols; i++)
	{
		gWriteInterfaceFile(strSection, m_InterGrid.get_TextMatrix(i, 0), m_InterGrid.get_TextMatrix(i, 1));
	}
}


void DlgSystemInterface::ClickInterfaceGrid()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString strValue, strMsg;

	int nRow = m_InterGrid.get_RowSel();
	int nCol = m_InterGrid.get_ColSel();

	strValue = m_InterGrid.get_TextMatrix(nRow, nCol);


	DlgSelect dlg;
	dlg.strnumMsg = strValue;
	dlg.strType = "ENABLE,DISABLE";
	if (dlg.DoModal() == IDOK) {
		if (dlg.strnumMsg == "") return;

		strValue = dlg.strnumMsg;
		m_InterGrid.put_TextMatrix(nRow, nCol, strValue);
	}
}
