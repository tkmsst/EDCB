#pragma once

#include "../../Common/CommonDef.h"
#include "HttpFileSend.h"
#include "HttpRequestReader.h"
#include "DLNAParseProtocolInfo.h"
#include "SOAPUtil.h"

#include "DLNADmsContentDB.h"

class CDLNADmsManager
{
public:
	CDLNADmsManager(void);
	~CDLNADmsManager(void);

	void SetRootUri(wstring& uri);

	void GetUuid(string& uuid);
	void GetDevicesType(vector<string>* urnList);
	void GetServicesType(vector<string>* urnList);
	int IsSupportUrn(string urn);
	void GetDDDUri(string uuid, string& uri);

	int CreateContainer(wstring parentObjectID, DLNA_DMS_CONTAINER_META_INFO* info, wstring& objectID);
	int CreateContainer2(wstring virtualPath, DLNA_DMS_CONTAINER_META_INFO* info, wstring& objectID);
	int DeleteContainer(wstring objectID);
	int AddContent(wstring containerObjectID, DLNA_DMS_CONTENT_META_INFO* info, wstring& objectID);
	int RemoveContent(wstring objectID);

	int HttpRequest(string method, string uri, nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
protected:
	wstring rootUri;
	wstring fileRootUri;
	string uuid;
	CHttpFileSend httpSend;
	CDLNAParseProtocolInfo protocolInfo;

	CDLNADmsContentDB dmsDB;

	map<wstring, __int64> cdsSubscribeList;
	unsigned short subscribeCount;

protected:
	int SendDDD(wstring filePath, SOCKET clientSock, HANDLE stopEvent);
	int SendSDD(wstring filePath, SOCKET clientSock, HANDLE stopEvent);

	int SoapCDS(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int SoapCMS(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int SoapAVT(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);

	int CDS_GetSearchCapabilities(SOAP_REQUEST_INFO* soapReq, string& resBody);
	int CDS_GetSortCapabilities(SOAP_REQUEST_INFO* soapReq, string& resBody);
	int CDS_GetSystemUpdateID(SOAP_REQUEST_INFO* soapReq, string& resBody);
	int CDS_Browse(string host, SOAP_REQUEST_INFO* soapReq, string& resBody);

	int CMS_GetProtocolInfo(SOAP_REQUEST_INFO* soapReq, string& resBody);

	int DIDL_CreateContainerMetaData(DLNA_DMS_CONTAINER_INFO*item, wstring& metaData);
	int DIDL_CreateContentMetaData(wstring host, DLNA_DMS_CONTENT_INFO* item, wstring& metaData);

	int SendFile(wstring filePath, nocase::map<string, string>* headerList, SOCKET clientSock, HANDLE stopEvent);

	int UploadFile(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);

	int Subscribe_CDS(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int Subscribe_CMS(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int Subscribe_AVT(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int UnSubscribe_CDS(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int UnSubscribe_CMS(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);
	int UnSubscribe_AVT(nocase::map<string, string>* headerList, CHttpRequestReader* reqReader, SOCKET clientSock, HANDLE stopEvent);

	void SendEvent();
};

