#ifndef __DEFINE_H__
#define __DEFINE_H__

////	 볼스크류 피치 
////   ---------------	x  원하는 펄스수 = mm
////     1회전 펄스수
////
////
////   (보내고자하는 거리 / 스크류 피치) * 1회전 펄스수 = pulse
////

//      이동위치 = 속도 V×시간 t[m]
//      속도     = 이동위치[m]÷시간 t[m/sec

//모터의 분해능(Resolution)과 기구부의 기어비(Gear Rate) 등을 고려해서 입력하여, 
//각종 위치 및 속도 등의 입력 값을 사용자가 지정한 단위로 쉽게 사용하기 위한 설정이다. 
//예를 들어, 가장 많이 사용하는 직선 구동 시스템의 경우를 생각해 보면 다음과 같다. 
//볼스크류 리드 피치(Lead Pitch) : 20 mm, 
//모터의 한 회전당 펄스 수 : 10,000 Pulse 
//위와 같은 경우에, 사용하고자 하는 단위가 mm일 경우, 20 mm를 이동하기 위해서는 10,000 pulse의 
//출력을 해야 하므로, 계산은 다음과 같다. 
//20 mm / 10000 pulse = 0.002 mm/pulse 이다. 
//즉, 1 pulse를 출력하면 0.002 mm를 구동하게 되는 것이다. 

//회전 좌표의 경우에도 같다. 
//회전 반경 : 360 도, 
//모터의 한 회전당 Pulse 수 : 2500 pulse 
//이 경우에는, 사용하고자 하는 단위가 도이다. 계산은 다음과 같다. 
//360 도 / 2500 pulse = 0.144 도/pulse이다.

#include <stdio.h>

// OnTimer()  nTimerID & Time
////////////////////////////////////////////////////

#ifndef LEN_COMMON
#define LEN_COMMON			64					//	Common string length
#define LEN_COMMON2			(LEN_COMMON * 2)	//	Common string length * 2
#define LEN_GENERAL			(LEN_COMMON * 4)	//	General string length -> 256
#define LEN_GENERAL2		(LEN_GENERAL * 2)	//	General string length * 2
#define LEN_GENERAL4		(LEN_GENERAL * 4)	//	General string length * 4 -> 1024
#define LEN_GENERAL8		(LEN_GENERAL * 8)	//	General string length * 8 -> 2048
#define LEN_GENERAL10		(LEN_GENERAL * 10)	//	General string length * 8 -> 2560
#define LEN_FILE			1024 * 100			// 
#define LEN_FILE8			1024 * 800			// 
#endif		//	LEN_COMMON


///////Data Read & Save Arear
#define MAX_VARIABLES			1000		//	# of variables
#define MAX_ALARMS				768		    //	# of alarm IDs//MAX ALARM CIO *16

// CIO READ (000.00 ~ )
#define MAX_IOCOUNT_48     48
#define ADDR_CIO_START_0			(0)
#define ADDR_CIO_END_95				(95)

#define MAX_OPERATION			2000		//	# of Operation IDs
#define	MAX_WORDIOS				2000		//	# of WORD MAP IOS
#define	MAX_BITIOS				2000		//	# of B
#define	MAX_BITIOSGEM			160		//	# Gem All IO Bit Qty


//////Data Read & Save Area
#define MAXBITCOUNT_16				16


//=================================================
#define MAX_GEMCIOCOUNT_10			10
#define	ADDR_CIO_1300				1300		//	# Gem All IO Word Qty
#define	MAX_GEMBITIOS_160				MAX_GEMCIOCOUNT_10 * MAXBITCOUNT_16		//	# of B

//=================================================
#define MAX_GEMEMORYCOUNT_50			50
#define	ADDR_GEMEMORY_900				900		//	# Gem All IO Word Qty


//=================================================
#define MAX_MAPEMORYCOUNT_50			50
#define	ADDR_MAPEMORY_950				950		//	# Gem All IO Word Qty

//============================================================
// ALARM EMEMORY READ
#define MAX_ALARMCOUNT_59			59
#define MAX_ALARMS_944				MAX_ALARMCOUNT_59 * MAXBITCOUNT_16		    //	# of alarm IDs
#define ADDR_ALARMS_400				400
#define ADDR_ALARMSTART_40000				40000
//==============================================
// OPERATION TOUCH READ
#define MAX_TOUCHCOUNT_62			62			// 
#define ADDR_CIOTOUCH_1000				1000			// 
#define ADDR_CIOTOUCHSTART_100000				100000			// 

#define	MAX_BITIOS_992				MAX_TOUCHCOUNT_62 * MAXBITCOUNT_16		//	# of B

//==========================================
// CIO READ (000.00 ~ )
#define MAX_IOCOUNT_48     48
#define ADDR_CIO_0			0

 
//=========================================
// MOTOR DISTANCE,SPEED READ
#define MAX_EMORYMOTORSPEEDCOUNT_100  100
#define MAX_EMORYMOTORSPEED_300  300

//=========================================
//=========================================
// SYSTEM EMEMORY READ
#define MAX_EMORYSYSTEMCOUNT_130  130
#define ADDR_EMORYSYSTEM_500  500

#define ADDR_EMORYDISPLAYNO_501  501
//=========================================
// SYSTEM EMEMORY READ
#define MAX_EMORYDATACOUNT_100  100
#define ADDR_EMORYDATA_700  700

#define MAX_EMORYDATADOUBLECOUNT_25  25


//==============================================
//

#define MAX_DISTANCE_SPEED_40    40
#define ADDR_MOTOR_DISTANCE_300		300 // E555 ~ E570
#define ADDR_MOTOR_SPEED_350		350	// E572 ~ E187
#define ADDR_MOTOR_HOME_546   ADDR_EMORYSYSTEM_500 + 46	// E546
#define ADDR_MOTOR_ERROR_547   ADDR_EMORYSYSTEM_500 + 47	// E547
//=======================================================

#define ADDR_SPEED_50   50	
#define ADDR_DISTANCE_0       0


// COMBO MEMORY READ
#define ADDR_COMBO_START_88        88
#define MAX_COMBOCOUNTS_12        12
#define ADDR_COMBO_588        ADDR_EMORYSYSTEM_500 + ADDR_COMBO_START_88


//=======================================================
// BIT INVERT

#define MAX_INVERTCOUNTS_7        7
#define MAX_INVERTBITCOUNTS_112        MAX_INVERTCOUNTS_7 * MAXBITCOUNT_16
#define ADDR_INVERT_548        ADDR_EMORYSYSTEM_500 + 48

//=======================================================

//===========================================
#define ADDR_FORMVIEWNUMBER_504        ADDR_EMORYSYSTEM_500 + 4

//===========================================
#define ADDR_DISCO_THICKNESS_200        200

//=============================================================
// MAX MOTOR COUNTS

#define MAX_MOTORCOUNTS_40 		40

//=========================================
// SYSTEM MOTOR EMEMORY READ
#define MAX_EMORYMOTORCOUNT_100  100
#define ADDR_EMORYMOTOR_800  800

//=====================================
#define MAX_OCRCNTS				30
#define MAX_OCRPRINTCNTS		20
#define MAZ_MAPFILESLOT			51
//================================================

#define COM_PORT1			1
#define COM_PORT2			2
#define COM_PORT3			3
#define COM_PORT4			4
#define COM_PORT5			5
#define COM_PORT6			6
#define COM_PORT7			7
#define COM_PORT8			8
#define COM_PORT9			9
#define COM_PORT10			10
#define COM_PORT11			11
#define COM_PORT12			12
#define COM_PORT13			13
#define COM_PORT14			14

#define MAX_COMPORTS_15        15


//////////////////////////////////////
#define FOUP_PORT1			1
#define FOUP_PORT2			2
#define FOUP_PORT3			3
#define FOUP_PORT4			4

#define MAX_FOUPCNTS_5		5
#define MAX_FOUPSLOTCNTS_25		25
#define MAX_OCRIDCNTS_100		100
//==============================
#define RFID_1			1
#define RFID_2			2
#define RFID_3			3
#define RFID_4			4

//==============================
#define MAPPING_LOAD			1
#define MAPPING_UNLOAD			2

//==================================================
// RECIPE

#define MAX_RECIPECNTS_100		100


//==================================================
#define	timeLoopScan				50  
#define	timeProcScan				1  
#define	timeTimeScan				1000



#define REGISTRY_KEY	"SOFTWARE\\CUON_SYSTEM\\CUON"

#define AUTO_MODE      1
#define ENGINEER_MODE  2
#define OPERATOR_MODE  3
#define CHECK_MODE     4


#define UM_MENUCLICK		WM_USER + 1
#define UM_MENUENABLE		WM_USER + 2
#define UM_DIALOG			WM_USER + 3

#define _CreateDlg      0
#define _DeleteDlg      1

#define _Auto		    0
#define _Manual		    1

#define NMBOFMTR        9
#define NMBOFPOS        10

#define NUMOFSEN        64
#define NUMOFSOL        64

#define RECIPE_WRITE		1
#define MOTOR_WRITE			2


#define MAPDATA_1WRITE		51
#define MAPDATA_2WRITE		52
#define MAPDATA_3WRITE		53
#define MAPDATA_4WRITE		54

#define FOUPCODE1_WRITE     55
#define FOUPCODE2_WRITE     56
#define FOUPCODE3_WRITE     57
#define FOUPCODE4_WRITE     58

#define GEM_MODUL1_WRITE     59	//E3000
#define GEM_MODUL2_WRITE     60	//E3020
#define GEM_MODUL3_WRITE     61	//E3040
#define GEM_MODUL4_WRITE     62	//E3060
#define GEM_MODUL5_WRITE     63	//E3060
#define GEM_MODUL6_WRITE     64	//E3060
#define GEM_MODUL7_WRITE     64	//E3060
#define GEM_MODUL8_WRITE     66	//E3060

#define GEM_VISION1_WRITE     67	//E3060
#define GEM_VISION2_WRITE     68	//E3060
#define GEM_VISION3_WRITE     69	//E3060
#define GEM_VISION4_WRITE     70	//E3060
#define GEM_VISION5_WRITE     71	//E3060
#define GEM_VISION6_WRITE     72	//E3060

#define MODULE_MAXWRITE     72


#define	ASCII_LF		0x0a
#define	ASCII_CR		0x0d
#define	ASCII_XON		0x11
#define	ASCII_XOFF		0x13


//	SECS-II data formats
#define DATA_FORMAT_LIST		0
#define DATA_FORMAT_BIN			8
#define DATA_FORMAT_BOOL		9
#define DATA_FORMAT_ASCII		16
#define DATA_FORMAT_I1			25
#define DATA_FORMAT_I2			26
#define DATA_FORMAT_I4			28
#define DATA_FORMAT_U1			41
#define DATA_FORMAT_U2			42
#define DATA_FORMAT_U4			44
#define DATA_FORMAT_F4			36
#define DATA_FORMAT_F8			32


#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923
#define ROOT2           1.41421356

//1mm = 1000/25.399 = 39.3716288 mil 
#define Mil             (1.0/25.4)	  //1mil
#define Inch			25.4		  //1inch


#define TMR_MAINFRAME    0
#define TMR_VIEW         1  
#define TMR_LOOP         2 
#define TMR_MTIMER       3   
#define TMR_BLINK        4
#define TMR_DIO          5 
#define TMR_REPEAT       6

/////
#define  BUT_INVERT      1
#define  BUT_MOMENTARY 	 0


////////////////////////
#define  ON      1
#define  OFF 	 0

//////////////////////////////
//////////////////////////////  GEM 

//////////////////////////////////////////////////////////////////////////////////////////////
#define INPUT_MDL_SU	 2
#define OUTPUT_MDL_SU	 2

#define PollingBit(a,b)      (a & (0x01 << b))
#define PollingBitClear(a,b) (a & ~(0x01 << b))
#define PollingBitSet(a,b)   (a | (0x01 << b))

/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SFA_LC_LAMINATOR
static const TCHAR* g_szSoftwareVer = { _T("UI_SYSTEM") };

#define	USE_DEBUG_STRING
#define VER_NEW_PLC
#define THREAD_FLOW

static const int EMEMORY_ADDR_BASE = 400;
static const int EMEMORY_MAX_COUNT = 500;

/// wAlarmInput E400 ~ E455
static const int ADDR_ALARMS_OFFSET_START = 0;
static const int ADDR_ALARMS_OFFSET_END = 55;

/// wEmemoryRead E500 ~ E759
static const int ADDR_EMEMORY_OFFSET_START = 100;
static const int ADDR_EMEMORY_OFFSET_END = 259;

/// wEmemoryMonitorRead E700 ~ E899
static const int ADDR_MONITOR_OFFSET_START = 300;
static const int ADDR_MONITOR_OFFSET_END = 199;

/// wEmemoryReadMotor E800 ~ E895
static const int ADDR_MOTOR_OFFSET_START = 400;
static const int ADDR_MOTOR_OFFSET_END = 95;
#endif //SFA_LC_LAMINATOR
////////////////////////////////////////////////////////////////////////////////////////////////

// INPUT MODULE #1
#define CIO00000            PollingBit(wInOutput[0],0)	
#define CIO00001            PollingBit(wInOutput[0],1)	
#define CIO00002            PollingBit(wInOutput[0],2)	
#define CIO00003            PollingBit(wInOutput[0],3)	
#define CIO00004            PollingBit(wInOutput[0],4)	
#define CIO00005            PollingBit(wInOutput[0],5)	
#define CIO00006            PollingBit(wInOutput[0],6)	
#define CIO00007            PollingBit(wInOutput[0],7)	
#define CIO00008            PollingBit(wInOutput[0],8)	
#define CIO00009            PollingBit(wInOutput[0],9)	
#define CIO00010            PollingBit(wInOutput[0],10)	
#define CIO00011            PollingBit(wInOutput[0],11)	
#define CIO00012            PollingBit(wInOutput[0],12)	
#define CIO00013            PollingBit(wInOutput[0],13)	
#define CIO00014            PollingBit(wInOutput[0],14)	
#define CIO00015            PollingBit(wInOutput[0],15)	

#define CIO00100                    PollingBit(wInOutput[1],0)	
#define CIO00101                    PollingBit(wInOutput[1],1)	
#define CIO00102                    PollingBit(wInOutput[1],2)	
#define CIO00103                    PollingBit(wInOutput[1],3)	
#define CIO00104                    PollingBit(wInOutput[1],4)	
#define CIO00105                    PollingBit(wInOutput[1],5)	
#define CIO00106                    PollingBit(wInOutput[1],6)	
#define CIO00107                    PollingBit(wInOutput[1],7)	
#define CIO00108                    PollingBit(wInOutput[1],8)	
#define CIO00109                    PollingBit(wInOutput[1],9)	
#define CIO00110                    PollingBit(wInOutput[1],10)	
#define CIO00111                    PollingBit(wInOutput[1],11)	
#define CIO00112                    PollingBit(wInOutput[1],12)	
#define CIO00113                    PollingBit(wInOutput[1],13)	
#define CIO00114                    PollingBit(wInOutput[1],14)	
#define CIO00115                    PollingBit(wInOutput[1],15)	
			  
#define CIO00200                    PollingBit(wInOutput[2],0)	
#define CIO00201                    PollingBit(wInOutput[2],1)	
#define CIO00202                    PollingBit(wInOutput[2],2)	
#define CIO00203                    PollingBit(wInOutput[2],3)	
#define CIO00204                    PollingBit(wInOutput[2],4)	
#define CIO00205                    PollingBit(wInOutput[2],5)	
#define CIO00206                    PollingBit(wInOutput[2],6)	
#define CIO00207                    PollingBit(wInOutput[2],7)	
#define CIO00208                    PollingBit(wInOutput[2],8)	
#define CIO00209                    PollingBit(wInOutput[2],9)	
#define CIO00210                    PollingBit(wInOutput[2],10)	
#define CIO00211                    PollingBit(wInOutput[2],11)	
#define CIO00212                    PollingBit(wInOutput[2],12)	
#define CIO00213                    PollingBit(wInOutput[2],13)	
#define CIO00214                    PollingBit(wInOutput[2],14)	
#define CIO00215                    PollingBit(wInOutput[2],15)	
			  
