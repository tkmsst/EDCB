#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace CtrlCmdCLI{
namespace Def {
		/// <summary>
	/// 録画設定情報
	/// </summary>
	public ref class RecFileSetInfo{
	public:
		/// <summary>
		/// 録画フォルダパス
		/// </summary>
		property String^ RecFolder;

		/// <summary>
		/// 出力PlugIn
		/// </summary>
		property String^ WritePlugIn;

		/// <summary>
		/// ファイル名変換PlugIn
		/// </summary>
		property String^ RecNamePlugIn;

		/// <summary>
		/// ファイル名個別対応 録画開始処理時に内部で使用。予約情報としては必要なし
		/// </summary>
		property String^ RecFileName;
	public:
		RecFileSetInfo(void){
			RecFolder = gcnew String("");
			WritePlugIn = gcnew String("");
			RecNamePlugIn = gcnew String("");
			RecFileName = gcnew String("");
		};
	};


	/// <summary>
	/// 録画設定情報
	/// </summary>
	public ref class RecSettingData{
	public:
		/// <summary>
		/// 録画モード
		/// </summary>
		property Byte RecMode;
		
		/// <summary>
		/// 優先度
		/// </summary>
		property Byte Priority;

		/// <summary>
		/// 追従モード
		/// </summary>
		property Byte TuijyuuFlag;

		/// <summary>
		/// 指定サービスモード
		/// </summary>
		property UInt32 ServiceMode;

		/// <summary>
		/// ぴったり（？）録画モード
		/// </summary>
		property Byte PittariFlag;

		/// <summary>
		/// 録画後実行パッチファイルパス
		/// </summary>
		property String^ BatFilePath;

		/// <summary>
		/// 録画フォルダパス
		/// </summary>
		property List<RecFileSetInfo^>^ RecFolderList;

		/// <summary>
		/// 休止／スタンバイモード
		/// </summary>
		property Byte SuspendMode;

		/// <summary>
		/// 録画後再起動するかどうか
		/// </summary>
		property Byte RebootFlag;

		/// <summary>
		/// マージン設定が有効かどうか
		/// </summary>
		property Byte UseMargineFlag;

		/// <summary>
		/// 開始マージン
		/// </summary>
		property Int32 StartMargine;

		/// <summary>
		/// 終了マージン
		/// </summary>
		property Int32 EndMargine;

		/// <summary>
		/// 後続同一サービス時、同一ファイルで録画
		/// </summary>
		property Byte ContinueRecFlag;

		/// <summary>
		/// 物理CHに部分受信サービスがある場合、同時録画するかどうか
		/// </summary>
		property Byte PartialRecFlag;

		/// <summary>
		/// 強制的に使用Tunerを固定
		/// </summary>
		property UInt32 TunerID;

		/// <summary>
		/// 部分受信サービス録画のフォルダ
		/// </summary>
		property List<RecFileSetInfo^>^ PartialRecFolder;

	public:
		RecSettingData(void){
			RecMode = 0;
			Priority = 1;
			TuijyuuFlag = 1;
			ServiceMode  = 0;
			PittariFlag = 0;
			BatFilePath = gcnew String("");
			RecFolderList = gcnew List<RecFileSetInfo^>();
			SuspendMode = 0;
			RebootFlag = 0;
			UseMargineFlag = 0;
			StartMargine = 0;
			EndMargine = 0;
			ContinueRecFlag = 0;
			PartialRecFlag = 0;
			TunerID = 0;
			PartialRecFolder = gcnew List<RecFileSetInfo^>();
		};
	};

