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
 Copyright (C) 1994-2007 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 AVProcs.h

 - Catalog of functions exported by AcroView.

*********************************************************************/
#if !PLUGIN 
#undef XNPROC
#undef XPROC
#undef XSPROC
#if CAN_EDIT && !READER /* Restore XProcs */
#define XNPROC NPROC
#define XPROC PROC
#define XSPROC SPROC
#else
#define XNPROC(returnType, name, params) NOPROC(name)
#define XPROC(returnType, name, params) NOPROC(name)
#define XSPROC(returnType, name, params, stubProc) NOPROC(name)
#endif /* CAN_EDIT && !READER */

#endif


/**
	Gets the ASAtom specifying what type of actions an action handler services. 
	This is the same as the name used when the action handler was registered 
	using AVAppRegisterActionHandler(). 
	@param handler IN The action handler whose type is obtained. 
	@return The ASAtom specifying what action types handler services. 
	@see AVAppRegisterActionHandler 
	@see AVActionHandlerGetProcs 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(ASAtom, AVActionHandlerGetType, (AVActionHandler handler))

/**
	Gets the string that was passed as the user friendly when the action 
	handler was registered using AVAppRegisterActionHandler(). 
	@param handler IN The action handler whose user interface name is obtained. 
	@return The user interface name of handler. 
	@see AVAppRegisterActionHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(const char*, AVActionHandlerGetUIName, (AVActionHandler handler))

/**
	Gets a structure containing pointers to the action handler's procedures. 

	<p>This method is useful when you want to subclass a previously registered 
	action handler. Acrobat releases the previously registered action 
	handler when you call AVAppRegisterActionHandler(), so you must copy 
	the previously registered action handler to a new action handler 
	structure, which you use in the call to AVAppRegisterActionHandler().</p> 
	@param handler IN The action handler whose procedures are obtained. 
	@return A pointer to a structure that contains the action handler's callbacks. 
	@see AVAppRegisterActionHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVActionHandlerProcs, AVActionHandlerGetProcs, (AVActionHandler handler))

/**
	Displays an alert containing the specified message, icon, and one 
	to three buttons with the specified titles. 

	<p>You can replace this method with your own version, using HFTReplaceEntry(). </p>

	@note It is a limitation of the current implementation that if the button 
	titles do not match either of the following sets, the size of the dialog box 
	is fixed and may not display all of the text in <code>msg</code>: 

	<p><code>Yes [, No [, Cancel] ] OK [, Cancel]</code> </p>

	@note All the implementations of the AVAlert methods call AVAlert(), 
	which is a replaceable method. If AVAlert() is replaced, all of the <code>AVAlert</code> 
	methods are also affected. 
	@param iconType IN The icon to display. It must be one of the AVAlert Icons. 
	Mac OS users: These constants are defined as per the standard Mac 
	user interface guidelines.
	
	<ul>
	<li>Use <code>NULL</code> for a button title to suppress a button's display.</li> 
	<li>At least <code>button1</code> must be non-<code>NULL</code>. </li>
	<li><code>button3</code> is not displayed if <code>button2</code> is <code>NULL</code>.</li> 
	</ul>

	@ingroup ReplaceableMethods
	@param msg IN The message to display. 
	@param button1 IN The title for the first button.  
	@param button2 IN The title for the second button.
	@param button3 IN The title for the third button.
	@param beep IN Pass <code>true</code> to perform a system beep when the alert is shown. 
	@return The button number (1, 2, or 3) on which the user clicked. 
	@see AVAlertGetPref 
	@see AVAlertConfirm 
	@see AVAlertNote 
	@see AVDocAlert 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
PROC(ASInt32, AVAlert, (ASInt32 iconType, const char *msg, const char *button1,
	const char *button2, const char *button3, ASBool beep))

/**
	Displays a dialog box containing the ALERT_NOTE icon, the specified 
	message and an OK button. The method also performs a system beep. 

	@note The implementation of AVAlertNote() calls AVAlert(), which is a 
	replaceable method. If AVAlert() is replaced, AVAlertNote() is also affected. 
	@param msg IN The message to display. 
	@see AVAlert 
	@see AVAlertConfirm 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(void, AVAlertNote, (const char *msg))

/**
	Displays a dialog box containing the ALERT_CAUTION icon, the specified 
	message, and OK and Cancel buttons. The method also performs a system 
	beep. See AVAlert() for more information. 
	@param msg IN The message to display. 
	@return <code>true</code> if the user clicks OK, <code>false</code> if the user clicks Cancel. 
	@see AVAlert 
	@see AVAlertNote 
	@see AVDocAlertConfirm 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(ASBool, AVAlertConfirm, (const char *msg))

/**
	Gets the major and minor version numbers of the Acrobat viewer. 

	<p>To correctly accommodate cases such as 4.05 and 4.5, the minor version 
	is split into two 8 bit numbers, as shown in the following example:</p> 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Version</TH><TH>Description</TH></TR>
	<TR><TD>4.05</TD><TD>The minor version would be <code>0x0005</code>.</TD></TR>
	<TR><TD>4.5</TD><TD>The minor version would be <code>0x0500</code>.</TD></TR>
	</TABLE>

	@param majorP OUT (Filled by the method) A pointer to the major version 
	number. 
	@param minorP OUT (Filled by the method) A pointer to the minor version 
	numbers. 
	@see AVAppGetLanguage 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(void, AVAppGetVersion, (AVTVersionNumPart *majorP, AVTVersionNumPart *minorP))

/**
  	Superseded in Acrobat 6.0 by AVAppGetLanguageWithParams().
  
  	<p>Gets the language in which the application's user interface is running. 
  	See the list of Language Codes for the possible return values. </p>
	
	@param buffer OUT (Filled by the method) The language code. <code>buffer</code> must 
	be able to contain four bytes. 
	@see AVAppGetLanguageWithParams 
	@see AVAppGetVersion 
  	@ref LanguageCodes
	
	@note Superseded in Acrobat 6.0 by AVAppGetLanguageWithParams(). 
	@since PI_ACROVIEW_VERSION >= 0x00020000
	
*/
NPROC(void, AVAppGetLanguage, (char* buffer))

/**
	Gets the ASAtom corresponding to the application's name, which is 
	the name of the file containing the Acrobat viewer application. The 
	user might have changed this, so do not use it to determine what the application 
	is; use ASGetConfiguration() instead. 
	@return An ASAtom representing the Acrobat viewer's name. 
	@see ASGetConfiguration 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(ASAtom, AVAppGetName, (void))

/**
	Gets the default application cancel procedure. The procedure returns 
	<code>true</code> if the user has recently entered the keystroke described below. 

	<p>A cancel procedure is often passed to methods that take a long time to 
	run. The method will call the procedure at frequent intervals, and 
	if the return value is <code>true</code>, the method cancels its operation. </p>

	<p>The keystroke that the application recognizes as a cancel command 
	is platform-dependent: </p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Keystroke</TH></TR>
	<TR><TD>Mac OS</TD><TD>Command-period</TD></TR>
	<TR><TD>Windows</TD><TD>Escape</TD></TR>
	</TABLE>

	@param cancelProcClientDataP IN (Allocated and filled by the method) 
	Data needed by a <code>CancelProc</code>. This value must be passed as the <code>clientData</code> 
	whenever the procedure is called or passed to a method which may call 
	it. 
	@return The default <code>CancelProc</code>, or <code>NULL</code> if one is not available. 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(CancelProc, AVAppGetCancelProc, (void **cancelProcClientDataP))

/**
	The Acrobat viewer calls this method to obtain permission programmatically 
	(without using the user interface) when it wants to quit. To use this method, 
	replace it with your own version using HFTReplaceEntry(). 

	<p>If you replace this method in UNIX, your replacement implementation 
	must not have any user interface component (for example, dialog boxes). 
	At the time your replacement is called, the Acrobat viewer owns the 
	pointer and will not give it to your dialog box, so the screen will freeze.</p> 
	@ingroup ReplaceableMethods
	@return Returns <code>true</code> if Acrobat can quit, <code>false</code> if it cannot. The default version 
	of this routine always returns <code>true</code>. 
	@see HFTReplaceEntry 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
PROC(ASBool, AVAppCanQuit, (void))

/**
	Gets the frontmost document window. In UNIX, it gets the AVDoc 
	being viewed within the window that got the last user event 
	(Key or Button event). This method is often useful for menu 
	or tool enable procs. The frontmost document may not be 
	active. For example, the clipboard window may be active and 
	over it. 

	<p>This method returns documents that are being viewed within 
	the host application. In some cases it can return a document 
	open in an external window (for example, a web browser), 
	but you cannot depend on this. </p>

	<p>The safest approach is to avoid calling AVAppGetActiveDoc(), 
	if at all possible. You will usually get good results if 
	AVAppGetActiveDoc() is called only from within menu item or 
	toolbar button callbacks (AVExecuteProc(), AVComputeEnabledProc(), 
	and AVComputeMarkedProc()), but in general it is best to use 
	some bit of context already provided to you to figure out 
	which AVDoc the user is interacting with. Use the following 
	guidelines: </p>

	<ul>
	<li> If you have a PDDoc available (or can get one from some 
	other PD object) call AVDocFromPDDoc() to find the AVDoc open 
	on the PDDoc. </li>
	<li> If you have an AVPageView available, call AVPageViewGetAVDoc() 
	to retrieve the AVDoc. </li>
	<li> If you have an AVPanel available, call AVPanelGetAVDoc() to 
	retrieve the AVDoc that the panel points to. You probably 
	should also provide a <code>DocChanged</code> callback in your panel 
	handler so you will be notified when your panel's document 
	changes. </li>
	<li> If you have an AVCommand available and are absolutely sure 
	you want an AVDoc, use AVCommandGetPDDoc() and pass the result 
	to AVDocFromPDDoc(). </li>
	</ul>

	<p>It is also a good idea to localize the determination of the 
	active doc. Occasionally client code calls AVAppGetActiveDoc() 
	often and at various levels. It is more robust to determine 
	the active document once, and then pass it along as an argument 
	to your other routines. </p>

	<p>Also, make absolutely sure you want an AVDoc and not a PDDoc 
	in the first place. If your code can work on a PDDoc (for 
	example, it does not require any user interface) then it should. </p>

	@note AVAppGetActiveDoc is often used to enable a menu item 
	in a client (<code>if AVAppGetActiveDoc() != NULL</code>). 
	@return The frontmost document window, or <code>NULL</code> if no documents are 
	open. <code>NULL</code> is also returned when a document is open but 
	its invisible flag is set (see AVDocOpenParams()) and may 
	be returned while a document is being opened.
	<p>You can get an AVDoc as it opens by registering for 
	AVDocDidOpen(). </p>
	@notify AVDocWillOpenFromFile
	@notify AVDocWillOpenFromPDDoc
	@notify AVDocDidOpen
	@see AVAppEnumDocs 
	@see AVAppGetNumDocs 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVDoc, AVAppGetActiveDoc, (void))

/**
	Gets the number of open document views. 
	@return The number of open AVDocs. 
	@see AVAppGetActiveDoc 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVTArraySize, AVAppGetNumDocs, (void))

/**
	Enumerates all AVDoc objects currently open in the viewer, calling the user-
	supplied procedure for each. It raises an exception only if <code>enumProc</code> raises an exception. 
	@param enumProc IN A user-supplied callback to call once for each open 
	AVDoc. 
	@param clientData IN A pointer to user-supplied data to pass to <code>enumProc</code> 
	each time it is called. 
	
	@see PDEnumDocs 

	@note <code>enumProc</code> must not close any documents. 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(void, AVAppEnumDocs, (AVDocEnumProc enumProc, void *clientData))

/**
	Gets the standard application progress monitor, which puts a
	combined status window/progress bar in the message pane 
	of the frontmost document window. This progress monitor 
	can subsequently be passed to any API method requiring a 
	progress monitor. 

	<p>If you want to display and control a progress monitor in 
	your own client, you can simply invoke the appropriate callbacks 
	in the progress monitor data structure this method returns. </p>
	

	(Acrobat 5.0 and later) A <code>setText</code> value in ASProgressMonitor that 
	allows you to add text to a monitor. 
	@param progMonClientData (Allocated and filled by the 
	method, may not be <code>NULL</code>) Private data used by the progress 
	monitor. This value must be passed as the <code>clientData</code> whenever 
	a callback in the structure is called or the monitor is 
	passed to a method that takes a progress monitor as a parameter.
	@return The standard application progress monitor, or <code>NULL</code> if no 
	documents are open. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASProgressMonitor, AVAppGetDocProgressMonitor, (void **progMonClientData))

#if HAS_MENUBAR

/**
	Gets Acrobat's menu bar. 
	@return The menu bar. 
	@see AVMenuGetParentMenubar 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVMenubar, AVAppGetMenubar, (void))
#else
NOPROC(AVAppGetMenubar)
#endif


/**
	Retrieves a special toolbar representing
	the union of all toolbars in the system.

	<p>If this toolbar is passed to AVLegacyToolBarEnumButtons(),
	every button on every non-flyout toolbar will be
	enumerated.</p>

	<p>If this toolbar is passed to AVLegacyToolBarAddButton(),
	the newly added button will actually be placed on
	the File menu, unless it is being positioned next
	to an existing button, in which case it will be
	placed on the same toolbar as the existing button.</p>

	<p>When adding a button, AVAppGetLegacyToolBar() should only be
	used if the new button is to be added next to an
	existing button. In fact, it is recommended that you
	do so by calling AVAppGetLegacyToolBar(), finding the existing
	button, and then placing the new button next to it by
	calling AVLegacyToolBarAddButton(), passing in the toolbar returned
	by AVAppGetLegacyToolBar(). This ensures that if the existing
	button moves to another toolbar in a later release, your
	new button will move with it.</p>

	<p>When adding a button that is not going to be positioned
	next to an existing button, it is recommended that you
	retrieve the desired toolbar using AVAppGetLegacyToolBarByName().</p>

	@return The toolbar. 
	@see AVAppGetLegacyToolBarByName 
	@see AVLegacyToolBarNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVToolBar, AVAppGetLegacyToolBar, (void))

/**
	Gets the active tool for the application. 
	@return The active tool. 
	@see AVAppSetActiveTool 
	@see AVAppGetLastActiveTool 
	@see AVAppGetDefaultTool 
	@see AVDocGetActiveTool 

	@note It is recommended that you use AVDocGetActiveTool() 
	instead, preferably specifying a particular document. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTool, AVAppGetActiveTool, (void))

/**
	Gets the tool that was active before the current tool became active.

	@return The last active tool. If only one tool has ever been active, it is returned. 
	@see AVAppGetActiveTool 
	@see AVAppGetDefaultTool 

	@note It is recommended that you use AVDocGetLastActiveTool()
	instead, preferably specifying a particular document.
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVTool, AVAppGetLastActiveTool, (void))

/**
	Gets the default tool. Use this method, together with AVAppSetActiveTool(), 
	to restore the default tool any time you want. The default tool is the 
	hand tool. 
	@return The default tool. It returns <code>NULL</code> if there is no default tool. 
	@see AVAppSetActiveTool 
	@see AVAppGetActiveTool 
	@see AVAppGetLastActiveTool 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVTool, AVAppGetDefaultTool, (void))

/**
	Sets the active tool. It does nothing if the specified tool 
	is not currently enabled. The AVComputeEnabledProc() callback in the 
	<code>AVTool</code> structure determines whether a tool is enabled. 
	If this callback is <code>NULL</code>, the tool is 
	always enabled. 
	@param tool The tool to set as the active tool. 
	@param persistent A flag that indicates a preference as 
	to whether the tool stays active after it is used. <code>true</code> 
	is a hint that the tool should, if possible, stay active 
	for an arbitrary number of <i>operations</i> (whatever that happens 
	to be) rather than doing a <i>one shot</i> operation and restoring 
	the prior active tool. Persistence is not enforced by the 
	Acrobat viewer. It is up to a one-shot tool to restore the 
	previously active tool (determined using AVAppGetLastActiveTool()), 
	or to restore the default tool (determined using AVAppGetDefaultTool()) 
	if there was no previously active tool.
	@see AVAppGetActiveTool 
	@see AVAppGetLastActiveTool 
	@see AVAppGetDefaultTool 
	@see AVDocSetActiveTool 

	@note It is recommended that you use AVDocSetActiveTool() 
	rather than AVAppSetActiveTool(), preferably specifying a 
	particular document. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppSetActiveTool, (AVTool tool, ASBool persistent))

/**
	Returns the AVTool that was registered under the specified name. 
	@param name IN The ASAtom corresponding to the tool's name. 
	@return The tool that was registered under <code>name</code>, or <code>NULL</code> if no match was found. 
	@see AVAppGetActiveTool 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVTool, AVAppGetToolByName, (ASAtom name))

/**
	Enumerates all registered tools, calling the user-supplied procedure 
	for each. It raises an exception only if <code>enumProc</code> raises an exception. 
	@param enumProc IN A user-supplied callback to call for each tool. 
	@param clientData IN A pointer to user-supplied data to pass to <code>enumProc</code> 
	each time it is called. 
	@see AVAppGetToolByName 
	@see AVAppRegisterTool 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(void, AVAppEnumTools, (AVToolEnumProc enumProc, void *clientData))

NPROC(void, oldAVAppRegisterTool, (AVTool tool))


/**
	Gets the annotation handler that handles the specified annotation 
	type. 
	@param name The name of the requested annotation handler.
	@return The annotation handler that services annotations of type 
	<code>name</code>. If no annotation handler is registered for that type, 
	the viewer's default annotation handler is returned. To 
	determine whether the returned annotation handler is the 
	default annotation handler, check the return value from 
	the handler's <code>GetType</code> for the type <code>Unknown</code>. 
	@see AVAppEnumAnnotHandlers 
	@see AVAppGetAnnotHandlerByName 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVAnnotHandler, AVAppGetAnnotHandlerByName, (ASAtom name))

/**
	Enumerates all registered annotation handlers, calling the user-
	supplied procedure for each. It raises an exception only if <code>enumProc</code> raises an exception. 
	@param enumProc IN A user-supplied callback to call for each annotation 
	handler. 
	@param clientData IN A pointer to user-supplied data to pass to <code>enumProc</code> 
	each time it is called. 
	
	@see AVAppGetAnnotHandlerByName 
	@see AVAppRegisterAnnotHandler 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(void, AVAppEnumAnnotHandlers, (AVAnnotHandlerEnumProc enumProc, void *clientData))

NPROC(void, oldAVAppRegisterAnnotHandler, (AVAnnotHandler handler))


/**
	Gets the action handler that services the specified action type. 
	@param type IN The action type whose handler is obtained. 
	@return The handler that services actions of the specified type. It returns <code>NULL</code> 
	if no such handler is registered. 
	@see AVAppRegisterActionHandler 
	@see AVActionHandlerGetType 
	@see AVActionHandlerGetUIName 
	@since PI_ACROVIEW_VERSION >= 0x00020000 
	
*/
NPROC(AVActionHandler, AVAppGetActionHandlerByType, (ASAtom type))

/**
	Enumerates all registered action handlers, calling the user-
	supplied procedure for each. It aises an exception only if <code>enumProc</code> raises an exception.
	@param enumProc IN A user-supplied procedure to call once for 
	each action handler. 
	@param clientData IN A pointer to user-supplied data to pass 
	to <code>enumProc</code> each time it is called.   
	
	@see AVActionHandlerGetProcs 
	@see AVAppRegisterActionHandler 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppEnumActionHandlers, (AVActionEnumProc enumProc, void *clientData),
	AVAppEnumSupportedActions)

/**
	Registers an action handler within Acrobat. 
	@param actionHandler IN/OUT A structure containing the callbacks 
	for the action handler to register. This structure must 
	not be freed after calling AVAppRegisterActionHandler. 
	@param actionHandlerObj IN/OUT A pointer to user-supplied data to 
	pass to the action handler's methods when they are invoked. 
	
	@param pdfName IN The action type serviced by this handler, 
	as it appears in the PDF file. Storage for this string may 
	be released after the call. This string must not contain 
	any white space characters (for example, spaces). 
	@param userName IN/OUT The name of this action type as it should 
	appear in the Acrobat viewer's user interface. Storage for 
	this string may be released after the call. 
	@see AVActionHandlerGetProcs 
	@see AVAppEnumActionHandlers 
	@see AVAppGetActionHandlerByType 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppRegisterActionHandler, (AVActionHandlerProcs actionHandler,
	void *actionHandlerObj, const char *pdfName, char *userName))

/**
	Gets the value of the specified built-in application preference. 
	
	@param preference IN/OUT The preference value to get. See the 
	preference descriptions in AVPrefsType. 
	@return <code>NULL</code> if preference was not recognized. Otherwise, clients 
	must cast the return value to the appropriate type, depending 
	on the preference requested. See the preference descriptions 
	in AVPrefsType. 
	@see AVAppSetPreference 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void *, AVAppGetPreference, (AVPrefsType preference))

/**
	Sets the value of the specified built-in application preference. 
	The preference values are automatically saved to disk when 
	a new value is set. 
	@param preference IN/OUT The preference value to set. See AVPrefsType 
	for a list of preference descriptions. 
	@param newValue IN/OUT The new value for the preference. The type of 
	this value is dependent on the preference being set. See 
	AVPrefsType for more information. 
	@notify AVAppOldPrefDidChange 
	@see AVAppGetPreference 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppSetPreference, (AVPrefsType preference, void *newValue))


#if HAS_FULL_SCREEN

/**
	Begins full-screen mode. In full-screen mode, all window 
	borders, the menu bar, and the toolbar are hidden. All regions 
	of the screen outside of the window boundary are painted 
	with the specified color. 

	<p>AVAppBeginFullScreen() is ignored if the application is already 
	in full-screen mode, or if there are no currently open documents. </p>
	
	@param color IN/OUT (May be <code>NULL</code>) The color to use for painting 
	all regions of the screen outside of the window boundary. 
	Pass <code>NULL</code> to use the default color specified by the application 
	preference <code>avpFullScreenColor</code>. 
	@return <code>true</code> if the application enters full-screen mode, <code>false</code> if 
	it is already in full-screen mode or the user selects Cancel 
	from the dialog box describing how to exit full-screen mode. 
	
	@see AVAppEndFullScreen 
	@see AVAppDoingFullScreen 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVAppBeginFullScreen, (PDColorValue color))

/**
	Ends full-screen mode. It does nothing if the application is 
	not running in full-screen mode. 
	@see AVAppBeginFullScreen 
	@see AVAppDoingFullScreen 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppEndFullScreen, (void))

/**
	Tests whether the application is running in full-screen 
	mode. 
	@return <code>true</code> if the application is currently in full-screen mode, <code>false</code> 
	otherwise. 
	@see AVAppBeginFullScreen 
	@see AVAppEndFullScreen 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVAppDoingFullScreen, (void))
#else
NOPROC(AVAppBeginFullScreen)
NOPROC(AVAppEndFullScreen)
NOPROC(AVAppDoingFullScreen)
#endif


/**
	Prepares the Acrobat viewer to display a modal window. For 
	example, it disables floating windows in Windows, where they 
	are not automatically disabled. When you are done with the 
	modal window, call AVAppEndModal(). Calling AVAppBeginModal() 
	does not make your window modal; it only informs the Acrobat 
	viewer that you intend to display a modal window now. 

	<p>If you are displaying a platform modal window that is not wrapped by an <code>AVWindow</code>, 
	call this method passing in <code>NULL</code>.</p>

	<p>Windows users: The parent of a modal window should be determined by calling <code>WinAppGetModalParent()</code>.
	If the first modal window has an <code>AVWindow</code> wrapper that was passed to this method, 
	you can use <code>WinAppGetModalParent()</code> in this case and obtain the correct result.</p>

	<p>Mac OS and UNIX users: This method must be called.</p> 

	@param window IN/OUT The modal window to display. 
	@see AVAppEndModal 
	@see AVAppModalWindowIsOpen 
	@see WinAppGetModalParent 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppBeginModal, (AVWindow window))

/**
	A client should use this method to determine whether a modal 
	window is open. There is a large (and ill-defined) group 
	of actions that are illegal while a modal window is open, 
	although these actions are not programmatically prevented 
	by the Acrobat viewer. While a modal dialog box is open, a client 
	must not open documents, change pages, change views, close 
	documents, change tools, or do anything that might disrupt 
	the user or Acrobat viewer. 
	@return <code>true</code> if a modal window is open, <code>false</code> otherwise. 
	@see AVAppBeginModal 
	@see AVAppEndModal 
	@see WinAppGetModalParent 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVAppModalWindowIsOpen, (void))

/**
	(Windows only) Informs the Acrobat viewer that a modal window 
	is no longer being displayed. 
	@see AVAppBeginModal 
	@see AVAppModalWindowIsOpen 
	@see WinAppGetModalParent 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppEndModal, (void))

/**
	Registers a user-supplied procedure to call regularly
	when the Acrobat viewer is otherwise idle. If more than 
	one idle procedure is registered, they are all called in 
	a round robin order. The registered idle procs may be called 
	when the Acrobat viewer is not the frontmost application. 
	In addition, in Mac OS, the registered idle procs receive 
	idle events any time a movable modal dialog box or modal AVWindow 
	is displayed, but not a system-modal one. Use AVAppModalWindowIsOpen() 
	if you wish to determine if a modal window is open. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering, and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param idleProc A user-supplied callback to call at idle 
	time. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>idleProc</code> each time it is called. 
	@param period The minimum time between calls to <code>idleProc</code>. 
	<code>idleProc</code> will not be called any more frequently than <code>period</code>, 
	but it may be called less frequently. <code>period</code> is specified 
	in ticks (one tick is 1/60 of a second).
	@see AVAppUnregisterIdleProc 
	@see AVAppModalWindowIsOpen 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppRegisterIdleProc, (AVIdleProc idleProc, void *clientData, ASUns32 period))

/**
	Un-registers a user-supplied idle procedure. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering, and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param idleProc The original callback. 
	@param clientData The original <code>clientData</code>.
	@see AVAppRegisterIdleProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppUnregisterIdleProc, (AVIdleProc idleProc, void *clientData))

/**
	Registers a user-supplied procedure to call when the specified 
	event occurs. 

	<p>Many notifications appear in Will/Did pairs (for example, 
	AVDocWillPerformAction() and AVDocDidPerformAction()). It is 
	possible that an operation may fail after the Will notification 
	and before the Did notification. When this occurs, the Did 
	notification is still broadcast, but the <code>err</code> parameter in 
	the Did notification is non-zero, and represents the error 
	that occurred. When <code>err</code> is non-zero, the other parameters 
	are not necessarily valid. Always check <code>err</code> in a Did notification 
	before using the other parameters. </p>

	<p>When calling AVAppUnregisterNotification() to un-register 
	for a notification, you must pass the <code>proc</code>, <code>clientData</code>, 
	and <code>owner</code> that were used when the notification was registered 
	using AVAppRegisterNotification(). You must use the same callback 
	that was used to register; you cannot use a newly created 
	callback. To accomplish this, call ASCallbackCreateNotification() 
	once before registering, and use the value returned from 
	this call both to register and un-register; do not call 
	ASCallbackCreateNotification() a second time when un-registering. 
	You will then need to destroy the pointer to the callback 
	using the ASCallbackDestroy() method. </p>
	@param nsel The notification type. It must be one of the 
	notification selectors (see Notifications). The notification 
	selector is the name of the notification with the characters 
	<code>NSEL</code> appended. For example, the selector for AVDocDidOpen() 
	is AVDocDidOpenNSEL(). 
	@param owner The <code>gExtensionID</code> of the client registering 
	the notification. 
	@param proc A user-supplied callback to call when the notification 
	occurs. Its declaration depends on the notification type 
	(see Notifications). Remember to use ASCallbackCreateNotification() 
	to convert <code>proc</code> to a callback before passing it to AVAppRegisterNotification(). 
	
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see AVAppUnregisterNotification 
	@see ASCallbackCreateNotification 
	@see ASCallbackDestroy 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppRegisterNotification, (NSelector nsel, ASExtension owner, void *proc,
	void *clientData), AVExtensionMgrRegisterNotification)

/**
	Un-registers a user-supplied notification procedure. 

	<p>To un-register, you must use the same callback, <code>clientData</code>, 
	and <code>owner</code> that were used when the notification was registered 
	using AVAppRegisterNotification(). To accomplish this, call 
	ASCallbackCreateNotification() once before registering, and 
	use the value returned from this call both to register and 
	un-register; do not call ASCallbackCreateNotification() a 
	second time when un-registering.</p> 
	@param nsel The notification type. 
	@param owner The <code>gExtensionID</code> of the client registering 
	the notification. 
	@param proc The original callback. 
	@param clientData The original <code>clientData</code>.
	@see AVAppRegisterNotification 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppUnregisterNotification, (NSelector nsel, ASExtension owner, void *proc,
	void *clientData),AVExtensionMgrUnregisterNotification)

NPROC(AVDoc, oldAVDocOpenFromFile, (ASPathName pathName, ASFileSys fileSys, const char *tempTitle))
PROC(AVDoc, oldAVDocOpenFromFileWithParams, (ASPathName pathName, ASFileSys fileSys,
	const char *tempTitle, oldAVDocOpenParams params))
NPROC(AVDoc, oldAVDocOpenFromPDDoc, (PDDoc doc, const char *tempTitle))
NPROC(AVDoc, oldAVDocOpenFromPDDocWithParams, (PDDoc pdDoc, const char *tempTitle, oldAVDocOpenParams params))

/**
	Closes the document window, optionally prompting the user 
	to save the document if it has been modified. When this 
	method closes the AVDoc, it also closes the underlying PDDoc. 
	
	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@param doc IN/OUT The document to close. 
	@param noSave IN/OUT If <code>true</code>, the document is closed without prompting 
	the user and without saving, even if the document has been 
	modified. Because this can cause data loss without user 
	approval, use this feature judiciously. If <code>false</code>, it prompts the 
	user to save the document if it has been modified. 
	@return <code>true</code> if the document closed, <code>false</code> if it did not (for example, 
	if the user was prompted with the Save dialog box and chose 
	Cancel). The document will always close if <code>noSave</code> is <code>true</code>. 
	
	@ingroup ReplaceableMethods
	@notify AVDocWillClose 
	@notify AVDocDidClose 
	@see AVDocOpenFromFile 
	@see AVDocOpenFromPDDoc 
	@see AVDocDoSave 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
PROC(ASBool, AVDocClose, (AVDoc doc, ASBool noSave))

/**
	Gets the PDDoc to associate with the specified AVDoc. 
	@param avDoc IN/OUT The document whose PDDoc is obtained. 
	@return The PDDoc associated with <code>avDoc</code>. 
	@see AVDocOpenFromPDDoc 
	@see PDEnumDocs 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(PDDoc, AVDocGetPDDoc, (AVDoc avDoc))

/**
	Gets the AVPageView for the specified document. 
	@param doc The document whose AVPageView is obtained.
	@return The document's AVPageView. 
	@see AVDocGetAVWindow 
	@see AVDocGetViewMode 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVPageView, AVDocGetPageView, (AVDoc doc))

/**
	Gets the AVWindow in which the document is displayed.
	If more than one window is open for a document,
	this call returns the active window for that document,
	which is the one with which the user is interacting.

	@param doc The document whose AVWindow is obtained.
	@return The document's AVWindow. 
	@see AVDocGetPageView 
	@see AVDocGetNumWindows
	@see AVDocGetNthWindow
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVWindow, AVDocGetAVWindow, (AVDoc doc))

/**
	Gets the current view mode. 
	@param doc IN/OUT The document whose view mode is obtained. 
	@return The current view mode. 
	@see AVDocSetViewMode 
	@see PDDocGetPageMode 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(PDPageMode, AVDocGetViewMode, (AVDoc doc))

/**
	Sets the current view mode. 

	<p>This method does nothing if the current view mode is full-
	screen, PDFullScreen. In this case, call AVAppEndFullScreen() 
	first. </p>
	@param doc IN/OUT The document whose view mode is set. 
	@param newMode IN/OUT The view mode to set. 
	@see AVAppEndFullScreen 
	@see AVDocGetViewMode 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocSetViewMode, (AVDoc doc, PDPageMode newMode))

/**
	Gets the splitter position. The splitter is the vertical 
	division between the bookmark/thumbnail pane and the document 
	pane. The default splitter location is saved in the Acrobat 
	viewer's preferences file, and can be read and set using AVAppGetPreference() 
	and AVAppSetPreference(). 
	@param doc IN/OUT The document whose splitter position is obtained. 
	
	@return The width of the bookmark/thumbnail pane, measured in pixels. 
	Returns <code>0</code> if the bookmark/thumbnail pane is not currently 
	displayed. 
	@see AVDocSetSplitterPosition 
	@see AVAppGetPreference 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASInt16, AVDocGetSplitterPosition, (AVDoc doc))

/**
	Sets the splitter position. The splitter is the vertical 
	division between the bookmark/thumbnail pane and the document 
	pane. The default splitter location is saved in the Acrobat 
	viewer's preferences file, and can be read and set using AVAppGetPreference() 
	and AVAppSetPreference(). 
	@param doc The document whose splitter position is set. 
	
	@param newPosition The new splitter position. This value 
	specifies the width of the bookmark/thumbnail pane in pixels.
	@see AVDocGetSplitterPosition 
	@see AVAppSetPreference 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocSetSplitterPosition, (AVDoc doc, ASInt16 newPosition))

/**
	Prints without displaying any user dialog boxes. The current 
	printer, page settings, and job settings are used. Printing 
	is complete when this method returns. 

	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param doc The document from which pages are printed. 
	
	@param firstPage The first page in <code>doc</code> to print. 
	@param lastPage The last page in <code>doc</code> to print. 
	@param psLevel Applies to PostScript printing. It must be 
	either <code>1</code> or <code>2</code>. If <code>1</code>, Level 1 PostScript code is generated. 
	If <code>2</code>, Level 2 PostScript code is generated. 
	@param binaryOK Applies to PostScript printing. If <code>true</code>, 
	the PostScript code may contain binary data. If <code>false</code>, all 
	binary data is encoded into an ASCII format. 
	@param shrinkToFit If <code>true</code>, the page is shrunk (if necessary) 
	to fit into the imageable area of a page in the printer. 
	If <code>false</code>, pages are printed at actual size and may appear 
	clipped on the printed page.
	@exception genErrBadParm is raised if an invalid parameter is provided. 
	It can raise any of the <code>CosErrExpected</code> exceptions, such as ErrSysCosSyntax or cosErrExpectedNumber. 
	In general, this method can raise any exception that can occur 
	during the parsing of a page and its resources, such as pdErrUnknownProcsets or 
	pdErrUnableToExtractFontErr.
	@notify PDDocWillPrintPages 
	@notify PDDocWillPrintPage 
	@notify PDDocDidPrintPage 
	@notify PDDocDidPrintPages 
	@notify PDDocDidPrintTiledPage 
	@notify PDDocPrintingTiledPage 
	@notify PDDocWillPrintTiledPage 
	@see AVDocDoPrint 
	@see AVDocPrintPagesWithParams 

	@note If security has been set on a file so that it is not 
	printable, the document will not print, but no error is 
	raised. Check the security before printing the file. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
PROC(void, AVDocPrintPages, (AVDoc doc, AVPageIndex firstPage, AVPageIndex lastPage,ASInt32 psLevel,
	ASBool binaryOK, ASBool shrinkToFit))

/**
	Gets the current selection's type for the specified document. 
	
	@param doc The document whose selection type is obtained.
	@return The ASAtom corresponding to the current selection type. 
	Returns ASAtomNull if there is no selection. The ASAtom 
	returned can be converted to a string using ASAtomGetString(). 
	See Selection Types for a list of the built-in selection 
	types. 
	@see AVDocGetSelection 
	@see AVDocSetSelection 

	@note To get information about the selected annotation, 
	use AVPageViewGetFocusAnnot(). 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASAtom, AVDocGetSelectionType, (AVDoc doc))

/**
	Gets the current selection for the specified document. 
	@param doc The document whose selection is obtained.
	@return The current selection, or <code>NULL</code> if there is no selection. 
	See Selection Types for a list of the data types returned 
	for the built-in selection types. A <code>NULL</code> return value from 
	this method is not sufficient to determine whether there is 
	no selection; use AVDocGetSelectionType() instead. 
	@see AVDocSetSelection 
	@see AVDocGetSelectionType 
	@see AVDocClearSelection 
	@see AVDocDeleteSelection 
	@see AVDocEnumSelection 
	@see AVDocCopySelection 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void*, AVDocGetSelection, (AVDoc doc))

/**
	Sets the document's current selection to the specified selection 
	by calling the appropriate selection server's AVDocSelectionGettingSelectionProc() 
	callback. It clears the previous selection, if any, by calling 
	the previous selection server's AVDocSelectionLosingSelectionProc() 
	callback. 

	<p>This raises only those exceptions raised by the previous selection server's 
	AVDocSelectionGettingSelectionProc(), and those raised by 
	the new selection server's AVDocSelectionGettingSelectionProc().</p>

  	<p>The following selection types can be specified when calling this method. The <i>Details</i> column 
  	specifies what should be used for the <code>data</code> parameter:</p>
  
  	<TABLE rules="all" cellspacing="1">
  	<TR><TH>Selection Type</TH><TH>Description</TH><TH>Data Type</TH><TH>Details</TH></TR>
  	<TR><TD><code>Text</code></TD><TD>Text in the document</TD><TD><code>PDTextSelect</code></TD><TD>Use PDDocCreateTextSelect() to create the selection.</TD></TR>
  	<TR><TD><code>Bitmap</code></TD><TD>Graphics</TD><TD><code>AVGrafSelect</code></TD><TD>Use AVGrafSelectCreate() to create the selection.</TD></TR>
  	<TR><TD><code>Annotation</code></TD><TD>Annotation (text annotation, link, and so on)</TD><TD>To get information about a selected annotation, use AVPageViewGetFocusAnnot().</TD><TD>Allocate memory using <code>ASmalloc(sizeof(PDAnnot))</code>. Copy the desired PDAnnot into the allocated memory and pass a pointer to it. The annotation selection server assumes responsibility for freeing the memory.</TD></TR>
  	<TR><TD><code>Thumbnail</code></TD><TD>Thumbnail image</TD><TD><code></code></TD><TD>Pass the page number (the first page in a document is page <code>0</code>).</TD></TR>
  	</TABLE>

	@param doc The AVDoc in which the selection is set. 
	@param type The selection type. It can be either a built-in type 
	or one supported by a selection server added by a client. 
	It can be converted to an ASAtom using ASAtomFromString(). See 
	Selection Types for a list of the built-in selection types. 
	
	@param data A data structure representing the selection. 
	Its type depends on what is passed in <code>type</code>. See Selection 
	Types for a list of the data types for the built-in selection 
	types. 
	@param highlight Clients should pass <code>true</code>, which tells 
	the Acrobat viewer to highlight the selection because it 
	has not already been highlighted. This only marks the highlighted 
	regions of the display as invalid, but does not immediately 
	redraw the screen. Use AVPageViewDrawNow() to force an immediate 
	redraw if you wish.
	@return <code>true</code> if the selection was set successfully, <code>false</code> otherwise. 
	This method can fail for reasons including:
	<ul>
	<li> There is no selection server for <code>type</code>. </li>
	<li> There was an attempt to set the selection during link creation. </li>
	</ul>

	@notify AVDocDidSetSelection 
	@see AVGrafSelectCreate 
	@see AVPageViewDrawNow 
	@see AVDocRegisterSelectionServer 
	@see AVDocClearSelection 
	@see AVDocDeleteSelection 
	@see AVDocDoSelectionProperties 
	@see AVDocEnumSelection 
	@see AVDocCopySelection 
	@see PDDocCreateTextSelect
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVDocSetSelection, (AVDoc doc, ASAtom type, void* data, ASBool highlight))

/**
	Deletes the specified document's current selection, if possible. 
	The selection is deleted if changing the selection is currently 
	permitted, the selection server has an AVDocSelectionDeleteProc() 
	callback, and the selection server's AVDocSelectionCanDeleteProc() 
	callback returns <code>true</code>. If the selection server does not 
	have a AVDocSelectionCanDeleteProc() callback, a default value 
	of <code>true</code> is used. 

	<p>The selection is deleted by calling the selection server's 
	AVDocSelectionDeleteProc() callback. </p>

	<p>It only raises those exceptions raised by the selection server's AVDocSelectionDeleteProc() 
	and AVDocSelectionCanDeleteProc() callbacks.</p>

	@param doc IN/OUT The document whose selection is deleted. 
	@return <code>true</code> if the current selection was actually deleted, <code>false</code> 
	otherwise. 
	@notify AVDocDidDeleteSelection 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVDocDeleteSelection, (AVDoc doc))

/**
	Clears and destroys the current selection by calling the 
	appropriate selection server's AVDocSelectionLosingSelectionProc(). 
	
	@param doc IN/OUT The document whose selection is cleared. 
	@param highlight IN/OUT Pass <code>true</code> to instruct the Acrobat 
	viewer to remove the selection's highlighting, if it has 
	not already been removed. The selection handler may only 
	mark the highlighted regions of the display as invalid, but 
	does not force an immediate redraw of the page view. Use 
	AVPageViewDrawNow() to force an immediate redraw if you wish. 
	
	@return <code>true</code> if the current selection was cleared, <code>false</code> otherwise. 
	
	@notify Broadcasts AVDocWillClearSelection() if the selection type 
	is not ASAtomNull. 
	@see AVDocSetSelection 
	@see AVDocCopySelection 
	@see AVDocEnumSelection 
	@see AVDocDoSelectionProperties 
	@see AVDocGetSelection 
	@see AVDocDeleteSelection 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVDocClearSelection, (AVDoc doc, ASBool highlight))

/**
	Copies the current selection to the clipboard, if possible. 
	The selection is copied if the selection server has a AVDocSelectionCopyProc() 
	callback, and the selection server's AVDocSelectionCanCopyProc() 
	callback returns <code>true</code>. If the selection server does not 
	have a AVDocSelectionCanCopyProc() method, a default value 
	of <code>true</code> is used. 

	<p>The selection is copied by calling the selection server's 
	AVDocSelectionCopyProc() callback. </p>

	<p>It only raises those exceptions raised by the selection server's AVDocSelectionCopyProc() 
	and AVDocSelectionCanCopyProc() callbacks.</p>

	@param doc IN/OUT The document whose selection is copied. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocCopySelection, (AVDoc doc))

/**
	Enumerates the elements of the current selection by calling 
	the current selection server's AVDocSelectionEnumSelectionProc() 
	callback. If the selection server does not have an AVDocSelectionEnumSelectionProc(), 
	it calls <code>proc</code> and passes the entire selection to it in the 
	<code>aSelectedObject</code> parameter. 

	<p>It only raises those exceptions raised by the selection server's AVDocSelectionEnumSelectionProc() 
	callback, and those raised by <code>proc</code>.</p>

	@param doc The document whose selection is enumerated. 
	
	@param proc A user-supplied callback to call for each element 
	in the selection. The enumeration ends if <code>proc</code> returns <code>false</code>. 
	
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see AVDocRegisterSelectionServer 
	@see AVDocSetSelection 
	@see AVDocClearSelection 
	@see AVDocDeleteSelection 
	@see AVDocCopySelection 
	@see AVDocSelectionEnumPageRanges 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocEnumSelection, (AVDoc doc, AVSelectionEnumProc proc, void *clientData))

/**
	Displays the user interface, if any, for setting the current 
	selection's properties. It does this by invoking the AVDocSelectionPropertiesProc() 
	callback, if any, of the current selection's selection server. 
	
	<p>It only raises those exceptions raised by the selection server's AVDocSelectionPropertiesProc() callback.</p>

	@param doc IN/OUT The document containing the selection whose 
	properties are set. 
	@see AVDocRegisterSelectionServer 
	@see AVDocSetSelection 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocDoSelectionProperties, (AVDoc doc))

/**
	Displays the current selection by calling the selection 
	server's AVDocSelectionShowSelectionProc() callback. It does 
	nothing if the document has no selection, or the current 
	selection's server has no AVDocSelectionShowSelectionProc() 
	callback. 

	<p>It only raises those exceptions raised by the selection server's AVDocSelectionShowSelectionProc() callback.</p>

	@param doc IN/OUT The document whose selection is shown. 
	@see AVDocSetSelection 
	@see AVGrafSelectCreate 
	@see AVDocRegisterSelectionServer 
	@see PDDocCreateTextSelect 
	@see PDTextSelectCreatePageHilite 
	@see PDTextSelectCreateWordHilite 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocShowSelection, (AVDoc doc))

NPROC(oldAVDocSelectionServer, oldAVDocGetSelectionServerByType, (ASAtom type))
NPROC(ASBool, oldAVDocRegisterSelectionServer, (oldAVDocSelectionServer server))


/**
	Performs an action.
	@param doc The document containing the action to perform. 
	
	@param action The action to perform.
	@exception pdErrBadAction 
	@notify AVDocWillPerformAction 
	@notify AVDocDidPerformAction 
	@see AVDocDoActionPropsDialog 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVDocPerformAction, (AVDoc doc, PDAction action))

#if HAS_MENUBAR

/**
	Shows the menu bar. 
	@param menubar IN/OUT The menu bar to show. 
	@see AVMenubarHide 
	@see AVAppGetMenubar 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenubarShow, (AVMenubar menubar))

/**
	Hides the menu bar. 
	@param menubar IN/OUT The menu bar to hide. 
	@see AVMenubarShow 
	@see AVAppGetMenubar 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenubarHide, (AVMenubar menubar))

/**
	Gets the number of menus in <code>menubar</code>. 
	@param menubar IN/OUT The menu bar for which the number of menus 
	is obtained. 
	@return The number of menus in the menu bar, not including submenus. 
	Returns <code>0</code> if <code>menubar</code> is <code>NULL</code>. 
	@see AVAppGetMenubar 
	@see AVMenubarAcquireMenuByIndex 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTArraySize, AVMenubarGetNumMenus, (AVMenubar menubar))

/**
	Acquires the menu or submenu that has the specified language-independent 
	menu name (case-sensitive). When you are done using the 
	menu, release it using AVMenuRelease(). Acquiring a menu by 
	name is generally reliable, because names (unlike indices) 
	do not change as menus are added or rearranged. 
	@param menubar The menu bar in which the menu item is located. 
	
	@param name The language-independent name of the menu 
	to acquire. See Menu and Menu Item Names for a list of the 
	names of the built-in menus in Acrobat.
	@return The menu with the specified name. 
	@see AVAppGetMenubar 
	@see AVMenuRelease 
	@see AVMenubarAcquireMenuItemByName 
	@see AVMenubarAcquireMenuItemByPredicate 
	@see AVMenubarAcquireMenuByIndex 
  	@ref MenuItemNames
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenubarAcquireMenuByName, (AVMenubar menubar, const char *name))

/**
	Acquires the menu with the specified index. Menu indices 
	are generally not reliable: they change as clients add, remove, 
	or rearrange menus, and may differ in different versions 
	of the Acrobat viewer (if menus are rearranged, removed, 
	or added). Menus should generally be acquired using AVMenubarAcquireMenuByName(), 
	which is generally reliable. 
	@param menubar The menu bar in which the menu is located. 
	
	@param menuIndex The index (in <code>menubar</code>) of the menu to 
	acquire.
	@return The menu with the specified index. It returns <code>NULL</code> if there is no such 
	menu or if <code>menubar</code> is <code>NULL</code>. 
	@see AVMenubarAcquireMenuByName 
	@see AVMenubarAcquireMenuByPredicate 
	@see AVAppGetMenubar 
	@see AVMenuRelease 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenubarAcquireMenuByIndex, (AVMenubar menubar, AVMenuIndex menuIndex))

/**
	Acquires a menu using a user-supplied selection routine. 
	This method can also be used to enumerate all menus. When 
	you are done using the menu that is acquired, release it 
	using AVMenuRelease(). 
	@param menubar IN/OUT The menu bar containing the menu to acquire. 
	
	@param predicate IN/OUT A user-supplied <code>AVMenuPredicate</code> function 
	that determines which menu is acquired. Menus are searched 
	depth-first. The first menu for which predicate returns 
	<code>true</code> is acquired. If <code>predicate</code> always returns <code>false</code>, all 
	menus will be enumerated. 
	@param clientData IN/OUT A pointer to user-supplied data to pass 
	to <code>predicate</code> each time it is called. 
	@return The first menu for which predicate returned <code>true</code>. It returns 
	<code>NULL</code> if predicate never returned <code>true</code> or if <code>menubar</code> is <code>NULL</code>. 
	
	@see AVMenuRelease 
	@see AVMenubarAcquireMenuByName 
	@see AVMenubarAcquireMenuByIndex 
	@see AVAppGetMenubar 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenubarAcquireMenuByPredicate, (AVMenubar menubar, AVMenuPredicate predicate,
	void *clientData))

/**
	Acquires the menu item with the specified language-independent 
	menu item name (case-sensitive). This method automatically 
	searches all menus and submenus. When you are done using 
	the menu item, release it using AVMenuItemRelease(). Acquiring 
	a menu item by name is generally reliable, because names 
	(unlike indices) do not change as menus items are added 
	or rearranged. 
	@param menubar The menu bar in which the menu item is located. 
	
	@param name The language-independent name of the menu 
	item to acquire. See Menu and Menu Item Names for the language-independent 
	names of the menu items built into Adobe Reader and Acrobat. 
	The language-independent names of menu items added by Adobe 
	clients are described in the technical notes for those clients.
	@return The menu item with the specified name. It returns <code>NULL</code> if no 
	such menu item exists, if <code>menubar</code> is <code>NULL</code>, or if <code>name</code> is 
	<code>NULL</code>. 
	@see AVAppGetMenubar 
	@see AVMenuItemRelease 
	@see AVMenubarAcquireMenuByName 
	@see AVMenubarAcquireMenuItemByPredicate 
	@see AVMenuAcquireMenuItemByIndex 
  	@ref MenuItemNames
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuItem, AVMenubarAcquireMenuItemByName, (AVMenubar menubar, const char *name))

/**
	Acquires a menu item using a user-supplied selection routine. 
	This method may also be used to enumerate all menu items. 
	When you are done using the menu item that is acquired, 
	release it using AVMenuItemRelease(). 
	@param menubar The menu bar containing the menu to acquire. 
	
	@param predicate A user-supplied function that determines 
	which menu item is acquired. Menu items are searched depth-first. 
	The first menu item for which <code>predicate</code> returns <code>true</code> is 
	acquired. If <code>predicate</code> always returns <code>false</code>, all menu items 
	will be enumerated. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>predicate</code> each time it is called.
	@return The first menu item for which <code>predicate</code> returned <code>true</code>. It returns 
	<code>NULL</code> if <code>predicate</code> never returns <code>true</code> or if <code>menubar</code> is <code>NULL</code>. 
	
	@see AVMenuItemRelease 
	@see AVMenubarAcquireMenuByName 
	@see AVMenuAcquireMenuItemByIndex 
	@see AVAppGetMenubar 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuItem, AVMenubarAcquireMenuItemByPredicate, (AVMenubar menubar,
	AVMenuItemPredicate predicate, void *clientData))

/**
	Gets the index of the specified menu in the menu bar. 
	@param menubar The menu bar in which the menu is located. 
	
	@param menu The menu whose index is obtained.
	@return The specified menu's index. It returns BAD_MENU_INDEX if the 
	menu is not in the menubar, is a submenu, if <code>menubar</code> is 
	<code>NULL</code>, or if <code>menu</code> is <code>NULL</code>. 
	@see AVAppGetMenubar 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuIndex, AVMenubarGetMenuIndex, (AVMenubar menubar, AVMenu menu))

/**
	Inserts a menu into the menubar. It does nothing if <code>menubar</code> 
	is <code>NULL</code> or <code>menu</code> is <code>NULL</code>. 
	@param menubar The menu bar into which the menu is added. 
	
	@param menu The menu to add. 
	@param menuIndex The position at which the menu is added. 
	The left-most menu in a menu bar has an index of zero. Passing 
	a value of APPEND_MENU (see AVExpT.h.) adds the menu to 
	the end of the menu bar.
	@exception genErrNoMemory 
	@see AVMenuNew 
	@see AVMenuRemove 
	@see AVMenubarAddHiddenMenu 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenubarAddMenu, (AVMenubar menubar, AVMenu menu, AVMenuIndex menuIndex))

#else

NOPROC(AVMenubarShow)
NOPROC(AVMenubarHide)
NOPROC(AVMenubarGetNumMenus)
NOPROC(AVMenubarAcquireMenuByName)
NOPROC(AVMenubarAcquireMenuByIndex)
NOPROC(AVMenubarAcquireMenuByPredicate)
NOPROC(AVMenubarAcquireMenuItemByName)
NOPROC(AVMenubarAcquireMenuItemByPredicate)
NOPROC(AVMenubarGetMenuIndex)
NOPROC(AVMenubarAddMenu)

#endif

#if HAS_MENUS

/**
	Creates and acquires a new menu with the given title and 
	language-independent name. The menu can be added to the 
	menu bar using AVMenubarAddMenu(). When you are done using 
	the menu, release it using AVMenuRelease(). 
	@param title The string that appears in the user interface. 
	On Windows, an ampersand (<code>&</code>) character in the string results 
	in underlining the character after it on the menu. 
	@param name The language-independent name of the menu to create: 
	it is the value returned by AVMenuGetName(). It must not contain 
	any spaces. Developers should prefix the names of menus 
	they add with the name of their client and a colon, to avoid 
	collisions in the menu name space. For example, a client 
	named <code>myPlug</code> might add menus named <code>myPlug:DrawTools</code> and 
	<code>myPlug:Checkout</code>. 
	@param owner The <code>gExtensionID</code> extension registering the 
	menu.
	@return The newly created menu. 
	@exception genErrNoMemory 
	@see AVMenuRelease 
	@see AVMenubarAddMenu 
	@see AVMenuGetName 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenuNew, (const char *title, const char *name,ASExtension owner))

/**
	Acquires the specified menu. It increments the menu's reference 
	count. When you are done using the menu item, release it 
	using AVMenuRelease(). 
	@param menu IN/OUT The menu to acquire. 
	@return The menu acquired. 
	@see AVMenubarAcquireMenuByIndex 
	@see AVMenubarAcquireMenuByName 
	@see AVMenubarAcquireMenuItemByPredicate 
	@see AVMenuRelease 
	@see AVMenuNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenuAcquire, (AVMenu menu))

/**
	Releases the specified menu. It decrements the reference count 
	and automatically destroys the menu when its reference count 
	is zero. 
	@param menu The menu to release.
	@see AVMenuAcquire 
	@see AVMenuNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuRelease, (AVMenu menu))
#else
NOPROC(AVMenuNew)
NOPROC(AVMenuAcquire)
NOPROC(AVMenuRelease)
#endif

#if HAS_MENUBAR

/**
	Removes a menu from the menu bar and releases it. If the 
	menu is a submenu, this method does nothing. 
	@param menu IN/OUT The menu to remove. 
	@see AVMenuItemRemove 
	@see AVMenuRelease 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuRemove, (AVMenu menu))
#else
NOPROC(AVMenuRemove)
#endif

#if HAS_MENUS

/**
	Gets the ASAtom for the menu's language-independent name. 
	
	@param menu IN/OUT The menu whose language-independent name is 
	obtained. 
	@return The menu's name. The ASAtom can be converted to a string 
	using ASAtomGetString(). It returns <code>NULL</code> if <code>menu</code> is <code>NULL</code>. 
	@see AVMenuAcquire 
	@see AVMenuGetTitle 
	@see AVMenuNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASAtom, AVMenuGetName, (AVMenu menu))

/**
	Gets the menu's title as it appears in the user interface. 
	The length of the title remains <code>0</code> if menu is <code>NULL</code>. 
	@param menu The menu whose title is obtained. 
	@param buffer (Filled by the method) A buffer into which 
	the title is copied. If <code>buffer</code> is <code>NULL</code>, it is not filled; 
	the length of the title is still returned. 
	@param bufferSize The maximum number of characters the 
	buffer can hold.
	@return If <code>menu</code> is non-zero, the length of the title is returned. If 
	<code>menu</code> is <code>NULL</code> and <code>buffer</code> is not, <code>buffer</code> is zeroed. It returns 
	<code>0</code> if <code>buffer</code> is <code>NULL</code>. 
	@see AVMenuGetName 
	@see AVMenuNew 
	@see AVMenuItemGetTitle 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTArraySize, AVMenuGetTitle, (AVMenu menu, char *buffer, AVTArraySize bufferSize))

/**
	Gets the number of menu items in a menu, including those 
	that are visible only in long-menus mode. 
	@param menu IN/OUT The menu for which the number of menu items 
	is obtained. 
	@return The number of menu items in the specified menu. It returns 
	<code>0</code> if <code>menu</code> is <code>NULL</code>. 
	@see AVMenuAcquireMenuItemByIndex 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTArraySize, AVMenuGetNumMenuItems, (AVMenu menu))

/**
	Acquires the menu item at the specified location in the 
	specified menu. When you are done using the menu item, release 
	it using AVMenuItemRelease(). Menu item indices are generally 
	not reliable: they change as clients add, remove, or rearrange 
	menu items, and may differ in different versions of the 
	Acrobat viewer (if menu items are rearranged, removed, or 
	added). Menu items should generally be acquired using AVMenubarAcquireMenuItemByName(), 
	which is generally reliable. 
	@param menu The menu in which a menu item is acquired. 
	
	@param menuItemIndex The index of the menu item in <code>menu</code> 
	to acquire. The first item in a menu has an index of zero. 
	Even if the Acrobat viewer is displaying short menus, the 
	index includes any intervening long-mode-only menu items 
	(irrelevant for Acrobat 3.0 or later since there are no 
	short menus).
	@return The menu item whose index is specified. It returns <code>NULL</code> if 
	<code>menu</code> is <code>NULL</code>, if the index is less than zero, or the index 
	is greater than the number of menu items in the menu. 
	@see AVMenuGetNumMenuItems 
	@see AVMenubarAcquireMenuItemByPredicate 
	@see AVMenubarAcquireMenuItemByName 
	@see AVMenuItemAcquire 
	@see AVMenuItemRelease 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuItem, AVMenuAcquireMenuItemByIndex, (AVMenu menu, AVMenuIndex menuItemIndex))

/**
	Gets the index of the specified menu item in the specified 
	menu. 

	<p>Indices must be used with caution, because they change as 
	clients add, remove, or rearrange menu items. </p>
	@param menu The menu in which <code>menuItem</code> is located. 
	@param menuItem The menu item whose index is obtained.
	@return The index of <code>menuItem</code> in <code>menu</code>. The first item in a menu 
	has an index of zero. Even if the Acrobat viewer is displaying 
	short menus, the index includes any intervening long-mode-only 
	menu items (irrelevant for Acrobat 3.0 or later since there 
	are no short menus). 

	@return BAD_MENUITEM_INDEX (see AVExpT.h) if <code>menuItem</code> is 
	not in <code>menu</code>, if <code>menu</code> is 
	<code>NULL</code>, or <code>menuItem</code> is <code>NULL</code>. 
	@see AVMenuGetNumMenuItems 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuIndex, AVMenuGetMenuItemIndex, (AVMenu menu, AVMenuItem menuItem))
#else
NOPROC(AVMenuGetName)
NOPROC(AVMenuGetTitle)
NOPROC(AVMenuGetNumMenuItems)
NOPROC(AVMenuAcquireMenuItemByIndex)
NOPROC(AVMenuGetMenuItemIndex)
#endif

#if HAS_MENUBAR

/**
	Gets the parent menu bar for the specified menu. 
	@param menu IN/OUT The menu whose parent menu bar is obtained. 
	
	@return The menu bar to which the menu is attached. It returns <code>NULL</code> 
	if the menu has not yet been added to the menu bar, or if 
	the menu is a submenu. 
	@see AVMenuGetParentMenuItem 
	@see AVMenubarGetMenuIndex 
	@see AVMenuItemGetParentMenu 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenubar, AVMenuGetParentMenubar, (AVMenu menu))
#else
NOPROC(AVMenuGetParentMenubar)
#endif

#if HAS_MENUS

/**
	Gets the parent menu item for the specified menu. 
	@param menu IN/OUT The menu whose parent menu item is obtained. 
	
	@return The menu item for which the specified menu is a submenu. 
	Returns <code>NULL</code> if the specified menu is not a submenu. 
	@see AVMenuGetParentMenubar 
	@see AVMenubarGetMenuIndex 
	@see AVMenuItemGetParentMenu 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuItem, AVMenuGetParentMenuItem, (AVMenu menu))

/**
	Inserts a menu item in a specified location in a menu, and 
	acquires the item. It does nothing if the menu or menu item 
	is <code>NULL</code>, or the menu item is already in a menu. 
	@param menu The menu to which a menu item is added. 
	@param menuItem The menu item to add. 
	@param menuItemIndex The location in <code>menu</code> to add <code>menuItem</code>. 
	The first item in a menu has an index of zero. Even if the 
	Acrobat viewer is displaying short menus, the index includes 
	any intervening long-mode-only menu items (irrelevant for 
	Acrobat 3.0 or later since there are no short menus). Pass 
	APPEND_MENUITEM (see AVExpT.h) to append the menu item to 
	the end of the menu.
	@exception genErrNoMemory 
	@see AVMenuItemRemove 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuAddMenuItem, (AVMenu menu, AVMenuItem menuItem, AVMenuIndex menuItemIndex))

/**
	Creates and acquires a new AVMenuItem. The menu item can 
	be added to a menu using AVMenuAddMenuItem(). 

	<p>Release the AVMenuItem using AVMenuItemRelease() after it 
	has been added to a menu. </p>
	@param title The string shown in the user interface for 
	this menu item. Use a hyphen to create a separator menu 
	item. This value is also returned by AVMenuItemGetTitle(). 
	On Windows, an ampersand (<code>&</code>) character in the string results 
	in underlining the character after it on the menu item. 
	
	@param name The language-independent name of the menu 
	item to create. This is the value returned by AVMenuItemGetName(). 
	<code>name</code> must not contain any spaces. Client developers should 
	prefix the names of menu items they add with the name of 
	their client and a colon, to avoid collisions in the menu 
	item name space. For example, a client named <code>myPlug</code> might 
	add menu items named <code>myPlug:Scan</code> and <code>myPlug:Find</code>. 
	@param submenu A submenu (if any) for which this menu item 
	is the parent. Pass <code>NULL</code> if this menu item does not have 
	a submenu. 
	@param longMenusOnly (Ignored in Acrobat 3.0 or later) 
	If <code>true</code>, the menu item is visible only when the user selects 
	Full Menus. If <code>false</code>, the menu item is visible for both 
	Full Menus and Short Menus modes. 
	@param shortcut The key to use as a shortcut for the menu 
	item (an ASCII character). Use NO_SHORTCUT (see AVExpT.h) 
	if the menu item has no shortcut. The Acrobat viewer does 
	not check for conflicts between shortcuts. The consequences 
	of multiple menu items having the same shortcut is undefined. 
	On Windows, the shortcut is not displayed for any menu item 
	that also has an icon, although the shortcut will work.
	@param flags Modifier keys, if any, used as part of the 
	shortcut. It must be an OR of the Modifier Keys values, except 
	that AV_COMMAND cannot be specified. 
	@param icon The icon to show in the menu item, or <code>NULL</code> 
	if no icon is shown. On Windows, <code>icon</code> is a 24x24 sample monochrome 
	<code>HBITMAP</code>. 
	@param owner The <code>gExtensionID</code> extension registering the 
	menu item.
	@return The newly created menu item. 
	@see AVMenuAddMenuItem 
	@see AVMenuItemRelease 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuItem, AVMenuItemNew, (const char *title, const char *name, AVMenu submenu,
	ASBool longMenusOnly, char shortcut, AVFlagBits16 flags, AVIcon icon, ASExtension owner))

/**
	Acquires a menu item. It increments the menu item's reference 
	count. 
	@param menuItem IN/OUT The menu item to acquire. 
	@return The menu item acquired. 
	@see AVMenuItemRelease 
	@see AVMenubarAcquireMenuItemByPredicate 
	@see AVMenubarAcquireMenuItemByName 
	@see AVMenuAcquireMenuItemByIndex 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenuItem, AVMenuItemAcquire, (AVMenuItem menuItem))

/**
	Releases a menu item. It decrements the reference count and 
	destroys the menu item if the count is zero. 
	@param menuItem IN/OUT The menu item to release. 
	@see AVMenuItemAcquire 
	@see AVMenubarAcquireMenuItemByPredicate 
	@see AVMenubarAcquireMenuItemByName 
	@see AVMenuAcquireMenuItemByIndex 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemRelease, (AVMenuItem menuItem))

/**
	Removes a menu item from the menu hierarchy and releases 
	it. It does nothing if <code>menuItem</code> is <code>NULL</code>. 

	<p>Keyboard accelerators for the Acrobat viewer's built-in 
	menu items will always work, even if the menu item is removed. </p>
	
	@param menuItem IN/OUT The menu item to remove. 
	@see AVMenuItemAcquire 
	@see AVMenuItemRelease 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemRemove, (AVMenuItem menuItem))

/**
	Gets the atom for the language-independent name of the menu 
	item. 
	@param menuItem IN/OUT The menu item whose language-independent 
	name is obtained. 
	@return The ASAtom corresponding to the name of the specified menu 
	item, or ASAtomNull if <code>menuItem</code> is <code>NULL</code>. The ASAtom can 
	be converted to a string using ASAtomGetString(). 
	@see AVMenuItemGetTitle 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASAtom, AVMenuItemGetName, (AVMenuItem menuItem))

/**
	Gets a menu item's title, which is the string that appears 
	in the user interface. 
	@param menuItem The menu item whose title is obtained. 
	
	@param buffer (Filled by the method) A buffer to hold 
	the <code>NULL</code>-terminated name. If title is <code>NULL</code>, it returns the 
	length of the menu item's name, but does not fill the buffer. 
	
	@param bufferSize The maximum number of characters that 
	can be placed into <code>title</code>. If the name is longer than this, 
	only the first <code>bufferSize - 1</code> characters are placed into 
	<code>buffer</code>, and the buffer is <code>NULL</code>-terminated.
	@return The length of the title. It returns <code>0</code> if <code>menuItem</code> is <code>NULL</code>. 
	@see AVMenuItemSetTitle 
	@see AVMenuItemGetName 
	@see AVMenuItemGetTitleAsASText 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTArraySize, AVMenuItemGetTitle, (AVMenuItem menuItem, char *buffer, AVTArraySize bufferSize))

/**
	Sets a menu item's title, which is the string that appears 
	in the user interface. Use this method to manage menu items 
	whose titles change (such as 'show/hide fooWindow'), instead 
	of inserting and removing menu items on the fly. 
	@param menuItem IN/OUT The menu item whose title is set. 
	@param title IN/OUT The new menu title. It must be a <code>NULL</code>-terminated 
	string. 
	@see AVMenuItemGetTitle 
	@see AVMenuItemGetName 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemSetTitle, (AVMenuItem menuItem, const char *title))

/**
	Gets the shortcut key for the specified menu item. 
	@param menuItem The menu item whose shortcut is obtained. 
	
	@param key (Filled by the method) The key that is a shortcut 
	for the menu item (an ASCII character). The value NO_SHORTCUT 
	(see AVExpT.h) indicates that the menu item has no shortcut. 
	
	@param flags (Filled by the method) Modifier keys, if 
	any, used as part of the shortcut. It must be an OR of the 
	Modifier Keys values, except that AV_COMMAND will never 
	be present.
	@return <code>true</code> if <code>menuItem</code> is not <code>NULL</code> and <code>menuItem</code> has a shortcut, 
	<code>false</code> otherwise. 
	@see AVMenuItemNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVMenuItemGetShortcut, (AVMenuItem menuItem, char* key, AVFlagBits16* flags))

/**
	Gets the flag indicating whether a menu item is visible 
	only in long-menus mode. 
	@param menuItem The menu item whose flag is obtained.
	@return <code>true</code> if the menu item is visible only in long-menus mode. 
	<code>false</code> if the menu item is visible in both long and short 
	menus, or if <code>menuItem</code> is <code>NULL</code>. 

	@note In Acrobat 3.0 and later, this is irrelevant, since 
	there is no long/short menus option. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVMenuItemGetLongOnly, (AVMenuItem menuItem))

/**
	Sets the user-supplied procedure to execute whenever the 
	menu item is chosen. It does nothing if <code>menuItem</code> is <code>NULL</code>. Clients 
	must not set the execute procedure of the Acrobat viewer's 
	built-in menu items. 
	@param menuItem The menu item whose execute procedure 
	is set. 
	@param proc A user-supplied callback to call whenever <code>menuItem</code> 
	is selected. 
	@param data A pointer to user-supplied data to pass to <code>proc</code> 
	each time it is called.
	@see AVMenuItemExecute 
	@see AVMenuItemSetComputeMarkedProc 
	@see AVMenuItemSetComputeEnabledProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemSetExecuteProc, (AVMenuItem menuItem, AVExecuteProc proc, void *data))

/**
	Sets the user-supplied procedure to call to determine whether 
	the menu item is enabled. It does nothing if <code>menuItem</code> is <code>NULL</code>. 
	
	@param menuItem The menu item whose AVComputeEnabledProc() 
	is set. 
	@param proc A user-supplied callback to call whenever the 
	Acrobat viewer needs to know whether <code>menuItem</code> should be 
	enabled. This procedure is called every time the menu is 
	displayed, so it should not do time-intensive processing. 
	
	@param data A pointer to user-supplied data to pass to <code>proc</code> 
	each time it is called.
	@see AVMenuItemIsEnabled 
	@see AVMenuItemSetComputeMarkedProc 
	@see AVMenuItemSetExecuteProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemSetComputeEnabledProc, (AVMenuItem menuItem, AVComputeEnabledProc proc,
	void *data))

/**
	Sets the user-supplied procedure that determines whether 
	the menu item appears with a check mark. It does nothing if 
	<code>menuItem</code> is <code>NULL</code>. If the menu item has no AVExecuteProc() 
	(see AVMenuItemSetExecuteProc()), its AVComputeMarkedProc() 
	is never called. To avoid this, add an AVExecuteProc() that 
	does nothing, and if you wish the menu item to gray out, 
	also add an AVComputeEnabledProc() that always returns <code>false</code>. 
	
	@param menuItem The menu item whose AVComputeMarkedProc() 
	is set. 
	@param proc A user-supplied callback to call whenever the 
	Acrobat viewer needs to know whether <code>menuItem</code> should 
	be marked. 
	@param data A pointer to user-supplied data to pass to <code>proc</code> 
	each time it is called.
	@see AVMenuItemIsMarked 
	@see AVMenuItemSetExecuteProc 
	@see AVMenuItemSetComputeEnabledProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemSetComputeMarkedProc, (AVMenuItem menuItem, AVComputeMarkedProc proc,
	void *data))

/**
	Acquires the submenu attached to the specified menu item, 
	if there is one. When you are done with the submenu, release 
	it using AVMenuRelease(). 
	@param menuItem IN/OUT The menu item whose submenu is obtained. 
	
	@return The specified menu item's submenu. It returns <code>NULL</code> if <code>menuItem</code> 
	is <code>NULL</code> or if <code>menuItem</code> does not have a submenu. 
	@see AVMenuAcquire 
	@see AVMenuRelease 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenuItemAcquireSubmenu, (AVMenuItem menuItem))

/**
	Tests whether the specified menu item is enabled. 
	@param menuItem The menu item whose enabled flag is obtained.
	@return <code>true</code> if <code>menuItem</code> is enabled, if <code>menuItem</code> is <code>NULL</code>, or if 
	<code>menuItem</code> has no AVComputeEnabledProc(). 
	It returns <code>false</code> if the menu item is disabled or its AVComputeEnabledProc() 
	raises an exception. 
	@see AVMenuItemSetComputeEnabledProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVMenuItemIsEnabled, (AVMenuItem menuItem))

/**
	Tests whether <code>menuItem</code> is marked (for example, it appears with 
	a check mark). 
	@param menuItem The menu item whose marked state is obtained.
	@return <code>true</code> if <code>menuItem</code> is marked. 
	It returns <code>false</code> if <code>menuItem</code> is <code>NULL</code>, if 
	the menu item does not have an AVComputeMarkedProc(), or if 
	it raises an exception. 
	@see AVMenuItemSetComputeMarkedProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVMenuItemIsMarked, (AVMenuItem menuItem))

/**
	Executes a menu item's AVExecuteProc(). It does nothing if <code>menuItem</code> 
	is <code>NULL</code>, if <code>menuItem</code> has no AVExecuteProc, or if <code>menuItem</code> 
	is not enabled. 

	<p>You cannot execute a menu item that has a submenu (for example, 
	the Pages menu item in the Document menu). </p>
	@param menuItem The menu item to execute.
	@see AVMenuItemSetExecuteProc 
	@see AVMenuItemIsEnabled 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVMenuItemExecute, (AVMenuItem menuItem))

/**
	Gets the menu in which the specified menu item appears. 
	
	@param menuItem IN/OUT The menu item whose parent menu is obtained. 
	
	@return The menu in which the specified menu item appears. It returns 
	<code>NULL</code> if this menu item is not in a menu. 
	@see AVMenuGetParentMenuItem 
	@see AVMenuItemAcquireSubmenu 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVMenu, AVMenuItemGetParentMenu, (AVMenuItem menuItem))
#else /* no menus */
NOPROC(AVMenuGetParentMenuItem)
NOPROC(AVMenuAddMenuItem)

NOPROC(AVMenuItemNew)
NOPROC(AVMenuItemAcquire)
NOPROC(AVMenuItemRelease)
NOPROC(AVMenuItemRemove)
NOPROC(AVMenuItemGetName)
NOPROC(AVMenuItemGetTitle)
NOPROC(AVMenuItemSetTitle)
NOPROC(AVMenuItemGetShortcut)
NOPROC(AVMenuItemGetLongOnly)
NOPROC(AVMenuItemSetExecuteProc)
NOPROC(AVMenuItemSetComputeEnabledProc)
NOPROC(AVMenuItemSetComputeMarkedProc)
NOPROC(AVMenuItemAcquireSubmenu)
NOPROC(AVMenuItemIsEnabled)
NOPROC(AVMenuItemIsMarked)
NOPROC(AVMenuItemExecute)
NOPROC(AVMenuItemGetParentMenu)
#endif /* no menus */


/**
	Gets the AVDoc for the document currently displayed in <code>pageView</code>. 
	
	@param pageView IN/OUT The page view whose AVDoc is obtained. 
	
	@return The AVDoc for <code>pageView</code>. 
	@see AVDocGetPageView 
	@see AVPageViewGetPage 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVDoc, AVPageViewGetAVDoc, (AVPageView pageView))
NPROC(void, oldAVPageViewGetAperture, (AVPageView pageView, oldAVRect *rect))

/**
	Gets a PDPage currently displayed in the specified page 
	view. This does not acquire the page. Do not use this result 
	across methods that might change the current page. To obtain 
	a value that can be used across such calls, use PDDocAcquirePage() 
	instead. 
	@param pageView IN/OUT The page view whose PDPage is obtained. 
	
	@return PDPage currently displayed in <code>pageView</code>, or <code>NULL</code> if there 
	is not a valid PDPage associated with <code>pageView</code>. 
	@see PDDocAcquirePage 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(PDPage, AVPageViewGetPage, (AVPageView pageView))

/**
	Gets the current zoom for <code>pageView</code>. The zoom factor is point-to-point, 
	not point-to-pixel. For example, a page that is 612 points 
	wide at 100% zoom should be 612 points wide on the monitor, 
	not 612 pixels. 
	@param pageView The page view whose zoom is obtained.
	@return Current zoom, as a fixed number measured in units in which 
	1.0 is 100% zoom. 
	@see AVPageViewGetPageToDevScaling 
	@see AVPageViewGetZoomType 
	@see AVPageViewZoomTo 

	@note In previous releases, you could use the zoom factor 
	to tranform page units (in points) to device units (in pixels). 
	In Acrobat 6.0 and later, because a point is no longer 
	assumed to be the same as a pixel, this is no longer accurate. 
	It is recommended that you use the page-to-device matrix 
	as much as possible, and use the AVPageViewGetPageToDevScaling() 
	method if you specifically need the point-to-pixel scaling 
	factor. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASFixed, AVPageViewGetZoom, (AVPageView pageView))

/**
	Gets the current zoom type. 
	@param pageView IN/OUT The page view whose zoom type is obtained. 
	
	@return The current zoom type. 
	@see AVPageViewGetZoom 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVZoomType, AVPageViewGetZoomType, (AVPageView pageView))

/**
	Gets the current page number for <code>pageView</code>. 
	@param pageView The page view whose current page number 
	is obtained.
	@return The current page number, or <code>-1</code> if <code>pageView</code> is invalid. The first 
	page in a document is page <code>0</code>. 
	@see AVPageViewGetFirstVisiblePageNum 
	@see AVPageViewGetLastVisiblePageNum 
	@see AVPageViewPageNumIsVisible 
	@see AVPageViewSetPageNum 

	@note If more than one page may be visible, use AVPageViewGetFirstVisiblePageNum(), 
	AVPageViewGetLastVisiblePageNum(), or AVPageViewPageNumIsVisible() 
	instead of this method. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(PDPageNumber, AVPageViewGetPageNum, (AVPageView pageView))

/**
	Gets the color that will be used for subsequent drawing 
	by AVPageViewDrawRect() and AVPageViewDrawRectOutline(). 
	@param pageView IN/OUT The page view whose drawing color is obtained. 
	
	@param color IN/OUT (Filled by the method) The color to get. 
	@exception genErrBadParm 
	@see AVPageViewSetColor 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGetColor, ( AVPageView pageView, PDColorValue color ))

/**
	Sets the color that will be used for subsequent drawing 
	by AVPageViewDrawRect() and AVPageViewDrawRectOutline(). 
	@param pageView IN/OUT The page view whose drawing color is set. 
	
	@param color IN/OUT The color to set. 
	@exception genErrBadParm 
	@see AVPageViewGetColor 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewSetColor, ( AVPageView pageView, PDConstColorValue color ))

/**
	Increments an internal variable. Neither drawing nor AVPageViewDidChange() 
	notifications will occur as long as the variable has a value 
	greater than zero. In addition, frames are not pushed onto 
	the view history stack. 
	@param pageView IN/OUT The page view whose <code>SuspendDraw</code> variable 
	is incremented. 
	@see AVPageViewEndOperation 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewBeginOperation, (AVPageView pageView))

/**
	Decrements an internal variable. Neither drawing nor AVPageViewDidChange() 
	notifications will occur as long as the variable has a value 
	greater than zero. In addition, frames are not pushed onto 
	the view history stack. 
	@param pageView IN/OUT The page view whose <code>SuspendDraw</code> variable 
	is decremented. 
	@notify AVPageViewDidChange 
	@see AVPageViewBeginOperation 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewEndOperation, (AVPageView pageView))

/**
	Goes to the specified page, retaining the current location on 
	the page and the current zoom (either explicit or a variable). 
	It invalidates the display, but does not perform an immediate 
	redraw. This allows your client to call AVPageViewZoomTo(), 
	AVPageViewScrollTo(), or both, and get only a single redraw 
	event. If you decide to do this, you should bracket the 
	calls with AVPageViewBeginOperation() and AVPageViewEndOperation(). 
	
	@param pageView The page view in which a different page 
	is displayed. 
	@param pageNum The page number of the destination page. 
	The first page in a document is page <code>0</code>.
	@notify AVPageViewDidChange 
	@see AVPageViewGetPage 
	@see AVPageViewGoBack 
	@see AVPageViewGoForward 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGoTo, (AVPageView pageView, PDPageNumber pageNum))

/**
	Sets the zoom factor and zoom type for the specified page 
	view. 
	@param pageView The page view to zoom. 
	@param zoomType The zoom type to set. 
	@param scale The zoom factor, specified as a magnification 
	factor (for example, 1.0 displays the document at actual 
	size). <code>scale</code> is ignored unless <code>zoomType</code> is AVZoomNoVary. 
	Use zero to inherit the zoom.
	@notify AVPageViewDidChange 
	@see AVPageViewScrollTo 
	@see AVPageViewScrollToRect 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewZoomTo, (AVPageView pageView, AVZoomType zoomType, ASFixed scale))

NPROC(void, oldAVPageViewScrollTo, (AVPageView pageView, ASInt16 xOrigin, ASInt16 yOrigin))
NPROC(void, oldAVPageViewScrollToRect, (AVPageView pageView, const oldAVRect *rect,ASBool favorLeft,
	ASBool favorTop, ASInt16 margin))

/**
	Scrolls up through a document, as if the user pressed the Enter 
	key. The scrolling follows articles if Acrobat is currently 
	in article-reading mode. 
	@param pageView IN/OUT The page view to scroll. 
	@notify AVPageViewDidChange 
	@see AVPageViewReadPageDown 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewReadPageUp, (AVPageView pageView))

/**
	Scrolls down through a document, as if the user pressed the 
	Enter key. The scrolling follows articles if Acrobat is 
	currently in article-reading mode. 
	@param pageView IN/OUT The page view to scroll. 
	@notify AVPageViewDidChange 
	@see AVPageViewReadPageUp 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewReadPageDown, (AVPageView pageView))

/**
	Goes to the previous view on the view stack, if a previous 
	view exists. This might result in a different document being 
	made active. 
	@param pageView IN/OUT The page view to change. 
	@notify AVPageViewDidChange 
	@see AVPageViewGoForward 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewGoBack, (AVPageView pageView), AVPageViewDoGoBack)

/**
	Goes to the next view on the view stack, if a next view 
	exists. This might result in a different document being 
	made active. 
	@param pageView IN/OUT The page view to change. 
	@notify AVPageViewDidChange 
	@see AVPageViewGoBack 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewGoForward, (AVPageView pageView), AVPageViewDoGoForward)

/**
	Builds a PDViewDestination from the current zoom and position. 
	
	@param pageView The page view from whose current view 
	the destination is created. 
	@param fitType The ASAtom specifying the fit type that 
	the view destination will have. The string associated with 
	<code>fitType</code> must be one of View Destination Fit Types. 
	@param srcPDDoc The document in which the view destination 
	is used.
	@return The newly created view destination. 
	@see PDViewDestCreate 
	@see PDActionGetDest 
	@see PDActionNewFromDest 
  	@ref ViewDestinationFitTypes
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
UNPROC(PDViewDestination, AVPageViewToViewDest, (AVPageView pageView, ASAtom fitType,
	PDDoc srcPDDoc))

NPROC(void, oldAVPageViewInvalidateRect, (AVPageView pageView, oldAVRect *area))

/**
	Forces any pending updates for the specified page view to 
	finish drawing. 
	@param pageView IN/OUT The AVPageView to redraw. 
	@see AVPageViewInvalidateRect 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewDrawNow, (AVPageView pageView))
NPROC(void, oldAVPageViewInvertRect, (AVPageView pageView, const oldAVRect *rect, ASBool highlight))
NPROC(void, oldAVPageViewInvertRectOutline, (AVPageView pageView, const oldAVRect *rect))
NPROC(void, oldAVPageViewDrawRectOutline, (AVPageView pageView, const oldAVRect *rect,
	ASInt16 lineWidth, ASFixed * dashArray, AVTArraySize arrayLen))
NPROC(void, oldAVPageViewDrawRect, (AVPageView pageView, const oldAVRect *rect))
NPROC(void, oldAVPageViewGetMousePosition, (AVPageView pageView, ASInt16 *x, ASInt16 *y))
NPROC(void, oldAVPageViewDragOutNewRect, (AVPageView pageView, ASInt16 xStart, ASInt16 yStart,
	oldAVRect *resultRect))
NPROC(void, oldAVPageViewDragRect, (AVPageView pageView, ASInt16 xStart, ASInt16 yStart,
	oldAVRect *startRect, oldAVRect *resultRect, ASInt32 dragType, oldAVRect *extrema))

SPROC(void, oldAVAppRegisterForPageViewDrawing, (oldAVPageViewDrawProc proc, void* data),
	oldAVPageViewRegisterForDrawing)

/**
  	<p>Un-registers a user-supplied page view drawing procedure. </p>
	
	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>

	@note Superseded by AVAppUnregisterForPageViewDrawingEx() 
	in Acrobat 6.0. 
	@param proc The original callback.
	@see AVAppRegisterForPageViewDrawing 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppUnregisterForPageViewDrawing, (AVPageViewDrawProc proc),
	AVPageViewUnregisterForDrawing)


/**
	Un-registers a user-supplied page view click procedure. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly-created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when unregistering. </p>
	@param clickProc IN/OUT The original callback. 
	@param data User-supplied private data.
	@see AVAppRegisterForPageViewClicks 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, oldAVAppRegisterForPageViewClicks, (oldAVPageViewClickProc clickProc, void* data),
	oldAVPageViewRegisterForClicks)

/**
	Un-registers a user-supplied page view click procedure. 
	
	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param clickProc The original callback.
	@see AVAppRegisterForPageViewClicks 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppUnregisterForPageViewClicks, (AVPageViewClickProc clickProc),
	AVPageViewUnregisterForClicks)

SPROC(void, oldAVAppRegisterForPageViewAdjustCursor, (oldAVPageViewCursorProc cursorProc,
	void* data), oldAVPageViewRegisterForAdjustCursor)

/**
	Un-registers a user-supplied adjust cursor procedure. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param cursorProc The original callback.
	@see AVAppRegisterForPageViewAdjustCursor 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppUnregisterForPageViewAdjustCursor, (AVPageViewCursorProc cursorProc),
	AVPageViewUnregisterForAdjustCursor)

NPROC(ASBool, oldAVPageViewIsAnnotAtPoint, (AVPageView pageView, ASInt16 xHit, ASInt16 yHit,
	PDAnnot *hitAnnot))
NPROC(void, oldAVPageViewGetAnnotRect, (AVPageView pageView, PDAnnot anAnnot, oldAVRect *rect))
NPROC(void, oldAVPageViewSetAnnotLocation, (PDAnnot anAnnot, AVPageView pageView,
	ASInt16 x, ASInt16 y))

/**
	Puts the specified page view into <i>article thread-reading</i> 
	mode. 
	@param pageView IN/OUT The page view to set to article thread-
	reading mode. 
	@param thread IN/OUT The thread to read. 
	@see AVPageViewGetActiveBead 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewStartReadingThread, (AVPageView pageView, PDThread thread))

/**
	Gets the index of the currently active thread in a page 
	view. 
	@param pageView IN/OUT The page view whose active thread index 
	is obtained. 
	@return The thread index of the current thread, or <code>-1</code> if there is 
	no current thread. 
	@see AVPageViewGetActiveBead 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTArraySize, AVPageViewGetThreadIndex, (AVPageView pageView))

/**
	Gets the currently active article thread bead in the specified 
	page view. 
	@param pageView IN/OUT The page view whose currently active bead 
	is obtained. 
	@return The current bead of the current thread, or a <code>NULL</code> Cos object 
	if there is no current thread. 
	@see AVPageViewGetThreadIndex 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(PDBead, AVPageViewGetActiveBead, (AVPageView pageView))

NPROC(ASBool, oldAVPageViewIsBeadAtPoint, (AVPageView pageView, ASInt16 xHit, ASInt16 yHit,
	PDBead *beadP))

#if !MAC_PLATFORM || (MAC_PLATFORM && !AS_ARCH_64BIT)
/**
	DEPRECATED in Acrobat 10
	Use AVPageViewAcquireDrawContext instead
 
	Acquires the platform-specific object needed to draw into 
	the Acrobat viewer's document window using a platform's 
	native graphics calls. When done, release it using AVPageViewReleaseMachinePort(). 
	
	@param pageView IN/OUT The AVPageView whose platform-dependent 
	port is acquired. 
	@return A platform-dependent value:

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Value</TH></TR>
	<TR><TD>Mac OS</TD><TD><code>GrafPtr</code>.</TD></TR>
	<TR><TD>Windows</TD><TD><code>WinPort</code>.</TD></TR>
	<TR><TD>UNIX</TD><TD><code>Widget</code>.</TD></TR>
	</TABLE>

	@see AVPageViewReleaseMachinePort 
	@see AVPageViewAcquireDrawContext
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void*, AVPageViewAcquireMachinePort, (AVPageView pageView), AVPageViewGetMachinePort)

/**
	DEPRECATED in Acrobat 10
	Use AVPageViewReleaseDrawContext instead
 
	Releases the platform-specific object needed to draw into 
	Acrobat's document window using a platform's native graphics 
	calls. 
	@param pageView IN/OUT The AVPageView whose platform-dependent 
	port is released. 
	@param port IN/OUT The platform-specific port to release. 
	@see AVPageViewAcquireMachinePort 
	@see AVPageViewReleaseDrawContext
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewReleaseMachinePort, (AVPageView pageView, void* port),
	AVPageViewFreeMachinePort)
#endif /* #if !MAC_PLATFORM || (MAC_PLATFORM && !AS_ARCH_64BIT) */

/**
	Gets the matrix that transforms user space coordinates to 
	device space coordinates for the specified page view. 
	@param pageView The page view whose transformation matrix 
	is obtained. 
	@param pageToDevMatrix (Filled by the method) A pointer 
	to the transformation matrix.
	@see AVPageViewGetDevToPageMatrix 
	@see AVPageViewGetPageToDevScaling 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGetPageToDevMatrix, (AVPageView pageView, ASFixedMatrix *pageToDevMatrix))

/**
	Gets the matrix that transforms device space coordinates 
	to user space coordinates for the specified page view. 
	@param pageView IN/OUT The page view whose matrix is obtained. 
	
	@param devToPageMatrix IN/OUT (Filled by the method) A pointer to 
	the transformation matrix. 
	@see AVPageViewGetPageToDevMatrix 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGetDevToPageMatrix, (AVPageView pageView, ASFixedMatrix *devToPageMatrix))

SPROC(void, oldAVPageViewPointToDevice, (AVPageView pageView, const ASFixedPointP p,
	ASInt16 *x, ASInt16 *y), oldAVPagePointToDevice)
SPROC(void, oldAVPageViewDevicePointToPage, (AVPageView pageView, ASInt16 x, ASInt16 y,
	ASFixedPoint *p), oldAVPageDevicePointToPage)
SPROC(void, oldAVPageViewRectToDevice, (AVPageView pageView, const ASFixedRectP p, oldAVRect* rect),
	oldAVPageRectToDevice)
SPROC(void, oldAVPageViewDeviceRectToPage, (AVPageView pageView, const oldAVRect* rect,
	ASFixedRect *p), oldAVPageDeviceRectToPage)

/**
	Gets a flag indicating which modifier keys are currently 
	being pressed. 
	@return An OR of the Modifier Keys. 
	@see AVSysMouseIsStillDown 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVFlagBits32, AVSysGetModifiers, (void))

/**
	Tests whether the mouse button is still being pressed. 
	@return <code>true</code> if the user is holding the mouse button down and has 
	not released it since the last mouse-down event, <code>false</code> otherwise. 
	
	@see AVSysGetModifiers 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVSysMouseIsStillDown, (void))

/**
	Beeps. 
	@param duration IN/OUT Always pass 0. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVSysBeep, (ASInt32 duration))

/**
	Gets the specified cursor. The cursor can subsequently be 
	displayed using AVSysSetCursor(). 
	@param cursorID IN/OUT The cursor to show. It must be one of the 
	Predefined Cursors. 
	@return The specified cursor. 
	@see AVSysGetCursor 
	@see AVSysSetCursor 
  	@ref cursorID
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVCursor, AVSysGetStandardCursor, (ASInt32 cursorID))

/**
	Sets the cursor to the specified AVCursor. 
	@param cursor The cursor to display. Predefined platform-independent 
	cursors can be obtained using AVSysGetStandardCursor(). Clients 
	can use their own custom cursors as follows: 
	<p>Mac OS developers:
	32/64-bit: Cast <code>NSImage*<code> to AVCursor and pass to AVSysSetCursor</p>
	DEPRECATED 32-bit: Use the Mac OS Toolbox <code>GetCursor</code> call to retrieve your 
	cursor from a resource. Cast the resulting <code>CursHandle</code> to 
	an AVCursor and pass it to AVSysSetCursor().</p> 
	<p>Windows developers: 
	Use the Windows API function <code>LoadCursor</code> to retrieve your 
	cursor resource. Cast the resulting <code>HCURSOR</code> to an AVCursor 
	and pass it to AVSysSetCursor().</p>
	@see AVSysGetCursor 
	@see AVSysGetStandardCursor 
	@see AVSysSetWaitCursor 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVSysSetCursor, (AVCursor cursor))

/**
	Gets the current cursor. Use this method when you want to 
	change the cursor temporarily and be able to restore it 
	to its current shape. 
	@return The current cursor. 
	@see AVSysGetStandardCursor 
	@see AVSysSetCursor 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVCursor, AVSysGetCursor, (void))

NPROC(void, oldAVToolBarGetFrame, (AVToolBar toolBar, oldAVRect *frame))

/**
	Gets the toolbar button that has the specified name. 
	@param toolBar The toolbar in which the button is located. 
	
	@param buttonName The ASAtom for the button to get. The 
	character string representing <code>buttonName</code> can be converted 
	to an ASAtom using ASAtomFromString(). See Toolbar and Toolbar 
	Button Names for a list of the names of the built-in buttons.
	@return The button with the specified name; if the name is not found, 
	the return value is <code>NULL</code>. 
	@see AVLegacyToolBarEnumButtons 
  	@ref ToolbarButtonNames
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVToolButton, AVLegacyToolBarGetButtonByName, (AVToolBar toolBar, ASAtom buttonName))

/**
	Calls <code>enumProc</code> once for each toolbar button in the specified 
	toolbar. 

	<p>If a tool button has a flyout, this is a separate toolbar 
	from the toolbar returned by AVAppGetLegacyToolBar(); enumerating 
	the toolbar buttons on this main toolbar does not enumerate 
	the toolbar buttons on any flyout. To enumerate the toolbar 
	buttons on a button's flyout, call AVLegacyToolButtonGetFlyout() 
	to get its associated toolbar, then call AVLegacyToolBarEnumButtons() 
	with this toolbar. </p>
	
	@param toolBar IN/OUT The toolbar whose buttons are enumerated. 
	
	@param enumProc IN/OUT A user-supplied procedure to call once for 
	each button. The enumeration ends if <code>enumProc</code> returns <code>false</code>. 
	
	@param clientData IN/OUT A pointer to user-supplied data to pass 
	to <code>enumProc</code> each time it is called. 
	@see AVAppGetLegacyToolBar 
	@see AVLegacyToolBarGetButtonByName 
	@see AVLegacyToolButtonGetFlyout 
	@see AVLegacyToolButtonSetExternal 

	@note AVLegacyToolBarEnumButtons does not enumerate toolbar buttons 
	that are marked as external by AVLegacyToolButtonSetExternal(). 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolBarEnumButtons, (AVToolBar toolBar, AVToolButtonEnumProc enumProc,
	void *clientData))

/**
	Inserts a button into a toolbar. Call AVLegacyToolBarUpdateButtonStates() 
	after adding a button to update the toolbar. 
	@param toolBar The toolbar into which a button is added. 
	
	@param button The button to add to the toolbar. 
	@param before If <code>true</code>, <code>button</code> is added before <code>otherButton</code>; 
	if <code>false</code>, it is added after. If <code>otherButton</code> is <code>NULL</code> and 
	<code>before</code> is <code>true</code>, the button is added to the beginning of 
	the toolbar. If <code>otherButton</code> is <code>NULL</code> and <code>before</code> is <code>false</code>, 
	the button is added to the end of the toolbar. 
	@param otherButton A button relative to which the new 
	button is added.
	@exception genErrNoMemory 
	@see AVLegacyToolButtonRemove 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolBarAddButton, (AVToolBar toolBar, AVToolButton button, ASBool before,
	AVToolButton otherButton))

/**
	Gets the number of buttons in <code>toolbar</code>. 
	@param toolBar IN/OUT The toolbar whose button count is obtained. 
	
	@return The number of buttons in <code>toolBar</code>. 
	@see AVAppGetLegacyToolBar 
	@see AVLegacyToolButtonGetFlyout 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVTArraySize, AVLegacyToolBarGetNumButtons, (AVToolBar toolBar))

/**
	Tests whether there is room in a toolbar for an additional 
	specified number of buttons and separators. 

	<p>On Windows, this method assumes the application window has 
	been maximized. </p>
	@param toolBar The toolbar to check. 
	@param nButtons The number of buttons. 
	@param nSeparators The number of separators.
	@return <code>true</code> if there is room in <code>toolBar</code> to add <code>nButtons</code> and <code>nSeparators</code>, 
	<code>false</code> otherwise. 
	@see AVAppGetLegacyToolBar 
	@see AVLegacyToolBarGetFrame 
	@see AVLegacyToolBarGetNumbuttons 
	@see AVLegacyToolButtonGetFlyout 
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVLegacyToolBarIsRoomFor, (AVToolBar toolBar, AVTCount nButtons, AVTCount nSeparators))

/**
	Forces a redraw of <code>toolbar</code>. Call this method when a toolbar 
	button is added or removed, or one of the buttons changes 
	state. 
	@param toolbar IN/OUT The toolbar to redraw. 
	@see AVAppGetLegacyToolBar 
	@see AVLegacyToolBarGetFrame 
	@see AVLegacyToolBarIsRoomFor 
	@see AVLegacyToolButtonGetFlyout 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolBarUpdateButtonStates, (AVToolBar toolbar))

/**
	Creates a toolbar button with the specified name, icon and 
	long-menus state. It can also be used to create a separator 
	with the specified name. 
	@param name The ASAtom corresponding to the button's name. 
	The character string for <code>name</code> can be converted to an ASAtom 
	using ASAtomFromString(). 
	@param icon The icon to use for this button. On Windows, 
	<code>icon</code> is an 18x18 icon with a light gray background (that 
	is, RGB values of 192,192,192). 
	@param longOnly (Ignored in Acrobat 3.0 or later) If <code>true</code>, 
	the button is shown only when the user selects Full Menus 
	in the Acrobat viewer. If <code>false</code>, it is shown in both Full menu 
	and Short menu modes. 
	@param isSeparator If <code>true</code>, the new button is a separator 
	used to leave space between groups of related buttons. For 
	separators, <code>icon</code>, the button's AVExecuteProc(), AVComputeEnabledProc(), 
	and AVComputeMarkedProc() are ignored. In addition, separators 
	are not clickable. If <code>false</code>, the button is a normal toolbar 
	button.
	@return The newly created button. 
	@exception genErrNoMemory 
	@see AVLegacyToolButtonDestroy 
	@see AVLegacyToolButtonSetExecuteProc 
	@see AVLegacyToolButtonSetComputeEnabledProc 
	@see AVLegacyToolButtonSetComputeMarkedProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVToolButton, AVLegacyToolButtonNew, (ASAtom name, AVIcon icon, ASBool longOnly,
	ASBool isSeparator))

/**
	Removes the specified button from the toolbar and destroys 
	the button. Call AVLegacyToolBarUpdateButtonStates() after removing 
	a button to update the toolbar. 
	@param toolButton IN/OUT The button to destroy. 
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolButtonDestroy, (AVToolButton toolButton))

/**
	Removes the specified button from the toolbar, but does 
	not destroy the button. Call AVLegacyToolBarUpdateButtonStates() 
	after removing a button to update the toolbar. 
	@param button IN/OUT The button to remove. 
	@see AVLegacyToolBarAddButton 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolButtonRemove, (AVToolButton button))

/**
	Tests whether a toolbar button is a separator or a normal 
	button. 
	@param button IN/OUT The button to test. 
	@return <code>true</code> if the button is a separator, <code>false</code> otherwise. 
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVLegacyToolButtonIsSeparator, (AVToolButton button))

/**
	Gets the ASAtom corresponding to the name of the specified 
	toolbar button. 
	@param button The toolbar button whose name is obtained. 
	
	@return The ASAtom corresponding to the toolbar button's name. ASAtom 
	can be converted to a character string using ASAtomGetString(). 
	See Toolbar and Toolbar Button Names for a list of the built-in 
	button names. 
	@see AVLegacyToolBarGetButtonByName 
  	@ref ToolbarButtonNames
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASAtom, AVLegacyToolButtonGetName, (AVToolButton button))

/**
	Executes the AVExecuteProc() associated with button, if it 
	exists. This AVExecuteProc() is set by AVLegacyToolButtonSetExecuteProc(). 
	It does nothing if AVLegacyToolButtonIsEnabled() for the button returns 
	<code>false</code>. 
	@param button IN/OUT The button whose execute proc is executed. 
	
	@see AVLegacyToolButtonIsEnabled 
	@see AVLegacyToolButtonNew 
	@see AVLegacyToolButtonSetExecuteProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolButtonExecute, (AVToolButton button))

/**
	Sets the user-supplied procedure to call to actually perform 
	the button's intended function. 
	@param button IN/OUT The button whose AVExecuteProc() is set. 
	@param proc IN/OUT A user-supplied procedure to call when <code>button</code> 
	is executed. 
	@param clientData IN/OUT A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called. 
	@see AVLegacyToolButtonNew 
	@see AVLegacyToolButtonSetComputeEnabledProc 
	@see AVLegacyToolButtonSetComputeMarkedProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolButtonSetExecuteProc, (AVToolButton button, AVExecuteProc proc,
	void *clientData))

/**
	Sets the AVComputeEnabledProc() associated with a toolbar 
	button. This routine determines whether the button can be 
	selected. 
	@param button The button whose AVComputeEnabledProc() is 
	set. 
	@param proc A user-supplied procedure to call whenever the 
	Acrobat viewer needs to know whether <code>button</code> should be enabled. 
	
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see AVLegacyToolButtonIsEnabled 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolButtonSetComputeEnabledProc, (AVToolButton button,
	AVComputeEnabledProc proc, void* clientData))

/**
	Sets the AVComputeMarkedProc() associated with a toolbar button. 
	A marked button appears pressed on the screen. 
	@param button The button whose AVComputeMarkedProc() is 
	set. 
	@param proc A user-supplied callback to call whenever the 
	Acrobat viewer needs to know whether the specified toolbar 
	button should be marked. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see AVLegacyToolButtonIsMarked 
	@see AVLegacyToolButtonNew 
	@see AVLegacyToolButtonSetComputeEnabledProc 
	@see AVLegacyToolButtonSetExecuteProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVLegacyToolButtonSetComputeMarkedProc, (AVToolButton button, AVComputeMarkedProc proc,
	void* clientData))

/**
	Tests whether a toolbar button is enabled. 
	@param button The button to test.
	@return <code>true</code> if the button's AVComputeEnabledProc() returns <code>true</code>, <code>false</code> 
	otherwise. 
	@see AVLegacyToolButtonSetComputeEnabledProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVLegacyToolButtonIsEnabled, (AVToolButton button))

/**
	Tests whether the specified button is marked. 
	@param button The button to test.
	@return <code>true</code> if the button's AVComputeMarkedProc() returns <code>true</code>, <code>false</code> 
	if <code>button</code> is not marked or does not have an AVComputeMarkedProc(). 
	
	@see AVLegacyToolButtonSetComputeMarkedProc 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVLegacyToolButtonIsMarked, (AVToolButton button))

/**
	Gets the currently active tools's type. See Toolbar and 
	Toolbar Button Names for a list of the built-in tool types. 
	
	@param tool The tool whose type is obtained.
	@return The ASAtom returned can be converted to a string using ASAtomGetString(). 
	
	@see AVAppEnumTools 
	@see AVAppGetActiveTool 
	@see AVAppGetDefaultTool 
	@see AVAppGetLastActiveTool 
	@see AVAppGetToolByName 
	@see AVToolIsPersistent 
  	@ref ToolbarButtonNames
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASAtom, AVToolGetType, (AVTool tool))

/**
	Tests whether the specified tool is in a state keeping it 
	active through multiple operations rather than only once, 
	then restoring the previous tool. This method is called 
	by another one-shot tool's <code>Activate</code> procedure. Two one-shot 
	tools cannot cycle, because if the previous tool was not 
	persistent, the second non-persistent tool reverts to the 
	default tool. 
	@param tool IN/OUT The tool whose persistence flag is tested. 
	
	@return <code>true</code> if the tool is persistent, <code>false</code> otherwise. 
	@see AVAppEnumTools 
	@see AVAppGetActiveTool 
	@see AVAppGetDefaultTool 
	@see AVAppGetLastActiveTool 
	@see AVAppGetToolByName 
	@see AVToolGetType 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVToolIsPersistent, (AVTool tool))

NPROC(AVWindow, oldAVWindowNew, (AVWindowLayer layer, AVFlagBits32 flags, oldAVWindowHandler handler,
	ASExtension owner))
NPROC(AVWindow, oldAVWindowNewFromPlatformThing, (AVWindowLayer layer, AVFlagBits32 flags,
	oldAVWindowHandler handler, ASExtension owner, AVPlatformWindowRef platformThing))

/**
	Destroys the specified window and all associated memory. 
	It closes the window without calling the window handler's AVWindowWillCloseProc() 
	(that is, this operation cannot be rejected). 
	@param win IN/OUT The window to destroy. 
	@see AVWindowNew 
	@see AVWindowNewFromPlatformThing 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowDestroy, (AVWindow win))

/**
	Simulates a user's click on a window's box. This calls the 
	AVWindowWillCloseProc() of the <code>win</code> object's AVWindowHandler. 
	@param win IN/OUT The window to close. 
	@param quitting IN/OUT If <code>true</code>, assume the application is trying 
	to quit. If <code>false</code>, assume the user clicked on the window's 
	close box. 
	@return <code>true</code> if the window was closed, <code>false</code> if the window handler's 
	AVWindowWillCloseProc() aborted the close by returning <code>false</code>. 
	
	@see AVWindowCenter 
	@see AVWindowHide 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVWindowUserClose, (AVWindow win, ASBool quitting))

/**
	Maximizes the specified window. On Mac OS, this corresponds 
	to calling the ZoomWindow Toolbox function. 
	@param win The window to maximize. 
	@param maximize <code>true</code> to maximize the window, <code>false</code> to 
	return it to its non-maximized state.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowMaximize, (AVWindow win, ASBool maximize))

/**
	Shows the specified window. 
	@param win IN/OUT The window to show. 
	@see AVWindowHide 
	@see AVWindowIsVisible 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowShow, (AVWindow win))

/**
	Hides the specified window. Hiding a window makes it invisible; 
	it does not minimize or icon-ize it. 

	<p>On Windows, a document window can be minimized using code 
	based on the following: </p>
	
	<p><code>theAVWindow = AVDocGetAVWindow( theAVDoc); </code></p>
	<p><code>theThing = (HWND) AVWindowGetPlatformThing( theAVWindow); </code></p>
	<p><code>wasVisible = ShowWindow(theThing, SW_MINIMIZED);</code></p> 
	

	@param win IN/OUT The window to hide. 
	@see AVWindowShow 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowHide, (AVWindow win))

/**
	Tests whether a window is displayed on the screen. 
	@param win The window whose visibility is tested.
	@return <code>true</code> if the window is displayed on the screen (even if it 
	is currently obscured by another window), <code>false</code> otherwise. 
	
	@see AVWindowBecomeKey 
	@see AVWindowHide 
	@see AVWindowShow 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVWindowIsVisible, (AVWindow win))

/**
	Returns a pointer to the platform-specific thing associated 
	with the window. Do not confuse this with the owner data 
	(see also AVWindowGetOwnerData). 

	<p>AVDocWantsToDie() is broadcast after AVDocSetDead() has been 
	called, which would warn that the AVWindow associated with that window is <code>NULL</code>. </p>

	@param win IN/OUT Platform-dependent window thing:

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Value</TH></TR>
	<TR><TD>Windows</TD><TD><code>HWND</code>.</TD></TR>
	<TR><TD>Mac OS</TD><TD><code>WindowRef</code> for Carbon-based windows,
	<code>NULL</code> for Cocoa-based windows (most windows are Cocoa as of 8.0)</TD></TR>
	<TR><TD>UNIX</TD><TD><code>Widget</code>.</TD></TR>
	</TABLE>

	@return The platform-dependent thing for the window. Returns <code>NULL</code> if the 
	window is associated with an AVDoc that has been set dead 
	by AVDocSetDead(). 
	
	@see AVDocGetAVWindow 
	@see AVWindowNewFromPlatformThing 
	@see AVWindowNew 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVPlatformWindowRef, AVWindowGetPlatformThing, (AVWindow win))

/**
	Gets a window's owner data. The owner data is private data 
	for the use of the window's creator. For example, if a client 
	uses its own class library, it might use the owner data 
	field to store a pointer to the object owning the AVWindow. 
	
	@param win The window whose owner data is obtained.
	@return A pointer to owner data for <code>win</code>. 
	@see AVWindowSetOwnerData 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void *, AVWindowGetOwnerData, (AVWindow win))

/**
	Sets a window's owner data. The owner data is private data 
	for the use of the window's creator. For example, if a client 
	uses its own class library, it might use the owner data 
	field to store a pointer to the object owning the AVWindow. 
	
	@param win The window whose owner data is set. 
	@param newData A pointer to the new owner data for <code>win</code>.
	@see AVWindowGetOwnerData 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowSetOwnerData, (AVWindow win, void *newData))

NPROC(AVTArraySize, oldAVWindowGetTitle, (AVWindow win, char *buffer, AVTBufferSize bufferLen))

NPROC(void, oldAVWindowSetTitle, (AVWindow win, const char *newTitle))
NPROC(void, oldAVWindowGetFrame, (AVWindow win, oldAVRect *rect))
NPROC(void, oldAVWindowSetFrame, (AVWindow win, const oldAVRect *rect))
NPROC(void, oldAVWindowGetInterior, (AVWindow win, oldAVRect *rect))

/**
	Brings the specified window to the front. 
	@param win IN/OUT The window to bring to the front. 
	@notify AVAppFrontDocDidChange 
	@see AVWindowBecomeKey 
	@see AVWindowIsKey 
	@see AVWindowSetWantsKey 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowBringToFront, (AVWindow win))
NPROC(void, oldAVWindowInvalidateRect, (AVWindow win, const oldAVRect *rect))

/**
	Redraws the invalid regions of the specified window. 
	@param win IN/OUT The window to draw. 
	@see AVWindowInvalidateRect 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowDrawNow, (AVWindow win))

/**
	AVWIN_WANTSKEY is deprecated and ignored.
	Because of this, AVWindowSetWantsKey effectively does nothing.
	
	@param wantsKey IN/OUT If <code>true</code>, <code>win</code> is willing to become the key 
	window, <code>false</code> otherwise. 
	@see AVWindowBecomeKey 
	@see AVWindowResignKey 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowSetWantsKey, (AVWindow win, ASBool wantsKey))

/**
	Tests whether the specified window is the key window. The 
	key window is the window that receives mouse clicks. 

	<p>UNIX users: This method is a no-op. </p>
	@param win The window to test.
	@return <code>true</code> if <code>win</code> is the key window, <code>false</code> otherwise. 
	@see AVWindowBecomeKey 
	@see AVWindowBringToFront 
	@see AVWindowSetWantsKey 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVWindowIsKey, (AVWindow win))

/**
	Makes <code>win</code> the key window (regardless of the setting of its 
	<code>wantsKey</code> flag) if the window is visible. 

	<p>UNIX developers: This method is a no-op. </p>
	@param win IN/OUT The window that is to become the key window. 
	
	@see AVWindowSetWantsKey 
	@see AVWindowIsVisible 
	@see AVWindowResignKey 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowBecomeKey, (AVWindow win))

/**
	Use this method when you want <code>win</code> to resign its key window 
	status. Another window might pick up key window status as 
	a result. You must first call AVWindowSetWantsKey() with a 
	value of <code>false</code> for the <code>wantsKey</code> parameter or your window 
	may immediately become the key window again. 

	<p>UNIX developers: This method is a no-op. </p>
	@param win IN/OUT The window resigning key window status. 
	@see AVWindowBecomeKey 
	@see AVWindowSetWantsKey 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowResignKey, (AVWindow win))

#if CAN_SELECT_GRAPHICS

/**
	Creates a graphics selection. After creation, the selection 
	can be set using AVDocSetSelection(). 
	@param pageView The AVPageView in which a graphics selection 
	is created. 
	@param selRect A pointer to the ASFixedRect bounding the 
	region from which a graphics selection is created, specified 
	in user space coordinates.
	@return The newly created AVGrafSelect, or <code>NULL</code> if <code>selRect</code> is <code>NULL</code> 
	or is an empty rectangle. 
	@exception genErrBadParm 
	@exception genErrNoMemory 
	@see AVGrafSelectDestroy 
	@see AVDocSetSelection 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVGrafSelect, AVGrafSelectCreate, ( AVPageView pageView, const ASFixedRectP selRect ))

/**
	Destroys a graphics selection. Use this method to destroy 
	the selection only if you have not called AVDocSetSelection() 
	with it. If the selection has been set by a call to AVDocSetSelection(), 
	it will automatically be destroyed by a call to AVDocClearSelection() 
	or the next call to AVDocSetSelection(). 
	@param avGraf IN/OUT The graphics selection to destroy. 
	@exception genErrBadParm 
	@see AVGrafSelectCreate 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVGrafSelectDestroy, ( AVGrafSelect avGraf ))

/**
	Gets the specified graphics selection's bounding rectangle. 
	
	@param avGraf IN/OUT The graphics selection whose bounding rectangle 
	is obtained. 
	@param boundRectP IN/OUT A pointer to the graphics selection's bounding 
	rectangle, specified in user space coordinates. 
	@exception genErrBadParm 
	@see AVGrafSelectCreate 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVGrafSelectGetBoundingRect, ( AVGrafSelect avGraf, ASFixedRect *boundRectP ))
#else
NOPROC(AVGrafSelectCreate)
NOPROC(AVGrafSelectDestroy)
NOPROC(AVGrafSelectGetBoundingRect)
#endif

/**
	Displays the settings dialog box for the built-in standard security 
	handler, allowing the user to change a document's permissions. 
	The initial configuration of the dialog box may be set by populating 
	the StdSecurityDataRec structure prior to calling the method. 
	@param pdDoc IN/OUT The document for which new security data is 
	obtained. 
	@param secData IN/OUT (Filled by the method) A pointer to a StdSecurityDataRec 
	structure to hold the permissions selected by the user. 
	
	@return <code>true</code> if the user confirmed the selections, <code>false</code> 
	if the user pressed Cancel. 
	@see PDDocAuthorize 
	
	@note This method does not modify the document in any way. 
	It is present in the API so that other security handlers 
	can use it, if they choose, as a standard way to display or 
	obtain permissions from a user. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
UNPROC(ASBool, AVCryptDoStdSecurity, (PDDoc pdDoc, void *secData))

/**
	Displays a standard dialog box that lets a user enter a 
	password. This method does not attempt to validate the password 
	entered by the user. That operation is performed by PDDocAuthorize(). 
	
	<p>It is the client's responsibility to release the memory 
	associated with the password, using ASfree(). </p>

	<p>This method is present in the API so that other security 
	handlers can use it, if they choose, as a standard way to 
	obtain a password from a user. </p>
	@param pdDoc IN The document whose password is obtained from 
	the user. This parameter is used to generate a label within 
	the dialog box. 
	@param permWanted IN The permissions requested. It must be an 
	OR of the PDPerms values. 
	@param authDataP OUT If 
	the method returns <code>true</code>, <code>authData</code> will reference a <code>char*</code> 
	containing the password. 
	@return <code>true</code> if the user confirmed the selection, <code>false</code> 
	if the user clicked Cancel. 
	@see PDDocAuthorize 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVCryptGetPassword, (PDDoc pdDoc, PDPerms permWanted, void **authDataP))

/**
	Saves a file, handling any user interface (for 
	example, a Save File dialog box) as needed. Clients do 
	not need to call this method directly, but it is available 
	for clients that need to override the Acrobat viewer's built-in 
	save method. For example, it can be used to save the changes made to a PDF 
	file into a special file, but not save the original PDF 
	file. 

	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param doc The document to save.
	@return <code>true</code> if the document was successfully saved, <code>false</code> otherwise. 
	
	@see AVDocDoCopyAs 
	@see AVDocDoPrint 
	@see AVDocDoSaveAs 
	@see AVDocDoSaveAsWithParams 
	@note Not replaceable in Adobe Reader.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
UPROC(ASBool, AVDocDoSave, (AVDoc doc))

/**
	Gets the AVDoc client (container application) name. 

	<p>This method can be used by a client to determine which client 
	application caused the Acrobat viewer to open a document. </p>
	
	@param avDoc The document whose client name is obtained. 
	
	@param buffer (Filled by the method) The buffer into which 
	the client name is written. It may contain up to 255 characters. 
	The client name is <code>NULL</code>-terminated. If the client name is 
	longer than <code>bufSize</code>, the first <code>bufSize-1</code> bytes are copied 
	into it, followed by a <code>NULL</code>. 
	@param bufSize The size of <code>buffer</code> in bytes.
	@return The number of characters written into <code>buffer</code>, excluding 
	the <code>NULL</code> termination. It returns <code>0</code> if the specified document 
	does not have a client associated with it. 
	@see AVDocSetClientName 
	@since PI_ACROVIEW_VERSION >= 0x00020001
*/
/* New for 2.1 */
NPROC(AVTArraySize, AVDocGetClientName, ( AVDoc avDoc, char *buffer, AVTBufferSize bufSize ))

/**
	Sets the AVDoc client (container application) name. This 
	method can be used by clients that open documents in the 
	viewer via DDE or Apple events. Most clients will not open 
	documents in this way, however, making this method unnecessary 
	for most clients. 
	@param avDoc The document whose client names is set. 
	@param clientName The buffer from which the client name 
	is read. It may contain up to 255 characters, and must be <code>NULL</code>-terminated.
	@exception genErrNoMemory 
	@see AVDocGetClientName 
	@since PI_ACROVIEW_VERSION >= 0x00020001
*/
NPROC(void, AVDocSetClientName, ( AVDoc avDoc, char *clientName ))

/**
	Gets the text from the specified text selection, converts 
	it to the specified format, and passes it to a user-supplied 
	procedure. 
	@param doc IN/OUT The document from which the text is obtained. 
	@param pageNum IN/OUT The page number in <code>doc</code> from which the text is 
	obtained. The first page in a document is page <code>0</code>. 
	@param pdText IN/OUT The text selection whose text is obtained. 
	Pass <code>NULL</code> to get all the text on the page. 
	@param format IN/OUT The format in which the text is desired. The 
	following are allowed values (these strings must be converted 
	to ASAtom objects using ASAtomFromString()): 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Allowed value</TH><TH>Description</TH></TR>
	<TR><TD><code>All</code></TD><TD></TD>(Mac OS/Windows) Calls <code>copyProc</code> once with each available format.</TR>
	<TR><TD><code>Text</code></TD><TD>(Mac OS/Windows) Calls <code>copyProc</code> twice. The first time, it 
	passes the text in the specified selection. The text is 
	passed using the same platform encoding as when it is put 
	onto the clipboard (<code>format = Text</code>). The second time, it 
	passes a Unicode version of the text (<code>format = UCSText</code>).</TD></TR>
	<TR><TD>Style</TD><TD>(Mac only) Calls <code>copyProc</code> twice. The first time, 
	it passes the <code>Text</code> representation. The second time, it passes 
	a <code>StyleInfo</code> record.</TD></TR>
	<TR><TD><code>RTF</code></TD><TD>(Mac OS/Windows) Calls <code>copyProc</code> 
	twice. The first time, it passes the text in Rich Text Format. 
	The second time, it passes a Unicode version of the text. 
	Upon using or manipulating the text, you should check the 
	format in <code>copyProc</code>.</TD></TR>
	</TABLE>

	@param copyProc IN/OUT A user-supplied callback to which the text 
	is passed. 
	@param clientData IN/OUT A pointer to user-supplied data to pass 
	to <code>copyProc</code> each time it is called. 
	@exception pdErrOpNotPermitted 
	@see PDTextSelectCreateRanges 
	@see PDTextSelectCreatePageHilite 
	@see PDTextSelectCreateWordHilite 
	@see PDDocCreateTextSelect 
	@see PDWordFinderEnumWords 
	@see PDWordFinderAcquireWordList 
	@since PI_ACROVIEW_VERSION >= 0x00020001
*/
SPROC(void, AVDocGetPageText, (AVDoc doc, PDPageNumber pageNum, PDTextSelect pdText, ASAtom format, AVTextCopyProc copyProc, void *clientData), AVDocGetPageTextHost)

/* New for 2.2 */
/**
	Sets the text to show in tooltips. This text is shown 
	when the cursor is held over a toolbar button for a period 
	of time. 

	<p>In Acrobat 4.0 and later, toolbar buttons can also have 
	single key shortcuts assigned to them. (Conceptually, tools 
	have shortcuts but the shortcuts are attached to the buttons). 
	This is done by appending a vertical bar character <code>'|'</code> followed 
	by the shortcut to the button's tooltip text.</p>

	<p>Appending the shortcut to the tooltip text allows it to 
	localize at the same time as the tooltip text. </p>
	
	@example Here is the tooltip text for the Hand tool:

	<p><code>'Hand Tool (H)|h' </code></p>

	<p>The trailing <code>'|h'</code> portion indicates that the Hand tool uses 
	the <code>'H'</code> key as the shortcut. This portion is stripped off 
	before the tooltip is displayed. </p>

	<p>This behavior only applies to tooltips where the '|' is 
	the second-to-last character. </p>

	@param button The toolbar button to which a tooltip is 
	added. 
	@param text The text to show.
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVLegacyToolButtonSetHelpText, (AVToolButton button, const char* text))

SPROC(PDTextSelect, oldAVPageViewTrackText, (AVPageView pageView, ASInt16 xHit, ASInt16 yHit, PDTextSelect current), oldAVPageViewTrackTextHost)

/**
	Inverts the given text selection on the current page using 
	the current AVPageView color. 
	@param pageView IN/OUT The page view. 
	@param textSelect IN/OUT The words to highlight. 
	@see AVPageViewTrackText 
	@see AVPageViewInvalidateText 
	@see AVPageViewPointInText 
	@see PDDocCreateTextSelect 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVPageViewHighlightText, (AVPageView pageView, PDTextSelect textSelect))

/**
	Invalidates the bits that AVPageViewHighlightText() touches. 
	
	@param pageView IN/OUT The page view. 
	@param textSelect IN/OUT The words to invalidate. 
	@see AVPageViewHighlightText 
	@see AVPageViewPointInText 
	@see AVPageViewTrackText 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVPageViewInvalidateText, (AVPageView pageView, PDTextSelect textSelect))
NPROC(ASBool, oldAVPageViewPointInText, (AVPageView pageView, ASInt16 xHit, ASInt16 yHit, PDTextSelect pdText))

/**
	Returns the page number of the first page that is visible 
	on the screen. 
	@param pageView The page view whose first visible page 
	number is obtained.
	@return The page number of the first page that is visible on the screen. 
	
	@see AVPageViewGetLastVisiblePageNum 
	@see AVPageViewPageNumIsVisible 
	@see AVPageViewGetPageNum 
	@see AVPageViewSetPageNum 
	@see AVPageViewGetSelectedAnnotPageNum 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(PDPageNumber, AVPageViewGetFirstVisiblePageNum, (AVPageView pageView))

/**
	Returns the page number of the last page that is visible 
	on the screen. 
	@param pageView The page view whose last visible page 
	number is obtained.
	@return The page number of the last page that is visible on the screen. 
	
	@see AVPageViewGetFirstVisiblePageNum 
	@see AVPageViewPageNumIsVisible 
	@see AVPageViewGetPageNum 
	@see AVPageViewSetPageNum 
	@see AVPageViewGetSelectedAnnotPageNum 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(PDPageNumber, AVPageViewGetLastVisiblePageNum, (AVPageView pageView))

/**
	Determines if a given page number is visible. 
	@param pageView IN/OUT The page view. 
	@param pageNum IN/OUT The page number corresponding to the view 
	of interest. 
	@return <code>true</code> if <code>pageNum</code> is visible, <code>false</code> otherwise. 
	@see AVPageViewGetFirstVisiblePageNum 
	@see AVPageViewGetLastVisiblePageNum 
	@see AVPageViewGetPageNum 
	@see AVPageViewGetSelectedAnnotPageNum 
	@see AVPageViewSetPageNum 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVPageViewPageNumIsVisible, (AVPageView pageView, PDPageNumber pageNum))

/**
	Sets the current logical page of the page view, which might 
	not be the same as the current number indicated on the screen. 
	
	<p>Client writers in general do not need this, but if you wish 
	to perform some operation on a page other than the one returned 
	by AVPageViewGetPageNum(), you can use this call to temporarily 
	set the page. You must restore the page number when you 
	are done. You should avoid causing any major changes to 
	the page view (such as scrolling) to ensure that you end 
	up restoring the page to the correct value. </p>
	@param pageView The page view. 
	@param pageNum The page number.
	@return Previous page number. 
	@see AVPageViewGetFirstVisiblePageNum 
	@see AVPageViewGetLastVisiblePageNum 
	@see AVPageViewGetPageNum 
	@see AVPageViewGetSelectedAnnotPageNum 
	@see AVPageViewPageNumIsVisible 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(PDPageNumber, AVPageViewSetPageNum, (AVPageView pageView, PDPageNumber pageNum))

/**
	Returns the page number of the currently selected annotation, 
	or <code>-1</code> if no annotation is selected. 
	@param pageView The page view whose selected annotation 
	page is obtained.
	@return Returns the page number of the currently selected annotation, 
	or <code>-1</code> if no annotation is selected. 
	@see AVPageViewGetFirstVisiblePageNum 
	@see AVPageViewGetLastVisiblePageNum 
	@see AVPageViewPageNumIsVisible 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(PDPageNumber, AVPageViewGetSelectedAnnotPageNum, (AVPageView pageView))

/**
	Sends auxiliary data to an AVDoc. If an AVAuxDataHandler 
	exists for the data type, the handler is called with <code>avDoc</code>, 
	<code>auxDataType</code>, and <code>auxData</code>. The definition of the auxiliary 
	data is dependent on the AVAuxDataHandler. 

	<p>For any value of <code>auxDataType</code>, the <code>auxData</code> parameter must 
	be predefined so that a user of this method knows what type 
	of data to send. It is expected that the implementor of 
	an AVAuxDataHandler provides this definition. </p>
	@param avDoc IN/OUT The target document. 
	@param auxDataType IN/OUT The type of data being sent. 
	@param auxData IN/OUT A pointer to the data. 
	@param auxDataLen IN/OUT The length of the data. 
	@return <code>true</code> if <code>auxData</code> was accepted by a handler, <code>false</code> otherwise. 
	
	@see AVHasAuxDataHandler 
	@see AVRegisterAuxDataHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVDocSendAuxData, (AVDoc avDoc, ASAtom auxDataType, void *auxData, AVTBufferSize auxDataLen))

/**
	Indicates whether a handler exists for the specified data 
	type. 
	@param auxDataType IN/OUT The name of the data handler being queried. 
	@return <code>true</code> if a handler is registered, <code>false</code> if a handler is not 
	registered. 
	@see AVDocSendAuxData 
	@see AVRegisterAuxDataHandler 
	@see AVUnregisterAuxDataHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVHasAuxDataHandler, (ASAtom auxDataType))

/**
	Obsolete.  Registers an old <code>AuxDataHandler</code>.  
	@see AVRegisterAuxDataHandler
*/
NPROC(ASBool, oldAVRegisterAuxDataHandler, (ASExtension extension, ASAtom auxDataType, oldAVAuxDataHandler handler))

/**
	Un-registers a previously registered auxiliary data handler. 
	@param extension The <code>gExtensionID</code> of the client un-registering 
	the handler. 
	@param auxDataType The type of data for the handler being 
	un-registered. 
	@param handler The handler to un-register.
	@return <code>true</code> if the handler was un-registered, <code>false</code> if the handler 
	could not be un-registered. For example, it returns <code>false</code> if 
	the handler was never registered. 
	@see AVHasAuxDataHandler 
	@see AVRegisterAuxDataHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVUnregisterAuxDataHandler, (ASExtension extension, ASAtom auxDataType, AVAuxDataHandler handler))

PROC(void, oldAVDocPrintPagesWithParams, (AVDoc doc, AVDocPrintParams params))
NPROC(void, oldAVPageViewDrawCosObj, (AVPageView pageView, CosObj cosObj, oldAVRect* r))

/**
	Indicates that the file stream for this document is terminated, 
	although the AVDoc is still open. No more data can be read 
	from this AVDoc. 

	<p>AVDocs that are marked as dead may start returning <code>NULL</code> 
	at any time between the initial call to AVDocSetDead() and 
	the time that the AVDoc is actually closed. Callers of 
	AVDocGetAVWindow() and other AVDoc property methods must check 
	for a <code>NULL</code> return value. </p>
	@param doc IN/OUT The document to set as dead. 
	@param dead IN/OUT <code>true</code> if the document's file stream is terminated, 
	<code>false</code> otherwise. 
	@notify AVDocWantsToDie (if dead is <code>true</code>) 
	@see AVDocClose 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVDocSetDead, (AVDoc doc, ASBool dead))

/**
	Indicates that the specified toolbar button should be displayed 
	in toolbars contained in external windows, such as in a 
	web browser. 
	@param button The button. 
	@param external Indicates whether to show the button in 
	external windows. It must be one of Tool Button Flags. 
	@see AVLegacyToolButtonNew 

	@note Call AVLegacyToolButtonSetExternal() before adding the tool button 
	with AVLegacyToolBarAddButton(). If you want to change the tool button's 
	location after it has been added, call AVLegacyToolButtonSetExternal() 
	and add the button again with AVLegacyToolBarAddButton(). 
	
	@note To enable a toolbar button in an external window, first 
	remove the button from the toolbar, then turn on the TOOLBUTTON_EXTERNAL 
	flag and add the button back onto the toolbar.
  	@ref ToolButtonFlags
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
SPROC(void, AVLegacyToolButtonSetExternal, (AVToolButton button, AVTFlagBits16 external), AVLegacyToolButtonSetLocation)


/**
	Returns <code>true</code> if the application is in a state in which it 
	is safe to destroy a document that uses the multi-read protocol. 
	The multi-read protocol is implemented on some platforms 
	using a <i>yield</i> mechanism, which involves a transfer of 
	information between two applications. This function returns 
	<code>true</code> if there is no task executing in the application that 
	could invoke such a transfer. Attempting to close a document 
	during such a transfer can cause a deadlock event or a crash. 
	
	<p>When a multi-read protocol document is closed, the client 
	must register an AVAppIdle task. During its idle proc, it 
	must call AVAppHandlePlatformEvent(). If the call returns 
	<code>true</code>, it is safe to call AVDocClose(). If it returns <code>false</code>, 
	the client must retry at its next idle proc call. AVAppHandlePlatformEvent() 
	always returns <code>false</code> if invoked from an AVExecuteProc(). </p>

	<p>This method does not protect against clients that invoke 
	the API outside of AVAppIdle(), an AVExecuteProc(), or other 
	explicit API methods. For example, if a Windows client uses 
	a Windows <code>SetTimer</code> event to call an API method, AVAppHandlePlatformEvent() 
	may erroneously return <code>true</code>. Therefore, clients should always 
	use the API methods. </p>
	@return <code>true</code> if it is safe to call AVDocClose(), <code>false</code> otherwise. 
	
	@see AVDocClose 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVAppIsIdle, (void))

NPROC(AVDoc, oldAVDocOpenFromASFileWithParams, (ASFile file, const char *tempTitle, oldAVDocOpenParams params))

/**
	Used by page caching code to determine the next page to 
	cache (and at what scale). Allows clients to do their own 
	page caching. 

	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param pageView The page view. 
	@param pdDoc (Filled by the method) The PDDoc containing 
	the next page to cache. 
	@param pageNum (Filled by the method) The next page to 
	cache. 
	@param scale (Filled by the method) The scale of the next 
	page to cache.
	@return <code>true</code> if the next page was cached, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
PROC(ASBool, AVPageViewGetNextView, (AVPageView pageView, PDDoc* pdDoc, PDPageNumber* pageNum, ASFixed* scale))

NPROC(void, oldAVDocGetViewDef, (AVDoc doc, oldAVDocViewDef viewDef))
SPROC(void, oldAVDocSetViewDef, (AVDoc doc, oldAVDocViewDef viewDef), oldAVDocUseViewDef)

/**
	Handles a platform-specific event. Use this method to dispatch 
	a platform-specific event structure to an AVWindow. This method may raise exceptions, depending on the event.
	@param win IN/OUT The window with the event to handle. 
	@param platformEvent IN/OUT A pointer to a platform-specific event 
	structure. 
	@return <code>true</code> if the event was handled, <code>false</code> otherwise. 
	@see AVAppHandleAppleEvent 
	@see AVAppHandlePlatformEvent 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVWindowHandlePlatformEvent, (AVWindow win, void *platformEvent))

/**
	Queries the AVWindow for the appropriate cursor for display 
	at the given point (in the AVWindow object's device coordinate 
	space). This method may raise exceptions, depending on the method called.
	@param win The AVWindow to query. 
	@param x The x-coordinate of a point in <code>win</code>. 
	@param y The y-coordinate of a point in <code>win</code>.
	@return The AVCursor appropriate for the specified point in the 
	window. 
	@since PI_MACINTOSH_VERSION >= 0x00020002
*/
NPROC(AVCursor, AVWindowGetCursorAtPoint, (AVWindow win, AVlCoord x, AVlCoord y))

/**
	Displays a modal dialog box that allows a user to specify an 
	action. For example, it is used by forms to add actions to fields. 
	
	@param doc IN/OUT The document in which the action is specified. 
	
	@param action IN/OUT The specified action. 
	@param dialogTitle IN/OUT The title for the dialog box. 
	@return <code>true</code> if the user clicked the Set Link button, <code>false</code> if the 
	user clicked Cancel. 
	@see AVDocPerformAction 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
XNPROC(ASBool, AVDocDoActionPropsDialog, (AVDoc doc, PDAction* action, const char* dialogTitle))

/**
	Gets the transition handler registered for the specified 
	transition type. 
	@param name IN/OUT Type of transition handler, which may be one 
	of the types provided in the Acrobat viewer or a new type 
	registered by a plug-in. 
	@return The transition handler for the type, or <code>NULL</code> if no transition 
	handler is registered for that type. 
	@see AVAppRegisterTransHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(AVTransHandler, AVAppGetTransHandlerByType, (ASAtom name))

/**
	Enumerates all registered transition handlers, calling the 
	user-supplied procedure for each. 
	@param enumProc IN/OUT A user-supplied procedure to call once for 
	each transition handler. 
	@param clientData IN/OUT A user-supplied data passed to <code>enumProc</code> 
	each time it is called. 
	@exception Raises an exception only if <code>enumProc</code> raises an exception. 
	
	@see AVAppGetTransHandlerByType 
	@see AVAppRegisterTransHandler 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVAppEnumTransHandlers, (AVTransHandlerEnumProc enumProc, void *clientData))

/**
	Registers a transition handler within Acrobat. If <code>avth</code> has 
	not implemented the <code>GetType</code> callback, it will not be registered. 
	
	@param avth IN/OUT An AVTransHandler structure containing pointers 
	to the transition handler's functions. This structure must 
	not be freed after calling AVAppRegisterTransHandler(). 
	@see AVAppEnumTransHandlers 
	@see AVAppGetTransHandlerByType 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVAppRegisterTransHandler, (AVTransHandler avth))

/**
	Displays a file dialog box which can be used to save the document to a  
	new name. It allows clients (such as Optimizer) to do their 
	own file saving. 

	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param doc The document to save.
	@return <code>true</code> if the document was successfully saved, <code>false</code> otherwise. 
	
	@see AVDocDoCopyAs 
	@see AVDocDoPrint 
	@see AVDocDoSave 
	@see AVDocDoSaveAsWithParams 
	@note Not replaceable in Adobe Reader.
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
UPROC(ASBool, AVDocDoSaveAs, (AVDoc doc))

/**
	Sets the layout mode for a page view. 
	@param pageView IN/OUT The page view whose layout mode is set. 
	
	@param mode IN/OUT The new layout mode for the page view. 
	@see AVPageViewGetLayoutMode 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVPageViewSetLayoutMode, (AVPageView pageView, PDLayoutMode mode))

/**
	Gets the page layout mode for a page view. 
	@param pageView IN/OUT The page view whose layout mode is obtained. 
	
	@return The <code>pageView</code> object's page layout mode, described in PDLayoutMode. 
	
	@see AVPageViewSetLayoutMode 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(PDLayoutMode, AVPageViewGetLayoutMode, (AVPageView pageView))
NPROC(void, oldAVPageViewInsetRect, (AVPageView pageView, const oldAVRect* rr, ASBool down))

/**
	Determines whether a given document is displayed in an application's 
	external window (such as in a web browser's window). 
	@param doc The document being tested.
	@return <code>true</code> if the given document is displayed in an application's 
	external window, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVDocIsExternal, (AVDoc doc))

/**
	Causes the given page view to change to the view given by 
	<code>viewDest</code> and <code>sourceZoom</code>. 
	@param pageView IN/OUT The page view to change. 
	@param viewDest IN/OUT The view destination. 
	@param sourceZoom IN/OUT The zoom factor to use, unless <code>viewDest</code> 
	specifies inheriting the current zoom, which is the zoom 
	in effect when a link is clicked. 
	
	<p>For example, <code>sourceZoom</code> 
	is used only if the view destination is of type <code>XYZ</code> (
	that is, it specifies a point and a zoom) and the zoom is 
	zero (meaning 'inherit the current zoom'). In this case, 
	<code>sourceZoom</code> is used as the zoom to inherit. </p>

	@see PDViewDestCreate 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVPageViewUseThisDestination, (AVPageView pageView, PDViewDestination viewDest, ASFixed sourceZoom))

/**
	Determines if the current user is authorized to open a document. 
	
	<p>If no password is required to open the document, the user 
	will be granted access automatically. If a password is required, 
	the method queries the user for the password and uses it 
	to request open permissions for the document. </p>

	<p>Clients: This method can be used as a standard, interactive 
	authorization callback when opening documents through PDDocOpen(). </p>
	
	@param pdDoc The document.
	@return <code>true</code> if the user is authorized to open the document, <code>false</code> 
	otherwise. 
	@see PDDocAuthorize 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVAuthOpen, (PDDoc pdDoc))


/* new procs for 3.1 */

/**
	Makes a copy of the annotation for the (possibly different) 
	specified AVDoc. It calls the AVAnnotHandlerCopyProc() callback 
	in AVAnnotHandler. 
	@param fromDoc The document containing the annotation. 
	@param anAnnot The annotation to copy. 
	@param toDoc The document to which the annotation is copied.
	@return A copy of the annotation. 
	@exception avErrBadAnnotationCopy is raised if the associated 
	annotation handler has not implemented the AVAnnotHandlerCopyProc() callback. 
	It raises the standard exceptions if memory limit problems occur. 

	@note The Acrobat viewers define AVAnnotHandlerCopyProc() 
	callbacks for all currently defined annotations. 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(PDAnnot, AVDocCopyAnnot, (AVDoc fromDoc, PDAnnot anAnnot, AVDoc toDoc))

/**
	Makes a copy of the annotation for the (possibly different) 
	specified AVDoc. 

	<p>This copy includes only those fields that are described 
	in the <i>PDF Reference</i> as common to all annotations (this 
	list currently includes Type, Subtype, Rect, Border, C, 
	T, M, F, H, AS, BS, and AA). This method is a proper starting 
	point for the design of a Copy method for a custom annotation. 
	This allows a client to concentrate on those member objects 
	specific to the custom annotation. </p>

	<p>It raises the standard exceptions if memory limit problems 
	occur.</p> 

	@param fromDoc The document whose annotation is copied. 
	
	@param anAnnot The annotation to copy. 
	@param toDoc The document to which the annotation is copied.
	@return A copy of the annotation. 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(PDAnnot, AVDocCopyAnnotCommon, (AVDoc fromDoc, PDAnnot anAnnot, AVDoc toDoc))

/**
	Makes a copy of the action for the (possibly different) 
	specified AVDoc. It calls the AVActionCopyProc() callback in 
	AVActionHandlerProcs. 

	<p>It raises the standard exceptions if memory limit problems 
	occur.</p> 

	@param fromDoc IN/OUT The document containing the action. 
	@param anAction IN/OUT The PDAction to copy. 
	@param toDoc IN/OUT The document to which the action is copied. 
	
	@return A copy of the action. 
	@exception avErrBadActionCopy is raised if the associated action handler has not 
	implemented the AVActionCopyProc() callback. 
	@exception pdErrBadAction is raised if the action dictionary is invalid. 
	@exception pdErrOpNotPermitted is raised if the user does not have the required 
	permissions level for <code>destDoc</code> to perform this operation. 
	
	@note The Acrobat viewers define AVActionCopyProc() callbacks 
	for all currently defined actions. 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(PDAction, AVDocCopyAction, (AVDoc fromDoc, PDAction anAction, AVDoc toDoc))

/**
	Makes a copy of the action for the (possibly different) 
	specified AVDoc. 

	<p>This copy includes only those fields that are described 
	in the PDF Reference as common to all actions (this list 
	currently includes Type, S, and Next). This method is a 
	proper starting point for the design of a Copy method 
	for a custom action. This allows a client to concentrate 
	on those member objects specific to the custom action. </p>

	<p>It raises the standard exceptions if memory limit problems 
	occur.</p> 

	@param fromDoc The document containing the action. 
	@param anAction The PDAction to copy. 
	@param toDoc The document to which the action is copied.
	@return A copy of the action. 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(PDAction, AVDocCopyActionCommon, (AVDoc fromDoc, PDAction anAction, AVDoc toDoc))

/**
	Copies any additional actions (AA) from a Cos Dictionary 
	to a Cos Dictionary in the (possibly different) specified 
	AVDoc. 

	<p>This method copies the following keys: E, X, D, U, O, C, 
	FP, PP, NP, and LP. This method is designed to aid clients 
	in copying additional actions for pages. </p>

	<p>For copying annotations, it is better to use AVDocCopyAnnotCommon(). </p>

	<p>This method raises the standard exceptions if memory limit problems 
	occur.</p> 
	
	@param avFr The document containing <code>srcDict</code>. 
	@param coFr The dictionary from which the action is 
	copied. 
	@param avTo The document to which the action is copied. 
	@param coTo The dictionary to which the action is 
	copied.
	@return A copy of the action. 
	@exception cosErrExpectedDict is raised if the object stored under the /AA key 
	in <code>srcDict</code> is not a CosDict. 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(void, AVDocCopyAdditionalActions, (AVDoc avFr, CosObj coFr, AVDoc avTo, CosObj coTo))
NPROC(void, oldAVPageViewDrawCosObjEx, (AVPageView pageView, CosObj cosObj, oldAVRect* r, ASFixedMatrix *matrix))

/**
	Creates a destination info object from a given AVPageView 
	and fit type. 
	@param pageView The page view from whose current view 
	the destination information is created. 
	@param fitType The ASAtom specifying the fit type that 
	the view destination will have. The string associated with 
	fit type must be one of View Destination Fit Types.
	@return The newly created destination info. 
	@see AVDestInfoDestroy 
	@see AVPageViewUseDestInfo 
  	@ref ViewDestinationFitTypes
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/

NPROC(AVDestInfo, AVPageViewToDestInfo, (AVPageView pageView, ASAtom fitType))

/**
	Causes the given page view to change to the view given by 
	an AVDestInfo object. 
	@param pageView IN/OUT The page view to change. 
	@param destInfo IN/OUT The destination to use. 
	@see AVPageViewToDestInfo 
	@see AVPageViewUseThisDestination 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(void, AVPageViewUseDestInfo, (AVPageView pageView, AVDestInfo destInfo))

/**
	Releases the memory associated with a destination. 
	@param destInfo IN/OUT The destination information object to destroy. 
	
	@see AVPageViewToDestInfo 
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(void, AVDestInfoDestroy, (AVDestInfo destInfo))

/**
	Prompts the user with a standard file dialog box and copies 
	the file byte for byte. It displays a progress monitor 
	showing the progress of the file copy. 
	@param avDoc IN/OUT The document to copy. 
	@return <code>true</code> if the copy was successful, <code>false</code> otherwise. 
	@see AVDocDoPrint 
	@see AVDocDoSave 
	@see AVDocDoSaveAs 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVDocDoCopyAs, (AVDoc avDoc))


/* Acrobat 4.0 Additions */
NPROC(void, oldAVPageViewDrawAnnotSequence, (AVPageView pv, PDAnnot an, oldAVRect *bbox))

/**
	Performs the print operation, including user dialog boxes. 

	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param doc IN/OUT The document to print. 
	@notify AVDocDidPrint 
	@notify AVDocWillPrint 
	@see AVDocDoCopyAs 
	@see AVDocDoSave 
	@see AVDocPrintPages 
	@see AVDocPrintPagesWithParams 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
PROC(void, AVDocDoPrint, (AVDoc doc))

/**
	Saves a file, using the parameters specified in <code>params</code>. 
	
	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param doc IN/OUT The document to save. 
	@param params IN/OUT A structure with information describing how 
	the AVDoc is saved. 
	@return <code>true</code> if the document was successfully saved, <code>false</code> otherwise. 
	
	@see AVDocDoCopyAs 
	@see AVDocDoPrint 
	@see AVDocDoSave 
	@see AVDocDoSaveAs 
	@note Not replaceable in Adobe Reader.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
UPROC(ASBool, AVDocDoSaveAsWithParams, (AVDoc doc, AVDocSaveParams params))

/**
	Gets the information structure associated with an annotation 
	handler. 
	@param avanh IN/OUT The annotation handler for which the 
	information structure is needed. 
	@return The information structure associated with the annotation handler, 
	or <code>NULL</code> if the handler does not support this operation. 
	
	@see AVAnnotHandlerDeleteInfo 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(AVAnnotHandlerInfo, AVAnnotHandlerGetInfo, (AVAnnotHandler avanh))

/**
	Deletes the AVAnnotHandlerInfo associated with an annotation 
	handler. 
	@param avanh IN/OUT The annotation handler. 
	@param info IN/OUT The AVAnnotHandlerInfo associated with the 
	annotation handler. <code>info</code> contains the user interface name 
	of the annotation type and the platform-dependent bitmap used 
	as the annotation icon. 
	@see AVAnnotHandlerGetInfo 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVAnnotHandlerDeleteInfo, (AVAnnotHandler avanh, AVAnnotHandlerInfo info))
#if HAS_MENUS
/* AVPageViewDoPopupMenu
** Display the given AVMenu as a popup menu anchored at xHit and yHit.  The coordinates
** are relative to the passed AVPageView.  "rightMouse" is <code>true</code> if the right mouse button 
** (where applicable) was used to invoke the popup.  "choice" is the index of the AVMenuItem 
** which should appear under the mouse at pop-up time.  
*/
NPROC(AVMenuItem, oldAVPageViewDoPopupMenu, (AVPageView pageView, AVMenu menu, ASInt16 xHit, ASInt16 yHit, ASBool rightMouse, AVMenuIndex choice))
#else	/* !HAS_MENUS */
NOPROC(AVPageViewDoPopupMenu)
#endif	/* !HAS_MENUS */


/**
	Calculates where an annotation is drawn with no zoom or 
	no rotation, as specified by the annotation flags. This 
	method generalizes AVPageViewGetAnnotRect(). 
	@param pv IN/OUT The page view used for the transformation. 
	@param flags IN/OUT Annotation flags obtained by PDAnnotGetFlags. 
	
	@param ar IN/OUT A pointer to the annotation's bounding rectangle, 
	specified in user space coordinates. 
	@param mr IN/OUT (Filled by the method) The transformation matrix. 
	
	@see AVPageViewAppearanceGetAVMatrix 
	@see AVPageViewDeviceRectToPageRZ 
	@see AVPageViewGetAnnotRect 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVPageViewTransformRectRZ, (AVPageView pv, AVTFlagBits flags, ASFixedRect *ar, ASFixedMatrix *mr))

/**
	Calculates a matrix for use with AVPageViewDrawCosObj() or 
	AVPageViewDrawCosObjEx() that leaves the appearance unrotated 
	and un-zoomed as specified by <code>flags</code>. This is typically used 
	in conjunction with drawing an annotation appearance represented 
	by <code>appear</code>. 
	@param PageView The page view for which the matrix is 
	calculated. 
	@param flags Annotation flags obtained by PDAnnotGetFlags(). 
	
	@param appear The appearance of the object, which is a Form 
	XObject. 
	@param ar The bounding rectangle for <code>appear</code>. 
	@param mr (Filled by the method) The transformation matrix.
	@see AVPageViewDrawCosObj 
	@see AVPageViewDrawCosObjEx 
	@see AVPageViewTransformRectRZ 
	@note The flag value numeric types changed in Acrobat 6.0.
	@since PI_ACROVIEW_VERSION >= 0x000400000x00060000.
*/
NPROC(void, AVPageViewAppearanceGetAVMatrix, (AVPageView PageView, AVFlagBits32 flags, CosObj appear, ASFixedRect *ar, ASFixedMatrix *mr))

/**
	Gets the number of a page containing an annotation. 
	@param pageView The page view with the annotation. 
	@param annot The annotation whose page number is obtained.
	@return The number of the page containing <code>annot</code>. 
	@see AVPageViewGetFirstVisiblePageNum 
	@see AVPageViewGetLastVisiblePageNum 
	@see AVPageViewPageNumIsVisible 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(PDPageNumber, AVPageViewGetVisibleAnnotPage,(AVPageView pageView, PDAnnot annot))

/**
	Inverts the interior of a quad.
	@param pageView The page view in which the inverted quad 
	is drawn. 
	@param quad A pointer to the quad to <code>invert</code>, specified in 
	device space coordinates. Use AVPageViewPointToDevice() to 
	convert the coordinates of the four corners of the quad 
	that is specified in user space. 
	@param highlight If <code>true</code>, it uses the highlight mode specified 
	by <code>avpHighlightMode</code> in the Acrobat viewer's preferences 
	file (see AVAppSetPreference()). If <code>false</code>, it uses a default 
	highlighting mode.
	@see AVPageViewInvertRect 
	@note The coordinate amd flag value numeric types changed in Acrobat 6.0.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVPageViewInvertQuad, (AVPageView pageView, const Quad *quad, ASBool highlight))

/**
	Given an ASTimeRecP, it gets a string representing the date 
	and time. This routine is locale-friendly. 

	<p>The returned string is allocated using ASmalloc() and must 
	be freed by the caller using ASfree(). </p>
	@param timeRec IN/OUT A pointer to an ASTimeRec structure. 
	@return A string representing the date and time. It returns <code>NULL</code> if the conversion 
	fails. 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(char*, AVSysAllocTimeStringFromTimeRec, (ASTimeRecP timeRec)) 

/**
	Handles a platform-specific event. This method may raise exceptions, depending on the event.
	@param platformEvent IN/OUT A pointer to a platform-specific event 
	structure. 
	@return <code>true</code> if the event was handled, <code>false</code> otherwise. 
	@see AVAppHandleAppleEvent 
	@see AVWindowHandlePlatformEvent 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVAppHandlePlatformEvent, (void *platformEvent))

/**
	Sets the read-only state of an AVDoc. 
	@param doc IN/OUT The AVDoc to set to read-only. 
	@param readOnly IN/OUT <code>true</code> if the given document is set to read-
	only, <code>false</code> if it is set to read-write. 
	@see AVDocIsReadOnly 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVDocSetReadOnly, (AVDoc doc, ASBool readOnly))

/**
	Determines whether an AVDoc is read-only. 
	@param doc IN/OUT The AVDoc whose read-only state is checked. 
	
	@return <code>true</code> if the document is read-only, <code>false</code> otherwise. 
	
	@see AVDocSetReadOnly 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVDocIsReadOnly, (AVDoc doc))

/**
	Shows or hides the controls in the status area at the bottom 
	of a page view. 
	@param pageView The page view whose controls are affected. 
	
	@param controlID The controls affected. 
	@param show <code>true</code> if the controls are displayed, <code>false</code> 
	if not shown.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVPageViewShowControl, (
	AVPageView pageView,
	AVPageViewControlID controlID,
	ASBool show))

/**
	Creates a new sub-toolbar for use as a toolbar button flyout. 
	
	<p>Flyouts are established by creating a new toolbar with AVLegacyToolBarNewFlyout(), 
	appending toolbar buttons to the new toolbar using <code>AVToolBar</code> 
	calls, and attaching that toolbar to a tool button, known 
	as the anchor button, with AVLegacyToolButtonSetFlyout(). </p>

	<p>This method creates a distinct toolbar from the toolbar 
	returned by AVAppGetLegacyToolBar(). </p>
	@return The newly created toolbar to use for a flyout. 
	@see AVLegacyToolButtonGetFlyout 
	@see AVLegacyToolButtonSetFlyout 

	@note The viewer makes a copy of the anchor button and attaches 
	it to the front of the flyout to achieve the correct visual 
	effect; the client does not need to do this. 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(AVToolBar, AVLegacyToolBarNewFlyout, (void))

/**
	Attaches a sub-toolbar or flyout to a toolbar button. A 
	copy of the button is attached to the front of the toolbar. 
	A click-hold pops up the flyout and allow the user to select 
	a different button. 

	<p>Flyouts are established by creating a new toolbar with AVLegacyToolBarNewFlyout(), 
	appending toolbar buttons to the new toolbar using AVToolBar 
	calls, and attaching that toolbar to a tool button, known 
	as the anchor button, with AVLegacyToolButtonSetFlyout(). </p>
	@param button IN/OUT The toolbar button to attach to the flyout.
	@param flyout IN/OUT The flyout to which <code>button</code> is attached. 
	@see AVLegacyToolBarNewFlyout 
	@see AVLegacyToolButtonGetFlyout 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVLegacyToolButtonSetFlyout, (AVToolButton button, AVToolBar flyout))

/**
	Gets the flyout attached to a toolbar button. A flyout is 
	a sub-toolbar attached to a toolbar button. 

	<p>This method gets a different toolbar from the toolbar returned 
	by AVAppGetLegacyToolBar(). </p>
	@param button The toolbar button whose flyout is obtained.
	@return The flyout associated with button. It returns <code>NULL</code> if there 
	is no flyout associated with button. 
	@see AVLegacyToolBarNewFlyout 
	@see AVLegacyToolButtonSetFlyout 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(AVToolBar, AVLegacyToolButtonGetFlyout, (AVToolButton button))


/**
	Attaches a menu to a toolbar button. 

	<p>If a tool button has no execute proc, the menu pops up when 
	the tool button is clicked. If the tool button does have 
	an execute proc, the user must click and hold on the button 
	for some time to display the menu. Simply clicking on the 
	button invokes the button's execute proc as usual. </p>
	@param button IN/OUT The toolbar button to which a menu is attached. 
	
	@param menu IN/OUT The menu to attach to <code>button</code>. 
	@see AVPageViewDoPopupMenu 
	@see AVLegacyToolButtonGetMenu 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVLegacyToolButtonSetMenu, (AVToolButton button, AVMenu menu))

/**
	Gets the menu attached to a toolbar button. 
	@param button IN/OUT The toolbar button to which a menu is attached. 
	
	@return The menu attached to <code>button</code>. 
	@see AVPageViewDoPopupMenu 
	@see AVLegacyToolButtonSetMenu 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(AVMenu, AVLegacyToolButtonGetMenu, (AVToolButton button))


/**
	Sets a new icon for a toolbar button. 

	<p>A tool button's icon can change dynamically. This allows 
	multi-state buttons, such as the one that opens and closes 
	the splitter bar, to change appearance appropriately. This 
	should allow multiple buttons to collapse into one. </p>

	<p>Most other aspects of a tool button, such as its execute proc 
	and tooltip text, can be changed on the fly using other 
	AVToolButton methods. </p>
	@param button IN/OUT The toolbar button whose icon is set. 
	@param icon IN/OUT The icon to place on button. 
	@see AVLegacyToolButtonGetIcon 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVLegacyToolButtonSetIcon, (AVToolButton button, AVIcon icon))

/**
	Gets the icon associated with the specified AVToolButton. 
	
	@param button The button whose icon is obtained.
	@return The icon associated with <code>button</code>. 
	@see AVLegacyToolButtonSetIcon 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(AVIcon, AVLegacyToolButtonGetIcon, (AVToolButton button))


SPROC(void, oldAVPageViewDeviceRectToPageRZ, (AVPageView pageView,
										   AVTFlagBits flags,
										   ASInt16 xHot,
										   ASInt16 yHot,
										   const oldAVRect* rect,
										   ASFixedRect *p),
	  oldAVPageDeviceRectToPageRZ)

/**
	Displays an alert containing the specified message, icon, 
	and one to three buttons with the specified titles. See 
	AVAlert for more information. 

	<p>On the Windows platform, the modal parent for <code>doc</code> (as returned 
	by WinAppGetModalParent()) is used as the owner window of 
	the message dialog box. As such, this method can be used 
	to display alert dialog boxes in the context of an external window 
	that is a web browser. </p>
	<p>Rules for the buttons:</p>
	<ul>
	<li> Use <code>NULL</code> to suppress a button's display. </li>
	<li> At least <code>button1</code> must be non-<code>NULL</code>.</li>
	<li> <code>button3</code> is not displayed if <code>button2</code> is <code>NULL</code>.</li>
	</ul>

	@param doc (Windows only) The AVDoc whose modal parent 
	is used as the owner window of the message dialog box. 
	@param iconType The icon to display. It must be one of the 
	AVAlert Icons. Mac users: These constants are defined 
	as per the standard Mac user interface guidelines. 
	
	@param msg The message to display. 
	@param button1 IN The title for the first button; it cannot be <code>NULL</code>. 
	@param button2 IN The title for the second button; it may be <code>NULL</code> (if so, <code>button3</code> is not displayed).
	@param button3 IN The title for the third button; it may be <code>NULL</code>.
	@param beep IN Pass <code>true</code> to perform a system beep when the 
	alert is shown.
	@return The button number (<code>1</code>, <code>2</code>, or <code>3</code>) on which the user clicked. 
	
	@see AVAlert 
	@see AVDocAlertConfirm 
	@see AVDocAlertNote 
	@see AVDocAlertYesNo 

	@note The implementations of the AVDocAlert methods call 
	AVAlert(), which is a replaceable method. If AVAlert() is replaced, 
	the <code>AVDocAlert</code> methods are also affected. 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASInt32, AVDocAlert, (AVDoc doc, AVIconType iconType, const char *msg,
							const char *button1, const char *button2,
							const char *button3, ASBool beep))

/**
	Displays a dialog box containing the ALERT_NOTE icon, the 
	specified message and an OK button. The method also performs 
	a system beep. See AVDocAlert() for more information. 
	@param doc IN/OUT (Windows only) The AVDoc whose modal parent 
	is used as the owner window of the message dialog box. 
	@param msg IN/OUT The message to display. 
	@see AVDocAlert 
	@see AVDocAlertConfirm 
	@see AVDocAlertYesNo 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVDocAlertNote, (AVDoc doc, const char *msg))

/**
	Displays a dialog box containing the ALERT_CAUTION icon, 
	the specified message, and OK and Cancel buttons. The method 
	also performs a system beep. See AVDocAlert() for more information. 
	
	@param doc IN/OUT (Windows only) The AVDoc whose modal parent 
	is used as the owner window of the message dialog box. 
	@param msg IN/OUT The message to display. 
	@return <code>true</code> if the user clicked OK, <code>false</code> if the user clicked Cancel. 
	
	@see AVDocAlert 
	@see AVDocAlertNote 
	@see AVDocAlertYesNo 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVDocAlertConfirm, (AVDoc doc, const char *msg))

/**
	Displays a dialog box containing the specified message, 
	icon, and two or three buttons with the titles Yes, No, 
	and (optionally) Cancel. See AVDocAlert() for more information. 
	
	@param doc IN/OUT (Windows only) The AVDoc whose modal parent 
	is used as the owner window of the message dialog box. 
	@param iconType IN/OUT The icon to display. It must be one of the 
	AVAlert Icons. Mac users: These constants are defined 
	as per the standard Mac user interface guidelines. 
	
	@param msg IN/OUT The message to display. 
	@param cancel IN/OUT <code>true</code> if a Cancel button should be provided, 
	<code>false</code> otherwise. 
	@param beep IN/OUT <code>true</code> if it beeps, <code>false</code> otherwise. 
	@return The button number (<code>1</code>, <code>2</code>, or <code>3</code>) on which the user clicked. 
	
	@see AVDocAlert 
	@see AVDocAlertConfirm 
	@see AVDocAlertNote 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASInt32, AVDocAlertYesNo, (AVDoc doc, AVIconType iconType,
								 const char *msg, ASBool cancel, ASBool beep))


/**
	Inserts a hidden menu into the menu bar. It does nothing if 
	<code>menubar</code> is <code>NULL</code> or <code>menu</code> is <code>NULL</code>. 
	@param menubar The menu bar into which the menu is added. 
	
	@param menu The menu to add.
	@exception genErrNoMemory 
	@see AVMenuIsHiddenOnMenubar 
	@see AVMenubarAddMenu 
	@see AVMenuNew 
	@see AVMenuRemove 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
/* Calls for adding a menu to the AVMenuBar without displaying it
   on the visible menu bar, and for asking if a menu has this
   property.
   */
NPROC(void, AVMenubarAddHiddenMenu, (AVMenubar menubar, AVMenu menu))

/**
	Tests whether a menu is hidden on the menu bar. 
	@param menu IN/OUT The menu to test. 
	@return <code>true</code> if <code>menu</code> is hidden, <code>false</code> otherwise. 
	@see AVMenubarAddHiddenMenu 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVMenuIsHiddenOnMenubar, (AVMenu menu))

/**
  	<p>Opens a specified help file from the default installation 
	help directory. If the help file is not found, it optionally 
	opens a dialog box asking if the user wants to search for 
	the help file.</p>

	@param fileName The help file name. This is not a fully qualified 
	path name, but the name of an individual help file such 
	as <code>"AcroHelp.pdf"</code>. 
	@param doSearch If <code>true</code> and the help file is not found, 
	it displays a dialog box asking if the user wants to search 
	for the help file. If <code>false</code>, it returns <code>false</code> if the help file 
	is not found.
	@return <code>true</code> if the help file is found, <code>false</code> otherwise. 

	@note Deprecated in Acrobat 6.0. It has been superseded 
	by AVAppOpenHelpFileWithParams(). 
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(ASBool, AVAppOpenHelpFile, (const char *fileName, ASBool doSearch))
NPROC(void, oldAVPageViewGetGrayRect, (AVPageView pageView, oldAVRect* greyRect))

/**
	Enumerates the pages on which there is a selection by calling 
	the current selection server's AVDocSelectionEnumPageRangesProc() 
	callback. 

	<p>This method allows you to determine which pages are currently 
	involved in a selection, regardless of the selection type. 
	This enables you to discover whether a given point is in 
	a selection.</p> 

	<p>Pages are enumerated in ascending order, and consecutive 
	pages are grouped into a single page range.</p> 
	@param doc IN/OUT The AVDoc from which to enumerate page ranges. 
	
	@param enumProc IN/OUT A user-supplied function that is called for 
	each page on which there is a selection. 
	@param clientData IN/OUT A pointer to user-supplied data to pass 
	to <code>enumProc</code> each time it is called. 
	@see AVDocEnumSelection 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVDocSelectionEnumPageRanges, (AVDoc doc, AVSelectionPageRangeEnumProc enumProc, void  *clientData))

/* Acrobat 4.05 Additions */

NPROC(void, oldAVWindowGetMinMaxSize, (AVWindow win, oldAVRect *rect))
NPROC(void, oldAVWindowSetMinMaxSize, (AVWindow win, const oldAVRect *rect))

/**
	Registers a user-supplied procedure to call each time a 
	key is pressed in an AVPageView. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param proc A user-supplied callback to call each time a 
	key is pressed. 
	@param data A pointer to user-supplied data to pass to <code>proc</code> 
	each time it is called.
	@exception genErrNoMemory 
	@see AVAppUnregisterForPageViewKeyDown 
	@since PI_ACROVIEW_VERSION >= 0x00040005
*/
NPROC(void, AVAppRegisterForPageViewKeyDown, (AVPageViewKeyDownProc proc, void* data))

/**
	Un-registers a user-supplied page view key down procedure. 
	
	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param proc The original callback.
	@exception genErrNoMemory 
	@see AVAppRegisterForPageViewKeyDown 
	@since PI_ACROVIEW_VERSION >= 0x00040005
*/
NPROC(void, AVAppUnregisterForPageViewKeyDown, (AVPageViewKeyDownProc proc))


/* Acrobat 5.0 Additions */


/**
	Registers an AVConversionToPDFHandler to import other file 
	formats. When a <code>ToPDF</code> converter is registered, the converter 
	is automatically added to the list of supported file formats 
	in the Open dialog box. In addition, the converter is displayed 
	in the list of <code>ToPDF</code> converters for the Batch framework. 
	@param conversionHandler IN/OUT The handler. 
	@see AVAppRegisterFromPDFHandler 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
UNPROC(void, AVAppRegisterToPDFHandler, (AVConversionToPDFHandler conversionHandler))

/**
	Registers an AVConversionFromPDFHandler to export from PDF 
	to other file formats. When a <code>FromPDF</code> converter is registered, 
	the converter is automatically added to the list of supported 
	file formats in the Save As dialog box. In addition, the converter 
	is displayed in the list of <code>FromPDF</code> converters for the Batch 
	framework. 

	<p>The handler is only required to implement the conversion callback. 
	All others are optional. If a handler fails to implement 
	the conversion callback, the handler will not be registered. </p>
	
	@param conversionHandler IN/OUT The handler. 
	@see AVAppRegisterToPDFHandler 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(void, AVAppRegisterFromPDFHandler, (AVConversionFromPDFHandler conversionHandler))

/**
	Enumerates all registered <code>ConvertToPDF</code> conversion handlers. 
	
	@param proc IN/OUT A user-supplied callback. 
	@param data IN/OUT A pointer to user-defined data to pass to <code>proc</code> 
	each time it is called. 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(void, AVConversionEnumToPDFConverters, (AVConversionToPDFEnumProc proc, AVConversionEnumProcData data))

/**
	Enumerates all registered <code>ConvertFromPDF</code> conversion handlers. 
	
	@param proc IN/OUT A user-supplied callback. 
	@param data IN/OUT A pointer to user-defined data to pass to <code>proc</code> 
	each time it is called. 
	@see AVConversionEnumToPDFConverters 
  	@ingroup Enumerators
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(void, AVConversionEnumFromPDFConverters, (AVConversionFromPDFEnumProc proc, AVConversionEnumProcData data))

/**
	Converts a file to a PDF document using the handler specified. 
	
	@param inHandler IN Specifies which <code>ConvertToPDF</code> handler to 
	use. 
	@param inSettings IN An ASCab containing the settings to be used 
	in the conversion operation. Pass <code>NULL</code> to use the default 
	settings. 
	@param flags IN Conversion flags. 
	@param inPath IN The location of the input file. 
	@param inFileSys IN The file system from which the path was obtained. 
	
	@param outPDDoc OUT (Filled by the method) It is the caller's responsibility 
	to close the document. 
	@param statusMonitor IN Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>. 
	@return One of the AVConversionStatus codes. 
	@see AVConversionEnumToPDFConverters 
	@see AVConversionConvertToPDF 
	@see AVConversionEnumFromPDFConverters 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(AVConversionStatus, AVConversionConvertToPDFWithHandler,(
	AVConversionToPDFHandler	inHandler,
	ASCab						inSettings,
	AVConversionFlags			flags,		
	ASPathName					inPath,
	ASFileSys					inFileSys,
	PDDoc						*outPDDoc,
	AVStatusMonitorProcs		statusMonitor))

/**
	Converts a PDF document to another file format using the 
	handler specified. 
	@param inHandler Specifies which conversion handler to use. 
	@param inSettings An ASCab containing the settings to be used 
	in the conversion operation. There are no specific predefined
	settings that need to be passed. Pass <code>NULL</code> to use the default 
	settings. 
	@param flags Conversion flags. See AVConversionFlags in AVExpT.h.  The default
	is kAVConversionNoFlags.
	@param inPDDoc The PDF document to be converted. 
	@param outPath The desired location for the output file. 
	@param outFileSys The file system from which the path was obtained. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	Can be <code>NULL</code>, or any of its members can be <code>NULL</code>.
	@return One of the AVConversionStatus codes. 
	@see AVConversionEnumFromPDFConverters 
	@see AVConversionConvertToPDFWithHandler 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(AVConversionStatus, AVConversionConvertFromPDFWithHandler,(
	AVConversionFromPDFHandler	inHandler,
	ASCab						inSettings,
	AVConversionFlags			flags,
	PDDoc						inPDDoc,
	ASPathName					outPath,
	ASFileSys					outFileSys,
	AVStatusMonitorProcs		statusMonitor))

/**
	Converts the specified file to a PDF document using whatever 
	converter is found. Use this function if you do not know 
	which handler to use. 

	<p>Multiple conversion handlers can register their services 
	for the same file description, so the first one that matches 
	the file type passed in and has the correct <code>canDoSync</code> settings 
	is used. </p>

	<p>The converters are enumerated in priority order, starting 
	with the highest priority. </p>
	@param flags IN/OUT Conversion flags. 
	@param inPath IN The location of the input file. 
	@param inFileSys IN The file system from which path was obtained. 
	
	@param outPDDoc OUT (Filled by the method) It is the caller's responsibility 
	to close the document. 
	@param statusMonitor IN Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>. 
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertToPDF 
	@see AVConversionConvertToPDFWithHandler 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(AVConversionStatus, AVConversionConvertToPDF, (
	AVConversionFlags		flags,		
	ASPathName				inPath,
	ASFileSys				inFileSys,
	PDDoc					*outPDDoc,
	AVStatusMonitorProcs	statusMonitor))


/**
	Creates a new command of the specified type. An AVCommandHandler 
	for that command type must have already been registered. 
	See AVCommand Descriptions (Built-in Commands) for the names 
	and parameters of built-in commands, as defined in AVCmdDefs.h. 
	
	@param name The new command's type name. 
	@return The new command, or <code>NULL</code> if the specified type has not been 
	registered. 
	@see AVCommandDestroy 
	@see AVAppFindGlobalCommandByName 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommand, AVCommandNew, (ASAtom name))

/**
	Destroys the specified command and its associated resources. 
	
	@param cmd The command to destroy. See AVCommand Descriptions 
	(Built-in Commands).
	@see AVCommandNew 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVCommandDestroy, (AVCommand cmd))

/**
	Returns the name of the command. 
	@param cmd The command whose name is returned. See AVCommand 
	Descriptions (Built-in Commands). 
	@return The command name. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASAtom, AVCommandGetName, (AVCommand cmd))

/**
	Returns the current status of the specified command. 
	@param cmd The command whose status is returned. See AVCommand 
	Descriptions (Built-in Commands). 
	@return The current status of cmd. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandGetStatus, (AVCommand cmd))

/**
	Returns the ASCab stored in the specified command under the
	key. If the cabinet is not available, this method will create 
	it if <code>create</code> is set to <code>true</code>. The command retains ownership 
	of the returned cabinet. 

	<p>This method can only be exercised by an AVCommandHandler. 
	Command handlers can use this call to attach arbitrary information 
	to a command. Only the command handler should access these 
	cabinets. See AVCommandSetInputs() and AVCommandSetParams(). </p>
	
	@param cmd The command to be queried. See AVCommand Descriptions 
	(Built-in Commands). 
	@param cabName The key under which the cabinet is stored. 
	@param create Pass <code>true</code> to have this method create the 
	cabinet if it does not exist.
	@return The cabinet if it was found or created, <code>NULL</code> otherwise. 
	@see AVCommandPutCab 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASCab, AVCommandGetCab, (AVCommand cmd, const char *cabName, ASBool create))

/**
	Stores a cabinet in the specified command. If a cabinet 
	is currently stored under the key, it is overwritten. The command 
	assumes ownership of <code>cabVal</code>. 

	<p>This method can only be exercised by an AVCommandHandler. 
	Command handlers can use this call to store state information 
	(such as parameters) in a command. Only the command handler 
	associated with the command should access these cabinets. 
	See AVCommandSetInputs() and AVCommandSetParams(). </p>
	
	@param cmd The command. See AVCommand Descriptions (Built-in 
	Commands). 
	@param cabName (May be <code>NULL</code>) The key name under which the cabinet 
	will be stored. If <code>NULL</code>, a numerical name is generated 
	and used. 
	@param cabVal (May be <code>NULL</code>) The cabinet to store. If <code>NULL</code>, 
	the method destroys the cabinet currently stored under the key (if any).
	@exception genErrBadParm 
	@see AVCommandGetCab 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVCommandPutCab, (AVCommand cmd, const char *cabName, ASCab cabVal))

/**
	Sets the parameters for the specified command. The parameters 
	are those pieces of information that can be controlled by 
	the user, such as the pages to act on. Use this method and 
	AVCommandSetInputs() to set up a command before calling AVCommandExecute() 
	to execute it. 

	<p>Setting any parameters for a command sets all parameters. 
	The command supplies appropriate default parameters for 
	any that are missing from <code>params</code>. Passing an empty cabinet 
	causes all parameters to be set to their default values. </p>

	<p>If the command is not in a ready state, the parameters are 
	not updated. </p>

	<p>The caller retains ownership of <code>params</code>. </p>
	@param cmd The command whose parameters are being set. 
	See AVCommand Descriptions (Built-in Commands). 
	@param params The parameters to be set.
	@return The status of <code>cmd</code> after the parameters are set. 
	@see AVCommandGetParams 
	@see AVCommandSetInputs 
	@see AVCommandExecute 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandSetParams, (AVCommand cmd, ASCab params))

/**
	Retrieves the parameter set for the specified command. It 
	is possible that some commands have no parameters that can 
	be configured, in which case no data will be written to 
	<code>params</code>. The <code>params</code> cabinet should be empty when passed in. 
	Upon return, it will be filled with copies of all of the 
	command's parameter settings. 

	<p>The caller retains ownership of <code>params</code>. </p>
	@param cmd The command whose parameters are being retrieved. 
	See AVCommand Descriptions (Built-in Commands). 
	@param params (Filled by the method) An ASCab into which 
	the parameter set is written. 
	@see AVCommandSetParams 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVCommandGetParams, (AVCommand cmd, ASCab params))

/**
	Sets the configuration for the specified command. See AVCommandGetConfig() 
	for more information. 

	<p><code>config</code> will be merged with the current configuration cabinet 
	to generate the new configuraton. To erase configuration 
	settings, set their values to <code>NULL</code> in your cabinet. </p>

	<p>Currently the only configuration parameters defined are: </p>
	
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Parameter</TH><TH>Description</TH></TR>
	<TR><TD><code>UIPolicy</code> (kASValueInteger)</TD><TD>The local user interface policy for this command.</TD></TR>
	<TR><TD><code>ParamsDescOpen</code> (kASValueBool)</TD><TD>Indicates whether the description of this command's parameters is visible in the sequence view.</TD></TR>
	</TABLE>
	
	<p>The caller retains ownership of <code>config</code>. </p>

	@param cmd The command whose configuration parameters 
	are being set. See AVCommand Descriptions (Built-in Commands). 
	@param config The configuration settings.
	@return The current status of <code>cmd</code>. The configuration settings will 
	not be updated if the command is not in a ready state. 
	@see AVCommandGetCancelProc 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandSetConfig, (AVCommand cmd, ASCab config))

/**
	Retrieves the configuration parameters for the specified 
	command. 

	<p>Configuration values are controlled by the mechanism that 
	is driving the command, such as a client or the batch 
	framework. For example, one configuration value determines whether 
	to display a dialog box while executing; it can be a setting that the 
	user can toggle through the user interface, or a client can set it 
	through AVCommandSetConfig(). </p>

	<p>To retrieve all the configuration parameters, pass in an 
	empty cabinet for <code>config</code> and the method will fill in the 
	cabinet with the current configuration keys and values. To retrieve 
	specific configuration parameter values, fill the initial 
	dictionary with the keys in which you are interested, each with 
	a <code>NULL</code> value, and the method will attempt to fill in the 
	appropriate value for each key.</p> 

	<p>Currently the only configuration parameters defined are: </p>
	
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Parameter</TH><TH>Description</TH></TR>
	<TR><TD><code>UIPolicy</code> (kASValueInteger)</TD><TD>The local user interface policy for this command.</TD></TR>
	<TR><TD><code>ParamsDescOpen</code> (kASValueBool)</TD><TD>Indicates whether the description of this command's parameters is visible in the sequence view.</TD></TR>
	</TABLE>
	@param cmd The command whose configuration parameters 
	are being retrieved. See AVCommand Descriptions (Built-in 
	Commands). 
	@param config (Filled by the method) An ASCab into which 
	the parameters are written.
	@see AVCommandSetConfig 
	@see AVCommandGetUIPolicy 
		
	@note The caller retains ownership of <code>config</code>. 
	@note Normally the batch sequence framework controls the 
	configuration of commands in batch sequences. 
	@since PI_ASEXTRA_VERSION >= 0x00050000
*/
NPROC(void, AVCommandGetConfig, (AVCommand cmd, ASCab config))

/**
	Retrieves the properties of the specified command. Properties 
	are values intrinsic to the command or to the command's 
	current state. 

	<p>To retrieve properties, create a cabinet containing the 
	keys for the properties in which you are interested (the values 
	should be invalid, such as <code>NULL</code>), and pass it into this 
	method. The command will copy the requested properties into 
	your cabinet. If the cabinet is empty, the command will 
	fill in all properties.</p>

	<p>The following properties are pre-defined:</p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Property</TH><TH>Description</TH></TR>
	<TR><TD><code>CanShowDialog</code> (kASValueBool)</TD><TD>Indicates that the command 
	can show a configuration dialog box. Support of this property 
	is optional; it defaults to <code>false</code>.</TD></TR>
	<TR><TD><code>CanDescribeParams</code> (kASValueBool)</TD><TD>Indicates that the command 
	can provide a description of its parameters. Support of 
	this property is optional; it defaults to <code>false</code>. If the command 
	sets this property to <code>true</code>, it should support the <code>ParamDesc</code> 
	property also.</TD></TR>
	<TR><TD><code>ParamsDesc</code> (kASValueCabinet)</TD><TD>A cabinet containing numeric 
	keys (for example, '1', '2', ..., 'n' with kASValueText values 
	describing the command's parameters). The text items will 
	be displayed in the sequence dialog box in the numerical order 
	of the keys.</TD></TR>
	<TR><TD><code>CanBatch</code> (kASValueBool)</TD><TD>Indicates that the command should 
	appear in the list of commands that can be batched. Support 
	of this property is optional; it defaults to <code>false</code>. If the 
	command set returns this property value as <code>true</code>, it <i>must</i> also
	support the <code>GenericTitle</code> and <code>GroupTitle</code> properties.</TD></TR>
	<TR><TD><code>GroupTitle</code> (kASValueText)</TD><TD>The name of the group to which 
	this command belongs. Currently the <code>GroupTitles</code> are localized 
	strings, so they vary from one language to another. The English 
	<code>GroupTitles</code> are those listed in the edit sequence dialog box: 
	<code>'Comments'</code>, <code>'Document'</code>, <code>'JavaScript'</code>, <code>'Page'</code>, and <code>'PDF Consultant'</code>.</TD></TR>
	<TR><TD><code>GenericTitle</code> (kASValueText)</TD><TD>The generic name for this command 
	(for example, <code>'Show/ Hide Bookmarks'</code>, <code>'Rotate Pages'</code>, and 
	so forth). This is used when displaying the command in the 
	list of global commands.</TD></TR>
	<TR><TD><code>Title</code> (kASValueText)</TD><TD>The specific title for this command 
	(for example, <code>'Hide Bookmarks'</code> taking the command's parameters 
	into account). This is used for displaying a specific command 
	within a sequence.</TD></TR>
	</TABLE>
	@param cmd The command whose properties are being retrieved. 
	See AVCommand Descriptions (Built-in Commands). 
	@param props (Filled by the method) The command properties. 
	The caller retains ownership of the ASCab. 
	
	@note The caller retains ownership of <code>props</code>. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVCommandGetProps, (AVCommand cmd, ASCab props))

/**
	Sets the input parameters of the specified command. The 
	inputs of a command consist of an ASCab detailing properties 
	of the object on which the command will operate. Use this method 
	and AVCommandSetParams() to set up a command before calling 
	AVCommandExecute() to execute it. 
	
	<p>A command handler should provide at least the following 
	information:</p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Key (see Command Keys)</TH><TH>Stored As</TH><TH>Description</TH></TR>
	<TR><TD>kAVCommandKeyPDDoc</TD><TD>kASValuePointer</TD><TD>The document being processed.</TD></TR>
	<TR><TD>kAVCommandKeyBaseFileName</TD><TD>kASValueString</TD><TD>The name of the input file, without extension.</TD></TR>
	<TR><TD>kAVCommandKeyOrigExtension</TD><TD>kASValueString</TD><TD>The extension of the input file.</TD></TR>
	</TABLE>

	<p>The command handler can specify additional inputs as necessary. 
	The caller retains ownership of <code>inputs</code>. </p>

	@param cmd The command whose inputs are being set. See 
	AVCommand Descriptions (Built-in Commands). 
	@param inputs The input parameters.
	@return The current status of <code>cmd</code>. The input settings will not be 
	updated if the command is not in a ready state. 
	@see AVCommandGetInputs 
	@see AVCommandSetParams 
	@see AVCommandExecute 
	@note AVCommandExecute() will also attempt to provide kAVCommandKeyAVDoc, 
	a pointer to the AVDoc being operated on. 
	@note You can use AVCommandGetPDDoc() and AVCommandGetAVDoc() 
	to quickly retrieve the PDDoc or AVDoc in a command's inputs. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandSetInputs, (AVCommand cmd, ASCab inputs))

/**
	Retrieves the input parameters of the specified command. 
	The inputs of a command consist of an ASCab detailing properties 
	of the object on which the command will operate. The contents 
	of the cabinet are dependent on the mechanism through which 
	the command is initialized. 
	
	<p>The batch framework attempts to provide the following:</p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Key (see Command Keys)</TH><TH>Stored As</TH><TH>Description</TH></TR>
	<TR><TD>kAVCommandKeyPDDoc</TD><TD>kASValuePointer</TD><TD>The document being processed.</TD></TR>
	<TR><TD>kAVCommandKeyBaseFileName</TD><TD>kASValueString</TD><TD>The name of the input file, without extension.</TD></TR>
	<TR><TD>kAVCommandKeyOrigExtension</TD><TD>kASValueString</TD><TD>The extension of the input file.</TD></TR>
	</TABLE>

	<p>Clients should also attempt to provide this information. The 
	content of the <code>inputs</code> cabinet is not limited to the keys 
	listed above. Clients (or the command handler itself ) can 
	specify additional inputs as necessary. The caller retains 
	ownership of <code>inputs</code>. </p>
	@param cmd The command whose input parameters are being 
	retrieved. See AVCommand Descriptions (Built-in Commands). 
	@param inputs (Filled by the method) The input parameters.
	@see AVCommandSetInputs 

	@note AVCommandExecute() will also attempt to provide kAVCommandKeyAVDoc, 
	a pointer to the AVDoc being operated on. 
	@note You can use AVCommandGetPDDoc() and AVCommandGetAVDoc() 
	to quickly retrieve the PDDoc or AVDoc in a command's inputs. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVCommandGetInputs, (AVCommand cmd, ASCab inputs))

/**
	Instructs the command to bring up its configuration dialog box 
	and gather parameter information from the user. The dialog box 
	is shown regardless of the <code>UIPolicy</code> of the command. 

	<p>If the user confirms the configuration dialog box, the <code>cmd</code> object's parameter 
	set is updated; otherwise <code>cmd</code> will enter a cancelled state. </p>
	
	<p>Query <code>cmd</code> for its kAVCommandKeyCanShowDialog property using 
	AVCommandGetProps() to determine whether it has a configuration dialog box. </p>
	
	@param cmd The command for which the dialog box is thrown. 
	See AVCommand Descriptions (Built-in Commands). 
	@return The current status of <code>cmd</code>. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandShowDialog, (AVCommand cmd))

/**
	Instructs the command do some work based on its current 
	parameters. 

	<p>A command will either divide its processing across multiple 
	AVCommandWork() calls, or perform all the processing within 
	a single call. </p>

	<p>If <code>cmd</code> is in a working state upon return, it is the client's 
	responsibility to poll the command's cancel proc, before 
	calling AVCommandWork() again, to continue processing. </p>
	@param cmd The command that is instructed to do some work. 
	See AVCommand Descriptions (Built-in Commands). 
	@return The current status of <code>cmd</code>. No processing is performed if 
	the command cannot be put in a ready or working state. 
	@see AVCommandCancel 
	@see AVCommandExecute 
	@see AVCommandReset 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandWork, (AVCommand cmd))

/**
	Cancels the specified command. If the command is currently 
	processing a file, the command might not attempt to roll 
	back any modifications it has made to the document. This 
	may leave the PDF in an invalid state. 
	@param cmd The command to cancel. See AVCommand Descriptions 
	(Built-in Commands).
	@return The current status of <code>cmd</code>. It should be kAVCommandCanceled. 
	
	@see AVCommandReset 
	@see AVCommandWork 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandCancel, (AVCommand cmd))

/**
	Resets the specified command. The command is expected to 
	clean up its current state and assume a ready state. 

	<p>If the command is currently processing a file, the command 
	might not attempt to roll back any modifications it has 
	made to the PDF. This may leave the PDF in an invalid state. </p>
	
	@param cmd The command to reset. See AVCommand Descriptions 
	(Built-in Commands). 
	@return The current status of <code>cmd</code>. 
	@see AVCommandCancel 
	@see AVCommandWork 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandReset, (AVCommand cmd))

/**
	Retrieves the user interface policy that the command will 
	respect while it is executed. The user interface policy is determined 
	by a combination of the command's configuration and the 
	context in which the command is executing (for example, 
	a batch sequence). 
	@param cmd The command whose user interface policy is returned. See 
	AVCommand Descriptions (Built-in Commands). 
	@return The user interface policy. 
	@see AVCommandGetCancelProc 
	@see AVCommandSetConfig 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandUIPolicy, AVCommandGetUIPolicy, (AVCommand cmd))

/**
	Retrieves the AVDoc from a command's inputs ASCab. 
	@param cmd The command to be queried. See AVCommand Descriptions 
	(Built-in Commands). 
	@return The AVDoc if it was found, <code>NULL</code> otherwise. 
	@see AVCommandSetInputs 

	@note In some cases, this call returns a <code>NULL</code> AVDoc even 
	when AVCommandGetPDDoc() returns a non-<code>NULL</code> PDDoc and an AVDoc 
	is open on that PDDoc. In these cases, you should probably 
	ignore the AVDoc or use AVDocFromPDDoc() to find the associated 
	AVDoc. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVDoc, AVCommandGetAVDoc, (AVCommand cmd))

/**
	Retrieves the PDDoc from a command's inputs ASCab. 
	@param cmd The command to be queried. See AVCommand Descriptions 
	(Built-in Commands). 
	@return A PDDoc if it was found, <code>NULL</code> otherwise. 
	@since PI_ASEXTRA_VERSION >= 0x00050000
*/
NPROC(PDDoc, AVCommandGetPDDoc, (AVCommand cmd))

/**
	Returns the ASReportProc associated with the specified command. 
	AVCommandHandlers should report all error and status messages 
	through this procedure. 

	<p>Pass the AVCommand itself as the <code>clientData</code> parameter when 
	calling the procedure. </p>
	@param cmd The command whose ASReportProc is returned. 
	See AVCommand Descriptions (Built-in Commands). 
	@return The ASReportProc. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASReportProc, AVCommandGetReportProc, (AVCommand cmd))

/**
	Returns a progress monitor the command can use to report 
	progress. The command itself should be passed in as the 
	<code>clientData</code> associated with the monitor's callbacks. 

	<p>Command handlers should use this progress monitor rather 
	than a custom implementation.</p> 

	<p>If the command is driven by the batch framework, the progress 
	monitor updates the batch progress dialog box. If the command 
	is driven by a client and the AVDoc input key has been set, 
	the progress monitor updates the progress pane at the bottom 
	of the document's window; otherwise, the progress monitor's 
	callbacks are no-ops. </p>
	@param cmd The command to be queried. See AVCommand Descriptions 
	(Built-in Commands). 
	@return The command progress monitor. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASProgressMonitor, AVCommandGetProgressMonitor, (AVCommand cmd))

/**
	Returns a cancellation procedure for the command. If the 
	user interface policy is anything other than kAVCommandUIInteractive, 
	this cancellation procedure must be used. If the user interface policy 
	is kAVCommandUIInteractive, an appropriate default cancel 
	proc will be provided, but the command may use a more appropriate 
	one it if preferred. Pass in the command itself as the client 
	data. 
	@param cmd The command whose cancellation procedure is 
	returned. See AVCommand Descriptions (Built-in Commands). 
	
	@return The cancellation procedure. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASCancelProc, AVCommandGetCancelProc, (AVCommand cmd))

/**
	Registers an AVCommandHandler as the implementor of an AVCommand 
	with the specified name. If there are any existing commands 
	registered under <code>name</code>, the new command replaces them. 

	<p>A single handler can implement and register multiple commands. </p>
	
	@param name IN/OUT The command name. 
	@param handler IN The handler to register. 
	@see AVAppFindCommandHandlerByName 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAppRegisterCommandHandler, (ASAtom name, AVCommandHandler handler))

/**
	Gets the AVCommandHandler that was registered under the 
	given name. 
	@param name IN/OUT The name of the handler to obtain. 
	@return The AVCommandHandler if it was found, <code>NULL</code> otherwise. 
	@see AVAppRegisterCommandHandler 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandHandler, AVAppFindCommandHandlerByName, (ASAtom name))

/**
	Registers an AVCommand in the global command list. The application 
	assumes ownership of the resources associated with <code>cmd</code>. 
	As such, the client must not call AVCommandDestroy(). 
	@param cmd IN/OUT The AVCommand to register. 
	@see AVAppFindGlobalCommandByName 
	@see AVAppUnregisterGlobalCommand 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAppRegisterGlobalCommand, (AVCommand cmd))

/**
	Returns the AVCommand that was registered under the given 
	name. 
	@param name The name of the AVCommand to obtain.
	@return The AVCommand if one was found, <code>NULL</code> otherwise. 
	@see AVAppRegisterGlobalCommand 
	@see AVAppUnregisterGlobalCommand 
	@see AVCommandNew 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommand, AVAppFindGlobalCommandByName, (ASAtom name))

/**
	Removes an AVCommand from the global command list. 
	@param cmd IN/OUT The command. 
	@see AVAppFindGlobalCommandByName 
	@see AVAppRegisterGlobalCommand 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAppUnregisterGlobalCommand, (AVCommand cmd))

/**
	Runs the specified AVCommand, after it has been 
	set up using AVCommandSetInputs() and AVCommandSetParams(). 
	
	<p>The method runs the command using the following process: </p>
	<ul>
	<li> Reset the command if its status is not AVCommandReady. </li>
	<li> If only a PDDoc input has been configured, AVCommandExecute() 
	does nothing to the inputs. If no AVDoc or PDDoc inputs 
	have been configured, AVCommandExecute() configures the command 
	to use the active AVDoc. In all cases, if an AVDoc has been 
	configured (either by AVCommandExecute() or its caller) the 
	implementation ensures that the PDDoc input matches the 
	AVDoc input. </li>
	<li> If the command can display a dialog box (that is, if the command 
	handler has a <code>ShowDialog</code> callback and the command's kAVCommandKeyCanShowDialog 
	property is <code>true</code>), present the dialog box to allow the user 
	to alter the command's parameters. </li>
	<li> Repeatedly call AVCommandWork() on <code>cmd</code> until that method 
	returns a status other than kAVCommandWorking. </li>
	</ul>
		
	<p>This method should be used when the client does not need 
	the level of control provided when calling AVCommandWork() 
	directly. Specifically, this method is useful for using 
	a global command from within a menu or a toolbar button's 
	execution procedure. </p>
	@param cmd The command to execute. See AVCommand Descriptions 
	(Built-in Commands). 
	@return The current status of cmd. 
	@see AVCommandSetInputs 
	@see AVCommandSetParams 
	@see AVCommandWork 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVCommandStatus, AVCommandExecute, (AVCommand cmd))
NPROC(ASBool, oldAVAppOpenDialog, (oldAVOpenSaveDialogParams dialogParams,		/* Standard dialog params for Open/Save/ChooseFolder dialogs */
										ASFileSys	*outFileSys,				/* May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams */
										ASPathName	**outASPathNames,			/* Caller must ASfree this array and release its ASPathName elements */
										AVArraySize		*outNumASPathNames,			/* Number of ASPathNames in outASPathNames array. It may be <code>NULL</code> if kAVOpenSaveAllowMultiple is not set */
										AVFilterIndex		*ioChosenFilterIndex))		/* May be <code>NULL</code> if caller doesn't care which filter was chosen, -1 if 'All Files'.
																				** Specify the initially selected filter with the value passed in.  If <code>NULL</code>, 1st entry is selected. */
																				/* Returns <code>true</code> if user clicked 'action' button, <code>false</code> if user clicked 'cancel' */

NPROC(ASBool, oldAVAppSaveDialog, (oldAVOpenSaveDialogParams dialogParams,		/* Standard dialog params for Open/Save/ChooseFolder dialogs */
										ASFileSys	*outFileSys,				/* May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams */
										ASPathName	*outASPathName,				/* Caller must release this ASPathName */
										AVFilterIndex		*ioChosenFilterIndex))		/* May be <code>NULL</code> if caller doesn't care which filter was chosen, -1 if 'All Files'.
																				** Specify the initially selected filter with the value passed in.  If <code>NULL</code>, 1st entry is selected. */
																				/* Returns <code>true</code> if user clicked 'action' button, <code>false</code> if user clicked 'cancel' */

NPROC(ASBool, oldAVAppChooseFolderDialog, (oldAVOpenSaveDialogParams dialogParams,/* Standard dialog params for Open/Save/ChooseFolder dialogs. It may be <code>NULL</code> */
										ASFileSys	*outFileSys,				/* May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams */
										ASPathName	*outASPathName))			/* Caller must release this ASPathName */
																				/* Returns <code>true</code> if user clicked 'action' button, <code>false</code> if user clicked 'cancel' */
/* Note on the Special Folder/File procedures: if any portion of the special path does
** not exist and bCreate is not <code>true</code> then kAVSEDoesntExist will be returned. */

/**
	Obtains the path name of a special folder. This method cannot 
	be used to obtain the ASPathName of a folder that does not 
	exist. It is the caller's responsibility to release the 
	ASPathName. 
	@param cat The folder category. See AVSpecialCategory. 
	Only certain combinations of category/folder are allowed. See 
	AVSpecialError. 
	@param fld The folder. See AVSpecialFolder. Only certain 
	combinations of category/folder are allowed. See AVSpecialError. 
	@param bCreate Create the folder if it does not exist. 
	@param asfs (Filled by the method) The file system 
	through which the path name was obtained. 
	@param asp (Filled by the method) An ASPathName associated 
	with the folder.
	@return One of the AVSpecialError status codes. It returns kAVSEOkay 
	if the method executed without error. The <code>asfs</code> and <code>asp</code> 
	variables will only be valid if the method returns kAVSEOkay. 
	If <code>bCreate</code> is <code>false</code> and the folder does not exist, kAVSEError 
	is returned on Windows, while kAVSEDoesntExist is returned 
	on Mac OS. 
	@see AVAcquireSpecialFilePathName
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASErrorCode, AVAcquireSpecialFolderPathName, (AVSpecialCategory cat, AVSpecialFolder fld, ASBool bCreate, ASFileSys *asfs, ASPathName *asp))

/**
  	In Acrobat 6.0, this method is superseded by AVAcquireSpecialFilePathNameWithASText().
  
  	<p>Obtains the path name for a file in a special folder. It 
	is the caller's responsibility to release the ASPathName. 
	This method may be used even if the associated file does 
	not exist.</p> 
	
	@param cat The folder category. See AVSpecialCategory. 
	Only certain combinations of category/folder are allowed - see 
	AVSpecialError. 
	@param fld The folder in which the file is located. 
	See AVSpecialFolder. Only certain combinations of category/folder 
	are allowed. See AVSpecialError. 
	@param cFile The name of the file (including extension) that 
	you want to access. 
	@param asfs OUT The file system through which the path name was obtained. 
	@param asp OUT An ASPathName associated with the file. The caller must release it.
	@return One of the AVSpecialError status codes. The <code>asfs</code> and <code>asp</code> 
	variables will only be valid if the method returns 
	kAVSEOkay or kAVSEDoesntExist. kAVSEDoesntExist is returned 
	if the ASPathName was created but the associated file does not 
	exist. 
	@see AVAcquireSpecialFilePathNameWithASText 
	@see AVAcquireSpecialFolderPathName 

	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASInt32, AVAcquireSpecialFilePathName, (AVSpecialCategory cat,			/* Category (see AVExpT.h) */
										AVSpecialFolder fld,					/* Folder (see AVExpT.h) */
										const char *cFile,						/* File you want to access (e.g. AcroHelp.pdf). */
										ASFileSys *asfs,						/* Filled by this routine. */
										ASPathName *asp))						/* Filled by this routine. Caller must release this ASPathName */

/**
	Gets the currently focused annotation from the page view. 
	
	@param pageView IN/OUT The page view. 
	@param annot IN/OUT (Filled by the method) The currently focused 
	annotation. It is <code>NULL</code> if the method returns <code>false</code>. 
	@return <code>true</code> if the annotation was obtained, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewGetFocusAnnot, (AVPageView pageView, PDAnnot *annot))

/**
	Attempts to set an annotation as the active annotation. 
	
	@param pageView IN/OUT The page view in which the annotation resides. 
	
	@param focusAnnot IN/OUT The annotation in question. 
	@param opData IN/OUT Can be <code>NULL</code> and probably should be in most 
	cases. If specified, it will be used for the kAVAnnotAcceptFocus 
	operation. 
	@return <code>true</code> if annot was given the focus, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewSetFocusAnnot, (AVPageView pageView, PDAnnot focusAnnot,AVAnnotOpData opData))

/**
	Removes the focus from the currently selected annotation. 
	
	@param pageView IN/OUT The page view holding the focus. 
	@return <code>false</code> if there was no focus annotation in effect when the 
	method was called, <code>true</code> if there was. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewClearFocusAnnot, (AVPageView pageView))

/**
	Used to determine if <code>annot</code> currently has focus. 
	@param pageView IN/OUT The page view in which the annotation resides. 
	
	@param annot IN/OUT The annotation in question. 
	@return <code>true</code> if <code>annot</code> has the focus, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewIsFocusAnnot, (AVPageView pageView, PDAnnot annot))

/**
	Parses a path name to obtain the base file name and extension 
	for a particular file. The function enumerates all registered 
	<code>convertToPDF</code> and <code>convertFromPDF</code> handlers to find a matching 
	extension for the file passed in. This function allocates 
	memory for the file name and extension. It is the caller's 
	responsibility to free the memory allocated by the method. 
	
	@param fileSys The file system from which the path was obtained. 
	Pass <code>NULL</code> to use the default file system. 
	@param pathName The path containing the file name. 
	@param numAddExt The number of additional extensions to 
	search through. 
	@param addExt An array of <code>NULL</code>-terminated strings with 
	extensions to search through. 
	@param baseName (Allocated and filled by the method) A 
	buffer containing the file name. It can be <code>NULL</code> if you do not 
	want the base file name. 
	@param baseExt (Allocated and filled by the method) A 
	buffer containing the file extension. It can be <code>NULL</code> if you 
	do not want the base file extension.
	@return <code>true</code> if the file info was successfully extracted from the path, 
	<code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVUtilGetBaseNameAndExtensionByPathName, (
	ASFileSys fileSys,
	ASPathName pathName,
	AVTArraySize numAddExt,
	const char * const *addExt,
	char **baseName,
	char **baseExt))

/**
	Parses a file name string to obtain the base file name path 
	and extension for a particular file. The function enumerates 
	all registered <code>convertToPDF</code> and <code>convertFromPDF</code> handlers 
	to find a matching extension for the file passed in. This 
	function allocates memory for the file name and extension. 
	It is the caller's responsibility to free the memory allocated 
	by the method. 
	@param fileName The file name string to parse. 
	@param numAddExt The number of additional extensions to 
	search through. 
	@param addExt An array of <code>NULL</code>-terminated strings with 
	extensions to search through. 
	@param baseName (Allocated and filled by the method) A 
	buffer containing the file name path, which is the path without 
	the extension (for example, <code>c:\\folder\\file</code>). It can be <code>NULL</code> if you 
	do not want the base file name path. 
	@param baseExt (Allocated and filled by the method) A 
	buffer containing the file extension. It can be <code>NULL</code> if you 
	do not want the base file extension.
	@return <code>true</code> if the file information was successfully extracted from <code>fileName</code>, 
	<code>false</code> otherwise. 

	@note <code>fileName</code> is modified by the implementation. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVUtilGetBaseNameAndExtensionByString, (
	char *fileName,
	AVTArraySize numAddExt,
	const char * const *addExt,
	char **baseName,
	char **baseExt))


/**
	Gets the value of a particular aspect of the active user's 
	identity. Valid keys are <code>login name</code>, <code>name</code>, <code>corporation</code> and 
	<code>email</code>. 
	@param it IN/OUT The AVIdentity key to retrieve. 
	@param ast IN/OUT (Filled by the method) An ASText object to hold 
	the text associated with the identity key. 
	@return A useful handle to the text parameter. 
	@see AVIdentitySetText 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
/* Gets/Sets the text associated with a particular aspect of user identity.
** Valid keys are defined by AVIdentity. */
NPROC(ASText, AVIdentityGetText, (AVIdentity it, ASText ast))

/**
	Sets the value of a particular aspect of the active user's 
	identity. 

	<p>It is not possible to modify the kAVILoginName 
	value through this method. </p>
	@param it IN/OUT The AVIdentity key to set. 
	@param ast IN/OUT The new value for the key. 
	@see AVIdentityGetText 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVIdentitySetText, (AVIdentity it, ASText ast))


/**
	Attempts to have the currently focused annotation perform 
	the given operation. The method will fail if: 
	
	<ul>
	<li> There is no currently selected annotation. </li>
	<li> <code>annotOp</code> is other than kAVAnnotDefaultAction or kAVAnnotShowMenu. </li>
	<li> The annotation handler is not available or does not support 
	the operation. </li>
	</ul>
	
	@param pageView IN/OUT The page view containing the annotation. 
	@param annotOp IN/OUT The operation to perform. 
	@return <code>true</code> if the operation was performed successfully, <code>false</code> 
	otherwise. 
	@notify AVPageViewAnnotDidPerformOp 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewFocusAnnotPerformOp, (AVPageView pageView, AVAnnotOp annotOp))

/**
	Processes a keystroke through the currently focused annotation. 
	The current behavior is defined below: 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Behavior</TH><TH>Description</TH></TR>
	<TR><TD>ASKEY_ESCAPE</TD><TD>The annotation loses focus.</TD></TR>
	<TR><TD>ASKEY_TAB</TD><TD>Focus switches to next annotation in tab order.</TD></TR>
	<TR><TD>ASKEY_ENTER, ASKEY_CR, and ASKEY_SPACE</TD><TD>It performs the default action associated with the annotation.</TD></TR>
	</TABLE>

	@param pageView IN/OUT The page view in which the annotation resides. 
	
	@param key IN/OUT The key code. See ASKey.h for possible values. 
	
	@param flags IN/OUT A bit-wise OR of the Modifier Flags. See AVSysGetModifiers(). 
	
	@param annotWillLoseFocus IN/OUT (Filled by the method) If <code>true</code> 
	upon return, the keystroke has caused the annotation to 
	lose focus. It may be <code>NULL</code> if the caller is not interested 
	in that information. 
	@return <code>true</code> if the keystroke was processed, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewFilterKeyDownForFocusAnnot, (AVPageView pageView, AVKeyCode key, AVFlagBits16 flags, ASBool *annotWillLoseFocus))
NPROC(void, oldAVPageViewGhostRectOutline, (AVPageView pageView, const oldAVRect* rect))


/**
	Creates a new named toolbar. AVAppRegisterToolBarPosition() 
	must be called after creating the new toolbar to position 
	it relative to other toolbars. 
	@param name IN/OUT The internal, language-independent name of 
	the toolbar. It may not be <code>NULL</code>. 
	@param title IN/OUT The localized, user-friendly name of the toolbar. 
	It may not be <code>NULL</code>. 
	@return The new AVToolBar. 
	@see AVLegacyToolBarGetFrame 
	@see AVLegacyToolBarGetNumbuttons 
	@see AVLegacyToolButtonGetFlyout 
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVToolBar, AVLegacyToolBarNew, (const char *name, const char *title))


NPROC(void, oldAVAppRegisterLegacyToolBarPosition,(const char *toolBarName, ASBool external, oldAVToolBarPosition position))

/* AVPageViewSnapPoint obsolete, use AVPageViewSnapPointEx */

NPROC(void, oldAVPageViewSnapPoint, (AVPageView pageView, ASInt16 *x, ASInt16 *y, AVDragType direction))

NPROC(void, oldAVPageViewGetMousePositionSnapped, (AVPageView pageView, ASInt16 *x, ASInt16 *y, AVDragType direction))

NPROC(AVTFlagBits, oldAVPageViewDragOutNewRectSnapped, (AVPageView pageView, ASInt16 xStart, ASInt16 yStart,
	oldAVRect *resultRect, AVCursor *cursorArray, AVTSmallArraySize nCursors))
/* AVPageViewDragRectSnapped obsolete, use AVPageViewDragRectSnappedEx */

NPROC(AVTFlagBits, oldAVPageViewDragRectSnapped, (AVPageView pageView, ASInt16 xStart, ASInt16 yStart,
	oldAVRect *startRect, oldAVRect *resultRect, AVlDragType dragType, oldAVRect *extrema, AVCursor *cursorArray, AVTSmallArraySize nCursors))


NPROC(AVDragTypeEx, oldAVRectHandleHitTest, (oldAVRect *rect, ASBool bMidpoints, ASInt16 x, ASInt16 y))

NPROC(void, oldAVPageViewDrawRectOutlineWithHandles, (AVPageView pageView,const oldAVRect *rect, ASBool bMidpoints, ASBool bThin, ASFixed *dashArray, AVTArraySize arrayLen))


NPROC(ASBool, oldAVPageViewIsAnnotOfTypeAtPoint,
	  (AVPageView pageView, ASInt16 xHit, ASInt16 yHit, ASAtom annotType, ASBool belowOthers, PDAnnot *annot))


/**
	Centers the window within its parent window or the desktop 
	if it has no parent. 
	@param win IN/OUT The window to center. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVWindowCenter, (AVWindow win))

/**
	Gets the AVDoc associated with a PDDoc. 
	@param pdDoc IN/OUT The PDDoc whose AVDoc is to be returned. 
	@return The AVDoc if an AVDoc is already opened for this PDDoc. Otherwise it returns <code>NULL</code>. 
	@see AVDocGetPDDoc 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVDoc, AVDocFromPDDoc, (PDDoc pdDoc))

SPROC(void, oldAVPageViewSnapRect, (AVPageView pageView, ASInt16 xStart, ASInt16 yStart, ASInt16 xNow, ASInt16 yNow,
	oldAVRect *startRect, oldAVRect *resultRect, ASInt32 handleType, ASUns32 modifiers, oldAVRect *extrema), oldAVPageViewGridSnapRect)

/**
	Retrieves a standard report proc that can be used to report 
	errors and warnings to the user. See ASReportProc for more 
	details. 
	@param asReportProcClientDataP IN/OUT A pointer to client data passed 
	to the report proc. 
	@return The report callback. 
	@see AVCommandGetReportProc 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASReportProc, AVAppGetReportProc, (void **asReportProcClientDataP))

/**
	Determines whether a given document is <i>dead</i>. When the 
	connection to a document is severed (for example, when its 
	HTTP connection is broken) the document becomes <i>dead</i> for 
	an interval before it is closed. During that interval, the 
	document may be visible and open, but no operations should 
	be performed on the document. 
	@param avDoc The document being investigated.
	@return <code>true</code> if the given document is dead, <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVDocIsDead, (AVDoc avDoc))

/* 5.0 Preference API's */

/**
	Retrieves an ASBool stored in the specified <code>prefs</code> section with the
	specified key. The default value of <code>defValue</code> will be used if the
	section or key is not found.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@param defValue The default value if the <code>pref</code> is not found.
	@return The value stored under the name, or <code>defValue</code> if the key was
	not found.
	@see AVAppGetPrefInt
	@see AVAppGetPrefAtom
	@see AVAppGetPrefDouble
	@see AVAppGetPrefString
	@see AVAppGetPrefText
	@see AVAppGetPrefCab
	@see AVAppGetPrefPathName
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVAppGetPrefBool, (const char *section, const char *key, ASBool defValue))


/**
	Retrieves an ASInt32 stored in the specified <code>prefs</code> section with the
	specified key. The default value of <code>defValue</code> will be used if the
	section or key is not found.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@param defVal The default value if the <code>pref</code> is not found.
	@return The value stored under the name, or <code>defValue</code> if the key was
	not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefAtom
	@see AVAppGetPrefDouble
	@see AVAppGetPrefString
	@see AVAppGetPrefText
	@see AVAppGetPrefCab
	@see AVAppGetPrefPathName
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASInt32, AVAppGetPrefInt, (const char *section, const char *key, ASInt32 defVal))


/**
	Retrieves an ASAtom stored in the specified <code>prefs</code> section with the
	specified key. The default value of <code>defValue</code> will be used if the
	section or key is not found.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@param defVal The default value if the <code>pref</code> is not found.
	@return The value stored under the name, or <code>defValue</code> if the key was
	not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefInt
	@see AVAppGetPrefDouble
	@see AVAppGetPrefString
	@see AVAppGetPrefText
	@see AVAppGetPrefCab
	@see AVAppGetPrefPathName
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASAtom, AVAppGetPrefAtom, (const char *section, const char *key, ASAtom defVal))


/**
	Retrieves a <code>double</code> value stored in the specified <code>prefs</code> section with the
	specified key. The default value of <code>defValue</code> will be used if the
	section or key is not found.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@param defVal The default value if the <code>pref</code> is not found.
	@return The value stored under the name, or <code>defValue</code> if the key was
	not found.
	@return The value stored under the name, or defValue if the key was
	not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefInt
	@see AVAppGetPrefAtom
	@see AVAppGetPrefString
	@see AVAppGetPrefText
	@see AVAppGetPrefCab
	@see AVAppGetPrefPathName
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(double, AVAppGetPrefDouble, (const char *section, const char *key, double defVal))


/**
	Retrieves a <code>char*</code> stored in the specified <code>prefs</code> section with the
	specified key. The <code>char*</code> is a copy and it is up to the caller
	to free the <code>char*</code> that is returned. If the specified key is not found
	within the section, then <code>NULL</code> is returned.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@return The value stored under the name, or <code>NULL</code> if the key is not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefInt
	@see AVAppGetPrefAtom
	@see AVAppGetPrefDouble
	@see AVAppGetPrefText
	@see AVAppGetPrefCab
	@see AVAppGetPrefPathName
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(char *, AVAppGetPrefString, (const char *section, const char *key))


/**
	Allocates and fills in an ASText object based on the specified <code>prefs</code> section
	with the specified key. The ASText object is a copy and it is up to the caller
	to free the ASText with ASTextDestroy(). If the specified key is not found within
	the section, then <code>NULL</code> is returned.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@return The value stored under the name, or <code>NULL</code> if the key is not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefInt
	@see AVAppGetPrefAtom
	@see AVAppGetPrefDouble
	@see AVAppGetPrefString
	@see AVAppGetPrefCab
	@see AVAppGetPrefPathName
	@see ASTextDestroy
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASText, AVAppGetPrefText, (const char *section, const char *key))


/**
	Allocates and fills in an ASCab object based on the specified <code>prefs</code> section
	with the specified key. The ASCab object is a copy and it is up to the caller
	to free the ASCab with ASCabDestroy(). If the specified key is not found within
	the section, then <code>NULL</code> is returned.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@return The value stored under the name, or <code>NULL</code> if the key is not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefInt
	@see AVAppGetPrefAtom
	@see AVAppGetPrefDouble
	@see AVAppGetPrefString
	@see AVAppGetPrefText
	@see AVAppGetPrefPathName
	@see ASCabDestroy
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASCab, AVAppGetPrefCab, (const char *section, const char *key))


/**
	Retrieves an ASBool stored in the specified <code>prefs</code> section with the
	specified key.  The default value of <code>defValue</code> will be used if the
	section or key is not found.
	@param section The name of the section in the <code>prefs</code> to retrieve. It is limited
	to alphanumeric characters only.
	@param key The name of the <code>pref</code> to retrieve within the section. It is limited
	to alphanumeric characters only.
	@param fileSysVal The function fills in the ASFileSys pointer with the pointer
	to the file system for the preference in question.
	@param pathNameVal The function fills in the ASPathName pointer with an allocated
	ASPathName for the preference in question.  It is up to the caller of
	AVAppGetPrefPathName() to release the ASPathName.
	@return The value stored under the name, or defValue if the key was
	not found.
	@see AVAppGetPrefBool
	@see AVAppGetPrefInt
	@see AVAppGetPrefAtom
	@see AVAppGetPrefDouble
	@see AVAppGetPrefString
	@see AVAppGetPrefText
	@see AVAppGetPrefCab
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAppGetPrefPathName, (const char *section, const char *key, ASFileSys *fileSysVal, ASPathName *pathNameVal))


/**
	Displays an alert dialog box with a feature set as described 
	by the supplied AVAlertParams. 
	@param params IN/OUT A description of the alert feature set. 
	@return The button number (<code>1</code>, <code>2</code>, or <code>3</code>) on which the user clicked. 
	
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
PROC(ASInt32, AVAlertWithParams, (AVAlertParams params))


/**
	Stores a value under <code>name</code> in the AVAlert preference store. 
	The AVAlert preference store is intended to be used by clients 
	to store user preferences regarding whether an alert is 
	displayed prior to execution of a particular operation. 
	The store is persistent across Acrobat sessions. This routine 
	would typically be used when implementing a dialog box that 
	contains a check box saying, <code>"Do not show this dialog 
	again."</code> 
	@param name The name of the entry. It is limited to alphanumeric 
	characters only. 
	@param nAnswer The value to store; pass <code>0</code> (zero) to clear 
	this specific entry.
	@see AVAlertGetPref 
	@see AVAlertResetPrefs 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAlertSetPref, (const char *name, ASInt32 nAnswer))


/**
	Retrieves the value stored under <code>name</code> in the AVAlert preference 
	store. The AVAlert preference store is intended to be used 
	by clients to store user preferences regarding whether to 
	display an alert prior to execution of a particular operation. 
	The store is persistent across Acrobat sessions. This routine 
	would typically be used when implementing a dialog box that 
	contains a check box saying, <code>"Do not show this dialog 
	again."</code> 
	@param name The name of the entry to retrieve. It is limited to 
	alphanumeric characters only.
	@return The value stored under the name, or <code>0</code> if the key was not 
	found. 
	@see AVAlertSetPref 
	@see AVAlertResetPrefs 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASInt32, AVAlertGetPref, (const char *name))


/**
	Resets the entire AVAlert preference store. Specific preference 
	entries can be cleared by passing a value of <code>0</code> to AVAlertSetPref(). 
	
	@see AVAlertGetPref 
	@see AVAlertSetPref 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAlertResetPrefs, (void))

/* Same as AVDocPerformAction but provides context for the execution of the action. */

/**
	Same as AVDocPerformAction(), but provides context for the 
	execution of the action. 
	@param doc IN/OUT The document containing the action to perform. 
	
	@param action IN/OUT The action to perform. 
	@param data IN/OUT The context for the execution of the action. 
	@see AVDocGetPDDoc 
	@see AVDocPerformAction 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVDocPerformActionEx, (AVDoc doc, PDAction action, AVActionContext data))


/**
	Returns the number of clients loaded by Acrobat. 
	@return The number of clients. 
	@see AVExtensionAcquireInfo 
	@see AVExtensionReleaseInfo 

	@note This method is not supported on UNIX platforms. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVArraySize, AVExtensionGetNumPlugIns, (void))

/**
	Fills an AVExtensionInfoRec structure with some information 
	about a client. It is the caller's responsibility to release 
	the memory associated with the contents of the returned 
	structure by calling AVExtensionReleaseInfo(). 
	@param nIndex The index of the client for which to retrieve information. 
	The minimum value for <code>index</code> is zero; the maximum is 
	the return value of <code>AVExtensionGetNumPlugIns() - 1</code>.
	@return The structure containing information about the client. 
	@see AVExtensionReleaseInfo 

	@note This API is not supported on UNIX platforms. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVExtensionInfo, AVExtensionAcquireInfo, (AVArraySize nIndex))

/**
	Releases the memory associated with the contents of <code>info</code>. 
	@param info The AVExtensionInfoRec structure 
	to release.
	@see AVExtensionAcquireInfo 
	
	@note This API is not supported on UNIX platforms. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVExtensionReleaseInfo, (AVExtensionInfo info))


/**
	<p>Translates the given point from the device space coordinate 
	system to the <i>info space</i> coordinate system. </p>

	<p><i>Info space</i> is the coordinate system used by the info palette 
	to provide the user with visual feedback during layout operations. 
	The origin of info space for a given page is the upper left 
	corner of the page. The x-axis is horizontal and increases 
	from left to right. The y-axis is vertical and increases 
	from top to bottom. Units are measured in points. Conceptually, 
	info space is the same as user space, with the y-axis flipped 
	and the origin anchored at the upper left of the page.</p> 
	@param pageView The page view holding the focus. 
	@param x The x-coordinate in device space. 
	@param y The y-coordinate in device space. 
	@param info (Filled by the method) The translated point.
	@see AVPageViewInfoToDevice 
	@see AVPageViewInfoToPoint 
	@see AVPageViewPointToInfo 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(void, AVPageViewDeviceToInfo, (AVPageView pageView, AVlCoord x, AVlCoord y, ASFixedPoint* info))

/**
	Translates the given point from <i>info space</i> to device space. 
	See AVPageViewDeviceToInfo() for a definition of <i>info space</i>. 
	@param pageView The page view holding the focus. 
	@param info The point in info space. 
	@param x (Filled by the method) The x-coordinate of <code>info</code> 
	in device space. 
	@param y (Filled by the method) The y-coordinate of <code>info</code> 
	in device space.
	@see AVPageViewDeviceToInfo 
	@see AVPageViewInfoToPoint 
	@see AVPageViewPointToInfo 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
XNPROC(void, AVPageViewInfoToDevice, (AVPageView pageView, const ASFixedPoint* info, AVlCoord* x, AVlCoord* y))

/**
	Translates the given point from user space to <i>info space</i>. 
	See AVPageViewDeviceToInfo() for a definition of <i>info space</i>. 
	
	@param pageView IN/OUT The page view holding the focus. 
	@param pt IN/OUT The point in user space. 
	@param info IN/OUT (Filled by the method) The point in info space. 
	
	@see AVPageViewDeviceToInfo 
	@see AVPageViewInfoToDevice 
	@see AVPageViewInfoToPoint 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
UNPROC(void, AVPageViewPointToInfo, (AVPageView pageView, const ASFixedPoint* pt, ASFixedPoint* info))

/**
	Translates the given point from <i>info space</i> to user space. 
	See AVPageViewDeviceToInfo() for a definition of <i>info space</i>. 
	
	@param pageView IN/OUT The page view holding the focus. 
	@param info IN/OUT The point in info space. 
	@param pt IN/OUT (Filled by the method) The point in user space. 
	
	@see AVPageViewDeviceToInfo 
	@see AVPageViewInfoToDevice 
	@see AVPageViewPointToInfo 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
UNPROC(void, AVPageViewInfoToPoint, (AVPageView pageView, const ASFixedPoint* info, ASFixedPoint* pt))


/**
	Allow clients to control the Info panel output. 
	@param pageView The page view. 
	@param updateType An AVInfoPanelUpdateType constant. If it is kAVInfoPanelLock 
	or kAVInfoPanelUnlock, <code>data</code> should be <code>NULL</code> and is ignored. 
	If <code>updateType</code> is kAVInfoPanelRect, clients should pass an 
	AVRect32P through <code>data</code>. It is also useful to note how the 
	rectangle will be interpreted by the info panel. 
	
	<p>The info panel will display the following data:</p> 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Data</TH><TH>Description</TH></TR>
	<TR><TD><code>X</code></TD><TD>The left of the rectangle.</TD></TR>
	<TR><TD><code>Y</code></TD><TD>The top of the rectangle.</TD></TR>
	<TR><TD><code>W</code></TD><TD>The width of the rectangle.</TD></TR>
	<TR><TD><code>H</code></TD><TD>The height of the rectangle.</TD></TR>
	</TABLE>
	
	@param data User-supplied data.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
UNPROC(void, AVPageViewUpdateInfoPanel, (AVPageView pageView, AVInfoPanelUpdateType updateType, void *data))

/**
	Returns the toolbar created with the specified name. Refer 
	to Toolbar and Toolbar Button Names for a list of the standard 
	named toolbars. 
	@param name The name of the toolbar.
	@return The AVToolBar, or <code>NULL</code> if no AVToolBar was found with the 
	specified name. 
	@see AVAppGetLegacyToolBar 

	@note It is recommended that you position toolbar buttons 
	by finding a related button on the main toolbar (the one 
	returned by AVAppGetLegacyToolBar()) and placing your button next 
	to the existing button. Acrobat will automatically place 
	your tool button on the correct named toolbar so it appears 
	next to the existing button. 
  	@ref ToolbarButtonNames
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVToolBar, AVAppGetLegacyToolBarByName, (const char *name))

/**
	Returns the ASHostEncoding corresponding to Acrobat's current 
	locale setting. For example, if the user is using the English 
	version of Acrobat on a Japanese system, AVAppGetLanguageEncoding() 
	returns a Roman encoding but PDGetHostEncoding() returns a 
	Japanese encoding. 
	@return The encoding constant for the application. 
	@see PDGetHostEncoding 
	@see PDGetPDFDocEncoding 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASHostEncoding, AVAppGetLanguageEncoding, (void))


/**
	Scrolls the <code>pageView</code> to ensure that the specified <code>annot</code> 
	is visible. 
	@param pageView IN/OUT The page view to scroll. 
	@param annot IN/OUT The annotation to scroll to. 
	@notify AVPageViewDidChange 
	@see AVPageViewScrollToRect 
	@see AVPageViewScrollTo 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewScrollToAnnot, (AVPageView pageView, PDAnnot annot))


/**
	Turns the wait cursor on or off. Unlike AVSysGetCursor(), 
	AVSysSetWaitCursor() ensures that the wait cursor stays on 
	until another call to AVSysSetWaitCursor() is made to turn 
	it off, or the time limit is reached. When using this call 
	to turn on the wait cursor, you must ensure that another 
	call will be made to turn it back off. 
	@param turnOn IN/OUT <code>true</code> sets the wait cursor, <code>false</code> resets it. 
	
	@param timeLimit IN/OUT The time limit in ticks (1/60th of a second). 
	If the time limit is reached, the wait cursor will be turned 
	off as if you called <code>AVSysSetWaitCursor(false, ... )</code>. This 
	value is ignored if it is less than or equal to <code>0</code> or if 
	the <code>turnOn</code> parameter is <code>false</code>. Set this to a reasonable 
	nonzero value to ensure that the user wait cursor will go 
	away. 
	@see AVSysGetCursor 
	@see AVSysGetStandardCursor 
	@see AVSysSetCursor 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVSysSetWaitCursor, (ASBool turnOn, ASUns32 timeLimit))


/**
	An exact way to ask if an operation is permitted. This routine 
	should be used to query all user interface-level permissions (for example, 
	to determine whether a tool button or menu item is enabled 
	or whether a tool can act upon a given document). This routine 
	should be used instead of some combination of AVDocIsReadOnly(), AVDocIsExternal(), and 
	PDDocPermRequest(). AVDocPermRequest() calls PDDocPermRequest() 
	internally in the process of determining whether to grant 
	the request. 
	@param doc The document opened in Acrobat. 
	@param obj The description of the target object of a permissions 
	request. 
	@param opr The description of the target operation of a permissions 
	request.
	@return <code>true</code> if the operation is permitted, <code>false</code> otherwise. 
	@see AVDocIsReadOnly 
	@see AVDocIsExternal 
	@see PDDocPermRequest 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVDocPermRequest, (AVDoc doc, PDPermReqObj obj, PDPermReqOpr opr))


/**
	Clients that correctly use machine ports should work with 
	the new off-screen drawing behavior introduced in Acrobat 
	5.0. For other clients, the AVPageViewResumeOffscreenDrawing() 
	and AVpageViewSuspendOffscreenDrawing() are provided for temporarily 
	disabling the off screen drawing behavior so that it acts 
	more like Acrobat 4.0. The one restriction is that you cannot 
	call these routines while the page being is drawn. In other 
	words, do not call these routines from within a drawing 
	callback such as one passed to AVAppRegisterForPageViewDrawing() 
	or an annotation handler's <code>DoDraw</code> or <code>DoDrawEx</code> callback. 
	Off-screen drawing should be suspended as rarely and briefly 
	as possible (for example, only while a client that does 
	not use machine ports correctly has a selection active). 
	
	@param pageView The page view whose drawing is to be suspended.
	@see AVPageViewResumeOffscreenDrawing 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewSuspendOffscreenDrawing, (AVPageView pageView))

/**
	Clients that correctly use machine ports should work with 
	the off-screen drawing behavior introduced in Acrobat 
	5. For other clients, the AVPageViewResumeOffscreenDrawing() 
	and AVPageViewSuspendOffscreenDrawing() are provided for temporarily 
	disabling the off screen drawing behavior so that it acts 
	more like Acrobat 4.0. The one restriction is that you cannot 
	call these routines while the page is drawn. In other words, 
	do not call these routines from within a drawing callback 
	such as one passed to AVAppRegisterForPageViewDrawing() or 
	an annotation handler's <code>DoDraw</code> or <code>DoDrawEx</code> callback. 
	@param pageView The AVPageView being drawn.
	@see AVPageViewSuspendOffscreenDrawing 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewResumeOffscreenDrawing, (AVPageView pageView))


/** 
	(Mac OS only) This call is useful when Acrobat is running embedded in 
	a browser and needs to present a dialog box for user input. 
	However, before presenting the dialog box, Acrobat needs to 
	pull itself to the front to be the front application. This 
	call enables it to do that. 
	@return <code>true</code> if Acrobat either is running in the background and 
	will pull itself to the front, or has already pulled itself 
	to be the front application; <code>false</code> otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVAppDidOrWillSwitchForDialog, (void) )

/**
	(Mac Only) Yield to other applications for <code>yieldTimeout</code>. 

	@note Mac platform clients will need to call AVAppYieldToOtherApps() 
	instead of <code>WaitNextEvent</code> to prevent problems with Mac OS 
	Carbon event handling. AVAppYieldToOtherApps() calls <code>ReceiveNextEvent</code>. 
	It is recommended that you use the kEventDurationForever 
	constant as the argument to AVAppYieldToOtherApps(), though 
	this will impact portability since it is a CodeWarrior <code>define</code> 
	(in CarbonEvents.h). 
	@param yieldTimeout The minimum amount of time to yield 
	in seconds. It is only applicable for Mac OS 8.6 and 9.x. It is a no-op 
	for Windows and UNIX.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVAppYieldToOtherApps, (double yieldTimeout))

/**
	If the <code>win</code> is completely outside the desktop region (it is off screen), 
	it is moved so that it will be within the 
	desktop region (it is on screen). No action is taken 
	if a draggable edge of the window is within the desktop 
	region. The desktop region does not include the task bar 
	(Windows) or menu bar (Mac OS). 
	@param win The window to ensure is on screen.
	@see AVWindowGetDesktopBounds 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVWindowEnsureInBounds, (AVWindow win))

/* Acrobat 5.0SP1 Additions */

#if HAS_MENUS

/**
	(New in Acrobat 5.0.5) 

	Clones a menu, creating a new menu which is an exact duplicate 
	of the original, except that shortcuts are not created for 
	the items. 
	@param menu The menu that is cloned.
	@return The new menu. 
	@since PI_ACROVIEW_VERSION >= 0x00050001
*/
NPROC(AVMenu, AVMenuClone, (AVMenu menu))
#else
NOPROC(AVMenuClone)
#endif

/* Acrobat 6 Additions */

/**
	Scrolls <code>pageView</code> to the location specified by <code>xOrigin</code> and 
	<code>yOrigin</code>, within the limits imposed by the current zoom mode 
	and the Acrobat viewer. 
	@param pageView The page view to scroll. 
	@param xOrigin The x-coordinate to scroll to, specified 
	in device space coordinates. 
	@param yOrigin The y-coordinate to scroll to, specified 
	in device space coordinates.
	@notify AVPageViewDidChange 
	@see AVPageViewScrollToRect 
	@see AVPageViewScrollToAnnot 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewScrollTo, (AVPageView pageView, AVDevCoord xOrigin, AVDevCoord yOrigin))

/**
	Registers a user-supplied procedure to call each time the 
	cursor is moved. If more than one procedure is registered, 
	the procedures are called in the order that they were registered. 
	
	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param cursorProc A user-supplied callback to call each 
	time the cursor is moved. 
	@param data A pointer to user-supplied data to pass to <code>cursorProc</code> 
	each time it is called. 
	@exception genErrNoMemory 
	@see AVAppUnregisterForPageViewAdjustCursor 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppRegisterForPageViewAdjustCursor, (AVPageViewCursorProc cursorProc,
	void* data), AVPageViewRegisterForAdjustCursor)

/**
	Registers a user-supplied procedure to call each time a 
	mouse click occurs. This is useful if a client wishes to 
	handle mouse clicks, and the client is better implemented 
	as something other than an annotation or a tool. If more 
	than one routine is registered to receive mouse clicks, 
	the most recently registered routine is called first. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param clickProc A user-supplied callback to call each time 
	a mouse click occurs. If the user-supplied callback returns 
	<code>true</code>, it indicates that the procedure handled the mouse 
	click, and it should not be passed along to the Acrobat 
	viewer or other clients that registered to receive mouse 
	clicks. If it returns <code>false</code>, the mouse click is passed to 
	the Acrobat viewer or other clients that registered to receive 
	mouse clicks. 
	@param data A pointer to user-supplied data to pass to <code>clickProc</code> 
	each time it is called.
	@exception genErrNoMemory 
	@see AVAppRegisterForPageViewRightClicks 
	@see AVAppUnregisterForPageViewClicks 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppRegisterForPageViewClicks, (AVPageViewClickProc clickProc, void* data),
	AVPageViewRegisterForClicks)

/**
	Registers a user-supplied procedure to call each time a 
	window is drawn, after the page's contents and annotations 
	have been drawn. This allows clients to draw whatever they 
	wish to on top of pages. The procedure is called each time 
	the page view changes (scrolls, zooms, goes to a different 
	page). 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>

	<p>You can register only one procedure, but you can register 
	it more than once, with a different client data pointer 
	in each case. If more than one procedure-data combination 
	is registered, they are called in a last-in, last-out order. 
	In versions prior to 6.0, you should not do this, as the 
	call to AVAppUnregisterForPageViewDrawing() un-registers only 
	one of the registered combinations, and does not guarantee 
	which one it is. However, in version 6.0 or later, you can 
	pass the same proc and <code>clientData</code> pointer to AVAppUnregisterForPageViewDrawingEx() 
	to un-register that particular combination. </p>
	@param proc A user-supplied callback to call each time a 
	window is drawn. 
	@param data A pointer to user-supplied data to pass to <code>proc</code> 
	each time it is called.
	@exception genErrNoMemory 
	@see AVAppUnregisterForPageViewDrawing 
	@see AVAppUnregisterForPageViewDrawingEx 

	@note As of version 5.0, Acrobat renders PDF pages offscreen 
	before copying them to the display memory. Windows developers 
	who call AVPageViewAcquireMachinePort() on the AVPageView 
	passed to the drawing callback should note that the <code>HWND</code> 
	points to the screen but the <code>HDC</code> points to an offscreen 
	bitmap. All drawing should be performed using the returned 
	<code>HDC</code>. Developers should not create their own <code>HDC</code> based on 
	the returned <code>HWND</code> because their content will be lost when 
	Acrobat copies the offscreen buffer to the display. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVAppRegisterForPageViewDrawing, (AVPageViewDrawProc proc, void* data),
	AVPageViewRegisterForDrawing)

/**
	Opens and displays a document from a file, using the specified 
	parameters to control the window's size, location, and visibility. 
	
	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>

	<p>If you want to display a page from a PDF file as a bitmap, 
	use PDPageDrawContentsToWindow(). </p>
	@ingroup ReplaceableMethods
	@param pathName The file to open. 
	@param fileSys The file system on which <code>pathName</code> resides. 
	You can obtain the default file system with ASGetDefaultFileSys(). 
	@param tempTitle If <code>tempTitle != NULL</code>, <code>pathName</code> is a temporary 
	file and <code>tempTitle</code> is used as the window's title. 
	@param params The parameters used when opening the file. It can 
	be <code>NULL</code>.
	@return The document that was opened. 
	@notify AVDocWillOpenFromFile 
	@notify AVDocDidOpen 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action)
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action)
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromFile 
	@see AVDocOpenFromFileWithParamString 
	@see AVDocOpenFromPDDoc 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without 
	letting at least one event loop complete.
	@note Changed from <code>char*</code> to ASText argument type in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
PROC(AVDoc, AVDocOpenFromFileWithParams, (ASPathName pathName, ASFileSys fileSys,
	const ASText tempTitle, AVDocOpenParams params))

/**
	Opens and displays a document from a PDDoc, using the specified 
	parameters to control the window's size, location, and visibility. 
	
	If you want to display a page from a PDF file as a bitmap, 
	use PDPageDrawContentsToWindow(). 
	@param pdDoc The document to open and display. 
	@param tempTitle If <code>tempTitle != NULL</code>, the path name is a temporary 
	file and <code>tempTitle</code> is used as the window's title. 
	@param params The parameters used when opening the file. It can 
	be <code>NULL</code>.
	@return The document that was opened. 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action) 
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDoc 
	@see AVDocOpenFromPDDocWithParamString 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without 
	letting at least one event loop complete. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVDoc, AVDocOpenFromPDDocWithParams, (PDDoc pdDoc, const ASText tempTitle, AVDocOpenParams params))

/**
	Opens and displays a document from a file, using the specified 
	parameters to control the window's size, location, and visibility. 
	
	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>

	<p>If you want to display a page from a PDF file as a bitmap, 
	use PDPageDrawContentsToWindow. </p>
	@ingroup ReplaceableMethods
	@param file The ASFile to open. 
	@param tempTitle If <code>tempTitle != NULL</code>, the path name is a temporary 
	file and <code>tempTitle</code> is used as the window's title. 
	@param params The parameters used when opening the file. It can 
	be <code>NULL</code>.
	@return The document that was opened. 
	@notify AVDocWillOpenFromFile 
	@notify AVDocDidOpen 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action) 
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromFile 
	@see AVDocOpenFromPDDoc 
	@see AVDocOpenFromPDDocWithParams 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without 
	letting at least one event loop complete. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
PROC(AVDoc, AVDocOpenFromASFileWithParams, (ASFile file, const ASText tempTitle, AVDocOpenParams params))

/**
	Prints a document with a full range of options. Printing 
	is complete when this method returns. It performs <i>embedded</i> 
	printing; that is, it allows a PDF page to print within a bounding 
	rectangle on a page. It allows interactive printing to the 
	specified printer (Windows, Mac OS, and UNIX). 

	<p>You can replace this method with your own version, using 
	HFTReplaceEntry(). </p>
	@ingroup ReplaceableMethods
	@param doc The AVDoc from which to print pages. 
	@param params A structure containing printing parameters. 
	See AVDocPrintParams. With Adobe Reader, you cannot 
	use the <code>emitToFile</code> flag. For Adobe Reader, use the <code>emitToPrinter</code>, 
	<code>interactive</code>, or <code>embedded</code> flags. In Acrobat 6.0 
	Standard, the printer mark drawing flags (<code>marksFlags</code>) in 
	the parameters structure are ignored.
	@exception genErrBadParm is raised if an invalid parameter is provided. 
	It can raise any of the <code>CosErrExpected</code> exceptions, such as ErrSysCosSyntax or cosErrExpectedNumber. 
	In general, this method can raise any exception that can occur 
	during the parsing of a page and its resources, such as pdErrUnknownProcsets or pdErrUnableToExtractFontErr. 
	@notify PDDocWillPrintPages 
	@notify PDDocWillPrintPage 
	@notify PDDocDidPrintPage 
	@notify PDDocDidPrintPages 
	@notify PDDocDidPrintTiledPage 
	@notify PDDocPrintingTiledPage 
	@notify PDDocWillPrintTiledPage 
	@see AVDocDoPrint 
	@see AVDocPrintPages 

	@note If security has been set on a file so that it is not 
	printable, the document will not print, but no error is 
	raised. Check the security before printing the file. 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
PROC(void, AVDocPrintPagesWithParams, (AVDoc doc, AVDocPrintParams params))

/**
	Fills out the given AVDocViewDef structure with the information 
	needed to restore this document's state at a later date. 
	You must set the <code>use</code> fields as desired. 
	@param doc The document whose state is recorded. 
	@param viewDef A pointer to the structure that stores 
	the state.
	@see AVDocGetViewDefEx 
	@see AVDocSetViewDef 
	@note Numeric types in AVDocViewDef have changed in Acrobat 
	6.0, and the method has been superseded by AVDocGetViewDefEx(). 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVDocGetViewDef, (AVDoc doc, AVDocViewDef viewDef))

/**
	Sets the document's state to match the information in <code>viewDef</code>. 
	
	@param doc The document whose state is updated. 
	@param viewDef A pointer to the structure that stores 
	the state.
	@see AVDocGetViewDef 
	@see AVDocGetViewDefEx 
	@see AVDocSetViewDefEx 
	@note Numeric types in AVDocViewDef have changed in Acrobat 
	6.0, and the method has been superseded by AVDocGetViewDefEx(). 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
SPROC(void, AVDocSetViewDef, (AVDoc doc, AVDocViewDef viewDef), AVDocUseViewDef)

/**
	Gets the selection server that handles the specified selection 
	type. 
	@param type IN/OUT The ASAtom corresponding to the type for which 
	the selection server was registered. The string for the type 
	can be converted to an ASAtom using ASAtomFromString(). 
	@return The selection server that handles the specified type. It returns 
	<code>NULL</code> if no such selection server is registered. 
	@see AVDocRegisterSelectionServer 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVDocSelectionServer, AVDocGetSelectionServerByType, (ASAtom type))

/**
	Registers a new selection server with the Acrobat viewer. 
	Selection servers allow the selection of items other than 
	those that can be selected in the as-shipped Acrobat viewer. 
	For example, a selection server could allow a user to select 
	a sampled image. 

	<p>This method can be used to replace an existing selection 
	server that handles the same selection type. </p>
	@param server IN/OUT A structure containing the selection server's 
	callback functions. This structure must not be freed after 
	calling AVDocRegisterSelectionServer(). 
	@return This always returns <code>true</code>. 
	@exception genErrBadParm is raised if <code>server</code> is <code>NULL</code>, if the size field 
	in the AVDocSelectionServerRec is incorrect, or if the selection server's AVDocSelectionGetTypeProc() is <code>NULL</code>. 
	@see AVDocClearSelection 
	@see AVDocCopySelection 
	@see AVDocDeleteSelection 
	@see AVDocDoSelectionProperties 
	@see AVDocEnumSelection 
	@see AVDocGetSelection 
	@see AVDocShowSelection 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVDocRegisterSelectionServer, (AVDocSelectionServer server))

/**
	Gets the aperture of the specified page view. The aperture 
	is the rectangular region of the window in which the document 
	is drawn, measured in device space units. 
	@param pageView The page view whose aperture is obtained. 
	
	@param rect (Filled by the method) A pointer to the aperture 
	rectangle, specified in device space coordinates.
	@see AVPageViewGetGrayRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGetAperture, (AVPageView pageView, AVDevRect *rect))

/**
	If the specified rectangle and margin fits inside the aperture, the pageview is scrolled to center the rectangle within the aperture.
	This method is handy for auto-scrolling the AVPageView in a natural 
	way to bring some page object completely into view. It does 
	not affect the zoom level or AVZoomType. 
	@param pageView The page view to scroll. 
	@param rect A pointer to the rectangle that is completely 
	visible. 
	@param favorLeft Used when <code>rect</code> is wider than the window's 
	aperture. If <code>favorLeft</code> is <code>true</code>, it favors the left side. If it is
	<code>false</code>, it favors the right side. Favoring a side means that 
	the corresponding edge will appear within the aperture, 
	even if the opposite edge will not. 
	@param favorTop Used when <code>rect</code> is taller than the window's 
	aperture. If <code>favorTop</code> is <code>true</code>, it favors the top side. If it is <code>false</code>, 
	it favors the bottom side. Favoring a side means that the corresponding 
	edge will appear within the aperture, even if the opposite 
	edge will not. 
	@param margin The number of pixels that <code>rect</code> should be from 
	the nearest edges if it does not cause the rectangle to 
	go from completely visible to partially obscured.
	@notify AVPageViewDidChange 
	@see AVPageViewScrollTo 
	@see AVPageViewScrollToAnnot 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewScrollToRect, (AVPageView pageView, const AVDevRect *rect,ASBool favorLeft,
	ASBool favorTop, AVDevSize margin))

/**
	Indicates that the specified area of <code>pageView</code> is invalid 
	and should be redrawn. This adds the rectangle to the list 
	of regions to redraw, but does not force an immediate redraw. 
	Use AVPageViewDrawNow() to force an immediate redraw. 
	@param pageView The AVPageView in which a region is invalidated. 
	
	@param area A pointer to the rectangle to invalidate, specified 
	in device space coordinates. Use AVPageViewRectToDevice() 
	to convert a user space rectangle to device space. Pass 
	<code>NULL</code> to invalidate the entire currently visible portion 
	of the page.
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewInvalidateRect, (AVPageView pageView, AVDevRect *area))

/**
	Inverts the interior of a rectangle. 
	@param pageView The page view in which the inverted rectangle 
	is drawn. 
	@param rect A pointer to the rectangle to invert, specified 
	in device space coordinates. Use AVPageViewRectToDevice() 
	to convert the coordinates of a rectangle that is specified 
	in user space. 
	@param highlight If <code>true</code>, it uses the highlight mode specified 
	by <code>avpHighlightMode</code> in the Acrobat viewer's preferences 
	file (see AVAppSetPreference()). If it is <code>false</code>, it uses a default 
	highlighting mode.
	@see AVPageViewDrawRect 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewInsetRect 
	@see AVPageViewInvertRectOutline 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewInvertRect, (AVPageView pageView, const AVDevRect *rect, ASBool highlight))

/**
	Draws a stroked, but not filled, rectangle using the color 
	most recently set using AVPageViewSetColor(). 
	@param pageView The page view in which the rectangle is 
	drawn. 
	@param rect A pointer to the rectangle to draw, specified 
	in device space coordinates. 
	@param lineWidth The border width in pixels. If <code>lineWidth > 1</code>, 
	the border line is entirely inside the <code>rect</code>, thus shrinking 
	the area inside the outline. 
	@param dashArray A pointer to an array of fixed numbers, 
	whose elements alternately specify the length of dashes 
	and gaps. Pass <code>NULL</code> to draw a solid outline. 
	@param arrayLen The number of elements in <code>dashArray</code>. It is ignored 
	if <code>dashArray</code> is <code>NULL</code>. The maximum allowed number of elements 
	is currently <code>10</code>.
	@see AVPageViewDrawRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewDrawRectOutline, (AVPageView pageView, const AVDevRect *rect,
	AVDevSize lineWidth, ASFixed * dashArray, AVTArraySize arrayLen))

/**
	Draws a rectangle filled with the color most recently set 
	using AVPageViewSetColor(). 
	@param pageView IN/OUT The page view in which the rectangle is 
	drawn. 
	@param rect IN/OUT A pointer to the rectangle to draw, specified 
	in device space coordinates. 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewDrawAnnotSequence 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewDrawRect, (AVPageView pageView, const AVDevRect *rect))

/**
	Gets an annotation's bounding rectangle. This may be a superset 
	of the actual bounding box of a particular annotation view. 
	
	<p>If the page view has more than one page displayed, as in 
	the continuous modes, you should call AVPageViewSetPageNum() 
	with the annotation's page number before calling this method. </p>
	@param pageView The page view for which the rectangle 
	is transformed. 
	@param anAnnot The annotation whose bounding rectangle 
	is obtained. 
	@param rect (Filled by the method) A pointer to the annotation's 
	bounding rectangle, specified in device space coordinates.
	@see AVPageViewSetPageNum 
	@see AVPageViewTransformRectRZ 
	@see PDPageGetAnnot 
	
	@note The coordinate numeric type changed in PI_ACROVIEW_VERSION 
	(in PIRequir.h) 0x00060000. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGetAnnotRect, (AVPageView pageView, PDAnnot anAnnot, AVDevRect *rect))

/**
	Transforms a rectangle's coordinates from user space to 
	device space. The resulting AVRect will be <i>normal</i>, meaning 
	that <code>left < right</code> and <code>top < bottom</code>. 
	@param pageView The page view for which the coordinates are 
	transformed. 
	@param p A pointer to the rectangle whose coordinates are 
	transformed, specified in user space coordinates. 
	@param rect (Filled by the method) A pointer to a rectangle 
	containing the device space coordinates corresponding to 
	<code>p</code>.
	@see AVPageViewPointToDevice 
	@see AVPageViewDevicePointToPage 
	@see AVPageViewDeviceRectToPage 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewRectToDevice, (AVPageView pageView, const ASFixedRectP p, AVDevRect* rect),
	AVPageRectToDevice)

/**
	Transforms a rectangle from device space to user space coordinates. 
	The resulting ASFixedRect is <i>normal</i>, meaning 
	that <code>left < right</code> and <code>bottom < top</code>. 

	@param pageView The page view for which the rectangle is transformed. 
	@param rect A pointer to a device space rectangle whose 
	coordinates are transformed to user space. 
	@param p (Filled by the method) A pointer to a user space 
	rectangle corresponding to <code>rect</code>.
	@see AVPageViewPointToDevice 
	@see AVPageViewDevicePointToPage 
	@see AVPageViewDeviceRectToPageRZ 
	@see AVPageViewRectToDevice 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewDeviceRectToPage, (AVPageView pageView, const AVDevRect* rect,
	ASFixedRect *p), AVPageDeviceRectToPage)

/**
	Draws the CosObj (which currently must be a Form object) 
	and scales it to fit the rectangle. This method may be used to draw 
	an annotation appearance. 
	@param pageView The page view. 
	@param cosObj The CosObj to draw. 
	@param r The rectangle in which to draw.
	@see AVPageViewAppearanceGetAVMatrix 
	@see AVPageViewDrawCosObjEx 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVPageViewDrawCosObj, (AVPageView pageView, CosObj cosObj, const AVDevRect* r))

/**
	Draws a 3-D looking inset rectangle on the page view. It can 
	be used to implement an inset style link, where clicking 
	the link causes the page to appear to push into the screen. 
	@param pageView IN/OUT The page view on which to draw the rectangle. 
	
	@param rr IN/OUT The rectangle to draw. 
	@param down IN/OUT <code>true</code> to draw an inset rectangle, <code>false</code> to draw 
	the rectangle in its normal state. 
	@see AVPageViewDrawRect 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewInvertRect 
	@see AVPageViewInvertRectOutline 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(void, AVPageViewInsetRect, (AVPageView pageView, const AVDevRect* rr, ASBool down))

/**
	Draws the CosObj (which currently must be a Form object), 
	scales it to fit the rectangle, and transforms it according to <code>matrix</code>. 
	This method is the same as AVPageViewDrawCosObj(), but applies 
	an ASFixedMatrix transformation to the CosObj once the CosObj 
	has been scaled to the anamorphic dimensions of the AVRect. 
	This method may be used to draw an annotation appearance. 
	@param pageView The page view. 
	@param cosObj The CosObj to draw. 
	@param r The rectangle in which to draw. 
	@param matrix A pointer to a matrix specifying the matrix 
	to transform the <code>cosObj</code> based on the rectangle. For example, if the 
	AVRect is [10 20 110 220] describing a 100 x 200 area near 
	the top left corner of the page, a ASFixedMatrix of [0.5 
	0 0 0.5 50 100] would scale the CosObj to 50% and center 
	it inside the AVRect.
	@see AVPageViewAppearanceGetAVMatrix 
	@see AVPageViewDrawCosObj 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020003
*/
NPROC(void, AVPageViewDrawCosObjEx, (AVPageView pageView, CosObj cosObj, const AVDevRect* r, ASFixedMatrix *matrix))

/**
	Draws the annotation sequence number of an annotation in 
	a rectangle. 

	@param pv The page view in which the annotation is drawn. 
	@param an The annotation whose sequence number is drawn. 
	@param bbox A bounding box in which to draw the sequence 
	number of the annotation.
	@see AVPageViewDrawRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVPageViewDrawAnnotSequence, (AVPageView pv, PDAnnot an, const AVDevRect *bbox))

/**
	Gets the rectangle that bounds a page view. This may include 
	some of the gray area outside a page's crop box. 
	@param pageView The page view. 
	@param greyRect (Filled by the method) A rectangle bounding 
	the page view, specified in device space coordinates.
	@see AVPageViewDrawRect 
	@see AVPageViewGetAperture 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(void, AVPageViewGetGrayRect, (AVPageView pageView, AVDevRect* greyRect))

/**
	Draws the specified rectangle in <code>pageView</code> using the ghost 
	outline. 
	@param pageView IN/OUT The page view into which <code>rect</code> is drawn. 
	
	@param rect IN/OUT The rectangle to draw. 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewGhostRectOutline, (AVPageView pageView, const AVDevRect* rect))

/**
	Tests to determine whether the given point lies on any of the control 
	handles of <code>rect</code>. 
	@param rect The rectangle to test. 
	@param bMidpoints Pass <code>true</code> if you are interested in the midpoint 
	handles. If it is <code>false</code> and a midpoint handle is hit, kAVDragRect 
	is returned. 
	@param x The x-coordinate of the point. 
	@param y The y-coordinate of the point.
	@return <code>-1</code> if the point is not within the rectangle. 
	If the point is within the rectangle, but not over a handle, 
	kAVDragRect is returned. If the point is within a handle 
	region, one of the AVRectHandleType constants is returned. 
	
	@see AVPageViewSnapRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVDragTypeEx, AVRectHandleHitTest, (const AVDevRect *rect, ASBool bMidpoints, AVDevCoord x, AVDevCoord y))

/**
	Draws the specified rectangle in the page view with drag 
	handles. 
	@param pageView The page view in which the <code>rect</code> is drawn. 
	
	@param rect The rectangle that is to be drawn. 
	@param bMidpoints If <code>true</code>, additional handles are drawn 
	at the midpoint of each side of the rectangle. 
	@param bThin If <code>true</code>, the rectangle is drawn using thin 
	lines. 
	@param dashArray A pointer to an array of fixed numbers 
	whose elements alternately specify the length of dashes 
	and gaps. Pass <code>NULL</code> to use a solid outline. 
	@param arrayLen The number of elements in <code>dashArray</code>. 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewDrawRectOutlineWithHandles, (AVPageView pageView, const AVDevRect *rect, ASBool bMidpoints, ASBool bThin, ASFixed *dashArray, AVTArraySize arrayLen))

/**
	Gets the mouse position in <code>pageView</code>. The mouse position 
	is specified in global coordinates. On Mac OS, 
	it is equivalent to calling the Toolbox <code>GetMouse</code> call and 
	adding the window's offset on the screen; on UNIX, it is 
	equivalent to calling <code>XQueryPointer</code> and adding the window's 
	offset on the screen. 
	@param pageView The page view in which the mouse location 
	is obtained. 
	@param x (Filled by the method) The x-coordinate of the 
	mouse location. 
	@param y (Filled by the method) The y-coordinate of the 
	mouse location.
	@see AVSysMouseIsStillDown 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewGetMousePosition, (AVPageView pageView, AVDevCoord *x, AVDevCoord *y))

/**
	Allows the user to drag out a new rectangle. Call this method 
	when the user clicks at some point and needs to create a 
	rectangle. The method returns when the user releases the 
	mouse button. 
	@param pageView The page view in which the rectangle is 
	created. 
	@param xStart The x-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param yStart The y-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param resultRect (Filled by the method) A pointer to the 
	rectangle that the user dragged out, specified in device 
	space coordinates.
	@see AVPageViewDragRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewDragOutNewRect, (AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart,
	AVDevRect *resultRect))

/**
	Allows the user to move or resize a rectangle. Call this 
	method when the user clicks on a rectangle to modify. It 
	returns after the user releases the mouse button. 
	@param pageView The page view in which the rectangle is 
	located. 
	@param xStart The x-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param yStart The y-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param startRect A pointer to the initial rectangle, which 
	is to moved or resized, specified in device space coordinates. 
	
	@param resultRect (Filled by the method) A pointer to the 
	resized or moved rectangle, specified in device space coordinates. 
	
	@param dragType One of the AVDragType constants. 
	@param extrema (May be <code>NULL</code>) A pointer to the 
	rectangle specifying the maximum limits of the user-dragged 
	rectangle. If it is <code>NULL</code>, the rectangle returned 
	by AVPageViewGetGrayRect() is used instead. The user cannot grow the rectangle outside <code>extrema</code>, 
	specified in device space coordinates. Pass <code>NULL</code> if you 
	do not wish to limit the changes the user is making. <code>extrema</code> 
	is ignored if <code>dragType</code> is <code>0</code>.
	@see AVPageViewDragOutNewRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewDragRect, (AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart,
	AVDevRect *startRect, AVDevRect *resultRect, ASInt32 dragType, AVDevRect *extrema))

/**
	Tests whether the specified point is within an annotation. 
	This method is typically used by mouse-handling code, to 
	pass clicks within an annotation to the appropriate annotation 
	handler. For each annotation, this method calls the appropriate 
	annotation handler's AVAnnotHandlerPtInAnnotViewBBoxProc() 
	to test whether the point is within the annotation. 
	@param pageView The page view for which the point to test. 
	
	@param xHit The x-coordinate of the point to test. 
	@param yHit The y-coordinate of the point to test. 
	@param hitAnnot (Filled by the method) A pointer to the 
	top-most annotation (if any) that was hit by the mouse click.
	@return <code>true</code> if the location specified by <code>xHit</code> and <code>yHit</code> is within 
	an annotation, <code>false</code> otherwise. 
	@see AVPageViewGetAnnotRect 
	@see AVPageViewGetMousePosition 
	@see AVPageViewGetSelectedAnnotPageNum 
	@see AVPageViewIsAnnotOfTypeAtPoint 
	@see AVPageViewGetSelectedAnnotPageNum 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVPageViewIsAnnotAtPoint, (AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit,
	PDAnnot *hitAnnot))

/**
	Tests whether the specified point is within a bead. It returns 
	the bead if it is. 
	@param pageView The page view in which the point is tested. 
	
	@param xHit The x-coordinate of the point to test, specified 
	in device space coordinates. 
	@param yHit The y-coordinate of the point to test, specified 
	in device space coordinates. 
	@param beadP (Filled by the method) A pointer to the bead 
	in which the point is located. This is only filled if the 
	point is within a bead.
	@return <code>true</code> if the point is within a bead, <code>false</code> otherwise. If 
	the location is within a bead, the bead is returned in <code>beadP</code>. 
	
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(ASBool, AVPageViewIsBeadAtPoint, (AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit,
	PDBead *beadP))

/**
	Transforms a point's coordinates from device space to user 
	space. 
	@param pageView The page view for which the point's coordinates 
	are transformed. 
	@param x The x-coordinate of the point to transform, specified 
	in device space coordinates. 
	@param y The y-coordinate of the point to transform, specified 
	in device space coordinates. 
	@param p (Filled by the method) A pointer to a point whose 
	user space coordinates correspond to <code>x</code> and <code>y</code>.
	@see AVPageViewPointToDevice 
	@see AVPageViewRectToDevice 
	@see AVPageViewDeviceRectToPage 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewDevicePointToPage, (AVPageView pageView, AVDevCoord x, AVDevCoord y,
	ASFixedPoint *p), AVPageDevicePointToPage)

/**
	Called in response to a mouse click to track a text selection 
	on the screen. It uses the AVPageView current color, and leaves 
	the screen with any highlights visible. It does not affect 
	the current document selection. 
	@param pageView The page view. 
	@param xHit The x-coordinate of the original click. 
	@param yHit The y-coordinate of the original click. 
	@param current Any existing selection that should be built 
	upon.
	@return PDTextSelect containing the words selected. 
	@see AVPageViewHighlightText 
	@see AVPageViewInvalidateText 
	@see AVPageViewPointInText 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
SPROC(PDTextSelect, AVPageViewTrackText, (AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDTextSelect current), AVPageViewTrackTextHost)

/**
	Tests if the given point is in the PDTextSelect. 
	@param pageView The page view. 
	@param xHit The x-coordinate to test. 
	@param yHit The y-coordinate to test. 
	@param pdText The text to hit-test upon.
	@return <code>true</code> if the point is in the PDTextSelect, <code>false</code> otherwise. 
	
	@see AVPageViewTrackText 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVPageViewPointInText, (AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDTextSelect pdText))

/**
	Displays the given AVMenu as a popup menu anchored at <code>xHit</code> 
	and <code>yHit</code>, which are in device coordinates relative to <code>pageView</code>.
	
	@param pageView The page view in which the menu appears. 
	
	@param menu The displayed menu. 
	@param xHit The x-coordinate of the upper left corner 
	of the menu. 
	@param yHit The y-coordinate of the upper left corner 
	of the menu. 
	@param rightMouse <code>true</code> if the right mouse button (where 
	applicable) was used to invoke the popup, <code>false</code> otherwise. 
	
	@param choice The index of the AVMenuItem that should 
	appear under the mouse at popup time.
	@return The menu item selected from <code>menu</code>. 
	@see AVLegacyToolButtonGetMenu 
	@see AVLegacyToolButtonSetMenu 
	@see AVMenuDoPopUp 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
NPROC(AVMenuItem, AVPageViewDoPopupMenu, (AVPageView pageView, AVMenu menu, AVDevCoord xHit, AVDevCoord yHit, ASBool rightMouse, AVMenuIndex choice))

/**
	Transforms an annotation's rectangle from device space to 
	user space coordinates, allowing for the annotation's attributes 
	of whether it should zoom or rotate when the page is zoomed 
	or rotated. It also specifies a point that can remain in 
	the view.
	@param pageView The page view for which the rectangle is transformed. 
	
	@param flags Flags to indicate whether the annotation 
	rotates or zooms with the page view. These flags correspond 
	to the annotation's F key and can be obtained from PDAnnotGetFlags(). 
	<p>It must be an OR of the following flags:</p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Flag</TH><TH>Description</TH></TR>
	<TR><TD>pdAnnotNoZoom</TD><TD>The annotation does not zoom with the view.</TD></TR>
	<TR><TD>pdAnnotNoRotate</TD><TD>The annotation does not rotate with the page.</TD></TR>
	</TABLE>

	@param xHot The x-coordinate of the point that should remain 
	in the view. 
	@param yHot The y-coordinate of the point that should remain 
	in the view. 
	@param rect A pointer to a device space annotation rectangle 
	whose coordinates are transformed to user space. 
	@param p (Filled by the method) A pointer to a user space 
	rectangle corresponding to <code>src</code>.
	@see AVPageViewAppearanceGetAVMatrix 
	@see AVPageViewDeviceRectToPage 
	@see AVPageViewRectToDevice 
	@see AVPageViewTransformRectRZ 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00040000
*/
SPROC(void, AVPageViewDeviceRectToPageRZ, (AVPageView pageView,
										   AVTFlagBits flags,
										   AVDevCoord xHot,
										   AVDevCoord yHot,
										   const AVDevRect* rect,
										   ASFixedRect *p),
	  AVPageDeviceRectToPageRZ)

/**
  	This method is superseded by AVPageViewSnapPointEx() in Acrobat 6.0.
  
  	<p>Snaps a point to the layout grid if the <code>avpSnapToGrid</code> preference 
  	is set.</p>

	@param pageView The page view. 
	@param x (Filled by the method) The x-coordinate of the 
	point. 
	@param y (Filled by the method) The y-coordinate of the 
	point. 
	@param direction An AVDragType indicating how the point 
	is to be translated. Not all AVDragTypes are allowed. 
	<p>Only the following AVDragTypes are used:</p>

	<TABLE rules="all" cellspacing="1">
	<TR><TH>AVDragType</TH><TH>Description</TH></TR>
	<TR><TD>kAVDragRect</TD><TD>Snap to the nearest grid intersection.</TD></TR>
	<TR><TD>kAVDragSnapToTopLeft</TD><TD>Snap to the nearest grid intersection in the top left direction.</TD></TR>
	<TR><TD>kAVDragSnapToTop</TD><TD>Snap to the nearest grid line above this point; <code>x</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToTopRight</TD><TD>Snap to the nearest grid intersection	in the top right direction.</TD></TR>
	<TR><TD>kAVDragSnapToRight</TD><TD>Snap to the nearest grid line right of this point; <code>y</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToBottomRight</TD><TD>Snap to the nearest grid intersection in the bottom right direction.</TD></TR>
	<TR><TD>kAVDragSnapToBottom</TD><TD>Snap to the nearest grid line below this point; <code>x</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToBottomLeft</TD><TD>Snap to the nearest grid intersection in the bottom left direction.</TD></TR>
	<TR><TD>kAVDragSnapToLeft</TD><TD>Snap to the nearest grid line left of this point; <code>y</code> is unchanged.</TD></TR>
	</TABLE>

	@note This method is superseded by AVPageViewSnapPointEx() in Acrobat 6.0.
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewSnapPoint, (AVPageView pageView, AVDevCoord *x, AVDevCoord *y, AVDragType direction))

/**
	Gets the current mouse position snapped to the layout grid. 
	@param pageView The current page view. 
	@param x (Filled by the method) The x-coordinate of the mouse 
	position. 
	@param y (Filled by the method) The y-coordinate of the mouse 
	position. 
	@param direction An AVDragType indicating how the point 
	is to be translated. Not all AVDragTypes are allowed: only 
	those indicating how the point is to be translated are allowed. 
	<p>The following AVDragTypes are used:</p>
	
	<TABLE rules="all" cellspacing="1">
	<TR><TH>AVDragType</TH><TH>Description</TH></TR>
	<TR><TD>kAVDragRect</TD><TD>Snap to the nearest grid intersection.</TD></TR>
	<TR><TD>kAVDragSnapToTopLeft</TD><TD>Snap to the nearest grid intersection in the top left direction.</TD></TR>
	<TR><TD>kAVDragSnapToTop</TD><TD>Snap to the nearest grid line above this point; <code>x</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToTopRight</TD><TD>Snap to the nearest grid intersection	in the top right direction.</TD></TR>
	<TR><TD>kAVDragSnapToRight</TD><TD>Snap to the nearest grid line right of this point; <code>y</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToBottomRight</TD><TD>Snap to the nearest grid intersection in the bottom right direction.</TD></TR>
	<TR><TD>kAVDragSnapToBottom</TD><TD>Snap to the nearest grid line below this point; <code>x</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToBottomLeft</TD><TD>Snap to the nearest grid intersection in the bottom left direction.</TD></TR>
	<TR><TD>kAVDragSnapToLeft</TD><TD>Snap to the nearest grid line left of this point; <code>y</code> is unchanged.</TD></TR>
	</TABLE>

	@see AVPageViewDragOutNewRectSnapped 
	@see AVPageViewDragRectSnapped 
	@see AVPageViewSnapPoint 
	@see AVPageViewSnapRect 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(void, AVPageViewGetMousePositionSnapped, (AVPageView pageView, AVDevCoord *x, AVDevCoord *y, AVDragType direction))

/**
	Drags out a rectangle anchored at the given point. The rectangle 
	will be snapped to the layout grid. 
	@param pageView The page view in which the rectangle will be 
	created. 
	@param xStart The x-coordinate of the anchor point. 
	@param yStart The y-coordinate of the anchor point. 
	@param resultRect (Filled by the method) The resulting 
	rectangle generated by the user. 
	@param cursorArray A pointer to an array of AVCursor objects. 
	This value is used in conjunction with <code>nCursors</code> and is treated 
	as follows: 
	
	<ul>
	<li>If it is <code>NULL</code>, the default cursor will be used 
	during the drag. <code>nCursors</code> is ignored.</li>
	<li>If it is non-<code>NULL</code> and 
	<code>nCursors</code> is <code>1</code>, the supplied cursor will replace the default 
	cursor during the drag.</li>
	<li>If it is non-<code>NULL</code> and <code>nCursors</code> is <code>2</code>, 
	the first cursor will replace the default cursor during 
	the drag, and the second cursor will be used if the user 
	presses the control key (on Windows) or the option key (on Mac OS).</li>
	</ul>
	
	@param nCursors The number of cursors supplied in <code>cursorArray</code>.
	@return A bit-wise OR of the Modifier Keys that were pressed as 
	the rectangle was dragged out. See AVSysGetModifiers(). 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVTFlagBits, AVPageViewDragOutNewRectSnapped, (AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart,
	AVDevRect *resultRect, AVCursor *cursorArray, AVTSmallArraySize nCursors))

/**
  	<p>Superseded in Acrobat 6.0 by AVPageViewDragRectSnappedEx().</p>
  
  	<p>Allows the user to move or resize an existing rectangle. 
	If the user has enabled Snap To Grid from the main menu, 
	the resulting rectangle will be aligned to the layout grid 
	according to the <code>dragType</code> parameter.</p>

	@param pageView The page view in which the rectangle resides. 
	
	@param xStart The x-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param yStart The y-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param startRect The initial position of the rectangle. 
	
	@param resultRect (Filled by the method) The position 
	of the rectangle at the end of the operation. 
	@param dragType One of the AVDragType constants. These 
	determine whether the drag is a resize or a move operation. 
	<p>To move the rectangle, specify one of the following:</p> 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Version</TH><TH>Description</TH></TR>
	<TR><TD>kAVDragRect</TD><TD>The corner of the rectangle that is closest to (<code>xStart</code>,<code>yStart</code>) 
	is snapped to the grid, and dragging begins from that point.</TD></TR>
	<TR><TD><code>kAVDragSnapToXXX</code></TD><TD>The corner or edge specified by <code>'XXX'</code> 
	(<code>TopLeft</code>, <code>Top</code>, and so on) is snapped, and dragging begins from that point.</TD></TR>
	</TABLE>
	
	<p>To resize the rectangle, specify <code>kAVDragXXX</code>. The corner or edge specified 
	by <code>'XXX'</code> (<code>TopLeft</code>, <code>Top</code>, and so on) is dragged, and the opposite 
	corner or edge is used as an anchor point.</p>
	
	@param extrema (May be <code>NULL</code>) The rectangle to which the drag operation 
	is restricted. If it is <code>NULL</code>, the rectangle returned by AVPageViewGetGrayRect() 
	is used instead. Use this to restrict the drag operation 
	to a bounding rectangle. It may be <code>NULL</code>, in which case the 
	bounding rectangle of the page view is used. 
	@param cursorArray A pointer to an array of AVCursor objects. 
	This value is used in conjunction with <code>nCursors</code> and is treated 
	as follows: 
	
	<ul>
	<li>If it is <code>NULL</code>, the default cursor will be used 
	during the drag. <code>nCursors</code> is ignored.</li>
	<li>If it is non-<code>NULL</code> and 
	<code>nCursors</code> is <code>1</code>, the supplied cursor will replace the default 
	cursor during the drag.</li>
	<li>If it is non-<code>NULL</code> and <code>nCursors</code> is <code>2</code>, 
	the first cursor will replace the default cursor during 
	the drag, and the second cursor will be used if the user 
	presses the control key (on Windows) or the option key (on Mac OS).</li>
	</ul>
	
	@param nCursors The number of cursors supplied in <code>cursorArray</code>.
	@return A bit-wise OR of the Modifier Keys that were pressed as 
	the rectangle was dragged. 
	@see AVPageViewDragRectSnappedEx 
	@see AVPageViewSnapPointEx 
	@see AVSysGetModifiers 

	@note Superseded in Acrobat 6.0 by AVPageViewDragRectSnappedEx(). 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVTFlagBits, AVPageViewDragRectSnapped, (AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart,
	AVDevRect *startRect, AVDevRect *resultRect, AVlDragType dragType, AVDevRect *extrema, AVCursor *cursorArray, AVTSmallArraySize nCursors))

/**
	Given a starting point, ending point, and starting rectangle, 
	this returns a resulting rectangle which is snapped to the grid. 
	The routine is designed for use within a custom mouse-drag 
	loop, when the default drawing behavior provided by AVPageViewDragRectSnapped() 
	is insufficient. 
	@param pageView The page view. 
	@param xStart The x-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param yStart The y-coordinate of the point where the 
	user initially clicked, specified in device space coordinates. 
	
	@param xNow The x-coordinate. 
	@param yNow The y-coordinate. 
	@param startRect The initial position of the rectangle. 
	@param resultRect (Filled by the method) The position 
	of the rectangle at the end of the operation. 
	@param handleType One of the AVRectHandleType enumerated 
	values, typically obtained by calling AVRectHandleHitTest() 
	with the initial rectangle and starting coordinates. The 
	<code>handleType</code> determines which point or edge of the rectangle 
	should be snapped to the grid.
	@param modifiers Pass AVSysGetModifiers() to pass in one 
	of the Modifier Keys. If the key indicates that the Shift 
	key is pressed, one of the following is done:
	
	<ul>
	<li>If the <code>handleType</code> parameter is a resizing parameter
	(kAVRectHandleTopLeft through kAVRectHandleLeftMiddle),
	then maintain the aspect ratio of the original rectangle.</li>
	<li>If the <code>handleType</code> parameter is kAVRectHandleNone,
	this means that the rectangle is being moved around rather than
	resized, and the result rectangle will be snapped to the x-axis or
	y-axis of the starting rectangle, whichever is closer. </li>
	</ul>

	@param extrema Restricts the drag operation to a bounding 
	rectangle. If it is <code>NULL</code>, the bounding rectangle of the page view 
	is used.

	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
SPROC(void, AVPageViewSnapRect, (AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVDevCoord xNow, AVDevCoord yNow,
	AVDevRect *startRect, AVDevRect *resultRect, ASInt32 handleType, ASUns32 modifiers, const AVDevRect *extrema), AVPageViewGridSnapRect)

/**
	Inverts the specified rectangle's outline. 
	@param pageView IN/OUT The page view in which the inverted rectangle 
	outline is drawn. 
	@param rect IN/OUT A pointer to the rectangle whose outline is inverted, 
	specified in device space coordinates. Use AVPageViewRectToDevice() 
	to convert the coordinates of a rectangle that is specified 
	in user space coordinates. 
	@see AVPageViewDrawRect 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewInvertRect 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewInvertRectOutline, (AVPageView pageView, const AVDevRect *rect))

/**
	Transforms a point's coordinates from user space to device 
	space.
	@param pageView The page view for which the point's coordinates 
	are transformed. 
	@param p A pointer to the ASFixedPoint whose coordinates, 
	specified in user space, are transformed. 
	@param x (Filled by the method) The x-coordinate of the device 
	space point corresponding to <code>p</code>. 
	@param y (Filled by the method) The y-coordinate of the device 
	space point corresponding to <code>p</code>.
	@see AVPageViewDevicePointToPage 
	@see AVPageViewRectToDevice 
	@see AVPageViewDeviceRectToPage 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
SPROC(void, AVPageViewPointToDevice, (AVPageView pageView, const ASFixedPointP p,
	AVDevCoord *x, AVDevCoord *y), AVPagePointToDevice)

/**
	Determines if an annotation of the specified type resides 
	under the given point. If so, a handle to the annotation 
	is returned. 
	@param pageView The page view. 
	@param xHit The x-coordinate of the point. 
	@param yHit The y-coordinate of the point. 
	@param annotType The annotation type of interest. 
	@param belowOthers If <code>true</code>, the search continues below 
	the topmost annotation. Otherwise the search halts after 
	a single annotation is found, irrespective of its type. 
	@param annot (Filled by the method) The uppermost annotation 
	of the given type.
	@return <code>true</code> if an annotation was found, <code>false</code> otherwise. 

	@note Most tools which author new annotations should ignore 
	annotations of other types when performing hit tests. Use 
	this routine instead of AVPageViewIsAnnotAtPoint() to ignore 
	annotations of other types, and pass <code>true</code> for <code>belowOthers</code> 
	so the user can click through annotations of other types. 
	
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(ASBool, AVPageViewIsAnnotOfTypeAtPoint,
	  (AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, ASAtom annotType, ASBool belowOthers, PDAnnot *annot))

/**
	Sets an annotation's location, specified in device space 
	coordinates. 
	@param anAnnot The annotation whose location is set. 
	@param pageView The page view in which the annotation 
	is displayed. 
	@param x The annotation's new x-coordinate, specified 
	in device space coordinates. 
	@param y The annotation's new y-coordinate, specified 
	in device space coordinates.
	@notify PDAnnotWillChange 
	@notify PDAnnotDidChange 
	@see AVPageViewGetAnnotRect 
	@see PDPageCreateAnnot 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVPageViewSetAnnotLocation, (PDAnnot anAnnot, AVPageView pageView,
	AVDevCoord x, AVDevCoord y))

/**
	Registers a handler for an annotation subtype, replacing 
	any previous handler that had been registered for that subtype. 
	The annotation handler is not registered if its AVAnnotHandlerGetTypeProc() 
	returns <code>NULL</code>. 
	@param handler IN/OUT A pointer to a structure containing the annotation 
	handler's callbacks. This structure must not be freed after 
	this call, but must be retained. 
	@see AVAppEnumAnnotHandlers 
	@see AVAppGetAnnotHandlerByName 
	@see AVPageViewIsAnnotAtPoint 
	@see AVAppUnregisterAnnotHandler
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppRegisterAnnotHandler, (AVAnnotHandler handler))

/**
	Registers the specified tool with the Acrobat viewer. The 
	tool is not registered if its GetTypeProcType() callback returns 
	<code>NULL</code>. 
	@param tool IN/OUT A structure containing the tool's callbacks. 
	This structure must not be freed after calling AVAppRegisterTool(), 
	but must be retained. 
	@see AVAppEnumTools 
	@see AVAppSetActiveTool 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVAppRegisterTool, (AVTool tool))

/**
	Creates a new window and registers it with the Acrobat viewer. 
	
	<p>Because Windows and UNIX use the platform's native window 
	handling instead of the Acrobat viewer's AVWindowHandler 
	mechanism (that is, the AVWindowHandler mechanism's callbacks are 
	never called on those platforms), there is no advantage 
	to using AVWindowNew(). Client developers on those platforms 
	should use AVWindowNewFromPlatformThing() instead of this 
	method.</p>
	@param layer The layer in which the window resides. On the 
	Mac OS, it must be one of the AVWindowLayer constants. On Windows, 
	all AVWindow objects are of type <code>AVWLfloating</code>, and <code>layer</code> is ignored. 
	@param flags An OR of the values listed in AVWindow Flags. 
	@param handler A structure containing the window handler's 
	callback functions. Pass <code>NULL</code> in Windows and UNIX, because 
	the window handler's callbacks are unused on those platforms. 
	@param owner The gExtensionID extension registering the 
	window.
	@return The newly created window. 
	@exception genErrNoMemory 
	@see AVWindowNewFromPlatformThing 
	@note The flags numeric type changed in version 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVWindow, AVWindowNew, (AVWindowLayer layer, AVFlagBits32 flags, AVWindowHandler handler,
	ASExtension owner))

/**
	Creates a new window from a platform-specific structure 
	and registers it with the Acrobat viewer. 

	<p>If a user creates an <code>HWND</code> or a <code>WindowRef</code> and does not register 
	it with the viewer via AVWindowNewFromPlatformThing(), it 
	should not be allowed to persist across event loops (that 
	is, on Mac OS, it should be system-modal). </p>

	<p>Windows and UNIX use the platform's native window handling 
	instead of the Acrobat viewer's AVWindowHandler mechanism 
	(that is, the AVWindowHandler object's callbacks are never called 
	on those platforms). Client developers on those platforms 
	should use AVWindowNewFromPlatformThing() instead of AVWindowNew(), 
	since they have to create the window using platform-specific 
	code anyway.</p>

	@param layer One of the AVWindowLayer constants, specifying 
	the layer in which the window is located. For Mac OS, see 
	AVWindowNew(). <code>layer</code> is ignored on Windows, because the equivalent 
	information was specified when the platform thing was created. 
	@param flags For Mac OS, it is an OR of the AVWindow Flags. 
	It is the responsibility of the Mac client developer 
	to ensure that <code>flags</code> matches any attributes of the <i>platform-thing</i> 
	window; the Acrobat viewer cannot determine <code>flags</code> from the 
	window itself. <code>flags</code> is ignored on Windows and UNIX, because 
	the equivalent information was specified when the platform 
	thing was created. 
	@param handler A structure containing the window handler's 
	callback functions. Pass <code>NULL</code> on Windows and UNIX, because 
	the window handler's callbacks are unused on those platforms. 
	@param owner The gExtensionID extension registering the 
	window. 
	@param platformThing A platform-specific object (an <code>HWND</code> on Windows, a <code>WindowRef</code> 
	on Mac OS, and a <code>Widget</code> on UNIX) that will be used for this window.
	@return The newly created window. 
	@exception genErrNoMemory AVWindowNew AVWindowGetPlatformThing 

	@note The flags numeric type changed in version 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVWindow, AVWindowNewFromPlatformThing, (AVWindowLayer layer, AVFlagBits32 flags,
	AVWindowHandler handler, ASExtension owner, AVPlatformWindowRef platformThing))

/**
	Gets the window's frame, which specifies its size and location 
	on the screen. 

	@param win The window whose frame is obtained. 
	@param rect (Filled by the method) A pointer to a rectangle 
	specifying the window's frame rectangle, specified in global 
	screen coordinates. On Mac OS, the frame includes only the
	window's content region. On Windows, the frame includes only
	the window's client rectangle.
	@see AVWindowSetFrame 
	@see AVWindowGetInterior 

	@note On Mac OS, this method may change the current port, 
	thus altering the Mac OS graphics state. It sets the 
	port to that specified by <code>win</code>, but fails to restore the 
	previous port before exiting. 
	
	@note On Windows, the frame for an MDI document window
	is in coordinates relative to the MDI client window, which is
	the window that contains the MDI children.

	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowGetFrame, (AVWindow win, AVScreenRect *rect))

/**
	Sets the window's frame, which specifies its size and location 
	on the screen.

	@param win The window whose frame is set. 
	@param rect A pointer to a rectangle specifying the window's 
	frame rectangle, specified in global screen coordinates. 
	On Windows, the frame includes only the window's
	client rectangle. On Mac OS, the frame includes only the window's content 
	region. 
	@see AVWindowGetFrame 
	@see AVWindowGetInterior
	
	@note On Windows, the frame for an MDI document window
	is in coordinates relative to the MDI client window, which is
	the window that contains the MDI children.

	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowSetFrame, (AVWindow win, const AVScreenRect *rect))

/**
	Gets the interior rectangle of the window. 
	@param win The window whose interior is obtained. 
	@param rect (Filled by the method) A pointer to a rectangle 
	specifying the window's interior, specified as local window 
	coordinates.
	@see AVWindowGetFrame 
	@see AVWindowSetFrame 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowGetInterior, (AVWindow win, AVWindowRect *rect))

/**
	Invalidates the specified rectangular region, for eventual 
	redraw. This is the preferred method for refreshing a portion 
	of an AVWindow. Use AVWindowDrawNow() to force a window to 
	redraw its invalid regions. 
	@param win The window in which to invalidate a region. 
	
	@param rect A pointer to a rectangle specifying the region 
	to invalidate.
	@see AVWindowDrawNow 
	@see AVWindowGetInterior 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowInvalidateRect, (AVWindow win, const AVWindowRect *rect))

/**
	Gets the minimum and maximum size of the window. 

	<p><code>top</code> and <code>left</code> in <code>rect</code> are for minimum size; <code>bottom</code> and <code>right</code> 
	are for maximum size. </p>
	@param win The window whose size is obtained. 
	@param rect (Filled by the method) A pointer to a rectangle 
	specifying the window's size, specified in device space 
	coordinates. If this method is not supported on a particular 
	platform, the minimum size returned is <code>0, 0</code> and the maximum 
	size is <code>ASMAXInt16, ASMAXInt16</code>.
	@see AVWindowSetMinMaxSize 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00040005
*/
NPROC(void, AVWindowGetMinMaxSize, (AVWindow win, AVRect *rect))

/**
	Sets the minimum and maximum size of the window. 

	<p><code>top</code> and <code>left</code> in <code>rect</code> are for minimum size; <code>bottom</code> and <code>right</code> 
	are for maximum size. </p>
	@param win The window whose size is set. 
	@param rect A pointer to a rectangle specifying the window's 
	size, specified in device space coordinates.
	@see AVWindowGetMinMaxSize 
	@note The coordinate numeric type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00040005
*/
NPROC(void, AVWindowSetMinMaxSize, (AVWindow win, const AVRect *rect))

/* end of new 32 bit versions of old routines */


/**
	Gets a unique identifier (UUID) for the current user or 
	the current session. The UUID can be used with P2P, web 
	interactions, and so on. 
	@param type (Filled by the method) The UUID type value, 
	which specifies whether it identifies the current user or 
	the current session. 
	@param dst (Filled by the method) A pointer to the UUID 
	object.
	@return <code>true</code> if the UUID is successfully retrieved, <code>false</code> otherwise. 
	
	@see ASUUIDFromCString 
	@see ASUUIDGenFromHash 
	@see ASUUIDGenFromName 
	@see ASUUIDGenUnique 
	@see ASUUIDToCString 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppGetUUID, (AVAppUUIDType type, ASUUID *dst))


/**
	Gets an icon of the specified type from the specified file. 
	
	@param fname The file name. 
	@param itype The icon type, kAVSysSmallIcon, or kAVSysLargeIcon.
	@return The icon object, or <code>NULL</code> if no icon of the given type was 
	found. 
	@see AVSysGetIconFromMimeType 
	@see AVSysGetIconFromTypeAndCreator 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVIcon, AVSysGetIconFromFilename, (ASText fname, AVSysIconType itype))

/**
	Gets an icon of the specified type from the specified MIME 
	type. 
	@param mimeType The MIME type. 
	@param itype The icon type, kAVSysSmallIcon, or kAVSysLargeIcon.
	@return The icon object, or <code>NULL</code> if no icon of the given type was 
	found. 
	@see AVSysGetIconFromFilename 
	@see AVSysGetIconFromTypeAndCreator 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVIcon, AVSysGetIconFromMimeType, (const char *mimeType, AVSysIconType itype))

/**
	Gets an icon of the specified type from the specified type 
	and creator (for Mac OS). 
	@param type The type value (which specifies a type such 
	as PDF or GIF). 
	@param creator The creator value (which specifies a creator 
	such as Acrobat or Photoshop). 
	@param itype The icon type, kAVSysSmallIcon, or kAVSysLargeIcon.
	@return The icon object, or <code>NULL</code> if no icon of the given type was 
	found. 
	@see AVSysGetIconFromFilename 
	@see AVSysGetIconFromMimeType 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVIcon, AVSysGetIconFromTypeAndCreator, (ASUns32 type, ASUns32 creator, AVSysIconType itype))


/**
	Converts the specified file to a PDF document using the 
	specified handler. 
	@param inHandler Specifies which <code>ConvertFromPDF</code> handler 
	to use. 
	@param inSettings An ASCab containing the settings to be 
	used in the conversion operation. Pass <code>NULL</code> to use the default 
	settings. 
	@param flags Conversion flags. 
	@param stream The stream to convert. 
	@param metaData The metadata. 
	@param outPDDoc (Filled by the method) It is the caller's 
	responsibility to close the document. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>.
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertStreamToPDF 
	@see AVConversionConvertToPDFWithHandler 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
XNPROC(AVConversionStatus, AVConversionConvertStreamToPDFWithHandler,(
	AVConversionToPDFHandler	inHandler,
	ASCab						inSettings,
	AVConversionFlags			flags,		
	ASStm						stream,
	ASCab						metaData,
	PDDoc						*outPDDoc,
	AVStatusMonitorProcs		statusMonitor))

/**
	Converts a PDF document to a stream using the specified handler. 
	
	@param inHandler Specifies which <code>ConvertFromPDF</code> handler 
	to use. 
	@param inSettings An ASCab containing the settings to be 
	used in the conversion operation. Pass <code>NULL</code> to use the default 
	settings. 
	@param flags Conversion flags. 
	@param inPDDoc The PDF document to be converted. 
	@param stream The desired location for the output stream. 
	
	@param metaData The file metadata. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>.
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertFromPDFWithHandler 
	@see AVConversionConvertStreamToPDFWithHandler 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
XNPROC(AVConversionStatus, AVConversionConvertStreamFromPDFWithHandler,(
	AVConversionFromPDFHandler	inHandler,
	ASCab						inSettings,
	AVConversionFlags			flags,
	PDDoc						inPDDoc,
	ASStm						stream,
	ASCab						metaData,
	AVStatusMonitorProcs		statusMonitor))

/**
	Converts a structure node to a stream using the handler 
	specified. 
	@param inHandler Specifies which <code>ConvertFromPDF</code> handler 
	to use. 
	@param inSettings An ASCab containing the settings to be 
	used in the conversion operation. Pass <code>NULL</code> to use the default 
	settings. 
	@param flags Conversion flags. 
	@param inStructNode The structure node to be converted. 
	
	@param stream The desired location for the output stream. 
	
	@param metaData The file metadata. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>.
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertStreamFromPDFWithHandler 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
XNPROC(AVConversionStatus, AVConversionConvertStreamFromStructNodeWithHandler,(
	AVConversionFromPDFHandler	inHandler,
	ASCab						inSettings,
	AVConversionFlags			flags,
	AVStructNode				inStructNode,
	ASStm						stream,
	ASCab						metaData,
	AVStatusMonitorProcs		statusMonitor))

/**
	Converts the specified stream to a PDF document using whatever 
	converter is found. Use this function if you do not know 
	which handler to use. 

	<p>Multiple conversion handlers can register their services 
	for the same file description, so the first one that matches 
	the file type passed in that has the correct <code>canDoSync</code> settings 
	is used. </p>

	<p>The converters are enumerated in priority order, starting 
	with the highest priority. </p>
	@param flags Conversion flags. 
	@param mimeType The MIME type. 
	@param stream The stream to convert. 
	@param metaData The metadata. 
	@param outPDDoc (Filled by the method) It is the caller's 
	responsibility to close the document. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>.
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertToPDF 
	@see AVConversionConvertStreamToPDFWithHandler 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
XNPROC(AVConversionStatus, AVConversionConvertStreamToPDF, (
	AVConversionFlags			flags,
	const char					*mimeType,
	ASStm						stream,
	ASCab						metaData,
	PDDoc						*outPDDoc,
	AVStatusMonitorProcs		statusMonitor))


/**
	Pops up a submenu. 
	@param menu The menu to be displayed. 
	@param x The x-coordinate of the upper left corner of 
	the menu. 
	@param y The y-coordinate of the upper left corner of 
	the menu. 
	@param rightButton <code>true</code> if the right mouse button (where 
	applicable) was used to invoke the popup, <code>false</code> otherwise. 
	
	@param choice The index of the AVMenuItem that should 
	appear under the mouse at popup time.
	@return The menu item selected from menu. 
	@see AVPageViewDoPopupMenu 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVMenuItem, AVMenuDoPopUp, (AVMenu menu, ASInt16 x, ASInt16 y, ASBool rightButton, ASInt32 choice))


/**
	Gets the number of page views for the specified document. 
	
	@param avDoc The document whose page view count is obtained.
	@return The number of AVPageView objects associated with the document, 
	as an ASCount. 
	@see AVDocGetNthPageView 
	@see AVDocGetPageView 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASCount, AVDocGetNumPageViews, (AVDoc avDoc))

/**
	Gets the specified AVPageView for the specified document. 
	
	@param avDoc The document whose AVPageView is obtained. 
	@param n The index of the page view to obtain. The index 
	range is <code>0</code> to <code>(AVDocGetNumPageViews-1)</code>.
	@return The document's nth AVPageView. 
	@see AVDocGetNumPageViews 
	@see AVDocGetPageView 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVPageView, AVDocGetNthPageView, (AVDoc avDoc, ASCount n))


/**
	Opens and displays a document from a file, using the specified 
	parameters to control the window's size, location, and visibility, 
	and passing a URL open action string to control how the 
	file is opened. For more information, see the document <i>Parameters for Opening PDF Files</i>. 

	<p>If you want to display a page from a PDF file as a bitmap, 
	use PDPageDrawContentsToWindow(). </p>
	@param pathName The file to open. 
	@param fileSys The file system on which pathName resides. 
	You can obtain the default file system with ASGetDefaultFileSys. 
	
	@param tempTitle If <code>tempTitle != NULL</code>, <code>pathName</code> is a temporary 
	file and <code>tempTitle</code> is used as the window's title. 
	@param p Parameters used when opening the file. It can 
	be <code>NULL</code>. 
	@param s A string containing the URL open action. For 
	example, <code>Help=contents&nameddest=distiller_mydest</code> would 
	open the PDF in the help window, with the contents panel 
	showing on the left and the page referenced by the named 
	destination <code>distiller_mydest</code> showing on the right.
	@ingroup ReplaceableMethods
	@return The document that was opened. 
	@notify AVDocWillOpenFromFile 
	@notify AVDocDidOpen 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action)
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromFileWithParams 
	@see AVDocOpenFromFile 
	@see AVDocOpenFromPDDoc 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without letting at least one event loop complete. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVDoc, AVDocOpenFromFileWithParamString, (ASPathName pathName, ASFileSys fileSys, const ASText tempTitle, AVDocOpenParams p, const char * s))

/**
	Opens and displays a document from a PDDoc, using the specified 
	parameters to control the window's size, location, and visibility, 
	and passing a URL open action string to control how the 
	file is opened. For more information, see the document <i>Parameters for Opening PDF Files</i>. 

	<p>If you want to display a page from a PDF file as a bitmap, 
	use PDPageDrawContentsToWindow(). </p>
	@param pdDoc The document to open and display. 
	@param tempTitle If <code>tempTitle != NULL</code>, <code>pathname</code> is a temporary 
	file and <code>tempTitle</code> is used as the window's title. 
	@param p Parameters used when opening the file. It can 
	be <code>NULL</code>. 
	@param s A string containing the URL open action. For 
	example, <code>Help=contents&nameddest=distiller_mydest</code> would 
	open the PDF in the help window, with the contents panel 
	showing on the left and the page referenced by the named 
	destination <code>distiller_mydest</code> showing on the right.
	@return The document that was opened. 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action)
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromFileWithParamString 
	@see AVDocOpenFromPDDoc 
	@see AVDocOpenFromPDDocWithParams 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without letting at least one event loop complete. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVDoc, AVDocOpenFromPDDocWithParamString, (PDDoc pdDoc, const ASText tempTitle, AVDocOpenParams p, const char * s))

/**
	Opens and displays a document from an ASFile, using the 
	specified parameters to control the window's size, location, 
	and visibility, and passing a URL open action string to 
	control how the file is opened. For more information, see 
	<i>Parameters for Opening PDF Files</i>. 

	<p>If you want to display a page from a PDF file as a bitmap, 
	use PDPageDrawContentsToWindow(). </p>
	@param file The ASFile to open. 
	@param tempTitle An optional window title for the document. 
	
	@param p Open parameters for the document. 
	@param s A string containing the URL open action. For 
	example, <code>Help=contents&nameddest=distiller_mydest</code> would 
	open the PDF in the help window, with the contents panel 
	showing on the left and the page referenced by the named 
	destination <code>distiller_mydest</code> showing on the right.
	@return An AVDoc object for file. 
	@notify AVDocWillOpenFromFile 
	@notify AVDocDidOpen 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action)
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromFileWithParamString 
	@see AVDocOpenFromPDDocWithParamString 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVDoc, AVDocOpenFromASFileWithParamString, (ASFile file, const ASText tempTitle, AVDocOpenParams p, const char * s))


/**
	Opens the specified PDF help file and goes to the location 
	of the specified content. If the help file is not found, it 
	opens a dialog box asking if the user wants to search for 
	the help file. 
	@param fileName The name of the PDF help file to open. 
	If it is a simple file name, it is assumed to reside in 
	the help contents folder. Pass <code>NULL</code> for the default Acrobat 
	help file. 
	@param contentTag A named destination defined in the PDF 
	help file.
	@return <code>true</code> if the PDF was opened successfully, <code>false</code> otherwise. 
	
	@see AVAppHelpSearch 
	@see AVAppHelpShowIndex 
	@see AVAppOpenHelpFileWithParams 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppHelpShowContents, (const char * fileName, const char * contentTag) )

/**
	Opens the specified help file (if it is not already open) 
	and searches for a specified string. If the help file is 
	not found, it opens a dialog box asking if the user wants to 
	search for the help file. If the help file is found, the 
	method opens it with the navigation panel on the left showing 
	the search panel, which displays the result of the search. 
	
	@param fileName The name of the help file in which to search. 
	If it is a simple file name, it is assumed to reside in 
	the help contents folder. Pass <code>NULL</code> for the default Acrobat 
	help file. 
	@param searchText The UTF8-encoded text for which to search. 
	
	@return <code>true</code> if the help file was successfully opened, <code>false</code> otherwise. 
	
	@see AVAppHelpShowContents 
	@see AVAppHelpShowIndex 
	@see AVAppOpenHelpFileWithParams 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppHelpSearch, (const char * fileName, const char * searchText))

/**
	Opens the specified PDF help file and displays the index. 
	If the help file is not found, it opens a dialog box asking 
	if the user wants to search for the help file. 
	@param fileName The name of the PDF help file to open. 
	If it is a simple file name, it is assumed to reside in 
	the help contents folder. Pass <code>NULL</code> for the default Acrobat 
	help file.
	@return <code>true</code> if the PDF was opened successfully, <code>false</code> otherwise. 
	
	@see AVAppHelpSearch 
	@see AVAppHelpShowContents 
	@see AVAppOpenHelpFileWithParams 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppHelpShowIndex, (const char * fileName))

/**
	Opens a specified help PDF file, using the specified parameters 
	to control the window's size, location, and visibility. 
	If the help file is not found, it optionally opens a dialog 
	box asking if the user wants to search for the help file. 
	@param fileName A help PDF file name. If it is a simple 
	file name, it is assumed to reside in the help contents 
	folder. 
	@param doSearch If <code>true</code> and the help file is not found, 
	a dialog box is displayed, asking if the user wants to search 
	for the help file. If <code>false</code>, <code>false</code> is returned if the help file 
	is not found. 
	@param p Open parameters for the document.
	@return <code>true</code> if the help file is found, <code>false</code> otherwise. 
	@see AVAppHelpSearch 
	@see AVAppHelpShowContents 
	@see AVAppHelpShowIndex 
	
	@note Supersedes AVAppOpenHelpFile(), which is deprecated in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppOpenHelpFileWithParams, (const char * fileName, ASBool doSearch, AVDocOpenParams p))

/**
	Adds the specified AVIcon to the AVToolbutton object's animation list. 
	@param button An AVToolbutton to which <code>newIcon</code> will be added.
	@param newIcon An icon that is added to the animation list for <code>button</code>.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonStopAnimation
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonRemoveAnimationIcons
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonAddAnimationIcon, (AVToolButton button, AVIcon newIcon))

/**
	Returns the count of animation icons associated with this tool button.
	@param button An AVToolbutton whose item count is returned.
	@return An ASInt32 representing the number of icons associated with this tool button.
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonStopAnimation 
	@see AVLegacyToolButtonRemoveAnimationIcons
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASInt32, AVLegacyToolButtonGetAnimationIconCount, (AVToolButton button))

/**
	Starts flipping icons for specified button.
	@param button An AVToolbutton whose animation list will be started.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStopAnimation 
	@see AVLegacyToolButtonRemoveAnimationIcons
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonStartAnimation, (AVToolButton button))

/**
	Stops flipping icons for specified button.
	@param button An AVToolbutton whose animation list will be stopped.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonRemoveAnimationIcons
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonStopAnimation, (AVToolButton button))

/**
	Indicates whether the tool button animation list is flipping.
	@param button The AVToolbutton whose animation list may be flipping.
	@return An ASBool indicating whether the button is flipping icons.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonRemoveAnimationIcons
	@see AVLegacyToolButtonStopAnimation
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVLegacyToolButtonIsAnimationRunning, (AVToolButton button))

/**
	Sets the period in seconds of how often to flip the tool button animation icons.
	@param button An AVToolbutton whose animation period list is being modified.
	@param newPeriod An ASInt32 period in seconds for this tool button.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonRemoveAnimationIcons
	@see AVLegacyToolButtonStopAnimation
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonSetAnimationPeriod, (AVToolButton button, ASInt32 newPeriod))

/**
	Gets the period in seconds of how often to flip the tool button animation icons.
	@param button An AVToolbutton whose animation period list is being examined.
	@return An ASInt32 representing the period in seconds for this tool button.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonRemoveAnimationIcons
	@see AVLegacyToolButtonStopAnimation
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASInt32, AVLegacyToolButtonGetAnimationPeriod, (AVToolButton button))

/**
	Removes all icons from the tool button animation list.
	@param button An AVToolbutton that will have its animation icon list cleared.
	@see AVLegacyToolButtonGetAnimationIconCount 
	@see AVLegacyToolButtonStartAnimation 
	@see AVLegacyToolButtonStopAnimation
	@see AVLegacyToolButtonIsAnimationRunning
	@see AVLegacyToolButtonSetAnimationPeriod
	@see AVLegacyToolButtonGetAnimationPeriod
	@see AVLegacyToolButtonAddAnimationIcon
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonRemoveAnimationIcons, (AVToolButton button))

#if HAS_MENUS

/**
	Creates and acquires a new menu with the given title and 
	language-independent name. The menu can be added to the 
	menu bar using AVMenubarAddMenu(). When you are done using 
	the menu, release it using AVMenuRelease(). 
	@param title A constant text object containing the string 
	that appears in the user interface. On Windows, an ampersand 
	(<code>&</code>) character in the string results in underlining the character 
	after it on the menu. 
	@param name A language-independent name of the menu to create: 
	it is the value returned by AVMenuGetName(). It must not contain 
	any spaces. Developers should prefix the names of menus 
	they add with the name of their client and a colon, to avoid 
	collisions in the menu name space. For example, a client 
	named <code>myPlug</code> might add menus named <code>myPlug:DrawTools</code> and 
	<code>myPlug:Checkout</code>. 
	@param owner The gExtensionID extension registering the 
	menu.
	@return The newly created menu. 
	@exception genErrNoMemory 
	@see AVMenuRelease 
	@see AVMenubarAddMenu 
	@see AVMenuGetName 
	@see AVMenuGetTitleAsASText 
	@see AVMenuNew 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVMenu, AVMenuNewWithASText, (ASConstText title, const char *name, ASExtension owner))

/**
	Gets the menu's title as it appears in the user interface, 
	as an ASText object. 
	@param menu The menu whose title is obtained. 
	@param title (Filled by the method) The text object containing 
	the title.
	@see AVMenuGetName 
	@see AVMenuGetTitle 
	@see AVMenuNewWithASText 
	@see AVMenuItemGetTitleAsASText 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVMenuGetTitleAsASText, (AVMenu menu, ASText title))

/**
	Creates and acquires a new AVMenuItem. The menu item can 
	be added to a menu using AVMenuAddMenuItem(). 

	<p>Release the AVMenuItem using AVMenuItemRelease() after it 
	has been added to a menu. </p>
	@param title A constant text object containing the string 
	shown in the user interface for this menu item. Use a hyphen 
	to create a separator menu item. This value is also returned 
	by AVMenuItemGetTitleAsASText(). On Windows, an ampersand 
	(<code>&</code>) character in the string results in underlining the character 
	after it on the menu item. 
	@param name The language-independent name of the menu 
	item to create. This is the value returned by AVMenuItemGetName(). 
	<code>name</code> must not contain any spaces. Client developers should 
	prefix the names of menu items they add with the name of 
	their client and a colon, to avoid collisions in the menu 
	item name space. For example, a client named <code>myPlug</code> might 
	add menu items named m<code>yPlug:Scan</code> and <code>myPlug:Find</code>. 
	@param submenu The submenu (if any) for which this menu item 
	is the parent. Pass <code>NULL</code> if this menu item does not have 
	a submenu. 
	@param longMenusOnly (Ignored in Acrobat 3.0 or later) 
	If <code>true</code>, the menu item is visible only when the user selects 
	Full Menus. If <code>false</code>, the menu item is visible for both 
	Full Menus and Short Menus modes. 
	@param shortcut The key to use as a shortcut for the menu 
	item (an ASCII character). Use <code>NO_SHORTCUT</code> (see AVExpT.h) 
	if the menu item has no shortcut. The Acrobat viewer does 
	not check for conflicts between shortcuts. The consequences 
	of multiple menu items having the same shortcut is undefined. 
	On Windows, the shortcut is not displayed for any menu item 
	that also has an icon, although the shortcut will work.
	@param flags Modifier keys, if any, used as part of the 
	shortcut. It must be an OR of the Modifier Keys values, except 
	that <code>AV_COMMAND</code> cannot be specified. 
	@param icon The icon to show in the menu item, or <code>NULL</code> 
	if no icon is shown. On Windows, <code>icon</code> is a 24x24 sample monochrome 
	<code>HBITMAP</code>. 
	@param owner The gExtensionID extension registering the 
	menu item.
	@return The newly created menu item. 
	@see AVMenuAddMenuItem 
	@see AVMenuItemGetTitleAsASText 
	@see AVMenuItemRelease 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVMenuItem, AVMenuItemNewWithASText, (ASConstText title, const char *name, AVMenu submenu,
	ASBool longMenusOnly, char shortcut, AVFlagBits16 flags, AVIcon icon, ASExtension owner))

/**
	Gets the menu item's title as it appears in the user interface, 
	as an ASText object. 
	@param menuItem The menu item whose title is obtained. 
	
	@param title (Filled by the method) The text object containing 
	the title.
	@see AVMenuGetTitleAsASText 
	@see AVMenuItemSetTitleWithASText 
	@see AVMenuItemGetName 
	@see AVMenuItemGetTitle 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVMenuItemGetTitleAsASText, (AVMenuItem menuItem, ASText title))

/**
	Sets a menu item's title, which is the string that appears 
	in the user interface, from a constant text object. Use 
	this method to manage menu items whose titles change (such 
	as <code>'show/hide fooWindow'</code>), instead of inserting and removing 
	menu items on the fly. 
	@param menuItem The menu item whose title is set. 
	@param title The new menu title, as a constant text object.
	@see AVMenuItemGetTitleAsASText 
	@see AVMenuItemGetName 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVMenuItemSetTitleWithASText, (AVMenuItem menuItem, ASConstText title))
#else
NOPROC(AVMenuNewWithASText)
NOPROC(AVMenuGetTitleAsASText)
NOPROC(AVMenuItemNewWithASText)
NOPROC(AVMenuItemGetTitleAsASText)
NOPROC(AVMenuItemSetTitleWithASText)
#endif


/**
	Gets the title to display in the specified window's title 
	bar.
	@param win The window whose title is obtained. 
	@param title (Filled by the method) The window title as 
	an ASText object.
	@see AVWindowSetTitle 
	@note The parameters changed in number and type and the return type changed
	in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowGetTitle, (AVWindow win, ASText title))

/**
	Sets the title to display in the specified window's title 
	bar. This method cannot be used to set the title of the 
	window in which the Acrobat viewer normally opens a PDF 
	file; it can only be used to set the title of an AVWindow 
	created by a client. To set the title of a window in which 
	the Acrobat viewer opens a PDF file, you must replace AVDocOpenFromASFileWithParams() 
	and pass the window title in <code>tempTitle</code>.
	@param win The window whose title is set. 
	@param newTitle The title to set for <code>win</code>.
	@exception genErrNoMemory 
	@see AVWindowGetTitle 
	@note The newTitle parameter type changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(void, AVWindowSetTitle, (AVWindow win, const ASText newTitle))

/**
	Opens and displays a document from a file. This is equivalent 
	to <code>AVDocOpenFromASFileWithParams(pathName, fileSys, tempTitle, NULL)</code>. 
	If you want to display a page from a PDF file as 
	a bitmap, use PDPageDrawContentsToWindow(). 
	@param pathName The file to open. 
	@param fileSys The file system on which <code>pathName</code> resides. 
	You can obtain the default file system with ASGetDefaultFileSys(). 
	
	@param tempTitle If <code>tempTitle != NULL</code>, <code>pathName</code> is a temporary 
	file, and <code>tempTitle</code> is used as the window's title.
	@return The document that was opened. It returns <code>NULL</code> if the viewer 
	failed to open the document. 
	@notify AVDocWillOpenFromFile 
	@notify AVDocDidDeleteSelection 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action)
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDoc 
	@see AVDocOpenFromPDDocWithParams 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without 
	letting at least one event loop complete. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVDoc, AVDocOpenFromFile, (ASPathName pathName, ASFileSys fileSys, const ASText tempTitle))

/**
	Opens and returns an AVDoc view of pdDoc.
	This method is equivalent to <code>AVDocOpenFromPDDocWithParams(pdDoc, tempTitle, NULL)</code>. 
	If you want to display a page from a PDF 
	file as a bitmap, use PDPageDrawContentsToWindow(). 
	
	@param doc The document to open. 
	@param tempTitle If <code>tempTitle != NULL</code>, <code>pathname</code> is a temporary 
	file and <code>tempTitle</code> is used as the window's title.
	@return <code>NULL</code> if failure occurs. 
	@exception genErrGeneral is raised if <code>doc</code> is <code>NULL</code> or has <code>0</code> pages. 
	@exception pdErrBadAction is raised if the document's open action is recursive. 
	@exception avErrCantOpenMoreThanTenDocs is raised if the maximum number of documents is already open. 
	@exception genErrNoMemory is raised if there is insufficient memory to open the document. 
	@notify AVAppFrontDocDidChange 
	@notify AVDocDidActivate 
	@notify AVDocDidDeactivate 
	@notify AVDocWillPerformAction (broadcast if the document has a valid open action)
	@notify AVDocDidPerformAction (broadcast if the document has a valid open action) 
	@see AVDocOpenFromPDDocWithParams 
	@see AVDocOpenFromPDDocWithParamString 
	@see AVDocOpenFromFile 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocClose 

	@note Do not open and then immediately close an AVDoc without 
	letting at least one event loop complete. 

	@note AVDocClose() should be used in place of PDDocClose() after 
	AVDocOpenFromPDDoc() is called. AVDocClose() will decrement 
	the PDDoc appropriately and free document-related resources. 
	@since PI_ACROVIEW_VERSION >= 0x00020000
*/
NPROC(AVDoc, AVDocOpenFromPDDoc, (PDDoc doc, const ASText tempTitle))


/**
	Parses a path name to obtain the base file name and extension 
	for a particular file. The function enumerates all registered 
	<code>convertToPDF</code> and <code>convertFromPDF</code> handlers to find a matching 
	extension for the file passed in. This function allocates 
	memory for the file name and extension. It is the caller's 
	responsibility to free the memory allocated by the method. 
	@param fileSys The file system from which the path was obtained. 
	Pass <code>NULL</code> to use the default file system. 
	@param pathName The path containing the file name. 
	@param fileName The file name as a constant text object. 
	
	@param numAddExt The number of additional extensions to 
	search through. 
	@param addExt An array of <code>NULL</code>-terminated strings with 
	extensions to search through. 
	@param baseName (Allocated and filled by the method) A 
	buffer containing the file name. It can be <code>NULL</code> if you do not 
	want the base file name. 
	@param baseExt (Allocated and filled by the method) A 
	buffer containing the file extension. It can be <code>NULL</code> if you 
	do not want the base file extension.
	@return <code>true</code> if the file info was successfully extracted from the path, 
	<code>false</code> otherwise. 
	
	@note This method extends AVUtilGetBaseNameAndExtensionByPathName() 
	in Acrobat 6.0 and later to use constant types and a text-object file 
	name. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVUtilGetBaseNameAndExtensionEx, (const ASFileSys fileSys, const ASPathName pathName, const ASText fileName, ASInt32 numAddExt, const char * const *addExt, ASText baseName, char **baseExt))


/**
	Obtains the path name for a file in a special folder. It 
	is the caller's responsibility to release the ASPathName. 
	This method may be used even if the associated file does 
	not exist. 
	@param cat The folder category. See AVSpecialCategory. 
	Only certain combinations of category/folder are allowed; see 
	AVSpecialError. 
	@param fld The folder in which the file is located. See 
	AVSpecialFolder. Only certain combinations of category/folder 
	are allowed; see AVSpecialError. 
	@param fileName A text object containing the name of the file 
	(including the extension) that you want to access. 
	@param asfs OUT The file system through which the path name was obtained. 
	@param asp OUT The ASPathName associated with the file. The caller must release it.
	@return One of the AVSpecialError status codes. The <code>asfs</code> and 
	<code>asp</code> variables will only be valid if the method returns 
	kAVSEOkay or kAVSEDoesntExist. kAVSEDoesntExist is returned 
	if the ASPathName was created but the associated file does not 
	exist. 
	@see AVAcquireSpecialFilePathName 
	@see AVAcquireSpecialFolderPathName 

	@note This method supersedes AVAcquireSpecialFilePathName() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASErrorCode, AVAcquireSpecialFilePathNameWithASText, (AVSpecialCategory cat,	/* Category (see AVExpT.h) */
										AVSpecialFolder fld,						/* Folder (see AVExpT.h) */
										const ASText fileName,						/* File you want to access (e.g. AcroHelp.pdf). */
										ASFileSys *asfs,							/* Filled by this routine. */
										ASPathName *asp))							/* Filled by this routine. Caller must release this ASPathName */

/**
	Displays a platform-dependent file open dialog box. It is the 
	caller's responsibility to release the returned ASPathName objects 
	and the associated memory.
	@ingroup ReplaceableMethods
	@param dialogParams Standard parameters for Open/Save/ChooseFolder 
	dialog boxes. 
	@param outFileSys (Filled by the method) The file system 
	through which the contents of the path names were opened. It may 
	be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed 
	in <code>dialogParams</code>. 
	@param outASPathNames (Allocated and filled by the method) 
	The ASPathName object(s) associated with the file(s) selected by 
	the user. The caller must free the list of filled-in ASPathName objects 
	using the supplied ASFileSys. 
	@param outNumASPathNames (Filled by the method, may be <code>NULL</code>) 
	The number of ASPathName objects in the <code>outASPathNames</code> array. It may be <code>NULL</code> 
	if kAVOpenSaveAllowMultiple is not set. 
	@param ioChosenFilterIndex (Filled by the method, may 
	be <code>NULL</code>) The index of the filter chosen by the user to select 
	the file(s). It may be <code>NULL</code> if the caller does not care which filter 
	was chosen, or <code>-1</code> for <code>'All Files'</code>.
	@return <code>true</code> if the user clicked Action to confirm the selection, 
	<code>false</code> if the user clicked Cancel or some error occurred. 
	@see AVAppChooseFolderDialog 
	@see AVAppSaveDialog 
	@note The numeric parameter types changed in 0x00060000.
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
PROC(ASBool, AVAppOpenDialog, (AVOpenSaveDialogParams dialogParams,			/* Standard dialog params for Open/Save/ChooseFolder dialogs */
										ASFileSys		*outFileSys,			/* May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams */
										ASPathName		**outASPathNames,		/* Caller must ASfree this array and release its ASPathName elements */
										AVArraySize		*outNumASPathNames,		/* Number of ASPathNames in outASPathNames array. It may be <code>NULL</code> if kAVOpenSaveAllowMultiple is not set */
										AVFilterIndex	*ioChosenFilterIndex))	/* May be <code>NULL</code> if caller doesn't care which filter was chosen, -1 if 'All Files'.
																				** Specify the initially selected filter with the value passed in.  If <code>NULL</code>, 1st entry is selected. */
																				/* Returns <code>true</code> if user clicked 'action' button, <code>false</code> if user clicked 'cancel' */

/**
	Displays a platform-dependent file save dialog box. It is the 
	caller's responsibility to release the returned ASPathName. 
	
	@ingroup ReplaceableMethods
	@param dialogParams Standard dialog box parameters for Open/Save/ChooseFolder 
	dialog boxes. 
	@param outFileSys (Filled by the method, may be <code>NULL</code>) 
	The file system through which the path name was obtained. It may 
	be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed 
	in <code>dialogParams</code>. 
	@param outASPathName (Filled by the method) The ASPathName 
	associated with the file selected by the user. The caller 
	must free the filled in ASPathName using the supplied ASFileSys. 
	
	@param ioChosenFilterIndex (Filled by the method, may 
	be <code>NULL</code>) The index of the filter chosen by the user to select 
	the file. It may be <code>NULL</code> if caller does not care which filter 
	was chosen, <code>-1</code> for <code>'All Files'</code>.
	@return <code>true</code> if the user confirmed the selection, <code>false</code> if the user 
	clicked Cancel or some error occurred. 
	@see AVAppOpenDialog 
	@see AVAppChooseFolderDialog 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
PROC(ASBool, AVAppSaveDialog, (AVOpenSaveDialogParams dialogParams,			/* Standard dialog params for Open/Save/ChooseFolder dialogs */
										ASFileSys		*outFileSys,			/* May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams */
										ASPathName		*outASPathName,			/* Caller must release this ASPathName */
										AVFilterIndex	*ioChosenFilterIndex))	/* May be <code>NULL</code> if caller doesn't care which filter was chosen, -1 if 'All Files'.
																				** Specify the initially selected filter with the value passed in.  If <code>NULL</code>, 1st entry is selected. */
																				/* Returns <code>true</code> if user clicked 'action' button, <code>false</code> if user clicked 'cancel' */

/**
	Displays a platform dependent folder selection dialog box. <code>outFileSys</code> 
	and <code>outASPathName</code> will be <code>NULL</code> if the user cancelled the operation. 
	
	<p>It is the caller's responsibility to release the returned 
	ASPathName. </p>
	@ingroup ReplaceableMethods
	@param dialogParams Standard dialog parameters for the 
	Open/Save/ChooseFolder dialog boxes. 
	@param outFileSys (Filled by the method, may be <code>NULL</code>) 
	The file system through which the path name was obtained. It may 
	be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed 
	in dialogParams. 
	@param outASPathName (Filled by the method) The ASPathName 
	associated with the folder chosen by the user.
	@return <code>true</code> if the user confirmed the selection, <code>false</code> 
	if the user clicked Cancel or some error occurred. 
	@see AVAppOpenDialog 
	@see AVAppSaveDialog 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
PROC(ASBool, AVAppChooseFolderDialog, (AVOpenSaveDialogParams dialogParams,	/* Standard dialog params for Open/Save/ChooseFolder dialogs. It may be <code>NULL</code> */
										ASFileSys		*outFileSys,			/* May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams */
										ASPathName		*outASPathName))		/* Caller must release this ASPathName */
																				/* Returns <code>true</code> if user clicked 'action' button, <code>false</code> if user clicked 'cancel' */


/**
	Sets the set of inks to be displayed in a separations preview 
	for a page view. The ink preview must be turned on for this 
	method to have an effect. 
	@param pageView The page view whose number of visible 
	inks is obtained. 
	@param nInks The size of the inks array. The maximum number 
	of inks is <code>16</code>. 
	@param inks An array of the new visible inks for the page. 
	It copies the inks into local storage, so the caller does not 
	need to keep the array.
	@see AVPageViewGetNumVisibleInks 
	@see AVPageViewGetVisibleInks 
	@see AVPageViewSetInkPreview 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
UNPROC(void, AVPageViewSetVisibleInks, (AVPageView pageView, ASInt32 nInks, PDPageInkRec *inks))

/**
	Sets or clears the ink preview value for a page view, which 
	allows you to disable the rendering of individual inks. 
	This does not change the set of visible inks. Enabling ink 
	preview also enables overprint preview (OPP). 
	@param pageView The page view whose number of visible 
	inks is obtained. 
	@param inkPreview Indicates whether the page view has an ink preview.
	@see AVPageViewGetNumVisibleInks 
	@see AVPageViewGetPixelInformationAtPoint 
	@see AVPageViewGetVisibleInks 
	@see AVPageViewSetVisibleInks 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
UNPROC(void, AVPageViewSetInkPreview, (AVPageView pageView, ASBool inkPreview))

/**
	Gets the number of inks (color separations) that are displayed 
	for a page view. An ink, in this context, means the content 
	that will appear on a single plate when the page is separated. 
	For example, a DeviceCMYK color is four inks, and a separation 
	color space is usually one ink. 
	@param pageView The page view whose number of visible 
	inks is obtained.
	@return The number of visible inks. 
	@see AVPageViewGetVisibleInks 
	@see AVPageViewSetInkPreview 
	@see AVPageViewSetVisibleInks 
	@see PDPageEnumInks 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
UNPROC(ASInt32, AVPageViewGetNumVisibleInks, (AVPageView pageView))

/**
	Gets the set of inks to be displayed in a separations preview 
	for a page view. 
	@param pageView The page view whose number of visible 
	inks is obtained. 
	@param inks (Filled by the method) A pointer to an array 
	of structures containing the visible ink names for the page. 
	The vector must be large enough to hold the visible inks.
	@see AVPageViewGetNumVisibleInks 
	@see AVPageViewSetInkPreview 
	@see AVPageViewSetVisibleInks 
	@see PDPageEnumInks 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
UNPROC(void, AVPageViewGetVisibleInks, (AVPageView pageView, PDPageInkRec *inks))

/**
	Gets the color separation ink information for pixels at 
	the cursor position in the specified page view. Ink previews 
	must be turned on before calling this method. 
	@param pageView The page view whose pixel information 
	is obtained. 
	@param x The horizontal cursor coordinate of the point, 
	as obtained by the AVPageViewCursorProc() callback. 
	@param y The vertical cursor coordinate of the point, 
	as obtained by the AVPageViewCursorProc() callback. 
	@param inkVector (Filled by the method) An array of ink 
	values for the specified point. 
	@param inkVectorLength (Filled by the method) The size 
	of the <code>inkVector</code> array.
	@return <code>true</code> if the information is successfully retrieved, <code>false</code> 
	otherwise. 
	@see AVPageViewGetVisibleInks 
	@see AVPageViewSetInkPreview 
	@see PDPageEnumInks 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
UNPROC(ASBool, AVPageViewGetPixelInformationAtPoint, (AVPageView pageView, AVDevCoord x, AVDevCoord y, AVInkValue *inkVector, ASUns32 *inkVectorLength))




/**
	Creates a new AVUndo record for a document's undo list. 
	
	@param doc The document whose undo list contains this 
	undo record. 
	@param handler The handler structure containing callbacks 
	that perform the undo and redo operations. 
	@param undoData Any private data needed by the handler 
	callbacks.
	@return The new AVUndo object. 
	@see AVUndoGetAVDoc 
	@see AVUndoGetData 
	@see AVUndoGetType 
	@see AVUndoSetData 
	@see AVDocBeginUndoOperation 
	@see AVDocClearUndos 
	@see AVDocEndUndoOperation 
	@see AVDocGetTopUndo 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVUndo, AVUndoNew, (AVDoc doc, AVUndoHandler handler, AVUndoHandlerData undoData))


/**
	Sets or replaces the client-defined private data for the 
	undo record. The handler data can be accessed by any of 
	the callbacks listed in the AVUndoHandler. 
	@param undo The undo record whose handler data is set.
	@param handlerData The client-defined private data to be set in the undo record.
	@see AVUndoNew 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVUndoSetData, (AVUndo undo, AVUndoHandlerData handlerData))


/**
	Gets the client-defined private data for the undo record, 
	as specified upon creation. The handler data can be accessed 
	by any of the callbacks listed in the AVUndoHandler. 
	@param undo The undo record whose handler data is obtained.
	@return The handler data. 
	@see AVUndoNew 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVUndoHandlerData, AVUndoGetData, (AVUndo undo))


/**
	Gets the document whose undo list contains the undo record. 
	
	@param undo The undo record whose document is obtained.
	@return The AVDoc object. 
	@see AVDocBeginUndoOperation 
	@see AVDocClearUndos 
	@see AVDocEndUndoOperation 
	@see AVDocGetTopUndo 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVDoc, AVUndoGetAVDoc, (AVUndo undo))


/**
	Gets the type of the undo record, as specified in the AVUndoHandler. 
	The type is a client-defined string that can be matched 
	for retrieval by AVDocGetTopUndo(). 
	@param undo The undo record whose type is obtained.
	@return The client-defined type string for the undo record. 
	@see AVUndoNew 
	@see AVDocGetTopUndo 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(const char *, AVUndoGetType, (AVUndo undo))


/**
	Clears the entire undo list for the AVDoc and releases all 
	associated AVUndo objects. 
	@param doc The document whose undo list is cleared.
	@return None. 
	@see AVUndoNew 
	@see AVUndoReleaseProc 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocClearUndos, (AVDoc doc))


/**
	Returns the most recent AVUndo record in the document's 
	undo list, if it of the desired type. 
	@param doc The document. 
	@param desiredType The type of the desired undo record. 
	
	@return The undo record object, or <code>NULL</code> if the undo list is empty 
	or if the type of the most recent undo record does not match 
	<code>desiredType</code>. 
	@see AVDocBeginUndoOperation 
	@see AVDocClearUndos 
	@see AVDocGetTopUndoAndRedo 
	@see AVUndoGetType 
	@see AVUndoNew 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVUndo, AVDocGetTopUndo, (AVDoc doc, const char *desiredType))


/**
	Begins an undo group for the document. To create an undo 
	group, call this method, create each instance with its handler 
	and data, and call AVDocEndUndoOperation(). 

	<p>All AVUndo objects that are added to a group are presented 
	in the user interface as a single undo operation. Undo groups that are 
	nested in other groups are considered part of the parent 
	group. </p>
	@param doc The document whose undo group is started.
	@see AVDocClearUndos 
	@see AVDocEndUndoOperation 
	@see AVDocGetTopUndo 
	@see AVUndoNew 
	@see AVUndoBeginEndProc 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocBeginUndoOperation, (AVDoc doc))


/**
	Ends an undo group for the document. To create an undo group, 
	call AVDocBeginUndoOperation(), create each instance with 
	its handler and data, and call this method. 
	@param doc The document whose undo group is ended. 
	@param undoTitle The title to be used as the <code>"Undo"</code> string 
	in the user interface. 
	@param redoTitle The title to be used as the <code>"Redo"</code> string 
	in the user interface.
	@see AVDocBeginUndoOperation 
	@see AVDocClearUndos 
	@see AVDocGetTopUndo 
	@see AVUndoNew 
	@see AVUndoBeginEndProc 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocEndUndoOperation, (AVDoc doc, const ASText undoTitle, const ASText redoTitle))


/**
	Forces any pending updates for the specified page view to 
	finish drawing, using the specified transition effect. 
	@param pageView The AVPageView to redraw. 
	@param trans The transition to use.
	@see AVPageViewDrawNow 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVPageViewDrawNowWithTransition, (AVPageView pageView, PDTrans trans))

/* AVDocPrintSeparations does nothing for Adobe Reader and non-Pro configurations */

/**
	Prints document color separations using the supplied parameters. 
	Printing is complete when this method returns. 

	<p>For Adobe Reader and Acrobat Standard, this method 
	does nothing.</p> 

	@note If security has been set on a file so that it is not 
	printable, the document will not print, but no error is 
	raised. Check the security before printing the file. 
	@param params A structure containing print separation 
	parameters. This structure includes the document object.
	@see PDPageMakeSeparations 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocPrintSeparations, (AVDocPrintSepsParams params))

/**
	Fills out the given view definition with the information 
	needed to restore this document's state at a later date. 
	If you pass an empty ASCab, the method fills it with all 
	of the view information. Otherwise, it fills only those 
	fields that are present in the ASCab. 

	<p>The ASCab can contain the same fields defined for AVDocViewDef, 
	plus an additional field, <code>ocgStates</code>, which is an ASCab containing 
	a set of optional content states. </p>
	@param doc The document whose state is recorded. 
	@param viewDef A pointer to the ASCab that stores the 
	state.
	@see AVDocGetViewDef 
	@see AVDocSetViewDefEx 

	@note Supersedes AVDocGetViewDef() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocGetViewDefEx, (AVDoc doc, ASCab viewDef))

/**
	Sets the document's state to match the information in <code>viewDef</code>. 
	@param doc The document whose state is updated. 
	@param viewDef A pointer to the ASCab that stores the 
	state.
	@see AVDocGetViewDefEx 
	@see AVDocSetViewDef 
	
	NOTE: Supersedes AVDocGetViewDef() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
SPROC(void, AVDocSetViewDefEx, (AVDoc doc, ASCab viewDef), AVDocUseViewDefEx)

/**
	Makes the specified window modal, so that no other window 
	can take the keyboard focus when this window is active. 
	
	@param window The window to make modal.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see AVWindowEndModal 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVWindowDoModal, (AVWindow window))

/**
	Stops the specified window from being modal, so that other 
	windows can take the keyboard focus when this window is 
	active. 
	@param window The window to stop from being modal.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see AVWindowDoModal 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVWindowEndModal, (AVWindow window))


/**
	Gets the value of the <code>UsePenForInput</code> user preference attribute (currently unused). 
	@return Currently, always <code>true</code>. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVSysGetUsePenForInput, (void))

/* AVPageViewSnapPointEx is the same as AVPageViewSnapPoint, but uses page space
 * coordinates. This is more accurate and generally preferred to AVPageViewSnapPoint
 * when working with page elements. */

/**
  	<p>Snaps a point to the layout grid if the <code>avpSnapToGrid</code> preference 
  	is set, using page-space coordinates. </p>

	@param pageView The page view. 
	@param pt (Filled by the method) The point that will be 
	snapped to the grid, specified in page space. 
	@param direction An AVDragType indicating how the point 
	is to be translated. Not all AVDragType values are allowed; only 
	the following AVDragType values are used:
	

	<TABLE rules="all" cellspacing="1">
	<TR><TH>AVDragType</TH><TH>Description</TH></TR>
	<TR><TD>kAVDragRect</TD><TD>Snap to the nearest grid intersection.</TD></TR>
	<TR><TD>kAVDragSnapToTopLeft</TD><TD>Snap to the nearest grid intersection in the top left direction.</TD></TR>
	<TR><TD>kAVDragSnapToTop</TD><TD>Snap to the nearest grid line above this point; <code>pt->h</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToTopRight</TD><TD>Snap to the nearest grid intersection in the top right direction.</TD></TR>
	<TR><TD>kAVDragSnapToRight</TD><TD>Snap to the nearest grid line right of this point; <code>pt->v</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToBottomRight</TD><TD>Snap to the nearest grid intersection in the bottom right direction.</TD></TR>
	<TR><TD>kAVDragSnapToBottom</TD><TD>Snap to the nearest grid line below this point; <code>pt->h</code> is unchanged.</TD></TR>
	<TR><TD>kAVDragSnapToBottomLeft</TD><TD>Snap to the nearest grid intersection in the bottom left direction.</TD></TR>
	<TR><TD>kAVDragSnapToLeft</TD><TD>Snap to the nearest grid line left of this point; <code>pt->v</code> is unchanged.</TD></TR>
	</TABLE>

	@see AVPageViewDragRectSnappedEx 
	@see AVPageViewSnapPoint 

	@note This method supersedes AVPageViewSnapPoint() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVPageViewSnapPointEx, (AVPageView pageView, ASFixedPoint *pt, AVDragType direction))

/* AVPageViewDragRectSnappedEx should be used in place of AVPageViewDragRectSnapped
** when page-level accuracy is important and/or the client would like to implement
** their own draw proc during the drag loop. */

/**
  	<p>Allows the user to move or resize an existing rectangle. 
	This version of the method allows you to specify your own 
	drawing procedure.</p> 
	
	@param params The parameters with which to perform the 
	drag operation. These include the page view object.
	@return A bit-wise OR of the Modifier Keys that were in effect when 
	the mouse button was released. 
	@see AVPageViewDragRectSnapped 
	@see AVPageViewSnapPointEx 
	@see AVSysGetModifiers 

	@note Supersedes AVPageViewDragRectSnapped() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
XNPROC(AVTFlagBits, AVPageViewDragRectSnappedEx, (const AVDragRectParamsRec *params))


/**
	Sets the AVComputeTooltipProc() associated with a toolbar 
	button. This routine determines the text displayed in the 
	mega-tooltip. 
	@param button IN/OUT The button whose AVComputeTooltipProc() is 
	set. 
	@param proc IN/OUT A user-supplied procedure to call whenever the 
	Acrobat viewer needs to know what mega-tooltip to display. 
	@param clientData IN/OUT A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonSetComputeTooltipProc, (AVToolButton button,
	AVComputeTooltipProc proc, void* clientData))

/* For setting the button label text. */

/**
	Sets the label text associated with the specified AVToolButton 
	and its priority value. The priority determines the preference 
	order in which labels are shown when a toolbar is too short 
	to hold all of the button labels. If the priority is less 
	than kAVButtonPriorityOnExtraLow, the label text is not shown 
	at all unless the user forces all labels to be shown using 
	the General preference panel. 
	@param button The button whose label text is obtained.
	@param labelText The label text. 
	@param priority The label text's priority value.
	@see AVLegacyToolButtonGetLabelText 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonSetLabelText, (AVToolButton button, ASConstText labelText,
									   AVToolButtonLabelPriority priority))

/**
	Gets the label text associated with the specified AVToolButton 
	and its priority value. The priority determines the preference 
	order in which labels are shown when a toolbar is too short 
	to hold all of the button labels. If the priority is less 
	than kAVButtonPriorityOnExtraLow, the label text is not shown 
	at all unless the user forces all labels to be shown using 
	the General preferences panel. 
	@param button The button whose label text is obtained. 
	
	@param resultText (Filled by the method) The label text. 
	
	@param priority (Filled by the method) The label text's 
	priority value.
	@return <code>true</code> if the label text string and priority are successfully 
	obtained, <code>false</code> otherwise. 
	@see AVLegacyToolButtonSetLabelText 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVLegacyToolButtonGetLabelText, (AVToolButton button, ASText resultText,
										 AVToolButtonLabelPriority *priority))

/* Simply clones an AVMenuItem */

/**
	Creates a new menu item object using an existing menu item 
	as a template. If the menu item contains a submenu, that 
	submenu is also copied. 
	@param menuItem The menu item to copy.
	@return The new menu item object. 
	@see AVMenuItemNew 
	@see AVMenuItemNewWithASText 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVMenuItem, AVMenuItemClone, (AVMenuItem menuItem))


/**
	Retrieves the language in which the application's user interface 
	is running, in the format specified by the <code>kLangFormat</code> member 
	of the supplied parameter structure. 
	@param params (Filled by the method) On input, it contains 
	the desired language format. On return, it contains the language 
	string in the given format. 
	@return <code>true</code> if the language string was retrieved, otherwise <code>false</code>. 
	
	@see AVAppGetLanguage 
	@see AVAppGetVersion 

	@note Supersedes AVAppGetLanguage() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppGetLanguageWithParams, (AVAppLanguageParams params))


/**
	Creates an icon bundle object from an array of icon data 
	records. 
	@param eDataFormat The data format for the icons in the 
	new icon bundle. 
	@param dataRecs An array of icon data records for the 
	new icon bundle. 
	@param numRecs The number of records in <code>dataRecs</code>.
	@return The new icon bundle object. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVIconBundle6, AVAppCreateIconBundle6, (AVIconDataFormat eDataFormat, AVIconDataRec *dataRecs, ASCount numRecs))


/**
	Sets the AVNotifyTooltipProc() associated with a toolbar button. 
	This routine is called before text is displayed in the tooltip. 
	
	@param button The toolbar button whose tooltip procedure 
	is set. 
	@param proc A user-supplied procedure to call when the Acrobat 
	viewer needs to display tooltip text, as when the cursor 
	moves over the button. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonSetNotifyTooltipProc, (AVToolButton button,
	AVNotifyTooltipProc proc, void* clientData))


/**
	Fills a rectangle structure with the left, top, right, and 
	bottom distances between the inner window rectangle (the frame 
	rectangle) and the outer window rectangle. These distances include 
	borders, title bars, and so on. 
	@param win The window whose border width is obtained. 
	
	@param rect (Filled by the method) A pointer to a rectangle 
	structure in which to return the window's border width rectangle, 
	specified in global screen coordinates.
	@see AVWindowGetFrame 
	@see AVWindowGetInterior 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVWindowGetBorderWidths, (AVWindow win, AVRect *rect))


/**
	Draws a polygon, filled with the color most recently set 
	using AVPageViewSetColor(), or inverted. 
	@param pageView The page view in which the polygon is 
	drawn. 
	@param x The list of x-coordinates for the vertices of 
	the polygon. 
	@param y The list of y-coordinates for the vertices of 
	the polygon. 
	@param numPoints The number of vertices in the polygon. 
	
	@param invert When <code>true</code>, it inverts the polygon instead of 
	filling it with the set color.
	@see AVPageViewDrawPolygonOutline 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVPageViewDrawPolygon, (AVPageView pageView, AVDevCoord* x, AVDevCoord* y, ASCount numPoints, ASBool invert))


/**
	Draws a stroked (not filled) or inverted polygon, using 
	the color most recently set using AVPageViewSetColor(). 
	@param pageView The page view in which the polygon is 
	drawn. 
	@param x The list of x-coordinates for the vertices of 
	the polygon. 
	@param y The list of y-coordinates for the vertices of 
	the polygon. 
	@param numPoints The number of vertices in the polygon. 
	
	@param invert When <code>true</code>, it inverts the polygon instead of 
	stroking it with the set color.
	@see AVPageViewDrawPolygon 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVPageViewDrawPolygonOutline, (AVPageView pageView, AVDevCoord* x, AVDevCoord* y, ASCount numPoints, ASBool invert))


/**
	Registers a HowTo panel with the application. 
	@param panelName The internal language-independent name 
	of the HowTo panel to register. 
	@param panelURL The file name for the XML/HTML content, 
	specified as a device-independent path (see PDFileSpecGetDIPath()). The path 
	is relative to <code>urlDirectory</code> if supplied; otherwise it is 
	relative to the application's localized HowTo folder. 
	@param panelIcon The icon to show in the upper-left corner 
	of the panel. 
	@param panelTitle The text to display in the panel's title. 
	The viewer make a copy of this text. 
	@param showInHomepage <code>true</code> to show the title on the HowTo 
	panel's home page, <code>false</code> otherwise. To hide or show the 
	title dynamically (for example, based on the contents of the current 
	document) use a compute-visible callback. See 
	AVAppSetHowToPanelComputeVisibleProc(). 
	@param urlDirectory The directory where the <code>panelURL</code> and 
	other XML/HTML pages are located, specified as a device-independent path, 
	or <code>NULL</code> for the default location (the application's localized 
	HowTo folder). 
	@param sortKey A key by which to order items on the HowTo 
	panel's home page.
	@see AVAppAutoShowHowToPanel 
	@see AVAppGetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShowText 
	@see AVAppSetHowToPanelComputeVisibleProc 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVAppRegisterHowToPanel, (ASAtom panelName, const char *panelURL,
									  AVIcon panelIcon, ASConstText panelTitle,
									  ASBool showInHomepage, ASPathName urlDirectory,
									  ASUns32 sortKey))


/**
	When the auto-show state of a HowTo panel is <code>true</code>, the panel 
	is shown whenever when the client calls AVAppAutoShowHowToPanel(). 
	To give users the option of suppressing the auto-show behavior, 
	use this method to register some text, which appears in 
	a checkbox at the bottom of the panel. If the user clears 
	the checkbox, use AVAppSetHowToPanelAutoShow() to suppress 
	the auto-show behavior for the panel. 
	@param panelName The internal language-independent name 
	of the HowTo panel whose auto-show suppression text is set. 
	
	@param checkBoxText The text to display in the auto-show 
	suppression check box at the bottom of the HowTo panel. 
	The view copies this text. The string should be of the form 
	<code>"Show XXXX when XXX"</code>. For example, it could be <code>"Show home page at startup"</code>. 
	
	@see AVAppAutoShowHowToPanel 
	@see AVAppGetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShow 
	@see AVAppSetHowToPanelComputeVisibleProc 
	@see AVAppRegisterHowToPanel 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVAppSetHowToPanelAutoShowText, (ASAtom panelName, ASConstText checkBoxText))


/**
	Get the current auto-show state of a HowTo panel. The auto-show 
	state is <code>true</code> by default. When the auto-show state is <code>true</code> 
	for a specified panel, that panel is shown whenever the 
	client calls AVAppAutoShowHowToPanel() on it. 
	@param panelName The internal language-independent name 
	of the HowTo panel whose auto-show state is obtained.
	@return <code>true</code> if the current auto-show state is ON, <code>false</code> otherwise. 
	
	@see AVAppAutoShowHowToPanel 
	@see AVAppSetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShowText 
	@see AVAppSetHowToPanelComputeVisibleProc 
	@see AVAppRegisterHowToPanel 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVAppGetHowToPanelAutoShow, (ASAtom panelName))


/**
	Set the current auto-show state of a HowTo panel. The auto-show 
	state is <code>true</code> by default. When the auto-show state is <code>true</code>, 
	the panel is shown whenever when the client calls AVAppAutoShowHowToPanel(). 
	Set it to <code>false</code> to disable the client's auto-show behavior 
	for the panel. See AVAppSetHowToPanelAutoShowText(). 
	
	@param panelName The internal language-independent name 
	of the HowTo panel whose auto-show state is set. 
	@param autoShow The new auto-show state, <code>true</code> or <code>false</code>.
	@see AVAppAutoShowHowToPanel 
	@see AVAppGetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShowText 
	@see AVAppSetHowToPanelComputeVisibleProc 
	@see AVAppRegisterHowToPanel 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVAppSetHowToPanelAutoShow, (ASAtom panelName, ASBool autoShow))


/**
	Opens the HowTo panel and fills it with the specified panel's 
	content, if that panel's <code>AutoShow</code> attribute is <code>true</code>. 

	<p>The Acrobat application does not automatically show any 
	HowTo panel; it is up to a client to determine the conditions 
	under which to show the panel automatically. Clients should 
	allow the user to disable the auto-show behavior; use AVAppSetHowToPanelAutoShow() 
	to set the <code>AutoShow</code> attribute of a panel to <code>false</code>. </p>
	@param avdoc The document for which to show the HowTo 
	panel, or <code>NULL</code> to display the application-wide HowTo panel 
	in the main application window. You must specify the document 
	if it is external to the application. 
	@param panelName The name of the HowTo panel to show.
	@see AVAppGetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShowText 
	@see AVAppSetHowToPanelComputeVisibleProc 
	@see AVAppRegisterHowToPanel 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVAppAutoShowHowToPanel, (AVDoc avdoc, ASAtom panelName))

/**
	Sets the user-supplied procedure that determines whether 
	the menu item appears when its parent menu is opened. It does 
	nothing if <code>menuItem</code> is <code>NULL</code>. 
	@param menuItem The menu item whose visibility procedure 
	is set. 
	@param proc User-supplied procedure to call when the Acrobat 
	viewer needs to know if the menu item is visible. 
	@param data A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see AVMenuItemIsVisible 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVMenuItemSetComputeVisibleProc, (AVMenuItem menuItem, AVComputeVisibleProc proc,
	void *data))

/**
	Tests whether the specified menu item is visible on its 
	parent menu. The visibility state is calculated using the 
	AVComputeVisibleProc(). 
	@param menuItem The menu item whose visibility state is 
	tested.
	@return <code>true</code> if <code>menuItem</code> is visible, or if <code>menuItem</code> has no AVComputeVisibleProc(). 
	It returns <code>false</code> if the menu item is not visible, if its AVComputeVisibleProc() 
	raises an exception (this is not recommended), or if <code>menuItem</code>
	is <code>NULL</code>. 
	@see AVMenuItemSetComputeVisibleProc 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVMenuItemIsVisible, (AVMenuItem menuItem))

/**
	Sets the AVComputeVisibleProc() associated with a toolbar 
	button. This routine determines whether the button is visible 
	when its parent toolbar is visible. 
	@param button The toolbar button whose visibility procedure 
	is set. 
	@param p A user-supplied procedure to call when the Acrobat 
	viewer needs to know if the button is visible. 
	@param data A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVLegacyToolButtonSetComputeVisibleProc, (AVToolButton button, AVComputeVisibleProc p, void *data))


/**
	Registers a new HowTo panel callback with the application. 
	This callback is executed at various times to determine 
	whether the panel's title will appear in the HowTo home 
	page. The title appears if and only if showInHomePage() was 
	set to <code>true</code> in the call to AVAppRegisterHowToPanel() and this 
	callback returns <code>true</code>. 

	<p>If this callback is not registered, the panel title appears 
	if <code>showInHomePage</code> was set to <code>true</code> in the call to AVAppRegisterHowToPanel().</p> 
	
	<p>Register this callback if you want the title to appear only 
	under certain conditions (for example, when the active document 
	has some special characteristics or attributes). </p>
	@param panelName The internal, language-independent name 
	of the HowTo panel. 
	@param p The procedure to call to determine whether 
	the panel should appear on the HowTo home page. 
	@param data A pointer to data to pass to the procedure.
	@see AVAppAutoShowHowToPanel 
	@see AVAppGetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShow 
	@see AVAppSetHowToPanelAutoShowText 
	@see AVAppRegisterHowToPanel 
*/
NPROC(void, AVAppSetHowToPanelComputeVisibleProc, (ASAtom panelName, AVComputeVisibleProc p, void *data) )

/**
	Sets the position of the toolbar. A toolbar can have separate 
	positional attributes for internal and external views. The 
	position is set when the user first opens Acrobat; after 
	that, the user's preferences dictate where the toolbar is 
	located. 
	@param toolBarName The name of the toolbar. Refer to Toolbar 
	and Toolbar Button Names for a list of the standard named 
	toolbars. 
	@param external If <code>true</code>, the preferences are associated 
	with the external view. 
	@param position The structure defining the toolbar's attributes.
	@see AVLegacyToolBarNew 
	@since PI_ACROVIEW_VERSION >= 0x000500000x00060000
*/
NPROC(void, AVAppRegisterLegacyToolBarPosition,(const char *toolBarName, ASBool external, AVToolBarPosition position))

/**
	Returns the most recent undo and redo records in the document's 
	undo list, if they are of the desired type. 
	@param doc The document. 
	@param undo (Filled by the method) A pointer to the latest 
	undo, or <code>NULL</code> if the undo list is empty or if the type of 
	the most recent undo record does not match <code>desiredType</code>. 
	
	@param redo (Filled by the method) A pointer to the latest 
	redo, or <code>NULL</code> if the redo list is empty or if the type of 
	the most recent redo record does not match <code>desiredType</code>. 
	
	@param desiredType The type of the desired undo record. 
	
	@see AVDocBeginUndoOperation 
	@see AVDocClearUndos 
	@see AVDocGetTopUndo 
	@see AVUndoGetType 
	@see AVUndoNew 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocGetTopUndoAndRedo, (AVDoc doc, AVUndo *undo, AVUndo *redo,const char *desiredType))

/**
	Registers a user-supplied procedure to call after a context 
	menu has been created but before it is shown to the user. 
	The callback can add menu items to or remove menu items 
	from the menu. 
	@param menuName The name of the context menu to modify. Its names can be one of the following:

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Name</TH><TH>Description</TH></TR>
	<TR><TD><code>Page</code></TD><TD>The standard context menu for an AVPageView.</TD></TR>
	<TR><TD><code>Select</code></TD><TD>The context menu for selected text. For both menus, the menu data is an AVDoc pointer.</TD></TR>
	</TABLE>

	@param proc The user-supplied procedure to call. 
	@param clientData A pointer to user-supplied data to pass 
	to the procedure each time it is called. 
	@exception genErrNoMemory 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVAppRegisterForContextMenuAddition, (ASAtom menuName, AVContextMenuAdditionProc proc, void *clientData))

/**
	Gets the point-to-pixel scaling factor that transforms page 
	units to device space units for the specified page view. 
	Although the method returns both x and y factors, these 
	are normally the same. 
	@param pageView The page view whose scaling is obtained. 
	
	@param xScale (Filled by the method) A pointer to the horizontal 
	scaling factor. 
	@param yScale (Filled by the method) A pointer to the vertical 
	scaling factor.
	@see AVPageViewGetPageToDevMatrix 
	@see AVPageViewGetZoom 

	@note In previous releases, you could use the zoom factor 
	to tranform page units (in points) to device units (in pixels). 
	In Acrobat 6.0 and later, because a point is no longer assumed 
	to be the same as a pixel, this is no longer accurate. It 
	is recommended that you use the page-to-device matrix as 
	much as possible, and use this method if you specifically 
	need the point-to-pixel scaling factor. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVPageViewGetPageToDevScaling, (AVPageView pageView, float *xScale, float *yScale))

/**
	Gets the active tool for the AVDoc. The call provides the 
	additional context needed to retrieve the active tool for 
	documents that are displayed in external windows such as 
	a web browser. 
	@param doc The document whose active tool is obtained, 
	or <code>NULL</code> to get the active tool for the main application 
	window.
	@return The active tool object. 
	@exception genErrNoMemory 
	@see AVAppGetActiveTool 
	@see AVAppGetDefaultTool 
	@see AVAppGetLastActiveTool 
	@see AVDocSetActiveTool 

	@note It is recommended that you use AVDocGetActiveTool() 
	rather than AVAppGetActiveTool(), preferably specifying a 
	particular document. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVTool, AVDocGetActiveTool, (AVDoc doc))

/**
	Sets the active tool for the AVDoc. 
	@param doc The document whose active tool is set, or 
	<code>NULL</code> to set the active tool for the application. 
	@param tool The new active tool. 
	@param persistent When <code>true</code>, the tool stays active after 
	it is used. It is passed to the tool's <code>Activate</code> callback.
	@exception genErrNoMemory 
	@see AVDocGetActiveTool 

	@note It is recommended that you use AVDocSetActiveTool() 
	rather than AVAppSetActiveTool(), preferably specifying a 
	particular document. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(void, AVDocSetActiveTool, (AVDoc doc, AVTool tool, ASBool persistent))

/**
	Registers a user-supplied procedure to call each time a 
	user clicks the right mouse button in an AVPageView. On 
	Mac OS, the procedure is called when the user holds down 
	the Control key and clicks the mouse button. 

	<p>To unregister, you must use the same callback that was used 
	to register; you cannot use a newly created callback. To 
	accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and unregister; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param clickProc A user-supplied callback to call each time the 
	right mouse button is clicked. 
	@param data A pointer to user-supplied data to pass to <code>proc</code> 
	each time it is called.
	@exception genErrNoMemory 
	@see AVAppUnregisterForPageViewClicks 
	@see AVAppUnregisterForPageViewRightClicks 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
SPROC(void, AVAppRegisterForPageViewRightClicks, (AVPageViewClickProc clickProc, void* data),
	AVPageViewRegisterForRightClicks)

/**
	Un-registers a user-supplied procedure to call each time 
	a user clicks the right mouse button in an AVPageView. 

	<p>To un-register, you must use the same callback that was 
	used to register; you cannot use a newly created callback. 
	To accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and un-register; do not call ASCallbackCreateProto() 
	a second time when un-registering. </p>
	@param clickProc The original callback.
	@exception genErrNoMemory 
	@see AVAppRegisterForPageViewRightClicks 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
SPROC(void, AVAppUnregisterForPageViewRightClicks, (AVPageViewClickProc clickProc),
	AVPageViewUnregisterForRightClicks)

/**
	Determines whether a given document is on a slow file system 
	(such as a web browser). 
	@param doc The document being investigated.
	@return <code>true</code> if the given document is on a slow file system; <code>false</code> 
	otherwise. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVDocIsSlow, (AVDoc doc))

/**
	Gets the desktop boundary for the monitor on which the window 
	would appear if its frame was set to the specified frame. 
	This boundary describes in global coordinates the visible 
	area of the desktop (that is, without the menu bar, task 
	bar, docked toolbars, and so on). 
	@param win The window whose desktop bounds are obtained. 
	
	@param frame A pointer to a rectangle structure for a potential 
	window frame. 
	@param bounds (Filled by the method) A pointer to a structure 
	in which to return the window's desktop bounds rectangle, 
	specified in global screen coordinates.
	@return <code>true</code> if successful, <code>false</code> if the method cannot provide the 
	information. In this case, the bounds are set to <code>(0,0,0,0)</code>. 
	
	@see AVWindowEnsureInBounds 
	@see AVWindowGetFrame 
	@see AVWindowGetInterior 
	@see AVWindowSetFrame 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(ASBool, AVWindowGetDesktopBounds, (AVWindow win, const AVRect *frame, AVRect *bounds))

/**
	Gets the server type for the specified document. 
	@param doc The document whose server type is obtained.
	@return The server type value. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
NPROC(AVDocServerType, AVDocGetServerType, (AVDoc doc))

/**
  	<p>Un-registers a user-supplied page view drawing procedure. </p>

	<p>To unregister, you must use the same callback that was used 
	to register; you cannot use a newly created callback. To 
	accomplish this, call ASCallbackCreateProto() once before 
	registering and use the value returned from this call both 
	to register and unregister; do not call ASCallbackCreateProto() 
	a second time when unregistering. </p>

	<p>You can register only one procedure; however, in version 
	6.0, you can register it more than once, with a different 
	client data pointer in each case. You can then pass the 
	same <code>proc</code> and <code>clientData</code> pointer to this method to un-register 
	that particular combination. </p>
	@param proc The original callback. 
	@param clientData A pointer to data to pass to the callback.
	@see AVAppRegisterForPageViewDrawing 
	
	@note Supersedes AVAppUnregisterForPageViewDrawing() in Acrobat 6.0. 
	@since PI_ACROVIEW_VERSION >= 0x00060000
*/
SPROC(void, AVAppUnregisterForPageViewDrawingEx, (AVPageViewDrawProc proc, void *clientData),
	AVPageViewUnregisterForDrawingEx)

/**
	Sets the wireframe mode for a page view. 
	@param pageView IN/OUT The page view whose wireframe mode is set. 
	@param drawWireframe IN/OUT The new wireframe mode for the page view. 
	@see AVPageViewGetWireframeDrawing 
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC(void, AVPageViewSetWireframeDrawing, (AVPageView pageView, ASBool drawWireframe))

/**
	Gets the wireframe mode for a page view. 
	@param pageView IN The page view whose wireframe mode is obtained. 
	
	@return pageView's page wireframe mode. 
	
	@see AVPageViewSetWireframeDrawing 
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC(ASBool, AVPageViewGetWireframeDrawing, (AVPageView pageView))

/**
	Returns whether the passed <code>key</code> should cause a selected item to be deleted.
	This is required since the rules for which keys should delete objects differ among platforms. 
	@param key IN The keycode of the key to check. 
	@param flags IN The flags associated with the keydown. 
	
	@return Whether <code>key</code> should cause an object to be deleted. 
	
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC(ASBool, AVAppShouldKeyDeleteObject, (AVKeyCode key, AVFlagBits16 flags))

/**
Registers a callback that will be called once, when Acrobat is first idle and
not drawing during idle.
@param lateInitProc IN The procedure to call. 
@param clientData IN A pointer to data to pass to the callback.
@param delay IN An additional amount of time to wait before calling after the first idle (in ticks). 

@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC(void, AVAppRegisterLateInitProc, (AVIdleProc lateInitProc, void *clientData, ASUns32 delay))

/**
	Gets the set of bookmarks for a given document that satisfies the input
	filter. It is the client's responsibility to release the memory associated
	with the bookmark array using ASfree().	
	
	@param avDoc IN The document containing the bookmarks
	@param avBookmarkFilter The filter applied to the bookmarks.  See the definition of
	AVBookmarkFilter in AVExpT.h.  The default is <code>0</code>.
	@param pPDBookmarkArray OUT A pointer to an array for storing the bookmarks
	If this parameter is <code>NULL</code>, it does not copy the PDBookmark associated
	with the bookmarks. If this parameter is not <code>NULL</code>, a bookmark
	array is allocated and assigned to this pointer. The bookmarks that satisfy
	the filter are copied into this array.
	@return The number of bookmarks copied into the array. 
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC(ASInt32, AVDocGetBookmarks, (AVDoc avDoc, AVBookmarkFilter avBookmarkFilter, PDBookmark **pPDBookmarkArray))

/**
	Gets the tool that was active for this document
	before the current tool became active.

	@return The last active tool. If only one tool has ever been active, it is returned. 
	@see AVAppGetActiveTool 
	@see AVAppGetDefaultTool
	@see AVDocGetActiveTool
	@since PI_ACROVIEW_VERSION >= 0x00070000 
	
*/
NPROC(AVTool, AVDocGetLastActiveTool, (AVDoc avDoc))

/**
	Returns the number of windows currently open for
	the document.

	@param avDoc IN The document
	@return The number of windows open for the document.
	@see AVDocGetNthWindow
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC( ASCount, AVDocGetNumWindows, (AVDoc avDoc))

/**
	Gets the specified AVWindow for the specified document. 
	If the index is out of range, <code>NULL</code> is returned. The windows
	are enumerated in no particular order. Specifically, the
	window at index <code>0</code> is not guaranteed to be the active window.

	@param avDoc The document whose AVWindow is obtained. 
	@param n The index of the window to obtain. The index 
	range is <code>0</code> to <code>(AVDocGetNumWindows()-1)</code>.
	@return The document's nth AVWindow. 
	@see AVDocGetNumWindows 
	@see AVDocGetAVWindow
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC( AVWindow, AVDocGetNthWindow, (AVDoc avDoc, ASCount n))

/**
	Gets the AVWindow associated with this AVPageView.

	<p>This routine may return <code>NULL</code> if the page view is
	not associated with any document window.</p>

	<p>The primary use of this API is to determine which
	AVPageView objects returned by AVDocGetNthPageView() are
	associated with the document's active window. To do
	this, compare the return value of this method with
	the return value of AVDocGetAVWindow().</p>

	@param pageView The AVPageView whose AVWindow is obtained. 
	@return The page view's AVWindow. 
	@see AVDocGetNumPageViews
	@see AVDocGetNthPageView
	@see AVDocGetAVWindow
	@since PI_ACROVIEW_VERSION >= 0x00070000
*/
NPROC( AVWindow, AVPageViewGetAVWindow, (AVPageView pageView))

/**
	Show the properties dialog box for the specified annotation.

	@param doc The document containing the annotation.
	@param pageNum The page number where the annotation is located.
	@param annot The annotation.
	@exception genErrBadParam is raised if the page number does not correspond to the page where the annotation is located.
	@since PI_ACROVIEW_VERSION >= 0x00070000 */
NPROC(void, AVDocDoAnnotProperties, (AVDoc doc, ASInt32 pageNum, PDAnnot annot))

/**
	Query the state of the mouse buttons in a manner
	appropriate for click-drag operations. This is
	similar to AVSysMouseStillDown(), but can be used to
	query the state of the mouse even while it is up.

	@param canceled Set to indicate whether the user cancelled the operation (for example, by pressing ESC). It can be <code>NULL</code>.
	@param committed Set to indicate whether the use pressed Enter to commit the operation. It can be <code>NULL</code>. 
	@param removeEvents If <code>true</code>, mouse events will be discarded to prevent mouse button
	change events from being sent after the drag operation is finished.
	@return An integer indicates the current state of the mouse buttons:
	<ul>
	<li>Bit <code>0</code> will be set if the primary mouse button is down (this is normally the left button).</li>
	<li>Bit <code>1</code> will be set if the secondary mouse button is down (this is normally the right button).</li>
	<li>Bit <code>2</code> will be set if the tertiary mouse button is down (this is normally the wheel button).</li>
	</ul>
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
NPROC(AVFlagBits32, AVSysTrackMouse, (ASBool* canceled, ASBool* committed, ASBool removeEvents))

/**
	This method invokes the PDF Optimizer tool on a specified AVDoc. An optimized document is created 
	using the settings specified in the PDFOptParamsRec structure. The optimized document is 
	saved to the disk at the location specified in the parameter's structure. If the operation
	is successful, the active document is closed and the optimized document is opened for viewing.
	If the operation fails, the active document remains open.

	<p>The AVDoc passed to the <code>proc</code> should not be dirty. PDF Optimizer is unavailable in external
	windows like those of a web browser, so the AVDoc should not be of a document open 
	in one such window. The document should not be of a version greater than the default PDF 
	version of the Acrobat application.
	If the optimization succeeds, the document associated with the AVDoc is closed and the 
	optimized document is opened in Acrobat.</p>

	@param avDoc The document that is to be optimized. It should be a valid AVDoc. It cannot be <code>NULL</code>.
	@param pdfOptParams A pointer to a structure that specifies the operations to be performed on the document.
	@exception genErrBadParm is raised if any option in the pdfOptParams structure does not conform to the specified rules.
	@exception fileErrDiskFull is raised if there is not enough disk space.
	@exception pdErrOpNotPermitted is raised if the caller does not have permissions to modify the PDF document or if the document is read-only.
	@see AVGetOptimizerParamsForPreset
	@see AVGetOptimizerPresets
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
XNPROC(void, AVDocSaveOptimized, (AVDoc avDoc, const PDFOptParamsRec *pdfOptParams))

/**
	This method fills the parameter with names of all PDF Optimizer presets that 
	are available to the caller.
	

	@param pPresetNames The array that will be allocated and populated by the method.
						The caller should free each member of the array using 
						ASTextDestroy(), and then free the array using ASfree().
	@return The number of preset names populated.

	@note	Certain user-created presets might not be available to the API: 
			<ul>
				<li> The last unsaved settings appear as Custom in the PDF Optimizer user interface, but it is not a valid preset and therefore will not be available. </li>
			</ul>
			The last unsaved settings appear as Custom in the PDF Optimizer user interface, 
			but it is not a valid preset and therefore will not be available.

	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
XNPROC(ASInt32, AVGetOptimizerPresets, (ASText **pPresetNames))

/**
	This method can be used to obtain a PDFOptParamsRec structure populated with the 
	values corresponding to a PDF Optimizer preset. 

	<p>The values of certain members of the preset may be dependent on the PDF file 
	that needs to be optimized. This is true when:</p>
	<ul>
		<li> 
			The Acrobat compatibility level specifies retaining the compatibility of 
			the file. 
		</li>
		<li>
			The default list of fonts to be unembedded needs to be determined.
		</li>
	</ul>
	
	<p>In the second parameter, the caller should specify the AVDoc to get values 
	relevant to a particular file. </p>

	<p>If <code>avDoc</code> is specified as <code>NULL</code>, the values populated in <code>pdfOptParams</code> are those 
	that are actually stored in the preset. These may or may not be valid for all 
	PDFs. The list of fonts to be unembedded will always be a <code>NULL</code> value in this 
	case.</p>

	<p>If the flattening of transparency is off in the preset, 
	<code>pdfOptFlattenTransparencyOptions</code> is also set to a <code>NULL</code> value.</p>

	<p>The method assigns <code>NULL</code> values to <code>asPathDest</code> and <code>fileSys</code> members of PDFOptParamsRec. </p>

	<p>It is the caller's responsibility to free the <code>arrPDFontsToUnembed</code> and 
	<code>pdfOptFlattenTransparencyOptions</code> members using ASfree(). </p>

	<p>The <code>progMon</code> and <code>progMonClientData</code> members are populated with the standard 
	application progress monitor, which is the same as the one returned by the 
	AVAppGetDocProgressMonitor() proc.</p>

	<p>It is the caller's responsibilty to ensure that a preset of the specified name 
	is available to the Acrobat user, either as a shipped or a user-created 
	preset. A useful check could be to ensure that the specified preset name is 
	among the names returned by the AVGetOptimizerPresets() method. </p>

	@param presetName	The preset for which a populated PDFOptParamsRec is desired.
	@param pdfOptParams (filled by the method) A pointer to PDFOptParamsRec. 
	@return <code>true</code> if successful. It returns <code>false</code> if the specified preset name is invalid.
	@see AVGetOptimizerPresets
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
XNPROC(ASBool, AVGetOptimizerParamsForPreset, (ASText presetName, AVDoc avDoc, PDFOptParams pdfOptParams))

/**
	<p>This method can be used to obtain the padding values necessary for the viewer
	to display an annotation's appearance, with various visual treatments applied.</p>

	<p>An annotation handler's <code>GetAppearance</code> callback can set several flags, some of which
	cause the viewer to apply visual treatments to the appearance (for example, kAVAppearanceSelected). 
	These visual treatments may require additional pixels around the
	appearance object, so the annotation handler must expand the device space bounding box
	returned by the <code>GetAnnotViewBBox</code> callback to include these additional pixels.</p>

	<p>To determine how many additional pixels to add to the device space bounding box,
	the annotation handler should call this method, passing in the same flags it intends
	to return from the <code>GetAppearance</code> callback. The returned offset should
	be applied to all sides of the bounding box. In other words, it should be subtracted
	from the top and left and added to the right and bottom.</p>

	@param flags The flags which will be returned by the <code>GetAppearance</code> callback.
	@return The number of units to expand the bounding box on each side.
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
NPROC(ASCount, AVAppGetAnnotAppearancePadding, (ASUns32 flags))

/**
	Determines whether the given menu item is an executable menu item.
	@param menuItem IN The given menu item.
	@return <code>true</code> if the given menu item is executable.
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
NPROC(ASBool, AVMenuItemIsScriptable, (AVMenuItem menuItem))

/**
	Given an ASTimeRecP, it sets the ASText object passed in to the string
	representing the date and time. This routine is locale-friendly. 

	@param timeRec IN/OUT A pointer to an ASTimeRec structure. 
	@param text The allocated ASText object this method will store result in.
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/
NPROC(void, AVSysTimeASTextFromTimeRec, (ASTimeRecP timeRec, ASText text))

/**
	Sets a new icon for a toolbar button to display in menus and
	other UI elements generated from the button that are too small
	to display the button's normal icon. 

	Toolbar buttons that do not have menu icons assigned to them
	via this API will have appropriately-sized icons generated for
	them based on the icon provided via AVLegacyToolButtonSetIcon. This
	may result in scaling or clipping artifacts.

	@param button IN The toolbar button whose menu icon is set. 
	@param icon IN The icon to assign as the button's menu icon. 
	@see AVLegacyToolButtonSetIcon 
	@since PI_ACROVIEW_VERSION >= 0x00080000
*/	
NPROC(void, AVLegacyToolButtonSetMenuIcon, (AVToolButton button, AVIcon icon))

/**
	<p>Listens for a custom notification. </p>

	<p>A custom notification is generated by a plug-in, and contains data customized for that notification.
	Plug-ins can use these to communicate with each other. Data passed to <code>proc</code> from the broadcaster
	is temporary, and receivers should copy any needed information and should not retain pointers to it.
	Client data is passed back to <code>proc</code> when the notification is broadcast.</p>
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(void, AVListenForCustomNotification,(const char* notification, AVCustomNotificationProc proc, void* clientData))

/**
	<p>Stops listening for a custom notification. </p>

	<p>A custom notification is generated by a plug-in, and contains data customized for that notification.
	Plug-ins can use these to communicate with each other.</p>
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(void, AVUnlistenForCustomNotification,(const char* notification, AVCustomNotificationProc proc, void* clientData))

/**
	<p>Sends out a custom notification. </p>

	<p>A custom notification is generated by a plug-in, and contains data customized for that notification.
	Plug-ins can use these to communicate with each other.
	Data can have a variable size but must contain at least the data in the <code>AVNotificationData</code> parameter.
	</p>
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(void, AVBroadcastCustomNotification,(const char* notification, AVNotificationData data)) 
/**
	<p>Registers an <code>AuxDataHandler</code>. </p>

	<p>A handler can be registered for more than one kind of auxiliary 
	data. The type of data is passed to the handler at 
	run time so that it can distinguish the type of data 
	it is receiving. </p>
	@param extension The <code>gExtensionID</code> of the client registering 
	the handler. 
	@param auxDataType The <code>ASAtom</code> for the type of data that 
	the handler accepts. 
	@param handler The handler to register.
	@return <code>true</code> if the handler was registered, <code>false</code> if the handler 
	could not be un-registered (for example, if another handler 
	is already registered for this time). 
	@see AVDocSendAuxData 
	@see AVHasAuxDataHandler 
	@see AVUnregisterAuxDataHandler 
	@since PI_ACROVIEW_VERSION >= 0x00020002
*/
NPROC(ASBool, AVRegisterAuxDataHandler, (ASAtom auxDataType, AVAuxDataHandler handler, void* clientData))

/**
	Applies a set of redaction marks to the document, permanently removing the affected
	document content and the marks themselves.
	@param avDoc IN/OUT The document to which the redaction marks should be applied.
	@param applyParams IN/OUT A pointer to a <code>PDApplyRedactionParams</code> object, specifying which
	redaction marks to apply and what parameters to use when applying them. If this parameter is <code>NULL</code>,
	all redaction marks present in the document will be applied.
	@param showConfirmation IN A boolean value indicating that a confirmation dialog should be presented
	to the user before beginning the application process.
	@param showWarnings IN A boolean value indicating that warning dialogs should be displayed.
	@param showErrors IN A boolean value indicating that error dialogs should be displayed.
	@return <code>true</code> if the document's content was changed, <code>false</code> otherwise.
	@exception pdErrBadAnnotation is raised if any specified redaction marks are invalid.
	@see PDDocApplyRedactions 
	@see PDDocCreateRedaction 
	@see PDRedactionGetProps 
	@see PDRedactionSetProps 
*/
XNPROC(ASBool, AVDocApplyRedactions, (AVDoc avDoc, PDApplyRedactionParams applyParams, ASBool showConfirmation, ASBool showWarnings, ASBool showErrors))

/**
	Inserts a button into a toolbar.  
	@param toolBar The toolbar into which the button is added. 
	
	@param button The button to add to the toolbar. 
	@param params A pointer to an <code>AVToolBarAddButtonParamsRec</code>, describing how the button should be added to the toolbar.
	@see AVLegacyToolButtonRemove 
	@ref AVToolBarAddButtonParams
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(void, AVLegacyToolBarAddButtonEx, (AVToolBar toolBar, AVToolButton button, AVToolBarAddButtonParams params))

/**
	Displays a platform-dependent file save dialog box.
	It is used in conjunction with <code>AVAppBeginSave</code> and <code>AVAppCancelSave</code>.

	@param dialogParams IN Standard dialog parameters for Open/Save/ChooseFolder dialogs.  The <code>initialFileName</code> member may be ignored when running in protected mode on Internet Explorer on Windows Vista.
	@param outFileSys OUT May be <code>NULL</code> if kAVOpenSaveAllowForeignFileSystems is not passed in dialogParams 
	@param outASPathNameToWrite OUT An <code>ASPath</code> to which writing can be done.  The caller must release this <code>ASPathName</code>.
	@param outChosenFilterIndex OUT May be <code>NULL</code> if the caller does not care which filter was chosen.
	@param outASPathNameChosen OUT The <code>ASPath</code> actually chosen by the user.  The caller must release this <code>ASPathName</code>.
	@param outFileSaveHandle OUT The file save handle used to pass to <code>AVAppEndSave</code> or <code>AVAppCancelSave</code>.  This handle represents the file that was actually chosen.
	@return <code>true</code> if the user confirmed the selection, <code>false</code> if the user clicked Cancel or some error occurred. 
	@see AVAppEndSave 
	@see AVAppCancelSave 
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/

NPROC(ASBool, AVAppBeginSave, (AVOpenSaveDialogParams dialogParams, ASFileSys	*outFileSys, ASPathName	*outASPathNameToWrite, ASInt16		*outChosenFilterIndex, ASPathName	*outASPathNameChosen, AVAppFileSaveHandle	*outFileSaveHandle))
																				
/**
	Completes the Save operation started by <code>AVAppBeginSave</code>. 
	It should be called after the data has been written to the path returned by <code>AVAppBeginSave</code>.

	@param inFileSaveHandle IN The file save handle returned by <code>AVAppBeginSave</code>.
	@param inASPathNameWritten IN An <code>ASPath</code> corresponding to the file to which the data was written.
	@return <code>true</code> on success, <code>false</code> on failure.
	@see AVAppBeginSave 
	@see AVAppCancelSave 
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(ASBool, AVAppEndSave, (AVAppFileSaveHandle inFileSaveHandle, ASPathName inASPathNameWritten))

/**
	Cancels the Save operation started by <code>AVAppBeginSave</code>. 
	It should be called if the writing of data to the path returned by <code>AVAppBeginSave</code> failed.

	@param inFileSaveHandle IN The file save handle returned by <code>AVAppBeginSave</code>.
	@return <code>true</code> on success, <code>false</code> on failure.
	@see AVAppBeginSave 
	@see AVAppEndSave 
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(ASBool, AVAppCancelSave, (AVAppFileSaveHandle inFileSaveHandle))

/**
Returns the ink preview value for a page view. 
@param pageView The page view whose number of visible 
inks is obtained. 
@see AVPageViewSetInkPreview 
@since PI_ACROVIEW_VERSION >= 0x00090000
*/
NPROC(ASBool, AVPageViewGetInkPreview, (AVPageView pageView))

/**
	Acquires the platform-specific object needed to draw into 
	the Acrobat viewer's document window using a platform's 
	native graphics calls. When done, release the context using AVPageViewReleaseDrawContext(). 
	
	@param pageView IN/OUT The AVPageView whose platform-dependent 
	port is acquired. 
	@param contextType IN See DrawContextType definition in AVExpT.h
	@return A platform-dependent value:

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Value</TH></TR>
	<TR><TD>Mac OS</TD><TD><code>GrafPtr</code>.</TD></TR>
	<TR><TD>Windows</TD><TD><code>WinPort</code>.</TD></TR>
	<TR><TD>UNIX</TD><TD><code>Widget</code>.</TD></TR>
	</TABLE>

	@see AVPageViewReleaseMachinePort 
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/
NPROC(void *, AVPageViewAcquireDrawContext, (AVPageView pageView, DrawContextType contextType))

/**
	Releases the platform-specific drawing context needed to draw into 
	Acrobat's document window using a platform's native graphics 
	calls. 
	@param pageView IN/OUT The AVPageView whose platform-dependent 
	port is released. 
	@param port IN/OUT The platform-specific port to release. 
	@see AVPageViewAcquireDrawContext 
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/

NPROC(void, AVPageViewReleaseDrawContext, (AVPageView pageView, DrawContextType contextType, void* drawContext))

/**
	Sets the text to show in tooltips. This text is shown 
	when the cursor is held over a toolbar button for a period 
	of time. 

	<p>In Acrobat 4.0 and later, toolbar buttons can also have 
	single key shortcuts assigned to them. (Conceptually, tools 
	have shortcuts but the shortcuts are attached to the buttons). 
	This is done by appending a vertical bar character <code>'|'</code> followed 
	by the shortcut to the button's tooltip text.</p>

	<p>Appending the shortcut to the tooltip text allows it to 
	localize at the same time as the tooltip text. </p>
	
	@example Here is the tooltip text for the Hand tool:

	<p><code>'Hand Tool (H)|h' </code></p>

	<p>The trailing <code>'|h'</code> portion indicates that the Hand tool uses 
	the <code>'H'</code> key as the shortcut. This portion is stripped off 
	before the tooltip is displayed. </p>

	<p>This behavior only applies to tooltips where the '|' is 
	the second-to-last character. </p>

	@param button The toolbar button to which a tooltip is 
	added. 
	@param text The text to show.
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/
NPROC(void, AVLegacyToolButtonSetHelpTextWithASText, (AVToolButton button, ASConstText text))

/**
	Creates a new named toolbar. AVAppRegisterToolBarPosition() 
	must be called after creating the new toolbar to position 
	it relative to other toolbars. 
	@param name IN/OUT The internal, language-independent name of 
	the toolbar. It may not be <code>NULL</code>. 
	@param title IN/OUT The localized, user-friendly name of the toolbar. 
	It may not be <code>NULL</code>. 
	@return The new AVToolBar. 
	@see AVLegacyToolBarGetFrame 
	@see AVLegacyToolBarGetNumbuttons 
	@see AVLegacyToolButtonGetFlyout 
	@see AVLegacyToolButtonNew 
	@since PI_ACROVIEW_VERSION >= 0x00050000
*/
NPROC(AVToolBar, AVLegacyToolBarNewWithASText, (const char *name, ASConstText title))

/**
	Unregisters a handler for an annotation subtype, thereby removing it from
	the global list of annotation handlers. 
	@param handler IN A pointer to a structure containing the annotation 
	handler's callbacks. 
	@see AVAppRegisterAnnotHandler
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/
NPROC(void, AVAppUnregisterAnnotHandler, (AVAnnotHandler handler))

/**
	Converts and appends a file to a PDF document using the handler specified. 
	
	@param inHandler IN Specifies which <code>ConvertToPDF</code> handler to 
	use. 
	@param inSettings IN An ASCab containing the settings to be used 
	in the conversion operation. Pass <code>NULL</code> to use the default 
	settings. 
	@param flags IN Conversion flags. 
	@param inPath IN The location of the input file. 
	@param inFileSys IN The file system from which the path was obtained. 
	
	@param outPDDoc OUT (Filled by the method) It is the caller's responsibility 
	to close the document. 
	@param statusMonitor IN Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>, or any of its members can be <code>NULL</code>. 
	@return One of the AVConversionStatus codes. 
	@see AVConversionEnumToPDFConverters 
	@see AVConversionConvertToPDF 
	@see AVConversionEnumFromPDFConverters 
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/
XNPROC(AVConversionStatus, AVConversionAppendToPDFWithHandler, (
	AVConversionToPDFHandler	inHandler,
	ASCab						inSettings,
	AVConversionFlags			flags,		
	ASPathName					inPath,
	ASFileSys					inFileSys,
	PDDoc						outPDDoc,
	AVStatusMonitorProcs		statusMonitor))

/**
	Gets the number of queued items using the handler specified.
	@param inHandler IN Specifies which <code>ConvertToPDF</code> handler to 
	use. 
	@return Number of pending Conversions
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/
XNPROC(ASUns32, AVConversionGetConversionQueueStatusWithHandler,(
	AVConversionToPDFHandler	inHandler))

/**
    Sets the conversion settings for the handler.
	@param inHandler IN Specifies which <code>ConvertToPDF</code> handler to 
	use.
    @param inSettings IN The ASCab containing the new settings.
	@return TRUE if settings were valid and were set successfully.
	@since PI_ACROVIEW_VERSION >= 0x000A0000
*/
XNPROC(ASBool, AVConversionToPDFSetSettings,(
	AVConversionToPDFHandler	inHandler,
    ASCab                       inSettings))

/**
    Checks whether a given document is opened in Protected View or not.
	Protected View provides an additional level of security. 
	When Protected View in enabled, PDFs are displayed in a restricted environment called a sandbox. 
	This isolation of the PDFs reduces the risk of security breaches in areas outside the sandbox.
	For more information please refer to the Application Security Guide at www.adobe.com/go/acroappsecurity
	@param avDoc IN The document
	@return TRUE if document is opened in Protected View otherwise returns FALSE
	@since PI_ACROVIEW_VERSION >= 0x000B0000
*/
NPROC(ASBool, AVDocIsInProtectedView, (AVDoc avDoc))

#undef XSPROC
#undef XNPROC
#undef XPROC
