// SendTSTCP.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include "../../Common/Util.h"
#include "../../Common/ErrDef.h"
#include "SendTSTCPMain.h"

vector<CSendTSTCPMain*> g_List;
int g_iCount = 0;


//DLLの初期化
//戻り値：識別ID（-1でエラー）
int WINAPI InitializeDLL(
	)
{
	g_iCount++;
	int iID = 0;
	iID = (int)g_List.size();
	CSendTSTCPMain* pCtrl = new CSendTSTCPMain;
	if(pCtrl->Initialize() == FALSE){
		SAFE_DELETE(pCtrl);
		return -1;
	}
	g_List.push_back(pCtrl);

	return iID;
}


//DLLの開放
//戻り値：エラーコード
DWORD WINAPI UnInitializeDLL(
	int iID //[IN] InitializeDLLの戻り値
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	g_List[iID]->UnInitialize();
	SAFE_DELETE(g_List[iID]);

	g_iCount--;
	if( g_iCount < 0 ){
		g_iCount = 0;
	}
	if( g_iCount == 0 ){
		for( int i=0; i<(int)g_List.size(); i++ ){
			SAFE_DELETE(g_List[i]);
		}
		g_List.clear();
	}
	return NO_ERR;
}


//送信先を追加
//戻り値：エラーコード
DWORD WINAPI AddSendAddrDLL(
	int iID, //[IN] InitializeDLLの戻り値
	LPCWSTR lpcwszIP,
	DWORD dwPort
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	DWORD dwRet = NO_ERR;
	dwRet = g_List[iID]->AddSendAddr(lpcwszIP, dwPort);
	return dwRet;
}

//送信先クリア
//戻り値：エラーコード
DWORD WINAPI ClearSendAddrDLL(
	int iID //[IN] InitializeDLLの戻り値
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	DWORD dwRet = NO_ERR;
	dwRet = g_List[iID]->ClearSendAddr();
	return dwRet;
}

//データ送信を開始
//戻り値：エラーコード
DWORD WINAPI StartSendDLL(
	int iID //[IN] InitializeDLLの戻り値
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	DWORD dwRet = NO_ERR;
	dwRet = g_List[iID]->StartSend();
	return dwRet;
}

//データ送信を停止
//戻り値：エラーコード
DWORD WINAPI StopSendDLL(
	int iID //[IN] InitializeDLLの戻り値
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	DWORD dwRet = NO_ERR;
	dwRet = g_List[iID]->StopSend();
	return dwRet;
}

//データ送信を開始
//戻り値：エラーコード
DWORD WINAPI AddSendDataDLL(
	int iID, //[IN] InitializeDLLの戻り値
	BYTE* pbData,
	DWORD dwSize
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	DWORD dwRet = NO_ERR;
	dwRet = g_List[iID]->AddSendData(pbData, dwSize);
	return dwRet;
}

//送信バッファをクリア
//戻り値：エラーコード
DWORD WINAPI ClearSendBuffDLL(
	int iID //[IN] InitializeDLLの戻り値
	)
{
	if( g_List[iID] == NULL ){
		return ERR_NOT_INIT;
	}
	DWORD dwRet = NO_ERR;
	dwRet = g_List[iID]->ClearSendBuff();
	return dwRet;
}
