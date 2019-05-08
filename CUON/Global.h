// Global.h: interface for the CGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_H__C59FFD91_3DFA_4D46_A337_C6323DD9807D__INCLUDED_)
#define AFX_GLOBAL_H__C59FFD91_3DFA_4D46_A337_C6323DD9807D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"



/*========================================================================================
ERROR CODES
========================================================================================*/
//	Base error code
#ifndef RV_SUCCESS
#define RV_SUCCESS			0				//	Success!
#endif	//	RV_SUCCESS
#ifndef ERS_NO_ERR
#define ERS_NO_ERR			RV_SUCCESS		//	No error
#endif	//	ERS_NO_ERR
#ifndef ERS_
#define ERS_				-20000			//	Base error
#define ERS_BEGIN_THREAD	(ERS_ - 1)		//	Fail on begin thread
#define ERS_SOCK_OPEN		(ERS_ - 2)		//	Socket is not opened
#define ERS_SOCK_CLOSE		(ERS_ - 3)		//	Socket is not closed
#define ERS_SOCKET			(ERS_ - 4)
#define	ERS_TIMEOUT			(ERS_ - 5)
#endif	//	ERS_
#ifndef FINS_
#define FINS_				-30000
#define	FINS_CONN_ERR		(FINS_ - 1)
#define FINS_TCP_RECIPE_ERR	(FINS_ - 2)		// TCP Receive Error
#define FINS_COMMAND_ERR	(FINS_ - 3)		// Illegal Command Error
#endif





#define EHI_NO_ERR			RV_SUCCESS		//	No error
#define EHI_				-30000			//	Base error

#define EHI_READ_START_INFO		(EHI_ - 1)	//	Fail to read startup information
#define EHI_INITIALIZE_XCOM		(EHI_ - 2)	//	Fail to initialize XCom
#define EHI_START_XCOM			(EHI_ - 3)	//	Fail to start XCom
#define EHI_INVALID_VID			(EHI_ - 4)	//	Invalid VID
#define EHI_NO_MATCHED_DATA		(EHI_ - 5)	//	Cannot find the matched data
#define EHI_CREATE_SYNC_OBJECT	(EHI_ - 6)	//	Fail to create sync object
#define EHI_INVALID_ALID		(EHI_ - 7)	//	Invalid ALID
#define EHI_INVALID_CEID		(EHI_ - 8)	//	Invalid CEID
#define EHI_INVALID_RPTID		(EHI_ - 9)	//	Invalid RPTID
#define EHI_OPEN_DATABASE		(EHI_ - 10)	//	Fail to open database
#define EHI_REPORT_FULL			(EHI_ - 11)	//	Report buffer is full.
#define EHI_SPOOL_NOT_USE		(EHI_ - 15)	//	This system does not use spooling now.
#define EHI_SPOOL_FULL			(EHI_ - 16)	//	Spool buffer is full.
#define EHI_EXECUTE_SQL			(EHI_ - 17)	//	Error in Execute SQL.
#define EHI_OPEN_SQL			(EHI_ - 18)	//	Error in Open SQL.

#ifndef LEN_COMMON
#define LEN_COMMON			64		//	Common string length
#define LEN_COMMON2			(LEN_COMMON * 2)	//	Common string length * 2
#define LEN_GENERAL			(LEN_COMMON * 4)	//	General string length
#define LEN_GENERAL2		(LEN_GENERAL * 2)	//	General string length * 2
#define LEN_GENERAL4		(LEN_GENERAL * 4)	//	General string length * 4
#define LEN_GENERAL8		(LEN_GENERAL * 8)	//	General string length * 8
#define LEN_MESSAGE			1024
#endif		//	LEN_COMMON

// Timer
#define TIMER_INIT				1
#define TIMER_PROC				2
#define TIMER_PM				3

//  Bit / Word Type
#define BIT_AREA				0
#define WORD_AREA				1
// PLC Memory Type
#define CIO_MEMORYRED			   0x80	  /// Read CIO->80 , Write 00
#define CIO_MEMORYWRIT			   0x00	  /// Read CIO->80 , Write 00
#define DWORD_MEMORY			   0x82	  /// Read 82    ,    Write 82 
#define EWORD_MEMORY			   0x90   //0x20	  /// Read 20    ,    Write	20

// PLC Memory CIO AREAR
#define CIO_INPUTAREAR			   0	  
#define CIO_TOUCHAREAR			   1

