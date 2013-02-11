#include "StdAfx.h"
#include "AVCVideoDesc.h"

CAVCVideoDesc::CAVCVideoDesc(void)
{
}

CAVCVideoDesc::~CAVCVideoDesc(void)
{
}

BOOL CAVCVideoDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0x28 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CAVCVideoDesc:: descriptor_tag err 0x28 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CAVCVideoDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		profile_idc = data[readSize];
		constraint_set0_flag = (data[readSize+1]&0x80)>>7;
		constraint_set1_flag = (data[readSize+1]&0x40)>>6;
		constraint_set2_flag = (data[readSize+1]&0x20)>>5;
		AVC_compatible_flags = data[readSize+1]&0x1F;
		level_idc = data[readSize+2];
		AVC_still_present = (data[readSize+3]&0x80)>>7;
		AVC_24_hour_picture_flag = (data[readSize+3]&0x40)>>6;
		readSize+=4;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
