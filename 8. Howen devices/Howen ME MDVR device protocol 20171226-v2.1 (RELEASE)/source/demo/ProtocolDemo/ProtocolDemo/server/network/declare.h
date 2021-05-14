
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 基础定义
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _declare_h_
#define _declare_h_

#pragma once

namespace protocol
{
	namespace test
	{
		//上报服务器地址，用于测试
		//Report Server address, for test
		//const char serverHost[] = "192.168.3.128:7788";
		extern char serverHost[128];
	}

	namespace define
	{
		typedef struct msgHeader
		{
			unsigned char		flag;			
			//标识，固定为'H'  
			//flag, fixed as "H"
			unsigned char		versionn;		
			//版本，当前协议版本为1 
			//Version,current protocol version is 1
			unsigned short		code;			
			//消息代码
			//message code
			unsigned int		payloadLength;	
			//负载长度(不包含当前消息头长度)
			//load length(not including the current message header length)
		}msgHeader;

		typedef struct mediaHeader 
		//媒体数据头
		//Media data header
		{
			unsigned short		frame;			
			//帧类型，参考protocol::define::frameCode
			//Frame type,refer to protocol::define::frameCode
			unsigned short		channel;		
			//通道编号，从1开始
			//channel number,begin from 1
			unsigned long long	timestamp;		
			//时间戳
			//Time stamp
		}mediaHeader;

		const int	msgHeaderLength = 8;//sizeof(msgHeader)
		const char	msgHeaderFlag = 'H';
		const char	msgHeaderVersion = 1;

		typedef enum errorCode					
		//错误代码
		//Error code
		{
			errorCodeSucceed			= 0,	//成功 //Success
			errorCodeRepeatDeviceID		= 1,	//重复设备ID //Repeat Device ID
			errorCodeInvalidParameter	= 2,	//无效参数 //Invalid parameter
			errorCodeInvalidCommand		= 3,	//无效命令  //Invalid command
			errorCodeDeviceBusing		= 4,	//设备繁忙  // Device busy
			errorCodeLinkFailed			= 5,	//建立连接失败 //build connection fail
			errorCodeFileNotFound		= 6,	//文件不存在  //file not existed
			errorCodeStoragekNotFound	= 7,	//存储磁盘不存在 //Storage is not found
			errorCodeDataContinue		= 8,	//后续还有文件数据 //Data continue
			errorCodeFileInfoFinished	= 9,	//文件信息传输完毕  //File info transfer finished
		}errorCode;

		typedef enum eventCode					//事件代码  //Event code
		{
			eventCodeUnknow				= 0x00,	//未知 //Unkonwn
			eventCodeVideoLost			= 0x01,	//视频丢失  //Video loss
			eventCodeMotionDetect		= 0x02,	//移动侦测  //Video motion
			eventCodeVideoMask			= 0x03,	//视频遮挡  //Video cover
			eventCodeInputGenerate		= 0x04,	//输入触发  //Sensor Input triggered
			eventCodeUrgency			= 0x05,	//紧急告警  //Emergency alarm
			eventCodeLowSpeed			= 0x06,	//低速告警  //Low speed alarm
			eventCodeOverSpeed			= 0x07, //超速告警  //Overspeed alarm
			eventCodeLowTemperature		= 0x08, //低温告警  //Low temperature alarm
			eventCodeOverTemperature	= 0x09, //高温告警  //High temperature alarm
			eventCodeHumidity			= 0x0a,	//湿度告警  //Humidity alarm
			eventCodeParkTimeout		= 0x0b,	//超时停车  //Parking Timeout alarm
			eventCodeShake				= 0x0c,	//震动告警  //Shock alarm;G-SENSOR alarm
			eventCodeEDefence			= 0x0d, //电子围栏  //GEO fence alarm
			eventCodeELine				= 0x0e, //电子线路  //Electronic route 
			eventCodeDoorException		= 0x0f, //异常开关门 // Abnormal door open/close
			eventCodeStorageException	= 0x10, //存储介质异常 //Storage media exception
			eventCodeFatigueDriving		= 0x11, //疲劳驾驶  //Fatigue driving
			eventCodeFuelException		= 0x12, //油量异常  //Fuel exception
			eventCodeIllegalFire		= 0x13, //非法点火  //Illegal ignition
			eventCodeLocationModulexception = 0x14, //定位模块异常  //GPS module exception
			eventCodeFrontPanelPrise		= 0x15, //前面板打开  //Front panel open
		}eventCode;

