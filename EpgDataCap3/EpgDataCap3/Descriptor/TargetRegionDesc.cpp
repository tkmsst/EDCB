#include "StdAfx.h"
#include "TargetRegionDesc.h"

CTargetRegionDesc::CTargetRegionDesc(void)
{
}

CTargetRegionDesc::~CTargetRegionDesc(void)
{
}

BOOL CTargetRegionDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xC6 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CTargetRegionDesc:: descriptor_tag err 0xC6 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CTargetRegionDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		region_spec_type = data[readSize];
		readSize++;
		if( region_spec_type == 0x01 ){
			memcpy( prefecture_bitmap, data + readSize, 7 );
			readSize += 7;
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
