/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: george wan
日期: 2017年03月21日
描述: 设备网络通讯库 状态定义
历史:
1、2017年03月21日 初步创建
使用说明:
*/

#ifndef _HDNetwork_Status_h_
#define _HDNetwork_Status_h_

#pragma once

#include "HDNetwork_Structs.h"

namespace HowenDeviceNetwork
{
	namespace structs
	{
#pragma pack(1)

		namespace status
		{

			//定位信息		//location's data
			typedef struct location
			{
				common::datatime	dtu;					//DTU
				enums::e_location_mode	emLocationType;		//定位类型	 					//location's type

				char				cSatellite;				//卫星数量						//number of satellite
				char				cLongitudeDirect;		//经度方向，'W','E'				//direct of longitude,'W' or 'E
				char				cLatitudeDirect;		//纬度方向,'S','N'				//direct of latitude,'S' or 'N'
				unsigned char		ucLongitudeDegree;		//经度的度						//degree of longitude

				unsigned char		ucLatitudeDegree;		//纬度的度						//degree of latitude
				char				reserved[3];			//保留							//reserved

				short				sDirect;				//方向,0~359  正北 为 0， 顺时针	//direct 0~359,north is 0
				short				sAltitude;				//海拔高度,米					//altitude,meter

				unsigned short		usSpeed;				//速度,千米/小时					//speed,KM/H
				short				usAccuracy;				//定位精度,米					//accuracy,meter

				int					nLongitudeMinute;		//经度的分，*10000				//minute of longitude,need *10000
				int					nLatitudeMinute;		//纬度的分，*10000				//minute of latitude,need *10000
			}location;

			//gsensor
			typedef struct gsensor
			{
				unsigned short		usX;					//X,g*100,-4000 ~ +4000,0xFFFF-无效		//X,g*100,-4000 ~ +4000,0xFFFF -- invalid
				unsigned short		usY;					//Y,g*100,-4000 ~ +4000,0xFFFF-无效		//Y,g*100,-4000 ~ +4000,0xFFFF -- invalid

				unsigned short		usZ;					//Z,g*100,-4000 ~ +4000,0xFFFF-无效		//Z,g*100,-4000 ~ +4000,0xFFFF -- invalid
				unsigned short		usTilt;					//倾斜,g*100,-4000 ~ +4000,0xFFFF-无效	//tilt,g*100,-4000 ~ +4000,0xFFFF -- invalid

				unsigned short		usHit;					//撞击,g*100,-4000 ~ +4000,0xFFFF-无效	//hit,g*100,-4000 ~ +4000,0xFFFF -- invalid
				unsigned short		reserved;				//保留
			}gsensor;

			//基础信息			//basis info
			typedef struct basis
			{
				unsigned char acc : 1;						//acc,0-无效，1-有效			//acc,0--invalid,1--valid
				unsigned char brake : 1;					//刹车,0-无效，1-有效			//brake,0--invalid,1--valid
				unsigned char left : 1;						//左转,0-无效，1-有效			//left,0--invalid,1--valid
				unsigned char right : 1;					//右转,0-无效，1-有效			//right,0--invalid,1--valid
				unsigned char forward : 1;					//前进,0-无效，1-有效			//front,0--invalid,1--valid
				unsigned char backward : 1;					//后退,0-无效，1-有效			//backward,0--invalid,1--valid
				unsigned char leftFrontDoor : 1;			//左前门,0-无效，1-有效		//left front door,0--invalid,1--valid
				unsigned char rightFrontDoor : 1;			//右前门,0-无效，1-有效		//right front door,0--invalid,1--valid

				unsigned char leftMiddleDoor : 1;			//左中门0-无效，1-有效		//left middle door,0--invalid,1--valid
				unsigned char rightMiddleDoor : 1;			//右中门0-无效，1-有效		//left middle door,0--invalid,1--valid
				unsigned char leftBackDoor : 1;				//左后门0-无效，1-有效		//left back door,0--invalid,1--valid
				unsigned char rightBackDoor : 1;			//右后门0-无效，1-有效		//left back door,0--invalid,1--valid
				unsigned char reservedChar2 : 4;			//保留						//reserved

				unsigned char reserved[2];					//保留
			}basis;

			//模块状态			//module's status
			typedef struct modules
			{
				enums::e_module_work_status	mobile : 4;		//移动网络状态			//mobile network module status
				enums::e_module_work_status	lcation : 4;	//定位模块状态			//location module status
				enums::e_module_work_status	wifi : 4;		//WIFI模块状态			//wifi module status
				enums::e_module_work_status	gsensor : 4;	//gsensor状态			//gsensor module status

				common::shortChannelBytes	record;			//录像状态，0--未录像，1--录像中	
															//record'status ,0--not record 1--recording

				char				reserved[2];			//保留					//reserved
			}modules;


			//燃油状态		//fuel status
			typedef struct fuel
			{
				unsigned short		usComsume;				//油耗,实际*10,0xFFFF-无效	//comsume of fuel ,need*10,0xFFFF-invalid
				unsigned short		usRemain;				//剩余,0xFFFF-无效			//remain of fuel,0xFFFF-invalid
			}fuel;