	/// <summary>
	/// 予約情報
	/// </summary>
	public ref class ReserveData{
	public:
		/// <summary>
		/// 番組名
		/// </summary>
		property String^ Title;

		/// <summary>
		/// 録画開始時間
		/// </summary>
		property DateTime StartTime;

		/// <summary>
		/// 録画総時間
		/// </summary>
		property UInt32 DurationSecond;

		/// <summary>
		/// サービス名
		/// </summary>
		property String^ StationName;

		/// <summary>
		/// OriginalNetworkID
		/// </summary>
		property UInt16 OriginalNetworkID;

		/// <summary>
		/// TransportStreamID
		/// </summary>
		property UInt16 TransportStreamID;

		/// <summary>
		/// ServiceID
		/// </summary>
		property UInt16 ServiceID;

		/// <summary>
		/// EventID
		/// </summary>
		property UInt16 EventID;

		/// <summary>
		/// コメント
		/// </summary>
		property String^ Comment;

		/// <summary>
		/// 予約ID
		/// </summary>
		property UInt32 ReserveID;

		/// <summary>
		/// 予約待機入った？
		/// </summary>
		property Byte RecWaitFlag;

		/// <summary>
		/// かぶり状態 1:かぶってチューナー足りない予約あり 2:チューナー足りなくて予約できない
		/// </summary>
		property Byte OverlapMode;

		/// <summary>
		/// 録画ファイルパス
		/// </summary>
		property String^ RecFilePath;

		/// <summary>
		/// 予約時の開始時間
		/// </summary>
		property DateTime StartTimeEpg;

		/// <summary>
		/// 録画設定
		/// </summary>
		property RecSettingData^ RecSetting;

		/// <summary>
		/// 予約追加状態
		/// </summary>
		property UInt32 ReserveStatus;

		/// <summary>
		/// 録画予定ファイル名
		/// </summary>
		property List<String^>^ RecFileNameList;

		/// <summary>
		/// 将来用
		/// </summary>
		property UInt32 param1;
	public:
		ReserveData(void){
			Title = gcnew String("");
//			StartTime = gcnew DateTime();
			DurationSecond = 0;
			StationName = gcnew String("");
			OriginalNetworkID = 0xFFFF;
			TransportStreamID = 0xFFFF;
			ServiceID = 0xFFFF;
			EventID = 0xFFFF;
			Comment = gcnew String("");
			ReserveID = 0;
			RecWaitFlag = 0;
			OverlapMode = 0;
			RecFilePath = gcnew String("");
//			StartTimeEpg = gcnew DateTime();
			RecSetting = gcnew RecSettingData();
			ReserveStatus = 0;
			RecFileNameList = gcnew List<String^>();
			param1 = 0;
		};
	};

	/// <summary>
	/// 録画済み情報
	/// </summary>
	public ref class RecFileInfo{
	public:
		/// <summary>
		/// 識別ID
		/// </summary>
		property UInt32 ID;

		/// <summary>
		/// 録画ファイルパス
		/// </summary>
		property String^ RecFilePath;

		/// <summary>
		/// 番組名
		/// </summary>
		property String^ Title;

		/// <summary>
		/// 録画開始時間
		/// </summary>
		property DateTime StartTime;

		/// <summary>
		/// 録画総時間
		/// </summary>
		property UInt32 DurationSecond;

		/// <summary>
		/// サービス名
		/// </summary>
		property String^ ServiceName;

		/// <summary>
		/// OriginalNetworkID
		/// </summary>
		property UInt16 OriginalNetworkID;

		/// <summary>
		/// TransportStreamID
		/// </summary>
		property UInt16 TransportStreamID;

		/// <summary>
		/// ServiceID
		/// </summary>
		property UInt16 ServiceID;

		/// <summary>
		/// EventID
		/// </summary>
		property UInt16 EventID;

		/// <summary>
		/// ドロップ数
		/// </summary>
		property UInt64 Drops;

		/// <summary>
		/// スクランブル数
		/// </summary>
		property UInt64 Scrambles;

		/// <summary>
		/// 録画結果のステータス
		/// </summary>
		property UInt32 RecStatus;

		/// <summary>
		/// 予約時の開始時間
		/// </summary>
		property DateTime StartTimeEpg;

		/// <summary>
		/// コメント
		/// </summary>
		property String^ Comment;

		/// <summary>
		/// .program.txtファイルの内容
		/// </summary>
		property String^ ProgramInfo;

		/// <summary>
		/// .errファイルの内容
		/// </summary>
		property String^ ErrInfo;

		/// <summary>
		/// プロテクトフラグ
		/// </summary>
		property bool ProtectFlag;

	public:
		RecFileInfo(void){
			ID = 0;
			RecFilePath = gcnew String("");
			Title = gcnew String("");
			DurationSecond = 0;
			ServiceName = gcnew String("");
			OriginalNetworkID = 0xFFFF;
			TransportStreamID = 0xFFFF;
			ServiceID = 0xFFFF;
			EventID = 0xFFFF;
			Drops = 0;
			Scrambles = 0;
			RecStatus = 0;
			Comment = gcnew String("");
			ProgramInfo = gcnew String("");
			ErrInfo = gcnew String("");
			ProtectFlag = false;
		};
	};

