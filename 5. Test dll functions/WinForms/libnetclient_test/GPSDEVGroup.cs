using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libnetclient_test
{
    class GPSDEVGroup
    {
        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct _tagGPSDEVGroup
        {
            [MarshalAs(UnmanagedType.I4)]
            public int nID;//Group Index
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string szName;//Group Name
            [MarshalAs(UnmanagedType.I4)]
            public int nParent;//Parent Group,  -1 : no Parent
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 48)]
            public string szRemarks;//
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 15)]
            public string cLevel;//0,1,2 3
            [MarshalAs(UnmanagedType.LPUTF8Str)]
            public string cReserve;//�����ֶ�
        }
    }
}
