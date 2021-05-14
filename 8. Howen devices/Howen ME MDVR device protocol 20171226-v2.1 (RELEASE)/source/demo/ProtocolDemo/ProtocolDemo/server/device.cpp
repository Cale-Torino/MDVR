
#include "stdafx.h"
#include "device.h"
#include <basic/jsonWriter.h>
#include <boost/format.hpp>

device::device()
{
	m_signal = protocol::business_ptr();
	m_deviceID.empty();
}

device::~device()
{
	resetVariant();
}

//复位变量 // reset variant
void device::resetVariant()
{
	if (NULL != m_signal)
		m_signal->stop();

	boost::unique_lock<boost::shared_mutex> lock(m_lockBusiness);
	
	businessList_iter it = m_businessList.begin();
	businessList_iter it_end = m_businessList.end();
	for (; it != it_end; ++it)
	{
		protocol::business_ptr session = it->second;
		session->stop();
	}

	m_businessList.clear();
}

void device::setDeviceID(const char* deviceID)
{
	m_deviceID = deviceID;
}

const char* device::getDeviceID()
{
	return m_deviceID.c_str();
}

//设置连接器 // Set connector
void device::setConnector(protocol::business_ptr session)
{
	switch (session->getLinkerCode())
	{
	case protocol::define::linkerCode::linkerCodeSignal:
		m_signal = session;
		break;
	case protocol::define::linkerCode::linkerCodeInvalid:
		return;
	default:
		addConnector(session);
		break;
	}
}

//清理连接器  //Reset connector 
void device::resetConnector(protocol::business_ptr session)
{
	switch (session->getLinkerCode())
	{
	case protocol::define::linkerCode::linkerCodeSignal:
		m_signal = protocol::business_ptr();
		break;
	case protocol::define::linkerCode::linkerCodeInvalid:
		return;
	default:
		removeConnector((long long)session.get());
		break;
	}
}

//查找连接器  //Search connector
protocol::business_ptr device::getConnector(long long memoryAddress)
{
	boost::shared_lock<boost::shared_mutex> lock(m_lockBusiness);

	businessList_iter it = m_businessList.find(memoryAddress);
	businessList_iter it_end = m_businessList.end();
	if (it == it_end)
		return protocol::business_ptr();

	return it->second;
}

protocol::business_ptr device::getConnector(const char* sessionID)
{
	boost::shared_lock<boost::shared_mutex> lock(m_lockBusiness);

	businessList_iter it = m_businessList.begin();
	businessList_iter it_end = m_businessList.end();
	for (; it != it_end; ++it)
	{
		protocol::business_ptr ptr = it->second;
		if (::strcmp(ptr->getSessionID(), sessionID) == 0)
			return ptr;
	}

	return protocol::business_ptr();
}

//移除连接器 // Remove connector
void device::removeConnector(long long memoryAddress)
{
	boost::shared_lock<boost::shared_mutex> lock(m_lockBusiness);
	m_businessList.erase(memoryAddress);
}

//添加连接器 //Add connector
void device::addConnector(protocol::business_ptr session)
{
	boost::shared_lock<boost::shared_mutex> lock(m_lockBusiness);
	m_businessList.insert(businessList::value_type((long long)session.get(), session));
}

//关闭链路  //Close connector
void device::closeConnector(const char* sessionID)
{
	protocol::business_ptr ptr = getConnector(sessionID);
	if (NULL == ptr)
		return;

	ptr->stop();
}

//订阅位置状态   //Subscribe status
void device::subscribeStatus()
{
	if (NULL == m_signal)
		return;

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	boost::format fmtSession("status-%s-%016X");
	fmtSession % m_deviceID.c_str() % (long long)this;

	writer.InsertElement("ss", "");// fmtSession.str().c_str());

	//bit0--位置信息(0:无，1:存在)    
	//bit1--Gsensor(0:无，1:存在) 
	//bit2--基础状态(0:无，1:存在)
	//bit3--模块工作状态(0:无，1:存在) 
	//bit4--油耗状态(0:无，1:存在)
	//bit5--移动网络状态(0:无，1:存在) 
	//bit6--WIFI网络状态(0:无，1:存在)  
	//bit7--硬盘状态(0:无，1:存在)  
	//bit8--告警状态(0:无，1:存在)  
	//bit9--温湿度状态(0:无，1:存在) 

	//bit0-location info ( 0: no, 1: exist)
	//bit1- Gsensor( 0: no, 1: exist)
	//bit 2-basic status (0: no, 1: exist) 
	//bit3-communication module working status (0: no, 1: exist)
	//bit4-fuel consumption status ( 0: no, 1: exist) 
	//bit5-network status (0: no, 1: exist)
	//bit6-WIFI network status (0: no, 1: exist)
	//bit7-hard disk status(0: no, 1: exist)
	//bit8-alarm status（0: no, 1: exist）
	//bit9-temperature and humidity status (0:no, 1: exist) 
	
	writer.InsertElement("ct", 0xfff);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::statusSubscribeRequest, request.c_str(), (int)request.length() + 1);
}

