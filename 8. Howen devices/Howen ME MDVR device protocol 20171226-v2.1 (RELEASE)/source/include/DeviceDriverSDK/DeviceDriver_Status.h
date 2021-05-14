
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月10日
描述: 状态定义
历史:
1、2017年04月10日 初步创建
使用说明:
*/

/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.10
Description: status Definition 
History:
1,20170410: initial establish
instruction:
*/


#ifndef _DeviceDriver_Status_h_
#define _DeviceDriver_Status_h_

#pragma once

#include "DeviceDriver_Enum.h"

namespace howenDriver
{
	namespace status
	{
		//位置信息
		//status information 
		typedef struct s_location
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//定位类型,参考howenDriver::enums::e_location_mode
			//location type, refer to "howenDriver::enums::e_location_mode"
			int				mode;

			//采集时间
			//maximum time 
			char			dtu[constants::max_time];

			//方向,0~359°
			//direction, 0~359°
			int				direct;

			//卫星数量
			//satellites QTY 
			int				satellites;

			//速度,(KM/H)
			//speed, (KM/H)
			float			speed;

			//海拔高度(米)
			//altitude (meter)
			int				altitude;

			//定位精度(米)
			//location acuracy (meter)
			int				precision;

			//经度
			//longitude
			float			longitude;

			//纬度
			//latitude
			float			latitude;
		}s_location;

		//gsensor
		typedef struct s_gsensor
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//x方向,(-16.00~+16.00,>=1000为无效)
			//x direction,(-16.00~+16.00,>=1000 is invalid)
			float			x;

			//y方向,(-16.00~+16.00,>=1000为无效)
			//y direction,(-16.00~+16.00,>=1000 is invalid)
			float			y;

			//z方向,(-16.00~+16.00,>=1000为无效)
			//z direction,(-16.00~+16.00,>=1000 is invalid)
			float			z;

			//倾斜方向,(-16.00~+16.00,>=1000为无效)
			//tile direction,(-16.00~+16.00,>=1000 is invalid )
			float			tilt;

			//撞击方向,(-16.00~+16.00,>=1000为无效)
			//impact direction,(-16.00~+16.00,>=1000 is invalid)
			float			hit;

