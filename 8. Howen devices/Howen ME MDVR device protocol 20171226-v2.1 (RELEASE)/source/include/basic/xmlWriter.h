
/*
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年03月14日
描述: xml格式作者
历史:
1、2017年03月14日
	初步创建
2、2017年05月13日
	调整getStream接口
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170314
Description: xml format writer        
History:
1, 20170314: initial establish 
instruction:
*/



#ifndef _xmlWriter_h_
#define _xmlWriter_h_

#pragma once

#include <thirdpart/tinyXML/include/tinyxml.h>
#include <string>

namespace resolver
{

	class xmlWriter
	{
	public:
		typedef enum digitFormat
		{
			digitFormat_Dec				= 0,		//十进制格式                //dotted-decimal format
			digitFormat_Hex_NonHeader	= 1,		//十六进制带0x标识          //Hexadecimal with Ox icon 
			digitFormat_Hex_ExistHeader = 2,		//十六进制不带0x标识        //Hexadecimal without Ox icon 
		}digitFormat;

	public:
		xmlWriter();
		virtual ~xmlWriter();

	public:
		//-------------------------------------------------------------------------------------
		// 功能：创建根节点
		// 参数：name[in]:节点名称
		// 返回：节点对象
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：create root node 
		// @parameter：name[in]:node name 
		// @Return：node object 
		//-------------------------------------------------------------------------------------
		TiXmlElement* createRoot(const char* name);

		//获取根节点
		//get root node 
		TiXmlElement* getRoot();

		//保存到文件
		//save to file 
		bool save(const char* filename);

		//获取字符串流
		//compact:  true--紧凑型,网络传输使用为主 false--格式化形式，文件使用为主
		//get string stream 
		//compact:  true--compactness,used for net transfer		false--format,used for file
		std::string getStream(bool compact = true);

	public:
		//-------------------------------------------------------------------------------------
		// 功能：创建节点
		// 参数：name[in]:节点名称
		// 返回：节点对象
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：create node 
		// @parameter：name[in]:node name 
		// @Return：node object 
		//-------------------------------------------------------------------------------------
		TiXmlElement* createNode(TiXmlElement* root, const char* name);

		//-------------------------------------------------------------------------------------
		// 功能：设置属性
		// 参数：element[in]:节点对象，为空，则为根节点
		//		 attribute[in]:属性名		value[in]:对应值
		// 返回：成功与否
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：setting property 
		// @parameter：element[in]:node object, if the node object is null, it's the root node 
		//		 attribute[in]:Attribute name		value[in]:Corresponding value
		// @Return：success or not 
		//-------------------------------------------------------------------------------------
		bool setAttribute(TiXmlElement* element, const char* attribute, const char* value);

		//-------------------------------------------------------------------------------------
		// 功能：插入节点
		// 参数：nodeName[in]:节点名称		value[in]:对应值
		//		 parent[in]:父亲节点，为空，则父亲节点为根节点
		//		 updateIfExist[in]:true：更新存在的节点		false：插入新节点（默认）
		// 返回：节点对象
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：insert node 
		// @parameter：nodeName[in]:node name 		value[in]:Corresponding value
		//		 parent[in]:father node, if the father node is NULL, it's the root node 
		//		 updateIfExist[in]:true：update existing node		false：Insert new node (default)
		// @Return：node object
		//-------------------------------------------------------------------------------------
		TiXmlElement* InsertElement(const char* nodeName, const char* value, TiXmlElement* parent = NULL, bool updateIfExist = false);
		TiXmlElement* InsertElement(const char* nodeName, long long value, TiXmlElement* parent = NULL, bool updateIfExist = false, digitFormat format = digitFormat_Dec);

	private:
		TiXmlDocument	m_document;		//文档对象         //file object 
		TiXmlElement*	m_root;			//根节点           //root node 
	};

};

#endif