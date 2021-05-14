
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年02月20日
描述: 解码器接口
历史: 
1、2017年02月20日 初步创建
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170220
Description: decoder definition    
History:
1, 20170220: initial establish 
instruction:
*/


#ifndef _decoder_port_h_
#define _decoder_port_h_

#pragma once

#include "decoder_define.h"

namespace HowenDecoder
{
	namespace ports
	{
		class decoder
		{
		public:
			//------------------------------------------------------------
			//功能：  初始化
			//参数：  parameter[in]:工作参数
			//返回：  错误代码
			//------------------------------------------------------------
			//------------------------------------------------------------
			//@function：  Initialization environment
			//@parameter：  parameter[in]: working parameter 
			//@Return：  Error code 
			//------------------------------------------------------------
			virtual long long	initialize(standards::s_work_parameter& parameter) = 0;

			//-------------------------------------------------------------------------------------
			// 功能：释放对象
			// 参数：无
			// 返回：无
			//-------------------------------------------------------------------------------------
			
			//-------------------------------------------------------------------------------------
			// @function：free object 
			// @parameter：null 
			// @Return：null 
			//-------------------------------------------------------------------------------------
			virtual void	release() = 0;

		public:

			//------------------------------------------------------------
			//功能：  释放解码器
			//参数：  无
			//返回：  错误代码
			//------------------------------------------------------------
			
			
			//------------------------------------------------------------
			//@function：  free decoder  
			//@parameter：  bull 
			//@Return：  Error Code 
			//------------------------------------------------------------
			virtual long long	free_decoder() = 0;

			//------------------------------------------------------------
			//功能：  解码（有可能采取异步，需要通过回调返回解码后数据）
			//参数：  frame_buffer[in]::数据帧缓冲区		length[in]::数据帧长度
			//		  frame_type:数据帧类型
			//返回：  错误代码
			//------------------------------------------------------------
			
			//------------------------------------------------------------
			//@function：  decoder（can take asynchronous, Need to return the decoded data after the callback）
			//@parameter：  frame_buffer[in]::data frame buffer		length[in]::data frame length 
			//		  frame_type: data frame type 
			//@Return：  Error Code 
			//------------------------------------------------------------
			
			
			virtual long long	decode_one(unsigned char* frame_buffer,long long frame_length,long long frame_type) = 0;

			//------------------------------------------------------------
			//功能：  复位解码缓冲区
			//参数：  无
			//返回：  错误代码
			//------------------------------------------------------------
			//------------------------------------------------------------
			//@function：  Reset decoding buffer
			//@parameter：  Null 
			//@Return：  Error Code 
			//------------------------------------------------------------
			virtual long long	reset_decoder_buffer() = 0;

		};

	};
};

#endif