#pragma once


//#include "PlcCommunication.h"
// CPlcThread
class CClientSock ;
class CPlcCommunication;
class CPlcThread : public CWinThread
{
	DECLARE_DYNCREATE(CPlcThread)

protected:
	CPlcThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPlcThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	CClientSock					*m_pClientSock;
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	void OnReceive();
	void OnAccept();
	short PLC_FinsNodeAddrDataSend();
	void OnSockConnect();
	short PLC_ReceiveData(short nAddr, short nPoints, short nType, unsigned short* pnRBuf, short nBufSize,BYTE nPlcType);
	short PLC_SendData(short nAddr, short nPoints, short nType, unsigned short *pnWBuf, short nBufSize,BYTE nPlcType);

	void AlarmBitClear();


	short InterpretCIOInOutRead();
	void  InterpretModeSelect(int m_ModeNo);
	short InterpretCIOTouchRead(); 
	short InterpretCIOTouchReadGem() ;
	short InterpretEMWordRead();
	short InterpretEMWordReadMotor() ;
	short InterpretEMWordMappingRead() ;
	short InterpretEMWordMonitorRead();
	short InterpretEMWordMotorSpeedRead() ;
	short InterpretCIOBitWrite(short nAddr, short nPosition,short onoff);
	short InterpretCIOBitCheck();
	short InterpretCIOBitCheckGem();
	short InterpretEMDoubleWordWrite(short nAddr, short nPoints,short nCnt);
	short InterpretEMSingleWordWrite(short nAddr, long nValue, short nPoints);
	short InterpretAlarmEMWordRead();
	short InterpretEMSingleOcrCharWrite(short nAddr, CString ocrstring , short nPoints) ;
	short InterpretEMWordGEMRead() ;
	void InterpretMotorCurrentPos();
	short InterpretBitInvertCheck() ;
	short InterpretMotorUpdateCheck() ;
	void InterpretAlarm();
	void InterpretOperator();
	void InterpretMonitorDataRead() ;


	short BitSetReset(short nAddr, short nPosition, short onoff) ;
	short BitInvert(short nAddr, short nPosition, BYTE rPlcType, BYTE wPlcType);
	int GetAlarmFromTable( _tAlarm *pAlarm );
	int GetOperatorFromTable( _tOperation *pOperation )	;
	void OnErrorDisplay(BOOL bShow) ;
	void PLCSquenceEvent() ;
	int Run();
};


