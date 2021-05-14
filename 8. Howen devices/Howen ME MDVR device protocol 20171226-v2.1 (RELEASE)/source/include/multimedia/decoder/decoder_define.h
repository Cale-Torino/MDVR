
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年02月20日
描述: 解码器基础定义
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


#ifndef _decoder_define_h_
#define _decoder_define_h_

#pragma once

namespace HowenDecoder
{
	namespace enums
	{
		typedef enum e_error_code				//错误代码     //Error Code 
		{
			e_error_code_succeed						= 0x0000,				//成功                //success 
			e_error_code_buffer_alloc_failed			= 0x1001,				//缓冲区分配失败      //buffer assigned failed 
			e_error_code_buffer_full					= 0x1002,				//缓冲区满            //buffer full 
			e_error_code_invalid_parameter				= 0x1003,				//无效参数            //invalid parameter 
			e_error_code_load_library_failed			= 0x1004,				//相关库文件加载失败  //failed to load relative file  
			e_error_code_initialize_not_execute			= 0x1005,				//未执行初始化        //No initialization

			e_error_code_unsupport						= 0x1FFE,				//不支持              //not support 
			e_error_code_unknow							= 0x1FFF,				//未知                 //unknow 
		}e_error_code;

		typedef enum	e_frame_after_decode_code								//解码后数据帧类型      //data frame type after decode 			
		{
			e_frame_after_decode_code_invalid			= 0x00,					//无效                  //invalid 
			e_frame_after_decode_code_audio_pcm8		= 0x01,					//8bit pcm               //8bit pcm
			e_frame_after_decode_code_audio_pcm16		= 0x02,					//16bit pcm              //16bit pcm

			e_frame_after_decode_code_video_rgb565		= 0x100,				//RGB565（RGB16,android）  //RGB565（RGB16,android）
			e_frame_after_decode_code_video_rgb24		= 0x200,				//RGB24（RGB24,ios）       //RGB24（RGB24,ios）
			e_frame_after_decode_code_video_yv12		= 0x400,				//YV12                    //YV12

		}e_frame_afeter_decode_code;


		typedef enum e_object_code											//对象类型                    //object type 
		{
			e_object_code_invalid						= 0x00,				//无效                        //invalid 
			e_object_code_g7xx							= 0x01,				//g711 & g726                 //G711 & G726

			e_object_code_ffmpeg						= 0x101,			//ffmpeg                      //ffmpeg
		}e_class_code;

		typedef enum e_audio_compress_code									//音频压缩类型               //audio compression type 
		{
			e_audio_compress_code_invalid				= 0x00,				//无效                       //invalid 
			e_audio_compress_code_g726					= 0x01,				//g726                        //G726
			e_audio_compress_code_g711					= 0x02,				//g711                         //G711
		}e_audio_compress_code;

		typedef enum	e_multimedia_frame_code									//媒体数据帧类型           //media data frame type 
		{
			e_multimedia_frame_code_invalid				= 0x00000000,			//无效帧                   //invalid frame 
			e_multimedia_frame_code_video_headframe		= 0x62646368,			//'hcdb'视频头帧            //'hcdb' video header frame 
			e_multimedia_frame_code_video_keyframe		= 0x62643030,			//'00db'视频主帧            //'00db' video main frame 
			e_multimedia_frame_code_video_pframe		= 0x63643030,			//'00dc'视频p帧             //'00dc'video P frame 

			e_multimedia_frame_code_audio_headframe		= 0x62776368,			//'hcwb'音频头帧            //'hcwb'video header frame 
			e_multimedia_frame_code_audio_compressframe = 0x62773030,			//'00wb'音频压缩帧          //'00wb'audio compression frame 

			e_multimedia_frame_code_LBS					= 0x73626c30,			//'0lbs'定位状态数据帧       //'0lbs'location status data frame 
			e_multimedia_frame_code_alarm				= 0x6D613030,			//'00am'定位状态数据帧       //'00am'location status data frame 
		}e_multimedia_frame_code;
	}

