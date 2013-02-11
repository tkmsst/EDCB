using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    public class ReserveViewItem
    {
        public ReserveViewItem()
        {
        }
        public ReserveViewItem(ReserveData info)
        {
            ReserveInfo = info;
        }

        public ReserveData ReserveInfo
        {
            get;
            set;
        }
        public double Width
        {
            get;
            set;
        }

        public double Height
        {
            get;
            set;
        }

        public double LeftPos
        {
            get;
            set;
        }

        public double TopPos
        {
            get;
            set;
        }

        //public SolidColorBrush ContentColor
        //{
        //    get
        //    {}
        //}
    }
}
