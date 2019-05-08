#pragma once


// DlgLoadPort 대화 상자

class DlgLoadPort : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLoadPort)

public:
	DlgLoadPort(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgLoadPort();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOADPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	CRect rect[4][25];
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Port1StatusDisplay();
	void Port2StatusDisplay();
	void Port3StatusDisplay();
	void Port4StatusDisplay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	int xStart;
	int xEnd;
	int yStart;
	int yEnd;
	int yHeight;
	short nSlot;
	short nPort;
};
