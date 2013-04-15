using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    public class CoopServerInfo
    {
        public String ServerAddress
        {
            get;
            set;
        }
        public UInt32 ServerPort
        {
            get;
            set;
        }
        public override string ToString()
        {
            String view = ServerAddress + ":" + ServerPort.ToString();
            return view;
        }
    }
}
