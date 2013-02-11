#include "StdAfx.h"
#include "EventGroupDesc.h"

CEventGroupDesc::CEventGroupDesc(void)
{
	private_data_byteLength = 0;
	private_data_byte = NULL;
}

CEventGroupDesc::~CEventGroupDesc(void)
{
	SAFE_DELETE_ARRAY(private_data_byte);
}

BOOL CEventGroupDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(private_data_byte);
	private_data_byteLength = 0;

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

	if( descriptor_tag != 0xD6 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CEventGroupDesc:: descriptor_tag err 0xD6 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CEventGroupDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		group_type = (data[readSize]&0xF0)>>4;
		event_count = data[readSize]&0x0F;
		readSize++;
		for( BYTE i=0; i<event_count; i++ ){
			EVENT_DATA item;
			item.service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item.event_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
			eventDataList.push_back(item);
			readSize+=4;
		}
		if( group_type == 4 || group_type == 5 ){
			while(readSize-2 < descriptor_length ){
				EVENT_DATA2 item;
				item.original_network_id = ((WORD)data[readSize])<<8 | data[readSize+1];
				item.transport_stream_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
				item.service_id = ((WORD)data[readSize+4])<<8 | data[readSize+5];
				item.event_id = ((WORD)data[readSize+6])<<8 | data[readSize+7];
				eventData2List.push_back(item);
				readSize+=8;
			}
		}else{
			if( readSize-2 < descriptor_length ){
				private_data_byteLength = descriptor_length - (BYTE)(readSize-2);
				private_data_byte = new BYTE[private_data_byteLength];
				memcpy(private_data_byte, data+readSize, private_data_byteLength);
				readSize += private_data_byteLength;
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
