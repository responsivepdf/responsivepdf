/**********************************************************************


 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1996-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 WLHFT.h

 - Contains all of the public definitions for using WebLink.

*********************************************************************/

#ifndef __WLHFT__
#define __WLHFT__

/* -------------------------------- includes ---------------------------------*/

#if PLUGIN
#include "ASExpT.h"
#include "PDExpT.h"
#endif /* PLUGIN */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------- WebLink datatypes ------------------------------ */

/** A data structure that specifies the path name to the web browser.
	@see WDAppSupportPredicate
	@see GetAppSpecifier
*/
#if MAC_PLATFORM
#if AS_ARCH_64BIT
typedef FSRef* WDAppSpecifier;
#else
typedef FSSpec *WDAppSpecifier;
#endif
#endif

#if WIN_PLATFORM || OS2_PLATFORM
typedef char *WDAppSpecifier;
#endif

#if UNIX_PLATFORM
typedef char *WDAppSpecifier;
#endif

#define WDVCURRENTREV (0L)

/** Put a thermometer-style meter in the progress display.
	@ingroup ProgressMonitorFlagOptions
*/
#define PROGRESS_HAS_METER (1L << 0)
/** Add either a Cancel button or a message directing the user how to abort the operation.
	@ingroup ProgressMonitorFlagOptions
*/
#define PROGRESS_HAS_CANCEL (1L << 1)


/** A parameter block specifying the target frame of a URL.
	@see WWWOpenURLWithParams
	@see WDFollowLinkWithParamsFunction
*/
typedef struct {
	/** Should be initialized to <code>sizeof(WWWOpenURLParamsRec)</code>. */
	ASSize_t size;  
	/** The name of the frame to open.
		@note <code>cFrame</code> is exactly the same as the <code>TARGET</code> attribute of a link
		in HTML. You can target a frame by a name you have
		assigned to it. In HTML, <code>TARGET</code> also has four predefined
		values which can be used as if certain windows and frames
		already have names without you having to assign them:
		<ul>
		<li><code>_blank</code></li>
		<li><code>_parent</code></li>
		<li><code>_self</code></li>
		<li><code>_top</code></li>
		</ul>
		
		<p>In Weblink, only <code>_blank</code> and <code>_self</code> are supported.</p>
	*/
	const char * cFrame;	
} 
WWWOpenURLParamsRec, *WWWOpenURLParams;


/** A data structure that implements a progress monitor. */
typedef void *WebProgressMonitor;

/* typedefs for function defintions */
/**	Callback functions to test a driver. 
	It tests whether a driver can support a given web browser application.
	@param driverRock IN A pointer to a driver-defined data structure provided in
			RegisterWebDriver().
			WDAppSpecifier A platform-specific data structure used to identify the web
			browser application. On Mac OS, it is a pointer to an FSRef(64 bit) or and FSSpec (32 bit).
	@param timeoutTime IN data structure. On Windows, it is a pointer to a
			string (<code>char*</code>) representing the full path of the executable
			application.
	@return <code>true</code> if the driver is compatible with the given web browser application, <code>false</code> otherwise.
*/
typedef ACCB1 ASBool (ACCB2 WDAppSupportPredicateProc)(void *driverRock, WDAppSpecifier timeoutTime);

/** Callback functions for to Follow a Link.
	
	<p>Follows and retrieves the link specified by <code>cURL</code> from the PDF document specified by
	<code>theDoc</code>. Weblink supplies the driver a fully resolved URL. The driver is solely
	responsible for launching a web browser, if it requires one. If the driver depends on an
	external web browser, the driver or the web browser is responsible for bringing that
	browser to the foreground if the link data is not displayed by the Acrobat viewer.
	For relative links, Weblink prepends a base URL if specified; otherwise, it prepends
	the appropriate portion from the current document's URL to resolve a relative link.
	Weblink automatically handles mapped links, which are links that generate different
	results based on the location of the mouse within the links. (Such links are specified
	by checking the Mapped Coordinates Link box in the Edit URL dialog box. These
	links have the <code>isMap</code> attribute). Weblink appends <code>"?"</code> to the URL, followed by the x-
	and y-coordinates of the mouse at the time the link was selected, relative to the
	upper-left corner of the link's rectangle.</p>

	@param driverRock IN A pointer to a driver-defined data structure provided in RegisterWebDriver().
	@param theDoc IN The PDF document that contains the link.
	@param cURL IN A <code>NULL</code>-terminated C string containing the URL the link points to.
	@param cFormData IN Data from a form to be sent with the URL as post data. The
			default MIME type of form data is <code>"application/x-www-formunencoded"</code>.
	@return <code>true</code> if the driver has successfully begun the process of following the link, <code>false</code> otherwise.
*/
typedef ACCB1 ASBool (ACCB2 WDFollowLinkFunctionProc)(void *driverRock, AVDoc theDoc, char *cURL, char *cFormData);

