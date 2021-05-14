
/*
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月10日
描述: 接口定义
历史:
1、2017年04月10日 初步创建
使用说明:
1、需要先执行initialize
2、操作设备之前,需要先执行一次openDevice打开设备
3、关于设备的所有操作都基于设备编号和会话编号进行,请确保session编号唯一性,也可采用createSessionId创建
4、业务进行中
5、业务进行完毕后需要先对所有设备执行closeDevice
6、最后执行uninitialize
*/

/*
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.10
Description: interface definition
History:
1,20170410: initial establish
instruction:
1, execute "initialize" 
2, execute "openDevice" command to open device before operate device 
3, all the device operation is base on device ID and session number, make sure session number is unique, can be created by "createSessionId"
4, bussiness under processing
5, execute "closeDevice" for all devices before task finished 
6, execute "uninitialize" by the end
*/



#ifndef _DeviceDriver_API_h_
#define _DeviceDriver_API_h_

#pragma once

#include "DeviceDriver_Define.h"

namespace howenDriver
{
	namespace api
	{

#if defined(_WINDOWS) || defined(_WIN32)

	#ifdef DEVICEDRIVERSDK_EXPORTS
		#define device_driver_sdk_api extern "C" __declspec(dllexport)
	#else
		#define device_driver_sdk_api extern "C" __declspec(dllimport)
	#endif

	#else

		#define device_driver_sdk_api extern "C"

#endif

		//-------------------------------------------------------------------------------------
		// 功能：初始化环境
		// 参数：para[in]:工作参数
		// 返回：错误代码（参考 howenDriver::standard::e_error_code）
		//-------------------------------------------------------------------------------------
	
		// fuction:initialization environment 
		// @parameter:para[in]:working parameter 
		// Return:Error Code（refer to" howenDriver::standard::e_error_code"）
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long	HDeviceDriver_Initialize(standards::s_work* para);

		//-------------------------------------------------------------------------------------
		// 功能：释放环境
		// 参数：无
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:release environement 
		// @parameter:null 
		// Return:null
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api void	HDeviceDriver_Uninitialize();

		//-------------------------------------------------------------------------------------
		// 功能：创建会话编号
		// 参数：session[out]:会话信息,需要分配足够的大小,参考 howenDriver::constants::max_session
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:create session number 
		// @parameter:session[out]:session information, need to assign enough size, refer to "howenDriver::constants::max_session"
		// @Return:null
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api void HDeviceDriver_CreateSessionId(char* session);





		//-------------------------------------------------------------------------------------
		// 功能：打开设备,打开后方可对设备进行操作
		// 参数：deviceID[in]:设备编号
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:startup device, operation on device can be carried out only after device startup 
		// @parameter:deviceID[in]:Device ID
		// Return:Error Code 
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_OpenDevice(const char* deviceID);

		//-------------------------------------------------------------------------------------
		// 功能：关闭设备,程序退出之前或者需要清理设备时候,调用
		// 参数：deviceID[in]:设备编号
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:shutdown device, call this function when program exit or need to clear the device
		// @parameter:deviceID[in]: DeviceID
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_CloseDevice(const char* deviceID);

		//-------------------------------------------------------------------------------------
		// 功能：停止业务(start打头的函数,关闭时候都需要调用该函数执行关闭)
		//		 startPreview、startVoice、startRecordReplay,startTransferFile2DeviceViaDirect等业务的关闭
		// 参数：deviceID[in]:设备编号	sessionID[in]:会话编号
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:Stop bussiness(the function start with "start",need to call this function to stop program when shutdown )
		//		 close the bussiness such as "startPreview,startVoice,startRecordReplay,startTransferFile2DeviceViaDirect"
		// @parameter:deviceID[in]:device number	sessionID[in]:Session number
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_StopBussiness(const char* deviceID, const char* sessionID);

		//-------------------------------------------------------------------------------------
		// 功能：视频预览
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:video preview
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_StartPreview(standards::s_video_preview_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：预览强制编码主帧(便于多个客户端快速预览)
		// 参数：deviceID[in]:设备编号	sessionID[in]:会话编号
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// Function:make I frame when preview (for multi client fast preview )
		// @parameter:deviceID[in]:Device number,	sessionID[in]:Session number
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_MakeIFrameWhenPreview(const char* deviceID, const char* sessionID);

		//-------------------------------------------------------------------------------------
		// 功能：抓拍,使用stopBussiness执行关闭
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:snapshot, use "stopBussiness" to execute shutdown
		// @parameter:para[in]:Request Parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_Snapshot(standards::s_snapshot_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：启动语音业务,使用stopBussiness执行关闭,使用sendVoiceData2Device发送音频数据
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @Function:start voice bussiness, use "StopBussiness" to execute shutdown, use "sendVoiceData2Device" to send voice data
		// @parameter:para[in]:request parameter 
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_StartVoice(standards::s_voice_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：发送语音数据到设备(用于对讲,广播等业务,G720,40kbps的采样压缩格式数据)
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:send voice data to device(for two way audio and broadcast, G720, 40kbps compressed format data)
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_SendVoiceData2Device(standards::s_send_media_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：文件查询
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:file search 
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_FileQuery(standards::s_file_query_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：启动录像回放,使用stopBussiness执行关闭
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:start video playback, use "stopBussiness" to execute shutdown
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_StartRecordReplay(standards::s_replay_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：录像回放控制
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:record playback control 
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_RecordReplayControl(standards::s_replay_control* para);

		//-------------------------------------------------------------------------------------
		// 功能：启动串口代理,使用stopBussiness执行关闭,使用sendData2DeviceSerialPort发送串口数据
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:start series port proxy, use "stopBussiness" to execute shutdown use "sendData2DeviceSerialPort" to send series port data
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_StartSerialPortProxy(standards::s_serialport_proxy_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：发送数据到设备串口
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:send data to device serial port 
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_SendData2DeviceSerialPort(standards::s_send_media_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：启动直接传输文件,使用stopBussiness执行关闭,使用sendFileData2Device发送文件数据
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:start transfer file directly, use "stopBussiness" to execute shutdown, use "sendFileData2Device" to send file data
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_StartTransferFileViaDirect(standards::s_transfer_file_via_direct_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：发送文件数据到设备
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:send file data to device
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_SendFileData2Device(standards::s_send_media_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：通过ftp传输文件到
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:transfer file via ftp
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_TransferFileViaFtp(standards::s_transfer_file_via_ftp_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：直接设置设备参数(除此之外,还可以通过ftp模式设置参数)
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:device setting directly (and the parameter can be set via ftp mode as well)
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_DeviceSettingDirect(standards::s_device_setting_via_direct_request* para);

		//-------------------------------------------------------------------------------------
		// 功能：设备控制
		// 参数：para[in]:请求参数
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:Device Control 
		// @parameter:para[in]:request parameter
		// Return:Error Code
		//-------------------------------------------------------------------------------------
		device_driver_sdk_api long long HDeviceDriver_DeviceControl(standards::s_device_control_request* para);
	};
};

#endif