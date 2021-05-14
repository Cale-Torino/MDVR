
// DeviceDriverDemo.cpp : ����Ӧ�ó��������Ϊ��
// DeviceDriverDemo.cpp : Defining the class behavior of the application
//

#include "stdafx.h"
#include "DeviceDriverDemo.h"
#include "DeviceDriverDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDeviceDriverDemoApp

BEGIN_MESSAGE_MAP(CDeviceDriverDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDeviceDriverDemoApp ����
// CDeviceDriverDemoApp construction 

CDeviceDriverDemoApp::CDeviceDriverDemoApp()
{
	// ֧����������������
	// support restart manager 
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	
	// TODO: add construction code here 
	// put all the important initialization to InitInstance 
}


// Ψһ��һ�� CDeviceDriverDemoApp ����
// the only CDeviceDriverDemoApp target 

CDeviceDriverDemoApp theApp;


// CDeviceDriverDemoApp ��ʼ��
// CDeviceDriverDemoApp initialization 

BOOL CDeviceDriverDemoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	
	// if a application running on windows XP requires 
	// ComCtl32.dll version 6 or higher version to start the viewable way,
	//it will need " InitCommonControlsEx()", else, could not create windows
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	
	// set it to be public control Ex Which includes all the required application 
	
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	
	// create shell manager, to avoid message windows includes any shell video tree control or any shell video list control 
	
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	// activate ��Windows Native�� view manager, to enable themes in MFC control 
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CDeviceDriverDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	// delete the above created shell manager 
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	// the message windows was closed, so it will return FALSE, to exist the application 
	//  Instead of launching the application message pump
	return FALSE;
}

