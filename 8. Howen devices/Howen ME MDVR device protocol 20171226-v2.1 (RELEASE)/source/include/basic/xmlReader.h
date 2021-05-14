
/*
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年03月14日
描述: xml格式读者
历史:
1、2017年03月14日 初步创建
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170314
Description: xml format reader        
History:
1, 20170314: initial establish 
instruction:
*/

#ifndef _xmlReader_h_
#define _xmlReader_h_

#pragma once

#include <thirdpart/tinyXML/include/tinyxml.h>
#include <string>

namespace resolver
{
	class xmlReader
	{
	public:
		typedef bool (CALLBACK *recurseElement)(xmlReader& parse, TiXmlElement* element, const char* node_name, const char* value, void* userdata1, void* userdata2);

		//-------------------------------------------------------------------------------------
		// 功能：通过名称查找节点对象
		// 参数：root[in]:根节点		nodename[in]:需要查找的名称(不区分大小写)
		// 返回：查找到的最终节点，否则返回空
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：Find node objects by name
		// @parameter：root[in]: root node 		nodename[in]:Name to be searched (case insensitive)
		// @Return：Find the end node, otherwise empty
		//-------------------------------------------------------------------------------------
		static TiXmlElement* getNodePointerByName(TiXmlElement* root, const char* nodename);

	public:
		xmlReader();
		virtual ~xmlReader();

	public:
		//-------------------------------------------------------------------------------------
		// 功能：从文件加载
		// 参数：filename[in]:文件名
		// 返回：true:成功	false:失败
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：load from file 
		// @parameter：filename[in]:file name 
		// @Return：true:success 	false: failed 
		//-------------------------------------------------------------------------------------
		bool loadFromeFile(const char* filename);

		//-------------------------------------------------------------------------------------
		// 功能：从内存加载
		// 参数：buffer[in]:缓冲区
		// 返回：true:成功	false:失败
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：load from momery 
		// @parameter：buffer[in]:buffer 
		// @Return：true:success 	false:fail 
		//-------------------------------------------------------------------------------------
		bool loadFromBuffer(const char* buffer);

	public:
		//获取相关类型数据
		//get related type data 
		bool getStringValue(TiXmlElement* element, const char* nodename, char* buffer, int buffer_length);
		bool getStringValue(TiXmlElement* element, char* buffer, int buffer_length);
		bool getStringValue(const char* nodename, char* buffer, int buffer_length);
		std::string getStringValue(TiXmlElement* element);

		long long getLongLongValue(TiXmlElement* element, long long defualtValue = 0, bool forceHex = false);
		long long getLongLongValue(TiXmlElement* element, const char* nodename, long long defualtValue = 0, bool forceHex = false);
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
		// @parameter：root[in]:root node 		recurse[in]:Recursive sub node
		//		 func,userdata1,userdata2[in]:Callback functions and related data
		// @Return：NULL
		//-------------------------------------------------------------------------------------
		void traverse(TiXmlElement* root, bool recurse, recurseElement func, void* userdata1, void* userdata2);

	public:
		//获取根节点
		//get root node 
		TiXmlElement* getRoot();

	private:
		TiXmlDocument	m_document;		//文档对象             //Document object
	};
};

#endif