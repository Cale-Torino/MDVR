

#include "stdafx.h"
#include "SDKProxy.h"
#include <DeviceDriverSDK/DeviceDriver_API.h>
#include <multimedia/decoder/decoder_define.h>
#include "Constants.h"
#include "MultiMediaBusiness.h"
#include "DirectFileSending.h"
#include "DirectFileDownloading.h"
#include "deviceManager.h"

#pragma warning(disable:4996)
#pragma warning(disable:4838)
#pragma warning(disable:4309)

//会话应答回调函数
//callback fuction for session respond
void CALLBACK SessionAnswer(const char* deviceID, const char* sessionID, howenDriver::responds::s_general_repsond* respond, long long userdata1, long long userdata2)
{
	SDKProxy* proxy = (SDKProxy*)userdata1;

	TRACE("Device [%s]:[%s] answer [%d,0x%x]. \n", deviceID, sessionID, respond->businessCode, respond->errorCode);

	switch (respond->businessCode)
	{
	case howenDriver::enums::e_business_type_file_query:
		{
			if (respond->errorCode == howenDriver::enums::e_error_code_data_continue)
				proxy->SendMessage2Bounder(constants::device_record_file_detail, (WPARAM)deviceID, (LPARAM)&respond->payload.fileDetail);
		}
		break;
	case howenDriver::enums::e_business_type_snapshot:
		{
			if (respond->errorCode == howenDriver::enums::e_error_code_succeed)
			{
				howenDriver::responds::s_general_repsond::s_snapshot_respond& snap = respond->payload.snapshot;
				for (int i = 0; i < snap.count; ++i)
				{
					howenDriver::responds::s_general_repsond::s_snapshot_item& item = snap.item[i];
					TRACE("Device [%s,%d] snapshot [%s]. \n", deviceID, item.channel, item.path);
				}
			}
		}
		break;
	case howenDriver::enums::e_business_type_setting_to_device_via_direct:
		{
			
			if (respond->errorCode == howenDriver::enums::e_error_code_succeed)
			{
				howenDriver::responds::s_general_repsond::s_setting_to_device_via_direct_respond& rep = respond->payload.deviceSettingViaDirect;
				//TRACE("%s. \n", rep.jsonSetting);
				//FILE* p = fopen("d:/aa.json", "wb");
				//fwrite(rep.jsonSetting, 1, strlen(rep.jsonSetting), p);
				//fclose(p);
			}
		}
		break;
	case howenDriver::enums::e_business_type_file_transfer_via_direct:
		if (respond->errorCode == howenDriver::enums::e_error_code_succeed)
		{
			howenDriver::responds::s_general_repsond::s_file_transfer_via_direct_respond& rep = respond->payload.fileTransferViaDirect;

			//上传到设备
			//upload to device
			if (DirectFileSending::_cur->isCurrentSession(sessionID))
			{
				DirectFileSending::_cur->setOffset(rep.offset);
				DirectFileSending::_cur->startWork();
			}
			//从设备下载
			//download from device
			else
			{

			}
		}
		break;
	}
}

//设备注册回调函数
//callback function for device register
long long CALLBACK DeviceRegister(howenDriver::responds::s_device_info* para, bool online, long long userdata1, long long userdata2)
{
	/*
	if(online)
		TRACE("Device [%s]:online %s=>%s. \n", para->deviceID, para->remoteAddress, para->localAddress);
	else
		TRACE("Device [%s] offline!!! \n", para->deviceID);
	*/

	deviceManager::_cur->updateDevice(para->deviceID, online);

	return 0;
}

//媒体链路注册回调函数
//callback fuction for device media register
long long CALLBACK MediaLinkRegister(howenDriver::responds::s_media_link_info* para, bool online, long long userdata1, long long userdata2)
{
	if (online)
		TRACE("Media register Device [%s] with [%s] from [%s]. \n", para->deviceID, para->sessionID, para->remoteAddress);
	else
		TRACE("Media offline Device [%s] with [%s] !!! \n", para->deviceID, para->sessionID, para->remoteAddress);

	return 0;
}

//位置和状态回调函数
//callback fuction for device's status report
void CALLBACK DeviceStatusCallback(howenDriver::responds::s_status* para, long long userdata1, long long userdata2)
{
	SDKProxy* proxy = (SDKProxy*)userdata1;
	if(proxy->isCurrentDeviceID(para->deviceID))
		proxy->SendMessage2Bounder(constants::device_status_update, (WPARAM)para, NULL);
	//TRACE("Device[%s] status update[%s] (%f,%f). \n", para->deviceID, para->all.dtu, para->all.location.longitude, para->all.location.latitude);
}

