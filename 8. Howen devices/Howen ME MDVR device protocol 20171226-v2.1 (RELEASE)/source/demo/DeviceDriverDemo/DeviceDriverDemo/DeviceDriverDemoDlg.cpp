
// DeviceDriverDemoDlg.cpp : ʵ���ļ�
// DeviceDriverDemoDlg.cpp : Implementation file
//

#include "stdafx.h"
#include "DeviceDriverDemo.h"
#include "DeviceDriverDemoDlg.h"
#include "afxdialogex.h"
#include "constants.h"
#include <DeviceDriverSDK/DeviceDriver_Define.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4800)
#pragma warning(disable:4996)

#define bounder_timer_interval 5*1000

static CString ansi2Unicode(const char* source)
{
	wchar_t target[MAX_PATH] = { 0 };
	int length = (int)::strlen(source);
	int newLength = (int)MultiByteToWideChar(CP_ACP, 0, source, (int)length, target, MAX_PATH);

	CString value(target);
	return value;
}

static  std::string unicode2Ansi(const wchar_t* source)
{
	char target[MAX_PATH] = { 0 };
	int length = (int)::wcslen(source);
	int newLength = (int)WideCharToMultiByte(CP_ACP, 0, source, (int)length, target, MAX_PATH, NULL, NULL);

	return target;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
// for "CAboutDlg" dialog box in " about" menu  

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
// data in About dialog box 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��    // DDX/DDV support 

// ʵ��
// Realization
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


// CDeviceDriverDemoDlg �Ի���
// CDeviceDriverDemoDlg dialog box 

CDeviceDriverDemoDlg::CDeviceDriverDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DEVICEDRIVERDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeviceDriverDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICELIST, m_listDevice);
	DDX_Control(pDX, IDC_LIST_DEVICE_STATUS, m_listLocationDetail);
	DDX_Control(pDX, IDC_LIST_RECORD_FILE, m_listRecordFile);
}

BEGIN_MESSAGE_MAP(CDeviceDriverDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILEQUERY, &CDeviceDriverDemoDlg::OnBnClickedButtonFilequery)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, &CDeviceDriverDemoDlg::OnBnClickedButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_VOICE, &CDeviceDriverDemoDlg::OnBnClickedButtonVoice)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CDeviceDriverDemoDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_FILE_DIRECT, &CDeviceDriverDemoDlg::OnBnClickedButtonFileDirect)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CDeviceDriverDemoDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDeviceDriverDemoDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDOK, &CDeviceDriverDemoDlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_MESSAGE(constants::device_status_update, &CDeviceDriverDemoDlg::DeviceLocationUpdate)
	ON_MESSAGE(constants::device_record_file_detail, &CDeviceDriverDemoDlg::DeviceFileDetail)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RECORD_FILE, &CDeviceDriverDemoDlg::OnNMDblclkListRecordFile)
	ON_BN_CLICKED(IDC_BUTTON_GETTING, &CDeviceDriverDemoDlg::OnBnClickedButtonGetting)
	ON_BN_CLICKED(IDC_BUTTON_REPLAY_CONTROL, &CDeviceDriverDemoDlg::OnBnClickedButtonReplayControl)
	ON_BN_CLICKED(IDC_BUTTON_SET_SERVER, &CDeviceDriverDemoDlg::OnBnClickedButtonSetServer)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL_PORT, &CDeviceDriverDemoDlg::OnBnClickedButtonSerialPort)
	ON_BN_CLICKED(IDC_BUTTON_UPGRADE, &CDeviceDriverDemoDlg::OnBnClickedButtonUpgrade)
	ON_BN_CLICKED(IDC_BUTTON_FORMAT_DISK, &CDeviceDriverDemoDlg::OnBnClickedButtonFormatDisk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW_4, &CDeviceDriverDemoDlg::OnBnClickedButtonPreview4)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW_8, &CDeviceDriverDemoDlg::OnBnClickedButtonPreview8)
	ON_LBN_SELCHANGE(IDC_LIST_DEVICELIST, &CDeviceDriverDemoDlg::OnLbnSelchangeListDevicelist)
