/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: george wan
日期: 2017年03月21日
描述: 设备网络通讯库 枚举和常量定义
历史:
1、2017年03月21日 初步创建
使用说明:
*/

#ifndef _HDNetwork_Enums_h_
#define _HDNetwork_Enums_h_

#pragma once

namespace HowenDeviceNetwork
{
	namespace constants
	{
		static const int			max_channel = 16;						//最多通道数目		//max channel of one device

		//static const int setting_number = 23;	//可配置参数总量
		//具体参数名称
		static const char*	setting_name[] = { 
			"clock", "dialup", "diskabnormalalm", "display", "gsensor", \
			"ioset", "jtbase", "local","motiondetect", "osd", \
			"power", "ptz", "record", "rsbase", "server", \
			"speed", "store", "temp", "upgrade", "videolostalm", \
			"videoout", "voltage", "wifi", "ttx", "dst" ,"version"};
	};

	namespace enums
	{
		//错误码定义
		typedef enum e_error_code
		{
			e_error_code_succeed				= 0,		//成功				//succeed
			e_error_code_repeat_ID				= 1,		//重复ID				//the same id exist
			e_error_code_invalid_parameter		= 2,		//无效参数			//
			e_error_code_invalid_command		= 3,		//无效命令			//
			e_error_code_device_busing			= 4,		//设备繁忙			//
			e_error_code_connect_failed			= 5,		//连接建立失败
			e_error_code_file_not_found			= 6,		//相关文件不存在
			e_error_code_disk_not_exist			= 7,		//磁盘不存在
			e_error_code_exist_data_later		= 8,		//后续还有数据
			e_error_code_file_query_finished	= 9,		//文件查询结束

			e_error_code_unknow					= 0xFF,		//未知错误
		}e_error_code;

		typedef enum e_alarm_type					//告警类型   //alarm type
		{
			e_alarm_type_unknow					= 0x00,		//未知   //unknow 
			e_alarm_type_video_lost				= 0x01,		//视频丢失   //video lost
			e_alarm_type_motion_detection		= 0x02,		//移动侦测   //motion detection
			e_alarm_type_video_mask				= 0x03,		//视频遮挡   //video blind 
			e_alarm_type_input_generate			= 0x04,		//输入触发   //input trigger 
			e_alarm_type_urgency				= 0x05,		//紧急告警   //emmergency alarm 

			e_alarm_type_low_speed				= 0x06,		//低速告警   //low speed alarm 
			e_alarm_type_over_speed				= 0x07,		//超速告警   //overspeed alarm 
			e_alarm_type_low_temperature		= 0x08,		//低温告警   //low temperature alarm 
			e_alarm_type_over_temperature		= 0x09,		//高温告警   //high temperature alarm  

			e_alarm_type_humidity				= 0x0a,		//湿度告警   //humidity alarm 

			e_alarm_type_park_timeout			= 0x0b,		//超时停车   //park timeout alarm 
			e_alarm_type_shake					= 0x0c,		//震动告警   //vibration alarm 

			e_alarm_type_e_defence				= 0x0d,		//电子围栏   //electronic defence 
			e_alarm_type_e_line					= 0x0e,		//电子线路   //electronic line 

			e_alarm_type_door_exception			= 0x0f,		//异常开关门   //door open/ close exception 
			e_alarm_type_storage_exception		= 0x10,		//存储介质异常   //storage exception 
			e_alarm_type_fatigue_driving		= 0x11,		//疲劳驾驶   //fatigue driving 
			e_alarm_type_fuel_exception			= 0x12,		//油量异常   //fuel exception 

			e_alarm_type_illegal_fire			= 0x13,		//非法点火   //illegal ACC 
			e_alarm_type_location_module_exception = 0x14,	//定位模块异常   //location module exception 
			e_alarm_type_front_panel_prise		= 0x15,		//前面板打开   //front panel prise 
		}e_alarm_type;

		//设备类型		//device' type
		typedef enum e_device_type
		{
			e_device_type_4_base				= 0x4000,	//4路机
			e_device_type_8_base				= 0x8000,	//8路机
		}e_device_type;

		//网络接入类型
		typedef enum e_access_net
		{
			e_access_net_unknow					= 0x00,		//未知   //unknow 
			e_access_net_cable					= 0x01,		//有线   //cable 
			e_access_net_wifi					= 0x02,		//wifi   //WIFI
			e_access_net_2G						= 0x03,		//2G     //2G
			e_access_net_3G						= 0x04,		//3G     //3G
			e_access_net_4G						= 0x05,		//4G     //4G
			e_access_net_5G						= 0x06,		//5G     //5G
		}e_access_net;

