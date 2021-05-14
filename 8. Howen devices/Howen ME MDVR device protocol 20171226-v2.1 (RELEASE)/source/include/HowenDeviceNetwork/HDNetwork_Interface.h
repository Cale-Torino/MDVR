
/*
V 1.0
作者: 黄佳 <hanan.huang@howentech.com,13927488810>
日期: 2017年05月22日
描述: 接口定义
	IMediumDataNotify:
			媒体数据通知接口,内部实现，传递给外部，让外部调用媒体数据更新
			用于设备主动获取数据的方式，如音频，视频，串口等业务

	IFileQuery:
			文件查询（需要设备层开发使用），实现后用来做文件查询业务
			由内部调用release来做释放动作

	IRecordFileReader:
			录像文件读者（需要设备层开发使用），实现后用来实现录像回放业务
			由内部调用release来做释放动作

	IFileReaderWriter:
			普通文件读写（需要设备层开发使用），实现后用实现文件传输业务
			由内部调用release来做释放动作

	IHardwareDriver：
			设备实现接口（需要设备层开发使用），实现后用来直接操作设备的相关业务控制

	INetWorkController:
			业务控制类，内部实现，外部调用进行启动和关闭工作等业务

历史:
1、2017年05月22日
	初步创建
2、2017年06月16日
	IHardwareDriver增加notifyNetMessage接口，用于模拟器，仅供内部使用
*/

#ifndef _HDNetwork_Interface_h_
#define _HDNetwork_Interface_h_

#pragma once

#include "HDNetwork_Status.h"
#include "HDNetwork_Alarm.h"

//-------------------------------------------------------------------------------------
//媒体数据通知接口,内部实现，传递给外部，让外部调用媒体数据更新
//用于设备主动获取数据的方式，如音频，视频，串口等业务
//-------------------------------------------------------------------------------------
class IMediumDataNotify
{
public:
	//通道编号,从1开始
	//get channel ,from 1
	virtual int	getChannel() = 0;

	//获取启动状态	true:启动		false:关闭
	//get starting status ,true:start	false:stop
	virtual bool getStarting() = 0;

	//用户数据
	//user data
	virtual long long getUserData() = 0;
	virtual void setUserData(long long userdata) = 0;

public:
	//数据通知
	//notify data
	virtual void notify(HowenDeviceNetwork::structs::common::frame_data& frame) = 0;

public:
	//获取码流类型，实时视频时候有效
	//get stream index
	virtual HowenDeviceNetwork::enums::e_video_stream_index		getStreamIndex() = 0;

public:
	//获取语音对讲模式，语音模式有效
	virtual HowenDeviceNetwork::enums::e_voice_mode		getVoiceMode() = 0;

//串口参数，串口透传时候有效
//serial port,is valid while using serial port proxy
public:
	//停止位
	//stop bit
	virtual HowenDeviceNetwork::enums::e_seiral_port_stop_bit	getStopBit() = 0;

	//校验位
	//check bit
	virtual HowenDeviceNetwork::enums::e_seiral_port_check_bit	getCheckBit() = 0;

	//数据位，4~8
	//data bit,4~8
	virtual int	getDataBit() = 0;

	//波特率,>=2400
	//baund rate,>=2400
	virtual int getBaudRate() = 0;
};



//-------------------------------------------------------------------------------------
//文件查询（需要设备层开发使用），实现后用来做文件查询业务
//-------------------------------------------------------------------------------------
class IFileQuery
{
public:
	//开始搜索	startTime、stopTime:开始和结束时间，如"2017-03-12 04:55:56"
	//			fileType:文件类型
	//			channeList、channelNumber:通道列表和数量
	//start searching	startTime、stopTime:start and stop time，such as "2017-03-12 04:55:56"
	//			fileType:type of file
	//			channeList、channelNumber:channel list and number
	virtual void start(const char* startTime,const char* stopTime,
				HowenDeviceNetwork::enums::e_file_type fileType,
				int channeList[],int channelNumber) = 0;

	//结束搜索
	//stop searching
	virtual void stop() = 0;

	//释放对象
	//destroy object
	virtual void release() = 0;



	//下一条记录,	false:失败,比如到了最后一条记录，磁盘损坏或者格式化都可能导致异常
	//next record,	false:failed,need break
	virtual bool moveNext() = 0;

	/**************获取当前记录信息*********************/
	/**************current file information***********/

	//文件名，绝对路径
	//file absolute path
	virtual const char* getFilePath() = 0;

	//开始时间和结束时间，如"2017-03-12 04:55:56"
	//start and stop time ,such as "2017-03-12 04:55:56"
	virtual const char* getStartTime() = 0;
	virtual const char* getStopTime() = 0;

