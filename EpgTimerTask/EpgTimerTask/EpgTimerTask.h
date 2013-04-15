
// EpgTimerTask.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CEpgTimerTaskApp:
// このクラスの実装については、EpgTimerTask.cpp を参照してください。
//

class CEpgTimerTaskApp : public CWinApp
{
public:
	CEpgTimerTaskApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CEpgTimerTaskApp theApp;