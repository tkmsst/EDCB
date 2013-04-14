#pragma once

#include "CommonDef.h"

class CLockUtil
{
public:
	CLockUtil(void);
	~CLockUtil(void);

	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = INFINITE);
	void UnLock(LPCWSTR log = NULL);
protected:
	HANDLE lockEvent;
	wstring lastLockLog;
};

