/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1996-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 AF_ExpT.h

 - Public data types and structures to handle Acrobat Forms objects.

*********************************************************************/

#ifndef _H_AF_ExpT /* { */
#define _H_AF_ExpT

#include "CoreExpT.h"
#include "CosExpT.h"
#include "ASExpT.h"
#ifndef HEADLESS_PDFDRIVER
#include "AVExpT.h"
#endif
#include "PDExpT.h"
#include "ASExtraExpT.h"

/*****************************************************************************
    Callback names
*****************************************************************************/
#ifndef AcroCallback /* { */
#define AcroCallback(type) ACCB1 type ACCB2
#endif /* } */

#ifdef __cplusplus
typedef class CPDField* CPDField_P;
typedef class CWidget* CWidget_P;
typedef class CAgg*	   CAgg_P;
#else
typedef struct CPDField* CPDField_P;
typedef struct CWidget* CWidget_P;
typedef struct CAgg*	CAgg_P;
#endif

/*****************************************************************************
 Return Values from procedures
*****************************************************************************/
typedef enum {Good = 0, Bad, Failed, GoodKeepFDF } RetCode;
#define CB_RetCode AcroCallback(RetCode)

/*****************************************************************************
  This is the character used to separate segments of a composed name.
  For example, "xx.yy" is the name of the field yy in the xx hierarchy.
*****************************************************************************/
#define NameSeparator '.'
#define NameSeparatorStr "."

/*****************************************************************************
  Acrobat Form handler (opaque) definition
*****************************************************************************/
typedef OPAQUE_64_BITS AcroForm;
#define CB_AcroForm AcroCallback(AcroForm)

/*****************************************************************************
  Acrobat Forms Field handler (opaque) definition.
*****************************************************************************/
/** A PDField is an opaque object representing a field in an Acrobat form.
	The three most important properties of a field are its type, name, and value. Other
	properties specify the appearance of a field. Fields can be organized into a hierarchy,
	and other field properties associate it with its parent and children.
	
	<p>There is a field dictionary for every PDField. Acrobat uses annotations to represent a
	field's appearance and to manage user interactions. A PDField dictionary may also
	be an annotation, in which case its subtype is Widget. There is no ambiguity, because
	the keys of annotations and PDField objects do not overlap.</p>
	
	<p>PDField objects are not created until needed. This saves memory and enhances
	performance.</p>

	<p>Suppose, for example, a PDF file represents a 100-page catalog, where a purchase
	order is on the last page. PDField objects are not created for all the elements in the
	purchase order when the document is opened. When the user displays the purchase
	order, the annotation handler draws the field announcements and creates the
	PDField objects for form fields.</p>

	<p>When the annotation handler creates a PDField, it typically displays a page that
	contains the field.</p>
*/
#define PDField CPDField_P
#define CB_PDField AcroCallback(PDField)

/*****************************************************************************
  Types of FormField Flags 
  Flags_Annot are flags defined in the /F key of the annotation
  Flags_Field are defined in the /Ff key of the FormField and apply to any FormField
*****************************************************************************/
/** The type of flag to be set in AFPDFieldSetFlags(). If Flags_Annot,
	SetFlagsAnnot, or ClrFlagsAnnot is specified and the PDField is not an
	annotation, no flags are changed.
	
	<p>See the <i>PDF Reference</i> for more information on flags used for annotations.</p>
	
	@see AFPDFieldSetFlags
*/
typedef enum { 
	/** Sets the flags defined in the F key of the annotation to the
		values specified in the <code>flags</code> parameter of AFPDFieldSetFlags(). 
	*/
	Flags_Annot	= 0,
	/** Sets the flags defined in the Ff key of the form field to the
		values specified in the <code>flags</code> parameter of AFPDFieldSetFlags(). 
	*/
	Flags_Field,
	/** Sets the bits in the flags to those that are <code>1</code>s in the <code>flags</code>
		parameter of AFPDFieldSetFlags(). 
	*/
	SetFlagsAnnot,
	/** Clears the bits in the flags to those that are <code>1</code>s in the <code>flags</code>
		parameter of AFPDFieldSetFlags(). 
	*/
	ClrFlagsAnnot,
	/** Sets the bits in the flags to those that are <code>1</code>s in the <code>flags</code>
		parameter of AFPDFieldSetFlags(). 
	*/
	SetFlagsField,
	/** Clears the bits in the flags to those that are <code>1</code>s in the <code>flags</code>
		parameter of AFPDFieldSetFlags(). 
	*/
	ClrFlagsField,
	/** Does not change any flags for the field or annot.
	*/
	Flags_Ignore
} AF_Flags_t;

