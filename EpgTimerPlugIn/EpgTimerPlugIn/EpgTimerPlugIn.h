#pragma once

#define TVTEST_PLUGIN_CLASS_IMPLEMENT	// ƒNƒ‰ƒX‚Æ‚µ‚ÄŽÀ‘•
#include "TVTestPlugin.h"

#include "../../Common/PipeServer.h"
#include "../../Common/ErrDef.h"
#include "../../Common/CtrlCmdDef.h"
#include "../../Common/CtrlCmdUtil.h"
#include "../../Common/SendCtrlCmd.h"

#include "StreamCtrlDlg.h"

class CEpgTimerPlugIn : public TVTest::CTVTestPlugin
{
private:
	CPipeServer pipeServer;

	BOOL nwMode;
	TVTEST_STREAMING_INFO nwModeInfo;
	CSendCtrlCmd cmd;
	BOOL fullScreen;
	BOOL showNormal;
	CStreamCtrlDlg* ctrlDlg;

private:
	static LRESULT CALLBACK EventCallback(UINT Event,LPARAM lParam1,LPARAM lParam2,void *pClientData);
	static int CALLBACK CtrlCmdCallback(void* param, CMD_STREAM* cmdParam, CMD_STREAM* resParam);
	static BOOL CALLBACK WindowMsgeCallback(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT *pResult,void *pUserData);

	void ResetStreamingCtrlView();

public:
	CEpgTimerPlugIn();
	~CEpgTimerPlugIn();
	virtual bool GetPluginInfo(TVTest::PluginInfo *pInfo);
	virtual bool Initialize();
	virtual bool Finalize();

	void EnablePlugin(BOOL enable);
};
