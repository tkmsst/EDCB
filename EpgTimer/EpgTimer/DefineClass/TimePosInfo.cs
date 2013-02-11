using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    class TimePosInfo
    {
        public TimePosInfo(DateTime time, double pos)
        {
            Time = time;
            TopPos = pos;
            ProgramList = new List<ProgramViewItem>();
            ReserveList = new List<ReserveViewItem>();
        }

        public DateTime Time
        {
            get;
            set;
        }
        public double TopPos
        {
            get;
            set;
        }
        public List<ProgramViewItem> ProgramList
        {
            get;
            set;
        }
        public List<ReserveViewItem> ReserveList
        {
            get;
            set;
        }
    }
}
