

#include "stdafx.h"
#include "clientBusiness.h"
#include <basic/jsonReader.h>
#include <basic/jsonWriter.h>
#include "../utils/utils.h"
#include "../device.h"


extern void device_register(const char* deviceID, protocol::business_ptr signal);
extern void device_offline(const char* deviceID, protocol::business_ptr session);

protocol::clientBusiness::clientBusiness(boost::asio::io_service& ioservice) : clientSession(ioservice)
{
	m_eLinkerCode = protocol::define::linkerCode::linkerCodeInvalid;
}

protocol::clientBusiness::~clientBusiness()
{

}

//获取连接类型
//Get link type
protocol::define::linkerCode protocol::clientBusiness::getLinkerCode()
{
	return m_eLinkerCode;
}

//会话标识
//Session ID
const char* protocol::clientBusiness::getSessionID()
{
	return m_sessionID.c_str();
}

//掉线
//Offline
void protocol::clientBusiness::offline()
{
	business_ptr ptr = boost::dynamic_pointer_cast<protocol::clientBusiness>(shared_from_this());
	device_offline(m_deviceID.c_str(), ptr);
}

//调度消息
//Dispatch message
void protocol::clientBusiness::dispatchMessage(protocol::define::msgHeader* header, char* payload)
{
	switch (header->code)
	{ 
	case protocol::command::common::heartbeat:
		this->writeAndFlush(protocol::command::common::heartbeat, NULL, 0);
		break;
	case protocol::command::common::mediaStream:
		mediaStream(payload, header->payloadLength);
		break;

	case protocol::command::device::signalRegisterRequest:
		signalRegister(payload, header->payloadLength);
		break;
	case protocol::command::device::mediaStreamRegisterRequest:
		mediaRegister(payload, header->payloadLength);
		break;
	case protocol::command::device::previewRespond:
		utils::DebugOutput("%x===>%s",header->code, payload);
		break;

	case protocol::command::device::statusSubscribeRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;
	case protocol::command::device::statusData:
		statusData(payload, header->payloadLength);
		break;
	case protocol::command::device::alarmSubscribeRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;
	case protocol::command::device::alarmData:
		alarmData(payload, header->payloadLength);
		break;

	case protocol::command::device::fileDetails:
		fileDetail(payload, header->payloadLength);
		break;

	case protocol::command::device::snapshotRespond:
		snapShot(payload, header->payloadLength);
		break;

	case protocol::command::device::voiceRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;

	case protocol::command::device::settingRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;

	case protocol::command::device::serialPortProxyRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;

	case protocol::command::device::fileTransferRespond:
	case protocol::command::device::ftpTransferRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;

	case protocol::command::device::baseControlRespond:
		utils::DebugOutput("%x===>%s", header->code, payload);
		break;
	}
}

//媒体数据
//Media data
void protocol::clientBusiness::mediaStream(char* playload_buffer, int payload_length)
{
	int pos = 0;
	char* buffer = playload_buffer;

	//1--视频I帧	2--视频P帧	3--音频帧	4--串口数据	5--文件数据
	//1--I frame of video 2--P frame of video 3--Audio Frame 4--Serial data 5--File data
	int mediaType = utils::transferInteger(&buffer[pos], 2);
	pos += 2;

	//通道编号，从1开始
	//Channel number, begin from 1
	int channel = utils::transferInteger(&buffer[pos], 2);
	pos += 2;

	//时间戳
	//Time stamp
	long long timestamp = utils::transferLong(&buffer[pos], 8);
	pos += 8;

	//媒体数据
	//Media data
	char* mediaBuffer = &buffer[pos];
	int mediaLength = payload_length - pos;
	
	extern void video_render(int channel,int mediaType, long long timestamp, char* streamData, int length);
	video_render(channel-1,mediaType, timestamp, mediaBuffer, payload_length - pos);

	if (getLinkerCode() == define::linkerCodeFileTransfer)
	{//文件传输	//file transfer
		if (0 == mediaLength)
		{//文件传输完毕	//finished
			stop();
		}
	}
}

