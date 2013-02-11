#ifndef __SEND_TS_TCP_DLL_UTIL_H__
#define __SEND_TS_TCP_DLL_UTIL_H__

#include "SendTSTCP.h"
#include "ErrDef.h"

using namespace sendtstcp;

class CSendTSTCPDllUtil
{
public:
	CSendTSTCPDllUtil(void);
	~CSendTSTCPDllUtil(void);

	//DLLの初期化
	//戻り値：エラーコード
	DWORD Initialize(
		);

	//DLLの開放
	//戻り値：なし
	void UnInitialize(
		);

	//送信先を追加
	//戻り値：エラーコード
	DWORD AddSendAddr(
		LPCWSTR lpcwszIP,
		DWORD dwPort
		);

	//送信先クリア
	//戻り値：エラーコード
	DWORD ClearSendAddr(
		);

	//データ送信を開始
	//戻り値：エラーコード
	DWORD StartSend(
		);

	//データ送信を停止
	//戻り値：エラーコード
	DWORD StopSend(
		);

	//データ送信を開始
	//戻り値：エラーコード
	DWORD AddSendData(
		BYTE* pbData,
		DWORD dwSize
		);

	//送信バッファをクリア
	//戻り値：エラーコード
	DWORD ClearSendBuff(
		);
		
protected:
	HMODULE m_hModule;
	int m_iID;

	sendtstcp::InitializeDLL pfnInitializeDLL;
	sendtstcp::UnInitializeDLL pfnUnInitializeDLL;
	sendtstcp::AddSendAddrDLL pfnAddSendAddrDLL;
	sendtstcp::ClearSendAddrDLL pfnClearSendAddrDLL;
	sendtstcp::StartSendDLL pfnStartSendDLL;
	sendtstcp::StopSendDLL pfnStopSendDLL;
	sendtstcp::AddSendDataDLL pfnAddSendDataDLL;
	sendtstcp::ClearSendBuffDLL pfnClearSendBuffDLL;

protected:
	BOOL LoadDll(void);
	BOOL UnLoadDll(void);
};

#endif
