#pragma once

#include "../../Common/CommonDef.h"
#include "../../Common/TimeUtil.h"

class CSleepUtil
{
public:
	CSleepUtil(void);
	~CSleepUtil(void);

	BOOL SetReturnTime(LONGLONG returnTime, BOOL rebootFlag, LONGLONG wakeTimeMin);
	BOOL SetStandby(BOOL standbyMode);

protected:
protected:
	//PublicAPIîrëºêßå‰óp
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 60*1000);
	void UnLock(LPCWSTR log = NULL);

	static UINT WINAPI WaitThread(LPVOID param);

protected:
	HANDLE lockEvent;

	HANDLE events[2];
	HANDLE thread;
};
