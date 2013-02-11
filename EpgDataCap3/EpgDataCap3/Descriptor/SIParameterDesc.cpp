#include "StdAfx.h"
#include "SIParameterDesc.h"

#include "../../../Common/EpgTimerUtil.h"

CSIParameterDesc::CSIParameterDesc(void)
{
}

CSIParameterDesc::~CSIParameterDesc(void)
{
	Clear();
}

void CSIParameterDesc::Clear()
{
	for( size_t i=0; i<tableDescDataList.size(); i++ ){
		SAFE_DELETE(tableDescDataList[i]);
	}
	tableDescDataList.clear();
}

BOOL CSIParameterDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	Clear();

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

	if( descriptor_tag != 0xD7 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CSIParameterDesc:: descriptor_tag err 0xD7 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CSIParameterDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		parameter_version = data[readSize];
		DWORD mjd = ((DWORD)data[readSize+1])<<8 | data[readSize+2];
		_MJDtoSYSTEMTIME(mjd, &update_time);
		readSize += 3;

		while( (readSize-2) < descriptor_length ){
			TABLE_DESC_DATA* item = new TABLE_DESC_DATA;
			item->table_id = data[readSize];
			item->table_description_length = data[readSize+1];
			readSize+=2;
			if( item->table_description_length > 0 ){
				item->table_description_byte = new BYTE[item->table_description_length];
				memcpy(item->table_description_byte, data + readSize, item->table_description_length );
				readSize += item->table_description_length;
			}
			tableDescDataList.push_back(item);
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
