// Write_Default.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include "Write_PlugIn.h"
#include "WriteMain.h"
#include "SettingDlg.h"
#include <tchar.h>
#include <map>
using namespace std;

extern map<DWORD, CWriteMain*> g_List;
DWORD g_nextID = 1;

extern HINSTANCE g_instance;

#define PLUGIN_NAME L"デフォルト 188バイトTS出力 PlugIn"

DWORD GetNextID()
{
	DWORD nextID = 0xFFFFFFFF;

	map<DWORD, CWriteMain*>::iterator itr;
	itr = g_List.find(g_nextID);
	if( itr == g_List.end() ){
		nextID = g_nextID;
		g_nextID++;
		if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
			g_nextID = 1;
		}
	}else{
		for( DWORD i=1; i<0xFFFFFFFF; i++ ){
			itr = g_List.find(g_nextID);
			if( itr == g_List.end() ){
				nextID = g_nextID;
				g_nextID++;
				if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
					g_nextID = 1;
				}
				break;
			}else{
				g_nextID++;
			}
			if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
				g_nextID = 1;
			}
		}
	}

	return nextID;
}


//PlugInの名前を取得する
//nameがNULL時は必要なサイズをnameSizeで返す
//通常nameSize=256で呼び出し
//戻り値
// TRUE（成功）、FALSE（失敗）
//引数：
// name						[OUT]名称
// nameSize					[IN/OUT]nameのサイズ(WCHAR単位)
BOOL WINAPI GetPlugInName(
	WCHAR* name,
	DWORD* nameSize
	)
{
	if( name == NULL ){
		if( nameSize == NULL ){
			return FALSE;
		}else{
			*nameSize = (DWORD)wcslen(PLUGIN_NAME)+1;
		}
	}else{
		if( nameSize == NULL ){
			return FALSE;
		}else{
			if( *nameSize < (DWORD)wcslen(PLUGIN_NAME)+1 ){
				*nameSize = (DWORD)wcslen(PLUGIN_NAME)+1;
				return FALSE;
			}else{
				wcscpy_s(name, *nameSize, PLUGIN_NAME);
			}
		}
	}
	return TRUE;
}

//PlugInで設定が必要な場合、設定用のダイアログなどを表示する
//引数：
// parentWnd				[IN]親ウインドウ
void WINAPI Setting(
	HWND parentWnd
	)
{
	WCHAR dllPath[512] = L"";
	GetModuleFileName(g_instance, dllPath, 512);

	wstring iniPath = dllPath;
	iniPath += L".ini";

	WCHAR buff[1024] = L"";
	GetPrivateProfileString(L"SET", L"Size", L"770048", buff, 1024, iniPath.c_str());

	CSettingDlg dlg;
	dlg.size = buff;
	if( dlg.CreateSettingDialog(g_instance, parentWnd) == IDOK ){
		WritePrivateProfileString(L"SET", L"Size", dlg.size.c_str(), iniPath.c_str());
	}

//	MessageBox(parentWnd, PLUGIN_NAME, L"Write PlugIn", MB_OK);
}

//複数保存対応のためインスタンスを新規に作成する
//複数対応できない場合はこの時点でエラーとする
//戻り値
// TRUE（成功）、FALSE（失敗）
//引数：
// id				[OUT]識別ID
BOOL WINAPI CreateCtrl(
	DWORD* id
	)
{
	if( id == NULL ){
		return FALSE;
	}

	CWriteMain* main = new CWriteMain;
	*id = GetNextID();
	g_List.insert(pair<DWORD, CWriteMain*>(*id, main));

	return TRUE;
}

//インスタンスを削除する
//戻り値
// TRUE（成功）、FALSE（失敗）
//引数：
// id				[IN]識別ID
BOOL WINAPI DeleteCtrl(
	DWORD id
	)
{
	map<DWORD, CWriteMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	delete itr->second;

	g_List.erase(itr);

	return TRUE;
}

//ファイル保存を開始する
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// id					[IN]識別ID
// fileName				[IN]保存ファイルフルパス（必要に応じて拡張子変えたりなど行う）
// overWriteFlag		[IN]同一ファイル名存在時に上書きするかどうか（TRUE：する、FALSE：しない）
// createSize			[IN]入力予想容量（188バイトTSでの容量。即時録画時など総時間未定の場合は0。延長などの可能性もあるので目安程度）
BOOL WINAPI StartSave(
	DWORD id,
	LPCWSTR fileName,
	BOOL overWriteFlag,
	ULONGLONG createSize
	)
{
	map<DWORD, CWriteMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->_StartSave(fileName, overWriteFlag, createSize);
}

//ファイル保存を終了する
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// id					[IN]識別ID
BOOL WINAPI StopSave(
	DWORD id
	)
{
	map<DWORD, CWriteMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->_StopSave();
}

//実際に保存しているファイルパスを取得する（再生やバッチ処理に利用される）
//filePathがNULL時は必要なサイズをfilePathSizeで返す
//通常filePathSize=512で呼び出し
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// id					[IN]識別ID
// filePath				[OUT]保存ファイルフルパス
// filePathSize			[IN/OUT]filePathのサイズ(WCHAR単位)
BOOL WINAPI GetSaveFilePath(
	DWORD id,
	WCHAR* filePath,
	DWORD* filePathSize
	)
{
	map<DWORD, CWriteMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->_GetSaveFilePath(filePath, filePathSize);
}

//保存用TSデータを送る
//空き容量不足などで書き出し失敗した場合、writeSizeの値を元に
//再度保存処理するときの送信開始地点を決める
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// id					[IN]識別ID
// data					[IN]TSデータ
// size					[IN]dataのサイズ
// writeSize			[OUT]保存に利用したサイズ
BOOL WINAPI AddTSBuff(
	DWORD id,
	BYTE* data,
	DWORD size,
	DWORD* writeSize
	)
{
	map<DWORD, CWriteMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->_AddTSBuff(data, size, writeSize);
}
