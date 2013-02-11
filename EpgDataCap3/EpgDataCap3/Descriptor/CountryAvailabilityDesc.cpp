#include "StdAfx.h"
#include "CountryAvailabilityDesc.h"

CCountryAvailabilityDesc::CCountryAvailabilityDesc(void)
{
}

CCountryAvailabilityDesc::~CCountryAvailabilityDesc(void)
{
}

BOOL CCountryAvailabilityDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	countryList.clear();

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

	if( descriptor_tag != 0x49 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CCountryAvailabilityDesc:: descriptor_tag err 0x49 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CCountryAvailabilityDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		country_availability_flag = (data[readSize] & 0x80) >> 7;
		readSize++;

		if( descriptor_length > 1 ){
			for( BYTE i=0; i<(descriptor_length-1)/3; i++ ){
				COUNTRY_DATA item;
				memcpy(item.country_code, data+readSize, 3);
				item.country_code[3] = '\0';

				countryList.push_back(item);
				readSize+=3;
			}
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
