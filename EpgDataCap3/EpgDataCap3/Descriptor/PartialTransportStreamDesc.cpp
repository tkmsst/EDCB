#include "StdAfx.h"
#include "PartialTransportStreamDesc.h"

CPartialTransportStreamDesc::CPartialTransportStreamDesc(void)
{
}

CPartialTransportStreamDesc::~CPartialTransportStreamDesc(void)
{
}

BOOL CPartialTransportStreamDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}

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

	if( descriptor_tag != 0x63 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CPartialTransportStreamDesc:: descriptor_tag err 0x63 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CPartialTransportStreamDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		peak_rate = ((DWORD)(data[readSize]&0x3F))<<16 | ((DWORD)data[readSize+1])<<8 | data[readSize+2];
		minimum_overall_smoothing_rate = ((DWORD)(data[readSize+3]&0x3F))<<16 | ((DWORD)data[readSize+4])<<8 | data[readSize+5];
		maximum_overall_smoothing_buffer = ((WORD)(data[readSize+6]&0x3F))<<8 | data[readSize+7];
		readSize+=8;

	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
