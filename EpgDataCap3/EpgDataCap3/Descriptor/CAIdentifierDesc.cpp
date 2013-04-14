#include "StdAfx.h"
#include "CAIdentifierDesc.h"

CCAIdentifierDesc::CCAIdentifierDesc(void)
{
}

CCAIdentifierDesc::~CCAIdentifierDesc(void)
{
}

BOOL CCAIdentifierDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	CA_system_id_List.clear();

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

	if( descriptor_tag != 0x53 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CCAIdentifierDesc:: descriptor_tag err 0x53 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CCAIdentifierDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		for( BYTE i=0; i<descriptor_length/2; i++ ){
			WORD id = ((WORD)data[readSize])<<8 | (WORD)data[readSize+1];

			CA_system_id_List.push_back(id);
			readSize += 2;
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
