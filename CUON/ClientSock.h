
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CClientSock.h : header file
//
#include "ClientSock.h"
#include "PlcThread.h"
/////////////////////////////////////////////////////////////////////////////
// CClientSock command target

class CClientSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:

			CPlcThread     *m_pPlcThread;
		   	SOCKET		m_Socket;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL
	

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

