// PlcCommThread.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "framework.h"
#include "CUON.h"
#include "PlcThread.h"
#include "CUON.h"
#include "MainFrm.h"
#include "ClientSock.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CPlcThread

IMPLEMENT_DYNCREATE(CPlcThread, CWinThread)

CPlcThread::CPlcThread()
{
}

CPlcThread::~CPlcThread()
{
}

BOOL CPlcThread::InitInstance()
{
	// TODO: 여기에서 각 스레드에 대한 초기화를 수행합니다.
	OnSockConnect();
	return TRUE;
}

int CPlcThread::ExitInstance()
{
	// TODO: 여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPlcThread, CWinThread)
END_MESSAGE_MAP()


// CPlcThread 메시지 처리기입니다.
int CPlcThread::Run()
{
	while(1)
	{
		InterpretEMWordGEMRead();     // E Gem Bit Read
		InterpretCIOTouchRead();		// Plc -> PC Cio Read
		InterpretCIOTouchReadGem();	// Plc -> PC Cio Gem Read
		InterpretOperator();			// Operator Log Add
		InterpretCIOBitCheck();		// PC -> PC Cio Write Data Check
		InterpretCIOBitCheckGem();	//	PC -> PC Gem Cio Write Data Check
		InterpretEMWordRead();		// E Memory Read
		InterpretEMWordReadMotor();  // Motor Current Pos
		InterpretEMWordMonitorRead(); // E Memory Monitor Read
		InterpretEMWordMappingRead(); // E memory 500 mapping Read
		InterpretEMWordMotorSpeedRead();
		InterpretMotorCurrentPos();
		InterpretMonitorDataRead();
		InterpretBitInvertCheck();
		InterpretMotorUpdateCheck();
		InterpretCIOInOutRead();  // Input Output Check Read	
		//
		if (Main.EMemoryWrite >= 1 && Main.EMemoryWrite <= MODULE_MAXWRITE) InterpretModeSelect(Main.EMemoryWrite);
	}
	
}

short CPlcThread::PLC_FinsNodeAddrDataSend()
{
	short		nRes, nmRes;
	DWORD		dwStart, dwEnd, dwCount;
	char		szReq[24];		memset(szReq, 0, sizeof(szReq));
	char		szRes[1024];	memset(szRes, 0, sizeof(szRes));
	char		*pszBuff = NULL;

	int strTemp=0;
	CString m_ComOpmand,m_ComOpmand1 ,m_szReq;
	CStringArray strConfigArray;
	szReq[23] = '\0';				// memset(szReq, 0, sizeof(szReq));
	szRes[1023] = '\0';				// memset(szRes, 0, sizeof(szRes));


	// Make Message
	sprintf(szReq, "%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
		"FINS",					// Header
		0x00,0x00,0x00,0x0C,	// length...0x0c
		0x00,0x00,0x00,0x00,	// Command	
		0x00,0x00,0x00,0x00,	// Error Code
		0x00,0x00,0x00,0x00);	// Client Node Add...Set 0 (Auto)
	

		m_pClientSock->Send(szReq, 20);
	

	//m_pClSock->Send(szReq, 20);
	
	pszBuff = new char[24];		memset(pszBuff, 0, sizeof(char) * 24);
	
	dwStart = ::GetTickCount();
	do 
	{
		strTemp ++;

		
			nRes = m_pClientSock->Receive(pszBuff, 256);
		
		

		
		if( nRes > -1 )
		{
			memcpy(szRes, pszBuff, nRes);
		}
		
		dwEnd = ::GetTickCount();
		dwCount = dwEnd - dwStart;
		::Sleep(100);
		
	} while ((nRes <= 0) && (dwCount < MAX_RESP_TIMEOUT));
	
	// Command check

	if(szRes[4]!=0x00 || szRes[5]!=0x00 || szRes[6]!=0x00 || szRes[7]!=0x00 || szRes[12]!=0x00 || szRes[13]!=0x00 || szRes[14]!=0x00 || szRes[15]!=0x00 || szRes[19]!=0x00 || szRes[23]!=0x00)
		
	if(nRes == 24)
	{
		if( szRes[8] != 0x00 || szRes[9] != 0x00 || szRes[10] != 0x00 || szRes[11] != 0x01 )
		{
			nRes = FINS_COMMAND_ERR;		
		}
		else if( szRes[15] != 0x00 )
		{
			CString sErr;
			sErr.Format(_T("%X"), szRes[15]);
			nRes = FINS_ - _ttoi(sErr);
		   	nmRes = _ttoi(sErr);
		}
		else 
		{
			SystemINIFiles.m_cClNodeNo = (BYTE)szRes[19];
			SystemINIFiles.m_cSvNodeNo = (BYTE)szRes[23];
			nRes = ERS_NO_ERR;
		}
	}
	else 
	{
		nRes = FINS_TCP_RECIPE_ERR;
	}
	
	delete [] pszBuff;


	
	return nRes;


}



short CPlcThread::PLC_ReceiveData(short nAddr, short nPoints, short nType, unsigned short* psRBuf, short nBufSize, BYTE nPlcType)
{
	DWORD	dwStart=0;
	DWORD	dwCount=0;
	
	CString	sTemp = "";
	CString	sLog = "";

	BYTE	nAddr1 = 0;
	BYTE	nAddr2 = 0;
	BYTE	nPoints1 = 0;
	BYTE	nPoints2 = 0;

	short	nSize=0;
	short	nRes=0;

	if( SystemINIFiles.m_fConn != TRUE && SystemINIFiles.m_fActive != TRUE ) { return FINS_COMMAND_ERR; }

	//  Initialize ------------------------------------------------------------------------------------------------
	// Service ID add
	if( SystemINIFiles.m_cSID > 0xFF ) { SystemINIFiles.m_cSID = 0x00; }
	else				{ SystemINIFiles.m_cSID++;		 }
		
	nAddr1 = HIBYTE((unsigned)nAddr);
	nAddr2 = LOBYTE((unsigned)nAddr);
	nPoints1 = HIBYTE((unsigned)nPoints);
	nPoints2 = LOBYTE((unsigned)nPoints);
	
	//  -----------------------------------------------------------------------------------------------------------
	// Read Bit
	if( nType == BIT_AREA ) 
	{
		BYTE		szReq[1024];		
		BYTE		*pszRead = NULL;
		BYTE		*pszBuff = NULL;
		BYTE		*pszData = NULL;
		int			nLen = 0;
		int			nStr = 0;
		
		memset(szReq, 0, sizeof(szReq));
		//================================================================================
		// FINS COMMAND READ
		// FINS | length | Command | Error Code													1
		// ICF | RSV | GCT | DNA | DA1 | DA2 | SNA | SA1 | SA2 | SID | ... FINS	Header			2
		// MRC | SRC | ... FINS Command															3
		// Variable Type (E) | Read Start Address | Read Length (per WORD)						4
		//		nLen = sprintf(szReq, "%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
		//						"FINS",0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,	  //1
		//						0x80,0x00,0x02,0x00,m_cSvNodeNo,0x00,0x00,m_cClNodeNo,0x00,m_cSID,	  //2	
		//						0x01,0x01,															  //3
		//						0x20,nAddr1,nAddr2,0x00,nPoints1,nPoints2);						      //4 

		szReq[0] = 'F';
		szReq[1] = 'I';
		szReq[2] = 'N';
		szReq[3] = 'S';
		szReq[7] = 0x1a;
		szReq[11] = 0x02;
		szReq[16] = 0x80;
		szReq[18] = 0x02;
		szReq[20] = SystemINIFiles.m_cSvNodeNo;
		szReq[23] = SystemINIFiles.m_cClNodeNo;
		szReq[25] = SystemINIFiles.m_cSID;
		szReq[26] = 0x01;
		szReq[27] = 0x01;
		szReq[28] = nPlcType;     	 //20-E , 
		szReq[29] = nAddr1;
		szReq[30] = nAddr2;
		szReq[32] = nPoints1;
		szReq[33] = nPoints2;

		nLen = 34;




			m_pClientSock->Send(szReq, nLen);

	//===============================================================
	//  Receive 
		nLen = LEN_READ_RESPONSE;
		nSize = nLen + nPoints + 1;

		// Read Response
		pszRead = new BYTE[nSize];	memset(pszRead, 0, sizeof(BYTE) * nSize);
		pszBuff = new BYTE[nSize];	memset(pszBuff, 0, sizeof(BYTE) * nSize);
		pszData = new BYTE[nSize];	memset(pszData, 0, sizeof(BYTE) * nSize);

		dwStart = ::GetTickCount();
		do 
		{	
			::Sleep(1);
			
				nRes = m_pClientSock->Receive(pszBuff, nSize - 1);

			dwCount = ::GetTickCount() - dwStart;

			if (nRes > 0)
			{ 
				memcpy(pszRead + nStr, pszBuff, nRes);
				nStr += nRes;
			}
		} while ((nRes <= 0) && (dwCount < MAX_RESP_TIMEOUT));
		*(pszRead + (nSize - 1)) = '\0';

		//  Error Check -------------------------------------------------------------------------------------------
		// Command check
		if( pszRead[8] != 0x00 || pszRead[9] != 0x00 || pszRead[10] != 0x00 || pszRead[11] != 0x02 ) {
			nRes = FINS_COMMAND_ERR;		
		}
		// Error Code Check
		else if( pszRead[15] != 0x00 ) 
		{
			CString sErr;
			sErr.Format("%X", pszRead[15]);
			nRes = FINS_ - atoi(sErr);
		}
		else 
		{
			nRes = ERS_NO_ERR;
		}

		memcpy(pszData, pszRead +  LEN_READ_RESPONSE, nPoints);

		for( int i=0; i<nPoints; i++ )
		{
			if( pszData[i] == 1 ) 
			{
				psRBuf[i] = 1;
			}
			else 
			{
				psRBuf[i] = 0;
			}
		}
		
		delete [] pszBuff;
		delete [] pszRead;
		delete [] pszData;
	}
	// Read Word ---------------------------------------------------------------------------------------------------
	else if ( nType == WORD_AREA ) 
	{
		BYTE		szReq[1024];		
		BYTE		*pszRead = NULL;
		BYTE		*pszBuff = NULL;
		BYTE		*pszData = NULL;
		WORD        *pszWdata = NULL;
		int			nLen = 0;
		int			nStr = 0;
		
		memset(szReq, 0, sizeof(szReq));

		///================================================================================
		// FINS COMMAND READ
		// FINS | length | Command | Error Code													1
		// ICF | RSV | GCT | DNA | DA1 | DA2 | SNA | SA1 | SA2 | SID | ... FINS	Header			2
		// MRC | SRC | ... FINS Command															3
		// Variable Type (E) | Read Start Address | Read Length (per WORD)						4

		//		nLen = sprintf(szReq, "%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
		//						"FINS",0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,	  //1
		//						0x80,0x00,0x02,0x00,m_cSvNodeNo,0x00,0x00,m_cClNodeNo,0x00,m_cSID,	  //2	
		//						0x01,0x01,															  //3
		//						0xA0,nAddr1,nAddr2,0x00,nPoints1,nPoints2);						      //4 

		szReq[0] = 'F';
		szReq[1] = 'I';
		szReq[2] = 'N';
		szReq[3] = 'S';
		szReq[7] = 0x1a;
		szReq[11] = 0x02;
		szReq[16] = 0x80;
		szReq[18] = 0x02;
		szReq[20] = SystemINIFiles.m_cSvNodeNo;
		szReq[23] = SystemINIFiles.m_cClNodeNo;
		szReq[25] = SystemINIFiles.m_cSID;
		szReq[26] = 0x01;
		szReq[27] = 0x01;
		szReq[28] = nPlcType;		//a0-E , //80-cio // 82-D
		szReq[29] = nAddr1;
		szReq[30] = nAddr2;
		szReq[32] = nPoints1;
		szReq[33] = nPoints2;

		nLen = 34;
		
		

			m_pClientSock->Send(szReq, nLen);

		//  Receive -------------------------------------------------------------------------------------------
		nLen = LEN_READ_RESPONSE;
		nSize = nLen + (nPoints * 2) + 1;

		pszRead = new BYTE[nSize];	memset(pszRead, 0, sizeof(BYTE) * nSize);
		pszBuff = new BYTE[nSize];	memset(pszBuff, 0, sizeof(BYTE) * nSize);
		pszData = new BYTE[nSize];	memset(pszData, 0, sizeof(BYTE) * nSize);
		pszWdata = new WORD[nSize];	memset(pszWdata, 0, sizeof(WORD) * nPoints);

		// Read Response
		dwStart = ::GetTickCount();
		do
		{	
			::Sleep(1);
			
				nRes = m_pClientSock->Receive(pszBuff, nSize - 1);
				

			dwCount = ::GetTickCount() - dwStart;
			
			if (nRes > 0) 
			{ 
				memcpy(pszRead + nStr, pszBuff, nRes);
				nStr += nRes;
			}
		} while ((nRes <= 0) && (dwCount < MAX_RESP_TIMEOUT));
		*(pszRead + (nSize - 1)) = '\0';

		//  Error Check -------------------------------------------------------------------------------------------
		// Command check
		if( pszRead[8] != 0x00 || pszRead[9] != 0x00 || pszRead[10] != 0x00 || pszRead[11] != 0x02 )
		{
			nRes = FINS_COMMAND_ERR;		
		}
		else if( pszRead[15] != 0x00 )	// Error Code Check
		{
			CString sErr;
			sErr.Format("%X", pszRead[15]);
			nRes = FINS_ - atoi(sErr);
		}
		else 
		{
			nRes = ERS_NO_ERR;
		}
		
		memcpy(pszData, pszRead +  LEN_READ_RESPONSE, nPoints * 2);
		memcpy(psRBuf, pszRead +  LEN_READ_RESPONSE, nPoints * 2);
		
		for (int i = 0; i < nPoints; i++) 
		{
			psRBuf[i] = (unsigned)pszData[(i * 2) + 0] * 0x0100 + (unsigned)pszData[(i * 2) + 1];
		}

		delete [] pszRead;
		delete [] pszBuff;	
		delete [] pszData;
		delete [] pszWdata;
	}
		
	return nRes;
}

short CPlcThread::PLC_SendData(short nAddr, short nPoints, short nType, unsigned short *pnWBuf, short nBufSize,BYTE nPlcType)
{
	char	szRes[1024];	memset(szRes, 0, sizeof(szRes));
	BYTE	szRead[1024];
	BYTE	szBuff[1024];
	DWORD	dwStart=0;
	DWORD	dwCount=0;
	
	CString	sTemp = "";
	CString	sLog = "";

	BYTE	nAddr1 = 0;
	BYTE	nAddr2 = 0;
	BYTE	nPoints1 = 0;
	BYTE	nPoints2 = 0;
	BYTE	nLength1 = 0;
	BYTE	nLength2 = 0;

	BYTE	*pszRead = NULL;
	BYTE	*pszData = NULL;

	short	nSize = 0;
	short	nRes = 0;
	char str2[256];

	if( SystemINIFiles.m_fConn != TRUE && SystemINIFiles.m_fActive != TRUE ) { return FINS_COMMAND_ERR; }
	memset(szRead, 0, sizeof(szRead));
	memset(szBuff, 0, sizeof(szBuff));

	//  Initialize ------------------------------------------------------------------------------------------------
	// Service ID add
	if( SystemINIFiles.m_cSID > 0xFF ) { SystemINIFiles.m_cSID = 0x00; }
	else				{ SystemINIFiles.m_cSID++;		 }
		
	nAddr1 = HIBYTE(nAddr);
	nAddr2 = LOBYTE(nAddr);
	nPoints1 = HIBYTE(nPoints);
	nPoints2 = LOBYTE(nPoints);

	//  Write Bit Area ---------------------------------------------------------------------------------------------
	if( nType == BIT_AREA )
	{
		BYTE	*pszReq = NULL;				// Request Command
		short	nSize = 0;
		short	nLen = 0;
		short	nStr = 0;

		char	szTemp[0xff];
		memset(szTemp, 0, sizeof(szTemp));

		// nPoints is Write Data length ( byte )
		nLen = LEN_READ_REQUEST;
		nSize = nLen + nPoints + 1;		

		pszReq = new BYTE[nSize];	
		memset(pszReq, 0, sizeof(BYTE) * nSize);

		// Command Length
		nStr = 8 + 18 + nPoints;
		

		//================================================================================
		// FINS COMMAND WRITE
		// FINS | length | Command | Error Code														1
		// ICF | RSV | GCT | DNA | DA1 | DA2 | SNA | SA1 | SA2 | SID | ... FINS	Header				2
		// MRC | SRC | ... FINS Command																3
		// Variable Type (E) | Read Start Address | Read Length (per WORD)							4
		//
		//		nLen = sprintf(pszReq, "%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s",
		//						"FINS",0x00,0x00,0x00,nStr,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,		
		//						0x80,0x00,0x02,0x00,m_cSvNodeNo,0x00,0x00,m_cClNodeNo,0x00,m_cSID,				
		//						0x01,0x02,																	
		//						0x20,nAddr1,nAddr2,0x00,nPoints1,nPoints2,pszWrite);						

		pszReq[0] = 'F';
		pszReq[1] = 'I';
		pszReq[2] = 'N';
		pszReq[3] = 'S';
		pszReq[7] = (BYTE)nStr;
		pszReq[11] = 0x02;
		pszReq[16] = 0x80;
		pszReq[18] = 0x02;
		pszReq[20] = SystemINIFiles.m_cSvNodeNo;
		pszReq[23] = SystemINIFiles.m_cClNodeNo;
		pszReq[25] = SystemINIFiles.m_cSID;
		pszReq[26] = 0x01;
		pszReq[27] = 0x02;			 //Read->01,Write->02
		pszReq[28] = nPlcType;   //nPlcType; //0x20;	   ///E->20 D->82 ,CIO->80
		pszReq[29] = nAddr1;
		pszReq[30] = nAddr2;
		pszReq[32] = nPoints1;
		pszReq[33] = nPoints2;

		for (int i = 0; i < nPoints; i++)
		{
			pszReq[LEN_READ_REQUEST + i] = (pnWBuf[i] == 1) ? 0x31 : 0x30;
		}
		
		nLen = LEN_READ_REQUEST + nPoints;			//LEN_READ_REQUEST = 34
		memcpy(szTemp, pszReq, nLen);


			m_pClientSock->Send(pszReq, nLen);


		nStr = 34;

		//  Receive -------------------------------------------------------------------------------------------
		dwStart = ::GetTickCount();
		do 
		{	
			::Sleep(10);
			

				nRes = m_pClientSock->Receive(szBuff, sizeof(szBuff));

			dwCount = ::GetTickCount() - dwStart;

			if (nRes > 0) 
			{ 
				memcpy(szRead + nStr, szBuff, nRes);
				nStr += nRes;

				nLen = LEN_READ_RESPONSE;
				nSize = nLen + (nPoints * 2) + 1;
			}
			
			pszData = new BYTE[nSize];	memset(pszData, 0, sizeof(BYTE) * nSize);

			for (int i = 0; i < nPoints; i++) 
			{
				pszData[i] = (unsigned)szRead[(i * 2) + 0] * 0x0100 +
					(unsigned)szRead[(i * 2) + 1];
			}
			

			dwCount = ::GetTickCount() - dwStart;

			if (nRes > 0) 
			{ 
				memcpy(szRead + nStr, szBuff, nRes);
				nStr += nRes;
			}
		} while ((nRes <= 0) && (dwCount < MAX_RESP_TIMEOUT));

		//  Error Check -------------------------------------------------------------------------------------------
		// Command check
		if( szRead[8] != 0x00 || szRead[9] != 0x00 || szRead[10] != 0x00 || szRead[11] != 0x02 ) 
		{
			nRes = FINS_COMMAND_ERR;		
		}
		// Error Code Check
		else if( szRead[15] != 0x00 )
		{
			CString sErr;
			sErr.Format("%X", szRead[15]);
			nRes = FINS_ - atoi(sErr);
		}
		else 
		{
			nRes = ERS_NO_ERR;
		}

		delete [] pszReq;
		delete [] pszData;
		delete [] pszRead;
	}
	//  Write Word Area ---------------------------------------------------------------------------------------------
	else if( nType == WORD_AREA )
	{
		BYTE	*pszReq = NULL;
		short	nSize = 0;
		short	nLen = 0;
		short	nStr = 0;
		
		nLen = LEN_READ_REQUEST;
		nSize = nLen + (nPoints * 2) + 1;		

		pszReq = new BYTE[nSize];	
		memset(pszReq, 0, sizeof(BYTE) * nSize);

		// Command Length
		nStr = 8 + 18 + (nPoints * 2);
		nLength1 = HIBYTE(nStr);
		nLength2 = LOBYTE(nStr);

		//================================================================================
		// FINS COMMAND WRITE
		// FINS | length | Command | Error Code														1
		// ICF | RSV | GCT | DNA | DA1 | DA2 | SNA | SA1 | SA2 | SID | ... FINS	Header				2
		// MRC | SRC | ... FINS Command																3
		// Variable Type (E) | Read Start Address | Read Length (per WORD)							4
		
		//		nLen = sprintf(pszReq, "%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s",
		//						"FINS",0x00,0x00,nLength1,nLength2,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,		
		//						0x80,0x00,0x02,0x00,m_cSvNodeNo,0x00,0x00,m_cClNodeNo,0x00,m_cSID,			
		//						0x01,0x02,																	
		//						0xA0,nAddr1,nAddr2,0x00,nPoints1,nPoints2,pszWrite);						
		//		
		pszReq[0] = 'F';
		pszReq[1] = 'I';
		pszReq[2] = 'N';
		pszReq[3] = 'S';
		pszReq[6] = nLength1;
		pszReq[7] = nLength2;
		pszReq[11] = 0x02;
		pszReq[16] = 0x80;
		pszReq[18] = 0x02;
		pszReq[20] = SystemINIFiles.m_cSvNodeNo;
		pszReq[23] = SystemINIFiles.m_cClNodeNo;
		pszReq[25] = SystemINIFiles.m_cSID;
		pszReq[26] = 0x01;
		pszReq[27] = 0x02;
		pszReq[28] = nPlcType ;  //E - 0xA0;
		pszReq[29] = nAddr1;
		pszReq[30] = nAddr2;
		pszReq[32] = nPoints1;
		pszReq[33] = nPoints2;

		for (int i = 0; i < nPoints; i++) 
		{
			pszReq[(i * 2) + 35] = ((unsigned)pnWBuf[i] & 0x00ff);
			pszReq[(i * 2) + 34] = ((unsigned)pnWBuf[i] / 0x0100) & 0x00ff;
		}




			m_pClientSock->Send(pszReq, nSize - 1);

		nStr = 0;

		//  Receive -------------------------------------------------------------------------------------------
		dwStart = ::GetTickCount();
		do 
		{	
			::Sleep(10);
			
				nRes = m_pClientSock->Receive(szBuff, sizeof(szBuff));

			dwCount = ::GetTickCount() - dwStart;

			if( nRes <= 0) 
			{
				wsprintf(str2, "Not Send: %s", pszData);
			}
			else
			{
				wsprintf(str2,"Sent: %s", pszData);
			}
			//	sLog.Format("%s",str2);
		
//			m_ScrList.AddString(str2);

			if (nRes > 0) 
			{ 
				memcpy(szRead + nStr, szBuff, nRes);
				nStr += nRes;
			}
		} while ((nRes <= 0) && (dwCount < MAX_RESP_TIMEOUT));

		//  Error Check -------------------------------------------------------------------------------------------
		// Command check
		if( szRead[8] != 0x00 || szRead[9] != 0x00 || szRead[10] != 0x00 || szRead[11] != 0x02 )
		{
			nRes = FINS_COMMAND_ERR;		
		}
		// Error Code Check
		else if( szRead[15] != 0x00 ) 
		{
			CString sErr;
			sErr.Format("%X", szRead[15]);
			nRes = FINS_ - atoi(sErr);
		}
		else
		{
			nRes = ERS_NO_ERR;
		}

		delete [] pszReq;
		delete [] pszData;
		delete [] pszRead;
	}

	return nRes;
}

////////////////////////////////
//// TCP Connect*/
void CPlcThread::OnReceive()
{
}
void CPlcThread::OnAccept()
{
}

void CPlcThread::OnSockConnect() 
{
	// TODO: Add your control notification handler code here
	BOOL result;
	m_pClientSock = new CClientSock();
    m_pClientSock->m_pPlcThread=this;
	m_pClientSock->Create();
	SystemINIFiles.m_fActive = TRUE;
 	if(strlen(SystemINIFiles.m_sIP) == 0)
	{

		return;
	}
	result = m_pClientSock->Connect(SystemINIFiles.m_sIP, SystemINIFiles.m_nPort);
	if(result == TRUE)
	{
	
		SystemINIFiles.m_fSatus = TRUE;
		if(PLC_FinsNodeAddrDataSend() == ERS_NO_ERR) {	SystemINIFiles.m_fConn = TRUE ;  }  //Connected(TRUE);
		else  {   SystemINIFiles.m_fConn = FALSE;  }		//Connected(FALSE);
	}
	else
	{
		SystemINIFiles.m_fSatus = FALSE;
		m_pClientSock->Close();
		//AfxMessageBox("PLC Connected Fail");
	}
}
void CPlcThread::InterpretModeSelect(int m_ModeNo) 
{
	// TODO: Add your control notification handler code here
	if(m_ModeNo == 0) return;

	switch (m_ModeNo)
	{

		case RECIPE_WRITE: 
			for (int i=0;i<Main.EMemoryWriteCount;i++)
			{
				InterpretEMDoubleWordWrite(atoi(m_RecipeTable.strAdress[i]), 1, i);
			}
			 break;
		case MOTOR_WRITE: 
			for (int i=0;i<Main.EMemoryWriteCount;i++)
			{
				InterpretEMDoubleWordWrite(atoi(m_MotorTable[Main.nCurrentMotorNo].strAdress[i]), 1, i);
			}
			break;
	
	}

	Main.EMemoryWrite = 0;
	Main.EMemoryWriteCount = 0;
}
short CPlcThread::InterpretCIOInOutRead() 
{
	// TODO: Add your control notification handler code here 
		  /////////////////////////////
	////////// IN/OUT AREA 

	short nPoints = MAX_IOCOUNT_48 * 2; /// 000.00 ~ 018.15
	short nAddr = ADDR_CIO_0;
	short nRet;
	short nBufSize = nPoints *2;
	unsigned short	*psRBuf = NULL;


	psRBuf = new unsigned short[nPoints + 1];		
	memset(psRBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(psRBuf, psRBuf, nPoints);
	
	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, CIO_MEMORYRED);

	if(!nRet)                                   //memcpy(wInOutput, pnWBuf, nPoints);
	{
		memcpy(wInOutput, psRBuf, nPoints);
	}
	delete [] psRBuf;

	return nRet;
}	

short CPlcThread::InterpretCIOTouchRead() 
{
	// TODO: Add your control notification handler code here 
	/////////////////////////////
	////////// IN/OUT AREA 

	short nPoints = MAX_TOUCHCOUNT_62 * 2; /// 1200.00 ~ 1259.15
	short nAddr = ADDR_CIOTOUCH_1000;
	short nRet;
	short nBufSize = nPoints *2;
	unsigned short	*psRBuf = NULL;

	psRBuf = new unsigned short[nPoints + 1];		
	memset(psRBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(psRBuf, psRBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, CIO_MEMORYRED);

	if(!nRet)                                   //memcpy(wInOutput, pnWBuf, nPoints);
	{
		memcpy(wTouchInput, psRBuf, nPoints);
	}
	delete [] psRBuf;

	return nRet;
}	
short CPlcThread::InterpretCIOTouchReadGem() 
{
	// TODO: Add your control notification handler code here 
	/////////////////////////////
	////////// IN/OUT AREA 

	short nPoints = MAX_GEMCIOCOUNT_10 * 2 ; 
	short nAddr = ADDR_CIO_1300;
	short nRet;
	short nBufSize = nPoints *2;
	unsigned short	*psRBuf = NULL;

	psRBuf = new unsigned short[nPoints + 1];		
	memset(psRBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(psRBuf, psRBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, CIO_MEMORYRED);

	if(!nRet)                                   //memcpy(wInOutput, pnWBuf, nPoints);
	{
		memcpy(wTouchCIOGem, psRBuf, nPoints);
	}
	delete [] psRBuf;

	return nRet;
}		

short CPlcThread::InterpretAlarmEMWordRead() 
{
	// TODO: Add your control notification handler code here 
	/////////////////////////////
	////////// IN/OUT AREA 

	short nPoints = MAX_ALARMCOUNT_59 * 2; /// (MAX_ALARMCIO-1)*2 = 94
	short nAddr = ADDR_ALARMS_400;
	short nRet;
	short nBufSize = nPoints *2;
	unsigned short	*psRBuf = NULL;

	psRBuf = new unsigned short[nPoints];		
	memset(psRBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(psRBuf, psRBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, EWORD_MEMORY);//CIO_MEMORYRED

	if(!nRet)                                   //memcpy(wInOutput, pnWBuf, nPoints);
	{
		memcpy(wAlarmInput, psRBuf, nPoints);
	}
	delete [] psRBuf;

	return nRet;
}	
short CPlcThread::InterpretCIOBitWrite(short nAddr, short nPosition, short onoff) 
{
	// TODO: Add your control notification handler code here 
	/////////////////////////////
	////////// IN/OUT AREA 

	short nPoints = 16; /// 1300.00 ~ 1379.15
	short nRet;
	short nBufSize = nPoints *2;
	unsigned short	*pnWBuf = NULL;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	pnWBuf[nPosition] = onoff;
	nRet = PLC_SendData(nAddr, nPoints, BIT_AREA, pnWBuf, nBufSize, CIO_MEMORYWRIT);

	delete [] pnWBuf;

	return nRet;
}  

short CPlcThread::InterpretCIOBitCheck() 
{
	short nPoints = 16; /// 1300.00 ~ 1379.15
	short nRet =0;
	short nBufSize = nPoints *2;
	unsigned short	*pnWBuf = NULL;
	short nAddr;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	for (int i = 0; i < MAX_TOUCHCOUNT_62; i++) 
	{
		for (int j = 0; j < MAXBITCOUNT_16; j++)
		{
			if( m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active == 1 && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_remember == 0 && PollingBit(wTouchInput[i],j )==0 && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_buttype == BUT_MOMENTARY)	  
			{
				nAddr = m_aBitCIO[(i*MAXBITCOUNT_16)+j].szIOName / 100;
				pnWBuf[j]=1;
				nRet = PLC_SendData(nAddr, nPoints, BIT_AREA, pnWBuf, nBufSize,CIO_MEMORYWRIT);

				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_remember = 1;
				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active = 0;
			}
			else if(m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active == 0 &&  PollingBit(wTouchInput[i],j ) >= 1 && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_buttype == BUT_MOMENTARY)	   
			{
				nAddr = m_aBitCIO[(i*MAXBITCOUNT_16)+j].szIOName / 100;
				pnWBuf[j]=0;
				nRet = PLC_SendData(nAddr, nPoints, BIT_AREA, pnWBuf, nBufSize,CIO_MEMORYWRIT);	
				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_remember = 0;
			}
			else if( m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active == 1 && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_buttype == BUT_INVERT)	  
			{
				nAddr = m_aBitCIO[(i*MAXBITCOUNT_16)+j].szIOName / 100;
				BitInvert(nAddr , j, CIO_MEMORYRED, CIO_MEMORYWRIT);
				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active = 0;
				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active = 0;
			}
		}
		for (int i = 0; i < MAXBITCOUNT_16; i++)
		{
			pnWBuf[i] = 0;
		}
	}

	delete [] pnWBuf;

	return nRet;
}		


short CPlcThread::InterpretCIOBitCheckGem() 
{
	short nPoints = 16; /// 1300.00 ~ 1359.15
	short nRet=0;
	short nBufSize = nPoints *2;
	unsigned short	*pnWBuf = NULL;
	short nAddr;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	for (int i = 0; i < MAX_GEMCIOCOUNT_10; i++) 
	{
		for (int j = 0; j < nPoints; j++)
		{
			if( m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_active == 1 && m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_remember == 0 && PollingBit(wTouchCIOGem[i],j )==0 )	  
			{
				nAddr = m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].szIOName / 100;
				pnWBuf[j]=1;
				nRet = PLC_SendData(nAddr, nPoints, BIT_AREA, pnWBuf, nBufSize,CIO_MEMORYWRIT);

				m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_remember = 1;
				m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_active = 0;
			}
			else if(m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_active == 0 &&  PollingBit(wTouchCIOGem[i],j ) >= 1 )	   
			{
				nAddr = m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].szIOName / 100;
				pnWBuf[j]=0;
				nRet = PLC_SendData(nAddr, nPoints, BIT_AREA, pnWBuf, nBufSize,CIO_MEMORYWRIT);	
				m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_remember = 0;
			}

		}

		for(int k=0;k<nPoints;k++)
		{
			pnWBuf[k]=0;
		}
	}

	delete [] pnWBuf;

	return nRet;
}


short CPlcThread::InterpretMotorUpdateCheck() 
{
	int m_DistanceAdd = ADDR_MOTOR_DISTANCE_300, m_SpeedAdd = ADDR_MOTOR_SPEED_350;                                  

	for(int i=0; i< MAXBITCOUNT_16; i++)
	{
		if (mtrpara[i].DistspdActiv == 1)
		{
			InterpretEMSingleWordWrite(m_DistanceAdd + i, mtrpara[i].Distance, 1);
			mtrpara[i].DistspdActiv = 0;
		}
		else if(mtrpara[i].JogSpedActiv == 1)
		{
			InterpretEMSingleWordWrite(m_SpeedAdd + i, long (mtrpara[i].JogSpedMode), 1);
			mtrpara[i].JogSpedActiv = 0;
		}
	}

	for(int i=0; i<MAX_COMBOCOUNTS_12; i++)
	{																	// [0] ~ 
		if (m_ComOpboTable[i].Combo_Active == 1)
		{
			InterpretEMSingleWordWrite(m_ComOpboTable[i].Combo_nAddr, m_ComOpboTable[i].Combo_Value, 1);
			m_ComOpboTable[i].Combo_Active = 0;
		}
	}

	if (Main.ActiveFormNo != Main.CurrentFormNo)
	{
		InterpretEMSingleWordWrite(ADDR_FORMVIEWNUMBER_504, Main.ActiveFormNo, 1);  // FormView No
		if(Main.ActiveFormNo == 1)//m_pCFuncRecipe->UpdateList();
		Main.CurrentFormNo =  Main.ActiveFormNo;
	}

	return TRUE;
}		

short CPlcThread::InterpretEMSingleOcrCharWrite(short nAddr, CString ocrstring, short nPoints) 
{
	// TODO: Add your control notification handler code here

	nPoints = ocrstring.GetLength();
	short nRet = nPoints % 2;
	short	rValue = 0;

	if (nRet == 0) rValue = nPoints / 2;
	else rValue = (nPoints/2)+1;


	unsigned short	*pnWBuf = NULL;
	short	nType = 0;

	long wValue = 0;

	char	*pszSend = NULL;




	pnWBuf = new unsigned short[nPoints + 1];
	pszSend = new char[nPoints + 1];

	memset(pszSend, 0, sizeof(char) * (nPoints + 1));
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);

	pszSend = LPSTR(LPCTSTR (ocrstring));

	StringToAsc(pszSend, pnWBuf, rValue);

	nRet = PLC_SendData(nAddr, rValue, WORD_AREA, pnWBuf, nPoints, EWORD_MEMORY);

	//	delete [] pszSend;

	return nRet;
}
short CPlcThread::InterpretEMWordMotorSpeedRead() 
{
	// TODO: Add your control notification handler code here

	short nAddr = MAX_EMORYMOTORSPEED_300;
	
	short nPoints = MAX_EMORYMOTORSPEEDCOUNT_100 *2; //EMORYMAXCOUNT;

	//	short *pWBuf ;

	short	nRet;
	//	char str[256];
	//	char str2[256];
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	CString m_Value;
	long	nValue = 0;
	double	rValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);
	memcpy(wEmemoryMotorSpeedRead, pnWBuf, nPoints);

	delete [] pnWBuf;

	return nRet;
}

