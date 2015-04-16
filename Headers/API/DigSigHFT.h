/*************************************************************************
 * DigSigHFT.h
 *
 * Copyright (c) 1998-2006 Adobe Systems Inc. All Rights Reserved.
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
 * Handlers can register as <code>DigSig</code> handlers to provide digital
 * signature services.  Handlers can also call back into the DigSigHFT
 * for various services.
 *
 * Update History: (most recent first)
 * 10-Dec-2009 - Add long file support (64-bit offsets) for Acrobat 10.0 SDK
 * 21-Mar-2003 - Last known edit for Acrobat 6.0 SDK
 * 05-Feb-2003 - Cleanup for Acrobat 6.0 SDK
 * 10-Jan-2003 - Added handlerName parameter to some new calls
 * 16-Dec-2002 - Acrobat 6.0 cleanup
 * 31-Aug-2001 - Added SigSeedValue object
 * 25-Aug-2000 - Add DigSigAP helper routines
 * 01-Jul-2000 - Introduce EScript support
 * 12-Nov-1998 - Export Compare Pages/Words to allow scripting
 * 20-Mar-1998 - Created
 ************************************************************************/


/*************************************************************************
 * OVERVIEW OF USAGE
 *
 * Digital signatures use a generic DigSig plugin supplied by Adobe, and one 
 * or more specific method plugins supplied by Adobe and third parties. This 
 * file defines the interface between DigSig and a specific method plugin, 
 * XxxxSig. 
 *
 * Note that enriched support for public key digital signatures and encryption
 * is available using the PubSecHFT, introduced in Acrobat 6.0.
 * Developers are encouraged to use the PubSecHFT rather then DigSigHFT.
 * The PubSec code uses DigSig for digital signature operations, but provides
 * many additional benefits.
 *
 * The reader is assumed to be familiar with the Acrobat SDK Plug-in Guide.
 *
 * Upon startup of Acrobat, there is a 3-step initialization sequence, 
 * consisting of
 *		1) all plug-ins export Host Function tables (HFTs)
 *		2) all plug-ins import HFTs
 *		3) all plug-ins perform initialization
 * This sequence allows plugins to establish communication among themselves 
 * without being dependent on the order of loading. For digital signatures, 
 * the sequence is:
 *
 *		1) DigSig exports its HFT under the name "DigSigHFT"
 *		2)		XxxxSig imports the DigSig HFT
 *				YyyySig imports the DigSig HFT
 *		3)		XxxxSig calls DigSigRegisterFilter to handle signatures of 
 *					type /Xxxx:PPK
 *				YyyySig calls DigSigRegisterFilter to handle signatures of 
 *					type /Yyyy:Finger
 *				These registrations include passing to DigSig a struct of 
 *				callback routines and other information.
 *		...
 * Eventually, the user opens a document.
 *		DigSig calls XxxxSig and YyyySig to notify them of the new document; 
 *		they might allocate some storage or choose to automatically validate 
 *		any of their respective signatures in the document. Note that auto-
 *		validation may encounter significant delays if it requires reading 
 *		the entirety of a large document off a CD-ROM or over a network, or 
 *		it requires accessing some signature registry or authority over a 
 *		network; Adobe software will only access signatures at user request.
 *		4) DigSig calls XxxxSig.docOpen()
 *		   DigSig calls YyyySig.docOpen()
 *
 * If the user creates a signature field and does not specify a default 
 * signing method, DigSig handles that with no communication to the method 
 * plugins. 
 *		DigSig creates the signature field dictionary
 *		DigSig creates the signature annotation dictionary
 *		DigSig creates the (blank) signature appearance dictionary
 *
 * Signature fields can also be created by the Forms plugin.
 *
 * If the user deletes a signature field, DigSig handles that with no 
 * communication to the method plugins. 
 *
 * If the user creates a signature field and specifies a default method, that 
 * plugin is called to fill in default values:
 *		DigSig creates the signature field dictionary
 *		DigSig creates the signature annotation dictionary
 *		DigSig creates the (blank) signature appearance dictionary
 *		5) DigSig calls XxxxSig.defaultValue
 *				XxxxSig creates the default signature value dictionary
 *				XxxxSig creates /DV in the signature field dictionary 
 *					pointing to this
 *
 * If the user asks to sign a specific signature field using method XxxxSig,
 * DigSig sequences the interaction. This sequence is now a four-step process 
 * (the routine names are all different so that you can write transitional code 
 * that includes both the old and new style interaction). The new interaction 
 * looks like this:
 *
 *		Call XxxxSig.dsNewSigData			-- Do any dialogs, gather 
 *											   signature, save in memory
 *											   YOU MAY USE THE DV (default value)
 *											   part of sigfield if sigfield is not COSNULL
 *		if !cancel
 *		  Call XxxxSig.dsUnValidateSig on each signature
 *		  Calculate /Changes
 *		  Do save-as dialog for file name and OK/Cancel
 *		  if !cancel
 *		    Call XxxxSig.dsCommitSign64 (or dsCommitSign)	-- Alter document in memory
 *		    if !cancel
 *		      Do any side effects on other fields	
 *		      Insert /Changes				-- Save document on disk
 *		      Do actual save				-- Save document on disk
 *		      if !cancel
 *		        Call XxxxSig.dsFinishSign[64]	-- Update document on disk
 *		Call XxxxSig.dsFreeSigData			-- Free up memory
 *
 *		6a) DigSig calls XxxxSig.dsNewSigData
 *			XxxxSig interacts with the user, and allows Cancel
 *			XxxxSig acquires the signature itself in a method-specific 
 *			way. All information is saved in memory, without altering 
 *			the document itself. This allows a later backout.
 *		6b) If dsNewSigData does not cancel, DigSig prepares the document 
 *			for saving. It first calls dsUnValidateSig on every 
 *			signature in the document to put any over/underprinting in
 *			cannonical form. It then counts how many pages and fields 
 * 			have changed since any prior signature and records this.
 *		6c) For a first signature, DigSig does the save-as dialog, 
 *			allowing the user to select filename, optimization, and 
 *			encryption. Or the user may cancel. Other than fatal errors
 *			such as out-of-disk-space, this is the point of no return.
 *
 *		6d) If the user does not cancel, DigSig calls XxxxSig.dsCommitSign64 or dsCommitSign 
 *			to update the document with the actual signature.
 *			XxxxSig creates the signature dictionary, possibly using 
 *			 information in the signature field /DV dictionary; some 
 *			 portions have dummy values, at least including the /ByteRange 
 *			 and /Contents keys
 *			XxxxSig points /V in the signature field dictionary to this
 *			XxxxSig creates the /AP /N value in the signature annotation 
 *			 dictionary, using a method-specific visible representation of 
 *			 the signature, including a symbol signifying "unvalidated 
 *			 signature" 
 *			XxxxSig may allocate dynamic storage for a marked array
 *			XxxxSig returns an array of "marked" COS objects that it 
 *			 cares about; this array includes at least the /ByteRange and 
 *			 /Contents value objects
 *		7a) DigSig inserts the /Changes array from 6b.
 *		7b) DigSig saves the PDF document to a file. For each Cos object in 
 *			the marked array, DigSig records the objects byte offset and 
 *			length in the file as written. The saved file may have objects 
 *			encrypted by the Acrobat standard encryption handler, if the user 
 *			so chooses.
 *			The very first time a document is signed, this save may rename 
 *			the file and may invoke the Optimizer, Linearizer, and Garbage 
 *			Collector. Upon return from the save, all COS objects are invalid, 
 *			including those in the marked array. Also, all PD-level objects 
 *			except the PDDoc are invalid. Signing methods must not depend on 
 *			saving any such state between dsCommitSign[64] and dsFinishSign[64]. In 
 *			particular, the byte offsets and lengths in the marked array are
 *			valid upon entry to doSign, but the COS objects are not. The order 
 *			of entries is unchanged, however.
 *				[these COS objects will be rewritten by DigSig as 
 *				 CosNull before calling dsFinishSign[64].]
 *		7c) DigSig calls XxxxSig.dsFinishSign[64], passing back in the marked array
 *			XxxxSig calculates the /ByteRange that it desires, using the 
 *			 byte offsets and lengths in the marked array.
 *			XxxxSig overwrites the marked /ByteRange value in the saved 
 *			 file, using the DigSigOverwriteIntArray or 
 *			 DigSigOverwriteBytes callback 
 *			XxxxSig overwrites any other marked Cos objects it wants to
 *			XxxxSig calculates any document digest that it desires, using 
 *			 the DigSigFileGetEOF, DigSigFileSetPos, and DigSigFileRead 
 *			 callbacks; or it may use the DigSigMD5ByteRange callback
 *			XxxxSig obscures or encrypts this digest in a method-specific 
 *			 way
 *			XxxxSig overwrites the marked /Contents value in the saved 
 *			 file, using DigSigOverwriteHexstring or DigSigOverwriteBytes
 *			XxxxSig may delete dynamic storage for the marked array
 *			XxxxSig returns
 *		8) DigSig calls XxxxSig.dsFreeSigData, which may free up any
 *			remaining storage 
 *
 * If the user asks to validate one or more signature fields, DigSig sequences 
 * though them one at a time:
 *		9) DigSig calls XxxxSig.validateSign
 *			XxxxSig re-calculates any document digest that it desires, 
 *			 using the DigSigFileGetEOF, DigSigFileSetPos, and 
 *			 DigSigFileRead callbacks; or it may use the DigSigMD5ByteRange 
 *			 callback
 *			XxxxSig compares this result to the stored one, and does any 
 *			 other method-specific checks it desires.
 *			XxxxSig optionally does a validation against some stored 
 *			 (network) registry.
 *			XxxxSig updates the /AP /N value in the signature annotation 
 *			 dictionary to show doublechecked/pass/fail symbol
 *			XxxxSig returns doublechecked/pass/fail
 *
 * The user may open more than one document at a time, and may switch between 
 * open documents at will.
 *
 * The user may ask to show a signature panel containing summary information 
 * for each signature in an open document. If multiple documents are open, 
 * there may be multiple panels, or a single panel may be repainted as the 
 * user switches between documents. DigSig manages updating the panel(s), but 
 * may call the respective method plugin for each signature to get information 
 * to display on the panel. For each signature, the signature panel has two 
 * levels of detail:
 *		10a) CLOSED displays a doublechecked/pass/fail/unknown/blank icon and 
 *			a line of text for each signature field in the document. The 
 *			default text is the name of the person signing and the date and 
 *			time of signing, displayed in a language-independent way. 
 *		  DigSig calls XxxxSig.validState to choose which icon to show
 *
 *		10b) OPEN displays an icon and line of text for each signature, then
 *			indented lines of further text, currently consistingof the name 
 *			of the signer, date and time of signing, location of signing, 
 *			reason for signing, and signing method
 *		  DigSig calls XxxxSig.validState to choose which icon to show
 *
 * A method plugin may wish to asynchronously have the signature panel for 
 * a document updated (it might be doing validation as a background or 
 * idle-loop task). To do this, XxxxSig calls back to DigSigUpdatePanel
 *
 * Eventually, the user closes a document.
 *		11) DigSig calls XxxxSig.docClose()
 *		    DigSig calls YyyySig.docClose()
 * 
 * Whenever a signature is created or verified, the method plugin may 
 * optionally alter the appearance of the signature in the document, for
 * the purpose of displaying or printing. For example, it could change
 * an overprinted question mark on an unverified signature to an underprinted 
 * logo for a verified signature. To help with this, DigSig provides an HFT 
 * callback DigSigGetStdXObj that returns an XObject for for a blank appearance, 
 * a queston mark, or a cross. These are suitable as targets of the Do operator
 * in a signatures appearance stream.
 *
 * To avoid saving a signature to a file with an appearance of valid (rather 
 * than unvalidated), just before each file save DigSig loops through all the 
 * signature fields and calls the specific methods dsUnValidateSig entry. This
 * routine may choose to restore the signatures appearance to the unvalidated
 * state.
 *
 * The purpose of the /Changes array is to pre-calculate at each save whether
 * any changes (other than the signature being applied) have been made to the 
 * document since the prior signature. This allows at subsequent document-open
 * time the quick display of a warning symbol on the Signatures panel if the
 * document was changed between any two signatures. The user may choose to 
 * roll back to the document to just before such a change and study the
 * difference between that document and the final one. This warning was a strong
 * customer request.
 *
 * There is now a constraint on the values in the /ByteRange array. This 
 * constraint allows DigSig to implement rollback to prior signatures:
 *		The largest offset + length value in the /ByteRange array
 *		for a given signature must be equal to the length of the PDF file
 *		containing that signature; i.e. it must equal offset + 1 of the 
 *		"F" in the %%EOF at the end of the file. 
 * In addition, the following constraints are strongly encouraged:
 *		All offsets must be in the range 0..2147483647
 *		All lengths must be in the range 1..2147483647
 *		offset[n+1] must be strictly greater than offset[n] + length[n]
 *
 * Using the '64' versions of the calls, offsets and lengths must be in the range 0..2^64-1
 * 
 * The AcroForms Widget Annot handler calls into DigSig using four entries. 
 * These calls all reflect user actions taken in the document view, not the 
 * Signatures panel view.
 *
 * When the user selects an annotaiton by tabbing to it or by clicking it with 
 * the mouse, and that annotation is for a signature field, AcroForms calls 
 * DigSigDraw. bIsSelected is <code>true</code> if the anotaiton is selected.
 *
 * When the user tabs to a signature annotation and activates it by hitting 
 * the spacebar or enter key, this is equivalent to a left mouse click. 
 * AcroForms calls DigSigKeyDown. The parameters parallel those of 
 * AVAnnotHandlerDoKeyDownProc.
 * 
 * When the user left-clicks inside a signature annotation, AcroForms calls 
 * DigSigClick. The parameters parallel those of DoClickProcType.
 * 
 * When the user right-clicks inside a signature annotation, AcroForms calls 
 * DigSigRightClick.
 *
 ************************************************************************/

