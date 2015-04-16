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
 Copyright (C) 2007 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.
*********************************************************************/

/**
	Indicates whether a PDDoc contains an Acrobat form. 
	@param doc The PDDoc to test. 
	@return <code>true</code> if <code>doc</code> contains a form, <code>false</code> otherwise. 
	@see AFPDFieldIsValid 
*/
PIPROC(ASBool, IsPDDocAcroForm, (PDDoc doc), doc)

/**
	Ensures that every PDField in the given PDDoc exists. 

	@note It is no longer necessary to call this method. It 
	still exists for backwards compatibility, but its purpose 
	is now automatically taken care of internally. 
	@param doc The PDDoc for the form whose PDField objects are loaded.
*/
PIPROC(void, AFPDDocLoadPDFields, (PDDoc doc), doc)

/**
	Enumerates all PDField objects that exist in a PDDoc. 
	@param doc The PDDoc whose PDField objects are enumerated. 
	@param terminals If <code>true</code>, only PDField objects without children 
	are enumerated. 
	@param parameterIgnored This parameter is no longer used (it is ignored).
	@param proc A user-supplied callback that is called for 
	each PDField. The enumeration terminates if <code>proc</code> returns 
	false. 
	@param clientData A pointer to user-specified data that 
	is passed to <code>proc</code> each time it is called.
*/
PIPROC(void, AFPDDocEnumPDFields, (PDDoc doc, ASBool terminals, ASBool parameterIgnored, AFPDFieldEnumProc proc, void *clientData),doc, terminals, parameterIgnored, proc, clientData)

/**
	Retrieves a PDField with a given name from a PDDoc. (If 
	multiple fields have the same name, a change to any of them 
	affects all of them.) 
	@param doc The PDDoc containing the field. 
	@param name The name of the field to retrieve. 
	@return The PDField specified by name. It returns <code>NULL</code> if there is 
	no PDField with the given name in the PDDoc. 
	@see AFPDFieldGetName 
*/
PIPROC(PDField, AFPDDocGetPDFieldFromName, (PDDoc doc, char* name), doc, name)

/**
	Retrieves the PDField object for which a Cos object is the 
	dictionary. 
	@param dict The Cos object for which to retrieve the corresponding 
	PDField object.
	@return The PDField corresponding to <code>dict</code>. It returns <code>NULL</code> if the Cos 
	object is not a PDField. 
	@see AFPDFieldGetCosObj 
*/
PIPROC(PDField, AFPDFieldFromCosObj, (CosObj dict), dict)

/**
	Retrieves the Cos object which is the field object of a 
	PDField object. 
	@param fldP The PDField object for which to retrieve the 
	corresponding Cos object.
	@return A Cos object corresponding to the PDField object (<code>fldP</code>). 
	@see AFPDFieldGetCosObj 
	@see AFPDFieldGetDefaultTextAppearance 
	@see AFPDFieldGetName 
	@see AFPDFieldGetValue 
*/
PIPROC(CosObj, AFPDFieldGetCosObj, (PDField fldP), fldP)

/**
	Determines whether a field is valid. 

	@param fldP The field to test.
	@return <code>true</code> if <code>fldP</code> is a valid PDField, <code>false</code> otherwise. 
	@see AFPDFieldIsAnnot 
	@see AFPDFieldIsTerminal 
	@note This method is intended only to ensure that the field 
	has not been deleted, not to ensure that all necessary information 
	is present and the field has valid values. 
*/
PIPROC(ASBool, AFPDFieldIsValid, (PDField fldP), fldP)

/**
	Determines whether a field is <i>terminal</i>, which means that the field has no 
	children or it has the same name as its children. 
	@param fldP The PDField to test. 
	@return <code>true</code> if <code>fldP</code> is valid and all its children (if any) have 
	the same name as <code>fldP</code>. Otherwise all have unique names. 
	
	@see AFPDFieldIsAnnot 
	@see AFPDFieldIsValid 
*/
PIPROC(ASBool, AFPDFieldIsTerminal, (PDField fldP), fldP)

/**
	Retrieves the value from a PDField. The value is stored 
	in the field entry with the V key. 

	<p>Values can be inherited. If a PDField Cos object does not 
	have a V key, its value is inherited from a parent's V key 
	(the parent must have the same name as the PDField). For 
	example, radio buttons inherit values this way. </p>

	@param fldP The PDField whose value is retrieved.
	@return The value of the field as a CosObj. If the field has no 
	value, <code>NULL</code> is returned. 
	@see AFPDFieldGetCosObj 
	@see AFPDFieldGetDefaultTextAppearance 
	@see AFPDFieldGetName 
	@see AFPDFieldSetValue 
	@note Retrieving the value of a radio button or combo box 
	requires Cos-level programming. See the <i>PDF Reference</i> for 
	details. 
*/
PIPROC(CosObj, AFPDFieldGetValue, (PDField fldP), fldP)

