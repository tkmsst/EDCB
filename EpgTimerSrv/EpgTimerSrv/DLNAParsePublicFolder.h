#pragma once

#include "../../Common/CommonDef.h"
#include "../../Common/StringUtil.h"

typedef struct _DLNA_PUBLIC_FOLDER_INFO{
	wstring virtualPath;
	wstring folderPath;
}DLNA_PUBLIC_FOLDER_INFO;

class DLNAParsePublicFolder
{
public:
	DLNAParsePublicFolder(void);
	~DLNAParsePublicFolder(void);

	BOOL ParseText(
		LPCWSTR filePath
		);


public:
	map<wstring, DLNA_PUBLIC_FOLDER_INFO> folderList;
protected:
	BOOL Parse1Line(string parseLine, DLNA_PUBLIC_FOLDER_INFO* info );
};