// PLC BIT on/off
#define BIT_OFF			   0
#define BIT_ON			   1


// Message Length
#define LEN_WORD				16
#define LEN_READ_REQUEST		34
#define LEN_READ_RESPONSE		30
#define LEN_WRITE_RESPONSE		30

//	Timer Event ID ---------------------------------------------------------------------
#define TM_RECEIVE				1
#define MAX_RESP_TIMEOUT		300    //2009-07-09 //3000

//	ETC... -----------------------------------------------------------------------------
#define SOCK_SERVER				0
#define SOCK_CLIENT				1


#define LEN_MAX_1		1
#define	LEN_MAX_2		2
#define LEN_MAX_3		2
#define	LEN_MAX_4		4
#define LEN_MAX_5		5
#define	LEN_MAX_6		6
#define	LEN_MAX_8		8
#define	LEN_MAX_9		9
#define	LEN_MAX_10		10
#define	LEN_MAX_12		12
#define	LEN_MAX_14      14
#define	LEN_MAX_16		16
#define	LEN_MAX_18		18

#define	LEN_MAX_20		20
#define	LEN_MAX_21		21
#define	LEN_MAX_24		24
#define	LEN_MAX_40		40
#define	LEN_MAX_48		48
#define LEN_MAX_63		63

#define	LEN_MAX_80      80



extern BOOL  RBtn;
extern BYTE  bInput;
extern BYTE  bOutput;

//=======================================================



//=========================================================================
extern WORD  wInOutput[MAX_IOCOUNT_48 * 2];
extern WORD  wTouchInput[MAX_TOUCHCOUNT_62 * 2];
extern WORD  wEmemoryRead[MAX_EMORYSYSTEMCOUNT_130 * 2];
extern WORD  wEmemoryMotorSpeedRead[MAX_EMORYMOTORSPEEDCOUNT_100 * 2];
extern WORD  wEmemoryMonitorRead[MAX_EMORYDATACOUNT_100 * 2];
extern double EmonitorDataDouble[MAX_EMORYDATADOUBLECOUNT_25 * 2];
extern WORD  wEmemoryReadMotor[MAX_EMORYMOTORCOUNT_100 * 2];
//=======================================================

extern WORD  wEmemoryMappingRead[MAX_MAPEMORYCOUNT_50 * 2];
extern WORD  wEmemoryGEMRead[MAX_GEMEMORYCOUNT_50 * 2];
extern WORD  wTouchCIOGem[MAX_GEMCIOCOUNT_10 * 2];





extern CStringArray wEmomoryWriteArray;
extern CStringArray wEmomoryMap1WriteArray;
extern CStringArray wEmomoryMap2WriteArray;


extern CString m_ComOp2Data[4];
extern CString m_strCom2Data[4];

extern CString m_ComOp3Data[4];
extern CString m_strCom3Data[4];

extern CString m_ComOp4Data[4];
extern CString m_strCom4Data[4];

extern CString m_ComOp5Data[4];
extern CString m_strCom5Data[4];

extern CString m_ComOp6Data[4];
extern CString m_strCom6Data[4];

extern CString m_ComOp7Data[4];
extern CString m_strCom7Data[4];

extern CString m_ComOp12Data[4];
extern CString m_strCom12Data[4];

extern CString m_ComOpData[15];
extern CString m_strComData[15];

extern int   onoff[NUMOFSOL];

extern char *SelLanguage(char *Han,char *Eng);  
extern CString SelLanguage(CString Han,CString Eng); 

extern BOOL RegReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpName, LPTSTR lpValue, DWORD nSize);
extern BOOL RegWriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpName, LPCTSTR lpValue) ;



extern	int    InitStartFlag; 
extern	int    IsInitProc[NMBOFMTR]; 
extern  int    IsInitComp[NMBOFMTR];
extern  int    IsInitComplete;
extern  int    LastErrorCode;
extern  int    LastErrorNo;

extern BOOL m_AlarmActive;
extern BOOL m_MappingActive;
extern BOOL ErrorDisplayActive;
extern BOOL m_InspectActive;
extern BOOL m_RingCheckActive;
extern BOOL m_OutJarActive;

extern int     m_nHomeStep[NMBOFMTR];
extern BOOL    m_bHomeSearch[NMBOFMTR]; 
extern double  m_dHomeVel1[NMBOFMTR];
extern double  m_dHomeVel2[NMBOFMTR];
extern double  m_dHomeVel3[NMBOFMTR];
extern BOOL    m_bIsDelayOn;
extern int	   m_nStep;
extern int	   m_nDelay;
extern int	   m_nSetDelay;
extern int     m_MonitorNo;