#define CIO00300                    PollingBit(wInOutput[3],0)	
#define CIO00301                    PollingBit(wInOutput[3],1)	
#define CIO00302                    PollingBit(wInOutput[3],2)	
#define CIO00303                    PollingBit(wInOutput[3],3)	
#define CIO00304                    PollingBit(wInOutput[3],4)	
#define CIO00305                    PollingBit(wInOutput[3],5)	
#define CIO00306                    PollingBit(wInOutput[3],6)	
#define CIO00307                    PollingBit(wInOutput[3],7)	
#define CIO00308                    PollingBit(wInOutput[3],8)	
#define CIO00309                    PollingBit(wInOutput[3],9)	
#define CIO00310                    PollingBit(wInOutput[3],10)	
#define CIO00311                    PollingBit(wInOutput[3],11)	
#define CIO00312                    PollingBit(wInOutput[3],12)	
#define CIO00313                    PollingBit(wInOutput[3],13)	
#define CIO00314                    PollingBit(wInOutput[3],14)	
#define CIO00315                    PollingBit(wInOutput[3],15)	
			  
#define CIO00400                    PollingBit(wInOutput[4],0)	
#define CIO00401                    PollingBit(wInOutput[4],1)	
#define CIO00402                    PollingBit(wInOutput[4],2)	
#define CIO00403                    PollingBit(wInOutput[4],3)	
#define CIO00404                    PollingBit(wInOutput[4],4)	
#define CIO00405                    PollingBit(wInOutput[4],5)	
#define CIO00406                    PollingBit(wInOutput[4],6)	
#define CIO00407                    PollingBit(wInOutput[4],7)	
#define CIO00408                    PollingBit(wInOutput[4],8)	
#define CIO00409                    PollingBit(wInOutput[4],9)	
#define CIO00410                    PollingBit(wInOutput[4],10)	
#define CIO00411                    PollingBit(wInOutput[4],11)	
#define CIO00412                    PollingBit(wInOutput[4],12)	
#define CIO00413                    PollingBit(wInOutput[4],13)	
#define CIO00414                    PollingBit(wInOutput[4],14)	
#define CIO00415                    PollingBit(wInOutput[4],15)	
			  
#define CIO00500                    PollingBit(wInOutput[5],0)	
#define CIO00501                    PollingBit(wInOutput[5],1)	
#define CIO00502                    PollingBit(wInOutput[5],2)	
#define CIO00503                    PollingBit(wInOutput[5],3)	
#define CIO00504                    PollingBit(wInOutput[5],4)	
#define CIO00505                    PollingBit(wInOutput[5],5)	
#define CIO00506                    PollingBit(wInOutput[5],6)	
#define CIO00507                    PollingBit(wInOutput[5],7)	
#define CIO00508                    PollingBit(wInOutput[5],8)	
#define CIO00509                    PollingBit(wInOutput[5],9)	
#define CIO00510                    PollingBit(wInOutput[5],10)	
#define CIO00511                    PollingBit(wInOutput[5],11)	
#define CIO00512                    PollingBit(wInOutput[5],12)	
#define CIO00513                    PollingBit(wInOutput[5],13)	
#define CIO00514                    PollingBit(wInOutput[5],14)	
#define CIO00515                    PollingBit(wInOutput[5],15)	
			  
#define CIO00600                    PollingBit(wInOutput[6],0)	
#define CIO00601                    PollingBit(wInOutput[6],1)	
#define CIO00602                    PollingBit(wInOutput[6],2)	
#define CIO00603                    PollingBit(wInOutput[6],3)	
#define CIO00604                    PollingBit(wInOutput[6],4)	
#define CIO00605                    PollingBit(wInOutput[6],5)	
#define CIO00606                    PollingBit(wInOutput[6],6)	
#define CIO00607                    PollingBit(wInOutput[6],7)	
#define CIO00608                    PollingBit(wInOutput[6],8)	
#define CIO00609                    PollingBit(wInOutput[6],9)	
#define CIO00610                    PollingBit(wInOutput[6],10)	
#define CIO00611                    PollingBit(wInOutput[6],11)	
#define CIO00612                    PollingBit(wInOutput[6],12)	
#define CIO00613                    PollingBit(wInOutput[6],13)	
#define CIO00614                    PollingBit(wInOutput[6],14)	
#define CIO00615                    PollingBit(wInOutput[6],15)	
			  
#define CIO00700                    PollingBit(wInOutput[7],0)	
#define CIO00701                    PollingBit(wInOutput[7],1)	
#define CIO00702                    PollingBit(wInOutput[7],2)	
#define CIO00703                    PollingBit(wInOutput[7],3)	
#define CIO00704                    PollingBit(wInOutput[7],4)	
#define CIO00705                    PollingBit(wInOutput[7],5)	
#define CIO00706                    PollingBit(wInOutput[7],6)	
#define CIO00707                    PollingBit(wInOutput[7],7)	
#define CIO00708                    PollingBit(wInOutput[7],8)	
#define CIO00709                    PollingBit(wInOutput[7],9)	
#define CIO00710                    PollingBit(wInOutput[7],10)	
#define CIO00711                    PollingBit(wInOutput[7],11)	
#define CIO00712                    PollingBit(wInOutput[7],12)	
#define CIO00713                    PollingBit(wInOutput[7],13)	
#define CIO00714                    PollingBit(wInOutput[7],14)	
#define CIO00715                    PollingBit(wInOutput[7],15)	
			  
#define CIO00800                    PollingBit(wInOutput[8],0)	
#define CIO00801                    PollingBit(wInOutput[8],1)	
#define CIO00802                    PollingBit(wInOutput[8],2)	
#define CIO00803                    PollingBit(wInOutput[8],3)	
#define CIO00804                    PollingBit(wInOutput[8],4)	
#define CIO00805                    PollingBit(wInOutput[8],5)	
#define CIO00806                    PollingBit(wInOutput[8],6)	
#define CIO00807                    PollingBit(wInOutput[8],7)	
#define CIO00808                    PollingBit(wInOutput[8],8)	
#define CIO00809                    PollingBit(wInOutput[8],9)	
#define CIO00810                    PollingBit(wInOutput[8],10)	
#define CIO00811                    PollingBit(wInOutput[8],11)	
#define CIO00812                    PollingBit(wInOutput[8],12)	
#define CIO00813                    PollingBit(wInOutput[8],13)	
#define CIO00814                    PollingBit(wInOutput[8],14)	
#define CIO00815                    PollingBit(wInOutput[8],15)	
			  
#define CIO00900                    PollingBit(wInOutput[9],0)	
#define CIO00901                    PollingBit(wInOutput[9],1)	
#define CIO00902                    PollingBit(wInOutput[9],2)	
#define CIO00903                    PollingBit(wInOutput[9],3)	
#define CIO00904                    PollingBit(wInOutput[9],4)	
#define CIO00905                    PollingBit(wInOutput[9],5)	
#define CIO00906                    PollingBit(wInOutput[9],6)	
#define CIO00907                    PollingBit(wInOutput[9],7)	
#define CIO00908                    PollingBit(wInOutput[9],8)	
#define CIO00909                    PollingBit(wInOutput[9],9)	
#define CIO00910                    PollingBit(wInOutput[9],10)	
#define CIO00911                    PollingBit(wInOutput[9],11)	
#define CIO00912                    PollingBit(wInOutput[9],12)	
#define CIO00913                    PollingBit(wInOutput[9],13)	
#define CIO00914                    PollingBit(wInOutput[9],14)	
#define CIO00915                    PollingBit(wInOutput[9],15)	

#define CIO01000                    PollingBit(wInOutput[10],0)	
#define CIO01001                    PollingBit(wInOutput[10],1)	
#define CIO01002                    PollingBit(wInOutput[10],2)	
#define CIO01003                    PollingBit(wInOutput[10],3)	
#define CIO01004                    PollingBit(wInOutput[10],4)	
#define CIO01005                    PollingBit(wInOutput[10],5)	
#define CIO01006                    PollingBit(wInOutput[10],6)	
#define CIO01007                    PollingBit(wInOutput[10],7)	
#define CIO01008                    PollingBit(wInOutput[10],8)	
#define CIO01009                    PollingBit(wInOutput[10],9)	
#define CIO01010                    PollingBit(wInOutput[10],10)	
#define CIO01011                    PollingBit(wInOutput[10],11)	
#define CIO01012                    PollingBit(wInOutput[10],12)	
#define CIO01013                    PollingBit(wInOutput[10],13)	
#define CIO01014                    PollingBit(wInOutput[10],14)	
#define CIO01015                    PollingBit(wInOutput[10],15)	
			  
#define CIO01100                    PollingBit(wInOutput[11],0)	
#define CIO01101                    PollingBit(wInOutput[11],1)	
#define CIO01102                    PollingBit(wInOutput[11],2)	
#define CIO01103                    PollingBit(wInOutput[11],3)	
#define CIO01104                    PollingBit(wInOutput[11],4)	
#define CIO01105                    PollingBit(wInOutput[11],5)	
#define CIO01106                    PollingBit(wInOutput[11],6)	
#define CIO01107                    PollingBit(wInOutput[11],7)	
#define CIO01108                    PollingBit(wInOutput[11],8)	
#define CIO01109                    PollingBit(wInOutput[11],9)	
#define CIO01110                    PollingBit(wInOutput[11],10)	
#define CIO01111                    PollingBit(wInOutput[11],11)	
#define CIO01112                    PollingBit(wInOutput[11],12)	
#define CIO01113                    PollingBit(wInOutput[11],13)	
#define CIO01114                    PollingBit(wInOutput[11],14)	
#define CIO01115                    PollingBit(wInOutput[11],15)	
			  
#define CIO01200                    PollingBit(wInOutput[12],0)	
#define CIO01201                    PollingBit(wInOutput[12],1)	
#define CIO01202                    PollingBit(wInOutput[12],2)	
#define CIO01203                    PollingBit(wInOutput[12],3)	
#define CIO01204                    PollingBit(wInOutput[12],4)	
#define CIO01205                    PollingBit(wInOutput[12],5)	
#define CIO01206                    PollingBit(wInOutput[12],6)	
#define CIO01207                    PollingBit(wInOutput[12],7)	
#define CIO01208                    PollingBit(wInOutput[12],8)	
#define CIO01209                    PollingBit(wInOutput[12],9)	
#define CIO01210                    PollingBit(wInOutput[12],10)	
#define CIO01211                    PollingBit(wInOutput[12],11)	
#define CIO01212                    PollingBit(wInOutput[12],12)	
#define CIO01213                    PollingBit(wInOutput[12],13)	
#define CIO01214                    PollingBit(wInOutput[12],14)	
#define CIO01215                    PollingBit(wInOutput[12],15)	
			  
#define CIO01300                    PollingBit(wInOutput[13],0)	
#define CIO01301                    PollingBit(wInOutput[13],1)	
#define CIO01302                    PollingBit(wInOutput[13],2)	
#define CIO01303                    PollingBit(wInOutput[13],3)	
#define CIO01304                    PollingBit(wInOutput[13],4)	
#define CIO01305                    PollingBit(wInOutput[13],5)	
#define CIO01306                    PollingBit(wInOutput[13],6)	
#define CIO01307                    PollingBit(wInOutput[13],7)	
#define CIO01308                    PollingBit(wInOutput[13],8)	
#define CIO01309                    PollingBit(wInOutput[13],9)	
#define CIO01310                    PollingBit(wInOutput[13],10)	
#define CIO01311                    PollingBit(wInOutput[13],11)	
#define CIO01312                    PollingBit(wInOutput[13],12)	
#define CIO01313                    PollingBit(wInOutput[13],13)	
#define CIO01314                    PollingBit(wInOutput[13],14)	
#define CIO01315                    PollingBit(wInOutput[13],15)	
			  
#define CIO01400                    PollingBit(wInOutput[14],0)	
#define CIO01401                    PollingBit(wInOutput[14],1)	
#define CIO01402                    PollingBit(wInOutput[14],2)	
#define CIO01403                    PollingBit(wInOutput[14],3)	
#define CIO01404                    PollingBit(wInOutput[14],4)	
#define CIO01405                    PollingBit(wInOutput[14],5)	
#define CIO01406                    PollingBit(wInOutput[14],6)	
#define CIO01407                    PollingBit(wInOutput[14],7)	
#define CIO01408                    PollingBit(wInOutput[14],8)	
#define CIO01409                    PollingBit(wInOutput[14],9)	
#define CIO01410                    PollingBit(wInOutput[14],10)	
#define CIO01411                    PollingBit(wInOutput[14],11)	
#define CIO01412                    PollingBit(wInOutput[14],12)	
#define CIO01413                    PollingBit(wInOutput[14],13)	
#define CIO01414                    PollingBit(wInOutput[14],14)	
#define CIO01415                    PollingBit(wInOutput[14],15)	
			  
#define CIO01500                    PollingBit(wInOutput[15],0)	
#define CIO01501                    PollingBit(wInOutput[15],1)	
#define CIO01502                    PollingBit(wInOutput[15],2)	
#define CIO01503                    PollingBit(wInOutput[15],3)	
#define CIO01504                    PollingBit(wInOutput[15],4)	
#define CIO01505                    PollingBit(wInOutput[15],5)	
#define CIO01506                    PollingBit(wInOutput[15],6)	
#define CIO01507                    PollingBit(wInOutput[15],7)	
#define CIO01508                    PollingBit(wInOutput[15],8)	
#define CIO01509                    PollingBit(wInOutput[15],9)	
#define CIO01510                    PollingBit(wInOutput[15],10)	
#define CIO01511                    PollingBit(wInOutput[15],11)	
#define CIO01512                    PollingBit(wInOutput[15],12)	
#define CIO01513                    PollingBit(wInOutput[15],13)	
#define CIO01514                    PollingBit(wInOutput[15],14)	
#define CIO01515                    PollingBit(wInOutput[15],15)	
			  
#define CIO01600                    PollingBit(wInOutput[16],0)	
#define CIO01601                    PollingBit(wInOutput[16],1)	
#define CIO01602                    PollingBit(wInOutput[16],2)	
#define CIO01603                    PollingBit(wInOutput[16],3)	
#define CIO01604                    PollingBit(wInOutput[16],4)	
#define CIO01605                    PollingBit(wInOutput[16],5)	
#define CIO01606                    PollingBit(wInOutput[16],6)	
#define CIO01607                    PollingBit(wInOutput[16],7)	
#define CIO01608                    PollingBit(wInOutput[16],8)	
#define CIO01609                    PollingBit(wInOutput[16],9)	
#define CIO01610                    PollingBit(wInOutput[16],10)	
#define CIO01611                    PollingBit(wInOutput[16],11)	
#define CIO01612                    PollingBit(wInOutput[16],12)	
#define CIO01613                    PollingBit(wInOutput[16],13)	
#define CIO01614                    PollingBit(wInOutput[16],14)	
#define CIO01615                    PollingBit(wInOutput[16],15)	
			  
#define CIO01700                    PollingBit(wInOutput[17],0)	
#define CIO01701                    PollingBit(wInOutput[17],1)	
#define CIO01702                    PollingBit(wInOutput[17],2)	
#define CIO01703                    PollingBit(wInOutput[17],3)	
#define CIO01704                    PollingBit(wInOutput[17],4)	
#define CIO01705                    PollingBit(wInOutput[17],5)	
#define CIO01706                    PollingBit(wInOutput[17],6)	
#define CIO01707                    PollingBit(wInOutput[17],7)	
#define CIO01708                    PollingBit(wInOutput[17],8)	
#define CIO01709                    PollingBit(wInOutput[17],9)	
#define CIO01710                    PollingBit(wInOutput[17],10)	
#define CIO01711                    PollingBit(wInOutput[17],11)	
#define CIO01712                    PollingBit(wInOutput[17],12)	
#define CIO01713                    PollingBit(wInOutput[17],13)	
#define CIO01714                    PollingBit(wInOutput[17],14)	
#define CIO01715                    PollingBit(wInOutput[17],15)	
			  
#define CIO01800                    PollingBit(wInOutput[18],0)	
#define CIO01801                    PollingBit(wInOutput[18],1)	
#define CIO01802                    PollingBit(wInOutput[18],2)	
#define CIO01803                    PollingBit(wInOutput[18],3)	
#define CIO01804                    PollingBit(wInOutput[18],4)	
#define CIO01805                    PollingBit(wInOutput[18],5)	
#define CIO01806                    PollingBit(wInOutput[18],6)	
#define CIO01807                    PollingBit(wInOutput[18],7)	
#define CIO01808                    PollingBit(wInOutput[18],8)	
#define CIO01809                    PollingBit(wInOutput[18],9)	
#define CIO01810                    PollingBit(wInOutput[18],10)	
#define CIO01811                    PollingBit(wInOutput[18],11)	
#define CIO01812                    PollingBit(wInOutput[18],12)	
#define CIO01813                    PollingBit(wInOutput[18],13)	
#define CIO01814                    PollingBit(wInOutput[18],14)	
#define CIO01815                    PollingBit(wInOutput[18],15)	