END_MESSAGE_MAP()


// CDeviceDriverDemoDlg ��Ϣ�������
// CDeviceDriverDemoDlg message process program 

BOOL CDeviceDriverDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	
	// add " ABout" to system menu 

	// IDM_ABOUTBOX must be in system command range 
	
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	// set the box icon, This operation is performed when the application's main window is not a dialog box
	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��      // set big icon 
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��      // set small icon 

	m_listLocationDetail.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_listLocationDetail.InsertColumn(0, _T("content"),LVCFMT_LEFT,60);
	m_listLocationDetail.InsertColumn(1, _T("detail"), LVCFMT_LEFT, 130);
	
	m_listLocationDetail.InsertItem(1, _T("device"));
	m_listLocationDetail.InsertItem(2, _T("time"));
	m_listLocationDetail.InsertItem(3, _T("longitude"));
	m_listLocationDetail.InsertItem(4, _T("latidute"));
	m_listLocationDetail.InsertItem(5, _T("speed"));
	m_listLocationDetail.InsertItem(6, _T("satellites"));
	m_listLocationDetail.InsertItem(7, _T("altitude"));

	m_listRecordFile.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listRecordFile.InsertColumn(0, _T("device"), LVCFMT_LEFT, 100);
	m_listRecordFile.InsertColumn(1, _T("channel"), LVCFMT_LEFT, 60);
	m_listRecordFile.InsertColumn(2, _T("start"), LVCFMT_LEFT, 160);
	m_listRecordFile.InsertColumn(3, _T("stop"), LVCFMT_LEFT, 160);
	m_listRecordFile.InsertColumn(4, _T("duration"), LVCFMT_LEFT, 80);
	m_listRecordFile.InsertColumn(5, _T("path"), LVCFMT_LEFT, 200);

	GetDlgItem(IDC_EDIT_SERVER)->SetWindowText(_T("192.168.3.210:7788"));

	EnbleControlUsed(FALSE);

	m_multimedia.startWork();

#ifdef _DEBUG
	OnBnClickedButtonSetServer();
#endif

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
	
	             // Returns TRUE unless the focus is set to the control
}

void CDeviceDriverDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

// below code required to draw the icon if you need minimize button in dialog box,
//  This operation is performed automatically for MFC program which using file / video mode 


void CDeviceDriverDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������         // Device context for drawing 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		// make the icon to be in the middle of the working retangle 
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		// draw icon 
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
//system call this function to get cursor when the user drags the minimized window 

HCURSOR CDeviceDriverDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDeviceDriverDemoDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

//��������������
//make user can use the button (allow operating interface)
void CDeviceDriverDemoDlg::EnbleControlUsed(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_PREVIEW_4)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_PREVIEW_8)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_FILEQUERY)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SNAPSHOT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_VOICE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_GETTING)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_FILE_DIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_UPGRADE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_REBOOT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_REPLAY_CONTROL)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SERIAL_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_FORMAT_DISK)->EnableWindow(bEnable);
}

//�����������,����������
//set the network parameter for starting
void CDeviceDriverDemoDlg::OnBnClickedButtonSetServer()
{
	CString str;
	GetDlgItem(IDC_BUTTON_SET_SERVER)->GetWindowText(str);

	if (str.CompareNoCase(_T("start listen")) == 0)
	{
		GetDlgItem(IDC_BUTTON_SET_SERVER)->SetWindowText(_T("stop listen"));

		CString str;
		GetDlgItem(IDC_EDIT_SERVER)->GetWindowText(str);
		m_server_address = unicode2Ansi(str.GetBuffer());

		int flagPosition = (int)m_server_address.find(":");
		int port = ::atoi(m_server_address.data() + flagPosition + 1);

		m_proxy.startWork(GetSafeHwnd(), port);

		EnbleControlUsed(TRUE);

		SetTimer(1, bounder_timer_interval, NULL);
	}
	else
	{
		KillTimer(1);

		m_proxy.stopWork();
		m_listDevice.ResetContent();
		resetButton();

		GetDlgItem(IDC_BUTTON_SET_SERVER)->SetWindowText(_T("start listen"));

		EnbleControlUsed(FALSE);

		ShowOnlineCount();
	}
}