extern CStringArray m_RobotDataArray;


extern int  Mouse_Line_CMove(double pos_x, double pos_y, double speed, double accel) ;
extern CString GetCurDateTime();
extern long	GetDiffTimeNum(CString sFromDateTime, CString sToDateTime, CString sType="m");
extern CString DateAdd(CString sType, int nInterval, CString sDate);
extern int GetCharToNbrValue (char ch);
extern int GetDistenceComboValue (int nValu) ;
extern int GetNumberCheck(CString name);
extern void AscToString(char *pszOut, unsigned short *pnaBuf, short nPoints);
extern void StringToAsc(char *pszBuf, unsigned short *pnaBuf, short nPoints);
extern void GetDigitTypeRead(short nAdd,short nPoints,short nType,short nSize,short nKind);
extern short GetDigitByDec(short nSource);
extern short SetCIOBit(BOOL Addr);
extern short SetCIOBitGem(BOOL Addr);
extern CString GetStringToData(CString nData,int nType);
extern CString onSortLotCompID(CString strWaferID,short nFrontCnt,short nBackCnt,BOOL nSortAdd,CString straddChar,BOOL nSortDot);
extern	CString onSortMapFile(CString strWaferID,CString strWaferIDGiho,short nFrontInfor,short nFrontCnt,CString strFrontChar,CString strMapfileGiho,BOOL bMapNumber,short nCheckSum,CString strMapEndForm);
extern void WriteWaferIDListFile(CString strPort,CString strSlotNo,CString strWaferID);
extern CString ReadWaferIDListFile(CString strPort,CString strSlotNo);
extern void WriteComportSettingFile(CString strPort, CString strSlotNo, CString strWaferID);
extern CString ReadComportSettingFile(CString strPort, CString strSlotNo);
extern void WriteSetRecipeFile(CString strPort,CString strSlotNo,CString strData);
extern CString ReadSetRecipeFile(CString strPort,CString strSlotNo);
extern CString GetFilePath();
extern void gRecipeLoad();
extern CString gReadRecipeFile(CString strParameter, CString strData, CString mRecipeName);
extern void gWriteRecipeFile(CString strParameter, CString strData, CString strValue, CString mRecipeName);
extern void gRecipeFileLoad(CString strRcpName);
extern void gRecipeFileChange(CString strRcpName);
extern CString ContentsSorting(CString strContents, CString strCompare);
extern void RecipeCreate(CString mRecipeName);
extern void RecipeDelete(CString mRecipeName);

CString gReadMotorFile(CString strParameter, CString strData, CString mMotorNo);
void gWriteMotorFile(CString strParameter, CString strData, CString strValue, CString mMotorNo);
void gMotorFileLoad(CString strMotorNo);
void gMotorLoad();
void gMotorFileSave(CString strMotorNo);

CString gReadInterfaceFile(CString strParameter, CString strData);
void gWriteInterfaceFile(CString strParameter, CString strData, CString strValue);

typedef struct {
	char	m_szEqCommIp[LEN_COMMON];			//	IP address for equipment comm.
	int		m_nEqCommPort;						//	TCP port # for equipment comm.
	int		m_nEqCommConnectTimeout;			//	Connection timeout for equipment comm.
	bool	m_fEqCommActive;					// EQ connection (XSock Setting: Active(true), Passive(false)
	
	char	m_szXComConfigFile[LEN_GENERAL];	//	XCom configuration file
	int		m_nDevId;							//	Device ID
	
	char	m_szDatabaseFile[LEN_GENERAL];		//	Database file
	char	m_szRecipeFolder[LEN_GENERAL];		//	Recipe folder
	char	m_szRecipeTempFolder[LEN_GENERAL];	//  Temp Recipe Folder
	
	char	m_szLogFolder[LEN_GENERAL];			//	Log folder
	char	m_szMainLogPrefix[LEN_COMMON];		//	Log prefix for main operation
	int		m_nLogKeepDays;						//	Days of keeping log files
	bool	m_fUseMainLog;						//	Use main log or not
	bool	m_fUseEqCommLog;					//	Use Eq. communication log or not
	bool	m_fUseEventReport;					//  Use event report when alarm occured
	char	m_szSpoolInfoFile[LEN_GENERAL];		//	Spooling information file
	
	char	m_szXComLogFolder[LEN_GENERAL];		//	XCom Log folder
	char	m_szXNetLogFolder[LEN_GENERAL];		//	XNet Log folder
	char	m_szHGemLogFolder[LEN_GENERAL];		//	HGem Log folder
 

}_tStartInfo ;
extern _tStartInfo 	m_StartInfo;

