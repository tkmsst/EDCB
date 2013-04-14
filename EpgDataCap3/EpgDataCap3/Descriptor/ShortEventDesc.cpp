#include "StdAfx.h"
#include "ShortEventDesc.h"

CShortEventDesc::CShortEventDesc(void)
{
	event_name_length = 0;
	event_name_char = NULL;
	text_length = 0;
	text_char = NULL;
}

CShortEventDesc::~CShortEventDesc(void)
{
	SAFE_DELETE_ARRAY(event_name_char);
	SAFE_DELETE_ARRAY(text_char);
}

BOOL CShortEventDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(event_name_char);
	event_name_length = 0;
	SAFE_DELETE_ARRAY(text_char);
	text_length = 0;

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

	if( descriptor_tag != 0x4D ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CShortEventDesc:: descriptor_tag err 0x4D != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CShortEventDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		memcpy(ISO_639_language_code, data + readSize, 3 );
		ISO_639_language_code[3] = '\0';
		readSize += 3;

		event_name_length = data[readSize];
		readSize++;
		event_name_char = new CHAR[event_name_length+1];
		if( event_name_length > 0 ){
			memcpy( event_name_char, data + readSize, event_name_length);
			readSize+=event_name_length;
		}
		event_name_char[event_name_length] = '\0';

		text_length = data[readSize];
		readSize++;
		text_char = new CHAR[text_length+1];
		if( text_length > 0 ){
			memcpy( text_char, data + readSize, text_length);
			readSize+=text_length;
		}
		text_char[text_length] = '\0';
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

