
#include "stdafx.h"
#include "MultiMediaBusiness.h"
#include <multimedia/voice/voice_api.h>
#include <HowenPlaySDK/PlayerSDK_API.h>
#include <multimedia/g7xx/g7xxendec.h>
#include <DeviceDriverSDK/DeviceDriver_API.h>

MultiMediaBusiness* MultiMediaBusiness::_cur = NULL;

//麦克风数据回调
//callback function for mic data 
void CALLBACK MIC_DataCallback(char* pcmBuffer, int length, long long userdata1, long long userdata2)
{
	MultiMediaBusiness* bm = (MultiMediaBusiness*)userdata1;

	char g726Buffer[1280] = { 0 };
	int g726Bytes = HowenG7xx::api::g7xx_api_encode(bm->m_726Encoder, pcmBuffer, length, g726Buffer);

	//发送给设备
	//send to device
	howenDriver::standards::s_send_media_request req;
	req.deviceID = bm->m_talkDeviceID.c_str();
	req.sessionID = bm->m_talkSenssionID.c_str();
	req.data.frameBuffer = g726Buffer;
	req.data.frameLength = g726Bytes;
	req.data.frameType = howenDriver::enums::e_frame_type_audio;
	req.data.timestamp = 0;

	howenDriver::api::HDeviceDriver_SendVoiceData2Device(&req);
}


MultiMediaBusiness::MultiMediaBusiness()
{
	MultiMediaBusiness::_cur = this;

	howenPlayer::api::HPlayer_Initialize();

	for (int i = 0; i < max_video_player; ++i)
	{
		m_video_player[i].player = 0;
		m_video_player[i].sessionID = "";
	}

	m_voice_recorder = NULL;
	m_726Encoder = 0;
}

MultiMediaBusiness::~MultiMediaBusiness()
{
	howenPlayer::api::HPlayer_Uninitialize();
}

//启动工作
//start work
//renderWindows:the window's handle for video rendering
void MultiMediaBusiness::startWork()
{
	//创建G726编码器
	//create g726 encoder
	m_726Encoder = HowenG7xx::api::g7xx_api_create(HowenG7xx::enums::bitrate_40, HowenG7xx::enums::packing_left);

	//创建音频采集器
	//create audio collector
	HowenVoice::api::voice_api_create_object((void**)&m_voice_recorder, HowenVoice::enums::e_object_code_record);
}

//停止工作
//stop work
void MultiMediaBusiness::stopWork()
{
	for (int i = 0; i < max_video_player; ++i)
	{
		if (0 != m_video_player[i].player)
		{
			howenPlayer::api::HPlayer_ClosePlayer(m_video_player[i].player);
		}
		
		m_video_player[i].player = 0;
		m_video_player[i].sessionID = "";
	}

	if (NULL != m_voice_recorder)
	{
		m_voice_recorder->stopWork();
		m_voice_recorder->release();
		m_voice_recorder = NULL;
	}

	HowenG7xx::api::g7xx_api_destroy(m_726Encoder);
	m_726Encoder = 0;
}

//启动 音视频播放
//start playing video ＆ audio
void MultiMediaBusiness::startAVPlaying(int index,const char* sessionID,HWND renderWindow,bool playVoice)
{
	if(m_video_player[index].player == 0)
		howenPlayer::api::HPlayer_OpenPlayer(m_video_player[index].player);

	howenPlayer::api::HPlayer_StartWork(m_video_player[index].player, (long long)renderWindow);
	howenPlayer::api::HPlayer_OpenSounds(m_video_player[index].player, playVoice);
	m_video_player[index].sessionID = sessionID;
}

//关闭 音视频播放
//stop playing video ＆ audio
void MultiMediaBusiness::stopAVPlaying(int index)
{
	if (m_video_player[index].player == 0)
		return;

	howenPlayer::api::HPlayer_OpenSounds(m_video_player[index].player, false);
	howenPlayer::api::HPlayer_StopWork(m_video_player[index].player);
	howenPlayer::api::HPlayer_ClosePlayer(m_video_player[index].player);
	m_video_player[index].player = 0;
	m_video_player[index].sessionID = "";
}

//播放音视频
//play audio and video frame
void MultiMediaBusiness::playAVFrame(const char* sessionID,howenPlayer::standards::s_frame_data& frame)
{
	for (int i = 0; i < max_video_player; ++i)
	{
		if (m_video_player[i].sessionID.compare(sessionID) == 0)
		{
			howenPlayer::api::HPlayer_InputMediaData(m_video_player[i].player, frame);
			break;
		}
	}
}

//设置对讲信息
//set talkInformation
void MultiMediaBusiness::setTalkInformation(const char* deviceID, const char* sessionID)
{
	m_talkSenssionID = sessionID;
	m_talkDeviceID = deviceID;
}

//启动mic采集
//start mic collection 
void MultiMediaBusiness::StartMicCollect()
{
	//启动音频采集
	//start mic collection 
	m_voice_recorder->setCallback(MIC_DataCallback, (long long) this, NULL);
	m_voice_recorder->startWork(1, 1, 8000, 16, 320);
}

//停止mic采集
//stop mic collection 
void MultiMediaBusiness::StopMicCollect()
{
	if (NULL != m_voice_recorder)
	{
		m_voice_recorder->stopWork();
	}
}