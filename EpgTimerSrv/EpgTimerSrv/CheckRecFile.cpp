#include "StdAfx.h"
#include "CheckRecFile.h"

#include "../../Common/PathUtil.h"

CCheckRecFile::CCheckRecFile(void)
{
}


CCheckRecFile::~CCheckRecFile(void)
{
}

void CCheckRecFile::SetCheckFolder(vector<wstring>* chkFolder)
{
	this->chkFolder = *chkFolder;
}

void CCheckRecFile::SetDeleteExt(vector<wstring>* delExt)
{
	this->delExt = *delExt;
}

void CCheckRecFile::CheckFreeSpace(map<DWORD, CReserveInfo*>* chkReserve, wstring defRecFolder, map<wstring, wstring>* protectFile)
{
	if( this->chkFolder.size() == 0 || chkReserve == NULL || defRecFolder.size() == 0 ){
		return;
	}

	map<wstring, ULONGLONG> checkMap;
	map<wstring, MOUNT_PATH_INFO> mountMap;
	for( size_t i=0; i<this->chkFolder.size(); i++ ){
		wstring folder = this->chkFolder[i];
		transform(folder.begin(), folder.end(), folder.begin(), toupper);
		ChkFolderPath(folder);
		checkMap.insert(pair<wstring, ULONGLONG>(folder, 0));

		wstring mountPath = L"";
		GetChkDrivePath(folder, mountPath);
		transform(mountPath.begin(), mountPath.end(), mountPath.begin(), toupper);
		ChkFolderPath(mountPath);

		map<wstring, MOUNT_PATH_INFO>::iterator itr;
		itr = mountMap.find(mountPath);
		if( itr != mountMap.end() ){
			itr->second.folderPath.push_back(folder);
		}else{
			MOUNT_PATH_INFO item;
			item.totalSize = 0;
			item.folderPath.push_back(folder);
			mountMap.insert(pair<wstring, MOUNT_PATH_INFO>(mountPath, item));
		}
	}

	LONGLONG now = GetNowI64Time();
	map<DWORD, CReserveInfo*>::iterator itrRes;
	for( itrRes = chkReserve->begin(); itrRes != chkReserve->end(); itrRes++ ){
		wstring chkFolder = defRecFolder;
		RESERVE_DATA data;
		itrRes->second->GetData(&data);
		if( data.recSetting.recMode == RECMODE_NO || data.recSetting.recMode == RECMODE_VIEW ){
			continue;
		}
		if( now + 2*60*60*I64_1SEC < ConvertI64Time(data.startTime) ){
			//2時間以上先
			continue;
		}
		if( ConvertI64Time(data.startTime) < now ){
			//録画中
			continue;
		}
		if( data.recSetting.recFolderList.size() > 0 ){
			//複数指定あり
			for( size_t i=0; i< data.recSetting.recFolderList.size(); i++ ){
				chkFolder = data.recSetting.recFolderList[i].recFolder;

				transform(chkFolder.begin(), chkFolder.end(), chkFolder.begin(), toupper);
				ChkFolderPath(chkFolder);

				map<wstring, ULONGLONG>::iterator itr;
				itr = checkMap.find(chkFolder);
				if( itr != checkMap.end() ){
					DWORD bitrate = 0;
					_GetBitrate(data.originalNetworkID, data.transportStreamID, data.serviceID, &bitrate);
					itr->second += ((ULONGLONG)(bitrate/8)*1000) * data.durationSecond;
				}

				wstring mountPath = L"";
				GetChkDrivePath(chkFolder, mountPath);
				transform(mountPath.begin(), mountPath.end(), mountPath.begin(), toupper);
				ChkFolderPath(mountPath);

				map<wstring, MOUNT_PATH_INFO>::iterator itrMount;
				itrMount = mountMap.find(mountPath);
				if( itrMount != mountMap.end() ){
					DWORD bitrate = 0;
					_GetBitrate(data.originalNetworkID, data.transportStreamID, data.serviceID, &bitrate);
					itrMount->second.totalSize += ((ULONGLONG)(bitrate/8)*1000) * data.durationSecond;
				}
			}
		}else{
			//デフォルト
			transform(chkFolder.begin(), chkFolder.end(), chkFolder.begin(), toupper);
			ChkFolderPath(chkFolder);

			map<wstring, ULONGLONG>::iterator itr;
			itr = checkMap.find(chkFolder);
			if( itr != checkMap.end() ){
				DWORD bitrate = 0;
				_GetBitrate(data.originalNetworkID, data.transportStreamID, data.serviceID, &bitrate);
				itr->second += ((ULONGLONG)(bitrate/8)*1000) * data.durationSecond;
			}

			wstring mountPath = L"";
			GetChkDrivePath(chkFolder, mountPath);
			transform(mountPath.begin(), mountPath.end(), mountPath.begin(), toupper);
			ChkFolderPath(mountPath);

			map<wstring, MOUNT_PATH_INFO>::iterator itrMount;
			itrMount = mountMap.find(mountPath);
			if( itrMount != mountMap.end() ){
				DWORD bitrate = 0;
				_GetBitrate(data.originalNetworkID, data.transportStreamID, data.serviceID, &bitrate);
				itrMount->second.totalSize += ((ULONGLONG)(bitrate/8)*1000) * data.durationSecond;
			}

		}
	}

	//ドライブレベルでのチェック
	map<wstring, MOUNT_PATH_INFO>::iterator itrMount;
	for( itrMount = mountMap.begin(); itrMount != mountMap.end(); itrMount++ ){
		if( itrMount->second.totalSize > 0 ){
			ULARGE_INTEGER freeBytesAvailable;
			ULARGE_INTEGER totalNumberOfBytes;
			ULARGE_INTEGER totalNumberOfFreeBytes;
			if( _GetDiskFreeSpaceEx(itrMount->first.c_str(), &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes ) == TRUE ){
				ULONGLONG free = freeBytesAvailable.QuadPart;
				if( free > (ULONGLONG)itrMount->second.totalSize ){
					continue;
				}
				map<LONGLONG, TS_FILE_INFO> tsFileList;
				for( size_t i=0; i<itrMount->second.folderPath.size(); i++ ){
					FindTsFileList(itrMount->second.folderPath[i], &tsFileList);
				}
				while( free < (ULONGLONG)itrMount->second.totalSize ){
					map<LONGLONG, TS_FILE_INFO>::iterator itrTS;
					itrTS = tsFileList.begin();
					if( itrTS != tsFileList.end() ){
						BOOL noDel = FALSE;
						map<wstring, wstring>::iterator itrP;
						itrP = protectFile->find(itrTS->second.filePath);
						if( itrP != protectFile->end() ){
							noDel = TRUE;
						}
						if( noDel == FALSE ){
							DeleteFile( itrTS->second.filePath.c_str() );

							_OutputDebugString(L"★Auto Delete2 : %s", itrTS->second.filePath.c_str());
							for( size_t i=0 ; i<this->delExt.size(); i++ ){
								wstring delFile = L"";
								wstring delFileName = L"";
								GetFileFolder(itrTS->second.filePath, delFile);
								GetFileTitle(itrTS->second.filePath, delFileName);
								delFile += L"\\";
								delFile += delFileName;
								delFile += this->delExt[i];

								DeleteFile( delFile.c_str() );
								_OutputDebugString(L"★Auto Delete2 : %s", delFile.c_str());
							}

							free += itrTS->second.fileSize;
						}else{
							_OutputDebugString(L"★No Delete(Protected) : %s", itrTS->second.filePath.c_str());
						}
						tsFileList.erase(itrTS);
					}else{
						break;
					}
				}
			}
		}
	}
}