	/// <summary>
	/// EPG基本情報
	/// </summary>
	public ref class EpgShortEventInfo{
	public:
		/// <summary>
		/// イベント名
		/// </summary>
		property String^ event_name;

		/// <summary>
		/// 情報
		/// </summary>
		property String^ text_char;
	public:
		EpgShortEventInfo(void){
			event_name = gcnew String("");
			text_char = gcnew String("");
		};
	};

	/// <summary>
	/// EPG拡張情報
	/// </summary>
	public ref class EpgExtendedEventInfo{
	public:
		/// <summary>
		/// 詳細情報
		/// </summary>
		property String^ text_char;
	public:
		EpgExtendedEventInfo(void){
			text_char = gcnew String("");
		};
	};

	/// <summary>
	/// EPGジャンルデータ
	/// </summary>
	public ref class EpgContentData{
	public:
		/// <summary>
		/// ジャンル1
		/// </summary>
		property Byte content_nibble_level_1;
		/// <summary>
		/// ジャンル2
		/// </summary>
		property Byte content_nibble_level_2;
		/// <summary>
		/// ユーザジャンル
		/// </summary>
		property Byte user_nibble_1;
		/// <summary>
		/// ユーザジャンル
		/// </summary>
		property Byte user_nibble_2;
	public:
		EpgContentData(void){
			content_nibble_level_1 = 0;
			content_nibble_level_2 = 0;
			user_nibble_1 = 0;
			user_nibble_2 = 0;
		};
	};

	/// <summary>
	/// EPGジャンル情報
	/// </summary>
	public ref class EpgContentInfo{
	public:
		/// <summary>
		/// </summary>
		property List<EpgContentData^>^ nibbleList;
	public:
		EpgContentInfo(void){
			nibbleList = gcnew List<EpgContentData^>();
		};
	};

	/// <summary>
	/// EPG映像情報
	/// </summary>
	public ref class EpgComponentInfo{
	public:
		/// <summary>
		/// コンポーネント内容
		/// </summary>
		property Byte stream_content;
		/// <summary>
		/// コンポーネント種別
		/// </summary>
		property Byte component_type;
		/// <summary>
		/// コンポーネントタグ
		/// </summary>
		property Byte component_tag;
		/// <summary>
		/// コンポーネント記述
		/// </summary>
		property String^ text_char;
	public:
		EpgComponentInfo(void){
			stream_content = 0;
			component_type = 0;
			component_tag = 0;
			text_char = gcnew String("");
		};
	};