/*****************************************************************************
  FormField Flags Definition
*****************************************************************************/
/** Used for the value of <code>flags</code> set by AFPDFieldSetFlags. */
typedef ASUns32 AFPDFieldFlags_t;
#define CB_AFPDFieldFlags_t AcroCallback(AFPDFieldFlags_t)

#define Clear_F				((AFPDFieldFlags_t)0x00000000)

/*****************************************************************************
  FormField Flags Definition that apply to all FormField types
  The following flags are stored in the /Ff object of the FormField dictionary.
*****************************************************************************/
#define AllFieldMask_F		((AFPDFieldFlags_t)0x00000FFF)

#define AFAVignore_F		((AFPDFieldFlags_t)0x00000001)
#define Required_F			((AFPDFieldFlags_t)0x00000002)
#define NoExport_F			((AFPDFieldFlags_t)0x00000004) /* won't export its value */

/*****************************************************************************
  FormField Flags Definition that apply to a single field type
  The following flags are stored in the /Ff object of the FormField dictionary.
*****************************************************************************/

/* Text FormFields */
#define MultiLine_F			((AFPDFieldFlags_t)0x00001000)
#define Password_F			((AFPDFieldFlags_t)0x00002000) /* Single line text fields only */
#define FileSelect_F		((AFPDFieldFlags_t)0x00100000) /* Single line text fields only */
#define DoNotSpellCheck_F	((AFPDFieldFlags_t)0x00400000) /* Applicable to editable combo boxes too */
#define DoNotScroll_F		((AFPDFieldFlags_t)0x00800000)
#define Comb_F				((AFPDFieldFlags_t)0x01000000)
#define RichText_F			((AFPDFieldFlags_t)0x02000000) /* Note: the PDF 1.5 spec says this is bit 28, it is really bit 26 and overlaps with 
																RadiosInUnison_F */

/* Button FormFields */
#define StayPushed_F		((AFPDFieldFlags_t)0x00004000)
#define Radio_F				((AFPDFieldFlags_t)0x00008000)
#define Push_F				((AFPDFieldFlags_t)0x00010000)

/* If on, this bit makes radio buttons work like in Acrobat 4, where multiple radio buttons (belonging to the
** same field) will turn on and off in unison if they have the same export value. By contrast, with Acrobat 5,
** radio buttons are always mutually exclusive, like in HTML */
#define RadiosInUnison_F	((AFPDFieldFlags_t)0x02000000)

/* Choice FormFields */
#define PopUp_F				((AFPDFieldFlags_t)0x00020000)
#define Editable_F			((AFPDFieldFlags_t)0x00040000)
#define OptionsSorted_F		((AFPDFieldFlags_t)0x00080000)
#define MultipleSelection_F	((AFPDFieldFlags_t)0x00200000)
#define CommitOnSelChange_F	((AFPDFieldFlags_t)0x04000000) /* http://hypermail.corp.adobe.com/mail-archive/acrobat6/msg00124.html */

/* Text FormFields - additions */

#define ParDirectionRTL_F	((AFPDFieldFlags_t)0x10000000) /* If set the Paragraph direction is right to left, otherwise it is left to right */


/*****************************************************************************
  FormField General Appearance definitions
*****************************************************************************/
/** Form field appearance definitions for the outside border of an annotation.
	@see AFLayoutBorder
*/
typedef enum {
	/** Strokes the entire perimeter of the widget with a solid line. */
	AFPDWBSolid = 0,
	/** Strokes the entire perimeter of the widget with a dashed line. */
	AFPDWBDashed,
	/** Equivalent to the AFPDWBSolid style with an additional beveled
		(pushed-out appearance) border applied inside the solid border. 
	*/
	AFPDWBBeveled,
	/** Equivalent to the AFPDWBBeveled style with an additional beveled
		(pushed-in appearance) border applied inside the solid border. 
	*/
	AFPDWBInset,
	/**  Strokes the bottom portion of the widget with a underline styled line. */
	AFPDWBUnderline,
	/** Do not change the border. */
	AFPDWBInvalid
} AFPDWidgetBorderStyle;