void CCheckRecFile::CheckFreeSpaceLive(RESERVE_DATA* reserve, wstring recFolder, map<wstring, wstring>* protectFile)
{
	if( this->chkFolder.size() == 0 || reserve == NULL || recFolder.size() == 0 ){
		return;
	}

	map<wstring, ULONGLONG> checkMap;
	for( size_t i=0; i<this->chkFolder.size(); i++ ){
		checkMap.insert(pair<wstring, ULONGLONG>(this->chkFolder[i], 0));
	}

	LONGLONG now = GetNowI64Time();

	if( reserve->recSetting.recMode == RECMODE_NO || reserve->recSetting.recMode == RECMODE_VIEW ){
		return;
	}

	map<wstring, ULONGLONG>::iterator itr;
	itr = checkMap.find(recFolder);
	if( itr != checkMap.end() ){
		//500MB空いてるかチェック
		itr->second = 500*1024*1024;

		ULARGE_INTEGER freeBytesAvailable;
		ULARGE_INTEGER totalNumberOfBytes;
		ULARGE_INTEGER totalNumberOfFreeBytes;
		if( _GetDiskFreeSpaceEx(itr->first.c_str(), &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes ) == TRUE ){
			ULONGLONG free = freeBytesAvailable.QuadPart;
			if( free > itr->second ){
				return;
			}
			map<LONGLONG, TS_FILE_INFO> tsFileList;
			FindTsFileList(itr->first, &tsFileList);
			while( free < itr->second ){
				map<LONGLONG, TS_FILE_INFO>::iterator itrTS;
				itrTS = tsFileList.begin();
				if( itrTS != tsFileList.end() ){
					BOOL noDel = FALSE;
					map<wstring, wstring>::iterator itrP;
					itrP = protectFile->find(itrTS->second.filePath);
					if( itrP != protectFile->end() ){
						noDel = TRUE;
					}
					if( noDel == FALSE ){
						DeleteFile( itrTS->second.filePath.c_str() );

						_OutputDebugString(L"★Auto Delete : %s", itrTS->second.filePath.c_str());
						for( size_t i=0 ; i<this->delExt.size(); i++ ){
							wstring delFile = L"";
							wstring delFileName = L"";
							GetFileFolder(itrTS->second.filePath, delFile);
							GetFileTitle(itrTS->second.filePath, delFileName);
							delFile += L"\\";
							delFile += delFileName;
							delFile += this->delExt[i];

							DeleteFile( delFile.c_str() );
							_OutputDebugString(L"★Auto Delete : %s", delFile.c_str());
						}

						free += itrTS->second.fileSize;
					}else{
						_OutputDebugString(L"★No Delete(Protected) : %s", itrTS->second.filePath.c_str());
					}
					tsFileList.erase(itrTS);
				}else{
					break;
				}
			}
		}
	}
}

