// CtrlCmdCLI.h

#pragma once

#include "CtrlCmdCLIDef.h"
#include "../../Common/SendCtrlCmd.h"
#include "../../Common/twitterUtil.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CtrlCmdCLI {
	public ref class CtrlCmdUtil
	{
		// TODO: このクラスの、ユーザーのメソッドをここに追加してください。
	public:
		CtrlCmdUtil(void);
		~CtrlCmdUtil(void);
		!CtrlCmdUtil(void);

		void GetContentKindList(
			Dictionary<UInt16, Def::ContentKind^>^% list
			);
		void GetComponentKindList(
			Dictionary<UInt16, Def::ComponentKind^>^% list
			);

		/// <summary>
		/// コマンド送信方法の設定
		/// </summary>
        /// <param name="tcpFlag">[IN]true：TCP/IPモード、false：名前付きパイプモード</param>
		void SetSendMode(
			bool tcpFlag
			);

		/// <summary>
		/// 名前付きパイプモード時の接続先を設定
		/// </summary>
        /// <param name="eventName">[IN]排他制御用Eventの名前</param>
        /// <param name="pipeName">[IN]接続パイプの名前</param>
		void SetPipeSetting(
			String^ eventName,
			String^ pipeName
			);

		/// <summary>
		/// TCP/IPモード時の接続先を設定
		/// </summary>
        /// <param name="ip">[IN]接続先IP</param>
        /// <param name="port">[IN]接続先ポート</param>
		void SetNWSetting(
			String^ ip,
			UInt32 port
			);

		/// <summary>
		/// 接続処理時のタイムアウト設定
		/// </summary>
        /// <param name="timeOut">[IN]タイムアウト値（単位：ms）</param>
		void SetConnectTimeOut(
			UInt32 timeOut
			);

		/// <summary>
		/// Program.txtを追加で再読み込みする
		/// </summary>
		UInt32 SendAddloadReserve();

		/// <summary>
		/// EPGデータを再読み込みする
		/// </summary>
		UInt32 SendReloadEpg();

		/// <summary>
		/// 設定情報を再読み込みする
		/// </summary>
		UInt32 SendReloadSetting();

		/// <summary>
		/// EpgTimerSrv.exeを終了する
		/// </summary>
		UInt32 SendClose();

		/// <summary>
		/// EpgTimerSrv.exeのパイプ接続GUIとしてプロセスを登録する
		/// </summary>
        /// <param name="processID">[IN]プロセスID</param>
		UInt32 SendRegistGUI(
			UInt32 processID
			);

		/// <summary>
		/// EpgTimerSrv.exeのパイプ接続GUI登録を解除する
		/// </summary>
        /// <param name="processID">[IN]プロセスID</param>
		UInt32 SendUnRegistGUI(
			UInt32 processID
			);
		
		/// <summary>
		/// EpgTimerSrv.exeのTCP接続GUIとしてプロセスを登録する
		/// </summary>
        /// <param name="port">[IN]ポート</param>
		UInt32 SendRegistTCP(
			UInt32 port
			);

		/// <summary>
		/// EpgTimerSrv.exeのTCP接続GUI登録を解除する
		/// </summary>
        /// <param name="port">[IN]ポート</param>
		UInt32 SendUnRegistTCP(
			UInt32 port
			);

		/// <summary>
		/// 予約一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]予約一覧</param>
		UInt32 SendEnumReserve(
			List<Def::ReserveData^>^% val
			);

		/// <summary>
		/// 予約情報を取得する
		/// </summary>
        /// <param name="reserveID">[IN]取得する情報の予約ID</param>
        /// <param name="val">[OUT]予約情報</param>
		UInt32 SendGetReserve(
			UInt32 reserveID,
			Def::ReserveData^% val
			);

		/// <summary>
		/// 予約を追加する
		/// </summary>
        /// <param name="val">[IN]追加する予約一覧</param>
		UInt32 SendAddReserve(
			List<Def::ReserveData^>^ val
			);

		/// <summary>
		/// 予約を削除する
		/// </summary>
        /// <param name="val">[IN]削除する予約ID一覧</param>
		UInt32 SendDelReserve(
			List<UInt32>^ val
			);

		/// <summary>
		/// 予約を変更する
		/// </summary>
        /// <param name="val">[IN]変更する予約一覧</param>
		UInt32 SendChgReserve(
			List<Def::ReserveData^>^ val
			);

		/// <summary>
		/// チューナーごとの予約一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]予約情報</param>
		UInt32 SendEnumTunerReserve(
			List<Def::TunerReserveInfo^>^% val
			);

		/// <summary>
		/// 録画済み情報一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]録画済み情報一覧</param>
		UInt32 SendEnumRecInfo(
			List<Def::RecFileInfo^>^% val
			);

		/// <summary>
		/// 録画済み情報を削除する
		/// </summary>
        /// <param name="val">[IN]削除するID一覧</param>
		UInt32 SendDelRecInfo(
			List<UInt32>^ val
			);

		/// <summary>
		/// 録画済み情報のプロテクトを変更する
		/// </summary>
        /// <param name="val">[IN]録画済み情報一覧</param>
		UInt32 SendChgProtectRecInfo(
			List<Def::RecFileInfo^>^ val
			);

		/// <summary>
		/// サービス一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]サービス一覧</param>
		UInt32 SendEnumService(
			List<Def::EpgServiceInfo^>^% val
			);

		/// <summary>
		/// サービス指定で番組情報を一覧を取得する
		/// </summary>
        /// <param name="service">[IN]ONID＜＜32 | TSID＜＜16 | SIDとしたサービスID</param>
        /// <param name="val">[OUT]番組情報一覧</param>
		UInt32 SendEnumPgInfo(
			UInt64 service,
			List<Def::EpgEventInfo^>^% val
			);

		/// <summary>
		/// 指定イベントの番組情報を取得する
		/// </summary>
        /// <param name="pgID">[IN]ONID＜＜48 | TSID＜＜32 | SID＜＜16 | EventIDとしたID</param>
        /// <param name="val">[OUT]番組情報</param>
		UInt32 SendGetPgInfo(
			UInt64 pgID,
			Def::EpgEventInfo^% val
			);

		/// <summary>
		/// 指定イベントの番組情報を取得する
		/// </summary>
        /// <param name="key">[IN]検索キー（複数指定時はまとめて検索結果が返る）</param>
        /// <param name="val">[OUT]番組情報一覧</param>
		UInt32 SendSearchPg(
			List<Def::EpgSearchKeyInfo^>^ key,
			List<Def::EpgEventInfo^>^% val
			);

		/// <summary>
		/// スタンバイ、休止、シャットダウンを行っていいかの確認
		/// </summary>
		UInt32 SendChkSuspend(
			);

		/// <summary>
		/// スタンバイ、休止、シャットダウンに移行する
		/// </summary>
        /// <param name="val">[IN]1:スタンバイ 2:休止 3:シャットダウン | 0x0100:復帰後再起動</param>
		UInt32 SendSuspend(
			UInt16 val
			);

		/// <summary>
		/// PC再起動を行う
		/// </summary>
		UInt32 SendReboot(
			);

		/// <summary>
		/// 10秒後にEPGデータの取得を行う
		/// </summary>
		UInt32 SendEpgCapNow(
			);

		/// <summary>
		/// 自動予約登録条件一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]条件一覧</param>
		UInt32 SendEnumEpgAutoAdd(
			List<Def::EpgAutoAddData^>^% val
			);

		/// <summary>
		/// 自動予約登録条件を追加する
		/// </summary>
        /// <param name="val">[IN]条件一覧</param>
		UInt32 SendAddEpgAutoAdd(
			List<Def::EpgAutoAddData^>^ val
			);

		/// <summary>
		/// 自動予約登録条件を削除する
		/// </summary>
        /// <param name="val">[IN]ID一覧</param>
		UInt32 SendDelEpgAutoAdd(
			List<UInt32>^ val
			);

		/// <summary>
		/// 自動予約登録条件を変更する
		/// </summary>
        /// <param name="val">[IN]条件一覧</param>
		UInt32 SendChgEpgAutoAdd(
			List<Def::EpgAutoAddData^>^ val
			);

		/// <summary>
		/// 自動予約登録条件一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]条件一覧</param>
		UInt32 SendEnumManualAdd(
			List<Def::ManualAutoAddData^>^% val
			);

		/// <summary>
		/// 自動予約登録条件を追加する
		/// </summary>
        /// <param name="val">[IN]条件一覧</param>
		UInt32 SendAddManualAdd(
			List<Def::ManualAutoAddData^>^ val
			);

		/// <summary>
		/// 自動予約登録条件を削除する
		/// </summary>
        /// <param name="val">[IN]ID一覧</param>
		UInt32 SendDelManualAdd(
			List<UInt32>^ val
			);

		/// <summary>
		/// 自動予約登録条件を変更する
		/// </summary>
        /// <param name="val">[IN]条件一覧</param>
		UInt32 SendChgManualAdd(
			List<Def::ManualAutoAddData^>^ val
			);

		/// <summary>
		/// 指定ファイルを転送する
		/// </summary>
        /// <param name="val">[IN]ファイル名</param>
        /// <param name="resVal">[OUT]バイナリ</param>
		UInt32 SendFileCopy(
			String^ val,
			[Runtime::InteropServices::Out]array<byte>^% resVal
			);

		/// <summary>
		/// 番組情報一覧を取得する
		/// </summary>
        /// <param name="val">[OUT]番組情報一覧</param>
		UInt32 SendEnumPgAll(
			List<Def::EpgServiceEventInfo^>^% val
			);

		/// <summary>
		/// PlugInファイルの一覧を取得する
		/// </summary>
        /// <param name="val">[IN]1:ReName、2:Write</param>
        /// <param name="resVal">[OUT]ファイル一覧</param>
		UInt32 SendEnumPlugIn(
			UInt16 val,
			List<String^>^% resVal
			);

		/// <summary>
		/// TVTestのチャンネル切り替え用の情報を取得する
		/// </summary>
        /// <param name="val">[IN]ONID＜＜32 | TSID＜＜16 | SIDとしたサービスID</param>
        /// <param name="resVal">[OUT]チャンネル情報</param>
		UInt32 SendGetChgChTVTest(
			UInt64 val,
			Def::TvTestChChgInfo^% resVal
			);

		/// <summary>
		/// ネットワークモードのEpgDataCap_Bonのチャンネルを切り替え
		/// </summary>
        /// <param name="val">[IN]チャンネル情報</param>
		UInt32 SendNwTVSetCh(
			Def::SetChInfo^ val
			);

		/// <summary>
		/// ネットワークモードで起動中のEpgDataCap_Bonを終了
		/// </summary>
		UInt32 SendNwTVClose(
			);

		/// <summary>
		/// ネットワークモードで起動するときのモード
		/// </summary>
        /// <param name="val">[IN]モード（1:UDP 2:TCP 3:UDP+TCP）</param>
		UInt32 SendNwTVMode(
			UInt32 val
			);

		/// <summary>
		/// ストリーム配信用ファイルを開く
		/// </summary>
        /// <param name="val">[IN]開くファイルのサーバー側ファイルパス</param>
        /// <param name="resVal">[OUT]制御用CtrlID</param>
		UInt32 SendNwPlayOpen(
			String^ val,
			UInt32% resVal
			);

		/// <summary>
		/// ストリーム配信用ファイルをタイムシフトモードで開く
		/// </summary>
        /// <param name="val">[IN]予約ID</param>
        /// <param name="resVal">[OUT]制御用CtrlID</param>
		UInt32 SendNwTimeShiftOpen(
			UInt32 val,
			Def::NWPlayTimeShiftInfo^% resVal
			);

//View（TVTest）用

		/// <summary>
		/// BonDriverの切り替え
		/// </summary>
        /// <param name="val">[IN]BonDriverファイル名</param>
		UInt32 SendViewSetBonDrivere(
			String^ val
			);

		/// <summary>
		/// 使用中のBonDriverのファイル名を取得
		/// </summary>
        /// <param name="val">[OUT]BonDriverファイル名</param>
		UInt32 SendViewGetBonDrivere(
			String^% val
			);

		/// <summary>
		/// チャンネル切り替え
		/// </summary>
        /// <param name="val">[IN]チャンネル情報</param>
		UInt32 SendViewSetCh(
			Def::SetChInfo^ val
			);

		/// <summary>
		/// アプリケーションの終了
		/// </summary>
		UInt32 SendViewAppClose(
			);

		/// <summary>
		/// ストリーミング配信制御IDの設定
		/// </summary>
        /// <param name="val">[IN]ストリーミング配信制御情報</param>
		UInt32 SendViewSetStreamingInfo(
			Def::TVTestStreamingInfo^ val
			);

	private:
		CSendCtrlCmd* sendCmd;

	private:
		void CopyData(DateTime src, SYSTEMTIME* dest);
		DateTime ConvertTime(SYSTEMTIME* src);
		void CopyData(Def::ReserveData^ src, RESERVE_DATA* dest);
		void CopyData(RESERVE_DATA* src, Def::ReserveData^% dest);
		void CopyData(Def::RecSettingData^ src, REC_SETTING_DATA* dest);
		void CopyData(REC_SETTING_DATA* src, Def::RecSettingData^% dest);

		void CopyData(Def::EpgShortEventInfo^ src, EPGDB_SHORT_EVENT_INFO* dest);
		void CopyData(EPGDB_SHORT_EVENT_INFO* src, Def::EpgShortEventInfo^% dest);
		void CopyData(Def::EpgExtendedEventInfo^ src, EPGDB_EXTENDED_EVENT_INFO* dest);
		void CopyData(EPGDB_EXTENDED_EVENT_INFO* src, Def::EpgExtendedEventInfo^% dest);
		void CopyData(Def::EpgContentData^ src, EPGDB_CONTENT_DATA* dest);
		void CopyData(EPGDB_CONTENT_DATA* src, Def::EpgContentData^% dest);
		void CopyData(Def::EpgContentInfo^ src, EPGDB_CONTEN_INFO* dest);
		void CopyData(EPGDB_CONTEN_INFO* src, Def::EpgContentInfo^% dest);
		void CopyData(Def::EpgComponentInfo^ src, EPGDB_COMPONENT_INFO* dest);
		void CopyData(EPGDB_COMPONENT_INFO* src, Def::EpgComponentInfo^% dest);
		void CopyData(Def::EpgAudioComponentInfo^ src, EPGDB_AUDIO_COMPONENT_INFO* dest);
		void CopyData(EPGDB_AUDIO_COMPONENT_INFO* src, Def::EpgAudioComponentInfo^% dest);
		void CopyData(Def::EpgAudioComponentInfoData^ src, EPGDB_AUDIO_COMPONENT_INFO_DATA* dest);
		void CopyData(EPGDB_AUDIO_COMPONENT_INFO_DATA* src, Def::EpgAudioComponentInfoData^% dest);
		void CopyData(Def::EpgEventData^ src, EPGDB_EVENT_DATA* dest);
		void CopyData(EPGDB_EVENT_DATA* src, Def::EpgEventData^% dest);
		void CopyData(Def::EpgEventGroupInfo^ src, EPGDB_EVENTGROUP_INFO* dest);
		void CopyData(EPGDB_EVENTGROUP_INFO* src, Def::EpgEventGroupInfo^% dest);
		void CopyData(Def::EpgEventInfo^ src, EPGDB_EVENT_INFO* dest);
		void CopyData(EPGDB_EVENT_INFO* src, Def::EpgEventInfo^% dest);

		void CopyData(Def::EpgServiceInfo^ src, EPGDB_SERVICE_INFO* dest);
		void CopyData(EPGDB_SERVICE_INFO* src, Def::EpgServiceInfo^% dest);
		void CopyData(Def::EpgSearchDateInfo^ src, EPGDB_SEARCH_DATE_INFO* dest);
		void CopyData(EPGDB_SEARCH_DATE_INFO* src, Def::EpgSearchDateInfo^% dest);
		void CopyData(Def::EpgSearchKeyInfo^ src, EPGDB_SEARCH_KEY_INFO* dest);
		void CopyData(EPGDB_SEARCH_KEY_INFO* src, Def::EpgSearchKeyInfo^% dest);

		void CopyData(Def::RecFileInfo^ src, REC_FILE_INFO* dest);
		void CopyData(REC_FILE_INFO* src, Def::RecFileInfo^% dest);

		void CopyData(Def::EpgAutoAddData^ src, EPG_AUTO_ADD_DATA* dest);
		void CopyData(EPG_AUTO_ADD_DATA* src, Def::EpgAutoAddData^% dest);

		void CopyData(Def::ManualAutoAddData^ src, MANUAL_AUTO_ADD_DATA* dest);
		void CopyData(MANUAL_AUTO_ADD_DATA* src, Def::ManualAutoAddData^% dest);

		void CopyData(Def::TunerReserveInfo^ src, TUNER_RESERVE_INFO* dest);
		void CopyData(TUNER_RESERVE_INFO* src, Def::TunerReserveInfo^% dest);

		void CopyData(Def::EpgServiceEventInfo^ src, EPGDB_SERVICE_EVENT_INFO* dest);
		void CopyData(EPGDB_SERVICE_EVENT_INFO* src, Def::EpgServiceEventInfo^% dest);

		void CopyData(Def::SetChInfo^ src, SET_CH_INFO* dest);
		void CopyData(SET_CH_INFO* src, Def::SetChInfo^% dest);

		void CopyData(Def::TvTestChChgInfo^ src, TVTEST_CH_CHG_INFO* dest);
		void CopyData(TVTEST_CH_CHG_INFO* src, Def::TvTestChChgInfo^% dest);

		void CopyData(Def::TVTestStreamingInfo^ src, TVTEST_STREAMING_INFO* dest);
		void CopyData(TVTEST_STREAMING_INFO* src, Def::TVTestStreamingInfo^% dest);

		void CopyData(Def::NWPlayTimeShiftInfo^ src, NWPLAY_TIMESHIFT_INFO* dest);
		void CopyData(NWPLAY_TIMESHIFT_INFO* src, Def::NWPlayTimeShiftInfo^% dest);

	};

	public ref class TwitterPlugInUtil
	{
		// TODO: このクラスの、ユーザーのメソッドをここに追加してください。
	public:
		TwitterPlugInUtil(void);
		~TwitterPlugInUtil(void);
		!TwitterPlugInUtil(void);

		UInt32 Initialize();
		UInt32 UnInitialize();

		bool GetIEProxyConfig(
			Def::CurrentUserIEProxyConfig^% proxyConfig
			);

		bool GetProxyAutoDetect(
			Def::ProxyConfig^% proxyConfig
			);

		bool GetProxyAutoScript(
			String^ scriptURL,
			Def::ProxyConfig^% proxyConfig
			);

		void SetProxy(
			bool useProxy,
			Def::UseProxyInfo^ proxyInfo
			);

		bool GetAuthorizationUrl(
			String^% url
			);

		bool SetAuthorizationPWD(
			String^ password
			);

		bool SendTweet(
			bool asyncMode,
			String^ text
			);

	private:
		CTwitterUtil* util;

	private:
		void CopyData(Def::CurrentUserIEProxyConfig^ src, CURRENT_USER_IE_PROXY_CONFIG* dest);
		void CopyData(CURRENT_USER_IE_PROXY_CONFIG* src, Def::CurrentUserIEProxyConfig^% dest);
		void CopyData(Def::ProxyConfig^ src, PROXY_CONFIG* dest);
		void CopyData(PROXY_CONFIG* src, Def::ProxyConfig^% dest);
		void CopyData(Def::UseProxyInfo^ src, USE_PROXY_INFO* dest);
		void CopyData(USE_PROXY_INFO* src, Def::UseProxyInfo^% dest);
	};
}
