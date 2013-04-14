using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace EpgTimer
{
    [Flags]
    public enum EFileAccess : uint
    {
        /// <summary>
        /// 
        /// </summary>
        GenericRead = 0x80000000,
        /// <summary>
        /// 
        /// </summary>
        GenericWrite = 0x40000000,
        /// <summary>
        /// 
        /// </summary>
        GenericExecute = 0x20000000,
        /// <summary>
        /// 
        /// </summary>
        GenericAll = 0x10000000
    }

    [Flags]
    public enum EFileShare : uint
    {
        /// <summary>
        /// 
        /// </summary>
        None = 0x00000000,
        /// <summary>
        /// Enables subsequent open operations on an object to request read access. 
        /// Otherwise, other processes cannot open the object if they request read access. 
        /// If this flag is not specified, but the object has been opened for read access, the function fails.
        /// </summary>
        Read = 0x00000001,
        /// <summary>
        /// Enables subsequent open operations on an object to request write access. 
        /// Otherwise, other processes cannot open the object if they request write access. 
        /// If this flag is not specified, but the object has been opened for write access, the function fails.
        /// </summary>
        Write = 0x00000002,
        /// <summary>
        /// Enables subsequent open operations on an object to request delete access. 
        /// Otherwise, other processes cannot open the object if they request delete access.
        /// If this flag is not specified, but the object has been opened for delete access, the function fails.
        /// </summary>
        Delete = 0x00000004
    }

    public enum ECreationDisposition : uint
    {
        /// <summary>
        /// Creates a new file. The function fails if a specified file exists.
        /// </summary>
        New = 1,
        /// <summary>
        /// Creates a new file, always. 
        /// If a file exists, the function overwrites the file, clears the existing attributes, combines the specified file attributes, 
        /// and flags with FILE_ATTRIBUTE_ARCHIVE, but does not set the security descriptor that the SECURITY_ATTRIBUTES structure specifies.
        /// </summary>
        CreateAlways = 2,
        /// <summary>
        /// Opens a file. The function fails if the file does not exist. 
        /// </summary>
        OpenExisting = 3,
        /// <summary>
        /// Opens a file, always. 
        /// If a file does not exist, the function creates a file as if dwCreationDisposition is CREATE_NEW.
        /// </summary>
        OpenAlways = 4,
        /// <summary>
        /// Opens a file and truncates it so that its size is 0 (zero) bytes. The function fails if the file does not exist.
        /// The calling process must open the file with the GENERIC_WRITE access right. 
        /// </summary>
        TruncateExisting = 5
    }

    [Flags]
    public enum EFileAttributes : uint
    {
        Readonly = 0x00000001,
        Hidden = 0x00000002,
        System = 0x00000004,
        Directory = 0x00000010,
        Archive = 0x00000020,
        Device = 0x00000040,
        Normal = 0x00000080,
        Temporary = 0x00000100,
        SparseFile = 0x00000200,
        ReparsePoint = 0x00000400,
        Compressed = 0x00000800,
        Offline = 0x00001000,
        NotContentIndexed = 0x00002000,
        Encrypted = 0x00004000,
        Write_Through = 0x80000000,
        Overlapped = 0x40000000,
        NoBuffering = 0x20000000,
        RandomAccess = 0x10000000,
        SequentialScan = 0x08000000,
        DeleteOnClose = 0x04000000,
        BackupSemantics = 0x02000000,
        PosixSemantics = 0x01000000,
        OpenReparsePoint = 0x00200000,
        OpenNoRecall = 0x00100000,
        FirstPipeInstance = 0x00080000
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SECURITY_ATTRIBUTES
    {
        public int nLength;
        public IntPtr lpSecurityDescriptor;
        public int bInheritHandle;
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct SECURITY_DESCRIPTOR
    {
        public byte revision;
        public byte size;
        public short control;
        public IntPtr owner;
        public IntPtr group;
        public IntPtr sacl;
        public IntPtr dacl;
    }    
    
    class CommonUtil
    {
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern IntPtr CreateFile(
           string lpFileName,
           EFileAccess dwDesiredAccess,
           EFileShare dwShareMode,
           IntPtr lpSecurityAttributes,
           ECreationDisposition dwCreationDisposition,
           EFileAttributes dwFlagsAndAttributes,
           IntPtr hTemplateFile);

        [DllImport("kernel32.dll")]
        static extern bool ReadFile(IntPtr hFile, byte[] lpBuffer,
           uint nNumberOfBytesToRead, out uint lpNumberOfBytesRead, IntPtr lpOverlapped);
        [DllImport("kernel32.dll")]
        static extern bool ReadFile(IntPtr hFile, IntPtr lpBuffer,
           uint nNumberOfBytesToRead, out uint lpNumberOfBytesRead, IntPtr lpOverlapped);

        [DllImport("kernel32.dll")]
        static extern bool WriteFile(IntPtr hFile, byte[] lpBuffer,
           uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped);
        [DllImport("kernel32.dll")]
        static extern bool WriteFile(IntPtr hFile, IntPtr lpBuffer,
           uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll")]
        static extern IntPtr CreateEvent(IntPtr lpEventAttributes, bool bManualReset, bool bInitialState, string lpName);

        [DllImport("kernel32.dll")]
        static extern bool SetEvent(IntPtr hEvent);

        [DllImport("kernel32.dll")]
        static extern bool ResetEvent(IntPtr hEvent);
        
        [DllImport("kernel32", SetLastError = true)]
        static extern UInt32 WaitForSingleObject(IntPtr handle, uint milliseconds);
        [DllImport("kernel32.dll")]
        static extern uint WaitForMultipleObjects(uint nCount, IntPtr[] lpHandles,
           bool bWaitAll, uint dwMilliseconds);
        public const UInt32 INFINITE = 0xFFFFFFFF;
        public const UInt32 WAIT_ABANDONED = 0x00000080;
        public const UInt32 WAIT_OBJECT_0 = 0x00000000;
        public const UInt32 WAIT_TIMEOUT = 0x00000102;

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateNamedPipe(string lpName, uint dwOpenMode,
           uint dwPipeMode, uint nMaxInstances, uint nOutBufferSize, uint nInBufferSize,
           uint nDefaultTimeOut, IntPtr lpSecurityAttributes);
        public const uint CREATE_NEW = 1;
        public const uint CREATE_ALWAYS = 2;
        public const uint OPEN_EXISTING = 3;
        public const uint OPEN_ALWAYS = 4;
        public const uint TRUNCATE_EXISTING = 5;

        public const uint FILE_FLAG_WRITE_THROUGH = 0x80000000;
        public const uint FILE_FLAG_OVERLAPPED = 0x40000000;
        public const uint FILE_FLAG_NO_BUFFERING = 0x20000000;
        public const uint FILE_FLAG_RANDOM_ACCESS = 0x10000000;
        public const uint FILE_FLAG_SEQUENTIAL_SCAN = 0x08000000;
        public const uint FILE_FLAG_DELETE_ON_CLOSE = 0x04000000;
        public const uint FILE_FLAG_BACKUP_SEMANTICS = 0x02000000;
        public const uint FILE_FLAG_POSIX_SEMANTICS = 0x01000000;
        public const uint FILE_FLAG_OPEN_REPARSE_POINT = 0x00200000;
        public const uint FILE_FLAG_OPEN_NO_RECALL = 0x00100000;
        public const uint FILE_FLAG_FIRST_PIPE_INSTANCE = 0x00080000;

        public const int PIPE_ACCESS_INBOUND = 0x00000001;
        public const int PIPE_ACCESS_OUTBOUND = 0x00000002;
        public const int PIPE_ACCESS_DUPLEX = 0x00000003;
        public const int PIPE_CLIENT_END = 0x00000000;
        public const int PIPE_SERVER_END = 0x00000001;
        public const int PIPE_WAIT = 0x00000000;
        public const int PIPE_NOWAIT = 0x00000001;
        public const int PIPE_READMODE_BYTE = 0x00000000;
        public const int PIPE_READMODE_MESSAGE = 0x00000002;
        public const int PIPE_TYPE_BYTE = 0x00000000;
        public const int PIPE_TYPE_MESSAGE = 0x00000004;
        public const int PIPE_UNLIMITED_INSTANCES = 255;

        public const int ERROR_PIPE_BUSY = 231;


        [DllImport("kernel32.dll")]
        static extern bool ConnectNamedPipe(IntPtr hNamedPipe,
           [In] ref System.Threading.NativeOverlapped lpOverlapped);

        [DllImport("kernel32.dll")]
        static extern bool FlushFileBuffers(IntPtr hFile);

        [DllImport("kernel32.dll")]
        static extern bool DisconnectNamedPipe(IntPtr hNamedPipe);

        [DllImport("advapi32.dll", SetLastError = true)]
        static extern bool InitializeSecurityDescriptor(ref SECURITY_DESCRIPTOR sd, uint dwRevision);
        const uint SECURITY_DESCRIPTOR_REVISION = 1;

        [DllImport("advapi32.dll", SetLastError = true)]
        static extern bool SetSecurityDescriptorDacl(ref SECURITY_DESCRIPTOR sd, bool daclPresent, IntPtr dacl, bool daclDefaulted);

        public static IntPtr _CreateFile(
           string lpFileName,
           EFileAccess dwDesiredAccess,
           EFileShare dwShareMode,
           ECreationDisposition dwCreationDisposition,
           EFileAttributes dwFlagsAndAttributes,
           IntPtr hTemplateFile
            )
        {
            SECURITY_DESCRIPTOR sd = new SECURITY_DESCRIPTOR();
            InitializeSecurityDescriptor(ref sd, SECURITY_DESCRIPTOR_REVISION);
            SetSecurityDescriptorDacl(ref sd, true, IntPtr.Zero, false);
            GCHandle sdHandle = GCHandle.Alloc(sd, GCHandleType.Pinned); 

            SECURITY_ATTRIBUTES sa = new SECURITY_ATTRIBUTES();
            sa.nLength = Marshal.SizeOf(sa);
            sa.lpSecurityDescriptor = sdHandle.AddrOfPinnedObject(); 
            sa.bInheritHandle = 0;
            GCHandle saHandle = GCHandle.Alloc(sa, GCHandleType.Pinned); 

            System.IntPtr hFile = IntPtr.Zero;
            hFile = CreateFile(
                lpFileName,
                dwDesiredAccess,
                dwShareMode,
                saHandle.AddrOfPinnedObject(),
                dwCreationDisposition,
                dwFlagsAndAttributes,
                hTemplateFile
            );

            saHandle.Free();
            sdHandle.Free();
            if (hFile == (System.IntPtr)(int)-1)
            {
                return IntPtr.Zero;
            }
            return hFile;
        }

        public static bool _ReadFile(IntPtr hFile, ref byte[] lpBuffer,
           uint nNumberOfBytesToRead, out uint lpNumberOfBytesRead, IntPtr lpOverlapped)
        {
            if (hFile == IntPtr.Zero)
            {
                lpNumberOfBytesRead = 0;
                return false;
            }
            return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, out lpNumberOfBytesRead, lpOverlapped);
        }

        public static bool _ReadFile(IntPtr hFile, IntPtr lpBuffer,
           uint nNumberOfBytesToRead, out uint lpNumberOfBytesRead, IntPtr lpOverlapped)
        {
            if (hFile == IntPtr.Zero)
            {
                lpNumberOfBytesRead = 0;
                return false;
            }
            return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, out lpNumberOfBytesRead, lpOverlapped);
        }

        public static bool _WriteFile(IntPtr hFile, ref byte[] lpBuffer,
           uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped)
        {
            if (hFile == IntPtr.Zero)
            {
                lpNumberOfBytesWritten = 0;
                return false;
            }
            return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, out lpNumberOfBytesWritten, lpOverlapped);
        }

        public static bool _WriteFile(IntPtr hFile, IntPtr lpBuffer,
           uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped)
        {
            if (hFile == IntPtr.Zero)
            {
                lpNumberOfBytesWritten = 0;
                return false;
            }
            return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, out lpNumberOfBytesWritten, lpOverlapped);
        }

        public static bool _CloseHandle(IntPtr hObject)
        {
            if (hObject == IntPtr.Zero)
            {
                return false;
            }
            return CloseHandle(hObject);
        }

        public static IntPtr _CreateEvent(bool bManualReset, bool bInitialState, string lpName)
        {
            SECURITY_DESCRIPTOR sd = new SECURITY_DESCRIPTOR();
            InitializeSecurityDescriptor(ref sd, SECURITY_DESCRIPTOR_REVISION);
            SetSecurityDescriptorDacl(ref sd, true, IntPtr.Zero, false);
            GCHandle sdHandle = GCHandle.Alloc(sd, GCHandleType.Pinned);

            SECURITY_ATTRIBUTES sa = new SECURITY_ATTRIBUTES();
            sa.nLength = Marshal.SizeOf(sa);
            sa.lpSecurityDescriptor = sdHandle.AddrOfPinnedObject();
            sa.bInheritHandle = 0;
            GCHandle saHandle = GCHandle.Alloc(sa, GCHandleType.Pinned);

            System.IntPtr hEvent = IntPtr.Zero;
            hEvent = CreateEvent(
                saHandle.AddrOfPinnedObject(),
                bManualReset,
                bInitialState,
                lpName
            );

            saHandle.Free();
            sdHandle.Free();
            if (hEvent == (System.IntPtr)(int)-1)
            {
                return IntPtr.Zero;
            }
            return hEvent;
        }

        public static UInt32 _WaitForSingleObject(IntPtr handle, uint milliseconds)
        {
            return WaitForSingleObject(handle, milliseconds);
        }

        public static uint _WaitForMultipleObjects(uint nCount, IntPtr[] lpHandles,
           bool bWaitAll, uint dwMilliseconds)
        {
            return WaitForMultipleObjects(nCount, lpHandles, bWaitAll, dwMilliseconds);
        }

        public static IntPtr _CreateNamedPipe(string lpName, uint dwOpenMode,
           uint dwPipeMode, uint nMaxInstances, uint nOutBufferSize, uint nInBufferSize,
           uint nDefaultTimeOut)
        {
            SECURITY_DESCRIPTOR sd = new SECURITY_DESCRIPTOR();
            InitializeSecurityDescriptor(ref sd, SECURITY_DESCRIPTOR_REVISION);
            SetSecurityDescriptorDacl(ref sd, true, IntPtr.Zero, false);
            GCHandle sdHandle = GCHandle.Alloc(sd, GCHandleType.Pinned);

            SECURITY_ATTRIBUTES sa = new SECURITY_ATTRIBUTES();
            sa.nLength = Marshal.SizeOf(sa);
            sa.lpSecurityDescriptor = sdHandle.AddrOfPinnedObject();
            sa.bInheritHandle = 0;
            GCHandle saHandle = GCHandle.Alloc(sa, GCHandleType.Pinned);

            System.IntPtr hPipe = IntPtr.Zero;
            hPipe = CreateNamedPipe(
                lpName,
                dwOpenMode,
                dwPipeMode,
                nMaxInstances,
                nOutBufferSize,
                nInBufferSize,
                nDefaultTimeOut,
                saHandle.AddrOfPinnedObject()
            );

            saHandle.Free();
            sdHandle.Free();
            if (hPipe == (System.IntPtr)(int)-1)
            {
                return IntPtr.Zero;
            }
            return hPipe;
        }

        public static bool _ConnectNamedPipe(IntPtr hNamedPipe,
           [In] ref System.Threading.NativeOverlapped lpOverlapped)
        {
            return ConnectNamedPipe(hNamedPipe, ref lpOverlapped);
        }

        public static bool _FlushFileBuffers(IntPtr hFile)
        {
            return FlushFileBuffers(hFile);
        }

        public static bool _DisconnectNamedPipe(IntPtr hNamedPipe)
        {
            return DisconnectNamedPipe(hNamedPipe);
        }

        public static bool _SetEvent(IntPtr hEvent)
        {
            return SetEvent(hEvent);
        }

        public static bool _ResetEvent(IntPtr hEvent)
        {
            return ResetEvent(hEvent);
        }

        [DllImport("user32.dll")]
        static extern bool GetLastInputInfo(ref LASTINPUTINFO plii);

        // Struct we'll need to pass to the function
        internal struct LASTINPUTINFO
        {
            public uint cbSize;
            public uint dwTime;
        }

        public static int GetIdleTimeSec()
        {
            // Get the system uptime
            int systemUptime = Environment.TickCount;
            // The tick at which the last input was recorded
            int LastInputTicks = 0;
            // The number of ticks that passed since last input
            int IdleTicks = 0;

            // Set the struct
            LASTINPUTINFO LastInputInfo = new LASTINPUTINFO();
            LastInputInfo.cbSize = (uint)Marshal.SizeOf(LastInputInfo);
            LastInputInfo.dwTime = 0;

            // If we have a value from the function
            if (GetLastInputInfo(ref LastInputInfo))
            {
                // Get the number of ticks at the point when the last activity was seen
                LastInputTicks = (int)LastInputInfo.dwTime;
                // Number of idle ticks = system uptime ticks - number of ticks at last input
                IdleTicks = systemUptime - LastInputTicks;
            }
            return IdleTicks / 1000;
        }
    }
}
