#include "stdafx.h"

#include "MPInclude.h"

#include "CharUtil.h"

void MP_STR_Trim(char* src)
{
	int count = 0;
	
	while(src[count] == ' '){
		count++;
	}
	if( strlen(src+count) <= 0 ){
		src[0] = '\0';
	}
	memmove(src, src+count, strlen(src+count));
	src[strlen(src+count)] = '\0';

	count = (int)strlen(src+count)-1;
	while(src[count] == ' ' && count >= 0){
		src[count] = '\0';
		count--;
	}
}

int MP_STR_CompNoCase(char* src1, char* src2)
{
#ifdef _WIN32
	return _stricmp(src1, src2);
#else
	return strcasecmp(src1, src2);
#endif
}

int MP_STR_Separate(char* src, char* key, char* left, int leftSize, char* right, int rightSize)
{
	char* pos = NULL;
	char* srcCopy = NULL;
	int leftLength = 0;
	int rightLength = 0;
	int srcLength = 0;

	if( src == NULL || key == NULL || left == NULL || right == NULL ){
		return -1;
	}
	if( strlen(key) <= 0 ){
		return -1;
	}

	srcCopy = (char*)malloc(strlen(src)+1);
	if( srcCopy == NULL ){
		return -1;
	}
#ifdef _WIN32
	strcpy_s(srcCopy, strlen(src)+1, src);
#else
	strcpy(srcCopy, src);
#endif
	srcLength = (int)strlen(srcCopy);

	pos = strstr(srcCopy, key);
	if( pos == NULL ){
#ifdef _WIN32
		strcpy_s(left, sizeof(left), srcCopy);
#else
		strcpy(left, srcCopy);
#endif
	}else{
		leftLength = (int)(pos-srcCopy);
		rightLength = srcLength-leftLength-(int)strlen(key);

		if( leftLength > 0 ){
#ifdef _WIN32
			strncpy_s(left, leftSize, srcCopy, leftLength);
#else
			strncpy(left, srcCopy, leftLength);
#endif
		}else{
			leftLength = 0;
			left[0] = '\0';
		}
		left[leftLength+1] = '\0';

		if( rightLength > 0 ){
#ifdef _WIN32
			strncpy_s(right, rightSize, pos+strlen(key), rightLength);
#else
			strncpy(right, pos+strlen(key), rightLength);
#endif
		}else{
			rightLength = 0;
			right[0] = '\0';
		}
		right[rightLength+1] = '\0';
	}

	free(srcCopy);

	return 1;
}

int MP_STR_Replace(char* src, char* dest, int* destSize, char* oldStr, char* newStr)
{
	char* pos = NULL;
	char* chkStart = NULL;
	char* destTemp = NULL;
	int destTempSize = 0;
	int oldStrSize = 0;
	int newStrSize = 0;
	int count = 0;
	int destPos = 0;
	int length = 0;

	if( src == NULL || destSize == NULL || oldStr == NULL || newStr == NULL ){
		return -1;
	}

	oldStrSize = (int)strlen(oldStr);
	newStrSize = (int)strlen(newStr);

	if( oldStrSize <= 0 ){
		return -2;
	}

	do{
		pos = strstr(pos, oldStr);
		if( pos != NULL ){
			pos+=oldStrSize;
			count++;
		}
	}while( pos != NULL );

	destTempSize = (int)strlen(src) + (newStrSize*count) - (oldStrSize*count) + 1;
	if( *destSize < destTempSize ){
		*destSize = destTempSize;
		return 2;
	}

	destTemp = (char*)malloc(destTempSize);
	memset(destTemp, 0, destTempSize);

	chkStart = src;
	do{
		pos = strstr(chkStart, oldStr);
		if( pos != NULL ){
			length = (int)(pos-chkStart);
#ifdef _WIN32
			strncpy_s(destTemp+destPos, destTempSize, chkStart, length);
#else
			strncpy(destTemp+destPos, chkStart, length);
#endif
			destPos+=length;
			if( newStrSize > 0 ){
#ifdef _WIN32
				strcat_s(destTemp, destTempSize, newStr);
#else
				strcat(destTemp, newStr);
#endif
				destPos+=newStrSize;
			}
			chkStart = pos+oldStrSize;

		}else{
#ifdef _WIN32
			strcat_s(destTemp, destTempSize, chkStart);
#else
			strcat(destTemp, chkStart);
#endif
		}
	}while( pos != NULL );

	return 1;
}

