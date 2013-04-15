#include "StdAfx.h"
#include "PartialTSTimeDesc.h"

#include "../../../Common/EpgTimerUtil.h"

CPartialTSTimeDesc::CPartialTSTimeDesc(void)
{
}

CPartialTSTimeDesc::~CPartialTSTimeDesc(void)
{
}

BOOL CPartialTSTimeDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}

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

	if( descriptor_tag != 0xC3 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CPartialTSTimeDesc:: descriptor_tag err 0xC3 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CPartialTSTimeDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		event_version_number = data[readSize];
		readSize++;

		DWORD mjd = ((WORD)data[readSize])<<8 | data[readSize+1];
		_MJDtoSYSTEMTIME(mjd, &event_start_time);
		event_start_time.wHour = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
		event_start_time.wMinute = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
		event_start_time.wSecond = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
		readSize+=5;
		duration_HH = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
		duration_MM = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
		duration_SS = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
		readSize+=3;
		offset_HH = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
		offset_MM = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
		offset_SS = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
		readSize+=3;
		offset_flag = (data[readSize]&0x04)>>2;
		other_descriptor_status = (data[readSize]&0x02)>>1;
		jst_time_flag = data[readSize]&0x01;
		readSize++;

		if( jst_time_flag == 1 ){
			mjd = ((WORD)data[readSize])<<8 | data[readSize+1];
			_MJDtoSYSTEMTIME(mjd, &jst_time);
			jst_time.wHour = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
			jst_time.wMinute = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
			jst_time.wSecond = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
			readSize+=5;
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
