

/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月21日
描述: g726 & g711 编解码库api定义
历史:
1、2017年04月21日 初步创建
使用说明:
*/

/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.21
Description: g726 &g711 compression api definition  
History:
1,20170421:initial establish 
instruction:
*/



#ifndef _g7xxendec_h_
#define _g7xxendec_h_

namespace HowenG7xx
{

	namespace enums
	{
		//比特率
		//bit rate
		typedef enum bitrate
		{
			bitrate_16					= 1,
			bitrate_24					= 2,
			bitrate_32					= 3,
			bitrate_40					= 4,
		}bitrate;

		//打包方式
		//pack mode
		typedef enum packing
		{
			packing_none				= 0,
			
			//对应海思MEDIA_G726类型
			//the type like hisi's MEDIA_G726
			packing_left				= 1,

			//对应海思G726类型
			//the type like hisi's G726
			packing_right				= 2,
		}packing;
	}

	namespace api
	{
		//windows
		#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32)

				#ifdef G726ENDEC_EXPORTS
					#define g7xx_api extern "C" __declspec(dllexport)
				#else
					#define g7xx_api extern "C" __declspec(dllimport)
				#endif

		#else

				#define decoder_api extern "C"

		#endif


		//-------------------------------------------------------------------------------------
		// 功能：创建解码器
		// 参数：bt[in]:比特率	pk[in]:打包方式
		// 返回：解码器对象
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function: create decoder 
		// @parameter: bt[in]:bit rate 	pk[in]:packing 
		// @return: decoder object
		//-------------------------------------------------------------------------------------
		g7xx_api long long	g7xx_api_create(enums::bitrate bt,enums::packing pk);

		//-------------------------------------------------------------------------------------
		// 功能：释放解码器
		// 参数：obj[in]:解码器对象
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function:free decoder 
		// @parameter：obj[in]:decoding object 
		// @return: null 
		//-------------------------------------------------------------------------------------
		g7xx_api void	g7xx_api_destroy(long long obj);

		//-------------------------------------------------------------------------------------
		// 功能：解码(单包G726音频数据)
		// 参数：obj[in]:解码器对象			g726Buffer[in]:G726数据缓冲区
		//		g726Bytes[in]:G726数据长度	pcmBuffer[out]:PCM数据缓冲区
		// 返回：解码后数据长度
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function: decode (sigle G726 audio data)
		// @parameter:obj[in]:decoder object			g726Buffer[in]:G726 data buffer 
		//		g726Bytes[in]:G726 data length 	pcmBuffer[out]:PCM data buffer 
		// @return: decoded data length 
		//-------------------------------------------------------------------------------------
		g7xx_api int	g7xx_api_decode(long long obj,char* g726Buffer,int g726Bytes,char pcmBuffer[1920]);

		//-------------------------------------------------------------------------------------
		// 功能：编码
		// 参数：obj[in]:编码器对象			pcmBuffer[in]:PCM数据缓冲区
		//		pcmBytes[in]:pcm数据长度		g726Buffer[out]:G726数据缓冲区
		// 返回：编码后数据长度
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function: encoder 
		// @parameter: obj[in]:encoder object 			pcmBuffer[in]:PCM data buffer 
		//		pcmBytes[in]:pcm data length 		g726Buffer[out]:G726 data buffer 
		// @return: encoded data length 
		//-------------------------------------------------------------------------------------
		g7xx_api int	g7xx_api_encode(long long obj, char* pcmBuffer, int pcmBytes, char* g726Buffer);
	};
};

#endif
