#include "StdAfx.h"
#include "AVCTimingHRDDesc.h"

CAVCTimingHRDDesc::CAVCTimingHRDDesc(void)
{
}

CAVCTimingHRDDesc::~CAVCTimingHRDDesc(void)
{
}

BOOL CAVCTimingHRDDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0x2A ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CAVCTimingHRDDesc:: descriptor_tag err 0x2A != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CAVCTimingHRDDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		hrd_management_valid_flag = (data[readSize]&0x80)>>7;
		picture_and_timing_info_present = data[readSize]&0x01;
		readSize++;
		if( picture_and_timing_info_present == 1 ){
			_90kHz_flag = (data[readSize]&0x80)>>7;
			if( _90kHz_flag == 0 ){
				N = ((DWORD)data[readSize])<<24 |
					((DWORD)data[readSize+1])<<16 |
					((DWORD)data[readSize+2])<<8 |
					data[readSize+3];
				readSize+=4;
				K = ((DWORD)data[readSize])<<24 |
					((DWORD)data[readSize+1])<<16 |
					((DWORD)data[readSize+2])<<8 |
					data[readSize+3];
				readSize+=4;
			}
			num_units_in_tick = ((DWORD)data[readSize])<<24 |
				((DWORD)data[readSize+1])<<16 |
				((DWORD)data[readSize+2])<<8 |
				data[readSize+3];
			readSize+=4;
		}

		fixed_frame_rate_flag = (data[readSize]&0x80)>>7;
		temporal_poc_flag = (data[readSize]&0x40)>>6;
		picture_to_display_conversion_flag = (data[readSize]&0x20)>>5;
		readSize++;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
