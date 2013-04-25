
// marker_extraction2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cmarker_extraction2App:
// See marker_extraction2.cpp for the implementation of this class
//

class Cmarker_extraction2App : public CWinAppEx
{
public:
	Cmarker_extraction2App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cmarker_extraction2App theApp;