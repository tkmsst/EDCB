using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace EpgTimer
{
    public class EpgCaptime : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private bool selected = false;
        //private bool basiconly = false;
        private string epgtype = "";

        private void NotifyPropertyChanged(String info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }

        public bool IsSelected
        {
            get
            {
                return this.selected;
            }
            set
            {
                this.selected = value;
                NotifyPropertyChanged("IsSelected");
            }
        }

        public string txtBasicOnly
        {
            get
            {
                if (this.epgtype.Length == 1)
                {
                    if (this.epgtype.Equals("1"))
                    {
                        return "基本のみ";
                    }
                    else
                    {
                        return "";
                    }
                }
                else
                {
                    if (this.epgtype.Equals("1111111"))
                    {
                        return "基本のみ";
                    }
                    else if (this.epgtype.Equals("2222222"))
                    {
                        return "";
                    }
                    else
                    {
                        return this.epgtype;
                    }
                }
            }
        }

        public string IsBasicOnly
        {
            get
            {
                return this.epgtype;
            }
            set
            {
                this.epgtype = value;
                NotifyPropertyChanged("IsBasicOnly");
            }
        }

        public string Time
        {
            get;
            set;
        }
    }
}
