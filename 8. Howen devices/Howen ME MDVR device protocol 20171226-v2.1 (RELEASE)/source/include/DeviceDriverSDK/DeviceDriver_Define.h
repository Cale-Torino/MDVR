
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月10日
描述: 基础定义
历史:
1、2017年04月10日 初步创建
使用说明:
*/

/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.10
Description: Basic Definition 
History:
1,20170410:initial establish
instruction:
*/

#ifndef _DeviceDriver_Define_h_
#define _DeviceDriver_Define_h_

#pragma once

#include "DeviceDriver_Status.h"
#include "DeviceDriver_Alarm.h"

namespace howenDriver
{
	namespace standards
	{
		//数据帧
		//the frame data of media stream
		typedef struct s_frame_data
		{
			//数据类型,参考 howenDriver::enums::e_frame_type
			//data type,reference howenDriver::enums::e_frame_type
			int				frameType;

			//时间戳
			//timestamp of the current frame
			long long		timestamp;

			//数据缓冲区
			//the buffer of the current frame
			const char*		frameBuffer;

			//数据长度
			//the length of the buffer
			int				frameLength;
		}s_frame_data;
	}

	namespace responds
	{
		//设备信息
		//device information
		typedef struct s_device_info
		{
			//设备编号
			//device number ,exsampe:10011
			const char*		deviceID;

			//全球唯一标识
			//guid, reserved
			const char*		guid;

			//远程地址,格式为 "192.168.1.100:5678"
			//the address of device,example:"192.168.1.100:5678"
			const char*		remoteAddress;

			//本地地址,格式为 "192.168.1.100:5678"
			//local address,example:"192.168.1.100:5678"
			const char*		localAddress;

			//手机号码,如 "13912349876"
			//phone number,example:"13912349876"
			const char*		mobile;

			//wifi热点名称,针对access_net=howenDriver::enums::e_access_net_wifi有效
			//the AP name,valid only when access_net=howenDriver::enums::e_access_net_wifi
			const char*		wifiName;

			//设备注册的时间,格式为"2017-03-12 12:56:32"
			//device register time,example:"2017-03-12 12:56:32"
			const char*		deviceTime;

			//接入网络,参考 howenDriver::enums::e_access_net
			//access net type,reference: howenDriver::enums::e_access_net
			int				accessNet;

			//设备类型,如0x4000标识4路设备,0x8000标识8路设备
			//device type,example:0x4000 is 4 video channel device,0x8000 is 8 video channel device
			int				deviceType;

			//设备版本
			//device software(firmware) version
			const char*		softwareVersion;
		}s_device_info;

		//媒体链路信息
		//media register information
		typedef struct s_media_link_info
		{
			//设备编号
			//device number
			const char*		deviceID;

			//远程地址,格式为 "192.168.1.100:5678"
			//the address of device,example:"192.168.1.100:5678"
			const char*		remoteAddress;

			//本地地址,格式为 "192.168.1.100:5678"
			//local address,example:"192.168.1.100:5678"
			const char*		localAddress;

			//会话编号
			//session number
			const char*		sessionID;

			//接入网络,参考 howenDriver::enums::e_access_net
			//access type,reference:howenDriver::enums::e_access_net
			int				accessNet;

			//媒体类型,参考 howenDriver::enums::e_data_link_control
			//media type,reference howenDriver::enums::e_data_link_control
			int				mediaType;
		}s_media_link_info;

		//状态
		//status
		typedef struct s_status
		{
			//设备编号
			//device number
			char				deviceID[constants::max_id];

			//状态内容
			//the status of device
			status::s_all		all;
		}s_status;

		//报警
		//alarm
		typedef struct s_alarm
		{
			//设备编号
			//device number
			char				deviceID[constants::max_id];

			//状态内容
			//the status of device
			status::s_all		status;

			//告警内容
			//the content of alarm
			alarms::s_all		alarm;
		}s_alarm;

		//设备创建新文件,告警录像和告警抓拍打包时候告知,以便用户进行下载
		//device create new file,we can use this information to download the file.
		//when device create alarm record file or snapshot
		typedef struct s_device_new_file
		{
			//设备编号
			//device number
			const char*		deviceID;

			//文件路径
			//file path
			const char*		path;

			//文件类型,参考 howenDriver::enums::e_file_type
			//file type,reference:howenDriver::enums::e_file_type
			int				fileType;
		}s_device_new_file;

