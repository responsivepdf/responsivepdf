/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 2008 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 wxInit.cpp

 - Initialization code for wxWidgets.

*********************************************************************/
#include "wx/app.h"
#include "wxInit.h"
#include "PIMain.h"

IMPLEMENT_APP_NO_MAIN(PluginApp)

wxPoint offscreenPoint(-5000,-5000);

bool PluginApp::OnInit()
{
    return true;
}


BEGIN_EVENT_TABLE(PluginApp, wxApp)
	END_EVENT_TABLE()

AcrobatFrame::AcrobatFrame() : wxFrame(NULL, -1, "", offscreenPoint)
{
#ifdef WIN_PLATFORM
	HWND oldHWnd = (HWND)GetHandle();
	SetHWND((WXHWND)gHWND);
	if(oldHWnd)
		::DestroyWindow(oldHWnd);
#endif
}


BEGIN_EVENT_TABLE(AcrobatFrame, wxFrame)
	END_EVENT_TABLE()



