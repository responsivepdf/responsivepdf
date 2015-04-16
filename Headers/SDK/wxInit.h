#ifndef __WXINIT__
#define __WXINIT__

#include "wx/init.h"
#include "wx/app.h"
#include "wx/frame.h"
#ifdef MAC_PLATFORM
#include "wx/cocoa/ObjcPose.h"
#endif

// Define a new application type
class PluginApp: public wxApp
{
public:
    bool OnInit();
    DECLARE_EVENT_TABLE()
};

class AcrobatFrame : public wxFrame
{
	public:
		AcrobatFrame();
	private:
		DECLARE_EVENT_TABLE()
};
#ifdef MAC_PLATFORM
//without this, Acrobat crashes, I think based on deleting something it shouldn't
class myPoseAsInitializer : public wxPoseAsInitializer
{
public:
    myPoseAsInitializer()
    {
        m_next = NULL;
    }
};
#endif
extern AcrobatFrame* mainFrame;

#endif