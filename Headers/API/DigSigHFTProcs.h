/*************************************************************************
* WARNING: All additions to this file must go at the end of the file.
* This file is #included to build a table of function pointers (an HFT).
* All components which make use of this HFT rely on the order and
* positioning of these functions (e.g. plug-ins). Adding entries in the 
* middle of this file or modifying existing entries will cause these 
* components to break.
**************************************************************************/

/*************************************************************************
 * DigSigHFTProcs.h
 *
 * Copyright (c) 2007 Adobe Systems Inc. All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the
 * property of Adobe Systems Incorporated and its suppliers, if any.
 * The intellectual and technical concepts contained herein are
 * proprietary to Adobe Systems Incorporated and its suppliers and may
 * be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Adobe permits you to
 * use, modify, and distribute this file in accordance with the terms
 * of the Adobe license agreement accompanying it. If you have
 * received this file from a source other than Adobe, then your use,
 * modification, or distribution of it requires the prior written
 * permission of Adobe.
 *
 * Description:
 *
 * Digital Signature interface for Acrobat Digital Signature handlers.
 * Handlers can register as DigSig handlers to provide digital
 * signature services.  Handlers can also call back into the DigSigHFT
 * for various services.
 *
 * 10-May-2007 - Created
 ************************************************************************/

/** Procs below are provided in version 0x00010000 */
/**
	Registers a signing method plug-in. A signing plug-in must 
	call this method before making any signatures. This object 
	should not be destroyed until after it is un-registered or 
	until exit. 
	@param owner The handler plug-in identifier, assigned 
	on initialization. 
	@param digSigHandler A structure specifying the name of 
	the filter and the functions to call to create and validate 
	signatures.
	@see DigSigUnregisterFilter 
*/
PIPROC(void, DigSigRegisterFilter, 
	(ExtensionID owner, DigSigHandler digSigHandler), owner, digSigHandler)


/**
	Gets the number of bytes in an ASFile. It serves as a wrapper 
	for the ASFileGetEOF() method. 
	@param asFile The ASFile whose length is obtained.
	@return The number of bytes in the ASFile, or <code>0</code> if an error is encountered. 
	
	@see DigSigFileSetPos 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray 
	@see DigSigOverwriteHexstring 
	@see DigSigOverwriteBytes 
*/
PIPROC(ASInt32, DigSigFileGetEOF, 
	(ASFile asFile), asFile)

/**
	Reopens an ASFile for reading and sets the file position. 
	
	@param asFile The ASFile to position. 
	@param pos The byte offset to a position in <code>asFile</code>.
	@see DigSigFileGetEOF 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray 
	@see DigSigOverwriteHexstring 
	@see DigSigOverwriteBytes 
*/
PIPROC(void, DigSigFileSetPos, 
	(ASFile asFile, ASInt32 pos), asFile, pos)

/**
	Reads from an ASFile. This is a wrapper function for the 
	ASFileRead() method. 
	@param asFile The ASFile to read. 
	@param p A pointer to a buffer. 
	@param count The number of bytes to read into the buffer.
	@return The number of bytes read, or <code>0</code> if unsuccessful. 
	@see DigSigFileGetEOF 
	@see DigSigFileSetPos 
	@see DigSigOverwriteIntArray 
	@see DigSigOverwriteHexstring 
	@see DigSigOverwriteBytes 
*/
PIPROC(ASInt32, DigSigFileRead, 
	(ASFile asFile, char *p, ASInt32 count), asFile, p, count)

/**
	Overwrites part of <code>asFile</code> with an integer array. It reopens 
	the file for write, positions to the specified place, formats 
	the array as characters, and writes. This method is used 
	to overwrite the <code>/ByteRange</code> entry in the signature dictionary. 
	
	@param asFile The ASFile to write to. 
	@param digSigOffset A structure specifying the byte position 
	and size to overwrite:
	<ul>
	<li>Writes padding blanks to the file if formatted length is less than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is longer than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is greater than <code>8200</code> bytes.</li>
	</ul>
	@param cosObj The Cos string to be written.
	@return The number of bytes written. 
	@see DigSigCosObjOverwrite 
	@see DigSigFileGetEOF 
	@see DigSigFileSetPos 
	@see DigSigFileRead 
	@see DigSigOverwriteHexstring 
	@see DigSigOverwriteBytes 
*/
PIPROC(ASInt32, DigSigOverwriteIntArray, 
	(ASFile asFile, const DigSigOffset digSigOffset, const CosObj cosObj), asFile, digSigOffset, cosObj)

/**
	Overwrites part of a file with a hex string. It reopens the 
	file for write, positions to the specified location, formats 
	the string as characters, and writes. This method is used 
	to overwrite the <code>/Contents</code> entry in the signature dictionary. 
	
	@param asFile The ASFile to write to. 
	@param digSigOffset A structure specifying the byte position 
	and size to overwrite:
	<ul>
	<li>Writes padding blanks to the file if formatted length is less than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is longer than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is greater than <code>8200</code> bytes.</li>
	</ul>
	@param cosObj The Cos string to be written.
	@return The number of bytes written. 
	@see DigSigCosObjOverwrite 
	@see DigSigFileGetEOF 
	@see DigSigFileSetPos 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray 
	@see DigSigOverwriteBytes 
*/
PIPROC(ASInt32, DigSigOverwriteHexstring, 
	(ASFile asFile, const DigSigOffset digSigOffset, const CosObj cosObj), asFile, digSigOffset, cosObj)

