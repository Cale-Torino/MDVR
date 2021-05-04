using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

/// <summary>
///	Date: 2020/01/11
///	Author: C.A Torino
///	Description: Libnetclient parameter test unmanaged C++ to C#
/// </summary>

namespace libnetclient_test
{
    public class GPSMCMsg
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct tagGPSMCMsg
        {
            [MarshalAs(UnmanagedType.I4)]
            public int nMsgType;
            [MarshalAs(UnmanagedType.I4)]
            public int nResult;
            [MarshalAs(UnmanagedType.SysUInt, SizeConst = 6)]
            public IntPtr pParam;//6
            [MarshalAs(UnmanagedType.SysUInt, SizeConst = 1024)]
            public IntPtr pMngCmdClass;
            //[MarshalAs(UnmanagedType.ByValArray)]
            //public byte[] pParam;//6
            //[MarshalAs(UnmanagedType.ByValArray)]
            //public byte[] pMngCmdClass;
        }
    }
}
