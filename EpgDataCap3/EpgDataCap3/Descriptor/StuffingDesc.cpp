#include "StdAfx.h"
#include "StuffingDesc.h"

CStuffingDesc::CStuffingDesc(void)
{
	stuffing_byteLength = 0;
	stuffing_byte = NULL;
}

CStuffingDesc::~CStuffingDesc(void)
{
	SAFE_DELETE_ARRAY(stuffing_byte);
}

BOOL CStuffingDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(stuffing_byte);
	stuffing_byteLength = 0;

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

	if( descriptor_tag != 0x42 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CStuffingDesc:: descriptor_tag err 0x42 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CStuffingDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		stuffing_byteLength = descriptor_length;
		stuffing_byte = new BYTE[stuffing_byteLength];
		memcpy( stuffing_byte, data + readSize, stuffing_byteLength );
		readSize+=stuffing_byteLength;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

