
// CUON.h: CUON 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "Define.h"
#include "Parameter.h"
#include "ado.h"

#define SYSTEM_INI_FILE	"..\\..\\DATA\\SYSTEMFILES\\System.ini"
#define GEM_INI_FILE	"..\\..\\DATA\\SYSTEMFILES\\GEM.INI"

// CCUONApp:
// 이 클래스의 구현에 대해서는 CUON.cpp을(를) 참조하세요.
//
class CCUONView;
class CCUONApp : public CWinApp
{
public:
	CCUONApp() noexcept;
	CCUONView* m_pMainView;
	CCUONView* GetMainView() { return m_pMainView; }
	int ReadConfig();
	void ReadConfigFile();
	void WriteConfigFile();
	//	void WriteConfigFile();
	CADODatabase* m_pDatabase;

	CString	m_sAppPath;
	CString m_Recipename;
	CString m_Recipesize;
	CString m_BGRecipe;
	CString m_MDBfilePath;
	CString m_DiscofilePath;

	CString m_UserName;
	CString m_UserID;
	CString m_UserPassword;
	CString m_UserLevel;
	CString m_Year;
	CString m_Month;
	CString m_Day;

	BOOL m_bATLInited;

	UINT m_nLastAlid;
	CString m_strLastAlarmDate;
	CString m_strLastAlarmTime;

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCUONApp theApp;
