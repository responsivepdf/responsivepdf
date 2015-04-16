/*************************************************************************
* WARNING: All additions to this file must go at the end of the file.
* This file is #included to build a table of function pointers (an HFT).
* All components which make use of this HFT rely on the order and
* positioning of these functions (e.g. plug-ins). Adding entries in the 
* middle of this file or modifying existing entries will cause these 
* components to break.
**************************************************************************/

/**********************************************************************


 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 2007 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 WLHFTProcs.h

*********************************************************************/

/** Register Web Driver.

	<p>Registers a driver with the Weblink plug-in. It must be called during the import, replace,
	and register phase of the plug-in initialization process of any plug-ins that want to use
	Weblink services.</p>

	@param driverName IN The driver's name. It is a <code>NULL</code>-terminated C string shown to
				the user to identify the current driver. The string is limited
				to 255 characters and is copied internally.
	@param driverRock IN A pointer to a driver-defined data structure. This value is
				passed to the driver for every driver-supplied function call.
	@param wdVec IN A pointer to a data structure of driver-supplied callback
				functions. It is not copied; therefore, the structure must be
				either statically or dynamically allocated, rather than
				automatically allocated as a local variable. It must not be
				modified, moved, or deallocated until the plug-in
				terminates within Acrobat.
	@return Registration status. <code>true</code> if the registration was successful, <code>false</code> otherwise. Failure
			occurs if there is insufficient memory or the version number in <code>wdVec</code> is incompatible
			with the Weblink plug-in.

*/
PIPROC(ASBool, RegisterWebDriver, (const char *driverName, void *driverRock, WebDriverVector *wdVec), driverName, driverRock, wdVec)

/** Creates a new Weblink progress.
	<p>It creates a new Weblink progress monitor to provide feedback during long operations.
	Current web browsers follow links asynchronously and use BeginWebProgress(),
	UpdateWebProgress(), and EndWebProgress() to assure a user that a request is making progress.</p>
	
	@param message IN Message text. A <code>NULL</code>-terminated C string that represents a
					message to display with the progress monitor.
	@param flags IN Possible flag options for the progress monitor. There are two
					flags defined (in WLHft.h):

					<TABLE rules="all" cellspacing="1">
					<TR><TH>Flag option</TH><TH>Description</TH></TR>
					<TR><TD><code>PROGRESS_HAS_METER</code></TD><TD>Put a thermometer-style meter in the progress display.</TD></TR>
					<TR><TD><code>PROGRESS_HAS_CANCEL</code></TD><TD>Add either a Cancel button or a message directing the user how to abort the operation.</TD></TR>
					</TABLE>

	@param timeoutTime IN Timeout period. The amount of time in seconds before the
					progress monitor indicates that progress is not being made.
	@return Monitor creation status. A non-<code>NULL</code> value if the monitor's creation was successful,
			<code>NULL</code> otherwise. In the current implementation, there can be at most one progress monitor.
*/
PIPROC(WebProgressMonitor, BeginWebProgress, (char *message, ASUns32 flags, ASInt32 timeoutTime), message, flags, timeoutTime)


/** Updates Web Progress.
	<p>It updates the state of the current progress monitor.</p>

	@param	progMon IN The current progress monitor returned from BeginWebProgress().
	@param	message IN Message text. If non-<code>NULL</code>, the text displayed is changed to
			that represented by <code>message</code>. If <code>message</code> is <code>NULL</code>, the text is not changed.
	@param from IN The lower bound of a sub-range between <code>0</code> and <code>outOf</code> to
			highlight: <code>from</code> and <code>to</code> are the lower and upper bounds of
			a subrange between <code>0</code> and <code>outOf</code> to highlight. Typically the
			lower bound, <code>from</code>, is zero, but a driver may wish to
			indicate the progress of an operation that has no known magnitude
			as a priority. It could do so with a <i>chaser light</i>
			display by cycling the lower bound, <code>from</code>, through the range
			between <code>0</code> and <code>outOf - 1</code>, and defining the upper bound,
			<code>to</code>, as <code>from + 1</code>.
	@param	to IN The upper bound of a sub-range between <code>0</code> and <code>outOf</code> to highlight.
	@param	outOf IN If <code>progMon</code> was created with the <code>PROGRESS_HAS_METER</code>
			flag, the <code>from</code>, <code>to</code>, and <code>outOf</code> arguments are used to
			change the state of the bar. The range of the meter is
			defined from <code>0</code> to <code>outOf</code>.
	@param	timeoutTime IN (Optional) The new timeout period in seconds. If it is non-zero, a
			new timeout is set.
	
	@return Update status. <code>true</code> if the update was successful, <code>false</code> if the monitor timed out or
		the user canceled the operation. The latter case only happens when the progress
		monitor was created with the <code>PROGRESS_HAS_CANCEL</code> flag in BeginWebProgress().
 
*/
PIPROC(ASBool, UpdateWebProgress, (WebProgressMonitor progMon, char *message, ASInt32 from, ASInt32 to, ASInt32 outOf, ASInt32 timeoutTime),
	   progMon, message, from, to, outOf, timeoutTime)
