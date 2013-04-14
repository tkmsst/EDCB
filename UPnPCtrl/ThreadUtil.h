#ifndef __MULTI_PLATFORM_THREAD_UTIL_H__
#define __MULTI_PLATFORM_THREAD_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef void* MP_THREAD_HANDLE;
typedef void* MP_LOCK_HANDLE;

#ifdef _WIN32
typedef unsigned int (__stdcall *MP_THREAD_FUNC)(void* param);
#else
//Linux系
typedef void* (*MP_THREAD_FUNC)(void* param);
#endif

//排他制御用のハンドルを作成する
//WindowsではCreateEvent
//Linux系はpthread_mutex_init
//戻り値：ハンドル、エラー時NULL
MP_LOCK_HANDLE MP_LOCK_CreateHandle(
	void
);

//ハンドルの解放
//解放後handleはNULLに
//WindowsではCloseHandle
//Linux系はpthread_mutex_destroy
void MP_LOCK_CloseHandle(
	MP_LOCK_HANDLE* handle				//[IN]MP_LOCK_CreateHandleの戻り値
);

//排他制御用にLockする
//WindowsではWaitForSingleObject
//Linux系はpthread_mutex_lock
//戻り値：0以上で成功、0未満でエラー
int MP_LOCK_Lock(
	MP_LOCK_HANDLE handle				//[IN]MP_LOCK_CreateHandleの戻り値
);

//排他制御用にUnLockする
//WindowsではSetEvent
//Linux系はpthread_mutex_unlock
//戻り値：0以上で成功、0未満でエラー
int MP_LOCK_UnLock(
	MP_LOCK_HANDLE handle				//[IN]MP_LOCK_CreateHandleの戻り値
);


//別スレッドで関数を実行する
//Windowsでは_beginthreadex
//Linux系はpthread_create
//戻り値：ハンドル、エラー時NULL
MP_THREAD_HANDLE MP_THREAD_BegineThread(
	MP_THREAD_FUNC func,							//[IN]新規スレッドの実行を起動するルーチン
	void* param							//[IN]新規スレッドに渡される引数
);

//スレッドの終了を待ち開放処理をする（タイムアウトはなし）
//キャンセル処理はあらかじめ行っておくこと
//WindowsではWaitForSingleObject
//Linux系はpthread_join
//終了後handleはNULLに
void MP_THREAD_WaitEndThread(
	MP_THREAD_HANDLE* handle			//[IN]MP_THREAD_BegineThreadの戻り値
);

//Sleepを行う
//WindowsではSleep
//Linux系はnanosleep
void MP_Sleep(
	int msec			//[IN]msec単位
);

#ifdef __cplusplus
}
#endif

#endif
