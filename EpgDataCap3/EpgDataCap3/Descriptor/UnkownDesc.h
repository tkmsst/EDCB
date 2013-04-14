#pragma once

class CUnkownDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
public:
	CUnkownDesc(void);
	~CUnkownDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
