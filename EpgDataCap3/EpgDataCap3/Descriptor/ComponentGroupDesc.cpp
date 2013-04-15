#include "StdAfx.h"
#include "ComponentGroupDesc.h"

CComponentGroupDesc::CComponentGroupDesc(void)
{
}

CComponentGroupDesc::~CComponentGroupDesc(void)
{
	Clear();
}

void CComponentGroupDesc::Clear()
{
	for( size_t i=0; i<componentList.size(); i++ ){
		SAFE_DELETE(componentList[i]);
	}
	componentList.clear();
}

BOOL CComponentGroupDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xD9 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CComponentGroupDesc:: descriptor_tag err 0xD9 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CComponentGroupDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		component_group_type = (data[readSize]&0xE0)>>5;
		total_bit_rate_flag = (data[readSize]&0x10)>>4;
		num_of_group = data[readSize]&0x0F;
		readSize++;
		for( BYTE i=0; i<num_of_group; i++ ){
			COMPONENT_DATA* item = new COMPONENT_DATA;
			item->component_group_id = (data[readSize]&0xF0)>>4;
			item->num_of_CA_unit = data[readSize]&0x0F;
			readSize++;
			for( BYTE j=0; j<item->num_of_CA_unit; j++ ){
				CA_UNIT_DATA item2;
				item2.CA_unit_id = (data[readSize]&0xF0)>>4;
				item2.num_of_component = data[readSize]&0x0F;
				readSize++;
				for( BYTE k=0; k<item2.num_of_component; k++ ){
					item2.component_tagList.push_back(data[readSize]);
					readSize++;
				}
				item->CAUnitList.push_back(item2);
			}
			if(total_bit_rate_flag == 1){
				item->total_bit_rate = data[readSize];
				readSize++;
			}
			item->text_length = data[readSize];
			readSize++;
			item->text_char = new CHAR[item->text_length+1];
			if(item->text_length > 0 ){
				memcpy(item->text_char, data + readSize, item->text_length);
				readSize += item->text_length;
			}
			item->text_char[item->text_length] = '\0';

			componentList.push_back(item);
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

