// Global.cpp: implementation of the CGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "framework.h"
#include "CUON.h"
#include "Global.h"
#include "MainFrm.h"
#include "CUONDoc.h"
#include "CUONView.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL   BlinkFlag;

int    InitStartFlag; 
int    IsInitProc[NMBOFMTR]; 
int    IsInitComp[NMBOFMTR];
int    IsMotorRun[NMBOFMTR]; 
int    IsInitComplete;
int    LastErrorCode;
int    LastErrorNo;


BOOL m_AlarmActive;
BOOL m_MappingActive;
BOOL ErrorDisplayActive;
BOOL m_InspectActive;
BOOL m_RingCheckActive;
BOOL m_OutJarActive;


int    m_nHomeStep[NMBOFMTR];
BOOL   m_bHomeSearch[NMBOFMTR]; 
double m_dHomeVel1[NMBOFMTR];
double m_dHomeVel2[NMBOFMTR];
double m_dHomeVel3[NMBOFMTR];
BOOL   m_bIsDelayOn;
int	   m_nStep;
int	   m_nDelay;
int	   m_nSetDelay;
int    m_MonitorNo;
 
BOOL  RBtn;
BYTE  bInput;
BYTE  bOutput;

//=========================================================

WORD  wInOutput[MAX_IOCOUNT_48 * 2];
WORD  wTouchInput[MAX_TOUCHCOUNT_62 * 2];
WORD  wEmemoryRead[MAX_EMORYSYSTEMCOUNT_130 * 2];
WORD  wEmemoryMotorSpeedRead[MAX_EMORYMOTORSPEEDCOUNT_100 * 2];
WORD  wEmemoryMonitorRead[MAX_EMORYDATACOUNT_100 * 2];
double EmonitorDataDouble[MAX_EMORYDATADOUBLECOUNT_25 * 2];

WORD  wEmemoryReadMotor[MAX_EMORYMOTORCOUNT_100 * 2];
//=======================================================

WORD  wEmemoryMappingRead[MAX_MAPEMORYCOUNT_50 * 2];
WORD  wEmemoryGEMRead[MAX_GEMEMORYCOUNT_50 * 2];
WORD  wTouchCIOGem[MAX_GEMCIOCOUNT_10 * 2];

WORD  wAlarmInput[MAX_ALARMCOUNT_59];


//=======================================================

CString m_ComOp2Data[4];
CString m_strCom2Data[4];

CString m_ComOp3Data[4];
CString m_strCom3Data[4];

CString m_ComOp4Data[4];
CString m_strCom4Data[4];

CString m_ComOp5Data[4];
CString m_strCom5Data[4];

CString m_ComOp6Data[4];
CString m_strCom6Data[4];

CString m_ComOp7Data[4];
CString m_strCom7Data[4];

CString m_ComOp12Data[4];
CString m_strCom12Data[4];

CString m_ComOpData[MAX_COMPORTS_15];
CString m_strComData[MAX_COMPORTS_15];
_GetCom m_GetCom[MAX_COMPORTS_15];



CStringArray wEmomoryWriteArray;
CStringArray wEmomoryMap1WriteArray;
CStringArray wEmomoryMap2WriteArray;


int   onoff[NUMOFSOL];



_ComboTable  m_ComOpboTable[MAX_COMBOCOUNTS_12];

_tprintFormat     m_printFormat[MAX_OCRCNTS];
_tBitCIOTable	  m_aBitCIO[MAX_BITIOS_992];
_tBitCIOTable	  m_aBitCIOGem[MAX_GEMBITIOS_160];
_tAlarm		  m_aAlarm[MAX_ALARMS_944];
_tOperation	  m_aOperation[MAX_BITIOS_992];


_Invert_Button InvertButton[MAX_INVERTBITCOUNTS_112];
MtrPara mtrpara[MAX_MOTORCOUNTS_40];

CStringArray m_RobotDataArray;

