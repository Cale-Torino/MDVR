
/*
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年03月14日
描述: xml格式作者
历史:
1、2017年03月18日
	初步创建
2、2017年05月13日
	调整getStream接口
3、2017年06月15日
	增加setAttribute接口
使用说明:
*/


/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170314
Description: xml format writer      
History:
1, 20170318: initial establish 
instruction:
*/

#ifndef _jsonWriter_h_
#define _jsonWriter_h_

#pragma once

#include <thirdpart/jsonCPP/include/json.h>

namespace resolver
{

	class jsonWriter
	{
	public:
		typedef enum digitFormat
		{
			digitFormat_Dec				= 0,		//十进制格式             //dotted-decimal format
			digitFormat_Hex_NonHeader	= 1,		//十六进制不带0x标识       //Hexadecimal without  Ox flag 
			digitFormat_Hex_ExistHeader = 2,		//十六进制带0x标识		 //Hexadecimal  with Ox flag
		}digitFormat;

	public:
		jsonWriter();
		virtual ~jsonWriter();

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
		Json::Value* createRoot(const char* name);

		//获取根节点
		//get root node 
		Json::Value* getRoot();

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
		Json::Value* createNode(Json::Value* root, const char* name);

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
		bool setAttribute(Json::Value* element, const char* attribute, const char* value);
		bool setAttribute(Json::Value* element, const char* attribute, long long value, digitFormat format = digitFormat_Dec);

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
		Json::Value* InsertElement(const char* nodeName, const char* value, Json::Value* parent = NULL, bool updateIfExist = false);
		Json::Value* InsertElement(const char* nodeName, long long value, Json::Value* parent = NULL, bool updateIfExist = false, digitFormat format = digitFormat_Dec);
		Json::Value* InsertElementFloat(const char* nodeName, float value, Json::Value* parent = NULL, const char* _format = "%f", bool updateIfExist = false);
		//-------------------------------------------------------------------------------------
		// 功能：追加节点
		// 参数：parent[in]:父亲
		// 返回：成功与否
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		// @function：add node 
		// @parameter：parent[in]:father 
		// @Return：success or not
		//-------------------------------------------------------------------------------------
		
		//sample:追加2个子节点
		//sample:add 2 sub node 
		/*
		Json::Value* aa = writer.createNode(writer.getRoot(), "aa");

		Json::Value* bb = writer.AppendElement(aa);
		writer.InsertElement("file", "aa.bmp", &bb);

		Json::Value* cc = writer.AppendElement(aa);
		writer.InsertElement("file", "bb.bmp", &cc);
		*/
		Json::Value* AppendElement(Json::Value* parent = NULL);

	private:
		Json::Value		m_root;			//根节点          //root node 
	};

};

#endif