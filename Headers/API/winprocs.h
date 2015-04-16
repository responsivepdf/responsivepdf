/*************************************************************************
* WARNING: All additions to this file must go at the end of the file.
* This file is #included to build a table of function pointers (an HFT).
* All components which make use of this HFT rely on the order and
* positioning of these functions (e.g. plug-ins). Adding entries in the 
* middle of this file or modifying existing entries will cause these 
* components to break.
**************************************************************************/

/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1994-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 WinProcs.h

 - Catalog of functions exported by the Windows Viewer.

*********************************************************************/


/**
	(Windows only) Registers modeless dialog boxes with the viewer 
	so that the dialog box gets the correct messages. 
	@param dialog IN/OUT The <code>HWND</code> for the dialog box to register. 
	@see WinAppUnRegisterModelessDialog 
	@since PI_WIN_VERSION >= 0x00020000
*/
NPROC(void, WinAppRegisterModelessDialog, (HWND dialog))

/**
	(Windows only) Un-registers modeless dialog boxes with the viewer. 
	
	@param dialog IN/OUT The <code>HWND</code> for the dialog box to un-register. 
	@see WinAppRegisterModelessDialog 
	@since PI_WIN_VERSION >= 0x00020000
*/
NPROC(void, WinAppUnRegisterModelessDialog, (HWND dialog))

/** 	
	<p>(Windows only) Allows a plug-in to turn the <code>AVAppIdle</code> timer 
	on and off, which is needed when a plug-in calls another 
	process and thus blocks Acrobat for an extended period of 
	time. </p>

	@param enable IN/OUT <code>true</code> to turn the timer on, <code>false</code> to turn 
	it off. 
	@return The previous state of the <code>AVAppIdle</code> timer. 
	@since PI_WIN_VERSION >= 0x00020000
*/
NPROC(BOOL, WinAppEnableIdleTimer, (BOOL enable))

/**
	(Windows only) Gets appropriate parent for any modal dialog boxes 
	created by a plug-in. This method is only useful if there 
	is an AVDoc; it cannot be used, for example, to put up a 
	modal dialog box while a file is being opened. 

	<p>In circumstances where there is no AVDoc, use the <code>gHWND</code> 
	provided in PIMAIN.C. Although this does not give perfect 
	results in some cases, there is no real alternative. For 
	example, if a file is opened in an external application's 
	window, the dialog box is not hidden if the external application 
	is hidden. </p>

	@param doc IN/OUT The AVDoc for a PDF file if the dialog box is acting 
	on an PDF document, which is generally the case. The AVDoc 
	must be provided so that for external documents, the viewer 
	can parent the dialog box of the external application instead 
	of the viewer. 
	@return The <code>HWND</code> for the modal dialog box' parent. 
	@see AVAppBeginModal 
	@see AVAppEndModal 
	@since PI_WIN_VERSION >= 0x00020000
*/
NPROC(HWND, WinAppGetModalParent, (AVDoc doc))

/**
	(Windows only) Gets the application's color palette in the 
	case where the system is running in 256-color mode or less. 
	Used when you want to set and realize a palette in an external 
	window before drawing to it. 

	<p>Do not release this palette handle: it may be in use by 
	other plug-ins.</p>

	@return The application's color palette. It is <code>NULL</code> if the system is running 
	direct colors (15/ 16/ 24/ 32-bit) or no palette is being 
	used. 
	@since PI_WIN_VERSION >= 0x00020000
*/
NPROC(HPALETTE, WinAppGetPalette, (void))

/* New for Acrobat 4.0 */

/**
	Gets the device context for a printer, which is the <code>HDC</code> 
	used to print a document. 

	<p>It is used if you need to modify the device context Acrobat creates 
	when printing to a non-PostScript printer. You should register 
	for the notification PDDocWillPrintPage() and acquire the 
	printer <code>DC</code> for the page you wish to modify.</p>

	@return The printer device context. 
	@since PI_WIN_VERSION >= 0x00040000
*/
NPROC(HDC, WinAppGetPrinterHDC, (void))

/* New for Acrobat 5.0 */

/**
	(Windows only) Register a COM interface. 
	@param pServer A pointer to <code>COMServerRec</code>. 
	@return <code>true</code> if the interface was registered with Acrobat, <code>false</code> 
	otherwise. 
	@since PI_WIN_VERSION >= 0x00050000
*/
NPROC(BOOL, WinAppRegisterInterface, (COMServer pServer))

/**
	This API is used to ensure that the application does not quit until the
	work that needs to be done by the interface registered with
	WinAppRegisterInterface() is done.
	@param lock <code>TRUE</code> locks the Viewer, preventing it from quitting.
	<code>FALSE</code> allows the Viewer to quit.  Calling WinAppLockViewer() with
	<code>FALSE</code> does not automatically quit the Viewer; it decrements an
	a reference count.
	@see WinAppRegisterInterface
	@since PI_WIN_VERSION >= 0x00050000
*/
NPROC(void, WinAppLockViewer, (BOOL lock))

/**
	(Windows only) Gets the appropriate parent for any modeless dialog boxes 
	created by a plug-in.
 
	<p>In previous versions of Acrobat, the correct parent was always
	<code>gHWND</code> and was provided in PIMAIN.C.</p>

	@return The <code>HWND</code> for the modeless dialog box' parent. 
	@see WinAppRegisterModelessDialog 
	@see WinAppUnregisterModelessDialog 
	@since PI_WIN_VERSION >= 0x00080000
*/
NPROC(HWND, WinAppGetModelessParent, (void))

/**
	(Windows only) Unregisters a COM interface. 
	@param pServer A pointer to a <code>COMServerRec</code>. 
	@since PI_WIN_VERSION >= 0x00090000
*/
NPROC(void, WinAppUnregisterInterface, (COMServer pServer))
