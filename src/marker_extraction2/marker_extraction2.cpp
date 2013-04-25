
// marker_extraction2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "marker_extraction2.h"
#include "marker_extraction2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmarker_extraction2App

BEGIN_MESSAGE_MAP(Cmarker_extraction2App, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cmarker_extraction2App construction

Cmarker_extraction2App::Cmarker_extraction2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cmarker_extraction2App object

Cmarker_extraction2App theApp;


// Cmarker_extraction2App initialization

BOOL Cmarker_extraction2App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	Cmarker_extraction2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
