using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    public class DateItem
    {
        public DateItem()
        {
        }
        public EpgSearchDateInfo DateInfo
        {
            get;
            set;
        }
        public String ViewText
        {
            get;
            set;
        }
        public override string ToString()
        {
            return ViewText;
        }
    }
}
