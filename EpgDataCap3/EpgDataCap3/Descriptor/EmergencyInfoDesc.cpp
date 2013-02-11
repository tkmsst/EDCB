#include "StdAfx.h"
#include "EmergencyInfoDesc.h"

CEmergencyInfoDesc::CEmergencyInfoDesc(void)
{
}

CEmergencyInfoDesc::~CEmergencyInfoDesc(void)
{
	Clear();
}

void CEmergencyInfoDesc::Clear()
{
	for( size_t i=0; i<emergencyList.size(); i++ ){
		SAFE_DELETE(emergencyList[i]);
	}
	emergencyList.clear();
}

BOOL CEmergencyInfoDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
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

	if( descriptor_tag != 0xFC ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CEmergencyInfoDesc:: descriptor_tag err 0xFC != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CEmergencyInfoDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		BYTE itemReadSize = 0;
		while( itemReadSize < descriptor_length ){
			EMERGENCY_DATA* item = new EMERGENCY_DATA;
			item->service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			item->start_end_flag = (data[readSize+2]&0x80)>>7;
			item->signal_level = (data[readSize+2]&0x40)>>6;
			item->area_code_length = data[readSize+3];
			readSize += 4;
			itemReadSize += 4;
			for( BYTE i=0; i<item->area_code_length/2; i++ ){
				WORD area_code = ((WORD)data[readSize])<<4 | (data[readSize+1]>>4);
				item->area_codeList.push_back(area_code);
				readSize += 2;
				itemReadSize += 2;
			}
			emergencyList.push_back(item);
		}
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}
