#include "StdAfx.h"
#include "StreamIdentifierDesc.h"

CStreamIdentifierDesc::CStreamIdentifierDesc(void)
{
}

CStreamIdentifierDesc::~CStreamIdentifierDesc(void)
{
}

BOOL CStreamIdentifierDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0x52 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CStreamIdentifierDesc:: descriptor_tag err 0x52 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CStreamIdentifierDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		component_tag = data[readSize];
		readSize++;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