typedef struct{
	CString			m_sIP;
	int				m_nPort;
	bool			m_bActive;
	int				m_nKeepData;
	
	int				m_nPlcStart01;
	int				m_nPlcSize01;
	int				m_nPlcStart02;
	int				m_nPlcSize02;
	
	int				m_nPCStart01;
	int				m_nPCSize01;
	int				m_nPCStart02;
	int				m_nPCSize02;
	
	int				m_nAlarmStart;
	int				m_nAlarmSize;
	int				m_nPMAlarmStart;
	int				m_nPMAlarmSize;
	
	short			m_nType;		// Socket Type
	bool			m_fConn;
	bool			m_fNode;
	BOOL			m_fActive;
	BOOL			m_fSatus;
	
	BYTE			m_cSvNodeNo;
	BYTE			m_cClNodeNo;
	BYTE			m_cSID;			// Serv

	int             m_nOperationMaxCount;
	int				m_nAlarmMaxCount;
	int				m_nProductMaxCount;

	CString			m_strCustomerName;
	CString			m_strCustomerPlace;
	CString			m_strSoftVer;
	
	CString			m_Date;
	CString			m_Time;

	///
	CString			m_strLanguage;
	CString			m_strSerialNo;
	CString			m_strModel;

}_SystemINI;
extern _SystemINI SystemINIFiles;

typedef struct {
	unsigned long timer;
	short nAddr;
	short bitActive;
	short bitName;
	short bitno;
}_Invert_Button;
extern _Invert_Button InvertButton[MAX_INVERTBITCOUNTS_112];

typedef struct  
{
    double delay;
	int move_mode;
	long Distance;
	int JogSpedMode;
	int  DistspdActiv;
	int JogSpedActiv;
	int hsen_level;
	int plmt_level;
	int nlmt_level;
	int inpos_enb;
	int alarm_enb;
	double current_pos;
	int mtorjog_active;
	short mtorjog_level;
	double max_speed;
	CString homemessage;
	CString currentmessage;
	BOOL    sspanel_plmt_name;
	BOOL    sspanel_nlmt_name;
	BOOL    sspanel_hsen_name;
	BOOL    edit_motor_name;
	BOOL    edit_currentpos_name;
	BOOL    edit_motormessage_name;
 
}MtrPara;
extern MtrPara mtrpara[MAX_MOTORCOUNTS_40];

typedef struct
{
	CString	strPrintWriteData;
	
	CString	strScannerReadID;

	CString	strCameraReadID;
	CString	strHostLotID;
	CString	strHostChipcount;
	CString	strHostQRCode;

}_GetOCR;
extern _GetOCR m_GetOCR;

typedef struct
{
	CString strWaferIDGiho;
	BOOL    bWafer_MapFile;
	short   nFrontInfor;
	short   nFrontCnt;
	CString strFrontChar;
	CString strMapfileGiho;
	CString strIDGiho;
	BOOL    bMapNumber;
	short   nCheckSum;
	CString strMapEndForm;
	BOOL    bFormatReadOk;
	CString strMapFilePath1;
	CString strMapFilePath2;
}_MapFileFormatInfor;
extern _MapFileFormatInfor m_GetmapFileFormat;

typedef struct
{
	
	CString m_WaferID;
	CString m_PrintID;
	CString m_ScannerID;
	CString m_Diepart;
	CString m_WaferGemID;
	CString m_Mapfile;
	BOOL    m_bmapbit;
	
}_GetWaferID;
extern _GetWaferID m_GetWaferID1[MAX_OCRIDCNTS_100];
extern _GetWaferID m_GetWaferID2[MAX_OCRIDCNTS_100];
extern _GetWaferID m_GetWaferID3[MAX_OCRIDCNTS_100];
extern _GetWaferID m_GetWaferID4[MAX_OCRIDCNTS_100];

