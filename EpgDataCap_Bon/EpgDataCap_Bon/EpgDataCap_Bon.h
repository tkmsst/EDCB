
// EpgDataCap_Bon.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CEpgDataCap_BonApp:
// このクラスの実装については、EpgDataCap_Bon.cpp を参照してください。
//

class CEpgDataCap_BonApp : public CWinApp
{
public:
	CEpgDataCap_BonApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CEpgDataCap_BonApp theApp;