			//保留
			//reserved
			char			reserved[4];
		}s_gsensor;

		//车辆基本状态
		//vehicle basic status 
		typedef struct s_base_vehi
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//钥匙, (0:未知或无效,1:有效)
			//key, (0:unknow invalid,1:valid)
			char			key;

			//刹车, (0:未知或无效,1:有效)
			//brake, (0:unknow or invalid,1:valid)
			char			brake;

			//左转, (0:未知或无效,1:有效)
			//turn left, (0:unknow or invalid,1:valid)
			char			left;

			//右转, (0:未知或无效,1:有效)
			//turn right, (0:unknow or invalid,1:valid)
			char			right;

			//前进, (0:未知或无效,1:有效)
			//forward, (0:unknow or invalid,1:valid)
			char			forword;

			//后退, (0:未知或无效,1:有效)
			//backword, (0:unknow or invalid,1:valid)
			char			backword;

			//左前门, (0:未知或无效,1:有效)
			//left front door, (0:unknow or invalid,1:valid)
			char			door_left_front;

			//右前门, (0:未知或无效,1:有效)
			//right front door, (0:unknow or invalid,1:valid)
			char			door_right_front;

			//左中门, (0:未知或无效,1:有效)
			//left middle door, (0:unknow or invalid,1:valid)
			char			door_left_middle;

			//右中门, (0:未知或无效,1:有效)
			//right middle door, (0:unknow or invalid,1:valid)
			char			door_right_middle;

			//左后门, (0:未知或无效,1:有效)
			//left back door, (0:unknow or invalid,1:valid)
			char			door_left_back;

			//右后门, (0:未知或无效,1:有效)
			//right back door, (0:unknow or invalid,1:valid)
			char			door_right_back;
		}s_base_vehi;

		//模块状态
		//module status 
		typedef struct s_module
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//移动网络模块状态, (0:未知,1:工作中,2:异常,3:不存在)
			//mobile network module status, (0:unknow,1:working,2:abnormal,3:not exist)
			char			mobileNetwork;

			//定位模块状态, (0:未知,1:工作中,2:异常,3:不存在)
			//location module status, (0:unknow,1:working,2:abnormal,3:not exist)
			char			location;

			//wif网络模块状态, (0:未知,1:工作中,2:异常,3:不存在)
			//wif network module status, (0:unknow,1:working,2:abnormal,3:not exist)
			char			wifiNetwork;

			//gsensor模块状态, (0:未知,1:工作中,2:异常,3:不存在)
			//gsensor module status, (0:unknow,1:working,2:abnormal,3:not exist)
			char			gsensor;

			//通道录像状态,bit0对应第一路视频,以此类推
			//channel record status,bit0 is corresponding to channel 1 video, and so on 
			int				record;

		}s_module;

		//油耗状态
		//fuel consumption status 
		typedef struct s_feul
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//油耗(>=1000为无效)
			//fuel consumption(>=1000 is invalid)
			float			cost;

			//剩余油量(<0为无效)
			//free fuel (<0 is invalid )
			float			free;
		}s_feul;

		//移动网络状态
		//mobile network status 
		typedef struct s_mobile
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//信号强度(>=1000为无效)
			//signal strength (>=1000 is invalid)
			int				strength;

			//网络类型(参考 howenDriver::enums::e_access_net)
			//network type (refer to " howenDriver::enums::e_access_net")
			int				type;
		}s_mobile;

		//wifi网络状态
		//wifi network status
		typedef struct s_wifi
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//信号强度(>=1000为无效)
			//signal strength(>=1000 is invalid)
			int				strength;

			//ip地址
			//ip address 
			char			ip[constants::max_ip];

			//子网掩码
			//subnet mask
			char			mask[constants::max_ip];

			//网关
			//gateway 
			char			gateway[constants::max_ip];

			//ssid
			//SSID
			char			ssid[constants::max_session];
		}s_wifi;

		//磁盘项
		//storage item 
		typedef struct s_storage_item
		{
			//编号
			//index 
			int				index;

			//磁盘状态,0:未知, 1:录像中,  2:空闲,  3:异常,  4:磁盘满
			//storage status,0:unknow, 1:recording,  2:free,  3:abnormal,  4:full
			int				status;

			//总量,(MB)
			//total,(MB)
			int				total;

			//剩余,(MB)
			//free,(MB)
			int				free;
		}s_storage_item;

		typedef struct s_storage
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//状态
			//status 
			s_storage_item	storage[constants::max_storage];
		}s_storage;

		//告警状态
		//alarm status 
		typedef struct s_alarm
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//视频丢失状态,bit0对应第一路视频,以此类推
			//video lost status,bit0 is corresponding to channel 1 video, and so on 
			int				videoLost;

			//移动侦测状态,bit0对应第一路视频,以此类推
			//motion detection status,bit0 is corresponding to channel 1 video, and so on
			int				motionDection;

			//视频遮挡状态,bit0对应第一路视频,以此类推
			//video blind status, bit0 is corresponding to channel 1 video, and so on 
			int				videoMask;

			//输入口状态,bit0对应第一个io口,以此类推
			//input status, bit0 is corresponding to first IO port, and so on
			int				input;

			//超速告警(0:未触发，1:触发)
			//overspeed alarm (0:not trigger，1:trigger)
			char			overSpeed;

			//低速告警(0:未触发，1:触发)
			//low speed alarm(0:not trigger，1:trigger)
			char			lowSpeed;

			//紧急告警(0:未触发，1:触发)
			//emergency alarm (0:not trigger，1:trigger)
			char			urgency;

			//保留
		    //reserved
			char			reserved[9];
		}s_alarm;

		//温湿度
		//temperature and humidity 
		typedef struct s_temp_humidity
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int				size;

			//车内温度,(>=1000:无效)
			//in vehicle temperature,(>=1000:invalid )
			float			insideTemp;

			//车外温度,(>=1000:无效)
			//outside vehicle temperature,(>=1000:invalid)
			float			outsideTemp;

			//发动机温度,(>=1000:无效)
			//motor temperature,(>=1000:invalid)
			float			engineerTemp;

			//设备温度,(>=1000:无效)
			//device temperature,(>=1000:invalid)
			float			deviceTemp;

			//车内湿度,百分比,(>=1000:无效)
			//in vehicle humidity,percentage,(>=1000:invalid)
			float			insideHumidity;

			//车外湿度,百分比,(>=1000:无效)
			//outside vehicle humidity，percentage,(>=1000:invalid)
			float			outsidHumidity;
		}s_temp_humidity;

		//统计信息		//statistics data
		typedef struct statistics
		{
			unsigned int		uiTotalMileage;			//总里程，米						//total mileage,meter
			unsigned int		uiCurrentDayMileage;	//当天里程，米					//current day mileage,meter
		}statistics;

		//信息汇总
		//information summary
		typedef struct s_all
		{
			//设备时间
			//device time
			char				dtu[constants::max_time];

			s_location			location;
			s_gsensor			gsensor;
			s_base_vehi			base_vehi;
			s_module			module;
			s_feul				feul;
			s_mobile			mobile;
			s_wifi				wifi;
			s_storage			storage;
			s_alarm				alarm;
			s_temp_humidity		temp;
			statistics			stat;
		}s_all;
	}
};
#endif