#ifndef _H_DigSigHFT
#define _H_DigSigHFT

#include "AF_ExpT.h"	// Acroforms HFT

#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************************
 * DigSigHFT globals
 ***********************************************************************************/
/* ---- Global typedefs, consts, and enums ---- */
#define DIGSIG_HFT_NAME "DigSigHFT"
#define DIGSIG_HFT_LATEST_VERSION (0x00020000)	//Not currently in use

extern HFT gDigSigHFT;


/** ESObject is an EScript object that is supported as of Acrobat 5.0
	by the escript plug-in. The EScript HFT has not been exposed to
	third party developers, thus you should use or assume <code>NULL</code> for
	ESObject parameters.  Signature support for EScript is available
	only when using the PubSecHFT for public-key signatures.
*/
typedef struct _s_ESObjectRec	ESObjectRec,	*ESObject;

/** Return values of <code>DS</code> calls (DSRetCode, or ASInt32).  All negative
	return values are considered exceptions.  If the value is kDSException, 
	exception text should be available from the called routine.  If
	this exception text is <code>NULL</code>, it should be considered an unknown error.
*/
typedef ASInt32 DSRetCode;

/** 
	Get the exception string. When this is returned,
	the exception text should be available from the called
	routine. If the exception text is <code>NULL</code>, it is
	considered to be an unknown error.
*/
#define kDSException		-2
/**
	Error in a parameter to the function call. There is no
	exception string.
*/
#define	kDSParameterError	-1
/** A boolean return value. */
#define kDSFalse			0
/** A boolean return value. */
#define kDSTrue				1
/** Success. */
#define kDSOk				1

/*************************************************************************
 * SigInfo properites
 * These are common properties found in the sigInfo ASCab
 * Plug-ins that want to add their own properties to this object
 * should do so within their own namespace (eg. 'Acme:contactInfo').
 ************************************************************************/

/** EScript SigInfo object name */
#define	SIGINFO_OBJ		"SigInfo"
/** Private data name of ASCab entry in sigInfo ESObject */
#define	ESOBJ_SigInfo	"signatureInfo"

/** ASText properties */
#define	PROP_SigInfo_Name				"name"
#define	PROP_SigInfo_Reason				"reason"
#define	PROP_SigInfo_Location			"location"
/** in PDF date format */
#define	PROP_SigInfo_Date				"date"
/** in PDF date format, new in A7 */
#define	PROP_SigInfo_VerifyDate			"verifyDate"
#define PROP_SigInfo_DataSigStatusText	"dataSigText"
#define PROP_SigInfo_DataSigSignerStatusText	"dataSigSignerText"
#define PROP_SigInfo_StatusText			"statusText"
#define PROP_SigInfo_Subfilter			"subFilter"
/** name specifed by /Filter */
#define PROP_SigInfo_Handler			"handlerName"
#define PROP_SigInfo_HandlerUIName		"handlerUIName"	
/** same as handlerUIName */
#define PROP_SigInfo_HandlerUserName	"handlerUserName"
/** name of handler used to validate signature */
#define PROP_SigInfo_VerifyHandler		"verifyHandlerName"
#define PROP_SigInfo_VerifyHandlerUIName	"verifyHandlerUIName"
#define PROP_SigInfo_MDP				"mdp"

/** ASText properties used only for Public key signatures */
#define	PROP_SigInfo_ContactInfo		"contactInfo"
/** write-only */
#define PROP_SigInfo_Appearance			"appearance"
/** write-only */
#define PROP_SigInfo_Password			"password"
#define PROP_SigInfo_SignFormat			"subFilter"
#define PROP_SigInfo_TimeStamp          "timeStamp"
#define PROP_SigInfo_HashAlgo			"digestMethod"

/** ASInt32 properties */
#define PROP_SigInfo_Revision			"revision"
#define PROP_SigInfo_NumRevisions		"numRevisions"
#define PROP_SigInfo_Status				"status"
#define PROP_SigInfo_NumPagesAltered	"numPagesAltered"
#define PROP_SigInfo_NumFieldsAltered	"numFieldsAltered"
#define PROP_SigInfo_NumFieldsFilledIn	"numFieldsFilledIn"
/** array of ASInt32 */
#define PROP_SigInfo_ByteRange			"byteRange"
/** result of byte range test (value is DSSigValState) */
#define PROP_SigInfo_docValidity		"docValidity"
/** result of MDP test (value is <code>DSSigValState</code>) */
#define PROP_SigInfo_objValidity		"objValidity"
/** result of id validity test (value is <code>DSSigValState</code>) */
#define PROP_SigInfo_idValidity			"idValidity"
/** result of handler id validity test (value is handler specific) */
#define PROP_SigInfo_idPrivValidity		"idPrivValidity"
/** contains a PSSigTrust, which is defined in PubSecHFT.h */
#define PROP_SigInfo_trustFlags			"trustFlags"

/** ESObjects properties. Implemented in PubSec. */
#define PROP_SigInfo_Certificates		"certificates"
#define	PROP_SigInfo_BuildInfo			"buildInfo"

/** Values for the mdp property of a SigInfo Object. See PSSigMDPType enum. */
#define PROP_MDPType_AllowAll			"allowAll"
#define PROP_MDPType_AllowNone			"allowNone"
#define PROP_MDPType_Default			"default"
#define PROP_MDPType_DefaultAndComments	"defaultAndComments"

/** Ubiquity Rights array of ASText. See PDF Reference. */
#define PROP_SigInfo_AppRightsDoc		"appRightsDocument"
#define PROP_SigInfo_AppRightsForm		"appRightsForm"
#define PROP_SigInfo_AppRightsSignature	"appRightsSignature"
#define PROP_SigInfo_AppRightsAnnots	"appRightsAnnots"
#define PROP_SigInfo_AppRightsFormEx	"appRightsFormEx"
#define PROP_SigInfo_AppRightsAnnotsEx	"appRightsAnnotsEx"
#define PROP_SigInfo_AppRightsEF	    "appRightsEF"

/* ASBool properties */
/** boolean indicating if date is from a trusted source, new in A7 */
#define	PROP_SigInfo_DateTrusted		"dateTrusted"		

/** binary properties */
#define PROP_SigInfo_SigValue           "sigValue"

#define PROP_SigInfo_RevInfo            "revInfo"
#define PROP_SigInfo_RevInfo_OCSP       "OCSP"
#define PROP_SigInfo_RevInfo_CRL        "CRL"

/** LockDocument properties */
#define PROP_LockValue_False			"false"
#define PROP_LockValue_True				"true"
#define PROP_LockValue_Auto				"auto"

/** Enumerate signature LTV-enabled state */
typedef enum
{
	kDSLTVUnknown,
	kDSLTVEnabled,
	kDSLTVNotEnabled
} DSLTVEnabled;

/** Enum of all possible PROP_SigInfo_docValidity and PROP_SigInfo_objValidity values (document/data/object hash validity states). */
typedef enum {
	/** Validity is not yet determined. */
	kDSSigValUnknown=0,				
	/** Validity could not be determined because of error. */
	kDSSigValUnknownTrouble,		
	/** Validity could not be determined because all bytes are not ready. */
	kDSSigValUnknownBytesNotReady,	
	/** Validation has been attempted, but there were errors that meant the signature
	    could not be validated, with the conclusion that the result is invalid. */
	kDSSigValInvalidTrouble,		
	/** Validity for this digest is not used (for example, there is no document validity if there is no byte range). */
	kDSSigValUnused,				
	/** The signature was just signed, so it is implicitly valid. */
	kDSSigValJustSigned,			
	/** The signature document/object digest is invalid. */
	kDSSigValFalse,					
	/** The signature document/object digest is valid. */
	kDSSigValTrue,					
	/** The size of the <code>DSSigValState</code> enumeration. */
	kDSSigValEnumSize 
} DSSigValState;

   
/*************************************************************************
 * SigSeedValue properites
 * These are common properties found in the seedValue ASCab
 * This ASCab is destroyed when the seedValue object is destroyed,
 * so plug-ins should uses this object whenever adding private data.
 * Plug-ins that want to add their own properties to this object
 * should do so within their own namespace (eg. 'PPKAcme:issuerDN').
 * See the Acrobat JavaScript guide for a more complete description
 * of these properties.
 ************************************************************************/

/** The private data name of the ASCab entry in the seed value ESObject. */
#define	ESOBJ_SigSeedValue	                "sigSeedValue"

/** An ASAtom giving the name of the required handler to use when signing. */
#define	PROP_SigSeedValue_Filter			"filter"
/** An ASAtom array giving the names of acceptable signing formats. */
#define PROP_SigSeedValue_SubFilter         "subFilter" 
/** A string specifying the hashing algorithm. */
#define PROP_SigSeedValue_DigestMethod      "digestMethod"
/** A <code>double</code> indicating the required revision of the handler. */
#define PROP_SigSeedValue_Version			"version"
/** An ASText array of reasons for signing. */
#define	PROP_SigSeedValue_Reasons			"reasons"    /* array */
/** A string giving the Modification Detection and Prevention (MDP) parameters. */
#define PROP_SigSeedValue_MDP               "mdp"
/** An ASText array of legal attestations for MDP signing. */
#define PROP_SigSeedValue_Attestations      "legalAttestations" /* array */
/** Lock properties. */
#define PROP_SigSeedValue_Lock				"lockDocument"	/* boolean */
/** Appearance filter. */
#define PROP_SigSeedValue_AppearanceFilter	"appearanceFilter"	/* string */
/** <code>ASInt32</code> flags. */
#define PROP_SigSeedValue_Flags				"flags"

/*************************************************************************
 * GetSigDictProp properites
 * These are common properties found in the ASCab that is returned
 * by GetSigDictProp. These values are used by DigSig for display
 * purposes (eg AVPanel, tooltips, or whatever). If a value
 * is not present then DigSig will determine the value on its own,
 * using alternate mechanisms. For example if PROP_DSSigProp_Date is not present then DigSig
 * looks in the /M field of the SigDict to get the date. The ASCab
 * should be cached by the <code>DigSig</code> handler
 ************************************************************************/

