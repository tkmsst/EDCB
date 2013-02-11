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

        private Dictionary<String, GridViewColumn> columnList = new Dictionary<String, GridViewColumn>();

        public EpgAutoAddView()
        {
            InitializeComponent();
            try
            {
                if (Settings.Instance.NoStyle == 1)
                {
                    button_add.Style = null;
                    button_del.Style = null;
                    button_change.Style = null;
                    button_up.Style = null;
                    button_down.Style = null;
                }

                foreach (GridViewColumn info in gridView_key.Columns)
                {
                    GridViewColumnHeader header = info.Header as GridViewColumnHeader;
                    columnList.Add((string)header.Tag, info);
                }
                gridView_key.Columns.Clear();

                foreach (ListColumnInfo info in Settings.Instance.AutoAddEpgColumn)
                {
                    columnList[info.Tag].Width = info.Width;
                    gridView_key.Columns.Add(columnList[info.Tag]);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        public void SaveSize()
        {
            try
            {
                Settings.Instance.AutoAddEpgColumn.Clear();
                foreach (GridViewColumn info in gridView_key.Columns)
                {
                    GridViewColumnHeader header = info.Header as GridViewColumnHeader;

                    Settings.Instance.AutoAddEpgColumn.Add(new ListColumnInfo((String)header.Tag, info.Width));
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
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

        private bool ReloadInfoData()
        {
            try
            {
                listView_key.DataContext = null;
                resultList.Clear();

                ErrCode err = CommonManager.Instance.DB.ReloadEpgAutoAddInfo();
                if (err == ErrCode.CMD_ERR_CONNECT)
                {
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        MessageBox.Show("サーバー または EpgTimerSrv に接続できませんでした。");
                    }), null);
                    return false;
                }
                if (err == ErrCode.CMD_ERR_TIMEOUT)
                {
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        MessageBox.Show("EpgTimerSrvとの接続にタイムアウトしました。");
                    }), null);
                    return false;
                }
                if (err != ErrCode.CMD_SUCCESS)
                {
                    this.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        MessageBox.Show("情報の取得でエラーが発生しました。");
                    }), null);
                    return false;
                }

                foreach (EpgAutoAddData info in CommonManager.Instance.DB.EpgAutoAddList.Values)
                {
                    EpgAutoDataItem item = new EpgAutoDataItem(info);
                    resultList.Add(item);
                }

                listView_key.DataContext = resultList;
            }
            catch (Exception ex)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
                }), null);
                return false;
            }
            return true;
        }

        private void button_add_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                SearchWindow dlg = new SearchWindow();
                dlg.Owner = (Window)PresentationSource.FromVisual(this).RootVisual;
                dlg.SetViewMode(1);
                dlg.ShowDialog();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void button_del_Click(object sender, RoutedEventArgs e)
        {
            try
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
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void button_change_Click(object sender, RoutedEventArgs e)
        {
            try
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
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void listView_key_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
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
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void button_up_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (listView_key.SelectedIndex > 0 && listView_key.SelectedItem != null)
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
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void button_down_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (listView_key.SelectedIndex + 1 < listView_key.Items.Count && listView_key.SelectedItem != null)
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
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void UserControl_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (ReloadInfo == true && this.IsVisible == true)
            {
                if (ReloadInfoData() == true)
                {
                    ReloadInfo = false;
                }
            }
        }


        private void ContextMenu_Header_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            try
            {
                foreach (MenuItem item in listView_key.ContextMenu.Items)
                {
                    item.IsChecked = false;
                    foreach (ListColumnInfo info in Settings.Instance.AutoAddEpgColumn)
                    {
                        if (info.Tag.CompareTo(item.Name) == 0)
                        {
                            item.IsChecked = true;
                            break;
                        }
                    }
                }


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void headerSelect_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MenuItem menuItem = sender as MenuItem;
                if (menuItem.IsChecked == true)
                {

                    Settings.Instance.AutoAddEpgColumn.Add(new ListColumnInfo(menuItem.Name, Double.NaN));
                    gridView_key.Columns.Add(columnList[menuItem.Name]);
                }
                else
                {
                    foreach (ListColumnInfo info in Settings.Instance.AutoAddEpgColumn)
                    {
                        if (info.Tag.CompareTo(menuItem.Name) == 0)
                        {
                            Settings.Instance.AutoAddEpgColumn.Remove(info);
                            gridView_key.Columns.Remove(columnList[menuItem.Name]);
                            break;
                        }
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }
    }
}
