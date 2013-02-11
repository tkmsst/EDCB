#include "StdAfx.h"
#include "HttpRequestReader.h"

#include "../../Common/ErrDef.h"
#include "../../Common/StringUtil.h"

CHttpRequestReader::CHttpRequestReader(void)
{
	this->clientSock = NULL;
	this->stopEvent = NULL;

	this->method = "";
	this->uri = "";
	this->httpVersion = "";
	this->headerList.clear();

	this->chunkedFlag = 0;
	this->contentSize = 0;
	this->totalReadSize = 0;
	this->totalReadChunkSize = 0;

	this->chunkEndRead = 0;
	this->chunkSize = -1;
}


CHttpRequestReader::~CHttpRequestReader(void)
{
}

void CHttpRequestReader::SetSocket(SOCKET clientSock, HANDLE stopEvent)
{
	this->clientSock = clientSock;
	this->stopEvent = stopEvent;

	this->method = "";
	this->uri = "";
	this->httpVersion = "";
	this->headerList.clear();

	this->chunkedFlag = 0;
	this->contentSize = 0;
	this->totalReadSize = 0;
	this->totalReadChunkSize = 0;

	this->chunkEndRead = 0;
	this->chunkSize = -1;
}

int CHttpRequestReader::ReadHeader(string& method, string& uri, string& httpVersion, nocase::map<string,string>* headerList)
{
	fd_set ready;
	struct timeval to;

	int res = NO_ERR;
	int result = 0;
	char* httpHead = new char[HTTP_HEADER_READ_BUFF+1];
	ZeroMemory(httpHead, HTTP_HEADER_READ_BUFF+1);
	BOOL readHead = FALSE;
	int timeoutCount = 0;
	char* endPos = NULL;
	int length = 0;

	string strHttpHead = "";
	string strRequestLine = "";
	string strBuff1 = "";
	string strBuff2 = "";

	nocase::map<string, string>::iterator itr;

	if( this->clientSock == NULL ){
		res = ERR_FALSE;
		goto Err_End;
	}

	//HTTPリクエストヘッダの読み込み
	while(timeoutCount<30){
		if( WaitForSingleObject( stopEvent, 0 ) != WAIT_TIMEOUT ){
			//中止
			break;
		}

		to.tv_sec = 1;
		to.tv_usec = 0;
		FD_ZERO(&ready);
		FD_SET(clientSock, &ready);

		result = select(0, &ready, NULL, NULL, &to );
		if( result == SOCKET_ERROR ){
			res = ERR_FALSE;
			goto Err_End;
		}
		if ( FD_ISSET(clientSock, &ready) ){
			result = recv(clientSock, httpHead, HTTP_HEADER_READ_BUFF, MSG_PEEK);
			if( result == SOCKET_ERROR ){
				res = ERR_FALSE;
				goto Err_End;
			}else if( result == 0 ){
				res = ERR_FALSE;
				goto Err_End;
			}
			endPos = strstr(httpHead, "\r\n\r\n");
			if( endPos != NULL ){
				readHead = TRUE;
				length = (int)(endPos-httpHead);
				length+=4;
				memset(httpHead, 0, HTTP_HEADER_READ_BUFF);
				recv(clientSock, httpHead, length, 0);
				break;
			}else{
				Sleep(10);
			}
			timeoutCount = 0;
		}else{
			timeoutCount++;
		}
	}
	if( readHead == FALSE ){
		//HTTP通信じゃない可能性あり
		res = ERR_FALSE;
		goto Err_End;
	}


	//ヘッダの解析
	strHttpHead = httpHead;
	//OutputDebugStringA(httpHead);

	Separate(strHttpHead, "\r\n", strRequestLine, strBuff1);

	Separate(strRequestLine, " ", this->method, strBuff2);
	Separate(strBuff2, " ", this->uri, this->httpVersion);

	while(strBuff1.size() > 0 ){
		Separate(strBuff1, "\r\n", strBuff2, strBuff1);

		string name = "";
		string val = "";
		Separate(strBuff2, ":", name, val);
		Trim(name);
		Trim(val);
		if( name.size() > 0 ){
			this->headerList.insert(pair<string, string>(name, val));
		}
	}

	method = this->method;
	uri = this->uri;
	httpVersion = this->httpVersion;
	if( headerList != NULL ){
		*headerList = this->headerList;
	}

	this->chunkedFlag = FALSE;
	this->contentSize = 0;
	this->totalReadSize = 0;
	this->totalReadChunkSize = 0;
	this->chunkEndRead = 0;
	this->chunkSize = -1;

	itr = this->headerList.find("Content-Length");
	if( itr != this->headerList.end() ){
		this->contentSize = _atoi64(itr->second.c_str());
	}
	itr = this->headerList.find("Transfer-Encoding");
	if( itr != this->headerList.end()){
		if( CompareNoCase(itr->second, "chunked") == 0 ){
			this->chunkedFlag = TRUE;
		}
	}

Err_End:
	if( httpHead != NULL ){
		SAFE_DELETE_ARRAY(httpHead);
	}
	return res;
}