/* ASText properties */
/** Signature LTV status */
#define PROP_DSSigProp_LTVStatus			"LTVStatus"
/** Text of the signature LTV status */
#define PROP_DSSigProp_LTVStatusText		"LTVStatusText"
/** The earliest expiration time for all certificates in the trusted chain */
#define PROP_DSSigPropChainExpiration		"ExpirationTime"
/** Total number of chains built for the signature validation */
#define PROP_DSSigPropNumberOfChains		"NumberOfChains"
/** Number of trusted chains built for the signature validation */
#define PROP_DSSigPropNumberOfTrustedChains	"NumberOfTrustedChains"
/** PDF Date format, time of signing */
#define	PROP_DSSigProp_Date	                "M"
/** PDF Date format, time of verification, new in Acrobat 7 */
#define PROP_DSSigProp_VerifyDate           "VerifyDate"
/** Common name of signer */
#define PROP_DSSigProp_Name					"Name"
/** Common name of issuer */
#define PROP_DSSigProp_IssuerCN				"IssuerCN"
/** Organisation of signer */
#define PROP_DSSigProp_SubjectOrg			"SubjectOrg"
/** Summary signature validity text, to append to AVPanel sig title */
#define PROP_DSSigProp_SigValTextSummary	"SigValTextTop"
/** Sig validity detail title line */
#define PROP_DSSigProp_SigValTextDetail		"SigValTextDetail"
/** ASCab array of ASText sig validity details */
#define PROP_DSSigProp_SigValTextDetails	"SigValTextDetails"
/** Signature validity text to show in tooltip */
#define PROP_DSSigProp_SigValTextTooltip	"SigValTextTooltip"
/** Error text, present only if there was error while validating, new in Acrobat 7 */
#define PROP_DSSigProp_ErrText              "ErrorText"

#define PROP_DSSigProp_SigValue             "sigValue"  
#define PROP_DSSigProp_RevInfo              "revInfo" 
#define PROP_DSSigProp_RevInfo_CRL          "CRL"
#define PROP_DSSigProp_RevInfo_OCSP         "OCSP"

/** Hashing algorithm used to hash the document. Can be empty, new in Acrobat 8 */
#define PROP_DSSigProp_HashAlgo				"digestMethod"

/* ASBool properties */
/**
	indicates whether the signing time was from a trusted time
	source or not. If the key is not present, its assumed it
	was from an untrusted (e.g. system) source, new in Acrobat 7 
*/
#define	PROP_DSSigProp_TrustedDate	        "Trusted_M"          

/**
	If you want to put this entry in your plugins' signature properties cab please make sure 
	you use the DSSigPropIconState enum below for its values. This will ensure that DigSig use the
	appropriate icons (in sync with your plugins') to represent the signature's state. 
	If you do not provide this value, DigSig will use validity icons according to what 
	it thinks is the validity status of the signature. 
*/
#define PROP_DSSigProp_IconState			"ADBE:sigIconState"     
/**	only use the values enumerated below. Default is kDSDisplayOnPageIconAlways. */
#define PROP_DSSigProp_DisplayOnPageIcon "ADBE:sigDisplayOnPageIcon"
typedef enum { 
	kDSDisplayOnPageIconAlways = 0, 
	kDSDisplayOnPageIconExceptWhenValid, 
	kDSDisplayOnPageIconNever,
	kDSDisplayOnPageIconEnumSize
} DSSigPropDisplayOnPageIcon;


typedef	enum {
	/** sig field is unsigned */
	kDSSigIconBlank=0,
	/** sig field is signed but not validated */
	kDSSigIconSigUnknown,
	/** sig field is signed and failed validate */
	kDSSigIconSigInvalid,
	/** sig field is signed and doc is valid, but identity is unknown or not trusted */
	kDSSigIconSigValidIdUnknown,
	/** sig field is signed, but identity is unknown or not trusted and mods have been made since sig applied */
	kDSSigIconSigValidIdUnknownModAfter,
	/** sig field is signed and double-checked valid */
	kDSSigIconSigValid,
	/** sig field is signed and double check valid, but mods have been made since sig applied */
	kDSSigIconSigValidModAfter,
	/** sig field is signed and double check valid, but mods have been made since sig applied -- *AND* sig is the last sig in the document */
	kDSSigIconSigValidTrailingModsAfter,
	/** sig field is auth signed but not validated */
	kDSSigIconAuthUnknown,
	/** sig field is auth signed and failed validate */
	kDSSigIconAuthInvalid,
	/** sig field is auth signed and doc is valid, but identity is unknown or not trusted */
	kDSSigIconAuthValidIdUnknown,
	/** sig field is auth signed, but identity is unknown or not trusted and mods have been made since sig applied */
	kDSSigIconAuthValidIdUnknownModAfter,
	/** sig field is auth signed and double-check valid */
	kDSSigIconAuthValid,
	/** sig field is auth signed and double check valid, but mods have been made since sig applied */
	kDSSigIconAuthValidModAfter,
	/** sig field was signed in an earlier version, but has since been deleted */
	kDSSigIconSigDeleted,
	/** The size of the <code>DSSigPropIconState</code> enumeration. */
	kDSSigIconEnumSize
} DSSigPropIconState;

/*************************************************************************
 * DigSigOffset record
 * Used to tell XxxxSig where objects landed in saved file
 ************************************************************************/
/**
	A structure that indicates the location of objects in a saved 
	PDF document. 
	@see DSClearSigProc 
	@see DSFinishSignProc 
	@see DigSigCosObjOverwrite 
	@see DigSigOverwriteBytes 
	@see DigSigOverwriteHexstring 
	@see DigSigOverwriteIntArray 
*/
typedef struct _t_DigSigOffsetRec {
	/** The CosObj whose byte offset/length is desired. */
	CosObj	cosObj;					
	/** The byte offset in the saved PDF file. Its range is <code>0</code> to <code>2147483647</code>. */
	ASInt32	byteOffset;				
	/**  The length in the saved PDF file. Its range is <code>0</code> to <code>2147483647</code>. */
	ASInt32	byteLength;				
} DigSigOffsetRec, *DigSigOffset;

/** Acrobat 10 - 64-bit positioning */
typedef struct _t_DigSigOffset64Rec {
	/** The CosObj whose byte offset/length is desired. */
	CosObj	cosObj;					
	/** The byte offset in the saved PDF file. */
	ASFileOffset64	byteOffset;				
	/**  The length in the saved PDF file. */
	ASInt64	byteLength;				
} DigSigOffset64Rec, *DigSigOffset64;


/** A signature annotation bounding box.
	@see DSNewSigDataProc
*/
typedef struct _t_DigSigBBoxRec {
	/** The width of the signature bounding box. */
	ASFixed	bbWidth;				
	/** The height of the signature bounding box. */
	ASFixed	bbHeight;				
} DigSigBBoxRec, *DigSigBBox;


/** A validity state constant for a signature field, resulting from verification.
	@see DigSigVerifySig
	@see DSGetValidStateProc
	@see DSValidateSigProc
*/
typedef enum {
	/** The signature field is unsigned. */
	DSSigBlank=0,					
	/** The signature field is signed but not validated. */
	DSSigUnknown,					
	/** The signature field is signed but failed validation. */
	DSSigInvalid,					
	/** The signature field is signed and valid. */
	DSSigValid,						
	/** The signature field is signed and double-checked as valid. */
	DSSigDoubleChecked,
	/**
	A validity state constant for a signature field, resulting 
	from verification. 
*/
	DSSigValidStateEnumSize			
} DSValidState;

/** A structure describing the appearance of a digital signature. 
	@see DSUnValidateSigProc
	@see DigSigGetStdXObj
*/
typedef enum { 
	/** Blank appearance. */
	DSBlankXObj=0,					
	/** Signed but not validated appearance. */
	DSUnknownXObj,					
	/** Signed and failed validation appearance. */
	DSInvalidXObj,					
	/** Signed and valid, but the identity is not verified. */
	DSValidXObj,					
	/** Signed and valid, and the identity is verified. */
	DSDoubleCheckedXObj				
} DSXObjType;

/** A return type for the DigSig and PubSec callbacks.
	@see DSNewSigDataExProc
	@see DSNewSigDataWithParamsProc
*/
typedef enum { 
	/** Do not proceed with signing. */
	DSSignCancel=0,					
	/** Save over old file. */
	DSSignSave,						
	/** Save into new file. */
	DSSignSaveAs,					
	/** No save option is specified (new in Acrobat 6). */
//	DSSignNone,						
	/** The size of the <code>DSSaveType</code> enumeration. */
	DSSaveTypeEnumSize
} DSSaveType;

/** Constants that specify the method to use for creating a signature digest. */
typedef enum {
	/** */
	kDSDigestNone=0,
	/** */
	kDSDigestMD5,
	/** */
	kDSDigestSHA1,
    /** Support added in Acrobat 7.0 */
    kDSDigestSHA256,
	/** Support added in Acrobat 8.0 */
    kDSDigestSHA384,
	/** Support added in Acrobat 8.0 */
    kDSDigestSHA512,
	/** Support added in Acrobat 8.0 */
    kDSDigestRIPEMD160,
    /** Support added in Acrobat 11.0 */
    kDSDigestSHA224,
	/** The size of the <code>DSDigestMethod</code> enumeration. */
	kDSDigestEnumSize
} DSDigestMethod;

/** Signature value encodings for public key signatures. 
	It is a parameter to DigSigDataSigSign() and DigSigDataSigValidate(). 
	@see DigSigDataSigSign
	@see DigSigDataSigValidate
*/
typedef enum {
	/** Not specified. */
	kDSSigEncodeNone=0,			
	/** PKCS#1 encoding. */
	kDSSigEncodePKCS1,			
	/** PKCS#7 encoding. This will apply the signature to an SHA1 digest of the data..
		This is now deprecated. Use <code>kDSSigEncodePKCS7Detached</code> instead. 
	*/
	kDSSigEncodePKCS7,			
	/** The digest is directly encrypted. 
		This has never worked before and is now deprecated.
	*/
	kDSSigEncodeRawSig,
	/** PKCS#7 encoding. Unlike <code>kDSSigEncodePKCS7</code>, the signature is directly applied
		to the data. 
	*/
	kDSSigEncodePKCS7Detached,
	/** CAdES-compatible encoding. It is PKCS#7 detached with additional attributes.
	*/
	kDSSigEncodeETSICAdES,
	/** PAdES Document Timestamp encoding. This is a Timestamp token per RFC 3161.
	*/
	kDSSigEncodeETSIDocTimestamp,
	/** The size of the <code>DSSigEncode</code> enumeration. */
	kDSSigEncodeEnumSize
} DSSigEncode;

/** Modification, detection, and prevention (MDP) options. 
*/
typedef enum {
    /** No MDP. The document does not have a signature. In versions earlier than Acrobat 9.0, 
	this status is returned for a document that does not have an author signature, but does have an ordinary signature. 
	In Acrobat 9.0 and later, any signature will invoke MDP analysis of all subsequent changes. */
    kDSMDPNone = -1,          
	/** Allow any changes (disables the MDP feature). */
	kDSMDPAllowAll=0,	      
	/** Allow no changes. */
	kDSMDPAllowNone,	      
	/** Only allow <i>natural</i> changes (form field fill-in, page spawning). */	
	kDSMDPDefault,		      
	/** Allow all comment types and edit/modify/delete operations, in addition to default changes. */
	kDSMDPCommentsAndDefault, 
	/** The size of the <code>DSMDPType</code> enumeration. */
	kDSMDPEnumSize    
} DSMDPType;

/** Boolean properties of a <code>DigSigHandler</code>, obtained with <code>DSGetBoolPropertyProc()</code>,
	that show whether the handler supports specific functionality.
	@see DSGetBoolPropertyProc
*/
typedef enum {
	/** When <code>true</code>, the handler supports author signatures. */
	kDSHandlerCanDocAuthSign=0,	
	/** When <code>true</code>, the handler supports ordinary visible signatures. */
	kDSHandlerCanDocPDDocSignVisible,	
	/** When <code>true</code>, the handler supports EScript. */
	kDSHandlerEScriptAware,	
	/** The size of the <code>DSHandlerProperty</code> enumeration. */
	kDSHandlerPropEnumSize
} DSHandlerProperty;

