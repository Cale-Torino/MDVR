
// DeviceDriverDemoDlg.h : 头文件      
// DeviceDriverDemoDlg.h : Header File    
//

#pragma once

#include <string>
#include "afxcmn.h"
#include "afxwin.h"

#include "SDKProxy.h"
#include "MultiMediaBusiness.h"
#include "DirectFileSending.h"
#include "DirectFileDownloading.h"
#include "deviceManager.h"

// CDeviceDriverDemoDlg 对话框
// CDeviceDriverDemoDlg dialog box 
class CDeviceDriverDemoDlg : public CDialogEx
{
// 构造
// structure
public:
	CDeviceDriverDemoDlg(CWnd* pParent = NULL);	// 标准构造函数      // standard structure function 

// 对话框数据
// dialog data 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICEDRIVERDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持    // DDX/DDV support 


// 实现
// Realization
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	// Generated message mapping function
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFilequery();
	afx_msg void OnBnClickedButtonSnapshot();
	afx_msg void OnBnClickedButtonVoice();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonFileDirect();
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedOk();
	afx_msg	LRESULT DeviceLocationUpdate(WPARAM wparam, LPARAM lparam);
	afx_msg	LRESULT DeviceFileDetail(WPARAM wparam, LPARAM lparam);
	afx_msg void OnBnClickedButtonGetting();
	afx_msg void OnNMDblclkListRecordFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonReplayControl();
	afx_msg void OnBnClickedButtonSetServer();
	afx_msg void OnBnClickedButtonSerialPort();
	afx_msg void OnBnClickedButtonUpgrade();
	afx_msg void OnBnClickedButtonFormatDisk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPreview4();
	afx_msg void OnBnClickedButtonPreview8();
	afx_msg void OnLbnSelchangeListDevicelist();

private:
	int findDeviceItem(CString& deviceID);
	void removeDeviceList(CString& deviceID);
	std::string getSelected(BOOL bDisplayMessage = TRUE);
	std::string getServerHost();
	void EnbleControlUsed(BOOL bEnable);
	void  TraverseDeviceManager(const char* deviceID, int status, int& nListItem);
	void ShowOnlineCount();
	void resetButton();
private:
	CListBox	m_listDevice;
	CListCtrl	m_listLocationDetail;
	CListCtrl	m_listRecordFile;

private:
	std::string				m_selected_device;
	std::string				m_server_address;
	SDKProxy				m_proxy;
	MultiMediaBusiness		m_multimedia;
	DirectFileSending		m_direct_file_sending;
	DirectFileDownloading	m_direct_file_downloading;
	deviceManager			m_device_manager;	
};
