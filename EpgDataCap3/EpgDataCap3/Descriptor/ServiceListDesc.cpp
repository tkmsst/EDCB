#include "StdAfx.h"
#include "ServiceListDesc.h"

CServiceListDesc::CServiceListDesc(void)
{
}

CServiceListDesc::~CServiceListDesc(void)
{
}

BOOL CServiceListDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	serviceList.clear();

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

	if( descriptor_tag != 0x41 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CServiceListDesc:: descriptor_tag err 0x41 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CServiceListDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		for( BYTE i=0; i<descriptor_length/3; i++ ){
			SERVICE_LIST_DATA item;
			item.service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item.service_type = data[readSize+2];

			serviceList.push_back(item);
			readSize += 3;
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