//��ȡ��ǰ·��
//get current directory
std::string getCurrentPath()
{
	char szFilePath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);

	char* lastFlag = strrchr(szFilePath, '\\');
	lastFlag[0] = 0;

	return szFilePath;
}

//��ȡjson
//get json
std::string  getJsonString(const char* filenName)
{
	FILE* p = fopen(filenName, "rb");
	if (NULL == p)
		return "";

	fseek(p, 0, SEEK_END);
	int length = ftell(p);
	fseek(p, 0, SEEK_SET);

	char* buffer = new char[length+1];
	fread(buffer, 1, length, p);
	fclose(p);

	buffer[length] = 0;
	std::string value(buffer);
	delete[] buffer;

	return value;
}

//�����豸
//find deivce by id from bounder
int CDeviceDriverDemoDlg::findDeviceItem(CString& deviceID)
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

//�Ƴ��豸
//remove device from bounder
void CDeviceDriverDemoDlg::removeDeviceList(CString& deviceID)
{
	int pos = findDeviceItem(deviceID);
	if (-1 == pos)
		return ;

	std::string _current = unicode2Ansi(deviceID.GetBuffer());
	if (_current.compare(m_selected_device) == 0)
	{
		m_selected_device.clear();
		resetButton();
	}

	m_listDevice.DeleteString(pos);
}

//��ȡ��������ַ
//get the upload media server address
std::string CDeviceDriverDemoDlg::getServerHost()
{
	return m_server_address;
}

//��ȡѡ�е��豸
//get device which is selected.
std::string CDeviceDriverDemoDlg::getSelected(BOOL bDisplayMessage)
{
	if (!m_selected_device.empty())
		return m_selected_device;

	int selected = m_listDevice.GetCurSel();
	if (-1 == selected)
	{
		if (m_listDevice.GetCount() > 0)
		{
			m_listDevice.SetCurSel(0);
			selected = 0;
		}
	}

	std::string deviceID;

	if (-1 != selected)
	{
		CString text;
		m_listDevice.GetText(selected, text);
		deviceID = unicode2Ansi(text.GetBuffer());
		m_selected_device = deviceID;

		m_proxy.setCurrentDeviceID(deviceID.c_str());
	}
	else
	{
		if(bDisplayMessage)
			AfxMessageBox(_T("please select one device!!!"));
	}

	return deviceID;
}

//��λ״̬�����ݸ���
//location & status is updated
LRESULT CDeviceDriverDemoDlg::DeviceLocationUpdate(WPARAM wparam, LPARAM lparam)
{
	std::string device = getSelected(FALSE);

	howenDriver::responds::s_status* para = (howenDriver::responds::s_status*)wparam;

	if (m_selected_device.compare(para->deviceID) != 0)
		return 0;

	m_listLocationDetail.SetItemText(0,1,ansi2Unicode(para->deviceID));

	//������Ч
	//data is invalid
	if (para->all.location.mode == howenDriver::enums::e_location_mode_invalid)
	{
		m_listLocationDetail.SetItemText(1, 1, _T("invalid"));
		m_listLocationDetail.SetItemText(2, 1, _T("invalid"));
		m_listLocationDetail.SetItemText(3, 1, _T("invalid"));
		m_listLocationDetail.SetItemText(4, 1, _T("invalid"));
		m_listLocationDetail.SetItemText(5, 1, _T("invalid"));
		m_listLocationDetail.SetItemText(6, 1, _T("invalid"));
		return 0;
	}

	CString temp;

	temp.Format(_T("%s"),ansi2Unicode(para->all.location.dtu));
	m_listLocationDetail.SetItemText(1, 1, temp);

	temp.Format(_T("%0.6f"), para->all.location.longitude);
	m_listLocationDetail.SetItemText(2, 1, temp);

	temp.Format(_T("%0.6f"), para->all.location.latitude);
	m_listLocationDetail.SetItemText(3, 1, temp);

	temp.Format(_T("%0.2f"), para->all.location.speed);
	m_listLocationDetail.SetItemText(4, 1, temp);

	temp.Format(_T("%d"), para->all.location.satellites);
	m_listLocationDetail.SetItemText(5, 1, temp);

	temp.Format(_T("%d"), para->all.location.altitude);
	m_listLocationDetail.SetItemText(6, 1, temp);
	
	return 0;
}

