
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年05月17日
描述: 多媒体控制业务
历史:
1、2017年05月17日 初步创建
使用说明:
*/

/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170517
Description: multimedia business
History:
1, 20170517: initial establish 
instruction:
*/


#ifndef  _MultiMedia_Business_h__
#define  _MultiMedia_Business_h__

#pragma once

#include <map>
#include <HowenPlaySDK/PlayerSDK_Define.h>
#include <multimedia/voice/voice_port.h>

class MultiMediaBusiness
{
public:
	static const int	max_video_player = 8;

	typedef struct video_player
	{
		long long		player;		//播放对象		//object for playing video & audio
		std::string		sessionID;	//会话编号		//session id for playing
	}video_player;

public:
	static MultiMediaBusiness*	_cur;

public:
	MultiMediaBusiness();
	virtual ~MultiMediaBusiness();

	//启动工作
	//start work
	//renderWindows:the window's handle for video rendering
	void startWork();

	//停止工作
	//stop work
	void stopWork();

public:
	//启动 音视频播放
	//start playing video ＆ audio
	void startAVPlaying(int index, const char* sessionID, HWND renderWindow, bool playVoice);

	//关闭 音视频播放
	//stop playing video ＆ audio
	void stopAVPlaying(int index);

	//播放音视频
	//play audio and video frame
	void playAVFrame(const char* sessionID, howenPlayer::standards::s_frame_data& frame);

public:
	//设置对讲信息
	//set talkInformation
	void setTalkInformation(const char* deviceID, const char* sessionID);

	//启动mic采集
	//start mic collection 
	void StartMicCollect();

	//停止mic采集
	//stop mic collection 
	void StopMicCollect();

public:
	//服务器地址，如"192.168.1.6:7788"
	//host address,like"192.168.1.6:7788"
	std::string							m_server_host;							

	//音视频播放对象
	//object for playing video & audio
	video_player						m_video_player[max_video_player];


public:
	//保存对讲的信息
	//save talk info to send data to device
	std::string							m_talkDeviceID;
	std::string							m_talkSenssionID;

	//音频采集对象，用来采集mic的数据
	//collect data from mic ,then use them to send to device
	HowenVoice::ports::record*			m_voice_recorder;
	//G726编码器，用于编码采集的对讲音频发送给设备
	//the decoder should use for encoding the G726 voice before send them to device after record from mic 
	long long							m_726Encoder;
	
};

#endif 
