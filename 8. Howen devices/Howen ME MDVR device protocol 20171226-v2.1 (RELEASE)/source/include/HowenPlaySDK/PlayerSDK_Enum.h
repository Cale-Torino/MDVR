
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年05月02日
描述: 枚举定义
历史:
1、2017年05月02日 初步创建
使用说明:
*/

/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.05.02
Description: Enumeration Definition 
History:
1,20170502:initial establish 
instruction:
*/



#ifndef _PlayerSDK_Enum_h_
#define _PlayerSDK_Enum_h_

#pragma once

namespace howenPlayer
{
	namespace enums
	{
		//错误码		//error code
		typedef enum e_error_code
		{
			e_error_code_succeed						= 0x0000,				//成功				//succeed
			e_error_code_initialize_not_execute			= 0x11001,				//未执行初始化		//not execute initialize
			e_error_code_invalid_parameter				= 0x11002,				//无效参数			//parameter is invalid
			e_error_code_file_not_exist					= 0x11003,				//文件不存在		//file is not exist
			e_error_code_object_not_exist				= 0x11004,				//对象不存在		//object is not exist

			e_error_code_unsupport						= 0x20FFE,				//不支持			//unsupport
			e_error_code_unknow							= 0x20FFF,				//未知				//unknow
		}e_error_code;
		
		//数据帧类型      // data frame type 
		typedef enum e_frame_type
		{
			e_frame_type_invalid						= 0x00,					//无效				//invalid
			e_frame_type_video_i						= 0x01,					//视频I帧			//the I frame of video
			e_frame_type_video_p						= 0x02,					//视频P帧			//the P frame of video
			e_frame_type_audio							= 0x03,					//音频帧				//audio frame 
			e_frame_type_status							= 0x06,					//状态数据帧(设备状态,如GPS) //status data frame of device,such as gps
			e_frame_type_alarm							= 0x07,					//告警数据帧			//alarm data frame 
		}e_frame_type;

	};
};
#endif

