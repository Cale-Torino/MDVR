
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月21日
描述: 音频控制接口(用于pc进行数据采集和播放)
历史: 
1、2017年04月21日 初步创建
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170421
Description: audio control interface (for PC data acquisition and playback )       
History:
1, 20170421: initial establish 
instruction:
*/

#ifndef _voice_port_h_
#define _voice_port_h_

#pragma once

#include "voice_define.h"

namespace HowenVoice
{
	namespace ports
	{
		//播放器
		//player 
		class player
		{
		public:
			//-------------------------------------------------------------------------------------
			//功能:启动
			//参数:
			//		wFormatTag[in]:采用格式		 nChannel[in] : 音频通道数(1~2)
			//		nSamplesPerSec[in]:每秒采样数(8000,11025,22050,44100)
			//		wBitsPerSample[in]:每个采样包位数(8,16)
			//		 uiBufferLength:每个采集数据缓冲区的长度(0:内部控制)
			//		 uiBufferCount:缓冲区数量(内部开辟的缓冲区大小为uiBufferLength*uiBufferCount,10~10000,默认100)
			//返回:成功与否
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//@function:start 
			//@parameter:
			//		wFormatTag[in]:adopt format 		 nChannel[in] : audio channel (1~2)
			//		nSamplesPerSec[in]:Sampling per second(8000,11025,22050,44100)
			//		wBitsPerSample[in]:Number of samples per packet(8,16)
			//		 uiBufferLength:The buffer length of each collection data (0:inner control )
			//		 uiBufferCount:buffer count (internal buffer size is uiBufferLength*uiBufferCount,10~10000,default : 100)
			//@Return:success or not 
			//-------------------------------------------------------------------------------------
			virtual	bool	startWork(unsigned short wFormatTag, unsigned short nChannel, unsigned int nSamplesPerSec, unsigned short wBitsPerSample, unsigned int uiBufferLength, unsigned int uiBufferCount) = 0;

			//-------------------------------------------------------------------------------------
			//功能:停止
			//参数:无
			//返回:成功与否
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//@function:stop 
			//@parameter:null 
			//@Return:success or not 
			//-------------------------------------------------------------------------------------
			virtual bool	stopWork() = 0;

			//-------------------------------------------------------------------------------------
			//功能:设置音量大小(startWork之后才能使用)
			//参数:usVolumn[in]:音量大小(0~0xFFFF)
			//返回:成功与否
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//@function:set volume size (valid after startWork)
			//@parameter:usVolumn[in]:volume size 小(0~0xFFFF)
			//@Return:success or not 
			//-------------------------------------------------------------------------------------
			virtual	bool	setVolumn(unsigned short usVolumn) = 0;

			//-------------------------------------------------------------------------------------
			//功能:获取音量大小(startWork之后才能使用)
			//参数:无
			//返回:音量大小(0~0xFFFF)
			//-------------------------------------------------------------------------------------
			//@function:get volume size (valid after startWork)
			//@parameter:null 
			//@Return:volume size (0~0xFFFF)
			//-------------------------------------------------------------------------------------
			
			virtual	unsigned short	getVolumn() = 0;

			//-------------------------------------------------------------------------------------
			//功能:压入数据进行播放(startWork之后才能使用)
			//参数:p_buffer:缓冲区
			//		 ui_buffer_length:缓冲区长度
			//返回:成功与否
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//@function:press data to play (valid after startWork)
			//@parameter:p_buffer:buffer 
			//		 ui_buffer_length:buffer length 
			//@Return:success or not 
			//-------------------------------------------------------------------------------------
			virtual bool  inputData(char* p_buffer, int ui_buffer_length) = 0;

			//-------------------------------------------------------------------------------------
			//功能:清空缓冲区
			//参数:无
			//返回:成功与否
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//@function:clear buffer 
			//@parameter:null 
			//@Return:success or not 
			//-------------------------------------------------------------------------------------
			virtual bool	resetBuffer() = 0;

			//-------------------------------------------------------------------------------------
			// 功能：释放对象
			// 参数：无
			// 返回：无
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			// @function：release object 
			// @parameter：null
			// @Return：null
			//-------------------------------------------------------------------------------------
			virtual void	release() = 0;
		};

		//采集器
		//collector 
		class record
		{
		public:
			//-------------------------------------------------------------------------------------
			// 功能：设置回调
			// 参数：func[in]:回调函数		userdata1,userdata[in]:用户数据
			// 返回：无
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			// @function：set callback 
			// @parameter：func[in]:callback function 		userdata1,userdata[in]:user data 
			// @Return：null 
			//-------------------------------------------------------------------------------------
			virtual void setCallback(standards::datacallback func, long long userdata1, long long userdata2) = 0;

			//-------------------------------------------------------------------------------------
			//功能:启动工作
			//参数:	wFormatTag[in]:采用格式		 nChannel[in]:音频通道数(1~2)
			//		nSamplesPerSec[in]:每秒采样数(8000,11025,22050,44100)
			//		wBitsPerSample[in]:每个采样包位数(8,16)
			//		uiBufferLength[in]:=0内部分配缓冲区,其他指定缓冲区大小
			//返回:成功与否
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//@function:start 
			//@parameter:	wFormatTag[in]:adopt format 		 nChannel[in]:audio channel(1~2)
			//		nSamplesPerSec[in]:Sampling per second(8000,11025,22050,44100)
			//		wBitsPerSample[in]:Number of samples per packet(8,16)
			//		uiBufferLength[in]:=0 is for internal buffer , else for specified buffer size 其他指定缓冲区大小
			//@Return:success or not 
			//-------------------------------------------------------------------------------------
			virtual	bool	startWork(unsigned short wFormatTag = 1, unsigned short nChannel = 1, unsigned long nSamplesPerSec = 8000, unsigned short wBitsPerSample = 16, unsigned int uiBufferLength = 0) = 0;

			//-------------------------------------------------------------------------------------
			// 功能：停止
			// 参数：无
			// 返回：无
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			// @function：stop 
			// @parameter：null
			// @Return：null
			//-------------------------------------------------------------------------------------
			
			virtual	bool	stopWork() = 0;

			//-------------------------------------------------------------------------------------
			// 功能：释放对象
			// 参数：无
			// 返回：无
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			// @function：release object 
			// @parameter：null
			// @Return：null
			//-------------------------------------------------------------------------------------
			virtual void	release() = 0;
		};

	};
};

#endif