short CPlcThread::InterpretEMWordRead() 
{
	// TODO: Add your control notification handler code here

	short nAddr = ADDR_EMORYSYSTEM_500;
	short nPoints = MAX_EMORYSYSTEMCOUNT_130 *2; //EMORYMAXCOUNT;

	//	short *pWBuf ;

	short	nRet;
	//	char str[256];
	//	char str2[256];
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	CString m_Value;
	long	nValue = 0;
	double	rValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);
	memcpy(wEmemoryRead, pnWBuf, nPoints);

	delete [] pnWBuf;

	return nRet;
}



short CPlcThread::InterpretEMWordMappingRead() 
{
	// TODO: Add your control notification handler code here

	short nAddr = ADDR_MAPEMORY_950;
	short nPoints = MAX_MAPEMORYCOUNT_50 *2; //EMORYMAXCOUNT;

	//	short *pWBuf ;

	short	nRet;
	//	char str[256];
	//	char str2[256];
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	CString m_Value;
	long	nValue = 0;
	double	rValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);
	memcpy(wEmemoryMappingRead, pnWBuf, nPoints);

	delete [] pnWBuf;

	return nRet;
}

short CPlcThread::InterpretEMWordReadMotor() 
{
	// TODO: Add your control notification handler code here

	short nAddr = ADDR_EMORYMOTOR_800;
	short nPoints = MAX_EMORYMOTORCOUNT_100 * 2; //EMORYMAXCOUNT;

	//	short *pWBuf ;

	short	nRet;
	//	char str[256];
	//	char str2[256];
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	CString m_Value;
	long	nValue = 0;
	double	rValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);
	memcpy(wEmemoryReadMotor, pnWBuf, nPoints);

	delete [] pnWBuf;

	return nRet;
}