_MainVariable Main;
_GetTempValue m_GetTempValue;
_RecipeTable  m_RecipeTable;
_UserTable  m_UserTable;
_ConfigTable  m_ConfigTable;
_MotorTable  m_MotorTable[MAX_MOTORCOUNTS_40];
_tStartInfo 	m_StartInfo;
_SystemINI SystemINIFiles;
_GemReportTable  m_GemReportTable;
_LimitTable  m_LimitTable;
_GemLogConfig  m_GemLogConfig;
_GetDiscoInterface m_GetDiscoInterface;

_GetOCR m_GetOCR;
_MapFileFormatInfor m_GetmapFileFormat;
_GetWaferID m_GetWaferID1[MAX_OCRIDCNTS_100];
_GetWaferID m_GetWaferID2[MAX_OCRIDCNTS_100];
_GetWaferID m_GetWaferID3[MAX_OCRIDCNTS_100];
_GetWaferID m_GetWaferID4[MAX_OCRIDCNTS_100];


_GemSquenceInfor m_GemEvent[MAX_GEMEMORYCOUNT_50];
_FoupTable m_FoupTable[MAX_FOUPCNTS_5];



CGlobal::CGlobal()
{
}

CGlobal::~CGlobal()
{

}

BOOL CGlobal::Serialization(CArchive &ar)
{
	return true;
}



void CGlobal::DoEvent () {
    MSG msg;
    GetMessage(&msg, NULL , 0, 0);
    TranslateMessage (&msg);
    DispatchMessage (&msg);
}

int  Mouse_Line_CMove(double pos_x, double pos_y, double speed, double accel) 
{

    //map_axes(2, AX2);
	//set_move_speed (speed);
	//set_move_accel (accel);

    //start_point_list();
    //move_2(pos_x, pos_y);
    //end_point_list ();
	//start_motion();
//    CFS20start_r_move(1, pos_x, speed, accel);	// 2008-09-01

    return (1);
}

BOOL RegReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpName, LPTSTR lpValue, DWORD nSize)
{
    HKEY key;
    DWORD dwDisp;
    DWORD Size;
    if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
		
		REG_OPTION_NON_VOLATILE, KEY_READ, NULL, 
		&key, &dwDisp ) != ERROR_SUCCESS )
		return FALSE;
    Size = nSize;
    if( RegQueryValueEx( key, lpName, 0, NULL, (LPBYTE)lpValue, &Size ) != ERROR_SUCCESS )
    {
        return FALSE;
    }
    RegCloseKey( key );
    return TRUE;
} 

BOOL RegWriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpName, LPCTSTR lpValue)
{
    HKEY key;
    DWORD dwDisp;
    if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
		
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, 
		
		&key, &dwDisp ) != ERROR_SUCCESS )
		
		return FALSE;
	
    if( RegSetValueEx(key,lpName,0, REG_EXPAND_SZ, (LPBYTE) lpValue, (DWORD)lstrlen(lpValue)) != ERROR_SUCCESS)
    {
        return FALSE;
    }
    RegCloseKey( key );
    return TRUE;
} 


int GetNumberCheck(CString name)
{
	char ch;
	int m_namecnt=0,m_jumcnt=0,m_numcnt=0,m_miuscnt=0;
	m_namecnt = name.GetLength();
	for(int i=0 ; i< m_namecnt;i++)
	{
		ch = name.GetAt(i) ;
		if(m_jumcnt != 0) m_numcnt++;
		if(GetCharToNbrValue (ch) == 2) m_jumcnt ++;
		if(GetCharToNbrValue (ch) == 3) m_miuscnt ++;
		if(GetCharToNbrValue (ch) == TRUE || m_numcnt >4 || m_jumcnt>1 || m_miuscnt >1)	return TRUE;
	}
	return FALSE ;
}



