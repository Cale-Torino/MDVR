
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <hanan.huang@howentech.com,13927488810>
日期: 2017年05月26日
描述: 接口定义
历史:
1、2017年05月26日 初步创建
使用说明:
*/


/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <hanan.huang@howentech.com,13927488810>
Date: 2017.05.26
Description: interface Definition 
History:
1,20170526:initial establish 
instruction:
*/

#ifndef _HDNetwork_API_h_
#define _HDNetwork_API_h_

#pragma once

namespace HowenDeviceNetwork
{
	namespace api
	{

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32)

	#ifdef HOWENDEVICENETWORK_EXPORTS
		#define howen_network_api extern "C" __declspec(dllexport)
	#else
		#define howen_network_api extern "C" __declspec(dllimport)
	#endif

	#else

		#define howen_network_api extern "C"

#endif

		//-------------------------------------------------------------------------------------
		// 功能：初始化环境
		// 参数：无
		// 返回：保留
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：initialize enviroment
		// @parameter：null
		// @return：reserved
		//-------------------------------------------------------------------------------------
		howen_network_api long long	HDeviceNetwork_Initialize();

		//-------------------------------------------------------------------------------------
		// 功能：释放环境
		// 参数：无
		// 返回：保留
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：free enviroment
		// @parameter：null
		// @return：reserved
		//-------------------------------------------------------------------------------------
		howen_network_api long long	HDeviceNetwork_Uninitialize();

		// -------------------------------------------------------------------------------------
		// 功能：创建对象
		// 参数：ppObject[in,out]:IController对象指针,内部创建指针对象,提供给外部使用，需要外部调用release()进行释放
		// 返回：
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：create object
		// @parameter：handler[in]:handle of IController,create inside,need to call release() to destroy it
		// @return：reserved
		//-------------------------------------------------------------------------------------
		howen_network_api long long HDeviceNetwork_CreateObject(void** ppObject);

	};
};

#endif