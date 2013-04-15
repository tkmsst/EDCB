using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    public class NotifySrvInfoItem
    {
        public NotifySrvInfo NotifyInfo
        {
            get;
            set;
        }
        public String Time
        {
            get
            {
                String text = "";
                if (NotifyInfo != null)
                {
                    text = NotifyInfo.time.ToString("yyyy/MM/dd HH:mm:ss.fff");
                }
                return text;
            }
        }
        public String Title
        {
            get
            {
                String text = "";
                if (NotifyInfo != null)
                {
                    switch ((UpdateNotifyItem)NotifyInfo.notifyID)
                    {
                        case UpdateNotifyItem.PreRecStart:
                            {
                                text = "予約録画開始準備";
                            }
                            break;
                        case UpdateNotifyItem.RecStart:
                            {
                                text = "録画開始";
                            }
                            break;
                        case UpdateNotifyItem.RecEnd:
                            {
                                text = "録画終了";
                            }
                            break;
                        case UpdateNotifyItem.RecTuijyu:
                            {
                                text = "追従発生";
                            }
                            break;
                        case UpdateNotifyItem.ChgTuijyu:
                            {
                                text = "番組変更";
                            }
                            break;
                        case UpdateNotifyItem.PreEpgCapStart:
                            {
                                text = "EPG取得";
                            }
                            break;
                        case UpdateNotifyItem.EpgCapStart:
                            {
                                text = "EPG取得";
                            }
                            break;
                        case UpdateNotifyItem.EpgCapEnd:
                            {
                                text = "EPG取得";
                            }
                            break;
                        default:
                            text = NotifyInfo.notifyID.ToString();
                            break;
                    }
                }
                return text;
            }
        }

        public String LogText
        {
            get
            {
                String text = "";
                if (NotifyInfo != null)
                {
                    switch ((UpdateNotifyItem)NotifyInfo.notifyID)
                    {
                        case UpdateNotifyItem.PreRecStart:
                            {
                                text = NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.RecStart:
                            {
                                text = NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.RecEnd:
                            {
                                text = NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.RecTuijyu:
                            {
                                text = NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.ChgTuijyu:
                            {
                                text = NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.PreEpgCapStart:
                            {
                                text = NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.EpgCapStart:
                            {
                                text = "開始";
                            }
                            break;
                        case UpdateNotifyItem.EpgCapEnd:
                            {
                                text = "終了";
                            }
                            break;
                        default:
                            text = NotifyInfo.notifyID.ToString();
                            break;
                    }
                }
                return text;
            }
        }

        public String FileLogText
        {
            get
            {
                String text = "";
                if (NotifyInfo != null)
                {
                    text = NotifyInfo.time.ToString("yyyy/MM/dd HH:mm:ss.fff");

                    text += " [";
                    switch ((UpdateNotifyItem)NotifyInfo.notifyID)
                    {
                        case UpdateNotifyItem.PreRecStart:
                            {
                                text += "予約録画開始準備";
                            }
                            break;
                        case UpdateNotifyItem.RecStart:
                            {
                                text += "録画開始";
                            }
                            break;
                        case UpdateNotifyItem.RecEnd:
                            {
                                text += "録画終了";
                            }
                            break;
                        case UpdateNotifyItem.RecTuijyu:
                            {
                                text += "追従発生";
                            }
                            break;
                        case UpdateNotifyItem.ChgTuijyu:
                            {
                                text += "番組変更";
                            }
                            break;
                        case UpdateNotifyItem.PreEpgCapStart:
                            {
                                text += "EPG取得";
                            }
                            break;
                        case UpdateNotifyItem.EpgCapStart:
                            {
                                text += "EPG取得";
                            }
                            break;
                        case UpdateNotifyItem.EpgCapEnd:
                            {
                                text += "EPG取得";
                            }
                            break;
                        default:
                            text += NotifyInfo.notifyID.ToString();
                            break;
                    }
                    text += "] ";

                    switch ((UpdateNotifyItem)NotifyInfo.notifyID)
                    {
                        case UpdateNotifyItem.PreRecStart:
                            {
                                text += NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.RecStart:
                            {
                                text += NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.RecEnd:
                            {
                                text += NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.RecTuijyu:
                            {
                                text += NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.ChgTuijyu:
                            {
                                text += NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.PreEpgCapStart:
                            {
                                text += NotifyInfo.param4;
                            }
                            break;
                        case UpdateNotifyItem.EpgCapStart:
                            {
                                text += "開始";
                            }
                            break;
                        case UpdateNotifyItem.EpgCapEnd:
                            {
                                text += "終了";
                            }
                            break;
                        default:
                            text += NotifyInfo.notifyID.ToString();
                            break;
                    }
                    text += "\r\n";
                }
                return text;
            }
        }
    }
}
