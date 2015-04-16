/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1995-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 UnixCalls.h

 ******************************************************************************************
                        **** Instructions for Plugin Developers **** 
   (In the instructions below ~ is used to refer to the HFT this file is for.  For
     example, this file would be called "~Calls.h")
  
   To use this file you must declare two global variables: g~HFT and g~Version.  You can
   see them declared as extern about one page down from here.  Your plugin should set a 
   #define of PI_~_VERSION to some non zero value.  Suggested values are given below in
   the "for public use" section.  ~HFT_LATEST_VERSION is not recommended because you will 
   not be able to support backwards compatible versions.  It is recommended that you use the lowest 
   ~HFT_VERSION you require.  Later versions are compatible with earlier versions, so if 
   you require ~HFT_VERSION_4, your plugin will work with ~HFT_VERSION_5, ~HFT_VERSION_6, and so on.
  
   You can support old versions and still use newer versions of this HFT by checking the 
   value of g~Version.  If you use the standard PiMain.c supplied in the SDK, this will be
   set to the actual version of the HFT returned to you (For example, if you require version 4,
   you are returned version 7, which is compatible, and g~Version is set to 7).  You can write
   code that looks something like this:
     if (g~Version >= ~HFT_VERSION_5) 
        CallNewSpeedyCode();
     else {
        assert(g~Version >= ~HFT_VERSION_4);  //PI_~_VERSION was defined as ~HFT_VERSION_4
        CallOldSlowCode();
     }
 ******************************************************************************************
                         **** Instructions for HFT Developer **** 
   (In the instructions below ~ is used to refer to the HFT this file is for.  For
     example, this file would be called "~Calls.h")

   Important: routines that have been released can never be deleted or changed.
   If you want to make a new version, create a new call, add it to the end of this file and
   increment _~_LATEST_VERSION (note the leading underscore).  
   
   If this is the first new routine in a new version, change the _~_IS_BETA flag
   to 1.  Next, create a new ~_VERSION_# for plugins to use and set it to 
   ~HFT_LATEST_VERSION.  For example, suppose the last release of Acrobat was version 20, version 21
   is under development, and you add a new routine for version 21.  Increment _~HFT_LATEST_VERSION 
   to 0x00200001 and set _~_IS_BETA to 1.  Add "#define ~HFT_VERSION_21 ~HFT_LATEST_VERSION".  
   Add your routine and assert that g~Version >= ~HFT_VERSION_21.  Leave 
   _~_LAST_BETA_COMPATIBLE_VERSION unchanged (0x00200000 in this example).

   If the ~_IS_BETA flag is set to 1, you may change or delete the beta routines at will.
   Before checking in the modifications, however, increment the _~HFT_LATEST_VERSION number.
   If the change is not compatible (delete, change, and so on) set _~_LAST_BETA_COMPATIBLE_VERSION equal
   to the new _~HFT_LATEST_VERSION.  If the change is compatible, leave the LAST_BETA version
   as is.

   Plugins that require a BETA HFT will be refused unless they ask for a beta version greater than or equal to
   (>=) LAST_BETA_COMPATIBLE_VERSION and less than or equal to (<=) HFT_LATEST_VERSION.
   By incrementing the version number, you ensure the plugin will refuse to load until it
   has been recompiled with your changes.  You also ensure plugins compiled with your changes
   will not load on older versions of Acrobat.  In other words, it makes sure both sides are in sync.  

   Important: Whenever you make a change to this file, you must increment _~HFT_LATEST_VERSION.
  
   Once the product reaches RC or a similar milestone, change the _~_IS_BETA flag to 0, jump
   the _~HFT_LATEST_VERSION to the final version (0x00210000 in our example), do the same for
   _~_LAST_BETA_COMPATIBLE_VERSION, and set the 
   ~HFT_VERSION_# to the final version number (0x00210000 in this example).  Once the HFT
   has left beta, the routines cannot be changed and a new beta must ensue (beta for version
   22 in this example).

*********************************************************************/

#ifndef _H_UnixCalls
#define _H_UnixCalls

#include "acroassert.h"

/* for Adobe use only */
#define _UnixHFT_LATEST_VERSION 0x00080000
#define _UnixHFT_IS_BETA 0

