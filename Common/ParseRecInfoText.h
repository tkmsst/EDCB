#ifndef __PARSE_RECINFO_TEXT_H__
#define __PARSE_RECINFO_TEXT_H__

#include "StructDef.h"

////////////////////////////////////////////////////////////////////////////
//録画済み情報ファイルの「RecInfo.txt」の読み込みと保存処理を行うためのクラス
//排他制御などは行っていないため、複数スレッドからのアクセスは上位層で排他制
//御を行うこと
////////////////////////////////////////////////////////////////////////////
class CParseRecInfoText
{
public:
	//録画済み一覧のmultimap
	//キーは録画開始日時
	//Readのみで追加などの操作はメンバ関数使用すること
	multimap<wstring, REC_FILE_INFO*> recInfoMap;
	//録画済み一覧のmap
	//キーは通し番号
	//Readのみで追加などの操作はメンバ関数使用すること
	map<DWORD, REC_FILE_INFO*> recIDMap;

public:
	CParseRecInfoText(void);
	~CParseRecInfoText(void);

	//RecInfo.txtの読み込みを行う
	//引数：
	// file_path	RecInfo.txtのフルパス
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL ParseRecInfoText(LPCWSTR filePath);
	//現在の情報をReserve.txtに上書き保存する
	//引数：
	// file_path	RecInfo.txtのフルパス(NULLで読み込み時のファイルパス使用)
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL SaveRecInfoText(LPCWSTR filePath = NULL);

	//録画済み情報を追加する
	//引数：
	// item			追加する録画済み情報
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL AddRecInfo(REC_FILE_INFO* item);
	//録画済み情報を削除する
	//引数：
	// id	削除する録画済み情報のID
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL DelRecInfo(DWORD id);
	//プロテクト情報を変更する
	//引数：
	// id	変更する録画済み情報のID
	// flag	プロテクトフラグ
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL ChgProtectRecInfo(DWORD id, BYTE flag);

	void GetProtectFiles(map<wstring, wstring>* fileMap);

	//一覧の自動削除を行うかの設定
	//引数：
	// keep_count		残しておく情報の個数
	// auto_del_flag	自動削除を行うかどうか（TRUE:行う、FALSE：行わない）
	void SetAutoDel(DWORD keepCount, BOOL autoDelFlag){ this->keepCount = keepCount; this->autoDelFlag = autoDelFlag; };

protected:
	wstring loadFilePath;
	DWORD keepCount;
	BOOL autoDelFlag;

	DWORD nextID;

	map<wstring, wstring> protectFileList;
protected:
	BOOL Parse1Line(string parseLine, REC_FILE_INFO* item );
	void AutoDelInfo(DWORD keepCount);
	DWORD GetNextReserveID();

	void DelTS_InfoFile(wstring tsFilePath);
	void AddPtotectFileList(wstring tsFilePath);
	void DelPtotectFileList(wstring tsFilePath);
};

#endif
