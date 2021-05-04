using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libnetclient_test
{
    class GPSDEVRelation
    {
        [StructLayout(LayoutKind.Sequential, Pack =4)]
        public struct _tagGPSVehiDevRelation
        {
            //struct now in proper sequence 
            [MarshalAs(UnmanagedType.I4)]
            public int nID;//Device Index
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string szName;//Device Name
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string szIDNO;//Device id
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
            public string szSIMCard;//simcard
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 40)]
            public string szChnAttr;//device main type MDVR, MOBILE,
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 40)]
            public string szIOInAttr;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 40)]
            public string szIOOutAttr;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 40)]
            public string szTempAttr;
            [MarshalAs(UnmanagedType.I4)]
            public int nMoudle;
            [MarshalAs(UnmanagedType.I4)]
            public int nDevType;
            [MarshalAs(UnmanagedType.I4)]
            public int nDevSubType;
            [MarshalAs(UnmanagedType.I4)]
            public int cMainDevFlag;
            [MarshalAs(UnmanagedType.I4)]
            public int cProtocol;
            [MarshalAs(UnmanagedType.I4)]
            public int cAudioCodec;//actual online
            [MarshalAs(UnmanagedType.I4)]//----------------
            public int cDiskType;
            [MarshalAs(UnmanagedType.I4)]
            public int cFactoryType;
            [MarshalAs(UnmanagedType.I4)]
            public int cFactoryDevType;
            [MarshalAs(UnmanagedType.I4)]
            public int ucMapValid;
            [MarshalAs(UnmanagedType.I4)]
            public int ucMapType;
            [MarshalAs(UnmanagedType.I4)]
            public int nOnline;
            [MarshalAs(UnmanagedType.I4)]
            public int nJingDu;
            [MarshalAs(UnmanagedType.I4)]
            public int nWeiDu;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string ucIoInNum;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string ucTempSensorNum;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string ucPlateColor;
        }
    }
}
