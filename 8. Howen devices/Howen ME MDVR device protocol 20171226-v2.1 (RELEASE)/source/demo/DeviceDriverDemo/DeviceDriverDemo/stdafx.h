
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

// stdafx.h : Include only the source file containing the standard include file 
// or ofen used but not ofen changed 
// special include file for specify project 

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����   // exclude Rarely used data from the Windows header
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��    // Some CString constructors will be explicit 

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
// Turn off MFC for some common but often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���       // MFC core components and standard components
#include <afxext.h>         // MFC ��չ         // MFC extension 


#include <afxdisp.h>        // MFC �Զ�����      // MFC automation class



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��   //MFC support for Internet Explorer 4 public controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��       // MFC support for Windows common controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��        // MFC support for functional areas and control strips



#pragma comment(lib,"HowenPlaySDK.lib")
#pragma comment(lib,"DeviceDriverSDK.lib")
#pragma comment(lib,"HowenPlayback.lib")
#pragma comment(lib,"HowenVoice.lib")
#pragma comment(lib,"HowenDecoder.lib")
#pragma comment(lib,"HowenG7xx.lib")

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


