using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace EpgTimer
{
    class WritePlugInClass
    {
        [DllImport("kernel32", CharSet = CharSet.Auto, ExactSpelling = false)]
        private extern static IntPtr LoadLibrary(String lpFileName);

        [DllImport("kernel32", ExactSpelling = true)]
        private extern static bool FreeLibrary(IntPtr hModule);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true)]
        private extern static IntPtr GetProcAddress(IntPtr hModule, String lpProcName);


        delegate void _Setting(IntPtr parentWnd);
        delegate UInt32 _GetPlugInName([MarshalAs(UnmanagedType.LPWStr)]StringBuilder name, ref UInt32 nameSize);

        public void Setting(String dllFilePath, IntPtr parentWnd)
        {
            IntPtr module = LoadLibrary(dllFilePath);

            IntPtr func = GetProcAddress(module, "Setting");
            _Setting settingDelegate = Marshal.GetDelegateForFunctionPointer(func, typeof(_Setting)) as _Setting;
            settingDelegate(parentWnd);

            if (module != IntPtr.Zero)
            {
                FreeLibrary(module);
            }
        }

        public UInt32 GetPlugInName(String dllFilePath, ref String name)
        {
            UInt32 ret = 0;
            IntPtr module = LoadLibrary(dllFilePath);
            if (module == IntPtr.Zero)
            {
                return 0;
            }

            IntPtr func = GetProcAddress(module, "GetPlugInName");
            _GetPlugInName getNameDelegate = Marshal.GetDelegateForFunctionPointer(func, typeof(_GetPlugInName)) as _GetPlugInName;
            StringBuilder _name = new StringBuilder(256);
            UInt32 nameSize = 256;
            ret = getNameDelegate(_name, ref nameSize);
            if (ret == 1)
            {
                name = _name.ToString();
            }
            if (module != IntPtr.Zero)
            {
                FreeLibrary(module);
            }
            return ret;
        }
    }
}
