#ifndef __PARSE_CH_TEXT_5_H__
#define __PARSE_CH_TEXT_5_H__

#include "StructDef.h"

////////////////////////////////////////////////////////////////////////////
//チャンネル情報ファイルの「ChSet5.txt」の読み込みと保存処理を行うためのクラス
//排他制御などは行っていないため、複数スレッドからのアクセスは上位層で排他制
//御を行うこと
////////////////////////////////////////////////////////////////////////////
class CParseChText5
{
public:
	//チャンネル情報のmultimap
	//キーはONID<<32 | TSID<<16 | SID
	//Readのみで追加などの操作はメンバ関数使用すること
	map<LONGLONG, CH_DATA5> chList;

public:
	CParseChText5(void);
	~CParseChText5(void);

	//ChSet5.txtの読み込みを行う
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// file_path		[IN]ChSet5.txtのフルパス
	BOOL ParseText(
		LPCWSTR filePath
		);
		
	//チャンネル情報を追加する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// ch_info			[IN]追加するチャンネル情報
	BOOL AddCh(
		CH_DATA5 chInfo
		);
		
	//チャンネル情報を削除
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// originalNetworkID		[IN]ONID
	// transportStreamID		[IN]TSID
	// serviceID				[IN]ServiceID
	BOOL DelCh(
		WORD originalNetworkID,
		WORD transportStreamID,
		WORD serviceID
		);

	//現在の情報をChSet5.txtに上書き保存する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// file_path				[IN]ChSet5.txtのフルパス(NULLで読み込み時のファイルパス使用)
	BOOL SaveChText(
		LPCWSTR filePath = NULL
		);
		
	//ONIDとServiceIDからTSIDを取得する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// originalNetworkID		[IN]ONID
	// serviceID				[IN]ServiceID
	WORD GetTSID(
		WORD originalNetworkID,
		WORD serviceID
		);

	//EPGデータの取得対象かを設定する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// originalNetworkID		[IN]ONID
	// transportStreamID		[IN]TSID
	// serviceID				[IN]ServiceID
	// enable					[IN]EPGデータの取得対象かどうか
	BOOL SetEpgCapMode(
		WORD originalNetworkID,
		WORD transportStreamID,
		WORD serviceID,
		BOOL enable
		);

protected:
	wstring filePath;

protected:
	BOOL Parse1Line(string parseLine, CH_DATA5* chInfo );
};

#endif