/** Callback functions for to Follow a Link with parameters.

	<p>Follows and retrieves the link specified by <code>cURL</code> from the PDF document specified by
	<code>theDoc</code>. Weblink supplies the driver a fully resolved URL. The driver is solely
	responsible for launching a web browser, if it requires one. If the driver depends on an
	external web browser, the driver or the web browser is responsible for bringing that
	browser to the foreground if the link data is not displayed by the Acrobat viewer.
	For relative links, Weblink prepends a base URL if specified; otherwise, it prepends
	the appropriate portion from the current document's URL to resolve a relative link.
	Weblink automatically handles mapped links, which are links that generate different
	results based on the location of the mouse within the links. (Such links are specified
	by checking the Mapped Coordinates Link box in the Edit URL dialog box. These
	links have the <code>isMap</code> attribute). Weblink appends <code>"?"</code> to the URL, followed by the x-
	and y-coordinates of the mouse at the time the link was selected, relative to the
	upper-left corner of the link's rectangle.	</p>
	
	@param driverRock IN A pointer to a driver-defined data structure provided in RegisterWebDriver().
	@param theDoc IN The PDF document that contains the link.
	@param cURL A <code>NULL</code>-terminated C string containing the URL the link points to.
	@param cFormData Data from a form to be sent with the URL as post data. The
				default MIME type of form data is <code>"application/x-www-formunencoded"</code>.
	@param params IN A parameter block specifying a target frame.
	
	@return <code>true</code> if the driver has successfully begun the process of following the link, <code>false</code> otherwise.
*/
typedef ACCB1 ASBool (ACCB2 WDFollowLinkWithParamsFunctionProc)(void *driverRock, AVDoc theDoc, char *cURL, char *cFormData, WWWOpenURLParams params);

/** Callback functions for driver state changes.
	
	<p>It is called whenever the state of the driver changes from inactive to current, or vice versa.</p>
	
	@param driverRock IN A pointer to a driver-defined data structure provided in RegisterWebDriver().
	@param bComing IN Tells the driver whether it should become current or relinquish control.
					If it is <code>true</code>, the driver is being requested to become the current
					Weblink driver, and it should take any action that is
					appropriate, such as installing IAC message handlers,
					opening TCP drivers, and so on. If it is <code>false</code>, the driver is being
					asked to relinquish its status as current driver and should
					take whatever action is necessary to accomplish this.
	@return <code>false</code> if the driver fails to change its state to that requested in <code>bComing</code>, <code>true</code> otherwise.
*/
typedef ACCB1 ASBool (ACCB2 WDBecomeDriverFunctionProc)(void *driverRock, ASBool bComing);


/** Callback functions for Weblink toolbar button click.
	
	<p>It is called when the user clicks on the Weblink toolbar button to switch to the browser application.</p>
	@param driverRock IN A pointer to a driver-defined data structure provided in RegisterWebDriver().
*/
typedef ACCB1 void (ACCB2 WDBringFrontFunctionProc)(void *driverRock);

/** Callback functions for a Weblink Options button click.
	
	<p>It is called when the user clicks on the Options button in the Weblink
	Preferences dialog box. If this function is <code>NULL</code>, the Options button is disabled.
	Optional: set it to <code>NULL</code> if there no options dialog.</p>
	@param driverRock IN A pointer to a driver-defined data structure provided in RegisterWebDriver().
*/
typedef ACCB1 void (ACCB2 WDOptionsFunctionProc)(void *driverRock);		

/** Callback functions to check driver transaction status 
	(Optional) Called to determine if the driver is performing a transaction or not. Weblink
	uses this to check that the driver is not busy before allowing a user to change preferences.
	@param driverRock IN A pointer to a driver-defined data structure provided in RegisterWebDriver().
	@return <code>true</code> if the driver is busy (driver-defined), <code>false</code> otherwise. The driver should
			return busy whenever it is not convenient for it to become the current driver as
			requested by \<DXRef\>WDBecomeDriverFunction.
*/
typedef ACCB1 ASBool (ACCB2 WDIsDriverBusyFunctionProc)(void *driverRock);