#define CIO01900                    PollingBit(wInOutput[19],0)	
#define CIO01901                    PollingBit(wInOutput[19],1)	
#define CIO01902                    PollingBit(wInOutput[19],2)	
#define CIO01903                    PollingBit(wInOutput[19],3)	
#define CIO01904                    PollingBit(wInOutput[19],4)	
#define CIO01905                    PollingBit(wInOutput[19],5)	
#define CIO01906                    PollingBit(wInOutput[19],6)	
#define CIO01907                    PollingBit(wInOutput[19],7)	
#define CIO01908                    PollingBit(wInOutput[19],8)	
#define CIO01909                    PollingBit(wInOutput[19],9)	
#define CIO01910                    PollingBit(wInOutput[19],10)	
#define CIO01911                    PollingBit(wInOutput[19],11)	
#define CIO01912                    PollingBit(wInOutput[19],12)	
#define CIO01913                    PollingBit(wInOutput[19],13)	
#define CIO01914                    PollingBit(wInOutput[19],14)	
#define CIO01915                    PollingBit(wInOutput[19],15)	

#define CIO02000                    PollingBit(wInOutput[20],0)	
#define CIO02001                    PollingBit(wInOutput[20],1)	
#define CIO02002                    PollingBit(wInOutput[20],2)	
#define CIO02003                    PollingBit(wInOutput[20],3)	
#define CIO02004                    PollingBit(wInOutput[20],4)	
#define CIO02005                    PollingBit(wInOutput[20],5)	
#define CIO02006                    PollingBit(wInOutput[20],6)	
#define CIO02007                    PollingBit(wInOutput[20],7)	
#define CIO02008                    PollingBit(wInOutput[20],8)	
#define CIO02009                    PollingBit(wInOutput[20],9)	
#define CIO02010                    PollingBit(wInOutput[20],10)	
#define CIO02011                    PollingBit(wInOutput[20],11)	
#define CIO02012                    PollingBit(wInOutput[20],12)	
#define CIO02013                    PollingBit(wInOutput[20],13)	
#define CIO02014                    PollingBit(wInOutput[20],14)	
#define CIO02015                    PollingBit(wInOutput[20],15)	

#define CIO02100                    PollingBit(wInOutput[21],0)	
#define CIO02101                    PollingBit(wInOutput[21],1)	
#define CIO02102                    PollingBit(wInOutput[21],2)	
#define CIO02103                    PollingBit(wInOutput[21],3)	
#define CIO02104                    PollingBit(wInOutput[21],4)	
#define CIO02105                    PollingBit(wInOutput[21],5)	
#define CIO02106                    PollingBit(wInOutput[21],6)	
#define CIO02107                    PollingBit(wInOutput[21],7)	
#define CIO02108                    PollingBit(wInOutput[21],8)	
#define CIO02109                    PollingBit(wInOutput[21],9)	
#define CIO02110                    PollingBit(wInOutput[21],10)	
#define CIO02111                    PollingBit(wInOutput[21],11)	
#define CIO02112                    PollingBit(wInOutput[21],12)	
#define CIO02113                    PollingBit(wInOutput[21],13)	
#define CIO02114                    PollingBit(wInOutput[21],14)	
#define CIO02115                    PollingBit(wInOutput[21],15)	

#define CIO02200                    PollingBit(wInOutput[22],0)	
#define CIO02201                    PollingBit(wInOutput[22],1)	
#define CIO02202                    PollingBit(wInOutput[22],2)	
#define CIO02203                    PollingBit(wInOutput[22],3)	
#define CIO02204                    PollingBit(wInOutput[22],4)	
#define CIO02205                    PollingBit(wInOutput[22],5)	
#define CIO02206                    PollingBit(wInOutput[22],6)	
#define CIO02207                    PollingBit(wInOutput[22],7)	
#define CIO02208                    PollingBit(wInOutput[22],8)	
#define CIO02209                    PollingBit(wInOutput[22],9)	
#define CIO02210                    PollingBit(wInOutput[22],10)	
#define CIO02211                    PollingBit(wInOutput[22],11)	
#define CIO02212                    PollingBit(wInOutput[22],12)	
#define CIO02213                    PollingBit(wInOutput[22],13)	
#define CIO02214                    PollingBit(wInOutput[22],14)	
#define CIO02215                    PollingBit(wInOutput[22],15)	

#define CIO02300                    PollingBit(wInOutput[23],0)	
#define CIO02301                    PollingBit(wInOutput[23],1)	
#define CIO02302                    PollingBit(wInOutput[23],2)	
#define CIO02303                    PollingBit(wInOutput[23],3)	
#define CIO02304                    PollingBit(wInOutput[23],4)	
#define CIO02305                    PollingBit(wInOutput[23],5)	
#define CIO02306                    PollingBit(wInOutput[23],6)	
#define CIO02307                    PollingBit(wInOutput[23],7)	
#define CIO02308                    PollingBit(wInOutput[23],8)	
#define CIO02309                    PollingBit(wInOutput[23],9)	
#define CIO02310                    PollingBit(wInOutput[23],10)	
#define CIO02311                    PollingBit(wInOutput[23],11)	
#define CIO02312                    PollingBit(wInOutput[23],12)	
#define CIO02313                    PollingBit(wInOutput[23],13)	
#define CIO02314                    PollingBit(wInOutput[23],14)	
#define CIO02315                    PollingBit(wInOutput[23],15)

#define CIO02400                    PollingBit(wInOutput[24],0)	
#define CIO02401                    PollingBit(wInOutput[24],1)	
#define CIO02402                    PollingBit(wInOutput[24],2)	
#define CIO02403                    PollingBit(wInOutput[24],3)	
#define CIO02404                    PollingBit(wInOutput[24],4)	
#define CIO02405                    PollingBit(wInOutput[24],5)	
#define CIO02406                    PollingBit(wInOutput[24],6)	
#define CIO02407                    PollingBit(wInOutput[24],7)	
#define CIO02408                    PollingBit(wInOutput[24],8)	
#define CIO02409                    PollingBit(wInOutput[24],9)	
#define CIO02410                    PollingBit(wInOutput[24],10)	
#define CIO02411                    PollingBit(wInOutput[24],11)	
#define CIO02412                    PollingBit(wInOutput[24],12)	
#define CIO02413                    PollingBit(wInOutput[24],13)	
#define CIO02414                    PollingBit(wInOutput[24],14)	
#define CIO02415                    PollingBit(wInOutput[24],15)	
  
#define CIO02500                    PollingBit(wInOutput[25],0)	
#define CIO02501                    PollingBit(wInOutput[25],1)	
#define CIO02502                    PollingBit(wInOutput[25],2)	
#define CIO02503                    PollingBit(wInOutput[25],3)	
#define CIO02504                    PollingBit(wInOutput[25],4)	
#define CIO02505                    PollingBit(wInOutput[25],5)	
#define CIO02506                    PollingBit(wInOutput[25],6)	
#define CIO02507                    PollingBit(wInOutput[25],7)	
#define CIO02508                    PollingBit(wInOutput[25],8)	
#define CIO02509                    PollingBit(wInOutput[25],9)	
#define CIO02510                    PollingBit(wInOutput[25],10)	
#define CIO02511                    PollingBit(wInOutput[25],11)	
#define CIO02512                    PollingBit(wInOutput[25],12)	
#define CIO02513                    PollingBit(wInOutput[25],13)	
#define CIO02514                    PollingBit(wInOutput[25],14)	
#define CIO02515                    PollingBit(wInOutput[25],15)

#define CIO02600                    PollingBit(wInOutput[26],0)	
#define CIO02601                    PollingBit(wInOutput[26],1)	
#define CIO02602                    PollingBit(wInOutput[26],2)	
#define CIO02603                    PollingBit(wInOutput[26],3)	
#define CIO02604                    PollingBit(wInOutput[26],4)	
#define CIO02605                    PollingBit(wInOutput[26],5)	
#define CIO02606                    PollingBit(wInOutput[26],6)	
#define CIO02607                    PollingBit(wInOutput[26],7)	
#define CIO02608                    PollingBit(wInOutput[26],8)	
#define CIO02609                    PollingBit(wInOutput[26],9)	
#define CIO02610                    PollingBit(wInOutput[26],10)	
#define CIO02611                    PollingBit(wInOutput[26],11)	
#define CIO02612                    PollingBit(wInOutput[26],12)	
#define CIO02613                    PollingBit(wInOutput[26],13)	
#define CIO02614                    PollingBit(wInOutput[26],14)	
#define CIO02615                    PollingBit(wInOutput[26],15)	

#define CIO02700                    PollingBit(wInOutput[27],0)	
#define CIO02701                    PollingBit(wInOutput[27],1)	
#define CIO02702                    PollingBit(wInOutput[27],2)	
#define CIO02703                    PollingBit(wInOutput[27],3)	
#define CIO02704                    PollingBit(wInOutput[27],4)	
#define CIO02705                    PollingBit(wInOutput[27],5)	
#define CIO02706                    PollingBit(wInOutput[27],6)	
#define CIO02707                    PollingBit(wInOutput[27],7)	
#define CIO02708                    PollingBit(wInOutput[27],8)	
#define CIO02709                    PollingBit(wInOutput[27],9)	
#define CIO02710                    PollingBit(wInOutput[27],10)	
#define CIO02711                    PollingBit(wInOutput[27],11)	
#define CIO02712                    PollingBit(wInOutput[27],12)	
#define CIO02713                    PollingBit(wInOutput[27],13)	
#define CIO02714                    PollingBit(wInOutput[27],14)	
#define CIO02715                    PollingBit(wInOutput[27],15)	

#define CIO02800                    PollingBit(wInOutput[28],0)	
#define CIO02801                    PollingBit(wInOutput[28],1)	
#define CIO02802                    PollingBit(wInOutput[28],2)	
#define CIO02803                    PollingBit(wInOutput[28],3)	
#define CIO02804                    PollingBit(wInOutput[28],4)	
#define CIO02805                    PollingBit(wInOutput[28],5)	
#define CIO02806                    PollingBit(wInOutput[28],6)	
#define CIO02807                    PollingBit(wInOutput[28],7)	
#define CIO02808                    PollingBit(wInOutput[28],8)	
#define CIO02809                    PollingBit(wInOutput[28],9)	
#define CIO02810                    PollingBit(wInOutput[28],10)	
#define CIO02811                    PollingBit(wInOutput[28],11)	
#define CIO02812                    PollingBit(wInOutput[28],12)	
#define CIO02813                    PollingBit(wInOutput[28],13)	
#define CIO02814                    PollingBit(wInOutput[28],14)	
#define CIO02815                    PollingBit(wInOutput[28],15)	

#define CIO02900                    PollingBit(wInOutput[29],0)	
#define CIO02901                    PollingBit(wInOutput[29],1)	
#define CIO02902                    PollingBit(wInOutput[29],2)	
#define CIO02903                    PollingBit(wInOutput[29],3)	
#define CIO02904                    PollingBit(wInOutput[29],4)	
#define CIO02905                    PollingBit(wInOutput[29],5)	
#define CIO02906                    PollingBit(wInOutput[29],6)	
#define CIO02907                    PollingBit(wInOutput[29],7)	
#define CIO02908                    PollingBit(wInOutput[29],8)	
#define CIO02909                    PollingBit(wInOutput[29],9)	
#define CIO02910                    PollingBit(wInOutput[29],10)	
#define CIO02911                    PollingBit(wInOutput[29],11)	
#define CIO02912                    PollingBit(wInOutput[29],12)	
#define CIO02913                    PollingBit(wInOutput[29],13)	
#define CIO02914                    PollingBit(wInOutput[29],14)	
#define CIO02915                    PollingBit(wInOutput[29],15)

#define CIO03000                    PollingBit(wInOutput[30],0)	
#define CIO03001                    PollingBit(wInOutput[30],1)	
#define CIO03002                    PollingBit(wInOutput[30],2)	
#define CIO03003                    PollingBit(wInOutput[30],3)	
#define CIO03004                    PollingBit(wInOutput[30],4)	
#define CIO03005                    PollingBit(wInOutput[30],5)	
#define CIO03006                    PollingBit(wInOutput[30],6)	
#define CIO03007                    PollingBit(wInOutput[30],7)	
#define CIO03008                    PollingBit(wInOutput[30],8)	
#define CIO03009                    PollingBit(wInOutput[30],9)	
#define CIO03010                    PollingBit(wInOutput[30],10)	
#define CIO03011                    PollingBit(wInOutput[30],11)	
#define CIO03012                    PollingBit(wInOutput[30],12)	
#define CIO03013                    PollingBit(wInOutput[30],13)	
#define CIO03014                    PollingBit(wInOutput[30],14)	
#define CIO03015                    PollingBit(wInOutput[30],15)

#define CIO03100                    PollingBit(wInOutput[31],0)	
#define CIO03101                    PollingBit(wInOutput[31],1)	
#define CIO03102                    PollingBit(wInOutput[31],2)	
#define CIO03103                    PollingBit(wInOutput[31],3)	
#define CIO03104                    PollingBit(wInOutput[31],4)	
#define CIO03105                    PollingBit(wInOutput[31],5)	
#define CIO03106                    PollingBit(wInOutput[31],6)	
#define CIO03107                    PollingBit(wInOutput[31],7)	
#define CIO03108                    PollingBit(wInOutput[31],8)	
#define CIO03109                    PollingBit(wInOutput[31],9)	
#define CIO03110                    PollingBit(wInOutput[31],10)	
#define CIO03111                    PollingBit(wInOutput[31],11)	
#define CIO03112                    PollingBit(wInOutput[31],12)	
#define CIO03113                    PollingBit(wInOutput[31],13)	
#define CIO03114                    PollingBit(wInOutput[31],14)	
#define CIO03115                    PollingBit(wInOutput[31],15)

#define CIO03200                    PollingBit(wInOutput[32],0)	
#define CIO03201                    PollingBit(wInOutput[32],1)	
#define CIO03202                    PollingBit(wInOutput[32],2)	
#define CIO03203                    PollingBit(wInOutput[32],3)	
#define CIO03204                    PollingBit(wInOutput[32],4)	
#define CIO03205                    PollingBit(wInOutput[32],5)	
#define CIO03206                    PollingBit(wInOutput[32],6)	
#define CIO03207                    PollingBit(wInOutput[32],7)	
#define CIO03208                    PollingBit(wInOutput[32],8)	
#define CIO03209                    PollingBit(wInOutput[32],9)	
#define CIO03210                    PollingBit(wInOutput[32],10)	
#define CIO03211                    PollingBit(wInOutput[32],11)	
#define CIO03212                    PollingBit(wInOutput[32],12)	
#define CIO03213                    PollingBit(wInOutput[32],13)	
#define CIO03214                    PollingBit(wInOutput[32],14)	
#define CIO03215                    PollingBit(wInOutput[32],15)

#define CIO03300                    PollingBit(wInOutput[33],0)	
#define CIO03301                    PollingBit(wInOutput[33],1)	
#define CIO03302                    PollingBit(wInOutput[33],2)	
#define CIO03303                    PollingBit(wInOutput[33],3)	
#define CIO03304                    PollingBit(wInOutput[33],4)	
#define CIO03305                    PollingBit(wInOutput[33],5)	
#define CIO03306                    PollingBit(wInOutput[33],6)	
#define CIO03307                    PollingBit(wInOutput[33],7)	
#define CIO03308                    PollingBit(wInOutput[33],8)	
#define CIO03309                    PollingBit(wInOutput[33],9)	
#define CIO03310                    PollingBit(wInOutput[33],10)	
#define CIO03311                    PollingBit(wInOutput[33],11)	
#define CIO03312                    PollingBit(wInOutput[33],12)	
#define CIO03313                    PollingBit(wInOutput[33],13)	
#define CIO03314                    PollingBit(wInOutput[33],14)	
#define CIO03315                    PollingBit(wInOutput[33],15)

#define CIO03400                    PollingBit(wInOutput[34],0)	
#define CIO03401                    PollingBit(wInOutput[34],1)	
#define CIO03402                    PollingBit(wInOutput[34],2)	
#define CIO03403                    PollingBit(wInOutput[34],3)	
#define CIO03404                    PollingBit(wInOutput[34],4)	
#define CIO03405                    PollingBit(wInOutput[34],5)	
#define CIO03406                    PollingBit(wInOutput[34],6)	
#define CIO03407                    PollingBit(wInOutput[34],7)	
#define CIO03408                    PollingBit(wInOutput[34],8)	
#define CIO03409                    PollingBit(wInOutput[34],9)	
#define CIO03410                    PollingBit(wInOutput[34],10)	
#define CIO03411                    PollingBit(wInOutput[34],11)	
#define CIO03412                    PollingBit(wInOutput[34],12)	
#define CIO03413                    PollingBit(wInOutput[34],13)	
#define CIO03414                    PollingBit(wInOutput[34],14)	
#define CIO03415                    PollingBit(wInOutput[34],15)

