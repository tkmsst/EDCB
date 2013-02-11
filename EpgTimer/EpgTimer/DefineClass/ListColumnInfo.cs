using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    public class ListColumnInfo
    {
        public ListColumnInfo()
        {
            Tag = "";
            Width = double.NaN;
        }
        public ListColumnInfo(String tag, double width)
        {
            Tag = tag;
            Width = width;
        }
        public String Tag
        {
            get;
            set;
        }
        public double Width
        {
            get;
            set;
        }
    }
}
