#pragma once
#include "EpgTimerSrvDef.h"
#include "../../Common/StructDef.h"
#include "../../Common/SendCtrlCmd.h"
#include "NotifyManager.h"

class CBatManager
{
public:
	CBatManager(void);
	~CBatManager(void);

	void ReloadSetting();
	void SetNotifyManager(CNotifyManager* manager);
	//void SetRegistGUI(map<DWORD, DWORD> registGUIMap);

	void AddBatWork(BAT_WORK_INFO* info);

	DWORD GetWorkCount();
	BOOL IsWorking();

	void StartWork();
	void PauseWork();

	BOOL GetLastWorkSuspend(BYTE* suspendMode, BYTE* rebootFlag);
protected:
	HANDLE lockEvent;

	CNotifyManager* notifyManager;
//	map<DWORD, DWORD> registGUIMap;

	vector<BAT_WORK_INFO> workList;

	BOOL workFlag;
	HANDLE batWorkThread;
	HANDLE batWorkStopEvent;

	BYTE lastSuspendMode;
	BYTE lastRebootFlag;
protected:
	//PublicAPIîrëºêßå‰óp
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 60*1000);
	void UnLock(LPCWSTR log = NULL);

	static UINT WINAPI BatWorkThread(LPVOID param);

	BOOL CreateBatFile(BAT_WORK_INFO* info, wstring batSrcFilePath, wstring& batFilePath );
};

