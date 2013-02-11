#ifndef __PARSE_RESERVE_TEXT_H__
#define __PARSE_RESERVE_TEXT_H__

#include "StructDef.h"

////////////////////////////////////////////////////////////////////////////
//予約情報ファイルの「Reserve.txt」の読み込みと保存処理を行うためのクラス
//排他制御などは行っていないため、複数スレッドからのアクセスは上位層で排他制
//御を行うこと
////////////////////////////////////////////////////////////////////////////
class CParseReserveText
{
public:
	//予約一覧のmultimap
	//キーは録画開始日時
	//Readのみで追加などの操作はメンバ関数使用すること
	multimap<wstring, RESERVE_DATA*> reserveMap;
	//予約一覧のmap
	//キーは通し番号
	//Readのみで追加などの操作はメンバ関数使用すること
	map<DWORD, RESERVE_DATA*> reserveIDMap;

public:
	CParseReserveText(void);
	~CParseReserveText(void);

	//Reserve.txtの読み込みを行う
	//引数：
	// file_path	Reserve.txtのフルパス
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL ParseReserveText(LPCWSTR filePath);
	//Reserve.txtの追加読み込みを行う(IDが0のものだけ追加読み込み)
	//引数：
	// file_path	Reserve.txtのフルパス(NULLで読み込み時のファイルパス使用)
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL AddParseReserveText(LPCWSTR filePath = NULL);
	//現在の情報をReserve.txtに上書き保存する
	//引数：
	// file_path	Reserve.txtのフルパス(NULLで読み込み時のファイルパス使用)
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL SaveReserveText(LPCWSTR filePath = NULL);

	//予約情報を追加する
	//引数：
	// item			追加する予約情報
	// reserveID	追加したID
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL AddReserve(RESERVE_DATA* item, DWORD* reserveID);
	//予約情報を変更する
	//引数：
	// item			変更する予約情報
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL ChgReserve(RESERVE_DATA* item);
	//予約情報を削除する
	//引数：
	// reserve_id	削除する予約情報のID
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL DelReserve(DWORD reserveID);

	void SwapMap();
protected:
	wstring loadFilePath;

	DWORD nextID;
protected:
	BOOL Parse1Line(string parseLine, RESERVE_DATA* item );
	DWORD GetNextReserveID();

};

#endif
