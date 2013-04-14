#include "StdAfx.h"
#include "LinkageDesc.h"

CLinkageDesc::CLinkageDesc(void)
{
	private_data_byteLength = 0;
	private_data_byte = NULL;
}

CLinkageDesc::~CLinkageDesc(void)
{
	SAFE_DELETE_ARRAY(private_data_byte);
}

BOOL CLinkageDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0x4A ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CLinkageDesc:: descriptor_tag err 0x4A != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CLinkageDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		transport_stream_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		original_network_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
		service_id = ((WORD)data[readSize+4])<<8 | data[readSize+5];
		linkage_type = data[readSize+6];
		readSize += 7;
		if( 7 < descriptor_length ){
			private_data_byteLength = descriptor_length - 7;
			private_data_byte = new BYTE[private_data_byteLength];
			memcpy( private_data_byte, data + readSize, private_data_byteLength );
			readSize += private_data_byteLength;
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