/**
	Tests whether a driver can support a given web browser 
	application. 
	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver(). 
	@param WDAppSpecifier A platform-specific data structure 
	used to identify the web browser application. On Mac OS, 
	it is a pointer to an FSRef (64 bit) or FSSpec (32 bit). On Windows, 
	it is a pointer to a string (<code>char*</code>) representing the full 
	path of the executable application.
	@return <code>true</code> if the driver is compatible with the given web browser 
	application, <code>false</code> otherwise. 
*/
typedef WDAppSupportPredicateProc			*WDAppSupportPredicate;
/**
	Follows and retrieves the link specified by a URL from the 
	PDF document specified by <code>theDoc</code>. Weblink supplies the driver 
	a fully resolved the URL. The driver is solely responsible 
	for launching a web browser, if it requires one. If the 
	driver depends on an external web browser, the driver or 
	the web browser is responsible for bringing that browser 
	to the foreground if the link data is not displayed by the 
	Acrobat viewer. 

	<p>For relative links, Weblink prepends a base URL if specified; 
	otherwise, it prepends the appropriate portion from the 
	current document's URL to resolve a relative link. </p>

	<p>Weblink automatically handles mapped links, that is, links 
	that generate different results based on the location of 
	the mouse within the links. (Such links are specified by 
	checking the Mapped Coordinates Link box in the Edit URL 
	dialog box. These links have the <code>isMap</code> attribute). Weblink 
	appends <code>"?"</code> to the URL, followed by the x- and y-coordinates 
	of the mouse at the time the link was selected, relative 
	to the upper-left corner of the link's rectangle. </p>

	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver(). 
	@param theDoc The PDF document that contains the link. 
	
	@param URL A <code>NULL</code>-terminated C string containing the URL 
	the link points to. 
	@param cFormData Data from a form to be sent with the 
	URL as post data. The default MIME type of form data is 
	<code>"application/x-www-form-unencoded"</code>.
	@return <code>true</code> if the driver has successfully begun the process of 
	following the link, <code>false</code> otherwise. 
*/
typedef WDFollowLinkFunctionProc			*WDFollowLinkFunction;
/**
	Follows and retrieves the link specified by a URL from the 
	PDF document specified by <code>theDoc</code>, going to a target frame. 
	Weblink supplies the driver a fully resolved the URL. The 
	driver is solely responsible for launching a web browser, 
	if it requires one. If the driver depends on an external 
	web browser, the driver or the web browser is responsible 
	for bringing that browser to the foreground if the link 
	data is not displayed by the Acrobat viewer. 

	<p>For relative links, Weblink prepends a base URL if specified; 
	otherwise, it prepends the appropriate portion from the 
	current document's URL to resolve a relative link. </p>

	<p>Weblink automatically handles mapped links, that is, links 
	that generate different results based on the location of 
	the mouse within the links. (Such links are specified by 
	checking the Mapped Coordinates Link box in the Edit URL 
	dialog box. These links have the <code>isMap</code> attribute). Weblink 
	appends <code>"?"</code> to the URL, followed by the x- and y-coordinates 
	of the mouse at the time the link was selected, relative 
	to the upper-left corner of the link's rectangle.</p>

	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver(). 
	@param theDoc The PDF document that contains the link. 
	
	@param cURL A <code>NULL</code>-terminated C string containing the 
	URL the link points to. 
	@param cFormData Data from a form to be sent with the 
	URL as post data. The default MIME type of form data is 
	<code>"application/x-www-form-unencoded"</code>. 
	@param params A parameter block specifying a target frame.
	@return <code>true</code> if the driver has successfully begun the process of 
	following the link, <code>false</code> otherwise. 

*/
typedef WDFollowLinkWithParamsFunctionProc	*WDFollowLinkWithParamsFunction;
/**
	Called whenever the state of the driver changes from inactive 
	to current, or vice versa. 
	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver(). 
	@param bComing Tells the driver whether it should become 
	current or relinquish control. If it is <code>true</code>, the driver is being 
	requested to become the current Weblink driver, and it should 
	take any action that is appropriate, such as installing 
	IAC message handlers, opening TCP drivers, and so on. If it is 
	<code>false</code>, the driver is being asked to relinquish its status 
	as current driver and should take whatever action is necessary 
	to accomplish this.
	@return <code>false</code> if the driver fails to change state to that requested 
	in <code>bComing</code>, <code>true</code> otherwise. 
*/
typedef WDBecomeDriverFunctionProc			*WDBecomeDriverFunction;
/**
	Called when the user clicks on the Weblink toolbar button 
	to switch to the browser application. 
	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver().

*/
typedef WDBringFrontFunctionProc			*WDBringFrontFunction;
/**
	(Optional) Called when the user clicks the Options button 
	in the Weblink Preferences dialog box. If this function 
	is <code>NULL</code>, the Options button is disabled. 
	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver().
*/
typedef WDOptionsFunctionProc				*WDOptionsFunction;
/**
	(Optional) Called to determine if the driver is performing 
	a transaction. Weblink uses this to check that the 
	driver is not busy (driver-defined) before allowing a user to change preferences. 
	
	<p>The driver should return busy whenever 
	it is not convenient for it to become the current driver 
	as requested by <code>WDBecomeDriverFunction()</code>. </p>

	@param driverRock A pointer to a driver-defined data structure 
	provided in RegisterWebDriver().
	@return <code>true</code> if the driver is busy, <code>false</code> otherwise. 
*/
typedef WDIsDriverBusyFunctionProc			*WDIsDriverBusyFunction;

