
// ProtocolDemoDlg.cpp : 实现文件
// ProtocolDemoDlg.cpp : Implement file

#include "stdafx.h"
#include "ProtocolDemo.h"
#include "ProtocolDemoDlg.h"
#include "afxdialogex.h"
#include "server/controller.h"
#include <boost/locale.hpp>
#include <HowenPlaySDK/PlayerSDK_API.h>
#include "server/utils/utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4996)

namespace protocol
{
	namespace test
	{
		//上报服务器地址，用于测试
		//Report Server address, for test
		//const char serverHost[] = "192.168.3.128:7788";
		char serverHost[128] = { 0 };
	}
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
//CAboutDlg dialog for "About" menu
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
//Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
//Implement
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProtocolDemoDlg 对话框
//CProtocolDemoDlg Dialog


CProtocolDemoDlg::CProtocolDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROTOCOLDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	::strcpy(protocol::test::serverHost, "192.168.3.212:7788");
}

void CProtocolDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICELIST, m_listDevice);
}

BEGIN_MESSAGE_MAP(CProtocolDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CProtocolDemoDlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_USER+0x1001,&CProtocolDemoDlg::DeviceConnect)
	ON_BN_CLICKED(IDC_BUTTON_SUBSCRIBE_LOCATION, &CProtocolDemoDlg::OnBnClickedButtonSubscribeLocation)
	ON_BN_CLICKED(IDC_BUTTON_SUBSCRIBE_ALARM, &CProtocolDemoDlg::OnBnClickedButtonSubscribeAlarm)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CProtocolDemoDlg::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_FILEQUERY, &CProtocolDemoDlg::OnBnClickedButtonFilequery)
	ON_BN_CLICKED(IDC_BUTTON_REPLAY, &CProtocolDemoDlg::OnBnClickedButtonReplay)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, &CProtocolDemoDlg::OnBnClickedButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_VOICE, &CProtocolDemoDlg::OnBnClickedButtonVoice)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CProtocolDemoDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_FILE_DIRECT, &CProtocolDemoDlg::OnBnClickedButtonFileDirect)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CProtocolDemoDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CProtocolDemoDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_START_LISTEN, &CProtocolDemoDlg::OnBnClickedButtonStartListen)
END_MESSAGE_MAP()

//播放音视频对象
//the ojbect which use for playing video & audio
#define max_video_wnd	4
long long g_player[max_video_wnd] = { 0 };

void video_render(int channel,int mediaType, long long timestamp, char* streamData, int length)
{
	howenPlayer::standards::s_frame_data playFrame;

	playFrame.frameBuffer = streamData;
	playFrame.frameLength = length;
	playFrame.frameType = mediaType;
	playFrame.timestamp = timestamp;

	howenPlayer::api::HPlayer_InputMediaData(g_player[channel], playFrame);
}

// CProtocolDemoDlg 消息处理程序
//CProtocolDemoDlg handler

BOOL CProtocolDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// Add "About..." menu in system menu

	// IDM_ABOUTBOX 必须在系统命令范围内。
	//IDM_ABOUTBOX must be in system command range
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//Set icon of the dialog. Frame will do this automatically when main window is not dialog.
	SetIcon(m_hIcon, TRUE);			// 设置大图标 //Set big icon
	SetIcon(m_hIcon, FALSE);		// 设置小图标 //Set small icon 
	
	for (int i = 0; i < max_video_wnd; ++i)
	{
		HWND render_window = GetDlgItem(IDC_EDIT_VIDEO_1+i)->GetSafeHwnd();
		howenPlayer::api::HPlayer_OpenPlayer(g_player[i]);
		howenPlayer::api::HPlayer_StartWork(g_player[i], (long long)render_window);
	}

	EnbleControlUsed(FALSE);

	analyseData();

	GetDlgItem(IDC_EDIT_SERVER)->SetWindowText(ansi2Unicode(protocol::test::serverHost));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE //Return TRUE unless the focus is set to the //control
}

void CProtocolDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
//Add below code to draw MINIMUM button on dialog.
//For MFC programs with Document/View template , this will be done by frame automatically.
void CProtocolDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文  //Context of device to draw

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		//Center the icon in the rectangle of workspace 
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标  //Draw icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
//System calls the function to show the cursor when user drag the minimum window
HCURSOR CProtocolDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProtocolDemoDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CProtocolDemoDlg::OnDestroy()
{
	controller* instance = controller::getInstance();
	instance->stopWork();
	delete instance;

	for (int i = 0; i < max_video_wnd; ++i)
	{
		if (0 != g_player[i])
		{
			howenPlayer::api::HPlayer_StopWork(g_player[i]);
			howenPlayer::api::HPlayer_ClosePlayer(g_player[i]);
			g_player[i] = 0;
		}
	}


	CDialogEx::OnDestroy();
}