/**
	Overwrites any or all entries in a signature dictionary. 
	It reopens the file for write, positions to the specified place, 
	and writes exactly the number of bytes specified in <code>digSigOffset</code>. 
	@param asFile The ASFile to write to. 
	@param digSigOffset A structure specifying the byte position 
	and size to overwrite. 
	@param p A byte string to be written. It must be in the correct 
	format, given the type of entry as defined in Section 8.7 
	in the PDF Reference.
	@return The number of bytes written, or <code>0</code> if unsuccessful. 
	@see DigSigCosObjOverwrite 
	@see DigSigFileGetEOF 
	@see DigSigFileSetPos 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray 
	@see DigSigOverwriteHexstring 
	
	@note To overwrite a text string entry, such as <code>/Reason</code>, 
	the string must be in the format <code>"< xxx >"</code>, not <code>"xxx"</code>. 
*/
PIPROC(ASInt32, DigSigOverwriteBytes, 
	(ASFile asFile, const DigSigOffset digSigOffset, const char *p), asFile, digSigOffset, p)


/**
	Calculates the MD5 hash function over a set of byte ranges 
	in a file. 
	@param asFile The file over which the hash function is 
	calculated. 
	@param byteRange An array of pairs of integers specifying 
	the byte offset and length of one or more subsets of the file. 
	The hash function is calculated over all these subsets, 
	concatenated in order. 
	@param md5hash A pointer to a buffer that receives the 
	16 byte hash value.
	@return The MD5 hash function over a set of byte ranges in <code>asFile</code>. 
	It also returns the total number of bytes over which the hash 
	is calculated. It returns <code>0</code> if the byte range array has an 
	odd number of elements or if it is unsuccessful. 
*/
PIPROC(ASInt32, DigSigMD5ByteRange,  
	(ASFile asFile, CosObj byteRange, char *md5hash), asFile,byteRange, md5hash)

/**
	Updates the signature panel, if any, associated with <code>pdDoc</code>. 
	
	@param pdDoc The document whose panel is to be updated.
	It verifies a digital signature. 
	@param pdDoc The document. 
*/
PIPROC(void, DigSigUpdatePanel, 
	(PDDoc pdDoc), pdDoc)


/**
	Converts a byte string to a PDF hex string. 
	@param byteP A pointer to the byte string. 
	@param hexP (Filled by the method) A pointer to an output 
	buffer to hold the hex string. It must be at least <code>(length * 2) + 3</code> bytes. 
	The string begins with <code>"\<"</code> and ends with 
	<code>"\>"</code>, followed by a <code>NULL</code> character. For example, the two 
	byte string <code>"A/"</code> is converted to <code>"\<412f\>\\0"</code>. 
	@param length The length of the byte string in bytes.
	@see DigSigHexToByte 
*/
PIPROC(void, DigSigByteToHex, 
	(unsigned char * byteP, unsigned char * hexP, ASInt32 length), byteP, hexP, length)

/**
	<p>Converts a PDF hex string to a byte string. For example, 
	the 6 byte string <code>"&lt;412f&gt;"</code> converts to the 2-byte string <code>"(A/)"</code>.</p> 
	
	<p>The first byte of the hex string is ignored. The last byte 
	of an even length hex string is ignored. </p>

	<p>Middle bytes outside the ranges <code>0-9</code>, <code>a-f</code>, and <code>A-F</code> are treated 
	as <code>0</code>. Pairs of middle bytes are converted to byte values 
	<code>0-255</code> and stored in the output buffer.</p> 
	@param hexP Pointer to the hex string. The string must 
	begin with <code>'&lt;'</code> and end with <code>'&gt;'</code>, optionally followed by 
	a <code>NULL</code> character. 
	@param byteP (Filled by the method) A pointer to an output 
	buffer to hold the byte string. It must be at least <code>(length - 2) / 2</code> bytes long. 
	@param length The length of the hex string in bytes, not including 
	any trailing <code>NULL</code> character (that is, <code>ASstrnlen_safe(hexP)</code>).
	@see DigSigByteToHex 
*/
PIPROC(void, DigSigHexToByte, 
	(unsigned char * hexP, unsigned char * byteP, ASInt32 length), hexP, byteP, length)

/** Signs and saves a document, using the specified field and signing method. If
	<code>sigField</code> is <code>NULL</code>, makes a field of size 0x0 points.
	@param pdDoc IN/OUT  The document to be signed.
	@param sigField IN/OUT  The field to be signed or CosNull.
	@param filterKey IN/OUT  The signing method to use.
*/
PIPROC(void, DigSigSignDoc, 
	(PDDoc pdDoc, CosObj sigField, ASAtom filterKey), pdDoc, sigField, filterKey)

/* Return an XObject that is created and stored in the PDF file.
   Bounding box of XObject is 100 x 100.
   dsXObjType must be one of DSBlankXObj, DSUnknownXObj or DSInvalidXObj */
/**
	Gets a Cos XObject for one of the standard signature graphics: 
	blank, question mark, and cross. 

	<p>It creates an AcroForm dictionary if none exists in the document, 
	makes a Default Resources (DR) dictionary if none exists, 
	creates an XObject dictionary if none exists, and creates 
	three standard XObjects: DSBlankXObj, DSUnknownXObj, and 
	DSInvalidXObj if they do not exist. These objects may be 
	used to modify the appearance of a digital signature. Each 
	object has a bounding box of 100 x 100 points and an identity 
	transformation matrix. </p>
	@param cosDoc The document in which to include the standard 
	XObject. 
	@param dsXObjType The type of object to get. 
	@return The CosObj of the desired type, or CosNewNull if 
	unsuccessful. 
*/
PIPROC(CosObj, DigSigGetStdXObj, 
	(CosDoc cosDoc, DSXObjType dsXObjType), cosDoc, dsXObjType)