short CPlcThread::InterpretEMWordGEMRead() 
{
	// TODO: Add your control notification handler code here

	short nAddr = ADDR_GEMEMORY_900;
	short nPoints = MAX_GEMEMORYCOUNT_50 * 2; //EMORYMAXCOUNT;  //Gem Arear

	//	short *pWBuf ;

	short	nRet;
	//	char str[256];
	//	char str2[256];
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	CString m_Value;
	long	nValue = 0;
	double	rValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);
	memcpy(wEmemoryGEMRead, pnWBuf, nPoints);

	delete [] pnWBuf;

	return nRet;
}


short CPlcThread::InterpretEMWordMonitorRead() 
{
	// TODO: Add your control notification handler code here

	short nAddr = ADDR_EMORYDATA_700;
	short nPoints = MAX_EMORYDATACOUNT_100 * 2; //EMORYMAXCOUNT;

	//	short *pWBuf;

	short		nRet;
	//	char str[256];
	//	char str2[256];
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	CString m_Value;
	long	nValue = 0;
	double	rValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);
	memcpy(wEmemoryMonitorRead, pnWBuf, nPoints);

	delete [] pnWBuf;

	return nRet;
}

short CPlcThread::InterpretEMDoubleWordWrite(short nAddr, short nPoints,short nCnt) 
{
	// TODO: Add your control notification handler code here

	short	nRet;
	short nBufSize = nPoints * 4;
	short wPoints = nPoints *2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	long	nValue = 0;
	double	rValue = 0;

	delete [] pnWBuf;
	pnWBuf = new unsigned short[wPoints + 1];		
	memset(pnWBuf, 0, sizeof(unsigned short) * wPoints);
	memcpy(pnWBuf, pnWBuf, wPoints);

	for (int i=0; i < nPoints; i++)
	{
		nValue = (long)atof(wEmomoryWriteArray.GetAt(nCnt));
		pnWBuf[(i*2)+1] = short(nValue / 0x10000);
		pnWBuf[(i*2)+0] = short(nValue - (nValue / 0x10000 * 0x10000));
	}

	nRet = PLC_SendData(nAddr, wPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);

	return nRet;
}