void MP_TIME_GetNowTime_RFC1123(char* time, int timeSize)
{
#ifdef _WIN32
	SYSTEMTIME now;
	char week[4] = "";
	char month[4] = "";

	if( time == NULL || timeSize < 30){
		return ;
	}
	GetSystemTime(&now);

	switch( now.wDayOfWeek ){
		case 0:
			strcpy_s(week, sizeof(week), "Sun");
			break;
		case 1:
			strcpy_s(week, sizeof(week), "Mon");
			break;
		case 2:
			strcpy_s(week, sizeof(week), "Tue");
			break;
		case 3:
			strcpy_s(week, sizeof(week), "Wed");
			break;
		case 4:
			strcpy_s(week, sizeof(week), "Thu");
			break;
		case 5:
			strcpy_s(week, sizeof(week), "Fri");
			break;
		case 6:
			strcpy_s(week, sizeof(week), "Sat");
			break;
		default:
			break;
	}

	switch( now.wMonth ){
		case 1:
			strcpy_s(month, sizeof(month), "Jan");
			break;
		case 2:
			strcpy_s(month, sizeof(month), "Feb");
			break;
		case 3:
			strcpy_s(month, sizeof(month), "Mar");
			break;
		case 4:
			strcpy_s(month, sizeof(month), "Apr");
			break;
		case 5:
			strcpy_s(month, sizeof(month), "May");
			break;
		case 6:
			strcpy_s(month, sizeof(month), "Jun");
			break;
		case 7:
			strcpy_s(month, sizeof(month), "Jul");
			break;
		case 8:
			strcpy_s(month, sizeof(month), "Aug");
			break;
		case 9:
			strcpy_s(month, sizeof(month), "Sep");
			break;
		case 10:
			strcpy_s(month, sizeof(month), "Oct");
			break;
		case 11:
			strcpy_s(month, sizeof(month), "Nov");
			break;
		case 12:
			strcpy_s(month, sizeof(month), "Dec");
			break;
		default:
			break;
	}

	sprintf_s(time, timeSize, "%s, %02d %s %04d %02d:%02d:%02d GMT",
		week, now.wDay, month, now.wYear, now.wHour, now.wMinute, now.wSecond);
#else
	struct tm *s_time;
	time_t now;
	char week[4] = "";
	char month[4] = "";

	if( time == NULL || timeSize < 30){
		return ;
	}

	time(&now);
	s_time=gmtime(&now);

	switch( s_time->tm_wday ){
		case 0:
			strcpy_s(week, sizeof(week), "Mon");
			break;
		case 1:
			strcpy_s(week, sizeof(week), "Tue");
			break;
		case 2:
			strcpy_s(week, sizeof(week), "Wed");
			break;
		case 3:
			strcpy_s(week, sizeof(week), "Thu");
			break;
		case 4:
			strcpy_s(week, sizeof(week), "Fri");
			break;
		case 5:
			strcpy_s(week, sizeof(week), "Sat");
			break;
		case 6:
			strcpy_s(week, sizeof(week), "Sun");
			break;
		default:
			break;
	}

	switch( s_time->tm_mon ){
		case 0:
			strcpy_s(month, sizeof(month), "Jan");
			break;
		case 1:
			strcpy_s(month, sizeof(month), "Feb");
			break;
		case 2:
			strcpy_s(month, sizeof(month), "Mar");
			break;
		case 3:
			strcpy_s(month, sizeof(month), "Apr");
			break;
		case 4:
			strcpy_s(month, sizeof(month), "May");
			break;
		case 5:
			strcpy_s(month, sizeof(month), "Jun");
			break;
		case 6:
			strcpy_s(month, sizeof(month), "Jul");
			break;
		case 7:
			strcpy_s(month, sizeof(month), "Aug");
			break;
		case 8:
			strcpy_s(month, sizeof(month), "Sep");
			break;
		case 9:
			strcpy_s(month, sizeof(month), "Oct");
			break;
		case 10:
			strcpy_s(month, sizeof(month), "Nov");
			break;
		case 11:
			strcpy_s(month, sizeof(month), "Dec");
			break;
		default:
			break;
	}

	sprintf_s(time, timeSize, "%s, %02d %s %04d %02d:%02d:%02d GMT",
		week, s_time->tm_mday, month, 1900+s_time->tm_year, s_time->tm_hour, s_time->tm_min, s_time->tm_sec);

#endif
}

