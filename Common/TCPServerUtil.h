#pragma once

#include "StringUtil.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "wsock32.lib")
typedef struct _TCP_ACCEPT_PARAM{
	void* param;
	SOCKET sock;
	struct sockaddr_in client;
	HANDLE stopEvent;
	HANDLE thread;
}TCP_ACCEPT_PARAM;

typedef int (CALLBACK *TCP_ACCEPT_CALLBACK_PROC)(void* param, SOCKET clientSock, struct sockaddr_in* client, HANDLE stopEvent);

class CTCPServerUtil
{
public:
	CTCPServerUtil(void);
	~CTCPServerUtil(void);

	BOOL StartServer(
		DWORD port, 
		TCP_ACCEPT_CALLBACK_PROC tcpAcceptProc,
		void* funcParam,
		int threadPriority = THREAD_PRIORITY_NORMAL
		);
	void StopServer();

protected:
	HANDLE lockEvent;
	wstring lastLockLog;
	
	TCP_ACCEPT_CALLBACK_PROC tcpAcceptProc;
	void* funcParam;
	DWORD port;

	int threadPriority;

	HANDLE stopEvent;
	HANDLE serverThread;

	SOCKET srvSock;
	struct sockaddr_in srvAddr;

	map<HANDLE, TCP_ACCEPT_PARAM*> acceptThreadMap;
	
protected:
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 60*1000);
	void UnLock(LPCWSTR log = NULL);

	static UINT WINAPI ServerThread(LPVOID pParam);
	static UINT WINAPI AcceptThread(LPVOID pParam);

};