int CHttpRequestReader::ReadBody(BYTE* buff, int* buffSize)
{
	int res = 0;
	int readSize = 0;
	int readPos = 0;
	fd_set ready;
	struct timeval to;
	int result = 0;
	char tempBuff[64] = "";

	if( this->headerList.size() <= 0 ){
		return -1;
	}

	if( this->chunkedFlag == 0){
		//通常
		while(totalReadSize < contentSize && readPos<*buffSize){
			if( WaitForSingleObject( stopEvent, 0 ) != WAIT_TIMEOUT ){
				//中止
				break;
			}

			to.tv_sec = 1;
			to.tv_usec = 0;
			FD_ZERO(&ready);
			FD_SET(clientSock, &ready);

			result = select(0, &ready, NULL, NULL, &to );
			if( result == SOCKET_ERROR ){
				res = -1;
				goto Err_End;
			}
			if ( FD_ISSET(clientSock, &ready) ){
				if( totalReadSize+(*buffSize-readPos) > contentSize){
					readSize = (int)(contentSize-totalReadSize);
				}else{
					readSize = (*buffSize-readPos);
				}

				result = recv(clientSock, (char*)buff+readPos, readSize, 0);
				if( result == SOCKET_ERROR ){
					res = -1;
					goto Err_End;
				}else if( result == 0 ){
					res = -1;
					goto Err_End;
				}

				totalReadSize+=result;
				readPos+=result;
			}
		}

		if( totalReadSize < contentSize ){
			res = 1;
		}else{
			res = 2;
		}
	}else{
		//チャンク形式
		while( readPos<*buffSize){
			if( WaitForSingleObject( stopEvent, 0 ) != WAIT_TIMEOUT ){
				//中止
				break;
			}
			if( chunkSize == 0 ){
				res = 2;
				break;
			}
			to.tv_sec = 1;
			to.tv_usec = 0;
			FD_ZERO(&ready);
			FD_SET(clientSock, &ready);

			result = select(0, &ready, NULL, NULL, &to );
			if( result == SOCKET_ERROR ){
				res = -1;
				goto Err_End;
			}
			if ( FD_ISSET(clientSock, &ready) ){
				if( chunkEndRead == 1 ){
					result = recv(clientSock, tempBuff, 2, 0);
					if( result == SOCKET_ERROR ){
						res = -1;
						goto Err_End;
					}else if( result == 0 ){
						res = -1;
						goto Err_End;
					}
					memset(tempBuff, 0, 64);
				}
				if( chunkSize == -1 ){
					//サイズ部分
					result = recv(clientSock, tempBuff, 1, 0);
					if( result == SOCKET_ERROR ){
						res = -1;
						goto Err_End;
					}else if( result == 0 ){
						res = -1;
						goto Err_End;
					}else{
						if( strstr(tempBuff, "\r\n") != NULL ){
							chunkSize = strtol(tempBuff, NULL, 16);
							readSize = 0;
							totalReadChunkSize = 0;
							if( chunkSize == 0 ){
								res = 2;
								break;
							}
						}
					}
				}else{
					//data部分
					if( totalReadChunkSize+(*buffSize-readPos) > chunkSize){
						readSize = (int)(chunkSize-totalReadChunkSize);
					}else{
						readSize = (*buffSize-readPos);
					}

					result = recv(clientSock, (char*)buff+readPos, readSize, 0);
					if( result == SOCKET_ERROR ){
						res = -1;
						goto Err_End;
					}else if( result == 0 ){
						res = -1;
						goto Err_End;
					}
					res=1;
					totalReadSize+=result;
					totalReadChunkSize+=result;
					if( totalReadChunkSize >= chunkSize){
						chunkEndRead = 1;
						chunkSize = -1;
						memset(tempBuff, 0, 64);
					}
				}
			}
		}
	}

	*buffSize = readPos;
Err_End:

	return res;
}