//订阅报警  //Subscribe alarm
void device::subscribeAlarm()
{
	if (NULL == m_signal)
		return;


	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	boost::format fmtSession("alarm-%s-%016X");
	fmtSession % m_deviceID.c_str() % (long long)this;

	writer.InsertElement("ss", fmtSession.str().c_str());

	//bit0--位置信息(0:无，1:存在)
	//bit1--Gsensor(0:无，1:存在)
	//bit2--基础状态(0:无，1:存在)
	//bit3--模块工作状态(0:无，1:存在)
	//bit4--油耗状态(0:无，1:存在)
	//bit5--移动网络状态(0:无，1:存在)
	//bit6--WIFI网络状态(0:无，1:存在)
	//bit7--硬盘状态(0:无，1:存在)
	//bit8--告警状态(0:无，1:存在)
	//bit9--温湿度状态(0:无，1:存在)
	
	//bit0-location info ( 0: no, 1: exist)
	//bit1- Gsensor( 0: no, 1: exist)
	//bit 2-basic status (0: no, 1: exist) 
	//bit3-communication module working status (0: no, 1: exist)
	//bit4-fuel consumption status ( 0: no, 1: exist) 
	//bit5-network status (0: no, 1: exist)
	//bit6-WIFI network status (0: no, 1: exist)
	//bit7-hard disk status(0: no, 1: exist)
	//bit8-alarm status（0: no, 1: exist）
	//bit9-temperature and humidity status (0:no, 1: exist) 

	//0x01:报警负载中只上报位置信息  //0x01: Only report location info in alarm load. 
	writer.InsertElement("ct", 0x01);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::alarmSubscribeRequest, request.c_str(), (int)request.length() + 1);
}

//预览  //Preview
void device::preview(int channel, int stream,bool open)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("%d-preview-%s-%02X-%02X");
	fmtSession % channel % m_deviceID.c_str() % channel % stream;

	if (open)
	{
		resolver::jsonWriter writer;
		writer.createRoot(NULL);

		//会话编号  //Session number
		writer.InsertElement("ss", fmtSession.str().c_str());
		//通道  //Channel
		writer.InsertElement("ch", channel);
		//码流类型	//Streaming type
		writer.InsertElement("si", stream);
		//上报服务器	Report server
		writer.InsertElement("srv", protocol::test::serverHost);

		std::string request = writer.getStream();

		m_signal->writeAndFlush(protocol::command::server::previewRequest, request.c_str(), (int)request.length() + 1);
	}
	else
	{
		closeConnector(fmtSession.str().c_str());
	}
}

//强制编码I帧   //Foced coding I Frame
void device::makeIFrame(int channel,int stream)
{
	boost::format fmtSession("preview-%s-%02X-%02X");
	fmtSession % m_deviceID.c_str() % channel % stream;

	protocol::business_ptr ptr = getConnector(fmtSession.str().c_str());
	if (NULL == ptr)
		return;

	ptr->writeAndFlush(protocol::command::server::makeIFrameRequest, NULL, 0);
}

//文件查询  //File query
void device::fileQuery(const char* startTime,const char* stopTime,const char* channelList,protocol::define::fileCode fileType)
{
	if (NULL == m_signal)
		return;

	static int gFileQueryID = 0;
	boost::format fmtSession("fileQuery-%s-%d");
	fmtSession % m_deviceID.c_str() % ++gFileQueryID;

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号  //Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//开始时间	//Start time
	writer.InsertElement("st", startTime);
	//结束时间	//End time
	writer.InsertElement("et", stopTime);
	//通道列表，从1开始，用”;”分割多个，如”1;2;3”表示1和2和3三个通道  //Channel list, starting from 1, split with ";", such as "1; 2; 3" means channel 1, 2 and 3 
	writer.InsertElement("chl", channelList);
	//文件类型	//File type
	writer.InsertElement("ft", (long long)fileType);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::fileQueryRequest, request.c_str(), (int)request.length() + 1);
}