#define CIO03500                    PollingBit(wInOutput[35],0)	
#define CIO03501                    PollingBit(wInOutput[35],1)	
#define CIO03502                    PollingBit(wInOutput[35],2)	
#define CIO03503                    PollingBit(wInOutput[35],3)	
#define CIO03504                    PollingBit(wInOutput[35],4)	
#define CIO03505                    PollingBit(wInOutput[35],5)	
#define CIO03506                    PollingBit(wInOutput[35],6)	
#define CIO03507                    PollingBit(wInOutput[35],7)	
#define CIO03508                    PollingBit(wInOutput[35],8)	
#define CIO03509                    PollingBit(wInOutput[35],9)	
#define CIO03510                    PollingBit(wInOutput[35],10)	
#define CIO03511                    PollingBit(wInOutput[35],11)	
#define CIO03512                    PollingBit(wInOutput[35],12)	
#define CIO03513                    PollingBit(wInOutput[35],13)	
#define CIO03514                    PollingBit(wInOutput[35],14)	
#define CIO03515                    PollingBit(wInOutput[35],15)

#define CIO03600                    PollingBit(wInOutput[36],0)	
#define CIO03601                    PollingBit(wInOutput[36],1)	
#define CIO03602                    PollingBit(wInOutput[36],2)	
#define CIO03603                    PollingBit(wInOutput[36],3)	
#define CIO03604                    PollingBit(wInOutput[36],4)	
#define CIO03605                    PollingBit(wInOutput[36],5)	
#define CIO03606                    PollingBit(wInOutput[36],6)	
#define CIO03607                    PollingBit(wInOutput[36],7)	
#define CIO03608                    PollingBit(wInOutput[36],8)	
#define CIO03609                    PollingBit(wInOutput[36],9)	
#define CIO03610                    PollingBit(wInOutput[36],10)	
#define CIO03611                    PollingBit(wInOutput[36],11)	
#define CIO03612                    PollingBit(wInOutput[36],12)	
#define CIO03613                    PollingBit(wInOutput[36],13)	
#define CIO03614                    PollingBit(wInOutput[36],14)	
#define CIO03615                    PollingBit(wInOutput[36],15)

#define CIO03700                    PollingBit(wInOutput[37],0)	
#define CIO03701                    PollingBit(wInOutput[37],1)	
#define CIO03702                    PollingBit(wInOutput[37],2)	
#define CIO03703                    PollingBit(wInOutput[37],3)	
#define CIO03704                    PollingBit(wInOutput[37],4)	
#define CIO03705                    PollingBit(wInOutput[37],5)	
#define CIO03706                    PollingBit(wInOutput[37],6)	
#define CIO03707                    PollingBit(wInOutput[37],7)	
#define CIO03708                    PollingBit(wInOutput[37],8)	
#define CIO03709                    PollingBit(wInOutput[37],9)	
#define CIO03710                    PollingBit(wInOutput[37],10)	
#define CIO03711                    PollingBit(wInOutput[37],11)	
#define CIO03712                    PollingBit(wInOutput[37],12)	
#define CIO03713                    PollingBit(wInOutput[37],13)	
#define CIO03714                    PollingBit(wInOutput[37],14)	
#define CIO03715                    PollingBit(wInOutput[37],15)		

#define CIO03800                    PollingBit(wInOutput[38],0)	
#define CIO03801                    PollingBit(wInOutput[38],1)	
#define CIO03802                    PollingBit(wInOutput[38],2)	
#define CIO03803                    PollingBit(wInOutput[38],3)	
#define CIO03804                    PollingBit(wInOutput[38],4)	
#define CIO03805                    PollingBit(wInOutput[38],5)	
#define CIO03806                    PollingBit(wInOutput[38],6)	
#define CIO03807                    PollingBit(wInOutput[38],7)	
#define CIO03808                    PollingBit(wInOutput[38],8)	
#define CIO03809                    PollingBit(wInOutput[38],9)	
#define CIO03810                    PollingBit(wInOutput[38],10)	
#define CIO03811                    PollingBit(wInOutput[38],11)	
#define CIO03812                    PollingBit(wInOutput[38],12)	
#define CIO03813                    PollingBit(wInOutput[38],13)	
#define CIO03814                    PollingBit(wInOutput[38],14)	
#define CIO03815                    PollingBit(wInOutput[38],15)

#define CIO03900                    PollingBit(wInOutput[39],0)	
#define CIO03901                    PollingBit(wInOutput[39],1)	
#define CIO03902                    PollingBit(wInOutput[39],2)	
#define CIO03903                    PollingBit(wInOutput[39],3)	
#define CIO03904                    PollingBit(wInOutput[39],4)	
#define CIO03905                    PollingBit(wInOutput[39],5)	
#define CIO03906                    PollingBit(wInOutput[39],6)	
#define CIO03907                    PollingBit(wInOutput[39],7)	
#define CIO03908                    PollingBit(wInOutput[39],8)	
#define CIO03909                    PollingBit(wInOutput[39],9)	
#define CIO03910                    PollingBit(wInOutput[39],10)	
#define CIO03911                    PollingBit(wInOutput[39],11)	
#define CIO03912                    PollingBit(wInOutput[39],12)	
#define CIO03913                    PollingBit(wInOutput[39],13)	
#define CIO03914                    PollingBit(wInOutput[39],14)	
#define CIO03915                    PollingBit(wInOutput[39],15)

/////////////////////////////////////////////////////////////////
/////// Touch Button Read I/O 


/////////////////////////////////////////////////////////////////
/////// Touch Button Read I/O 

#define CIO100000                    PollingBit(wTouchInput[0],0 )	
#define CIO100001                    PollingBit(wTouchInput[0],1 )	
#define CIO100002                    PollingBit(wTouchInput[0],2 )	
#define CIO100003                    PollingBit(wTouchInput[0],3 )	
#define CIO100004                    PollingBit(wTouchInput[0],4 )	
#define CIO100005                    PollingBit(wTouchInput[0],5 )	
#define CIO100006                    PollingBit(wTouchInput[0],6 )	
#define CIO100007                    PollingBit(wTouchInput[0],7 )	
#define CIO100008                    PollingBit(wTouchInput[0],8 )	
#define CIO100009                    PollingBit(wTouchInput[0],9 )	
#define CIO100010                    PollingBit(wTouchInput[0],10)	
#define CIO100011                    PollingBit(wTouchInput[0],11)	
#define CIO100012                    PollingBit(wTouchInput[0],12)	
#define CIO100013                    PollingBit(wTouchInput[0],13)	
#define CIO100014                    PollingBit(wTouchInput[0],14)	
#define CIO100015                    PollingBit(wTouchInput[0],15)

//////////////////////// Motor Jog Cw Ccw Button On Check 

#define CIO100414                    PollingBit(wTouchInput[4],14)	
#define CIO100415                    PollingBit(wTouchInput[4],15)

#define CIO100514                    PollingBit(wTouchInput[5],14)	
#define CIO100515                    PollingBit(wTouchInput[5],15)

#define CIO100614                    PollingBit(wTouchInput[6],14)	
#define CIO100615                    PollingBit(wTouchInput[6],15)

#define CIO100714                    PollingBit(wTouchInput[7],14)	
#define CIO100715                    PollingBit(wTouchInput[7],15)

#define CIO100814                    PollingBit(wTouchInput[8],14)	
#define CIO100815                    PollingBit(wTouchInput[8],15)

#define CIO100914                    PollingBit(wTouchInput[9],14)	
#define CIO100915                    PollingBit(wTouchInput[9],15)

#define CIO101014                    PollingBit(wTouchInput[10],14)	
#define CIO101015                    PollingBit(wTouchInput[10],15)

#define CIO101114                    PollingBit(wTouchInput[11],14)	
#define CIO101115                    PollingBit(wTouchInput[11],15)

#define CIO101214                    PollingBit(wTouchInput[12],14)	
#define CIO101215                    PollingBit(wTouchInput[12],15)

#define CIO101314                    PollingBit(wTouchInput[13],14)	
#define CIO101315                    PollingBit(wTouchInput[13],15)

#define CIO101414                    PollingBit(wTouchInput[14],14)	
#define CIO101415                    PollingBit(wTouchInput[14],15)

#define CIO101514                    PollingBit(wTouchInput[15],14)	
#define CIO101515                    PollingBit(wTouchInput[15],15)

#define CIO101614                    PollingBit(wTouchInput[16],14)	
#define CIO101615                    PollingBit(wTouchInput[16],15)

#define CIO101714                    PollingBit(wTouchInput[17],14)	
#define CIO101715                    PollingBit(wTouchInput[17],15)

#define CIO101814                    PollingBit(wTouchInput[18],14)	
#define CIO101815                    PollingBit(wTouchInput[18],15)

#define CIO101914                    PollingBit(wTouchInput[19],14)	
#define CIO101915                    PollingBit(wTouchInput[19],15)

#define CIO102014                    PollingBit(wTouchInput[20],14)	
#define CIO102015                    PollingBit(wTouchInput[20],15)

#define CIO102114                    PollingBit(wTouchInput[21],14)	
#define CIO102115                    PollingBit(wTouchInput[21],15)


#define CIO102214                    PollingBit(wTouchInput[22],14)	
#define CIO102215                    PollingBit(wTouchInput[22],15)


#define CIO102314                    PollingBit(wTouchInput[23],14)	
#define CIO102315                    PollingBit(wTouchInput[23],15)

#define CIO102414                    PollingBit(wTouchInput[24],14)	
#define CIO102415                    PollingBit(wTouchInput[24],15)

#define CIO102514                    PollingBit(wTouchInput[25],14)	
#define CIO102515                    PollingBit(wTouchInput[25],15)

#define CIO102614                    PollingBit(wTouchInput[26],14)	
#define CIO102615                    PollingBit(wTouchInput[26],15)

#define CIO102714                    PollingBit(wTouchInput[27],14)	
#define CIO102715                    PollingBit(wTouchInput[27],15)

#define CIO102814                    PollingBit(wTouchInput[28],14)	
#define CIO102815                    PollingBit(wTouchInput[28],15)

#define CIO102914                    PollingBit(wTouchInput[29],14)	
#define CIO102915                    PollingBit(wTouchInput[29],15)

#define CIO103014                    PollingBit(wTouchInput[30],14)	
#define CIO103015                    PollingBit(wTouchInput[30],15)

#define CIO103114                    PollingBit(wTouchInput[31],14)	
#define CIO103115                    PollingBit(wTouchInput[31],15)

#define CIO103214                    PollingBit(wTouchInput[32],14)	
#define CIO103215                    PollingBit(wTouchInput[32],15)

#define CIO103314                    PollingBit(wTouchInput[33],14)	
#define CIO103315                    PollingBit(wTouchInput[33],15)

#define CIO103414                    PollingBit(wTouchInput[34],14)	
#define CIO103415                    PollingBit(wTouchInput[34],15)

#define CIO103514                    PollingBit(wTouchInput[35],14)	
#define CIO103515                    PollingBit(wTouchInput[35],15)

#define CIO103614                    PollingBit(wTouchInput[36],14)	
#define CIO103615                    PollingBit(wTouchInput[36],15)

#define CIO103714                    PollingBit(wTouchInput[37],14)	
#define CIO103715                    PollingBit(wTouchInput[37],15)

#define CIO103814                    PollingBit(wTouchInput[38],14)	
#define CIO103815                    PollingBit(wTouchInput[38],15)

#define CIO103914                    PollingBit(wTouchInput[39],14)	
#define CIO103915                    PollingBit(wTouchInput[39],15)

#define CIO104014                    PollingBit(wTouchInput[40],14)	
#define CIO104015                    PollingBit(wTouchInput[40],15)

#define CIO104114                    PollingBit(wTouchInput[41],14)	
#define CIO104115                    PollingBit(wTouchInput[41],15)

#define CIO104214                    PollingBit(wTouchInput[42],14)	
#define CIO104215                    PollingBit(wTouchInput[42],15)

#define CIO104314                    PollingBit(wTouchInput[43],14)	
#define CIO104315                    PollingBit(wTouchInput[43],15)
/////////////////////////////////////////////////////////////////////////
// Robot Command

#define ROBOT_AZRHOMEON			1
#define ROBOT_AZRHOMEPOF		2
#define ROBOT_THOME				3
#define ROBOT_A1CSTWLD			4
#define ROBOT_A1CSTWULD			5
#define ROBOT_A2CSTWULD			6
#define ROBOT_A1A2CSTRDYP		7
#define ROBOT_A1AGNWLD			8
#define ROBOT_A1AGNWULD			9
#define ROBOT_A2AGNWULD			10
#define ROBOT_A1LDA2ULDAGN		11
#define ROBOT_A2LDA1ULDAGN		12
#define ROBOT_A1A2AGNRDYP		13
#define ROBOT_A1A2CENTRDYP		14
#define ROBOT_A1CENTWLD180		15
#define ROBOT_A2CENTWULD0		16
#define ROBOT_A1CENTWULD0		17
#define ROBOT_A1CENTWULD180		18
#define ROBOT_A2CENTWULD180		19
#define ROBOT_A1JBOXWULD180		20
#define ROBOT_A2JBOXWULD180		21
#define ROBOT_A1A1JBOXRDYP		22
#define ROBOT_A1LASERWULD		23
#define ROBOT_A2LASERWULD		24
#define ROBOT_A1A2SAFETYP		25
#define ROBOT_A1A2LASERRDYP		26
#define ROBOT_A1RINS1WLD		27
#define ROBOT_A1A2RINS1RDYP		28
#define ROBOT_A1RINS2WLD		29
#define ROBOT_A1A2RINS2RDYP		30
#define ROBOT_A1INSPTWLD		31
#define ROBOT_A1INSPTWULD		32
#define ROBOT_A2INSPTWULD		33
#define ROBOT_A1LDA2ULDINSPT	34
#define ROBOT_A2LDA1ULDINSPT	35
#define ROBOT_A1A2INPTRDYP		36
#define ROBOT_A1TAXIS180		37
#define ROBOT_A1TAXIS0			38
#define ROBOT_A2TAXIS180		39
#define ROBOT_A2TAXIS0			40
#define ROBOT_BANKCHANG			41


/////////////////////////////////////////////////////////////////////////
// PC to Robot Command