//�豸¼���ļ���Ϣ
//information about device record file
LRESULT CDeviceDriverDemoDlg::DeviceFileDetail(WPARAM wparam, LPARAM lparam)
{
	const char* deviceID = (const char*)wparam;
	howenDriver::responds::s_general_repsond::s_file_detail_respond* detail = (howenDriver::responds::s_general_repsond::s_file_detail_respond*)lparam;
	
	int inserted = m_listRecordFile.InsertItem(0, ansi2Unicode(deviceID));
	m_listRecordFile.SetItemText(inserted, 1,ansi2Unicode(detail->channelList));
	

	//if (::strstr(detail->path, "jpg") != NULL)
	{//ͼƬ�ļ�        //picture file 
		
	}
	//else
	{//¼���ļ�      //record file 
		m_listRecordFile.SetItemText(inserted, 2, ansi2Unicode(detail->startTime));
		m_listRecordFile.SetItemText(inserted, 3, ansi2Unicode(detail->stopTime));

		CString temp;
		temp.Format(_T("%d"), detail->fileDuration);
		m_listRecordFile.SetItemText(inserted, 4, temp);
	}

	m_listRecordFile.SetItemText(inserted, 5, ansi2Unicode(detail->path));

	return 0;
}

//Ԥ�� 1~4ͨ��
//preview 1~4 channel
void CDeviceDriverDemoDlg::OnBnClickedButtonPreview4()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	CString lastText;
	GetDlgItem(IDC_BUTTON_PREVIEW_4)->GetWindowText(lastText);

	bool bMainStream = false;
	if (((CButton*)GetDlgItem(IDC_CHECK_MAIN_STREAM))->GetCheck() == 1)
		bMainStream = true;

	int requireCount = 4;
	char sessionID[64] = { 0 };

	if (lastText.Find(_T("start")) != -1)
	{
		GetDlgItem(IDC_BUTTON_PREVIEW_4)->SetWindowText(_T("stop preview(1~4)"));
		for (int i = 0; i < requireCount; ++i)
		{
			::sprintf(sessionID, "preview_channel_%d", i + 1);
			m_multimedia.startAVPlaying(i, sessionID, GetDlgItem(IDC_EDIT_VIDEO_1 + i)->GetSafeHwnd(), true);
			m_proxy.StartPreview(device.c_str(), i+1, bMainStream, sessionID, getServerHost().c_str());
		}
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PREVIEW_4)->SetWindowText(_T("start preview(1~4)"));
		for (int i = 0; i < requireCount; ++i)
		{
			::sprintf(sessionID, "preview_channel_%d", i + 1);
			m_proxy.CloseSession(device.c_str(), sessionID);
		}

		//���ߣ��ȴ������˳�
		//sleep for wating thread exist
		Sleep(1000);

		for (int i = 0; i < requireCount; ++i)
		{
			m_multimedia.stopAVPlaying(i);
		}
	}
}

void CDeviceDriverDemoDlg::OnBnClickedButtonPreview8()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	CString lastText;
	GetDlgItem(IDC_BUTTON_PREVIEW_8)->GetWindowText(lastText);

	bool bMainStream = false;
	if (((CButton*)GetDlgItem(IDC_CHECK_MAIN_STREAM))->GetCheck() == 1)
		bMainStream = true;

	int requireCount = 4;
	char sessionID[64] = { 0 };

	if (lastText.Find(_T("start")) != -1)
	{
		GetDlgItem(IDC_BUTTON_PREVIEW_8)->SetWindowText(_T("stop preview(4~8)"));
		for (int i = 0; i < requireCount; ++i)
		{
			::sprintf(sessionID, "preview_channel_%d", i + 5);
			m_multimedia.startAVPlaying(i, sessionID, GetDlgItem(IDC_EDIT_VIDEO_1 + i)->GetSafeHwnd(), true);
			m_proxy.StartPreview(device.c_str(), i + 5, bMainStream, sessionID, getServerHost().c_str());
		}
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PREVIEW_8)->SetWindowText(_T("start preview(4~8)"));
		for (int i = 0; i < requireCount; ++i)
		{
			::sprintf(sessionID, "preview_channel_%d", i + 5);
			m_proxy.CloseSession(device.c_str(), sessionID);
		}

		//���ߣ��ȴ������˳�
		//sleep for wating thread exist
		Sleep(1000);

		for (int i = 0; i < requireCount; ++i)
		{
			m_multimedia.stopAVPlaying(i);
		}
	}
}


