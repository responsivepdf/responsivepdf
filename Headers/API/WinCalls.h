/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1994-2007 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 WinCalls.h

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
#ifndef _H_WinCalls
#define _H_WinCalls

#include "acroassert.h"

/* for Adobe use only */
#define _WINHFT_LATEST_VERSION 0x00090000
#define _WINHFT_IS_BETA 0

/* for public use */
#define WINHFT_LATEST_VERSION (_WINHFT_IS_BETA ? (kHFT_IN_BETA_FLAG | _WINHFT_LATEST_VERSION) : _WINHFT_LATEST_VERSION)

#define WINHFT_VERSION_4   0x00040000
#define WINHFT_VERSION_5   0x00050000
#define WINHFT_VERSION_8   0x00080000
#define WINHFT_VERSION_9   WINHFT_LATEST_VERSION

#ifdef __cplusplus
extern "C" {
#endif

#include "WinExpT.h"

#if PI_WIN_VERSION != 0

#include <windows.h>

extern HFT gWinHFT;
extern ASUns32 gWinVersion;

#define WinAppRegisterModelessDialogSEL 1

/**
	(Windows only) Registers modeless dialogs with the viewer 
	so that the dialog gets the correct messages. 
	@param dialog IN/OUT The <code>HWND</code> for the dialog to register. 
	@see WinAppUnRegisterModelessDialog 
	@since PI_WIN_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *WinAppRegisterModelessDialogSELPROTO)
	(HWND dialog);
#define WinAppRegisterModelessDialog (ACROASSERT(gWinVersion >=WINHFT_VERSION_4), *((WinAppRegisterModelessDialogSELPROTO)(gWinHFT[WinAppRegisterModelessDialogSEL])))

#define WinAppUnRegisterModelessDialogSEL 2

/**
	(Windows only) Un-registers modeless dialogs with the viewer. 
	
	@param dialog IN/OUT The <code>HWND</code> for the dialog to un-register. 
	@see WinAppRegisterModelessDialog 
	@since PI_WIN_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *WinAppUnRegisterModelessDialogSELPROTO)
	(HWND dialog);
#define WinAppUnRegisterModelessDialog (ACROASSERT(gWinVersion >=WINHFT_VERSION_4), *((WinAppUnRegisterModelessDialogSELPROTO)(gWinHFT[WinAppUnRegisterModelessDialogSEL])))

#define WinAppEnableIdleTimerSEL 3

/** Windows-specific Methods 

	<p>(Windows only) Allows a plug-in to turn the <code>AVAppIdle</code> timer 
	on and off, which is needed when a plug-in calls another 
	process and thus blocks Acrobat for an extended period of 
	time. </p>

	@param enable IN/OUT <code>true</code> to turn the timer on, <code>false</code> to turn 
	it off. 
	@return The previous state of the <code>AVAppIdle</code> timer. 
	@since PI_WIN_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 BOOL (ACCBPROTO2 *WinAppEnableIdleTimerSELPROTO)
	(BOOL enable);
#define WinAppEnableIdleTimer (ACROASSERT(gWinVersion >=WINHFT_VERSION_4), *((WinAppEnableIdleTimerSELPROTO)(gWinHFT[WinAppEnableIdleTimerSEL])))

#define WinAppGetModalParentSEL 4

/**
	(Windows only) Gets the appropriate parent for any modal dialogs 
	created by a plug-in. This method is only useful if there 
	is an AVDoc; it cannot be used, for example, to put up a 
	modal dialog while a file is being opened. 

	<p>In circumstances where there is no AVDoc, use the <code>gHWND</code> 
	provided in PIMAIN.C. Although this does not give perfect 
	results in some cases, there is no real alternative. For 
	example, if a file is opened in an external application's 
	window, the dialog is not hidden if the external application 
	is hidden. </p>

	@param doc IN/OUT The AVDoc for a PDF file if the dialog is acting 
	on an PDF document, which is generally the case. The AVDoc 
	must be provided so that for external documents, the viewer 
	can parent the dialog of the external application instead 
	of the viewer. 
	@return The <code>HWND</code> for the modal dialog's parent. 
	@see AVAppBeginModal 
	@see AVAppEndModal 
	@since PI_WIN_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 HWND (ACCBPROTO2 *WinAppGetModalParentSELPROTO)
	(AVDoc doc);
#define WinAppGetModalParent (ACROASSERT(gWinVersion >=WINHFT_VERSION_4), *((WinAppGetModalParentSELPROTO)(gWinHFT[WinAppGetModalParentSEL])))

/* Return the Application's palette. Return is NULL if no palette is being used */
/* DON'T release this palette handle -- it may be used by other plugins */
#define WinAppGetPaletteSEL 5

/**
	(Windows only) Gets the application's color palette in the 
	case where the system is running in 256 color mode or less. 
	It is used when you want to set and realize a palette in an external 
	window before drawing to it. 

	<p>Do not release this palette handle: it may be in use by 
	other plug-ins. </p>
	@return The application's color palette. It is <code>NULL</code> if the system is running 
	direct colors (15/ 16/ 24/ 32-bit) or no palette is being 
	used. 
	@since PI_WIN_VERSION >= 0x00020000
*/
typedef ACCBPROTO1 HPALETTE (ACCBPROTO2 *WinAppGetPaletteSELPROTO)
	(void);
#define WinAppGetPalette (ACROASSERT(gWinVersion >=WINHFT_VERSION_4), *((WinAppGetPaletteSELPROTO)(gWinHFT[WinAppGetPaletteSEL])))

/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_WIN_VERSION in PIRequir.h to
** 0x00040000.
*/

/* WinAppGetPrinterHDC */
#define WinAppGetPrinterHDCSEL 6

/**
	Gets the device context for a printer, which is the <code>HDC</code> 
	used to print a document. 

	<p>It is used if you need to modify the device context Acrobat creates 
	when printing to a non-PostScript printer. You should register 
	for the notification PDDocWillPrintPage() and acquire the 
	printer <code>DC</code> for the page you wish to modify. </p>

	@return The printer device context. 
	@since PI_WIN_VERSION >= 0x00040000
*/
typedef ACCBPROTO1 HDC (ACCBPROTO2 *WinAppGetPrinterHDCSELPROTO)
	(void);
#define WinAppGetPrinterHDC (ACROASSERT(gWinVersion >=WINHFT_VERSION_5), *((WinAppGetPrinterHDCSELPROTO)(gWinHFT[WinAppGetPrinterHDCSEL])))


/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_WIN_VERSION in PIRequir.h to
** 0x00050000.
*/

/* WinAppGetPrinterHDC */
#define WinAppRegisterInterfaceSEL 7

/**
	(Windows only) Register a COM interface. 
	@param COMServer IN/OUT A pointer to <code>COMServerRec</code>. 
	@return <code>true</code> if the interface was registered with Acrobat; <code>false</code> 
	otherwise. 
	@since PI_WIN_VERSION >= 0x00050000
*/
typedef ACCBPROTO1 BOOL (ACCBPROTO2 *WinAppRegisterInterfaceSELPROTO)
	(COMServer);

#define WinAppRegisterInterface (ACROASSERT(gWinVersion >=WINHFT_VERSION_5), *((WinAppRegisterInterfaceSELPROTO)(gWinHFT[WinAppRegisterInterfaceSEL])))

/**
	This function is designed for internal use only. It is deprecated in 
	Acrobat 6.0 and will not be available in future releases.
*/
#define WinAppLockViewerSEL 8
typedef ACCBPROTO1 void (ACCBPROTO2 *WinAppLockViewerSELPROTO)
	(BOOL);
#define  WinAppLockViewer (ACROASSERT(gWinVersion >=WINHFT_VERSION_5), *((WinAppLockViewerSELPROTO)		\
                               (gWinHFT[WinAppLockViewerSEL])))