	//文件类型
	//file type
	virtual HowenDeviceNetwork::enums::e_file_type getType() = 0;

	//是否为复合通道
	//is complex channel
	virtual bool isComplexChannel() = 0;

	//如果是复合通道，返回按位操作,其他为具体通道,从1开始
	//if is complex channel,need return bits channel,else return current channel which start from 1
	virtual int getChannel() = 0;
	
	//总大小，字节
	//total size,bytes
	virtual int getTotalBytes() = 0;

	//时长，秒
	//duration,seconds
	virtual int getDuration() = 0;
};




//-------------------------------------------------------------------------------------
//录像文件读者（需要设备层开发使用），实现后用来做回放业务
//-------------------------------------------------------------------------------------
class IRecordFileReader
{
public:
	//启动	utf8Name:utf8文件格式名称		返回：true：成功	false：失败
	//start(normal file) utf8Name:filename	return:true:succeed, false:failed
	virtual bool start(const char* utf8Name) = 0;

	//启动	startTime，stopTime:开始和结束时间	channelList:通道列表,从1开始		返回：true：成功	false：失败
	//start startTime，stopTime:start and stop time	channelList:channel list,from 1		return:true:succeed, false:failed
	virtual bool start2(const char* startTime,const char* stopTime,const char* channelList) = 0;

	//关闭
	//close
	virtual void stop() = 0;

	//释放对象
	//destroy object
	virtual void release() = 0;

	//向后读取一帧数据	frame:一帧数据(返回）	
	//attentionList,attentionNumber : 关注的数据类型（如果不是关注的数据类型，则忽略掉）
	//pCurrentChannel:当前通道，返回
	//read next one frame	frame:one frame's pack(output)
	//attentionList,attentionNumber : need frames,if we don't care,nned to skip
	//pCurrentChannel:current channel,using for return,from 1
	virtual	bool readNextOneFrame(HowenDeviceNetwork::structs::common::frame_data& frame, int attentionFrameList[], int attentionNumber,int* pCurrentChannel) = 0;

	//向前读取一个主帧数据	frame:一帧数据(返回）	
	//pCurrentChannel:当前通道，返回
	//read main frame backward	frame:one frame's pack(output)
	//pCurrentChannel:current channel,using for return,from 1
	virtual	bool readPreviewOneMainFrame(HowenDeviceNetwork::structs::common::frame_data& frame, int* pCurrentChannel) = 0;

	//时间模式跳转	seconds:偏离文件开始的秒数
	//jump by time	seconds:seconds off file start
	virtual	bool gotoSeconds(int seconds) = 0;

	//时间模式跳转	szTime:指定具体时间
	//jump by time	szTime:special time,such as "2017-05-11 03:21:35"
	virtual	bool gotoTime(const char* szTime) = 0;

	//获取当前时间
	//get current time,such as "2017-05-11 03:21:35"
	virtual const char* getCurrentTime() = 0;

	//是否读取到文件尾
	//is goto the file tail
	virtual bool isTail() = 0;
};


//-------------------------------------------------------------------------------------
//普通文件读写（需要设备层开发使用），实现后用实现文件传输业务
//-------------------------------------------------------------------------------------
class IFileReaderWriter
{
public:
	//启动	返回：true：成功	false：失败
	//utf8Name:utf8文件格式名称		_writeable:true:可写，需要移动到文件尾部，以便断点续传，false:只读
	//fileType:文件类型
	//start(normal file)	return:true:succeed, false:failed
	//utf8Name:filename		_writeable:true:can write,need to move the end of file ,using for continue sending ;false:only read
	//fileType:文件类型
	virtual bool start(const char* utf8Name,bool _writeable,HowenDeviceNetwork::enums::e_file_type fileType) = 0;

	//关闭
	//close
	virtual void stop() = 0;

	//释放对象
	//destroy object
	virtual void release() = 0;

	//读取数据	返回：实际读取的长度，为0标识失败
	//bufferData : 缓冲区，由函数内部写入
	//bufferLength:缓冲区长度
	//read data	  return:total length read length,if 0 is error
	//bufferData : for writing inside function
	//bufferLength:need to read
	virtual	int readData(char* bufferData,int bufferLength) = 0;

	//写入数据	返回：实际写入的长度，为0标识失败
	//bufferData : 缓冲区
	//bufferLength:缓冲区长度
	//write data	  return:total length write length,if 0 is error
	//bufferData : buffer
	//bufferLength:need to read
	virtual	int writeData(const char* bufferData, int bufferLength) = 0;

	//位置模式跳转	offsetBytes:偏离文件开始的字节数量
	//jump by position	offsetBytes:offset bytes from file start
	virtual	bool gotoPosition(int offsetBytes) = 0;

	//获取当前文件偏移量
	//get the offset bytes of file header
	virtual int getCurrentPosition() = 0;