/**
	Retrieves the flags of a PDField for a given flag type. 
	
	@param fldP The PDField whose flags are obtained. 
	@param flagType The type of flags to obtain.
	@return The value of the flags of <code>flagType</code>. 
	@see AFPDFieldGetName 
	@see AFPDFieldGetValue 
	@see AFPDFieldSetFlags 
*/
PIPROC(ASUns32, AFPDFieldGetFlags, (PDField fldP, AF_Flags_t flagType), fldP, flagType)

/**
	Gets the name of a PDField object. 
	@param fldP The PDField whose name is retrieved. 
	@return A <code>NULL</code>-terminated string. 

	@see AFPDFieldGetDefaultTextAppearance 
	@see AFPDFieldGetValue 
	@note Do not modify or free this string. To use this string 
	indefinitely, copy it to a private buffer. 
*/
PIPROC(char*, AFPDFieldGetName, (PDField fldP), fldP)

/**
	Determines whether a PDField is an annotation (PDAnnot), 
	that is, whether the field dictionary is also an annotation. 
	If this is the case, the value of Subtype is Widget. 
	@param fldP The field in question. 
	@return <code>true</code> if the PDField is an Acrobat annotation, <code>false</code> otherwise. 
	
	@see AFPDFieldIsTerminal 
	@see AFPDFieldIsValid 
*/
PIPROC(ASBool, AFPDFieldIsAnnot, (PDField fldP), fldP)

/**
	Sets the value for a PDField. The value is stored in the 
	field entry with the V key. The method updates the display of the field 
	and its namesakes; that is, fields with the same fully qualified 
	names, if any. Changing the field dictionary's value for 
	the V entry directly does not change the appearance of the 
	field, which is represented by the AP key. 
	
	@param fldP The field whose value is set. 
	@param val The field's new value. If it is different than 
	the previous value, all previous instances of value keys 
	(V) in the field's dictionary and those of its namesakes 
	(fields with the same fully qualified name) are removed.
	@see AFPDFieldGetValue 
	@see AFPDFieldSetFlags 
	@see AFPDFieldSetOptions 
	@note Setting the value of a radio button or combo box requires 
	Cos-level programming. See the <i>PDF Reference</i> for details. 
*/
PIPROC(ASBool, AFPDFieldSetValue, (PDField fldP, CosObj val), fldP, val)

/**
	Sets the flags of type <code>flagType</code> for a PDField. 

	<p>The flags of a field's children (if any) are also set. </p>

	@param fldP The PDField for which to set flags and children's 
	flags. 
	@param flagType The type of the flags to set. If its value 
	is <code>Flags_Annot</code> and the PDField is not an annotation, no 
	flags are changed. 
	@param flags The value of the flags. 
	@see AFPDFieldGetDefaultTextAppearance 
	@see AFPDFieldSetOptions 
	@see AFPDFieldSetValue 
*/
PIPROC(void, AFPDFieldSetFlags, (PDField fldP, AF_Flags_t flagType, AFPDFieldFlags_t flags), fldP, flagType, flags)

/**
	Sets the options entry for a field. The options entry has 
	the key <code>Opt</code> and represents a list of options for a choice 
	field. 

	<p>If the field is not valid, remove the options entry. </p>

	@param fldP The PDField whose options are set. 
	@param array The value to set in the options entry.
	@return <code>Good</code> if the operation succeeded, <code>Bad</code> otherwise. 
	@see AFPDFieldSetFlags 
	@see AFPDFieldSetValue 
*/
PIPROC(RetCode, AFPDFieldSetOptions, (PDField fldP, CosObj array), fldP, array)

/**
	Sets a PDField object's value to its default state. This is the 
	value associated with the DV key for the field. If there 
	is no DV key for the field, set the field's value to the 
	<code>NULL</code> Cos object; otherwise, if the field has options, the default 
	DV is the first element of the <code>Opt</code> array. 

	<p>A DV entry's value can be inherited from a parent (just 
	like V). </p>

	<p>The PDField object's value is set only if it is terminal (check this by calling AFPDFieldIsTerminal()).</p>
	
	@param fldP The PDField to reset. 
	@see AFPDFieldIsTerminal
	@see ResetForm 
*/
PIPROC(void, AFPDFieldReset, (PDField fldP), fldP)

