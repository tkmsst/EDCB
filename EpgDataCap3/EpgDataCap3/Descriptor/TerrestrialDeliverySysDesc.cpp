#include "StdAfx.h"
#include "TerrestrialDeliverySysDesc.h"

CTerrestrialDeliverySysDesc::CTerrestrialDeliverySysDesc(void)
{
}

CTerrestrialDeliverySysDesc::~CTerrestrialDeliverySysDesc(void)
{
}

BOOL CTerrestrialDeliverySysDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	frequencyList.clear();

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

	if( descriptor_tag != 0xFA ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CTerrestrialDeliverySysDesc:: descriptor_tag err 0xFA != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CTerrestrialDeliverySysDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		area_code = ((WORD)data[readSize])<<4 | (data[readSize+1]>>4);
		guard_interval = (data[readSize+1]&0x0C)>>2;
		transmission_mode = data[readSize+1]&0x03;
		readSize+=2;
		for( BYTE i=0; i<(descriptor_length-2)/2; i++ ){
			WORD frequency = ((WORD)data[readSize])<<8 | data[readSize+1];
			frequencyList.push_back(frequency);
			readSize+=2;
		}
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