//回放 	//Playback
void device::replay(const char* startTime,const char* stopTime,const char* channelList)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("replay-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//开始时间	//Start time
	writer.InsertElement("st", startTime);
	//结束时间	//End time
	writer.InsertElement("et", stopTime);
	//通道列表，从1开始，用”;”分割多个，如”1;2;3”表示1和2和3三个通道 //Channel list, starting from 1, split with ";", such as "1; 2; 3" means channel 1, 2 and 3 
	writer.InsertElement("chl", channelList);
	//文件类型	//File type
	writer.InsertElement("srv", protocol::test::serverHost);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::replayRequest, request.c_str(), (int)request.length() + 1);
}

//回放控制	//playback control
void device::replayControl(const char* offset/* = NULL*/)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("replay-%s");
	fmtSession % m_deviceID.c_str();

	protocol::business_ptr ptr = getConnector(fmtSession.str().c_str());
	if (NULL == ptr)
		return;

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//控制类型，保留		//control type ,reserved
	writer.InsertElement("act", (long long)0);
	writer.InsertElement("et", offset);
	std::string request = writer.getStream();

	ptr->writeAndFlush(protocol::command::server::replayControl, request.c_str(), (int)request.length() + 1);
}

//抓拍	//Snapshot
void device::snapShot(const char* channelList)
{
	if (NULL == m_signal)
		return;

	static int gSnapShotID = 0;
	boost::format fmtSession("snapshot-%s-%d");
	fmtSession % m_deviceID.c_str() % ++gSnapShotID;

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//通道列表，从1开始，用”;”分割多个，如”1;2;3”表示1和2和3三个通道 //Channel list, starting from 1, split with ";", such as "1; 2; 3" means channel 1, 2 and 3 
	writer.InsertElement("cl", channelList);
	
	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::snapshotRequest, request.c_str(), (int)request.length() + 1);
}

//语音业务(对讲\监听\广播等) //Voice (intercom\listening\broadcast, etc.))
void device::voiceBusiness(int channel,protocol::define::voiceMode mode,bool open)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("voice-%s-%02X");
	fmtSession % m_deviceID.c_str() % channel;

	if (open)
	{
		resolver::jsonWriter writer;
		writer.createRoot(NULL);

		//会话编号	//Session number
		writer.InsertElement("ss", fmtSession.str().c_str());
		//通道	//Channel
		writer.InsertElement("ch", channel);
		//工作模式，0--监听 1--对讲 2--广播 3--PTT	//working mode, 0—listening, 1—intercom, 2—Broadcast, 3—PTT 
		writer.InsertElement("wm", mode);
		//上报服务器 	//report to server
		writer.InsertElement("srv", protocol::test::serverHost);

		std::string request = writer.getStream();

		m_signal->writeAndFlush(protocol::command::server::previewRequest, request.c_str(), (int)request.length() + 1);
	}
	else
	{
		closeConnector(fmtSession.str().c_str());
	}
}

//参数设置	//Parameter setting
//name:需要设置的参数，如"time"，则表示设置时间		//name:the parameter to be set, like "time", means to set time.
//setting:为空表示获取，其他对应具体的参数json字符串		//setting: null means obtain, other, corespond to detailed json string.
void device::parameterSetting(const char* name,const char* setting)
{
	if (NULL == m_signal)
		return;

	std::string request;

	static int gSettingID = 0;
	if (NULL == setting)
	{
		boost::format fmtSession("{\"ss\":\"setting-%s-%d\",\"%s\":{}}");
		fmtSession % m_deviceID.c_str() % (++gSettingID) % name;
		request = fmtSession.str();
	}
	else
	{
		boost::format fmtSession("{\"ss\":\"setting-%s-%d\", \"%s\":{%s}}");
		fmtSession % m_deviceID.c_str() % (++gSettingID) % name % setting;
		request = fmtSession.str();
	}
		
	m_signal->writeAndFlush(protocol::command::server::settingRequest, request.c_str(), (int)request.length() + 1);
}

