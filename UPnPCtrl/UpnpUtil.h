#ifndef __UPNP_UTIL_H__
#define __UPNP_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define UPNP_DEVICE_TYPE_DMS 1
#define UPNP_DEVICE_TYPE_DMR 2
#define UPNP_DEVICE_TYPE_DMP 3
#define UPNP_DEVICE_TYPE_DMC 4
#define UPNP_SERVICE_TYPE_CDS 101
#define UPNP_SERVICE_TYPE_CMS 102
#define UPNP_SERVICE_TYPE_ATS 103
#define UPNP_SERVICE_TYPE_RCS 104

static const char UPNP_URN_CDS_1[] = "urn:schemas-upnp-org:service:ContentDirectory:1";
static const char UPNP_URN_CMS_1[] = "urn:schemas-upnp-org:service:ConnectionManager:1";
static const char UPNP_URN_AVT_1[] = "urn:schemas-upnp-org:service:AVTransport:1";
static const char UPNP_URN_RCS_1[] = "urn:schemas-upnp-org:service:RenderingControl:1";

int UPNP_UTIL_CreateUUID(char* uuid, int uuidSize, unsigned short deviceType, unsigned short uniqueID, unsigned short value);

int UPNP_UTIL_GetUserAgent(char* ua, int uaSize);

#ifdef __cplusplus
}
#endif

#endif
