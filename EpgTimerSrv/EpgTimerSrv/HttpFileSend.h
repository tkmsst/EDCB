#pragma once

#include "../../Common/CommonDef.h"


#define MULTI_PART_BOUNDARY "EPG_TIMER_SRV"

#define HTML_TEXT_TOP "<HTML LANG=\"ja\">\r\n<HEAD>\r\n<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html;charset=Shift_JIS\">\r\n<TITLE>EpgTimer</TITLE>\r\n</HEAD>\r\n<BODY>\r\n"
#define HTML_TEXT_END "</BODY>\r\n</HTML>\r\n"

class CHttpFileSend
{
public:
	CHttpFileSend(void);
	~CHttpFileSend(void);

	int SendResponseHeader(int httpStatus, nocase::map<string, string>* paramList, SOCKET clientSock, HANDLE stopEvent);
	int SendFile(wstring filePath, __int64 offset, __int64 endPos, SOCKET clientSock, HANDLE stopEvent);
	int SendData(BYTE* data, DWORD dataSize, SOCKET clientSock, HANDLE stopEvent);

	void GetContentType(wstring filePath, string& contentType);
	__int64 GetContentLength(wstring filePath);

	BOOL ParseRangeHeader(__int64 fileSize, string val, map<__int64, __int64>* rangeList);
};

