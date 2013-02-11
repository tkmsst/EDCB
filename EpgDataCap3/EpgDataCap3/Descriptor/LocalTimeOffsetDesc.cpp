#include "StdAfx.h"
#include "LocalTimeOffsetDesc.h"

#include "../../../Common/EpgTimerUtil.h"

CLocalTimeOffsetDesc::CLocalTimeOffsetDesc(void)
{
}

CLocalTimeOffsetDesc::~CLocalTimeOffsetDesc(void)
{
}

BOOL CLocalTimeOffsetDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	timeOffsetList.clear();

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

	if( descriptor_tag != 0x58 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CLocalTimeOffsetDesc:: descriptor_tag err 0x58 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CLocalTimeOffsetDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		for( BYTE i=0; i<descriptor_length/13; i++ ){
			LOCAL_TIME_OFFSET_DATA item;
			memcpy(item.country_code, data + readSize, 3);
			item.country_code[3] = '\0';
			readSize+=3;

			item.country_region_id = data[readSize]>>2;
			item.local_time_offset_polarity = data[readSize]&0x01;
			readSize++;
			item.local_time_offset = (WORD)(_BCDtoDWORD(data+readSize, 1, 2)*60) + (WORD)_BCDtoDWORD(data+readSize+1, 1, 2);
			readSize+=2;
			ZeroMemory(&item.time_of_change, sizeof(SYSTEMTIME));
			DWORD mjd = ((WORD)data[readSize])<<8 | data[readSize+1];
			_MJDtoSYSTEMTIME(mjd, &item.time_of_change);
			item.time_of_change.wHour = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
			item.time_of_change.wMinute = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
			item.time_of_change.wSecond = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
			readSize+=5;
			item.next_time_offset = (WORD)(_BCDtoDWORD(data+readSize, 1, 2)*60) + (WORD)_BCDtoDWORD(data+readSize+1, 1, 2);
			readSize+=2;

			timeOffsetList.push_back(item);
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