/**
	Exports form data to a CosDoc, which can be written to an 
	FDF file. See the <i>PDF Reference</i> for a description of this 
	format. 

	<p>To create an FDF file from the CosDoc, call CosDocSaveToFile(). </p>

	@param pdForm The PDDoc for the form for which to export the data. 
	@param rgIncExcFlds If this parameter's value is CosNewNull(), then 
	all fields are exported and <code>bIncl</code> is ignored. If this parameter 
	is a CosArray, then the array elements may be: 
	
	<ul>
	<li>
	Names of fields (the names may be of non-terminal fields, which 
	is a fast and easy way to cause all their children to be 
	included in the FDF file).
	</li>
	
	<li>
	<p>Arrays whose first element is a field name, and the rest of whose elements are field 
	dictionary key names whose values should be exported in the FDF file. </p>
    	
	<p>For example: <code>[ (My listbox) /AP /Opt ]</code></p>
	
	<p>This variety of <code>rgIncExcFlds</code> array element can only be used if 
	<code>bIncl</code> is <code>true</code> (see below).</p>
	</li>

	<li>
	<p>If <code>rgIncExcFlds</code> contains a single element, which is itself an array as described  
	above, and its first element, which corresponds to the 
	field name, is <code>NULL</code>, then the FDF file will include the 
	requested field properties of all fields. </p>

	<p>For example: <code>[ null /F /Ff ]</code> </p>
	</li>
	</ul>

	@param bIncl If <code>true</code>, <code>rgIncExcFlds</code> is an array of the 
	fields to export. Otherwise, <code>rgIncExcFlds</code> is an array of 
	the fields to exclude from exporting. 
	@param bEmpty If <code>true</code>, all fields selected per the above 
	criteria are exported. If <code>false</code>, exclude fields that have 
	no value. 
	@param bMenu If <code>true</code>, suppresses saving text fields that 
	have the <i>"password"</i> flag set, and does not force filling in 
	required fields when creating an FDF file. 
	@param bLoadFields IN Not used.
	@param fdfPath IN The path where the FDF file will be saved 
	(by the client of ExportAsFDF()) after it is produced. You need 
	this in order to create an FDF file with an F key that gives the 
	relative path to the form from the location where the FDF 
	file will be saved. Pass <code>NULL</code> if an absolute path name is desired.
	@return The FDF CosDoc object containing the exported data.
	@exception gAFpdErrExportFdf is raised if it cannot export field data. 
	The viewer may raise other exceptions.
	@see ExportAsFDFEx 
	@see ExportAsFDFWithParams 
	@see ImportAnFDF 
	@see AssembleFormAndImportFDF 
	@note ExportAsFDFWithParams() provides the same functionality with additional options. 
*/
PIPROC(CosDoc, ExportAsFDF, (PDDoc pdForm, CosObj rgIncExcFlds, ASBool bIncl, ASBool bEmpty, ASBool bMenu, ASBool bLoadFields, ASPathName fdfPath), pdForm, rgIncExcFlds, bIncl, bEmpty, bMenu, bLoadFields, fdfPath)

/**
	Exports data from a form to a file in HTML format. 
	@param pdForm The PDDoc for the form whose data is exported. 
	@param rgIncExcFlds If this parameter's value is CosNewNull(), then 
	all fields are exported, and <code>bIncl</code> is ignored. If it is 
	a CosArray, then the array elements must be indirect references 
	to field dictionaries. 
	@param bIncl If <code>true</code>, <code>rgIncExcFlds</code> is an array of the 
	fields to export. Otherwise, <code>rgIncExcFlds</code> is an array of 
	the fields to exclude from exporting. 
	@param bEmpty If <code>true</code>, all fields selected per the above 
	criteria are exported. If <code>false</code>, exclude fields that have 
	no value. 
	@param Hfile The file to which the HTML data is written.
	@see ExportAsHtmlEx 
*/
PIPROC(void, ExportAsHtml, (PDDoc pdForm, CosObj rgIncExcFlds, ASBool bIncl, ASBool bEmpty, ASFile Hfile),pdForm, rgIncExcFlds, bIncl, bEmpty, Hfile)

/**
	Imports data from an FDF file into a PDDoc object's form. See the 
	<i>PDF Reference</i> for a description of this format. 
	@param pdForm The PDDoc for the form into which to import the data. 
	@param cdFDF The CosDoc for the FDF file containing the data.
	@return <code>true</code> if the fields in the FDF file only contained values 
	or flags (that is, V, F, Ff, ClrF, ClrFf, SetF, SetFf), 
	<code>false</code> if any field contained other attributes, such as appearances (AP), actions (A), and so on. 
	@exception gAFpdErrBadFdf is raised if the FDF file is invalid. An exception is also raised if memory cannot be allocated for FDF file data. 
	@see AssembleFormAndImportFDF 
	@see ExportAsFDF 
	@see ExportAsFDFEx 
	@see ExportAsFDFWithParams 
*/
PIPROC(ASBool, ImportAnFDF, (PDDoc pdForm, CosDoc cdFDF), pdForm, cdFDF)

