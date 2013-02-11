#ifndef __MULTI_PLATFORM_INCLUDE_H__
#define __MULTI_PLATFORM_INCLUDE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32)
#include <Windows.h>
#include <Objbase.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#include <process.h>

#elif defined(__APPLE__)
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <pthread.h>

#define SOCKET int

#else
//Linuxån
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SOCKET int
#endif


#ifdef __cplusplus
}
#endif

#endif
