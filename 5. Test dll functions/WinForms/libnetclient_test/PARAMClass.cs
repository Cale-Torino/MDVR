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
    public class PARAMClass
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct tagGPSConfigData
        {
            [MarshalAs(UnmanagedType.I4)]
            public int nLength;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 1024)]
            public string cBuffer;
        }
    }
}
