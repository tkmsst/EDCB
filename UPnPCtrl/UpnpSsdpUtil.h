#ifndef __UPNP_SSDP_UTIL_H__
#define __UPNP_SSDP_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "SortListUtil.h"
#include "UpnpStructDef.h"

typedef void* UPNP_SERVER_HANDLE;
typedef void* UPNP_MSEARCH_HANDLE;

typedef enum{
	SSDP_unknown        = 0x0000,
	SSDP_alive			= 0x0001,	//alive通知 notifyParamは通知内容(UPNP_SSDP_NOTIFY_INFO*)
	SSDP_byebye			= 0x0002,	//byebye通知 notifyParamは通知内容(UPNP_SSDP_NOTIFY_INFO*)
	SSDP_update			= 0x0004,	//update通知 notifyParamは通知内容(UPNP_SSDP_NOTIFY_INFO*)
	SSDP_MSearch		= 0x0010,	//M-Searchの結果 notifyParamは通知内容(UPNP_MSEARCH_RESPONSE_INFO*)
	SSDP_MSearchEnd		= 0x0020,	//M-Searchの完了 notifyParamはUPNP_MSEARCH_HANDLE
} SSDP_NOTIFY_STATUS;


//SSDPのNotify通知用コールバック関数
typedef void (*UPNP_SSDP_CALLBACK)(
	SSDP_NOTIFY_STATUS notifyType,		//[IN]ssdpの種類
	void* notifyParam,					//[IN]NOTIFYの内容
	void* param							//[IN]ユーザー指定のパラメータ
);

typedef int (*UPNP_MSEARCH_REQUEST_CALLBACK)(
	UPNP_MSEARCH_REQUEST_INFO* requestParam,	//[IN]NOTIFYの内容
	void* param,								//[IN]ユーザー指定のパラメータ
	SORT_LIST_HANDLE resDeviceList				//[OUT]レスポンスとして返すデバイスの情報を入れる　キー：UPNP_MSEARCH_RES_DEV_INFOのuuid 要素：UPNP_MSEARCH_RES_DEV_INFO*
);

//ハンドルの作成
//戻り値：ハンドル、エラー時NULL
UPNP_SERVER_HANDLE UPNP_SERVER_CreateHandle(
	UPNP_SSDP_CALLBACK ssdpCallBack,	//[IN]SSDPのNotify通知用コールバック
	void* ssdpCallBackParam,			//[IN]SSDPのNotify通知用コールバック呼出時に入れるパラメーター
	UPNP_MSEARCH_REQUEST_CALLBACK msearchCallBack,	//[IN]SSDPのM-SEARCHリクエスト通知用コールバック
	void* msearchCallBackParam			//[IN]SSDPのM-SEARCHリクエスト通知用コールバック呼出時に入れるパラメーター
);

//ハンドルの解放
//解放後handleはNULLに
void UPNP_SERVER_CloseHandle(
	UPNP_SERVER_HANDLE* handle			//[IN]UPNP_SERVER_CreateHandleの戻り値
);

//UPnPサーバーの起動
//戻り値：エラーコード
int UPNP_SERVER_Start(
	UPNP_SERVER_HANDLE handle			//[IN]UPNP_SERVER_CreateHandleの戻り値
);

//UPnPサーバーの停止
//戻り値：エラーコード
int UPNP_SERVER_Stop(
	UPNP_SERVER_HANDLE handle			//[IN]UPNP_SERVER_CreateHandleの戻り値
);

//Notify用のdeviceとserviceを登録する
int UPNP_SERVER_AddNotifyInfo(
	UPNP_SERVER_HANDLE handle,			//[IN]UPNP_SERVER_CreateHandleの戻り値
	const char* uuid,					//[IN]uuid「uuid:」は省く
	const char* urn,					//[IN]urn「urn:」を含む
	int locationPort,					//[IN]Locationのポート
	const char* locationUri				//[IN]Locationの「http://ip:port」より後ろの部分(「/」から始まる)
);

//Notify用のdeviceとserviceの登録を解除する
int UPNP_SERVER_RemoveNotifyInfo(
	UPNP_SERVER_HANDLE handle,			//[IN]UPNP_SERVER_CreateHandleの戻り値
	const char* uuid					//[IN]uuid「uuid:」は省く
);

//Notify用のdeviceとserviceの全登録を解除する
int UPNP_SERVER_ClearNotifyInfo(
	UPNP_SERVER_HANDLE handle			//[IN]UPNP_SERVER_CreateHandleの戻り値
);

//M-Search 機器の検索を実行（同期）
//戻り値：ハンドル、エラー時NULL
UPNP_MSEARCH_HANDLE UPNP_MSearch_Exec(
	UPNP_SERVER_HANDLE handle,			//[IN]UPNP_SERVER_CreateHandleの戻り値
	const char* searchTarget,			//[IN]実行時のSTの値（検索キー）
	short mx,							//[IN]実行時のMXの値(単位：秒)（タイムアウト）
	SORT_LIST_HANDLE* resultList		//[OUT]検索結果のリスト、キー：char* のUUID、要素：UPNP_MSEARCH_INFO*　UPNP_MSearch_CloseHandleで開放するされる
);

//M-Search 機器の検索を実行（非同期）
//検索結果はコールバックでの通知のみ
//戻り値：ハンドル、エラー時NULL
UPNP_MSEARCH_HANDLE UPNP_MSearch_ExecAsync(
	UPNP_SERVER_HANDLE handle,			//[IN]UPNP_SERVER_CreateHandleの戻り値
	const char* searchTarget,			//[IN]実行時のSTの値（検索キー）
	short mx							//[IN]実行時のMXの値(単位：秒)（タイムアウト）
);

//M-Searchハンドルの解放
//非同期実行時は動作のキャンセルもされる
//解放後handleはNULLに
void UPNP_MSearch_CloseHandle(
	UPNP_MSEARCH_HANDLE* handle			//[IN]UPNP_MSearch_Exec or UPNP_MSearch_ExecAsyncの戻り値
);

//DDD(Device Description Document)取得実行(同期)
//戻り値：0以上で成功、0未満でエラー
int UPNP_GetDDD_Exec(
	const char* location						//[IN]M-Search結果のlocation
);

#ifdef __cplusplus
}
#endif

#endif