/** Form field appearance definitions for the outside border of an annotation.
	@see AFLayoutBorder
	@see AFLayoutText
	@see AFPDWidgetGetBorder
	@see AFPDWidgetSetBorder
*/
typedef struct _AFPDWidgetBorderRec
{
	/** The style of the border. The possible types are solid, dashed, beveled,
		inset, and underline. 
		@see AFPDWidgetBorderStyle. 
	*/
	AFPDWidgetBorderStyle nStyle;
	/** The width of the border. */
	ASInt32 			nWidth;
} AFPDWidgetBorderRec, *AFPDWidgetBorder;

/** Field border data type.
	@see AFLayoutBorder
	@see AFLayoutText
	@see AFPDWidgetGetBorder
	@see AFPDWidgetSetBorder
*/
typedef AFPDWidgetBorderRec AFPDFieldBorder;

typedef enum {
	AFPDWPTextOnly = 0,
	AFPDWPIconOnly,
	AFPDWPIconOverText,
	AFPDWPTextOverIcon,
	AFPDWPIconText,
	AFPDWPTextIcon,
	AFPDWPTextInIcon,
	AFPDWPInvalid
} AFPDWidgetPosition;

/*****************************************************************************
  Text Appearance and Quadding definitions
*****************************************************************************/
#define LeftQ    (ASUns16)0 /* Default quadding value */
#define CenterQ  (ASUns16)1
#define RightQ   (ASUns16)2

enum { Fill_text=0, Stroke_text=1, FnS_text=2, Invisible_text=3 } ;

/* Options for Middle Eastern scripts */
/** The default paragraph direction is right to left. */
#define	kAFOptionsR2LDirection 	((ASUns32)0x0001)


enum
{
	kAFAlign_Left,
	kAFAlign_Center,
	kAFAlign_Right,
	kAFAlign_Justify,
	kAFAlign_JustifyAll
};
typedef ASEnum8 AFHorizontalAlign;

enum
{
	kAFAlign_Top,
	kAFAlign_Middle,
	kAFAlign_Bottom
};
typedef ASEnum8 AFVerticalAlign;

typedef struct {
	/** The size of the structure. Clients must initialize with the size of the structure. */
	size_t	size;

	/** The default font name. */
    ASText          fontName;

 	/** The point size of the text. When it is <code>fixedZero</code>, it enables text autosizing. */
    ASReal			textSize;

	/** The text justification. */
    AFHorizontalAlign  horizontalAlignment;

	/** The vertical Alignment */
	AFVerticalAlign		verticalAlignment;

	/** The text color. */
    PDColorValueRec fillColor;

	/** Options. 
	@see kAFOptionsR2LDirection
	*/
    ASUns32			options; 

	/** Native Zero digit. */
	ASUnicodeChar	nativeZeroDigit;

} AFTextAttributesRec, *AFTextAttributesP;

/** A structure containing information about the text appearance of a field.

	@see Init_TextAppearanceP

*/

/* ADD new entries at the end */
typedef struct {
	/** The spacing between characters. */
    ASFixed         charSpacing;
	/** The spacing between words. */
    ASFixed         wordSpacing;
	/** The horizontal scale. */
    ASFixed         horizontalScale;
	/** The leading. */
    ASFixed         leading;
	/** The text rise. */
    ASFixed         textRise;
	/** The point size of the text. When it is <code>fixedZero</code>, it enables text autosizing. */
    ASFixed         textSize;
	/** The font matrix. */
    ASFixedMatrix	textMatrix;
	/** The pen color. */
    PDColorValueRec strokeColor;
	/** The fill color. */
    PDColorValueRec fillColor;
	/** The mode. */
    ASUns16         renderMode;
	/** The text justification. */
    ASUns16         quadding;
	/** The default font name. */
    ASAtom          baseFont;
	/** The current font name.  */
    ASAtom          nameFont;
	/** Options.
		@see kAFOptionsR2LDirection
		@note New in Acrobat 7.0. 
	*/
    ASUns32			options; 
	/** Native Zero digit.  
		@note New in Acrobat 7.0. 
	*/
	ASUnicodeChar	nativeZeroDigit;

}TextAppearance_t, *TextAppearanceP;

#define AutoSize fixedZero

/** Macro for setting text appearance.*/
#define Init_TextAppearanceP(aP) {\
  memset(aP, 0, sizeof(TextAppearance_t));\
  (aP)->baseFont = ASAtomNull;\
  (aP)->nameFont = ASAtomNull;\
}

