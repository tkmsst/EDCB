#include "StdAfx.h"
#include "DownloadContentDesc.h"

CDownloadContentDesc::CDownloadContentDesc(void)
{
	text_length = 0;
	text_char = NULL;
}

CDownloadContentDesc::~CDownloadContentDesc(void)
{
	Clear();
}

void CDownloadContentDesc::Clear()
{
	for( size_t i=0; i<moduleInfoList.size(); i++ ){
		SAFE_DELETE(moduleInfoList[i]);
	}
	moduleInfoList.clear();

	SAFE_DELETE_ARRAY(text_char);
	text_length = 0;
}

BOOL CDownloadContentDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	Clear();
	SAFE_DELETE_ARRAY(text_char);
	text_length = 0;

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

	if( descriptor_tag != 0xC9 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CDownloadContentDesc:: descriptor_tag err 0xC9 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CDownloadContentDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		reboot = (data[readSize]&0x80)>>7;
		add_on = (data[readSize]&0x40)>>6;
		compatibility_flag = (data[readSize]&0x20)>>5;
		module_info_flag = (data[readSize]&0x10)>>4;
		text_info_flag = (data[readSize]&0x08)>>3;
		readSize++;

		component_size = ((DWORD)data[readSize])<<24 |
			((DWORD)data[readSize+1])<<16 | 
			((DWORD)data[readSize+2])<<8 |
			((DWORD)data[readSize+4]);
		readSize+=4;

		download_id = ((DWORD)data[readSize])<<24 |
			((DWORD)data[readSize+1])<<16 | 
			((DWORD)data[readSize+2])<<8 |
			((DWORD)data[readSize+4]);
		readSize+=4;

		time_out_value_DII = ((DWORD)data[readSize])<<24 |
			((DWORD)data[readSize+1])<<16 | 
			((DWORD)data[readSize+2])<<8 |
			((DWORD)data[readSize+4]);
		readSize+=4;

		leak_rate = ((DWORD)data[readSize])<<14 |
			((DWORD)data[readSize+1])<<6 | 
			((DWORD)data[readSize+2]&0xFC)>>2;
		readSize+=3;

		component_tag = data[readSize];
		readSize++;

		if( compatibility_flag == 1 ){
			//CompatibilityDescriptor
			WORD compatibilityDescriptorLength = ((WORD)data[readSize])<<8 | data[readSize+1];
			readSize+=compatibilityDescriptorLength+2;
		}

		if( module_info_flag == 1 ){
			num_of_modules = ((WORD)data[readSize])<<8 | data[readSize+1];
			readSize+=2;
			for( WORD i=0; i<num_of_modules; i++ ){
				MODULE_INFO_DATA* item = new MODULE_INFO_DATA;
				item->module_id = ((WORD)data[readSize])<<8 | data[readSize+1];
				readSize+=2;

				item->module_size = ((DWORD)data[readSize])<<24 |
					((DWORD)data[readSize+1])<<16 | 
					((DWORD)data[readSize+2])<<8 |
					((DWORD)data[readSize+4]);
				readSize+=4;

				item->module_info_length = data[readSize];
				readSize++;

				if( item->module_info_length > 0 ){
					item->module_info_byte = new BYTE[item->module_info_length];
					memcpy(item->module_info_byte, data+readSize, item->module_info_length);
				}
				readSize+=item->module_info_length;

				moduleInfoList.push_back(item);
			}
		}

		private_data_length = data[readSize];
		readSize += 1 + private_data_length;

		if( text_info_flag == 1 ){
			memcpy( ISO_639_language_code, data+readSize, 3 );
			ISO_639_language_code[3] = '\0';
			readSize+=3;
			text_length = data[readSize];
			readSize++;
			if( text_length > 0 ){
				text_char = new BYTE[text_length+1];
				ZeroMemory(text_char, text_length+1);
				memcpy(text_char, data+readSize, text_length);
			}
			readSize+=text_length;
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

