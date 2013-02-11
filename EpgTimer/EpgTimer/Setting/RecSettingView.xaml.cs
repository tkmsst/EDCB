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
using System.IO;
using System.Windows.Interop;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    /// <summary>
    /// RecSettingView.xaml の相互作用ロジック
    /// </summary>
    public partial class RecSettingView : UserControl
    {
        private RecSettingData recSetting = new RecSettingData();
        private List<TunerSelectInfo> tunerList = new List<TunerSelectInfo>();
        private CtrlCmdUtil cmd = CommonManager.Instance.CtrlCmd;

        public RecSettingView()
        {
            InitializeComponent();

            try
            {
                Settings.GetDefRecSetting(0, ref recSetting);

                comboBox_recMode.DataContext = CommonManager.Instance.RecModeDictionary.Values;
                comboBox_tuijyu.DataContext = CommonManager.Instance.YesNoDictionary.Values;
                comboBox_pittari.DataContext = CommonManager.Instance.YesNoDictionary.Values;
                comboBox_priority.DataContext = CommonManager.Instance.PriorityDictionary.Values;


                String plugInFile = "Write_Default.dll";
                String recNamePlugInFile = "";

                List<String> fileList = new List<string>();
                ErrCode err = (ErrCode)cmd.SendEnumPlugIn(2, ref fileList);
                if (err == ErrCode.CMD_ERR_CONNECT)
                {
                    MessageBox.Show("サーバー または EpgTimerSrv に接続できませんでした。");
                }
                if (err == ErrCode.CMD_ERR_TIMEOUT)
                {
                    MessageBox.Show("EpgTimerSrvとの接続にタイムアウトしました。");
                }
                if (err != ErrCode.CMD_SUCCESS)
                {
                    MessageBox.Show("PlugIn一覧の取得でエラーが発生しました。");
                }

                int select = 0;
                foreach (string info in fileList)
                {
                    int index = comboBox_writePlugIn.Items.Add(info);
                    if (String.Compare(info, plugInFile, true) == 0)
                    {
                        select = index;
                    }
                }
                if (comboBox_writePlugIn.Items.Count != 0)
                {
                    comboBox_writePlugIn.SelectedIndex = select;
                }

                fileList.Clear();
                if (err == ErrCode.CMD_SUCCESS)
                {
                    err = (ErrCode)cmd.SendEnumPlugIn(1, ref fileList);
                    if (err == ErrCode.CMD_ERR_CONNECT)
                    {
                        MessageBox.Show("サーバー または EpgTimerSrv に接続できませんでした。");
                    }
                    if (err == ErrCode.CMD_ERR_TIMEOUT)
                    {
                        MessageBox.Show("EpgTimerSrvとの接続にタイムアウトしました。");
                    }
                    if (err != ErrCode.CMD_SUCCESS)
                    {
                        MessageBox.Show("PlugIn一覧の取得でエラーが発生しました。");
                    }
                    select = 0;
                    comboBox_recNamePlugIn.Items.Add("なし");
                    foreach (string info in fileList)
                    {
                        int index = comboBox_recNamePlugIn.Items.Add(info);
                        if (String.Compare(info, recNamePlugInFile, true) == 0)
                        {
                            select = index;
                        }
                    }
                    if (comboBox_recNamePlugIn.Items.Count != 0)
                    {
                        comboBox_recNamePlugIn.SelectedIndex = select;
                    }
                }

                if (err == ErrCode.CMD_SUCCESS)
                {
                    List<CtrlCmdCLI.Def.TunerReserveInfo> tunerReserveList = new List<CtrlCmdCLI.Def.TunerReserveInfo>();
                    err = (ErrCode)cmd.SendEnumTunerReserve(ref tunerReserveList);
                    if (err == ErrCode.CMD_ERR_CONNECT)
                    {
                        MessageBox.Show("サーバー または EpgTimerSrv に接続できませんでした。");
                    }
                    if (err == ErrCode.CMD_ERR_TIMEOUT)
                    {
                        MessageBox.Show("EpgTimerSrvとの接続にタイムアウトしました。");
                    }
                    if (err != ErrCode.CMD_SUCCESS)
                    {
                        MessageBox.Show("チューナー一覧の取得でエラーが発生しました。");
                    }
                    tunerList.Add(new TunerSelectInfo("自動", 0));
                    foreach (TunerReserveInfo info in tunerReserveList)
                    {
                        if (info.tunerID != 0xFFFFFFFF)
                        {
                            tunerList.Add(new TunerSelectInfo(info.tunerName, info.tunerID));
                        }
                    }
                    comboBox_tuner.ItemsSource = tunerList;
                    comboBox_tuner.SelectedIndex = 0;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        public void SetDefSetting(RecSettingData set)
        {
            recSetting = set;
        }

        public void SetDefSetting(UInt32 presetID)
        {
            Settings.GetDefRecSetting(presetID, ref recSetting);
        }

        public void GetRecSetting(ref RecSettingData set)
        {
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            UpdateView();
        }

        private void comboBox_preSet_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (comboBox_preSet.SelectedItem != null)
                {
                    RecPresetItem item = comboBox_preSet.SelectedItem as RecPresetItem;
                    Settings.GetDefRecSetting(item.ID, ref recSetting);
                    UpdateView();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void UpdateView()
        {
            try
            {
                foreach (RecModeInfo info in comboBox_recMode.Items)
                {
                    if (info.Value == recSetting.RecMode)
                    {
                        comboBox_recMode.SelectedItem = info;
                    }
                }
                foreach (PriorityInfo info in comboBox_priority.Items)
                {
                    if (info.Value == recSetting.Priority)
                    {
                        comboBox_priority.SelectedItem = info;
                    }
                }
                foreach (YesNoInfo info in comboBox_tuijyu.Items)
                {
                    if (info.Value == recSetting.TuijyuuFlag)
                    {
                        comboBox_tuijyu.SelectedItem = info;
                    }
                }

                if (recSetting.ServiceMode == 0)
                {
                    checkBox_serviceMode.IsChecked = true;
                }
                else
                {
                    checkBox_serviceMode.IsChecked = false;
                    if ((recSetting.ServiceMode & 0x10) > 0)
                    {
                        checkBox_serviceCaption.IsChecked = true;
                    }
                    else
                    {
                        checkBox_serviceCaption.IsChecked = false;
                    }
                    if ((recSetting.ServiceMode & 0x20) > 0)
                    {
                        checkBox_serviceData.IsChecked = true;
                    }
                    else
                    {
                        checkBox_serviceData.IsChecked = false;
                    }
                }

                foreach (YesNoInfo info in comboBox_pittari.Items)
                {
                    if (info.Value == recSetting.PittariFlag)
                    {
                        comboBox_pittari.SelectedItem = info;
                    }
                }


                textBox_bat.Text = recSetting.BatFilePath;
                listView_recFolder.ItemsSource = recSetting.RecFolderList;

                if (recSetting.SuspendMode == 0)
                {
                    checkBox_suspendDef.IsChecked = true;
                    checkBox_reboot.IsChecked = false;
                }
                else
                {
                    checkBox_suspendDef.IsChecked = false;

                    if (recSetting.SuspendMode == 1)
                    {
                        radioButton_standby.IsChecked = true;
                    }
                    if (recSetting.SuspendMode == 2)
                    {
                        radioButton_supend.IsChecked = true;
                    }
                    if (recSetting.SuspendMode == 3)
                    {
                        radioButton_shutdown.IsChecked = true;
                    }
                    if (recSetting.SuspendMode == 4)
                    {
                        radioButton_non.IsChecked = true;
                    }
                    if (recSetting.RebootFlag == 1)
                    {
                        checkBox_reboot.IsChecked = true;
                    }
                    else
                    {
                        checkBox_reboot.IsChecked = false;
                    }
                }
                if (recSetting.UseMargineFlag == 0)
                {
                    checkBox_margineDef.IsChecked = true;
                }
                else
                {
                    checkBox_margineDef.IsChecked = false;
                    textBox_margineStart.Text = recSetting.StartMargine.ToString();
                    textBox_margineEnd.Text = recSetting.EndMargine.ToString();
                }

                if (recSetting.ContinueRecFlag == 1)
                {
                    checkBox_continueRec.IsChecked = true;
                }
                else
                {
                    checkBox_continueRec.IsChecked = false;
                }
                if (recSetting.PartialRecFlag == 1)
                {
                    checkBox_partial.IsChecked = true;
                }
                else
                {
                    checkBox_partial.IsChecked = false;
                }

                foreach (TunerSelectInfo info in comboBox_tuner.Items)
                {
                    if (info.ID == recSetting.TunerID)
                    {
                        comboBox_tuner.SelectedItem = info;
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }
        }

        private void checkBox_suspendDef_Click(object sender, RoutedEventArgs e)
        {
            checkBox_reboot.IsChecked = false;
        }

        private void radioButton_suspend_Click(object sender, RoutedEventArgs e)
        {
            checkBox_suspendDef.IsChecked = false;
        }

        private void checkBox_serviceMode_Checked(object sender, RoutedEventArgs e)
        {
            checkBox_serviceCaption.IsChecked = false;
            checkBox_serviceData.IsChecked = false;
        }

        private void checkBox_serviceCaption_Checked(object sender, RoutedEventArgs e)
        {
            checkBox_serviceMode.IsChecked = false;
        }

        private void button_bat_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.DefaultExt = ".bat";
            dlg.Filter = "bat Files (.bat)|*.bat;|all Files(*.*)|*.*";

            Nullable<bool> result = dlg.ShowDialog();
            if (result == true)
            {
                textBox_bat.Text = dlg.FileName;
            }
        }

        private void button_recFolder_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog dlg = new System.Windows.Forms.FolderBrowserDialog();
            dlg.Description = "フォルダ選択";
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textBox_recFolder.Text = dlg.SelectedPath;
            }
        }

        private void button_writePlugIn_Click(object sender, RoutedEventArgs e)
        {
            if (comboBox_writePlugIn.SelectedItem != null)
            {
                string name = comboBox_writePlugIn.SelectedItem as string;
                string filePath = SettingPath.ModulePath + "\\Write\\" + name;

                WritePlugInClass plugin = new WritePlugInClass();
                HwndSource hwnd = (HwndSource)HwndSource.FromVisual(this);

                plugin.Setting(filePath, hwnd.Handle);
            }
        }

        private void button_namePlugIn_Click(object sender, RoutedEventArgs e)
        {
            if (comboBox_recNamePlugIn.SelectedItem != null)
            {
                string name = comboBox_recNamePlugIn.SelectedItem as string;
                if (String.Compare(name, "なし", true) != 0)
                {
                    string filePath = SettingPath.ModulePath + "\\RecName\\" + name;

                    RecNamePluginClass plugin = new RecNamePluginClass();
                    HwndSource hwnd = (HwndSource)HwndSource.FromVisual(this);

                    plugin.Setting(filePath, hwnd.Handle);
                }
            }
        }

        private void button_recFolderAdd_Click(object sender, RoutedEventArgs e)
        {
            if (String.IsNullOrEmpty(textBox_recFolder.Text) == false)
            {
                foreach (RecFileSetInfo info in recSetting.RecFolderList)
                {
                    if (String.Compare(textBox_recFolder.Text, info.RecFolder, true) == 0 &&
                        String.Compare((String)comboBox_writePlugIn.SelectedItem, info.WritePlugIn, true) == 0 &&
                        String.Compare((String)comboBox_recNamePlugIn.SelectedItem, info.RecNamePlugIn, true) == 0)
                    {
                        MessageBox.Show("すでに追加されています");
                        return;
                    }
                }
                RecFileSetInfo item = new RecFileSetInfo();
                item.RecFolder = textBox_recFolder.Text;
                item.WritePlugIn = (String)comboBox_writePlugIn.SelectedItem;
                item.RecNamePlugIn = (String)comboBox_recNamePlugIn.SelectedItem;
                if (String.Compare(item.RecNamePlugIn, "なし", true) == 0)
                {
                    item.RecNamePlugIn = "";
                }

                recSetting.RecFolderList.Add(item);
                listView_recFolder.ItemsSource = null;
                listView_recFolder.ItemsSource = recSetting.RecFolderList;
            }
        }

        private void button_recFolderDel_Click(object sender, RoutedEventArgs e)
        {
            if (listView_recFolder.SelectedItem != null)
            {
                recSetting.RecFolderList.RemoveAt(listView_recFolder.SelectedIndex);
                listView_recFolder.ItemsSource = null;
                listView_recFolder.ItemsSource = recSetting.RecFolderList;
            }
        }


    }
}