typedef struct
{

	short   EMemoryWrite;
	short   EMemoryWriteCount;

	short    CurrentFormNo;
	short    ActiveFormNo;
	short    BeforEngOprForm;

	int    CurrentManualNo;
	int    ActiveManualNo;
	int    nManualDisplayNo;
	BOOL	 bManualButOn;

	BOOL    IsDBLoaded;

	BOOL	m_UserLogInOut;

	CString m_UserID;
	CString m_UserPassword;
	CString m_UserLevel;
	CString m_UserShift;

	CString m_strMapInformation;
	CString m_strMapInQtyCST1;
	CString m_strMapOutQtyCST1;
	int m_nMapInQtyCST1;
	int m_nMapOutQtyCST1;
	CString m_strMapInQtyCST2;
	CString m_strMapOutQtyCST2;
	int m_nMapInQtyCST2;
	int m_nMapOutQtyCST2;

	int m_nSlotno1;
	int m_nSlotno2;
	CString m_strRobotSlotno;
	CString m_strCenteringSlotno;
	CString m_strRinseSlotno;
	CString m_strDescum1Slotno;
	CString m_strDescum2Slotno;
	CString m_strSputterSlotno;
	CString m_strWaferIDs;

	int m_UPH;
	int m_CycleTime;
	double m_Warp01;
	double m_Warp02;
	double m_Warp03;
	double m_Warp04;
	double m_Warp05;
	double m_Warp06;
	double m_Warp07;
	double m_Warp08;

	CString m_strWarp01;
	CString m_strWarp02;
	CString m_strWarp03;
	CString m_strWarp04;
	CString m_strWarp05;
	CString m_strWarp06;
	CString m_strWarp07;
	CString m_strWarp08;
	CString m_strWarpMaxHi;
	CString m_strWarpMaxLow;
	CString m_strWarp;
	CString m_strWarpLimit;
	CString strMeasurements;


	CString m_nAllProduct;
	CString m_nYear;
	CString m_nMonth;
	CString m_nDay;


	CString m_strInspectMsg;
	//====== GEM CONTROL, PROCESSMODE =========//
	SHORT	m_nMainControl;
	SHORT	m_nMainProcessMode;

	CString	m_strWaferID;
	CString m_strRecipeID;
	CString m_strWaferSize;

	SHORT   m_nSlotNumber;
	SHORT	m_nWaferSize;

	CString m_strFoupID;
	CString m_strSequence;

	//=======================
	// Remote command

	BOOL    m_bWorkEnd;
	BOOL    m_bSystemInitial;

	BOOL    m_bFoup1ProStart;
	BOOL    m_bFoup1ProAbort;
	BOOL    m_bFoup1ProReject;
	BOOL    m_bFoup1ProEnd;

	BOOL    m_bFoup2ProStart;
	BOOL    m_bFoup2ProAbort;
	BOOL    m_bFoup2ProReject;
	BOOL    m_bFoup2ProEnd;

	short	m_nControlMode;
	short	m_nControlConnect;
	CString m_strRailCarrierID;


	BOOL     m_bRecipeCreated;
	BOOL     m_bRecipeDeleted;
	BOOL     m_bRecipeModifyed;
	BOOL     m_bRecipeChanged;
	CString  m_strRecipename;

	CString m_strLaserPower;

	CString m_strReqProceMetalCarrierID;
	short   m_nWaferErrorCnt;

	CString m_strRcpAdress[50];
	int m_nMotorAdress[50];
	CString m_strMotorName[40];
	CString MotorbitNum[50];
	short nMotorCnt;
	short nMotorSizeCnt;
	CString strMotorSize[10];
	short nWaferSizeCnt;
	CString strWaferSize[5];
	short nCurrentMotorNo;

}_MainVariable;
extern _MainVariable Main;

typedef struct
{
	CString m_strDeondTop_1;
	CString m_strDeondTop_2;
	CString m_strDeondBot_1;
	CString m_strDeondBot_2;
	CString m_strMChuckTempSet;
	CString m_strMChuckTempCur;
	CString m_strDChuckTempSet;
	CString m_strDChuckTempCur;
	CString m_strCool1Top_1;
	CString m_strCool1Top_2;
	CString m_strUVintencity;
	CString m_strUVdosage;
	CString m_strUVlifeSettime;
	CString m_strUVlifeCurtime;
	CString m_strIndex_3;
	CString m_strHotAir_1;
	CString m_strHotAir_2;
	CString m_strHotAir_3;

}_GetTempValue;
extern _GetTempValue m_GetTempValue;


