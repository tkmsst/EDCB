#pragma once

#include <windows.h>

#include "../Common/Util.h"

class CPacketInit
{
public:
	CPacketInit(void);
	~CPacketInit(void);

	//入力バッファを188バイト単位のTSに変換し、188の倍数になるようにそろえる
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// inData			[IN]入力TSデータ
	// inSize			[IN]inDataのサイズ（BYTE単位）
	// outData			[OUT]188バイトに整列したバッファ（呼び出し元でdeleteする必要あり）
	// outSize			[OUT]outDataのサイズ（BYTE単位）
	BOOL GetTSData(
		BYTE* inData,
		DWORD inSize,
		BYTE** outData,
		DWORD* outSize
		);

	//内部バッファのクリア
	void ClearBuff();

protected:
	BYTE* nextStartBuff;
	DWORD nextStartSize;

	typedef enum TS_MODE{
		TS_NONE = 0,
		TS_188 = 188,
		TS_192 = 192,
		TS_204 = 204
	};
	TS_MODE TSMode;

	int lastOffset;

	BYTE* copyBuff;
	DWORD copyBuffSize;

protected:
	//入力バッファを188バイト単位のTSにするoffset位置と1パケットのサイズを取得する
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	//引数：
	// data				[IN]入力TSデータ
	// size				[IN]dataのサイズ（BYTE単位）
	// offset			[OUT]nextStartBuffの先頭を0とした開始オフセット位置
	// packetSize		[OUT]1パケットのサイズ
	BOOL CheckSync(
		BYTE* data,
		DWORD size,
		DWORD* offset,
		DWORD* packetSize
		);
};
