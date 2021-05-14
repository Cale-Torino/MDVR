/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: george wan
日期: 2017年03月21日
描述: 设备网络通讯库 公用定义
历史:
1、2017年03月21日 初步创建
使用说明:
*/

#ifndef _HDNetwork_Struct_h_
#define _HDNetwork_Struct_h_

#pragma once

#include "HDNetwork_Enums.h"

namespace HowenDeviceNetwork
{
	namespace structs
	{
		namespace common
		{

#pragma pack(1)
			//设备概要			//device's summary
			typedef struct device_summary
			{
				int			deviceType;			//设备类型,参考enums::device_type			//deviceType,ref enums::device_type
				char		deviceID[24];		//设备编号								//device's id
				char		mobile[24];			//手机号码								//mobile number
				char		appVersion[24];		//应用程序版本							//app's version
				char		guid[64];			//guid,暂时保留							//device's guid
			}device_summary;

			//日期		//datetime
			typedef struct datatime
			{
				short		year;
				char		month;
				char		day;

				char		hour;
				char		minute;
				char		second;
				char		reserved;
			}datatime;

			//一个字节位	//bit's of one byte
			typedef struct oneByte
			{
				unsigned char	bit0 : 1;
				unsigned char	bit1 : 1;
				unsigned char	bit2 : 1;
				unsigned char	bit3 : 1;
				unsigned char	bit4 : 1;
				unsigned char	bit5 : 1;
				unsigned char	bit6 : 1;
				unsigned char	bit7 : 1;
			}oneByte;

			//通道字节位		//bit's of channel
			typedef struct shortChannelBytes
			{
				unsigned char	ch0 : 1;
				unsigned char	ch1 : 1;
				unsigned char	ch2 : 1;
				unsigned char	ch3 : 1;
				unsigned char	ch4 : 1;
				unsigned char	ch5 : 1;
				unsigned char	ch6 : 1;
				unsigned char	ch7 : 1;

				unsigned char	reserved : 8;
			}shortChannelBytes;

			//数据帧		//frame's data
			typedef struct frame_data
			{
				enums::e_frame_type		type;		//数据帧类型		//frame type
				int				length;		//一帧数据长度(不包含当前结构长度)		//frame's length ,not include current header size
				long long 		timestamp;	//utc时间戳,微秒						//utc
				long long		payload;	//缓冲区地址							//frame buffer address
			}frame_data;

#pragma pack()

		};

		namespace works
		{
			//工作参数
			typedef struct parameter
			{
				int			size;					//本结构体大小，便于扩展
				int			statusCacheNumber;		//定位等状态缓冲条数（默认为10000），为0，表示不缓冲
				char		statusCacheName[32];	//定位等状态缓冲文件名，为空，默认为status.cache
				int			statusGenerateSeconds;	//定位状态发送间隔,默认为15秒
			}parameter;
		}

		namespace deviceControl
		{
#pragma pack(4) 
			//云台控制		//ptz control
			typedef struct ptz
			{
				enums::e_ptz_action		action;		//动作类型			//action type
				unsigned char			channel;	//通道，从1开始		//channel,start from 1
				unsigned char			xspeed;		//x方向速度，1~10	//speed of x,1~10
				unsigned char			yspeed;		//y方向速度，1~10	//speed of y,1~10
				unsigned char			preset;		//预置位	,0~255		//preset,0~255
			}ptz;

			//车辆控制		//control vehi
			typedef struct vehi_operate
			{
				typedef struct doorPosition
				{
					enums::e_door_position	pos;	//门位置				//door position
				}doorPosition;

				typedef union payload
				{
					doorPosition		door;
				}payload;

				enums::e_vehicle_action	action;		//动作类型			//action type
				payload					data;		//负载				//payload
			}vehi_operate;
#pragma pack()
		}
	};
};

#endif

