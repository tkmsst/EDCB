#pragma once

/*
CA_descriptor() {
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	CA_system_ID				16 uimsbf
	reserved					3 bslbf
	CA_PID						13 uimsbf
	for (i = 0; i < N; i++) {
		private_data_byte			8 uimsbf
	}
}

*/

#include "../../../Common/Util.h"

class CCADesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD CA_system_ID;
	WORD CA_PID;
	BYTE private_data_byteLength;
	BYTE* private_data_byte;

public:
	CCADesc(void);
	~CCADesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};