//串口代理	//Serial port proxy
void device::serialPortProxy(int channel,int stop_bit,int check_bit,int data_bit,int buad_rate)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("serialport-%s-%02X");
	fmtSession % m_deviceID.c_str() % channel;

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//串口编号，从1开始	//serial nubmer, start from 1
	writer.InsertElement("si", channel);
	//停止位，0 -- 1;  1--1.5 ;  2--2 c			//Stop bit，0 -- 1;  1--1.5 ;  2--2 c
	writer.InsertElement("sb", stop_bit);
	//校验位，0--无 1--奇  2--偶  3--标志  4--空格		//Check bit，0--none 1--odd  2--even  3--mark  4--space
	writer.InsertElement("cb", check_bit);
	//数据位，取值范围4~8			//Data bits, in the range of 4 to 8
	writer.InsertElement("db", check_bit);
	//波特率		//Baud rate
	writer.InsertElement("br", buad_rate);
	//上报服务器		//report to server
	writer.InsertElement("srv", protocol::test::serverHost);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::serialPortProxyRequest, request.c_str(), (int)request.length() + 1);
}

//直接发送文件到设备		//directtly send file to device
void device::file2DeviceDirect(const char* filename,int file_size)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("voice-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号		//session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//动作类型,0—从设备下载  1—上传到设备   //Action type, 0 - download from server 1 - upload to device
	writer.InsertElement("act", (long long)1);
	//上报服务器		//report to server
	writer.InsertElement("srv", protocol::test::serverHost);
	//文件名		//file name
	writer.InsertElement("fn", filename);
	//文件大小		//file size
	writer.InsertElement("fs", (long long)file_size);
	//相对文件的偏移地址	//Relative to the file offset address
	writer.InsertElement("of", (long long)0);
	//文件类型,0--未知,1--普通录像,2--报警录像,3--普通抓拍,4--报警抓拍,5--升级文件,6--日志文件,7--配置文件		
	//File type, 0 - unknown, 1 - ordinary video, 2 - alarm video, 3 - ordinary capture, 4 - alarm capture, 5 - upgrade file, 6 - log file, 7 - configuration file
	writer.InsertElement("ft", (long long)5);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::fileTransferRequest, request.c_str(), (int)request.length() + 1);
}

//通过ftp发送文件到设备		//Send the file to the device via ftp
void device::file2DeviceViaFtp( const char* ftp, const char* filename,const char* version)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("viaFtp-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号		//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//ftp服务器,规则:ftp://用户名:密码@服务器:端口
	//Ftp server, rule: ftp: // username: password @ server: port
	writer.InsertElement("ftp", ftp);
	//动作类型，1--升级  2--从ftp下载文件 3--上传文件到ftp  4--配置文件		//action type, 1 - upgrade 2 - download file from ftp 3 - upload file to ftp 4 - configuration file
	writer.InsertElement("fn", 4);
	//文件类型,0--未知,1--普通录像,2--报警录像,3--普通抓拍,4--报警抓拍,5--升级文件,6--日志文件,7--配置文件
	//File type, 0 - unknown, 1 - ordinary video, 2 - alarm video, 3 - ordinary capture, 4 - alarm capture, 5 - upgrade file, 6 - log file, 7 - configuration file
	writer.InsertElement("ft", (long long)7);
	//文件名	//file name
	if (NULL != filename)
		writer.InsertElement("fn", filename);
	//版本	//version
	if (NULL != version)
		writer.InsertElement("ver", version);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::ftpTransferRequest, request.c_str(), (int)request.length() + 1);
}

//云台控制	//PTZ control
void device::ptz(protocol::define::ptzAction action, int x_speed, int y_speed, int preset)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("ptz-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//云台动作	//PTZ action
	writer.InsertElement("act", action);
	//X方向的运动速度，1~10		//X direction  movement speed, 1 ~ 10
	writer.InsertElement("xs", (long long)x_speed);
	//Y方向的运动速度，1~10		//Y direction  movement speed, 1 ~ 10
	writer.InsertElement("ys", (long long)y_speed);
	//预置位		//Preset position
	writer.InsertElement("pre", (long long)preset);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::ptzControl, request.c_str(), (int)request.length() + 1);
}