int GetCharToNbrValue (char ch) 
{
	
	switch (ch) {
	   case '0':
		   return FALSE;
		   break;
	   case '1':
		   return FALSE;
		   break;
	   case '2':
		   return FALSE;
		   break;
	   case '3':
		   return FALSE;
		   break;
	   case '4':
		   return FALSE;
		   break;
	   case '5':
		   return FALSE;
		   break;
	   case '6':
		   return FALSE;
		   break;
	   case '7':
		   return FALSE;
		   break;
	   case '8':
		   return FALSE;
		   break;
	   case '9':
	   case ' ':
		   return FALSE;
		   break;
	   case '.':
	   		   return 2;
		   break;
	   case '-':
	   		   return 3;
		   break;
	   default:
		   break;
	}
	return TRUE;
}




void AscToString(char *pszOut, unsigned short *pnaBuf, short nPoints)
{
	int i=0;
	for (i = 0; i < nPoints; i++) {
		pszOut[(i * 2) + 0] = (unsigned)pnaBuf[i] / 0x100;
		pszOut[(i * 2) + 1] = (unsigned)pnaBuf[i] - ((pnaBuf[i] / 0x100 * 0x100));
	}
	pszOut[(i * 2) + 0] = '\0';
}

void StringToAsc(char *pszBuf, unsigned short *pnaBuf, short nPoints)
{
	short	i = 0;
	
	for (i = 0; i < nPoints; i++) {
		pnaBuf[i] = pszBuf[(i * 2) + 0] * 0x0100 + pszBuf[(i * 2) + 1];
	}
}



void GetDigitTypeRead(short nAdd,short nPoints,short nType,short nSize,short nKind)
{
//	short	nStart;
	short	nBufSize = 0;
	short	nCount = 0;
	short	nTotal = 0;
	
	int		nNum = 0;
	double	rValue = 0;
	long    nValue =0;
	long	nDigit = 0;
	char	szFormat[256];

	unsigned short	*psRBuf = NULL;
	char	*pszRead = NULL;

	nBufSize = nPoints * 2;
	
	psRBuf = new unsigned short[nBufSize];
	memset(psRBuf, 0, sizeof(short) * nBufSize);
	
	pszRead = new char[nBufSize + 1];
	memset(pszRead, 0, sizeof(char) * (nBufSize + 1));
	pszRead[nBufSize] = '\0';


	switch (nType) {
	case DATA_FORMAT_ASCII:
		AscToString(pszRead,psRBuf , nSize);
		break;
		
	case DATA_FORMAT_BIN:
	case DATA_FORMAT_I1:
	case DATA_FORMAT_I2:
	case DATA_FORMAT_U1:
	case DATA_FORMAT_U2:
		if (nSize != 1) { /*	Error	*/ break; }
		nValue = psRBuf[nNum];
		sprintf_s(szFormat, "%d", nValue);
		break;
		
	case DATA_FORMAT_I4:
	case DATA_FORMAT_U4:
		if (nSize != 2) { /*	Error	*/ break; }
		nValue = (unsigned)psRBuf[nNum + 1] * 0x10000 +	(unsigned)psRBuf[nNum + 0];
		
		sprintf(szFormat, "%d", nValue);
		break;
		
	case DATA_FORMAT_F4:
	case DATA_FORMAT_F8:
		nValue = (unsigned)psRBuf[nNum + 1] * 0x10000 +
			(unsigned)psRBuf[nNum + 0];
		
		//rValue = (double)nValue / m_pOwner->m_pDataMan->m_aFormat[nStartHost + j].m_nKind;
		nDigit = GetDigitByDec(nKind);
		if (nDigit != 0) { sprintf(szFormat, "%c.%df", 0x25, nDigit); }
		if (nDigit == 0) { sprintf(szFormat, "%cf", 0x25); }
		//sprintf(m_pOwner->m_pDataMan->m_aWordIO[nStartHost + j].m_szValue, szFormat, rValue);
		
		rValue = (double)nValue / nKind;
		sprintf(szFormat, "%d", rValue);
		break;
		
	default:;
				}
	
}