typedef struct
{
	CString m_strFileName;
	CString m_strSlotNo;
	CString m_strCSTAorB;
	CString m_strWaferThickness;
	CString m_strWaferID;
	CString m_strFilePath;
}_GetDiscoInterface;
extern _GetDiscoInterface m_GetDiscoInterface;

typedef struct
{
	
	CString m_strReceiveData[20];
	CString m_strSendData;
	short   m_shReceiveCnt;
	BOOL    m_bReceiveEnd;
	BOOL    m_bReceiveError;
	BOOL    m_bCmdSendEnd;
	BOOL    m_bCmdBusy;
	BOOL    m_bRunEnd;
	BOOL    m_bEventError;
	BOOL    m_bEvent;
	short   m_shErrorNo;
	CString m_strErrorMess;
	CString m_strEventMess;
	int     m_nComTimer;
	int     m_nComSquence;
	int     m_nTimer;
}_GetCom;
extern _GetCom m_GetCom[MAX_COMPORTS_15];

//==========================================================================
// Gem Interface PLC to PC Bit Check
typedef struct
	{
		BOOL b_Bit[16];
		BOOL b_Bit0;
		BOOL b_Bit1;
		BOOL b_Bit2;
		BOOL b_Bit3;
		BOOL b_Bit4;
		BOOL b_Bit5;
		BOOL b_Bit6;
		BOOL b_Bit7;
		BOOL b_Bit8;
		BOOL b_Bit9;
		BOOL b_Bit10;
		BOOL b_Bit11;
		BOOL b_Bit12;
		BOOL b_Bit13;
		BOOL b_Bit14;
		BOOL b_Bit15;
	}_GemSquenceInfor;
extern _GemSquenceInfor m_GemEvent[MAX_GEMEMORYCOUNT_50];


//========================================================================================
//	STRUCT	: _tV
//	DESCRIPT: Variable structure
//========================================================================================

typedef struct {
	int		m_nId;							//	VID
	int		m_nFormat;						//	V format
	char	m_szName[LEN_COMMON];			//	VNAME
	char	m_szValue[LEN_GENERAL];			//	V
	char	m_szClass[8];					//	V class (ECV, SV, DVVAL)
	char	m_szMin[LEN_GENERAL];			//	Min. value
	char	m_szMax[LEN_GENERAL];			//	Max. value
	char	m_szDef[LEN_GENERAL];			//	Default value
	char	m_szUnit[LEN_COMMON];			//	Variable unit
	int		m_nKind;

	//	char	m_szValueHuge[LEN_VALUE2048];	//	for 1024~2048 Data length
}_tV;

//========================================================================================
//	STRUCT	: _tAlarm
//	DESCRIPT: Alarm structure
//========================================================================================
typedef struct {
	int		m_nId;		//	ALID
	int		m_nEnabled;	//	Alarm enabled flag (0 = Disabled, 1 = Enabled)
	int		m_nState;	//	Alarm state (0 = Cleared, 1 = Set)
	char	m_szText[LEN_COMMON2];	//	Alarm text
	int		m_nAlcd;	//	ALCD : Alarm Code - 2007.05.16.kplee
	char	m_szCauText[LEN_COMMON2];	//	Alarm text
	char	m_szActText[LEN_COMMON2];	//	Alarm text
	int     m_nActiv;
	int     m_nBackup;
}_tAlarm ;

//========================================================================================
//	STRUCT	: _tAlarm
//	DESCRIPT: Alarm structure
//========================================================================================

//========================================================================================
typedef struct {
	
	char	m_szFormatText[LEN_COMMON2];	//	Print Format text
	char	m_szDataText[LEN_COMMON2];	//	Data text
	
}_tprintFormat ;
extern _tprintFormat     m_printFormat[MAX_OCRCNTS];


//////////==========================
//========================================================================================
//	STRUCT	: _tOperation
//	DESCRIPT: Alarm structure
//========================================================================================
typedef struct {
	int		m_nId;		//	OPCODEOPCODE
	char	m_szText[LEN_COMMON2];	//	OPTEXT
	int     m_nActiv;
	int     m_nBackup;
}_tOperation ;


//========================================================================================
//	STRUCT	: _tWordIOTable
//	DESCRIPT: VID ListType structure to get a items from ListType VID - ECInfo
//  BUILD-DATE: 2007.11.29. by kplee
//========================================================================================

typedef struct 
{
	int		m_nIO;
	char	m_szIOName[100];
	char	m_szValue[256];
	int		m_nSize;
}_tWordIOTable;

