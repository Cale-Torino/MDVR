
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年04月10日
描述: 枚举定义
历史:
1、2017年04月10日 初步创建
使用说明:
*/

/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.10
Description: Enumeration Definition 
History:
1,20170410: initial establish
instruction:
*/

#ifndef _DeviceDriver_Enum_h_
#define _DeviceDriver_Enum_h_

#pragma once

namespace howenDriver
{
	namespace constants
	{
		const int max_channel	= 16;			//最大通道   //maximum channel 
		const int max_id		= 32;			//最大设备编号长度   //maximum device number length 
		const int max_session	= 128;			//最大会话长度   //maximum session length
		const int max_time		= 24;			//最大时间长度   //maximum time length 
		const int max_ip		= 24;			//最大ip地址长度   //maximum IP address length 
		const int max_ch_list	= 128;			//最大通道列表长度   //maximum channel list length 

		const int max_disk_name = 8;			//最大磁盘名字   //maximum disk name 
		const int max_storage	= 8;			//最大磁盘个数   //maximum disk QTY
		const int max_path		= 256;			//最大路径长度   //maximum path length 

		const int max_server_name = 256;		//最大服务器名称,包含域名端口,账号等信息 maximum server name, include domain name port, account ID etc.
	};

	namespace enums
	{
		//错误码
		//Error Code
		typedef enum e_error_code
		{
			e_error_code_succeed						= 0x0000,				//成功   //success 
			e_error_code_initialize_not_execute			= 0x10001,				//未执行初始化   //No initialization 
			e_error_code_invalid_parameter				= 0x10002,				//无效参数   //invalid parameter 
			e_error_code_invalid_command				= 0x10003,				//无效命令   //invalid command
			e_error_code_invalid_session_id				= 0x10004,				//无效会话编号   //invalid session number 
			e_error_code_storage_not_exist				= 0x10005,				//磁盘不存在   //disk not exist 
			e_error_code_file_not_exist					= 0x10006,				//文件不存在   //file not exist 

			e_error_code_device_offline					= 0x10007,				//设备掉线   //device offline 
			e_error_code_device_busing					= 0x10008,				//设备繁忙   //device busy 
			e_error_code_device_connect_server_failed	= 0x10009,				//设备连接服务器失败   //device fail to connect server 
			e_error_code_data_continue					= 0x1000a,				//后续还有数据(暂时用于文件查询)   //data continue (for file query)
			e_error_code_data_finished					= 0x1000b,				//数据结束(暂时用于文件查询)   //data finished ( for file query )
			e_error_code_device_same_id					= 0x1000c,				//重复设备编号   //device number repeat 
			e_error_code_device_not_exist				= 0x1000d,				//设备不存在   //device not exist 
			e_error_code_device_setting_rule_unconform	= 0x1000e,				//设备参数不符合规则   //device setting unconform the rule 
			e_error_code_buffer_full					= 0x1000f,				//缓冲区满   //buffer is  full
			e_error_code_media_offline					= 0x10010,				//链路掉线	//media link offline

			e_error_code_unsupport						= 0x10FFE,				//不支持   //unsupport 
			e_error_code_unknow							= 0x10FFF,				//未知   //unknow
		}e_error_code;

		//云台动作代码
		//PTZ action code
		typedef enum e_ptz_action
		{
			e_ptz_action_unknow							= 0x00,					//未知   //unknow 
			e_ptz_action_up								= 0x01,					//上   //up 
			e_ptz_action_down							= 0x02,					//下   //down 
			e_ptz_action_left							= 0x03,					//左   //left 
			e_ptz_action_right							= 0x04,					//右   //right 
			e_ptz_action_left_up						= 0x05,					//左上   //left up 
			e_ptz_action_left_down						= 0x06,					//左下   //left down 
			e_ptz_action_right_up						= 0x07,					//右上   //right up 
			e_ptz_action_right_down						= 0x08,					//右下   //right down 
			e_ptz_action_preset_goto					= 0x09,					//预置位跳转   //preset go to 
			e_ptz_action_preset_set						= 0x0a,					//预置位设置   //set preset 
			e_ptz_action_preset_clear					= 0x0b,					//清理预置位   //clear preset 
			e_ptz_action_iris_open						= 0x0c,					//光圈大   //iris open 
			e_ptz_action_iris_close						= 0x0d,					//光圈小   //iris close 
			e_ptz_action_zoom_in						= 0x0e,					//调焦缩小   //zoom in 
			e_ptz_action_zoom_out						= 0x0f,					//调焦放大   //zoom out 
			e_ptz_action_focus_near						= 0x10,					//聚焦近   //focus near 
			e_ptz_action_focus_far						= 0x11,					//聚焦远   //focus far 
			e_ptz_action_auto_scan						= 0x12,					 //自动水平转动   //auto scan 
			e_ptz_action_brush_on						= 0x13,					//雨刮启动   //brush/ wiper on 
			e_ptz_action_brush_off						= 0x14,					//雨刮关闭   //brush / wiper off 
			e_ptz_action_cruise_open					= 0x15,					//巡航启动   //cruise/ tour open 
			e_ptz_action_cruise_close					= 0x16,					//巡航关闭   //cruise/ tour close
			e_ptz_action_Light_on						= 0x17,					//灯光打开   //light open
			e_ptz_action_light_off						= 0x18,					//灯光关闭   //light off  
		}e_ptz_action;