#define RCMD_ROBOT_AZRHOMEPON				"//RD//ERC//T10//$101//$103//T500//$102//$104//$102//$103//$105//!E//"
#define RCMD_ROBOT_AZRHOMEPOF				"// //"
#define RCMD_ROBOT_THOME					"//T10//$20//$30//T500//!P D,10/!Q D//!E//"
#define RCMD_ROBOT_A1CSTWLD					"//SP8//$1PM"
#define RCMD_ROBOT_A1CSTWULD				"//SP8//$1PM"
#define RCMD_ROBOT_A2CSTWULD				"//SP8//$1PM"
#define RCMD_ROBOT_A1A2CSTRDYP				"//SP8//$1PMT"
#define RCMD_ROBOT_A1AGNWLD					"//SP8//$1PM1//DS11/$1B1234+//T10//$111//!E//"
#define RCMD_ROBOT_A1AGNWULD				"//SP8//$1PMT1//$1B1234+//$1M1PM1//DS10//T10//$1B1234-//$111//!E//"
#define RCMD_ROBOT_A2AGNWULD				"//SP8//$1PMT2//$1B1234+//$1M3PM2//DS20//T10//$1B1234-//$113//!E//"
#define RCMD_ROBOT_A1LDA2ULDAGN				"//SP8//$1PM1//DS11/$1B1234+//T10//$111//$1PMT2//$1B1234+//$1M3PM2//DS20//T10//$1B1234-//$113//!E//"
#define RCMD_ROBOT_A2LDA1ULDAGN				"//SP8//$1PM2//DS21/$1B1234+//T10//$113//$1PMT1//$1B1234+//$1M1PM1//DS10//T10//$1B1234-//$111//!E//"
#define RCMD_ROBOT_A1A2AGNRDYP				"//SP8//$1PMT1//"
#define RCMD_ROBOT_A1A2CENTRDYP				"//SP8//$1PMT3//"
#define RCMD_ROBOT_A1CENTWLD180				"//SP8//$1PM4//$1B1734-//DS11//T10//$1B1734+//$111//!E//"
#define RCMD_ROBOT_A2CENTWULD0				"//SP8//$1PMT5//$1B1484+//$1M3PM5//DS20//T10//$1B1484-//$113//!E//"
#define RCMD_ROBOT_A1CENTWULD0				"//SP8//$1PMT3//$1B1484+//$1M1PM3//DS10//T10//$1B1484-//$111//!E//"
#define RCMD_ROBOT_A1CENTWULD180			"//SP8//$1PM4//$1B1734-//DS10//T10//$1B1734+//$111//!E//"
#define RCMD_ROBOT_A2CENTWULD180			"//SP8//$1PM6//$1B1734-//DS10//T10//$1B1734+//$113//!E//"
#define RCMD_ROBOT_A1JBOXWULD180			"//SP8//$1PM7//$1B1984-//DS10//T10//$1B1984+//$111//!E//"
#define RCMD_ROBOT_A2JBOXWULD180			"//SP8//$1PM8//$1B1984-//DS20//T10//$1B1984+//$113//!E//"
#define RCMD_ROBOT_A1A1JBOXRDYP				"//SP8//$1PMT7//"
#define RCMD_ROBOT_A1LASERWULD				"//SP8//$1PM9//DS10//T10//$1B2234-//$111//!E//"
#define RCMD_ROBOT_A2LASERWULD				"//SP8//$1PM10//DS20//T10//$1B2234-//$113//!E//"
#define RCMD_ROBOT_A1A2SAFETYP				"//SP8//$1PMT19//"
#define RCMD_ROBOT_A1A2LASERRDYP			"//SP8//$1PMT9//"
#define RCMD_ROBOT_A1RINS1WLD				"//SP8//$1PM11//DS11/$1B1244+//T10//$111//!E//"
#define RCMD_ROBOT_A1A2RINS1RDYP			"//SP8//$1PMT11//"
#define RCMD_ROBOT_A1RINS2WLD				"//SP8//$1PM13//DS11/$1B1494+//T10//$111//!E//"
#define RCMD_ROBOT_A1A2RINS2RDYP			"//SP8//$1PMTT13//"
#define RCMD_ROBOT_A1INSPTWLD				"//SP8//$1PM15//DS11/$1B1744+//T10//$111//!E//"
#define RCMD_ROBOT_A1INSPTWULD				"//SP8//$1PMT15//$1B1744+//$1M1PM15//DS10//$1B1744-//$111//!E//"
#define RCMD_ROBOT_A2INSPTWULD				"//SP8//$1PMT16//$1B1744+//$1M3PM16//DS20//$1B1744-//$113//!E//"
#define RCMD_ROBOT_A1LDA2ULDINSPT			"//SP8//$1PM15//DS11/$1B1744+//T10//$111//$1PMT16//$1B1744+//$1M3PM16//DS20//T10//$1B1744-//$113//!E//"
#define RCMD_ROBOT_A2LDA1ULDINSPT			"//SP8//$1PM16//DS21/$1B1744+//T10//$113//$1PMT15//$1B1744+//$1M1PM15//DS10//T10//$1B1744-//$111//!E//"
#define RCMD_ROBOT_A1A2INPTRDYP				"//SP8//$1PMT15//"
#define RCMD_ROBOT_A1TAXIS180				"//SP8//$1M2PM17/$1M4PM17//$1M1PM17//$2PM,1//$111//T50//!P D,11/!Q D//!E//"
#define RCMD_ROBOT_A1TAXIS0					"//SP8//$1M2PM17/$1M4PM17//$1M1PM17//$2PM,2//$111//T50//!P D,12/!Q D//!E//"
#define RCMD_ROBOT_A2TAXIS180				"//SP8//$1M2PM18/$1M4PM18//$1M3PM18//$3PM,1//$113//T50//!P D,22/!Q D//!E//"
#define RCMD_ROBOT_A2TAXIS0					"//SP8//$1M2PM18/$1M4PM18//$1M3PM18//$3PM,2//$113//T50//!P D,23/!Q D//!E//"
#define RCMD_ROBOT_BANKCHANG				"//BC//"
#define RCMD_ROBOT_CMDEND					"//!E//"

////////////////////////////////////
////////////  Enable Bit Check

#define E50700_            PollingBit(wEmemoryRead[7],0 )		   // Auto Ready
#define E50701_              PollingBit(wEmemoryRead[7],1 )		   // 
#define E50702_              PollingBit(wEmemoryRead[7],2 )
#define E50703_                       PollingBit(wEmemoryRead[7],3 )
#define E50704_                       PollingBit(wEmemoryRead[7],4 )			
#define E50705_            PollingBit(wEmemoryRead[7],5 )
#define E50706_     PollingBit(wEmemoryRead[7],6 )
#define E50707_           PollingBit(wEmemoryRead[7],7 )
#define E50708_             PollingBit(wEmemoryRead[7],8 )
#define E50709_             PollingBit(wEmemoryRead[7],9 )
#define E50710_             PollingBit(wEmemoryRead[7],10)
#define E50711_             PollingBit(wEmemoryRead[7],11)
#define E50712_             PollingBit(wEmemoryRead[7],12)
#define E50713_             PollingBit(wEmemoryRead[7],13)
#define E50714_             PollingBit(wEmemoryRead[7],14)
#define E50715_            PollingBit(wEmemoryRead[7],15)


////////////////////////////////////
////////////  Enable Bit Check

#define E50800                       PollingBit(wEmemoryRead[8],0 )		   // Recipe Change Enable
#define E50801_ERRORVIEW            PollingBit(wEmemoryRead[8],1 )		   // Error Event
#define E50802_MAPVIEW              PollingBit(wEmemoryRead[8],2 )
#define E50803                       PollingBit(wEmemoryRead[8],3 )
#define E50804_AUTORUN               PollingBit(wEmemoryRead[8],4 )			// Auto Running
#define E50805                       PollingBit(wEmemoryRead[8],5 )
#define E50806                       PollingBit(wEmemoryRead[8],6 )
#define E50807                       PollingBit(wEmemoryRead[8],7 )
#define E50808                       PollingBit(wEmemoryRead[8],8 )
#define E50809                       PollingBit(wEmemoryRead[8],9 )
#define E50810                       PollingBit(wEmemoryRead[8],10)
#define E50811          PollingBit(wEmemoryRead[8],11)
#define E50812                       PollingBit(wEmemoryRead[8],12)
#define E50813                       PollingBit(wEmemoryRead[8],13)
#define E50814                       PollingBit(wEmemoryRead[8],14)
#define E50815                       PollingBit(wEmemoryRead[8],15)



/// Motor Sensor Check 

#define M1ORIGINEND                        PollingBit(wEmemoryRead[38],0 )
#define M2ORIGINEND                        PollingBit(wEmemoryRead[38],1 )
#define M3ORIGINEND                        PollingBit(wEmemoryRead[38],2 )
#define M4ORIGINEND                        PollingBit(wEmemoryRead[38],3 )
#define M5ORIGINEND                        PollingBit(wEmemoryRead[38],4 )
#define M6ORIGINEND                        PollingBit(wEmemoryRead[38],5 )
#define M7ORIGINEND                        PollingBit(wEmemoryRead[38],6 )
#define M8ORIGINEND                        PollingBit(wEmemoryRead[38],7 )
#define M9ORIGINEND                        PollingBit(wEmemoryRead[38],8 )
#define M10ORIGINEND                       PollingBit(wEmemoryRead[38],9 )
#define M11ORIGINEND                       PollingBit(wEmemoryRead[38],10)
#define M12ORIGINEND                       PollingBit(wEmemoryRead[38],11)
#define M13ORIGINEND                       PollingBit(wEmemoryRead[38],12)
#define M14ORIGINEND                       PollingBit(wEmemoryRead[38],13)
#define M15ORIGINEND                       PollingBit(wEmemoryRead[38],14)
#define M16ORIGINEND                       PollingBit(wEmemoryRead[38],15)

#define M17ORIGINEND                        PollingBit(wEmemoryRead[39],0 )
#define M18ORIGINEND                        PollingBit(wEmemoryRead[39],1 )
#define M19ORIGINEND                        PollingBit(wEmemoryRead[39],2 )
#define M20ORIGINEND                        PollingBit(wEmemoryRead[39],3 )
#define M21ORIGINEND                        PollingBit(wEmemoryRead[39],4 )
#define M22ORIGINEND                        PollingBit(wEmemoryRead[39],5 )
#define M23ORIGINEND                        PollingBit(wEmemoryRead[39],6 )
#define M24ORIGINEND                        PollingBit(wEmemoryRead[39],7 )
#define M25ORIGINEND                        PollingBit(wEmemoryRead[39],8 )
#define M26ORIGINEND                        PollingBit(wEmemoryRead[39],9 )
#define M27ORIGINEND                        PollingBit(wEmemoryRead[39],10)
#define M28ORIGINEND                        PollingBit(wEmemoryRead[39],11)
#define M29ORIGINEND                        PollingBit(wEmemoryRead[39],12)
#define M30ORIGINEND                        PollingBit(wEmemoryRead[39],13)
#define M31ORIGINEND                        PollingBit(wEmemoryRead[39],14)
#define M32ORIGINEND                        PollingBit(wEmemoryRead[39],15)

#define M33ORIGINEND                        PollingBit(wEmemoryRead[40],0)
#define M34ORIGINEND                        PollingBit(wEmemoryRead[40],1)
#define M35ORIGINEND                        PollingBit(wEmemoryRead[40],2)
#define M36ORIGINEND                        PollingBit(wEmemoryRead[40],3)
#define M37ORIGINEND                        PollingBit(wEmemoryRead[40],4)
#define M38ORIGINEND                        PollingBit(wEmemoryRead[40],5)
#define M39ORIGINEND                        PollingBit(wEmemoryRead[40],6)
#define M40ORIGINEND                        PollingBit(wEmemoryRead[40],7)

#define M1HOME                       PollingBit(wEmemoryRead[42],0 )
#define M1PLMT                       PollingBit(wEmemoryRead[42],1 )
#define M1NLMT                       PollingBit(wEmemoryRead[42],2 )
#define M1BUSY                       PollingBit(wEmemoryRead[42],3 )
#define M2HOME                       PollingBit(wEmemoryRead[42],4 )
#define M2PLMT                       PollingBit(wEmemoryRead[42],5 )
#define M2NLMT                       PollingBit(wEmemoryRead[42],6 )
#define M2BUSY                       PollingBit(wEmemoryRead[42],7 )
#define M3HOME                       PollingBit(wEmemoryRead[42],8 )
#define M3PLMT                       PollingBit(wEmemoryRead[42],9 )
#define M3NLMT                       PollingBit(wEmemoryRead[42],10)
#define M3BUSY                       PollingBit(wEmemoryRead[42],11)
#define M4HOME                       PollingBit(wEmemoryRead[42],12)
#define M4PLMT                       PollingBit(wEmemoryRead[42],13)
#define M4NLMT                       PollingBit(wEmemoryRead[42],14)
#define M4BUSY                       PollingBit(wEmemoryRead[42],15)

#define M5HOME                       PollingBit(wEmemoryRead[43],0 )
#define M5PLMT                       PollingBit(wEmemoryRead[43],1 )
#define M5NLMT                       PollingBit(wEmemoryRead[43],2 )
#define M5BUSY                       PollingBit(wEmemoryRead[43],3 )
#define M6HOME                       PollingBit(wEmemoryRead[43],4 )
#define M6PLMT                       PollingBit(wEmemoryRead[43],5 )
#define M6NLMT                       PollingBit(wEmemoryRead[43],6 )
#define M6BUSY                       PollingBit(wEmemoryRead[43],7 )
#define M7HOME                       PollingBit(wEmemoryRead[43],8 )
#define M7PLMT                       PollingBit(wEmemoryRead[43],9 )
#define M7NLMT                       PollingBit(wEmemoryRead[43],10)
#define M7BUSY                       PollingBit(wEmemoryRead[43],11)
#define M8HOME                       PollingBit(wEmemoryRead[43],12)
#define M8PLMT                       PollingBit(wEmemoryRead[43],13)
#define M8NLMT                       PollingBit(wEmemoryRead[43],14)
#define M8BUSY                       PollingBit(wEmemoryRead[43],15)

#define M9HOME                        PollingBit(wEmemoryRead[44],0 )
#define M9PLMT                        PollingBit(wEmemoryRead[44],1 )
#define M9NLMT                        PollingBit(wEmemoryRead[44],2 )
#define M9BUSY                        PollingBit(wEmemoryRead[44],3 )
#define M10HOME                       PollingBit(wEmemoryRead[44],4 )
#define M10PLMT                       PollingBit(wEmemoryRead[44],5 )
#define M10NLMT                       PollingBit(wEmemoryRead[44],6 )
#define M10BUSY                       PollingBit(wEmemoryRead[44],7 )
#define M11HOME                       PollingBit(wEmemoryRead[44],8 )
#define M11PLMT                       PollingBit(wEmemoryRead[44],9 )
#define M11NLMT                       PollingBit(wEmemoryRead[44],10)
#define M11BUSY                       PollingBit(wEmemoryRead[44],11)
#define M12HOME                       PollingBit(wEmemoryRead[44],12)
#define M12PLMT                       PollingBit(wEmemoryRead[44],13)
#define M12NLMT                       PollingBit(wEmemoryRead[44],14)
#define M12BUSY                       PollingBit(wEmemoryRead[44],15)

#define M13HOME                       PollingBit(wEmemoryRead[45],0 )
#define M13PLMT                       PollingBit(wEmemoryRead[45],1 )
#define M13NLMT                       PollingBit(wEmemoryRead[45],2 )
#define M13BUSY                       PollingBit(wEmemoryRead[45],3 )
#define M14HOME                       PollingBit(wEmemoryRead[45],4 )
#define M14PLMT                       PollingBit(wEmemoryRead[45],5 )
#define M14NLMT                       PollingBit(wEmemoryRead[45],6 )
#define M14BUSY                       PollingBit(wEmemoryRead[45],7 )
#define M15HOME                       PollingBit(wEmemoryRead[45],8 )
#define M15PLMT                       PollingBit(wEmemoryRead[45],9 )
#define M15NLMT                       PollingBit(wEmemoryRead[45],10)
#define M15BUSY                       PollingBit(wEmemoryRead[45],11)
#define M16HOME                       PollingBit(wEmemoryRead[45],12)
#define M16PLMT                       PollingBit(wEmemoryRead[45],13)
#define M16NLMT                       PollingBit(wEmemoryRead[45],14)
#define M16BUSY                       PollingBit(wEmemoryRead[45],15)

#define M17HOME                       PollingBit(wEmemoryRead[46],0 )
#define M17PLMT                       PollingBit(wEmemoryRead[46],1 )
#define M17NLMT                       PollingBit(wEmemoryRead[46],2 )
#define M17BUSY                       PollingBit(wEmemoryRead[46],3 )
#define M18HOME                       PollingBit(wEmemoryRead[46],4 )
#define M18PLMT                       PollingBit(wEmemoryRead[46],5 )
#define M18NLMT                       PollingBit(wEmemoryRead[46],6 )
#define M18BUSY                       PollingBit(wEmemoryRead[46],7 )
#define M19HOME                       PollingBit(wEmemoryRead[46],8 )
#define M19PLMT                       PollingBit(wEmemoryRead[46],9 )
#define M19NLMT                       PollingBit(wEmemoryRead[46],10)
#define M19BUSY                       PollingBit(wEmemoryRead[46],11)
#define M20HOME                       PollingBit(wEmemoryRead[46],12)
#define M20PLMT                       PollingBit(wEmemoryRead[46],13)
#define M20NLMT                       PollingBit(wEmemoryRead[46],14)
#define M20BUSY                       PollingBit(wEmemoryRead[46],15)

#define M21HOME                       PollingBit(wEmemoryRead[47],0 )
#define M21PLMT                       PollingBit(wEmemoryRead[47],1 )
#define M21NLMT                       PollingBit(wEmemoryRead[47],2 )
#define M21BUSY                       PollingBit(wEmemoryRead[47],3 )
#define M22HOME                       PollingBit(wEmemoryRead[47],4 )
#define M22PLMT                       PollingBit(wEmemoryRead[47],5 )
#define M22NLMT                       PollingBit(wEmemoryRead[47],6 )
#define M22BUSY                       PollingBit(wEmemoryRead[47],7 )
#define M23HOME                       PollingBit(wEmemoryRead[47],8 )
#define M23PLMT                       PollingBit(wEmemoryRead[47],9 )
#define M23NLMT                       PollingBit(wEmemoryRead[47],10)
#define M23BUSY                       PollingBit(wEmemoryRead[47],11)
#define M24HOME                       PollingBit(wEmemoryRead[47],12)
#define M24PLMT                       PollingBit(wEmemoryRead[47],13)
#define M24NLMT                       PollingBit(wEmemoryRead[47],14)
#define M24BUSY                       PollingBit(wEmemoryRead[47],15)