short GetDigitByDec(short nSource)
{
	short	nDigit = 0;
	short	nValue = 0;
	nValue = nSource;
	do {
		nValue /= 10;
		nDigit += 1;
	} while (nValue > 0);
	return nDigit - 1;
}


short SetCIOBit(BOOL Addr)
{
	short	nDigit = 0;
	short	nValue = 0;
	nDigit = Addr /100;
	nValue = Addr % 100;
	for (int i = 0; i<MAX_TOUCHCOUNT_62; i++) 
	{
		for (int j = 0; j<MAXBITCOUNT_16; j++)
		{
			if(Addr == m_aBitCIO[(i*MAXBITCOUNT_16)+j].szIOName && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_remember == 0 && PollingBit(wTouchInput[i], j) == 0 && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_buttype == BUT_MOMENTARY)
			{
				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active = 1;
			}
			else if(Addr == m_aBitCIO[(i*MAXBITCOUNT_16)+j].szIOName && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_remember == 0 && m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_buttype == BUT_INVERT)
			{
				m_aBitCIO[(i*MAXBITCOUNT_16)+j].m_active = 1;
			}	
		}
	}
	return nDigit - 1;
}


short SetCIOBitGem(BOOL Addr)
{
	short	nDigit = 0;
	short	nValue = 0;
	nDigit = Addr /100;
	nValue = Addr % 100;
	for (int i = 0; i< MAX_GEMCIOCOUNT_10; i++) 
	{
		for (int j = 0; j< MAXBITCOUNT_16; j++)
		{
			if(Addr == m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].szIOName && m_aBitCIOGem[(i* MAXBITCOUNT_16)+j].m_remember == 0 && PollingBit(wTouchCIOGem[i], j) == 0 )
			{
				m_aBitCIOGem[(i*16)+j].m_active = 1;
			}
			
		}
	}
	return nDigit - 1;
}

CString GetStringToData(CString nData, int nType)
{
	double rValue;
	long   nValue;
	CString strTmp;

	rValue = (double)(atof(nData));
	nValue = (long)(rValue * nType);
	strTmp.Format("%d", nValue) ;
	return strTmp;
}	   
void WriteComportSettingFile(CString strPort, CString strSlotNo, CString strWaferID)
{
	CString strPath;
	strPath = "..\\..\\DATA\\SYSTEMFILES\\COMPORT_SETTING.ini";
	WritePrivateProfileString(strPort, strSlotNo, strWaferID, strPath);
}


CString ReadComportSettingFile(CString strPort, CString strSlotNo)
{
	char  szValue[0xFF];
	CString strPath;
	strPath = "..\\..\\DATA\\SYSTEMFILES\\COMPORT_SETTING.ini";
	CString strReturn = _T("");

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(strPort, strSlotNo, "", szValue, sizeof(szValue), strPath))
		strReturn = szValue;

	return strReturn;
}

void WriteWaferIDListFile(CString strPort,CString strSlotNo,CString strWaferID)
{
	CString strPath;
	strPath = "\\SYSTEMFILES\\WAFERID_LIST.INI";
	WritePrivateProfileString(strPort, strSlotNo,strWaferID,strPath);
}


CString ReadWaferIDListFile(CString strPort,CString strSlotNo)
{
	char  szValue[0xFF];
	CString strPath;
	strPath = "..\\DATA\\SYSTEMFILES\\WAFERID_LIST.INI";
	CString strReturn = _T("");

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(strPort, strSlotNo,"",szValue,sizeof(szValue), strPath))
		strReturn = szValue;
	
	return strReturn;
}

void WriteSetRecipeFile(CString strPort,CString strSlotNo,CString strData)
{
	// strPort =  PORT1 or PORT2
	// strSlotNo = S1,S2....
	// strWaerID = "WAFERID"
	char szCurrentPath[1024];//, szValue[0xFF];
	GetCurrentDirectory(1024, szCurrentPath);
	CString strPath = szCurrentPath;
	strPath += "\\SYSTEMFILES\\HOST_RECIPE.INI";
	
	WritePrivateProfileString(strPort, strSlotNo,strData,strPath);

}


