
/*
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年03月17日
描述: json格式读者
历史:
1、2017年03月17日
	初步创建
2、2017年05月22日
	增加接口 loadFromBuffer2
	增加 getStream接口，支持获取一部分json数据模式
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170317
Description: Json format reader     
History:
1, 20170317: 
	initial establish
2, 201702:
	add function loadFromBuffer2
instruction:
*/



#ifndef _jsonReader_h_
#define _jsonReader_h_

#pragma once

#include <thirdpart/jsonCPP/include/json.h>

namespace resolver
{
	class jsonReader
	{
	public:
		typedef bool (CALLBACK *recurseElement)(jsonReader& parse, Json::Value* element, const char* node_name, const char* value, void* userdata1, void* userdata2);
		
		//-------------------------------------------------------------------------------------
		// 功能：通过名称查找节点对象
		// 参数：root[in]:根节点		nodename[in]:需要查找的名称(不区分大小写)
		// 返回：查找到的最终节点，否则返回空
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Find node objects by name
		// @parameter：root[in]:root node		nodename[in]:name to be searched(Case insensitive)
		// @Return：Find the end node , otherwise empty
		//-------------------------------------------------------------------------------------
		static Json::Value* getNodePointerByName(Json::Value* root, const char* nodename);

	public:
		jsonReader();
		virtual ~jsonReader();

	public:
		//-------------------------------------------------------------------------------------
		// 功能：从文件加载
		// 参数：filename[in]:文件名
		// 返回：true:成功	false:失败
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：load from file 
		// @parameter：filename[in]: file name
		// @Return：true:success 	false: failed 
		//-------------------------------------------------------------------------------------
		bool loadFromeFile(const char* filename);

		//-------------------------------------------------------------------------------------
		// 功能：从内存加载
		// 参数：buffer[in]:缓冲区,确保为0结束的字符串
		// 返回：true:成功	false:失败
		//-------------------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------------------
		// @function：load from memory 
		// @parameter：buffer[in]:buffer ,be sure to finished by '\0'
		// @Return：true:success 	false:failed 
		//-------------------------------------------------------------------------------------
		bool loadFromBuffer(const char* buffer);

		//-------------------------------------------------------------------------------------
		// 功能：从内存加载
		// 参数：buffer[in]:缓冲区	length[in]:缓冲区长度
		// 返回：true:成功	false:失败
		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// @function：load from memory 
		// @parameter：buffer[in]:buffer
		//			   length[in]:buffer's length,for sub the string
		// @Return：true:success 	false:failed 
		//-------------------------------------------------------------------------------------
		bool loadFromBuffer2(const char* buffer,int length);

	public:
		//获取相关类型数据
		//get related type data 
		bool getStringValue(Json::Value* element, const char* nodename, char* buffer, int buffer_length);
		bool getStringValue(Json::Value* element, char* buffer, int buffer_length);
		bool getStringValue(const char* nodename, char* buffer, int buffer_length);
		std::string getStringValue(const char* nodename);
		std::string getStringValue(Json::Value* element, const char* nodename);

		long long getLongLongValue(Json::Value* element, long long defualtValue = 0, bool forceHex = false);
		long long getLongLongValue(Json::Value* element, const char* nodename, long long defualtValue = 0, bool forceHex = false);
		long long getLongLongValue(const char* nodename, long long defualtValue = 0, bool forceHex = false);

	public:
		//-------------------------------------------------------------------------------------
		// 功能：遍历访问
		// 参数：root[in]:根节点		recurse[in]:是否递归子节点
		//		 func,userdata1,userdata2[in]:回调函数和相关数据
		// 返回：无
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Traversal access
		// @parameter：root[in]:root node 		recurse[in]:Recursive sub node or not 
		//		 func,userdata1,userdata2[in]:Callback functions and related data
		// @Return：NULL
		//-------------------------------------------------------------------------------------
		void traverse(Json::Value* root, bool recurse, recurseElement func, void* userdata1, void* userdata2);

	public:
		//获取根节点
		//get root node 
		Json::Value* getRoot();

	public:
		//获取字符串流
		//nodeName:节点名，为空，则不增加任何节点，格式为{....内容...},不为空，则增加节点名，格式为{"nodename":{...内容...}}
		//compact:  true--紧凑型 false--文件格式使用为主
		//get string stream 
		//nodeName:if empty，format:{....content...},  not NULL,format:{"nodename":{...内容...}}
		//compact:  true--compactness,used for net transfer		false--format,used for file
		std::string getStream(Json::Value* root, const char* nodeName = NULL,bool compact = true);

	private:
		Json::Value				m_root;
	};
};

#endif