#include "StdAfx.h"
#include "SleepUtil.h"
#include <process.h>

CSleepUtil::CSleepUtil(void)
{
	this->lockEvent = _CreateEvent(FALSE, TRUE, NULL);

	this->events[0] = _CreateEvent(TRUE, FALSE, NULL);
	this->thread = NULL;
}

CSleepUtil::~CSleepUtil(void)
{
	if( this->thread != NULL ){
		::SetEvent(this->events[0]);
		// スレッド終了待ち
		if ( ::WaitForSingleObject(this->thread, 2000) == WAIT_TIMEOUT ){
			::TerminateThread(this->thread, 0xffffffff);
		}
		CloseHandle(this->thread);
		this->thread = NULL;
	}
	::CloseHandle(this->events[0]);
	this->events[0] = NULL;

	if( this->lockEvent != NULL ){
		UnLock();
		CloseHandle(this->lockEvent);
		this->lockEvent = NULL;
	}
}

BOOL CSleepUtil::Lock(LPCWSTR log, DWORD timeOut)
{
	if( this->lockEvent == NULL ){
		return FALSE;
	}
	if( log != NULL ){
		OutputDebugString(log);
	}
	DWORD dwRet = WaitForSingleObject(this->lockEvent, timeOut);
	if( dwRet == WAIT_ABANDONED || 
		dwRet == WAIT_FAILED){
		return FALSE;
	}
	return TRUE;
}

void CSleepUtil::UnLock(LPCWSTR log)
{
	if( this->lockEvent != NULL ){
		SetEvent(this->lockEvent);
	}
	if( log != NULL ){
		OutputDebugString(log);
	}
}

UINT WINAPI CSleepUtil::WaitThread(LPVOID param)
{
	CSleepUtil* sys = (CSleepUtil*)param;

	WaitForMultipleObjects( 2, sys->events, FALSE, INFINITE );

	CloseHandle( sys->events[1] );
	sys->events[1] = NULL;

	return 0;
}

BOOL CSleepUtil::SetReturnTime(LONGLONG returnTime, BOOL reboot, LONGLONG wakeTimeMin)
{
	if( Lock() == FALSE ) return FALSE;

	//まず復帰時間チェック
	BOOL ret = TRUE;

	LONGLONG nowTime = GetNowI64Time();
	LONGLONG setTime = 0;
	if( reboot == TRUE ){
		//指定+７分前は入れないようにする
		if( nowTime>returnTime-(60*I64_1SEC*(wakeTimeMin+5)) ){
			ret = FALSE;
		}
		//指定+５分前に復帰
		setTime = nowTime-(returnTime-(60*I64_1SEC*(wakeTimeMin+5)));
	}else{
		//指定+２分前は入れないようにする
		if( nowTime>returnTime-(60*I64_1SEC*(wakeTimeMin)) ){
			ret = FALSE;
		}
		//指定分前に復帰
		setTime = nowTime-(returnTime-(60*I64_1SEC*(wakeTimeMin)));
	}
/*	_OutputDebugString(L"ReturnTime");
	wstring str;
	SYSTEMTIME retTime;
	ConvertSystemTime(returnTime, &retTime);
	GetTimeString(retTime, str);
	OutputDebugString(str.c_str());
	*/
	FILETIME fileSetTime;
	fileSetTime.dwHighDateTime = (DWORD)(setTime>>32);
	fileSetTime.dwLowDateTime = (DWORD)(setTime&0x00000000FFFFFFFF);

	//復帰タイマー作成
	if( this->thread != NULL ){
		::SetEvent(this->events[0]);
		// スレッド終了待ち
		if ( ::WaitForSingleObject(this->thread, 10000) == WAIT_TIMEOUT ){
			::TerminateThread(this->thread, 0xffffffff);
		}
		CloseHandle(this->thread);
		this->thread = NULL;
	}

	this->events[1] = CreateWaitableTimer(NULL, FALSE, L"FriioEpgTimerBon2");

	SetWaitableTimer( this->events[1], (LARGE_INTEGER *)&fileSetTime, 0, NULL, NULL, TRUE );
	if( this->thread == NULL ){
		//待機スレッド起動
		::ResetEvent(this->events[0]);

		this->thread = (HANDLE)_beginthreadex(NULL, 0, WaitThread, (LPVOID)this, CREATE_SUSPENDED, NULL);
		//OutputDebugString(L"WaitThread");
		ResumeThread(this->thread);
	}

	UnLock();
	return ret;
}

BOOL CSleepUtil::SetStandby(BOOL standbyMode)
{
	if( Lock() == FALSE ) return FALSE;

	HANDLE htoken;
	TOKEN_PRIVILEGES tknPrvlgs;
 
	OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &htoken);

	LookupPrivilegeValue(L"", SE_SHUTDOWN_NAME, &(tknPrvlgs.Privileges[0].Luid));

	tknPrvlgs.PrivilegeCount = 1;
	tknPrvlgs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(htoken, false, &tknPrvlgs,
		sizeof(TOKEN_PRIVILEGES), 0, 0);

	// スタンバイ
	SetSystemPowerState(standbyMode, FALSE);

	UnLock();
	return TRUE;
}

