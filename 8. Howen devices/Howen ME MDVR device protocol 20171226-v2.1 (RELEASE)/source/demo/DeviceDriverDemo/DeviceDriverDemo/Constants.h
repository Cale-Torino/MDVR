
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <info@howentech.com>
日期: 2017年04月19日
描述: 常量定义
历史:
1、2017年04月19日 初步创建
使用说明:
*/


/*
Copy right (c) 2017-2018  Howen Technologies Co., Ltd
V 1.0
Developer: Justin <info@howentech.com>
Date: 2017.04.19
Description: Constant definition  
History:
1,20170419:initial establish 
instruction:
*/

#ifndef _Constants_h_
#define _Constants_h_

#pragma once

namespace constants
{
	//设备状态更新消息通知
	//notify device status updated message
	const UINT	device_status_update = WM_USER + 0x0001;

	//设备录像信息内容消息通知
	//notify device record file detail
	const UINT	device_record_file_detail = WM_USER + 0x0002;
}

#endif

