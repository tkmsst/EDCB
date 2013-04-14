#ifndef __PARSE_CH_TEXT_4_H__
#define __PARSE_CH_TEXT_4_H__

#include "StructDef.h"

////////////////////////////////////////////////////////////////////////////
//チャンネル情報ファイルの「ChSet4.txt」の読み込みと保存処理を行うためのクラス
//排他制御などは行っていないため、複数スレッドからのアクセスは上位層で排他制
//御を行うこと
////////////////////////////////////////////////////////////////////////////
class CParseChText4
{
public:
	//チャンネル情報のmultimap
	//キーはONID<<32 | TSID<<16 | SID
	//Readのみで追加などの操作はメンバ関数使用すること
	multimap<LONGLONG, CH_DATA4> chList;

public:
	CParseChText4(void);
	~CParseChText4(void);

	//ChSet4.txtの読み込みを行う
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// file_path		[IN]ChSet4.txtのフルパス
	BOOL ParseText(
		LPCWSTR filePath
		);
	
	//チャンネル情報を追加する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// ch_info			[IN]追加するチャンネル情報
	BOOL AddCh(
		CH_DATA4 chInfo
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
		WORD serviceID);

	//チャンネル情報を削除
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// space		[IN]物理チャンネル
	// ch			[IN]物理チャンネル
	BOOL DelCh(
		WORD space,
		WORD ch);

	//チャンネル情報を削除
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// space		[IN]物理チャンネル
	// ch			[IN]物理チャンネル
	// serviceID				[IN]ServiceID
	BOOL DelChService(
		WORD space,
		WORD ch,
		WORD serviceID);

	//現在の情報をChSet4.txtに上書き保存する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// file_path				[IN]ChSet4.txtのフルパス(NULLで読み込み時のファイルパス使用)
	BOOL SaveChText(
		LPCWSTR filePath = NULL
		);
	
	CParseChText4& operator=(const CParseChText4& o)
	{
		chList = o.chList;
		return *this;
	};

protected:
	wstring filePath;

protected:
	BOOL Parse1Line(string parseLine, CH_DATA4* chInfo );
};

#endif
