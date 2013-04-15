#pragma once

#include "../../Common/CommonDef.h"
#include "../../Common/StringUtil.h"

typedef struct _DLNA_PROTOCOL_INFO{
	wstring ext;
	wstring upnpClass;
	wstring mimeType;
	wstring info;
}DLNA_PROTOCOL_INFO;

class CDLNAParseProtocolInfo
{
public:
	CDLNAParseProtocolInfo(void);
	~CDLNAParseProtocolInfo(void);

	BOOL ParseText(
		LPCWSTR filePath
		);

public:
	map<wstring, DLNA_PROTOCOL_INFO> supportList;

protected:
	BOOL Parse1Line(string parseLine, DLNA_PROTOCOL_INFO* info );
};

