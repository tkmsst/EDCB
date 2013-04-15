#include "StdAfx.h"
#include "HttpRecFileSend.h"

#include "../../Common/StringUtil.h"
#include "../../Common/PathUtil.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

CHttpRecFileSend::CHttpRecFileSend(void)
{
	this->rootUri = L"";
}


CHttpRecFileSend::~CHttpRecFileSend(void)
{
}

void CHttpRecFileSend::SetRootUri(wstring rootUri)
{
	this->rootUri = rootUri;
}

void CHttpRecFileSend::SetRecInfo(vector<REC_FILE_INFO>* infoList)
{
	this->recInfoList.clear();

	for( size_t i=0; i<infoList->size(); i++ ){
		if( (*infoList)[i].recFilePath.size() > 0 ){
			this->recInfoList.insert(pair<DWORD, REC_FILE_INFO>((*infoList)[i].id, (*infoList)[i]));
		}
	}
}


int CHttpRecFileSend::HttpRequest(string method, string uri, nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent)
{
	int ret = 200;
	string buff = "";
	string path = "";
	string rootA = "";
	wstring filePath = L"";
	nocase::map<string, string> httpResHeader;
	nocase::map<string, string>::iterator itrHead;
	__int64 fileSize = 0;
	string contentType = "";
	__int64 offset = 0;
	__int64 endPos = 0;
	map<__int64, __int64> rangeList;

	DWORD id = 0;
	map<DWORD, REC_FILE_INFO>::iterator itrInfo;


	if( this->rootUri.size() == 0){
		ret = 404;
		goto Err_End;
	}
	if( CompareNoCase(method, "GET") != 0 ){
		ret = 404;
		goto Err_End;
	}

	WtoA(this->rootUri, rootA);

	UrlDecode(uri.c_str(), (DWORD)uri.size(), buff);

	//通常のルート
	Separate(buff, rootA, buff, path);
	if(path.size() == 0 || path.compare("list.html") == 0){
		//ファイル一覧のHTMLを返す
		ret = SendRecFileList(headerList, clientSock, stopEvent);
		goto End;
	}

	id = atoi(path.c_str());
	itrInfo = this->recInfoList.find(id);
	if( itrInfo == this->recInfoList.end()){
		ret = 404;
		goto Err_End;
	}


	filePath = itrInfo->second.recFilePath;

	if( PathFileExists(filePath.c_str()) == FALSE ){
		ret = 404;
		goto Err_End;
	}

	httpSend.GetContentType(filePath, contentType);
	fileSize = httpSend.GetContentLength(filePath);

	endPos = fileSize;

	itrHead = headerList->find("Range");
	if( itrHead == headerList->end() ){
		//Rangeなし
		Format(buff, "%I64d", fileSize);
		httpResHeader.insert(pair<string, string>("Content-Length", buff));
		httpResHeader.insert(pair<string, string>("Content-Type", contentType));

		httpSend.SendResponseHeader(200, &httpResHeader, clientSock, stopEvent);
		httpSend.SendFile(filePath, offset, endPos, clientSock, stopEvent);
	}else{
		if( httpSend.ParseRangeHeader(fileSize, itrHead->second, &rangeList) == FALSE ){
			//Range指定が何かおかしい
			Format(buff, "%I64d", fileSize);
			httpResHeader.insert(pair<string, string>("Content-Length", buff));
			httpResHeader.insert(pair<string, string>("Content-Type", contentType));

			httpSend.SendResponseHeader(200, &httpResHeader, clientSock, stopEvent);
			httpSend.SendFile(filePath, offset, endPos, clientSock, stopEvent);
		}else{
			httpResHeader.insert(pair<string, string>("Accept-Ranges", "bytes"));
			if( rangeList.size() > 1 ){
				//複数の場所指定
				Format(buff, "multipart/byteranges; boundary=%s", MULTI_PART_BOUNDARY);
				httpResHeader.insert(pair<string, string>("Content-Type", buff));

				httpSend.SendResponseHeader(206, &httpResHeader, clientSock, stopEvent);


				map<__int64, __int64>::iterator itr;
				string boundary = "";
				for( itr = rangeList.begin(); itr != rangeList.end(); itr++ ){
					boundary = "--";
					boundary += MULTI_PART_BOUNDARY;
					boundary += "\r\n";
					Format(buff, "Content-Type: %s\r\n", contentType);
					boundary += buff;
					Format(buff, "Content-Range: bytes %I64d-%I64d/%I64d\r\n", itr->first, itr->second, fileSize);
					boundary += buff;
					boundary += "\r\n";

					if( httpSend.SendData((BYTE*)boundary.c_str(), (DWORD)boundary.size(), clientSock, stopEvent) != NO_ERR ){
						goto End;
					}
					if( httpSend.SendFile(filePath, itr->first, itr->second+1, clientSock, stopEvent) != NO_ERR ){
						goto End;
					}

					boundary = "\r\n";
					httpSend.SendData((BYTE*)boundary.c_str(), (DWORD)boundary.size(), clientSock, stopEvent);
				}
				boundary = "--";
				boundary += MULTI_PART_BOUNDARY;
				boundary += "--\r\n";
				httpSend.SendData((BYTE*)boundary.c_str(), (DWORD)boundary.size(), clientSock, stopEvent);
			}else{
				//一カ所のみ
				map<__int64, __int64>::iterator itr;
				itr = rangeList.begin();

				httpResHeader.insert(pair<string, string>("Content-Type", contentType));
				Format(buff, "bytes %I64d-%I64d/%I64d", itr->first, itr->second, fileSize);
				httpResHeader.insert(pair<string, string>("Content-Range", buff));
				Format(buff, "%I64d", itr->second-itr->first+1);
				httpResHeader.insert(pair<string, string>("Content-Length", buff));

				httpSend.SendResponseHeader(206, &httpResHeader, clientSock, stopEvent);
				httpSend.SendFile(filePath, itr->first, itr->second+1, clientSock, stopEvent);

			}
		}
	}

	return ret;

Err_End:
	httpSend.SendResponseHeader(ret, &httpResHeader, clientSock, stopEvent);
End:
	return ret;
}

int CHttpRecFileSend::SendRecFileList(nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent)
{
	int ret = 200;

	string sendHtml = "";
	string buff="";
	nocase::map<string, string> httpResHeader;

	sendHtml = HTML_TEXT_TOP;

	sendHtml+="録画ファイル一覧<BR>\r\n<BR>\r\n";

	if( this->recInfoList.size() == 0 ){
		sendHtml+="ファイルが存在しません<BR>\r\n";
	}else{
		map<DWORD, REC_FILE_INFO>::iterator itr;
		for(itr = this->recInfoList.begin(); itr != this->recInfoList.end(); itr++ ){
			string item="";
			wstring fileName = L"";
			string fileNameA = "";
			GetFileName(itr->second.recFilePath, fileName);
			WtoA(fileName, fileNameA);

			Format(item, "<a href=\".%s/%d\">%s</a><BR>\r\n", rootUri.c_str(), itr->second.id, fileNameA.c_str());
			sendHtml+=item;
		}
	}

	sendHtml += HTML_TEXT_END;

	Format(buff, "%I64d", sendHtml.size());
	httpResHeader.insert(pair<string, string>("Content-Length", buff));
	httpResHeader.insert(pair<string, string>("Content-Type", "text/html; charset=Shift_JIS;"));

	httpSend.SendResponseHeader(200, &httpResHeader, clientSock, stopEvent);
	httpSend.SendData((BYTE*)sendHtml.c_str(), (DWORD)sendHtml.size(), clientSock, stopEvent);

	return ret;
}

