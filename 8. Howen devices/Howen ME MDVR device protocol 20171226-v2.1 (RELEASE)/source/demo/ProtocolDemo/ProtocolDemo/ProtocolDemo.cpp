
// ProtocolDemo.cpp : 定义应用程序的类行为。// ProtocolDemo.cpp :Define the Class behavior 
//

#include "stdafx.h"
#include "ProtocolDemo.h"
#include "ProtocolDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProtocolDemoApp

BEGIN_MESSAGE_MAP(CProtocolDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CProtocolDemoApp 构造 //CProtocolDemoApp Constructor

CProtocolDemoApp::CProtocolDemoApp()
{
	// 支持重新启动管理器  //Supprot Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，  //Add constructor code here
	// 将所有重要的初始化放置在 InitInstance 中  //Put all important initilizations in InitInstance 
}


// 唯一的一个 CProtocolDemoApp 对象  //Unique CProtocolDemoApp object

CProtocolDemoApp theApp;


// CProtocolDemoApp 初始化    //CProtocolDemoApp Initialization

BOOL CProtocolDemoApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	//If a program list running on Windows XP requires to use ComCtl32.dll version6 or higher to enable visual mode,it will need to use InitCommonControlsEx(). It cannot create the window without it.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	//Set it to include all the common controls 
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	//Create shell manager to avoid dialog containing any shell tree view control or shell list view //control
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	//Activate "Windows Native" visual state manager to enable theme in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化  //Standard initialization
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//If you don't use these functions and want to reduce the size of final generated exe file,please //remove the unnecessary special initialization instances and change the registery items for storage //config. 
	//TODO:Change the string properly. 
	//E.g. Change it to Company name or organization name.
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	//SetRegistryKey(_T("Local program generated by program wizard"));

	CProtocolDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
		//TODO:Put the code of when to close the dialog after "Yes" confirm.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
		//TODO:Put the code of when to close the dialog after "Cancel" confirm
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		//TRACE(traceAppMsg, 0, "Warn: Create dialog fail. Program will stop unexpectedly \n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
		//TRACE(traceAppMsg, 0, "Warn: If you use MFC control in dialog,you cannot#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	//Delete created shell manager above
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	//The dailog is closed, so it will return FALSE to exit the program other than start the message pump
	return FALSE;
}

