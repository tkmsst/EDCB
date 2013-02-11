using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    public class ViewMenuItem
    {
        public ViewMenuItem(String name, bool select)
        {
            MenuName = name;
            IsSelected = select;
        }

        public bool IsSelected
        {
            get;
            set;
        }
        public String MenuName
        {
            get;
            set;
        }
        public override string ToString()
        {
            return MenuName;
        }
    }
}
