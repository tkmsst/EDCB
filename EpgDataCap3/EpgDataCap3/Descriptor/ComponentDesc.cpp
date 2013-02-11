#include "StdAfx.h"
#include "ComponentDesc.h"

CComponentDesc::CComponentDesc(void)
{
	text_charLength = 0;
	text_char = NULL;
}

CComponentDesc::~CComponentDesc(void)
{
	SAFE_DELETE_ARRAY(text_char);
}

BOOL CComponentDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(text_char);
	text_charLength = 0;

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

	if( descriptor_tag != 0x50 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CComponentDesc:: descriptor_tag err 0x50 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CComponentDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		stream_content = data[readSize] & 0x0F;
		component_type = data[readSize+1];
		component_tag = data[readSize+2];
		memcpy(ISO_639_language_code, data+3, 3);
		ISO_639_language_code[3] = '\0';
		readSize += 6;

		if( descriptor_length > 6 ){
			text_charLength = descriptor_length - 6;
			text_char = new BYTE[text_charLength];
			memcpy(text_char, data+readSize, text_charLength );
			readSize += text_charLength;
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
