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

 MacProcs.h

 - Catalog of functions exported by the Mac Viewer.

*********************************************************************/


/**
	Converts an AVRect into a QuickDraw rectangle. 
	<p> This can throw numerous exceptions and broadcast numerous notifications. </p>
	@param avr IN/OUT Pointer to the AVRect to convert to a rectangle. 
	
	@param r IN/OUT (Filled by the method) The rectangle corresponding 
	to <code>avr</code>. 
	@see RectToAVRect 
	@since PI_MACINTOSH_VERSION >= 0x00020000

*/
NPROC(void, AVRectToRect, (const AVRect *avr, Rect *r))

/**
	Converts a Quickdraw Rect into an AVRect. 
	@param r Pointer to a Rect to convert to an AVRect. 
	
	@param avr (Filled by the method) Pointer to the AVRect 
	corresponding to rect.
	@see AVRectToRect 
	@since PI_MACINTOSH_VERSION >= 0x00020000
*/
NPROC(void, RectToAVRect, (const Rect *r, AVRect *avr))
#if HAS_APPLE_EVENTS

/**
	Handles Apple events that are sent to the Acrobat viewer. 
	Clients that wish to handle their own Apple events do so 
	by using HFTReplaceEntry() to replace this method. If your 
	replacement method does not wish to handle an Apple event 
	it receives, it must pass the Apple event along to the Acrobat 
	viewer by using the CALL_REPLACED_PROC macro. 

	<p>For further information, see <i>Application-Defined Routines</i> 
	in the <i>Responding to Apple Events</i> chapter of <i>Inside Macintosh: 
	Interapplication Communication</i>. </p>

	<p>If a client wishes to get or replace any of the four required 
	Apple events, it must use Mac toolbox calls such as 
	<code>AEGetEventHandler</code> and <code>AESetEventHandler</code>. </p>

	<p>Clients can also support AppleScript; the Acrobat viewer 
	contains an 'scsz' resource, and clients can handle the 
	GetAETE event to append information about scriptable events 
	they provide. </p>
	@ingroup ReplaceableMethods
	@param appleEvent The Apple event that was sent to the 
	Acrobat viewer. 
	@param eventClass The event class of <code>appleEvent</code>. 
	@param eventId The event ID of <code>appleEvent</code>. 
	@param replyEvent An event to send back to the application 
	that sent <code>appleEvent</code>. Add parameters to this event, if appropriate. 
	
	@param err A value indicating whether the Apple event 
	was handled successfully. Return the value <code>noErr</code> (defined 
	by Apple, not in the Acrobat SDK) if the Apple event was 
	handled successfully. See <i>Inside Macintosh: Interapplication 
	Communication</i>. <code>err</code> is the value returned by the function 
	<code>MyEventHandler</code> in that section. In the Acrobat API, 
	it is returned as a parameter rather than as a function's 
	return value.
	@since PI_MACINTOSH_VERSION >= 0x00020000
*/
PROC(void, AVAppHandleAppleEvent, (AppleEvent *appleEvent, DescType eventClass, DescType eventId, AppleEvent *replyEvent, OSErr *err))
#endif

#if MAC_ENV && !AS_ARCH_64BIT
/**
	Enumerates a list of fonts that are installed in the system. 
	These are the fonts that are available for use by Acrobat. 
	This method does not enumerate fonts that have been extracted 
	or fauxed by Acrobat. 
	@param flags For future expansion. It must be zero. 
	@param enumProc A client-provided callback to call for each 
	system font. 
	@param clientData The client data for <code>enumProc</code>.
	@see PDEnumSysFonts 
	@ingroup Enumerators
	@since PI_MACINTOSH_VERSION >= 0x00020002
*/
NPROC(void, AVAppEnumSystemFonts, (Uns32 flags,	AVSystemFontEnumProc enumProc, void *clientData))
#endif /* MAC_ENV && !AS_ARCH_64BIT */

/**
	This function returns the Carbon Print Manager Page Format object to other clients during a print job.
	@note The restriction on using this function is that is that it can only be called after printing has started 
	(for example, the PDDocWillPrintDoc() notification has already been sent.
	@note Clients who use this function should not do anything with the PageFormat object that will interfere with Acrobat's
	print functionality. ITS USE IS VERY RISKY! Please use all Acrobat APIs to accomplish whatever you are trying to do before
	resorting to using this function.
	@return PMPageFormat, which is a Carbon Print Manager type that describes the format of a page during a print job. See the Carbon Print Manager API
	documentation for more information.
	@since PI_MACINTOSH_VERSION >= 0x00060000
*/
NPROC(PMPageFormat, AVAppGetPMPageFormat, (void))

/**
	This function returns the Carbon Print Manager Print Settings object to other clients during a print job.
	@note The restriction on using this function is that is that it can only be called after printing has started 
	(for example, the PDDocWillPrintDoc() notification has already been sent.
	@note Clients who use this function should not do anything with the PrintSettings object that will interfere with Acrobat's
	print functionality. ITS USE IS VERY RISKY! Please use all Acrobat APIs to accomplish whatever you are trying to do before
	resorting to using this function.
	@return PMPrintSettings, which is a Carbon Print Manager type that describes the print job settings. See the Carbon Print Manager API	documentation
	for more information.
	@since PI_MACINTOSH_VERSION >= 0x00060000
*/
NPROC(PMPrintSettings, AVAppGetPMPrintSettings, (void))
