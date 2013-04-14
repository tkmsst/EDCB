#pragma once

#include <windows.h>

#include "../Common/Util.h"
#include "../Common/PathUtil.h"
#include "../Common/StringUtil.h"
#include "../Common/ErrDef.h"

#include "IBonDriver.h"
#include "IBonDriver2.h"
#include "BonCtrlDef.h"

class CBonDriverUtil
{
public:
	CBonDriverUtil(void);
	~CBonDriverUtil(void);

	//初期設定
	//設定ファイル保存先とBonDriverフォルダを指定
	//引数：
	// settingFolderPath		[IN]設定ファイル保存フォルダパス
	// bonDriverFolderPath		[IN]BonDriverフォルダパス
	void SetSettingFolder(
		LPCWSTR settingFolderPath,
		LPCWSTR bonDriverFolderPath
		);

	//BonDriverフォルダのBonDriver_*.dllを列挙
	//戻り値：
	// エラーコード
	//引数：
	// bonList			[OUT]検索できたBonDriver一覧（mapのキー 内部インデックス値、mapの値 BonDriverファイル名）
	DWORD EnumBonDriver(
		map<int, wstring>* bonList
		);

	//BonDriverのロード
	//BonDriverをロードしてチャンネル情報などを取得（インデックス値で指定）
	//戻り値：
	// エラーコード
	//引数：
	// index			[IN]EnumBonDriverで取得されたBonDriverのインデックス値
	DWORD OpenBonDriver(
		int index,
		int openWait = 200
		);

	//BonDriverをロードしてチャンネル情報などを取得（ファイル名で指定）
	//戻り値：
	// エラーコード
	//引数：
	// bonDriverFile	[IN]EnumBonDriverで取得されたBonDriverのファイル名
	DWORD OpenBonDriver(
		LPCWSTR bonDriverFile,
		int openWait = 200
		);

	//ロードしているBonDriverの開放
	//戻り値：
	// エラーコード
	DWORD CloseBonDriver();

	//ロードしたBonDriverの情報取得
	//SpaceとChの一覧を取得する
	//戻り値：
	// エラーコード
	//引数：
	// spaceMap			[OUT] SpaceとChの一覧（mapのキー Space）
	DWORD GetOriginalChList(
		map<DWORD, BON_SPACE_INFO>* spaceMap
	);

	//BonDriverのチューナー名を取得
	//戻り値：
	// チューナー名
	wstring GetTunerName();

	//チャンネル変更
	//戻り値：
	// エラーコード
	//引数：
	// space			[IN]変更チャンネルのSpace
	// ch				[IN]変更チャンネルの物理Ch
	DWORD SetCh(
		DWORD space,
		DWORD ch
		);

	//現在のチャンネル取得
	//戻り値：
	// エラーコード
	//引数：
	// space			[IN]現在のチャンネルのSpace
	// ch				[IN]現在のチャンネルの物理Ch
	DWORD GetNowCh(
		DWORD* space,
		DWORD* ch
		);

	BOOL GetSetCh(
		DWORD* space,
		DWORD* ch
		);

	//TSストリームを取得
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// data				[OUT]BonDriver内部バッファのポインタ
	// size				[OUT]取得バッファのサイズ
	// remain			[OUT]未取得バッファのサイズ
	BOOL GetTsStream(
		BYTE **data,
		DWORD *size,
		DWORD *remain
		);

	//シグナルレベルの取得
	//戻り値：
	// シグナルレベル
	float GetSignalLevel();

	//Ch設定3のファイルパスを取得
	//戻り値：
	// Ch設定3のファイルパス
	wstring GetChSet4Path();

	//Ch設定4のファイルパスを取得
	//戻り値：
	// Ch設定4のファイルパス
	wstring GetChSet5Path();

	//OpenしたBonDriverのインデックス値を取得
	//戻り値：
	// インデックス値（-1で未Open）
	int GetOpenBonDriverIndex();

	//OpenしたBonDriverのファイル名を取得
	//戻り値：
	// BonDriverのファイル名（拡張子含む）
	wstring GetOpenBonDriverFileName();

	//指定物理チャンネルのチャンネル名を取得
	//戻り値：
	// BonDriverで定義されている物理チャンネル名
	wstring GetChName(DWORD space, DWORD ch);

protected:
	HANDLE lockEvent;

	wstring settingFolderPath;
	wstring bonDriverFolderPath;

	map<int, BON_DRIVER_INFO> bonDllMap;

	int loadIndex;
	wstring loadTunerName;
	map<DWORD, BON_SPACE_INFO> loadChMap;
	BOOL initChSetFlag;
	IBonDriver* bonIF;
	IBonDriver2* bon2IF;
	HMODULE module;

	DWORD setSpace;
	DWORD setCh;
protected:
	//PublicAPI排他制御用
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 5*1000);
	void UnLock(LPCWSTR log = NULL);

	//ファイル名の最後が本当に「.dll」か確認
	//戻り値：
	// TRUE（「.dll」が最後）、FALSE（「.dll」が最後ではない）
	//引数：
	// name						[IN]確認する文字列
	BOOL IsDllFile(wstring name);

	//BonDriverをロード時の本体
	//戻り値：
	// エラーコード
	//引数：
	// bonDriverFilePath		[IN] ロードするBonDriverのファイルパス
	DWORD _OpenBonDriver(
		LPCWSTR bonDriverFilePath,
		int openWait
		);

	//ロードしているBonDriverの開放の本体
	//戻り値：
	// エラーコード
	DWORD _CloseBonDriver();
};

