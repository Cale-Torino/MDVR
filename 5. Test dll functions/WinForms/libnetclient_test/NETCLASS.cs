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
	//DELEGATES
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate void FUNLoginMsgCB(int nMsg, Form1 form1);

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate void FUNMCMsgCB(ref GPSMCMsg.tagGPSMCMsg data, Form1 form1);//ref GPSMCMsg.tagGPSMCMsg data

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate void FUNUserTransparentCB(int nType, string pDataBuf, int nDataLen, Form1 form1);

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate void FUNDownDevCBEx(int nType, IntPtr pData, Form1 form1);//ref Intptr

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate void FUNMsgCB(int nMsg, int nParam, Form1 form1);

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate void FUNDataCB(string pBuf, int nLen, long nPos, Form1 form1);

	class NETCLASS
    {
		//----------------------------------------------------------------------------
		//----------------------------------------------------------------------------
		//LOGIN
		//----------------------------------------------------------------------------
		//----------------------------------------------------------------------------
		//RegLoginMsg CALLBACK
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_RegLoginMsg(Form1 form1, FUNLoginMsgCB _callback);
		//----------------------------------------------------------------------------
		//NETCLIENT_Initialize 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_Initialize(int bPriorRGB16);
		//----------------------------------------------------------------------------
		//NETCLIENT_SetRecntCount 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]

		public static extern void NETCLIENT_SetRecntCount(int nCount);
		//----------------------------------------------------------------------------
		//NETCLIENT_LoginDirSvr 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_LoginDirSvr(string pSvrIP, int usPort, string szCompany, string szUsr, string szPwd, int nType);
		//----------------------------------------------------------------------------
		//NETCLIENT_LogoutDirSvr 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_LogoutDirSvr();
		//----------------------------------------------------------------------------
		//NETCLIENT_GetSvrVersion 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_GetSvrVersion();
		//----------------------------------------------------------------------------
		//NETCLIENT_SetUserSvrInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_SetUserSvrInfo(string pSvrIP, int usPort);
		//----------------------------------------------------------------------------
		//NETCLIENT_UnInitialize 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern void NETCLIENT_UnInitialize();
		//----------------------------------------------------------------------------
		//NETCLIENT_CheckOnline 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_CheckOnline(string szDevIDNO, string szServer, int usPort);

		//----------------------------------------------------------------------------
		//----------------------------------------------------------------------------
		//MC CLASS
		//----------------------------------------------------------------------------
		//----------------------------------------------------------------------------
		//NETCLIENT_MCStartWork
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCStartWork();
		//----------------------------------------------------------------------------
		//NETCLIENT_MCStopWork 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern void NETCLIENT_MCStopWork();
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCRegMsgCB(Form1 form1, FUNMCMsgCB _callback);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCReleaseMsg(ref GPSMCMsg.tagGPSMCMsg data);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCReleaseHandle(IntPtr lHandle);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCTransparentConfig(string szDevIDNO, int nType, ref PARAMClass.tagGPSConfigData data, Form1 form1, FUNMCMsgCB _callback, ref IntPtr lpHandle);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCTransparentPortData(string szDevIDNO, int nType, string data, int nLength, Form1 form1, FUNMCMsgCB _callback, ref IntPtr lpHandle);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCTransparentConfigEx(string szDevIDNO, int nType, ref PARAMClass.tagGPSConfigData data, Form1 form1, FUNMCMsgCB _callback, ref IntPtr lpHandle);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCCheckCtrlUsr(string szUsr, string szPwd);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCSendText(string szDevIDNO, string szText, Form1 form1, FUNMCMsgCB _callback);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCSendCtrl(string szDevIDNO, int nCtrlType, string szUsr, string szPwd);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCReadDevStatus(string szDevIDNO, Form1 form1, FUNMCMsgCB _callback);
		//----------------------------------------------------------------------------
		//NETCLIENT_DOWNCloseAppInfo 
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_MCReadNetFlowStatistics(string szDevIDNO, Form1 form1, FUNMCMsgCB _callback, ref IntPtr lpHandle);

		//=============================Data is transparently transmitted to the server====================================//
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_OpenUserTransparent(ref IntPtr lHandle);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_RegUserTransparentCB(IntPtr lHandle, Form1 form1, FUNUserTransparentCB _callback);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_SetUserTransData(IntPtr lHandle, string pDataBuf, int nDataLen);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_StartUserTransparent(IntPtr lHandle);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_StopUserTransparent(IntPtr lHandle);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_CloseUserTransparent(IntPtr lHandle);

		//=============================Device list====================================//
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVOpenDevDownEx(ref IntPtr lHandle);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVSetCharEx(IntPtr lHandle, bool bUtf8 = true);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVSetStringMode(IntPtr lHandle, bool bStrMode = true);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVRegDevDownCBEx(IntPtr lHandle, Form1 form1, FUNDownDevCBEx _callback);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVStartDevDownEx(IntPtr lHandle, int nMgrType, int nDevType);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVStopDevDownEx(IntPtr lHandle);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DEVCloseDevDownEx(IntPtr lHandle);

		//=============================Get device parameters====================================//
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DLOpenGetDevCfg(ref IntPtr lpGetDevCfg, string szDevIDNO);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DLSetGetDCfgMsgCB(IntPtr lpGetDevCfg, Form1 form1, FUNMsgCB _callback);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DLSetGetDCfgDataCB(IntPtr lpGetDevCfg, Form1 form1, FUNDataCB _callback);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DLStartGetDevCfg(IntPtr lpGetDevCfg);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DLStopGetDevCfg(IntPtr lpGetDevCfg);
		[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern int NETCLIENT_DLCloseGetDevCfg(IntPtr lpGetDevCfg);
	}
}
