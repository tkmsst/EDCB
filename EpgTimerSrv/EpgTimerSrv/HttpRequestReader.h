#pragma once

#include "../../Common/CommonDef.h"

#define HTTP_HEADER_READ_BUFF (64*1024)

class CHttpRequestReader
{
public:
	CHttpRequestReader(void);
	~CHttpRequestReader(void);

	void SetSocket(SOCKET clientSock, HANDLE stopEvent);

	int ReadHeader(string& method, string& uri, string& version, nocase::map<string,string>* headerList);
	int ReadBody(BYTE* buff, int* buffSize);
protected:
	SOCKET clientSock;
	HANDLE stopEvent;

	string method;
	string uri;
	string httpVersion;
	nocase::map<string,string> headerList;

	BOOL chunkedFlag;
	__int64 contentSize;
	__int64 totalReadSize;
	__int64 totalReadChunkSize;
	int chunkEndRead;
	int chunkSize;
};

