// DlgErrorDisplay.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgErrorDisplay.h"
#include "afxdialogex.h"


// DlgErrorDisplay 대화 상자

IMPLEMENT_DYNAMIC(DlgErrorDisplay, CDialogEx)

DlgErrorDisplay::DlgErrorDisplay(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ERROR_DISPLAY, pParent)
{
	m_bErrShow = FALSE;
	m_ErrorImigeDib = NULL;
	m_nErrorCode = 0;
	m_nErrorNo = 0;
	ErrXSize = 0;
	ErrYSize = 0;
}

DlgErrorDisplay::~DlgErrorDisplay()
{
	if (m_ErrorImigeDib != NULL) delete m_ErrorImigeDib;
}

void DlgErrorDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgErrorDisplay, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &DlgErrorDisplay::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgErrorDisplay::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgErrorDisplay 메시지 처리기


BOOL DlgErrorDisplay::PreTranslateMessage(MSG* pMsg)
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


BOOL DlgErrorDisplay::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(WHITE);
	//SetBackgroundColor(RGB(128,128,128));
	//SetBackgroundColor(RED);
	//SetBackgroundColor(BLACK);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgErrorDisplay::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


void DlgErrorDisplay::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CBrush brush, * oldbrush;

	// brush.CreateSolidBrush(RGB(211,220,163));
	brush.CreateSolidBrush(BLACK);

	oldbrush = dc.SelectObject(&brush);
	//dc.Rectangle(0, 9, 1111, 624);
	dc.SelectObject(oldbrush);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();


	CDC* pDC = GetDC();
	//	CDC* pDisplayMemDC= new CDC;
	CWnd* pWnd = GetDlgItem(IDC_STATIC);
	if (m_ErrorImigeDib && pWnd) {
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		if (m_ErrorImigeDib) {
			m_ErrorImigeDib->PaintDIB(pDC, rc, CRect(0, 0, m_ErrorImigeDib->GetWidth(), m_ErrorImigeDib->GetHeight()), NULL);
		}
	}

	ReleaseDC(pDC);
}

void DlgErrorDisplay::PaintDetailImage(int num)
{
	
/*	CString str;
	str.Format("c:\\ImageBitmap\\%d.bmp",num);
	m_ErrorImigeDib.Create(str);
	CRect rect;//(0,0,825,740);
	CWnd* detail=GetDlgItem(IDC_STATIC);
	detail->GetClientRect(rect);
	CDC* pDC=detail->GetDC();
	m_ErrorImigeDib.PaintDIB(pDC,rect,CRect(0,0,m_ErrorImigeDib.GetWidth(),m_ErrorImigeDib.GetHeight()),NULL);
	detail->ReleaseDC(pDC);*/

		
	num = 40015;
	CString str;
	str.Format("..\\..\\..\\ImageBitmap\\%d.bmp", num);
	

	if (m_ErrorImigeDib) {
		delete m_ErrorImigeDib;
		m_ErrorImigeDib = NULL;
	}
	if (m_ErrorImigeDib == NULL) {
		m_ErrorImigeDib = new CDib((LPSTR)str.operator const char* ());
		ErrXSize = m_ErrorImigeDib->GetWidth();
		ErrYSize = m_ErrorImigeDib->GetHeight();
	}

}

void DlgErrorDisplay::DispErrorSub(int type, int nAlarmCode)
{
	CString strcause1, strcause2 = "", strcause3 = "";
	CString straction1, straction2 = "", straction3 = "";
	CString stralarmcode;
	//		 int k;

	/*		 strcause1 = m_aAlarm[type].m_szCauText;
	k =	 strcause1.Find(0x0d);
	strcause2 = strcause1.Left(k);
	strcause2.Right(k+1);
	*/

	/*strcause2.Format("%s", m_aAlarm[type].m_szText);
	m_ErrorTitle.SetCaption(strcause2);

	stralarmcode.Format("%d", nAlarmCode);
	m_ErrorCode.SetCaption(stralarmcode);

	strcause1.Format("%s \n ", m_aAlarm[type].m_szCauText);
	m_ErrorCause.SetCaption(strcause1);

	straction1.Format("%s\n", m_aAlarm[type].m_szActText);
	m_ErrorAction.SetCaption(straction1);*/
}


void DlgErrorDisplay::SetErrText(int nErrorNo, int nErrorCode, BOOL bshow)
{

	CString strGTime = _T("");
	CString strGText = _T("");
	CString strGCode = _T("");
	CString strGLog = _T("");

	CString strDate, strTime;
	CTime time = CTime::GetCurrentTime();
	strGTime.Format("%02d:%02d:%02d", time.GetHour(), time.GetMinute(), time.GetSecond());

	DispErrorSub(nErrorNo, nErrorCode);
//	GetDlgItemText(IDC_ERROR_TITLE, strGText);
//	GetDlgItemText(IDC_ERROR_CODE, strGCode);
	strGLog = strGTime + "::[" + strGCode + "]_" + strGText;
	if (strGText.GetLength() > 1)	AddLog(strGLog);

	if (m_bErrShow)
	{

		//AddLog( strGTime );
	}
	else
	{
		PaintDetailImage(nErrorCode);


	}


	//	m_msg = strText;
	//	SetDlgItemText( IDC_STATIC_TIME , strTime );
	//	m_MainMsg.SetCaption(strText);


	//if (!bshow)this->ShowWindow(SW_SHOW);
	//else this->ShowWindow(SW_HIDE);

	m_bErrShow = TRUE;
	//strText(m_msg);
}


void DlgErrorDisplay::AddLog(CString strLog)
{
	//======================

/*	//m_ListLog.AddString( strLog );
	m_ErrorListLog.InsertString(0, strLog);

	INT nCnt = 0;

	nCnt = m_ErrorListLog.GetCount();

	while (nCnt > MAX_TERMINAL_COUNT)
	{
		m_ErrorListLog.DeleteString(nCnt - 1);
		nCnt = m_ErrorListLog.GetCount();

	}*/

}

void DlgErrorDisplay::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void DlgErrorDisplay::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
BEGIN_EVENTSINK_MAP(DlgErrorDisplay, CDialogEx)
	ON_EVENT(DlgErrorDisplay, IDC_ERROR_CLOSE, DISPID_CLICK, DlgErrorDisplay::ClickErrorClose, VTS_NONE)
END_EVENTSINK_MAP()


void DlgErrorDisplay::ClickErrorClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	EndDialog(IDOK);
}