	/// <summary>
	/// EPG音声情報データ
	/// </summary>
	public ref class EpgAudioComponentInfoData{
	public:
		/// <summary>
		/// コンポーネント内容
		/// </summary>
		property Byte stream_content;
		/// <summary>
		/// コンポーネント種別
		/// </summary>
		property Byte component_type;
		/// <summary>
		/// コンポーネントタグ
		/// </summary>
		property Byte component_tag;
		/// <summary>
		/// ストリーム形式種別
		/// </summary>
		property Byte stream_type;
		/// <summary>
		/// サイマルキャストグループ識別
		/// </summary>
		property Byte simulcast_group_tag;
		/// <summary>
		/// ES 多言語フラグ
		/// </summary>
		property Byte ES_multi_lingual_flag;
		/// <summary>
		/// 主コンポーネントフラグ
		/// </summary>
		property Byte main_component_flag;
		/// <summary>
		/// 音質表示
		/// </summary>
		property Byte quality_indicator;
		/// <summary>
		/// サンプリング周波数
		/// </summary>
		property Byte sampling_rate;
		/// <summary>
		/// コンポーネント記述
		/// </summary>
		property String^ text_char;
	public:
		EpgAudioComponentInfoData(void){
			stream_content = 0;
			component_type = 0;
			component_tag = 0;
			stream_type = 0;
			simulcast_group_tag = 0;
			ES_multi_lingual_flag = 0;
			main_component_flag = 0;
			quality_indicator = 0;
			sampling_rate = 0;
			text_char = gcnew String("");
		};
	};

	/// <summary>
	/// EPG音声情報
	/// </summary>
	public ref class EpgAudioComponentInfo{
	public:
		/// <summary>
		/// </summary>
		property List<EpgAudioComponentInfoData^>^ componentList;
	public:
		EpgAudioComponentInfo(void){
			componentList = gcnew List<EpgAudioComponentInfoData^>();
		};
	};

	/// <summary>
	/// EPGイベントデータ
	/// </summary>
	public ref class EpgEventData{
	public:
		/// <summary>
		/// OriginalNetworkID
		/// </summary>
		property UInt16 original_network_id;
		/// <summary>
		///	TransportStreamID
		/// </summary>
		property UInt16 transport_stream_id;
		/// <summary>
		/// ServiceID
		/// </summary>
		property UInt16 service_id;
		/// <summary>
		/// EventID
		/// </summary>
		property UInt16 event_id;
	public:
		EpgEventData(void){
			original_network_id = 0xFFFF;
			transport_stream_id = 0xFFFF;
			service_id = 0xFFFF;
			event_id = 0xFFFF;
		};
	};

	/// <summary>
	/// EPGイベントグループ情報
	/// </summary>
	public ref class EpgEventGroupInfo{
	public:
		/// <summary>
		/// グループタイプ
		/// </summary>
		property Byte group_type;
		/// <summary>
		/// イベントデータ
		/// </summary>
		property List<EpgEventData^>^ eventDataList;
	public:
		EpgEventGroupInfo(void){
			group_type = 0;
			eventDataList = gcnew List<EpgEventData^>();
		};
	};

	/// <summary>
	/// EPGイベント情報
	/// </summary>
	public ref class EpgEventInfo{
	public:
		/// <summary>
		/// OriginalNetworkID
		/// </summary>
		property UInt16 original_network_id;
		/// <summary>
		///	TransportStreamID
		/// </summary>
		property UInt16 transport_stream_id;
		/// <summary>
		/// ServiceID
		/// </summary>
		property UInt16 service_id;
		/// <summary>
		/// EventID
		/// </summary>
		property UInt16 event_id;
		/// <summary>
		/// start_timeが有効かどうか
		/// </summary>
		property Byte StartTimeFlag;
		/// <summary>
		/// 開始時間
		/// </summary>
		property DateTime start_time;
		/// <summary>
		/// durationSecが有効かどうか
		/// </summary>
		property Byte DurationFlag;
		/// <summary>
		/// 総時間（単位：秒）
		/// </summary>
		property UInt32 durationSec;

		/// <summary>
		/// 基本情報
		/// </summary>
		property EpgShortEventInfo^ ShortInfo;
		/// <summary>
		/// 拡張情報
		/// </summary>
		property EpgExtendedEventInfo^ ExtInfo;
		/// <summary>
		/// ジャンル情報
		/// </summary>
		property EpgContentInfo^ ContentInfo;
		/// <summary>
		/// 映像情報
		/// </summary>
		property EpgComponentInfo^ ComponentInfo;
		/// <summary>
		/// 音声情報
		/// </summary>
		property EpgAudioComponentInfo^ AudioInfo;
		/// <summary>
		/// イベントグループ情報
		/// </summary>
		property EpgEventGroupInfo^ EventGroupInfo;
		/// <summary>
		/// イベントリレー情報
		/// </summary>
		property EpgEventGroupInfo^ EventRelayInfo;
		/// <summary>
		/// ノンスクランブルかどうか
		/// </summary>
		property Byte FreeCAFlag;

	public:
		EpgEventInfo(void){
			original_network_id = 0xFFFF;
			transport_stream_id = 0xFFFF;
			service_id = 0xFFFF;
			event_id = 0xFFFF;
			StartTimeFlag = 0;
//			start_time = gcnew DateTime();
			DurationFlag = 0;
			durationSec = 0;
			ShortInfo = nullptr;
			ExtInfo = nullptr;
			ContentInfo = nullptr;
			ComponentInfo = nullptr;
			AudioInfo = nullptr;
			EventGroupInfo = nullptr;
			EventRelayInfo = nullptr;
			FreeCAFlag = 0;
		};
	};