//告警回调函数
//callback function for device's alarm report
void CALLBACK DeviceAlarmCallback(howenDriver::responds::s_alarm* para, long long userdata1, long long userdata2)
{
	TRACE("Device[%s] [%s] create alarm[%d]. \n", para->deviceID, para->alarm.deviceTime, para->alarm.type);
}

//设备文件数据回调函数
//callback funtion for file data from device
void CALLBACK FileDataFromDevice(const char* deviceID, const char* sessionID, howenDriver::standards::s_frame_data* frame, long long userdata1, long long userdata2)
{
	if (frame->frameLength > 0)
	{
		DirectFileDownloading::_cur->writeData(frame->frameBuffer,frame->frameLength);
	}
	else
	{
		DirectFileDownloading::_cur->stopWork();
	}
	//TRACE("Device[%] [%s] send file data length:%d. \n", deviceID, sessionID, frame->frameLength);
}

//远程回放媒体数据回调函数
//callback fuction for playback media data remotely from device
void CALLBACK RemoteReplayDataFromDevice(const char* deviceID, const char* sessionID, howenDriver::standards::s_frame_data* data, long long userdata1, long long userdata2)
{
	howenPlayer::standards::s_frame_data frame;

	frame.frameBuffer = data->frameBuffer;
	frame.frameLength = data->frameLength;
	frame.frameType = data->frameType;
	frame.timestamp = data->timestamp;
	MultiMediaBusiness::_cur->playAVFrame(sessionID, frame);
}

//时间戳转换： 设备时间为0时区时间，微妙
//stampTime: is recevice from device,the unit is microsecond
void stamp_to_standard(long long stampTime)
{
	long long seconds = stampTime / 1000 / 1000;
	time_t tick = (time_t)seconds;
	struct tm t = *gmtime(&tick);

	char s[100] = { 0 };
	strftime(s, sizeof(s), "\n %Y-%m-%d %H:%M:%S", &t);
	OutputDebugStringA(s);

	return;
}

//实时预览数据回调函数
//callback function for preivew media data from device
void CALLBACK PreviewMediaData(const char* deviceID, const char* sessionID, howenDriver::standards::s_frame_data* data, long long userdata1, long long userdata2)
{
	howenPlayer::standards::s_frame_data frame;

	frame.frameBuffer = data->frameBuffer;
	frame.frameLength = data->frameLength;
	frame.frameType = data->frameType;
	frame.timestamp = data->timestamp;
	//stamp_to_standard(frame.timestamp);
	MultiMediaBusiness::_cur->playAVFrame(sessionID, frame);
}

//串口数据回调函数
//callback function for device serial port data 
void CALLBACK SerialPortDataFromDevice(const char* deviceID, const char* sessionID, howenDriver::standards::s_frame_data* frame, long long userdata1, long long userdata2)
{
	TRACE("Device[%s] [%s] send serial port data length:%d. \n", deviceID, sessionID, frame->frameLength);
}


//设备对讲监听数据回调函数
//callback function for voice data from device
void CALLBACK VoiceDataFromDevice(const char* deviceID, const char* sessionID, howenDriver::standards::s_frame_data* data, long long userdata1, long long userdata2)
{
	howenPlayer::standards::s_frame_data playFrame;

	playFrame.frameBuffer = data->frameBuffer;
	playFrame.frameLength = data->frameLength;
	playFrame.frameType = data->frameType;
	playFrame.timestamp = data->timestamp;
	MultiMediaBusiness::_cur->playAVFrame(sessionID, playFrame);

	return ;
}

SDKProxy::SDKProxy()
{
	m_isWorking = false;
}

SDKProxy::~SDKProxy()
{

}

//是否工作中
//is working?
bool SDKProxy::isWorking()
{
	return m_isWorking;
}

