#include "StdAfx.h"
#include "ContentDesc.h"

CContentDesc::CContentDesc(void)
{
}

CContentDesc::~CContentDesc(void)
{
}

BOOL CContentDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	nibbleList.clear();

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

	if( descriptor_tag != 0x54 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CContentDesc:: descriptor_tag err 0x54 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CContentDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		for( BYTE i=0; i<descriptor_length/2; i++ ){
			NIBBLE_DATA item;
			item.content_nibble_level_1 = (data[readSize] & 0xF0) >> 4;
			item.content_nibble_level_2 = data[readSize] & 0x0F;
			item.user_nibble_1 = (data[readSize+1] & 0xF0) >> 4;
			item.user_nibble_2 = data[readSize+1] & 0x0F;

			nibbleList.push_back(item);
			readSize += 2;
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