	/// <summary>
	/// EPGイベント情報
	/// </summary>
	public ref class EpgServiceInfo{
	public:
		/// <summary>
		/// OriginalNetworkID
		/// </summary>
		property UInt16 ONID;
		/// <summary>
		///	TransportStreamID
		/// </summary>
		property UInt16 TSID;
		/// <summary>
		/// ServiceID
		/// </summary>
		property UInt16 SID;
		/// <summary>
		/// ServiceType
		/// </summary>
		property BYTE service_type;
		/// <summary>
		/// 部分受信フラグ
		/// </summary>
		property BYTE partialReceptionFlag;
		/// <summary>
		/// ServiceProviderName
		/// </summary>
		property String^ service_provider_name;
		/// <summary>
		/// ServiceName
		/// </summary>
		property String^ service_name;
		/// <summary>
		/// NetworkName
		/// </summary>
		property String^ network_name;
		/// <summary>
		/// TsName
		/// </summary>
		property String^ ts_name;
		/// <summary>
		/// リモコンキーID
		/// </summary>
		property BYTE remote_control_key_id;

	public:
		EpgServiceInfo(void){
			ONID = 0xFFFF;
			TSID = 0xFFFF;
			SID = 0xFFFF;
			service_type = 0;
			partialReceptionFlag = 0;
			service_provider_name = gcnew String("");
			service_name = gcnew String("");
			network_name = gcnew String("");
			ts_name = gcnew String("");
			remote_control_key_id = 0;
		};
	};

	/// <summary>
	/// 検索キー情報
	/// </summary>
	public ref class EpgSearchDateInfo{
	public:
		/// <summary>
		/// 開始曜日
		/// </summary>
		property Byte startDayOfWeek;
		/// <summary>
		/// 開始時間
		/// </summary>
		property UInt16 startHour;
		/// <summary>
		/// 開始分
		/// </summary>
		property UInt16 startMin;
		/// <summary>
		/// 終了曜日
		/// </summary>
		property Byte endDayOfWeek;
		/// <summary>
		/// 終了時間
		/// </summary>
		property UInt16 endHour;
		/// <summary>
		/// 終了分
		/// </summary>
		property UInt16 endMin;
	public:
		EpgSearchDateInfo(void){
			startDayOfWeek = 0;
			startHour = 0;
			startMin = 0;
			endDayOfWeek = 0;
			endHour = 0;
			endMin = 0;
		};
	};