//设备信令注册
//Device register on command server
void protocol::clientBusiness::signalRegister(char* playload_buffer, int payload_length)
{
	resolver::jsonReader reader;
	reader.loadFromBuffer(playload_buffer);

	std::string deviceID = reader.getStringValue("dn");
	std::string guid = reader.getStringValue("guid");
	std::string session = reader.getStringValue("ss");
	std::string mobile = reader.getStringValue("mb");
	std::string dtu = reader.getStringValue("dtu");
	std::string version = reader.getStringValue("ver");

	int netAdapter = (int)reader.getLongLongValue("at");
	int deviceAdpater = (int)reader.getLongLongValue("dt");
	
	//应答
	//Reply
	resolver::jsonWriter writer;
	writer.createRoot(NULL);
	writer.InsertElement("ss", session.c_str());
	writer.InsertElement("err",(long long) 0);
	std::string respond = writer.getStream();
	writeAndFlush(protocol::command::server::signalRegisterRespond, respond.c_str(),(int) respond.length()+1);

	m_sessionID = session;
	m_deviceID = deviceID;
	m_eLinkerCode = protocol::define::linkerCode::linkerCodeSignal;

	business_ptr ptr = boost::dynamic_pointer_cast<protocol::clientBusiness>(shared_from_this());
	device_register(deviceID.c_str(), ptr);
}

//设备媒体链路注册
//Device register on media server
void protocol::clientBusiness::mediaRegister(char* playload_buffer, int payload_length)
{
	resolver::jsonReader reader;
	reader.loadFromBuffer(playload_buffer);

	//服务器生成的会话编号
	//Session ID generated by server
	std::string session = reader.getStringValue("ss");
	//设备ID
	//DeviceID
	std::string deviceID = reader.getStringValue("dn");
	//接入网络 1--有线 2--WIFI 3--2G
	//Network connection type 1--Local Ethernet 2--WIFI 3--2G
	int netAdapter = (int)reader.getLongLongValue("at");
	//媒体类型 1--实时预览 2--像回放 3--语音 4--文件传输 5--串口透传
	//Media data type 1--Live video preview 2--Playback 3--Voice 4--File transmission 5--Serial transparent transmission
	int mediaAdapter = (int)reader.getLongLongValue("mt");
	//通道编号
	//Channel number
	int channel = (int)reader.getLongLongValue("mt");

	m_sessionID = session;
	m_eLinkerCode = (protocol::define::linkerCode)mediaAdapter;

	//应答
	//Reply
	resolver::jsonWriter writer;
	writer.createRoot(NULL);
	writer.InsertElement("ss", session.c_str());
	writer.InsertElement("err", (long long)0);
	std::string respond = writer.getStream();
	writeAndFlush(protocol::command::server::mediaStreamRegisterRespond, respond.c_str(), (int)respond.length() + 1);

	business_ptr ptr = boost::dynamic_pointer_cast<protocol::clientBusiness>(shared_from_this());
	device_register(deviceID.c_str(), ptr);
}

//状态数据
//Status data
void protocol::clientBusiness::statusData(char* playload_buffer, int payload_length)
{
	int pos = 0;
	char* buffer = playload_buffer;

	//会话编号
	//Session ID
	
	std::string sessionID = utils::getLess256String(buffer, &pos);
	utils::statusAnalyse(&buffer[pos]);
}

