
#include "stdafx.h"
#include "utils.h"
#include <boost/format.hpp>

//-------------------------------------------------------------------------------------
// 功能：格式化时间
// 参数：buffer[in]:日期数组，每个字节分别对应年月日时分秒，其中年份=当前年份-2000
// 返回：“2017-02-21 11:21:32"格式
//Function:Format time
//Parameter:buffer[in]: date array,YEAR = current year - 2000
//Return:“2017-02-21 11:21:32" format
//---------------------------------------------------------------------------
std::string utils::formatTime(unsigned char* buffer)
{
	boost::format fmtTime("%04d-%02d-%02d %02d:%02d:%02d");
	int year = buffer[0] + 2000;
	int month = buffer[1];
	int day = buffer[2];
	int hour = buffer[3];
	int minute = buffer[4];
	int second = buffer[5];
	fmtTime % year % month % day % hour % minute % second;

	return fmtTime.str().c_str();
}

//-------------------------------------------------------------------------------------
// 功能：转换
// 参数：buffer[in]:缓冲区 bytes[in]:字节数
// 返回：整型
//Function:convert
//Parameter:buffer[in]	bytes[in]
//Return:Int
//------------------------------------------------------------------------------
int utils::transferInteger(char* buffer, int bytes)
{
	int value = 0;
	::memcpy(&value, buffer, bytes);
	return value;
}

//-------------------------------------------------------------------------------------
// 功能：转换
// 参数：buffer[in]:缓冲区		bytes[in]:字节数
// 返回：整型
//Function:convert
//Parameter:buffer[in]	bytes[in]
//Return:Int
//-------------------------------------------------------------------------------------
long long utils::transferLong(char* buffer, int bytes)
{
	long long value = 0;
	::memcpy(&value, buffer, bytes);
	return value;
}

//-------------------------------------------------------------------------------------
// 功能：转换
// 参数：buffer[in]:缓冲区		bytes[in]:字节数	denominator[in]:分母
// 返回：整型
//Function:convert
//Parameter:buffer[in]	bytes[in] denominator[in]
//Return:Int
//-------------------------------------------------------------------------------------
float utils::transferFloat(char* buffer, int bytes,float denominator)
{
	int temp = transferInteger(buffer, bytes);
	float value = temp / denominator;
	return value;
}

//-------------------------------------------------------------------------------------
// 功能：转换为浮点型的度
// 参数：degree[in]:度		minute[in]:分
// 返回：浮点型
//Function:convert degree value to floating type
//Parameter:degree[in] minute[in]
//Return:floating value
//---------------------------------------------------------------------------------
float utils::transferDegree(unsigned char degree, float minute)
{
	minute = minute / 60;
	float value = degree + minute;
	return value;
}

//-------------------------------------------------------------------------------------
// 功能：格式化网络地址
// 参数：address[in]:地址数组
// 返回："192.168.1.5"样式
//Function:Format network address
//Parameter:address[in]:address array
//Return:"192.168.1.5" format
//-------------------------------------------------------------------------------------
std::string utils::formatNetworkAddress(unsigned char* address)
{
	boost::format fmt("%03d.%03d.%03d.%03d");
	int a = address[0];
	int b = address[1];
	int c = address[2];
	int d = address[3];
	fmt % a % b % c % d;

	return fmt.str().c_str();
}

//-------------------------------------------------------------------------------------
// 功能：获取小于256字节的字符串(其中第一字节为长度，包含结束符)
// 参数：buffer[in]:缓冲区 p_length[out]:占用长度
// 返回：字符串
//Function:get string whose length is less than 256bytes(The first byte is the length ,including end character)
//Parameter:buffer[in]	p_length[out]:occupied length
//Return:String
//---------------------------------------------------------------------------------
std::string utils::getLess256String(char* buffer,int* p_length)
{
	char length = buffer[0];
	char* first = &buffer[1];
	char* last = first;
	if(length > 0)
		last = &buffer[length];

	if (NULL != p_length)
	{
		*p_length += 1;
		*p_length += length;
	}
	
	std::string value(first, last);
	return value.c_str();
}

//-------------------------------------------------------------------------------------
// 功能：打印输出
// 参数：fmt[in]:输出内容
// 返回：无
//Function:Print output
//Parameter:fmt[in]
//Return:Null
//---------------------------------------------------------------------------------
void utils::DebugOutput(const char* fmt, ...)
{
	char szMsg[4096] = { 0 };
	va_list args;
	va_start(args, fmt);
	vsnprintf(szMsg, 4096, fmt, args);
	va_end(args);

	OutputDebugStringA(szMsg);
	OutputDebugStringA("\n");
}