	/// <summary>
	/// 検索キー情報
	/// </summary>
	public ref class EpgSearchKeyInfo{
	public:
		/// <summary>
		/// Andキーワード
		/// </summary>
		property String^ andKey;
		/// <summary>
		/// Notキーワード
		/// </summary>
		property String^ notKey;
		/// <summary>
		/// 番組名のみ検索対象とする
		/// </summary>
		property Byte titleOnlyFlag;
		/// <summary>
		/// 正規表現モードで検索を行う
		/// </summary>
		property Byte regExpFlag;
		/// <summary>
		/// ジャンル絞り込み
		/// </summary>
		property List<EpgContentData^>^ contentList;
		/// <summary>
		/// 時間絞り込み
		/// </summary>
		property List<EpgSearchDateInfo^>^ dateList;
		/// <summary>
		/// 検索対象のサービス一覧
		/// </summary>
		property List<Int64>^ serviceList;
		/// <summary>
		/// 映像絞り込み
		/// </summary>
		property List<UInt16>^ videoList;
		/// <summary>
		/// 音声絞り込み
		/// </summary>
		property List<UInt16>^ audioList;
		/// <summary>
		/// あいまい検索を行う
		/// </summary>
		property Byte aimaiFlag;
		/// <summary>
		/// ジャンル絞り込みNOT扱い
		/// </summary>
		property Byte notContetFlag;
		/// <summary>
		/// 映像絞り込みNOT扱い
		/// </summary>
		property Byte notDateFlag;
		/// <summary>
		/// FreeCAモード
		/// </summary>
		property Byte freeCAFlag;
		/// <summary>
		/// 録画済かのチェックあり
		/// </summary>
		property Byte chkRecEnd;
		/// <summary>
		/// 録画済かのチェック対象期間
		/// </summary>
		property UInt16 chkRecDay;
	public:
		EpgSearchKeyInfo(void){
			andKey = gcnew String("");
			notKey = gcnew String("");
			titleOnlyFlag = 0;
			regExpFlag = 0;
			contentList = gcnew List<EpgContentData^>();
			dateList = gcnew List<EpgSearchDateInfo^>();
			serviceList = gcnew List<Int64>();
			videoList = gcnew List<UInt16>();
			audioList = gcnew List<UInt16>();
			aimaiFlag = 0;
			notContetFlag = 0;
			notDateFlag = 0;
			freeCAFlag = 0;
			chkRecEnd = 0;
			chkRecDay = 6;
		};
	};

	/// <summary>
	/// 自動予約登録情報
	/// </summary>
	public ref class EpgAutoAddData{
	public:
		/// <summary>
		/// ID
		/// </summary>
		property UInt32 dataID;
		/// <summary>
		/// 検索キー
		/// </summary>
		property EpgSearchKeyInfo^ searchInfo;
		/// <summary>
		/// 録画設定
		/// </summary>
		property RecSettingData^ recSetting;
		/// <summary>
		/// 予約登録数
		/// </summary>
		property UInt32 addCount;
	public:
		EpgAutoAddData(void){
			dataID = 0;
			searchInfo = gcnew EpgSearchKeyInfo();
			recSetting = gcnew RecSettingData();
			addCount = 0;
		};
	};

	/// <summary>
	/// 自動予約登録情報
	/// </summary>
	public ref class ManualAutoAddData{
	public:
		/// <summary>
		/// ID
		/// </summary>
		property UInt32 dataID;
		/// <summary>
		/// 対象曜日
		/// </summary>
		property Byte dayOfWeekFlag;
		/// <summary>
		/// 録画開始時間（00:00を0として秒単位）
		/// </summary>
		property UInt32 startTime;
		/// <summary>
		/// 録画総時間
		/// </summary>
		property UInt32 durationSecond;
		/// <summary>
		/// 番組名
		/// </summary>
		property String^ title;
		/// <summary>
		/// サービス名
		/// </summary>
		property String^ stationName;
		/// <summary>
		/// ONID
		/// </summary>
		property UInt16 originalNetworkID;
		/// <summary>
		/// TSID
		/// </summary>
		property UInt16 transportStreamID;
		/// <summary>
		/// SID
		/// </summary>
		property UInt16 serviceID;
		/// <summary>
		/// 録画設定
		/// </summary>
		property RecSettingData^ recSetting;
	public:
		ManualAutoAddData(void){
			dataID = 0;
			dayOfWeekFlag = 0;
			startTime = 0;
			durationSecond = 0;
			title = gcnew String("");
			stationName = gcnew String("");
			originalNetworkID = 0;
			transportStreamID = 0;
			serviceID = 0;

			recSetting = gcnew RecSettingData();
		};
	};

