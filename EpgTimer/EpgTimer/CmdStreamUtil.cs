using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EpgTimer
{
    public class NotifySrvInfo
    {
        public UInt32 notifyID;
        public DateTime time;
        public UInt32 param1;
        public UInt32 param2;
        public UInt32 param3;
        public String param4;
        public String param5;
        public String param6;

        public NotifySrvInfo()
        {
            notifyID = 0;
            time = new DateTime();
            param1 = 0;
            param2 = 0;
            param3 = 0;
            param4 = "";
            param5 = "";
            param6 = "";
        }
    }

    public class CmdStreamUtil
    {
        private static bool ReadData(UInt16 ver, ref String val, byte[] buff, ref int startIndex)
        {
            try
            {
                int iStrSize = 0;
                Encoding uniEnc = Encoding.GetEncoding("unicode");

                iStrSize = BitConverter.ToInt32(buff, startIndex);
                startIndex += sizeof(int);
                iStrSize -= sizeof(int)+2;
                if (iStrSize > 0)
                {
                    val = uniEnc.GetString(buff, startIndex, iStrSize);
                }
                startIndex += iStrSize + 2;
            }
            catch
            {
                return false;
            }
            return true;
        }
        private static bool ReadData(UInt16 ver, ref UInt32 val, byte[] buff, ref int startIndex)
        {
            try
            {
                val = BitConverter.ToUInt32(buff, startIndex);
                startIndex += sizeof(UInt32);
            }
            catch
            {
                return false;
            }
            return true;
        }
        private static bool ReadData(UInt16 ver, ref DateTime val, byte[] buff, ref int startIndex)
        {
            try
            {
                Int16 yy = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                Int16 mm = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                //wDayOfWeek
                startIndex += sizeof(Int16);
                Int16 dd = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                Int16 h = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                Int16 m = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                Int16 s = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                Int16 ms = BitConverter.ToInt16(buff, startIndex);
                startIndex += sizeof(Int16);
                val = new DateTime(yy, mm, dd, h, m, s, ms, DateTimeKind.Utc);
            }
            catch
            {
                return false;
            }
            return true;
        }

        public static bool ReadStreamData(ref String value, CMD_STREAM cmd)
        {
            int iPos = 0;
            int iStrSize = 0;
            Encoding uniEnc = Encoding.GetEncoding("unicode");

            if (cmd.uiSize != cmd.bData.Length)
            {
                return false;
            }

            iStrSize = BitConverter.ToInt32(cmd.bData, iPos);
            iPos += sizeof(int);
            iStrSize -= sizeof(int) + 2;

            value = uniEnc.GetString(cmd.bData, iPos, iStrSize);
            iPos += iStrSize;

            return true;
        }

        public static bool ReadStreamData(ref UInt16 value, CMD_STREAM cmd)
        {
            int iPos = 0;

            if (cmd.uiSize != cmd.bData.Length)
            {
                return false;
            }

            value = BitConverter.ToUInt16(cmd.bData, iPos);
            iPos += sizeof(UInt16);

            return true;
        }

        public static bool ReadStreamData(ref NotifySrvInfo value, CMD_STREAM cmd)
        {
            try
            {
                int iPos = 0;

                UInt16 ver = BitConverter.ToUInt16(cmd.bData, iPos);
                iPos += sizeof(UInt16);
                UInt32 size = BitConverter.ToUInt32(cmd.bData, iPos);
                iPos += sizeof(UInt32);

                if (size > cmd.bData.Length - 2)
                {
                    return false;
                }

                if (ReadData(ver, ref value.notifyID, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.time, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.param1, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.param2, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.param3, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.param4, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.param5, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
                if (ReadData(ver, ref value.param6, cmd.bData, ref iPos) == false)
                {
                    return false;
                }
            }
            catch
            {
                return false;
            }
            return true;
        }

        public static bool CreateStreamData(int value, ref CMD_STREAM cmd)
        {
            cmd.uiSize = sizeof(uint);
            cmd.bData = new byte[cmd.uiSize];

            int iPos = 0;

            Array.Copy(BitConverter.GetBytes(value), 0, cmd.bData, iPos, sizeof(uint));
            iPos += sizeof(uint);

            return true;
        }
    }
}