//-------------------------------------------------------------------------------------
// 功能：状态数据分析
// 参数：status_buffer[in]:状态数据
// 返回：无
//Function:Status data analysis
//Parameter:status_buffer[in]:status data
//Return:Null
//-------------------------------------------------------------------------------------
void utils::statusAnalyse(char* status_buffer)
{
	int pos = 0;
	char* buffer = status_buffer;

	//设备时间
	//Device time
	std::string dtuTime = utils::formatTime((unsigned char*)&buffer[pos]);
	pos += 6;

	//内容标识字段，2个字节 
	//bit0--位置信息(0:无，1:存在) 
	//bit1--Gsensor(0:无，1:存在)
	//bit2--基础状态(0:无，1:存在)
	//bit3--模块工作状态(0:无，1:存在)
	//bit4--油耗状态(0:无，1:存在)
	//bit5--移动网络状态(0:无，1:存在)
	//bit6--WIFI网络状态(0:无，1:存在)
	//bit7--硬盘状态(0:无，1:存在)
	//bit8--告警状态(0:无，1:存在)
	//bit9--温湿度状态(0:无，1:存在)
	//
    //content flag,2 bytes
	//bit0--location info(0:Null，1:Exist) 
	//bit1--Gsensor(0:Null，1:Exist) 
	//bit2--Basic status(0:Null，1:Exist) 
	//bit3--Module status(0:Null，1:Exist) 
	//bit4--Fuel status(0:Null，1:Exist) 
	//bit5--Mobile network status(0:Null，1:Exist) 
	//bit6--WIFI network status(0:Null，1:Exist) 
	//bit7--Disk status(0:Null，1:Exist) 
	//bit8--Alarm status(0:Null，1:Exist) 
	//bit9--Temperature and humidity status(0:Null，1:Exist) 
	char* contentFlag = buffer + pos;
	pos += 2;


	if (contentFlag[0] & 0x01)
	{//bit0--位置信息(0:无，1:存在)
     
		 //bit0--方向标识，0—0°~180°，1--180°~360°
		 //bit1--经度标识，0--东经，1--西经
		 //bit2--海拔方向，0--高于海平面，1--低于海平面
	//bit0--location info(0:Null，1:Exist)
	     //bit0--Direction flag，0—0°~180°，1--180°~360°
		 //bit1--Longitude flag，0--Longitude east，1--Longitude west
		 //bit2--Altitude direction，0--Above sea level，1--Below sea level
		char flag = buffer[pos];

		//0—定位无效  1--GPS  2--BD  3--Glonass
		//4--AGPS  5--基站定位  6--WIFI
		//0—Invalid  1--GPS  2--BD  3--Glonass
		//4--AGPS  5--LBS  6--WIFI
		char locationMode = buffer[pos + 1];

		//定位模块获取的时间
		//Time generated by location module
		std::string locationTime = utils::formatTime((unsigned char*)&buffer[pos + 2]);

		//方向
		//Direction
		int direct = buffer[pos + 8];
		if (flag & 0x01)
			direct += 180;

		//卫星数量
		//Satellite quantity
		char satellites = buffer[pos + 9];
		//千米/小时
		//KM/H
		float speed = utils::transferFloat(&buffer[pos + 10], 2, 100.);
		//海拔高度,米
		//Altitude,meter
		int altitude = utils::transferInteger(&buffer[pos + 12], 2);                              
		if (flag & 0x04)
			altitude *= -1;
		//定位精度,米
		//positioning accurancy,meter
		int precision = utils::transferInteger(&buffer[pos + 14], 2);
		//经度
		//Longitude
		float longitude = utils::transferDegree(buffer[pos + 16], utils::transferFloat(&buffer[pos + 17], 4, 10000.));
		if (flag & 0x02)
			longitude *= -1;
		//纬度
		//Latitude
		float lagitude = utils::transferDegree(buffer[pos + 21], utils::transferFloat(&buffer[pos + 22], 4, 10000.));

		pos += 26;
	}

	if (contentFlag[0] & 0x02)
	{//bit1--Gsensor(0:无，1:存在)

		 //bit0--xyz加速度(0:数据不存在，1:数据存在)
		 //bit1--倾斜(0: 数据不存在，1:数据存在)
		 //bit2--撞击(0: 数据不存在，1:数据存在)
	 //bit1--Gsensor(0:Null，1:Exist)

		 //bit0--xyz acceleration(0:Null，1:Exist)
		 //bit1--Lean(0:Null，1:Exist)
		 //bit2--Crash(0:Null，1:Exist)
		char flag = buffer[pos];
		pos += 1;

		if (flag & 0x01)
		{//bit0--xyz加速度(0:数据不存在，1:数据存在)
	     //bit0--xyz acceleration(0:Null，1:Exist)
			float x = utils::transferFloat(&buffer[pos], 2, 100.);
			float y = utils::transferFloat(&buffer[pos + 2], 2, 100.);
			float z = utils::transferFloat(&buffer[pos + 4], 2, 100.);
			pos += 6;
		}

		if (flag & 0x02)
		{//bit1--倾斜(0: 数据不存在，1:数据存在)
	     //bit1--Lean(0:Null，1:Exist)
			float tilt = utils::transferFloat(&buffer[pos], 2, 100.);
			pos += 2;
		}

		if (flag & 0x04)
		{//bit2--撞击(0: 数据不存在，1:数据存在)
	     //bit2--Crash(0:Null，1:Exist)
			float hit = utils::transferFloat(&buffer[pos], 2, 100.);
			pos += 2;
		}
	}

	if (contentFlag[0] & 0x04)
	{//bit2--基础状态(0:无，1:存在)
     //bit2--Basic status(0:Null,1:Exist)

		char* flag = &buffer[pos];
		pos += 4;

		//bit0--车钥匙(0 - 无效，1 - 有效)
		//bit1--刹车(0 - 无效，1 - 有效)
		//bit2--左转(0 - 无效，1 - 有效)
		//bit3--右转(0 - 无效，1 - 有效)
		//bit4--前行(0 - 无效，1 - 有效)
		//bit5--后退(0 - 无效，1 - 有效)
		//bit6--左前门(0--关闭，1--打开)
		//bit7--右前门(0--关闭，1--打开)
		
		//bit0--Vehicle Key(0-Invalid,1-Valid)
		//bit1--Brake(0-Invalid,1-Valid)
		//bit2--Turn left(0-Invalid,1-Valid)
		//bit3--Turn right(0-Invalid,1-Valid)
		//bit4--Move on(0-Invalid,1-Valid)
		//bit5--Reverse(0-Invalid,1-Valid)
		//bit6--Left front door(0--Close，1--Open)
		//bit7--Right front door(0--Close，1--Open)
		bool key = (flag[0] & 0x01) ? true : false;
		bool brake = (flag[0] & 0x02) ? true : false;

		//bit0--左中门(0--关闭，1--打开)
		//bit1--右中门(0--关闭，1--打开)
		//bit2--左后门(0--关闭，1--打开)
		//bit3--右后门(0--关闭，1--打开)
		
		//bit0--Left middle door(0--Close，1--Open)
		//bit1--Right middle door(0--Close，1--Open)
		//bit2--Left back door(0--Close，1--Open)
		//bit3--Right back door(0--Close，1--Open)
		bool leftMiddleDoor = (flag[1] & 0x01) ? true : false;
	}

	if (contentFlag[0] & 0x08)
	{//bit3--模块工作状态(0:无，1:存在)

		 //bit0--移动网络(0:数据不存在，1:数据存在)
		 //bit1--定位模块(0:数据不存在，1:数据存在)
		 //bit2--WIFI模块(0:数据不存在，1:数据存在)
		 //bit3--GSensor(0:数据不存在，1:数据存在)
		 //bit4--录像状态(0:数据不存在，1:数据存在)
		 
	 //bit3--Module status(0:Null,1:Exist)

		 //bit0--Mobile network(0:Null,1:Exist)
		 //bit1--Location module(0:Null,1:Exist)
		 //bit2--WIFI module(0:Null,1:Exist)
		 //bit3--GSensor(0:Null,1:Exist)
		 //bit4--Record status(0:Null,1:Exist)
		char* flag = &buffer[pos];
		pos += 2;

		if (flag[0] & 0x01)
		{//bit0--移动网络(0:数据不存在，1:数据存在)
	     //bit0--Mobile network(0:Null,1:Exist)
			char mobileModule = buffer[pos];
			pos += 1;
		}

		if (flag[0] & 0x02)
		{//bit1--定位模块(0:数据不存在，1:数据存在)
	     //bit1--Location module(0:Null,1:Exist)
			char locationModule = buffer[pos];
			pos += 1;
		}

		if (flag[0] & 0x04)
		{//bit2--WIFI模块(0:数据不存在，1:数据存在)
	     //bit2--WIFI module(0:Null,1:Exist)
			char wifiModule = buffer[pos];
			pos += 1;
		}

		if (flag[0] & 0x08)
		{//bit3--GSensor(0:数据不存在，1:数据存在)
	     //bit3--GSensor(0:Null,1:Exist)
			char gsensorModule = buffer[pos];
			pos += 1;
		}

		if (flag[0] & 0x10)
		{//bit4--录像状态(0:数据不存在，1:数据存在)
	     //bit4--Record status(0:Null,1:Exist)
			char* recordStatus = &buffer[pos];
			pos += 2;
			bool chn1 = (recordStatus[0] & 0x01) ? true : false;
			bool chn2 = (recordStatus[0] & 0x02) ? true : false;
		}
	}

	if (contentFlag[0] & 0x10)
	{//bit4--油耗状态(0:无，1:存在)

		 //bit0--油耗(0:数据不存在，1:数据存在)
		 //bit1--剩余油量(0:数据不存在，1:数据存在)
		 
	 //bit4--Fuel status(0:Null，1:Exist)

		 //bit0--Fuel usage(0:Null，1:Exist)
		 //bit1--Remained fuel capacity(0:Null，1:Exist)
		char flag = buffer[pos];
		pos += 1;

		if (flag & 0x01)
		{//bit0--油耗(0:数据不存在，1:数据存在)
	     //bit0--Fuel usage(0:Null，1:Exist)
			float fuelCost = utils::transferFloat(&buffer[pos], 2, 10.);
			pos += 2;
		}

		if (flag & 0x02)
		{//bit1--剩余油量(0:数据不存在，1:数据存在)
	     //bit1--Remained fuel capacity(0:Null，1:Exist)
			int fuelFree = utils::transferInteger(&buffer[pos], 2);
			pos += 2;
		}
	}

	if (contentFlag[0] & 0x20)
	{//bit5--移动网络状态(0:无，1:存在)
     //bit5--Monile network status(0:Null,1:Exist)

	 //标识位，保留
	 //flag,reserved
		char flag = buffer[pos];
		pos += 1;

		//信号强度
		//Signal strength
		char strength = buffer[pos];
		pos += 1;

		//网络类型
		//Network type
		char adapter = buffer[pos];
		pos += 1;

		//保留
		//Reserved
		char* reserved = &buffer[pos];
		pos += 2;
	}

	if (contentFlag[0] & 0x40)
	{//bit6--WIFI网络状态(0:无，1:存在)

		 //bit0--信号强度(0:数据无效，1:数据有效)
		 //bit1--网络地址(0:数据无效，1:数据有效)
		 //bit2--网关(0:数据无效，1:数据有效)
		 //bit3--子网掩码(0:数据无效，1:数据有效)
		 //bit4--SSID(0:数据无效，1:数据有效)
		 
	 //bit6--WIFI network status(0:Null,1:Exist)

		 //bit0--Signal strength(0:Invalid,1:Valid)
		 //bit1--Network address(0:Invalid,1:Valid)
		 //bit2--Gateway(0:Invalid,1:Valid)
		 //bit3--Network mask(0:Invalid,1:Valid)
		 //bit4--SSID(0:Invalid,1:Valid)
		char flag = buffer[pos];
		pos += 1;

		if (flag & 0x01)
		{//bit0--信号强度(0:数据无效，1:数据有效)
	     //bit0--Signal strength(0:Invalid,1:Valid)
			char strength = buffer[pos];
			pos += 1;
		}

		if (flag & 0x02)
		{//bit1--网络地址(0:数据无效，1:数据有效)
	     //bit1--Network address(0:Invalid,1:Valid)
			std::string address = utils::formatNetworkAddress((unsigned char*)&buffer[pos]);
			pos += 4;
		}

		if (flag & 0x04)
		{//bit2--网关(0:数据无效，1:数据有效)
	     //bit2--Gateway(0:Invalid,1:Valid)
			std::string gateway = utils::formatNetworkAddress((unsigned char*)&buffer[pos]);
			pos += 4;
		}

		if (flag & 0x08)
		{//bit3--子网掩码(0:数据无效，1:数据有效)
	     //bit3--Network mask(0:Invalid,1:Valid)
			std::string subNet = utils::formatNetworkAddress((unsigned char*)&buffer[pos]);
			pos += 4;
		}

		if (flag & 0x10)
		{//bit4--SSID(0:数据无效，1:数据有效)
	     //bit4--SSID(0:Invalid,1:Valid)
			std::string ssid = utils::getLess256String(&buffer[pos], &pos);
		}
	}

	if (contentFlag[0] & 0x80)
	{//bit7--硬盘状态(0:无，1:存在)
     //bit7--Disk status(0:Null,1:Exist)

		 //每一位对应一组硬盘状态，(0:数据无效，1:数据有效)
		 //Every bit is related with a disk status(0:Invalid,1:Valid)
		char flag = buffer[pos];
		pos += 1;

		for (int i = 0; i < 8; ++i)
		{
			if (!((flag >> i) & 0x01))
				continue;

			//编号
			//Index ID
			char index = buffer[pos];
			pos += 1;

			//磁盘状态	0--未知  1--录像中  2--空闲  3--异常  4--磁盘满
			//Disk status 0--Unknown 1--In recording 2--Standby 3--Abnormal 4--Disk full
			char status = buffer[pos];
			pos += 1;

			//大小(兆）
			//Capacity(MB)
			int totalMegaBytes = utils::transferInteger(&buffer[pos], 4);
			pos += 4;

			//余量(兆）
			//Free space(MB)
			int freeMegaBytes = utils::transferInteger(&buffer[pos], 4);
			pos += 4;
		}
	}

	if (contentFlag[1] & 0x01)
	{//bit8--告警状态(0:无，1:存在)

		//bit0--视频丢失(0:数据无效，1:数据有效)
		//bit1--移动侦测(0:数据无效，1:数据有效)
		//bit2--视频遮挡(0:数据无效，1:数据有效)
		//bit3--输入告警(0:数据无效，1:数据有效)
		//bit4--超速告警(0 - 未触发，1 - 触发)
		//bit5--低速告警(0 - 未触发，1 - 触发)
		//bit6--紧急告警(0 - 未触发，1 - 触发)
		//bit7--超时停车(0 - 未触发，1 - 触发)
		//bit8--震动告警(0 - 未触发，1 - 触发)
		//bit9--越界告警(0 - 未触发，1 - 触发)
		//bit10--入界告警(0 - 未触发，1 - 触发)
		//bit11--越线告警(0 - 未触发，1 - 触发)
		//bit12--入线告警(0 - 未触发，1 - 触发)
		//bit13--油量告警(0 - 未触发，1 - 触发)
		
	 //bit8--Alarm status(0:Null,1:Exist)
		//bit0--VideoLoss(0:Invalid,1:Valid)
		//bit1--VideoMotion(0:Invalid,1:Valid)
		//bit2--VideoCover(0:Invalid,1:Valid)
		//bit3--SensorInputAlarm(0:Invalid,1:Valid)
		//bit4--OverspeedAlarm(0-Not triggered，1-Triggered)
		//bit5--LowSpeedAlarm(0-Not triggered，1-Triggered)
		//bit6--EmergencyAlarm(0-Not triggered，1-Triggered)
		//bit7--ParkingTimeoutAlarm(0-Not triggered，1-Triggered)
		//bit8--ShockAlarm(0-Not triggered，1-Triggered)
		//bit9--Get out border alarm(0-Not triggered，1-Triggered)
		//bit10--Get in border alarm(0-Not triggered，1-Triggered)
		//bit11--Get out line alarm(0-Not triggered，1-Triggered)
		//bit12--Get in line alarm(0-Not triggered，1-Triggered)
		//bit13--Fuel alarm(0-Not triggered，1-Triggered)
		char* flag = &buffer[pos];
		pos += 4;

		if (flag[0] & 0x01)
		{//bit0--视频丢失(0:数据无效，1:数据有效)
	     //bit0--VideoLoss(0:Invalid,1:Valid)
			char* flag = &buffer[pos];
			pos += 2;

			bool chn1Lost = (flag[0] & 0x01) ? true : false;
			bool chn2Lost = (flag[0] & 0x02) ? true : false;
		}

		if (flag[0] & 0x02)
		{//bit1--移动侦测(0:数据无效，1:数据有效)
	     //bit1--VideoMotion(0:Invalid,1:Valid)
			char* flag = &buffer[pos];
			pos += 2;

			bool chn1Lost = (flag[0] & 0x01) ? true : false;
			bool chn2Lost = (flag[0] & 0x02) ? true : false;
		}

		if (flag[0] & 0x04)
		{//bit2--视频遮挡(0:数据无效，1:数据有效)
	     //bit2--VideoCover(0:Invalid,1:Valid)
			char* flag = &buffer[pos];
			pos += 2;

			bool chn1Mask = (flag[0] & 0x01) ? true : false;
			bool chn2Mask = (flag[0] & 0x02) ? true : false;
		}

		if (flag[0] & 0x08)
		{//bit3--输入告警(0:数据无效，1:数据有效)
	     //bit3--SensorInputAlarm(0:Invalid,1:Valid)
			char* flag = &buffer[pos];
			pos += 2;

			bool input1Trigger = (flag[0] & 0x01) ? true : false;
			bool input2Trigger = (flag[0] & 0x02) ? true : false;
		}

		//bit4--超速告警(0 - 未触发，1 - 触发)
		//bit4--OverspeedAlarm(0-Not triggered，1-Triggered)
		
		bool overSpeed = (flag[0] & 0x10) ? true : false;
		//bit5--低速告警(0 - 未触发，1 - 触发)
		//bit5--LowSpeedAlarm(0-Not triggered，1-Triggered)
		
		bool lowSpeed = (flag[0] & 0x20) ? true : false;
		//bit6--紧急告警(0 - 未触发，1 - 触发)
		//bit6--EmergencyAlarm(0-Not triggered，1-Triggered)
		
		bool urgency = (flag[0] & 0x20) ? true : false;
	}

	if (contentFlag[1] & 0x02)
	{//bit9--温湿度状态(0:无，1:存在)

		 //bit0--车内温度(0:数据无效，1:数据有效)
		 //bit1--车外温度(0:数据无效，1:数据有效)
		 //bit2--发动机温度(0:数据无效，1:数据有效)
		 //bit3--设备温度(0:数据无效，1:数据有效)
		 //bit4--车内湿度(0:数据无效，1:数据有效)
		 //bit5--车外湿度(0:数据无效，1:数据有效)
		 
	 //bit9----Temperature and humidity status(0:Null,1:Exist)

		 //bit0--Temperature in the vehicle(0:Null,1:Exist)
		 //bit1--Temperature outside the vehicle(0:Null,1:Exist)
		 //bit2--Temperature of engine(0:Null,1:Exist)
		 //bit3--Temperature of Device(0:Null,1:Exist)
		 //bit4--Humidity in the vehicle(0:Null,1:Exist)
		 //bit5--Humidity outside the vehicle(0:Null,1:Exist)
		char* flag = &buffer[pos];
		pos += 2;

		if (flag[0] & 0x01)
		{//bit0--车内温度(0:数据无效，1:数据有效)
	     //bit0--Temperature in the vehicle(0:Null,1:Exist)
			float indoorTemperature = utils::transferFloat(&buffer[pos], 2, 100.);
			pos += 2;
		}

		if (flag[0] & 0x02)
		{//bit1--车外温度(0:数据无效，1:数据有效)
	     //bit1--Temperature outside the vehicle(0:Null,1:Exist)
			float outdoorTemperature = utils::transferFloat(&buffer[pos], 2, 100.);
			pos += 2;
		}

		if (flag[0] & 0x04)
		{//bit2--发动机温度(0:数据无效，1:数据有效)
	     //bit2--Temperature of engine(0:Null,1:Exist)
			float engineerTemperature = utils::transferFloat(&buffer[pos], 2, 100.);
			pos += 2;
		}

		if (flag[0] & 0x04)
		{//bit3--设备温度(0:数据无效，1:数据有效)
	     //bit3--temperature of Device(0:Null,1:Exist)
			float deviceTemperature = utils::transferFloat(&buffer[pos], 2, 100.);
			pos += 2;
		}

		if (flag[0] & 0x08)
		{//bit4--车内湿度(0:数据无效，1:数据有效)
	     //bit4--Humidity in the vehicle(0:Null,1:Exist)
			char insideHumidity = buffer[pos];
			pos += 1;
		}

		if (flag[0] & 0x10)
		{//bit5--车外湿度(0:数据无效，1:数据有效)
	     //bit5--Humidity outside the vehicle(0:Null,1:Exist)
			char insideHumidity = buffer[pos];
			pos += 1;
		}
	}
}