	/// <summary>
	/// チューナー予約情報
	/// </summary>
	public ref class TunerReserveInfo{
	public:
		/// <summary>
		/// ID
		/// </summary>
		property UInt32 tunerID;
		/// <summary>
		/// 検索キー
		/// </summary>
		property String^ tunerName;
		/// <summary>
		/// 録画設定
		/// </summary>
		property List<Int32>^ reserveList;
	public:
		TunerReserveInfo(void){
			tunerID = 0;
			tunerName = gcnew String("");
			reserveList = gcnew List<Int32>();
		};
	};

	/// <summary>
	/// 番組一覧情報
	/// </summary>
	public ref class EpgServiceEventInfo{
	public:
		/// <summary>
		/// サービス情報
		/// </summary>
		property EpgServiceInfo^ serviceInfo;
		/// <summary>
		/// 番組一覧
		/// </summary>
		property List<EpgEventInfo^>^ eventList;
	public:
		EpgServiceEventInfo(void){
			serviceInfo = gcnew EpgServiceInfo();
			eventList = gcnew List<EpgEventInfo^>();
		};
	};

	/// <summary>
	/// チャンネル変更情報
	/// </summary>
	public ref class SetChInfo{
	public:
		/// <summary>
		/// ONIDとTSIDとSIDの値が使用できるかどうか
		/// </summary>
		property UInt32 useSID;
		/// <summary>
		/// ONID
		/// </summary>
		property UInt16 ONID;
		/// <summary>
		/// TSID
		/// </summary>
		property UInt16 TSID;
		/// <summary>
		/// SID
		/// </summary>
		property UInt16 SID;
		/// <summary>
		/// SpaceとChの値が使用できるかどうか
		/// </summary>
		property UInt32 useBonCh;
		/// <summary>
		/// space
		/// </summary>
		property UInt32 space;
		/// <summary>
		/// ch
		/// </summary>
		property UInt32 ch;
	public:
		SetChInfo(void){
		};
	};

	/// <summary>
	/// TVTestのチャンネル切り替え用
	/// </summary>
	public ref class TvTestChChgInfo{
	public:
		/// <summary>
		/// サービス情報
		/// </summary>
		property String^ bonDriver;
		/// <summary>
		/// 番組一覧
		/// </summary>
		property Def::SetChInfo^ chInfo;
	public:
		TvTestChChgInfo(void){
			bonDriver = gcnew String("");
			chInfo = gcnew Def::SetChInfo();
		};
	};

	/// <summary>
	/// コンテンツ情報
	/// </summary>
	public ref class ContentKind{
	public:
		/// <summary>
		/// メインジャンル名称
		/// </summary>
		property String^ ContentName;
		/// <summary>
		/// サブジャンル名称
		/// </summary>
		property String^ SubName;
		/// <summary>
		/// メイン識別子
		/// </summary>
		property Byte Nibble1;
		/// <summary>
		/// サブ識別子
		/// </summary>
		property Byte Nibble2;
	public:
		ContentKind(void){
			ContentName = gcnew String("");
			SubName = gcnew String("");
			Nibble1 = 0;
			Nibble2 = 0;
		};
		ContentKind(String^ contentName, String^ subName, Byte nibble1, Byte nibble2){
			ContentName = contentName;
			SubName = subName;
			Nibble1 = nibble1;
			Nibble2 = nibble2;
		};
	};