/** Macro for setting text appearance. This macro uses Helvetica as the default font. */
#define SetDefault_TextAppearanceP(aP) {\
  memset(aP, 0, sizeof(TextAppearance_t)); \
  (aP)->baseFont = ASAtomFromString("Helvetica");\
  (aP)->nameFont = ASAtomNull;\
  (aP)->textSize = AutoSize;\
  (aP)->horizontalScale = fixedHundred;\
  (aP)->renderMode = Fill_text;\
  (aP)->fillColor.space = PDDeviceGray;\
  (aP)->textMatrix.a = fixedOne;\
  (aP)->textMatrix.d = fixedOne;\
  (aP)->quadding = LeftQ;\
  (aP)->nativeZeroDigit = 0x0030;\
}

/** Macro for checking whether a text appearance is valid. */
#define TextApperanceIsValid(aP) (\
  (aP)->quadding <= RightQ && \
  (aP)->renderMode <= Invisible_text && \
  (aP)->baseFont != ASAtomNull && \
  (aP)->textSize >= AutoSize)


/*****************************************************************************
  Listbox and Combobox Choices
*****************************************************************************/
/*	_ESTRREC
**	Use define to stop "Warning : identifier 'EStr' redeclared" for strict compilers.
**	This same typedef in also in "miEStr.h".
*/
#ifndef _ESTRREC
#define _ESTRREC
typedef struct _EStrRec *EStr;
typedef const struct _EStrRec *EConstStr;
#endif

/*****************************************************************************
 AcroForms Notification Server 
*****************************************************************************/
/** Deprecated as of Acrobat 8.0. */
typedef ACCBPROTO1 void (ACCBPROTO2 *AF_NotificationProc)(void *info, void *clientData);
/** Deprecated as of Acrobat 8.0. */
typedef ACCBPROTO1 void (ACCBPROTO2 *AF_NotificationFailureProc)(ASInt32 error, void *info, void *clientData);

/*****************************************************************************
  AcroForms Notification server index definition and arguments
  
  These are the arguments in AF_NtfyParams_t which are applicable:
  
  FieldValueWillChange	 	: pdd, pCPDFld, esValue, rc
  FieldValueDidChange	 	: pdd, pCPDFld, esValue
  AcroFormWasCreated 		: pdd

							  Note that renaming a field results in FieldWillBeRemoved followed by FieldWasAdded
  FieldWasAdded				: pdd, pCPDFld, pCWidget and pdAnnot (for the specific annot that was added)
  FieldWillBeRemoved		: pdd, pCPDFld, pCWidget and pdAnnot (for the specific annot that will be removed)
  FieldChangedType			: pdd, pCPDFld, asaFieldType (the previous type)
  FieldValidateChange		: pdd, pCPDFld, esValue, esChange, nSelStart, nSelEnd, rc, style, fieldFull, esChangeEx
  FieldWillGenerateDisplay	: pdd, pCPDFld, esValue
  FDFWillImport				: cd, rc. Set rc to 0 if you handled the FDF, and Forms doesn't need to. If you
							  return rc equal to 0, you can additionally OR it with KeepFDF_F if you don't
							  want Forms to delete the FDF.
  FDFWillImportHaveDoc		: pdd, cd, rc. Set rc to 0 if you handled the FDF, and Forms doesn't need to.
							  Regardless of whether you set rc to 0 or 1, OR it with KeepFDF_F if you
							  *did* handle the FDF, but still want Forms to keep the FDF around for
							  re-import, which is important in the scenario that we are running in
							  the browser, and the user leaves the web page containing the PDF, in
							  case the user later should return to that same page).
  
  FDFWillExport				: pdd, cd, nSubmitFlags. When Forms sends this notification, cd will be NULL.
							  The first listener who gets the notification and acts on it will need to
							  create the FDF and set cd. If the FDF that is about to be created
							  will be used simply as an intermediate step for XML export, then this
							  notification will include the argument "cos2XMLEngine", else that
							  field in params will be NULL.

  XFDFWillImport			: cd (CosDoc for the FDF being created from the XFDF), cos2XMLEngine
 
  TextFieldSelectionDidChange : pCPDField, pCWidget, nSelStart, nSelEnd, nCursorPos,
								cValue (Unicode (Host Endian) bytes of field value),
								len (length of cValue in bytes),
								avPageView (pageView containing	the AVTE),
								pdAnnot
  FieldAttributeDidChange	: pdd, pCPDFld, pCWidget, pdAnnot,
							  asaFieldType (this is the ASAtom of the attribute that changed)
  TextFieldValueDidChange	: pCPDField, pCWidget, nSelStart, nSelEnd, nCursorPos,
							cValue (Unicode (Host Endian) bytes of field value),
							len (length of cValue in bytes),
							avPageView (pageView containing	the AVTE),
							pdAnnot
  DynamicDocWillRender		: pdd
  DynamicDocDidRender		: pdd
  ContextSelectionDidChange : pdd

  Note: In all cases, the sender of the notification is responsible for deleting any EStrs
  
*****************************************************************************/

