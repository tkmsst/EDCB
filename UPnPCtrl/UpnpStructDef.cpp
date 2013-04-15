#include "stdafx.h"

#include "MPInclude.h"
#include "UpnpStructDef.h"

UPNP_MSEARCH_REQUEST_INFO* UPNP_MSEARCH_REQUEST_INFO_New()
{
	UPNP_MSEARCH_REQUEST_INFO* item = NULL;

	item = (UPNP_MSEARCH_REQUEST_INFO*)malloc(sizeof(UPNP_MSEARCH_REQUEST_INFO));
	if( item != NULL ){
		item->res = NULL;
		item->host = NULL;
		item->man = NULL;
		item->mx = NULL;
		item->st = NULL;
		item->userAgent = NULL;
	}
	return item;
}

void UPNP_MSEARCH_REQUEST_INFO_Delete(void* item)
{
	UPNP_MSEARCH_REQUEST_INFO* info = (UPNP_MSEARCH_REQUEST_INFO*)item;
	if( info == NULL ){
		return ;
	}

	if( info->res != NULL ){
		free(info->res);
	}
	if( info->host != NULL ){
		free(info->host);
	}
	if( info->man != NULL ){
		free(info->man);
	}
	if( info->mx != NULL ){
		free(info->mx);
	}
	if( info->st != NULL ){
		free(info->st);
	}
	if( info->userAgent != NULL ){
		free(info->userAgent);
	}
	free(item);
}

UPNP_MSEARCH_REQUEST_INFO* UPNP_MSEARCH_REQUEST_INFO_Clone(UPNP_MSEARCH_REQUEST_INFO* src)
	{
	UPNP_MSEARCH_REQUEST_INFO* dest = UPNP_MSEARCH_REQUEST_INFO_New();
	if( dest != NULL ){
		if( src->res != NULL ){
			dest->res = (char*)malloc(strlen(src->res)+1);
#ifdef _WIN32
			strcpy_s(dest->res, strlen(src->res)+1, src->res);
#else
			strcpy(dest->res, src->res);
#endif
		}
		if( src->host != NULL ){
			dest->host = (char*)malloc(strlen(src->host)+1);
#ifdef _WIN32
			strcpy_s(dest->host, strlen(src->host)+1, src->host);
#else
			strcpy(dest->host, src->host);
#endif
		}
		if( src->man != NULL ){
			dest->man = (char*)malloc(strlen(src->man)+1);
#ifdef _WIN32
			strcpy_s(dest->man, strlen(src->man)+1, src->man);
#else
			strcpy(dest->man, src->man);
#endif
		}
		if( src->mx != NULL ){
			dest->mx = (char*)malloc(strlen(src->mx)+1);
#ifdef _WIN32
			strcpy_s(dest->mx, strlen(src->mx)+1, src->mx);
#else
			strcpy(dest->mx, src->mx);
#endif
		}
		if( src->st != NULL ){
			dest->st = (char*)malloc(strlen(src->st)+1);
#ifdef _WIN32
			strcpy_s(dest->st, strlen(src->st)+1, src->st);
#else
			strcpy(dest->st, src->st);
#endif
		}
		if( src->userAgent != NULL ){
			dest->userAgent = (char*)malloc(strlen(src->userAgent)+1);
#ifdef _WIN32
			strcpy_s(dest->userAgent, strlen(src->userAgent)+1, src->userAgent);
#else
			strcpy(dest->userAgent, src->userAgent);
#endif
		}

	}

	return dest;
}

UPNP_MSEARCH_RES_DEV_INFO* UPNP_MSEARCH_RES_DEV_INFO_New()
{
	UPNP_MSEARCH_RES_DEV_INFO* item = NULL;

	item = (UPNP_MSEARCH_RES_DEV_INFO*)malloc(sizeof(UPNP_MSEARCH_RES_DEV_INFO));
	if( item != NULL ){
		item->uuid = NULL;
		item->max_age = 0;
		item->port = 0;
		item->uri = NULL;
		item->server = NULL;
		item->usn = NULL;
	}
	return item;
}

void UPNP_MSEARCH_RES_DEV_INFO_Delete(void* item)
{
	UPNP_MSEARCH_RES_DEV_INFO* info = (UPNP_MSEARCH_RES_DEV_INFO*)item;
	if( info == NULL ){
		return ;
	}

	if( info->uuid != NULL ){
		free(info->uuid);
	}
	if( info->uri != NULL ){
		free(info->uri);
	}
	if( info->server != NULL ){
		free(info->server);
	}
	if( info->usn != NULL ){
		free(info->usn);
	}
	free(item);
}

