
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年05月10日
描述: 接口定义
历史:
1、2017年05月10日 初步创建
使用说明:
*/


/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.05.10
Description: interface Definition 
History:
1,20170510:initial establish 
instruction:
*/

#ifndef _PlayerSDK_API_h_
#define _PlayerSDK_API_h_

#pragma once

#include "PlayerSDK_Define.h"

namespace howenPlayer
{
	namespace api
	{

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32)

	#ifdef HOWENPLAYSDK_EXPORTS
		#define player_sdk_api extern "C" __declspec(dllexport)
	#else
		#define player_sdk_api extern "C" __declspec(dllimport)
	#endif

	#else

		#define player_sdk_api extern "C"

#endif

		//-------------------------------------------------------------------------------------
		// 功能：初始化环境
		// 参数：无
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：initialize enviroment
		// @parameter：null
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long	HPlayer_Initialize();

		//-------------------------------------------------------------------------------------
		// 功能：释放环境
		// 参数：无
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：free enviroment
		// @parameter：null
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long	HPlayer_Uninitialize();





		//-------------------------------------------------------------------------------------
		// 功能：打开播放器
		// 参数：handler[out]:播放器对象
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：open the player to use
		// @parameter： the handle of the player,if return 0 ,it is unexcept
		// @return：erorr code(refer to " howenPlayer::enums::e_error_code")
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_OpenPlayer(long long& handler);

		//-------------------------------------------------------------------------------------
		// 功能：关闭播放器
		// 参数：handler[in]:播放器对象,通过openPlayer返回的值
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：close the player(after use we need to call it)
		// @parameter：handler[in]:handle of player which from call openPlayer
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_ClosePlayer(long long handler);

		//-------------------------------------------------------------------------------------
		// 功能：启动工作
		// 参数：handler[in]:播放器对象,通过openPlayer返回的值
		//		 renderObject[in]:渲染目的地		 bufferSize[in]:缓冲区大小
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：make the player to work
		// @parameter：handler[in]:handle of player which from call openPlayer
		//		 renderObject[in]:object for render		 bufferSize[in]:buffer size for saving stream
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_StartWork(long long handler, long long renderObject, int bufferSize = 1920 * 1080 * 10);

		//-------------------------------------------------------------------------------------
		// 功能：停止工作
		// 参数：handler[in]:播放器对象,通过openPlayer返回的值
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：stop the player work
		// @parameter：handler[in]:handle of player which from call openPlayer
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_StopWork(long long handler);

		//-------------------------------------------------------------------------------------
		// 功能：输入媒体数据
		// 参数：handler[in]:播放器对象,通过openPlayer返回的值
		//		frame[in]:媒体数据
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：input the frame data to player
		// @parameter：handler[in]:handle of player which from call openPlayer
		//			   frame[in]:media stream data
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_InputMediaData(long long handler, standards::s_frame_data& frame);

		//-------------------------------------------------------------------------------------
		// 功能：打开/关闭声音
		// 参数：handler[in]:播放器对象,通过openPlayer返回的值
		//		 opened[in]:true:打开,false:关闭
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：open/ close the sound(after use we need to call it)
		// @parameter：handler[in]:handle of player which from call openPlayer
		//			   opened[in]:true:open,false:close
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_OpenSounds(long long handler,bool opened);

		//-------------------------------------------------------------------------------------
		// 功能：调整音量
		// 参数：handler[in]:播放器对象,通过openPlayer返回的值
		//		 opened[in]:true:打开,false:关闭
		// 返回：错误代码（参考 howenPlayer::enums::e_error_code）
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：adjust the volumn
		// @parameter：handler[in]:handle of player which from call openPlayer
		//			   value[in]:the value of volumn,0xFFFF is max.
		// @return：erorr code （refer to "howenPlayer::enums::e_error_code"）
		//-------------------------------------------------------------------------------------
		player_sdk_api long long HPlayer_SetVolumn(long long handler, short value);

	};
};

#endif