	//是否读取到文件尾
	//is goto the file tail
	virtual bool isTail() = 0;
};


//-------------------------------------------------------------------------------------
//设备操作接口（需要设备层开发使用），实现后用来直接操作设备的相关业务控制
//-------------------------------------------------------------------------------------
class IHardwareDriver
{
public:
	//获取设备概要信息
	//get device's summary
	virtual void getSummary(HowenDeviceNetwork::structs::common::device_summary& summary) = 0;

	//获取需要进行登录注册的服务器信息
	//get the host information about which device's will register
	virtual void getRegisterHost(char* out_host_buffer, int length, unsigned short& out_port) = 0;

	//获取状态信息
	//get status data of device
	virtual void getStatusData(HowenDeviceNetwork::structs::status::allData& __status) = 0;

	//获取注册链路网络类型	out_wifi_ap_name:wifi ap 名称(如果为wifi接入时候返回)	length:wifi ap缓冲区长度
	//get regiseter network type
	virtual HowenDeviceNetwork::enums::e_access_net getRegisterNetworkType(char* out_wifi_ap_name,int length) = 0;

	//获取文件存储路径，返回格式为"/sd1/xx/",用来保存本代理相关的数据，如设备状态缓冲，报警缓存等
	//get the file storage path,sample:"/sd1/xx/",using for cache data,like deivce'status ,alarm' device
	virtual const char* getCachePath() = 0;

public:
	//注册
	//__registered:注册成功与否
	//remoteAddress:服务器地址（如果是域名，此处已经解析为有效地址），如"201.91.21.12:5678"
	//clientAddress:本地地址，如"201.91.21.12:5678"
	virtual void notifyRegistered(bool __registered, const char* remoteAddress, const char* clientAddress) = 0;

	//语音数据	返回值:保留
	//pNotify:数据通知对象（外部实现，SDK内部调用） dataBuffer:语音数据		dataLngth:长度
	//remote voice data return:reserved
	//pNotify:data notify object(implement outside,sdk will call it)	dataBuffer:remote voice data ,dataLength:length
	virtual int notifyVoiceDataFromRemote(IMediumDataNotify* pNotify, const char* dataBuffer, int dataLngth) = 0;

	//串口数据	返回值:保留
	//pNotify:数据通知对象（外部实现，SDK内部调用） dataBuffer:串口数据		dataLngth:长度
	//remote voice data return:reserved
	//pNotify:data notify object(implement outside,sdk will call it)	dataBuffer:remote data ,dataLngth:length
	virtual int notifySerialPortDataFromRemote(IMediumDataNotify* pNotify, const char* dataBuffer, int dataLngth) = 0;

	//强制编码主帧
	//force to make main frame
	virtual int notifyMakeIFrame(IMediumDataNotify* pNotify) = 0;

#if defined(WIN32) || defined(_WINDOWS)
	//消息通知,window有效，用于模拟器,messageID 参考 contractDeclare.h
	//notify net message，valid under window ,not for user,only for simulator
	virtual int notifyNetMessage(int messageID ,const char* content,int length) = 0;
#endif

public:
	//直播	pNotify:数据通知对象（内部实现，外部调用）返回值:保留
	//live stream	return:reserved
	virtual int livestream(IMediumDataNotify* pNotify) = 0;

	//抓拍	channel:通道，从1开始		outFilePath:设备生成的文件绝对路径，最大240字节	 返回值:保留	
	//snapshot,channel:from 1	outFilePath:device's generate absolute file path，less than 240 bytes; 	return:reserved
	virtual int snapshot(int channel,char* outFilePath) = 0;

	//语音聊天	pNotify:数据通知对象（内部实现，外部调用） 返回值:保留
	//voice chat	return:reserved
	virtual int voiceChat(IMediumDataNotify* pNotify) = 0;

	//创建文件查询对象，内部调用对象的release进行释放
	//create file query object, that will call release fuction to destroy when finish 
	virtual IFileQuery* createFileQueryObject() = 0;

	//创建录像文件文件读取对象，内部调用对象的release进行释放
	//create file read object, that will call release fuction to destroy when finish 
	virtual IRecordFileReader* createRecordFileReader() = 0;

	//创建普通文件读写对象，内部调用对象的release进行释放
	//create file read object, that will call release fuction to destroy when finish 
	virtual IFileReaderWriter* createNormalFileReaderWriter() = 0;

