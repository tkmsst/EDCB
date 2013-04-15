#include "StdAfx.h"
#include "PATTable.h"

#include "../../../Common/EpgTimerUtil.h"

CPATTable::CPATTable(void)
{
}

CPATTable::~CPATTable(void)
{
}

BOOL CPATTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	pmtMap.clear();

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

	if( section_syntax_indicator != 1 || (data[1]&0x40) != 0 ){
		//固定値がおかしい
		_OutputDebugString( L"++CPATTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0x00 ){
		//table_idがおかしい
		_OutputDebugString( L"++CPATTable:: table_id err 0x00 != 0x%02X", table_id );
		return FALSE;
	}
	if( readSize+section_length > dataSize && section_length > 3){
		//サイズ異常
		_OutputDebugString( L"++CPATTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}
	//CRCチェック
	crc32 = ((DWORD)data[3+section_length-4])<<24 |
		((DWORD)data[3+section_length-3])<<16 |
		((DWORD)data[3+section_length-2])<<8 |
		data[3+section_length-1];
	if( crc32 != _Crc32(3+section_length-4, data) ){
		_OutputDebugString( L"++CPATTable:: CRC err" );
		return FALSE;
	}

	if( section_length > 4 ){
		transport_stream_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		readSize += 5;
		while( readSize < (DWORD)section_length+3-4 ){
			PMT_DATA item;
			item.program_number = ((WORD)data[readSize])<<8 | data[readSize+1];
			item.PID = ((WORD)data[readSize+2]&0x1F)<<8 | data[readSize+3];

			pmtMap.insert(pair<WORD, PMT_DATA>(item.program_number, item));
			readSize+=4;
		}
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 3+section_length;
	}

	return TRUE;
}
