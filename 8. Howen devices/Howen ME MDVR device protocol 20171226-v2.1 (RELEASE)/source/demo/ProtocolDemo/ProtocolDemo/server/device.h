
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月21日
描述: 设备类
历史:
1、2017年03月21日 初步创建
使用说明:
*/

#ifndef _device_h_
#define _device_h_

#pragma once

#include "network/clientBusiness.h"
#include <map>

class device : public boost::enable_shared_from_this<device>
{
public:
	typedef std::map<long long, protocol::business_ptr>	businessList;		
	//用内存地址做为KEY
	//Use memoryAddress as KEY
	typedef businessList::iterator						businessList_iter;

public:
	device();
	virtual ~device();

public:
	//复位变量
	//Reset variable
	void resetVariant();

	//设置设备ID
	//Set DeviceID
	void setDeviceID(const char* deviceID);

	const char* getDeviceID();

	//设置连接器
	//Set connector
	void setConnector(protocol::business_ptr session);

	//清理连接器
	//Clear conenctor
	void resetConnector(protocol::business_ptr session);

public:
	//关闭链路
	//Close link
	void closeConnector(const char* sessionID);

	//订阅位置状态
	//Subscribe GPS location status
	void subscribeStatus();

	//订阅报警
	//Subscribe alarm
	void subscribeAlarm();

	//预览
	//Live video Preview
	void preview(int channel, int stream, bool open);

	//强制编码I帧
	//Force device to encode I frame
	void makeIFrame(int channel,int stream);

	//文件查询
	//File query
	void fileQuery(const char* startTime, const char* stopTime, const char* channelList, protocol::define::fileCode fileType);

	//回放
	//Playback
	void replay(const char* startTime, const char* stopTime, const char* channelList);

	//抓拍
	//Snapshot
	void snapShot(const char* channelList);

	//语音业务(对讲\监听\广播等)
	//Voice business(intercom\listen\Broadcast)
	void voiceBusiness(int channel, protocol::define::voiceMode mode, bool open);

	//回放控制
	//Playback control 
	void replayControl(const char* offset = NULL);

	//参数设置
	//Parameter config
	//name:需要设置的参数，如"time"，则表示设置时间
	//name:The parameter to be set, E.g. "time" means to set time
	//setting:为空表示获取，其他对应具体的参数json字符串
	//setting:NULL means to get parameters;for others please refer to the json strings for parameters
	void parameterSetting(const char* name, const char* setting);

	//串口代理
	//Serial proxy
	void serialPortProxy(int channel, int stop_bit, int check_bit, int data_bit, int buad_rate);

	//直接发送文件到设备
	//Send file to device directly
	void file2DeviceDirect(const char* filename, int file_size);

	//通过ftp发送文件到设备
	//Send file to device via FTP
	void file2DeviceViaFtp(const char* ftp, const char* filename, const char* version);

	//云台控制
	//PTZ control
	void ptz(protocol::define::ptzAction action,int x_speed,int y_speed,int preset);

	//输出口控制
	//Output port control
	//open_list: 开启列表，通过;分割，如1;3;5 表示1,3,5通道开启
	//open_list:devided by ";", e.g. 1;3;5 means channel 1,3,5 are open
	//close_list: 关闭列表，通过;分割，如1;3;5 表示1,3,5通道关闭
	//close_list:devided by ";", e.g. 1;3;5 means channel 1,3,5 are close
	void outputPort(const char* open_list,const char* close_list);

	//重启
	//Restart
	void reboot();

	//恢复默认设置
	//Restore defaut settings
	void resetConfig();

	//同步时间
	//Sync time
	//time:格式"2017-03-12 12:05:39"
	//time: time format "2017-03-12 12:05:39"
	void syncTime(const char* time);

	//录像控制
	//Record control
	//open_list: 开启列表，通过;分割，如1;3;5 表示1,3,5通道开启
	//open_list:devided by ";", e.g. 1;3;5 means channel 1,3,5 are open
	//close_list: 关闭列表，通过;分割，如1;3;5 表示1,3,5通道关闭
	//close_list:devided by ";", e.g. 1;3;5 means channel 1,3,5 are close
	void record(const char* open_list, const char* close_list);

	//清理告警
	//Clear alarm
	void resetAlarm();

	//车辆控制
	//Vehicle control
	void vehicleControl(protocol::define::vehicleAction action,int para1);

	//发送媒体数据
	//Send media data
	void sendMediaData(const char* sessionID, protocol::define::frameCode frame, int channel, long long timestamp, char* buffer, int length);

public:
	//查找连接器
	//Search connector
	protocol::business_ptr getConnector(long long memoryAddress);
	protocol::business_ptr getConnector(const char* sessionID);

	//移除连接器
	//Remove connector
	void removeConnector(long long memoryAddress);
	//添加连接器
	//Add connector
	void addConnector(protocol::business_ptr session);

private:
	protocol::business_ptr		m_signal;
	std::string					m_deviceID;

	//业务链路管理
	//Business link management
	boost::shared_mutex			m_lockBusiness;
	businessList				m_businessList;
};

typedef boost::shared_ptr<device> device_ptr;

#endif