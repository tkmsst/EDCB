#include "StdAfx.h"
#include "ConnectedTransmissionDesc.h"

CConnectedTransmissionDesc::CConnectedTransmissionDesc(void)
{
	additional_connected_transmission_infoLength = 0;
	additional_connected_transmission_info = NULL;
}

CConnectedTransmissionDesc::~CConnectedTransmissionDesc(void)
{
	SAFE_DELETE_ARRAY(additional_connected_transmission_info);
}

BOOL CConnectedTransmissionDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(additional_connected_transmission_info);
	additional_connected_transmission_infoLength = 0;

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

	if( descriptor_tag != 0xDD ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CConnectedTransmissionDesc:: descriptor_tag err 0xDD != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CConnectedTransmissionDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		connected_transmission_group_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		segment_type = (data[readSize+2]&0xC0)>>6;
		modulation_type_A = (data[readSize+2]&0x30)>>4;
		modulation_type_B = (data[readSize+2]&0x0C)>>2;
		readSize+=3;

		if( (readSize-2) < descriptor_length ){
			additional_connected_transmission_infoLength = descriptor_length - (BYTE)(readSize-2);
			additional_connected_transmission_info = new BYTE[additional_connected_transmission_infoLength];
			memcpy(additional_connected_transmission_info, data + readSize, additional_connected_transmission_infoLength );
			readSize+=additional_connected_transmission_infoLength;
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
