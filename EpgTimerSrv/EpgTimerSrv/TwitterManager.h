#pragma once

#include "../../Common/twitterUtil.h"
#include "../../Common/StructDef.h"

typedef enum{
	TW_TEXT	= 0,				//テキストそのまま
	TW_CHG_RESERVE_RELOADEPG,	//EPG再読み込み
	TW_CHG_RESERVE_CHK_REC,		//録画中の追従
	TW_ADD_RESERVE,				//予約追加
	TW_REC_START,				//録画開始
	TW_REC_END,					//録画終了
}SEND_TWEET_MODE;

class CTwitterManager
{
public:
	CTwitterManager(void);
	~CTwitterManager(void);

	//Proxy使用を設定
	//戻り値：
	// エラーコード
	//引数：
	// useProxy			[IN]Proxy使うかどうか（TRUE:Proxy使う）
	// proxyInfo		[IN]Proxy使う場合の設定情報
	void SetProxy(
		BOOL useProxy,
		USE_PROXY_INFO* proxyInfo
		);

	void SendTweet(
		SEND_TWEET_MODE mode,
		void* param1,
		void* param2,
		void* param3
		);

	//非同期ツイートの残りを取得する
	//戻り値：
	// 個数
	DWORD GetTweetQue(
		);
protected:
	HANDLE lockEvent;
	CTwitterUtil twitterUtil;

	typedef struct _MACRO_DATA{
		wstring oldTitle;
		wstring oldSDYYYY;
		wstring oldSDYY;
		wstring oldSDMM;
		wstring oldSDM;
		wstring oldSDDD;
		wstring oldSDD;
		wstring oldSTHH;
		wstring oldSTH;
		wstring oldSTMM;
		wstring oldSTM;
		wstring oldSTSS;
		wstring oldSTS;
		wstring oldEDYYYY;
		wstring oldEDYY;
		wstring oldEDMM;
		wstring oldEDM;
		wstring oldEDDD;
		wstring oldEDD;
		wstring oldETHH;
		wstring oldETH;
		wstring oldETMM;
		wstring oldETM;
		wstring oldETSS;
		wstring oldETS;
		wstring oldONID10;
		wstring oldTSID10;
		wstring oldSID10;
		wstring oldEID10;
		wstring oldONID16;
		wstring oldTSID16;
		wstring oldSID16;
		wstring oldEID16;
		wstring oldServiceName;
		wstring oldSDYYYY28;
		wstring oldSDYY28;
		wstring oldSDMM28;
		wstring oldSDM28;
		wstring oldSDDD28;
		wstring oldSDD28;
		wstring oldSTHH28;
		wstring oldSTH28;
		wstring oldEDYYYY28;
		wstring oldEDYY28;
		wstring oldEDMM28;
		wstring oldEDM28;
		wstring oldEDDD28;
		wstring oldEDD28;
		wstring oldETHH28;
		wstring oldETH28;
		wstring oldDUHH;
		wstring oldDUH;
		wstring oldDUMM;
		wstring oldDUM;
		wstring oldDUSS;
		wstring oldDUS;
		wstring newTitle;
		wstring newSDYYYY;
		wstring newSDYY;
		wstring newSDMM;
		wstring newSDM;
		wstring newSDDD;
		wstring newSDD;
		wstring newSTHH;
		wstring newSTH;
		wstring newSTMM;
		wstring newSTM;
		wstring newSTSS;
		wstring newSTS;
		wstring newEDYYYY;
		wstring newEDYY;
		wstring newEDMM;
		wstring newEDM;
		wstring newEDDD;
		wstring newEDD;
		wstring newETHH;
		wstring newETH;
		wstring newETMM;
		wstring newETM;
		wstring newETSS;
		wstring newETS;
		wstring newONID10;
		wstring newTSID10;
		wstring newSID10;
		wstring newEID10;
		wstring newONID16;
		wstring newTSID16;
		wstring newSID16;
		wstring newEID16;
		wstring newServiceName;
		wstring newSDYYYY28;
		wstring newSDYY28;
		wstring newSDMM28;
		wstring newSDM28;
		wstring newSDDD28;
		wstring newSDD28;
		wstring newSTHH28;
		wstring newSTH28;
		wstring newEDYYYY28;
		wstring newEDYY28;
		wstring newEDMM28;
		wstring newEDM28;
		wstring newEDDD28;
		wstring newEDD28;
		wstring newETHH28;
		wstring newETH28;
		wstring newDUHH;
		wstring newDUH;
		wstring newDUMM;
		wstring newDUM;
		wstring newDUSS;
		wstring newDUS;
		wstring newSYMDHM;
		wstring newSYMDHM28;
		wstring newEYMDHM;
		wstring newEYMDHM28;
		wstring newSEYMDHM;
		wstring newSEYMDHM28;
		wstring drops;
		wstring scrambles;
		wstring result;
	}MACRO_DATA;

protected:
	//PublicAPI排他制御用
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 60*1000);
	void UnLock(LPCWSTR log = NULL);

	void CreateTextChgResReload(wstring& text, RESERVE_DATA* oldInfo, RESERVE_DATA* newInfo);
	void CreateTextChgResRec(wstring& text, RESERVE_DATA* oldInfo, RESERVE_DATA* newInfo, EPGDB_EVENT_INFO* eventInfo);
	void CreateTextAddRes(wstring& text, RESERVE_DATA* resInfo);
	void CreateTextRecStart(wstring& text, RESERVE_DATA* resInfo);
	void CreateTextRecStop(wstring& text, REC_FILE_INFO* resInfo);

	void ConvertText(wstring& text, MACRO_DATA* macroData);
};

