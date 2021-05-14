

/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年02月21日
描述: 解码器api定义
历史:
1、2017年02月21日 初步创建
使用说明:
1、对应的lib为decoder_hw_xx.lib
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170221
Description: decoder api definition   
History:
1, 20170221: initial establish 
instruction:
1,the corresponding lib is decoder_hw_xx.lib
*/



#ifndef _decoder_api_h_
#define _decoder_api_h_

namespace HowenDecoder
{
	namespace api
	{
		//win32
		#if defined(_WINDOWS)

				#ifdef HW_DECODER_EXPORTS
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
		// @Return：Error Code 
		//-------------------------------------------------------------------------------------
		decoder_api long long	decoder_api_initialize(void* p_reserved);

		//-------------------------------------------------------------------------------------
		// 功能：释放环境
		// 参数：无
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：free environment
		// @parameter：nul 
		// @Return：Error Code 
		//-------------------------------------------------------------------------------------
		decoder_api long long	decoder_api_uninitialize();

		//-------------------------------------------------------------------------------------
		// 功能：创建对象
		// 参数：pp_object[in,out]:对象指针,内部创建指针对象,提供给外部使用，需要外部进行释放	
		//		  object_type:对象类型（HowenDecoder::enums::e_object_code对象)
		// 返回：错误代码
		//-------------------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------------------
		// @function：create object 
		// @parameter：pp_object[in,out]:Pointer to an object that creates an internal pointer object that is available for external use and requires an external release	
		//		  object_type:object type（HowenDecoder::enums::e_object_code)
		// @Return：Error Code
		//-------------------------------------------------------------------------------------
		decoder_api long long	decoder_api_create_object(void** pp_object,long long object_type);
	};
};

#endif