/**
	Resets the indicated fields of a PDDoc object's form to their default 
	values. 

	<p>A PDField object's value is reset only if it is terminal; you can  check this by calling AFPDFieldIsTerminal(). </p>
	
	@param pdForm The PDDoc for the form whose fields are reset. 
	@param rgIncExcFlds If this parameter's value is CosNewNull(), then 
	all fields are reset, and <code>bIncl</code> is ignored. If it is a CosArray, 
	then the array elements must be names of fields. The names 
	may be of non-terminal fields, which is a fast and easy 
	way to cause all their children to be reset. 
	@param bIncl If <code>true</code>, <code>rgIncExcFlds</code> is an array of the 
	fields to reset. Otherwise, <code>rgIncExcFlds</code> is an array of 
	the fields to exclude from resetting.
	@see AFPDFieldSetDefaultTextAppearance 
	Callback used by AFPDDocEnumPDFields(). It is called once 
	for each PDField in a form. 
	@return <code>true</code> to continue the enumeration, <code>false</code> to halt the enumeration.
	@see AFPDDocEnumPDFields 
*/
PIPROC(void, ResetForm, (PDDoc pdForm, CosObj rgIncExcFlds, ASBool bIncl), pdForm, rgIncExcFlds, bIncl)

/** Deprecated as of Acrobat 8.0. */
PIPROC(ASInt32, AcroFormRegisterObserver, (AF_NotificationSelector_t notificationID, AF_NotificationProc notifyProc, AF_NotificationFailureProc notifyFailure, void *clientData),notificationID, notifyProc,notifyFailure, clientData)

/** Deprecated as of Acrobat 8.0. */
PIPROC(void, AcroFormUnregisterObserver, (AF_NotificationSelector_t notificationID, ASInt32 observerID), notificationID, observerID)

/** Deprecated as of Acrobat 8.0. */		
PIPROC(ASBool, AFGetScriptingContext, (void** pcx, void** pobj), pcx, pobj)

/**
	Exports form data to a CosDoc object, which can be written to an 
	FDF file. See the <i>PDF Reference</i> for a description of this 
	format. 

	<p>To create an FDF file from this CosDoc object, call CosDocSaveToFile(). </p>
	
	@param pdForm A PDDoc for the form whose data is exported. 
	
	@param rgIncExcFlds If this parameter's value is CosNewNull(), then 
	all fields are exported, and <code>bIncl</code> is ignored. If it  
	is a CosArray, then the array elements may be: 
	
	<ul>
	<li>
	Names of fields (the names may be of non-terminal fields, which 
	is a fast and easy way to cause all their children to be 
	included in the FDF file). 
	</li>
	<li>
	<p>Arrays whose first element 
	is a field name, and the rest of whose elements are field 
	dictionary key names whose values should be exported in 
	the FDF file. </p>
	<p>For example: <code>[ (My listbox) /AP /Opt ]</code> </p>
	<p>This variety of <code>rgIncExcFlds</code> array element can only be used if 
	<code>bIncl</code> is <code>true</code> (see below).</p>
	</li>
	<li>
	<p>If <code>rgIncExcFlds</code> contains a 
	single element, which is itself an array as described 
	above, and its first element, which corresponds to the 
	field name, is <code>NULL</code>, then the FDF file will include the 
	requested field properties of all fields. </p>
	<p>For example: <code>[ null /F /Ff ]</code></p>
	</li>
	</ul>

	@param bIncl If <code>true</code>, <code>rgIncExcFlds</code> is an array of the 
	fields to export. Otherwise, <code>rgIncExcFlds</code> is an array of 
	the fields to exclude from exporting. 
	@param bEmpty If <code>true</code>, all fields selected per the above 
	criteria are exported. If <code>false</code>, exclude fields that have 
	no value.
	@param bMenu IN If <code>true</code>, suppresses saving text fields that 
	have the <i>"password"</i> flag set, and does not force filling-in 
	required fields when creating an FDF file.
	@param bLoadFields IN Not used.
	@param fdfPath IN The path where the FDF file will be saved 
	(by the client of ExportAsFDF()) after it is produced. You need 
	this in order to create an FDF file with an F key that gives 
	the relative path to the form from the location where the FDF 
	file will be saved. Pass <code>NULL</code> if an absolute path name is desired.
	@param submitBtnName IN A <code>NULL</code>-terminated string containing 
	the name of the button used to submit. If the value passed is 
	not <code>NULL</code>, then the FDF file will include a field dictionary 
	corresponding to the submit button, which will only contain 
	one key (T).
	
	<p>Note that this dictionary is no different than the one you get when 
	an AcroForm has an empty text field (that is, no value), and 
	parameter <code>bEmpty</code> is <code>true</code>.</p>

	@return The FDF CosDoc containing the exported data.
	@exception gAFpdErrExportFdf is raised if field data cannot be exported. The viewer may raise other exceptions.
	@see ExportAsFDF 
	@see ExportAsFDFWithParams 
	@see ImportAnFDF 
	@see AssembleFormAndImportFDF 
	@note This method is the same as ExportAsFDF(), with the exception 
	of the additional parameter <code>submitBtnName</code>. ExportAsFDFWithParams() 
	provides the same functionality with additional options. 
*/
PIPROC(CosDoc, ExportAsFDFEx, (PDDoc pdForm, CosObj rgIncExcFlds, ASBool bIncl, ASBool bEmpty, ASBool bMenu, ASBool bLoadFields, ASPathName fdfPath, const char* submitBtnName), pdForm, rgIncExcFlds, bIncl, bEmpty, bMenu, bLoadFields, fdfPath, submitBtnName)

