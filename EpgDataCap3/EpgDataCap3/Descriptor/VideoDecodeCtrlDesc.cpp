#include "StdAfx.h"
#include "VideoDecodeCtrlDesc.h"

CVideoDecodeCtrlDesc::CVideoDecodeCtrlDesc(void)
{
}

CVideoDecodeCtrlDesc::~CVideoDecodeCtrlDesc(void)
{
}

BOOL CVideoDecodeCtrlDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xC8 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CVideoDecodeCtrlDesc:: descriptor_tag err 0xC8 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CVideoDecodeCtrlDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		still_picture_flag = (data[readSize]&0x80)>>7;
		sequence_end_code_flag = (data[readSize]&0x40)>>6;
		video_encode_format = (data[readSize]&0x3C) >> 2;
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
