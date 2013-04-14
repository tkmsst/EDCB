#ifndef __MESSAGE_UTIL_H__
#define __MESSAGE_UTIL_H__

//キーを元にStringを取得する
const wchar_t* GetMessageString(const wchar_t* resourceKey);

//録画終了ステータスのメッセージを取得
const wchar_t* GetRecStatusString(DWORD recStatus, SYSTEMTIME startRecEpg);

#endif