/** Deprecated as of Acrobat 8.0. */
typedef enum { 
	/** */
	FieldValueWillChange		= (ASInt32)0,
	/** */
	FieldValueDidChange,
	/** */
	AcroFormWasCreated,
	/** */
	FieldWasAdded,
	/** */
	FieldWillBeRemoved,
	/** */
	FieldChangedType,
	/** */
	FieldValidateChange,	
	/** */	
	FieldWillGenerateDisplay,
	FDFWillImport,
	/** */
	FDFWillImportHaveDoc,
	/** */
	FDFWillExport,
	/** */
	XFDFWillImport,
	/** */
	TextFieldSelectionDidChange,
	/** */
	FieldAttributeDidChange,
	/** */
	TextFieldValueDidChange,
	/** */
	DynamicDocWillRender,
	/** */
	DynamicDocDidRender,
	/** */
	ContextSelectionDidChange,
	/** */
	AcroFormNumNotifications	/* Always last */
} AF_NotificationSelector_t;

/** Deprecated as of Acrobat 8.0. */
typedef struct {
	/** */
	PDDoc 				pdd;
	/** */
	CPDField_P			pCPDFld;
	/** */
	CWidget_P			pCWidget;
	/** */
	struct _EStrRec*	esValue;
	/** */
	struct _EStrRec*	esChange;
	/** */
	struct _EStrRec*	esChangeEx;
	/** */
	ASBool				fieldFull;
	union
	{
		/** */
		ASInt32			nSelStart;
		/** */
		ASUns32			nSubmitFlags;
	};
	/** */
	ASInt32				nSelEnd;
	/** */
	RetCode 			rc;
	/** */
	CosDoc				cd;
	/** */
	ASAtom				asaFieldType;
	/** */
	void*				cos2XMLEngine;
	/** */
	const char*			cValue;
	/** */
	ASInt32				len;
	/** */
	ASInt32				nCursorPos;
#ifndef HEADLESS_PDFDRIVER
	/** */
	AVPageView			avPageView;
#endif
	/** */
	PDAnnot				pdAnnot;

	/** */
	CAgg_P				richChange;
	/** */
	CAgg_P				richChangeEx;
	/** */
	CAgg_P				richValue;
	/** */
	ASBool				bModified;
} AF_NtfyParams_t;


/*****************************************************************************
 Type for the callback procedures
*****************************************************************************/
/** Callback used by AFPDDocEnumPDFields(). It is called once for each PDField in a form.
	@return <code>true</code> to continue the enumeration, <code>false</code> to halt the enumeration.
	@param fldP IN The PDField currently being enumerated.
	@param clientData IN/OUT User-supplied data passed in the call to AFPDDocEnumPDFields().
	@see AFPDDocEnumPDFields
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AFPDFieldEnumProc)(PDField fldP, void *clientData);

/*****************************************************************************
 Flags for the Submit Form action
*****************************************************************************/
typedef ASUns32 ActionFlags_t;
#define InclOrExcl_F		((ActionFlags_t)0x0001)
#define InclEmpty_F			((ActionFlags_t)0x0002)
#define UrlEnc_F			((ActionFlags_t)0x0004)
#define GetMethod_F			((ActionFlags_t)0x0008)
#define SubmitCoords_F		((ActionFlags_t)0x0010)
#define XFDF_Enc_F			((ActionFlags_t)0x0020)
#define InclAppendSaves_F	((ActionFlags_t)0x0040)
#define InclAnnotations_F	((ActionFlags_t)0x0080)
#define SubmitPDF_F			((ActionFlags_t)0x0100)
#define CanonicalFormat_F	((ActionFlags_t)0x0200)
#define ExclNonUserAnnots_F	((ActionFlags_t)0x0400)
#define ExclFKey_F			((ActionFlags_t)0x0800)
#define XDP_Enc_F			((ActionFlags_t)0x1000)
#define EmbedForm_F			((ActionFlags_t)0x2000)
#define InclNMKey_F			((ActionFlags_t)0x4000)
#define XML_Enc_F			((ActionFlags_t)0x8000)
#define XFD_Enc_F			((ActionFlags_t)0x10000)
#define URL_Enc_F			((ActionFlags_t)0x20000)