/** Causes the signature to be redrawn.
	@param pdAnnot IN/OUT  The annotation the user clicked on or tabbed into.
	@param avPV IN/OUT  The page view that contains the annotation.
	@param bIsSelected IN/OUT  <code>true</code> if the annotation is selected, <code>false</code> otherwise.
	@see DigSigHexToByte
	@see DigSigRightClick
*/
PIPROC(void, DigSigDraw, 
	(PDAnnot pdAnnot, AVPageView avPV, ASBool bIsSelected), pdAnnot, avPV, bIsSelected)

/**
	The AcroForm plug-in calls this method when the user tabs 
	to a signature annotation and activates it by pressing the 
	space bar or Enter key, which is equivalent to a left-mouse 
	click. The parameters parallel those of the AVAnnotHandlerDoKeyDownProc() 
	callback. If the key pressed is an ASCII <code>\<CR\></code>, this method 
	selects the annotation. 
	@param pdAnnot The annotation the user clicked on. 
	@param avPV The current page view. 
	@param nKey The key pressed by the user. 
	@param nFlags Indicates which modifier keys are pressed, 
	if any. It must be an OR of the Modifier Keys values, which 
	are the following:
	<ul>
	<li>AV_COMMAND</li>
	<li>AV_OPTION</li>
	<li>AV_CONTROL </li>
	<li>AV_SHIFT </li>
	</ul>
	@see DigSigDraw 
	@see DigSigClick 
	@see DigSigRightClick 
*/
PIPROC(void, DigSigKeyDown, 
	(PDAnnot pdAnnot, AVPageView avPV, ASUns16 nKey, ASInt16 nFlags), pdAnnot, avPV, nKey, nFlags)

/**
	The AcroForm plug-in calls this method when a user left-clicks 
	inside a signature annotation. 
	@param pdAnnot The annotation the user clicked on. 
	@param avPV The page view that contains the annotation. 
	
	@param nX The x-coordinate of the mouse click, specified 
	in device space coordinates. 
	@param nY The y-coordinate of the mouse click, specified 
	in device space coordinates. 
	@param nFlags Indicates which modifier keys are pressed, 
	if any. It must be an OR of the Modifier Keys values, which 
	are the following:
	<ul>
	<li>AV_COMMAND</li>
	<li>AV_OPTION</li>
	<li>AV_CONTROL </li>
	<li>AV_SHIFT </li>
	</ul>
	@param nClicks The number of clicks.
	@see DigSigDraw 
	@see DigSigHexToByte 
	@see DigSigRightClick 
*/
PIPROC(void, DigSigClick, 
	(PDAnnot pdAnnot, AVPageView avPV, ASInt16 nX, ASInt16 nY, ASInt16 nFlags, ASInt16 nClicks),
	pdAnnot, avPV, nX, nY, nFlags, nClicks)


/**
	Invokes the signature-panel pull-right menu and allows the 
	user to select an action. 
	@param pdAnnot The annotation the user clicked on. 
	@param avPV The page view the annotation is within. 
	@param nX The x-coordinate of the mouse click, specified 
	in device space coordinates. 
	@param nY The y-coordinate of the mouse click, specified 
	in device space coordinates 
	@param nFlags Indicates which modifier keys are pressed, 
	if any. It must be an OR of the Modifier Keys values, which 
	are the following:
	<ul>
	<li>AV_COMMAND</li>
	<li>AV_OPTION</li>
	<li>AV_CONTROL </li>
	<li>AV_SHIFT </li>
	</ul>
	@param nClicks The number of clicks.
	@see DigSigDraw 
	@see DigSigHexToByte 
	@see DigSigClick 
*/
PIPROC(void, DigSigRightClick, 
	(PDAnnot pdAnnot, AVPageView avPV, ASInt16 nX, ASInt16 nY, ASInt16 nFlags, ASInt16 nClicks),
	pdAnnot, avPV, nX, nY, nFlags, nClicks)

/**
	Gets a character string that is suitable as the field name 
	for a new signature field. This is guaranteed not to duplicate 
	an existing field name. Typically, this name would be of 
	the form <code>XXXXnnn</code>, where <code>XXXX</code> is the word <code>'signature'</code> in 
	a local Latin-alphabet language, and <code>nnn</code> is a unique integer. 
	
	@param cosDoc The document that will contain the new field.
	@return The unique field name string. 
*/
PIPROC(char *, DigSigGetUniqueTitle, 
	(CosDoc cosDoc), cosDoc)

/**
	Recalculates the number of signature fields and redraws 
	the signature panel after any signature is deleted. 

	<p>It is called by the AcroForm plug-in or any agent that deletes 
	a signature field. </p>
	@param pdDoc The document that contains a signature field.
	@see DigSigAddedSig 
	@see DigSigDeletedSigEx 
*/
PIPROC(void, DigSigDeletedSig, 
	(PDDoc pdDoc), pdDoc)

/**
	Recalculates the number of signature fields and redraws 
	the signature panel after any signature is added. 

	<p>It is called by the AcroForm plug-in or any agent that adds a 
	signature field. </p>
	@param pdDoc The document that contains the signature 
	field.
	@see DigSigAddedSigEx 
	@see DigSigDeletedSig 
*/
PIPROC(void, DigSigAddedSig, 
	(PDDoc pdDoc), pdDoc)

/**
	Compares the pages of two documents, producing a third document 
	of the differences. 
	
	@param docA The first document to compare. 
	@param docB The second document to compare. 
	@param insertDiffs Not used.
	@return <code>true</code> if the pages of the documents are identical, <code>false</code> 
	otherwise. 
	@see DigSigCompareWords  

	@note Superseded by DigSigComparePagesEx() in Acrobat 6.0. 
*/
PIPROC(ASBool, DigSigComparePages, 
	(PDDoc docA, PDDoc docB, ASBool insertDiffs), docA, docB, insertDiffs)