UPNP_MSEARCH_RES_DEV_INFO* UPNP_MSEARCH_RES_DEV_INFO_Clone(UPNP_MSEARCH_RES_DEV_INFO* src)
{
	UPNP_MSEARCH_RES_DEV_INFO* dest = UPNP_MSEARCH_RES_DEV_INFO_New();
	if( dest != NULL ){
		if( src->uuid != NULL ){
			dest->uuid = (char*)malloc(strlen(src->uuid)+1);
#ifdef _WIN32
			strcpy_s(dest->uuid, strlen(src->uuid)+1, src->uuid);
#else
			strcpy(dest->uuid, src->uuid);
#endif
		}
		if( src->uri != NULL ){
			dest->uri = (char*)malloc(strlen(src->uri)+1);
#ifdef _WIN32
			strcpy_s(dest->uri, strlen(src->uri)+1, src->uri);
#else
			strcpy(dest->uri, src->uri);
#endif
		}

		dest->max_age = src->max_age;
		dest->port = src->port;

		if( src->server != NULL ){
			dest->server = (char*)malloc(strlen(src->server)+1);
#ifdef _WIN32
			strcpy_s(dest->server, strlen(src->server)+1, src->server);
#else
			strcpy(dest->server, src->server);
#endif
		}
		if( src->usn != NULL ){
			dest->usn = (char*)malloc(strlen(src->usn)+1);
#ifdef _WIN32
			strcpy_s(dest->usn, strlen(src->usn)+1, src->usn);
#else
			strcpy(dest->usn, src->usn);
#endif
		}
	}

	return dest;
}

UPNP_MSEARCH_RESPONSE_INFO* UPNP_MSEARCH_RESPONSE_INFO_New()
{
	UPNP_MSEARCH_RESPONSE_INFO* item = NULL;

	item = (UPNP_MSEARCH_RESPONSE_INFO*)malloc(sizeof(UPNP_MSEARCH_RESPONSE_INFO));
	if( item != NULL ){
		item->uuid = NULL;
		item->res = NULL;
		item->max_age = 0;
		item->date = NULL;
		item->location = NULL;
		item->server = NULL;
		item->st = NULL;
		item->usn = NULL;
	}
	return item;
}

void UPNP_MSEARCH_INFO_Delete(void* item)
{
	UPNP_MSEARCH_RESPONSE_INFO* info = (UPNP_MSEARCH_RESPONSE_INFO*)item;
	if( info == NULL ){
		return ;
	}

	if( info->uuid != NULL ){
		free(info->uuid);
	}
	if( info->res != NULL ){
		free(info->res);
	}
	if( info->date != NULL ){
		free(info->date);
	}
	if( info->location != NULL ){
		free(info->location);
	}
	if( info->server != NULL ){
		free(info->server);
	}
	if( info->st != NULL ){
		free(info->st);
	}
	if( info->usn != NULL ){
		free(info->usn);
	}
	free(item);
}

UPNP_MSEARCH_RESPONSE_INFO* UPNP_MSEARCH_INFO_Clone(UPNP_MSEARCH_RESPONSE_INFO* src)
{
	UPNP_MSEARCH_RESPONSE_INFO* dest = UPNP_MSEARCH_RESPONSE_INFO_New();
	if( dest != NULL ){
		if( src->uuid != NULL ){
			dest->uuid = (char*)malloc(strlen(src->uuid)+1);
#ifdef _WIN32
			strcpy_s(dest->uuid, strlen(src->uuid)+1, src->uuid);
#else
			strcpy(dest->uuid, src->uuid);
#endif
		}
		if( src->res != NULL ){
			dest->res = (char*)malloc(strlen(src->res)+1);
#ifdef _WIN32
			strcpy_s(dest->res, strlen(src->res)+1, src->res);
#else
			strcpy(dest->res, src->res);
#endif
		}
		if( src->date != NULL ){
			dest->date = (char*)malloc(strlen(src->date)+1);
#ifdef _WIN32
			strcpy_s(dest->date, strlen(src->date)+1, src->date);
#else
			strcpy(dest->date, src->date);
#endif
		}
		dest->max_age = src->max_age;
		if( src->location != NULL ){
			dest->location = (char*)malloc(strlen(src->location)+1);
#ifdef _WIN32
			strcpy_s(dest->location, strlen(src->location)+1, src->location);
#else
			strcpy(dest->location, src->location);
#endif
		}
		if( src->server != NULL ){
			dest->server = (char*)malloc(strlen(src->server)+1);
#ifdef _WIN32
			strcpy_s(dest->server, strlen(src->server)+1, src->server);
#else
			strcpy(dest->server, src->server);
#endif
		}
		if( src->st != NULL ){
			dest->st = (char*)malloc(strlen(src->st)+1);
#ifdef _WIN32
			strcpy_s(dest->st, strlen(src->st)+1, src->st);
#else
			strcpy(dest->st, src->st);
#endif
		}
		if( src->usn != NULL ){
			dest->usn = (char*)malloc(strlen(src->usn)+1);
#ifdef _WIN32
			strcpy_s(dest->usn, strlen(src->usn)+1, src->usn);
#else
			strcpy(dest->usn, src->usn);
#endif
		}
	}

	return dest;
}

