#include "StdAfx.h"
#include "NetworkNameDesc.h"

CNetworkNameDesc::CNetworkNameDesc(void)
{
	char_nameLength = 0;
	char_name = NULL;
}

CNetworkNameDesc::~CNetworkNameDesc(void)
{
	SAFE_DELETE_ARRAY(char_name);
}

BOOL CNetworkNameDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(char_name);
	char_nameLength = 0;

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

	if( descriptor_tag != 0x40 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CNetworkNameDesc:: descriptor_tag err 0x40 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CNetworkNameDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		char_nameLength = descriptor_length;
		char_name = new CHAR[char_nameLength + 1];
		memcpy( char_name, data + readSize, char_nameLength );
		char_name[char_nameLength] = '\0';

		readSize += descriptor_length;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
