#include "StdAfx.h"
#include "SDTTTable.h"

#include "../../../Common/EpgTimerUtil.h"
#include "../Descriptor/Descriptor.h"

CSDTTTable::CSDTTTable(void)
{
}

CSDTTTable::~CSDTTTable(void)
{
	Clear();
}

void CSDTTTable::Clear()
{
	for( size_t i=0 ;i<contentInfoList.size(); i++ ){
		SAFE_DELETE(contentInfoList[i]);
	}
	contentInfoList.clear();
}

BOOL CSDTTTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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
		_OutputDebugString( L"++CSDTTTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0xC3 ){
		//table_idがおかしい
		_OutputDebugString( L"++CSDTTTable:: table_id err 0xC3 != 0x%02X", table_id );
		return FALSE;
	}
	if( readSize+section_length > dataSize && section_length > 3){
		//サイズ異常
		_OutputDebugString( L"++CSDTTTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}
	//CRCチェック
	crc32 = ((DWORD)data[3+section_length-4])<<24 |
		((DWORD)data[3+section_length-3])<<16 |
		((DWORD)data[3+section_length-2])<<8 |
		data[3+section_length-1];
	if( crc32 != _Crc32(3+section_length-4, data) ){
		_OutputDebugString( L"++CSDTTTable:: CRC err" );
		return FALSE;
	}

	if( section_length > 12 ){
		maker_id = data[readSize];
		model_id = data[readSize+1];
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		transport_stream_id = ((WORD)data[readSize+5])<<8 | data[readSize+6];
		original_network_id = ((WORD)data[readSize+7])<<8 | data[readSize+8];
		service_id = ((WORD)data[readSize+9])<<8 | data[readSize+10];
		num_of_contents = data[readSize+11];
		readSize += 12;

		for( BYTE i=0; i<num_of_contents; i++ ){
			CONTENT_INFO_DATA* item = new CONTENT_INFO_DATA;
			item->group = (data[readSize]&0xF0)>>4;
			item->target_version = ((WORD)data[readSize]&0x0F)<<8 | data[readSize+1];
			item->new_version = ((WORD)data[readSize+2])<<4 | (data[readSize+3]&0xF0)>>4;
			item->download_level = (data[readSize+3]&0x0C)>>2;
			item->version_indicator = (data[readSize+3]&0x03);
			item->content_description_length = ((WORD)data[readSize+4])<<4 | (data[readSize+5]&0xF0)>>4;
			item->schedule_description_length = ((WORD)data[readSize+6])<<4 | (data[readSize+7]&0xF0)>>4;
			item->schedule_time_shift_information = data[readSize+7]&0x0F;
			readSize += 8;

			for( WORD j=0; j<item->schedule_description_length; j+=8){
				SCHEDULE_INFO_DATA time;

				DWORD mjd = ((DWORD)data[readSize])<<8 | data[readSize+1];
				_MJDtoSYSTEMTIME(mjd, &time.start_time);
				time.start_time.wHour = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
				time.start_time.wMinute = (WORD)_BCDtoDWORD(data+readSize+3, 1, 2);
				time.start_time.wSecond = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
				readSize += 5;

				time.duration = (_BCDtoDWORD(data+readSize, 1, 2)*60*60)
					+ (_BCDtoDWORD(data+readSize+1, 1, 2)*60)
					+ _BCDtoDWORD(data+readSize+2, 1, 2);
				readSize += 3;

				item->scheduleList.push_back(time);
			}

			WORD descLength = item->content_description_length - item->schedule_description_length;
			if( descLength > 0 ){
				CDescriptor descriptor;
				if( descriptor.Decode( data+readSize, descLength, &item->descriptorList, NULL ) == FALSE ){
					_OutputDebugString( L"++CSDTTTable:: descriptor err" );
					return FALSE;
				}
				readSize+=descLength;
			}

			contentInfoList.push_back(item);
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
