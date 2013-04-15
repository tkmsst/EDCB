#include "StdAfx.h"
#include "SystemManagementDesc.h"

CSystemManagementDesc::CSystemManagementDesc(void)
{
	additional_identification_infoLength = 0;
	additional_identification_info = NULL;
}

CSystemManagementDesc::~CSystemManagementDesc(void)
{
	SAFE_DELETE_ARRAY(additional_identification_info);
}

BOOL CSystemManagementDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(additional_identification_info);
	additional_identification_infoLength = 0;

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

	if( descriptor_tag != 0xFE ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CSystemManagementDesc:: descriptor_tag err 0xFE != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CSystemManagementDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		system_management_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		readSize += 2;
		if( descriptor_length > 2 ){
			additional_identification_infoLength = descriptor_length - 2;
			additional_identification_info = new BYTE[additional_identification_infoLength];
			memcpy(additional_identification_info, data + readSize, additional_identification_infoLength );
			readSize += additional_identification_infoLength;
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
