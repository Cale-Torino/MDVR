
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently
#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            
// �� Windows ͷ���ų�����ʹ�õ����� 
//Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
// ĳЩ CString ���캯��������ʽ��
//Some CString constructors will be explicit


// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
//turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���  // MFC core and standard components
#include <afxext.h>         // MFC ��չ  //MFC extensions


#include <afxdisp.h>        // MFC �Զ�����  //MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>          
 // MFC �� Internet Explorer 4 �����ؼ���֧��
// MFC support for Internet Explorer 4 Common Controls 
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             
// MFC �� Windows �����ؼ���֧��  
// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     
// �������Ϳؼ����� MFC ֧��
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