UPNP_SSDP_NOTIFY_INFO* UPNP_SSDP_NOTIFY_INFO_New()
{
	UPNP_SSDP_NOTIFY_INFO* item = NULL;

	item = (UPNP_SSDP_NOTIFY_INFO*)malloc(sizeof(UPNP_SSDP_NOTIFY_INFO));
	if( item != NULL ){
		item->res = NULL;
		item->host = NULL;
		item->max_age = 0;
		item->location = NULL;
		item->nt = NULL;
		item->nts = NULL;
		item->server = NULL;
		item->usn = NULL;
	}
	return item;
}

void UPNP_SSDP_NOTIFY_INFO_Delete(void* item)
{
	UPNP_SSDP_NOTIFY_INFO* info = (UPNP_SSDP_NOTIFY_INFO*)item;
	if( info == NULL ){
		return ;
	}

	if( info->res != NULL ){
		free(info->res);
	}
	if( info->host != NULL ){
		free(info->host);
	}
	if( info->location != NULL ){
		free(info->location);
	}
	if( info->nt != NULL ){
		free(info->nt);
	}
	if( info->nts != NULL ){
		free(info->nts);
	}
	if( info->server != NULL ){
		free(info->server);
	}
	if( info->usn != NULL ){
		free(info->usn);
	}
	free(item);
}

UPNP_SSDP_NOTIFY_INFO* UPNP_SSDP_NOTIFY_INFO_Clone(UPNP_SSDP_NOTIFY_INFO* src)
{
	UPNP_SSDP_NOTIFY_INFO* dest = UPNP_SSDP_NOTIFY_INFO_New();
	if( dest != NULL ){
		if( src->res != NULL ){
			dest->res = (char*)malloc(strlen(src->res)+1);
#ifdef _WIN32
			strcpy_s(dest->res, strlen(src->res)+1, src->res);
#else
			strcpy(dest->res, src->res);
#endif
		}
		if( src->host != NULL ){
			dest->host = (char*)malloc(strlen(src->host)+1);
#ifdef _WIN32
			strcpy_s(dest->host, strlen(src->host)+1, src->host);
#else
			strcpy(dest->host, src->host);
#endif
		}
		dest->max_age = src->max_age;
		if( src->location != NULL ){
			dest->location = (char*)malloc(strlen(src->location)+1);
#ifdef _WIN32
			strcpy_s(dest->location, strlen(src->location)+1, src->location);
#else
			strcpy(dest->location, src->location);
#endif
		}
		if( src->nt != NULL ){
			dest->nt = (char*)malloc(strlen(src->nt)+1);
#ifdef _WIN32
			strcpy_s(dest->nt, strlen(src->nt)+1, src->nt);
#else
			strcpy(dest->nt, src->nt);
#endif
		}
		if( src->nts != NULL ){
			dest->nts = (char*)malloc(strlen(src->nts)+1);
#ifdef _WIN32
			strcpy_s(dest->nts, strlen(src->nts)+1, src->nts);
#else
			strcpy(dest->nts, src->nts);
#endif
		}
		if( src->server != NULL ){
			dest->server = (char*)malloc(strlen(src->server)+1);
#ifdef _WIN32
			strcpy_s(dest->server, strlen(src->server)+1, src->server);
#else
			strcpy(dest->server, src->server);
#endif
		}
		if( src->usn != NULL ){
			dest->usn = (char*)malloc(strlen(src->usn)+1);
#ifdef _WIN32
			strcpy_s(dest->usn, strlen(src->usn)+1, src->usn);
#else
			strcpy(dest->usn, src->usn);
#endif
		}
	}

	return dest;
}