//启动工作
//start work,include initializing sdk etc.
void SDKProxy::startWork(HWND msgWnd,int port)
{
	m_messageReceiveWnd = msgWnd;

	howenDriver::standards::s_work para = { 0 };
	para.size = sizeof(para);
	
	para.register_port = port;
	para.recv_timeout = 60;
	para.auto_subscribe_status_content = 0xFFFF;
	para.auto_subscribe_status_content_include_alarm = 0x01;

	para.alarm_func = DeviceAlarmCallback;
	para.alarm_userdata1 = (long long)this;
	para.alarm_userdata2 = NULL;

	para.device_register_func = DeviceRegister;
	para.device_register_userdata1 = (long long)this;
	para.device_register_userdata2 = NULL;

	para.file_transfer_to_server_func = FileDataFromDevice;
	para.file_transfer_to_server_userdata1 = (long long)this;
	para.file_transfer_to_server_userdata2 = NULL;

	para.media_register_func = MediaLinkRegister;
	para.media_register_userdata1 = (long long)this;
	para.media_register_userdata2 = NULL;

	para.preview_func = PreviewMediaData;
	para.preview_userdata1 = (long long)this;
	para.preview_userdata2 = NULL;

	para.replay_func = RemoteReplayDataFromDevice;
	para.replay_userdata1 = (long long)this;
	para.replay_userdata2 = NULL;

	para.serial_port_func = SerialPortDataFromDevice;
	para.serial_port_userdata1 = (long long)this;
	para.serial_port_userdata2 = NULL;

	para.session_answer_func = SessionAnswer;
	para.session_answer_userdata1 = (long long)this;
	para.session_answer_userdata2 = NULL;

	para.status_func = DeviceStatusCallback;
	para.status_userdata1 = (long long)this;
	para.serial_port_userdata2 = NULL;

	para.voice_func = VoiceDataFromDevice;
	para.voice_userdata1 = (long long)this;
	para.voice_userdata2 = NULL;

	howenDriver::api::HDeviceDriver_Initialize(&para);

	m_isWorking = true;
}

//停止工作
//stop work
void SDKProxy::stopWork()
{
	howenDriver::api::HDeviceDriver_Uninitialize();
	m_isWorking = false;
}

//发送消息到界面展现
//send message to bounder for display
void SDKProxy::SendMessage2Bounder(UINT msg, WPARAM wparam, LPARAM lParam)
{
	::SendMessageTimeout(m_messageReceiveWnd, msg, wparam, lParam, 0, 1000, NULL);
}

//设备管理
//device manager ,open or close device
void SDKProxy::DeviceManager(const char* deviceID, bool open)
{
	if (open)
		howenDriver::api::HDeviceDriver_OpenDevice(deviceID);
	else
		howenDriver::api::HDeviceDriver_CloseDevice(deviceID);
}

//预览频视
//start video preview
void SDKProxy::StartPreview(const char* deviceID, int channel, bool _mainStream, const char* sessionID,const char* serverHost)
{
	howenDriver::standards::s_video_preview_request req;
	req.channel = channel;
	req.deviceID = deviceID;
	req.serverHost = serverHost;

	//修改该参数进行主码流和子码流的请求
	//you can change the value of "req.stream" if you need to switch the stream
	if(_mainStream)
		req.stream = howenDriver::enums::e_stream_type_mainstream;
	else
		req.stream = howenDriver::enums::e_stream_type_substream;

	req.sessionID = sessionID;
	howenDriver::api::HDeviceDriver_StartPreview(&req);
}

//关闭会话
//close session
void SDKProxy::CloseSession(const char* deviceID,const char * sessionID)
{
	howenDriver::api::HDeviceDriver_StopBussiness(deviceID, sessionID);
}

//文件查询
//file query
void SDKProxy::FileQuery(const char* deviceID)
{
	howenDriver::standards::s_file_query_request req;
	req.channelList = "1;2;4";
	req.deviceID = deviceID;
	req.sessionID = "file_query_test";
	req.type = howenDriver::enums::e_file_type_normal_record;

	SYSTEMTIME cur;
	GetLocalTime(&cur);

	char startTime[24] = { 0 };
	char stopTime[24] = { 0 };
	::sprintf_s(startTime, "%04d-%02d-%02d 00:00:00", cur.wYear, cur.wMonth, cur.wDay);
	::sprintf_s(stopTime, "%04d-%02d-%02d 23:59:59", cur.wYear, cur.wMonth, cur.wDay);

	req.startTime = startTime;
	req.stopTime = stopTime;

	howenDriver::api::HDeviceDriver_FileQuery(&req);
}

//远程回放
//remote playback 
void SDKProxy::StartRemoteReplay(const char* deviceID, const char* sessionID, const char* channelList, const char* startTime, const char* stopTime, const char* serverHost)
{
	howenDriver::standards::s_replay_request req;
	req.channelList = channelList;
	req.deviceID = deviceID;
	req.serverHost = serverHost;

	req.sessionID = sessionID;
	req.startTime = startTime;
	req.stopTime = stopTime;

	howenDriver::api::HDeviceDriver_StartRecordReplay(&req);
}