	//启动ftp传输文件	返回：保留
	//sessionID:会话编号		ftps:ftp服务器信息，规则 : ftp://用户名:密码@服务器:端口
	//action:动作类型		type:文件类型		version:版本信息（用于升级，参数等需要版本管理的信息）
	//start to ftp transfer file		return:reserved
	//sessionID:sessionID		ftps:ftp's server info，fule : ftp://user:pwd@host:port
	//action:action		type:file type		version:about need to upgrade ,setting
	virtual int startftpTransfer(const char* sessionID, const char* ftps, HowenDeviceNetwork::enums::e_ftp_action action, HowenDeviceNetwork::enums::e_file_type type, const char* utf8FileName, const char* version) = 0;

	//串口代理	pNotify:数据通知对象（内部实现，外部调用） 返回值:保留
	//serial port proxy	return:reserved
	virtual int serialPortProxy(IMediumDataNotify* pNotify) = 0;

	//参数配置	_type:字符串类型		json:需要操作的json格式的字符串参数,为空，标识获取参数		
	//			outJson:返回的json格式的字符串参数		outLength:传入时候为outJson长度，传出为实际使用长度
	//			返回值:保留
	//setting	_type:type		json:json format parameter,get setting if is NULL
	//			outJson:json format out data		outLength:means outJson's length when input,means really length when output
	//			return:reserved
	virtual int setting(const char* _type,const char* json,char* outJson,int& outLength) = 0;


/****************************设备控制************************************/
/****************************device control*****************************/
public:
	//云台控制
	//control ptz
	virtual int ptz(HowenDeviceNetwork::structs::deviceControl::ptz& _ptz) = 0;

	//重启
	//reboot
	virtual int reboot() = 0;

	//恢复默认参数
	//reset default setting
	virtual int defaultSetting() = 0;

	//同步时间		specialTime:为空，则根据定位同步，不为空则设置当前时间，格式为"2017-05-11 11:23:11"
	//sync time		specialTime:if NULL,sync by location time,if not NULL,format:"2017-05-11 11:23:11"
	virtual int syncTime(const char* specialTime) = 0;

	//录像控制			startChannel,stopChannelList:启停录像信息，通过';'分割
	//record control	startChannel,stopChannelList:start or stop channels，seperate by ';'
	virtual int recordControl(const char* startChannelList, const char* stopChanneList) = 0;

	//车辆控制
	//control vehicle
	virtual int vehicleControl(HowenDeviceNetwork::structs::deviceControl::vehi_operate& para) = 0;

	//格式化磁盘			diskName:磁盘名称，sd1,sd2,hdd1,hdd2
	//format disk		diskaName:name of diks,like sd1,sd2,hdd1,hdd2
	virtual int formatDisk(const char* diskName) = 0;
};



//-------------------------------------------------------------------------------------
//业务控制类，内部实现，外部调用进行启动和关闭工作等业务
//-------------------------------------------------------------------------------------
class INetWorkController
{
public:
	//设置驱动对象
	//set driver object
	virtual void setDriver(IHardwareDriver* driver) = 0;

	//启动工作 para=NULL,默认参数
	//start working	 para=NULL,defualt setting
	virtual bool startwork(HowenDeviceNetwork::structs::works::parameter* para = NULL) = 0;

	//停止工作
	//stop working
	virtual bool stopwork() = 0;

	//释放对象
	//free obejct
	virtual void release() = 0;

public:
	//添加告警信息
	//add alarm information;
	virtual void pushOneAlarm(HowenDeviceNetwork::structs::alarms::oneAlarmData& __alarm) = 0;

	//通知磁盘装载情况,默认为打开，如果通知为关闭时候，需要内部关闭所有访问磁盘的动作，一般为格式化硬盘时候通知
	//notify storage mount status
	virtual void notifyStorageMount(bool mounted) = 0;

	//ftp传输文件报告	
	//sessionID:会话编号		ftps:ftp服务器信息，规则 : ftp://用户名:密码@服务器:端口
	//action:动作类型		type:文件类型		version:版本信息（用于升级，参数等需要版本管理的信息）
	//errorCode:错误代码
	//ftp transfer file	report
	//sessionID:sessionID		ftps:ftp's server info，fule : ftp://user:pwd@host:port
	//action:action		type:file type		version:about need to upgrade ,setting
	//errorCode:code of error
	virtual void notifyFPTTransfer(const char* sessionID, const char* ftps, HowenDeviceNetwork::enums::e_ftp_action action, HowenDeviceNetwork::enums::e_file_type type, const char* utf8FileName, const char* version, HowenDeviceNetwork::enums::e_error_code errorCode) = 0;

	//新文件创建报告
	//type:文件类型		utf8FileName:文件路径
	//channelList:通道列表，从1开始，';'分割，如果为空，不需要关注
	//new file report
	//type:file type	utf8FileName:file path
	//channelList:list of channels,start from 1,seperate by ';',not care this data if NULL
	virtual void notifyNewFileCreate(HowenDeviceNetwork::enums::e_file_type type, const char* utf8FileName, const char* channelList) = 0;

};

#endif
