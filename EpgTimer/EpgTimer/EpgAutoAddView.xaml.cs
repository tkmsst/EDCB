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
    /// EpgAutoAddView.xaml の相互作用ロジック
    /// </summary>
    public partial class EpgAutoAddView : UserControl
    {
        private CtrlCmdUtil cmd = CommonManager.Instance.CtrlCmd;
        private List<EpgAutoDataItem> resultList = new List<EpgAutoDataItem>();
        private bool ReloadInfo = true;

        public EpgAutoAddView()
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

            ErrCode err = CommonManager.Instance.DB.ReloadEpgAutoAddInfo();
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

            foreach (EpgAutoAddData info in CommonManager.Instance.DB.EpgAutoAddList.Values)
            {
                EpgAutoDataItem item = new EpgAutoDataItem(info);
                resultList.Add(item);
            }

            listView_key.DataContext = resultList;
        }

        private void button_add_Click(object sender, RoutedEventArgs e)
        {
            SearchWindow dlg = new SearchWindow();
            dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
            dlg.SetViewMode(1);
            dlg.ShowDialog();
        }

        private void button_del_Click(object sender, RoutedEventArgs e)
        {
            if (listView_key.SelectedItems.Count > 0)
            {
                List<UInt32> dataIDList = new List<uint>();
                foreach (EpgAutoDataItem info in listView_key.SelectedItems)
                {
                    dataIDList.Add(info.EpgAutoAddInfo.dataID);
                }
                cmd.SendDelEpgAutoAdd(dataIDList);
            }
        }

        private void button_change_Click(object sender, RoutedEventArgs e)
        {
            if (listView_key.SelectedItem != null)
            {
                EpgAutoDataItem info = listView_key.SelectedItem as EpgAutoDataItem;
                SearchWindow dlg = new SearchWindow();
                dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
                dlg.SetViewMode(2);
                dlg.SetChgAutoAddID(info.EpgAutoAddInfo.dataID);
                dlg.SetSearchDefKey(info.EpgAutoAddInfo.searchInfo);
                dlg.SetRecInfoDef(info.EpgAutoAddInfo.recSetting);
                dlg.ShowDialog();
            }
        }

        private void listView_key_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (listView_key.SelectedItem != null)
            {
                EpgAutoDataItem info = listView_key.SelectedItem as EpgAutoDataItem;
                SearchWindow dlg = new SearchWindow();
                dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
                dlg.SetViewMode(2);
                dlg.SetChgAutoAddID(info.EpgAutoAddInfo.dataID);
                dlg.SetSearchDefKey(info.EpgAutoAddInfo.searchInfo);
                dlg.SetRecInfoDef(info.EpgAutoAddInfo.recSetting);
                dlg.ShowDialog();
            }
        }

        private void button_up_Click(object sender, RoutedEventArgs e)
        {
            if (listView_key.SelectedIndex > 0)
            {
                EpgAutoDataItem info1 = listView_key.SelectedItem as EpgAutoDataItem;
                EpgAutoDataItem info2 = listView_key.Items.GetItemAt(listView_key.SelectedIndex - 1) as EpgAutoDataItem;

                UInt32 tempId = info1.EpgAutoAddInfo.dataID;
                info1.EpgAutoAddInfo.dataID = info2.EpgAutoAddInfo.dataID;
                info2.EpgAutoAddInfo.dataID = tempId;

                List<EpgAutoAddData> addList = new List<EpgAutoAddData>();
                addList.Add(info1.EpgAutoAddInfo);
                addList.Add(info2.EpgAutoAddInfo);
                if (cmd.SendChgEpgAutoAdd(addList) != 1)
                {
                    MessageBox.Show("変更に失敗しました");
                }
            }
        }

        private void button_down_Click(object sender, RoutedEventArgs e)
        {
            if (listView_key.SelectedIndex+1 < listView_key.Items.Count)
            {
                EpgAutoDataItem info1 = listView_key.SelectedItem as EpgAutoDataItem;
                EpgAutoDataItem info2 = listView_key.Items.GetItemAt(listView_key.SelectedIndex + 1) as EpgAutoDataItem;

                UInt32 tempId = info1.EpgAutoAddInfo.dataID;
                info1.EpgAutoAddInfo.dataID = info2.EpgAutoAddInfo.dataID;
                info2.EpgAutoAddInfo.dataID = tempId;

                List<EpgAutoAddData> addList = new List<EpgAutoAddData>();
                addList.Add(info1.EpgAutoAddInfo);
                addList.Add(info2.EpgAutoAddInfo);
                if (cmd.SendChgEpgAutoAdd(addList) != 1)
                {
                    MessageBox.Show("変更に失敗しました");
                }
            }
        }
    }
}