#define M25HOME                       PollingBit(wEmemoryRead[48],0 )
#define M25PLMT                       PollingBit(wEmemoryRead[48],1 )
#define M25NLMT                       PollingBit(wEmemoryRead[48],2 )
#define M25BUSY                       PollingBit(wEmemoryRead[48],3 )
#define M26HOME                       PollingBit(wEmemoryRead[48],4 )
#define M26PLMT                       PollingBit(wEmemoryRead[48],5 )
#define M26NLMT                       PollingBit(wEmemoryRead[48],6 )
#define M26BUSY                       PollingBit(wEmemoryRead[48],7 )
#define M27HOME                       PollingBit(wEmemoryRead[48],8 )
#define M27PLMT                       PollingBit(wEmemoryRead[48],9 )
#define M27NLMT                       PollingBit(wEmemoryRead[48],10)
#define M27BUSY                       PollingBit(wEmemoryRead[48],11)
#define M28HOME                       PollingBit(wEmemoryRead[48],12)
#define M28PLMT                       PollingBit(wEmemoryRead[48],13)
#define M28NLMT                       PollingBit(wEmemoryRead[48],14)
#define M28BUSY                       PollingBit(wEmemoryRead[48],15)

#define M29HOME                       PollingBit(wEmemoryRead[54],0 )
#define M29PLMT                       PollingBit(wEmemoryRead[54],1 )
#define M29NLMT                       PollingBit(wEmemoryRead[54],2 )
#define M29BUSY                       PollingBit(wEmemoryRead[54],3 )
#define M30HOME                       PollingBit(wEmemoryRead[54],4 )
#define M30PLMT                       PollingBit(wEmemoryRead[54],5 )
#define M30NLMT                       PollingBit(wEmemoryRead[54],6 )
#define M30BUSY                       PollingBit(wEmemoryRead[54],7 )
#define M31HOME                       PollingBit(wEmemoryRead[54],8 )
#define M31PLMT                       PollingBit(wEmemoryRead[54],9 )
#define M31NLMT                       PollingBit(wEmemoryRead[54],10)
#define M31BUSY                       PollingBit(wEmemoryRead[54],11)
#define M32HOME                       PollingBit(wEmemoryRead[54],12)
#define M32PLMT                       PollingBit(wEmemoryRead[54],13)
#define M32NLMT                       PollingBit(wEmemoryRead[54],14)
#define M32BUSY                       PollingBit(wEmemoryRead[54],15)

#define M33HOME                       PollingBit(wEmemoryRead[55],0 )
#define M33PLMT                       PollingBit(wEmemoryRead[55],1 )
#define M33NLMT                       PollingBit(wEmemoryRead[55],2 )
#define M33BUSY                       PollingBit(wEmemoryRead[55],3 )
#define M34HOME                       PollingBit(wEmemoryRead[55],4 )
#define M34PLMT	                      PollingBit(wEmemoryRead[55],5 )
#define M34NLMT                       PollingBit(wEmemoryRead[55],6 )
#define M34BUSY                       PollingBit(wEmemoryRead[55],7 )
#define M35HOME                       PollingBit(wEmemoryRead[55],8 )
#define M35PLMT                       PollingBit(wEmemoryRead[55],9 )
#define M35NLMT                       PollingBit(wEmemoryRead[55],10)
#define M35BUSY                       PollingBit(wEmemoryRead[55],11)
#define M36HOME                       PollingBit(wEmemoryRead[55],12)
#define M36PLMT                       PollingBit(wEmemoryRead[55],13)
#define M36NLMT                       PollingBit(wEmemoryRead[55],14)
#define M36BUSY                       PollingBit(wEmemoryRead[55],15)


#define M37HOME                       PollingBit(wEmemoryRead[51],0 )
#define M37PLMT                       PollingBit(wEmemoryRead[51],1 )
#define M37NLMT                       PollingBit(wEmemoryRead[51],2 )
#define M37BUSY                       PollingBit(wEmemoryRead[51],3 )
#define M38HOME                       PollingBit(wEmemoryRead[51],4 )
#define M38PLMT	                      PollingBit(wEmemoryRead[51],5 )
#define M38NLMT                       PollingBit(wEmemoryRead[51],6 )
#define M38BUSY                       PollingBit(wEmemoryRead[51],7 )
#define M39HOME                       PollingBit(wEmemoryRead[51],8 )
#define M39PLMT                       PollingBit(wEmemoryRead[51],9 )
#define M39NLMT                       PollingBit(wEmemoryRead[51],10)
#define M39BUSY                       PollingBit(wEmemoryRead[51],11)
#define M40HOME                       PollingBit(wEmemoryRead[51],12)
#define M40PLMT                       PollingBit(wEmemoryRead[51],13)
#define M40NLMT                       PollingBit(wEmemoryRead[51],14)
#define M40BUSY                       PollingBit(wEmemoryRead[51],15)



#define INVBIT54900                       PollingBit(wEmemoryRead[49],0 )
#define INVBIT54901                       PollingBit(wEmemoryRead[49],1 )
#define INVBIT54902                       PollingBit(wEmemoryRead[49],2 )
#define INVBIT54903                       PollingBit(wEmemoryRead[49],3 )
#define INVBIT54904                       PollingBit(wEmemoryRead[49],4 )
#define INVBIT54905                       PollingBit(wEmemoryRead[49],5 )
#define INVBIT54906                       PollingBit(wEmemoryRead[49],6 )
#define INVBIT54907                       PollingBit(wEmemoryRead[49],7 )
#define INVBIT54908                       PollingBit(wEmemoryRead[49],8 )
#define INVBIT54909                       PollingBit(wEmemoryRead[49],9 )
#define INVBIT54910                       PollingBit(wEmemoryRead[49],10)
#define INVBIT54911                       PollingBit(wEmemoryRead[49],11)
#define INVBIT54912                       PollingBit(wEmemoryRead[49],12)
#define INVBIT54913                       PollingBit(wEmemoryRead[49],13)
#define INVBIT54914                       PollingBit(wEmemoryRead[49],14)
#define INVBIT54915                       PollingBit(wEmemoryRead[49],15)

#define INVBIT55000                       PollingBit(wEmemoryRead[50],0 )
#define INVBIT55001                       PollingBit(wEmemoryRead[50],1 )
#define INVBIT55002                       PollingBit(wEmemoryRead[50],2 )
#define INVBIT55003                       PollingBit(wEmemoryRead[50],3 )
#define INVBIT55004                       PollingBit(wEmemoryRead[50],4 )
#define INVBIT55005                       PollingBit(wEmemoryRead[50],5 )
#define INVBIT55006                       PollingBit(wEmemoryRead[50],6 )
#define INVBIT55007                       PollingBit(wEmemoryRead[50],7 )
#define INVBIT55008                       PollingBit(wEmemoryRead[50],8 )
#define INVBIT55009                       PollingBit(wEmemoryRead[50],9 )
#define INVBIT55010                       PollingBit(wEmemoryRead[50],10)
#define INVBIT55011                       PollingBit(wEmemoryRead[50],11)
#define INVBIT55012                       PollingBit(wEmemoryRead[50],12)
#define INVBIT55013                       PollingBit(wEmemoryRead[50],13)
#define INVBIT55014                       PollingBit(wEmemoryRead[50],14)
#define INVBIT55015                       PollingBit(wEmemoryRead[50],15)

#define INVBIT55100                       PollingBit(wEmemoryRead[51],0 )
#define INVBIT55101                       PollingBit(wEmemoryRead[51],1 )
#define INVBIT55102                       PollingBit(wEmemoryRead[51],2 )
#define INVBIT55103                       PollingBit(wEmemoryRead[51],3 )
#define INVBIT55104                       PollingBit(wEmemoryRead[51],4 )
#define INVBIT55105                       PollingBit(wEmemoryRead[51],5 )
#define INVBIT55106                       PollingBit(wEmemoryRead[51],6 )
#define INVBIT55107                       PollingBit(wEmemoryRead[51],7 )
#define INVBIT55108                       PollingBit(wEmemoryRead[51],8 )
#define INVBIT55109                       PollingBit(wEmemoryRead[51],9 )
#define INVBIT55110                       PollingBit(wEmemoryRead[51],10)
#define INVBIT55111                       PollingBit(wEmemoryRead[51],11)
#define INVBIT55112                       PollingBit(wEmemoryRead[51],12)
#define INVBIT55113                       PollingBit(wEmemoryRead[51],13)
#define INVBIT55114                       PollingBit(wEmemoryRead[51],14)
#define INVBIT55115                       PollingBit(wEmemoryRead[51],15)

#define INVBIT55200                       PollingBit(wEmemoryRead[52],0 )
#define INVBIT55201                       PollingBit(wEmemoryRead[52],1 )
#define INVBIT55202                       PollingBit(wEmemoryRead[52],2 )
#define INVBIT55203                       PollingBit(wEmemoryRead[52],3 )
#define INVBIT55204                       PollingBit(wEmemoryRead[52],4 )
#define INVBIT55205                       PollingBit(wEmemoryRead[52],5 )
#define INVBIT55206                       PollingBit(wEmemoryRead[52],6 )
#define INVBIT55207                       PollingBit(wEmemoryRead[52],7 )
#define INVBIT55208                       PollingBit(wEmemoryRead[52],8 )
#define INVBIT55209                       PollingBit(wEmemoryRead[52],9 )
#define INVBIT55210                       PollingBit(wEmemoryRead[52],10)
#define INVBIT55211                       PollingBit(wEmemoryRead[52],11)
#define INVBIT55212                       PollingBit(wEmemoryRead[52],12)
#define INVBIT55213                       PollingBit(wEmemoryRead[52],13)
#define INVBIT55214                       PollingBit(wEmemoryRead[52],14)
#define INVBIT55215                       PollingBit(wEmemoryRead[52],15)


#define INVBIT55300                       PollingBit(wEmemoryRead[53],0 )
#define INVBIT55301                       PollingBit(wEmemoryRead[53],1 )
#define INVBIT55302                       PollingBit(wEmemoryRead[53],2 )
#define INVBIT55303                       PollingBit(wEmemoryRead[53],3 )
#define INVBIT55304                       PollingBit(wEmemoryRead[53],4 )
#define INVBIT55305                       PollingBit(wEmemoryRead[53],5 )
#define INVBIT55306                       PollingBit(wEmemoryRead[53],6 )
#define INVBIT55307                       PollingBit(wEmemoryRead[53],7 )
#define INVBIT55308                       PollingBit(wEmemoryRead[53],8 )
#define INVBIT55309                       PollingBit(wEmemoryRead[53],9 )
#define INVBIT55310                       PollingBit(wEmemoryRead[53],10)
#define INVBIT55311                       PollingBit(wEmemoryRead[53],11)
#define INVBIT55312                       PollingBit(wEmemoryRead[53],12)
#define INVBIT55313                       PollingBit(wEmemoryRead[53],13)
#define INVBIT55314                       PollingBit(wEmemoryRead[53],14)
#define INVBIT55315                       PollingBit(wEmemoryRead[53],15)

#define INVBIT55400                       PollingBit(wEmemoryRead[54],0 )
#define INVBIT55401                       PollingBit(wEmemoryRead[54],1 )





#define MAPBIT60000                       PollingBit(wEmemoryRead[100],0 )
#define MAPBIT60001                       PollingBit(wEmemoryRead[100],1 )
#define MAPBIT60002                       PollingBit(wEmemoryRead[100],2 )
#define MAPBIT60003                       PollingBit(wEmemoryRead[100],3 )
#define MAPBIT60004                       PollingBit(wEmemoryRead[100],4 )
#define MAPBIT60005                       PollingBit(wEmemoryRead[100],5 )
#define MAPBIT60006                       PollingBit(wEmemoryRead[100],6 )
#define MAPBIT60007                       PollingBit(wEmemoryRead[100],7 )
#define MAPBIT60008                       PollingBit(wEmemoryRead[100],8 )
#define MAPBIT60009                       PollingBit(wEmemoryRead[100],9 )
#define MAPBIT60010                       PollingBit(wEmemoryRead[100],10)
#define MAPBIT60011                       PollingBit(wEmemoryRead[100],11)
#define MAPBIT60012                       PollingBit(wEmemoryRead[100],12)
#define MAPBIT60013                       PollingBit(wEmemoryRead[100],13)
#define MAPBIT60014                       PollingBit(wEmemoryRead[100],14)
#define MAPBIT60015                       PollingBit(wEmemoryRead[100],15)


#define MAPBIT60100                       PollingBit(wEmemoryRead[101],0 )
#define MAPBIT60101                       PollingBit(wEmemoryRead[101],1 )
#define MAPBIT60102                       PollingBit(wEmemoryRead[101],2 )
#define MAPBIT60103                       PollingBit(wEmemoryRead[101],3 )
#define MAPBIT60104                       PollingBit(wEmemoryRead[101],4 )
#define MAPBIT60105                       PollingBit(wEmemoryRead[101],5 )
#define MAPBIT60106                       PollingBit(wEmemoryRead[101],6 )
#define MAPBIT60107                       PollingBit(wEmemoryRead[101],7 )
#define MAPBIT60108                       PollingBit(wEmemoryRead[101],8 )
#define MAPBIT60109                       PollingBit(wEmemoryRead[101],9 )
#define MAPBIT60110                       PollingBit(wEmemoryRead[101],10)
#define MAPBIT60111                       PollingBit(wEmemoryRead[101],11)
#define MAPBIT60112                       PollingBit(wEmemoryRead[101],12)
#define MAPBIT60113                       PollingBit(wEmemoryRead[101],13)
#define MAPBIT60114                       PollingBit(wEmemoryRead[101],14)
#define MAPBIT60115                       PollingBit(wEmemoryRead[101],15)

#define E60200_	    	      PollingBit(wEmemoryRead[102],0 )
#define E60201_				  PollingBit(wEmemoryRead[102],1 )
#define E60202_			      PollingBit(wEmemoryRead[102],2 )
#define E60203_			      PollingBit(wEmemoryRead[102],3 )
#define E60204_			 	  PollingBit(wEmemoryRead[102],4 )
#define E60205_			      PollingBit(wEmemoryRead[102],5 )
#define E60206_				  PollingBit(wEmemoryRead[102],6 )
#define E60207_			      PollingBit(wEmemoryRead[102],7 )
#define E60208_				  PollingBit(wEmemoryRead[102],8 )
#define E60209_				  PollingBit(wEmemoryRead[102],9 )
#define E60210_				      PollingBit(wEmemoryRead[102],10)
#define E60211_				      PollingBit(wEmemoryRead[102],11)
#define E60212_LOGBACKUP			      PollingBit(wEmemoryRead[102],12)
#define E60213_			      PollingBit(wEmemoryRead[102],13)
#define E60214_			      PollingBit(wEmemoryRead[102],14)
#define E60215_			      PollingBit(wEmemoryRead[102],15)
	