	namespace standards
	{
		typedef struct s_audio_format											//音频格式(用于做初始化动作)   // audio format (for initialization action)
		{
			long long			compress;										//压缩类型（参考 HowenDecoder::enums::e_audio_compress_code） //compression type (refer to "HowenDecoder::enums::e_audio_compress_code"）
			long long			auxiliary;										//辅助信息（参考 HowenG7xx::enums::packing）  //auxiliary inforamtion (refer to "HowenG7xx::enums::packing"）
			long long			bitrate;										//采样率16000，24000，32000，40000            //sampling rate 16000，24000，32000，40000
		}s_audio_format;

		typedef struct s_video_yuv_part											//yuv视频分量                     //yuv video component 
		{
			unsigned char*		buffer;											//缓冲区                          //buffer 
			long long			pitch;											//跨度
		}s_video_yuv_part;

		typedef struct s_video_yuv_data											//yuv数据                   //yuv data 
		{
			//y,u,v分量数据
			s_video_yuv_part		y;
			s_video_yuv_part		u;
			s_video_yuv_part		v;
		}s_video_yuv_data;
		 
		typedef struct s_video_rgb												//rgb数据                    //rgb data    
		{
			unsigned char*		buffer;											//缓冲区                     //buffer 
			long long			length;											//长度
		}s_video_rgb;


		typedef struct s_video_data												//视频数据                   //video data              
		{
			typedef union u_data
			{
				s_video_yuv_data	yv12;										//yv12                       //yv12
				s_video_rgb			rgb;										//rgb                        //rgb
			}u_data;

			long long			witdh;											//宽度                       //width 
			long long			height;											//高度                       //height 
			u_data				video;											//视频数据                    //video data 
			
		}s_video_data;

		typedef struct s_audio_data												//音频数据                    //audio data 
		{
			unsigned char*		buffer;											//缓冲区                      //buffer 
			long long			length;											//长度                        //length
		}s_audio_data;

		//-------------------------------------------------------------------------------------
		// 功能：解码后数据回调函数定义
		// 参数：
		//		 frame_code：数据帧类型，参考e_frame_after_decode_code
		//		 buffer:缓冲区
		//		 frame_code == e_frame_after_decode_code_video_xxx,时候，对应s_video_data
		//		 frame_code == e_frame_after_decode_code_audio_xxx,时候，对应s_audio_data
		//		 e_decoded_frame_code_rgb_xx:对应数据缓冲区)
		//		 ll_userdata1,ll_userdata2:用户数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------------------
		// @function：callback function definition of data after decode 
		// @parameter：
		//		 frame_code：data frame type，refer to "e_frame_after_decode_code"
		//		 buffer: buffer 
		//		 frame_code == e_frame_after_decode_code_video_xxx, is correspond to " s_video_data"
		//		 frame_code == e_frame_after_decode_code_audio_xxx, is correspond to " s_audio_data"
		//		 e_decoded_frame_code_rgb_xx: is correspond to data buffer )
		//		 ll_userdata1,ll_userdata2: user data 
		// @Return：null 
		//-------------------------------------------------------------------------------------
		
		typedef void (CALLBACK *datacallback)(long long frame_code, unsigned char* buffer,long long ll_userdata1,long  long ll_userdata2);


		typedef struct s_work_parameter											//工作参数             //working parameter 
		{
			long long			cb_data_type;									//需要回调的数据类型（参考e_frame_afeter_decode_code，按位复合）
			                                                                     //the data type need to be callback (refer to "e_frame_afeter_decode_code"，Positional recombination）
			datacallback		cb_function;									//回调函数                //callback function
			long long			cb_userdata1;									//回调用户数据1            //callback user data 1
			long long			cb_userdata2;									//回调用户数据2             //callback user data 2
		}s_work_parameter;

	};
};

#endif

