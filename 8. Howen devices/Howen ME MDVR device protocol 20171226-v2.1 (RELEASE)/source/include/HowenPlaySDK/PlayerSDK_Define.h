
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年05月02日
描述: 基础定义
历史:
1、2017年05月02日 初步创建
使用说明:
*/


/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.05.02
Description: basic Definition 
History:
1,20170502:initial establish 
instruction:
*/


#ifndef _PlayerSDK_Define_h_
#define _PlayerSDK_Define_h_

#pragma once

#include "PlayerSDK_Enum.h"

namespace howenPlayer
{
	namespace standards
	{
		//数据帧
		//the frame data of media stream
		typedef struct s_frame_data
		{
			//数据类型,参考 howenPlayer::enums::e_frame_type
			//data type,refer to "howenPlayer::enums::e_frame_type"
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

	namespace functions
	{
		//-------------------------------------------------------------------------------------
		// 功能：设备创建新文件回调函数定义
		// 参数： info[in]:信息内容
		//		 userdata1,userdata2[in]:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function: device create new file callback function definition 
		// @parameter: info[in]:information content
		//		 userdata1,userdata2[in]:user data 
		// @return:null 
		//-------------------------------------------------------------------------------------
		//typedef void (CALLBACK *callback_device_create_new_file)(responds::s_device_new_file* info, long long userdata1, long long userdata2);

	}
};
#endif

