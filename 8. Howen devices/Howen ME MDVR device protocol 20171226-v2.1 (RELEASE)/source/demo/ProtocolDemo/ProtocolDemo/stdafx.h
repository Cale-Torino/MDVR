
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently
#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            
// 从 Windows 头中排除极少使用的资料 
//Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
// 某些 CString 构造函数将是显式的
//Some CString constructors will be explicit


// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
//turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件  // MFC core and standard components
#include <afxext.h>         // MFC 扩展  //MFC extensions


#include <afxdisp.h>        // MFC 自动化类  //MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>          
 // MFC 对 Internet Explorer 4 公共控件的支持
// MFC support for Internet Explorer 4 Common Controls 
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             
// MFC 对 Windows 公共控件的支持  
// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     
// 功能区和控件条的 MFC 支持
//MFC support for function area and controlbar

#ifdef _DEBUG

	#pragma comment(lib,"hw_basicD.lib")

#else

	#pragma comment(lib,"hw_basic.lib")

#endif


#pragma comment(lib,"HowenPlaySDK.lib")


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


