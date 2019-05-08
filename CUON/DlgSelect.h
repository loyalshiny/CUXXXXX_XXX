#pragma once


// DlgSelect 대화 상자

class DlgSelect : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSelect)

public:
	DlgSelect(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgSelect();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox m_SelectList;
	void LoadList(short row, CString m_strType);
	CString strnumMsg;
	CString strType;
	short nRow;
	afx_msg void OnLbnSelchangeSelectList();
	DECLARE_EVENTSINK_MAP()
	void ClickSelectEnter();
	void ClickSelectClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