//输出口控制		//output control
//open_list: 开启列表，通过;分割，如1;3;5 表示1,3,5通道开启		//open_list: open list, split through;, such as 1; 3; 5 means channel 1,3,5 channel are open
//close_list: 关闭列表，通过;分割，如1;3;5 表示1,3,5通道关闭	//close_list: close list, split through;, such as 1; 3; 5 means channel 1,3,5 channel are closed
void device::outputPort(const char* open_list, const char* close_list)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("output-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//打开列表,对应具体通道，其他从1开始，通过”;”分割，如”1;2;5”， 表示1, 2和5三个通道
	//Open list, corresponding to the specific channel, the other from 1, split through";", such as "1; 2; 5", means channel 1, 2, 5
	writer.InsertElement("ol", open_list);
	//关闭列表,对应具体通道，其他从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
	//close list, corresponding to the specific channel, the other from 1, split through";", such as "1; 2; 5", means channel 1, 2, 5

	writer.InsertElement("cl", close_list);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::outputControl, request.c_str(), (int)request.length() + 1);
}

//重启  //Reboot
void device::reboot()
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("restart-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号		//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::reboot, request.c_str(), (int)request.length() + 1);
}

//恢复默认设置  //Reset to default setting
void device::resetConfig()
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("resetConfig-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号		//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::resetDefualtSetting, request.c_str(), (int)request.length() + 1);
}

//同步时间		//Synchronize time
//time:格式"2017-03-12 12:05:39"		//time: format"2017-03-12 12:05:39"
void device::syncTime(const char* time)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("syncTime-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//具体的时间，为空则MDVR获取定位时间进行同步；如”2017-01-01 11:30:58”,则表示设置为这个时间点
	//Specific time, if empty then MDVRsynchronize via locating time; if like "2017-01-01 11:30:58", then set to this point in time
	writer.InsertElement("tm", time);
	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::syncTime, request.c_str(), (int)request.length() + 1);
}

//录像控制  //Recording control
//open_list: 开启列表，通过;分割，如1;3;5 表示1,3,5通道开启
//close_list: 关闭列表，通过;分割，如1;3;5 表示1,3,5通道关闭
//open_list: open list, split through;, such as 1; 3; 5 means channel 1,3,5 channel are open
//close_list: close list, split through;, such as 1; 3; 5 means channel 1,3,5 channel are closed
void device::record(const char* open_list, const char* close_list)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("record-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号	//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//启动录像通道列表,对应具体通道，其他从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
	//Open recording channel list, corresponding to the specific channel, the other from 1, split through";", such as "1; 2; 5", means channel 1, 2, 5
	writer.InsertElement("ol", open_list);
	//关闭录像通道列表,对应具体通道，其他从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
	//Close Recording channel list, corresponding to the specific channel, the other from 1, split through";", such as "1; 2; 5", means channel 1, 2, 5
	writer.InsertElement("cl", close_list);

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::recordControl, request.c_str(), (int)request.length() + 1);
}

//清理告警	//reset alarm
void device::resetAlarm()
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("resetAlarm-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号		//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::resetAlarm, request.c_str(), (int)request.length() + 1);
}

//车辆控制	//Vehicle control
void device::vehicleControl(protocol::define::vehicleAction action, int para1)
{
	if (NULL == m_signal)
		return;

	boost::format fmtSession("vehicleControl-%s");
	fmtSession % m_deviceID.c_str();

	resolver::jsonWriter writer;
	writer.createRoot(NULL);

	//会话编号		//Session number
	writer.InsertElement("ss", fmtSession.str().c_str());
	//云台动作		//PTZ action
	writer.InsertElement("act", action);
	if (protocol::define::vehicleAction::vehicleActionDoorOpen == action || protocol::define::vehicleAction::vehicleActionDoorClose == action)
	{
		//门编号		//Door number
		writer.InsertElement("do", (long long)para1);
	}

	std::string request = writer.getStream();

	m_signal->writeAndFlush(protocol::command::server::vehiControl, request.c_str(), (int)request.length() + 1);
}

//发送媒体数据	//Send media data
void device::sendMediaData(const char* sessionID, protocol::define::frameCode frame, int channel, long long timestamp, char* buffer, int length)
{
	protocol::business_ptr ptr = getConnector(sessionID);
	if (NULL == ptr)
		return;

	protocol::define::mediaHeader header = { 0 };
	header.channel = channel;
	header.frame = frame;
	header.timestamp = (unsigned long long)timestamp;

	messageBuffer::bufferList bfs[2];
	bfs[0].buffer = (char*)&header;
	bfs[0].length = sizeof(header);

	bfs[1].buffer = buffer;
	bfs[1].length = length;

	int count = sizeof(bfs) / sizeof(bfs[0]);

	m_signal->writeAndFlush2(protocol::command::common::mediaStream, bfs, count);
}