/* for public use */
#define UnixHFT_LATEST_VERSION (_UnixHFT_IS_BETA ? (kHFT_IN_BETA_FLAG | _UnixHFT_LATEST_VERSION) : _UnixHFT_LATEST_VERSION)

#define UnixHFT_VERSION_4   0x00040000
#define UnixHFT_VERSION_5   0x00040001
#define UnixHFT_VERSION_8   0x00080000

#include <X11/Intrinsic.h>
#include <gtk/gtk.h>

#include "PIRequir.h"
#include "CoreExpT.h" /* HFT */
#include "AVUIExpT.h"

#ifdef __cplusplus
extern "C" {
#endif

#if PI_UNIX_VERSION != 0

extern HFT gUnixHFT;
extern ASUns32 gUnixVersion;

/* UnixAppGetAppShellWidget */
#define UnixAppGetAppShellWidgetSEL 1

/**
	Not supported due to movement to Gtk. If you wanted this for a dialog, ADM is the preferred way now. 
	@see UnixAppGetAppShellGtkWidget
*/
typedef ACCBPROTO1 Widget (ACCBPROTO2 *UnixAppGetAppShellWidgetSELPROTO)
	(void);
#define UnixAppGetAppShellWidget (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppGetAppShellWidgetSELPROTO)(gUnixHFT[1])))

/* UnixAppLoadPlugInAppDefaults */
#define UnixAppLoadPlugInAppDefaultsSEL 2

/**
	Not Supported. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixAppLoadPlugInAppDefaultsSELPROTO)
        (String className, String *fallbackResources);
#define UnixAppLoadPlugInAppDefaults (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppLoadPlugInAppDefaultsSELPROTO)(gUnixHFT[2])))

/* UnixAppClipboardGetItemId */
#define UnixAppClipboardGetItemIdSEL 3

/**
	Not supported. If you wanted this for the selection server Gtk is the preferred way.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 long (ACCBPROTO2 *UnixAppClipboardGetItemIdSELPROTO)
	(Display **displayPtr, Window *windowPtr);
#define UnixAppClipboardGetItemId (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppClipboardGetItemIdSELPROTO)(gUnixHFT[3])))

/* UnixAppDispatchEvent */
#define UnixAppDispatchEventSEL 4

/**
	Not supported. Not required with Gtk. Try <code>gtk_main</code>, or better still, <code>g_main_context_iteration(NULL, FALSE)</code>.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 Boolean (ACCBPROTO2 *UnixAppDispatchEventSELPROTO)
	(XEvent *eventPtr);
#define UnixAppDispatchEvent (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppDispatchEventSELPROTO)(gUnixHFT[4])))

/* UnixAppProcessEvent */
#define UnixAppProcessEventSEL 5

/**
	Not supported. Not required with Gtk. Try <code>gtk_main</code>, or better still, <code>g_main_context_iteration(NULL, FALSE)</code>.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixAppProcessEventSELPROTO)
	(XtAppContext appContext, XtInputMask mask);
#define UnixAppProcessEvent (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppProcessEventSELPROTO)(gUnixHFT[5])))

/* UnixAppWaitForWm */
#define UnixAppWaitForWmSEL 6

/**
	Not supported. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixAppWaitForWmSELPROTO)
	(Widget shellWidget);
#define UnixAppWaitForWm (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppWaitForWmSELPROTO)(gUnixHFT[6])))

/* UnixAppGetPlugInFilename */
#define UnixAppGetPlugInFilenameSEL 7

/**
	Gets the plug-in's file name. The directory can be used to 
	find auxiliary files for that plug-in. 

	<p>The Acrobat viewer searches all the directories specified 
	in the <code>systemPlugInPath</code> and <code>userPlugInPath</code> resources to 
	find plug-ins. </p>

	@param thePI IN/OUT The gExtensionID extension registering the 
	plug-in. 
	@return The plug-in's file name. The string returned must not be 
	altered or freed. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixAppGetPlugInFilenameSELPROTO)
	(ExtensionID thePI);
#define UnixAppGetPlugInFilename (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppGetPlugInFilenameSELPROTO)(gUnixHFT[7])))

/* UnixSysGetHomeDirectory */
#define UnixSysGetHomeDirectorySEL 8

/**
	Gets the home directory of the user running the Acrobat 
	viewer. If the <code>HOME</code> environment variable is set, its value 
	is returned. Otherwise the method looks in the <code>passwd</code> database. 
	
	@return The user's home directory. The string returned by this method 
	must not be altered or freed. 
	@see UnixSysGetCwd 
	@see UnixSysGetHostname 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetHomeDirectorySELPROTO)
	(void);
#define UnixSysGetHomeDirectory (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetHomeDirectorySELPROTO)(gUnixHFT[8])))

/* UnixSysGetInstallDirectory */
#define UnixSysGetInstallDirectorySEL 9

/**
	Gets the directory in which the Acrobat viewer is installed. 
	The launch shell script sets the installation directory 
	in the environment variable <code>ACRO_INSTALL_DIR</code>. 

	<p>Auxiliary files can be found by concatenating the installation 
	directory with the configuration name sub-directory: </p>

	<p><code>"< installation_dir>/< config_name>" </code></p>

	@return The Acrobat viewer's installation directory. 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetInstallDirectorySELPROTO)
	(void);
#define UnixSysGetInstallDirectory (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetInstallDirectorySELPROTO)(gUnixHFT[9])))

/* UnixSysGetConfigName */
#define UnixSysGetConfigNameSEL 10

/**
	Gets the Acrobat viewer's configuration name. 
	
	<p>The name will be one of the following:</p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Configuration name</TH></TR>
	<TR><TD>SunOS</TD><TD><code>sparcsun</code></TD></TR>
	<TR><TD>Solaris</TD><TD><code>sparcsolaris</code></TD></TR>
	<TR><TD>HP-UX</TD><TD><code>hppahpux</code></TD></TR>
	<TR><TD>Linux</TD><TD><code>intellinux</code></TD></TR>
	<TR><TD>IBM AIX</TD><TD><code>rs6000aix</code></TD></TR>
	</TABLE>

	<p>Auxiliary files can be found by concatenating the installation 
	directory with the configuration name sub-directory: </p>

	<p><code>"< installation_dir>/< config_name>" </code></p>

	@return The Acrobat viewer's configuration name. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetConfigNameSELPROTO)
	(void);
#define UnixSysGetConfigName (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetConfigNameSELPROTO)(gUnixHFT[10])))

/* UnixSysGetHostname */
#define UnixSysGetHostnameSEL 11

/**
	Gets the host name. 
	@return The host name. 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetHostnameSELPROTO)
	(void);
#define UnixSysGetHostname (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetHostnameSELPROTO)(gUnixHFT[11])))

/* UnixSysGetTempFileDirectory */
#define UnixSysGetTempFileDirectorySEL 12

/**
	Gets the temporary file directory specified by the user. 
	The default is <code>"/tmp"</code>. 
	@return The temporary file directory. 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetTempFileDirectorySELPROTO)
	(void);
#define UnixSysGetTempFileDirectory (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetTempFileDirectorySELPROTO)(gUnixHFT[12])))

/* UnixSysGetCwd */
#define UnixSysGetCwdSEL 13

/**
	Gets the current working directory. This method tries to 
	eliminate <code>automounter tmp</code> directories and symbol links. 
	Using <code>stat</code>, it checks if the environment variable <code>PWD</code> specifies 
	the same directory returned by <code>getcwd</code>. 
	@return The current working directory. 
	@exception genErrNoMemory 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetCwdSELPROTO)
	(void);
#define UnixSysGetCwd (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetCwdSELPROTO)(gUnixHFT[13])))

/* UnixSysGetString */
#define UnixSysGetStringSEL 14

/**
	Not supported. The strings can be handled as resources.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 char * (ACCBPROTO2 *UnixSysGetStringSELPROTO)
	(Widget widget, char *resourceName, char *defaultString);
#define UnixSysGetString (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetStringSELPROTO)(gUnixHFT[14])))

/* UnixSysGetCursor */
#define UnixSysGetCursorSEL 15

/**
	Not supported. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 Cursor (ACCBPROTO2 *UnixSysGetCursorSELPROTO)
	(Widget widget, char *resourceName, char *defaultName, char *defaultBits, char *defaultMaskBits, unsigned int defaultWidth, unsigned int defaultHeight, int defaultHotX, int defaultHotY);
#define UnixSysGetCursor (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetCursorSELPROTO)(gUnixHFT[15])))

/* UnixSysGetIcon */
#define UnixSysGetIconSEL 16

/**
	Not supported. The Icons should be bundled as a resource.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 Pixmap (ACCBPROTO2 *UnixSysGetIconSELPROTO)
	(Widget widget, char *resourceName, char *defaultName, char *defaultBits, unsigned int defaultWidth, unsigned int defaultHeight);
#define UnixSysGetIcon (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetIconSELPROTO)(gUnixHFT[16])))

/* UnixSysGetPixmap */
#define UnixSysGetPixmapSEL 17

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 Pixmap (ACCBPROTO2 *UnixSysGetPixmapSELPROTO)
	(Widget widget, char *resourceName, char *defaultFilename, char **defaultXpmData, int defaultXpmDataCount, unsigned int *widthPtr, unsigned int *heightPtr);
#define UnixSysGetPixmap (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysGetPixmapSELPROTO)(gUnixHFT[17])))

/* UnixAppAddModifierCallback */
#define UnixAppAddModifierCallbackSEL 18
/*
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixAppAddModifierCallbackSELPROTO)
	(XtCallbackProc callback, XtPointer closure);
#define UnixAppAddModifierCallback (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppAddModifierCallbackSELPROTO)(gUnixHFT[18])))

/* UnixAppRemoveModifierCallback */
#define UnixAppRemoveModifierCallbackSEL 19

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixAppRemoveModifierCallbackSELPROTO)
	(XtCallbackProc callback, XtPointer closure);
