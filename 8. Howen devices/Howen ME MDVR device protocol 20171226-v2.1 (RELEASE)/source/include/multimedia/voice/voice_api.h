

/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月21日
描述:音频控制api定义(用于pc进行数据采集和播放)
历史:
1、2017年04月21日 初步创建
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170421
Description: audio control api definition (for PC data acquisition and playback )       
History:
1, 20170421: initial establish 
instruction:
*/


#ifndef _voice_api_h_
#define _voice_api_h_

namespace HowenVoice
{
	namespace api
	{
		//windows
		#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32)  

				#ifdef HW_VOICE_EXPORTS
					#define decoder_api extern "C" __declspec(dllexport)
				#else
					#define decoder_api extern "C" __declspec(dllimport)
				#endif

		#else

				#define decoder_api extern "C"

		#endif


		//-------------------------------------------------------------------------------------
		// 功能：初始化环境
		// 参数：p_reserved[in]:保留
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Initialization environment
		// @parameter：p_reserved[in]:reserved 
		// @Return：Error code 
		//-------------------------------------------------------------------------------------
		decoder_api long long	voice_api_initialize(void* p_reserved);

		//-------------------------------------------------------------------------------------
		// 功能：释放环境
		// 参数：无
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：free environment
		// @parameter：NULL
		// @Return：Error 
		//-------------------------------------------------------------------------------------
		decoder_api long long	voice_api_uninitialize();

		//-------------------------------------------------------------------------------------
		// 功能：创建对象
		// 参数：pp_object[in,out]:对象指针,内部创建指针对象,提供给外部使用，需要外部进行释放	
		//		  object_type:对象类型（HowenVoice::enums::e_object_code对象)
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：create Object 
		// @parameter：pp_object[in,out]:Pointer to an object that creates an internal pointer object that is available for external use and requires an external release	
		//		  object_type:ojbect type (HowenVoice::enums::e_object_code object)
		// @Return：Error 
		//-------------------------------------------------------------------------------------
		decoder_api long long	voice_api_create_object(void** pp_object,long long object_type);
	};
};

#endif