		//通用应答
		//general answer from device
		typedef struct s_general_respond
		{
			//预览应答
			//the respond of preview
			typedef struct s_preview_respond
			{
				//通道编号,从1开始
				//channel number,start from 1
				int				channel;

				//码流类型,(参考 howenDriver::enums::e_stream_type)
				//stream type,reference:howenDriver::enums::e_stream_type
				int				stream;
			}s_preview_respond;

			//抓拍内容项目
			//snapshot item
			typedef struct s_snapshot_item
			{
				//通道编号,从1开始
				//channel number,start from 1
				int				channel;

				//文件路径
				//file path
				char			path[constants::max_path];
			}s_snapshot_item;

			//抓拍应答
			//the respond of snapshot
			typedef struct s_snapshot_respond
			{
				//数量,如果为2,则只有item[0]和item[1]有效
				//count for item,if ==2,then item[0] or item[1] is valid
				int				count;

				//相关信息
				//information
				s_snapshot_item	item[constants::max_channel];
			}s_snapshot_respond;

			//语音
			//the respond of voice business
			typedef struct s_voice_respond
			{
				//通道编号,从1开始
				//channel number,start from 1
				int			channel;

				//工作模式,(参考 howenDriver::enums::e_voice_mode)
				//work mode,reference:howenDriver::enums::e_voice_mode
				int			mode;
			}s_voice_respond;

			//文件信息
			//the respond of file query
			typedef struct s_file_detail_respond
			{
				//开始时间
				//start time
				char		startTime[constants::max_time];

				//结束时间
				//stop time
				char		stopTime[constants::max_time];

				//通道列表,从1开始,多个复合,通过;分开,如"1;3;5"表示1,3,5三个通道
				//channel list,start from 1,multiple,seperate by ",";exsample:"1;3;5" include 1,3,5,total three channel
				char		channelList[constants::max_ch_list];

				//文件路径
				//file path
				char		path[constants::max_path];

				//文件类型,(参考 howenDriver::enums::e_file_type)
				//file type,reference:howenDriver::enums::e_file_type
				int			fileType;

				//文件大小
				//the size of file.(megabytes)
				int			fileSize;

				//文件时长(秒)
				//duration of record file.(seconds)
				int			fileDuration;
			}s_file_detail_respond;

			//回放应答
			//the respond of replay
			typedef struct s_replay_respond
			{
				//保留
				//reserved
				int			reserved;
			}s_replay_respond;

			//串口代理应答
			//the respond of serial port proxy
			typedef struct s_serial_port_proxy_respond
			{
				//保留
				//reserved
				int			reserved;
			}s_serial_port_proxy_respond;

			//直接传输模式的应答
			//the respond of transfer file directly
			typedef struct s_file_transfer_via_direct_respond
			{
				//相对文件的偏移量,用于断点续传
				//offset of file,for breakpoint resume
				int			offset;
			}s_file_transfer_via_direct_respond;

			//通过fpt传输文件模式应答
			//the respond of transferring file via ftp
			typedef struct s_file_transfer_via_ftp_respond
			{
				//ftp信息,规则为ftp://用户名:密码@服务器:端口
				//the details of ftp server,rule: ftp://user:password@server:port
				char		ftp[constants::max_server_name];

				//动作类型,(参考 howenDriver::enums::e_ftp_action)
				//action type,refer to:howenDriver::enums::e_ftp_action
				int			action;

				//文件类型,参考 howenDriver::enums::e_file_type
				//file type,refer to:howenDriver::enums::e_file_type
				int			fileType;

				//版本号(比如需要升级的版本信息)
				//version (example:the version about upgrade file)
				char		version[constants::max_time];

				//文件名
				//the path of file
				char		fileName[constants::max_path];
			}s_file_transfer_via_ftp_respond;

			//直接设置设备参数应答
			//set the device's parameter directly
			typedef struct s_setting_to_device_via_direct_respond
			{
				//参数信息,json格式
				//setting information,using json rule
				const char*	jsonSetting;
			}s_setting_to_device_via_direct_respond;

			//设备控制应答
			//the respond of control device
			typedef struct s_device_control_respond
			{
				//保留
				//reserved
				int			reserved;
			}s_device_control_respond;

			typedef union  u_payload
			{
				//预览
				//preview
				s_preview_respond								preview;

				//抓拍
				//snapshot
				s_snapshot_respond								snapshot;

				//语音
				//voice business
				s_voice_respond									voice;

				//文件信息
				//the respond of query file
				s_file_detail_respond							fileDetail;

				//回放
				//remote playback
				s_replay_respond								replay;

				//串口代理
				//proxy of serail port
				s_serial_port_proxy_respond						serialPortProxy;

				//文件直接传输
				//send file directly
				s_file_transfer_via_direct_respond				fileTransferViaDirect;

				//文件通过ftp传输
				//send file via ftp
				s_file_transfer_via_ftp_respond					fileTransferViaFtp;

				//直接设置设备参数
				//set the device's parameter directly
				s_setting_to_device_via_direct_respond			deviceSettingViaDirect;

				//设备控制
				//control device
				s_device_control_respond						deviceControl;
			}u_payload;

			//错误代码,参考 howenDriver::enums::e_error_code
			//error code,reference:howenDriver::enums::e_error_code
			int					errorCode;

			//业务类型 howenDriver::enums::e_business_type
			//business type,refer:howenDriver::enums::e_business_type
			int					businessCode;

			//负载
			//payload
			u_payload			payload;				
		}s_general_repsond;
	}