/**
	Exports data from a form to a file in HTML format. 

	@param pdForm The PDDoc for the form whose data is exported. 
	@param rgIncExcFlds If this parameter's value is CosNewNull(), then 
	all fields are exported, and <code>bIncl</code> is ignored. If it is 
	a CosArray, then the array elements must be names of fields. 
	The names may be of non-terminal fields, which is a fast 
	and easy way to cause all their children to be exported. 
	
	@param bIncl If <code>true</code>, <code>rgIncExcFlds</code> is an array of the 
	fields to export. Otherwise, <code>rgIncExcFlds</code> is an array of 
	the fields to exclude from exporting. 
	@param bEmpty If <code>true</code>, all fields selected per the above 
	criteria are exported. If <code>false</code>, exclude fields that have 
	no value. 
	@param Hfile The file to which the HTML data is written. 
	@param submitBtnName A <code>NULL</code>-terminated string containing 
	the name of the button used to submit. If the value passed 
	is not <code>NULL</code>, then include <code>"...&submitBtnName=&..."</code> as part 
	of the generated x-www-form-urlencoded output. 
	<p>Note that this type of output is the same one you get when an AcroForm 
	has an empty text field (that is, no Value), and parameter <code>bEmpty</code> is <code>true</code>.</p>
	@see ExportAsHtml 
	@see ImportAnFDF
	@note This method is the same as ExportAsHtml(), with the 
	exception of the additional parameter <code>submitBtnName</code>. 
*/
PIPROC(void, ExportAsHtmlEx, (PDDoc pdForm, CosObj rgIncExcFlds, ASBool bIncl, ASBool bEmpty, ASFile Hfile, const char* submitBtnName), pdForm, rgIncExcFlds, bIncl, bEmpty,Hfile, submitBtnName)

/**
	Constructs an Acrobat form from templates and imports an 
	FDF file. 
	@param pdCurrForm The current form being viewed, if any, 
	at the time <code>cdFDF</code> is being imported. This parameter can 
	be <code>NULL</code>; if it is not <code>NULL</code>, then <code>cdFDF</code> can refer to templates 
	in the current form by omitting the F key in the TRef dictionary. 
	Even if the F key is not <code>NULL</code>, it can be a relative path 
	(as opposed to an absolute path), as long as <code>pdCurrForm</code> is not <code>NULL</code>. 
	@param cdFDF The FDF file being imported. 
	@param bAddToCurr If <code>true</code> (and <code>pdCurrForm</code> is not <code>NULL</code>), 
	then instead of creating a new form, the templates spawn 
	pages that are appended at the end of <code>pdCurrForm</code> (and the 
	function returns <code>pdCurrForm</code>).
	@return The PDDoc for the newly-created form (or <code>pdCurrForm</code>, if 
	<code>bAddToCurr</code> is <code>true</code>). 
	@see ExportAsFDF 
	@see ExportAsFDFEx 
	@see ExportAsFDFWithParams 
	@see ImportAnFDF 
*/
PIPROC(PDDoc, AssembleFormAndImportFDF, (PDDoc pdCurrForm, CosDoc cdFDF, ASBool bAddToCurr), pdCurrForm, cdFDF, bAddToCurr)

/**
	Exports form data to a CosDoc, which can be written to an 
	FDF file. See the <i>PDF Reference</i> for a description of this 
	format. 
	@param params An ExportAsFDFParamsRec structure.
	@return The FDF CosDoc containing the exported data. 
	@exception gAFpdErrExportFdf is raised if field data cannot be exported. The viewer may raise other exceptions. 
	@see ExportAsFDF 
	@see ExportAsFDFEx 
	@see ImportAnFDF 
	@see AssembleFormAndImportFDF 
	@note Call CosDocSaveToFile() to create an FDF file from this CosDoc. 
*/
PIPROC(CosDoc, ExportAsFDFWithParams, (ExportAsFDFParams params),params)

/**
	Creates an XObject form from a PDF page. A form XObject 
	is a content stream that can be treated as a single graphics 
	object. Use this method for importing PDF graphics into 
	documents. 
	@param cd The CosDoc in which the XObject will be created. 
	@param pdp The PDPage from which to create the XObject. 
	@return A Cos object pointing to the XObject on the PDF page. 
*/
PIPROC(CosObj, AFPDFormFromPage, (CosDoc cd, PDPage pdp), cd, pdp)

/* AFLayoutNew has been revved */
NOPROC(AFLayoutNewOBSOLETE)

