
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月10日
描述: 告警定义
历史:
1、2017年04月10日 初步创建
使用说明:
*/

/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.10
Description: Alarm Definition 
History:
1,20170410:initial establish
instruction:
*/




#ifndef _DeviceDriver_Alarm_h_
#define _DeviceDriver_Alarm_h_

#pragma once

#include "DeviceDriver_Enum.h"

namespace howenDriver
{
	namespace alarms
	{
		//通道告警
		//channel trigger alarm
		typedef struct 
		{
			//通道编号,从1开始		
			//channel index,start from 1
			int						channel;						
		}s_channel,s_video_lost,s_motion_dection,s_video_mask,s_input,s_emergency;

		//低速告警、超速告警、低温告警、高温告警
		//low speed trigger,over speed trigger,low temperature trigger,over temperature trigger
		typedef struct
		{
			//触发阈值
			//trigger threshold
			int						triggerValue;
			//时间阈值
			//time threshold
			int						timeValue;
			//最大值
			//max value
			int						maxValue;
			//最小值
			//min value
			int						minValue;
			//平均值
			//average
			int						averageValue;
			//当前值
			//current value
			int						currentValue;
		}s_low_speed,s_over_speed,s_low_temp,s_over_temp;

		//超时停车
		//park timeout
		typedef struct s_park_timeout
		{
			//触发阈值
			//trigger threshold
			int						triggerValue;
			//总停车时长
			//total park time(seconds)
			int						totalSeconds;
		}s_park_timeout;

		//震动告警
		//shake alarm
		typedef struct s_shake
		{
			//触发阈值
			//trigger threshold
			int						triggerValue;
			//时间阈值
			//time threshold
			int						timeValue;
			//最大值
			//max value
			int						maxValue;
			//最小值
			//min value
			int						minValue;
			//平均值
			//average value
			int						averageValue;
			//当前值
			//current value
			int						currentValue;
			//方向	1--x 2--y 3--z 4--撞击  5--倾斜
			//direct 1--x 2--y 3--z 4--impact 5--tilt
			int						direct;
		}s_shake;

		//电子围栏,电子线路
		//electronic defence,electronic line
		typedef struct s_defence
		{
			//围栏编号
			//number of defence or line
			int						index;
			//状态,  0--进入 1--离开
			//status ,0--enter 1--leave
			int						status;
		}s_defence, s_e_defence,s_e_line;

		//异常开关门
		//open/close door exception
		typedef struct s_door_exception
		{
			//门编号, 1--左前门  2--右前门  3--左中门 4--右中门  5--左后门  6--右后门
			//number of door,1--left front door 2--right front door 3--left middle door 4--right middle door 5--left back door 6--right back door
			int						index;

			//状态,  0--关闭  1--打开
			//status, 0--close  1--open
			int						status;
		}s_door_exception;

		//存储介质异常
		//storage exception
		typedef struct s_storage_exception
		{
			//磁盘名字,如sd1,sd2,hdd1,hdd2
			//disk name ,example:sd1,sd2,hdd1,hdd2
			char					name[constants::max_disk_name];

			//状态,  0--丢失  1--损坏 2--无法覆盖
			//status, 0--lost 1--demage 2--can not cover
			int						status;
		}s_storage_exception;

		//疲劳驾驶
		//fatigue drive
		typedef struct s_fatigue_driving
		{
			//疲劳度,1~10,10最疲惫
			//fatigue degree 1~10,10 is the highest;
			int						level;
		}s_fatigue_driving;

		//燃料异常
		//fuel exception
		typedef struct s_feul_exception
		{
			//触发阈值
			//trigger value
			int						triggerValue;

			//总容量
			//total megabytes
			int						total;

			//剩余容量
			//free megabytes
			int						free;
		}s_feul_exception;
		
		typedef union  s_payload
		{
			s_video_lost			videoLost;
			s_motion_dection		motionDection;
			s_video_mask			videoMask;
			s_input					input;
			s_emergency				emergency;
			s_low_speed				lowSpeed;
			s_over_speed			overSpeed;
			s_park_timeout			parkTimeOut;
			s_shake					shake;
			s_e_defence				defence;
			s_e_line				line;
			s_door_exception		doorException;
			s_storage_exception		storageException;
			s_fatigue_driving		fatigueDriving;
			s_feul_exception		feulException;
		}s_payload;

		//所有告警汇总
		//all alarm information
		typedef struct s_all
		{
			//本结构体大小,用来后续扩展字段时候做判断
			//the size of this structer ,for extension field judgement
			int						size;

			//事件类型,参考howen::enums::Drivere_alarm_type
			//event type, refer to " howen::enums::Drivere_alarm_type"
			int						type;

			//设备时间
			//Device time;
			char					deviceTime[constants::max_time];
			//开始时间
			//start time
			char					startTime[constants::max_time];
			//结束时间
			//stop time
			char					stopTime[constants::max_time];
			//图片地址
			//the path of snapshot file
			char					snapshot[constants::max_path];
			//录像地址
			//the path of record file
			char					record[constants::max_path];

			//信息联合体
			//union of information
			s_payload				payload;
		}s_all;

	}
};
#endif

