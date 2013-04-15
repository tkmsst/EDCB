#include "StdAfx.h"
#include "HttpPublicFileSend.h"

#include "../../Common/StringUtil.h"
#include "../../Common/PathUtil.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

CHttpPublicFileSend::CHttpPublicFileSend(void)
{
	this->rootUri = L"";
	this->folderPath = L"";
}


CHttpPublicFileSend::~CHttpPublicFileSend(void)
{
}

void CHttpPublicFileSend::SetPublicFolder(wstring rootUri, wstring folderPath)
{
	this->rootUri = rootUri;
	this->folderPath = folderPath;
}

void CHttpPublicFileSend::SetVirtualPath(map<wstring, wstring>* virtualPathList)
{
	this->virtualPathList.clear();

	map<wstring, wstring>::iterator itr;
	for(itr = virtualPathList->begin(); itr != virtualPathList->end(); itr++){
		string uri = "";
		WtoA(itr->first, uri);
		this->virtualPathList.insert(pair<string, wstring>(uri, itr->second));
	}
}

int CHttpPublicFileSend::HttpRequest(string method, string uri, nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent)
{
	int ret = 200;
	string buff = "";
	string path = "";
	string rootA = "";
	wstring filePath = L"";
	wstring wbuff = L"";
	map<string, wstring>::iterator itrVPath;
	nocase::map<string, string>::iterator itrHead;
	nocase::map<string, string> httpResHeader;
	__int64 fileSize = 0;
	string contentType = "";
	__int64 offset = 0;
	__int64 endPos = 0;
	map<__int64, __int64> rangeList;

	if( this->folderPath.size() == 0 || this->rootUri.size() == 0){
		ret = 404;
		goto Err_End;
	}
	if( CompareNoCase(method, "GET") != 0 ){
		ret = 404;
		goto Err_End;
	}

	WtoA(this->rootUri, rootA);

	UrlDecode(uri.c_str(), (DWORD)uri.size(), buff);


	//仮想パスから検索
	for(itrVPath = this->virtualPathList.begin(); itrVPath != this->virtualPathList.end(); itrVPath++){
		string key;
		Format(key, "%s/%s/", rootA.c_str(), itrVPath->first.c_str());

		if( buff.find(key) == 0 ){
			Separate(buff, key, buff, path);
			Replace(path, "/", "\\");

			UTF8toW(path, wbuff);

			filePath = itrVPath->second;
			ChkFolderPath(filePath);
			filePath += L"\\";
			filePath += wbuff;
			break;
		}
	}

	if(filePath.size() == 0 ){
		//通常のルート
		Separate(buff, rootA, buff, path);
		Replace(path, "/", "\\");

		UTF8toW(path, wbuff);

		filePath = this->folderPath;
		ChkFolderPath(filePath);
		filePath += L"\\";
		filePath += wbuff;
	}

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
