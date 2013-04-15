#pragma once
#include "NWStructDef.h"
#include "StringUtil.h"

class CProxyUtil
{
public:
	CProxyUtil(void);
	~CProxyUtil(void);

	//IEのProxy設定を取得する
	//戻り値：
	// TRUE（関数成功）、FALSE（関数失敗）
	BOOL GetIEProxyConfig(
		CURRENT_USER_IE_PROXY_CONFIG** proxyConfig //[OUT]IEのProxy設定
		);

	//自動的に検出でProxyのアドレスを取得する
	//戻り値：
	// TRUE（関数成功）、FALSE（関数失敗）
	BOOL GetProxyAutoDetect(
		LPCWSTR accessURL, //[IN]Proxy設定取得のために試しに接続するURL
		PROXY_CONFIG** proxyConfig //[OUT]Proxyの情報
		);

	//自動構成スクリプトでProxyのアドレスを取得する
	//戻り値：
	// TRUE（関数成功）、FALSE（関数失敗）
	BOOL GetProxyAutoScript(
		LPCWSTR accessURL, //[IN]Proxy設定取得のために試しに接続するURL
		LPCWSTR scriptURL, //[IN]自動構成スクリプトのURL
		PROXY_CONFIG** proxyConfig //[OUT]Proxyの情報
		);

private:
	wstring agent;
	CURRENT_USER_IE_PROXY_CONFIG* ieConfig;
	PROXY_CONFIG* autoDetectConfig;
	PROXY_CONFIG* autoScriptConfig;
};