/** Constants that specify what dialog box to show.
*/
typedef enum {
	/** Do not show the signature properties dialog box. */
	kDSPropNone=0,
	/** Show the general signature properties dialog box. */
	kDSPropSignature,
	/** Show the legal notice dialog box. */
	kDSPropLegal,
	/** Show the signature rollback (it will actually roll back to this signature). */
	kDSPropViewVersion,
	/** The size of the <code>DSPropertyType</code> enumeration. */
	kDSPropTypeEnumSize
} DSPropertyType;

/** Parameters for <code>DSNewSigDataWithParamsProc()</code>.
	@see DSNewSigDataWithParamsProc
*/
typedef struct _t_DigSigNewSigDataParamsRec {
	/** The size of the data structure. It must be set to
		<code>sizeof(DigSigNewSigDataParamsRec)</code>. */
	ASSize_t size;				

	/** The PDF document that is being signed. */
	PDDoc pdDoc;				
	/** The signature form field that is being signed. */
	CosObj sigField;			
	/** The signature annotation that is being signed (it is usually equivalent to <code>sigField</code>). */
	CosObj sigAnnot;			
	/** The bounding box of the signature appearance. */
	DigSigBBox bb;				

	/** The name of the selected handler to use when signing. */
	ASAtom filter;				
	/** Used internally. If specified, then use it to sign; otherwise use the engine that belongs to the default user interface. */
	ESObject esSigEngine;		
	/** Used internally. If specified, it provides parameters to use when signing. */
	ESObject esSigParams;		
	/** Used internally. If it is not <code>NULL</code> and there is an error that needs reporting for EScript, set it here and return DSSignCancel. */ 
	ASText esErrorText;			
	/** If <code>true</code>, prompt to sign, otherwise be silent (it can be <code>true</code> with Escript.) */
	ASBool bUI;					
	/** When <code>true</code>, the document is being signed with an author signature. */
	ASBool bDocAuthSig;			
	/** Legal PDF scrubber warnings, populated only when signing a document author signature.*/
	CosObj legalPDFDict;		
	/** Modification, detection, and prevention (MDP) setting, populated
		only when signing a document author signature. It has one of the following values:

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD><code>kDSMDPAllowAll</code></TD><TD>Allow all changes (disables MDP).</TD></TR>
		<TR><TD><code>kDSMDPAllowNone</code></TD><TD>Allow no changes.</TD></TR>
		<TR><TD><code>kDSMDPDefault</code></TD><TD>Allow only <i>natural</i> changes (form field filling, page spawning).</TD></TR>
		<TR><TD><code>kDSMDPCommentsAndDefault</code></TD><TD>Allow all comment types and edit/modify/delete, in addition to default changes.</TD></TR>
		</TABLE>
	*/
	DSMDPType mdpSetting;
	/** Signifies whether user rights are being applied to the document. It is mutually exclusive with <code>bDocAuthSig</code>. */
	ASBool bUBSig;
	/*	Parameters for signing with user rights. */
	CosObj urdDict;
} DigSigNewSigDataParamsRec, *DigSigNewSigDataParams;


/** The type of <code>CosDoc</code> signature. */
typedef enum {
	/** A CosDoc signature. */
    kDSObjCosDoc=0,
	/** Usage rights. */
    kDSObjUbiquity,
	/** The size of the <code>DSCosDocSigObjType</code> enumeration. */
    kDSObjEnumSize
} DSCosDocSigObjType;

/** Parameters passed in to <code>DSCosDocSigSign()</code> and <code>DSCosDocSigValidate()</code> procs.
	Certain parameters vary depending on what <code>DSCosDocSigObjType</code> <code>objSigType</code> is set to.
	
	<p>If <code>objSigType</code> is <code>kDSObjCosDoc</code>:</p>

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Parameter</TH><TH>Description</TH></TR>
		<TR><TD><code>objSignParams</code></TD><TD>None.</TD></TR>
		<TR><TD><code>pdDoc</code></TD><TD>Used for window parenting when available, otherwise it is <code>NULL</code> (this would be the active document, and not necessarily the document to which the <code>CosDoc</code> belongs).</TD></TR>
		<TR><TD><code>cosDoc</code></TD><TD>The CosDoc that is to be signed.</TD></TR>
		</TABLE>

	
	<p>If <code>objSigType</code> is <code>kDSObjUbiquity</code>:</p>

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Parameter</TH><TH>Description</TH></TR>
		<TR><TD><code>objSignParams</code></TD><TD>A CosDict containing the usage rights sub-options for form filling, annotation changes, page template spawning, and so on. Look at the URD specification in the <i>PDF Reference</i> 1.5, section 8.7.2 for the precise syntax of CosDict and the keys within.</TD></TR>
		<TR><TD><code>pdDoc</code></TD><TD>Indicates the <code>PDDoc</code> to which usage rights are applied.</TD></TR>
		<TR><TD><code>cosDoc</code></TD><TD>Ignored.</TD></TR>
		</TABLE>

    @see DSCosDocSigSign
	@see DSCosDocSigValidate
*/
typedef struct _t_DigSigCosDocSigParamsRec {
	/** The size of this <code>struct</code>. */
	ASSize_t size;
	/** The associated PDDoc, if needed. See DigSigCosDocSigParamsRec 
		for more details.
	*/			
	PDDoc pdDoc;				
	/** The CosDoc to be signed, if needed. See DigSigCosDocSigParamsRec 
		for more details.
	*/
	CosDoc cosDoc;
	
	/** The name of the selected handler to use when signing or validating. */
	ASAtom filter;				
	/** If specified, then use it to sign, otherwise use the engine that belongs to the default user interface. */
	ESObject esSigEngine;		
	/** If specified, then provides parameters to use when signing. */
	ASCab sigParamsCab;			
	/** If <code>0</code> then be silent, otherwise prompt the user to sign (it can be <code>true</code> even with escript). If <code>1</code> then use a simple user interface, otherwise use a complex user interface. */
	ASInt32 uiType;				

	/** Dialog title to use when signing. The object is owned by <code>DigSig</code>. */
	ASText signDialogTitle;		
	/** The message to use when acquiring resources for signing. The object is owned by <code>DigSig</code>. */
	ASText promptMessage;		
	/** If an exception occurs, this returns the exception string. The caller must call <code>ASTextDestroy()</code>. */
	ASText asTextError;			

	/** The type of <code>CosDoc</code> signature. */
    DSCosDocSigObjType objSigType;
	/** The associated <code>objSigParams</code>, if needed. See DigSigCosDocSigParamsRec 
		for more details.
	*/
    void *objSigParams;
} DigSigCosDocSigParamsRec, *DigSigCosDocSigParams;

typedef struct _t_DigSigDataParamsRec {
	/** The size of this <code>struct</code>. */		                                
	ASSize_t size;					
	/** A pointer to the data to be processed. */
	ASUns8* inDataPtr;				
	/** The size of the data to be processed. */
	ASUns32 inDataSize;				
	/** The resulting object value, to be freed using <code>ASfree()</code> by the caller. */
	ASUns8* outDataPtr;			
	/** The size of the resulting object. */
	ASUns32 outDataSize;		
	/** If an exception occurs, this returns the exception string. The caller must call <code>ASTextDestroy()</code>. */
	ASText outASTextError;				

} DigSigDataParamsRec, *DigSigDataParams;

typedef struct _t_DigSigDataBufferSigNewParamsRec {
	/** The size of this <code>struct</code>. */
	ASSize_t size;					

	/** Used for window parenting. */				                                
	PDDoc inPDDoc;					
	/** The name of the selected handler to use when signing. It must set to <code>ASAtomNull</code> if it is not defined. 
		Upon the signature being applied, this will be set to the name of the filter that was used to sign. */
	ASAtom filter;					
	/** If specified, use it to sign, otherwise use the engine that belongs to the default user interface. */
	ESObject inESSigEngine;			
	/** If specified, it provides parameters to use when signing. */
	ESObject inESSigParams;			
	/** When signing, if it is not none, then the data is to be digested and the digest is to be signed; otherwise directly sign the data. */
	DSDigestMethod inDigestMethod;	
	/** Specifies signature value encoding. */
	DSSigEncode inSigValueEncoding;	
	/* Seed value information. */
	ASCab inSeedValue;
	/** The name of the data that is being signed. */
	ASText inDataTitle;
	/** The description of the data that is being signed. */
	ASText inDataDescription;
	/** The dialog box title to use when signing. The object is owned by <code>DigSig</code>. */
	ASText inSignDialogTitle;		
	/** The message to use when acquiring resources for signing. The object is owned by <code>DigSig</code>. */
	ASText inPromptMessage;		
	/** If this is greater than <code>0</code>, prompt the user to sign; otherwise be silent (it can be <code>true</code> even with EScript). */
	ASInt32 inNUI;						
	/** The callback to display data that is being signed. */
	void* inDataDisplayCallbackProc;

	/** The certificate chain of the signer. It must be an initialized <code>ASCab</code>. It is returned by the <code>sigNew</code> call. */
	ASCab outCertChainCab;				
	/** Signature properties. It must be an initialized <code>ASCab</code>. 
		Refer to <code>PROP_SigProp_*</code> definitions in PubSecHFT.h for defined properties. 
		It is returned by a <code>sigNew</code> call. */
	ASCab outSigPropCab;				
	/** Signature build information. It must be an initialized <code>ASCab</code>. 
		Refer to <code>PROP_SigBuild*</code> definitions in PubSecHFT.h for defined properties. 
		It is returned by a <code>sigNew</code> call. */
	ASCab outSigBuildCab;				
	/** If an exception occurs, this returns the exception string. The caller must call <code>ASTextDestroy()</code>. */
	ASText outASTextError;				

} DigSigDataBufferSigNewParamsRec, *DigSigDataBufferSigNewParams;


/**  Callback function used to verify all references used by the data signature.
	 It is only called if the core signature is valid. 
	 @return <code>true</code> if the other resources are valid. */
typedef ASBool (VerifyRefCallbackProc)(void* callbackData);


typedef struct _t_DigSigDataBufferSigValidateParamsRec {
	/** The size of this <code>struct</code>. */
	ASSize_t size;					

	/** Used for window parenting */				                                
	PDDoc inPDDoc;					
	/** The name of the selected handler to use when verifying. It must be set to ASAtomNull if it is not defined. */
	ASAtom filter;					
	/** If specified, use it to verify; otherwise use the engine that belongs to the default user interface. */
	ESObject inESSigEngine;			
	/** If specified, it provides parameters to use when signing. */
	ESObject inESSigParams;			
	/** When signing, if it is not none, then the data is to be digested and the digest is to be signed, otherwise directly sign the data. */
	DSDigestMethod inDigestMethod;	
	/** Specifies signature value encoding. */
	DSSigEncode inSigValueEncoding;	
	/** The name of the data that is being verified. */
	ASText inDataTitle;
	/** The description of the data that is being verified. */
	ASText inDataDescription;
	/** The dialog box title to use when signing. The object is owned by <code>DigSig</code>. */
//	ASText inSignDialogTitle;		
	/** Message to use when acquiring resources for signing. The object is owned by <code>DigSig</code>. */
//	ASText inPromptMessage;		
	/** If this is greater than <code>0</code>, allow the user interface; otherwise be silent (it can be <code>true</code> even with EScript).	*/
	ASInt32 inNUI;						
	/** The callback to display data that is being signed. */
	void* inDataDisplayCallbackProc;

	/** The certificate chain of the signer. It must be an initialized ASCab. It is returned by the <code>sigNew</code> call. */
	ASCab inCertChainCab;

	/** A pointer to the data to be signed. If it is <code>NULL</code>, then signing does not occur. */
	ASUns8* inDataPtr;				
	/** The size of the data to be signed. */
	ASUns32 inDataSize;				
	/** The resulting signature value, to be freed using ASfree() by the caller, or the signature value if verifying. */
	ASUns8* inSigValuePtr;			
	/** The size of the resulting signature value. */
	ASUns32 inSigValueSize;			

	/** If an exception occurs, this returns the exception string. The caller must call <code>ASTextDestroy()</code>. */
	ASText outASTextError;

	/**  Callback function used to verify all references used by the data signature. */
	VerifyRefCallbackProc * inVerifyReferencesCallbackProc;
	/** Data used by <code>inVerifyReferencesCallbackProc()</code>. */
	void * inVerifyReferencesCallbackProcData;

} DigSigDataBufferSigValidateParamsRec, *DigSigDataBufferSigValidateParams;

