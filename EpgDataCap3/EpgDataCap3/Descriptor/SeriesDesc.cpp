#include "StdAfx.h"
#include "SeriesDesc.h"

CSeriesDesc::CSeriesDesc(void)
{
	series_name_charLength = 0;
	series_name_char = NULL;
}

CSeriesDesc::~CSeriesDesc(void)
{
	SAFE_DELETE_ARRAY(series_name_char);
}

BOOL CSeriesDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(series_name_char);
	series_name_charLength = 0;

	//////////////////////////////////////////////////////
	//サイズのチェック
	//最低限descriptor_tagとdescriptor_lengthのサイズは必須
	if( dataSize < 2 ){
		return FALSE;
	}
	//->サイズのチェック

	DWORD readSize = 0;
	//////////////////////////////////////////////////////
	//解析処理
	descriptor_tag = data[0];
	descriptor_length = data[1];
	readSize += 2;

	if( descriptor_tag != 0xD5 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CSeriesDesc:: descriptor_tag err 0xD5 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CSeriesDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		series_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		repeat_label = (data[readSize+2]&0xF0)>>4;
		program_pattern = (data[readSize+2]&0x0E)>>1;
		expire_date_valid_flag = data[readSize+2]&0x01;
		expire_date = ((WORD)data[readSize+3])<<8 | data[readSize+4];
		episode_number = ((WORD)data[readSize+5])<<4 | (data[readSize+6]>>4);
		last_episode_number = ((WORD)data[readSize+6]&0x0F)<<8 | data[readSize+7];

		readSize+=8;
		if( descriptor_length > 8 ){
			series_name_charLength = descriptor_length - 8;
		}

		series_name_char = new CHAR[series_name_charLength+1];

		if( descriptor_length > 8 ){
			memcpy( series_name_char, data + readSize, series_name_charLength );
		}
		series_name_char[series_name_charLength] = '\0';
		readSize += series_name_charLength;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