/**
	Compares the words of two documents, producing a third document 
	of the differences. 
	
	@param docA The first document being compared. 
	@param docB The second document being compared. 
	@param iUseFonts If <code>true</code>, the font name, size, and color 
	of each character in a word are considered when matching 
	against other words. If <code>false</code>, these attributes are ignored.
	@return <code>true</code> if the words of the documents are identical, <code>false</code> 
	otherwise. 
	@see DigSigComparePages 
	@see DigSigCompareWordsAndFontsRecent 
	@see DigSigCompareWordsEx 
	@see DigSigCompareWordsRecent 

	@note Superseded by DigSigCompareWordsEx() in Acrobat 6.0. 
*/
PIPROC(ASBool, DigSigCompareWords, 
	(PDDoc docA, PDDoc docB, ASBool iUseFonts), docA, docB, iUseFonts)

/**
	Compares the words of two documents, producing a third document 
	of the differences. 
	
	@param docA The first document being compared. 
	@param docB The second document being compared. 
	@param iUseFonts If <code>true</code>, the font name, size, and color 
	of each character in a word are considered when matching 
	against other words. If <code>false</code>, these attributes are ignored.
	@return <code>true</code> if the words of the documents are identical, <code>false</code> 
	otherwise. 
	@see DigSigComparePages 
	@see DigSigCompareWords 
	@see DigSigCompareWordsAndFontsRecent 
	@see DigSigCompareWordsEx 

	@note Superseded by DigSigCompareWordsEx() in Acrobat 6.0. 
*/
PIPROC(void, DigSigCompareWordsRecent, 
	(PDDoc docA, PDDoc docB, ASBool iUseFonts), docA, docB, iUseFonts)

/**
	Opens the DigSig's property dialog box. 
	@param avDoc The document that contained the signature 
	field. 
	@param sigField The signature field of the document.
*/
PIPROC(void, DigSigDoProperties, 
	(AVDoc avDoc, CosObj sigField), avDoc, sigField)

/**
	Compares the words of two documents, taking into account 
	possible font changes, and produces a third document of 
	the differences. 
	
	@param docA The first document being compared. 
	@param docB The second document being compared. 
	@param iUseFonts If <code>true</code>, the font name, size, and color 
	of each character in a word are considered when matching 
	against other words. If <code>false</code>, these attributes are ignored.
	@return <code>true</code> if the words of the documents are identical, <code>false</code> 
	otherwise. 
	@see DigSigComparePages 
	@see DigSigCompareWords 
	@see DigSigCompareWordsEx 
	@see DigSigCompareWordsRecent 

	@note Superseded by DigSigCompareWordsEx() in Acrobat 6.0. 
*/
PIPROC(void, DigSigCompareWordsAndFontsRecent, 
	(PDDoc docA, PDDoc docB, ASBool iUseFonts), docA, docB, iUseFonts)

/*************************************************************************
 * New routines for Acrobat 5.0
 ************************************************************************/

/**
	Creates a new temporary file that corresponds to the state 
	of the file after the specified signature was applied. 
	@param pdDoc The document that contained the signature 
	field. 
	@param sigField The signature field of the document.
*/
PIPROC(void, DigSigRollbackToSig, 
	(PDDoc pdDoc, CosObj sigField), pdDoc, sigField)


/**
	Enumerates the signature fields (signed and unsigned) in 
	the file. 
	@param pdDoc The document that contains the signature 
	field. 
	@param proc The procedure to call once for each existing 
	signature. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see DigSigEnumProc 
*/
PIPROC(void, DigSigEnumSignatures,  ( PDDoc pdDoc, DigSigEnumProc proc, void *clientData ), pdDoc, proc, clientData )

/**
	Tests whether a document has been modified since being signed 
	with the specified signature. 
	@param doc The document containing the signature field. 
	@param sigField The signature field.
	@return ASBool <code>true</code> if the document has been modified, <code>false</code> otherwise. 
	
*/
PIPROC(ASBool, DigSigDocModifiedAfterSig,  ( PDDoc doc, CosObj sigField ), doc, sigField)

/**
	Returns a new XObject with the specified bounding box. Unlike 
	the XObject returned by DigSigGetStdXObj(), DigSig does not 
	attach the XObject returned by this function to the CosDoc. 
	
	@param cosDoc The document containing the new object. 	
	@param pBBoxRec A pointer to the desired bounding box. 
	@param dsXObjType The type of object to create. 
	@return A CosObj containing the new XObject form, or CosNewNull 
	if unsuccessful. 
	@see DigSigGetStdXObj 
*/
PIPROC(CosObj, DigSigCreateStdXObj, 
	( const CosDoc cosDoc, const ASFixedRect* const pBBoxRec, DSXObjType dsXObjType),
	cosDoc, pBBoxRec, dsXObjType)