		//数据链路类型
		typedef enum e_data_link_control
		{
			e_data_link_control_unkonw					= 0x00,					//未知   //unknow 
			e_data_link_control_signal					= 0x01,					//信令   //control signal 

			e_data_link_control_preview					= 0x11,					//预览   //preview 
			e_data_link_control_replay					= 0x12,					//录像回放   //record playback 
			e_data_link_control_voice					= 0x13,					//语音   //voice 
			e_data_link_control_file_transfer			= 0x14,					//文件代理   //file transfer 
			e_data_link_control_serialport_proxy		= 0x15,					//串口代理   //serial port proxy 
		}e_data_link_control;

		//网络接入类型
		typedef enum e_access_net
		{
			e_access_net_unknow							= 0x00,					//未知   //unknow 
			e_access_net_cable							= 0x01,					//有线   //cable 
			e_access_net_wifi							= 0x02,					//wifi   //WIFI
			e_access_net_2G								= 0x03,					//2G     //2G
			e_access_net_3G								= 0x04,					//3G     //3G
			e_access_net_4G								= 0x05,					//4G     //4G
			e_access_net_5G								= 0x06,					//5G     //5G
		}e_access_net;

		//数据帧类型
		//data frame type 
		typedef enum e_frame_type
		{
			e_frame_type_invalid						= 0x00,					//无效   //invalid 
			e_frame_type_video_i						= 0x01,					//视频I帧   //video i frame 
			e_frame_type_video_p						= 0x02,					//视频P帧   //video P frame 
			e_frame_type_audio							= 0x03,					//音频帧   //audio frame 
			e_frame_type_serial_port					= 0x04,					//串口数据帧   //serial port frame 
			e_frame_type_file_data						= 0x05,					//文件数据帧   //file data frame 
		}e_frame_type;

		//定位模式
		//location mode 
		typedef enum e_location_mode
		{
			e_location_mode_invalid						= 0x00,					//无效   //invalid 
			e_location_mode_gps							= 0x01,					//GPS     //GPS
			e_location_mode_beidou						= 0x02,					//北斗   //BDS  
			e_location_mode_glonass						= 0x03,					//伽利略   //Glonass 
			e_location_mode_agps						= 0x04,					//辅助GPS   //assist GPS
			e_location_mode_base_station				= 0x05,					//基站   //base station
			e_location_mode_base_wifi					= 0x05,					//wifi     //WIFI 
		}e_location_mode;

		typedef enum e_alarm_type					//告警类型   //alarm type
		{
			e_alarm_type_unknow							= 0x00,					//未知   //unknow 
			e_alarm_type_video_lost						= 0x01,					//视频丢失   //video lost
			e_alarm_type_motion_detection				= 0x02,					//移动侦测   //motion detection
			e_alarm_type_video_mask						= 0x03,					//视频遮挡   //video blind 
			e_alarm_type_input_generate					= 0x04,					//输入触发   //input trigger 
			e_alarm_type_urgency						= 0x05,					//紧急告警   //emmergency alarm 
			e_alarm_type_low_speed						= 0x06,					//低速告警   //low speed alarm 
			e_alarm_type_over_speed						= 0x07,					//超速告警   //overspeed alarm 
			e_alarm_type_low_temperature				= 0x08,					//低温告警   //low temperature alarm 
			e_alarm_type_over_temperature				= 0x09,					//高温告警   //high temperature alarm  
			e_alarm_type_humidity						= 0x0a,					//湿度告警   //humidity alarm 
			e_alarm_type_park_timeout					= 0x0b,					//超时停车   //park timeout alarm 
			e_alarm_type_shake							= 0x0c,					//震动告警   //vibration alarm 
			e_alarm_type_e_defence						= 0x0d,					//电子围栏   //electronic defence 
			e_alarm_type_e_line							= 0x0e,					//电子线路   //electronic line 
			e_alarm_type_door_exception					= 0x0f,					//异常开关门   //door open/ close exception 
			e_alarm_type_storage_exception				= 0x10,					//存储介质异常   //storage exception 
			e_alarm_type_fatigue_driving				= 0x11,					//疲劳驾驶   //fatigue driving 
			e_alarm_type_fuel_exception					= 0x12,					//油量异常   //fuel exception 
			e_alarm_type_illegal_fire					= 0x13,					//非法点火   //illegal ACC 
			e_alarm_type_location_module_exception		= 0x14,					//定位模块异常   //location module exception 
			e_alarm_type_front_panel_prise				= 0x15,					//前面板打开   //front panel prise 
		}e_alarm_type;

