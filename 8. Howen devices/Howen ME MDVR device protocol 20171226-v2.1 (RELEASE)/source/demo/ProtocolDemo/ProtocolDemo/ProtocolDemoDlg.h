
// ProtocolDemoDlg.h : ͷ�ļ�
//ProtocolDemoDlg.h : head file

#pragma once

#include "afxwin.h"

#include "server/device.h"

// CProtocolDemoDlg �Ի���
//CProtocolDemoDlg dialog
class CProtocolDemoDlg : public CDialogEx
{
// ����
//Constructor
public:
	CProtocolDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
//Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOCOLDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��  //DDX/DDV support


// ʵ��
//Implement
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	//Generated message-map function
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	LRESULT DeviceConnect(WPARAM wParam, LPARAM  lParam);
	afx_msg void OnBnClickedButtonSubscribeLocation();
	afx_msg void OnBnClickedButtonSubscribeAlarm();
	afx_msg void OnBnClickedButtonPreview();
	DECLARE_MESSAGE_MAP()

private:
	CString ansi2Unicode(const char* source);
	std::string unicode2Ansi(const wchar_t* source);

	void removeDeviceList(CString& deviceID);
	int findDeviceItem(CString& deviceID);

	void EnbleControlUsed(BOOL bEnable);
	device_ptr getSelected();

	void analyseData();

private:
	CListBox	m_listDevice;
public:
	afx_msg void OnBnClickedButtonFilequery();
	afx_msg void OnBnClickedButtonReplay();
	afx_msg void OnBnClickedButtonSnapshot();
	afx_msg void OnBnClickedButtonVoice();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonFileDirect();
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonStartListen();
};