short CPlcThread::InterpretEMSingleWordWrite(short nAddr, long nValue, short nPoints) 
{
	// TODO: Add your control notification handler code here

	short	nRet;
	short nBufSize = nPoints * 2;
	unsigned short	*pnWBuf = NULL;
	short	nType = 0;
	short	rValue = 0;
	long wValue = 0;

	pnWBuf = new unsigned short[nPoints + 1];

	//	delete [] pnWBuf; 

	memset(pnWBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(pnWBuf, pnWBuf, nPoints);

	for (int i=0; i < nPoints; i++)
	{
		pnWBuf[(i*2)+1] = short(nValue / 0x10000);
		pnWBuf[(i*2)+0] = short(nValue - (nValue / 0x10000 * 0x10000));
	}

	nRet = PLC_SendData(nAddr, nPoints, WORD_AREA, pnWBuf, nBufSize, EWORD_MEMORY);

	delete [] pnWBuf;

	return nRet;
}

void CPlcThread::InterpretMotorCurrentPos() 
{
	// TODO: Add your control notification handler code here

	long	nValue = 0;
	double	rValue = 0;

	for (int i=0; i<MAX_MOTORCOUNTS_40; i++)																      //24 축
	{																							  // E400 ~ E447
		nValue = ((long)wEmemoryReadMotor[(i*2)+1] * 0x10000 ) +  ((long)wEmemoryReadMotor[(i*2)]);	  // 400번 부터 E447번 까지 모터 현재 위치
		mtrpara[i].current_pos = (double)nValue/100;
	}
}

void CPlcThread::InterpretMonitorDataRead() 
{
	// TODO: Add your control notification handler code here

	long	nValue = 0;
	double	rValue = 0;

	for (int i=0; i<MAX_EMORYDATADOUBLECOUNT_25; i++)																      // E800 ~ 850
	{																							  
		nValue = ((long)wEmemoryMonitorRead[(i*2)+1] * 0x10000 ) + ((long)wEmemoryMonitorRead[(i*2)]);	  // 0번 부터 	50번 까지  읽어 오기
		EmonitorDataDouble[i] = (double)nValue;
	}
}

short CPlcThread::BitSetReset(short nAddr, short bitno, short onoff) 
{
	// TODO: Add your control notification handler code here 
	/////////////////////////////
	////////// IN/OUT AREAR 

	short nPoints = 1; /// 1300.00 ~ 1359.15
	//	short nAddr = 1200;
	short	nRet;
	short nBufSize = nPoints *2;
	unsigned short	*psRBuf = NULL;

	psRBuf = new unsigned short[nPoints];		
	memset(psRBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(psRBuf, psRBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize,EWORD_MEMORY);

	if(!nRet)                                   
	{
		if(onoff)
		{
			bitno = 0x0001 << (bitno);					  // 비트 온 
			psRBuf[0] = psRBuf[0] | bitno;
		} 
		else  
		{
			bitno = ~(0x0001 << (bitno));				 // 비트 오프
			psRBuf[0] = psRBuf[0] & bitno;
		}
		nRet = PLC_SendData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, EWORD_MEMORY);
	}

	delete [] psRBuf;

	return nRet;
}		

short CPlcThread::InterpretBitInvertCheck() 
{


	for (int i=0; i<MAX_INVERTCOUNTS_7; i++)
	{
		for (int j=0; j<MAXBITCOUNT_16; j++)
		{
			if(InvertButton[(i*MAXBITCOUNT_16)+j].bitActive == 1)
			{
				BitInvert(InvertButton[(i*MAXBITCOUNT_16)+j].nAddr, InvertButton[(i*MAXBITCOUNT_16)+j].bitno, EWORD_MEMORY, EWORD_MEMORY);	  //E148 Invert Add ~ E154까지
				InvertButton[(i*MAXBITCOUNT_16)+j].bitActive = 0;
			}
		}
	}

	return TRUE;
}

short CPlcThread::BitInvert(short nAddr, short bitno, BYTE rPlcType, BYTE wPlcType) 
{
	// TODO: Add your control notification handler code here 
	/////////////////////////////
	////////// IN/OUT AREAR 

	short nPoints = 1; /// 1300.00 ~ 1359.15
	//	short nAddr =  1200;
	short	nRet;
	short nBufSize = nPoints *2;
	unsigned short	*psRBuf = NULL;

	psRBuf = new unsigned short[nPoints];		
	memset(psRBuf, 0, sizeof(unsigned short) * nPoints);
	memcpy(psRBuf, psRBuf, nPoints);

	nRet = PLC_ReceiveData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, rPlcType);

	if(!nRet)                                   
	{
		bitno = 0x0001 << (bitno);	   // 비트 반전 
		psRBuf[0] = psRBuf[0] ^ bitno;

		nRet = PLC_SendData(nAddr, nPoints, WORD_AREA, psRBuf, nBufSize, rPlcType);
	}

	delete [] psRBuf;

	return nRet;
}		