/**
	Frees the layout context. 
	@param vlayout The layout of the annotation to remove.
	@see AFLayoutNew 
	@see AFLayoutCreateStream 
*/
PIPROC(void, AFLayoutDelete, (void* vlayout), vlayout)

/* AFLayoutCreateStream has been revved */
NOPROC(AFLayoutCreateStreamOBSOLETE)

/**
	Draws a border into the layout context. 
	@param vlayout The layout of the annotation. Use AFLayoutNew() 
	to create a new layout before calling this method. 
	@param border A pointer to a structure containing information 
	about the appearance a border. 
	@param pdcvBrdr A PDColorValue structure representing 
	the color of the annotations border. 
	@param pdcvBg A PDColorValue structure representing the 
	color of the annotations background. 
	@param bDown A boolean value specifying whether the background 
	should be drawn as it is drawn in forms while being <i>pressed</i> 
	(clicked by the mouse). If <code>true</code>, it is drawn as if it is 
	a field that is being pressed.
	@see AFLayoutNew 
*/
PIPROC(void, AFLayoutBorder, (void* vlayout, AFPDWidgetBorder border, PDColorValue pdcvBrdr, PDColorValue pdcvBg,ASBool bDown), vlayout, border, pdcvBrdr, pdcvBg,bDown)

/**
	Sets the text layout for the annotation. 

	<p>It raises an exception if the field is a radio box or button. </p>

	@param vlayout The layout of the annotation. 
	@param bMultline If <code>true</code>, the text can use multiple lines 
	in a text field. Otherwise, the text is a single line. 
	@param bWrap If <code>true</code>, the text will wrap. 
	@param border The border appearance that defines the width 
	and line style of a border. The border of the annotation 
	should be the same as in your call to AFLayoutBorder(). 
	@param ta A pointer to a structure containing font, point 
	size, and color information. You should initialize the structure 
	with the <code>SetDefaultTextAppearanceP</code> macro which defaults 
	to Helvetica. 
	@param cBytes The text string for the layout.
	
	@see AFLayoutNew 
	@see AFLayoutBorder 
	@note Before calling this method, you should call AFLayoutNew() 
	to create a new layout, as well as AFLayoutBorder(). 
*/
PIPROC(void, AFLayoutText, (void* vlayout, ASBool bMultline, ASBool bWrap, AFPDWidgetBorder border, TextAppearanceP ta, char* cBytes), vlayout, bMultline, bWrap, border, ta, cBytes)

/** Deprecated as of Acrobat 8.0. */
PIPROC(void, AFPDFieldValueChanged, (PDDoc pdd, PDField fldP), pdd, fldP)



/**
	Gets the rotation of the annotation. 
	@param pdan The annotation widget.
	@return Returns an ASAtom object representing the annotation's rotation 
	with respect to the page. 
*/
PIPROC(PDRotate, AFPDWidgetGetRotation, (PDAnnot pdan), pdan)

/**  
    This routine is deprecated: use AFPDFieldGetDefaultTextAppearanceEx() instead.

	<p>Gets the default text appearance of a field. Use this method 
	to get the font, size, color, and so on (values that were 
	set through the field properties dialog box). </p>
	@param fldP The PDField object for which to retrieve the 
	text appearance. 
	@param aP A pointer to a structure describing the text 
	appearance. It returns font, size, quadding, text color, and 
	so on up to and including the <code>nameFont</code> field in the text appearance structure. 
	The remaining fields will not be initialized.
	@see AFPDWidgetSetAreaColors
	@see AFPDFieldGetDefaultTextAppearanceEx
*/

PIPROC(void, AFPDFieldGetDefaultTextAppearance, (PDField fldP, TextAppearanceP aP), fldP, aP)

/**
    This routine is deprecated. Use AFPDFieldSetDefaultTextAppearanceEx() instead.

	<p>Sets the default text appearance of a field. Use this method 
	to set the font, size, color, and so on. </p>

	@param fldP The PDField object for which to set the text 
	appearance. 
	@param aP A pointer to a structure describing the text 
	appearance to set. This routine will use the values up to 
	and including the <code>nameFont</code> field in the text appearance structure. 
	@see AFPDWidgetSetAreaColors
	@see AFPDFieldSetDefaultTextAppearanceEx
*/
PIPROC(void, AFPDFieldSetDefaultTextAppearance, (PDField fldP, TextAppearanceP aP), fldP, aP)

/**
	Gets the border of an annotation. 
	@param pdan The annotation. 
	@param pdwb (Filled by the method) A pointer to a structure 
	describing the form field appearance definitions for the 
	outside border of an annotation. 
	@return <code>true</code> if successful getting the border, <code>false</code> otherwise. 
	@see AFPDWidgetSetAreaColors 
*/
PIPROC(ASBool, AFPDWidgetGetBorder, (PDAnnot pdan, AFPDWidgetBorder pdwb), pdan, pdwb)

