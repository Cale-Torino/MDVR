
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月21日
描述: 工具集
历史:
1、2017年03月21日 初步创建
使用说明:
*/

#ifndef _utils_h_
#define _utils_h_

#pragma once

#include <string>

namespace utils
{
	//-------------------------------------------------------------------------------------
	// 功能：格式化时间
	//参数：buffer[in]:日期数组，每个字节分别对应年月日时分秒，其中年份=当前年份-2000
	// 返回：“2017-02-21 11:21:32"格式
	
    //Function:Format time
    //Parameter:buffer[in]: date array,YEAR = current year - 2000
    //Return:“2017-02-21 11:21:32" format	//-------------------------------------------------------------
	std::string formatTime(unsigned char* buffer);

	//-----------------------------------------------------------------
	// 功能：转换
	// 参数：buffer[in]:缓冲区		bytes[in]:字节数
	// 返回：对应类型结果
	
	//Function:convert
    //Parameter:buffer[in]	bytes[in]
    //Return:related type value
	//----------------------------------------------------------------------
	int transferInteger(char* buffer,int bytes);
	long long transferLong(char* buffer, int bytes);

	//-------------------------------------------------------------------------------------
	// 功能：转换为浮点型
	// 参数：buffer[in]:缓冲区		bytes[in]:字节数	denominator[in]:分母
	// 返回：浮点型
	
	//Function:convert to floating value
    //Parameter:buffer[in]	bytes[in] denominator[in]
    //Return:floating value
	//-----------------------------------------------------------------------
	float transferFloat(char* buffer, int bytes, float denominator);

	//-------------------------------------------------------------------------------------
	// 功能：转换为浮点型的度
	// 参数：degree[in]:度		minute[in]:分
	// 返回：浮点型
	//Function:convert degree value to floating type
    //Parameter:degree[in] minute[in]
    //Return:floating value
	//-----------------------------------------------------------------------
	float transferDegree(unsigned char degree, float minute);

	//-------------------------------------------------------------------------------------
	// 功能：格式化网络地址
	// 参数：address[in]:地址数组
	// 返回："192.168.1.5"样式
	//Function:Format network address
    //Parameter:address[in]:address array
    //Return:"192.168.1.5" format
	
	//----------------------------------------------------------------------
	std::string formatNetworkAddress(unsigned char* address);

	//-------------------------------------------------------------------------------------
	// 功能：获取小于256字节的字符串(其中第一字节为长度，包含结束符)
	// 参数：buffer[in]:缓冲区	p_length[out]:占用长度
	// 返回：字符串
	//Function:get string whose length is less than 256bytes(The first byte is the length ,including end character)
    //Parameter:buffer[in]	p_length[out]:occupied length
    //Return:String
	
	//--------------------------------------------------------------------
	std::string getLess256String(char* buffer, int* p_length);

	//-------------------------------------------------------------------------------------
	// 功能：打印输出
	// 参数：fmt[in]:输出内容
	// 返回：无
	//Function:Print output
    //Parameter:fmt[in]
    //Return:Null
	
	//-----------------------------------------------------------------------
	void DebugOutput(const char* fmt, ...);

	//-------------------------------------------------------------------------------------
	// 功能：状态数据分析
	// 参数：status_buffer[in]:状态数据
	// 返回：无
	//Function:Status data analysis
    //Parameter:status_buffer[in]:status data
    //Return:Null
	
	//--------------------------------------------------------------------
	void statusAnalyse(char* status_buffer);
};

#endif