//�ļ���ѯ
//file query
void CDeviceDriverDemoDlg::OnBnClickedButtonFilequery()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	m_listRecordFile.DeleteAllItems();

	m_proxy.FileQuery(device.c_str());
}

//Զ��ץ��
//remote snapshot 
void CDeviceDriverDemoDlg::OnBnClickedButtonSnapshot()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	m_proxy.Snapshot(device.c_str(), "1;4");
}

//�����Խ����������㲥
//talk,listen,broadcast
void CDeviceDriverDemoDlg::OnBnClickedButtonVoice()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	CString lastText;
	GetDlgItem(IDC_BUTTON_VOICE)->GetWindowText(lastText);

	const char talkSessionID[] = "talk-request-session";

	//ǰ��4·�Ѿ�������ʵʱ����¼��طţ�����ѡ���������Ŷ�����������������
	//using the 5th to play sound,because the 1 to 4 had used for preview or replay

	if (lastText.CompareNoCase(_T("start voice")) == 0)
	{
		GetDlgItem(IDC_BUTTON_VOICE)->SetWindowText(_T("stop voice"));

		m_proxy.StartVoice(device.c_str(),2, talkSessionID, getServerHost().c_str());

		m_multimedia.setTalkInformation(device.c_str(), talkSessionID);
		m_multimedia.StartMicCollect();
		m_multimedia.startAVPlaying(5, talkSessionID, NULL, true);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_VOICE)->SetWindowText(_T("start voice"));

		m_proxy.CloseSession(device.c_str(), talkSessionID);
		m_multimedia.setTalkInformation("","");
		m_multimedia.StopMicCollect();
		m_multimedia.stopAVPlaying(5);
	}
}

//��������
//device parameter setting
void CDeviceDriverDemoDlg::OnBnClickedButtonSetting()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;
	
	//������������ʱ��,����Ǵ��ļ��ж�ȡ������,��Ϊ�ļ��б���ľ���������json�﷨�ַ���,����ֱ������
	//you can set the json string from file when you set only a parameter to device,
	//because it is right role for json in the file.
	std::string fileName = getCurrentPath() + "\\json\\record.json";
	std::string json = getJsonString(fileName.c_str());

	//�����json�����ļ��ж�ȡ�������������,����Ҫ�Ѷ���ļ�����ص�����ȥ����������,��ѭδһ��������json�﷨������ַ���
	//if you want to set multipe paramete where is getting from example files,
	//you need to rebuild the strings from each file to make a full json role's string.

	m_proxy.DeviceSettingDirect(device.c_str(), json.c_str());
}

//������ȡ
//device parameter getting
void CDeviceDriverDemoDlg::OnBnClickedButtonGetting()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	std::string json = "{ \"SERVER\":null,\"TTX\":null}";

	m_proxy.DeviceSettingDirect(device.c_str(), json.c_str());
}


//ֱ�Ӵ����ļ�
//send file to device direclty 
void CDeviceDriverDemoDlg::OnBnClickedButtonFileDirect()
{
	if (m_direct_file_sending.isWorking())
	{
		AfxMessageBox(_T("The other file transfering."));
		return;
	}

	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	CFileDialog fileDlg(TRUE,_T("*.*"),NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
			_T("all (*.*) |*.*||"));

	//fileDlg.m_ofn.lpstrInitialDir = _T("D:\\");

	if (fileDlg.DoModal() != IDOK)
		return;

	//����ѡ���������ļ����ƣ�   //Return selection or input file name 
	std::string fileName = unicode2Ansi(fileDlg.GetPathName().GetBuffer());
	m_proxy.StartTransfer2DeviceDirect(device.c_str(), fileName.c_str(), getServerHost().c_str());
}

