using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Collections;
using System.Threading;
using System.Runtime.InteropServices;

namespace EpgTimer
{
    class PipeServerThread
    {
        public const string CMD_CTRL_EVENT_WAIT = "CtrlCmdEvent_"; //+ID
        public const uint PIPE_TIMEOUT = 500;
        public const uint SEND_BUFF_SIZE = 1024 * 10;
        public const uint RES_BUFF_SIZE = 1024 * 10;

        public CMD_CALLBACK_PROC m_pCmdProc = null;
        public object m_pParam = null;
        public string m_strEventName = "";
        public string m_strPipeName = "";
        public IntPtr m_hStopEvent = IntPtr.Zero;
        public int m_iCtrlCmdEventID = -1;
        
        public PipeServerThread(IntPtr hStopEvent)
        {
            m_hStopEvent = hStopEvent;
        }

        public void Run()
        {
	        IntPtr hPipe = IntPtr.Zero;
	        IntPtr hEventCmdWait = IntPtr.Zero;
	        IntPtr hEventConnect = IntPtr.Zero;
	        IntPtr[] hEventArray = new IntPtr[2];
	        NativeOverlapped stOver = new NativeOverlapped();

 	        if( m_iCtrlCmdEventID != -1 ){
		        string strCmdEvent;
                strCmdEvent = CMD_CTRL_EVENT_WAIT + m_iCtrlCmdEventID.ToString();
                hEventCmdWait = CommonUtil._CreateEvent(false, true, strCmdEvent);
	        }
            hEventConnect = CommonUtil._CreateEvent(false, false, m_strEventName);
	        hEventArray[0] = m_hStopEvent;
            hEventArray[1] = CommonUtil._CreateEvent(false, false, null);

            while (true)
            {
                if (hPipe == IntPtr.Zero)
                {
                    while (true)
                    {
                        hPipe = CommonUtil._CreateNamedPipe(m_strPipeName,
                            CommonUtil.PIPE_ACCESS_DUPLEX | CommonUtil.FILE_FLAG_WRITE_THROUGH | CommonUtil.FILE_FLAG_OVERLAPPED,
                        CommonUtil.PIPE_TYPE_BYTE, 1,
                        SEND_BUFF_SIZE, RES_BUFF_SIZE, PIPE_TIMEOUT);
                        if (Marshal.GetLastWin32Error() == CommonUtil.ERROR_PIPE_BUSY)
                        {
                            Thread.Sleep(100);
                        }
                        else
                        {
                            if (hPipe == IntPtr.Zero)
                            {
                                hPipe = IntPtr.Zero;
                            }
                            break;
                        }
                    }
                    stOver.EventHandle = hEventArray[1];
                    CommonUtil._ConnectNamedPipe(hPipe, ref stOver);
                    CommonUtil._SetEvent(hEventConnect);
                }

                uint uiRes = CommonUtil._WaitForMultipleObjects(2, hEventArray, false, CommonUtil.INFINITE);
                if (uiRes == CommonUtil.WAIT_OBJECT_0)
                {
                    //STOP
                    break;
                }
                else if (uiRes == CommonUtil.WAIT_OBJECT_0 + 1)
                {
                    //ほかのサーバーで処理中？
                    if (hEventCmdWait != IntPtr.Zero)
                    {
                        CommonUtil._WaitForSingleObject(hEventCmdWait, CommonUtil.INFINITE);
                    }
                    //コマンド受信
                    if (m_pCmdProc != null)
                    {
                        CMD_STREAM stCmd = new CMD_STREAM();
                        CMD_STREAM stRes = new CMD_STREAM();
                        uint dwRead = 0;
                        uint dwWrite = 0;
                        do
                        {
                            byte[] bHead = new byte[8];

                            Array.Copy(BitConverter.GetBytes(stCmd.uiParam), 0, bHead, 0, sizeof(uint));
                            Array.Copy(BitConverter.GetBytes(stCmd.uiSize), 0, bHead, 4, sizeof(uint));
                            if (CommonUtil._ReadFile(hPipe, ref bHead, sizeof(uint) * 2, out dwRead, IntPtr.Zero) == false)
                            {
                                break;
                            }
                            stCmd.uiParam = BitConverter.ToUInt32(bHead, 0);
                            stCmd.uiSize = BitConverter.ToUInt32(bHead, 4); 
                            if (stCmd.uiSize > 0)
                            {
                                stCmd.bData = new byte[stCmd.uiSize];
                                uint dwReadNum = 0;
                                while (dwReadNum < stCmd.uiSize)
                                {
                                    uint dwReadSize = 0;
                                    if (stCmd.uiSize - dwReadNum < SEND_BUFF_SIZE)
                                    {
                                        dwReadSize = stCmd.uiSize - dwReadNum;
                                    }
                                    else
                                    {
                                        dwReadSize = SEND_BUFF_SIZE;
                                    }
                                    byte[] bRead = new byte[dwReadSize];
                                    if (CommonUtil._ReadFile(hPipe, ref bRead, dwReadSize, out dwRead, IntPtr.Zero) == false)
                                    {
                                        break;
                                    }
                                    Array.Copy(bRead, dwReadNum, stCmd.bData, 0, dwRead);
                                    dwReadNum += dwRead;
                                }
                                if (dwReadNum < stCmd.uiSize)
                                {
                                    break;
                                }
                            }

                            m_pCmdProc.Invoke(m_pParam, stCmd, ref stRes);
                            if (stRes.uiParam == (uint)ErrCode.CMD_NO_RES)
                            {
                                break;
                            }

                            Array.Copy(BitConverter.GetBytes(stRes.uiParam), 0, bHead, 0, sizeof(uint));
                            Array.Copy(BitConverter.GetBytes(stRes.uiSize), 0, bHead, 4, sizeof(uint));

                            if (CommonUtil._WriteFile(hPipe, ref bHead, sizeof(uint) * 2, out dwWrite, IntPtr.Zero) == false)
                            {
                                break;
                            }
                            if (stRes.uiSize > 0)
                            {
                                if (stRes.bData == null)
                                {
                                    break;
                                }
                                if (CommonUtil._WriteFile(hPipe, ref stRes.bData, stRes.uiSize, out dwWrite, IntPtr.Zero) == false)
                                {
                                    break;
                                }
                            }
                        } while (stRes.uiParam == (uint)ErrCode.CMD_NEXT); //Emun用の繰り返し
                    }
                    CommonUtil._FlushFileBuffers(hPipe);
                    CommonUtil._DisconnectNamedPipe(hPipe);
                    CommonUtil._CloseHandle(hPipe);
                    hPipe = IntPtr.Zero;
                    if (hEventCmdWait != IntPtr.Zero)
                    {
                        CommonUtil._SetEvent(hEventCmdWait);
                    }
                }
            }

            if (hPipe != IntPtr.Zero)
            {
                CommonUtil._FlushFileBuffers(hPipe);
                CommonUtil._DisconnectNamedPipe(hPipe);
                CommonUtil._CloseHandle(hPipe);
            }

            CommonUtil._CloseHandle(hEventArray[1]);
            CommonUtil._CloseHandle(hEventConnect);
            if (hEventCmdWait != IntPtr.Zero)
            {
                CommonUtil._CloseHandle(hEventCmdWait);
            }
        }
    }

