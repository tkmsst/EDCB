#pragma once

#include "../../Common/Util.h"
#include "../../Common/EpgTimerUtil.h"
#include "../../Common/PathUtil.h"
#include "../../Common/StringUtil.h"
#include "../../Common/SendCtrlCmd.h"

class CTunerCtrl
{
public:
	CTunerCtrl(void);
	~CTunerCtrl(void);

	void SetExePath(wstring exePath);
	BOOL OpenExe(wstring bonDriver, DWORD id, BOOL minWake, BOOL noView, BOOL noNW, map<DWORD, DWORD> registGUIMap, DWORD* PID, BOOL UDP, BOOL TCP, DWORD Priority );
	void CloseExe(DWORD PID);
	BOOL GetOpenExe(vector<DWORD>* IDList);
	BOOL GetOpenExe(wstring exeName, vector<DWORD>* IDList);
protected:
	HANDLE openWaitEvent;

	wstring exePath;
	wstring exeName;
	BOOL win2kFlag;
	CSendCtrlCmd cmdSend;

	wstring optBon;
	wstring optMin;
	wstring optNoView;
	wstring optNoNW;
protected:
	void GetOption();
	static BOOL CALLBACK CloseEnumWindowProc(HWND hWnd, LPARAM lParam);
};