CString ReadSetRecipeFile(CString strPort,CString strSlotNo)
{
	// strPort =  PORT1 or PORT2
	// strSlotNo = S1,S2....

	// strReturn = "WAFERID"

	char szCurrentPath[1024], szValue[0xFF];
	GetCurrentDirectory(1024, szCurrentPath);
	CString strPath = szCurrentPath;
	strPath += "\\SYSTEMFILES\\HOST_RECIPE.INI";
	CString strReturn = _T("");

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(strPort, strSlotNo,"",szValue,sizeof(szValue), strPath))
		strReturn = szValue;
	
	return strReturn;
}

CString GetFilePath(void)
{
	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof path);
	CString strPath = path;
	int i = strPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.
	strPath = strPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.
	return strPath;
}
///////////////////////////////////////레시피 관련 글로벌 함수 ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CString gReadRecipeFile(CString strParameter, CString strData, CString mRecipeName)								///////
{
	char  szValue[0xFF];
	CString strPath;
	CString strReturn = _T("");
	strPath = "..\\..\\DATA\\RECIPE\\"+ mRecipeName+".INI";

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(strParameter, strData, "", szValue, sizeof(szValue), strPath))
		strReturn = szValue;
	return strReturn;
}

void gWriteRecipeFile(CString strParameter, CString strData, CString strValue, CString mRecipeName)
{
	char szCurrentPath[1024];//, szValue[0xFF];
	GetCurrentDirectory(1024, szCurrentPath);
	CString strPath = szCurrentPath;
	strPath = "..\\..\\DATA\\RECIPE\\" + mRecipeName + ".INI";
	WritePrivateProfileString(strParameter, strData, strValue, strPath);
}

void gRecipeFileLoad(CString strRcpName)
{
	CString strPath;
	strPath = "..\\..\\DATA\\RECIPE\\" + strRcpName + ".INI";
	char SectionBuffer[256];
	int l = 0;
	int nSize = 256;
	short nmCnt = 0;

	GetPrivateProfileSectionNames(SectionBuffer, 256, strPath);
	for (int i = 0; i < nSize; ++i)
	{
		if (SectionBuffer[i] == '\0')
		{
			if (i > l)
			{
				m_RecipeTable.strParaName[nmCnt] = &SectionBuffer[l];
				m_RecipeTable.Data[nmCnt] = gReadRecipeFile(m_RecipeTable.strParaName[nmCnt], "DATA", strRcpName);
				m_RecipeTable.strType[nmCnt] = gReadRecipeFile(m_RecipeTable.strParaName[nmCnt], "DATA_TYPE", strRcpName);
				m_RecipeTable.strAdress[nmCnt] = gReadRecipeFile(m_RecipeTable.strParaName[nmCnt], "E_ADRESS", strRcpName);
				m_RecipeTable.strEvalue[nmCnt] = gReadRecipeFile(m_RecipeTable.strParaName[nmCnt], "E_VALUE", strRcpName);
				m_RecipeTable.strMin[nmCnt] = gReadRecipeFile(m_RecipeTable.strParaName[nmCnt], "MIN", strRcpName);
				m_RecipeTable.strMax[nmCnt] = gReadRecipeFile(m_RecipeTable.strParaName[nmCnt], "MAX", strRcpName);
				nmCnt++;
				
			}
			else if (i == l)  // 2 zeros detected
				break;
			l = i + 1;
		}
	}
	m_RecipeTable.nRcpParaCnt = nmCnt;
	
}
void gRecipeLoad()
{
	int mnCnt = 0;
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	char path[255];
	CString strRcpName;

	strcpy(path, "..\\..\\DATA\\RECIPE\\*.ini*");

	hFind = FindFirstFile((LPCSTR)path, &FindData);
	if (hFind == INVALID_HANDLE_VALUE)
		return;

	do {
		printf("%s", FindData.cFileName);
		PathRemoveExtension(FindData.cFileName);
		m_RecipeTable.strRcpName[mnCnt] = FindData.cFileName;
		mnCnt++;
		
	} while (FindNextFile(hFind, &FindData));

	FindClose(hFind);
	m_RecipeTable.nRcpCnt = mnCnt;

}