//�����豸
//reboot
void CDeviceDriverDemoDlg::OnBnClickedButtonReboot()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	m_proxy.Reboot(device.c_str());
}

//��ʽ������
//format disk
void CDeviceDriverDemoDlg::OnBnClickedButtonFormatDisk()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	m_proxy.FormatDeviceDisk(device.c_str(), "sd1");
}

//�ָ�Ĭ�ϲ���
//reset default config
void CDeviceDriverDemoDlg::OnBnClickedButtonReset()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	m_proxy.Reset(device.c_str());
}


void CDeviceDriverDemoDlg::OnDestroy()
{
	KillTimer(1);

	m_proxy.stopWork();
	m_direct_file_sending.stopWork();
	m_direct_file_downloading.stopWork();
	m_multimedia.stopWork();

	CDialogEx::OnDestroy();
}

//˫���ط�¼��
//double click to replay 
void CDeviceDriverDemoDlg::OnNMDblclkListRecordFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	if (-1 == pNMItemActivate->iItem)
		return;

	CString wFileName = m_listRecordFile.GetItemText(pNMItemActivate->iItem, 5);
	std::string szFileName = unicode2Ansi(wFileName.GetBuffer());

	CString wDeviceID = m_listRecordFile.GetItemText(pNMItemActivate->iItem, 0);
	std::string deviceID = unicode2Ansi(wDeviceID.GetBuffer());

	CString wChannelList = m_listRecordFile.GetItemText(pNMItemActivate->iItem, 1);
	std::string channeList = unicode2Ansi(wChannelList.GetBuffer());

	CString wStartTime = m_listRecordFile.GetItemText(pNMItemActivate->iItem, 2);
	std::string startTime = unicode2Ansi(wStartTime.GetBuffer());

	CString wStopTime = m_listRecordFile.GetItemText(pNMItemActivate->iItem, 3);
	std::string stopTime = unicode2Ansi(wStopTime.GetBuffer());

	if (strstr(szFileName.c_str(), "jpg") != NULL)
	{
		//ͼƬ,ִ������
		//download the snapshot

		if (m_direct_file_downloading.isWorking())
		{
			AfxMessageBox(_T("The other file transfering."));
			return;
		}

		m_proxy.StartDownloaFileFromDeviceViaDirect(deviceID.c_str(), szFileName.c_str(), getServerHost().c_str());
	}
	else
	{
		//¼���ļ�,�ط�
		//replay this record file


		//���ô˷���������ʱ��ֱ����ת��ָ��λ��
		//you can goto the special time via set starttime
		//::strcpy_s(startTime, "2017-04-26 19:55:00");

		//����д��,������лطſ���
		//write fixed value because the next function "SDKProxy::ReplayControl" will be used.
		char* sessionID = "replay-remote-file";

		m_multimedia.stopAVPlaying(0);
		m_proxy.CloseSession(deviceID.c_str(), sessionID);
		Sleep(1000);

		m_multimedia.startAVPlaying(0, sessionID, GetDlgItem(IDC_EDIT_VIDEO_1)->GetSafeHwnd(),true);
		m_proxy.StartRemoteReplay(deviceID.c_str(),sessionID, channeList.c_str(), startTime.c_str(), stopTime.c_str(), getServerHost().c_str());
	}
}

//�طſ���
//control the replay
void CDeviceDriverDemoDlg::OnBnClickedButtonReplayControl()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	char* sessionID = "replay-remote-file";
	m_proxy.ReplayControl(device.c_str(), sessionID, "2017-04-26 19:55:00");
}

