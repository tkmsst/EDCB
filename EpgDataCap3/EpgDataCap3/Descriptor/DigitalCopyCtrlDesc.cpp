#include "StdAfx.h"
#include "DigitalCopyCtrlDesc.h"

CDigitalCopyCtrlDesc::CDigitalCopyCtrlDesc(void)
{
}

CDigitalCopyCtrlDesc::~CDigitalCopyCtrlDesc(void)
{
}

BOOL CDigitalCopyCtrlDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	component_controlList.clear();

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

	if( descriptor_tag != 0xC1 ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CDigitalCopyCtrlDesc:: descriptor_tag err 0xC1 != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CDigitalCopyCtrlDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		digital_recording_control_data = (data[readSize]&0xC0) >> 6;
		maximum_bitrate_flag = (data[readSize]&0x20) >> 5;
		component_control_flag = (data[readSize]&0x10) >> 4;
		user_defined = data[readSize]&0x0F;
		readSize++;
		if( maximum_bitrate_flag == 1 ){
			maximum_bitrate = data[readSize];
			readSize++;
		}
		if( component_control_flag == 1 ){
			component_control_length = data[readSize];
			readSize++;
			BYTE itemReadSize = 0;
			while( itemReadSize < component_control_length ){
				COMPONENT_CTRL_DATA item;
				item.component_tag = data[readSize];
				itemReadSize++;
				readSize++;

				item.digital_recording_control_data = (data[readSize]&0xC0) >> 6;
				item.maximum_bitrate_flag = (data[readSize]&0x20) >> 5;
				item.user_defined = data[readSize]&0x0F;
				itemReadSize++;
				readSize++;
				
				if( item.maximum_bitrate_flag == 1 ){
					item.maximum_bitrate = data[readSize];
					itemReadSize++;
					readSize++;
				}

				component_controlList.push_back(item);
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