void gRecipeFileChange(CString strRcpName)
{
	CString strData;
	wEmomoryWriteArray.RemoveAll();
	RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_NAME", strRcpName);
	RegWriteString(HKEY_CURRENT_USER, REGISTRY_KEY, "CURRENT_RECIPE_SIZE", m_RecipeTable.Data[0]);
	m_RecipeTable.Name = strRcpName;
	m_RecipeTable.WaferSize = m_RecipeTable.Data[0];
	for (int j = 0; j < m_RecipeTable.nRcpParaCnt; j++)
	{
		strData = m_RecipeTable.Data[j];
		if (m_RecipeTable.strType[j] != "VALUE")wEmomoryWriteArray.Add(GetStringToData(ContentsSorting(m_RecipeTable.strType[j], strData), atoi(m_RecipeTable.strEvalue[j])));
		else if (m_RecipeTable.strType[j] == "VALUE")wEmomoryWriteArray.Add(GetStringToData(strData, atoi(m_RecipeTable.strEvalue[j])));
	}
	Main.EMemoryWrite = RECIPE_WRITE;
	Main.EMemoryWriteCount = m_RecipeTable.nRcpParaCnt;
}
CString ContentsSorting(CString strContents, CString strCompare)
{
	CString strReturn;
	CString strSort;
	int i = 0;

	while (AfxExtractSubString(strSort, strContents, i, ','))
	{
		if (strSort == strCompare) strReturn.Format("%d", i);  
		i++;
	}
	return strReturn;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RecipeCreate(CString mRecipeName )
{
}
void RecipeDelete(CString mRecipeName )
{
}

///
///////////////////////////////////////모터 관련 글로벌 함수 ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CString gReadMotorFile(CString strParameter, CString strData, CString mMotorNo)								///////
{
	char  szValue[0xFF];
	CString strPath;
	CString strReturn = _T("");
	strPath = "..\\..\\DATA\\MOTOR\\" + mMotorNo + ".INI";

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(strParameter, strData, "", szValue, sizeof(szValue), strPath))
		strReturn = szValue;
	return strReturn;
}

void gWriteMotorFile(CString strParameter, CString strData, CString strValue, CString mMotorNo)
{
	char szCurrentPath[1024];//, szValue[0xFF];
	GetCurrentDirectory(1024, szCurrentPath);
	CString strPath = szCurrentPath;
	strPath = "..\\..\\DATA\\MOTOR\\" + mMotorNo + ".INI";
	WritePrivateProfileString(strParameter, strData, strValue, strPath);
}

