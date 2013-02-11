using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    public class TunerSelectInfo
    {
        public TunerSelectInfo(String name, UInt32 id)
        {
            Name = name;
            ID = id;
        }
        public String Name
        {
            get;
            set;
        }
        public UInt32 ID
        {
            get;
            set;
        }
        public override string ToString()
        {
            String view = "";
            if (ID == 0)
            {
                view = "自動";
            }
            else
            {
                view = "ID:" + ID.ToString("X8") + " (" + Name + ")";
            }
            return view;
        }
    }
}