/**
	(Windows only) Gets the appropriate parent for any modeless dialogs 
	created by a plug-in.
 
	<p>In previous versions of Acrobat the correct parent for modeless
	dialogs was always <code>gHWND</code> and was provided in PIMAIN.C.</p>

	@return The <code>HWND</code> for the modeless dialog's parent. 
	@see WinAppRegisterModelessDialog 
	@see WinAppUnregisterModelessDialog 
	@since PI_WIN_VERSION >= 0x00080000
*/
#define WinAppGetModelessParentSEL 9
typedef ACCBPROTO1 HWND (ACCBPROTO2 *WinAppGetModelessParentSELPROTO)();
#define WinAppGetModelessParent (ACROASSERT(gWinVersion >=WINHFT_VERSION_8), *((WinAppGetModelessParentSELPROTO)(gWinHFT[WinAppGetModelessParentSEL])))

#define WinAppUnregisterInterfaceSEL 10

/**
	(Windows only) Unregisters a COM interface. 
	@param COMServer IN/OUT A pointer to a <code>COMServerRec</code>. 
	@since PI_WIN_VERSION >= 0x00090000
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *WinAppUnregisterInterfaceSELPROTO)
	(COMServer);

#define WinAppUnregisterInterface (ACROASSERT(gWinVersion >=WINHFT_VERSION_9), *((WinAppUnregisterInterfaceSELPROTO)(gWinHFT[WinAppUnregisterInterfaceSEL])))

/* If you add, delete, or modify procs listed in this file please read the instructions at the top about how to properly change the version number */

#endif /* PI_WIN_VERSION */

#ifdef __cplusplus
}
#endif

#endif /* _H_WinCalls */

