#include "StdAfx.h"
#include "MosaicDesc.h"

CMosaicDesc::CMosaicDesc(void)
{
}

CMosaicDesc::~CMosaicDesc(void)
{
	Clear();
}

void CMosaicDesc::Clear()
{
	for( size_t i=0; i<cellList.size(); i++ ){
		SAFE_DELETE(cellList[i]);
	}
	cellList.clear();
}

BOOL CMosaicDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0x51 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CMosaicDesc:: descriptor_tag err 0x51 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CMosaicDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		mosaic_entry_point = (data[readSize]&0x80)>>7;
		number_of_horizontal_elementary_cells = (data[readSize]&0x70)>>4;
		number_of_vertical_elementary_cells = data[readSize]&0x07;
		readSize++;
		if( descriptor_length > 1 ){
			BYTE readItemSize = 0;
			while(readItemSize < descriptor_length - 1 ){
				CELL_DATA* item = new CELL_DATA;
				item->logical_cell_id = (data[readSize]&0xFC)>>2;
				item->logical_cell_presentation_info = data[readSize+1]&0x07;
				item->elementary_cell_field_length = data[readSize+2];
				readSize += 3;
				readItemSize += 3;
				for( BYTE i=0; i<item->elementary_cell_field_length; i++ ){
					item->elementary_cell_idList.push_back(data[readSize]&0x3F);
					readSize++;
					readItemSize++;
				}
				item->cell_linkage_info = data[readSize];
				if( item->cell_linkage_info == 0x01 ){
					item->bouquet_id = ((WORD)data[readSize])<<8 | data[readSize+1];
					readSize += 2;
					readItemSize += 2;
				}else if( item->cell_linkage_info == 0x02 || 
					item->cell_linkage_info == 0x03 ||
					item->cell_linkage_info == 0x04 ){
					item->original_network_id = ((WORD)data[readSize])<<8 | data[readSize+1];
					item->transport_stream_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
					item->service_id = ((WORD)data[readSize+4])<<8 | data[readSize+5];
					readSize += 6;
					readItemSize += 6;
					if( item->cell_linkage_info == 0x04 ){
						item->event_id = ((WORD)data[readSize])<<8 | data[readSize+1];
						readSize += 2;
						readItemSize += 2;
					}
				}
				cellList.push_back(item);
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
