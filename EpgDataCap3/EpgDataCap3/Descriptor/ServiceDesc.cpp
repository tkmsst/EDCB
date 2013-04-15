#include "StdAfx.h"
#include "ServiceDesc.h"

CServiceDesc::CServiceDesc(void)
{
	service_provider_name_length = 0;
	char_service_provider_name = NULL;
	service_name_length = 0;
	char_service_name = NULL;
}

CServiceDesc::~CServiceDesc(void)
{
	SAFE_DELETE_ARRAY(char_service_provider_name);
	SAFE_DELETE_ARRAY(char_service_name);
}

BOOL CServiceDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(char_service_provider_name);
	service_provider_name_length = 0;
	SAFE_DELETE_ARRAY(char_service_name);
	service_name_length = 0;

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

	if( descriptor_tag != 0x48 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CServiceDesc:: descriptor_tag err 0x48 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CServiceDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		service_type = data[readSize];
		readSize++;
		service_provider_name_length = data[readSize];
		readSize++;
		char_service_provider_name = new CHAR[service_provider_name_length+1];
		if( service_provider_name_length > 0 ){
			memcpy( char_service_provider_name, data + readSize, service_provider_name_length);
			readSize+=service_provider_name_length;
		}
		char_service_provider_name[service_provider_name_length] = '\0';

		service_name_length = data[readSize];
		readSize++;
		char_service_name = new CHAR[service_name_length+1];
		if( service_name_length > 0 ){
			memcpy( char_service_name, data + readSize, service_name_length);
			readSize+=service_name_length;
		}
		char_service_name[service_name_length] = '\0';
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

