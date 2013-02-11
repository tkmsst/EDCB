#pragma once

#include "../../Common/Util.h"
#include "ReserveInfo.h"

class CCheckRecFile
{
public:
	CCheckRecFile(void);
	~CCheckRecFile(void);

	void SetCheckFolder(vector<wstring>* chkFolder);
	void SetDeleteExt(vector<wstring>* delExt);

	void CheckFreeSpace(map<DWORD, CReserveInfo*>* chkReserve, wstring defRecFolder, map<wstring, wstring>* protectFile);
	void CheckFreeSpaceLive(RESERVE_DATA* reserve, wstring recFolder, map<wstring, wstring>* protectFile);
	
protected:
	vector<wstring> chkFolder;
	vector<wstring> delExt;

	typedef struct _TS_FILE_INFO{
		LONGLONG fileSize;
		LONGLONG fileTime;
		wstring filePath;
	}TS_FILE_INFO;

	typedef struct _MOUNT_PATH_INFO{
		LONGLONG totalSize;
		vector<wstring> folderPath;
	}MOUNT_PATH_INFO;

protected:
	void FindTsFileList(wstring findFolder, map<LONGLONG, TS_FILE_INFO>* findList);
};