			//移动网络状态	//mobile network status
			typedef struct mobileNetwork
			{
				enums::e_access_net	emNetworkType:16;		//网络类型						//network type
				unsigned int		cSignalIntensity:16;	//信号强度0：无效 1~10（最强）	//intensity of signal 0--无效 1~10(max)
			}mobileNetwork;

			//WIFI网络状态	//wifi network status
			typedef struct wifiNetwork
			{
				unsigned int		uiAddress;				//网络地址,如192.168.0.1，对应为byte[0] = 0xC0, byte[1] = 0xA8, byte[2] = x000, byte[3] = 0x01
															//address,like 192.168.0.1,byte[0] = 0xC0, byte[1] = 0xA8, byte[2] = x000, byte[3] = 0x01
				unsigned int		uiGateway;				//网关,同上		//refer to the above

				unsigned int		uiSubnetMask;			//子网掩码,同上	//refer to the above

				char				cSignalIntensity;		//信号强度,0：无效 1~10（最强）	//intensity of signal 0--无效 1~10(max)
				char				reserved[3];			//保留			//reserved
				//char				cSSID[255];				//SSID
			}wifiNetwork;

			//磁盘状态		//disk's status
			typedef struct disks
			{
				typedef struct item
				{
					enums::e_disk_work_status	status:16;	//状态			//status
					unsigned int				index:16;	//编号			//index,0~7
					unsigned int				uiTotal;	//总大小，MB		//totol size of diks,mega bytes
					unsigned int				uiRemain;	//剩余，MB		//remain size of diks,mega bytes
				}item;

				item		disk[4];						//磁盘状态，按顺序填充，如果disk[1]全为0，后面disk[2],disk[3]有数据也不会再解析
															//status information,by sequeue,if disk[1] equal zero,disk[2],disk[3] will be ignored
			}disks;

			//告警状态			//alarms
			typedef struct alarms
			{
				unsigned int		overspeed : 1;			//超速告警,0--未触发，1--触发			//overspeed ,0--untrigger 1--trigger
				unsigned int		lowespeed : 1;			//低速告警,0--未触发，1--触发			//low speed ,0--untrigger 1--trigger
				unsigned int		urgent : 1;				//紧急告警,0--未触发，1--触发			//urgent ,0--untrigger 1--trigger
				unsigned int		longParking : 1;		//超时停车,0--未触发，1--触发			//long park ,0--untrigger 1--trigger

				unsigned int		shaking : 1;			//震动告警,0--未触发，1--触发			//shake ,0--untrigger 1--trigger
				unsigned int		getOutFence : 1;		//越界告警,0--未触发，1--触发			//get out fence ,0--untrigger 1--trigger
				unsigned int		getInFence : 1;			//入界告警,0--未触发，1--触发			//get in fence ,0--untrigger 1--trigger
				unsigned int		getOutLine : 1;			//越线告警,0--未触发，1--触发			//get out line ,0--untrigger 1--trigger

				unsigned int		getInLine : 1;			//入线告警,0--未触发，1--触发			//get in line ,0--untrigger 1--trigger
				unsigned int		fuels : 1;				//油量告警,0--未触发，1--触发			//fuel ,0--untrigger 1--trigger

				unsigned int		reservedBits : 22;		//保留位，补充足4个字节				//reserved bits.full in 4 bytes

				common::shortChannelBytes	videoLost;		//视频丢失							//video lost
				common::shortChannelBytes	motionDetection;//移动侦测							//motion detection
				common::shortChannelBytes	videoMask;		//视频遮挡							//video mask
				common::shortChannelBytes	inputs;			//输入触发							//input trigger
			}alarms;

			//温湿度状态		//temperature and humidity
			typedef struct temperateHumidity
			{
				unsigned short		usInsideTemperature;	//车内温度,*100倍					//temperature inside of vehi,need*100
				unsigned short		usOutsideTemperature;	//车外温度,*100倍					//temperature outside of vehi,need*100

				unsigned short		usEngineTemperature;	//发动机温度,*100倍					//temperature of engine ,need*100
				unsigned short		usDeviceTemperature;	//设备温度,*100倍					//temperature of device,need*100

				char				cInsideHumidity;		//车内湿度							//humidity inside of vehi,percent
				char				cOutsideHumidity;		//车外湿度							//humidity outside of vehi,percent
				char				reserved[2];			//保留
			}temperateHumidity;

			//统计信息		//statistics data
			typedef struct statistics
			{
				unsigned int		uiTotalMileage;			//总里程，米						//total mileage,meter
				unsigned int		uiCurrentDayMileage;	//当天里程，米					//current day mileage,meter
			}statistics;

			//信息汇总
			typedef struct allData
			{
				location			locationData;
				gsensor				gsensorData;
				basis				basisData;
				modules				moduleData;
				fuel				fuelData;
				mobileNetwork		mobileData;
				wifiNetwork			wifiData;
				disks				diskData;
				alarms				alarmData;
				temperateHumidity	THData;
				statistics			statData;
			}allData;
		};

#pragma pack()
	};
};

#endif

