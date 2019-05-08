#pragma once


// DlgGemParameter 대화 상자

class DlgGemParameter : public CDialogEx
{
	DECLARE_DYNAMIC(DlgGemParameter)

public:
	DlgGemParameter(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgGemParameter();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GEM_PARAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	CString m_strPort;
	CString m_strDeviceID;
	CString m_strT3;
	CString m_strT5;
	CString m_strT6;
	CString m_strT7;
	CString m_strT8;
	CString m_strLinkTest;
	CString m_strRetryLimit;

	void GemParameterSave();
	void ShowConfig();

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
};
