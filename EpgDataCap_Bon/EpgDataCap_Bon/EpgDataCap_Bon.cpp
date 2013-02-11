
// EpgDataCap_Bon.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "EpgDataCap_Bon.h"
#include "EpgDataCap_BonDlg.h"

#include "CmdLineUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEpgDataCap_BonApp

BEGIN_MESSAGE_MAP(CEpgDataCap_BonApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEpgDataCap_BonApp コンストラクション

CEpgDataCap_BonApp::CEpgDataCap_BonApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CEpgDataCap_BonApp オブジェクトです。

CEpgDataCap_BonApp theApp;


// CEpgDataCap_BonApp 初期化

BOOL CEpgDataCap_BonApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	SetProcessShutdownParameters(0x300, 0);

	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	CCmdLineUtil cCmdUtil;
	ParseCommandLine(cCmdUtil);

	CEpgDataCap_BonDlg dlg;

	map<CString, CString>::iterator itr;
	dlg.SetIniMin(FALSE);
	dlg.SetIniView(TRUE);
	dlg.SetIniNW(TRUE);
	for( itr = cCmdUtil.m_CmdList.begin(); itr != cCmdUtil.m_CmdList.end(); itr++ ){
		if( itr->first.CompareNoCase(L"d") == 0 ){
			dlg.SetInitBon(itr->second);
			OutputDebugString(itr->second);
		}else if( itr->first.CompareNoCase(L"min") == 0 ){
			dlg.SetIniMin(TRUE);
		}else if( itr->first.CompareNoCase(L"noview") == 0 ){
			dlg.SetIniView(FALSE);
		}else if( itr->first.CompareNoCase(L"nonw") == 0 ){
			dlg.SetIniNW(FALSE);
		}else if( itr->first.CompareNoCase(L"nwudp") == 0 ){
			dlg.SetIniNWUDP(TRUE);
		}else if( itr->first.CompareNoCase(L"nwtcp") == 0 ){
			dlg.SetIniNWTCP(TRUE);
		}
	}


	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