/**
	Creates a stream that is composed of either four or five layers:
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Layer</TH><TH>Description</TH></TR>
	<TR><TD><code>n0</code></TD><TD>Background, inherited from the form annotation background.</TD></TR>
	<TR><TD><code>n1</code></TD><TD>Middle, question mark or equivalent (uses the default if the layer <code>1</code> XObject is CosNull).</TD></TR>
	<TR><TD><code>n2</code></TD><TD>Main, text and appearance (must be provided).</TD></TR>
	<TR><TD><code>n3</code></TD><TD>Top, blank or X (uses the default if <code>layer1XObject</code> is CosNull).</TD></TR>
	<TR><TD><code>nN</code></TD><TD>(Optional) Very top layer, used for text showing the validity state (none if CosNull).</TD></TR>
	</TABLE>

	@note Superseded by DigSigAPCreateLayeredStreamEx() in Acrobat 6.0.
*/
PIPROC(CosObj, DSAPCreateLayeredStream,  ( const CosDoc cosDoc, 
							const CosObj layer1XObject, ASFixedMatrixP layer1Matrix,
							const CosObj layer2XObject, ASFixedMatrixP layer2Matrix,
							const CosObj layer3XObject, ASFixedMatrixP layer3Matrix,
							const CosObj layerNXObject, ASFixedMatrixP layerNMatrix, ASInt16 layerNNum,
							AFPDWidgetBorder border, 
							PDColorValue cBorder, PDColorValue cBackGnd,
							ASFixed width, ASFixed height,
							PDRotate pdr ),
							cosDoc, layer1XObject, layer1Matrix, layer2XObject, layer2Matrix,
							layer3XObject, layer3Matrix, layerNXObject, layerNMatrix, layerNNum,
							border, cBorder, cBackGnd, width, height, pdr)

/**
	Legacy procedure for backwards compatibility.
*/
PIPROC(CosObj, DSAPXObjectFromXObjListObsolete,  ( CosDoc cosDoc,
						const ASFixedRect* const bbox,
						DSAPXObjEntry objEntry,
						TextAppearanceP ta,
						AFPDWidgetBorder border,
						ASBool bMerge ),
						cosDoc, bbox, objEntry, ta, border, bMerge)

/** 
	Takes text for a stream <code>logoStr</code> with bounding box <code>logoBBox</code> and fits it precisely to
	<code>bbox</code>. It performs uniform x and y scaling, and x-y translation. It can raise an exception. This
	method might throw an exception, and should be wrapped in a DURING/HANDLER block.
	@param cosDoc The document.
	@param logoStr The stream containing the text.
	@param logoStrSize The length of the logo string, or <code>0</code> to calculate the length automatically.
	@param logoBBox The bounding box for <code>logoStr</code>.
	@param bbox The bounding rectangle of the result.
	@return A Cos object XObject that contains the logo.
	@see DigSigAPCreateLayeredStream
	@see DigSigAPXObjectFromXObjList
*/
PIPROC(CosObj, DSAPXObjectFromLogo,  ( const CosDoc cosDoc, 
						   const char* logoStr, const ASInt32 logoStrSize,
						   const ASFixedRect* const logoBBox,
						   const ASFixedRect* const bbox ),
						   cosDoc, logoStr, logoStrSize,logoBBox,bbox)

/** Create a new XObject that consists of vertically stacked blocks of text,
	where each block is auto-sized to fit its own bounding box.
*/
PIPROC(CosObj, DSAPCreateCompositeTextXObj,  ( const CosDoc cosDoc, 
							const DSAPTextEntry inText,
							const ASFixedRect* const bbox,	/* already compensated for rotation and position within annot*/
							const CosObj sigField, const CosObj sigAnnot ),
							cosDoc, inText, bbox, sigField, sigAnnot )

/*
** New routines for Acrobat 6.0
*/

/**
	Recalculates the number of signature fields and redraws 
	the signature panel after a specified signature is deleted. 
	
	<p>This version, added in Acrobat 6.0, is more efficient than 
	DigSigDeletedSig(), but requires that you specify the signature 
	field that is being deleted. </p>
	@param pdDoc The document that contained the signature 
	field. 
	@param cosField The signature field that was deleted.
	@see DigSigAddedSigEx 
	@see DigSigDeletedSig 	
*/
PIPROC(void, DigSigDeletedSigEx, 
	(PDDoc pdDoc, CosObj cosField), pdDoc, cosField)

/**
	Recalculates the number of signature fields and redraws 
	the signature panel after a specified signature field is 
	added. 

	<p>This version, added in Acrobat 6.0, is more efficient than 
	DigSigAddedSig(), but requires that you specify the signature 
	field that is being added. </p>
	@param pdDoc The document that contains the signature 
	field. 
	@param cosField The signature field that was added.
	@see DigSigAddedSig 
	@see DigSigDeletedSigEx 
*/
PIPROC(void, DigSigAddedSigEx, 
	(PDDoc pdDoc, CosObj cosField), pdDoc, cosField)

/************************************************************************************
 * New routines for Acrobat 6.0
 ***********************************************************************************/


/**
	Begins the process of creating a new signature reference 
	dictionary containing an object digest. The caller fills 
	in the values of the refParams structure. 

	<p>In this method, no persistent changes are made to the document; 
	therefore, it is safe to cancel the creation of the reference 
	dictionary without any cleanup. To save the file, DigSigCommitSigRefDict() 
	should be called next. </p>
	@param refParams A structure containing information about 
	the signature reference dictionary; it must be filled in by 
	the caller. 
	@param errParams (Filled by the method) A structure containing 
	information about exceptions that occurred.
	@return <code>kDSTrue</code> on success, <code>kDSFalse</code> on parameter errors. 
	<code>kDSException</code> means an exception occurred; information can 
	be found in <code>errParams</code>. 
	@see DigSigClearSigRefDict 
	@see DigSigCommitSigRefDict 
	@see DigSigFinishSigRefDict 
	@see DigSigVerifySigRefDict 
*/
PIPROC(DSRetCode, DigSigNewSigRefDict, 
	( DSSigRefDictParams refParams, DSSigRefDictErrParams errParams ), 	refParams, errParams)

