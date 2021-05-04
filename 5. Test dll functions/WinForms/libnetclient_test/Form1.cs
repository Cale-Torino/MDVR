using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

/// <summary>
///	Date: 2020/01/11
///	Author: C.A Torino
///	Description: Libnetclient parameter test unmanaged C++ to C#
/// </summary>

namespace libnetclient_test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        public static class ThreadHelperClass
        {
            delegate void SetTextCallback(Form f, Control ctrl, string text);
            public static void SetText(Form form, Control ctrl, string text)
            {
                if (ctrl.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetText);
                    form.Invoke(d, new object[] { form, ctrl, text });
                }
                else
                {
                    ctrl.Text = text;
                }
            }
        }

        static void FUNLoginMsgCB(int _nMsg, Form1 form1)
        {
            switch (_nMsg)
            {
                case 0:
                    MessageBox.Show("GPS_LOGIN_SUC");
                    break;
                case 1:
                    MessageBox.Show("GPS_LOGIN_FAILED");
                    break;
                case 2:
                    MessageBox.Show("GPS_LOGIN_DISCNT");
                    break;
                case 3:
                    MessageBox.Show("GPS_LOGIN_NAME_ERR");
                    break;
                case 4:
                    MessageBox.Show("GPS_LOGIN_PWD_ERR");
                    break;
                case 5:
                    MessageBox.Show("GPS_LOGIN_FULL_ERR");
                    break;
                case 6:
                    MessageBox.Show("GPS_LOGIN_VER_ERR");
                    break;
                case 7:
                    MessageBox.Show("GPS_LOGIN_USR_CHANGE");
                    break;
                case 8:
                    MessageBox.Show("GPS_LOGIN_USR_DEL");
                    break;
                case 9:
                    MessageBox.Show("GPS_LOGIN_EXPIRED");
                    break;
                case 10:
                    MessageBox.Show("GPS_LOGIN_SERVER_EMPTY");
                    break;
                case 11:
                    MessageBox.Show("GPS_LOGIN_PRIVILEGE_CHANGE");
                    break;
                case 12:
                    MessageBox.Show("GPS_LOGIN_SVR_CONFIG_CHANGE");
                    break;
                default:
                    MessageBox.Show("UNKNOWN");
                    break;
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                button1.Enabled = false;
                button2.Enabled = true;
                groupBox2.Enabled = true;
                int _ini = NETCLASS.NETCLIENT_Initialize(0);
                int _MCStartWork = NETCLASS.NETCLIENT_MCStartWork();
                //NETCLASS.AVDEC_Initialize(0);
                //NETCLASS.NETMEDIA_Initialize(0, 128, 2000, 2);
                //NETCLASS.NETCLIENT_SetRecntCount(5);
                FUNLoginMsgCB _callback = new FUNLoginMsgCB(FUNLoginMsgCB);
                int callback = NETCLASS.NETCLIENT_RegLoginMsg(this, _callback);
                int _LoginDirSvr = NETCLASS.NETCLIENT_LoginDirSvr(textBox1.Text, int.Parse(numericUpDown1.Text), "", textBox2.Text, textBox3.Text, 1);
                int _GetSvrVersion = NETCLASS.NETCLIENT_GetSvrVersion();                
                int _SetUserSvrInfo = NETCLASS.NETCLIENT_SetUserSvrInfo(textBox1.Text, int.Parse(numericUpDown1.Text));
                textBox4.AppendText("Initialize = " + _ini.ToString() + Environment.NewLine+
                    "MCStartWork = " + _MCStartWork.ToString() + Environment.NewLine+
                    "RegLoginMsg = " + callback.ToString() + Environment.NewLine+
                    "LoginDirSvr = " + _LoginDirSvr.ToString() + Environment.NewLine+
                    "GetSvrVersion = " + _GetSvrVersion.ToString() + Environment.NewLine+
                    "SetUserSvrInfo = " + _SetUserSvrInfo.ToString() + Environment.NewLine);
                button2.Focus();
                button2.Select();
            }
            catch (Exception _ex)
            {
                button1.Enabled = true;
                button2.Enabled = false;
                groupBox2.Enabled = false;
                MessageBox.Show(_ex.ToString(), "Login Exception");
                return;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                button1.Enabled = true;
                button2.Enabled = false;
                groupBox2.Enabled = false;
                int _callback = NETCLASS.NETCLIENT_RegLoginMsg(null, null);
                NETCLASS.NETCLIENT_MCStopWork();
                NETCLASS.NETCLIENT_UnInitialize();
                int _LogoutDirSvr = NETCLASS.NETCLIENT_LogoutDirSvr();
                MessageBox.Show("Logout = " + _LogoutDirSvr.ToString() +
                Environment.NewLine + "NETCLIENT_RegLoginMsg = " + _callback.ToString());
                button1.Focus();
                button1.Select();
            }
            catch (Exception _ex)
            {
                button1.Enabled = false;
                button2.Enabled = true;
                groupBox2.Enabled = true;
                MessageBox.Show(_ex.ToString(), "Logout Exception");
                return;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                int _online = NETCLASS.NETCLIENT_CheckOnline(textBox7.Text, textBox1.Text, int.Parse(numericUpDown1.Text));
                MessageBox.Show("Device On = " + _online.ToString());
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Device On Exception");
                return;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                FUNMCMsgCB _callback = new FUNMCMsgCB(FUNMCMsgCB);
                string _pData = "Hello this is a test";
                int _result = NETCLASS.NETCLIENT_MCSendText(textBox7.Text, _pData, this, _callback);
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Param List Exception");
                return;
            }
        }
        public void FUNUserTransparentCB(int nType, string pDataBuf, int nDataLen, Form1 form1)
        {
            MessageBox.Show("nResult=" + nType + " pDataBuf=" + pDataBuf + " nDataLen=" + nDataLen);
        }
        public void FUNMCMsgCB(ref GPSMCMsg.tagGPSMCMsg _data, Form1 form1)
        {
            //https://stackoverflow.com/questions/16614704/pass-c-sharp-struct-by-reference
            int _nMsgType = _data.nMsgType;
            int _nResult = _data.nResult;
            string _pMngCmdClass = Marshal.PtrToStringAnsi(_data.pMngCmdClass);
            PARAMClass.tagGPSConfigData tmp = new PARAMClass.tagGPSConfigData();
            tmp = Marshal.PtrToStructure<PARAMClass.tagGPSConfigData>(_data.pParam);
            string cBuffer = tmp.cBuffer;
            switch (_nMsgType)
            {
                case 0:
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 0=" + _nResult + Environment.NewLine)));
                    break;
                case 1:
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 1=" + _nResult + Environment.NewLine)));
                    break;
                case 2:
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 2=" + _nResult + Environment.NewLine)));
                    break;
                case 3:
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 3=" + _nResult + Environment.NewLine)));
                    break;
                case 4:
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 4=" + _nResult + Environment.NewLine)));
                    break;
                case 5:
                    NETCLASS.NETCLIENT_MCReleaseMsg(ref _data);
                    NETCLASS.NETCLIENT_MCReleaseHandle(_lHandle);
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 5=" + _nResult + "pParam=" + cBuffer + " pMngCmdClass=" + _pMngCmdClass + Environment.NewLine)));
                    break;
                case 25:
                    NETCLASS.NETCLIENT_MCReleaseMsg(ref _data);
                    NETCLASS.NETCLIENT_MCReleaseHandle(_lHandle);
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case 25=" + _nResult +"pParam="+ cBuffer + " pMngCmdClass=" + _pMngCmdClass + Environment.NewLine)));
                    break;
                default:
                    form1.Invoke((MethodInvoker)(() => textBox4.AppendText("case default="+ _nMsgType+" Result=" + _nResult + Environment.NewLine)));
                    break;
            }
            //MessageBox.Show("nResult=" + _nResult + " nMsgType=" + _nMsgType + " pParam=" + _pParam + " pMngCmdClass=" + _pMngCmdClass);
        }
        static IntPtr _lHandle = IntPtr.Zero;
        private void button6_Click(object sender, EventArgs e)
        {
            try
            {
                FUNMCMsgCB _callback = new FUNMCMsgCB(FUNMCMsgCB);
                string _pData = "<Control_system><MESSAGE_ID>2</MESSAGE_ID><MESSAGE_TYPE>2</MESSAGE_TYPE><Control_Type>10</Control_Type><Control_State>0</Control_State></Control_system>";
                int _nLen = _pData.Length;
                int _resultport = NETCLASS.NETCLIENT_MCTransparentPortData(textBox7.Text, 0, _pData, _pData.Length, this, _callback, ref _lHandle);
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Param List Exception");
                return;
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            try
            {
                FUNMCMsgCB _callback = new FUNMCMsgCB(FUNMCMsgCB);
                int _result = NETCLASS.NETCLIENT_MCReadNetFlowStatistics(textBox7.Text, this, _callback, ref _lHandle);
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Param List Exception");
                return;
            }
        }
        private void button7_Click(object sender, EventArgs e)
        {
            try
            {
                FUNMCMsgCB _callback = new FUNMCMsgCB(FUNMCMsgCB);
                NETCLASS.NETCLIENT_MCReadDevStatus(textBox7.Text, this, _callback);
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Param List Exception");
                return;
            }
        }
        private void button8_Click(object sender, EventArgs e)
        {
            try
            {
                int _result = NETCLASS.NETCLIENT_MCCheckCtrlUsr(textBox2.Text, textBox3.Text);
                MessageBox.Show("Device On = " + _result.ToString());
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Param List Exception");
                return;
            }
        }
        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                FUNMCMsgCB _callback = new FUNMCMsgCB(FUNMCMsgCB);
                int _result = NETCLASS.NETCLIENT_MCSendCtrl(textBox7.Text, 5, textBox2.Text, textBox3.Text);//ctrl 5 means reboot
                MessageBox.Show("Device On = " + _result.ToString());
            }
            catch (Exception _ex)
            {
                MessageBox.Show(_ex.ToString(), "Param List Exception");
                return;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Focus();
            button1.Select();
            textBox1.Text = "000.000.000.000";//ip
            textBox2.Text = "demo";//user
            textBox3.Text = "demo311010";//password
            textBox7.Text = "00001";//device id
            numericUpDown1.Text = "6605";//port
            button2.Enabled = false;
            groupBox2.Enabled = false;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            //IntPtr _lHandle = IntPtr.Zero;
            string _pData = "<Param_System_Info><MESSAGE_ID>1</MESSAGE_ID><MESSAGE_TYPE>1</MESSAGE_TYPE></Param_System_Info>";
            PARAMClass.tagGPSConfigData tmp = new PARAMClass.tagGPSConfigData();
            int _nLen = _pData.Length;
            tmp.cBuffer = _pData;
            tmp.nLength = _nLen;
            FUNMCMsgCB _callback = new FUNMCMsgCB(FUNMCMsgCB);
            //GC.Collect();//garbage collection so call back chills out!
            //GC.WaitForPendingFinalizers();
            //GC.Collect();
            //GC.KeepAlive(_callback);
            NETCLASS.NETCLIENT_MCRegMsgCB(this, _callback);
            int _result = NETCLASS.NETCLIENT_MCTransparentConfig(textBox7.Text, 0, ref tmp, this, _callback, ref _lHandle);
            MessageBox.Show(tmp.nLength+tmp.cBuffer);
        }

        public void FUNDownDevCBEx(int mType, IntPtr pData, Form1 form1)
        {
            if (pData == null || form1 == null) { MessageBox.Show("NULL EXCLUSION"); }
            try
            {
                GPSDEVRelation._tagGPSVehiDevRelation p = new GPSDEVRelation._tagGPSVehiDevRelation(); // Create the managed struct
                p = Marshal.PtrToStructure<GPSDEVRelation._tagGPSVehiDevRelation>(pData);
                int a = p.nID;
                string b = p.szName;
                string c = p.szIDNO;
                string d = p.szSIMCard;

                /*                
                GPSDEVGroup._tagGPSDEVGroup pg = new GPSDEVGroup._tagGPSDEVGroup(); // Create the managed struct
                pg = Marshal.PtrToStructure<GPSDEVGroup._tagGPSDEVGroup>(pData);
                int nIDpg = pg.nID;
                string szNamepg = pg.szName;
                int nParentpg = pg.nParent;
                string szRemarkspg = pg.szRemarks;
                string cLevelpg = pg.cLevel;
                string cReservepg = pg.cReserve;
                 */

                //GPSDevDown.tagGPSDEVDevInfo pi = new GPSDevDown.tagGPSDEVDevInfo(); // Create the managed struct
                //pi = Marshal.PtrToStructure<GPSDevDown.tagGPSDEVDevInfo>(pData);
                //int nIDpi = pi.nID;//Device Index
                //string szNamepi = pi.szName;//Device Name
                //string szIDNOpi = pi.szIDNO;//Device id
                //int nTypepi = pi.nType;//0 :Encoder, 1 :Decoder

                switch (mType)
                {
                    case 0:
                        //form1.Invoke((MethodInvoker)(() => form1.textBox4.AppendText("DEV nIDpi=" + nIDpi + " szNamepi=" + szNamepi + " szIDNOpi=" + szIDNOpi + Environment.NewLine)));
                        break;
                    case 1:
                        //form1.Invoke((MethodInvoker)(() => form1.textBox4.AppendText("==============================="+Environment.NewLine)));
                        //form1.Invoke((MethodInvoker)(() => form1.textBox4.AppendText("GROUP nID=" + nIDpg + "  szNamepg=" + szNamepg + "  nParentpg=" + nParentpg + Environment.NewLine)));
                        break;
                    case 2:
                        Invoke((MethodInvoker)(() => MessageBox.Show("GPS_DEV_DOWN_FAILED")));
                        //MessageBox.Show("GPS_DEV_DOWN_FAILED");
                        break;
                    case 3:
                        Invoke((MethodInvoker)(() => MessageBox.Show("GPS_DEV_DOWN_SUC")));
                        //MessageBox.Show("GPS_DEV_DOWN_SUC");
                        NETCLASS.NETCLIENT_DEVStopDevDownEx(_lHandle);
                        NETCLASS.NETCLIENT_DEVCloseDevDownEx(_lHandle);
                        break;
                    case 4:
                        //_tagGPSVehiDevRelation in API
                        Invoke((MethodInvoker)(() => form1.textBox4.AppendText("nID=" + a + "  szName=" + b + "  szIDNO=" + c + "  szSIMCard=" + d + Environment.NewLine)));
                        break;
                    default:
                        Invoke((MethodInvoker)(() => MessageBox.Show("DEFAULT")));
                        //MessageBox.Show("GPS_DEV_DOWN_SUC");
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "FUNDownDevCBEx Exception");
                return;
            }
        }
        private void button11_Click(object sender, EventArgs e)
        {
            int N1A = NETCLASS.NETCLIENT_DEVOpenDevDownEx(ref _lHandle);
            int N1AA = NETCLASS.NETCLIENT_DEVSetCharEx(_lHandle);
            FUNDownDevCBEx _callback = new FUNDownDevCBEx(FUNDownDevCBEx);
            int N1B = NETCLASS.NETCLIENT_DEVRegDevDownCBEx(_lHandle, this, _callback);
            int N1C = NETCLASS.NETCLIENT_DEVStartDevDownEx(_lHandle, 0, 0);
            //GC.Collect();//garbage collection so call back chills out!
            //GC.WaitForPendingFinalizers();
            //GC.Collect();
            //GC.KeepAlive(_callback);
        }
        public void FUNDataCB(string pBuf, int nLen, long nPos, Form1 form1)
        {
            Invoke((MethodInvoker)(() => MessageBox.Show("pBuf=" + pBuf+ " nLen=" + nLen + " nPos=" + nPos)));
        }
        public void FUNMsgCB(int nMsg, int nParam, Form1 form1)
        {
            Invoke((MethodInvoker)(() => MessageBox.Show("nMsg=" + nMsg+ " nParam=" + nParam)));
            NETCLASS.NETCLIENT_DLStopGetDevCfg( _lHandle);
            NETCLASS.NETCLIENT_DLCloseGetDevCfg( _lHandle);
        }
        private void button12_Click(object sender, EventArgs e)
        {
            IntPtr _lHandle = IntPtr.Zero;
            NETCLASS.NETCLIENT_DLOpenGetDevCfg(ref _lHandle, textBox7.Text);
            FUNMsgCB _callback = new FUNMsgCB(FUNMsgCB);
            FUNDataCB _callback1 = new FUNDataCB(FUNDataCB);
            NETCLASS.NETCLIENT_DLSetGetDCfgMsgCB(_lHandle, this, _callback);
            NETCLASS.NETCLIENT_DLSetGetDCfgDataCB(_lHandle, this, _callback1);
            NETCLASS.NETCLIENT_DLStartGetDevCfg(_lHandle);
        }
    }
}