		typedef enum linkerCode 
		//连接器类型代码
		//Connector type
		{
			linkerCodeSignal			= 0x00,//信令 //Command
			linkerCodePreview			= 0x01,//预览 //Live video preview
			linkerCodeReplay			= 0x02,//录像回放 //Playback
			linkerCodeVoice				= 0x03,//语音  //Voice
			linkerCodeFileTransfer		= 0x04,//文件传输 //File transfer
			linkerCodeSerialPortProxy	= 0x05,//串口代理（透传）//Serial proxy(transparent transmission)

			linkerCodeInvalid			= 0xff,//无效  //Invalid
		}linkerCode;

		typedef enum fileCode 
		//文件类型代码
		//File type
		{
			fileCodeNormalRecord		= 0x01,//普通录像  //Normal record
			fileCodeAlarmRecord			= 0x02,//报警录像  //Alarm record
			fileCodeNormalSnapshot		= 0x03,//普通抓拍文件  //Normal snapshot
			fileCodeAlarmSnapshot		= 0x04,//报警抓拍文件  //Alarm snapshot
			fileCodeUpgrade				= 0x05,//升级文件  //Update file
			fileCodeLog					= 0x06,//日志文件  //Log file

			fileCodeInvalid				= 0xff,//无效  //Invalid
		}fileCode;

		typedef enum voiceMode 
		//音频模式
		//Voice mode
		{
			voiceModeListen				= 0x00,//监听 //Listen
			voiceModeTalk				= 0x01,//对讲 //Intercom
			voiceModeBroadcast			= 0x02,//广播 //Broadcast
			voiceModePTT				= 0x03,//PTT  //PTT
		}voiceMode;

		typedef enum ptzAction	
		//云台动作代码
		//PTZ control operation 
		{
			ptzActionUnknow				= 0x00,	//未知  //Unknown
			ptzActionUp					= 0x01,	//上  //Up
			ptzActionDown				= 0x02,	//下  //Down
			ptzActionLeft				= 0x03,	//左  //Left
			ptzActionRight				= 0x04,	//右  //Right
			ptzActionLeftUp				= 0x05,	//左上 //Upper Left
			ptzActionLeftDown			= 0x06,	//左下 //Lower Left
			ptzActionRightUp			= 0x07, //右上 //Upper Right 
			ptzActionRightDown			= 0x08, //右下  //Lower down
			ptzActionPresetGoto			= 0x09, //预置位跳转 //Goto preset
			ptzActionPresetSet			= 0x0a,	//预置位设置 //Set preset
			ptzActionPresetClear		= 0x0b,	//清理预置位 //Clear preset
			ptzActionIrisOpen			= 0x0c,	//光圈大 //Iris+
			ptzActionIrisClose			= 0x0d, //光圈小 //Iris-
			ptzActionZoomIn				= 0x0e, //调焦缩小 //Zoom In
			ptzActionZoomOut			= 0x0f, //调焦放大 //Zoom Out
			ptzActionFocusNear			= 0x10, //聚焦近 //Focus+
			ptzActionFocusFar			= 0x11, //聚焦远 //Focus-
			ptzActionAutoScan			= 0x12, //自动水平转动 //AutoScan
			ptzActionBrushOn			= 0x13, //雨刮启动 //Start windscreen wiper
			ptzActionBrushOff			= 0x14, //雨刮关闭 //Stop windscreen wiper
			ptzActionCruiseOpen			= 0x15, //巡航启动 //Start cruise
			ptzActionCruiseClose		= 0x16, //巡航关闭 //Stop cruise
			ptzActionLightOn			= 0x17, //灯光打开 //Turn on light
			ptzActionLightOff			= 0x18, //灯光关闭 //Turn off light
		}ptzAction;

		typedef enum vehicleAction 
		//车辆控制代码
		//Vehicle control operations
		{
			vehicleActionUnknow			= 0x00,	//未知 //Unknown
			vehicleActionOilOff			= 0x01,	//切断油路 //Stop fuel supply
			vehicleActionOilOn			= 0x02,	//恢复油路 //Recover fuel supply
			vehicleActionCircuitOff		= 0x03,	//切断电路 //Turn off power
			vehicleActionCircuitOn		= 0x04,	//恢复电路 //Turn on power
			vehicleActionDoorOpen		= 0x05,	//打开车门 //Open door
			vehicleActionDoorClose		= 0x06,	//关闭车门 //Close door
		}vehicleAction;

