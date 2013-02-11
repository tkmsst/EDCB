#include "StdAfx.h"
#include "SIPrime_tsDesc.h"

#include "../../../Common/EpgTimerUtil.h"

CSIPrime_tsDesc::CSIPrime_tsDesc(void)
{
}

CSIPrime_tsDesc::~CSIPrime_tsDesc(void)
{
	Clear();
}

void CSIPrime_tsDesc::Clear()
{
	for( size_t i=0; i<tableDescDataList.size(); i++ ){
		SAFE_DELETE(tableDescDataList[i]);
	}
	tableDescDataList.clear();
}

BOOL CSIPrime_tsDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xDA ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CSIPrime_tsDesc:: descriptor_tag err 0xDA != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CSIPrime_tsDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		parameter_version = data[readSize];
		DWORD mjd = ((DWORD)data[readSize+1])<<8 | data[readSize+2];
		_MJDtoSYSTEMTIME(mjd, &update_time);
		SI_prime_ts_network_id = ((DWORD)data[readSize+3])<<8 | data[readSize+4];
		SI_prime_transport_stream_id = ((DWORD)data[readSize+5])<<8 | data[readSize+6];
		readSize += 7;

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
