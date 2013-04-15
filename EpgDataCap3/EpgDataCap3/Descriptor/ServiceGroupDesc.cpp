#include "StdAfx.h"
#include "ServiceGroupDesc.h"

CServiceGroupDesc::CServiceGroupDesc(void)
{
}

CServiceGroupDesc::~CServiceGroupDesc(void)
{
}

BOOL CServiceGroupDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xE0 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CServiceGroupDesc:: descriptor_tag err 0xE0 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CServiceGroupDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		service_group_type = (data[readSize]&0xF0)>>4;
		readSize++;
		if( service_group_type == 1 ){
			for( BYTE i=0; i<(descriptor_length-1)/4; i++ ){
				SERVICE_GROUP_DATA item;
				item.primary_service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
				item.secondary_service_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];

				serviceGroupList.push_back(item);
				readSize+=4;
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
