#include "StdAfx.h"
#include "AudioComponentDesc.h"

CAudioComponentDesc::CAudioComponentDesc(void)
{
	text_charLength = 0;
	text_char = NULL;
}

CAudioComponentDesc::~CAudioComponentDesc(void)
{
	SAFE_DELETE_ARRAY(text_char);
}

BOOL CAudioComponentDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xC4 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CAudioComponentDesc:: descriptor_tag err 0x58 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CAudioComponentDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		stream_content = data[readSize]&0x0F;
		component_type = data[readSize+1];
		component_tag = data[readSize+2];
		stream_type = data[readSize+3];
		simulcast_group_tag = data[readSize+4];
		ES_multi_lingual_flag = (data[readSize+5]&0x80)>>7;
		main_component_flag = (data[readSize+5]&0x40)>>6;
		quality_indicator = (data[readSize+5]&0x30)>>4;
		sampling_rate = (data[readSize+5]&0x0E)>>1;
		readSize += 6;
		memcpy( ISO_639_language_code, data+readSize, 3);
		ISO_639_language_code[3] = '\0';
		readSize += 3;
		if( ES_multi_lingual_flag == 1 ){
			memcpy( ISO_639_language_code2, data+readSize, 3);
			ISO_639_language_code2[3] = '\0';
			readSize += 3;
		}
		text_charLength = descriptor_length - (BYTE)(readSize-2);
		text_char = new CHAR[text_charLength + 1];
		if( text_charLength > 0 ){
			memcpy( text_char, data+readSize, text_charLength);
			readSize += text_charLength;
		}
		text_char[text_charLength] = '\0';
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