//报警数据
//Alarm data
void protocol::clientBusiness::alarmData(char* playload_buffer, int payload_length)
{
	int pos = 0;
	char* buffer = playload_buffer;

	//会话编号
	//Session ID
	std::string sessionID = utils::getLess256String(buffer,&pos);
	
	//报警描述json字符串长度(包含结束符)
	//length of alarm json string(including end character)
	int jsonLength = utils::transferInteger(&buffer[pos],4);
	pos += 4;

	resolver::jsonReader reader;
	reader.loadFromBuffer(&buffer[pos]);
	pos += jsonLength;

	//设备时间
	//Device time
	std::string dtu = reader.getStringValue("dtu");
	//报警开始时间
	//Alarm start time
	std::string alarmStartTime = reader.getStringValue("st");
	//报警结束时间
	//Alarm end time
	std::string alarmStopTime = reader.getStringValue("et");
	//事件类型
	//Event type
	int alarmType = (int)reader.getLongLongValue("ec");
	//相关抓拍图片文件保存地址
	//save path of related snapshot files
	std::string picturePath = reader.getStringValue("pa");
	//相关录像文件保存地址
	//save path of related recording files
	std::string recordPath = reader.getStringValue("ra");

	//详细信息
	//Details
	Json::Value* detail = reader.getNodePointerByName(reader.getRoot(), "det");

	switch (alarmType)
	{
	case protocol::define::eventCode::eventCodeVideoLost:
	case protocol::define::eventCode::eventCodeMotionDetect:
	case protocol::define::eventCode::eventCodeVideoMask:
	case protocol::define::eventCode::eventCodeInputGenerate:
	case protocol::define::eventCode::eventCodeUrgency:
		{
			int channel = (int)reader.getLongLongValue(detail, "ch");
		}
		break;
	case protocol::define::eventCode::eventCodeLowSpeed:
	case protocol::define::eventCode::eventCodeOverSpeed:
	case protocol::define::eventCode::eventCodeLowTemperature:
	case protocol::define::eventCode::eventCodeOverTemperature:
		{
			//触发阈值
			//Trigger threshold
			int thresholdGenerate = (int)reader.getLongLongValue(detail, "vt");
			//时间阈值
			//Time threshold
			int thresholdTime = (int)reader.getLongLongValue(detail, "tt");
			//最小值
			//Min value
			int minValue = (int)reader.getLongLongValue(detail, "min");
			//最大值
			//Max value
			int maxValue = (int)reader.getLongLongValue(detail, "max");
			//平均值
			//average value
			int averageValue = (int)reader.getLongLongValue(detail, "avg");
			//当前值
			//Current value
			int currentValue = (int)reader.getLongLongValue(detail, "cur");
		}
		break;
	case protocol::define::eventCode::eventCodeParkTimeout:
		{
			//触发阈值
			//Trigger threshold
			int thresholdGenerate = (int)reader.getLongLongValue(detail, "vt");
			//停车时长
			//Parking time
			int totalSeconds = (int)reader.getLongLongValue(detail, "st");
		}
		break;
	case protocol::define::eventCode::eventCodeShake:
		{
			//触发阈值
			//Trigger threshold
			int thresholdGenerate = (int)reader.getLongLongValue(detail, "vt");
			//时间阈值
			//Time threshold
			int thresholdTime = (int)reader.getLongLongValue(detail, "tt");
			//最小值
			//Min value
			int minValue = (int)reader.getLongLongValue(detail, "min");
			//最大值
			//Max value
			int maxValue = (int)reader.getLongLongValue(detail, "max");
			//平均值
			//Average value
			int averageValue = (int)reader.getLongLongValue(detail, "avg");
			//当前值
			//Current value
			int currentValue = (int)reader.getLongLongValue(detail, "cur");
			//方向 1--x方向 2--y方向 3--z方向 4--撞击 5--倾斜
			//Directions 1--x 2--y 3--z 4--crash 5--lean
			int direct = (int)reader.getLongLongValue(detail, "dt");
		}
		break;
	case protocol::define::eventCode::eventCodeEDefence:
	case protocol::define::eventCode::eventCodeELine:
		{
			//区域或者线路编号
			//Area number or route number
			int number = (int)reader.getLongLongValue(detail, "num");
			//状态 0--进入 1--离开
			//Status 0--Enter 1--Leave
			int status = (int)reader.getLongLongValue(detail, "st");
		}
		break;
	case protocol::define::eventCode::eventCodeDoorException:
		{
			//门编号，1--左前门 2--右前门 3--左中门
			//4--右中门 5--左后门 6--右后门
			//Door number,1--left front door 2--right front door 3--left middle door 4--right middle door 5--left rear door 6--right rear door
			int number = (int)reader.getLongLongValue(detail, "num");
			//状态 0--关闭 1--打开
			//Status 0-Close 1-Open
			int status = (int)reader.getLongLongValue(detail, "st");
		}
		break;
	case protocol::define::eventCode::eventCodeStorageException:
		{
			//磁盘编号，如sd1,sd2,hdd1,hdd2
			//Disk Number,such as sd1,sd2,hdd1,hdd2
			int number = (int)reader.getLongLongValue(detail, "num");
			//状态 0--丢失 1--损坏 2--无法覆盖
			//Status 0--lost 1-damaged 2--Cannot overwrite
			int status = (int)reader.getLongLongValue(detail, "st");
		}
		break;
	case protocol::define::eventCode::eventCodeFatigueDriving:
		{
			//疲劳度
			//Fatigue level
			int level = (int)reader.getLongLongValue(detail, "de");
		}
		break;
	case protocol::define::eventCode::eventCodeFuelException:
		{
			//触发阈值
			//Trigger threshold
			int thresholdGenerate = (int)reader.getLongLongValue(detail, "vt");
			//油箱容量，升
			//Fuel tank capacity, Liter
			int total = (int)reader.getLongLongValue(detail, "to");
			//剩余油量，升
			//Remained fuel ,liter
			int free = (int)reader.getLongLongValue(detail, "fr");
		}
		break;
	}

	//状态数据
	//Status data
	int statusLength = payload_length - jsonLength;
	statusData(&buffer[pos], statusLength);
}

