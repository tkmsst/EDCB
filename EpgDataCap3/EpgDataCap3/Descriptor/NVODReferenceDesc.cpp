#include "StdAfx.h"
#include "NVODReferenceDesc.h"

CNVODReferenceDesc::CNVODReferenceDesc(void)
{
}

CNVODReferenceDesc::~CNVODReferenceDesc(void)
{
}

BOOL CNVODReferenceDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0x4B ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CNVODReferenceDesc:: descriptor_tag err 0x4B != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CNVODReferenceDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		for( BYTE i=0; i<descriptor_length/6; i++ ){
			SERVICE_DATA item;
			item.original_network_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item.transport_stream_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
			item.service_id = ((WORD)data[readSize+4])<<8 | data[readSize+5];

			serviceList.push_back(item);
			readSize += 6;
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
