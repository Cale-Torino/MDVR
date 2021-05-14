
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月21日
描述: 音频控制基础定义(用于pc进行数据采集和播放)
历史: 
1、2017年04月21日 初步创建
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170421
Description: audio control basic definition (for PC data acquisition and playback )       
History:
1, 20170421: initial establish 
instruction:
*/


#ifndef _voice_define_h_
#define _voice_define_h_

#pragma once

namespace HowenVoice
{
	namespace enums
	{
		//错误代码
		typedef enum e_error_code
		{
			e_error_code_succeed = 0x0000,				//成功                           //success 
			e_error_code_buffer_alloc_failed = 0x4001,				//缓冲区分配失败     //buffer assign failed
			e_error_code_buffer_full = 0x4002,				//缓冲区满                   //buffer full 
			e_error_code_invalid_parameter = 0x4003,				//无效参数           //invalid parameter 
			e_error_code_initialize_not_execute = 0x4005,				//未执行初始化   //initialize not execute 

			e_error_code_unsupport = 0x4FFE,				//不支持                     //not support 
			e_error_code_unknow = 0x4FFF,				//未知                            //unknow 
		}e_error_code;

		//对象类型
		//object type 
		typedef enum e_object_code
		{
			e_object_code_unknow = 0x00,					//未知                      //unknow 
			e_object_code_player = 0x01,					//播放器                      //player 
			e_object_code_record = 0x02,					//录制器                      //recorder 
		}e_object_code;
	};

	namespace standards
	{
		//-------------------------------------------------------------------------------------
		// 功能：音频采集数据回调函数定义
		// 参数：
		//		 buffer:缓冲区		length:长度
		//		 ll_userdata1,ll_userdata2:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Audio acquisition data callback function definition
		// @parameter：
		//		 buffer:buffer 		length:length 
		//		 ll_userdata1,ll_userdata2:user data 
		// @Return：NULL
		//-------------------------------------------------------------------------------------
		typedef void (CALLBACK *datacallback)(char* buffer, int length, long long ll_userdata1, long  long ll_userdata2);
	};
};

#endif