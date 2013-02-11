#include "StdAfx.h"
#include "TSInfoDesc.h"

CTSInfoDesc::CTSInfoDesc(void)
{
	length_of_ts_name = 0;
	ts_name_char = NULL;
}

CTSInfoDesc::~CTSInfoDesc(void)
{
	SAFE_DELETE_ARRAY(ts_name_char);
}

BOOL CTSInfoDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	transmissionList.clear();
	length_of_ts_name = 0;
	SAFE_DELETE_ARRAY(ts_name_char);

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

	if( descriptor_tag != 0xCD ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CTSInfoDesc:: descriptor_tag err 0xCD != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CTSInfoDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		remote_control_key_id = data[readSize];
		length_of_ts_name = (data[readSize+1]&0xFC)>>2;
		transmission_type_count = data[readSize+1]&0x03;
		readSize += 2;

		ts_name_char = new CHAR[length_of_ts_name+1];
		if( length_of_ts_name > 0 ){
			memcpy(ts_name_char, data + readSize, length_of_ts_name );
			readSize += length_of_ts_name;
		}
		ts_name_char[length_of_ts_name] = '\0';
		for( BYTE i=0; i<transmission_type_count; i++ ){
			TRANSMISSION_DATA item;
			item.transmission_type_info = data[readSize];
			item.num_of_service = data[readSize+1];
			readSize+=2;
			for( BYTE j=0; j<item.num_of_service; j++ ){
				WORD service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
				item.service_idList.push_back(service_id);
				readSize+=2;
			}
			transmissionList.push_back(item);
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