void gMotorFileLoad(CString strMotorNo)
{
	CString strPath, strTemp,strData;
	strPath = "..\\..\\DATA\\MOTOR\\" + strMotorNo + ".INI";
	char SectionBuffer[256];
	int l = 0;
	int nSize = 256;
	short nmCnt = 0;
	int nMotorNo = 0;
	strTemp = strMotorNo;
	strTemp.Replace("M", "");
	nMotorNo = atoi(strTemp) -1;
	Main.nCurrentMotorNo = nMotorNo;
	GetPrivateProfileSectionNames(SectionBuffer, 256, strPath);

	strData = m_RecipeTable.WaferSize;

	for (int i = 0; i < nSize; ++i)
	{
		if (SectionBuffer[i] == '\0')
		{
			if (i > l)
			{
				m_MotorTable[nMotorNo].strParaName[nmCnt] = &SectionBuffer[l];
				m_MotorTable[nMotorNo].Data[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], strData, strMotorNo);
				m_MotorTable[nMotorNo].strType[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], "DATA_TYPE", strMotorNo);
				m_MotorTable[nMotorNo].strCioBit[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], "CIOBIT", strMotorNo);
				m_MotorTable[nMotorNo].strAdress[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], "E_ADRESS", strMotorNo);
				m_MotorTable[nMotorNo].strEvalue[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], "E_VALUE", strMotorNo);
				m_MotorTable[nMotorNo].strMin[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], "MIN", strMotorNo);
				m_MotorTable[nMotorNo].strMax[nmCnt] = gReadMotorFile(m_MotorTable[nMotorNo].strParaName[nmCnt], "MAX", strMotorNo);
				nmCnt++;
			}
			else if (i == l)  // 2 zeros detected
				break;
			l = i + 1;
		}
	}
	m_MotorTable[nMotorNo].nMotorParaCnt = nmCnt;



}
void gMotorLoad()
{
	CString strMotorNo, strMotorJog, strMotorBit, strMotorName,strSort;
	CString strPath="MOTOR_INFORMATION";
	short nCnt = 0;
	int i = 0;
	int j = 0;

	while (AfxExtractSubString(strSort, m_RecipeTable.strType[0], j, ','))
	{
		Main.strWaferSize[j] = strSort;
		j++;
	}
	Main.nWaferSizeCnt = j;

	for (i = 0; i < 40; i++)
	{
		strMotorNo.Format("M%d", i+1);
		strMotorName = gReadMotorFile("MOTOR_NAME", strMotorNo, strPath);
		strMotorJog = gReadMotorFile("MOTOR_JOG", strMotorNo, strPath);
		strMotorBit = gReadMotorFile("MOTOR_BIT", strMotorNo, strPath);
		if (strMotorName != "")nCnt++;
		m_MotorTable[i].strMotorName = strMotorName;
		m_MotorTable[i].strJog = strMotorJog;
		m_MotorTable[i].strBit = strMotorBit;
	}
	Main.nMotorCnt = nCnt;
}

void gMotorFileSave(CString strMotorNo)
{
	CString strData, strTemp;
	short nMotorNo = 0;
	strTemp = strMotorNo;
	strTemp.Replace("M", "");
	nMotorNo = atoi(strTemp) - 1;
	Main.nCurrentMotorNo = nMotorNo;
	wEmomoryWriteArray.RemoveAll();

	for (int j = 0; j < m_MotorTable[nMotorNo].nMotorParaCnt; j++)
	{
		strData = m_MotorTable[nMotorNo].Data[j];
		wEmomoryWriteArray.Add(GetStringToData(strData, atoi(m_MotorTable[nMotorNo].strEvalue[j])));
	}
	Main.EMemoryWrite = MOTOR_WRITE;
	Main.EMemoryWriteCount = m_MotorTable[nMotorNo].nMotorParaCnt;
}

///////////////////////////////////////인터페이스 관련 글로벌 함수 ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CString gReadInterfaceFile(CString strParameter, CString strData)								///////
{
	char  szValue[0xFF];
	CString strPath;
	CString strReturn = _T("");
	strPath = "..\\..\\DATA\\INTERFACE\\INTERFACE.INI";

	ZeroMemory(szValue, 0xFF);
	if (GetPrivateProfileString(strParameter, strData, "", szValue, sizeof(szValue), strPath))
		strReturn = szValue;
	return strReturn;
}

void gWriteInterfaceFile(CString strParameter, CString strData, CString strValue)
{
	char szCurrentPath[1024];//, szValue[0xFF];
	GetCurrentDirectory(1024, szCurrentPath);
	CString strPath = szCurrentPath;
	strPath = "..\\..\\DATA\\INTERFACE\\INTERFACE.INI";
	WritePrivateProfileString(strParameter, strData, strValue, strPath);
}