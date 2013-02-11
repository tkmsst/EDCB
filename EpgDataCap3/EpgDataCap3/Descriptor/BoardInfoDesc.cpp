#include "StdAfx.h"
#include "BoardInfoDesc.h"

CBoardInfoDesc::CBoardInfoDesc(void)
{
	title_length = 0;
	title_char = NULL;
	text_length = 0;
	text_char = NULL;
}

CBoardInfoDesc::~CBoardInfoDesc(void)
{
	SAFE_DELETE_ARRAY(title_char);
	SAFE_DELETE_ARRAY(text_char);
}

BOOL CBoardInfoDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(title_char);
	title_length = 0;
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

	if( descriptor_tag != 0xDB ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CBoardInfoDesc:: descriptor_tag err 0xDB != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CBoardInfoDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		title_length = data[readSize];
		readSize++;
		title_char = new CHAR[title_length+1];
		if( title_length > 0 ){
			memcpy(title_char, data + readSize, title_length);
			readSize += title_length;
		}
		title_char[title_length] = '\0';

		text_length = data[readSize];
		readSize++;
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