/**
	Adds a signature reference dictionary to the document and 
	saves the document. 

	<p>This method uses the information that was provided in the 
	DSSigRefDictErrParams parameter block during the call to <code>DigSigNewSigRefDict.transformMethod()</code>, 
	and <code>sigDict</code> should match the values provided at that time. </p>
	
	<p>After this operation, some of the values in the reference 
	dictionary are still dummy values, including <code>DigestValue</code> 
	and <code>DigestLocation</code> (see Section 8.7, <i>Digital Signatures</i> 
	in the <i>PDF Reference</i> for more information). DigSigFinishSigRefDict() 
	should be called next to fill in these values. </p>

	<p>If signing is cancelled after this operation, DigSigClearSigRefDict() 
	should be called to remove all references to the reference 
	dictionary from the document. </p>
	@param transformMethod The transform method. 
	@param sigDict The signature dictionary that contains 
	the signature reference dictionary. 
	@param pOutRefDict (Filled by the method) A pointer to the 
	committed signature reference dictionary.
	@return <code>kDSTrue</code> on success, <code>kDSFalse</code> on parameter error, <code>kDSException</code> 
	for all other errors. 
	@see DigSigClearSigRefDict 
	@see DigSigFinishSigRefDict 
	@see DigSigNewSigRefDict 
	@see DigSigVerifySigRefDict 
*/
PIPROC(DSRetCode, DigSigCommitSigRefDict, 
    ( ASAtom transformMethod, CosObj sigDict, CosObj *pOutRefDict ), transformMethod, sigDict, pOutRefDict )

/**
	Computes the digest value and stores it in the reference 
	dictionary. It should be called after DigSigCommitSigRefDict(). 
	
	@param transformMethod The transform method used to calculate 
	the digest. It must match what was originally specified in DigSigNewSigRefDict(). 
	
	@param sigDict The signature dictionary that contains 
	the signature reference dictionary. 
	@param refDict The reference dictionary returned from 
	the call to DigSigCommitSigRefDict(). 
	@param errParams A structure containing information about 
	an exception. 
	@return <code>kDSTrue</code> on success, <code>kDSFalse</code> on parameter error. <code>kDSException</code> 
	means an exception, and the information about it can be 
	found in <code>errParams</code>. 
	@see DigSigClearSigRefDict 
	@see DigSigCommitSigRefDict 
	@see DigSigNewSigRefDict 
	@see DigSigVerifySigRefDict 
*/
PIPROC(DSRetCode, DigSigFinishSigRefDict, 
    ( ASAtom transformMethod, CosObj sigDict, CosObj refDict, DSSigRefDictErrParams errParams ), transformMethod, sigDict, refDict, errParams )

/**
	Verifies an object signature stored in a signature reference 
	dictionary. It involves computing the object digest using 
	the transform method and comparing it to the digest value 
	stored in the reference dictionary. 
	@param transformMethod The transform method used to calculate 
	the signature. It must match the one stored in <code>refDict</code>. 
	@param sigDict The signature dictionary that contains 
	the signature reference dictionary. 
	@param refDict The signature reference dictionary that 
	was returned from a call to DigSigCommitSigRefDict(). 
	@param errParams A structure containing information about 
	an exception.
	@return <code>kDSTrue</code> on success, <code>kDSFalse</code> on parameter error. <code>kDSException</code> 
	means an exception, and the information about it can be 
	found in <code>errParams</code>. 
	@see DigSigClearSigRefDict 
	@see DigSigCommitSigRefDict 
	@see DigSigFinishSigRefDict 
	@see DigSigNewSigRefDict 
*/
PIPROC(DSRetCode, DigSigVerifySigRefDict, 
    ( ASAtom transformMethod, CosObj sigDict, CosObj refDict, DSSigRefDictErrParams errParams ), 
	transformMethod, sigDict, refDict, errParams )

/**
	Clears the signature reference dictionary referred to by 
	<code>refDict</code> and removes any reference to it from the document. 
	
	@param transformMethod The transform method. It should 
	match the one contained in <code>sigDict</code>. 
	@param sigDict The signature dictionary containing the 
	signature reference dictionary. 
	@param refDict The signature reference dictionary.
	@return A positive value on success. 
	@see DigSigCommitSigRefDict 
	@see DigSigFinishSigRefDict 
	@see DigSigNewSigRefDict 
	@see DigSigVerifySigRefDict 
*/
PIPROC(DSRetCode, DigSigClearSigRefDict, 
    ( ASAtom transformMethod, CosObj sigDict, CosObj refDict ), transformMethod, sigDict, refDict )

/**
	Un-registers a signing method plug-in. The caller should 
	deallocate the DigSigHandler object after making this call. 
	
	@param digSigHandler A structure specifying the name of 
	the filter and the functions to call to create and validate 
	signatures.
	@see DigSigRegisterFilter 
*/
PIPROC(void, DigSigUnregisterFilter, 
	( DigSigHandler digSigHandler ), digSigHandler)

/*************************************************************************
 * DigSigAPCreateLayeredStreamEx
 * Creates a stream that is composed of four or five layers:
 *	layer n0 - background, inherited from form annot background
 *	layer n1 - middle, question mark or equivalent (none if CosNull)
 *	layer n2 - main, text and appearance (must be provided)
 *	layer n3 - top, blank or X (none if CosNull)
 *	layer nN - optional very top layer, used for text showing validity state (none if CosNull)
 ************************************************************************/

/** 
	Creates a signature-appearance layered stream, using a parameters structure.
	@param params The parameter structure containing the signature appearance layer
	information.
	@return A new CosStream composed of different layers.
	@see DigSigAPXObjectFromLogo
	@see DigSigAPXObjectFromXObjList
	@note Supersedes DigSigAPCreateLayeredStream() in Acrobat 6.0.
*/
PIPROC(CosObj, DSAPCreateLayeredStreamEx,  (const DSAPCreateLayeredStreamExParams params), params)