		typedef enum frameCode	
		//帧类型
		//Frame type
		{
			frameCodeUnknow				= 0x00,	//未知  //Unknown
			frameCodeVideoIFrame		= 0x01,	//视频I帧 //I frame of video
			frameCodeVideoPFrame		= 0x02,	//视频P帧 //P frame of video
			frameCodeAudioFrame			= 0x03,	//音频帧  //Audio frame
			frameCodeSerialDataFrame	= 0x04,	//串口数据帧 //Serial data frame
			frameCodeFileDataFrame		= 0x05,	//文件数据帧 //File data frme
		}frameCode;
	}

	namespace command
	{
		namespace common
		{
			const int	heartbeat			= 0x0001;//心跳 //Heartbeat
			const int	mediaStream			= 0x0011;//媒体  //Media
		}

		namespace device
		{
			const int	signalRegisterRequest = 0x1001;//信令注册  //Command register
			const int	mediaStreamRegisterRequest = 0x1002;//媒体注册 //Media register
			const int	previewRespond = 0x1010;//预览应答 //Respond to preview
			const int	snapshotRespond = 0x1020;//抓拍应答 //Respond to snapshot
			const int	voiceRespond = 0x1030;//语音请求应答 //Respond to voice request
			const int	statusSubscribeRespond = 0x1040;//状态订阅应答 //Respond to status subscription
			const int	statusData = 0x1041;//状态数据 //Status data
			const int	alarmSubscribeRespond = 0x1050;//告警订阅应答 //Respond to alarm subscription
			const int	alarmData = 0x1051;//告警数据 //Alarm data
			const int	fileDetails = 0x1060;//文件信息 //File info
			const int	replayRespond = 0x1070;// 回放请求应答 //Repond to playback
			const int	serialPortProxyRespond = 0x1080;//透传请求应答 //Respond to transparent transmission
			const int	fileTransferRespond = 0x1090;//文件传输应答 //Respond to file transfer
			const int	ftpTransferRespond = 0x1091;//ftp文件传输完毕报告 //Respond to FTP transfer
			const int	settingRespond = 0x10A0;//参数配置应答 //Respond to paramter config

			const int	baseControlRespond = 0x1100;//基础控制应答（针对0x4100~0x4110)
			//Respond to basic control(Related with 0x4100~0x4110)
		}

		namespace server
		{
			const int	signalRegisterRespond = 0x4001;//信令注册 //Command register
			const int	mediaStreamRegisterRespond = 0x4002;//媒体注册 //Media register
			const int	previewRequest = 0x4010;//预览应答 //Respond to preview
			const int	makeIFrameRequest = 0x4011;//强制编码I帧 //Force it to encode I frame
			const int	snapshotRequest = 0x4020;//抓拍应答 //Respond to snapshot
			const int	voiceRequest = 0x4030;//语音请求应答 //Respond to voice request
			const int	statusSubscribeRequest = 0x4040;//状态订阅应答 //Respond to status subscription
			const int	alarmSubscribeRequest = 0x4050;//告警订阅应答 //Respond to alarm subscription

			const int	fileQueryRequest = 0x4060;//文件查询请求 //File query request
			const int	replayRequest = 0x4070;//回放请求 //Playback request
			const int	replayControl = 0x4071;//回放控制 //Playback control
			const int	serialPortProxyRequest = 0x4080;//透传请求	//Transparent transmission request
			const int	fileTransferRequest = 0x4090;//文件传输请求	//File transfer request
			const int	ftpTransferRequest = 0x4091;//ftp文件传输请求 //FTP transfer request
			const int	settingRequest = 0x40A0;//参数配置请求 //Parameter config request


			const int	ptzControl = 0x4100;//云台控制 //PTZ control
			const int	outputControl = 0x4101;//输出控制 //Output control	
			const int	reboot = 0x4102;//重启 //Restart
			const int	resetDefualtSetting = 0x4103;//恢复出厂设置	//Restore default settings
			const int	syncTime = 0x4104;//同步时间 //Sync time
			const int	recordControl = 0x4105;//录像控制 //Record control	
			const int	resetAlarm = 0x4106;//清理告警 //Clear alarm
			const int	vehiControl = 0x4107;//车辆控制	//Vehicle control
		}
	}

};

#endif