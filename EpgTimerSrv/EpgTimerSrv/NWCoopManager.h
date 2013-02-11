#pragma once

#include "ReserveInfo.h"
#include "../../Common/SendCtrlCmd.h"

class CNWCoopManager
{
public:
	CNWCoopManager(void);
	~CNWCoopManager(void);

	void SetCoopServer(vector<COOP_SERVER_INFO>* infoList);
	BOOL AddChkReserve(CReserveInfo* data);
	void StartChkReserve();
	void StopChkReserve();
	void ResetResCheck();

	BOOL SetChkEpgFile(vector<wstring>* chkFileList);
	void StartChkEpgFile();
	void StopChkEpgFile();
	BOOL IsUpdateEpgData();
protected:
	typedef struct _CHK_RESERVE_INFO{
		CReserveInfo* reserve;
		map<DWORD, WORD> chkStatus;
	}CHK_RESERVE_INFO;
	typedef struct _CHK_SERVER_INFO{
		DWORD id;
		COOP_SERVER_INFO srvInfo;
		BOOL wake;
		BOOL sendMagic;
		__int64 sendMagicTime;
	}CHK_SERVER_INFO;

	HANDLE lockEvent;
	HANDLE lockQueue;
	HANDLE chkThread;
	HANDLE chkStopEvent;

	HANDLE chkEpgThread;
	HANDLE chkEpgStopEvent;


	map<DWORD, COOP_SERVER_INFO> srvList;

	vector<CHK_RESERVE_INFO*> chkQueue;

	vector<wstring> chkEpgFileList;
	BOOL updateEpgData;
protected:
	//PublicAPIîrëºêßå‰óp
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 60*1000);
	void UnLock(LPCWSTR log = NULL);

	BOOL QueueLock(LPCWSTR log = NULL, DWORD timeOut = 60*1000);
	void QueueUnLock(LPCWSTR log = NULL);

	BOOL GetIP2Host(wstring host, wstring& ip);
	BOOL GetIP2Host(wstring host, string& ip);

	BOOL SendMagicPacket(BYTE* mac, wstring host, WORD port);
	BOOL SendMagicPacket(BYTE* mac, WORD port);

	void StartChkThread();
	static UINT WINAPI ChkThread(LPVOID param);
	static UINT WINAPI ChkEpgThread(LPVOID param);
};