int CProtocolDemoDlg::findDeviceItem(CString& deviceID)
{
	int count = m_listDevice.GetCount();
	for (int i = 0; i < count; ++i)
	{
		CString text;
		m_listDevice.GetText(i, text);
		if (text.CompareNoCase(deviceID) == 0)
		{
			return i;
		}
	}

	return -1;
}

void CProtocolDemoDlg::removeDeviceList(CString& deviceID)
{
	int count = m_listDevice.GetCount();
	for (int i = 0; i < count; ++i)
	{
		CString text;
		m_listDevice.GetText(i, text);
		if (text.CompareNoCase(deviceID) == 0)
		{
			m_listDevice.DeleteString(i);
			break;
		}
	}
}

LRESULT CProtocolDemoDlg::DeviceConnect(WPARAM wParam, LPARAM  lParam)
{
	device_ptr device = controller::getInstance()->getDeviceManager().getDevice((long long)wParam);

	if (NULL != device)
	{
		CString deviceID = ansi2Unicode(device->getDeviceID());

		if (0 != lParam)//在线 //Online
		{
			if(-1 == findDeviceItem(deviceID))
				m_listDevice.AddString(deviceID);
		}
		else//掉线  //Offline
		{
			removeDeviceList(deviceID);
		}
	}

	return 0;
}

CString CProtocolDemoDlg::ansi2Unicode(const char* source)
{
	wchar_t target[MAX_PATH] = { 0 };
	int length = (int)::strlen(source);
	int newLength = (int)MultiByteToWideChar(CP_ACP, 0, source, (int)length, target, MAX_PATH);
	
	CString value(target);
	return value;
}

std::string CProtocolDemoDlg::unicode2Ansi(const wchar_t* source)
{
	char target[MAX_PATH] = { 0 };
	int length = (int)::wcslen(source);
	int newLength = (int)WideCharToMultiByte(CP_ACP, 0, source, (int)length, target, MAX_PATH, NULL,NULL);

	return target;
}

device_ptr CProtocolDemoDlg::getSelected()
{
	device_ptr ptr = device_ptr();

	int selected = m_listDevice.GetCurSel();
	if (-1 == selected)
	{
		if (m_listDevice.GetCount() > 0)
			m_listDevice.SetCurSel(0);
		selected = 0;
	}

	if (-1 != selected)
	{
		CString text;
		m_listDevice.GetText(selected, text);
		std::string deviceID = unicode2Ansi(text.GetBuffer());
		ptr = controller::getInstance()->getDeviceManager().getDevice(deviceID.c_str());
	}

	if (NULL == ptr)
		AfxMessageBox(_T("please select one device!!!"));

	return ptr;
}

void CProtocolDemoDlg::OnBnClickedButtonSubscribeLocation()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->subscribeStatus();
}


void CProtocolDemoDlg::OnBnClickedButtonSubscribeAlarm()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->subscribeAlarm();
}


void CProtocolDemoDlg::OnBnClickedButtonPreview()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	for(int i=0;i<max_video_wnd;++i)
		device->preview(i+1, 0,true);
}

void CProtocolDemoDlg::OnBnClickedButtonFilequery()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	SYSTEMTIME cur;
	GetLocalTime(&cur);
	char szStartTime[24] = { 0 };
	char szStopTime[24] = { 0 };
	::sprintf(szStartTime, "%04d-%02d-%02d 00:00:00", cur.wYear, cur.wMonth, cur.wDay);
	::sprintf(szStopTime, "%04d-%02d-%02d 23:00:00", cur.wYear, cur.wMonth, cur.wDay);

	device->fileQuery(szStartTime, szStopTime, "1;2;4", protocol::define::fileCode::fileCodeNormalRecord);
}

void CProtocolDemoDlg::OnBnClickedButtonReplay()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	SYSTEMTIME cur;
	GetLocalTime(&cur);
	char szStartTime[24] = { 0 };
	char szStopTime[24] = { 0 };
	::sprintf(szStartTime, "%04d-%02d-%02d 09:00:00", cur.wYear, cur.wMonth, cur.wDay);
	::sprintf(szStopTime, "%04d-%02d-%02d 23:00:00", cur.wYear, cur.wMonth, cur.wDay);

	device->replay(szStartTime, szStopTime, "1;2");
}