/**	A data structure containing callbacks that implement a Weblink driver.
	@see RegisterWebDriver
*/
typedef struct {
	/** Driver version number. */
	ASUns32 WDVRev;
	/** Currently unused. */
	ASUns32 nReserved;
/** */
	WDAppSupportPredicate doYouSupport;
/** */
	WDFollowLinkFunction followLink;
/** */
	WDBecomeDriverFunction becomeDriver;
/** */
	WDBringFrontFunction bringFront;
/** */
	WDOptionsFunction options;
/** */
	WDIsDriverBusyFunction isDriverBusy;
/** */
	WDFollowLinkWithParamsFunction followLinkWithParams;
} WebDriverVector;

/* -------------------------- WebLink defines ------------------------------- */


#define WEB_LINK_HFT_LATEST_VERSION		(2L)

/* For creating selector (index to HFT) 
*/
#define PIPROC(returnType, name, params, ...)	name##_SEL,

enum 
{ 
	WLBAD_SELECTOR,
#include "WLHFTProcs.h"
	WLNUMSELECTORSplusOne 
};
#undef PIPROC

#define WebLinkNUMSELECTORS (WLNUMSELECTORSplusOne - 1)

extern HFT gWLHFT;


//typedef ACCB1 ASInt32 (ACCB2 WLCreateOrDeleteWebLinksPROTO)(ASBool bCreate, PDDoc pdd, ASInt32 nStart, ASInt32 nEnd, ProgressMonitor pm, void *vPMData, CancelProc cp, void *vCPData);
//typedef WLCreateOrDeleteWebLinksPROTO* WLCreateOrDeleteWebLinksSELPROTO;
//#define WLCreateOrDeleteWebLinks ((*((WLCreateOrDeleteWebLinksSELPROTO)(gWLHFT[WLCreateOrDeleteWebLinksSEL]))))

 
#define WLHFTNAME "WebLink"

#define Init_gWLHFT ASExtensionMgrGetHFT( ASAtomFromString(WLHFTNAME), WEB_LINK_HFT_LATEST_VERSION);
/* Define API/Function prototypes
*/
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
#include "WLHFTProcs.h"
#undef PIPROC

#define RegisterWebDriver ((*((RegisterWebDriver_SELPROTO)(gWLHFT[RegisterWebDriver_SEL]))))
#define BeginWebProgress ((*((BeginWebProgress_SELPROTO)(gWLHFT[BeginWebProgress_SEL]))))
#define UpdateWebProgress ((*((UpdateWebProgress_SELPROTO)(gWLHFT[UpdateWebProgress_SEL]))))
#define EndWebProgress ((*((EndWebProgress_SELPROTO)(gWLHFT[EndWebProgress_SEL]))))
#define GetAppSpecifier ((*((GetAppSpecifier_SELPROTO)(gWLHFT[GetAppSpecifier_SEL]))))
#define WebProgressDidCancel ((*((WebProgressDidCancel_SELPROTO)(gWLHFT[WebProgressDidCancel_SEL]))))
#define WWWOpenURL ((*((WWWOpenURL_SELPROTO)(gWLHFT[WWWOpenURL_SEL]))))
#define WLCreateOrDeleteWebLinks ((*((WLCreateOrDeleteWebLinks_SELPROTO)(gWLHFT[WLCreateOrDeleteWebLinks_SEL]))))
#define WWWOpenURLWithParams ((*((WWWOpenURLWithParams_SELPROTO)(gWLHFT[WWWOpenURLWithParams_SEL]))))

#ifdef __cplusplus
}
#endif

#endif		/************** End of WLHFT.h **************/
