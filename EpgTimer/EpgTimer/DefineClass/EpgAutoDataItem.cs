using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    public class EpgAutoDataItem
    {
        public EpgAutoDataItem(EpgAutoAddData item)
        {
            this.EpgAutoAddInfo = item;
        }

        public EpgAutoAddData EpgAutoAddInfo
        {
            get;
            set;
        }

        public String AndKey
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.searchInfo.andKey;
                }
                return view;
            }
        }
        public String NotKey
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.searchInfo.notKey;
                }
                return view;
            }
        }
        public String RegExp
        {
            get
            {
                String view = "×";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.regExpFlag == 1)
                    {
                        view = "○";
                    }
                }
                return view;
            }
        }
        public String TitleOnly
        {
            get
            {
                String view = "×";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.titleOnlyFlag == 1)
                    {
                        view = "○";
                    }
                }
                return view;
            }
        }
        public String JyanruKey
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.contentList.Count == 1)
                    {
                        int nibble1 = EpgAutoAddInfo.searchInfo.contentList[0].content_nibble_level_1;
                        int nibble2 = EpgAutoAddInfo.searchInfo.contentList[0].content_nibble_level_2;

                        UInt16 contentKey1 = (UInt16)(nibble1 << 8 | 0xFF);
                        UInt16 contentKey2 = (UInt16)(nibble1 << 8 | nibble2);
                        if (nibble2 != 0xFF)
                        {
                            if (CommonManager.Instance.ContentKindDictionary.ContainsKey(contentKey1) == true)
                            {
                                view += CommonManager.Instance.ContentKindDictionary[contentKey1];
                            }
                            if (CommonManager.Instance.ContentKindDictionary.ContainsKey(contentKey2) == true)
                            {
                                view += " - " + CommonManager.Instance.ContentKindDictionary[contentKey2];
                            }
                        }
                        else
                        {
                            if (CommonManager.Instance.ContentKindDictionary.ContainsKey(contentKey1) == true)
                            {
                                view += CommonManager.Instance.ContentKindDictionary[contentKey1];
                            }
                        }
                    }
                    else if (EpgAutoAddInfo.searchInfo.contentList.Count > 1)
                    {
                        view = "複数指定";
                    }
                }
                else
                {
                    view = "なし";
                }
                return view;
            }
        }
        public String DateKey
        {
            get
            {
                String view = "なし";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.dateList.Count == 1)
                    {
                        EpgSearchDateInfo info = EpgAutoAddInfo.searchInfo.dateList[0];
                        view = CommonManager.Instance.DayOfWeekDictionary[info.startDayOfWeek] + " " + info.startHour.ToString("00") + ":" + info.startMin.ToString("00") +
                            " ～ " + CommonManager.Instance.DayOfWeekDictionary[info.endDayOfWeek] + " " + info.endHour.ToString("00") + ":" + info.endMin.ToString("00");
                    }
                    else if (EpgAutoAddInfo.searchInfo.dateList.Count > 1)
                    {
                        view = "複数指定";
                    }
                }
                return view;
            }
        }
        public String ServiceKey
        {
            get
            {
                String view = "なし";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.serviceList.Count == 1)
                    {
                        try
                        {
                            view = ChSet5.Instance.ChList[(ulong)EpgAutoAddInfo.searchInfo.serviceList[0]].ServiceName;
                        }
                        catch
                        {
                            view = "検索エラー";
                        }
                    }
                    else if (EpgAutoAddInfo.searchInfo.serviceList.Count > 1)
                    {
                        view = "複数指定";
                    }
                }
                return view;
            }
        }
        public String RecMode
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    switch (EpgAutoAddInfo.recSetting.RecMode)
                    {
                        case 0:
                            view = "全サービス";
                            break;
                        case 1:
                            view = "指定サービス";
                            break;
                        case 2:
                            view = "全サービス（デコード処理なし）";
                            break;
                        case 3:
                            view = "指定サービス（デコード処理なし）";
                            break;
                        case 4:
                            view = "視聴";
                            break;
                        case 5:
                            view = "無効";
                            break;
                        default:
                            break;
                    }
                }
                return view;
            }
        }
        public String Priority
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.recSetting.Priority.ToString();
                }
                return view;
            }
        }
        public String Tuijyu
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.recSetting.TuijyuuFlag == 0)
                    {
                        view = "しない";
                    }
                    else if (EpgAutoAddInfo.recSetting.TuijyuuFlag == 1)
                    {
                        view = "する";
                    }
                }
                return view;
            }
        }
        public String AddCount
        {
            get
            {
                String view = "0";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.addCount.ToString();
                }
                return view;
            }
        }
        public TextBlock ToolTipView
        {
            get
            {
                if (Settings.Instance.NoToolTip == true)
                {
                    return null;
                }
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo != null)
                    {
                        view += "検索条件\r\n";
                        view += "Andキーワード：" + AndKey + "\r\n";
                        view += "Notキーワード：" + NotKey + "\r\n";
                        view += "正規表現モード：" + RegExp + "\r\n";
                        view += "番組名のみ検索対象：" + TitleOnly + "\r\n";
                        view += "ジャンル絞り込み：" + JyanruKey + "\r\n";
                        view += "時間絞り込み：" + DateKey + "\r\n";
                        view += "検索対象サービス：" + ServiceKey + "\r\n";

                        view += "\r\n";
                    }
                    if (EpgAutoAddInfo.recSetting != null)
                    {
                        view += "録画設定\r\n";
                        view += "録画モード：" + RecMode + "\r\n";
                        view += "優先度：" + Priority + "\r\n";
                        view += "追従：" + Tuijyu + "\r\n";

                        if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x01) == 0)
                        {
                            view += "指定サービス対象データ : デフォルト\r\n";
                        }
                        else
                        {
                            view += "指定サービス対象データ : ";
                            if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x10) > 0)
                            {
                                view += "字幕含む ";
                            }
                            if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x20) > 0)
                            {
                                view += "データカルーセル含む";
                            }
                            view += "\r\n";
                        }

                        view += "録画実行bat : " + EpgAutoAddInfo.recSetting.BatFilePath + "\r\n";

                        if (EpgAutoAddInfo.recSetting.RecFolderList.Count == 0)
                        {
                            view += "録画フォルダ : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画フォルダ : \r\n";
                            foreach (RecFileSetInfo info in EpgAutoAddInfo.recSetting.RecFolderList)
                            {
                                view += info.RecFolder + " (WritePlugIn:" + info.WritePlugIn + ")\r\n";
                            }
                        }

                        if (EpgAutoAddInfo.recSetting.UseMargineFlag == 0)
                        {
                            view += "録画マージン : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画マージン : 開始 " + EpgAutoAddInfo.recSetting.StartMargine.ToString() +
                                " 終了 " + EpgAutoAddInfo.recSetting.EndMargine.ToString() + "\r\n";
                        }

                        if (EpgAutoAddInfo.recSetting.SuspendMode == 0)
                        {
                            view += "録画後動作 : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画後動作 : ";
                            switch (EpgAutoAddInfo.recSetting.SuspendMode)
                            {
                                case 1:
                                    view += "スタンバイ";
                                    break;
                                case 2:
                                    view += "休止";
                                    break;
                                case 3:
                                    view += "シャットダウン";
                                    break;
                                case 4:
                                    view += "何もしない";
                                    break;
                            }
                            if (EpgAutoAddInfo.recSetting.RebootFlag == 1)
                            {
                                view += " 復帰後再起動する";
                            }
                            view += "\r\n";
                        }
                    }
                }

                TextBlock block = new TextBlock();
                block.Text = view;
                block.MaxWidth = 400;
                block.TextWrapping = TextWrapping.Wrap;
                return block;
            }
        }
    }
}
