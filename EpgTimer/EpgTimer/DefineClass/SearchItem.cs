using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Controls;
using System.Windows;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    public class SearchItem
    {
        private EpgEventInfo eventInfo = null;
        private ReserveData reserveData = null;

        public EpgEventInfo EventInfo
        {
            get { return eventInfo; }
            set { eventInfo = value; }
        }
        public ReserveData ReserveInfo
        {
            get { return reserveData; }
            set { reserveData = value; }
        }
        public String EventName
        {
            get
            {
                String view = "";
                if (eventInfo != null)
                {
                    if (eventInfo.ShortInfo != null)
                    {
                        view = eventInfo.ShortInfo.event_name;
                    }
                }
                return view;
            }
        }
        public String ServiceName
        {
            get;
            set;
        }
        public String NetworkName
        {
            get
            {
                String view = "";
                if (eventInfo != null)
                {
                    if (0x7880 <= eventInfo.original_network_id && eventInfo.original_network_id <= 0x7FE8)
                    {
                        view = "地デジ";
                    }
                    else if (eventInfo.original_network_id == 0x0004)
                    {
                        view = "BS";
                    }
                    else if (eventInfo.original_network_id == 0x0006)
                    {
                        view = "CS1";
                    }
                    else if (eventInfo.original_network_id == 0x0007)
                    {
                        view = "CS2";
                    }
                    else
                    {
                        view = "その他";
                    }

                }
                return view;
            }
        }
        public String StartTime
        {
            get
            {
                String view = "未定";
                if (eventInfo != null)
                {
                    view = eventInfo.start_time.ToString("yyyy/MM/dd(ddd) HH:mm:ss");
                }
                return view;
            }
        }
        public bool IsReserved
        {
            get
            {
                if (reserveData == null)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
        public String Reserved
        {
            get
            {
                String view = "";
                if (IsReserved == true)
                {
                    view = "予";
                }
                return view;
            }
        }
        public SolidColorBrush BackColor
        {
            get
            {
                SolidColorBrush color = Brushes.White;
                if (ReserveInfo != null)
                {
                    if (ReserveInfo.RecSetting.RecMode == 5)
                    {
                        color = Brushes.DarkGray;
                    }
                    else if (ReserveInfo.OverlapMode == 2)
                    {
                        color = Brushes.Red;
                    }
                    else if (ReserveInfo.OverlapMode == 1)
                    {
                        color = Brushes.Yellow;
                    }
                }
                return color;
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
                if (eventInfo != null)
                {
                    view = CommonManager.Instance.ConvertProgramText(eventInfo, EventInfoTextMode.All);
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
