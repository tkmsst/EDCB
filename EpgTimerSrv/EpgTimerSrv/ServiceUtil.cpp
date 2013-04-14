#include "stdafx.h"
#include "ServiceUtil.h"

BOOL InstallService(LPCWSTR lpcwszFilePath, LPCWSTR lpcwszName, LPCWSTR lpcwszViewName)
{
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;

	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = CreateServiceW(hScm, lpcwszName, lpcwszViewName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL, lpcwszFilePath, NULL, NULL, NULL, NULL, NULL);
	if(hSrv == NULL){
		OutputDebugString(_T("service install failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}

	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);

	return TRUE;
}

BOOL RemoveService(LPCWSTR lpcwszName)
{
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;
	SERVICE_STATUS stStatus;

	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = OpenServiceW(hScm, lpcwszName, DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);
	if(hSrv == NULL){
		OutputDebugString(_T("OpenService failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}
	if(QueryServiceStatus(hSrv, &stStatus) == FALSE ){
		OutputDebugString(_T("QueryServiceStatus failed"));
		CloseServiceHandle(hSrv);
		CloseServiceHandle(hScm);
		return FALSE;
	}
	if( stStatus.dwCurrentState != SERVICE_STOPPED ){
		if( ControlService(hSrv, SERVICE_CONTROL_STOP, &stStatus) == FALSE ){
			OutputDebugString(_T("ControlService failed"));
			CloseServiceHandle(hSrv);
			CloseServiceHandle(hScm);
			return FALSE;
		}
	}
	DeleteService(hSrv);

	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);

	return TRUE;
}

BOOL IsInstallService(LPCWSTR lpcwszName)
{
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;
	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = OpenServiceW(hScm, lpcwszName, SERVICE_QUERY_STATUS);
	if(hSrv == NULL){
		OutputDebugString(_T("OpenService failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}
	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);

	return TRUE;
}

BOOL IsStopService(LPCWSTR lpcwszName)
{
	BOOL bRet = FALSE;
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;
	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = OpenServiceW(hScm, lpcwszName, SERVICE_QUERY_STATUS);
	if(hSrv == NULL){
		OutputDebugString(_T("OpenService failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}
	SERVICE_STATUS stStatus;
	if( QueryServiceStatus(hSrv, &stStatus) == TRUE ){
		if(stStatus.dwCurrentState == SERVICE_STOPPED){
			bRet = TRUE;
		}
	}else{
		OutputDebugString(_T("QueryServiceStatus failed"));
	}

	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);

	return bRet;
}

BOOL StartServiceCtrl(LPCWSTR lpcwszName)
{
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;
	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = OpenServiceW(hScm, lpcwszName, SERVICE_START);
	if(hSrv == NULL){
		OutputDebugString(_T("OpenService failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}
	if( StartServiceW(hSrv, 0, NULL) == FALSE ){
		OutputDebugString(_T("StartService failed"));
	}

	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);

	return TRUE;
}

BOOL StopServiceCtrl(LPCWSTR lpcwszName)
{
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;
	SERVICE_STATUS stStatus;

	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = OpenServiceW(hScm, lpcwszName, SERVICE_STOP | SERVICE_QUERY_STATUS);
	if(hSrv == NULL){
		OutputDebugString(_T("OpenService failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}
	if(QueryServiceStatus(hSrv, &stStatus) == FALSE ){
		OutputDebugString(_T("QueryServiceStatus failed"));
		CloseServiceHandle(hSrv);
		CloseServiceHandle(hScm);
		return FALSE;
	}
	if( stStatus.dwCurrentState != SERVICE_STOPPED ){
		if( ControlService(hSrv, SERVICE_CONTROL_STOP, &stStatus) == FALSE ){
			OutputDebugString(_T("ControlService failed"));
			CloseServiceHandle(hSrv);
			CloseServiceHandle(hScm);
			return FALSE;
		}
	}

	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);

	return TRUE;
}

DWORD GetServiceStatus(LPCWSTR lpcwszName)
{
	SC_HANDLE hScm = NULL;
	SC_HANDLE hSrv = NULL;
	SERVICE_STATUS stStatus;

	hScm = OpenSCManagerW(0, 0, SC_MANAGER_CONNECT);
	if(hScm == NULL){
		OutputDebugString(_T("OpenSCManager failed"));
		return FALSE;
	}
	hSrv = OpenServiceW(hScm, lpcwszName, SERVICE_QUERY_STATUS);
	if(hSrv == NULL){
		OutputDebugString(_T("OpenService failed"));
		CloseServiceHandle(hScm);
		return FALSE;
	}
	if(QueryServiceStatus(hSrv, &stStatus) == FALSE ){
		OutputDebugString(_T("QueryServiceStatus failed"));
		CloseServiceHandle(hSrv);
		CloseServiceHandle(hScm);
		return FALSE;
	}
	DWORD dwStatus = stStatus.dwCurrentState;
	return dwStatus;
}