/**
	Tests whether a particular signature field in a document 
	is signed. 
	@param pdDoc The document that contains the signature field. 
	@param sigField The signature field that is tested. 
	@return <code>true</code> if the signature field is signed, <code>false</code> otherwise. 
	
	@see DigSigIsDocSigned 
*/
PIPROC(ASBool, DigSigIsSigSigned, 
	(PDDoc pdDoc, CosObj sigField), pdDoc, sigField)


/*****************************************************************************
 DigSig Notification Server 
*****************************************************************************/
/**
	Registers callbacks with the notification server, to be 
	called for specific digital signature events. 
	
	<p>The events are: </p>
	
	<ul>
	<li>Adding or deleting a signature field.</li>
	<li>Requesting a new signature, and the success of the request. </li>
	<li>Requesting that an existing signature be cleared, and the success of the request. </li>
	</ul>

	@param notificationID The type of event for which to register 
	a callback. 
	@param notifyProc The procedure to call when a field change, 
	request, or success event occurs. 
	@param notifyFailure The procedure to call when a failure 
	event occurs. 
	@param clientData A pointer to client-supplied data to 
	pass to the callback procedure.
	@return The observer identifier, which must be provided to DigSigUnregisterObserver(). 
	
	@see DigSigUnregisterObserver 
*/
PIPROC(ASInt32, DigSigRegisterObserver, 
		(DSNotificationType notificationID, DSNotificationProc notifyProc,
		DSNotificationFailureProc notifyFailure, void *clientData), notificationID, notifyProc,
		notifyFailure, clientData)

/**
	Un-registers an event interest from the notification server. 
	
	@param notificationID The event for which an interest 
	has been registered, as specified in DigSigRegisterObserver(). 
	
	@param observerID The observer identifier as returned 
	by DigSigRegisterObserver().
	@see DigSigRegisterObserver 
*/
PIPROC(void, DigSigUnregisterObserver, 
		(DSNotificationType notificationID, ASInt32 observerID),
		notificationID, observerID)


/**
	Gets the author signature for a document, as a Cos object. 
	
	@param doc The document for which the author signature 
	is obtained.
	@return The CosObj containing the author signature. 
	@see DigSigGetDocMDPSetting 
*/
PIPROC(CosObj, DigSigGetDocAuthorSignature, 
		(PDDoc doc), doc)

/**
	Compares the pages of two documents, producing a third document 
	of the differences. 
	@param docA The first document being compared. 
	@param docB The second document being compared. 
	@param params A structure containing the sensitivity level 
	for the comparison.
	@return <code>true</code> if the pages of the documents are identical, <code>false</code> 
	otherwise. 
	@see DigSigComparePages 
	@see DigSigCompareWords 
*/
PIPROC(ASBool, DigSigComparePagesEx, 
	(PDDoc docA, PDDoc docB, DSComparePagesParams params), docA, docB, params)

/**
	Compares the words of two documents, producing a third document 
	of the differences. 
	@param docA The first document being compared. 
	@param docB The second document being compared. 
	@param params A structure containing the comparison parameters.
	@return <code>true</code> if the words of the documents are identical, <code>false</code> 
	otherwise. 
	@see DigSigComparePagesEx 
	@see DigSigCompareWords 
	@see DigSigCompareWordsAndFontsRecent 
	@see DigSigCompareWordsRecent 

	@note Supersedes DigSigCompareWords(), DigSigCompareWordsAndFontsRecent(), 
	and DigSigCompareWordsRecent() in Acrobat 6.0. 
*/
PIPROC(ASBool, DigSigCompareWordsEx, 
	(PDDoc docA, PDDoc docB, DSCompareWordsParams params), docA, docB, params)

/**
	Verifies a digital signature. 
	@param pdDoc The document. 
	@param sigField The signature field to verify. 
	@param bUI When <code>true</code>, it can bring up the user interface 
	dialogs if needed.
	@return The validity state that results from verification. 
	@see DigSigClearSig 
*/
PIPROC(DSValidState, DigSigVerifySig, 
	(PDDoc pdDoc, CosObj sigField, ASBool bUI), pdDoc, sigField, bUI)

/**
	Clears a signature field in a document. This removes the 
	signature so that the document is unsigned. 
	@param pdDoc The document. 
	@param sigField The signature field to clear.
	@see DigSigVerifySig 
*/
PIPROC(void, DigSigClearSig, 
	(PDDoc pdDoc, CosObj sigField), pdDoc, sigField)

/**
	Gets the Modification Detection and Prevention (MDP) setting for the author signature for the specified 
	document. 
	@param pdDoc The document for which the MDP setting is obtained.
	@return The MDP setting of the document's author signature, or <code>kDSMDPNone</code> 
	if there is no author signature. 
	@see DigSigGetDocAuthorSignature 
*/
PIPROC(DSMDPType, DigSigGetDocMDPSetting, 
	(PDDoc pdDoc), pdDoc)