void CCheckRecFile::FindTsFileList(wstring findFolder, map<LONGLONG, TS_FILE_INFO>* findList)
{
	wstring searchKey = findFolder;
	searchKey += L"\\*.ts";

	WIN32_FIND_DATA findData;
	HANDLE find;

	//指定フォルダのファイル一覧取得
	find = FindFirstFile( searchKey.c_str(), &findData);
	if ( find == INVALID_HANDLE_VALUE ) {
		return ;
	}
	do{
		if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
			// ディレクトリは対象外
			continue;
		}

		if (IsExt(findData.cFileName, L".ts") != TRUE) {
			// 拡張子 TS でなければ対象外
			continue;
		}
		
		TS_FILE_INFO item;

		Format(item.filePath, L"%s\\%s", findFolder.c_str(), findData.cFileName);
		transform(item.filePath.begin(), item.filePath.end(), item.filePath.begin(), toupper);
		
		item.fileTime = ((LONGLONG)(findData.ftCreationTime.dwHighDateTime))<<32 | findData.ftCreationTime.dwLowDateTime;
		item.fileSize = ((LONGLONG)(findData.nFileSizeHigh))<<32 | findData.nFileSizeLow;

		findList->insert(pair<LONGLONG, TS_FILE_INFO>(item.fileTime, item));
		
	}while(FindNextFile(find, &findData));

	FindClose(find);
}
