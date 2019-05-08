#pragma once
#include "dib.h" 

// DlgErrorDisplay 대화 상자

class DlgErrorDisplay : public CDialogEx
{
	DECLARE_DYNAMIC(DlgErrorDisplay)

public:
	DlgErrorDisplay(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgErrorDisplay();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ERROR_DISPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDib* m_ErrorImigeDib;
	void PaintDetailImage(int num);
	void DispErrorSub(int type, int nAlarmCode);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	int m_nErrorCode;
	int m_nErrorNo;
	int  ErrXSize, ErrYSize;
	LPSTR lpErrDibBits;

	BOOL m_bErrShow;
	void SetErrText(int nErrorNo, int nErrorCode, BOOL bshow);
	void AddLog(CString strLog);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	DECLARE_EVENTSINK_MAP()
	void ClickErrorClose();
};
