#include "StdAfx.h"
#include "LogoTransmissionDesc.h"

CLogoTransmissionDesc::CLogoTransmissionDesc(void)
{
	logo_charLength = 0;
	logo_char = NULL;
}

CLogoTransmissionDesc::~CLogoTransmissionDesc(void)
{
	SAFE_DELETE_ARRAY(logo_char);
}

BOOL CLogoTransmissionDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	SAFE_DELETE_ARRAY(logo_char);
	logo_charLength = 0;

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

	if( descriptor_tag != 0xCF ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CLogoTransmissionDesc:: descriptor_tag err 0xCF != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CLogoTransmissionDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		logo_transmission_type = data[readSize];
		readSize++;
		if( logo_transmission_type == 0x01 ){
			logo_id = ((WORD)(data[readSize]&0x01))<<8 | data[readSize+1];
			logo_version = ((WORD)(data[readSize+2]&0x0F))<<8 | data[readSize+3];
			download_data_id = ((WORD)(data[readSize+4]))<<8 | data[readSize+5];
		}else if( logo_transmission_type == 0x02 ){
			logo_id = ((WORD)(data[readSize]&0x01))<<8 | data[readSize+1];
		}else if( logo_transmission_type == 0x03 ){
			if( (readSize-2) < descriptor_length ){
				logo_charLength = descriptor_length - (BYTE)(readSize-2);
				logo_char = new CHAR[logo_charLength+1];
				if( logo_charLength > 0 ){
					memcpy(logo_char, data+readSize, logo_charLength );
					readSize+=logo_charLength;
				}
				logo_char[logo_charLength] = '\0';
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