	/// <summary>
	/// コンポーネント情報
	/// </summary>
	public ref class ComponentKind{
	public:
		/// <summary>
		/// 名称
		/// </summary>
		property String^ ComponentName;
		/// <summary>
		/// ストリーム識別子
		/// </summary>
		property Byte StreamContent;
		/// <summary>
		/// コンポーネント識別子
		/// </summary>
		property Byte ComponentType;
	public:
		ComponentKind(void){
			ComponentName = gcnew String("");
			StreamContent = 0;
			ComponentType = 0;
		};
		ComponentKind(Byte streamContent, Byte componentType, String^ componentName){
			ComponentName = componentName;
			StreamContent = streamContent;
			ComponentType = componentType;
		};
	};

	/// <summary>
	/// ストリーミング配信制御IDの情報
	/// </summary>
	public ref class TVTestStreamingInfo{
	public:
		/// <summary>
		/// 有効/無効
		/// </summary>
		property UInt32 enableMode;
		/// <summary>
		/// 制御ID
		/// </summary>
		property UInt32 ctrlID;
		/// <summary>
		/// サーバーIP
		/// </summary>
		property UInt32 serverIP;
		/// <summary>
		/// サーバー待ち受けポート
		/// </summary>
		property UInt32 serverPort;
		/// <summary>
		/// 再生ファイルパス
		/// </summary>
		property String^ filePath;
		/// <summary>
		/// UDP送信
		/// </summary>
		property UInt32 udpSend;
		/// <summary>
		/// TCP送信
		/// </summary>
		property UInt32 tcpSend;
		/// <summary>
		/// TCP送信
		/// </summary>
		property UInt32 timeShiftMode;
	public:
		TVTestStreamingInfo(void){
			filePath = gcnew String("");
		};
	};

	/// <summary>
	/// ストリーミング配信制御IDの情報
	/// </summary>
	public ref class NWPlayTimeShiftInfo{
	public:
		/// <summary>
		/// 制御ID
		/// </summary>
		property UInt32 ctrlID;
		/// <summary>
		/// 再生ファイルパス
		/// </summary>
		property String^ filePath;
	public:
		NWPlayTimeShiftInfo(void){
			filePath = gcnew String("");
		};
	};

	/// <summary>
	/// IEのProxy設定
	/// </summary>
	public ref class CurrentUserIEProxyConfig{
	public:
		/// <summary>
		/// 設定を自動的に検出するかどうか
		/// </summary>
		property UInt32 autoDetect;
		/// <summary>
		/// 自動構成スクリプトのURL
		/// </summary>
		property String^ autoConfigUrl;
		/// <summary>
		/// サーバー名（アドレス:ポート番号）
		/// </summary>
		property String^ proxy;
		/// <summary>
		/// Proxyの例外設定
		/// </summary>
		property String^ proxyBypass;
	public:
		CurrentUserIEProxyConfig(void){
			autoConfigUrl = gcnew String("");
			proxy = gcnew String("");
			proxyBypass = gcnew String("");
		};
	};

	/// <summary>
	/// Proxyの情報
	/// </summary>
	public ref class ProxyConfig{
	public:
		/// <summary>
		/// サーバー名（アドレス:ポート番号）
		/// </summary>
		property String^ proxy;
		/// <summary>
		/// Proxyの例外設定
		/// </summary>
		property String^ proxyBypass;
	public:
		ProxyConfig(void){
			proxy = gcnew String("");
			proxyBypass = gcnew String("");
		};
	};

	/// <summary>
	/// 接続時に使用するProxyの情報
	/// </summary>
	public ref class UseProxyInfo{
	public:
		/// <summary>
		/// サーバー名（アドレス:ポート番号）
		/// </summary>
		property String^ serverName;
		/// <summary>
		/// Proxyの例外設定
		/// </summary>
		property String^ proxyBypass;
		/// <summary>
		/// 認証Proxyユーザー名
		/// </summary>
		property String^ userName;
		/// <summary>
		/// 認証Proxyパスワード
		/// </summary>
		property String^ password;
	public:
		UseProxyInfo(void){
			serverName = gcnew String("");
			proxyBypass = gcnew String("");
			userName = gcnew String("");
			password = gcnew String("");
		};
	};

}
}
