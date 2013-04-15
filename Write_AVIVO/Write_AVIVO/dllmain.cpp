// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "stdafx.h"

#include "WriteMain.h"
#include <map>
using namespace std;

map<DWORD, CWriteMain*> g_List;
HINSTANCE g_Instance;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_Instance = (HINSTANCE)hModule;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if( g_List.size() > 0 ){
			map<DWORD, CWriteMain*>::iterator itr;
			for( itr = g_List.begin(); itr != g_List.end(); itr++ ){
				itr->second->_StopSave();
				delete itr->second;
			}
		}
		break;
	}
	return TRUE;
}

