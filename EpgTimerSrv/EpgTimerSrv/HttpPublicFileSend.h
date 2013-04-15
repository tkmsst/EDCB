#pragma once

#include "../../Common/CommonDef.h"
#include "HttpFileSend.h"

class CHttpPublicFileSend
{
public:
	CHttpPublicFileSend(void);
	~CHttpPublicFileSend(void);

	void SetPublicFolder(wstring rootUri, wstring folderPath);
	void SetVirtualPath(map<wstring, wstring>* virtualPathList);

	int HttpRequest(string method, string uri, nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent);

protected:
	CHttpFileSend httpSend;
	wstring rootUri;
	wstring folderPath;
	map<string, wstring> virtualPathList;
};

