using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    class DayOfWeekInfo
    {
        public DayOfWeekInfo()
        {
        }
        public DayOfWeekInfo(String displayName, Byte value)
        {
            this.DisplayName = displayName;
            this.Value = value;
        }
        public String DisplayName
        {
            get;
            set;
        }
        public Byte Value
        {
            get;
            set;
        }
        public override string ToString()
        {
            return DisplayName;
        }
    }
}
