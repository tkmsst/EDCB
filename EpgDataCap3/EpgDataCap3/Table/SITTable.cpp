#include "StdAfx.h"
#include "SITTable.h"

#include "../../../Common/EpgTimerUtil.h"
#include "../Descriptor/Descriptor.h"

CSITTable::CSITTable(void)
{
}


CSITTable::~CSITTable(void)
{
	Clear();
}

void CSITTable::Clear()
{
	for( size_t i=0 ;i<descriptorList.size(); i++ ){
		SAFE_DELETE(descriptorList[i]);
	}
	descriptorList.clear();
	for( size_t i=0 ;i<serviceLoopList.size(); i++ ){
		SAFE_DELETE(serviceLoopList[i]);
	}
	serviceLoopList.clear();
}

BOOL CSITTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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
		_OutputDebugString( L"++CSITTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0x7F ){
		//table_idがおかしい
		_OutputDebugString( L"++CSITTable:: table_id err 0x7F != 0x%02X", table_id );
		return FALSE;
	}
	if( readSize+section_length > dataSize && section_length > 3){
		//サイズ異常
		_OutputDebugString( L"++CSITTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}
	//CRCチェック
	crc32 = ((DWORD)data[3+section_length-4])<<24 |
		((DWORD)data[3+section_length-3])<<16 |
		((DWORD)data[3+section_length-2])<<8 |
		data[3+section_length-1];
	if( crc32 != _Crc32(3+section_length-4, data) ){
		_OutputDebugString( L"++CSITTable:: CRC err" );
		return FALSE;
	}

	if( section_length > 8 ){
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		transmission_info_loop_length = ((WORD)data[readSize+5]&0x0F)<<8 | data[readSize+6];
		readSize += 7;
		if( readSize+transmission_info_loop_length <= (DWORD)section_length+3-4 && transmission_info_loop_length > 0){
			CDescriptor descriptor;
			if( descriptor.Decode( data+readSize, transmission_info_loop_length, &descriptorList, NULL ) == FALSE ){
				_OutputDebugString( L"++CSITTable:: descriptor err" );
				return FALSE;
			}
			readSize+=transmission_info_loop_length;
		}
		while( readSize < (DWORD)section_length+3-4 ){
			SERVICE_LOOP_DATA* item = new SERVICE_LOOP_DATA;
			item->service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item->running_status = (data[readSize+2]&0x70)>>4;
			item->service_loop_length = ((WORD)data[readSize+2]&0x0F)<<8 | data[readSize+3];
			readSize += 4;
			if( readSize+item->service_loop_length <= (DWORD)section_length+3-4 && item->service_loop_length > 0){
				CDescriptor descriptor;
				if( descriptor.Decode( data+readSize, item->service_loop_length, &(item->descriptorList), NULL ) == FALSE ){
					_OutputDebugString( L"++CSITTable:: descriptor2 err" );
					return FALSE;
				}
			}
			readSize+=item->service_loop_length;
			serviceLoopList.push_back(item);
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