	namespace functions
	{

		//-------------------------------------------------------------------------------------
		// 功能：会话应答回调函数定义
		// 参数：deviceID[in]:设备编号	sessionID[in]:会话编号
		//		 repsond[in]:应答内容
		//		 userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：session respond callback function definition 
		// @parameter: deviceID[in]:Device Number	sessionID[in]:session number 
		//		 repsond[in]:respond content 
		//		 userdata1,userdata2[in]:user data
		// @Return :null
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK *callback_session_answer)(const char* deviceID,const char* sessionID, responds::s_general_respond* respond,long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：设备注册回调函数定义
		// 参数：para[in]:设备信息	online[in]:true:在线,false:掉线
		//		 userdata1,userdata2[in]:用户数据
		// 返回：保留
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:device registe callback function definition 
		// @parameter:para[in]:device information	online[in]:true:online,false:offline 
		//		 userdata1,userdata2[in]:user data
		// @Return:reserved 
		//-------------------------------------------------------------------------------------
		typedef long long (CALLBACK *callback_device_register)(responds::s_device_info* para, bool online, long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：媒体链路注册回调函数定义
		// 参数：para[in]:媒体链路信息	online[in]:true:在线,false:掉线
		//		 userdata1,userdata2[in]:用户数据
		// 返回：保留
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:media link registe callback function definition
		// @parameter:para[in]:media link information online[in]:true:online,false:offline
		//		 userdata1,userdata2[in]:user data
		// @Return:reserved
		//-------------------------------------------------------------------------------------
		typedef long long (CALLBACK* callback_media_register)(responds::s_media_link_info* para, bool online, long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：位置和状态回调函数定义
		// 参数：para[in]:参数数据		 userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:location and status callback function definition 
		// parameter:para[in]:parameter data		 userdata1,userdata2[in]:user data
		// @Return :null
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK* callback_status)(responds::s_status* para, long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：告警回调函数定义
		// 参数：para[in]:参数数据		 userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:alarm callback function definition 
		// parameter:para[in]:parameter data		 userdata1,userdata2[in]:user data
		// @Return :null
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK* callback_alarm)(responds::s_alarm* para, long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：扩展告警回调函数定义
		// 参数：para[in]:状态数据			_jsonAlarm[in]:报警数据
		//		userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:alarm callback function definition 
		// parameter:para[in]:status data	_jsonAlarm[in]:alarm data
		//			 userdata1,userdata2[in]:user data
		// @Return :null
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK* callback_alarm_extern)(responds::s_status* _status,const char* _jsonAlarm,long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：媒体数据回调函数定义
		// 参数：deviceID[in]:设备编号	sessionID[in]:会话编号
		//		 frame[in]:媒体数据		userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:media data callback function definition
		// parameter:deviceID[in]:device number	sessionID[in]:session number
		//		 frame[in]:media data		userdata1,userdata2[in]:user data
		// @Return :null
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK* callback_media_frame)(const char* deviceID,const char* sessionID,standards::s_frame_data* frame, long long userdata1, long long userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：设备创建新文件回调函数定义
		// 参数： info[in]:信息内容
		//		 userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:device create new file callback function definition
		// parameter: info[in]:infomation content
		//		 userdata1,userdata2[in]:user data
		// @Return :null
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK *callback_device_create_new_file)(responds::s_device_new_file* info, long long userdata1, long long userdata2);

	}
	
	namespace standards
	{
		
		// 工作参数
		// working parameter
		typedef struct s_work									
		{
			//本机构体大小
			//this structure size
			int				size;
			//注册端口
			//register port
			int				register_port;

			//接收超时时间（默认为60秒）
			//receive timeout (default time is 60second)
			int				recv_timeout;

			//设备会话应答回调参数
			//device session respond callback parameter 
			functions::callback_session_answer	session_answer_func;
			long long		session_answer_userdata1;
			long long		session_answer_userdata2;

			//设备注册回调参数
			//device register callback parameter
			functions::callback_device_register	device_register_func;
			long long		device_register_userdata1;
			long long		device_register_userdata2;

			//媒体注册回调参数
			//media register callback parameter
			functions::callback_media_register	media_register_func;
			long long		media_register_userdata1;
			long long		media_register_userdata2;

			//订阅的状态数据内容,按位
			//the suscribed status data content, bit 
			//bit0--位置信息(0:不订阅，1:订阅)
			//bit1--Gsensor(0:不订阅，1:订阅)
			//bit2--基础状态(0:不订阅，1:订阅)
			//bit3--模块工作状态(0:不订阅，1:订阅)
			//bit4--油耗状态(0:不订阅，1:订阅)
			//bit5--移动网络状态(0:不订阅，1:订阅)
			//bit6--WIFI网络状态(0:不订阅，1:订阅)
			//bit7--硬盘状态(0:不订阅，1:订阅)
			//bit8--告警状态(0:不订阅，1:订阅)
			//bit9--温湿度状态(0:不订阅，1:订阅)
			
			//the suscribed status data content, bit 
			//bit0--location information(0:null subscribe，1:subscribe)
			//bit1--Gsensor(0:null subscribe，1:subscribe)
			//bit2--basic status (0:null subscribe，1:subscribe)
			//bit3--module workign status (0:null subscribe，1:subscribe)
			//bit4--fuel consumption status (0:null subscribe，1:subscribe)
			//bit5--mobile network status(0:null subscribe，1:subscribe)
			//bit6--WIFI network status(0:null subscribe，1:subscribe)
			//bit7--harddisk status(0:null subscribe，1:subscribe)
			//bit8--alarm status(0:null subscribe，1:subscribe)
			//bit9--temperature and humidity status(0:null subscribe，1:subscribe)
			int				auto_subscribe_status_content;

			//状态数据回调参数
			//status data callback paramater
			functions::callback_status	status_func;
			long long		status_userdata1;
			long long		status_userdata2;

			//订阅的报警中关于设备的状态数据内容,按位
			//bit0--位置信息(0:不订阅，1:订阅)
			//bit1--Gsensor(0:不订阅，1:订阅)
			//bit2--基础状态(0:不订阅，1:订阅)
			//bit3--模块工作状态(0:不订阅，1:订阅)
			//bit4--油耗状态(0:不订阅，1:订阅)
			//bit5--移动网络状态(0:不订阅，1:订阅)
			//bit6--WIFI网络状态(0:不订阅，1:订阅)
			//bit7--硬盘状态(0:不订阅，1:订阅)
			//bit8--告警状态(0:不订阅，1:订阅)
			//bit9--温湿度状态(0:不订阅，1:订阅)
			
			//the device status data content in the subscribed alarm,bit
			//bit0--location information (0:null subscribe，1:subscribe)
			//bit1--Gsensor(0:null subscribe，1:subscribe)
			//bit2--basic status(0:null subscribe，1:subscribe)
			//bit3--module working status(0:null subscribe，1:subscribe)
			//bit4--fuel consumption status(0:null subscribe，1:subscribe)
			//bit5--mobile network status(0:null subscribe，1:subscribe)
			//bit6--WIFI network status(0:null subscribe，1:subscribe)
			//bit7--harddisk status(0:null subscribe，1:subscribe)
			//bit8--alarm status (0:null subscribe，1:subscribe)
			//bit9--temperature and humidity status(0:null subscribe，1:subscribe)
			int				auto_subscribe_status_content_include_alarm;

			//告警数据回调参数
			//alarm data callback parameter 
			functions::callback_alarm	alarm_func;
			long long		alarm_userdata1;
			long long		alarm_userdata2;

			functions::callback_alarm_extern		alarm_extern_func;
			long long		alarm_extern_userdata1;
			long long		alarm_extern_userdata2;

			//预览媒体数据回调参数
			//preview media data callback parameter
			functions::callback_media_frame		preview_func;
			long long		preview_userdata1;
			long long		preview_userdata2;

			//语音业务媒体数据回调参数
			//voice bussiness media data callback parameter 
			functions::callback_media_frame		voice_func;	
			long long		voice_userdata1;
			long long		voice_userdata2;

			//录像回放媒体数据回调参数
			//record playback media data callback parameter 
			functions::callback_media_frame		replay_func;
			long long		replay_userdata1;
			long long		replay_userdata2;

			//串口代理数据回调参数
			//serial port proxy data callback parameter
			functions::callback_media_frame		serial_port_func;
			long long		serial_port_userdata1;
			long long		serial_port_userdata2;

			//文件上行到服务器数据回调参数
			//file transfer to server data callback parameter 
			functions::callback_media_frame		file_transfer_to_server_func;
			long long		file_transfer_to_server_userdata1;
			long long		file_transfer_to_server_userdata2;

			//设备创建文件回调参数
			//device create file callback parameter
			functions::callback_device_create_new_file	device_create_new_file_func;
			long long		device_create_new_file_userdata1;
			long long		device_create_new_file_userdata2;
		}s_work;

		//媒体数据发送
		//media data sending 
		typedef struct s_send_media_request
		{
			//设备编号
			//device number 
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define, or create via "howenDriver::api::createSessionId")
			const char* sessionID;

			//媒体数据
			//media data
			s_frame_data	data;
		}s_send_media_request;


		//视频预览
		//video preview
		typedef struct s_video_preview_request
		{
			//设备编号
			//device number 
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define, or create via "howenDriver::api::createSessionId")
			const char* sessionID;

			//通道编号,从1开始
			//channel number,start from 1
			int			channel;

			//码流类型,(参考 howenDriver::enums::e_stream_type)
			//stream type,(refer to "howenDriver::enums::e_stream_type")
			int			stream;	

			//上报服务器地址,如"www.google.com:10056"
			//register server address,e.g "www.google.com:10056"
			const char* serverHost;	
		}s_video_preview_request;