/** Ends Web Progress.
	<p>Terminates the current progress monitor.</p>
	@param progMon IN The current progress monitor.
*/
PIPROC(void, EndWebProgress, (WebProgressMonitor progMon), progMon)


/** Get App Specifier.
	<p>Obtains a platform-specific structure specifying the application the user has chosen
	as the web browser.</p>

	@param promptUser IN <code>true</code> if there is no current web browser and the user is
						prompted to choose one, <code>false</code> otherwise.
	@return A pointer to a platform-specific data structure that specifies the web browser. On the
			Mac OS, it is a pointer to an FSSpec. On Windows and UNIX platforms,
			it is a pointer to a string (<code>char*</code>) representing the full path of the executable
			application.
*/
PIPROC(WDAppSpecifier, GetAppSpecifier, (ASBool promptUser), promptUser)

/** Checks if the Cancel button was clicked.
	<p>It tests whether the user clicked the Cancel button in the progress monitor dialog.</p>

	@param progMon IN The current progress monitor.
	@return <code>true</code> if the progress monitor has been canceled, <code>false</code> otherwise.
*/
PIPROC(ASBool, WebProgressDidCancel, (WebProgressMonitor progMon), progMon)

/** Opens a new URL.
	<p>Asks Weblink to follow the specified URL. If the URL specifies a PDF document,
	it opens it in a new window (an AVDoc view).  It is used by other plug-ins that wish to start a download.</p>

	@param avd IN If specified, it is the AVDoc that contains the source of the URL.
	@param cURL IN The URL to be opened.
	@param cFormData IN The data for a form to be posted. 
	@return <code>true</code> if the request succeeded, <code>false</code> otherwise.
*/
PIPROC(ASBool, WWWOpenURL, (AVDoc avd, const char *cURL, const char *cFormData), avd, cURL, cFormData)


/** Creates Or Deletes WebLinks
	<p>Used by other plug-ins that want to create or delete weblinks in a document.</p>
	<p>Adobe Reader does not, by default, create or delete items in a PDF document.</p>
	@param bCreate IN A boolean to indicate whether links should be created. If it is <code>false</code>, links will be deleted. 
	@param pdd IN The PDDoc in which to create or delete weblinks.
	@param nStart IN The starting page
	@param nEnd IN The ending page
	@param pm IN The current progress monitor.
	@param vPMData IN The data to be passed to the progress monitor.
	@param cp IN The cancel proc
	@param vCPData IN The data to be passed to the cancel proc. 
	@return The number of web links created or deleted. 
	@product_exclude RDR
*/
PIPROC(ASInt32, WLCreateOrDeleteWebLinks, (ASBool bCreate, PDDoc pdd, ASInt32 nStart, ASInt32 nEnd, ProgressMonitor pm, void *vPMData, CancelProc cp, void *vCPData), 
	   bCreate, pdd, nStart, nEnd, pm, vPMData, cp, vCPData)


/** Opens a new URL With Parameters .
	<p>Asks Weblink to follow a URL, specifying a target frame. If the URL specifies a PDF
	document, it opens it in a new window (an AVDoc view). It is used by other plug-ins that wish to start a download and specify a target frame.</p>
	@param avd If specified, it is the AVDoc that contains the source of the URL.
	@param cURL The URL to be opened.
	@param cFormData The data for a form to be posted.
	@param params The parameter block specifying the name of the frame.	
	@return <code>true</code> if the request succeeded, <code>false</code> otherwise.
*/
PIPROC(ASBool, WWWOpenURLWithParams, (AVDoc avd, const char *cURL, const char *cFormData, WWWOpenURLParams params), avd, cURL, cFormData, params)