//文件信息
//File info
void protocol::clientBusiness::fileDetail(char* playload_buffer, int payload_length)
{
	resolver::jsonReader reader;
	reader.loadFromBuffer(playload_buffer);

	//服务器生成的会话编号
	//Session ID generated by server
	std::string session = reader.getStringValue("ss");
	//错误代码
	//Error code
	int errCode = (int)reader.getLongLongValue("err");
	if (errCode != protocol::define::errorCode::errorCodeDataContinue)
		return;

	Json::Value* detail = reader.getNodePointerByName(reader.getRoot(), "fi");

	//开始时间，如”2017-01-01 12:30:30”
	//Start time,such as ”2017-01-01 12:30:30”
	std::string startTime = reader.getStringValue(detail,"st");
	//结束时间，如”2017-01-01 12:30:30”
	//End time,such as ”2017-01-01 12:30:30”
	std::string stopTime = reader.getStringValue(detail, "et");
	//通道列表
	//Channel list
	std::string channelList = reader.getStringValue(detail, "chl");
	//文件类型
	//File type
	int fileType = (int)reader.getLongLongValue(detail, "ft");
	//文件大小
	//File size
	int fileSize = (int)reader.getLongLongValue(detail, "fs");
	//文件时长(秒)
	//File duration(second)
	int file_duration = (int)reader.getLongLongValue(detail, "fd");
	//文件路径
	//File path
	std::string path = reader.getStringValue(detail, "fn");

	utils::DebugOutput("Time[%s==>%s,%d],chn[%s],code[%d],path[%s]",
		startTime.c_str(), stopTime.c_str(), file_duration, channelList.c_str(),
		fileType, path.c_str());
}

//抓拍
//Snapshot
void protocol::clientBusiness::snapShot(char* playload_buffer, int payload_length)
{
	resolver::jsonReader reader;
	reader.loadFromBuffer(playload_buffer);

	//服务器生成的会话编号
	//Session ID generated by server
	std::string session = reader.getStringValue("ss");
	//错误代码
	//Error code
	int errCode = (int)reader.getLongLongValue("err");

	if (errCode != protocol::define::errorCode::errorCodeSucceed)
		return;

	//详细信息
	//Details
	Json::Value* detail = reader.getNodePointerByName(reader.getRoot(), "rl");
	if (NULL == detail || !detail->isArray())
		return;

	int count = detail->size();
	
	for(int i=0;i<count;++i)
	{
		Json::Value* parent = &detail[i];

		//通道
		//Channel
		int channel = (int)reader.getLongLongValue(parent,"ch");
		//文件路径
		//File path
		std::string path = reader.getStringValue(parent, "fn");

		utils::DebugOutput("chn[%d],path[%s]", channel, path.c_str());
	}
}