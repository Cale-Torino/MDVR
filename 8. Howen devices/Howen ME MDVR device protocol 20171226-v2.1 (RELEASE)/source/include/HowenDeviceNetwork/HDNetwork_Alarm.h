/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: george wan
日期: 2017年03月28日
描述: 报警信息定义
历史:
1、2017年03月28日 初步创建
使用说明:
*/

#ifndef _HDNetwork_Alarm_h_
#define _HDNetwork_Alarm_h_

#pragma once

#include "HDNetwork_Structs.h"

namespace HowenDeviceNetwork
{
	namespace structs
	{
		namespace alarms
		{

#pragma pack(1)

			//通道定义，用于视频丢失、移动侦测、视频遮挡、输入触发、紧急告警
			//channel list ,using for videlost ,motion detection,video mask,input trigger,urgent
			typedef struct channels
			{
				unsigned short					channel;			//通道		//channel
				unsigned short					reserved;			//保留		//reserved
			}channels;


			//过载告警，用于 低速告警、超速告警、低温告警、高温告警
			//over load alarm,using for low speed,over speed,low temperature,over temperature
			typedef struct overload
			{
				int		nTriggerJudgeValue;		//触发判断阈值,条件判断的数值，如超速中 > 90为超速，则此值为90
												//the value of trigger to consider,if overspeed,>90 is overspeed,the value set 90

				int		nTriggerTimeValue;		//时间阈值,如超速中连续 > 90达到5秒才算超速，则此值为5秒
												//the value of time to consider,seconds, if overspeed,like =5,means the vehi will overspeed>90 and continue 5 seconds
				int		nMaxValue;				//最大值,期间产生的最大值		//the max value
				int		nMinValue;				//最小值,期间产生的最小值		//the min value
				int		nAverageValue;			//平均值,期间平均值          //the average within the alarm period
				int		nCurrentValue;			//当前上报时候的数值			//the value of current
			}overload;

			//超时停车		//long parking
			typedef struct parking
			{
				int		nTriggerJudgeSeconds;	//触发判断阈值,条件判断的数值,秒		//the second of considering
				int		nParkSeconds;			//停车时长，秒						//seconds of parking
			}parking;


			//震动告警		//shaking
			typedef struct shaking
			{
				overload				condition;			//条件			//condition
				enums::e_gsensor_type	type:32;			//方向			//direction
			}shaking;

			//电子围栏、电子线路	//fence and line
			typedef struct eFence
			{
				int							number;			//编号,围栏或者线路的编号		//number of fence or line
				enums::e_get_inout_status	status;			//状态			//status
			}eFence;

			//异常开关门			//door exception
			typedef struct doorException
			{
				enums::e_door_position		position:32;		//门位置			//position of door
				enums::e_door_status		status:32;			//状态			//status
			}doorException;

			//磁盘异常			//disk exception		
			typedef struct diskException
			{
				char							name[8];			//名称,需要全部小写	如sd1, sd2, hdd1, hdd2	//name ,need lower characters,link sd1,sd2,hdd1,hdd2
				enums::e_disk_exception_reason	reason:32;			//原因		//reason
			}diskException;

			//疲劳驾驶
			typedef struct fatigueDrive
			{
				int		nDegree;				//疲劳度	
			}fatigueDrive;

			//油量异常
			typedef struct fuelException
			{
				int		nTriggerJudgeValue;		//触发判断阈值			//the value of trigger to consider
				int		nCapacity;				//油箱容量,升			//capacity of tank,litre
				int		nRemain;				//剩余油量				//remain of tank,litre
			}fuelException;

			//简化的报警数据		//one simple alarm pack data
			typedef struct oneSimpleAlarmData
			{
				typedef union unPayload
				{
					channels			channelsData;
					overload			overloadData;
					parking				parkingData;
					shaking				shakingData;
					eFence				eFenceData;
					doorException		doorData;
					diskException		diskData;
					fatigueDrive		fatigueData;
					fuelException		fuelData;
				}unPayload;


				common::datatime	dtu;
				common::datatime	startTime;
				common::datatime	stopTime;

				enums::e_alarm_type	type : 32;

				unPayload		payload;
			}oneSimpleAlarmData;

			//一条报警数据		//one alarm pack data
			typedef struct oneAlarmData
			{
				oneSimpleAlarmData	alarm;

				char				szSnapshotFile[128];	//图片地址		//the path of snapshot
				char				szRecordFile[128];		//录像地址		//the path of record
			}oneAlarmData;

#pragma pack()

		};
	};
};

#endif