//��λ��ť
//reset button
void CDeviceDriverDemoDlg::resetButton()
{
	//����
	//serial port
	CString lastText;
	GetDlgItemText(IDC_BUTTON_SERIAL_PORT,lastText);
	if (lastText.CompareNoCase(_T("start COM")) != 0)
		SetDlgItemText(IDC_BUTTON_SERIAL_PORT,_T("start COM"));

	//1~4ͨ��
	GetDlgItemText(IDC_BUTTON_PREVIEW_4,lastText);
	if (lastText.Find(_T("start")) == -1)
		SetDlgItemText(IDC_BUTTON_PREVIEW_4,_T("start preview(1~4)"));

	//4~8ͨ��
	GetDlgItemText(IDC_BUTTON_PREVIEW_8,lastText);
	if (lastText.Find(_T("start")) == -1)
		SetDlgItemText(IDC_BUTTON_PREVIEW_8,_T("start preview(4~8)"));
}

//���ڴ���
//serial port agent
void CDeviceDriverDemoDlg::OnBnClickedButtonSerialPort()
{
	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	CString lastText;
	GetDlgItem(IDC_BUTTON_SERIAL_PORT)->GetWindowText(lastText);

	if (lastText.CompareNoCase(_T("start COM")) == 0)
	{
		GetDlgItem(IDC_BUTTON_SERIAL_PORT)->SetWindowText(_T("send to COM"));
		m_proxy.StartSerialPortProxy(device.c_str(), "serial-port-proxy", getServerHost().c_str());
	}
	else
	{
		//GetDlgItem(IDC_BUTTON_SERIAL_PORT)->SetWindowText(_T("start COM"));
		m_proxy.SendData2SerialPort(device.c_str(), "serial-port-proxy");
	}
}

//����
//upgrade
void CDeviceDriverDemoDlg::OnBnClickedButtonUpgrade()
{
	if (m_direct_file_sending.isWorking())
	{
		AfxMessageBox(_T("The other file transfering."));
		return;
	}

	std::string device = getSelected();
	if (device.size() <= 0)
		return;

	CFileDialog fileDlg(TRUE, _T("*.sw"), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("upgrade (*.sw) |*.sw||"));

	//fileDlg.m_ofn.lpstrInitialDir = _T("D:\\");

	if (fileDlg.DoModal() != IDOK)
		return;

	//����ѡ���������ļ����ƣ�     //Return selection or input file name 
	std::string fileName = unicode2Ansi(fileDlg.GetPathName().GetBuffer());
	m_proxy.StartUpgradeDirect(device.c_str(), fileName.c_str(), getServerHost().c_str());
}

void  CDeviceDriverDemoDlg::TraverseDeviceManager(const char* deviceID, int status, int& nListItem)
{
	CString value = ansi2Unicode(deviceID);

	if (0 == status)
	{
		//���ߣ��Ƴ�
		//offline ,remove
		removeDeviceList(value);
		nListItem = -1;
	}
	else
	{
		//���ߣ�������ʾ
		nListItem = m_listDevice.AddString(value);

		if (m_selected_device.empty())
		{
			m_selected_device = deviceID;
			m_proxy.setCurrentDeviceID(deviceID);
		}
	}
}

//��ʾ��������
//display online number
void CDeviceDriverDemoDlg::ShowOnlineCount()
{
	CString textCount;
	textCount.Format(_T("online:%d"), m_listDevice.GetCount());

	SetDlgItemText(IDC_STATIC_DEVICELIST, textCount);
}

void CDeviceDriverDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	//����״̬������
	//update device status to bounder
	deviceManager::func _func = boost::bind(&CDeviceDriverDemoDlg::TraverseDeviceManager, this, _1,_2, _3);
	m_device_manager.traverse(_func);

	ShowOnlineCount();

	CDialogEx::OnTimer(nIDEvent);
}


void CDeviceDriverDemoDlg::OnLbnSelchangeListDevicelist()
{
	int selected = m_listDevice.GetCurSel();

	CString text;
	m_listDevice.GetText(selected, text);
	std::string deviceID = unicode2Ansi(text.GetBuffer());
	m_selected_device = deviceID;

	m_proxy.setCurrentDeviceID(deviceID.c_str());
}
