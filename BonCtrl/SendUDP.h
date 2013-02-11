#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include "BonCtrlDef.h"
#include "../Common/Util.h"
#include "../Common/StringUtil.h"

class CSendUDP
{
public:
	CSendUDP(void);
	~CSendUDP(void);

	BOOL StartUpload( vector<NW_SEND_INFO>* List );
	void SendData(BYTE* pbBuff, DWORD dwSize);
	BOOL CloseUpload();

protected:
	static UINT WINAPI SendThread(LPVOID pParam);

protected:
	typedef struct _SOCKET_DATA{
		SOCKET sock;
		struct sockaddr_in addr;
	}SOCKET_DATA;
	vector<SOCKET_DATA> SockList;

	wstring m_strIniPath;

	vector<TS_DATA*> m_TSBuff;
	HANDLE m_hSendThread;
	HANDLE m_hSendStopEvent;

	HANDLE m_hCriticalEvent;

	UINT m_uiWait;
	UINT m_uiSendSize;

};