void CProtocolDemoDlg::OnBnClickedButtonSnapshot()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->snapShot("1;2;3;4");
}


void CProtocolDemoDlg::OnBnClickedButtonVoice()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->voiceBusiness(1, protocol::define::voiceModeListen, true);
}


void CProtocolDemoDlg::OnBnClickedButtonSetting()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	//获取参数  //Get parameters
	//device->parameterSetting("record",NULL);

	
	//设置参数  //Set parameters
	const char setting[] = "{\
				\"-version\": \"1.0.1.0\", \
				\"switch\" : \"1\",\
				\"type\" : \"0\",\
				\"apn\" : \"3gnet\",\
				\"servercode\" : \"*99#\",\
				\"user\" : \"card\",\
				\"passwd\" : \"card\",\
				\"SmsService\" : \"13800138000\"\
			}";

	device->parameterSetting("dialup", setting);
}


void CProtocolDemoDlg::OnBnClickedButtonFileDirect()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->file2DeviceDirect("aa.bmp", 10240);

	//启动线程，发送数据
	//Start thread, send data

	//如下面的样例，就是发送媒体数据
	//Sample of sending media data:
	//char hello[] = "hello world!";
	//device->sendMediaData("aa", protocol::define::frameCodeVideoIFrame, 1, 0x1011201130114011, hello, strlen(hello));
}


void CProtocolDemoDlg::OnBnClickedButtonReboot()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->reboot();
}


void CProtocolDemoDlg::OnBnClickedButtonReset()
{
	device_ptr device = getSelected();
	if (NULL == device)
		return;

	device->resetConfig();
}

void CProtocolDemoDlg::OnBnClickedButtonStartListen()
{
	CString str;
	GetDlgItem(IDC_BUTTON_START_LISTEN)->GetWindowText(str);

	if (str.CompareNoCase(_T("start listen")) == 0)
	{
		GetDlgItem(IDC_BUTTON_START_LISTEN)->SetWindowText(_T("stop listen"));

		CString str;
		GetDlgItem(IDC_EDIT_SERVER)->GetWindowText(str);
		std::string _host = unicode2Ansi(str.GetBuffer());

		int flagPosition = (int)_host.find(":");
		int port = ::atoi(_host.data() + flagPosition + 1);

		::strcpy(protocol::test::serverHost, _host.c_str());

		controller::getInstance()->startWork(GetSafeHwnd(), port);

		EnbleControlUsed(TRUE);
	}
	else
	{
		controller::getInstance()->stopWork();

		GetDlgItem(IDC_BUTTON_START_LISTEN)->SetWindowText(_T("start listen"));

		EnbleControlUsed(FALSE);

		m_listDevice.ResetContent();
	}
}

//允许操作界面与否
//make user can use the button (allow operating interface)
void CProtocolDemoDlg::EnbleControlUsed(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_SUBSCRIBE_LOCATION)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SUBSCRIBE_ALARM)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_PREVIEW)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_FILEQUERY)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_REPLAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SNAPSHOT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_VOICE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_FILE_DIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_REBOOT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(bEnable);
}


void CProtocolDemoDlg::analyseData()
{
	char* _data = "480141109B0000002436423842343536372D32334336333237422D41393938334336342D37333438333336360011071B071A20FF03030111071B071A20AF04D802270F13006B1391030018646A07000700000400000002000000010000001F0000010101FF00030000000000000000001F0A00000000000000000000000001000101018CEA0A00000000000F010000FA000000000000003F0000000000000000000000";
	//char* _data = "48014110";
	char* _data_EndFlag = _data + strlen(_data);
	unsigned char _buffer[1024] = { 0 };
	char* _nextData = _data;
	int count = 0;
	char _value[4] = { 0 };
	int _temp = 0;

	for (;;)
	{
		::memcpy(_value, _nextData, 2);
		_temp = strtol(_value, NULL, 16);
		_buffer[count] =(unsigned int) _temp;
		_nextData = _nextData + 2;
		++count;

		if (_nextData == _data_EndFlag)
			break;
		
	}

	protocol::define::msgHeader* _header = (protocol::define::msgHeader*)_buffer;

	int pos = 0;
	char* _payload = (char*)_buffer + protocol::define::msgHeaderLength;

	//会话编号
	std::string sessionID = utils::getLess256String(_payload, &pos);
	utils::statusAnalyse(&_payload[pos]);
}