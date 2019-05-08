// DlgLoadPort.cpp: 구현 파일
//

#include "pch.h"
#include "CUON.h"
#include "DlgLoadPort.h"
#include "afxdialogex.h"


// DlgLoadPort 대화 상자

IMPLEMENT_DYNAMIC(DlgLoadPort, CDialogEx)

DlgLoadPort::DlgLoadPort(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOADPORT, pParent)
{
	xStart = 0;
	xEnd = 0;
	yStart = 0;
	yEnd = 0;
	yHeight = 0;
	nSlot = 0;
	nPort = 0;
}

DlgLoadPort::~DlgLoadPort()
{
}

void DlgLoadPort::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgLoadPort, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DlgLoadPort 메시지 처리기


BOOL DlgLoadPort::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(0, 500, NULL);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(SILVER);
	
	nSlot = 25;
	nPort = 2;

	if (nSlot == 13)
	{
		yStart = 720;
		yEnd = 760;
		yHeight = 50;
	}
	else if (nSlot == 25)
	{
		yStart = 710;
		yEnd = 730;
		yHeight = 25;
	}

	if (nPort == 2)
	{
		xStart = 10;
		xEnd = 530;
	}
	else if (nPort == 4)
	{
		xStart = 10;
		xEnd = 270;
	}
	else if (nPort == 5)
	{
		xStart = 10;
		xEnd = 215;
	}
	else if (nPort == 6)
	{
		xStart = 10;
		xEnd = 180;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DlgLoadPort::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgLoadPort::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Port1StatusDisplay();
	Port2StatusDisplay();
	Port3StatusDisplay();
	Port4StatusDisplay();

	CDialogEx::OnTimer(nIDEvent);
}


void DlgLoadPort::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오
}

void DlgLoadPort::Port1StatusDisplay()
{
	CClientDC  dc(this);
	short nPortNumber = 0;
	CString strTemp = _T("");
	int nValue = 0;
	if (nPort < 1)return;

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 10, xEnd + (xEnd * nPortNumber), 30);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
	dc.DrawText(TEXT("PORT 1"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 40, xEnd + (xEnd * nPortNumber), 80);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUELED));
	dc.DrawText(TEXT("PORT ID : AAWWEERR2203"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);


	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			nValue = (k * 16) + i;
			strTemp.Format("%d", nValue + 1);
			
			if (nValue > nSlot-1)break;
			if (PollingBit(wEmemoryMappingRead[k], i) && !PollingBit(wEmemoryMappingRead[k + 2], i) && !PollingBit(wEmemoryMappingRead[k + 4], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (DKGREEN));
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 2], i) && !PollingBit(wEmemoryMappingRead[k + 4], i))
			{	
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUE));
				//dc.DrawText(TEXT("LOAD"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 4], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (RED));
				dc.DrawText(TEXT("FAIL"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else 
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
				dc.DrawText(TEXT("NONE"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
		}
	}

}

void DlgLoadPort::Port2StatusDisplay()
{
	CClientDC  dc(this);
	short nPortNumber = 1;
	CString strTemp = _T("");
	int nValue = 0;
	if (nPort < 2)return;

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 10, xEnd + (xEnd * nPortNumber), 30);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
	dc.DrawText(TEXT("PORT 2"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 40, xEnd + (xEnd * nPortNumber), 80);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUELED));
	dc.DrawText(TEXT("PORT ID : AAWWEERR2203"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);


	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			nValue = (k * 16) + i;
			strTemp.Format("%d", nValue + 1);

			if (nValue > nSlot - 1)break;
			if (PollingBit(wEmemoryMappingRead[k + 6], i) && !PollingBit(wEmemoryMappingRead[k + 8], i) && !PollingBit(wEmemoryMappingRead[k + 10], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (DKGREEN));
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 8], i) && !PollingBit(wEmemoryMappingRead[k + 10], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUE));
				//dc.DrawText(TEXT("LOAD"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 10], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (RED));
				dc.DrawText(TEXT("FAIL"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else 
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
				dc.DrawText(TEXT("NONE"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
		}
	}

}
void DlgLoadPort::Port3StatusDisplay()
{
	CClientDC  dc(this);
	short nPortNumber = 2;
	CString strTemp = _T("");
	int nValue = 0;
	if (nPort < 3)return;

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 10, xEnd + (xEnd * nPortNumber), 30);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
	dc.DrawText(TEXT("PORT 3"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 40, xEnd + (xEnd * nPortNumber), 80);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUELED));
	dc.DrawText(TEXT("PORT ID : AAWWEERR2203"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);


	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			nValue = (k * 16) + i;
			strTemp.Format("%d", nValue + 1);

			if (nValue > nSlot - 1)break;
			if (PollingBit(wEmemoryMappingRead[k + 12], i) && !PollingBit(wEmemoryMappingRead[k + 14], i) && !PollingBit(wEmemoryMappingRead[k + 16], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (DKGREEN));
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 14], i) && !PollingBit(wEmemoryMappingRead[k + 16], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUE));
				//dc.DrawText(TEXT("LOAD"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 16], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (RED));
				dc.DrawText(TEXT("FAIL"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
				dc.DrawText(TEXT("NONE"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
		}
	}

}

void DlgLoadPort::Port4StatusDisplay()
{
	CClientDC  dc(this);
	short nPortNumber = 3;
	CString strTemp = _T("");
	int nValue = 0;
	if (nPort < 4)return;

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 10, xEnd + (xEnd * nPortNumber), 30);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
	dc.DrawText(TEXT("PORT 4"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), 40, xEnd + (xEnd * nPortNumber), 80);
	dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUELED));
	dc.DrawText(TEXT("PORT ID : AAWWEERR2203"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			nValue = (k * 16) + i;
			strTemp.Format("%d", nValue + 1);

			if (nValue > nSlot - 1)break;
			if (PollingBit(wEmemoryMappingRead[k + 18], i) && !PollingBit(wEmemoryMappingRead[k + 20], i) && !PollingBit(wEmemoryMappingRead[k + 22], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (DKGREEN));
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 20], i) && !PollingBit(wEmemoryMappingRead[k + 22], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (BLUE));
				//dc.DrawText(TEXT("LOAD"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else if (PollingBit(wEmemoryMappingRead[k + 22], i))
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (RED));
				dc.DrawText(TEXT("FAIL"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
			else
			{
				rect[nPortNumber][nValue] = CRect(xStart + (xEnd * nPortNumber), yStart - (yHeight * nValue), xEnd + (xEnd * nPortNumber), yEnd - (yHeight * nValue));
				dc.FillSolidRect(&rect[nPortNumber][nValue], (LTGRAY));
				dc.DrawText(TEXT("NONE"), &rect[nPortNumber][nValue], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.DrawText(TEXT(strTemp), &rect[nPortNumber][nValue], DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			}
		}
	}

}