/**
	Sets the border of an annotation. 
	@param pdan The annotation whose change border appearance 
	will be set. 
	@param pdwb A pointer to a structure describing the form 
	field appearance definitions for the outside border of an 
	annotation. Possible border types are solid, dashed, beveled, 
	inset, and underline.
	@see AFPDWidgetSetAreaColors 
*/
PIPROC(void, AFPDWidgetSetBorder, (PDAnnot pdan, AFPDWidgetBorder pdwb), pdan, pdwb)

/**
	Gets the border and background colors of an annotation. 
	
	@param pdan The annotation. 
	@param borderP (Filled by the method) A pointer to a structure 
	representing the border color of the annotation. 
	@param bkgndP (Filled by the method) A pointer to a structure 
	representing the background color of the annotation. 
	@see AFPDWidgetSetAreaColors 
*/
PIPROC(void, AFPDWidgetGetAreaColors, (PDAnnot pdan, PDColorValue borderP, PDColorValue bkgndP), pdan, borderP, bkgndP)

/**
	Sets the border and background color of the annotation. 
	
	@param pdan The annotation. 
	@param borderP A pointer to a structure representing the 
	border color of the annotation. 
	@param bkgndP A pointer to a structure representing the 
	background color of the annotation. 
	@see AFPDWidgetGetAreaColors 
*/
PIPROC(void, AFPDWidgetSetAreaColors, (PDAnnot pdan, PDColorValue borderP, PDColorValue bkgndP),pdan, borderP, bkgndP)

/**
	Opens the dialog box that allows the user to select a PDF 
	to use as the icon for a button. 
	@param cd The CosDoc that contains the appearance you 
	are trying to import. 
	@param coIcon If AFImportAppearance() is successful, <code>coIcon</code> 
	is a pointer to a CosObj that will contain the Cos representation 
	of the appearance. 
	@param avd The AVDoc that you want as the parent for the window. You can pass <code>NULL</code> if you do not have an AVDoc. 
	
	@param cTitle The window title of the dialog box when 
	it appears. You can pass <code>NULL</code> if you want the title of the 
	dialog box to be the same as it is when brought up through the 
	field properties dialog.
	@return <code>true</code> if appearance was imported properly, <code>false</code> otherwise. 
	
*/
PIPROC(ASBool, AFImportAppearance, (CosDoc cd, CosObj *coIcon, AVDoc avd, char *cTitle), cd, coIcon, avd, cTitle)


/** 
	Sets the text layout for the annotation. 

	<p>It raises an exception if the field is a radio box or button. </p>

	@param vlayout The layout of the annotation. 
	@param bMultline If <code>true</code>, the text can use multiple lines 
	in a text field. Otherwise, the text is a single line. 
	@param bWrap If <code>true</code>, the text will wrap. 
	@param border The border appearance that defines the width 
	and line style of a border. The border of the annotation 
	should be the same as in your call to AFLayoutBorder(). 
	@param ta A pointer to a structure containing font, point 
	size, and color information. You should initialize the structure 
	with the <code>SetDefaultTextAppearanceP</code> macro which defaults 
	to Helvetica. 
	@param cBytes The text string for the layout.
	@param fxMinFontSize The minimum font size, when using autosizing.
	@param fxMaxFontSize The maximum font size, when using autosizing.
	
	@see AFLayoutNew 
	@see AFLayoutBorder 
	@note Before calling this method, you should call AFLayoutNew() 
	to create a new layout, as well as AFLayoutBorder(). 

*/
PIPROC(void, AFLayoutTextEx, (void* vlayout, ASBool bMultline, ASBool bWrap, AFPDWidgetBorder border, TextAppearanceP ta, char* cBytes, ASFixed fxMinFontSize, ASFixed fxMaxFontSize), vlayout, bMultline, bWrap, border, ta, cBytes, fxMinFontSize, fxMaxFontSize)

/** Deprecated as of Acrobat 8.0. */
PIPROC(void, AFLayoutIconText, (void* vLayout, AFPDWidgetPosition nPosition, CosObj coIcon, AFPDWidgetBorder border, TextAppearanceP ta, char *cBytes), vLayout, nPosition, coIcon, border, ta, cBytes)

/* Obsolete. */
PIPROC(ASBool, AFGetScriptingContextEx, (ScriptingData data), data)

/** 
	Executes an AcroForm JavaScript script. 
	@param pdd The PDDoc in which the script is to be executed. 
	
	@param cScript A string containing the text of the script 
	to be executed. If it is Unicode, the string must begin with <code>0xFEFF</code> 
	and end with 2 <code>NULL</code> bytes. If this is not the case, it is 
	assumed to be in the application's language encoding, as 
	returned by AVAppGetLanguageEncoding(). 
	@param pRetValue To get a return value from the execution 
	of the script, pass a non-<code>NULL</code> value for this parameter. 
	If, upon return, <code>*pRetVal</code> is non-<code>NULL</code>, the caller should dispose 
	of the string by calling ASFree(). If present, the value will 
	be in host encoding. 
	@return The JavaScript value of <code>event.rc</code>. This function pre-initializes 
	it to <code>true</code>; a script may set it to <code>false</code> if desired. 
	@note The script sets this value by 
	assigning it to <code>event.value</code>. See the Acrobat JavaScript 
	documentation for more information.
*/
PIPROC(ASBool, AFExecuteThisScript, (PDDoc pdd, const char* cScript, char** pRetValue), pdd, cScript, pRetValue)

