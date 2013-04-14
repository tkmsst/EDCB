#include "stdafx.h"

#include "CtrlCmdCLI.h"
#include "../../Common/ErrDef.h"

#include <vcclr.h>
#include <string>

using namespace CtrlCmdCLI;

TwitterPlugInUtil::TwitterPlugInUtil(void)
{
	this->util = new CTwitterUtil;
}

TwitterPlugInUtil::~TwitterPlugInUtil(void)
{
	if( this->util != NULL ){
		delete this->util;
		this->util = NULL;
	}
}

TwitterPlugInUtil::!TwitterPlugInUtil(void)
{
	if( this->util != NULL ){
		delete this->util;
		this->util = NULL;
	}
}

void TwitterPlugInUtil::CopyData(Def::CurrentUserIEProxyConfig^ src, CURRENT_USER_IE_PROXY_CONFIG* dest)
{
	pin_ptr<const wchar_t> autoConfigUrlPin = PtrToStringChars(src->autoConfigUrl);
	pin_ptr<const wchar_t> proxyPin = PtrToStringChars(src->proxy);
	pin_ptr<const wchar_t> proxyBypassPin = PtrToStringChars(src->proxyBypass);

	dest->autoDetect = src->autoDetect;

	wstring autoConfigUrl = autoConfigUrlPin;
	wstring proxy = proxyPin;
	wstring proxyBypass = proxyBypassPin;

	if( autoConfigUrl.size() > 0 ){
		dest->autoConfigUrl = new WCHAR[autoConfigUrl.size()+1];
		wcscpy_s(dest->autoConfigUrl, autoConfigUrl.size()+1, autoConfigUrl.c_str());
	}
	if( proxy.size() > 0 ){
		dest->proxy = new WCHAR[proxy.size()+1];
		wcscpy_s(dest->proxy, proxy.size()+1, proxy.c_str());
	}
	if( proxyBypass.size() > 0 ){
		dest->proxyBypass = new WCHAR[proxyBypass.size()+1];
		wcscpy_s(dest->proxyBypass, proxyBypass.size()+1, proxyBypass.c_str());
	}
}

void TwitterPlugInUtil::CopyData(CURRENT_USER_IE_PROXY_CONFIG* src, Def::CurrentUserIEProxyConfig^% dest)
{
	dest->autoDetect = src->autoDetect;
	if( src->autoConfigUrl != NULL ){
		dest->autoConfigUrl = gcnew String(src->autoConfigUrl);
	}
	if( src->proxyBypass != NULL ){
		dest->proxyBypass = gcnew String(src->proxyBypass);
	}
	if( src->proxy != NULL ){
		dest->proxy = gcnew String(src->proxy);
	}
	if( src->proxyBypass != NULL ){
		dest->proxyBypass = gcnew String(src->proxyBypass);
	}
}

void TwitterPlugInUtil::CopyData(Def::ProxyConfig^ src, PROXY_CONFIG* dest)
{
	pin_ptr<const wchar_t> proxyPin = PtrToStringChars(src->proxy);
	pin_ptr<const wchar_t> proxyBypassPin = PtrToStringChars(src->proxyBypass);

	wstring proxy = proxyPin;
	wstring proxyBypass = proxyBypassPin;

	if( proxy.size() > 0 ){
		dest->proxy = new WCHAR[proxy.size()+1];
		wcscpy_s(dest->proxy, proxy.size()+1, proxy.c_str());
	}
	if( proxyBypass.size() > 0 ){
		dest->proxyBypass = new WCHAR[proxyBypass.size()+1];
		wcscpy_s(dest->proxyBypass, proxyBypass.size()+1, proxyBypass.c_str());
	}
}

void TwitterPlugInUtil::CopyData(PROXY_CONFIG* src, Def::ProxyConfig^% dest)
{
	if( src->proxy != NULL ){
		dest->proxy = gcnew String(src->proxy);
	}
	if( src->proxyBypass != NULL ){
		dest->proxyBypass = gcnew String(src->proxyBypass);
	}
}

