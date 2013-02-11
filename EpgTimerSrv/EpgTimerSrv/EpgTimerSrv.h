#pragma once

#include "resource.h"

//サービス動作用のメイン
void WINAPI service_main(DWORD dwArgc, LPTSTR *lpszArgv);

//サービスからのコマンドのコールバック
DWORD WINAPI service_ctrl(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext);

//サービスのステータス通知用
BOOL SendStatusScm(int iState, int iExitcode, int iProgress);

//メイン処理
//引数：
// serviceFlag			[IN]サービスとしての起動かどうか
void StartMain(
	BOOL serviceFlag
	);

//メイン処理停止
void StopMain();
