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

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    /// <summary>
    /// ManualAutoAddView.xaml の相互作用ロジック
    /// </summary>
    public partial class ManualAutoAddView : UserControl
    {
        private CtrlCmdUtil cmd = CommonManager.Instance.CtrlCmd;
        private List<ManualAutoAddDataItem> resultList = new List<ManualAutoAddDataItem>();
        private bool ReloadInfo = true;

        public ManualAutoAddView()
        {
            InitializeComponent();
        }

        /// <summary>
        /// リストの更新通知
        /// </summary>
        public void UpdateInfo()
        {
            if (this.IsVisible == true)
            {
                ReloadInfoData();
                ReloadInfo = false;
            }
            else
            {
                ReloadInfo = true;
            }
        }
        
        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            if (ReloadInfo == true && this.IsVisible == true)
            {
                ReloadInfoData();
                ReloadInfo = false;
            }
        }

        private void ReloadInfoData()
        {
            listView_key.DataContext = null;
            resultList.Clear();

            ErrCode err = CommonManager.Instance.DB.ReloadManualAutoAddInfo();
            if (err == ErrCode.CMD_ERR_CONNECT)
            {
                MessageBox.Show("サーバー または EpgTimerSrv に接続できませんでした。");
                return;
            }
            if (err == ErrCode.CMD_ERR_TIMEOUT)
            {
                MessageBox.Show("EpgTimerSrvとの接続にタイムアウトしました。");
                return;
            }
            if (err != ErrCode.CMD_SUCCESS)
            {
                MessageBox.Show("情報の取得でエラーが発生しました。");
                return;
            }

            foreach (ManualAutoAddData info in CommonManager.Instance.DB.ManualAutoAddList.Values)
            {
                ManualAutoAddDataItem item = new ManualAutoAddDataItem(info);
                resultList.Add(item);
            }

            listView_key.DataContext = resultList;
        }

        private void button_add_Click(object sender, RoutedEventArgs e)
        {
            AddManualAutoAddWindow dlg = new AddManualAutoAddWindow();
            dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
            dlg.ShowDialog();
        }

        private void button_del_Click(object sender, RoutedEventArgs e)
        {
            if (listView_key.SelectedItems.Count > 0)
            {
                List<UInt32> dataIDList = new List<uint>();
                foreach (ManualAutoAddDataItem info in listView_key.SelectedItems)
                {
                    dataIDList.Add(info.ManualAutoAddInfo.dataID);
                }
                cmd.SendDelManualAdd(dataIDList);
            }
        }

        private void button_change_Click(object sender, RoutedEventArgs e)
        {
            if (listView_key.SelectedItem != null)
            {
                ManualAutoAddDataItem info = listView_key.SelectedItem as ManualAutoAddDataItem;
                AddManualAutoAddWindow dlg = new AddManualAutoAddWindow();
                dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
                dlg.SetChangeMode(true);
                dlg.SetDefaultSetting(info.ManualAutoAddInfo);
                dlg.ShowDialog();
            }
        }

        private void listView_key_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (listView_key.SelectedItem != null)
            {
                ManualAutoAddDataItem info = listView_key.SelectedItem as ManualAutoAddDataItem;
                AddManualAutoAddWindow dlg = new AddManualAutoAddWindow();
                dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
                dlg.SetChangeMode(true);
                dlg.SetDefaultSetting(info.ManualAutoAddInfo);
                dlg.ShowDialog();
            }
        }

    }
}
