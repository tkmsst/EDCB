#include "StdAfx.h"
#include "ParentalRatingDesc.h"

CParentalRatingDesc::CParentalRatingDesc(void)
{
}

CParentalRatingDesc::~CParentalRatingDesc(void)
{
}

BOOL CParentalRatingDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	ratingList.clear();

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

	if( descriptor_tag != 0x55 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CParentalRatingDesc:: descriptor_tag err 0x55 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CParentalRatingDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		for( BYTE i=0; i<descriptor_length/4; i++ ){
			RATING_DATA item;
			memcpy( item.country_code, data + readSize, 3 );
			item.country_code[3] = '\0';
			item.rating = data[readSize+3];

			ratingList.push_back(item);
			readSize+=4;
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
