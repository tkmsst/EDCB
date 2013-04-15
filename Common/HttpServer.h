#pragma once

#include "StringUtil.h"
#include "CtrlCmdDef.h"
#include "StructDef.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "wsock32.lib")

typedef int (CALLBACK *HTTP_CALLBACK_PROC)(void* pParam, HTTP_STREAM* recvParam, HTTP_STREAM* sendParam);

class CHttpServer
{
public:
	CHttpServer(void);
	~CHttpServer(void);

	BOOL StartServer(
		DWORD dwPort, 
		HTTP_CALLBACK_PROC pfnHttpProc, 
		void* pParam, 
		int iThreadPriority = THREAD_PRIORITY_NORMAL,
		int iCtrlCmdEventID = -1
		);
	void StopServer();

protected:
	HTTP_CALLBACK_PROC m_pHttpProc;
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

	DWORD ChkContentLength(string httpHeader);
};