/** Notification types for the DSNotifySigProc().
*/
typedef enum {
	/** No notification (not used). */
	kDSNotifyNone=0,
	/** Mark the validity of this signature as unknown. This should mark validity 
	caches to indicate that the signature validity is unknown. */
	kDSNotifySetUnknown,
	/** The document may have been modified since this signature was applied. The handler
	   should update the signature status after calling DigSigDocModifiedAfterSig(). 
	   This is not called as of Acrobat 6.0, but may be used in a later release. */
	kDSNotifyModifiedAfterSig,
	/** The size of the <code>DSNotifySigType</code> enumeration. */
	kDSNotifySigTypeEnumSize
} DSNotifySigType;

/*************************************************************************
 * DigSigHFT Methods
 ************************************************************************/

/**
	A callback for <code>DigSigHandler</code>. It is called when a new document is 
	opened. 
	@param pdDoc The document that has been opened.
	@see DSDocCloseProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSDocOpenProc)
	(PDDoc pdDoc);
/** A callback for <code>DigSigHandler</code>. It is called when a new document is closed.
	@param pdDoc The document being closed.
	@see DSDocOpenProc
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSDocCloseProc)
	(PDDoc pdDoc);

/** This call was used only in Acrobat 5.x when the EScript security
   object was implemented in DigSig.  It returns the existing user interface engine
   object (ESObject) if <code>uiEngine</code> is <code>true</code>, otherwise it returns a new signature
   engine object (ESObject). <code>handlerName</code> is the name of the handler
   that is being asked to return the new engine. <code>vData</code> is reserved for
   future use and is currently not used.  This call is no longer
   used. */
typedef ACCBPROTO1 ESObject (ACCBPROTO2 *DSNewSigEngineProc)
	( void *context, ASAtom handlerName, ASBool uiEngine, void *vData );

/** Internal use. Add your engine-specific properties to the existing <code>sigInfo</code>
    ESObject.  Any private data should be added to the ASCab that is
    set as private data in ESOBJ_SigInfo <code>ASCab</code> (see above). This
    should have been written to pass an <code>ASCab</code> instead of ESObject, but
    we missed this.  <code>handlerName</code> is the name of the handler that is
    being asked to return the data (not necessarly the same as the
    value of the <code>/Filter</code> attribute in the <code>sigDict</code>).  It is for Adobe use only,
    and subject to change.  It can only be used by EScript-aware DigSig
    handlers (for example, <code>PubSec</code>). */
typedef ACCBPROTO1 void (ACCBPROTO2 *DSGetSigInfoProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASAtom handlerName, ESObject sigInfo );

/** Internal use. Add your engine-specific properties to the existing <code>seedValue</code> ESObject.
   Any private data should be added to ESOBJ_SigSeedValue <code>ASCab</code> (see
   above).  It is for Adobe use only, and subject to change.  It can only be used
   by EScript-aware <code>DigSig</code> handlers (for example, <code>PubSec</code>). <code>*jsErrText</code> will
   be <code>NULL</code>. The handler should set <code>*jsErrText</code> to a new <code>ASText</code> object,
   which will then be destroyed by <code>DigSig</code>.
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSGetSigSeedValueProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ESObject seedValue, ASText *jsErrText );

/** Internal use. Add your engine-specific properties to the existing <code>seedValue</code> ESObject.
   Any private data should be added to ESOBJ_SigSeedValue ASCab (see
   above).  It is for Adobe use only, and subject to change.  It can only be used
   by EScript-aware <code>DigSig</code> handlers (for example, PubSec). <code>*jsErrText</code> will
   be <code>NULL</code>. The handler should set <code>*jsErrText</code> to a new <code>ASText</code> object,
   which will then be destroyed by <code>DigSig</code>.
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSSetSigSeedValueProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ESObject seedValue, ASText *jsErrText );

/** Internal use. Validates a signature (performs an action).  If <code>sigEngine</code> is not <code>NULL</code>
    then use this engine, otherwise use the user interface engine.  <code>handlerName</code> is
    the name of the handler that is being asked to validate the
    signature (not necessarily the same as the value of the <code>/Filter</code>
    attribute in the <code>sigDict</code>). If <code>bUI</code> is <code>true</code>, show an alert after
    validating.  Note that this alert may be suppressed depending on
    preference settings. It is for Adobe use only, and subject to change.  Itan only be
    used by EScript aware <code>DigSig</code> handlers (for example, PubSec).
*/
typedef ACCBPROTO1 DSValidState (ACCBPROTO2 *DSValidateSigExProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASAtom handlerName, ESObject sigEngine, ASBool bUI );

/**
	<p>A callback for <code>DigSigHandler</code>. It is called to validate a signature. 
	It recalculates any document digest desired, possibly 
	using the <code>DigSigFileGetEOF()</code>, <code>DigSigMD5ByteRange()</code>, <code>DigSigFileRead()</code>, 
	and <code>DigSigFileSetPos()</code> methods. </p>

	<p>It may compare this result to the stored one, and do any other 
	signature-specific checks desired. It optionally does a validation 
	against a stored (network) registry. If necessary, it updates 
	the AP dictionary in the signature annotation dictionary 
	to show the validation state of the signature. </p>
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot the Cos object of the signature annotation.
	@return The validation state. 
	@see DSUnValidateSigProc 
	@see DSReValidateSigProc 
	@see DigSigFileGetEOF 
	@see DigSigMD5ByteRange 
	@see DigSigFileRead 
	@see DigSigFileSetPos 
*/
typedef ACCBPROTO1 DSValidState (ACCBPROTO2 *DSValidateSigProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot);

/**
	A callback for <code>DigSigHandler</code>. It is called by the signature panel display 
	to choose which of the double-checked pass, fail, unknown, 
	or blank icons to show. It may call <code>DigSigUpdatePanel()</code> to update 
	the signature panel. 
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation. 
	
	@return The validation state. 
	@see DigSigUpdatePanel 
	@note Superseded in Acrobat 6.0 by DSNewSigDataWithParamsProc(). 
*/
typedef ACCBPROTO1 DSValidState (ACCBPROTO2 *DSGetValidStateProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot);

/**
	<p>This function is called to query the handler to find out 
	if it can validate this PDDoc signature field. The call 
	determines if the general signature format is supported 
	by the handler, or if the handler should be given the opportunity 
	to validate this signature. </p>

	<p>If the response is <code>false</code>, the handler cannot be called to 
	validate the signature. In this event, the handler will 
	not be able to provide other information (for example, that 
	an updated version of the handler should be obtained in 
	order to validate the signature). </p>
	@param pdDoc The document that contains the signature 
	field. 
	@param sigField The signature field. 
	@param sigAnnot The signature annotation that is being 
	verified (usually equivalent to <code>sigField</code>). 
	@param filter The name by which <code>DigSig</code> knows this handler. 
	This is not necessarily the value of <code>/Filter</code>.
	@return <code>true</code> if the handler can validate the field signature, <code>false</code> 
	otherwise. 
	@see DigSigVerifySig 
*/
typedef ACCBPROTO1 ASBool(ACCBPROTO2 *DSCanValidateProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASAtom filter );

/**
	Returns a string describing the status of the signature. 
	It must be <code>PDDocEncoding</code> or Unicode, where Unicode strings 
	must start with <code>0xFE</code>, <code>0xFF</code>. 
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation.
	@param bSilent
	@return None. 

	@note Superseded by DSGetSigPropProc() in Acrobat 6.0, which 
	provides better granularity for the signature status. 
*/
typedef ACCBPROTO1 ASText (ACCBPROTO2 *DSGetStatusTextProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASBool bSilent );

/**
	A callback for <code>DigSigHandler</code>. It is called when a new signature 
	field is created. This method creates the default signature 
	value dictionary and creates a default value (DV) entry 
	in the signature field dictionary pointing to this dictionary. 
	
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation.
	A callback for <code>DigSigHandler</code>. It is called when a new document is 
	closed. 
	@param pdDoc The document being closed.
	@see DSDocOpenProc 

	@note Deprecated in Acrobat 6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSDefaultValueProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot);

/**
	<p>A callback for <code>DigSigHandler</code>. It is called to gather signature data 
	or to cancel. It may display dialogs. It may use the default value 
	(DV) field of the signature field if it is not <code>CosNull</code>. </p>
	
	<p>To allow for a user to cancel signing, the handler should 
	not modify the document during this callback. The handler 
	will commit the signature to the PDF file during <code>DSClearSigProc()</code>. </p>
	
	@param pdDoc The document being signed. 
	@param bb The signature annotation bounding box. 
	@param sigData The signature data, as defined by the specific 
	signature plug-in. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation.
	@return <code>true</code> if the signature data is gathered, <code>false</code> if it is cancelled. 
	@see DSClearSigProc 
	@see DSNewSigDataWithParamsProc 
	@see DSFinishSignProc 
	@see DSFreeSigDataProc 
	@note Superseded in Acrobat 6.0 by DSNewSigDataWithParamsProc(). 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSNewSigDataProc)
	(PDDoc pdDoc,  DigSigBBox bb, void **sigData, CosObj sigField, CosObj sigAnnot);

/** Use <code>DSNewSigDataWithParamsProc()</code> instead of this call.
   Support for this call will continue for at least the short term. */
typedef ACCBPROTO1 DSSaveType (ACCBPROTO2 *DSNewSigDataExProc)
	(PDDoc pdDoc,  DigSigBBox bb, void **sigData, CosObj sigField, CosObj sigAnnot,
	ASAtom filter, ESObject sigEngine, ESObject sigInfo);

/**
	A callback for <code>DigSigHandler</code>. It creates new signature data to 
	be used by Commit and Finish, and is then destroyed by <code>DSFreeSigDataProc()</code>. 
	
	<p>If a dialog box is not used (<code>bUI</code> is <code>false</code>), 
	exception strings are stored in the signature data and 
	can be retrieved with <code>DSSigDataGetErrorTextProc()</code>.</p>
 
	@param sigParams The structure containing signing parameters. 
	
	@param sigData (Filled by the method) Signature data as defined by the specific signature plug-in.
	@return A constant indicating the action to be performed on the 
	document; cancel signing, save to the same file name, or 
	save to a new file name. 
	@see DSCommitSignProc 
	@see DSNewSigDataProc 
	@see DSFinishSignProc 
	@see DSFreeSigDataProc 
	@see DSSigDataGetErrorTextProc 
	@note Supersedes DSNewSigDataProc() in Acrobat 6.0. 
*/
typedef ACCBPROTO1 DSSaveType (ACCBPROTO2 *DSNewSigDataWithParamsProc)
	( DigSigNewSigDataParams sigParams, void **sigData );

/**
	<p>A callback for <code>DigSigHandler</code>. It is called to put the signature into 
	the document in memory or to cancel. It modifies the signature 
	dictionary as needed. It may allocate storage for an array 
	of signature objects. </p>

	<p>The signature includes a signature dictionary written to 
	the <code>/V</code> attribute of the <code>sigField</code> and an optional appearance 
	written to the <code>/AP</code> dictionary of the <code>sigAnnot</code>. </p>

	<p>See <i>Section 8.7</i> in the <i>PDF Reference</i> for the format of the 
	signature dictionary. At least two objects in the signature 
	dictionary, <code>ByteRange</code> and <code>Contents</code>, will need to be overwritten 
	during the <code>DSFinishSignProc()</code> callback.</p> 
	@param pdDoc The document being signed. 
	@param sigData The signature data, as defined by the specific 
	signature plug-in. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation. 
	
	@param offsetArray (Optional) An offset array pointing 
	to a set of <i>marked</i> Cos objects relevant to the signature type; 
	this array includes at least the <code>ByteRange</code> 
	and <code>Contents</code> value objects. 
	@param arrayCount (Optional) The number of objects in <code>offsetArray</code>, 
	if used.
	@return <code>true</code> if the signature was successfully placed in <code>pdDoc</code>, 
	<code>false</code> otherwise. 
	@see DSFinishSignProc 
	@see DSNewSigDataProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSCommitSignProc)
	(PDDoc pdDoc, void *sigData, CosObj sigField, CosObj sigAnnot, 
	 DigSigOffset *offsetArray, ASInt32 *arrayCount);

/* long file version */
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSCommitSign64Proc)
	(PDDoc pdDoc, void *sigData, CosObj sigField, CosObj sigAnnot, 
	 DigSigOffset64 *offsetArray, ASInt32 *arrayCount);