//========================================================================================
//	STRUCT	: _tBitIOTable
//	DESCRIPT: VID ListType structure to get a items from ListType VID - ECInfo
//  BUILD-DATE: 2007.11.29. by kplee
//========================================================================================
typedef struct
{
	int		m_remember;
	int 	szIOName;
	int		m_active;
	int     m_buttype;
}_tBitCIOTable;


typedef struct
{
	CString		srtInch;
	CString		strMotorName;
	CString		strParaName[50];
	CString		Data[50];
	CString		strType[50];
	CString		strSize[5];
	CString		strAdress[50];
	CString		strEvalue[50];
	CString		strMin[50];
	CString		strMax[50];
	CString		strCioBit[50];
	CString		strJog;
	CString		strBit;

	short		nMotorParaCnt;
	short		nMotorCnt;


}_MotorTable;
extern _MotorTable  m_MotorTable[MAX_MOTORCOUNTS_40];
//
typedef struct
{

	CString		Name;
	CString		HostRecipeName;
	CString		WaferSize;
	CString		Data[50];
	CString		strRcpName[50];
	CString		strParaName[50];
	CString		strType[50];
	
	CString		strAdress[50];
	CString		strEvalue[50];
	CString		strMin[50];
	CString		strMax[50];

	short		nRcpParaCnt;
	short		nRcpCnt;
	BOOL LoadOK;

}_RecipeTable;
extern _RecipeTable  m_RecipeTable;
//
typedef struct
{

	CString		Data[50];

}_ConfigTable;
extern _ConfigTable  m_ConfigTable;
//
typedef struct
{
	CString		UserID[50];
	CString		UserLevel[50];
	CString		UserPass[50];
	short		UserCnt;
}_UserTable;
extern _UserTable  m_UserTable;
//

typedef struct
{
//	CString m_strRFID;
	UINT	 m_nFoupType;
	CString m_WaferSize;
	CString m_strFoupType;
	CString m_FoupID;
	CString m_strFoupNo;
	CString m_strMapData;
	CString m_strMapCount;
	CString m_strLotID;

	CString m_strRecipeName;
	CString m_strProcessEndMapData;
	CString m_strProcessEndMapCount;
	
//	short	m_nWaferSize;
	int		m_nInMapCount;
	int		m_nOutMapCount;



//	int		m_nFoupSquence;
//	int		m_nHLbeforStageNo;
//	int		m_nHRbeforStageNo;
//	CString m_HLstrRFID;
//	CString m_LRstrRFID;
	
/*	BOOL    m_bProtrusion;
	BOOL    m_bError;
	BOOL    m_bWExistence;
	BOOL    m_bWAbort;
	BOOL    m_bHLExistence;
	BOOL    m_bHRExistence;
	BOOL    m_bFoupDetect;
	BOOL    m_bFoupLoadEnd;
	BOOL    m_bFoupUnLoadEnd;
	BOOL    m_bFoupWorkStartEnb;
	BOOL    m_bFoupWorkEnd;
	BOOL    m_bFoupWorkBusy;
	BOOL    m_bInitialStart;
	BOOL    m_bInitialBusy;
	BOOL    m_bInitialEnd;
	BOOL    m_bFoupOpen;
	BOOL    m_bFoupClose;
	
	
	
	*/
	BOOL    m_bFoupError;
	BOOL    m_bRFIDEnd;
	BOOL    m_bRFIDError;
	BOOL    m_bDisable;
	BOOL    m_bMapEnd;
	BOOL    m_bMapError;
	CString m_WaferID[26];  // Wafer ID
//	int     m_SlotINonfor[26];  // Slot No Infor

	int     m_SlotInfor[26];  // Mapping Slot Infor
	int     m_SlotUnloadfor[26];  //  UnloadSlot Infor

//	int     m_SlotFailfor[26];  //  FailSlot Infor
//	int     m_SlotSSpanel[26];  // SSpanel Address

//	CString m_strRecipeName[26];
//	CString m_BFstrRFID[26];
//	CString m_HLstrRecipeName[26];
//	CString m_HRstrRecipeName[26];
//	int     m_nBufDryTime[26];
//	BOOL    m_bBufDryEnd[26];
//	int		m_nBufDryRunTime[26];
//	int     m_nWorkFoupNo[26];

//	_RecipeTable m_RecipeData[26];
	
}_FoupTable;
extern _FoupTable m_FoupTable[MAX_FOUPCNTS_5];


