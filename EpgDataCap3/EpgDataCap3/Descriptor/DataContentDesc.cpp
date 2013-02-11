#include "StdAfx.h"
#include "DataContentDesc.h"

CDataContentDesc::CDataContentDesc(void)
{
	selector_length = 0;
	selector_byte = NULL;
	num_of_component_ref = 0;
	component_ref = NULL;
	text_length = 0;
	text_char = NULL;
}

CDataContentDesc::~CDataContentDesc(void)
{
	SAFE_DELETE_ARRAY(selector_byte);
	SAFE_DELETE_ARRAY(component_ref);
	SAFE_DELETE_ARRAY(text_char);
}

BOOL CDataContentDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(selector_byte);
	selector_length = 0;
	SAFE_DELETE_ARRAY(component_ref);
	num_of_component_ref = 0;
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

	if( descriptor_tag != 0xC7 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CDataContentDesc:: descriptor_tag err 0xC7 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CDataContentDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		data_component_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		entry_component = data[readSize+2];
		selector_length = data[readSize+3];
		readSize += 4;
		if( selector_length > 0 ){
			selector_byte = new BYTE[selector_length];
			memcpy(selector_byte, data + readSize, selector_length);
			readSize += selector_length;
		}
		num_of_component_ref = data[readSize];
		readSize++;
		if( num_of_component_ref > 0 ){
			component_ref = new BYTE[num_of_component_ref];
			memcpy(component_ref, data + readSize, num_of_component_ref);
			readSize += num_of_component_ref;
		}
		memcpy( ISO_639_language_code, data + readSize, 3 );
		ISO_639_language_code[3] = '\0';
		readSize += 3;
		text_length = data[readSize];
		text_char = new CHAR[text_length+1];
		if( text_length > 0 ){
			memcpy(text_char, data + readSize, text_length);
			readSize += text_length;
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