/*****************************************************************************
 ExportAsFDFParams
 Used in the call to ExportAsFDFWithParams
*****************************************************************************/
#ifndef HEADLESS_PDFDRIVER
/** A parameter block used in the call to ExportAsFDFWithParams(). */
typedef struct _t_ExportAsFDFParams {
	/** The size of the data structure. It must be set to <code>sizeof(ExportAsFDFParamsRec)</code>.
	 */
	ASSize_t	size;		
	/** The AVDoc for the form from which you want to export the data.
		You can pass <code>NULL</code> if the document does not have an AVDoc
		(that is, it is open only at the PD level).
	*/
	AVDoc		avForm;		
	/** The PDDoc for the form from which you want to export the data. */
	PDDoc		pdForm;		
	/** If <code>rgIncExcFlds</code> is CosNewNull(), then all fields are exported, and
		<code>bIncl</code> is ignored. If it is a CosArray, then the array elements may be:
	
		<ul>
		<li> Names of fields (the names may be of non-terminal fields, which is a
		fast and easy way to cause all their children to be included in the FDF). </li>
		<li> Arrays whose first element is a field name whose remaining elements are 
		field dictionary key names whose values should be
		exported in the FDF. For example:  <code>[ (My listbox) /AP /Opt ]</code> </li>
		<li> If rgIncExcFlds contains a single element, which is itself
		an array as described above, and its first element, which
		corresponds to the field name, is <code>NULL</code>, then the FDF will
		include the requested field properties of all fields. 
		For example, <code>[ null /F /Ff ]</code> </li>
		</ul>
			
		<p>This variety of <code>rgIncExcFlds</code> array element can only be used if
		<code>bIncl</code> is <code>true</code>. </p>
	*/
	CosObj		rgIncExcFlds; 
	/** If <code>true</code>, then <code>rgIncExcFlds</code> is an array of the fields to export. Otherwise,
		<code>rgIncExcFlds</code> is an array of the fields to exclude from exporting. 
	*/
	ASBool		bIncl;		
	/** If <code>true</code>, then all fields selected per the criteria above are exported.
		Otherwise those that have no value are excluded. 
	*/
	ASBool		bEmpty;		
	/** If <code>true</code>, the FDF text fields that have the
		<code>"password"</code> flag set will not be included.
	*/
	ASBool		bExcludePasswd; 
	/** If <code>true</code>, an alert pops up if any required field is empty. */
	ASBool		bCheckReqd;	
	/** Encoding to use in the produced FDF file for the value of the V
		entry when it is a string. If ASAtomNull is passed, then
		ExportAsFDF() will determine which encoding to use. If
		PDFDocEncoding is passed, then do not perform any encoding
		conversions and simply send V as is (which means as
		PDFDocEncoding or Unicode).
		
		<p>Other allowed values are Shift_JIS, BigFive, GBK, and
		UHC.</p>
	*/
	ASAtom		asaEncoding; 
	/** The path where the FDF file will be saved (by the client) after it is
		produced (by ExportAsFDFWithParams()). You need this in
		order to create an FDF file with an /F key that gives the relative
		path to the form from the location where the FDF file will be
		saved. Pass <code>NULL</code> if you want an absolute pathname.
	*/
	ASPathName	fdfPath;	
	/** Corresponding file system for <code>fdfPath</code>.
	*/
	ASFileSys	fdfFilesys;
	/** A <code>NULL</code>-terminated string containing the name of the button
		used to submit. If the value passed is not <code>NULL</code>, then the FDF file
		will include a field dictionary corresponding to the submit
		button, which will only contain one key, namely /T. This
		dictionary is no different than the one you get when an
		AcroForm has an empty text field (that is, no Value), and
		<code>bEmpty</code> is <code>true</code>.
	*/
	char*		submitBtnName; 
} ExportAsFDFParamsRec, *ExportAsFDFParams;
#endif // ndef HEADLESS_PDFDRIVER

typedef void* ScriptingData; // Deprecated		   

#endif /* _H_AF_ExpT  } */
