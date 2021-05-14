
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月18日
描述: SDK代理类
历史:
1、2017年04月18日 初步创建
使用说明:
*/

/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170418
Description: SDK proxy  
History:
1, 20170418: initial establish 
instruction:
*/

#ifndef _SDK_Proxy_h_
#define _SDK_Proxy_h_

#pragma once

#include <string>

class SDKProxy
{
public:
	SDKProxy();
	virtual ~SDKProxy();

public:
	//启动工作
	//start work,include initializing sdk etc.
	void startWork(HWND msgWnd, int port);

	//停止工作
	//stop work
	void stopWork();

	//是否工作中
	//is working?
	bool isWorking();

public:
	//设备管理
	//device manager ,open or close device
	void DeviceManager(const char* deviceID, bool open);

	//预览视频
	//start video preview
	void StartPreview(const char* deviceID, int channel,bool _mainStream, const char* sessionID, const char* serverHost);

	//关闭会话
	//close session
	void CloseSession(const char* deviceID, const char * sessionID);

	//文件查询
	//file query
	void FileQuery(const char* deviceID);

	//远程回放
	//remote playback 
	void StartRemoteReplay(const char* deviceID, const char* sessionID, const char* channelList, const char* startTime, const char* stopTime, const char* serverHost);

	//回放时间跳转
	//goto the special playback time
	void ReplayControl(const char* deviceID, const char* sessionID, const char* gotoTime);

	//抓拍
	//control device to snapshot
	//after snapshot ,the file will upload to ftp server
	void Snapshot(const char* deviceID, const char* channelList);

	//对讲&监听,需要通过howenDriver::api::sendMediaData发送对讲数据,发送之前需要做G726编码
	//listen & talk,need send data which is compressed by G726 protocol to device use api howenDriver::api::sendMediaData
	void StartVoice(const char* deviceID, int channel, const char* sessionID, const char* serverHost);

	//直接设置参数到设备
	//set device parameter to device directly 
	void DeviceSettingDirect(const char* deviceID, const char* json);

	//启动文件发送
	//start to send file to device
	void StartTransfer2DeviceDirect(const char* deviceID, const char* fileName, const char* serverHost);

	//下载文件
	//start to get file from device
	void StartDownloaFileFromDeviceViaDirect(const char* deviceID, const char* fileName, const char* serverHost);

	//通过ftp发送文件
	//send file to device by ftp 
	void Transfer2DeviceViaFtpMode(const char* deviceID, const char* fileName, const char* ftp);

	//重启
	//reboot
	void Reboot(const char* deviceID);

	//复位
	//Reset
	void Reset(const char* deviceID);

	//格式化磁盘
	//format disk
	void FormatDeviceDisk(const char* deviceID, const char* diskName);

	//串口代理
	//serial port proxy 
	void StartSerialPortProxy(const char* deviceID, const char* sessionID, const char* serverHost);

	//发送数据到串口
	//send data to the serial port
	void SendData2SerialPort(const char* deviceID, const char* sessionID);

	//直接传输文件进行远程升级
	//start to upgrade via sending file to device directly 
	void StartUpgradeDirect(const char* deviceID, const char* fileName, const char* serverHost);

public:
	//发送消息到界面展现
	//send message to bounder for display
	void SendMessage2Bounder(UINT msg, WPARAM wparam, LPARAM lParam);

public:
	//是否为当前选中的设备ID
	//is current select device id
	bool isCurrentDeviceID(const char* deviceID);
	void setCurrentDeviceID(const char* deviceID);

private:
	//消息接收窗口
	//message receive window
	HWND			m_messageReceiveWnd;

	bool			m_isWorking;

	std::string		m_current_DeviceID;
};

#endif