/*
#define E60300_TRANSFER1_W                 PollingBit(wEmemoryRead[103],0 )
#define E60301_STAGE1_W                PollingBit(wEmemoryRead[103],1 )
#define E60302_ROBOT_W              PollingBit(wEmemoryRead[103],2 )
#define E60303_UVZONE_W              PollingBit(wEmemoryRead[103],3 )
#define E60304_STAGE2_W              PollingBit(wEmemoryRead[103],4 )
#define E60305_TRANSFER2_W				  PollingBit(wEmemoryRead[103],5 )
#define E60306_ALING_W				  PollingBit(wEmemoryRead[103],6 )
#define E60307_MOUNT_W			  PollingBit(wEmemoryRead[103],7 )
#define E60308_TRANSFER3_W		      PollingBit(wEmemoryRead[103],8 )
#define E60309_DETAPE_W					      PollingBit(wEmemoryRead[103],9 )
#define E60310_OUTRAIL_W              PollingBit(wEmemoryRead[103],10)
#define E60311_PICKUP_F            PollingBit(wEmemoryRead[103],11)
#define E60312_STOCK_LOCK_F              PollingBit(wEmemoryRead[103],12)
#define E60313_              PollingBit(wEmemoryRead[103],13)
#define E60314_						  PollingBit(wEmemoryRead[103],14)
#define E60315_						  PollingBit(wEmemoryRead[103],15)
*/
#define E60300_ROBOT1_W                 PollingBit(wEmemoryRead[103],0 )
#define E60301_ROBOT2_W                PollingBit(wEmemoryRead[103],1 )
#define E60302_UV_W              PollingBit(wEmemoryRead[103],2 )
#define E60303_ALIGN_W              PollingBit(wEmemoryRead[103],3 )
#define E60304_TRANSFER_W              PollingBit(wEmemoryRead[103],4 )
#define E60305_MOUNT_W				  PollingBit(wEmemoryRead[103],5 )
#define E60306_TURNOVER_W				  PollingBit(wEmemoryRead[103],6 )
#define E60307_BUFFER_W			  PollingBit(wEmemoryRead[103],7 )
#define E60308_DETAPE_W		      PollingBit(wEmemoryRead[103],8 )
#define E60309_RAIL_W					      PollingBit(wEmemoryRead[103],9 )
#define E60310_OCR_W              PollingBit(wEmemoryRead[103],10)
#define E60311_PICHUP_F            PollingBit(wEmemoryRead[103],11)
#define E60312_STOCK_LOCK_F              PollingBit(wEmemoryRead[103],12)
#define E60313_               PollingBit(wEmemoryRead[103],13)
#define E60314_						  PollingBit(wEmemoryRead[103],14)
#define E60315_						  PollingBit(wEmemoryRead[103],15)



//==============================
// Gem Address E938 ~ E619

#define E90000_RFRAME_TABLE_CONVER				PollingBit(wEmemoryGEMRead[0],0 )
#define E90001_WCHUCK_CONVER				PollingBit(wEmemoryGEMRead[0],1 )
#define E90002_RFRAME_BUF_CONVER				PollingBit(wEmemoryGEMRead[0],2 )
#define E90003_SUPPLY_TAP_EMPTY				PollingBit(wEmemoryGEMRead[0],3 )
#define E90004_SUPPLY_TAP_REMOVE             PollingBit(wEmemoryGEMRead[0],4 )
#define E90005_SUPPLY_TAP_INSTAL             PollingBit(wEmemoryGEMRead[0],5 )
#define E90006_USED_TAP_FULL					PollingBit(wEmemoryGEMRead[0],6 )
#define E90007_USED_TAP_REMOVE             PollingBit(wEmemoryGEMRead[0],7 )
#define E90008_USED_TAP_INSTAL				PollingBit(wEmemoryGEMRead[0],8 )
#define E90009_PROTEC_TAP_FULL				PollingBit(wEmemoryGEMRead[0],9 )
#define E90010_PROTEC_TAP_REMOVE				PollingBit(wEmemoryGEMRead[0],10)
#define E90011_PROTEC_TAP_INSTAL				PollingBit(wEmemoryGEMRead[0],11)
#define E90012_CUTTER_LIFETIME				PollingBit(wEmemoryGEMRead[0],12)
#define E90013_CUTTER_REMOVE				PollingBit(wEmemoryGEMRead[0],13)
#define E90014_CUTTER_INSTAL				PollingBit(wEmemoryGEMRead[0],14)
#define E90015_RFRAME_BUF_EMPTY				PollingBit(wEmemoryGEMRead[0],15)

#define E90100_ADHESIVE_TAP_EMPTY				PollingBit(wEmemoryGEMRead[1],0 )
#define E90101_ADHESIVE_TAP_REMOVE				PollingBit(wEmemoryGEMRead[1],1 )
#define E90102_ADHESIVE_TAP_INSTAL				PollingBit(wEmemoryGEMRead[1],2 )
#define E90103_PEEL_TAP_FULL				PollingBit(wEmemoryGEMRead[1],3 )
#define E90104_PEEL_TAP_REMOVE             PollingBit(wEmemoryGEMRead[1],4 )
#define E90105_PEEL_TAP_INSTAL             PollingBit(wEmemoryGEMRead[1],5 )
#define E90106_UVLMP_LIFETIME				PollingBit(wEmemoryGEMRead[1],6 )
#define E90107_UVLMP_REMOVE             PollingBit(wEmemoryGEMRead[1],7 )
#define E90108_UVLMP_INSTALL				PollingBit(wEmemoryGEMRead[1],8 )
#define E90109_UVLMP_CHNG_START				PollingBit(wEmemoryGEMRead[1],9 )
#define E90110_UVLMP_CHNG_FINISH				PollingBit(wEmemoryGEMRead[1],10)
#define E90111_SUPPLY_TAP_EXPOS_TIME				PollingBit(wEmemoryGEMRead[1],11)
#define E90112_ADHESIVE_TAP_EXPOS_TIME				PollingBit(wEmemoryGEMRead[1],12)
#define E90113_				PollingBit(wEmemoryGEMRead[1],13)
#define E90114_				PollingBit(wEmemoryGEMRead[1],14)
#define E90115_				PollingBit(wEmemoryGEMRead[1],15)


#define E90300_INITIALEND			  PollingBit(wEmemoryGEMRead[3],0 )
#define E90301_AUTOREADY			  PollingBit(wEmemoryGEMRead[3],1 )
#define E90302_           PollingBit(wEmemoryGEMRead[3],2 )
#define E90303_				  PollingBit(wEmemoryGEMRead[3],3 )
#define E90304_              PollingBit(wEmemoryGEMRead[3],4 )
#define E90305_             PollingBit(wEmemoryGEMRead[3],5 )
#define E90306_      PollingBit(wEmemoryGEMRead[3],6 )
#define E90307_REMOTEMODE             PollingBit(wEmemoryGEMRead[3],7 )
#define E90308_			  PollingBit(wEmemoryGEMRead[3],8 )
#define E90309_			  PollingBit(wEmemoryGEMRead[3],9 )
#define E90310_LOTSTART				  PollingBit(wEmemoryGEMRead[3],10)
#define E90311_			  PollingBit(wEmemoryGEMRead[3],11)
#define E90312_						  PollingBit(wEmemoryGEMRead[3],12)
#define E90313_						  PollingBit(wEmemoryGEMRead[3],13)
#define E90314_            PollingBit(wEmemoryGEMRead[3],14)
#define E90315_PROCESSNOTCHANGE				  PollingBit(wEmemoryGEMRead[3],15)


#define E90400_REQ_DISCO_FILE			  PollingBit(wEmemoryGEMRead[4],0 )
#define E90401_TOUCH_1			  PollingBit(wEmemoryGEMRead[4],1 )
#define E90402_TOUCH_2           PollingBit(wEmemoryGEMRead[4],2 )
#define E90403_				  PollingBit(wEmemoryGEMRead[4],3 )
#define E90404_              PollingBit(wEmemoryGEMRead[4],4 )
#define E90405_             PollingBit(wEmemoryGEMRead[4],5 )
#define E90406_      PollingBit(wEmemoryGEMRead[4],6 )
#define E90407_             PollingBit(wEmemoryGEMRead[4],7 )
#define E90408_			  PollingBit(wEmemoryGEMRead[4],8 )
#define E90409_			  PollingBit(wEmemoryGEMRead[4],9 )
#define E90410_				  PollingBit(wEmemoryGEMRead[4],10)
#define E90411_			  PollingBit(wEmemoryGEMRead[4],11)
#define E90412_						  PollingBit(wEmemoryGEMRead[4],12)
#define E90413_						  PollingBit(wEmemoryGEMRead[4],13)
#define E90414_            PollingBit(wEmemoryGEMRead[4],14)
#define E90415_				  PollingBit(wEmemoryGEMRead[4],15)

#define E90500_WMOVE_CST_TO_ROBOT          PollingBit(wEmemoryGEMRead[5],0 )
#define E90501_WMOVE_ROBOT_TO_ALIGN          PollingBit(wEmemoryGEMRead[5],1 )
#define E90502_WAFER_SUCCESS_ALIGN          PollingBit(wEmemoryGEMRead[5],2 )
#define E90503_WAFER_FAILD_ALIGN          PollingBit(wEmemoryGEMRead[5],3 )
#define E90504_WMOVE_ROBOT_FROM_ALIGN          PollingBit(wEmemoryGEMRead[5],4 )
#define E90505_WMOVE_ROBOT_TO_UV     PollingBit(wEmemoryGEMRead[5],5 )
#define E90506_WAF_UV_STARTED    PollingBit(wEmemoryGEMRead[5],6 )
#define E90507_WAF_UV_LAMPON        PollingBit(wEmemoryGEMRead[5],7 )
#define E90508_WAF_UV_LAMPOFF         PollingBit(wEmemoryGEMRead[5],8 )
#define E90509_WAF_UV_FINISHED          PollingBit(wEmemoryGEMRead[5],9 )
#define E90510_WMOVE_TRANSF1_FROM_UV          PollingBit(wEmemoryGEMRead[5],10)
#define E90511_WMOVE_TRANSF1_TO_MOUNT      PollingBit(wEmemoryGEMRead[5],11)
#define E90512_WAF_MOUNT_STARTED       PollingBit(wEmemoryGEMRead[5],12)
#define E90513_WAF_BOND_STARTED       PollingBit(wEmemoryGEMRead[5],13)
#define E90514_WAF_BOND_FINISHED        PollingBit(wEmemoryGEMRead[5],14)
#define E90515_WAF_CUTTING_STARTED         PollingBit(wEmemoryGEMRead[5],15)


#define E90600_WAF_MOUNT_FINISHED          PollingBit(wEmemoryGEMRead[6],0 )
#define E90601_WMOVE_TRANSF2_FROM_MOUNT          PollingBit(wEmemoryGEMRead[6],1 )
#define E90602_WMOVE_TRANSF2_TO_TURNOVER          PollingBit(wEmemoryGEMRead[6],2 )
#define E90603_WMOVE_TURNOVER_TO_DETAPE          PollingBit(wEmemoryGEMRead[6],3 )
#define E90604_WAF_DETAPE_STARTED          PollingBit(wEmemoryGEMRead[6],4 )
#define E90605_WAF_ADHESIVETAPE_PULLOUT          PollingBit(wEmemoryGEMRead[6],5 )
#define E90606_WAF_ADHESIVETAPE_BONDED          PollingBit(wEmemoryGEMRead[6],6 )
#define E90607_WAF_TAPE_PEELED_OFF          PollingBit(wEmemoryGEMRead[6],7 )
#define E90608_WAF_DETAPE_FINISHED          PollingBit(wEmemoryGEMRead[6],8 )
#define E90609_WMOVE_RAIL_FROM_DETAPE          PollingBit(wEmemoryGEMRead[6],9 )
#define E90610_WMOVE_RAIL_TO_BARCODE          PollingBit(wEmemoryGEMRead[6],10)
#define E90611_WAF_BARCODE_PROCES_STARTED          PollingBit(wEmemoryGEMRead[6],11)
#define E90612_WAF_OCR_READ          PollingBit(wEmemoryGEMRead[6],12)
#define E90613_WAF_OCR_UNREADABLE          PollingBit(wEmemoryGEMRead[6],13)
#define E90614_WAF_BARCODE_PRINTED          PollingBit(wEmemoryGEMRead[6],14)
#define E90615_WAF_BARCODE_ATTACHED          PollingBit(wEmemoryGEMRead[6],15)


#define E90700_WAF_BARCODE_FINISHED          PollingBit(wEmemoryGEMRead[7],0 )
#define E90701_WMOVE_RAIL_FROM_BARCODE          PollingBit(wEmemoryGEMRead[7],1 )
#define E90702_WMOVE_LOADED_TO_OUTCST          PollingBit(wEmemoryGEMRead[7],2 )
#define E90703_          PollingBit(wEmemoryGEMRead[7],3 )
#define E90704_WAF_EMPTY_ON_EQUIPMENT          PollingBit(wEmemoryGEMRead[7],4 )
#define E90705_          PollingBit(wEmemoryGEMRead[7],5 )
#define E90706_WAF_MANUAL_REMOVE_ROBOTTOP          PollingBit(wEmemoryGEMRead[7],6 )
#define E90707_WAF_MANUAL_REMOVE_ROBOTBOT          PollingBit(wEmemoryGEMRead[7],7 )
#define E90708_WAF_MANUAL_REMOVE_ALIGN          PollingBit(wEmemoryGEMRead[7],8 )
#define E90709_WAF_MANUAL_REMOVE_UV          PollingBit(wEmemoryGEMRead[7],9 )
#define E90710_WAF_MANUAL_REMOVE_TRANSF1          PollingBit(wEmemoryGEMRead[7],10)
#define E90711_WAF_MANUAL_REMOVE_TURNOVER          PollingBit(wEmemoryGEMRead[7],11)
#define E90712_WAF_MANUAL_REMOVE_MOUNT          PollingBit(wEmemoryGEMRead[7],12)
#define E90713_WAF_MANUAL_REMOVE_OCRCHUCK          PollingBit(wEmemoryGEMRead[7],13)
#define E90714_WAF_MANUAL_REMOVE_DETAPE          PollingBit(wEmemoryGEMRead[7],14)
#define E90715_WAF_MANUAL_REMOVE_OUTRAIL          PollingBit(wEmemoryGEMRead[7],15)



#define E93800_F1OPENBSY		PollingBit(wEmemoryGEMRead[38],0 )
#define E93801_F1CLOSBSY		PollingBit(wEmemoryGEMRead[38],1 )
#define E93802_F1OPEN			PollingBit(wEmemoryGEMRead[38],2 )
#define E93803_F1LOTENDED		PollingBit(wEmemoryGEMRead[38],3 )
#define E93804_F1CSTEMPTY		PollingBit(wEmemoryGEMRead[38],4 )
#define E93805_F1CSTDET			PollingBit(wEmemoryGEMRead[38],5 )
#define E93806_F1RFIDEND		PollingBit(wEmemoryGEMRead[38],6 )
#define E93807_F1REJECTED		PollingBit(wEmemoryGEMRead[38],7 )
#define E93808_F1LOTSTARTED		PollingBit(wEmemoryGEMRead[38],8 )
#define E93809_F1ABORTLOT		PollingBit(wEmemoryGEMRead[38],9 )
#define E93810_F1CST600MM		PollingBit(wEmemoryGEMRead[38],10)
#define E93811_F1RFIDSTART		PollingBit(wEmemoryGEMRead[38],11)
#define E93812_F1RFIDFAIL		PollingBit(wEmemoryGEMRead[38],12)
#define E93813_F1LDFAIL			PollingBit(wEmemoryGEMRead[38],13)
#define E93814_F1UNLDFAIL		PollingBit(wEmemoryGEMRead[38],14)
#define E93815_F1REQ_PROCESS	PollingBit(wEmemoryGEMRead[38],15)


#define E93900_PORT1ACTION	PollingBit(wEmemoryGEMRead[39],0 )
#define E93901_PORT1FOUP	PollingBit(wEmemoryGEMRead[39],1 )
#define E93902_PORT1HEAT	PollingBit(wEmemoryGEMRead[39],2 )
#define E93903_PORT1FOSB	PollingBit(wEmemoryGEMRead[39],3 )
#define E93904_PORT1OPEN	PollingBit(wEmemoryGEMRead[39],4 )
#define E93905_F1REQ_PPSELECTED	PollingBit(wEmemoryGEMRead[39],5 )
#define E93906_F1PPSELECTED	PollingBit(wEmemoryGEMRead[39],6 )
#define E93907_F1STARTEDINPUT	PollingBit(wEmemoryGEMRead[39],7 )
#define E93908_F1STOPEDINPUT	PollingBit(wEmemoryGEMRead[39],8 )
#define E93909_	PollingBit(wEmemoryGEMRead[39],9 )
#define E93910_	PollingBit(wEmemoryGEMRead[39],10)
#define E93911_	PollingBit(wEmemoryGEMRead[39],11)
#define E93912_F1_150MM	PollingBit(wEmemoryGEMRead[39],12)
#define E93913_F1_200MM	PollingBit(wEmemoryGEMRead[39],13)
#define E93914_F1_300MM	PollingBit(wEmemoryGEMRead[39],14)
#define E93915_F1_600MM	PollingBit(wEmemoryGEMRead[39],15)