void TwitterPlugInUtil::CopyData(Def::UseProxyInfo^ src, USE_PROXY_INFO* dest)
{
	pin_ptr<const wchar_t> serverNamePin = PtrToStringChars(src->serverName);
	pin_ptr<const wchar_t> proxyBypassPin = PtrToStringChars(src->proxyBypass);
	pin_ptr<const wchar_t> userNamePin = PtrToStringChars(src->userName);
	pin_ptr<const wchar_t> passwordPin = PtrToStringChars(src->password);

	wstring serverName = serverNamePin;
	wstring proxyBypass = proxyBypassPin;
	wstring userName = userNamePin;
	wstring password = passwordPin;

	if( serverName.size() > 0 ){
		dest->serverName = new WCHAR[serverName.size()+1];
		wcscpy_s(dest->serverName, serverName.size()+1, serverName.c_str());
	}
	if( proxyBypass.size() > 0 ){
		dest->proxyBypass = new WCHAR[proxyBypass.size()+1];
		wcscpy_s(dest->proxyBypass, proxyBypass.size()+1, proxyBypass.c_str());
	}
	if( userName.size() > 0 ){
		dest->userName = new WCHAR[userName.size()+1];
		wcscpy_s(dest->userName, userName.size()+1, userName.c_str());
	}
	if( password.size() > 0 ){
		dest->password = new WCHAR[password.size()+1];
		wcscpy_s(dest->password, password.size()+1, password.c_str());
	}
}

void TwitterPlugInUtil::CopyData(USE_PROXY_INFO* src, Def::UseProxyInfo^% dest)
{
	if( src->serverName != NULL ){
		dest->serverName = gcnew String(src->serverName);
	}
	if( src->proxyBypass != NULL ){
		dest->proxyBypass = gcnew String(src->proxyBypass);
	}
	if( src->userName != NULL ){
		dest->userName = gcnew String(src->userName);
	}
	if( src->password != NULL ){
		dest->password = gcnew String(src->password);
	}
}

UInt32 TwitterPlugInUtil::Initialize()
{
	return util->Initialize();
}

UInt32 TwitterPlugInUtil::UnInitialize()
{
	return util->UnInitialize();
}

bool TwitterPlugInUtil::GetIEProxyConfig(
	Def::CurrentUserIEProxyConfig^% proxyConfig
	)
{
	CURRENT_USER_IE_PROXY_CONFIG* info;
	if( util->GetIEProxyConfig(&info) == TRUE ){
		CopyData(info, proxyConfig);
		return true;
	}else{
		return false;
	}
}

bool TwitterPlugInUtil::GetProxyAutoDetect(
	Def::ProxyConfig^% proxyConfig
	)
{
	PROXY_CONFIG* info;
	if( util->GetProxyAutoDetect(&info) == TRUE ){
		CopyData(info, proxyConfig);
		return true;
	}else{
		return false;
	}
}

bool TwitterPlugInUtil::GetProxyAutoScript(
	String^ scriptURL,
	Def::ProxyConfig^% proxyConfig
	)
{
	pin_ptr<const wchar_t> scriptURLPin = PtrToStringChars(scriptURL);
	std::wstring _scriptURL(scriptURLPin);

	PROXY_CONFIG* info;
	if( util->GetProxyAutoScript(_scriptURL.c_str(), &info) == TRUE ){
		CopyData(info, proxyConfig);
		return true;
	}else{
		return false;
	}
}

void TwitterPlugInUtil::SetProxy(
	bool useProxy,
	Def::UseProxyInfo^ proxyInfo
	)
{
	USE_PROXY_INFO info;
	CopyData(proxyInfo, &info);

	util->SetProxy(useProxy, &info);

}

bool TwitterPlugInUtil::GetAuthorizationUrl(
	String^% url
	)
{
	WCHAR* info;

	if( util->GetAuthorizationUrl(&info) == TRUE ){
		url = gcnew String(info);
		return true;
	}else{
		return false;
	}
}

bool TwitterPlugInUtil::SetAuthorizationPWD(
	String^ password
	)
{
	pin_ptr<const wchar_t> passwordPin = PtrToStringChars(password);
	std::wstring _password(passwordPin);

	if( util->SetAuthorizationPWD(_password.c_str()) == TRUE ){
		return true;
	}else{
		return false;
	}
}

bool TwitterPlugInUtil::SendTweet(
	bool asyncMode,
	String^ text
	)
{
	pin_ptr<const wchar_t> textPin = PtrToStringChars(text);
	std::wstring _text(textPin);

	if( util->SendTweet(asyncMode, _text.c_str()) == TRUE ){
		return true;
	}else{
		return false;
	}
}
