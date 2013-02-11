#include "StdAfx.h"
#include "ExtendedBroadcasterDesc.h"

CExtendedBroadcasterDesc::CExtendedBroadcasterDesc(void)
{
}

CExtendedBroadcasterDesc::~CExtendedBroadcasterDesc(void)
{
}

BOOL CExtendedBroadcasterDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	affiliation_idList.clear();
	broadcastList.clear();
	sound_broadcast_affiliation_idList.clear();

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

	if( descriptor_tag != 0xCE ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CExtendedBroadcasterDesc:: descriptor_tag err 0xCE != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CExtendedBroadcasterDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		broadcaster_type = (data[readSize]&0xF0)>>4;
		readSize++;
		if( broadcaster_type == 0x01 ){
			terrestrial_broadcaster_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			number_of_affiliation_id_loop = (data[readSize+2] & 0xF0)>>4;
			number_of_broadcaster_id_loop = data[readSize+2] & 0x0F;
			readSize+=3;
			for( BYTE i=0; i<number_of_affiliation_id_loop; i++ ){
				affiliation_idList.push_back(data[readSize]);
				readSize++;
			}
			for( BYTE i=0; i<number_of_broadcaster_id_loop; i++ ){
				BROADCAST_DATA item;
				item.original_network_id = ((WORD)data[readSize])<<8 | data[readSize+1];
				item.broadcaster_id = data[readSize+2];

				broadcastList.push_back(item);
				readSize+=3;
			}
		}else if( broadcaster_type == 0x02 ){
			terrestrial_sound_broadcaster_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			number_of_sound_broadcast_affiliation_id_loop = (data[readSize+2] & 0xF0)>>4;
			number_of_broadcaster_id_loop = data[readSize+2] & 0x0F;
			readSize+=3;
			for( BYTE i=0; i<number_of_sound_broadcast_affiliation_id_loop; i++ ){
				sound_broadcast_affiliation_idList.push_back(data[readSize]);
				readSize++;
			}
			for( BYTE i=0; i<number_of_broadcaster_id_loop; i++ ){
				BROADCAST_DATA item;
				item.original_network_id = ((WORD)data[readSize])<<8 | data[readSize+1];
				item.broadcaster_id = data[readSize+2];

				broadcastList.push_back(item);
				readSize+=3;
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