/** 
	Gets the LiveCycle Reader Extensions signature for a document, as a Cos object.
	@param pdDoc The document for which the LiveCycle Reader Extensions signature is obtained.
	@return The CosObj containing the LiveCycle Reader Extensions signature.
	@see DigSigGetDocAuthorSignature
*/
PIPROC(CosObj, DigSigGetUbiquitySig, 
	(PDDoc pdDoc), pdDoc)

	/** Creates a new XObject from the list of DSAPXObjEntry objects. Each object in the list is
	either an existing stream or a string that will be laid out and reflowed into a new stream.
	The streams are then turned into XObjects. Controls allow you to adjust the vertical
	position of each stream within bbox. If <code>bMerge</code> is <code>true</code>, this method combines the
	new XObjects into one large XObject, and the sub XObjects are destroyed. Otherwise the
	method leaves the component XObjects intact and new XObjects are created but not
	destroyed for the text entries. Text streams use the text attributes of <code>ta</code>.
	@param cosDoc The document in which to include the standard XObject.
	@param bbox The bounding box for the signature.
	@param objEntry A list of DSAPXObjEntry objects.
	@param ta The text appearance. For an explanation of the TextAppearanceP type, see "AcroForm
	Declarations" in the Acrobat and PDF Language API Reference.
	@param border The border style for the signature, as returned by AFPDWidgetGetBorder().
	For an explanation of the AFPDWidgetBorder type, see "AcroForm Declarations" in the Acrobat and PDF Language API Reference.
	@param bMerge When <code>false</code>, keep the sub XObjects. When <code>true</code>, combine them all into
	one large one.
	@return An XObject composed from the list.
	@see DigSigAPCreateLayeredStream
	@see DigSigAPXObjectFromLogo
*/
PIPROC(CosObj, DSAPXObjectFromXObjList,  ( CosDoc cosDoc,
						const ASFixedRect* const bbox,
						DSAPXObjEntry objEntry,
						TextAppearanceP ta,
						size_t taSize,
						AFPDWidgetBorder border,
						ASUns32 flags),
						cosDoc,bbox,objEntry,ta, taSize, border,flags)

// Added in Acrobat 10
/** Procs below are provided in version 0x00020000 */

/**
	Gets the number of bytes in an ASFile. It serves as a wrapper 
	for the ASFileGetEOF64() method. 
	@param asFile The ASFile whose length is obtained.
	@return The number of bytes in the ASFile, or <code>0</code> if an error is encountered. 
	
	@see DigSigFileSetPos64 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray64 
	@see DigSigOverwriteHexstring64 
	@see DigSigOverwriteBytes64 
*/
PIPROC(ASFilePos64, DigSigFileGetEOF64, 
	(ASFile asFile), asFile)

/**
	Reopens an ASFile for reading and sets the file position. 
	
	@param asFile The ASFile to position. 
	@param pos The byte offset to a position in <code>asFile</code>.
	@see DigSigFileGetEOF64 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray64 
	@see DigSigOverwriteHexstring64 
	@see DigSigOverwriteBytes64
*/
PIPROC(void, DigSigFileSetPos64, 
	(ASFile asFile, ASFilePos64 pos), asFile, pos)

/**
	Overwrites part of <code>asFile</code> with an integer array. It reopens 
	the file for write, positions to the specified place, formats 
	the array as characters, and writes. This method is used 
	to overwrite the <code>/ByteRange</code> entry in the signature dictionary. 
	
	@param asFile The ASFile to write to. 
	@param digSigOffset A structure specifying the byte position 
	and size to overwrite:
	<ul>
	<li>Writes padding blanks to the file if formatted length is less than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is longer than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is greater than <code>8200</code> bytes.</li>
	</ul>
	@param cosObj The Cos string to be written.
	@return The number of bytes written. 
	@see DigSigCosObjOverwrite 
	@see DigSigFileGetEOF64 
	@see DigSigFileSetPos64 
	@see DigSigFileRead 
	@see DigSigOverwriteHexstring64 
	@see DigSigOverwriteBytes64 
*/
PIPROC(ASUns64, DigSigOverwriteIntArray64, 
	(ASFile asFile, const DigSigOffset64 digSigOffset, const CosObj cosObj), asFile, digSigOffset, cosObj)

/**
	Overwrites part of a file with a hex string. It reopens the 
	file for write, positions to the specified location, formats 
	the string as characters, and writes. This method is used 
	to overwrite the <code>/Contents</code> entry in the signature dictionary. 
	
	@param asFile The ASFile to write to. 
	@param digSigOffset A structure specifying the byte position 
	and size to overwrite:
	<ul>
	<li>Writes padding blanks to the file if formatted length is less than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is longer than this length.</li>
	<li>Does not write and returns <code>0</code> if the formatted length is greater than <code>8200</code> bytes.</li>
	</ul>
	@param cosObj The Cos string to be written.
	@return The number of bytes written. 
	@see DigSigCosObjOverwrite 
	@see DigSigFileGetEOF64 
	@see DigSigFileSetPos64 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray64 
	@see DigSigOverwriteBytes64 
*/
PIPROC(ASUns64, DigSigOverwriteHexstring64, 
	(ASFile asFile, const DigSigOffset64 digSigOffset, const CosObj cosObj), asFile, digSigOffset, cosObj)

/**
	Overwrites any or all entries in a signature dictionary. 
	It reopens the file for write, positions to the specified place, 
	and writes exactly the number of bytes specified in <code>digSigOffset</code>. 
	@param asFile The ASFile to write to. 
	@param digSigOffset A structure specifying the byte position 
	and size to overwrite. 
	@param p A byte string to be written. It must be in the correct 
	format, given the type of entry as defined in Section 8.7 
	in the PDF Reference.
	@return The number of bytes written, or <code>0</code> if unsuccessful. 
	@see DigSigCosObjOverwrite 
	@see DigSigFileGetEOF64 
	@see DigSigFileSetPos64 
	@see DigSigFileRead 
	@see DigSigOverwriteIntArray64 
	@see DigSigOverwriteHexstring64 
	
	@note To overwrite a text string entry, such as <code>/Reason</code>, 
	the string must be in the format <code>"< xxx >"</code>, not <code>"xxx"</code>. 
*/
PIPROC(ASUns64, DigSigOverwriteBytes64, 
	(ASFile asFile, const DigSigOffset64 digSigOffset, const char *p), asFile, digSigOffset, p)

/* End of DigSigHFTProcs.h */