//回放时间跳转
//goto the special playback time
void SDKProxy::ReplayControl(const char* deviceID,const char* sessionID,const char* gotoTime)
{
	howenDriver::standards::s_replay_control req;
	req.deviceID = deviceID;
	req.action = 0;
	req.sessionID = "replay-remote-file";
	::strcpy_s(req.payload.offset, gotoTime);

	howenDriver::api::HDeviceDriver_RecordReplayControl(&req);
}

//抓拍
//control device to snapshot
//after snapshot ,the file will be uploaded to ftp server
void SDKProxy::Snapshot(const char* deviceID,const char* channelList)
{
	char session[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(session);

	howenDriver::standards::s_snapshot_request req;
	req.channelList = channelList;
	req.deviceID = deviceID;
	req.sessionID = session;

	howenDriver::api::HDeviceDriver_Snapshot(&req);
}

//对讲&监听,需要通过howenDriver::api::sendMediaData发送对讲数据,发送之前需要做G726编码
//listen & talk,need to send data which is compressed by G726 protocol to device use api howenDriver::api::sendMediaData
void SDKProxy::StartVoice(const char* deviceID, int channel,const char* sessionID, const char* serverHost)
{
	howenDriver::standards::s_voice_request req;
	req.deviceID = deviceID;
	req.channel = channel;
	
	//修改该参数进行对讲、广播、监听切换
	//you can change the value to switch work mode like talk, license, broaccast
	req.mode = howenDriver::enums::e_voice_mode_listen;

	req.serverHost = serverHost;
	req.sessionID = sessionID;
	howenDriver::api::HDeviceDriver_StartVoice(&req);
}

//直接设置参数到设备
//set device parameter to device directly 
void SDKProxy::DeviceSettingDirect(const char* deviceID,const char* json)
{
	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--setting");

	howenDriver::standards::s_device_setting_via_direct_request req;
	req.deviceID = deviceID;
	req.sessionID = sessionID;
	req.jsonSetting = json;
	howenDriver::api::HDeviceDriver_DeviceSettingDirect(&req);
}

//获取文件大小
//get file size 
int getFileSizeEx(const char* filenName)
{
	FILE* p = fopen(filenName, "rb");
	if (NULL == p)
		return 0;

	fseek(p, 0, SEEK_END);
	int length = ftell(p);
	fclose(p);

	return length;
}

//启动文件发送
//start to send file to device
void SDKProxy::StartTransfer2DeviceDirect(const char* deviceID,const char* fileName, const char* serverHost)
{
	int fileSize = getFileSizeEx(fileName);
	if (0 == fileSize)
		return;

	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--transfer-file");

	howenDriver::standards::s_transfer_file_via_direct_request req;
	req.deviceID = deviceID;
	req.fileName = fileName;
	req.fileSize = fileSize;
	req.serverHost = serverHost;
	req.sessionID = sessionID;
	req.action = howenDriver::enums::e_file_transfer_action_to_device;
	req.fileType = howenDriver::enums::e_file_type_upgrade;
	req.offset = 0;

	DirectFileSending::_cur->setParameter(deviceID, sessionID, fileName);

	howenDriver::api::HDeviceDriver_StartTransferFileViaDirect(&req);
}

//下载文件
//start to get file from device
void SDKProxy::StartDownloaFileFromDeviceViaDirect(const char* deviceID, const char* fileName, const char* serverHost)
{
	char sessionID[128] = { 0 };
	::strcat(sessionID, "download-file");

	int hadDownload = DirectFileDownloading::_cur->startWork(fileName);

	howenDriver::standards::s_transfer_file_via_direct_request req;
	req.deviceID = deviceID;
	req.fileName = fileName;
	req.fileSize = 0;
	req.serverHost = serverHost;
	req.sessionID = sessionID;
	req.action = howenDriver::enums::e_file_transfer_action_to_server;
	req.offset = hadDownload;
	req.fileType = howenDriver::enums::e_file_type_alarm_snapshot;
	howenDriver::api::HDeviceDriver_StartTransferFileViaDirect(&req);
}

//通过ftp发送文件
//send file to device by ftp 
void SDKProxy::Transfer2DeviceViaFtpMode(const char* deviceID,const char* fileName,const char* ftp)
{
	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--transfer-file");

	howenDriver::standards::s_transfer_file_via_ftp_request req;
	//让设备从ftp服务器下载指定文件
	//let the device download file from ftp
	req.action = howenDriver::enums::e_ftp_action_download_from_server;
	req.deviceID = deviceID;
	req.fileName = fileName;
	req.ftp = ftp;
	req.sessionID = sessionID;
	req.version = "V1.0.1.35";
	req.fileType = howenDriver::enums::e_file_type_upgrade;

	howenDriver::api::HDeviceDriver_TransferFileViaFtp(&req);
}

//重启
//reboot
void SDKProxy::Reboot(const char* deviceID)
{
	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--reboot");

	howenDriver::standards::s_device_control_request req;
	req.action = howenDriver::enums::e_control_device_action_reboot;
	req.deviceID = deviceID;
	req.payload.reboot.reserved = 0;
	req.sessionID = sessionID;

	howenDriver::api::HDeviceDriver_DeviceControl(&req);
}

//复位
//Reset
void SDKProxy::Reset(const char* deviceID)
{
	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--reset");

	howenDriver::standards::s_device_control_request req;
	req.action = howenDriver::enums::e_control_device_action_reset_setting;
	req.deviceID = deviceID;
	req.payload.reboot.reserved = 0;
	req.sessionID = sessionID;

	howenDriver::api::HDeviceDriver_DeviceControl(&req);
}

//格式化磁盘
//format disk
void SDKProxy::FormatDeviceDisk(const char* deviceID,const char* diskName)
{
	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--format");

	howenDriver::standards::s_device_control_request req;
	req.action = howenDriver::enums::e_control_device_action_format_disk;
	req.deviceID = deviceID;
	::strcpy(req.payload.disk.diskName, diskName);
	req.sessionID = sessionID;

	howenDriver::api::HDeviceDriver_DeviceControl(&req);
}

//串口代理
//serial port proxy 
void SDKProxy::StartSerialPortProxy(const char* deviceID,const char* sessionID,const char* serverHost)
{
	howenDriver::standards::s_serialport_proxy_request req;
	req.buadRate = 8000;
	req.channel = 1;
	req.checkBit = 0;
	req.dataBit = 8;
	req.deviceID = deviceID;
	req.serverHost = serverHost;
	req.sessionID = sessionID;
	req.stopBit = 0;
	howenDriver::api::HDeviceDriver_StartSerialPortProxy(&req);
}

//发送数据到串口
//send data to the serial port
void SDKProxy::SendData2SerialPort(const char* deviceID,const char* sessionID)
{
	char temp[8] = { 0x01,0x02,0x03,0x9,0x08,0x07,0xEE,0xED };
	howenDriver::standards::s_send_media_request req;
	req.data.frameType = howenDriver::enums::e_frame_type_serial_port;
	req.data.timestamp = 0;
	req.data.frameBuffer = temp;
	req.data.frameLength = 8;

	req.deviceID = deviceID;
	req.sessionID = sessionID;

	howenDriver::api::HDeviceDriver_SendData2DeviceSerialPort(&req);
}

//直接传输文件进行远程升级
//start to upgrade via send file to device directly 
void SDKProxy::StartUpgradeDirect(const char* deviceID, const char* fileName, const char* serverHost)
{
	int fileSize = getFileSizeEx(fileName);
	if (0 == fileSize)
		return;

	char sessionID[128] = { 0 };
	howenDriver::api::HDeviceDriver_CreateSessionId(sessionID);

	//加个标识,便于回调打印信息查看
	//add flag for debug
	::strcat(sessionID, "--upgrade-file");

	howenDriver::standards::s_transfer_file_via_direct_request req;
	req.deviceID = deviceID;
	req.fileName = fileName;
	req.fileSize = fileSize;
	req.serverHost = serverHost;
	req.sessionID = sessionID;
	req.action = howenDriver::enums::e_file_transfer_action_to_device;
	req.offset = 0;
	req.fileType = howenDriver::enums::e_file_type_upgrade;

	DirectFileSending::_cur->setParameter(deviceID, sessionID, fileName);

	howenDriver::api::HDeviceDriver_StartTransferFileViaDirect(&req);
}


//是否为当前选中的设备ID
//is current select device id
bool SDKProxy::isCurrentDeviceID(const char* deviceID)
{
	if (m_current_DeviceID.compare(deviceID) != 0)
		return false;

	return true;
}

void SDKProxy::setCurrentDeviceID(const char* deviceID)
{
	m_current_DeviceID = deviceID;
}