#include "stdafx.h"

#include "MPInclude.h"

#include "SortListUtil.h"
#include "UpnpStructDef.h"

#include "UpnpUtil.h"
#include "ThreadUtil.h"
#include "NICUtil.h"
#include "CharUtil.h"

int UPNP_UTIL_CreateUUID(char* uuid, int uuidSize, unsigned short deviceType, unsigned short uniqueID, unsigned short value)
{
	SORT_LIST_HANDLE nicList = NULL;
	MP_NIC_INFO* nicInfo = NULL;
	unsigned int key = 0x45504744;

	if( uuidSize < 37 ){
		return -1;
	}
	
	nicList = MP_NIC_GetNICInfo();
	if( nicList == NULL ){
		return -1;
	}
	nicInfo = (MP_NIC_INFO*)SORT_LIST_GetItemByIndex(nicList, 0);
#ifdef _WIN32
	sprintf_s(uuid, uuidSize, "%08x-%04x-%04x-%04x-%02x%02x%02x%02x%02x%02x",
		key,
		deviceType,
		uniqueID,
		value,
		nicInfo->macAddressValue[0],
		nicInfo->macAddressValue[1],
		nicInfo->macAddressValue[2],
		nicInfo->macAddressValue[3],
		nicInfo->macAddressValue[4],
		nicInfo->macAddressValue[5]
	);
#else;
	sprintf(uuid, "%08X-%04X-%04X-%04X-%02X%02X%02X%02X%02X%02X",
		key,
		deviceType,
		uniqueID,
		value,
		nicInfo->macAddressValue[0],
		nicInfo->macAddressValue[1],
		nicInfo->macAddressValue[2],
		nicInfo->macAddressValue[3],
		nicInfo->macAddressValue[4],
		nicInfo->macAddressValue[5]
	);
#endif

	SORT_LIST_CloseHandle(&nicList);

	return 1;
}

#define UPNP_UTIL_UA_PRODUCT "EpgTimerSrv/0.10"

int UPNP_UTIL_GetUserAgent(char* ua, int uaSize)
{
#if defined(_WIN32)
	OSVERSIONINFO VerInfo;
	VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx( &VerInfo );

	sprintf_s(ua, uaSize, "Windows/%d.%d UPnP/1.1 %s",
		VerInfo.dwMajorVersion,
		VerInfo.dwMinorVersion,
		UPNP_UTIL_UA_PRODUCT
	);
#elif defined(__APPLE__)
	sprintf(ua, "iOS_MacOS/%s UPnP/1.1 %s",
		"version",
		UPNP_UTIL_UA_PRODUCT
	);
#else
	sprintf(ua, "Android/%s UPnP/1.1 %s",
		"version",
		UPNP_UTIL_UA_PRODUCT
	);
#endif
	return 1;
}