		//抓拍
		//snapshot
		typedef struct s_snapshot_request
		{
			//设备编号
			//device number
			const char*	deviceID;
			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define,or create via "howenDriver::api::createSessionId")
			const char* sessionID;

			//通道列表,从1开始,多个复合,通过;分开,如"1;3;5"表示1,3,5三个通道截图
			//channel list, start from 1, using ";" to seperate channel number if more than 1 channel e.g. "1;3;5" means snapshot for channel 1, channel 3, channel 5 
			const char* channelList;
		}s_snapshot_request;

		//语音
		//voice
		typedef struct s_voice_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number, (user define,or create via "howenDriver::api::createSessionId")
			const char* sessionID;

			//通道编号,从1开始
			//channel number, start from 1
			int			channel;

			//工作模式,(参考 howenDriver::enums::e_voice_mode)
			//working mode, (refer to" howenDriver::enums::e_voice_mode")
			int			mode;

			//上报服务器地址,如"www.google.com:10056"
			//register server address,e.g."www.google.com:10056"
			const char* serverHost;
		}s_voice_request;

		//文件查询
		//file query 
		typedef struct s_file_query_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define,or create via "howenDriver::api::createSessionId")
			const char* sessionID;

			//开始时间
			//start time
			const char* startTime;

			//结束时间
			//stop time
			const char* stopTime;

			//通道列表,从1开始,多个复合,通过;分开,如"1;3;5"表示1,3,5三个通道
			//channel list, start from 1,using ";" to seperate channel number if more than 1 channel e.g. "1;3;5" means channel 1,channel 3,channel 5
			const char* channelList;

			//文件类型,(参考 howenDriver::enums::e_file_type)
			//file type,(refer to" howenDriver::enums::e_file_type")
			int			type;
		}s_file_query_request;

		//录像回放
		//record playback 
		typedef struct s_replay_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define, or create via " howenDriver::api::createSessionId")
			const char* sessionID;

			//开始时间
			//start time
			const char* startTime;

			//结束时间
			//stop time
			const char* stopTime;

			//通道列表,从1开始,多个复合,通过;分开,如"1;3;5"表示1,3,5三个通道
			//channel list, start from 1, using ";" to seperate channel number if more than 1 channel e.g. "1;3;5" means channel 1,channel 3,channel 5
			const char* channelList;

			//上报服务器地址,如"www.google.com:10056"
			//register server address,e.g."www.google.com:10056"
			const char* serverHost;
		}s_replay_request;

		//录像控制
		//record control
		typedef struct s_replay_control
		{
			typedef union para
			{
				//跳转时间,如"2017-03-02 12:35:41",(动作为e_replay_action_goto有效)
				//jump time, e.g. "2017-03-02 12:35:41",(action is "e_replay_action_goto" valid)
				char	offset[constants::max_time];
			}para;

			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number, (user define, or create via" howenDriver::api::createSessionId")
			const char* sessionID;

			//保留
			//reserved
			int			action;

			//负载
			//payload
			para		payload;
		}s_replay_control;

		//串口代理
		//serial port proxy 
		typedef struct s_serialport_proxy_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number, (user define, or create via" howenDriver::api::createSessionId")
			const char* sessionID;

			//串口编号,从1开始
			//serial port number, start from 1
			int			channel;

			//停止位,0 -- 1;  1--1.5 ;  2--2 
			//stop bit,0 -- 1;  1--1.5 ;  2--2 
			int			stopBit;

			//校验位,0--无 1--奇  2--偶  3--标志  4--空格
			//parity bit,0--null 1--Odd  2--Even  3--sign  4--space
			int			checkBit;

			//数据位,4~8
			//data bit,4~8
			int			dataBit;

			//波特率
			//buadrate
			int			buadRate;

			//上报服务器地址,如"www.google.com:10056"
			//register server address,e.g."www.google.com:10056"
			const char* serverHost;
		}s_serialport_proxy_request;

		//直接传输文件
		//transfer file directly 
		typedef struct s_transfer_file_via_direct_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define,or create via" howenDriver::api::createSessionId")
			const char* sessionID;

			//业务类型,参考 howenDriver::enums::e_file_transfer_action
			//bussiness type, refer to" howenDriver::enums::e_file_transfer_action"
			int			action;

			//文件大小
			//file size
			int			fileSize;

			//相对文件的偏移地址
			//relative file offset address
			int			offset;
			
			//文件类型,参考 howenDriver::enums::e_file_type
			//file type,reference:howenDriver::enums::e_file_type
			int			fileType;

			//文件名,为空,则设备自行控制
			//file name, if file name is empty, device will auto control by itself 
			const char* fileName;

			//上报服务器地址,如"www.google.com:10056"
			//register server address,e.g."www.google.com:10056"
			const char* serverHost;
		}s_transfer_file_via_direct_request;

		//通过ftp传输文件给设备
		//transfer file to device via ftp
		typedef struct s_transfer_file_via_ftp_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number,(user define,or create via " howenDriver::api::createSessionId")
			const char* sessionID;

			//ftp信息,规则为ftp://用户名:密码@服务器:端口
			//ftp information,rule is ftp://username:password@server:port
			const char*	ftp;

			//动作类型,(参考 howenDriver::enums::e_ftp_action)
			//action type, (refer to" howenDriver::enums::e_ftp_action")
			int			action;

			//文件类型,参考 howenDriver::enums::e_file_type
			//file type,refer to "howenDriver::enums::e_file_type"
			int			fileType;

			//版本号(比如需要升级的版本信息),不需要时候设置为空
			//version (for example the version information which needs to be upgraded),can be empty if no need 
			const char*	version;

			//文件名,不需要时候设置为空
			//file name,can be empty if no need
			const char*	fileName;
		}s_transfer_file_via_ftp_request;

		//直接传输配置参数设备
		//transfer device setting parameter direclty 
		typedef struct s_device_setting_via_direct_request
		{
			//设备编号
			//device number
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number, (user define, or create via " howenDriver::api::createSessionId")
			const char* sessionID;

			//配置参数,json格式
			//setting parameter,json format
			const char*	jsonSetting;
		}s_device_setting_via_direct_request;

		//设备控制
		//device control
		typedef struct s_device_control_request
		{
			//云台
			//PTZ
			typedef struct s_ptz
			{
				//动作类型,(参考 howenDriver::enums::e_ptz_action)
				//action type,(refer to" howenDriver::enums::e_ptz_action")
				int		action;

				//通道编号,从1开始
				//channel number, start from 1
				int		channel;

				//x方向速度(1~10)
				//x direction speed(1~10)
				int		xSpeed;

				//y方向速度(1~10)
				//y direction speed(1~10)
				int		ySpeed;

				//预置位(0~255)
				//preset(0~255)
				int		preset;
			}s_ptz;

			//输出
			//output
			typedef struct s_output
			{
				//开启的通道,从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
				//open channel, start from 1,using ";" to seperate channel number if more than 1 channel e.g. "1;2;5" means channel 1,channel 2,channel 5
				const char*	openChannelList;

				//关闭的通道,从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
				//close channel, start from 1,using ";" to seperate channel number if more than 1 channel e.g. "1;2;5" means channel 1,channel 2,channel 5
				const char*	closeChannelList;
			}s_output;

			//重启
			//reboot
			typedef struct s_reboot
			{
				//保留
				//reserved
				int		reserved;
			}s_reboot;

			//升级
			//upgrade
			typedef struct s_upgrade
			{
				s_transfer_file_via_ftp_request	request;
			}s_upgrade;

			//复位参数
			//reset setting
			typedef struct s_resetSetting
			{
				//保留
				//reserved 
				int		reserved;
			}s_resetSetting;

			//同步时间
			//sync time 
			typedef struct s_syncTime
			{
				//具体的时间如”2017-01-01 11:30:58”,则表示设置为这个时间点，为空则设备自动获取定位时间进行同步
				//if user set the exact time to be ”2017-01-01 11:30:58”,that means device time will be this time，if empty, device will gain GPS time and sync the time
				const char*	time;
			}s_syncTime;

			//录像控制
			//record control
			typedef struct s_record
			{
				//开启的通道,从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
				//open channel, start from 1,using ";" to seperate channel number if more than 1 channel e.g. "1;2;5" means channel 1,channel 2,channel 5
				const char*	openChannelList;
				//关闭的通道,从1开始，通过”;”分割，如”1;2;5”，表示1, 2和5三个通道
				//close channel, start from 1,using ";" to seperate channel number if more than 1 channel e.g. "1;2;5" means channel 1,channel 2,channel 5
				const char*	closeChannelList;
			}s_record;

			//清理报警
			//reset alarm
			typedef struct s_resetAlarm
			{
				//保留
				//reserved
				int		reserved;
			}s_resetAlarm;

			//油路,电路
			//fuel-way circuit 
			typedef struct 
			{
				//动作, 0:切断	其他:恢复
				//action , 0:cut	other:recover
				int		action;
			}s_fuel, s_circuit;

			//车门
			//door
			typedef struct s_door
			{
				//动作, 0:打开	其他:关闭
				//action, 0:open	other:close
				int		action;

				//门编号,1--左前门 2--右前门 3--左中门	4--右中门 5--左后门 6--右后门
				//door number,1--left front door, 2--right front door 3--left middle door,	4--right middle door 5--left back door 6--right back door
				int		index;
			}s_door;

			//格式化
			//format disk
			typedef struct s_disk
			{
				//磁盘名字，如"sd1","sd2","hdd1","usb1"等
				//disk name ,such as "sd1","sd2","hdd1","usb1"
				char	diskName[8];	
			}s_disk;

			//负载
			//payload
			typedef union  u_payload
			{
				//云台
				//PTZ
				s_ptz			ptz;

				//输出
				//output
				s_output		output;

				//重启
				//reboot
				s_reboot		reboot;

				//升级
				//upgrade
				s_upgrade		upgrade;

				//恢复出厂设置
				//reset factory default setting
				s_resetSetting	resetSetting;

				//同步时间
				//sync time 
				s_syncTime		time;

				//录像控制
				//record control
				s_record		record;

				//清理告警
				//reset alarm
				s_resetAlarm	resetAlarm;

				//油路控制
				//fuel way control 
				s_fuel			fuel;

				//电路控制
				//circute control 
				s_circuit		circuit;

				//门控制
				//door control 
				s_door			door;

				//格式化
				s_disk			disk;
			}u_payload;

			//设备编号
			//device number 
			const char*	deviceID;

			//会话编号,(用户自定义,或者通过 howenDriver::api::createSessionId生成)
			//session number, (user define,or create via "howenDriver::api::createSessionId")
			const char* sessionID;

			//动作类型,(参考 howenDriver::enums::e_control_device_action)
			//action type,(refer to" howenDriver::enums::e_control_device_action")
			int			action;

			//负载
			//payload
			u_payload	payload;
		}s_device_control_request;
	};
};
#endif