		//数据帧类型
		//data frame type 
		typedef enum e_frame_type
		{
			e_frame_type_invalid				= 0x00,		//无效			//invalid 
			e_frame_type_video_i				= 0x01,		//视频I帧		//video i frame 
			e_frame_type_video_p				= 0x02,		//视频P帧		//video P frame 
			e_frame_type_audio					= 0x03,		//音频帧			//audio frame 
			e_frame_type_serial_port			= 0x04,		//串口数据帧		//serial port frame 
			e_frame_type_file_data				= 0x05,		//文件数据帧		//file data frame 
			e_frame_type_status_data			= 0x06,		//状态数据帧		//status data frame 
			e_frame_type_alarm_data				= 0x07,		//告警数据帧		//alarm data frame 
		}e_frame_type;

		//定位模式
		//location mode 
		typedef enum e_location_mode
		{
			e_location_mode_invalid				= 0x00,		//无效		//invalid 
			e_location_mode_gps					= 0x01,		//GPS		//GPS
			e_location_mode_beidou				= 0x02,		//北斗		//BDS  
			e_location_mode_glonass				= 0x03,		//伽利略		//Glonass 
			e_location_mode_agps				= 0x04,		//辅助GPS   //assist GPS
			e_location_mode_base_station		= 0x05,		//基站		//base station
			e_location_mode_base_wifi			= 0x05,		//wifi		//WIFI 
		}e_location_mode;

		//码流类型定义
		//stream index
		typedef enum e_video_stream_index
		{
			e_video_stream_index_subtype		= 0,		//子码流		//sub stream
			e_video_stream_index_major			= 1,		//主码流		//major stream
		}e_video_stream_index;

		//模块工作状态
		//module work status
		typedef enum e_module_work_status
		{
			e_module_work_status_unknow			= 0,		//未知		//unknow
			e_module_work_status_working		= 1,		//工作中		//be working
			e_module_work_status_exception		= 2,		//异常		//exception
			e_module_work_status_not_exist		= 3,		//不存在		//not exist
		}e_module_work_status;

		//磁盘工作状态
		//disk work status
		typedef enum e_disk_work_status
		{
			e_disk_work_status_unkonw			= 0,		//未知		//unknow
			e_disk_work_status_recording		= 1,		//录像中		//be recording
			e_disk_work_status_idle				= 2,		//空闲		//idle
			e_disk_work_status_exception		= 3,		//异常		//exception
			e_disk_work_status_full				= 4,		//磁盘满		//full
		}e_disk_work_status;

		//gsensor 类型		//gesensor's type
		typedef enum e_gsensor_type
		{
			e_gsensor_type_unknow				= 0,		//未知		//unknow
			e_gsensor_type_x					= 1,
			e_gsensor_type_y					= 2,
			e_gsensor_type_z					= 3,
			e_gsensor_type_hit					= 4,
			e_gsensor_type_tilt					= 5,
		}e_gsensor_type;

		//防区或线路，进出状态		//get in or get out about fence or line
		typedef enum e_get_inout_status
		{
			e_get_inout_status_in				= 0,		//进入		//get in
			e_get_inout_status_out				= 1,		//离开		//get out
		}e_get_inout_status;

		//门开关状态		//door status
		typedef enum e_door_status
		{
			e_door_status_close					= 0,		//关闭		//close
			e_door_status_open					= 1,		//打开		//open
		}e_door_status;

		//门位置		//position of door
		typedef enum e_door_position
		{
			e_door_position_unknow				= 0,		//未知		//unknow
			e_door_position_left_front			= 1,
			e_door_position_right_front			= 2,
			e_door_position_left_middle			= 3,
			e_door_position_right_middle		= 4,
			e_door_position_left_back			= 5,
			e_door_position_right_back			= 6,
		}e_door_position;


		//磁盘异常原因状态
		//disk exception reason
		typedef enum e_disk_exception_reason
		{
			e_disk_exception_reason_lost		= 0,		//丢失		//lost
			e_disk_exception_reason_demage		= 1,		//损坏		//demage
			e_disk_exception_reason_not_override =2,		//无法覆盖	//can't override
		}e_disk_exception_reason;

		typedef enum e_file_type				//文件类型   //file type
		{
			e_file_type_normal_record			= 0x01,		//普通录像		 //normal record 
			e_file_type_alarm_record			= 0x02,		//报警录像		 //alarm record 
			e_file_type_normal_snapshot			= 0x03,		//普通抓拍文件	 //normal snapshot file 
			e_file_type_alarm_snapshot			= 0x04,		//报警抓拍文件	 //alarm snapshot file 
			e_file_type_upgrade					= 0x05,		//升级文件		 //upgrade file 
			e_file_type_log						= 0x06,		//日志文件		 //log file 
			e_file_type_setting					= 0x07,		//配置文件		 //setting file 

			e_file_type_invalid					= 0xff,		//无效			 //invalid 
		}e_file_type;

