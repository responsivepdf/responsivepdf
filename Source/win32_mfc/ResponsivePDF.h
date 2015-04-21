// ResponsivePDF.h : main header file for the ResponsivePDF DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CResponsivePDFApp
// See ResponsivePDF.cpp for the implementation of this class
//

class CResponsivePDFApp : public CWinApp
{
public:
	CResponsivePDFApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
