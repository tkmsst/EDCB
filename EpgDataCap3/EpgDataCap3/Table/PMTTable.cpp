#include "StdAfx.h"
#include "PMTTable.h"

#include "../../../Common/EpgTimerUtil.h"
#include "../Descriptor/Descriptor.h"

CPMTTable::CPMTTable(void)
{
}

CPMTTable::~CPMTTable(void)
{
	Clear();
}

void CPMTTable::Clear()
{
	for( size_t i=0 ;i<descriptorList.size(); i++ ){
		SAFE_DELETE(descriptorList[i]);
	}
	descriptorList.clear();
	for( size_t i=0 ;i<ESInfoList.size(); i++ ){
		SAFE_DELETE(ESInfoList[i]);
	}
	ESInfoList.clear();
}

BOOL CPMTTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( section_syntax_indicator != 1 || (data[1]&0x40) != 0 ){
		//固定値がおかしい
		_OutputDebugString( L"++CPMTTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0x02 ){
		//table_idがおかしい
		_OutputDebugString( L"++CPMTTable:: table_id err 0x01 != 0x%02X", table_id );
		return FALSE;
	}
	if( readSize+section_length > dataSize && section_length > 3){
		//サイズ異常
		_OutputDebugString( L"++CPMTTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}
	//CRCチェック
	crc32 = ((DWORD)data[3+section_length-4])<<24 |
		((DWORD)data[3+section_length-3])<<16 |
		((DWORD)data[3+section_length-2])<<8 |
		data[3+section_length-1];
	if( crc32 != _Crc32(3+section_length-4, data) ){
		_OutputDebugString( L"++CPMTTable:: CRC err" );
		return FALSE;
	}

	if( section_length > 8 ){
		program_number = ((WORD)data[readSize])<<8 | data[readSize+1];
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		PCR_PID = ((WORD)data[readSize+5]&0x1F)<<8 | data[readSize+6];
		program_info_length = ((WORD)data[readSize+7]&0x0F)<<8 | data[readSize+8];
		readSize += 9;
		if( readSize+program_info_length <= (DWORD)section_length+3-4 && program_info_length > 0){
			CDescriptor descriptor;
			if( descriptor.Decode( data+readSize, program_info_length, &descriptorList, NULL ) == FALSE ){
				_OutputDebugString( L"++CPMTTable:: descriptor err" );
				return FALSE;
			}
			readSize+=program_info_length;
		}
		while( readSize < (DWORD)section_length+3-4 ){
			ES_INFO_DATA* item = new ES_INFO_DATA;
			item->stream_type = data[readSize];
			item->elementary_PID = ((WORD)data[readSize+1]&0x1F)<<8 | data[readSize+2];
			item->ES_info_length = ((WORD)data[readSize+3]&0x0F)<<8 | data[readSize+4];
			readSize += 5;
			if( readSize+item->ES_info_length <= (DWORD)section_length+3-4 && item->ES_info_length > 0){
				CDescriptor descriptor;
				if( descriptor.Decode( data+readSize, item->ES_info_length, &(item->descriptorList), NULL ) == FALSE ){
					_OutputDebugString( L"++CPMTTable:: descriptor2 err" );
					return FALSE;
				}
			}
			readSize+=item->ES_info_length;
			ESInfoList.push_back(item);
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