		//音频模式
		//voice/ audio mode 
		typedef enum e_voice_mode
		{
			e_voice_mode_listen					= 0x00,		//监听   //listen 
			e_voice_mode_talk					= 0x01,		//对讲   //talk 
			e_voice_mode_broadcast				= 0x02,		//广播   //broadcast 
			e_voice_mode_ptt					= 0x03,		//PTT   //PTT 
		}e_voice_mode;

		//文件传输模式		//file transfer mode
		typedef enum e_file_transfer_mode
		{
			e_file_transfer_mode_download_from_device	= 0x00,//从设备下载	//download from device
			e_file_transfer_mode_upload_to_device		= 0x01,//上传到设备  //upload to device
		}e_file_transfer_mode;

		//ftp动作类型		//ftp action 
		typedef enum e_ftp_action
		{
			e_ftp_action_upload_to_server		= 0x00,		//上传文件到服务器	//upload file to server
			e_ftp_action_download_from_server	= 0x01,		//从服务器下载文件	//download file from server
		}e_ftp_action;

		//云台动作代码
		//PTZ action code
		typedef enum e_ptz_action
		{
			e_ptz_action_unknow					= 0x00,		//未知   //unknow 
			e_ptz_action_up						= 0x01,		//上   //up 
			e_ptz_action_down					= 0x02,		//下   //down 
			e_ptz_action_left					= 0x03,		//左   //left 
			e_ptz_action_right					= 0x04,		//右   //right 
			e_ptz_action_left_up				= 0x05,		//左上   //left up 
			e_ptz_action_left_down				= 0x06,		//左下   //left down 
			e_ptz_action_right_up				= 0x07,		//右上   //right up 
			e_ptz_action_right_down				= 0x08,		//右下   //right down 
			e_ptz_action_preset_goto			= 0x09,		//预置位跳转   //preset go to 
			e_ptz_action_preset_set				= 0x0a,		//预置位设置   //set preset 
			e_ptz_action_preset_clear			= 0x0b,		//清理预置位   //clear preset 
			e_ptz_action_iris_open				= 0x0c,		//光圈大   //iris open 
			e_ptz_action_iris_close				= 0x0d,		//光圈小   //iris close 
			e_ptz_action_zoom_in				= 0x0e,		//调焦缩小   //zoom in 
			e_ptz_action_zoom_out				= 0x0f,		//调焦放大   //zoom out 
			e_ptz_action_focus_near				= 0x10,		//聚焦近   //focus near 
			e_ptz_action_focus_far				= 0x11,		//聚焦远   //focus far 
			e_ptz_action_auto_scan				= 0x12,		//自动水平转动   //auto scan 
			e_ptz_action_brush_on				= 0x13,		//雨刮启动   //brush/ wiper on 
			e_ptz_action_brush_off				= 0x14,		//雨刮关闭   //brush / wiper off 
			e_ptz_action_cruise_open			= 0x15,		//巡航启动   //cruise/ tour open 
			e_ptz_action_cruise_close			= 0x16,		//巡航关闭   //cruise/ tour close
			e_ptz_action_Light_on				= 0x17,		//灯光打开   //light open
			e_ptz_action_light_off				= 0x18,		//灯光关闭   //light off  
		}e_ptz_action;

		//车辆控制代码		//Vehicle control operations
		typedef enum e_vehicle_action
		{
			e_vehicle_action_unknow				= 0x00,		//未知		//unknow
			e_vehicle_action_oil_off			= 0x01,		//切断油路	//cut oil off
			e_vehicle_action_oil_on				= 0x02,		//恢复油路	//restore oil
			e_vehicle_action_circuit_off		= 0x03,		//切断电路	//cut off circuit
			e_vehicle_action_circuit_on			= 0x04,		//恢复电路	//restore circuit
			e_vehicle_action_door_open			= 0x05,		//打开车门	//open door
			e_vehicle_action_door_close			= 0x06,		//关闭车门	//close door
		}e_vehicle_action;

		//串口停止位		//stop bit of serial port
		typedef enum e_seiral_port_stop_bit
		{
			e_seiral_port_stop_bit_one			= 0x00,		//1
			e_seiral_port_stop_bit_one_half		= 0x01,		//1.5
			e_seiral_port_stop_bit_two			= 0x02,		//2
		}e_seiral_port_stop_bit;

		//串口校验位		//check bit of serial port
		typedef enum e_seiral_port_check_bit
		{
			e_seiral_port_check_bit_null		= 0x00,		//无
			e_seiral_port_check_bit_odd			= 0x01,		//奇校验位
			e_seiral_port_check_bit_even		= 0x02,		//偶校验位
			e_seiral_port_check_bit_flag		= 0x03,		//标识校验位
			e_seiral_port_check_bit_space		= 0x04,		//空格校验位
		}e_seiral_port_check_bit;
	};
};

#endif

