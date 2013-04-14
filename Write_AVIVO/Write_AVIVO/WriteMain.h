#pragma once

#include "../../Common/Util.h"
#include "../../Common/StringUtil.h"
#include "../../Common/PathUtil.h"

#include "DShowCtrl.h"

class CWriteMain
{
public:
	CWriteMain(void);
	~CWriteMain(void);
	
	//ファイル保存を開始する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// fileName				[IN]保存ファイルフルパス（必要に応じて拡張子変えたりなど行う）
	// overWriteFlag		[IN]同一ファイル名存在時に上書きするかどうか（TRUE：する、FALSE：しない）
	// createSize			[IN]入力予想容量（188バイトTSでの容量。即時録画時など総時間未定の場合は0。延長などの可能性もあるので目安程度）
	BOOL _StartSave(
		LPCWSTR fileName,
		BOOL overWriteFlag,
		ULONGLONG createSize,
		HINSTANCE hInstance
		);

	//ファイル保存を終了する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL _StopSave(
		);

	//実際に保存しているファイルパスを取得する（再生やバッチ処理に利用される）
	//filePathがNULL時は必要なサイズをfilePathSizeで返す
	//通常filePathSize=512で呼び出し
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// filePath				[OUT]保存ファイルフルパス
	// filePathSize			[IN/OUT]filePathのサイズ(WCHAR単位)
	BOOL _GetSaveFilePath(
		WCHAR* filePath,
		DWORD* filePathSize
		);

	//保存用TSデータを送る
	//空き容量不足などで書き出し失敗した場合、writeSizeの値を元に
	//再度保存処理するときの送信開始地点を決める
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// data					[IN]TSデータ
	// size					[IN]dataのサイズ
	// writeSize			[OUT]保存に利用したサイズ
	BOOL _AddTSBuff(
		BYTE* data,
		DWORD size,
		DWORD* writeSize
		);

protected:
	wstring savePath;
	CDShowCtrl dshowCtrl;

protected:
	BOOL GetNextFileName(wstring filePath, wstring& newPath);
};