void CPlcThread::InterpretAlarm()
{
	int	nAddr = 0;
	short	nPoints = 0;
	short	nPosition = 0;
	int		nAlarmID = 0;
	int     nActiveNo = 0;
	CString	strnId;

//	m_nErrorDialogView = 0;
	////// Alarm ////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i=0; i<MAX_ALARMCOUNT_59; i++)				  /// Error Check CIO Max 40 ea
	{
		for( int j=0; j<MAXBITCOUNT_16; j++ ) 
		{
			nActiveNo = (i*MAXBITCOUNT_16) + j;
			nAddr = (ADDR_ALARMSTART_40000 +(i*100)) + j;					 // Start Addr
			nPosition = j;
			if(m_aAlarm[nActiveNo].m_nBackup == 0 && PollingBit(wAlarmInput[i], j) > 0) 
			{
				// PM Alarm Set
				// strnId.Format("%d",nAddr);
				strnId.Format("%d",m_aAlarm[nActiveNo].m_nId);
				m_aAlarm[nActiveNo].m_nBackup = 1;
//				theApp.AddAlarmLog(strnId, m_aAlarm[nActiveNo].m_szText, nActiveNo);

				if(nAddr == 41500 || nAddr == 41501|| nAddr == 41502)
				{
//					m_nErrorDialogView = 1;  // WAFER ID Read Error
//					bErrDialogSelect = TRUE;
				}
				//		else if(nAddr == 40103 || nAddr == 40104)
				//				{
				//				m_nErrorDialogView = 2;  // Panel 2D Read Error
				//				bErrDialogSelect = TRUE;
				//			}
				else if(nAddr == 41114 )
				{
//					m_nErrorDialogView = 3;  // In Foup1 RFID Read Error
//					bErrDialogSelect = TRUE;
				}
				else if(nAddr == 41115 )
				{
//					m_nErrorDialogView = 4;  // OutFoup2 RFID Read Error
	//				bErrDialogSelect = TRUE;
				}
				else if(nAddr == 41204 )
				{
//					m_nErrorDialogView = 5;  // OutFoup3 RFID Read Error
//					bErrDialogSelect = TRUE;
				}else if(nAddr == 41205 )
				{
//					m_nErrorDialogView = 6;  // OutFoup4 RFID Read Error
//					bErrDialogSelect = TRUE;
				}else if(nAddr == 41003 || nAddr == 41004  )
				{
					CString strSlot,strPort;
/*
					m_pCFunGem->m_gem.SetCurrentStatusValue( SVID_OUTOUT_CASSETTE_SLOT_CHECK_ERROR_SLOTNO , Main.strHostSlot);
					m_pCFunGem->m_gem.SetCurrentStatusValue( SVID_OUTOUT_CASSETTE_SLOT_CHECK_ERROR_PORTNO , Main.strHostPort);
					m_pCFunGem->SendEventReport( CEID_WAFER_OUTPUT_CASSETTE_SLOT_CHECK_ERROR );*/
				}

				//SendMessage(WM_ALARM_HISTORY_ADDED, 0, 0);
/*				m_pDialogWaferIDError->AddLog( " ["+strnId+"] "+ m_aAlarm[nActiveNo].m_szText +" ");
				m_pDialogErrorDisplay->AddLog( " ["+strnId+"] "+ m_aAlarm[nActiveNo].m_szText +" ");*/


				//	bErrShow = FALSE;

				if(m_GemReportTable.m_bStarted)
				{
					CString strTemp;
					strTemp.Format("%ld", nAddr);
//					m_pCFunGem->OnSendAlarmSet((long) nAddr);
				}
			}
			// PM Alarm Reset
			else if(m_aAlarm[nActiveNo].m_nBackup == 1 && PollingBit(wAlarmInput[i], j) == 0) 
			{

			}
		}	
	}
}

