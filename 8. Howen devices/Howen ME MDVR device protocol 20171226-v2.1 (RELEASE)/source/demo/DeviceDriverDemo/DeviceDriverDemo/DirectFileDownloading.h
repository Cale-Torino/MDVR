
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年05月20日
描述: 文件接收（直接从设备下载）
历史:
1、2017年05月20日 初步创建
使用说明:
*/

/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170520
Description: direct download file from device
History:
1, 20170520: initial establish 
instruction:
*/


#ifndef  _Direct_File_Downloading_h_
#define  _Direct_File_Downloading_h_

#pragma once

class DirectFileDownloading
{
public:
	DirectFileDownloading();
	virtual ~DirectFileDownloading();

public:
	//返回已经下载的文件长度
	//return the size of file had downloaded
	int startWork(const char* fileName);

	void stopWork();

	void writeData(const char* buffer, int length);

	
public:
	//是否工作中
	//working status
	bool isWorking();

private:
	FILE*			m_file;

public:
	static DirectFileDownloading*	_cur;
};

#endif 
