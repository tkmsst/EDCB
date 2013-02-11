#include "StdAfx.h"
#include "CADesc.h"


CCADesc::CCADesc(void)
{
	private_data_byte = NULL;
}


CCADesc::~CCADesc(void)
{
	SAFE_DELETE_ARRAY(private_data_byte);
}

BOOL CCADesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(private_data_byte);
	private_data_byteLength = 0;

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

	if( descriptor_tag != 0x09 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CCADesc:: descriptor_tag err 0x09 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CCADesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		CA_system_ID = ((WORD)data[readSize])<<8 | (WORD)data[readSize+1];
		readSize += 2;
		CA_PID = ((WORD)data[readSize]&0x1F)<<8 | (WORD)data[readSize+1];
		readSize += 2;

		if( descriptor_length > 4 ){
			private_data_byteLength = descriptor_length - 4;
			private_data_byte = new BYTE[private_data_byteLength];
			memcpy(private_data_byte, data+readSize, private_data_byteLength);

			readSize+=private_data_byteLength;
		}

	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