    public class PipeServer
    {
        private Thread m_ServerThread = null;
        private IntPtr m_hStopEvent = IntPtr.Zero;

        public PipeServer()
        {
            m_hStopEvent = CommonUtil._CreateEvent(false, false, null);
        }

        ~PipeServer()
        {
            if (m_ServerThread != null)
            {
                CommonUtil._SetEvent(m_hStopEvent);
                m_ServerThread.Join();
                m_ServerThread = null;
            }
            CommonUtil._CloseHandle(m_hStopEvent);
            m_hStopEvent = IntPtr.Zero;
        }

        public bool StartServer(string strEventName, string strPipeName, CMD_CALLBACK_PROC pfnCmdProc, object pParam)
        {
            return StartServer(strEventName, strPipeName, pfnCmdProc, pParam, ThreadPriority.Normal, -1);
        }
        public bool StartServer(string strEventName, string strPipeName, CMD_CALLBACK_PROC pfnCmdProc, object pParam, ThreadPriority iThreadPriority, int iCtrlCmdEventID)
        {
            if (pfnCmdProc == null || strEventName.Length == 0 || strPipeName.Length == 0)
            {
                return false;
            }
            if (m_ServerThread != null)
            {
                return false;
            }

            PipeServerThread RunThread = new PipeServerThread(m_hStopEvent);
            RunThread.m_pCmdProc = pfnCmdProc;
            RunThread.m_pParam = pParam;
            RunThread.m_strEventName = strEventName;
            RunThread.m_strPipeName = strPipeName;
            RunThread.m_iCtrlCmdEventID = iCtrlCmdEventID;

            CommonUtil._ResetEvent(m_hStopEvent);
            m_ServerThread = new Thread(new ThreadStart(RunThread.Run));
            m_ServerThread.Priority = iThreadPriority;
            m_ServerThread.Start();

            return true;
        }

        public void StopServer()
        {
            if (m_ServerThread != null)
            {
                CommonUtil._SetEvent(m_hStopEvent);
                m_ServerThread.Join();
                m_ServerThread = null;
            }
        }


    }
}