		//音频模式 voice/ audio mode 
		typedef enum e_voice_mode
		{
			e_voice_mode_listen							= 0x00,					//监听   //listen 
			e_voice_mode_talk							= 0x01,					//对讲   //talk 
			e_voice_mode_broadcast						= 0x02,					//广播   //broadcast 
			e_voice_mode_ptt							= 0x03,					//PTT   //PTT 
		}e_voice_mode;

		//码流类型  
		//stream type
		typedef enum e_stream_type
		{
			e_stream_type_substream						= 0x00,					//子码流   //substream 
			e_stream_type_mainstream					= 0x01,					//主码流   //main stream 
		}e_stream_type;

		typedef enum e_file_type				//文件类型   //file type
		{
			e_file_type_normal_record					= 0x01,					//普通录像   //normal record 
			e_file_type_alarm_record					= 0x02,					//报警录像   //alarm record 
			e_file_type_normal_snapshot					= 0x03,					//普通抓拍文件   //normal snapshot file 
			e_file_type_alarm_snapshot					= 0x04,					//报警抓拍文件   //alarm snapshot file 
			e_file_type_upgrade							= 0x05,					//升级文件   //upgrade file 
			e_file_type_log								= 0x06,					//日志文件   //log file 
			e_file_type_setting							= 0x07,					//配置文件   //setting file 

			e_file_type_invalid							= 0xff,					//无效   //invalid 
		}e_file_type;

		//ftp相关业务操作类型 
		//ftp relative bussiness action type  
		typedef enum e_ftp_action
		{
			e_ftp_action_upload_to_server				= 0x00,					//上传到服务器   //upload to server 
			e_ftp_action_download_from_server			= 0x01,					//上行到服务器   //download from server 
		}e_ftp_action;

		//传输文件业务类型
		//transfer file bussiness type 
		typedef enum e_file_transfer_action
		{
			e_file_transfer_action_to_server			= 0x00,					//发送到服务器  //transfer file to server 
			e_file_transfer_action_to_device			= 0x01,					//发送到设备   //transfer file to device 
		}e_file_transfer_action;

		//设备控制类型
		//device control type 
		typedef enum e_control_device_action
		{
			e_control_device_action_unknow				= 0x00,					//未知   //unknow 
			e_control_device_action_ptz					= 0x01,					//云台   //PTZ 
			e_control_device_action_reboot				= 0x02,					//重启   //reboot 
			e_control_device_action_upgrade				= 0x03,					//升级   //upgrade 
			e_control_device_action_reset_setting		= 0x04,					//恢复出厂设置   //reset factory default setting 
			e_control_device_action_sync_time			= 0x05,					//同步时间   //sync time 
			e_control_device_action_record				= 0x06,					//录像控制   //record control 
			e_control_device_action_reset_alarm			= 0x07,					//清理告警   //clear alarm 
			e_control_device_action_oil_control			= 0x08,					//油路控制   //fuel way control 
			e_control_device_action_circuit_control		= 0x09,					//电路控制   //circuit control 
			e_control_device_action_door_control		= 0x0a,					//门控制   //door control 
			e_control_device_action_format_disk			= 0x0b,					//格式化磁盘   //format disk 
		}e_control_device_action;

		//业务类型
		//bussiness type 
		typedef enum e_business_type
		{
			e_business_type_unknow						= 0x00,					//未知   //unknow 
			e_business_type_preview						= 0x01,					//预览   //preview 
			e_business_type_snapshot					= 0x02,					//抓拍   //snapshot 
			e_business_type_voice						= 0x03,					//语音   //voice 
			e_business_type_file_query					= 0x04,					//文件查询   //file query 
			e_business_type_replay						= 0x05,					//回放   //playback 
			e_business_type_serialport_proxy			= 0x06,					//串口代理   //serial port proxy 
			e_business_type_file_transfer_via_direct	= 0x07,					//直接传输文件  // transfer file directly 
			e_business_type_file_transfer_via_ftp		= 0x08,					//ftp模式传输文件  // transfer file via ftp 
			e_business_type_setting_to_device_via_direct= 0x09,					//直接设置设备参数   //device setting directly 
			e_business_type_device_control				 = 0x0A,				//设备控制   //device control 
		}e_business_type;
	};
};
#endif

