#pragma once

#include "StringUtil.h"
#include "CtrlCmdDef.h"
#include "StructDef.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "wsock32.lib")

typedef int (CALLBACK *CMD_CALLBACK_PROC)(void* pParam, CMD_STREAM* pCmdParam, CMD_STREAM* pResParam);

class CTCPServer
{
public:
	CTCPServer(void);
	~CTCPServer(void);

	BOOL StartServer(
		DWORD dwPort, 
		CMD_CALLBACK_PROC pfnCmdProc, 
		void* pParam, 
		int iThreadPriority = THREAD_PRIORITY_NORMAL,
		int iCtrlCmdEventID = -1
		);
	void StopServer();

protected:
	CMD_CALLBACK_PROC m_pCmdProc;
	void* m_pParam;
	DWORD m_dwPort;

	int m_iThreadPriority;
	int m_iCtrlCmdEventID;

	HANDLE m_hStopEvent;
	HANDLE m_hThread;

	SOCKET m_sock;
	struct sockaddr_in m_addr;
	
protected:
	static UINT WINAPI ServerThread(LPVOID pParam);

};