/**
	A callback for <code>DigSigHandler</code>. It is called to calculate the checksum 
	and update the disk copy of document. It may use information from 
	the <code>offsetArray</code> parameter. 
	@param pdDoc The document being signed. 
	@param sigData The signature data, as defined by the specific 
	signature plug-in. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation. 
	
	@param offsetArray (Optional) An offset array pointing 
	to a set of <i>marked</i> Cos objects relevant to the signature type; 
	this array includes at least the <code>ByteRange</code> 
	and <code>Contents</code> value objects. 
	@param arrayCount (Optional) The number of objects in <code>offsetArray</code>, 
	if used.
	@return <code>true</code> if processing is successful, <code>false</code> otherwise. 
	@see DSClearSigProc 
	@see DigSigOverwriteHexstring 
	@see DigSigOverwriteIntArray 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSFinishSignProc)
	(PDDoc pdDoc, void *sigData, CosObj sigField, CosObj sigAnnot, 
	 DigSigOffset offsetArray, ASInt32 arrayCount);

/* Long file version */
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSFinishSign64Proc)
	(PDDoc pdDoc, void *sigData, CosObj sigField, CosObj sigAnnot, 
	 DigSigOffset64 offsetArray, ASInt32 arrayCount);

/**
	Returns an error string to describe failure during new, 
	commit, or free steps. If it is not <code>NULL</code>, then a JavaScript general 
	exception is thrown using this string. 

	<p>The handler can set this procedure to <code>NULL</code> if desired. </p>

	<p>The string is owned by <code>sigData</code>, so it should be freed by DSFreeSigDataProc(). </p>
	
	@param sigData A pointer to the signature for which the 
	error string is obtained.
	@return The error string as an <code>ASText</code>. 
	@see DSFreeSigDataProc 
	@see DSNewSigDataWithParamsProc 
*/
typedef ACCBPROTO1 ASText (ACCBPROTO2 *DSSigDataGetErrorTextProc)
	(void *sigData);

/**
	A callback for <code>DigSigHandler</code>. It frees signature data. 
	@param sigData The signature data, as defined by the specific 
	signature plug-in. The handler should check to see if <code>sigData</code> 
	is <code>NULL</code>.
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSFreeSigDataProc)
	(void *sigData);

/**
	A callback for <code>DigSigHandler</code>. It is called when a user selects a 
	signature and asks for its properties. It brings up the properties 
	dialog box for the signature. 
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation.
	@param handlerName The sub-handler to use to validate, 
	in the event that the handler has more then one sub-handler 
	(as is the case with <code>PubSec</code>), and the handler is being asked 
	to validate a signature that has a different filter name 
	than its own. 
	@param sigEngine Used internally.
	@param propType One of the <code>.DSPropertyType</code>. values.  Its default is <code>kDSPropNone</code>.
	@see DigSigUpdatePanel 
	@note Supersedes <code>DSPropertiesProc()</code>. in Acrobat 6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSPropertiesExProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASAtom handlerName, ESObject sigEngine, DSPropertyType propType );

/**
	A callback for <code>DigSigHandler</code>. It is called when a user selects a 
	signature and asks for its properties. The handler should 
	present its own dialog box that provides details concerning 
	the signature and its validation state. 
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation.
	@see DigSigUpdatePanel 
	@note Superseded by <code>DSPropertiesExProc()</code> in Acrobat 6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSPropertiesProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot);

/**
	A callback for <code>DigSigHandler</code>. It is called to change the appearance 
	key (AP) back to the appearance that is used for the unvalidated 
	state. 
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation.
	@see DSValidateSigProc 
	@see DSReValidateSigProc 
	@see DigSigGetStdXObj 
	@see DigSigFileGetEOF 
	@see DigSigMD5ByteRange 
	@see DigSigFileRead 
	@see DigSigFileSetPos 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSUnValidateSigProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot);

/** Sends a notification for this signature. The only current notification is
	<code>kDSNotifySetUnknown</code>, which will cause handlers to mark the validity 
	for this signature as unknown. This is done if the document
	is dirtied or changed in a manner that would cause the current validity status
	to no longer be valid. This is not the same as the <code>DSUnValidateProc()</code>. 
	The handler should update its cached validity values to the signature unknown state. */
typedef ACCBPROTO1 void (ACCBPROTO2 *DSNotifySigProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, DSNotifySigType notifyType, ASBool bUI );

/* DigSig uses this callback to send a notification that it has cleared the signature. This
	clears the local caching.
	@param IN/OUT pdDoc The document being signed.
	@param IN/OUT sigField The signature field.
	@param IN/OUT sigAnnot The Cos object of the signature annotation.
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSClearSigProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASBool bSilent );

/**
	Called to obtain an <code>ASCab</code> containing values that the handler 
	wants DigSig to use in the user interface. This is called only after 
	the handler is called to validate the signature. 
	@param pdDoc The document being signed. 
	@param sigField The signature field. 
	@param sigAnnot The Cos object of the signature annotation. 
	
	@param handlerName The name of the handler that is being 
	asked to return the data. This is not necessarly the same 
	as the value of the <code>/Filter</code> attribute in the signature dictionary.
	@return An <code>ASCab</code> object containing the properties. For a list of 
	properties, see DigSigHFT.h. 
*/
typedef ACCBPROTO1 ASCab (ACCBPROTO2 *DSGetSigPropProc)
	(PDDoc pdDoc, CosObj sigField, CosObj sigAnnot, ASAtom handlerName );

/** Signs a <code>CosDoc</code> (for example, when signing FDF). It is for Adobe use only. This call is
   subject to change in future releases. It was introduced in Acrobat
   6.0. */
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *DSCosDocSigSignProc)
	(DigSigCosDocSigParams sigParams );

/** Validates a <code>CosDoc</code> signature. It returns a valid state in <code>sigInfoCab</code>.
	<p>It should populate the following entries in this cab:</p>
	<ul>
	<li><code>PROP_SigInfo_Status</code></li>
	<li><code>PROP_SigInfo_StatusText</code></li>
	<li><code>PROP_SigInfo_HandlerName</code></li>
	</ul>
	It is for Adobe use only. This call is subject to change in future releases.
	It was introduced in Acrobat 6.0. */
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *DSCosDocSigValidateProc)
	(DigSigCosDocSigParams sigParams, ASCab sigInfoCab );

/** Initiate the signing of a data buffer (for example, when signing XML data).
	It is for Adobe use only. This call is subject to change in future releases.
	It was introduced in Acrobat 7.0.
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *DSDataBufferSigSignNewProc)
	(DigSigDataBufferSigNewParams sigParams, void** pOutDataSigContext  );

/** Finish the signing of a data buffer (for example, when signing XML data).
	It must be called to destroy the context, whenever <code>signNew</code> returns a context.
	It is for Adobe use only. This call is subject to change in future releases.
	It was introduced in Acrobat 7.0.
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *DSDataBufferSigSignFinishProc)
	( void* dataSigContext, DigSigDataParams sigParams );

/**	Validate a data buffer signature. It returns a valid state in <code>sigInfoCab</code>.
	It should populate the following entries in this cab:
	<ul>
	<li><code>PROP_SigInfo_Status</code></li>
	<li><code>PROP_SigInfo_StatusText</code></li>
	<li><code>PROP_SigInfo_HandlerName</code></li>
	</ul>
	It is for Adobe use only. This call is subject to change in future releases.
	It was introduced in Acrobat 7.0.
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *DSDataBufferSigValidateProc)
	(DigSigDataBufferSigValidateParams sigParams, ASCab sigInfoCab );

/**
	Gets the boolean value of a <code>DigSig</code> handler property. It returns 
	<code>true</code> for those properties that represent functionality your 
	handler supports, <code>false</code> if it does not support the functionality. 
	(Some properties are available directly from the <code>DigSigHandler</code>.) 
	
	@param filter The name (<code>filterKey</code> value) of the handler 
	from which the property is obtained. 
	@param property The property whose value is obtained.
	@return The property value (<code>true</code> or <code>false</code>). 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DSGetBoolPropertyProc)
	( ASAtom filter, DSHandlerProperty property);

/**
    Returns whether the current application user has the credential that 
    was used to create the signature that was passed in.

    @param handlerName  The name of the handler that is being queried.
    @param pdd          The <code>PDDoc</code> containing the signature field.
    @param sigField     The signature field.
    @return One of the following values:
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD><code>0</code></TD><TD>Unknown.</TD></TR>
	<TR><TD><code>1</code></TD><TD>Yes.</TD></TR>
	<TR><TD><code>2</code></TD><TD>No.</TD></TR>
	</TABLE>
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *DSIsSignerProc)
    ( ASAtom handlerName, PDDoc pdd, CosObj sigField );

/** A data structure containing callbacks that define a signature plug-in's behavior. 
	Unused entries should be <code>NULL</code>.
*/
typedef struct _t_DigSigHandlerRec {
	/** The size of the data structure. It must be set to <code>sizeof(DigSigHandlerRec)</code>. */
	ASSize_t	size;
	/** The language-dependent name to show for signature type selection. */
	const char *uiName;				
	/** The value of the Filter key in the signature dictionary. */
	ASAtom filterKey;				
	/** <code>true</code> if this signature type can do no-appearance signatures, <code>false</code> otherwise. */
	ASBool canBlindSign;			
	/** <code>true</code> if this signature type can do encrypt-and-sign, <code>false</code> otherwise. */
	ASBool canEncrypt;				

	/** Called when a new document is opened. */
	DSDocOpenProc			dsDocOpen;		
	/** Called when a new document is closed. */
	DSDocCloseProc			dsDocClose;		
	/** Called when a new signature field is created. */
	DSDefaultValueProc		dsDefaultValue;	

	/** Called to gather the signature or cancel. */
	DSNewSigDataProc		dsNewSigData;   
	/** Called to put the signature into the document or cancel. */
	DSCommitSignProc		dsCommitSign;	
	/** Called to calculate the checksum and overwrite. */
	DSFinishSignProc		dsFinishSign;	
	/** Called to free the signature data. */
	DSFreeSigDataProc		dsFreeSigData;	
	/** Called to validate a signature. */
	DSValidateSigProc		dsValidateSig;
	/** Gets the validity status for a signature. */
	DSGetValidStateProc		dsGetValidState;
	/** Shows the signature properties dialog box for this signature. */
	DSPropertiesProc		dsProperties;	
	/** Called to change AP back to unvalidated. */
	DSUnValidateSigProc		dsUnValidateSig; 

	/** Called to change AP back to whatever it was. */
	DSUnValidateSigProc		dsReValidateSig; 

	/* New in Acrobat 5.0 */
	/** A notification that the signature has been cleared. */
	DSClearSigProc				dsClearSig;		
	/** Gets a string describing the status. */
	DSGetStatusTextProc			dsStatusText;	
	/** Used internally in Acrobat 5.0. Superseded in Acrobat 6.0 by <code>dsNewSigDataWithParams()</code>.*/
	DSNewSigDataExProc			dsNewSigDataEx;
	/** Used internally by <code>PubSec</code>. */
	DSValidateSigExProc			dsValidateSigEx;
	/** Used internally by <code>PubSec</code>. */
	DSGetSigInfoProc			dsGetSigInfo;
	/** Used internally by EScript in Acrobat 5.0. It is no longer used. */
	DSNewSigEngineProc			dsNewSigEngine;
	/** Called to get a descriptive string for an error during new, commit, or free steps.*/
	DSSigDataGetErrorTextProc	dsSigDataGetErrorText;

	/* New in Acrobat 6.0 */
	/** Called to create new signature data to be used by Commit and Finish. Supersedes 
		<code>dsNewSigDataEx()</code>. 
	*/
	DSNewSigDataWithParamsProc	dsNewSigDataWithParams;
	/** Called to show the signature properties dialog box for the signature. */
	DSPropertiesExProc			dsPropertiesEx;
	/** For internal use only.*/
	DSCosDocSigSignProc			dsCosDocSigSign;
	/** For internal use only.*/
	DSCosDocSigValidateProc		dsCosDocSigValidate;
	
	/** Called to determine whether the handler can validate a <code>PDDoc</code> field signature.*/
	DSCanValidateProc			dsCanValidate;
	/** */
	DSNotifySigProc				dsNotifySig;
	/** Used internally by <code>PubSec</code>. */
    DSGetSigSeedValueProc       dsGetSigSeedValue;   
	/** Used internally by <code>PubSec</code>. */
    DSSetSigSeedValueProc       dsSetSigSeedValue;
	/** Called to test whether your handler supports specific functionality. */
	DSGetBoolPropertyProc		dsGetBoolProperty;
	/** Called to get an <code>ASCab</code> containing signature properties to be used in the user interface. */
	DSGetSigPropProc			dsGetSigProp;

	/* New in Acrobat 7.0 */
    /** Determines whether the current user is the signer of the signature passed in. */
    DSIsSignerProc              dsIsSigner;
	/** Filter alias. */
	ASAtom						filterAlias;

	/* Data buffer signing and verification. For Adobe internal use only. */
	DSDataBufferSigSignNewProc	dsDataBufferSigSignNew;

	/* Data buffer signing and verification. For Adobe internal use only. */
	DSDataBufferSigSignFinishProc	dsDataBufferSigSignFinish;

	/* Data buffer signing and verification. For Adobe internal use only. */
	DSDataBufferSigValidateProc dsDataBufferSigValidate;

	/** Acrobat 10 - Handle files longer than 2147483647 bytes
		DigSig will attempt to call these if they are defined
    */
	/** Called to put the signature into the document or cancel. */
	DSCommitSign64Proc		dsCommitSign64;	
	/** Called to calculate the checksum and overwrite. */
	DSFinishSign64Proc		dsFinishSign64;	
	/** Called to free the signature data. */

} DigSigHandlerRec, *DigSigHandler;



