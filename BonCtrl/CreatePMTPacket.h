#pragma once

#include "../Common/Util.h"
#include "../Common/ErrDef.h"
#include "../Common/EpgTimerUtil.h"
#include "../Common/TSPacketUtil.h"
#include "../Common/TSBuffUtil.h"

class CCreatePMTPacket
{
public:
	CCreatePMTPacket(void);
	~CCreatePMTPacket(void);

	//PMT作成時のモード
	//引数：
	// needCaption			[IN]字幕データを含めるかどうか（TRUE:含める、FALSE：含めない）
	// needData				[IN]データカルーセルを含めるかどうか（TRUE:含める、FALSE：含めない）
	void SetCreateMode(
		BOOL needCaption,
		BOOL needData
	);

	//作成元となるPMTのパケットを入力
	//戻り値：
	// エラーコード
	//引数：
	// packet			//[IN] PMTのパケット
	DWORD AddData(
		CTSPacketUtil* packet
	);

	//必要なPIDかを確認
	//戻り値：
	// TRUE（必要）、FALSE（不必要）
	//引数：
	// PID				//[IN]確認するPID
	BOOL IsNeedPID(
		WORD PID
	);

	//作成PMTのバッファポインタを取得
	//戻り値：
	// 作成PMTのバッファポインタ
	//引数：
	// buff					[OUT]作成したPMTパケットへのポインタ（次回呼び出し時まで有効）
	// size					[OUT]buffのサイズ
	// incrementFlag		[IN]TSパケットのCounterをインクリメントするかどうか（TRUE:する、FALSE：しない）
	BOOL GetPacket(
		BYTE** buff,
		DWORD* size,
		BOOL incrementFlag = TRUE
	);

	//内部情報をクリア
	void Clear();

	BYTE GetVersion();

protected:
	DWORD DecodePMT(BYTE* data, DWORD dataSize);
	void ClearSecondBuff();

	void CreatePMT();
	void CreatePacket();
	void IncrementCounter();
protected:
	CTSBuffUtil buffUtil;

	BOOL needCaption;
	BOOL needData;

	WORD lastPmtPID;
	WORD lastPcrPID;
	WORD lastPgNumber;
	BYTE lastVersion;

	BYTE* firstDescBuff;
	WORD firstDescBuffSize;

	typedef struct _SECOND_DESC_BUFF{
		BYTE stream_type;
		WORD elementary_PID;
		WORD ES_info_length;
		WORD descBuffSize;
		BYTE* descBuff;
		WORD quality;
		WORD qualityPID;
		_SECOND_DESC_BUFF(){
			stream_type = 0;
			elementary_PID = 0;
			ES_info_length = 0;
			descBuffSize = 0;
			descBuff = NULL;
			quality = 0;
			qualityPID = 0;
		}
		~_SECOND_DESC_BUFF(){
			SAFE_DELETE_ARRAY(descBuff);
		}
	}SECOND_DESC_BUFF;
	vector<SECOND_DESC_BUFF*> secondDescBuff;

	map<WORD,WORD> emmPIDMap;

	map<WORD,WORD> needPIDList;

	BYTE* createPSI;
	int createPSISize;
	
	BYTE* createPacket;
	int createPacketSize;

	BYTE createVer;
	BYTE createCounter;
};
