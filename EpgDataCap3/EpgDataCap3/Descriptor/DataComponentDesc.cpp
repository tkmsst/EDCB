#include "StdAfx.h"
#include "DataComponentDesc.h"

CDataComponentDesc::CDataComponentDesc(void)
{
	additional_data_component_infoLength = 0;
	additional_data_component_info = NULL;
}

CDataComponentDesc::~CDataComponentDesc(void)
{
	SAFE_DELETE_ARRAY(additional_data_component_info);
}

BOOL CDataComponentDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(additional_data_component_info);
	additional_data_component_infoLength = 0;

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

	if( descriptor_tag != 0xFD ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CDataComponentDesc:: descriptor_tag err 0xFD != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CDataComponentDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		data_component_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		readSize += 2;
		if( descriptor_length > 2 ){
			additional_data_component_infoLength = descriptor_length - 2;
			additional_data_component_info = new BYTE[additional_data_component_infoLength];
			memcpy(additional_data_component_info, data + readSize, additional_data_component_infoLength );
			readSize += additional_data_component_infoLength;
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