/*****************************************************************************\
|*																			 *|
|*				INTERFACE TO DIGSIG <--- SPECIFIC METHODS					 *|
|*																		 	 *|
\*****************************************************************************/

/*****************************************************************************\
|*								DigSigHFT types								 *|
\*****************************************************************************/

/* The DigSigHFT allows calls from a specific method plugin to the generic plugin */
/* Enumerate the selectors */
#define PIPROC(returnType, name, params, ...)		name##_SEL,
#define NOPROC(name)								name##_SEL,

enum
{
	DSDUMMYBLANKSELECTOR,
	#include "DigSigHFTProcs.h"
	DSNUMSELECTORSPlusOne
};

#define DigSigHFT_NUMSELECTORS (DSNUMSELECTORSPlusOne - 1)
#undef PIPROC
#undef NOPROC

/** A linked list of text items to be merged together. */
typedef struct _t_DSAPTextEntryRec {
	/** The next entry in the list, or <code>NULL</code> if it is the last entry. */
	struct _t_DSAPTextEntryRec *next;	
	/** The ratio of the height to the overall height of <code>bbox</code> (<code>0x00010000</code> is 100%). */
	ASFixed heightRatio;			
	/** The text to render in this object. The caller owns the memory. */
	ASText text;				
} DSAPTextEntryRec, *DSAPTextEntry;

/**
	A user-supplied callback that is passed in the call to <code>DigSigEnumSignatures()</code>. 
	<code>DigSig</code> calls this once for each existing signature. 
	@param pdDoc The document that contains the signature 
	field. 
	@param sigField The signature field. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@return <code>true</code> to continue enumeration, <code>false</code> otherwise. 
	@see DigSigEnumSignatures 
*/
typedef ACCB1 ASBool ACCB2 (*DigSigEnumProc) ( PDDoc pdDoc, CosObj sigField, void *clientData );

/** Error constants for signature reference dictionary procedures. */
typedef enum {
	kDSSigRefErrNone=0,
	/**	Missing the required plug-in or software module.
		The software module is named by <code>errText</code> in
		DSSigRefDictErrParams.
	*/
	kDSSigRefErrMissingPlugin,
	/** The new, unsupported version of the signature.  */
	kDSSigRefErrNewVersion,
	/** The old, unsupported version of the signature. */
	kDSSigRefErrOldVersion,
	/** The size of the <code>DSSigRefErrCode</code> enumeration. */
	kDSSigRefErrEnumSize
} DSSigRefErrCode;

/** A structure that contains information about exceptions that occurred in signature
	reference dictionary procedures. 
*/
typedef struct _t_DSSigRefDictErrParamsRec {
	/** The The size of this <code>struct</code>. */
	ASSize_t size;				/* Size of this struct */
	/** The exception code. */
	DSSigRefErrCode errCode;	/* Exception code. */
	/** The text associated with the error code. If <code>errCode</code> is
		<code>kDSSigRefErrMissingPlugin</code>, the text is the name of a software module.
		It must point to an initialized <code>ASText</code> object.
	*/
	ASText errText;				/* Name of software module, if errCode == kDSSigRefErrMissingPlugin. Must point to initialized <code>ASText</code> object. */
} DSSigRefDictErrParamsRec, *DSSigRefDictErrParams;

/** Parameters used by methods that create a signature reference dictionary. See Section 8.7,
	<i>Digital Signatures</i>, in the <i>PDF Reference</i>, for more information on signature reference
	dictionaries. 
*/
typedef struct _t_DSSigRefDictParamsRec {
	/** The size of the data structure. It must be set to
		<code>sizeof(DSSigRefDictParamsRec)</code>.
	*/
	ASSize_t size;				/* Size of this struct */
	/** The document containing the object to be signed. */
	CosDoc cosDoc;				/* CosDoc in which to-be-signed object resides */
	/** The root object to be signed. */
	CosObj rootObj;				/* Root object that is being signed */
	/** The signature dictionary that this reference dictionary will be part of. */
    CosObj sigDict;             /* References will be part of this sigDict */
    /** The transform method name. Its possible values are:
	<ul>
	<li><code>DocMDP</code></li>
	<li><code>FieldMDP</code></li>
	<li><code>UR</code></li>
	<li><code>Identity</code></li>
	</ul>
	*/
	ASAtom transformMethod;		/* Transform name */
	/** The transform parameters, which are specific to each transform method. */
	CosObj transformParams;		/* Parameters to transform */
	/** <code>true</code> if the dictionary should be indirect, <code>false</code> if it should be direct. */
	ASBool bIndirect;			/* Set <code>true</code> if refDict should be indirect */
} DSSigRefDictParamsRec, *DSSigRefDictParams;

typedef struct _t_DSAPCreateLayeredStreamExParams
{	
	/** The document in which to include the standard XObject. */
	CosDoc cosDoc;	
	/** A pointer to an array of XObjects for the appearance layers.*/
	CosObj* XObjects;
	/** A pointer to an array of positions. */
	ASFixedMatrixP layerMatrices;
	/** The size of the XObjects array. */
	ASInt32 numXObjects;
	/** The layer number for the optional validity state layer. */
	ASInt16 layerNNum;
	/** The border from AFPDWidgetGetBorder(). */
	AFPDWidgetBorder border; 
	/** The color of the border. */
	PDColorValue cBorder;
	/** The color of the background. */
	PDColorValue cBackGnd;
	/** The width of the new stream object. */
	ASFixed width;
	/** The height of the new stream object. */
	ASFixed height;
	/** The rotational parameter from AFPDWidgerGetRotation(). */
	PDRotate pdr; 
	/** An array of flag values corresponding 
		to the layers specified by XObject. A value of <code>true</code> means 
		that the corresponding layer is displayed. 
	*/
	ASBool* layerFlags;
} DSAPCreateLayeredStreamExParamsRec, *DSAPCreateLayeredStreamExParams;

/** Justification of XObjects.
@see DigSigAPXObjectFromXObjList
*/
typedef enum {
	/** Left justification. */
	DSLeftQ = 0,
	/**Center justification.  */
	DSCenterQ,
	/** Right justification.  */
	DSRightQ
} DSQuadding;

/**
	Structure used in <code>DigSigAPXObjectFromXObjList()</code>. 
	@see DigSigAPXObjectFromXObjList
*/
typedef struct _t_DSAPXObjEntryRec {
	/** The next list entry.  */
	struct _t_DSAPXObjEntryRec *next;	
	/** If not <code>NULL</code>, use this XObject as the entry.  */
	CosObj xobj;					
	/** The rectangle relative to <code>bbox</code> in which to render the object.  */
	ASFixedRect rect;				
	/** If not empty, render this string (it can contain new lines).  */
	ASText text;					
	/** Font size, <code>0</code> for auto. */
	ASFixed textSize;				
	/** Justification of the XObject (not all options supported). */
	DSQuadding xjustify;			
	/** Justification of the XObject (not all options supported). */
	DSQuadding yjustify;			
	/** Scale the XObject within <code>rect</code>. */
	ASFixed scale;					
	/** If the XObject is Subtype XObject, then the XObject is merged up. */
	ASBool bMerge;					
	/** If <code>true</code> and <code>bMerge</code> is <code>true</code> and the XObject exists, then destroy the XObject. */
	ASBool bDestroy;					
} DSAPXObjEntryRec, *DSAPXObjEntry;

typedef enum {
	kDSMerge = 0x0001,
	kDSForceEmbed = 0x0002

} DSAPXObjectFromXObjectListFlags;

/** A type of notification to register for. 
	@see DigSigRegisterObserver
*/
typedef enum { 
	/** The signature field is added. */
    DSSigAdded = 0,/* Signature field is added */
    /** The signature field is deleted. */
    DSSigDeleted,  /* Signature field got deleted */
    /** A signature is requested (the notification procedure is
		invoked before the signature is applied).
	*/
	DSWillSign,
	/** A signature is created (the notification procedure is
		invoked when signing succeeds).
	*/
	DSDidSign,
	/** A signature request fails (the notification procedure is
		invoked when signing fails).
	*/
    DSFailSign,
    /** A signature verification is requested. */
	DSWillVerify,
	/** A signature verification succeeds. */
	DSDidVerify,
	/** A signature verification request fails. */
    DSFailVerify,
    /** The clearing of a signature is requested. */
	DSWillClear,
	/** The clearing of a signature succeeds. */
	DSDidClear,
	/** The clearing of a signature fails. */
    DSFailClear,
    /** Number of notifications. */
	DigSigNumNotifications	/* Always last. */
} DSNotificationType;


/** A structure passed to the callback when a digital signature event occurs for which an
	interest has been registered. The structure contains information about the event.
	
	<p>These are the arguments in <code>DSNtfyParams_t</code> which are applicable:</p>
	
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD><code>DSSigAdded</code></TD><TD></TD></TR>
	<TR><TD><code>DSSigDeleted</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	<TR><TD><code>DSWillSign</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	<TR><TD><code>DSDidSign</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField, sigDict</code></TD></TR>
	<TR><TD><code>DSFailSign</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	<TR><TD><code>DSWillVerify</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	<TR><TD><code>DSDidVerify</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField, sigDict</code></TD></TR>
	<TR><TD><code>DSFailVerify</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	<TR><TD><code>DSWillClear</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField, sigDict</code></TD></TR>
	<TR><TD><code>DSDidClear</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	<TR><TD><code>DSFailClear</code></TD><TD><code>size, notificationID, pdDoc, cosDoc, sigField</code></TD></TR>
	</TABLE>
*/
typedef struct _t_DSNtfyParamsRec {
	/** The size of the data structure. It must be set to
		<code>sizeof(DSNotifyParamsRec)</code>.
	*/
    ASSize_t           size;
    /** The event that occurred. */
    DSNotificationType notificationID;
    /** The PDF document for which the event occurred. */
	PDDoc 	           pdDoc;          
	/** The Cos document containing the object for which the event
		occurred.
	*/
    CosDoc             cosDoc;
    /** The signature field for which the event occurred. */
    CosObj             sigField;
    /** The signature dictionary (used only for the events <code>DSDidSign</code>
		and <code>DSDidClear</code>).
	*/
    CosObj             sigDict;
} DSNtfyParamsRec, *DSNtfyParams;

