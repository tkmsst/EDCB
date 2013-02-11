#include "StdAfx.h"
#include "CDTTable.h"

#include "../../../Common/EpgTimerUtil.h"
#include "../Descriptor/Descriptor.h"

CCDTTable::CCDTTable(void)
{
	data_module_byteSize = 0;
	data_module_byte = NULL;
}

CCDTTable::~CCDTTable(void)
{
}

void CCDTTable::Clear()
{
	for( size_t i=0 ;i<descriptorList.size(); i++ ){
		SAFE_DELETE(descriptorList[i]);
	}
	descriptorList.clear();

	SAFE_DELETE_ARRAY(data_module_byte);
}

BOOL CCDTTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	Clear();

	//////////////////////////////////////////////////////
	//サイズのチェック
	//最低限table_idとsection_length+CRCのサイズは必須
	if( dataSize < 7 ){
		return FALSE;
	}
	//->サイズのチェック

	DWORD readSize = 0;
	//////////////////////////////////////////////////////
	//解析処理
	table_id = data[0];
	section_syntax_indicator = (data[1]&0x80)>>7;
	section_length = ((WORD)data[1]&0x0F)<<8 | data[2];
	readSize+=3;

	if( section_syntax_indicator != 1 ){
		//固定値がおかしい
		_OutputDebugString( L"++CCDTTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0xC8 ){
		//table_idがおかしい
		_OutputDebugString( L"++CCDTTable:: table_id err 0xC8 != 0x%02X", table_id );
		return FALSE;
	}
	if( readSize+section_length > dataSize && section_length > 3){
		//サイズ異常
		_OutputDebugString( L"++CCDTTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}
	//CRCチェック
	crc32 = ((DWORD)data[3+section_length-4])<<24 |
		((DWORD)data[3+section_length-3])<<16 |
		((DWORD)data[3+section_length-2])<<8 |
		data[3+section_length-1];
	if( crc32 != _Crc32(3+section_length-4, data) ){
		_OutputDebugString( L"++CCDTTable:: CRC err" );
		return FALSE;
	}

	if( section_length > 10 ){
		download_data_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		original_network_id = ((WORD)data[readSize+5])<<8 | data[readSize+6];
		data_type = data[readSize+7];
		descriptors_loop_length = ((WORD)data[readSize+8]&0x0F)<<8 | data[readSize+9];
		readSize += 10;

		if( descriptors_loop_length > 0 ){
			CDescriptor descriptor;
			if( descriptor.Decode( data+readSize, descriptors_loop_length, &descriptorList, NULL ) == FALSE ){
				_OutputDebugString( L"++CCDTTable:: descriptor err" );
				return FALSE;
			}
			readSize+=descriptors_loop_length;
		}

		data_module_byteSize = (3+section_length-4) - (WORD)readSize;
		if( data_module_byteSize > 0 ){
			data_module_byte = new BYTE[data_module_byteSize];
			memcpy(data_module_byte, data+readSize, data_module_byteSize);
		}
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 3+section_length;
	}

	return TRUE;
}