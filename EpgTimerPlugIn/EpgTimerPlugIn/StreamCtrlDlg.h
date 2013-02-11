#pragma once

#include "../../Common/SendCtrlCmd.h"
#include "../../Common/StringUtil.h"


#define WM_RESET_GUI (WM_USER+0x1001)
#define WM_CHG_PORT (WM_USER+0x1101)
#define WM_PLAY_CLOSE (WM_USER+0x1102)

class CStreamCtrlDlg
{
public:
	CStreamCtrlDlg(void);
	~CStreamCtrlDlg(void);

	void SetCtrlCmd(CSendCtrlCmd* ctrlCmd, DWORD ctrlID, BOOL chkUdp, BOOL chkTcp, BOOL play, BOOL timeShiftMode);
	DWORD CreateStreamCtrlDialog(HINSTANCE hInstance, HWND parentHWND);
	void CloseStreamCtrlDialog();

	void StopTimer();

	BOOL ShowCtrlDlg(DWORD cmdShow);
	HWND GetDlgHWND(){ return this->hwnd; }

	void StartFullScreenMouseChk();
	void StopFullScreenMouseChk();
protected:
	void SetNWModeSend();
	void EnumIP();
	void UpdateLog();

	static LRESULT CALLBACK DlgProc(HWND hDlgWnd, UINT msg, WPARAM wp, LPARAM lp);

protected:
	HWND hwnd;
	HWND parentHwnd;
	CSendCtrlCmd* cmd;
	DWORD ctrlID;
	BOOL iniTCP;
	BOOL iniUDP;
	BOOL timeShiftMode;

	NWPLAY_PLAY_INFO nwPlayInfo;
};

