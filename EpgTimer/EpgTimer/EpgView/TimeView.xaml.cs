using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace EpgTimer.EpgView
{
    /// <summary>
    /// TimeView.xaml の相互作用ロジック
    /// </summary>
    public partial class TimeView : UserControl
    {
        public TimeView()
        {
            InitializeComponent();
        }

        public void ClearInfo()
        {
            stackPanel_time.Children.Clear();
        }

        public void SetTime(System.Collections.SortedList timeList, bool NeedTimeOnly, bool weekMode)
        {
            try
            {
                stackPanel_time.Children.Clear();
                foreach (TimePosInfo info in timeList.Values)
                {
                    TextBlock item = new TextBlock();

                    double height = Settings.Instance.MinHeight;
                    item.Height = (60 * height) - 4;

                    if (weekMode == true)
                    {
                        item.Text = info.Time.Hour.ToString();
                    }
                    else
                    {
                        if (info.Time.Hour % 3 == 0 || NeedTimeOnly == true)
                        {
                            if (height < 1)
                            {
                                item.Text = info.Time.ToString("M/d\r\nH");
                            }
                            else if (height < 1.5)
                            {
                                item.Text = info.Time.ToString("M/d\r\n(ddd)\r\nH");
                            }
                            else
                            {
                                item.Text = info.Time.ToString("M/d\r\n(ddd)\r\n\r\nH");
                            }
                        }
                        else
                        {
                            if (height < 1)
                            {
                                item.Text = info.Time.Hour.ToString();
                            }
                            else if (height < 1.5)
                            {
                                item.Text = info.Time.ToString("\r\nH");
                            }
                            else
                            {
                                item.Text = info.Time.ToString("\r\n\r\n\r\nH");
                            }
                        }

                        if (info.Time.DayOfWeek == DayOfWeek.Saturday)
                        {
                            item.Foreground = Brushes.Blue;
                        }
                        else if (info.Time.DayOfWeek == DayOfWeek.Sunday)
                        {
                            item.Foreground = Brushes.Red;
                        }
                        else
                        {
                            item.Foreground = Brushes.Black;
                        }
                    }

                    item.Margin = new Thickness(2, 2, 2, 2);
                    item.Background = Brushes.AliceBlue;
                    item.TextAlignment = TextAlignment.Center;
                    item.FontSize = 12;
                    stackPanel_time.Children.Add(item);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }

        }

        private void scrollViewer_PreviewMouseWheel(object sender, MouseWheelEventArgs e)
        {
            e.Handled = true;
        }
    }
}