typedef struct
{

	CString strChuckZ_axis;
	double     nChuckZ_axis;

	
}_LimitTable;
extern _LimitTable  m_LimitTable;

typedef struct
{
	
	int Svid_LotID1_Clear;
	int Svid_LotID2_Clear;
	BOOL m_bStarted;

	BOOL m_bRequestSquence;
	BOOL m_bRequestRinse;
	BOOL m_bRequestDescum1;
	BOOL m_bRequestDescum2;
	BOOL m_bRequestDownStream;

	BOOL m_bRequestInputStopped;
	BOOL m_bRequestInputStarted;
	
	
}_GemReportTable;
extern _GemReportTable  m_GemReportTable;

typedef struct
{
	UINT	m_nDeviceID;
	UINT	m_nRetry;
	UINT	m_nLinkInterval;
	UINT	m_nPort;
	UINT	m_nT3;
	UINT	m_nT5;
	UINT	m_nT6;
	UINT	m_nT7;
	UINT	m_nT8;
	UINT	m_nCommReqeustTimeout;

	char	m_szModelName[0xFF];
	char	m_szSoftRev[0xFF];
	UINT	m_nTimeFormat;	// 0, 1
	UINT	m_nDefaultControlState;

	
	UINT	m_nMaxLogSize;
	UINT	m_nLogRetention;
	UINT	m_nWLogRetention;
	UINT	m_nOLogRetention;
	UINT	m_nALogRetention;
	
	UINT	m_bLogEnable;

	BOOL	m_bWLogEnable;
	BOOL	m_bOLogEnable;
	BOOL	m_bALogEnable;
	CString m_strLaserPower;

	CString m_strTapeTag;
	CString m_strTapeTime;

	UINT	m_nEcid9000;
	UINT	m_nEcid9001;
	UINT	m_nEcid9002;
	UINT	m_nEcid9003;
	UINT	m_nEcid9004;
	UINT	m_nEcid9005;


}_GemLogConfig;
extern _GemLogConfig  m_GemLogConfig;


typedef struct
{
	long    Combo_Value;
	int	    Combo_Active;
	int     Combo_Name;
	short   Combo_nAddr;
	int	    Combo_CursorNo;
	CString Combo_CursorStr;
}_ComboTable;

//========================================================================
extern _ComboTable  m_ComOpboTable[MAX_COMBOCOUNTS_12];
extern WORD  wAlarmInput[MAX_ALARMCOUNT_59];

extern _tAlarm		  m_aAlarm[MAX_ALARMS_944];			//	Alarm structure
extern _tBitCIOTable	  m_aBitCIO[MAX_BITIOS_992];
extern  _tOperation	  m_aOperation[MAX_BITIOS_992];	// Operation structure
extern _tBitCIOTable	  m_aBitCIOGem[MAX_GEMBITIOS_160];

//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


class CGlobal : public CObject  
{
public:
	CGlobal();
	virtual ~CGlobal();

 

    void TMessage(char* fmt, ...);
    void DoEvent();
    void GetPortStatus();


protected:
	BOOL Serialization(CArchive &ar);

public:

public:


};

//////////////////////////////////////////////////////////////////////////
// TIMER ID
#define TIMERID_FUNCSW_STATUS				4000
#define TIMERID_CUONVIEW_UISTATUS			4001
#define TIMERID_CUONVIEW_PLCSTATUS			4002
#define	TIMERID_CUONVIEW_SHOW_ERROR_DISPLAY 4004

#define TIMERID_ENG01_CHECK_STATUS			WM_USER+101
#define TIMERID_ENG02_CHECK_STATUS			WM_USER+102
#define TIMERID_ENG03_CHECK_STATUS			WM_USER+103
#define TIMERID_ENG04_CHECK_STATUS			WM_USER+104
#define TIMERID_ENG05_CHECK_STATUS			WM_USER+105
#define TIMERID_ENG06_CHECK_STATUS			WM_USER+106
#define TIMERID_ENG07_CHECK_STATUS			WM_USER+107
#define TIMERID_ENG08_CHECK_STATUS			WM_USER+108
#define TIMERID_ENG09_CHECK_STATUS			WM_USER+109
#define TIMERID_ENG10_CHECK_STATUS			WM_USER+110

#define TIMERID_CSTDLG_CHECK_STATUS			WM_USER+111
#endif // !defined(AFX_PARA_H__A8F564E4_A2B6_11D5_B0FD_00E02927DE98__INCLUDED_)
