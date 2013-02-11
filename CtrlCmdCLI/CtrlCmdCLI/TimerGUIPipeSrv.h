#pragma once

#include "CtrlCmdCLIDef.h"
#include "../../Common/PipeServer.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace CtrlCmdCLI {
	ref class TimerGUIPipeSrv
	{
	public:
		delegate void ShowDlgHandler();
		delegate void UpdateReserveHandler();

		event ShowDlgHandler^ ShowDlg;
		event UpdateReserveHandler^ UpdateReserve;
	public:
		TimerGUIPipeSrv(void);
		~TimerGUIPipeSrv(void);
		!TimerGUIPipeSrv(void);

		bool StartServer(int processID);
		void StopServer();
	private:
		CPipeServer* pipeServer;
		delegate VOID TimerProcDelegate( void* , CMD_STREAM* , CMD_STREAM*  );

	private:
		static int CtrlCmdCallback(void* param, CMD_STREAM* cmdParam, CMD_STREAM* resParam);
	};
}