#define UnixAppRemoveModifierCallback (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixAppRemoveModifierCallbackSELPROTO)(gUnixHFT[19])))

/* UnixSysPrefInit */
#define UnixSysPrefInitSEL 20

/**
	Not supported
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixSysPrefInitSELPROTO)
	(Widget widget, String name, String Xclass, char *prefFilename, XtResourceList resources, Cardinal numResources, XtPointer base, XrmDatabase *dbPtr, void **resourceDataPtr);
#define UnixSysPrefInit (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysPrefInitSELPROTO)(gUnixHFT[20])))

/* UnixSysPrefUpdate */
#define UnixSysPrefUpdateSEL 21

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *UnixSysPrefUpdateSELPROTO)
	(Widget widget, char *prefFilename, XtPointer base, XtResourceList resources, Cardinal numResources, void *resourceData);
#define UnixSysPrefUpdate (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_4), *((UnixSysPrefUpdateSELPROTO)(gUnixHFT[21])))

/* UnixAppGetAppShellGtkWidget */
#define UnixAppGetAppShellGtkWidgetSEL 22

/**
	Gets the topmost widget of the application. The window is of the type GtkWindow.
	@return The Acrobat viewer's application shell widget. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 GtkWidget * (ACCBPROTO2 *UnixAppGetAppShellGtkWidgetSELPROTO)
	(void);
#define UnixAppGetAppShellGtkWidget (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_5), *((UnixAppGetAppShellGtkWidgetSELPROTO)(gUnixHFT[22])))

/**
        Retrieves an appropriate top-level parent window, from which a modal dialog can be parented.
        @param avdoc IN The currently active document if known. It can be <code>NULL</code>.
        @return An appropriate parent will be determined and returned. This will be a top-level GTK window.
*/
typedef ACCBPROTO1 GtkWidget * (ACCBPROTO2 *UnixAppGetModalParentSELPROTO) (AVDoc avdoc);
#define UnixAppGetModalParent (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_8), *((UnixAppGetModalParentSELPROTO)(gUnixHFT[23])))

/**
        Returns an appropriate top-level parent window, from which a dialog can be parented.
        @return An appropriate parent will be determined and returned. This will be a top-level GTK window.
*/
typedef ACCBPROTO1 GtkWidget * (ACCBPROTO2 *UnixAppGetModelessParentSELPROTO) (void);
#define UnixAppGetModelessParent (ACROASSERT(gUnixVersion >=UnixHFT_VERSION_8), *((UnixAppGetModelessParentSELPROTO)(gUnixHFT[24])))

/* If you add, delete, or modify procs listed in this file please read the instructions at the top about how to properly change the version number */
#endif /* PI_UNIX_VERSION != 0 */

#ifdef __cplusplus
}
#endif

#endif /* !defined(_H_UnixCalls) */