/**
	A callback for the Notification Server. It is called when a digital 
	signature event occurs for which you have registered an 
	interest. 
	
	<p>This procedure is called for these events: </p>

	<ul>
	<li>Adding or deleting a signature field.</li>
	<li>Requesting a new signature, and the success of the request. </li>
	<li>Requesting that an existing signature be cleared, and the success of the request. </li>
	</ul>

	<p>For failure events, the server calls the DSNotificationFailureProc(). </p>
	
	@param info Pointer to a DSNotifyParams structure containing 
	information about the event. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see DSNotificationFailureProc 
	@see DigSigRegisterObserver 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSNotificationProc)(void *info, void *clientData);

/**
	A callback for the Notification Server. It is called when a digital 
	signature event occurs for which you have registered an 
	interest. 
	
	<p>This procedure is called for these events: </p>

	<ul>
	<li>The failure of a request for a new signature. </li>
	<li>The failure of a request for an existing signatureto be cleared. </li>
	</ul>

	<p>For field change, request, and success events, the server 
	calls the DSNotificationProc(). </p>
	@param error The error code for the error that occured. 
	
	@param info A pointer to a DSNotifyParams structure containing 
	information about the event. 
	@param clientData A pointer to user-supplied data to pass 
	to <code>proc</code> each time it is called.
	@see DSNotificationProc 
	@see DigSigRegisterObserver 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DSNotificationFailureProc)(ASInt32 error, void *info, void *clientData);

/** Parameters for page comparison. 
	@see DigSigComparePagesEx
*/
typedef struct _t_DSComparePagesParamsRec {
	/** The size of the data structure. It must be set to
		<code>sizeof(DSComparePagesParamsRec)</code>.
	*/
	ASSize_t	size;
	/** The sensitivity level for the comparison. The DPI determines
		the resolution at which each page is rendered before
		comparing on a pixel-by-pixel basis. The values are:

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD><code>0</code></TD><TD>72 DPI.</TD></TR>
		<TR><TD><code>1</code></TD><TD>36 DPI.</TD></TR>
		<TR><TD><code>2</code></TD><TD>18 DPI.</TD></TR>
		</TABLE>
	*/
	ASInt32 sensitivityLevel;
	
} DSComparePagesParamsRec, *DSComparePagesParams;

/** Parameters for page comparison.
	@see DigSigCompareWordsEx
*/
typedef struct _t_DSCompareWordsParamsRec {
	/** The size of the data structure. It must be set to
		<code>sizeof(DSCompareWordsParamsRec)</code>.
	*/
	ASSize_t	size;
	/** If <code>true</code>, the font name, size, and color of each character in a word are
		considered when matching against other words. If <code>false</code>, these
		attributes are ignored.
	*/
	ASBool useFont;				/* Turn font comparison on or off. */
} DSCompareWordsParamsRec, *DSCompareWordsParams;

/* Create the prototypes */
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
#define NOPROC(name)
	#include "DigSigHFTProcs.h"
#undef PIPROC
#undef NOPROC

#define DigSigRegisterFilter (*((DigSigRegisterFilter_SELPROTO)(gDigSigHFT[DigSigRegisterFilter_SEL])))
#define DigSigFileGetEOF (*((DigSigFileGetEOF_SELPROTO)(gDigSigHFT[DigSigFileGetEOF_SEL])))
#define DigSigFileGetEOF64 (*((DigSigFileGetEOF64_SELPROTO)(gDigSigHFT[DigSigFileGetEOF64_SEL])))
#define DigSigFileSetPos (*((DigSigFileSetPos_SELPROTO)(gDigSigHFT[DigSigFileSetPos_SEL])))
#define DigSigFileSetPos64 (*((DigSigFileSetPos64_SELPROTO)(gDigSigHFT[DigSigFileSetPos64_SEL])))
#define DigSigFileRead (*((DigSigFileRead_SELPROTO)(gDigSigHFT[DigSigFileRead_SEL])))
#define DigSigOverwriteIntArray (*((DigSigOverwriteIntArray_SELPROTO)(gDigSigHFT[DigSigOverwriteIntArray_SEL])))
#define DigSigOverwriteIntArray64 (*((DigSigOverwriteIntArray64_SELPROTO)(gDigSigHFT[DigSigOverwriteIntArray64_SEL])))
#define DigSigOverwriteHexstring (*((DigSigOverwriteHexstring_SELPROTO)(gDigSigHFT[DigSigOverwriteHexstring_SEL])))
#define DigSigOverwriteHexstring64 (*((DigSigOverwriteHexstring64_SELPROTO)(gDigSigHFT[DigSigOverwriteHexstring64_SEL])))
#define DigSigOverwriteBytes (*((DigSigOverwriteBytes_SELPROTO)(gDigSigHFT[DigSigOverwriteBytes_SEL])))
#define DigSigOverwriteBytes64 (*((DigSigOverwriteBytes64_SELPROTO)(gDigSigHFT[DigSigOverwriteBytes64_SEL])))
#define DigSigMD5ByteRange (*((DigSigMD5ByteRange_SELPROTO)(gDigSigHFT[DigSigMD5ByteRange_SEL])))
#define DigSigUpdatePanel (*((DigSigUpdatePanel_SELPROTO)(gDigSigHFT[DigSigUpdatePanel_SEL])))
#define DigSigByteToHex (*((DigSigByteToHex_SELPROTO)(gDigSigHFT[DigSigByteToHex_SEL])))
#define DigSigHexToByte (*((DigSigHexToByte_SELPROTO)(gDigSigHFT[DigSigHexToByte_SEL])))
#define DigSigSignDoc (*((DigSigSignDoc_SELPROTO)(gDigSigHFT[DigSigSignDoc_SEL])))
#define DigSigGetStdXObj (*((DigSigGetStdXObj_SELPROTO)(gDigSigHFT[DigSigGetStdXObj_SEL])))
#define DigSigDraw (*((DigSigDraw_SELPROTO)(gDigSigHFT[DigSigDraw_SEL])))
#define DigSigKeyDown (*((DigSigKeyDown_SELPROTO)(gDigSigHFT[DigSigKeyDown_SEL])))
#define DigSigClick (*((DigSigClick_SELPROTO)(gDigSigHFT[DigSigClick_SEL])))
#define DigSigRightClick (*((DigSigRightClick_SELPROTO)(gDigSigHFT[DigSigRightClick_SEL])))
#define DigSigGetUniqueTitle (*((DigSigGetUniqueTitle_SELPROTO)(gDigSigHFT[DigSigGetUniqueTitle_SEL])))
#define DigSigDeletedSig (*((DigSigDeletedSig_SELPROTO)(gDigSigHFT[DigSigDeletedSig_SEL])))
#define DigSigAddedSig (*((DigSigAddedSig_SELPROTO)(gDigSigHFT[DigSigAddedSig_SEL])))
#define DigSigComparePages (*((DigSigComparePages_SELPROTO)(gDigSigHFT[DigSigComparePages_SEL])))
#define DigSigCompareWords (*((DigSigCompareWords_SELPROTO)(gDigSigHFT[DigSigCompareWords_SEL])))
#define DigSigCompareWordsRecent (*((DigSigCompareWordsRecent_SELPROTO)(gDigSigHFT[DigSigCompareWordsRecent_SEL])))
#define DigSigDoProperties (*((DigSigDoProperties_SELPROTO)(gDigSigHFT[DigSigDoProperties_SEL])))
#define DigSigCompareWordsAndFontsRecent (*((DigSigCompareWordsAndFontsRecent_SELPROTO)(gDigSigHFT[DigSigCompareWordsAndFontsRecent_SEL])))
#define DigSigRollbackToSig (*((DigSigRollbackToSig_SELPROTO)(gDigSigHFT[DigSigRollbackToSig_SEL])))
#define DigSigEnumSignatures (*((DigSigEnumSignatures_SELPROTO)(gDigSigHFT[DigSigEnumSignatures_SEL])))
#define DigSigDocModifiedAfterSig (*((DigSigDocModifiedAfterSig_SELPROTO)(gDigSigHFT[DigSigDocModifiedAfterSig_SEL])))
#define DigSigCreateStdXObj (*((DigSigCreateStdXObj_SELPROTO)(gDigSigHFT[DigSigCreateStdXObj_SEL])))
#define DigSigAPCreateLayeredStream (*((DSAPCreateLayeredStream_SELPROTO)(gDigSigHFT[DSAPCreateLayeredStream_SEL])))
#define DigSigAPXObjectFromXObjList (*((DSAPXObjectFromXObjList_SELPROTO)(gDigSigHFT[DSAPXObjectFromXObjList_SEL])))
#define DigSigAPXObjectFromLogo (*((DSAPXObjectFromLogo_SELPROTO)(gDigSigHFT[DSAPXObjectFromLogo_SEL])))
#define DigSigAPCreateCompositeTextXObj (*((DSAPCreateCompositeTextXObj_SELPROTO)(gDigSigHFT[DSAPCreateCompositeTextXObj_SEL])))
#define DigSigDeletedSigEx (*((DigSigDeletedSigEx_SELPROTO)(gDigSigHFT[DigSigDeletedSigEx_SEL])))
#define DigSigAddedSigEx (*((DigSigAddedSigEx_SELPROTO)(gDigSigHFT[DigSigAddedSigEx_SEL])))
#define DigSigUnregisterFilter (*((DigSigUnregisterFilter_SELPROTO)(gDigSigHFT[DigSigUnregisterFilter_SEL])))
#define DigSigNewSigRefDict (*((DigSigNewSigRefDict_SELPROTO)(gDigSigHFT[DigSigNewSigRefDict_SEL])))
#define DigSigCommitSigRefDict (*((DigSigCommitSigRefDict_SELPROTO)(gDigSigHFT[DigSigCommitSigRefDict_SEL])))
#define DigSigFinishSigRefDict (*((DigSigFinishSigRefDict_SELPROTO)(gDigSigHFT[DigSigFinishSigRefDict_SEL])))
#define DigSigVerifySigRefDict (*((DigSigVerifySigRefDict_SELPROTO)(gDigSigHFT[DigSigVerifySigRefDict_SEL])))
#define DigSigClearSigRefDict (*((DigSigClearSigRefDict_SELPROTO)(gDigSigHFT[DigSigClearSigRefDict_SEL])))
#define DigSigAPCreateLayeredStreamEx (*((DSAPCreateLayeredStreamEx_SELPROTO)(gDigSigHFT[DSAPCreateLayeredStreamEx_SEL])))
#define DigSigIsSigSigned (*((DigSigIsSigSigned_SELPROTO)(gDigSigHFT[DigSigIsSigSigned_SEL])))
#define DigSigRegisterObserver (*((DigSigRegisterObserver_SELPROTO)(gDigSigHFT[DigSigRegisterObserver_SEL])))
#define DigSigUnregisterObserver (*((DigSigUnregisterObserver_SELPROTO)(gDigSigHFT[DigSigUnregisterObserver_SEL])))
#define DigSigGetDocAuthorSignature (*((DigSigGetDocAuthorSignature_SELPROTO)(gDigSigHFT[DigSigGetDocAuthorSignature_SEL])))
#define DigSigComparePagesEx (*((DigSigComparePagesEx_SELPROTO)(gDigSigHFT[DigSigComparePagesEx_SEL])))
#define DigSigCompareWordsEx (*((DigSigCompareWordsEx_SELPROTO)(gDigSigHFT[DigSigCompareWordsEx_SEL])))
#define DigSigVerifySig (*((DigSigVerifySig_SELPROTO)(gDigSigHFT[DigSigVerifySig_SEL])))
#define DigSigClearSig (*((DigSigClearSig_SELPROTO)(gDigSigHFT[DigSigClearSig_SEL])))
#define DigSigGetDocMDPSetting (*((DigSigGetDocMDPSetting_SELPROTO)(gDigSigHFT[DigSigGetDocMDPSetting_SEL])))
#define DigSigGetUbiquitySig (*((DigSigGetUbiquitySig_SELPROTO)(gDigSigHFT[DigSigGetUbiquitySig_SEL])))

#ifdef __cplusplus
}
#endif

#endif /* _H_DigSigHFT */

/* End of DigSigHFT.h */
