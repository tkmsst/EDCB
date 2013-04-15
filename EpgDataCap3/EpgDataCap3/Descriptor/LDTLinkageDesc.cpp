#include "StdAfx.h"
#include "LDTLinkageDesc.h"

CLDTLinkageDesc::CLDTLinkageDesc(void)
{
}

CLDTLinkageDesc::~CLDTLinkageDesc(void)
{
}

BOOL CLDTLinkageDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	LDTList.clear();

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

	if( descriptor_tag != 0xDC ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CLDTLinkageDesc:: descriptor_tag err 0xDC != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CLDTLinkageDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		original_service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		transport_stream_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
		original_network_id = ((WORD)data[readSize+4])<<8 | data[readSize+5];
		readSize += 6;
		while( (readSize-2) < descriptor_length ){
			LDT_DATA item;
			item.description_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item.description_type = data[readSize+2]&0x0F;
			item.user_defined = data[readSize+3];

			LDTList.push_back(item);
			readSize+=4;
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

