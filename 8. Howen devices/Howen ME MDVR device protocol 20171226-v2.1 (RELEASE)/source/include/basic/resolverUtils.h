

/*
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年03月14日
描述: 属性相关解析工具集
历史:
1、2017年03月14日
	初步创建
2、2017年05月13日
	调整xml2json，json2xml接口
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170314
Description: Attribute correlation analysis tool       
History:
1, 20170314: initial establish 
instruction:
*/

#ifndef _resolverUtils_h_
#define _resolverUtils_h_

#pragma once

#include <string>
#include <basic/xmlReader.h>
#include <basic/jsonWriter.h>

namespace resolver
{
	namespace utils
	{
		//-------------------------------------------------------------------------------------
		// 功能：比较字符串（ 不区分大小写）
		// 参数：src1,src2[in]:需要比较的两个字符串
		// 返回：true:相等
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Compare string (case insensitive)
		// @parameter：src1,src2[in]:Two strings to compare
		// @Return：true:equal 
		//-------------------------------------------------------------------------------------
		bool compareNoCase(const char* src1, const char* src2);

		//-------------------------------------------------------------------------------------
		// 功能：拷贝字符串
		// 参数：source[in]:数据源		buffer[out]:目的地
		//		 buffer_length[in]:目的一长度
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：copy string 
		// @parameter：source[in]:data source 		buffer[out]:destination 
		//		 buffer_length[in]:Destination length
		// @Return：NULL 
		//-------------------------------------------------------------------------------------
		void copyStringValue(const char* source, char* buffer, int buffer_length);

		//-------------------------------------------------------------------------------------
		// 功能：转换字符串为32位整数
		// 参数：source[in]:数据源		defualtValue[in]:默认值
		//		 forceHex[in]:是否强制转换为16进制（字符串数据认为是16进制，如"1234"认为是0x1234）
		// 返回：64位整数
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Convert string to 32 bit integer
		// @parameter：source[in]:data source 		defualtValue[in]:default value 
		//		 forceHex[in]:Whether to convert to hexadecimal（string data is hexadecimal, e.g " 1, 2, 3, 4" is 0x1234）
		// @Return：64 bit integer 
		//-------------------------------------------------------------------------------------
		long long convertLongLongValue(const char* source, long long defualtValue = 0, bool forceHex = false);
	}

	namespace convertors
	{
		//-------------------------------------------------------------------------------------
		// 功能：xml转换成json
		// 参数：xmlBuffer[in]:xml格式数据
		//		 nodeName[in]:需要转换的节点名称以及下面内容,如果查找到,则处理第一个,为空,处理全部
		//		 compact[in]:  true--紧凑型,网络传输使用为主 false--格式化形式，文件使用为主
		// 返回：json格式数据
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：xml convert json
		// @parameter：xmlBuffer[in]:xml format data 
		//		 nodeName[in]:The name of the node to be converted and the following, if can be search, process first one, else process all 
		//		 compact[in]: true--compactness,used for net transfer		false--format,used for file
		// @Return：json format data 
		//-------------------------------------------------------------------------------------
		std::string  xml2json(const char* xmlBuffer,const char* nodeName = NULL, bool compact = true);

		//-------------------------------------------------------------------------------------
		// 功能：json转换成xml
		// 参数：jsonBuffer[in]:json格式数据
		//		 nodeName[in]:需要转换的节点名称以及下面内容,如果查找到,则处理第一个,为空,处理全部
		//		 compact[in]:  true--紧凑型,网络传输使用为主 false--格式化形式，文件使用为主
		// 返回：xml格式数据
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：json convert to xml
		// @parameter：jsonBuffer[in]:json format data 
		//		 nodeName[in]:The name of the node to be converted and the following, if can be search, process first one, else process all
		//		 compact[in]: true--compactness,used for net transfer		false--format,used for file
		// @Return：xml foramt data 
		//-------------------------------------------------------------------------------------
		std::string json2xml(const char* jsonBuffer, const char* nodeName = NULL, bool compact = true);
	}
};

#endif