void CPlcThread::AlarmBitClear()
{
	int	nAddr = 0;
	short	nPoints = 0;
	short	nPosition = 0;
	int		nAlarmID = 0;
	int     nActiveNo = 0;
	CString	strnId;
	//short   nTestAdd =4248;

	////// Alarm ////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i=0; i<MAX_ALARMCOUNT_59; i++)				  /// Error Check CIO Max 40 ea
	{
		for( int j=0; j<MAXBITCOUNT_16; j++ ) 
		{
			nActiveNo = (i*MAXBITCOUNT_16) + j;
			nAddr  = (ADDR_ALARMSTART_40000 + (i*100)) + j;					 // Start Addr
			nPosition = j;

			// Alarm Reset 
			if(m_aAlarm[nActiveNo].m_nBackup == 1) 
			{
				/// GEM Alarm Report
				CString strTemp;
				//nAddr = nTestAdd;
				strTemp.Format("%ld", nAddr);
				if(m_GemReportTable.m_bStarted)
				{
//					m_pCFunGem->OnSendAlarmReset((long)nAddr);
				}
			}
			m_aAlarm[nActiveNo].m_nBackup = 0;
			/// Gem Alarm Report
		}	
	}

}  

void CPlcThread::InterpretOperator()
{
	short	nAddr = 0;
	short	nPoints = 0;
	short	nPosition = 0;
	int		nAlarmID = 0;
	int     nActiveNo = 0;
	CString	strnId;

	////// Alarm ////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i=0; i<MAX_TOUCHCOUNT_62; i++)				  /// Button Check CIO Max 60 ea
	{
		for( int j=0; j<MAXBITCOUNT_16; j++ ) 
		{
			nActiveNo = (i*MAXBITCOUNT_16) + j;
			nAddr  = (ADDR_CIOTOUCHSTART_100000 +(i*100)) + j;					 // Start Addr
			nPosition = j;
			if(m_aOperation[nActiveNo].m_nBackup == 0 && PollingBit(wTouchInput[i], j) > 0) 
			{
				// PM Alarm Set
				///	strnId.Format("%d",nAddr);
				strnId.Format("%d",m_aOperation[nActiveNo].m_nId);
				m_aOperation[nActiveNo].m_nBackup = 1;
//				theApp.AddOperatorLog(strnId, m_aOperation[nActiveNo].m_szText);
				//m_pCFormCheckErrLog->SendMessage(WM_ALARM_HISTORY_ADDED, 0, 0);
			}
			// PM Alarm Reset
			else if(m_aOperation[nActiveNo].m_nBackup == 1 && PollingBit(wTouchInput[i], j) == 0) 
			{
				// Alarm Reset 
				m_aOperation[nActiveNo].m_nBackup = 0;
			}
		}	
	}
}
