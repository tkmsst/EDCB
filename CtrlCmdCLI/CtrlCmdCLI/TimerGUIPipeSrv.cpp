#include "StdAfx.h"
#include "TimerGUIPipeSrv.h"
#include "../../Common/CtrlCmdDef.h"
#include "../../Common/StringUtil.h"

using namespace CtrlCmdCLI;

TimerGUIPipeSrv::TimerGUIPipeSrv(void)
{
	this->pipeServer = NULL;
}

TimerGUIPipeSrv::~TimerGUIPipeSrv(void)
{
	if( this->pipeServer != NULL ){
		this->pipeServer->StopServer();
		SAFE_DELETE(this->pipeServer);
	}
}

TimerGUIPipeSrv::!TimerGUIPipeSrv(void)
{
	if( this->pipeServer != NULL ){
		this->pipeServer->StopServer();
		SAFE_DELETE(this->pipeServer);
	}
}

bool TimerGUIPipeSrv::StartServer(int processID)
{
	if( this->pipeServer != NULL ){
		return false;
	}
	this->pipeServer = new CPipeServer;

	wstring pipeName = L"";
	wstring waitEventName = L"";

	Format(pipeName, L"%s%d", CMD2_GUI_CTRL_PIPE, processID);
	Format(waitEventName, L"%s%d", CMD2_GUI_CTRL_WAIT_CONNECT, processID);

	TimerProcDelegate^ timerProcDelegate = gcnew TimerProcDelegate( TimerGUIPipeSrv::CtrlCmdCallback );

	this->pipeServer->StartServer(
		waitEventName.c_str(),
		pipeName.c_str(),
		CtrlCmdCallback,
		this
		);

	return true;
}

void TimerGUIPipeSrv::StopServer()
{
	if( this->pipeServer != NULL ){
		this->pipeServer->StopServer();
		SAFE_DELETE(this->pipeServer);
	}
}

static int TimerGUIPipeSrv::CtrlCmdCallback(void* param, CMD_STREAM* cmdParam, CMD_STREAM* resParam)
{
	return 0;
}