#include "StdAfx.h"
#include "NITTable.h"

#include "../../../Common/EpgTimerUtil.h"
#include "../Descriptor/Descriptor.h"

CNITTable::CNITTable(void)
{
}

CNITTable::~CNITTable(void)
{
	Clear();
}

void CNITTable::Clear()
{
	for( size_t i=0 ;i<descriptorList.size(); i++ ){
		SAFE_DELETE(descriptorList[i]);
	}
	descriptorList.clear();
	for( size_t i=0 ;i<TSInfoList.size(); i++ ){
		SAFE_DELETE(TSInfoList[i]);
	}
	TSInfoList.clear();
}

BOOL CNITTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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
		_OutputDebugString( L"++CNITTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id != 0x40 && table_id != 0x41 ){
		//table_idがおかしい
		_OutputDebugString( L"++CNITTable:: table_id err 0x%02X", table_id );
		return FALSE;
	}
	if( readSize+section_length > dataSize && section_length > 3){
		//サイズ異常
		_OutputDebugString( L"++CNITTable:: size err %d > %d", readSize+section_length, dataSize );
		return FALSE;
	}
	//CRCチェック
	crc32 = ((DWORD)data[3+section_length-4])<<24 |
		((DWORD)data[3+section_length-3])<<16 |
		((DWORD)data[3+section_length-2])<<8 |
		data[3+section_length-1];
	if( crc32 != _Crc32(3+section_length-4, data) ){
		_OutputDebugString( L"++CNITTable:: CRC err" );
		return FALSE;
	}

	if( section_length > 8 ){
		network_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		network_descriptors_length = ((WORD)data[readSize+5]&0x0F)<<8 | data[readSize+6];
		readSize += 7;
		if( readSize+network_descriptors_length <= (DWORD)section_length+3-4 && network_descriptors_length > 0){
			if( network_id == 0x0001 || network_id == 0x0003 ){
				SDDecode( data+readSize, network_descriptors_length, &descriptorList, NULL );
			}else{
				CDescriptor descriptor;
				if( descriptor.Decode( data+readSize, network_descriptors_length, &descriptorList, NULL ) == FALSE ){
					_OutputDebugString( L"++CNITTable:: descriptor err" );
					return FALSE;
				}
			}
			readSize+=network_descriptors_length;
		}
		transport_stream_loop_length = ((WORD)data[readSize]&0x0F)<<8 | data[readSize+1];
		readSize += 2;
		WORD tsLoopReadSize = 0;
		while( readSize < (DWORD)section_length+3-4 && tsLoopReadSize < transport_stream_loop_length){
			TS_INFO_DATA* item = new TS_INFO_DATA;
			item->transport_stream_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item->original_network_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
			item->transport_descriptors_length = ((WORD)data[readSize+4]&0x0F)<<8 | data[readSize+5];
			readSize += 6;
			if( readSize+item->transport_descriptors_length <= (DWORD)section_length+3-4 && item->transport_descriptors_length > 0){
				CDescriptor descriptor;
				if( descriptor.Decode( data+readSize, item->transport_descriptors_length, &(item->descriptorList), NULL ) == FALSE ){
					_OutputDebugString( L"++CNITTable:: descriptor2 err" );
					return FALSE;
				}
			}

			readSize+=item->transport_descriptors_length;
			tsLoopReadSize += 6 + item->transport_descriptors_length;

			TSInfoList.push_back(item);
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

BOOL CNITTable::SDDecode( BYTE* data, DWORD dataSize, vector<DESCRIPTOR_DATA*>* descriptorList, DWORD* decodeReadSize )
{
	BOOL ret = TRUE;
	if( data == NULL || dataSize == 0 || descriptorList == NULL ){
		return FALSE;
	}
	DWORD decodeSize = 0;

	DESCRIPTOR_DATA* item = new DESCRIPTOR_DATA;
	item->networkName = new CNetworkNameDesc;

	while( decodeSize < dataSize ){
		BYTE* readPos = data+decodeSize;
		if( readPos[0] == 0x82 ){
			//サービス名
			if( readPos[2] == 0x01 ){
				//日本語版？
				item->networkName->char_nameLength = readPos[1]-1;
				item->networkName->char_name = new CHAR[item->networkName->char_nameLength];
				memcpy(item->networkName->char_name, readPos+3, item->networkName->char_nameLength);
			}
			decodeSize += readPos[1]+2;
		}else{
			decodeSize += readPos[1]+2;
		}
	}
	if( item->networkName->char_nameLength == 0 ){
		SAFE_DELETE(item);
		ret = FALSE;
	}else{
		descriptorList->push_back(item);
	}

	if( decodeReadSize != NULL ){
		*decodeReadSize = dataSize;
	}
	return ret;
}
