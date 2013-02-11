#include "StdAfx.h"
#include "TDTTable.h"

#include "../../../Common/EpgTimerUtil.h"
#include "../Descriptor/Descriptor.h"

CTDTTable::CTDTTable(void)
{
}

CTDTTable::~CTDTTable(void)
{
}

BOOL CTDTTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}

	//////////////////////////////////////////////////////
	//サイズのチェック
	//最低限table_idとsection_length+CRCのサイズは必須
	if( dataSize < 7 ){
		return FALSE;
	}
	//->サイズのチェック

	DWORD readSize = 0;
	//////////////////////////////////////////////////////
	//解析処理
	table_id = data[0];
	section_syntax_indicator = (data[1]&0x80)>>7;
	section_length = ((WORD)data[1]&0x0F)<<8 | data[2];
	readSize+=3;

	if( section_syntax_indicator != 0 ){
		//固定値がおかしい
		_OutputDebugString( L"++CTDTTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0x70 ){
		//table_idがおかしい
		_OutputDebugString( L"++CTDTTable:: table_id err 0x%02X", table_id );
		return FALSE;
	}
	if( section_length != 0x0005){
		//サイズ異常
		_OutputDebugString( L"++CTDTTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}

	if( section_length > 4 ){
		DWORD mjd = ((DWORD)data[readSize])<<8 | data[readSize+1];
		_MJDtoSYSTEMTIME(mjd, &jst_time);
		jst_time.wHour = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
		jst_time.wMinute = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
		jst_time.wSecond = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);

		readSize += 5;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 3+section_length;
	}

	return TRUE;
}