/**
	Creates a new layout context for annotations. Use PDAnnotGetRect() 
	to get the annotation's bounding box, then use this method 
	to define new layout context. 
	@param frBbox The bounding box of the area for text and 
	border data to flow into. 
	@param annotRotation The rotation of the annotation. 
	@param cd The CosDoc.
	@return A new layout. 
	@see AFLayoutBorder 
	@see AFLayoutText 
	@see AFLayoutCreateStream 
*/
PIPROC(void*, AFLayoutNew, (ASFixedRectP frBbox, PDRotate annotRotation, CosDoc cd), frBbox, annotRotation, cd)

/**
	Creates a layout stream that can be used as an annotation 
	appearance. 
	@param vlayout The layout of the annotation. Use AFLayoutNew() 
	to create a new layout before calling this method. 
	@return A stream CosObj. 
	@see AFLayoutNew 
	@see AFLayoutDelete 
*/
PIPROC(CosObj, AFLayoutCreateStream, (void* vlayout), vlayout)

/** Deprecated as of Acrobat 8.0. */
PIPROC(ASBool, AFCalculateFields, (PDDoc pdd, ASCab asc), pdd, asc)


/**
	Lays out the text and creates a Cos XObject with the content stream
	for the text and required Resources. This API supports Unicode text. 
	If required, different fonts may be used for different characters in 
	the text. It has support for western scripts, Arabic, Hebrew, Thai, Vietnamese, 
	Chinese, Japanese, and Korean. Other scripts may be added in the future.

	@return A stream CosObj. If the operation fails, then CosNewNull()
	is returned.

	@param cd The CosDoc.
	@param frBbox The bounding box of the area for text and border data to flow into. 
	@param annotRotation The rotation of the annotation. 
	@param bWrap If <code>true</code>, the text will wrap. 
	@param border The border appearance that defines the width. 
	@param fxMinFontSize The minimum font size, when using autosizing.
	@param fxMaxFontSize The maximum font size, when using autosizing and line style of a border.  
	@param textAttrs A pointer to structure containing font, point size, color information, alignment, and writing direction. 
	@param asText The text string for the layout.
	
*/
PIPROC(CosObj, AFDrawText, (CosDoc cd,  ASFixedRectP frBbox, PDRotate annotRotation, ASBool bWrap, AFPDWidgetBorder border, AFTextAttributesP textAttrs, ASConstText asText, ASFixed fxMinFontSize, ASFixed fxMaxFontSize), cd,  frBbox, annotRotation, bWrap, border, textAttrs, asText, fxMinFontSize, fxMaxFontSize)

/**
	Gets the default text appearance of a field. Use this method 
	to get the font, size, color, and other values that were 
	set through the field properties dialog box. 
	@param fldP The PDField object for which to retrieve the 
	text appearance. 
	@param aP A pointer to a structure describing the text 
	appearance. It returns font, size, alignment, text color, and 
	so on. 
	@param size The size in bytes of the structure referenced by <code>aP</code>. Fields in the 
	structure up to this size will be initialized. 
	@see AFPDWidgetSetAreaColors 
*/
PIPROC(void, AFPDFieldGetDefaultTextAppearanceEx, (PDField fldP, TextAppearanceP aP, size_t size),fldP, aP, size)

/**
	Sets the default text appearance of a field. Use this method 
	to set the font, size, color, and so on. 
	@param fldP The PDField object for which to set the text 
	appearance. 
	@param aP A pointer to a structure describing the text 
	appearance to set.
	@param size The size in bytes of the structure referenced by <code>aP</code>. Fields in the 
	structure up to this size will be used. If there are additional fields after this
	size, default values will be used. 
	@see AFPDWidgetSetAreaColors 
*/

PIPROC(void, AFPDFieldSetDefaultTextAppearanceEx, (PDField fldP, TextAppearanceP aP, size_t size),fldP, aP, size)

/**
	Get the default size for a specific field type. This method  
	will get the new default value if the user changes it.
	@param fieldType The ASAtom corresponding to the field type. 
	The string for the type can be converted to an ASAtom using 
	ASAtomFromString().
	@param asfp (Filled by the method) A pointer to a point whose 
	coordinates correspond to width and height of the field.
*/
PIPROC(void, AFGetDefaultFieldSize, (ASAtom fieldType, ASFixedPoint *asfp), fieldType, asfp)