#define E94000_F2OPENBSY        PollingBit(wEmemoryGEMRead[40],0 )
#define E94001_F2CLOSBSY        PollingBit(wEmemoryGEMRead[40],1 )
#define E94002_F2OPEN		    PollingBit(wEmemoryGEMRead[40],2 )
#define E94003_F2LOTENDED	    PollingBit(wEmemoryGEMRead[40],3 )
#define E94004_F2CSTEMPTY	    PollingBit(wEmemoryGEMRead[40],4 )
#define E94005_F2CSTDET		    PollingBit(wEmemoryGEMRead[40],5 )
#define E94006_F2RFIDEND		PollingBit(wEmemoryGEMRead[40],6 )
#define E94007_F2REJECTED		PollingBit(wEmemoryGEMRead[40],7 )
#define E94008_F2LOTSTARTED		PollingBit(wEmemoryGEMRead[40],8 )
#define E94009_F2ABORTLOT		PollingBit(wEmemoryGEMRead[40],9 )
#define E94010_F2CST600MM		PollingBit(wEmemoryGEMRead[40],10)
#define E94011_F2RFIDSTART		PollingBit(wEmemoryGEMRead[40],11)
#define E94012_F2RFIDFAIL		PollingBit(wEmemoryGEMRead[40],12)
#define E94013_F2LDFAIL			PollingBit(wEmemoryGEMRead[40],13)
#define E94014_F2UNLDFAIL		PollingBit(wEmemoryGEMRead[40],14)
#define E94015_F2REQ_PROCESS	PollingBit(wEmemoryGEMRead[40],15)

#define E94100_PORT2ACTION	PollingBit(wEmemoryGEMRead[41],0 )
#define E94101_PORT2FOUP	PollingBit(wEmemoryGEMRead[41],1 )
#define E94102_PORT2HEAT	PollingBit(wEmemoryGEMRead[41],2 )
#define E94103_PORT2FOSB	PollingBit(wEmemoryGEMRead[41],3 )
#define E94104_PORT2OPEN	PollingBit(wEmemoryGEMRead[41],4 )
#define E94105_F2REQ_PPSELECTED	PollingBit(wEmemoryGEMRead[41],5 )
#define E94106_F2PPSELECTED	PollingBit(wEmemoryGEMRead[41],6 )
#define E94107_F2STARTEDINPUT	PollingBit(wEmemoryGEMRead[41],7 )
#define E94108_F2STOPEDINPUT	PollingBit(wEmemoryGEMRead[41],8 )
#define E94109_	PollingBit(wEmemoryGEMRead[41],9 )
#define E94110_	PollingBit(wEmemoryGEMRead[41],10)
#define E94111_	PollingBit(wEmemoryGEMRead[41],11)
#define E94112_F2_150MM	PollingBit(wEmemoryGEMRead[41],12)
#define E94113_F2_200MM	PollingBit(wEmemoryGEMRead[41],13)
#define E94114_F2_300MM	PollingBit(wEmemoryGEMRead[41],14)
#define E94115_F2_600MM	PollingBit(wEmemoryGEMRead[41],15)



#define E94200_F3OPENBSY              PollingBit(wEmemoryGEMRead[42],0 )
#define E94201_F3CLOSBSY              PollingBit(wEmemoryGEMRead[42],1 )
#define E94202_F3OPEN		          PollingBit(wEmemoryGEMRead[42],2 )
#define E94203_F3LOTENDED	          PollingBit(wEmemoryGEMRead[42],3 )
#define E94204_F3CSTEMPTY	          PollingBit(wEmemoryGEMRead[42],4 )
#define E94205_F3CSTDET		          PollingBit(wEmemoryGEMRead[42],5 )
#define E94206_F3RFIDEND	          PollingBit(wEmemoryGEMRead[42],6 )
#define E94207_F3REJECTED	          PollingBit(wEmemoryGEMRead[42],7 )
#define E94208_F3LOTSTARTED	          PollingBit(wEmemoryGEMRead[42],8 )
#define E94209_F3ABORTLOT	          PollingBit(wEmemoryGEMRead[42],9 )
#define E94210_F3CST600MM	          PollingBit(wEmemoryGEMRead[42],10)
#define E94211_F3RFIDSTART		      PollingBit(wEmemoryGEMRead[42],11)
#define E94212_F3RFIDFAIL			  PollingBit(wEmemoryGEMRead[42],12)
#define E94213_F3LDFAIL				  PollingBit(wEmemoryGEMRead[42],13)
#define E94214_F3UNLDFAIL             PollingBit(wEmemoryGEMRead[42],14)
#define E94215_F3REQ_PROCESS		  PollingBit(wEmemoryGEMRead[42],15)

#define E94400_F4OPENBSY	          PollingBit(wEmemoryGEMRead[44],0 )
#define E94401_F4CLOSBSY	          PollingBit(wEmemoryGEMRead[44],1 )
#define E94402_F4OPEN		          PollingBit(wEmemoryGEMRead[44],2 )
#define E94403_F4LOTENDED	          PollingBit(wEmemoryGEMRead[44],3 )
#define E94404_F4CSTEMPTY	          PollingBit(wEmemoryGEMRead[44],4 )
#define E94405_F4CSTDET		          PollingBit(wEmemoryGEMRead[44],5 )
#define E94406_F4RFIDEND	          PollingBit(wEmemoryGEMRead[44],6 )
#define E94407_F4REJECTED	          PollingBit(wEmemoryGEMRead[44],7 )
#define E94408_F4LOTSTARTED	          PollingBit(wEmemoryGEMRead[44],8 )
#define E94409_F4ABORTLOT	          PollingBit(wEmemoryGEMRead[44],9 )
#define E94410_F4CST600MM	          PollingBit(wEmemoryGEMRead[44],10)
#define E94411_F4RFIDSTART		      PollingBit(wEmemoryGEMRead[44],11)
#define E94412_F4RFIDFAIL	          PollingBit(wEmemoryGEMRead[44],12)
#define E94413_F4LDFAIL		          PollingBit(wEmemoryGEMRead[44],13)
#define E94414_F4UNLDFAIL	          PollingBit(wEmemoryGEMRead[44],14)
#define E94415_F4REQ_PROCESS          PollingBit(wEmemoryGEMRead[44],15)


#define E94800_CARRIER_ID			 PollingBit(wEmemoryGEMRead[48],0 )
#define E94801_USER_DEFINED          PollingBit(wEmemoryGEMRead[48],1 )
#define E94802_						 PollingBit(wEmemoryGEMRead[48],2 )
#define E94803_						 PollingBit(wEmemoryGEMRead[48],3 )
#define E94804_					     PollingBit(wEmemoryGEMRead[48],4 )
#define E94805_						 PollingBit(wEmemoryGEMRead[48],5 )
#define E94806_						 PollingBit(wEmemoryGEMRead[48],6 )
#define E94807_						 PollingBit(wEmemoryGEMRead[48],7 )
#define E94808_STANDALONE          PollingBit(wEmemoryGEMRead[48],8 )
#define E94809_FULL_INTEGRATED          PollingBit(wEmemoryGEMRead[48],9 )
#define E94810_          PollingBit(wEmemoryGEMRead[48],10)
#define E94811_          PollingBit(wEmemoryGEMRead[48],11)
#define E94812_          PollingBit(wEmemoryGEMRead[48],12)
#define E94813_          PollingBit(wEmemoryGEMRead[48],13)
#define E94814_          PollingBit(wEmemoryGEMRead[48],14)
#define E94815_          PollingBit(wEmemoryGEMRead[48],15)


#define _INVBIT54800                    0	// Motor Jog InC 전용 16 bit 화면별 정리
#define _INVBIT54801                    1
#define _INVBIT54802                    2
#define _INVBIT54803                    3
#define _INVBIT54804                    4
#define _INVBIT54805                    5
#define _INVBIT54806                    6
#define _INVBIT54807                    7
#define _INVBIT54808                    8
#define _INVBIT54809                    9
#define _INVBIT54810                    10
#define _INVBIT54811                    11
#define _INVBIT54812                    12
#define _INVBIT54813                    13
#define _INVBIT54814                    14
#define _INVBIT54815                    15

#define _INVBIT54900                    16	// Mapping 사용 유무 용 16 bit 정리
#define _INVBIT54901                    17
#define _INVBIT54902                    18
#define _INVBIT54903                    19
#define _INVBIT54904                    20
#define _INVBIT54905                    21
#define _INVBIT54906                    22
#define _INVBIT54907                    23
#define _INVBIT54908                    24
#define _INVBIT54909                    25
#define _INVBIT54910                    26
#define _INVBIT54911                    27
#define _INVBIT54912                    28
#define _INVBIT54913                    29
#define _INVBIT54914                    30
#define _INVBIT54915                    31

#define _INVBIT55000                    32	// select Mode 에서 Utility 사용  E550 ~ E554 까지
#define _INVBIT55001                    33
#define _INVBIT55002                    34
#define _INVBIT55003                    35
#define _INVBIT55004                    36
#define _INVBIT55005                    37
#define _INVBIT55006                    38
#define _INVBIT55007                    39
#define _INVBIT55008                    40
#define _INVBIT55009                    41
#define _INVBIT55010                    42
#define _INVBIT55011                    43
#define _INVBIT55012                    44
#define _INVBIT55013                    45
#define _INVBIT55014                    46
#define _INVBIT55015                    47

#define _INVBIT55100                    48
#define _INVBIT55101                    49
#define _INVBIT55102                    50
#define _INVBIT55103                    51
#define _INVBIT55104                    52
#define _INVBIT55105                    53
#define _INVBIT55106                    54
#define _INVBIT55107                    55
#define _INVBIT55108                    56
#define _INVBIT55109                    57
#define _INVBIT55110                    58
#define _INVBIT55111                    59
#define _INVBIT55112                    60
#define _INVBIT55113                    61
#define _INVBIT55114                    62
#define _INVBIT55115                    63

#define _INVBIT55200                    64
#define _INVBIT55201                    65
#define _INVBIT55202                    66
#define _INVBIT55203                    67
#define _INVBIT55204                    68
#define _INVBIT55205                    69
#define _INVBIT55206                    70
#define _INVBIT55207                    71
#define _INVBIT55208                    72
#define _INVBIT55209                    73
#define _INVBIT55210                    74
#define _INVBIT55211                    75
#define _INVBIT55212                    76
#define _INVBIT55213                    77
#define _INVBIT55214                    78
#define _INVBIT55215                    79

#define _INVBIT55300                    80
#define _INVBIT55301                    81
#define _INVBIT55302                    82
#define _INVBIT55303                    83
#define _INVBIT55304                    84
#define _INVBIT55305                    85
#define _INVBIT55306                    86
#define _INVBIT55307                    87
#define _INVBIT55308                    88
#define _INVBIT55309                    89
#define _INVBIT55310                    90
#define _INVBIT55311                    91
#define _INVBIT55312                    92
#define _INVBIT55313                    93
#define _INVBIT55314                    94
#define _INVBIT55315                    95

#define _INVBIT55400                    96
#define _INVBIT55401                    97


#define _M1JOGCW                        78			 ///////   120414 이면 예) 16 * 04 + 14
#define _M2JOGCW                        94
#define _M3JOGCW                     	110
#define _M4JOGCW                     	126
#define _M5JOGCW                     	142
#define _M6JOGCW                     	158
#define _M7JOGCW                     	174
#define _M8JOGCW                     	190
#define _M9JOGCW                     	206
#define _M10JOGCW                      	222
#define _M11JOGCW                      	238
#define _M12JOGCW                      	254
#define _M13JOGCW                      	270
#define _M14JOGCW                      	286
#define _M15JOGCW                      	302
#define _M16JOGCW                      	318

#define _M17JOGCW                       334			 ///////   120414 이면 예) 16 * 04 + 14
#define _M18JOGCW                       350
#define _M19JOGCW                     	366
#define _M20JOGCW                     	382
#define _M21JOGCW                     	398
#define _M22JOGCW                     	414
#define _M23JOGCW                     	430
#define _M24JOGCW                     	446
#define _M25JOGCW                     	462

#define _M1JOGCCW                       79 
#define _M2JOGCCW                     	95 
#define _M3JOGCCW                     	111
#define _M4JOGCCW                     	127
#define _M5JOGCCW                     	143
#define _M6JOGCCW                     	159
#define _M7JOGCCW                     	175
#define _M8JOGCCW                     	191
#define _M9JOGCCW                     	207
#define _M10JOGCCW                      223
#define _M11JOGCCW                      239
#define _M12JOGCCW                      255
#define _M13JOGCCW                      271
#define _M14JOGCCW                      287
#define _M15JOGCCW                      303
#define _M16JOGCCW     					319

#define _M17JOGCCW                     	335
#define _M18JOGCCW                     	351
#define _M19JOGCCW                     	367
#define _M20JOGCCW                      383
#define _M21JOGCCW                      399
#define _M22JOGCCW                      415
#define _M23JOGCCW                      431
#define _M24JOGCCW                      447
#define _M25JOGCCW                      463



#define _M1STATUS                        0	
#define _M2STATUS                       1
#define _M3STATUS                       2
#define _M4STATUS                       3
#define _M5STATUS                       4
#define _M6STATUS                       5
#define _M7STATUS                       6
#define _M8STATUS                       7
#define _M9STATUS                       8
#define _M10STATUS                        9
#define _M11STATUS                        10
#define _M12STATUS                        11
#define _M13STATUS                        12
#define _M14STATUS                        13
#define _M15STATUS                        14
#define _M16STATUS                        15
#define _M17STATUS                        16
#define _M18STATUS                        17
#define _M19STATUS                        18
#define _M20STATUS                        19
#define _M21STATUS                        20
#define _M22STATUS                        21
#define _M23STATUS                        22
#define _M24STATUS                        23
#define _M25STATUS                        24
#define _M26STATUS                        25



#define	PAGE_NO_1	1
#define	PAGE_NO_2	2
#define	PAGE_NO_3	3
#define	PAGE_NO_4	4
#define	PAGE_NO_5	5
#define	PAGE_NO_6	6
#define	PAGE_NO_7	7

#define	DEVICE_4INCH	1
#define	DEVICE_600MM	2

const COLORREF BACKCOLOR = RGB(200, 187, 168);
const COLORREF CLOUDBLUE = RGB(128, 184, 223);
const COLORREF WHITE     = RGB(255, 255, 255);
const COLORREF BKGROUND  = RGB(130, 150, 173);
const COLORREF LWHITE    = RGB(250, 250, 200);
const COLORREF BLACK     = RGB(1, 1, 1);
const COLORREF DKGRAY    = RGB(192, 192, 192);	 //const COLORREF DKGRAY    = RGB(128, 128, 128);
const COLORREF LTGRAY    = RGB(126, 126, 126);
const COLORREF SILVER    = RGB(192, 192, 192);
const COLORREF YELLOW    = RGB(252, 206, 24);
const COLORREF DKYELLOW  = RGB(255, 220, 0);
const COLORREF RED       = RGB(253, 54, 32);
const COLORREF LTRED     = RGB(241, 20, 17);
const COLORREF DKRED     = RGB(200, 0, 0);
const COLORREF BLUE      = RGB(103, 52, 255);
const COLORREF DKBLUE    = RGB(0, 0, 128);
const COLORREF CYAN      = RGB(0, 255, 255);
const COLORREF DKCYAN    = RGB(0, 128, 128);
const COLORREF GREEN     = RGB(79, 214, 5);
const COLORREF DKGREEN   = RGB(0, 200, 0);
const COLORREF MAGENTA   = RGB(255, 0, 255);
const COLORREF DKMAGENTA = RGB(128, 0, 128);
const COLORREF LBORA     = RGB(76, 70, 147);
const COLORREF DKBORA    = RGB(172, 45, 172);
const COLORREF GOLD      = RGB(0xFF, 0xD7, 0x00);
const COLORREF SKYBLUE   = RGB(0xC0, 0xFF, 0xFF);
const COLORREF LORANGE   = RGB(0xFF, 0xAD, 0x5B);
const COLORREF LAVENDER  = RGB(0xE6, 0xE6, 0xFA);
const COLORREF DKTEAL    = RGB(0x00, 0x00, 0x5E);
const COLORREF BLUEGRAY  = RGB(0x7B, 0x7B, 0xC0);
const COLORREF SEAGREEN  = RGB(0x3C, 0xB3, 0x71);
const COLORREF INDIGO    = RGB(0x4B, 0x00, 0x82);
const COLORREF PALEBLUE  = RGB(0x68, 0x83, 0x8B);
const COLORREF AQUAR     = RGB(0x7F, 0xFF, 0xD4);
const COLORREF TURQUOISE = RGB(0x40, 0xE0, 0xD0);
const COLORREF ROSE      = RGB(0xFF, 0xE4, 0xE1);
const COLORREF TAN       = RGB(0xD2, 0xB4, 0x8C);
const COLORREF BROWN     = RGB(0xA5, 0x2A, 0x00);
const COLORREF MWB       = RGB(99, 72, 223);
const COLORREF BLUELED	 = RGB(18, 248, 245);
#endif
