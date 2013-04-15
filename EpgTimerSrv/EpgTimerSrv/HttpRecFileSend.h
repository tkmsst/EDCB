#pragma once

#include "../../Common/CommonDef.h"
#include "HttpFileSend.h"

class CHttpRecFileSend
{
public:
	CHttpRecFileSend(void);
	~CHttpRecFileSend(void);

	void SetRootUri(wstring rootUri);
	void SetRecInfo(vector<REC_FILE_INFO>* infoList);

	int HttpRequest(string method, string uri, nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent);

protected:
	CHttpFileSend httpSend;
	wstring rootUri;
	map<DWORD, REC_FILE_INFO> recInfoList;

protected:
	int SendRecFileList(nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent);
};

