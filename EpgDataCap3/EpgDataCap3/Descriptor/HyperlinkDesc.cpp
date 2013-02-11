#include "StdAfx.h"
#include "HyperlinkDesc.h"

CHyperlinkDesc::CHyperlinkDesc(void)
{
	private_dataLength = 0;
	private_data = NULL;
}

CHyperlinkDesc::~CHyperlinkDesc(void)
{
	Clear();
	SAFE_DELETE_ARRAY(private_data);
}

void CHyperlinkDesc::Clear()
{
	for( size_t i=0; i<selectorList.size(); i++ ){
		SAFE_DELETE(selectorList[i]);
	}
	selectorList.clear();
}

BOOL CHyperlinkDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	Clear();
	SAFE_DELETE_ARRAY(private_data);
	private_dataLength = 0;

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

	if( descriptor_tag != 0xC5 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CHyperlinkDesc:: descriptor_tag err 0xC5 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CHyperlinkDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		hyper_linkage_type = data[readSize];
		link_destination_type = data[readSize+1];
		selector_length = data[readSize+2];
		readSize += 3;
		if( selector_length > 0 ){
			BYTE itemReadSize = 0;
			while( itemReadSize < selector_length ){
				SELECTOR_DATA* item = new SELECTOR_DATA;
				if( link_destination_type == 0x01 ){
					item->original_network_id = ((WORD)data[readSize])<< 8 | data[readSize+1];
					item->transport_stream_id = ((WORD)data[readSize+2])<< 8 | data[readSize+3];
					item->service_id = ((WORD)data[readSize+4])<< 8 | data[readSize+5];

					readSize += 6;
					itemReadSize += 6;
				}else if( link_destination_type == 0x02 ){
					item->original_network_id = ((WORD)data[readSize])<< 8 | data[readSize+1];
					item->transport_stream_id = ((WORD)data[readSize+2])<< 8 | data[readSize+3];
					item->service_id = ((WORD)data[readSize+4])<< 8 | data[readSize+5];
					item->event_id = ((WORD)data[readSize+6])<< 8 | data[readSize+7];

					readSize += 8;
					itemReadSize += 8;
				}else if( link_destination_type == 0x03 ){
					item->original_network_id = ((WORD)data[readSize])<< 8 | data[readSize+1];
					item->transport_stream_id = ((WORD)data[readSize+2])<< 8 | data[readSize+3];
					item->service_id = ((WORD)data[readSize+4])<< 8 | data[readSize+5];
					item->event_id = ((WORD)data[readSize+6])<< 8 | data[readSize+7];
					item->component_tag = data[readSize+8];
					item->moduleId = ((WORD)data[readSize+9])<< 8 | data[readSize+10];

					readSize += 11;
					itemReadSize += 11;
				}else if( link_destination_type == 0x04 ){
					item->original_network_id = ((WORD)data[readSize])<< 8 | data[readSize+1];
					item->transport_stream_id = ((WORD)data[readSize+2])<< 8 | data[readSize+3];
					item->service_id = ((WORD)data[readSize+4])<< 8 | data[readSize+5];
					item->content_id = ((DWORD)data[readSize+6])<< 24 |
						((DWORD)data[readSize+7])<< 16 |
						((DWORD)data[readSize+8])<< 8 |
						data[readSize+9];

					readSize += 10;
					itemReadSize += 10;
				}else if( link_destination_type == 0x05 ){
					item->original_network_id = ((WORD)data[readSize])<< 8 | data[readSize+1];
					item->transport_stream_id = ((WORD)data[readSize+2])<< 8 | data[readSize+3];
					item->service_id = ((WORD)data[readSize+4])<< 8 | data[readSize+5];
					item->content_id = ((DWORD)data[readSize+6])<< 24 |
						((DWORD)data[readSize+7])<< 16 |
						((DWORD)data[readSize+8])<< 8 |
						data[readSize+9];
					item->component_tag = data[readSize+10];
					item->moduleId = ((WORD)data[readSize+11])<< 8 | data[readSize+12];

					readSize += 13;
					itemReadSize += 13;
				}else if( link_destination_type == 0x06 ){
					item->information_provider_id = ((WORD)data[readSize])<< 8 | data[readSize+1];
					item->event_relation_id = ((WORD)data[readSize+2])<< 8 | data[readSize+3];
					item->node_id = ((WORD)data[readSize+4])<< 8 | data[readSize+5];

					readSize += 6;
					itemReadSize += 6;
				}else if( link_destination_type == 0x07 ){
					BYTE uriSize = selector_length - itemReadSize;
					memcpy(item->uri_char, data+readSize, uriSize );
					item->uri_char[uriSize] = '\0';

					readSize += uriSize;
					itemReadSize += uriSize;
				}else{
					readSize += selector_length - itemReadSize;
					itemReadSize = selector_length;
					SAFE_DELETE(item);
				}
				if( item != NULL ){
					selectorList.push_back(item);
				}
			}
		}

		if( descriptor_length > readSize-2 ){
			private_dataLength = descriptor_length - (BYTE)(readSize-2);
			private_data = new BYTE[private_dataLength];
			memcpy( private_data, data + readSize, private_dataLength );
			readSize += private_dataLength;
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
