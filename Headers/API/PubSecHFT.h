/*************************************************************************
 * PubSecHFT.h
 *
 * Copyright (c) 2000-2006 Adobe Systems Inc. All Rights Reserved.
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
 * Public key security interface for Acrobat public-key security
 * handlers.  Handlers can register as PubSec handlers to provide
 * crypto services for private key signing, for signature validation,
 * as a crypto source for decrypting using private keys, and as a
 * directory source.
 *
 * Handlers can also call back into the PubSecHFT for various
 * services, including a signature appearance handler and a trusted
 * address book.
 *
 * Update History: (most recent first)
 *  30-Mar-2003 -- Acrobat 6.0 SDK cleanup
 *  13-Dec-2002 -- Acrobat 6.0 beta cleanup
 *  18-Oct-2002 -- Added Confidentiality notice
 *  11-Aug-2002 -- Added FDF data exchange import/export calls
 *	02-Aug-2002 -- Added new notification API for AAB, removed old API
 *  10-Mar-2002 -- Added routines to support CosDoc and generic signature API
 *  11-Jan-2001 -- Wrote hftbuild perl script to autogenerate portions of this file
 *  09-Jan-2001 -- Created for Acrobat 6.0
 ************************************************************************/

#ifndef PUBSECHFT_H
#define PUBSECHFT_H
   
#include "CosExpT.h"
#include "PDExpT.h"
#include "ASExpT.h"				/* Required for ASText */
#include "DigSigHFT.h"
#include "DirectoryHFT.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************
 * PubSecHFT globals
 ***********************************************************************************/
/* ---- Global typedefs, consts, and enums ---- */
#define PUBSEC_HFT_NAME "PubSecHFT"
#define PUBSEC_HFT_LATEST_VERSION (0x00010000)	//Not currently in use

extern HFT gPubSecHFT;

/************************************************************************************
 * PubSecHFT - Enumerations and structure declarations
 ***********************************************************************************/

/** The maximum size of the binary signature blob in bytes.
 @note This translates to <code>SIG_MAX_SIZE * 2 + 2</code> in the file, as it is hex-encoded 
 currently <code>(* 2)</code> and the delimiters at the two end <code>(+2)</code>.
 */
/* This was based on the maximum size of a CosString, but there is no maximum after Acrobat 6 */
#define PS_SIG_MAX_SIZE   2097152	// Bug 2266569 leave even more room for CRLs

/** 
	A PubSec engine object. There can be multiple engine objects per handler.
	@see PSCloseEncryptedDocs
	@see PSCountEncryptedDocs
*/
typedef void* PubSecEngine;

/** 
	A signature appearance file object to be used by handlers to access the built-in APIcon
	appearance handler.
	@see DSAPFileAcquire
*/
typedef struct CAPIconFile *DSAPFile;

/** Operations for which a PubSec session can be acquired. */
typedef enum { 
	/**  None */
	kPSOpTypeNone=0,
	/** Sign a PDDoc to create a PDDoc signature. */
	kPSOpTypePDDocSign,				
	/** Validate a PDDoc signature. */
	kPSOpTypePDDocSigValidate,		
	/** Sign a CosDoc. */
	kPSOpTypeCosDocSign,			
	/** Validate a CosDoc signature. */
	kPSOpTypeCosDocSigValidate,		
	/** Sign bytes. */
	kPSOpTypeDataSign,			 
	/** Validate bytes. */
	kPSOpTypeDataSigValidate,		
	/** Read and export My Contact information. */
	kPSOpTypeMyContactExport,		
	/** Import contacts into address book. */
	kPSOpTypeContactImport,			
	/** Modify credential access policy (used by EScript). */
	kPSOpTypePolicyModify,			
	/** Read an appearance file (used by EScript). */
	kPSOpTypeAPRead,				
	/** Prepare to encrypt documents. */
	kPSOpTypePDCryptDocCreate,		
	/** Prepare to open encrypted documents. */
	kPSOpTypePDCryptDocOpen,		
	/** Authenticate or login user (used by EScript). */
	kPSOpTypeLogin,					
	/** De-authenticate or logout user (used by EScript). */
	kPSOpTypeLogout,				
	/** Enumerate certificates available for signing and encryption. */
	kPSOpTypeCertEnum,				
	/** Enumerate directories and get directory information. */
	kPSOpTypeDirEnum,				
	/** Connect to and use a directory. */
	kPSOpTypeDirGet,
    /* Enumerate credential stores. */
    kPSOpTypeStoreEnum
} PSSessionOpType;

/** A signature type to use for generating a signature appearance.
	@see PSSigCreateAPNXObjProc
 */
typedef enum { 
	/** Signing a prexisting signature field. */
	kPSAPSigPreExists=0,		
	/** Creating a signature, on the fly, on a page. */
	kPSAPSigTentative,			
	/** Creating a preview of a signature. */
	kPSAPSigPreview				
} PSAPSigType;


/************************************************************************************
 * Enumerations and structures used for signing and validation
 ***********************************************************************************/

/** A buffer of data to be hashed when signing or verifying signatures. The buffer contains the
	bytes to be signed (by ByteRange) when signing a PDF file.
	@see PSDataBufferDigest
	@see PSDataBufferEnum
*/
typedef struct _s_PSDataBufferRec PSDataBufferRec, *PSDataBuffer;

/** Types of PDDoc signatures. */
typedef enum {
	/** */
    kPSSigTypeUnknown=0,
	/** An ordinary signature. */
	kPSSigTypeUser,			
	/** An ordinary signature, plus an MDP object signature. */
	kPSSigTypeAuthor,		
	/** An Adobe Reader rights-enabling object signature. */
	kPSSigTypeUbiquity,		
	/** */
    kPSSigTypeEnumSize
} PSSigType;

/** The type of document being signed.
	@see PSSigPDDocParams
	@see PSSigSigPropParams
	@see PSSigValidateDialogParams
*/
typedef enum {
	/** */
	kPSSigDocTypeNone=0,
	/** A PDF document. */
	kPSSigDocTypePDDoc,			
	/** An FDF file. */
	kPSSigDocTypeCosDoc,		
	/** Transactional data (for example, XFA). */
	kPSSigDocTypeTransData,		
	/** */
	kPSSigDocTypeEnumSize
} PSSigDocType;

/** A constant value that indicates the file type and environment in which data is being signed,
	used to set up buttons and text in the signing dialog.
	@see PSSigSigPropParams
*/
typedef enum {
	/** Uninitialized. */
	kPSFileNone=0,			
	/** Normal PDDoc signing. Enable the Save and SaveAs buttons. */
	kPSFileAVDoc,			
	/** External browser window. Enable the Sign button. */
	kPSFileBrowserDoc,		
	/** External non-browser window. Enable the Sign button. */
	kPSFileExternalDoc,		
	/** Temp file. Enable the SaveAs button. */
	kPSFileTempDoc,			
	/** Signing an FDF Data Exchange file. Enable the Sign button. */
	kPSFileFDFData,			
	/** Signing a CosDoc. Enable the Sign button. */
	kPSFileCosDoc,			
	/** Signing transactional data. */
	kPSFileTransData,		
	/** */
	kPSFileEnumSize
} PSSigFileType;

/** Constants that specify the method to use for creating a signature. For details, see the <i>PDF
	Reference</i>.
	@see PSSigGetSigValueParams
	@see PSSigGetSigValueProc
*/
typedef enum {
	/** None */
	kPSSigMethodNone=0,
	/** <code>PKCS#1</code>, <code>adbe.x509.rsa.sha1</code> */
	kPSSigMethodPKCS1,					
	/** <code>adbe.pkcs7.detached</code> */
	kPSSigMethodPKCS7Detached,			
	/** <code>adbe.pkcs7.sha1</code> */
	kPSSigMethodPKCS7SHA1,				
	/** <code>ETSI.CAdES.detached</code> */
	kPSSigMethodETSICADES,				
	/** <code>ETSI.RFC3161</code> */
	kPSSigMethodETSIDocTimestamp,				
	/** */
	kPSSigMethodEnumSize
} PSSigMethod;

/** Dialog information, returned from GetSigProperties() and other
   calls to tell PubSec what flow of subsequent dialogs or actions to
   execute. Not all values are legal for all procs. */
typedef enum {
	/** No further dialogs are required. */
	kPSSigDialogNone=0,					
	/** PubSec's sign dialog box should be executed. */
	kPSSigDialogSign,					
	/** PubSec's sign dialog box should be executed, and should ask for a password. */
	kPSSigDialogSignWithPassword,		
	/** PubSec's sign dialog box should be executed, then SigAuthenticate() should be called. */
	kPSSigDialogSignThenAuthenticate,	
	/** The size of the PSSigDialogStatus enum. */
	kPSSigDialogStatusEnumSize
} PSSigDialogStatus;

// Enum of whether signature validation is supported
/** Constant values indicating how a handler supports validation for a particular signature. */
typedef enum {
	/** The handler does not support validation of this signature. */
	kPSSigValSupportFalse,
	/** The handler supports validation of this signature. */
	kPSSigValSupportTrue,
	/** A handler software update is needed to support validation of this signature. */
	kPSSigValSupportUpdate,	
	/** The signature was created with a pre-release or invalid release of the software. The user is warned. */
	kPSSigValSupportPreRelease,
	/** The size of the PSSigValSupport enum. */
	kPSSigValSupportEnumSize
} PSSigValSupport;

/** A structure containing parameters and return values for
	PSSigGetSigPropertiesProc().
	@see SigGetSigPropertiesProc 
*/
typedef struct _t_PSSigSigPropParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) The PDDoc being signed. If a PDDoc is not being signed,
		this is only used for window parenting and can be <code>NULL</code>.
	*/
	PDDoc pdDoc;					
	/** (Constant) The file type and signing environment, which the
		handler uses to display appropriate save buttons.
	*/
	PSSigFileType fileOptions;		
	/** (Constant) When it is <code>true</code>, the call is being made from the user interface;
		when it is <code>false</code> it is being made from a script or batch file.
	*/
	ASBool bUI;						
	/** The title to use for the signing dialog, if <code>bUI</code> is <code>true</code>. It is usually
		<code>NULL</code>, which allows the handler to use the default.
	*/
	ASText dialogTitle;				
	/** (Constant) It represents the parameters passed in by EScript converted to an
		ASCab, or <code>NULL</code> if the call is not from EScript.
	*/
	ASCab sigParamsCab;				
	/** If you are not providing your own sign dialog, set this value to
		DSSignSave.

		<p>If you are providing your own sign dialog, return the result of your
		sign dialog. Setting the value to DSignCancel cancels the
		signing operation.</p>
	*/
	DSSaveType outSaveOptions;			
	/** Return status information that tells PubSec what dialogs to
		display and how to authenticate the handler.
	    
		<p>The legal return values are:</p> 

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD>kPSSigDialogNone</TD><TD>The handler provides its own sign dialog.</TD></TR>
		<TR><TD>kPSSigDialogSign</TD><TD>PubSec provides a sign dialog.</TD></TR>
		<TR><TD>kPSSigDialogSignWithPassword</TD><TD>PubSec provides a sign dialog box with a password.</TD></TR>
		<TR><TD>kPSSigDialogSignThenAuthenticate</TD><TD>PubSec provides a sign dialog, then afterwards calls the handler to allow the handler to authenticate the user.</TD></TR>
		</TABLE>
	*/
	PSSigDialogStatus outDialogStatus;	
	/** (Required) Return an ASCab containing an ordered certificate chain, signing certificate first (at key <code>0</code>). */
	ASCab outCertListCab;				
	/** (Required) Populate this existing ASCab with signature
		properties that will be written to the signature dictionary
		when the signature is committed.
	*/
	ASCab outNewSigPropCab;
	/** (Optional) Populate this existing ASCab with return build
		properties that will be written to the signature dictionary
		when the signature is committed.
	*/
	ASCab outNewSigBuildCab;
	/** (Constant) The type of document being signed. */
	PSSigDocType docType;			
	/** A structure containing signature parameters appropriate to
		the type of document. Depending on <code>sigType</code>, it is a structure
		of type PSSigPDDocParams, PSSigCosDocParams, or
		PSSigDataBufferParams.
	*/
	void* docParams;
	/** (Constant) A specification for SignatureValue. See the <i>PDF Reference</i> for details. */
	PSSigMethod sigMethod;			
	/** (Constant) A method used to create a digest. */
	DSDigestMethod digestMethod;	

    /**
        Additions for Acrobat 7.
    */
    /** The type of the signature being created
    */
    PSSigType inSigType;

} PSSigSigPropParamsRec, *PSSigSigPropParams;

/** A structure containing parameters and return values for PSSigGetSigValueProc(). */
typedef struct _t_PSSigGetSigValueParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) The method used to create the signature value. */
	PSSigMethod sigMethod;			
	/** (Constant) The method used to create the digest. */
	DSDigestMethod digestMethod;	
	/** (Constant) A digest value to be signed, or <code>NULL</code>. */
	const ASUns8* digestValue;		
	/** The handle to use for fetching bytes to digest. */
	PSDataBuffer dataBuffer;		
	/** (Constant) If <code>true</code>, get a signature value,
		otherwise return the size of the signature
		value.
	*/
	ASBool bGetSigValue;			
	/** Return the signature value data. The caller will call
		ASfree() to destroy the structure.
	*/
	ASUns8* outSigValueData;			
	/** The return size of <code>SignatureValue</code>. */
	ASUns32 outSigValueSize;			
	/** Return an ASCab containing signature
		properties that should be displayed instead of
		signature dictionary entries.
	*/
	ASCab outSigPropCab;		
} PSSigGetSigValueParamsRec, *PSSigGetSigValueParams;

/** A structure containing signature parameters for PSSigValidateSupportedProc(). 
	@see PSSigValidateSupportedProc */
typedef struct _t_PSSigValidateSupportParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) The value of the /Filter attribute for the signature. */
	ASAtom filter;			
	/** (Constant) The value of the /SubFilter attribute for the signature. */
	ASAtom subFilter;	
	/** (Constant) The value of the /V attribute for the signature. */
	ASInt32 version;			
	/** (Constant) The value of the /R attribute for the signature. */
	ASInt32 revision;			
	/** (Constant) The handler's build properties dictionary, as an ASCab. */
	ASCab buildCab;	
} PSSigValidateSupportParamsRec, *PSSigValidateSupportParams;

/** A structure containing parameters and return values for PSSigValidateProc().
	@see PSSigValidateProc */
typedef struct _t_PSSigValidateParamsRecRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) The method used to create the
		signature value. */
	PSSigMethod sigMethod;			
	/** (Constant) The method used to create the
		digest. */
	DSDigestMethod digestMethod;	
	/** (Constant) A digest value to be signed, or <code>NULL</code>. */
	ASUns8* digestValue;			
	/** (Constant) A signature value to be verified. */
	ASUns8* sigValueData;			
	/** (Constant) The size of the signature value. */
	ASUns32 sigValueSize;			
	/** (In and out) 
		<p>For a PKCS#1 signature, PubSec fills in the certificate chain.</p>
		<p>For a PKCS#7 signature, PubSec returns an empty ASCab.</p>
		<p> For both signature types, the handler must provide the certificate chain that was validated.</p>
	*/
	ASCab certListCab;
    /** Informs the handler whether revocation
		checks are required. Handlers should always
		do revocation checks, but return failure only
		when this value is <code>true</code>.
     */
    ASBool reqRevokeChecks;
    /** The maximum lifetime (in minutes) of the
		cached information that is used for revocation
		checking. This is relevant for some types of
		revocation checking (such as CRL-based revocation checking) and
		not for others (such as OCSP).
	*/
    ASInt32 maxRevokeInfoCacheLifetime;
	/** Returns an ASCab containing the validity of
		the signature. It must not be <code>NULL</code>.
		The handler must set the values for
		PROP_SigVal_Id and
		PROP_SigVal_TrustFlags, and can
		optionally set PROP_SigVal_IdPriv and/or
		PROP_SigVal_IDPrivTextValidity. The
		handler should also set the value of
		PROP_SigVal_Digest, if it is not already
		set. All other values should be left unmodified,
		since they will not be preserved by PubSec. 
	*/
	ASCab sigValCab;				
	/** Returns signature properties to display instead
		of signature dictionary entries.
	*/
	ASCab outSigPropCab;				
	/** The handle to use for fetching bytes to digest. */
	PSDataBuffer dataBuffer;			

    /*
        Additions for Acrobat 7.
    */
    /** PubSec provides the time that it thinks signing occured.
    */
    ASTimeRec *inSignTime;
    /** The type of signature being validated.
    */
    PSSigType inSigType;
	/** Cos document to which signature belongs */
	CosDoc cosDoc;
} PSSigValidateParamsRec, *PSSigValidateParams;

/** A structure containing parameters and return values for PSSigValidateDialogProc().
	@see PSSigValidateDialogProc
	@see PSSigPropDialogProc 
*/
typedef struct _t_PSSigValidateDialogParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (In and out) 
		<p>For a PKCS#1 signature, PubSec fills in the certificate chain.</p>
		<p>For a PKCS#7 signature, PubSec returns an empty ASCab.</p>
		<p> For both signature types, the handler must provide the certificate chain that was validated.</p>
	*/
	ASCab certListCab;    
	/** Informs the handler whether revocation
		checks are required. Handlers should always
		do revocation checks, but return failure only
		when this value is <code>true</code>.
	*/
    ASBool reqRevokeChecks;
    /** The maximum lifetime (in minutes) of the
		cached information that is used for revocation
		checking. This is relevant for some types of
		revocation checking (such as CRL-based revocation checking) and
		not for others (such as OCSP).
    */
    ASInt32 maxRevokeInfoCacheLifetime;
	/** An ASCab containing the validity of the
		signature. It is never <code>NULL</code>.
		The handler can validate the signature and
		update this object if desired.
	 */
	ASCab sigValCab;
	/** Indicates whether it is being called when a modal
		parent dialog box is open. If it is <code>true</code>, rollback and
		verify buttons should be disabled because:
		<ul>
		<li>Rollback is not possible while the modal parent is open.</li>
		<li>The verify status may not be propagated properly to various caching locations. </li>
		</ul>
	*/
	ASBool bModalParent;
	/** Returns a value that tells PubSec whether to
		roll back the signature or show a properties
		dialog box for the signature.
	*/
	DSPropertyType dsPropType;
	/** (Constant) The type of document being signed. */
	PSSigDocType docType;
	/** A structure containing signature parameters
		appropriate to the type of document.
		Depending on <code>sigType</code>, it is a structure of type
		PSSigPDDocParams or
		PSSigCosDocParams.
	*/
	void* docParams;
	ASCab sigPropCab;
	ASCab sigDictCab;
} PSSigValidateDialogParamsRec, *PSSigValidateDialogParams;

/** Validation parameters for validating a document signature or specific signature field.
	@see PSSigValidatePDDocSigField
	@see PSSigGetSigPropertiesProc
	@see PSSigCreateAPNXObjProc
	@see PSSigSigPropParams
*/
typedef struct _t_PSSigPDDocParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) It is always kPSSigDocTypePDDoc. */
	PSSigDocType sigType;			
	/** (Constant) The document being signed. */
	PDDoc pdDoc;					
	/** (Constant) The field being signed. */
	CosObj sigField;				
	/** (Constant) The annotation associated with this field. */
	CosObj sigAnnot;				
	/** (Constant) The width of the annotion, if the signature is visible. */
	ASFixed annotWidth;				
	/** (Constant) The height of the annotion, if the signature is visible. */
	ASFixed annotHeight;			
	/** Returns handler-specific appearance information for
		PSSigGetSigPropertiesProc(). */
	ASCab sigAPCab;					
} PSSigPDDocParamsRec, *PSSigPDDocParams;

/** Signature parameters for a CosDoc. It is used internally.
	@see PSSigGetSigPropertiesProc
	@see PSSigSigPropParams */
typedef struct _t_PSSigCosDocParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) Always kPSSigDocTypeCosDoc. */
	PSSigDocType sigType;			
	/** (Constant) <code>NULL</code> if there is no parent. */
	PDDoc pdDoc;					
	/** (Constant) The document being signed. */
	CosDoc cosDoc;					
	/* (Constant) The signature dictionary. */
/*	CosObj sigDict;	*/				
} PSSigCosDocParamsRec, *PSSigCosDocParams;

/** Signature parameters for signing transitional data, such as XFA.
	@see PSSigGetSigPropertiesProc
	@see PSSigSigPropParams
*/
typedef struct _t_PSSigDataBufferParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** (Constant) Always kPSSigDocTypeTransData. */
	PSSigDocType sigType;			
	/** (Constant) <code>NULL</code> if there is no parent. */
	PDDoc pdDoc;					
	/** (Constant) The document being signed. */
	CosDoc cosDoc;					
	/* const */
/*	CosObj sigDict;	*/			
} PSSigDataBufferParamsRec, *PSSigDataBufferParams;

/** Reasons why opening a CMS envelope could be requested */
typedef enum {
    kPSDecryptionReasonUnspecified = 0,
    /** Decrypting a document. */
    kPSDecryptingDocument,
    /** Decrypting a file attachment. */
    kPSDecryptingAttachment,
    /** Obtaining access to an encrypted batch command. */
    kPSDecryptingBatchCommand
} PSDecryptionReason;

/** Parameters that are used when opening a CMS envelope. */
typedef struct _t_PSOpenCMSEnvelopeParamsRec {
	/** The size of this structure. */
	ASSize_t size;

	/** (Constant) The ASN1 encoded PKCS#7 Enveloped
		Data to open. */
	const ASUns8* cmsEnvelopeData;
	/** The size in bytes of the data pointed to by
		<code>cmsEnvelopeData</code>. */
	ASUns32 cmsEnvelopeSize;

	/** Returns the envelope contents data. PubSec
		owns, allocates and frees the memory. */
	ASUns8* outEnvelopeContentsData;
	/** The size in bytes of the data pointed to by
		<code>cmsEnvelopeContentsData</code>. */
	ASUns32 outEnvelopeContentsSize;

	/** (Optional) Returns the session key recovered
		when opening the envelope. If a session key is
		returned by the handler, PubSec uses it to open
		other recipient groups and enable the user to
		edit them.
*/
	ASUns8* outSessionKeyData;
	/** The size in bytes of the data pointed to by
		<code>outSessionKeyData</code>. */
	ASUns32 outSessionKeySize;

	/** (Optional) The certificate corresponding to the
		private key used to open the envelope. When it is 
		provided, PubSec displays the name of the
		opener when the user edits the recipient list.
	 */
	ASCab outCertificates;

    /** The reason why the opening of a CMS envelope is requested. */
    PSDecryptionReason inReason;

} PSOpenCMSEnvelopeParamsRec, *PSOpenCMSEnvelopeParams;

typedef struct _t_PSSigSignReportParamsRec
{
	/** The size of this structure. */
	ASSize_t size;
	/** Signature properties of the signature we would like to report on.	*/
	ASCab sigPropCab;
} PSSigSignReportParamsRec, *PSSigSignReportParams;



/*************************************************************************
 * Validity Cab public properties and property values.  This Cab is
 * populated by PubSec and its handlers when validating signatures. It
 * contains the validity state of the signature, and is cached by
 * PubSec so that validity information is immediately available to
 * javascript calls and UI. Handlers can populate the ASCab with
 * additional custom values as required. PubSec takes care of most of these values.
 * The PubSec handler must set PROP_SigVal_Id and may set PROP_SigVal_IdPriv.
 * The PubSec handler must set PROP_SigVal_Digest with the result of the
 * digest comparison: this occurs when comparing the signed digest 
 * to the passed-in digest, or when calculating a byte range digest. 
 * The PubSec handler also must set PROP_SigVal_TrustFlags, though
 * these values may be 'tested' by PubSec.
 * PubSec will update the ASCab itself, just after signing, 
 * to set the state to 'just signed' (kDSSigValJustSigned).
 ************************************************************************/

/* Public Validity Cab entries.  Engines can add their own private
   entries, but must do so using their own namespace
   (e.g. "Acme:Identity") to prevent future name clashes. */
#define	PROP_SigVal_DS		"ds"		/* value is ASInt32(DSValidState), state returned through DigSigHFT */
#define	PROP_SigVal_Digest	"digest"	/* value is ASInt32(DSSigValState), handler digest result, indicates if signature digest is valid */
#define	PROP_SigVal_Doc		"doc"		/* value is ASInt32(DSSigValState), byte range digest result */
#define	PROP_SigVal_Obj		"obj"		/* value is ASInt32(DSSigValState), object signature results, used by author sigs and ordinary sigs when MDP+ is used */
#define	PROP_SigVal_Id		"id"		/* value is ASInt32(DSValidState), Indicates whether identity is valid */
#define PROP_SigVal_IdPriv	"idPriv"	/* value is handler-specific ASInt32. Indicates identity validity. */
#define PROP_SigVal_IdPrivText	"idPrivText"	/* Language-independent, machine readible version of  PROP_SigVal_IdPriv (eg. 'kIdUnknown') */
#define	PROP_SigVal_AuthSig	"authSig"	/* value is ASInt32(DSSigValState),  indicates the status of the author sig for this document */
#define	PROP_SigVal_Mod		"mod"		/* value is ASBool, <code>true</code> if doc has been modified after this sig was applied */
#define	PROP_SigVal_Author	"auth"		/* value is ASBool, <code>true</code> if this signature is an author signature */
#define	PROP_SigVal_Ubiquity "ubiquity"	/* value is ASBool, <code>true</code> if this signature is an ubiquity signature. This if for Adobe's internal user only*/
#define	PROP_SigVal_Data    "data"	    /* value is ASBool, <code>true</code> if this signature is an data signature */
#define	PROP_SigVal_FDF     "fdf"	    /* value is ASBool, <code>true</code> if this signature is an FDF signature */
#define PROP_SigVal_TrustFlags "trustFlags" /* value is ASInt32(PSSigTrust), stores the actions that the signer is trusted for */

/** The types of text requested by PSSigValGetTextProc() for a signature-validity ASCab
	object. The strings are generated by the handler, usually on the fly, when requested. A
	handler can cache the values in the <code>sigVal</code> ASCab (Acrobat plug-ins do not do this).
	PubSec copies values for DSTop, DSDetail, DSDetails and DSTooltip to the
	signature-propeties ASCab.

	<p>For optional entries, returning <code>NULL</code> causes PubSec to generate the values.
	Depending on the context, one of the <code>*IdValidity</code> entries is required to specify the
	signer identity validity.</p>

*/
typedef enum {
	/** Never called. It should return <code>NULL</code>. */
	kDSSigValTextNull,			
	/* (Optional) Get text to show in the AVPanel,
		added to the end of signature summary line. */
	kDSSigValTextDSTop,			
	/** (Optional) Get text to show in the AVPanel,
		shown in the signature detail title line. */
	kDSSigValTextDSDetail,		
	/** (Optional) Get text to show in the tooltip when
		the mouse is over the signature annotation. */
	kDSSigValTextDSTooltip,		
	/** (Optional) Get text to show in the EScript
		SignatureInfo object. */
	kDSSigValTextSigInfo,		
	/** (Optional) Get text to show in the validate alert
		dialog. */
	kDSSigValTextVal,			
	/** (Optional) Get text to show in the signature
		properties dialog. */
	kDSSigValTextProp,			
	/** (Optional) Get text to show in the appearance, if
		the signature appearance uses layer n4 (not
		recommended). In this case, you must also
		pass an index. */
	kDSSigValTextAP,			
	/* Get text to describe the validity of the signer
		certificate (used in properties and validity
		dialogs). */
	kDSSigValTextPropIdValidity,
	/** Get text to describe the validity of the signer
		certificate (used in AVPanel). */
	kDSSigValTextDSAVIdValidity,
	/** Get text to describe the validity of the signer
		certificate (appended to the tooltip, and called only
		when describing why the certificate is invalid). */
	kDSSigValTextDSTTIdValidity,
	/** */
	kDSSigValTextEnumSize
} DSSigValText;

/** Bit flag constants that specify a level of trust for a certificate.
	@see AABGetTrustedCerts
	@see PSImportDataParams
*/
typedef ASInt32 PSSigTrust;
/** The certificate is untrusted. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustUntrusted			0x0000	
/** Trusted for signing (creating recipient signatures). 
    @note Starting with Acrobat 7, this flag can no longer be (un)set by the user. This 
    flag is always set internally .
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustSigning              0x0001  

/** Trusted for authoring documents (creating author signatures). 	
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustAuthenticDocuments	0x0002	

/** Trusted for authoring documents with dyamic (multimedia) content. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustDynamicContent		0x0004	

/** Trusted for feature-enabling signatures (Adobe internal use only). 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustUbiquity				0x0008	

/** Trusted for authoring documents with full access JavaScript. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustJavaScript		    0x0010	

/** Trusted for identity: it must be present to use in trust calculations. 	
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustIdentity				0x0020	

/** Trusted as an anchor: no checks are done for certificates above this certificate. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustAnchor				0x0040	

/** Trusted for by-passing Crossdomain check. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustCrossDomain          0x0080

/** Trusted for accessing external resources/Streams. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustExternalStream       0x0100

/** Trusted for silent printing. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustSilentPrint          0x0200

/** Trusted for Connecting to Web. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustWebLink              0x0400

/** Trusted for Forms data injection. 
@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustDataInjection        0x0800

/** Trusted for Forms Script injection. 
@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustScriptInjection      0x1000

/** Trusted for Unsafe JavaScript. 
@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustUnsafeJavaScript      0x2000

/** Trusted to be the root for non-explicit Policy Constraints checking model
    Must be also a trust anchor.
	@ingroup BitFlagConstantsCertTrust
 */
#define kPSSigTrustNonExplicitPolicy     0x4000

/** Trusted for everything. 
	@ingroup BitFlagConstantsCertTrust
*/
#define kPSSigTrustAll                  0x0000FFFF  

/*************************************************************************
 * Import and Export data
 ************************************************************************/

/** The format of data to be imported using PSImportDataProc().
	The operation is only executed if the corresponding property (PROP_ImportContact or
	PROP_ImportDirSettings) is set, which indicates that the handler supports this
	format. If PROP_ImportContact is set, both of the corresponding formats must be
	supported. */
typedef enum {
	/** None. No import operation is performed. */
	kPSImportDataNone=0,
	/** An ASCab containing a list (<code><code>"0", "1", ...</code></code>) of
		contact cabs. Contact cabs have the entries
		PROP_ContactCab_*. */	
	kPSImportDataContactsCab,			
	/** An ASCab containing a list (<code>"0", "1", ...</code>)
		containing a single contact cab. This Contact
		cab will have only the
		PROP_ContactCab_Certs entry set.
		This is sent only when trusting the signer of a
		signature. */	
	kPSImportDataContactsCabFromSig,
	/** An ASCab containing a list (<code>"0", "1", ...</code>) of directory
		setting cabs, which have the entries
		<code>PROP_DirSettingCab_*</code>. */	
	kPSImportDataDirsCab,		
	/** The size of the PSImportDataType. */
	kPSImportDataEnumSize
} PSImportDataType;

/** Parameters for importing data from a file into PubSec; it is used in PSImportDataProc().
	@see PSImportDataProc */
typedef struct _t_PSImportDataParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** The format of the data to be imported. */
	PSImportDataType dataType;	
	/** 	If <code>dataType</code> is kPSImportDataSigDict, it is the signature dictionary.
			If <code>dataType</code> is kPSImportDataFDFImportArray, it is the import array.
			If <code>dataType</code> is kPSImportDataFDFDirArray, it is the directory settings array.
	*/
	ASCab dataCab;
	/** A flag that indicates whether this data comes from a trusted source. */
	PSSigTrust sigTrust;			
} PSImportDataParamsRec, *PSImportDataParams;

/** The format of data to be exported using PSExportDataProc() or
	PSExportDataExchange().
	@see PSExportDataProc
	@see PSExportDataExchange
*/
typedef enum { 
	/** None. No export operation is performed. */
	kPSExportDataNone=0,			
	/** Export certificates for self.
		This operation is performed only if the
		PROP_PSENG_ExportContact property is
		set, indicating that the handler supports this
		format. 
	*/
	kPSExportDataMyContact,			
	/* Export a list of entries from an address book.
		This operation is performed only if the
		PROP_PSENG_ExportContact property is
		set, indicating that the handler supports this
		format. 
	*/
	kPSExportDataContacts,			
	/** Export a list of directory settings.
		This operation is performed only if the
		PROP_PSENG_ExportDirSettings
		property is set, indicating that the handler
		supports this format.
	*/
	kPSExportDataDirSettings,		
	/** The enum size. */
	kPSExportDataEnumSize
} PSExportDataType;

/** File output options for PSExportDataExchangeParams().
	@see PSExportDataProc
	@see PSExportDataExchange
*/
typedef enum { 
	/** None. Prompt for the output file type. This is recommended. */
	kPSExportDestNone=0,			
	/** Save as an unspecified file type, possibly prompting for the file type. */
	kPSExportDestFile,				
	/** Save as a CMS file (.p7c). */
	kPSExportDestCMSFile,			
	/** Save as a Certificate file (.cer). */
	kPSExportDestCertFile,			
	/** Save as an FDF file. */
	kPSExportDestFDFFile,			
	/** Email an FDF file. */
	kPSExportDestEMailFDF,			
	/** Send a single certificate to the URL. */
	kPSExportDestCertURL,			
	/** */
	kPSExportDestEnumSize
} PSExportDestType;

 
/*************************************************************************
 * Engine Public Properties
 * The properties listed here are public and common to all engines.
 * An engine is free to define its own additional properties.
 * Many of these property names are also used by EScript or as ASCab keys, 
 * which is why (char*) is used for the keys.
 ************************************************************************/

/* Common engine ASText properties */
#define PROP_PSENG_Exception			"exception"				/* Exception string if return code is kDSException */
#define	PROP_PSENG_ProfilePath			"loginPath"				/* Used by JavaScript to get path to DigitalID file */
#define	PROP_PSENG_CN					"loginName"				/* Used by JavaScript to get active signing credential */
#define	PROP_PSENG_HandlerUIName		"uiName"				/* Language dependent name */
#define PROP_PSENG_Text_HandlerVersion	"version"				/* Engine version as text*/
#define	PROP_PSENG_Appearances			"appearances"
#define PROP_PSENG_Directories			"directories"			/* list of directories for this pubsec handler */
#define PROP_PSENG_DirectoryHandlers	"directoryHandlers"		/* list of directory handlers for this pubsec handler */
#define PROP_PSENG_BuildDate			"buildDate"				/* Build date/time for handler */

/* Common engine ASBool properties */
#define	PROP_PSENG_PDSignVisible		"signVisible"			/* If true then can create signatures with visible on-page appearances */
#define	PROP_PSENG_PDSignInvisible		"signInvisible"			/* If true then can create signatures that do not have a signature appearance */
#define	PROP_PSENG_PDSignAuthor			"signAuthor"			/* If true then can create author sigs, that include MDP */
#define	PROP_PSENG_PDSignValidate		"signValidate"			/* If true then can validate signatures */
#define	PROP_PSENG_CosSign				"signFDF"				/* If true then can sign CosDocs */
#define	PROP_PSENG_CosValidate			"validateFDF"			/* If true then can validate CosDoc signatures */
#define	PROP_PSENG_PDEncrypt			"docEncrypt"
#define	PROP_PSENG_PDDecrypt			"docDecrypt"
#define	PROP_PSENG_IsLoggedOn			"isLoggedIn"		/* Do we have a persitent contect? Does not indicate if authentication required. */
#define PROP_PSENG_PDSignCustomAP		"signCustomAP"		/* set to <code>true</code> if you want to do your own signature appearances */
#define	PROP_PSENG_UserInterface		"userInterface"		/* Can operate with UI (not just an escript engine) */
#define PROP_PSENG_ImportContact		"importContact"		/* Must be true if PSImportDataProc and kPSImportDataSigDict or kPSImportDataFDFImportArray are supported */
#define PROP_PSENG_ImportDirSettings	"importDirSettings"	/* Must be true if PSImportDataProc and kPSImportDataFDFDirArray are supported */
#define PROP_PSENG_ExportContact		"exportContact"		/* Must be true if PSExportDataProc and kPSExportDataMyContact are supported */
#define PROP_PSENG_ExportDirSettings	"exportDirSettings"	/* Must be true if PSExportDataProc and kPSExportDataDirSettings are supported */

/** Return <code>true</code> if the handler is capable of signing and verifying PKCS#1 signatures.
    The handler is then required to support <code>adbe.x509.rsa_sha1</code> signatures. */
#define PROP_PSENG_SignFormatPKCS1					"signPKCS1"
/** Return <code>true</code> if the handler is capable of signing and verifying PKCS#7 signatures.
    The handler is then required to support both <code>adbe.pkcs7.sha1</code> and <code>adbe.pkcs7.detached</code> formats. */
#define PROP_PSENG_SignFormatPKCS7					"signPKCS7"
/** Return <code>true</code> if the handler is capable of signing and verifying ETSI.PAdES signatures.
    The handler is then required to support <code>ETSI.CAdES.detached</code> signatures. */
#define PROP_PSENG_SignFormatETSIPAdES				"signETSIPAdES"
/** Return <code>true</code> if the handler is capable of signing and verifying ETSI.RFC3161 (Timestamp) signatures.
    The handler is then required to support <code>ETSI.RFC3161</code> signatures. */
#define PROP_PSENG_SignFormatETSIRFC3161			"signETSIRFC3161"
/** Return <code>true</code> if the handler must do its own digesting when signing and verifying <code>adbe.x509.rsa_sha1</code> 
    signatures (the handler cannot directly sign the digest). */
#define PROP_PSENG_SignFormatPKCS1Digest			"signPKCS1Digest"
/** Return <code>true</code> if the handler must do its own digesting when signing and verifying <code>adbe.pkcs7.detached</code> 
    signatures (the handler cannot directly sign the digest). */
#define PROP_PSENG_SignFormatPKCS7DetachedDigest	"signPKCS7DetachedDigest"
/** Return <code>true</code> if the handler must do its own digesting when signing and verifying <code>ETSI.CAdES.detached</code> 
    signatures (the handler cannot directly sign the digest). */
#define PROP_PSENG_SignFormatETSIPAdESDigest		"signETSIPAdESDetachedDigest"
/** Return <code>true</code> if the handler must do its own digesting when signing and verifying <code>ETSI.RFC3161</code> 
    timestamp signatures (the handler cannot directly sign the digest). */
#define PROP_PSENG_SignFormatETSIRFC3161Digest		"signETSIRFC3161Digest"

/** Return <code>true</code> if the handler is capable of hashing using SHA256. 
    @note New in Acrobat 8. In previous versions it was always assumed that the handler could
    handle MD5 and SHA1 (the only hashing algorithms supported at that time).  Hence, if the hashing 
    algorithms are MD5 and SHA1, it is assumed that the handlers can handle those, and they are not queried.
    The handler can use the function PSDataBufferDigest(), if they want PubSec to hash the data.  */
#define PROP_PSENG_HashAlgoSHA256					"hashSHA256"
/** Return <code>true</code> if the handler is capable of hashing using SHA224.   */
#define PROP_PSENG_HashAlgoSHA224					"hashSHA224"
/** Return <code>true</code> if the handler is capable of hashing using SHA384.   */
#define PROP_PSENG_HashAlgoSHA384					"hashSHA384"
/** Return <code>true</code> if the handler is capable of hashing using SHA152.   */
#define PROP_PSENG_HashAlgoSHA512					"hashSHA512"
/** Return <code>true</code> if the handler is capable of hashing using RIPEMD160.*/
#define PROP_PSENG_HashAlgoRIPEMD160				"hashRIPEMD160"


/** Return an ASInt32 indicating the number of appearances the handler has.
    This is used for JavaScript. */
#define	PROP_PSENG_ASInt32_AppearanceNum	"appearances"
/** Return an ASInt32 indicating the number of directories the handler has.
    This is used for JavaScript. */
#define	PROP_PSENG_ASInt32_DirectoryNum		"directories"
/** Return the version of this plug-in. The handler should be careful about setting this value
    in relation to the build dictionary that is created. If a handler ever needs to revoke
	signatures that are created with a version of software that has errors, and the PreRelease
	flag in the build dictionary is not set, then the handler will probably need to use the
	value of this number. */
#define	PROP_PSENG_ASInt32_HandlerVersion	"version"

/** The name by which this handler is to be registered with DigSigHFT.
*/
#define	PROP_PSENG_ASAtom_DigSigHandlerName		"DigSigHandlerName"
/** The alias of the handler registered with DigSigHFT
    (primarily used for backward compatibility, where the handler has changed its name over time). 
*/
#define	PROP_PSENG_ASAtom_DigSigHandlerAlias	"DigSigHandlerAlias"

/** The name by which this handler is to be registered with PubSecHFT (usually the same name as DigSig).
*/
#define	PROP_PSENG_ASAtom_PubSecHandlerName		"PubSecHandlerName"
/** The alias of the handler registered with PubSecHFT. 
*/
#define	PROP_PSENG_ASAtom_PubSecHandlerAlias	"PubSecHandlerAlias"

/** The preferred signing format to use, specifing the value of the SubFilter. It is overridden by SeedValue and SigInfo. */
#define PROP_PSENG_ASAtom_DefaultSubFilter		"SubFilter"

/*************************************************************************
 * PSPerformOperation parameters
 * Currently called only from EScript.
 * The PubSec plug-in interprets relevant calls and dispatches
 * then to handlers for the operation to be performed.
 ************************************************************************/

/** The type of operation to be performed by PSPerformOperationProc(). The PubSec
	plug-in interprets relevant calls and dispatches them to handlers for the operation to be
	performed. 
	@see PSPerformOperationProc
*/
typedef enum {
	/** None */
	kPSOpPerformNone=0,
	/** Silent scripted operation. Access/select the file/store containing digital IDs. */
	kPSOpPerformESLogin,			
	/** Silent scripted operation. Deaccess the file/store containing digital IDs. */
	kPSOpPerformESLogout,			
	/** Silent scripted operation. Create a new self-sign digital ID. */
	kPSOpPerformESNewUser,		
	/** Silent scripted operation. Deprecated. */
	kPSOpPerformESSetValidateMethod,
	/** Silent scripted operation. Set the password timeout policy. */
	kPSOpPerformESPasswordTimeout,	
	/** Brings up a user interface to display a list of
		certificates contained in an ASCab.
		It returns <code>true</code> if it is implemented by the
		handler.
	 */
	kPSOpPerformDisplayCertList,	
	/** Returns a list of certificates in an ASCab. */
	kPSOpPerformGetCerts,	
	/** Returns a list of credential stores. */
	kPSOpPerformGetStores,
	kPSOpPerformEnumSize
} PSPerformOpType;

/*************************************************************************
 * APPreviewRec - parameter to DSAPFileEditNthEntry
 ************************************************************************/

/** Data with which to build a signature preview in the 
	edit dialog box for a signature appearance file entry. 
*/
typedef struct _t_APPreviewRec {
	/** The logo string. */
	const char* logo;
	/** The bounding box for the logo string. */
	ASFixedRect* logoBBox;
	/** The entry name. */
	ASText fName;
	/** The distinguished name. */
	ASText fDN;
	/** The reason for signing. */
	ASText fReason;
	/** The location of the signature. */
	ASText fLocation;
	/** The width that determines the aspect ratio of the preview image. */
	ASFixed fWidth;				
	/** The height that determines the aspect ratio of the preview image. */
	ASFixed fHeight;			
	/** <code>true</code> if this is an author signature, <code>false</code> otherwise. */
	bool fbAuthSig;				
} APPreviewRec, *APPreview;

/*************************************************************************
 * Parameters to EScript and cabs
 ************************************************************************/

/* EScript ESRDN object public properties */
#define	PROP_ESRDN_CN				"cn"
#define	PROP_ESRDN_O				"o"
#define	PROP_ESRDN_OU				"ou"
#define	PROP_ESRDN_C				"c"
#define PROP_ESRDN_E				"e"
// The following are new for Acrobat 8
#define PROP_ESRDN_NAME				"name"  
#define PROP_ESRDN_SURNAME			"sn"
#define PROP_ESRDN_GIVENNAME    	"givenName"  
#define PROP_ESRDN_INITIALS			"initials"
#define PROP_ESRDN_GENQUALIFIER		"generationQualifier"  
#define PROP_ESRDN_DNQUALIFIER		"dnQualifier"
#define PROP_ESRDN_LOCALITY			"l"  
#define PROP_ESRDN_STATE			"st"
#define PROP_ESRDN_TITLE			"title"  
#define PROP_ESRDN_SERIALNUM		"serialNumber"
#define PROP_ESRDN_DC				"dc"  
#define PROP_ESRDN_PSEUDONYM		"pseudonym"
#define PROP_ESRDN_BIZCATEGORY		"businessCategory"  
#define PROP_ESRDN_STREET			"street"
#define PROP_ESRDN_POSTALCODE		"postalCode"  
#define PROP_ESRDN_POSTALADDR		"postalAddress"
#define PROP_ESRDN_DOB				"dateOfBirth"  
#define PROP_ESRDN_POB	    		"placeOfBirth"
#define PROP_ESRDN_GENDER			"gender"  
#define PROP_ESRDN_CITIZENSHIP		"countryOfCitizenship"
#define PROP_ESRDN_RESIDENCE		"countryOfResidence"  
#define PROP_ESRDN_NAMEATBIRTH		"nameAtBirth"


/* EScript ESCPS object public properties */
#define	PROP_ESCPS_OID				"oid"
#define	PROP_ESCPS_URL				"url"
#define	PROP_ESCPS_NOTICE			"notice"
   
/* EScript Security object public method parameters (also passed to PSPerformOperation) */
#define PARAM_ESSecurity_Password			"cPassword"		/* This is a string */
#define PARAM_ESSecurity_DIPath				"cDIPath"		/* This is an ASPathName */
#define PARAM_ESSecurity_PFX                "cPFX"          /* Instead of a Path to a PFX, the entire PFX can be put here */
#define PARAM_ESSecurity_RDN				"oRDN"			/* If true then acquiring with new user fields */
#define PARAM_ESSecurity_CPS				"oCPS"			/* Generic object containing CPS info to be 
                                                               added to the Self signed certificate */
#define PARAM_ESSecurity_Timeout			"iTimeout"		/* An ASInt32 */
#define PARAM_ESSecurity_DigestSHA1			"cDigestSHA1"	/* SHA-1 digest of certificate */
#define PARAM_ESSecurity_Message			"cMsg"			/* Message to display in login dialog */
#define PARAM_ESSecurity_Method				"cMethod"		/* An ASInt32 */
#define PARAM_ESSecurity_Params				"oParams"		/* */
#define PARAM_ESSecurity_Select				"oSelect"		/* Select Digital ID */
#define PARAM_ESSecurity_Type				"cType"			/* Type of data, operation, etc */
#define PARAM_ESSecurity_Cert				"oCert"			/* Certificate Object */
#define PARAM_ESSecurity_Object				"oObject"		/* Object of unspecified type */
#define PARAM_ESSecurity_EndUserSignCert	"oEndUserSignCert"	/* Cert that is selected to use when signing */
#define PARAM_ESSecurity_EndUserCryptCert	"oEndUserCryptCert"	/* Cert that is selected to use when encrypting */
#define PARAM_ESSecurity_Certs				"certs"			/* Returned array of certificates */
#define PARAM_ESSecurity_Stores				"stores"		/* Stores where the above credentials are stored */
#define PARAM_ESSecurity_URI				"cURI"			/* String - URI for APS connection */
#define PARAM_ESSecurity_UserId				"cUserId"		/* String - User id for APS authentication */
#define PARAM_ESSecurity_Domain				"cDomain"		/* String - Domain name for APS authentication */

/* EScript Security object public method parameters specific to importSettings method */
#define PARAM_ESSecurity_Document			"oDocObj"		/* Object containing a PDDoc document */
#define PARAM_ESSecurity_Filename			"cFilename"		/* UCString - the filename for an attached embedded file */
#define PARAM_ESSecurity_SimplifiedUI		"bSimplifiedUI"	/* Boolean - if true and applicable use a simplified UI */

#define PROP_Op_Certificates				"certificates"		/* r */
#define PROP_Op_ContactInfo					"contactInfo"
   
/** Signature properties that are written to the signature dictionary. 
	These property names exactly match the corresponding signature dictionary names.
	These are used in <code>PSSigSigPropParamsRec.outNewSigPropCab</code>.
	Handlers can specify custom signature properties. These should be named using 
	the format <code>ACME_Prop_MyProperty</code>, where <code>ACME</code> is the abbreviated company name. */
#define PROP_SigProp_Name				"Name"
#define PROP_SigProp_Reason				"Reason"
#define PROP_SigProp_Location			"Location"
#define PROP_SigProp_ContactInfo		"ContactInfo"
#define PROP_SigProp_Date				"M"
#define PROP_SigProp_Filter				"Filter"		/* Handler can override value put in /Filter */
#define PROP_SigProp_AuthType			"Prop_AuthType"
#define PROP_SigProp_AuthTime			"Prop_AuthTime"
#define PROP_SigProp_MDP			    "Prop_MDP"

#define PROP_SigProp_PDFMinorVersion	"PDFMinorVersion"		/* PDF minor version */

/** Signature properties that are written to the build dictionary. 
	These property names exactly match the corresponding build dictionary names.
	These are used in PSSigSigPropParamsRec.outNewSigBuildCab
	Handlers can specify custom sig properties. These should be named using 
	format <code>ACME_MyProperty</code>, where <code>ACME</code> is the abbreviated company name. */
/** Signature dictionary formatting version number, for specific/private use by the handler. 
	The handler may use this to determine whether the handler supports verification of this signature.
	Set it to <code>0</code> if it is unused. */ 
#define PROP_SigBuild_V					"V"
/** Indicates if the signature was created by pre-release software. Its default value is <code>false</code>. */
#define PROP_SigBuild_PreRelease		"PreRelease"

/* Common engine APCab properties */
#define PROP_APCab_Type					"type"
#define PROP_APCab_Name					"text"
#define PROP_APCab_Index				"index"
   
/* Value (char*) of PROP_APCab_Type when using DSAPIcon APHandler */
#define VALUE_APCab_TypeDSAPIcon		"apIcon"
   
/* Preference settings? */
#define PROP_Reasons			"reasons"			// this is an array when in a cab
#define PROP_More				"more"
#define PROP_Left				"left"
#define PROP_Top				"top"
#define PROP_APIndex			"apIndex"

/************************************************************************************
 * Directory Handler - Declarations
 ***********************************************************************************/

/** Directory Service Provider (DSP) Object. As of Acrobat 6.0 this is a
  PubSecEngine object that acts as a DSP. In future releases this may
  become a stand-alone structure. */
typedef void* DirDSP;

 /** A directory information list ASCab contains a vector of nested DirectoryInfo ASCab objects,
	one for every directory contained within the engine. Each directory ASCab contains a user interface
	name as an ASText and a unique ID as an ASAtom.
	@see PSGetDirList
 */
typedef ASCab DirectoryList;

/** A directory handler information ASCab contains a vector of nested ASCab objects, one for every
	directory handler contained within the engine. Each directory handler ASCab contains a user interface
	name and a unique ID (for example, <code>"Adobe.PPKMS.LDAP"</code>). 
	@see PSGetDirHandlerInfo 
*/
typedef ASCab DirHandlerInfo;

/* DirHandlerInfo object properties */
/** (Required) The user interface name for the handler. */
#define PROP_DirHandlerInfo_Name	"name"		/* ASText, required. UI friendly name for the handler */
/** (Required) A unique identifier for the
	directory handler. The handler is
	rejected if the ASAtom conflicts with
	one already registered.
*/
#define PROP_DirHandlerInfo_ID		 "id"		/* Unique ASAtom identifying the directory handler. Example is Adobe.PPKMS.LDAP. Required */

/**  An ASCab object containing authentication details such as the user name and password. It
	could be used to override the default authentication entries, or to avoid repeated
	authentications in case the context could be cached. The actual contents depend on the
	directory handlers. The currently supported directory handlers (AAB and LDAP) do not
	support this feature.
	@see PSOpenConnection
*/
typedef ASCab DirAuthenticationContext;


/*************************************************************************
 * PubSecHFT Procedure Declarations
 ************************************************************************/

/** Create a new public key security engine for this handler.
   This engine would not be associated with any user interface. 
   @see PSDestroyEngineProc
*/ 
typedef ACCBPROTO1 PubSecEngine (ACCBPROTO2 *PSNewEngineProc) ( );

/** Destroys a public key security engine for this handler, freeing the memory.
	@param engine The engine to be destroyed.
	@see PSNewEngineProc
*/ 
typedef ACCBPROTO1 void (ACCBPROTO2 *PSDestroyEngineProc) 
	( PubSecEngine engine );

/** Gets an ASBool property of an engine. For a list of public properties of a
	PubSecEngine, see PubSecHFT.h.
	@param engine The engine for which the property value is obtained.
	@param szPropertyName The name of the ASBool property whose value is obtained.
	@param defaultValue The value to return if the property value is not set.
	@return The boolean property value, or the specified default value if the property value is not set.
	@see PSGetAtomPropertyProc
	@see PSGetInt32PropertyProc
	@see PSGetTextPropertyProc
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *PSGetBoolPropertyProc)
	( PubSecEngine engine, const char* szPropertyName, const ASBool defaultValue );

/** Gets an ASAtom property of an engine. For a list of public properties of a
	PubSecEngine, see PubSecHFT.h.
	@param engine The engine for which the property value is obtained.
	@param szPropertyName The name of the ASAtom property whose value is obtained.
	@return The ASAtom property value, or ASAtomNull if the property value is not set.
	@see PSGetBoolPropertyProc
	@see PSGetInt32PropertyProc
	@see PSGetTextPropertyProc
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *PSGetAtomPropertyProc)
	( PubSecEngine engine, const char* szPropertyName );

/** Gets an ASInt32 property of an engine. For a list of public properties of a
	PubSecEngine, see PubSecHFT.h.
	@param engine The engine for which the property value is obtained.
	@param szPropertyName The name of the ASInt32 property whose value is obtained.
	@param defaultValue The value to return if the property value is not set.
	@return The ASInt32 property value, or the specified default value if the property value is not set.
	@see PSGetAtomPropertyProc
	@see PSGetBoolPropertyProc
	@see PSGetTextPropertyProc
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *PSGetInt32PropertyProc)
	( PubSecEngine engine, const char* szPropertyName, const ASInt32 defaultValue );

/** Gets an ASText property of an engine. For a list of public properties of a
	PubSecEngine, see PubSecHFT.h.
	
	<p>For the PROP_PSENG_Exception property, <code>index</code> is a DSRetCode value. If a handler
	receives a a call to get PROP_PSENG_Exception, it must reset its exception status so
	that subsequent calls to get an exception string return <code>NULL</code>.
	<code>NULL</code> return values are legal for all properties.</p>

	@param engine The engine for which the property value is obtained.
	@param szPropertyName The name of the ASText property whose value is obtained.
	@param index The index of the string to obtain if the property contains a list of values. If it does not, <code>index</code> is ignored.
	@return The ASText property value, or <code>NULL</code> if the property value is not set.
	@see PSGetAtomPropertyProc
	@see PSGetBoolPropertyProc
	@see PSGetInt32PropertyProc
*/
typedef ACCBPROTO1 ASText (ACCBPROTO2 *PSGetTextPropertyProc)
	( PubSecEngine engine, const char* szPropertyName, const ASInt32 index );


/** Called to acquire resources that will be needed to begin a PubSec session. For example, it
	might need to log on before performing a desired operation. If resources are already
	available, the handler may not need to do anything.
	When the function completes successfully, PubSec calls PSSessionReleaseProc() with
	the same operation type. Multiple calls can be made to acquire the same or different
	operation types, before a previously acquired resource is released. Handlers should keep a
	reference count if required for a particular resource.
	
	<p>Despite the name, this function does not acquire a session; it just acquires the resources that will be
	needed by the session. For example, to begin a signing session, PubSec calls
	PSSessionAcquire() with kPSOpTypePDDocSign. The PubSec handler should select
	the resources and credentials that are to be used for signing. If the call is successful,
	PubSec will proceed with the PSSigGetSigPropertiesProc() and PSSigGetSigValueProc() calls.</p>

	@param engine The engine for which the information is obtained.
	@param pdDoc The PDF document for which the session is acquired.
	@param opType The operation that is the reason for acquiring the session.
	@param opText A human-readable version of the reason for acquiring the session. If it is
	not supplied, <code>opType</code> is used to build text.
	@param cabParams An ASCab object containing information about the acquisition,
	owned by PubSec. It is currently not used, and is passed as <code>NULL</code>.
	@param bUIAllowed When it is <code>true</code>, the call can invoke the user-interface dialogs if needed.
	@return A positive value on success.
	@see PSSessionReadyProc
	@see PSSessionReleaseProc
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSessionAcquireProc)
	( PubSecEngine engine, PDDoc pdDoc, PSSessionOpType opType, ASText opText, ASCab cabParams, ASBool bUIAllowed );

/** Releases any resources that were required for the specified operation, such as file handles.
	It is up to a handler to decide what resources to release. A handler can, for example, leave a
	user logged on, even after a session is released.
	This call can fail. For example, you might want the call to fail if the operation is
	kPSOpTypeEScriptLogin and encrypted documents are open.
	@param engine The engine for which the session was acquired.
	@param opType The operation for which the session was needed.
	@return kDSTrue if the session is successfully released, kDSFalse otherwise.
	@see PSSessionAcquireProc
	@see PSSessionReadyProc
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSessionReleaseProc)
	( PubSecEngine engine, PSSessionOpType opType );

/** Returns kDSTrue if the resources and information needed to perform the specified
	operation have been acquired.
	@param engine The engine for which the information is obtained.
	@param opType The operation for which the session is needed.
	@return kDSTrue if the session is ready, kDSFalse otherwise.
	@see PSSessionAcquireProc
	@see PSSessionReleaseProc
 */
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSessionReadyProc)
	( PubSecEngine engine, PSSessionOpType opType );

/** Performs the specified operation using parameters contained in cab. This interface is used
	by EScript.
	@param engine The engine for which the operation is performed.
	@param type The type of operation to perform.
	@param cab An ASCab containing parameters for the requested operation, or <code>NULL</code> to test whether the operation is supported.
	@param bUI When it is <code>true</code>, the call can invoke the user interface dialogs if necessary.
	@return If cab is <code>NULL</code>, returns kDSTrue if the operation is supported, kDSFalse if it is not.
	If cab contains data, it returns kDSOk if the operation is successful, an exception code if it is not.
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSPerformOperationProc)
	( PubSecEngine engine, PSPerformOpType type, const ASCab cab, ASBool bUI );


/** Called when creating a new signature. For PDDoc signatures, this call replaces SigNew()
and SigCommit() calls. It returns the values that PubSec writes into the signature dictionary
in the parameters structure.
Before making this call, the handler should use PSSessionAcquireProc() to choose the
credential to be used for signing.
The handler can use the user interface during this call to allow authentication and to bring up the
signing dialog.
	@param engine The engine for which signature properties are retrieved.
	@param params A signature properties parameters structure.
	@return kDSOk if successful, otherwise an exception code is returned.
	@see PSGetLogoProc
	@see PSSessionAcquireProc
	@see PSSigValGetAPLabelProc
	@see PSSigGetSigValueProc
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigGetSigPropertiesProc)
	( PubSecEngine engine, PSSigSigPropParams params );

/**
	Called to authenticate the signer. The caller can determine 
	whether authentication is required by calling PSGetBoolPropertyProc() 
	with the property PROP_PSENG_IsAuthenticated. 

	<p>This procedure is called only if specified by the PSSigSigPropParams 
	passed to PSSigGetSigPropertiesProc(). If your handler does 
	not need this call, it should be defined to always return 
	kDSTrue. </p>
	@param engine The engine for which signature authentication 
	is performed. 
	@param pdDoc A PDF document for window parenting. It is <code>NULL</code> 
	if there is no PDDoc. 
	@param inESParams (Optional) An ASCab containing authentication 
	parameters. If it is not supplied or if authentication fails, 
	and if <code>bInUIAllowed</code> is <code>true</code>, it brings up the authentication 
	user interface to obtain parameters. 
	@param bInUIAllowed When it is <code>true</code>, the call can invoke the 
	authentication user interface. 
	@return kDSTrue if authentication succeeds, kDSFalse if authentication 
	fails. 
	@see PSGetBoolPropertyProc 
	@see PSSigGetSigValueProc 
	@see PSSigValidateProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigAuthenticateProc)
	( PubSecEngine engine, const PDDoc pdDoc, ASCab inESParams, ASBool bInUIAllowed );

/**
	Called to sign the digest and return the signature value. 
	The memory for the signature value becomes the property 
	of the caller. 

	<p>When it is called for a PKCS #7 signature, there is a <i>size-only</i> 
	option: if the value of <code>pOutSigValueData</code> in the <code>inOutParams</code> 
	structure is <code>NULL</code>, it returns the expected size of the signature 
	value. </p>

	<p>For most values of <code>digestMethod</code> in the <code>inOutParams</code> structure, 
	the digest is passed into the handler, and the handler needs 
	to sign it. However if a handler specifies that it must 
	do its own digest (for example, for the legacy EntrustFile 
	toolkit) then a <code>NULL</code> digest is passed in. The handler can 
	specify this using PROP_PSENG_SignFormatPKCS7Digest. If 
	this property is <code>true</code>, the digest is not passed 
	to the handler. </p>

	<p>This procedure should not show any user interface and should not 
	allow a user to cancel the signing operation. </p>

	@param engine The engine for which a signature value is 
	created. 
	@param inOutParams (Modified by the method) A structure containing 
	signature-value parameters and return values.
	@return kDSOk if successful, otherwise an exception code is returned. 
	@see PSSigAuthenticateProc 
	@see PSSigGetSigPropertiesProc 
	@see PSSigValidateProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigGetSigValueProc)
	( PubSecEngine engine, PSSigGetSigValueParams inOutParams );

/**
	Called to determine whether the handler can validate a signature. 
	
	@param engine The engine for which the signature is validated. 
	
	@param params A parameters structure containing information 
	about the signature to be validated.
	@return A signature-validation support value. 
	@see PSSigAuthenticateProc 
	@see PSSigGetSigValueProc 
	@see PSSigValidateDialogProc 
	@see PSSigValidateProc 
*/
typedef ACCBPROTO1 PSSigValSupport (ACCBPROTO2 *PSSigValidateSupportedProc)
	( PubSecEngine engine, PSSigValidateSupportParams params );

/**
	Called to validate a signature. 
	@param engine The engine for which the signature is validated. 
	
	@param params (Modified by the method) A structure containing signature validation 
	parameters and return values. The result of validation 
	is stored in the <code>sigValCab</code> field.
	@return kDSOk if successful, otherwise an exception code is returned. 
	@see PSSigAuthenticateProc 
	@see PSSigGetSigValueProc 
	@see PSSigValidateDialogProc 
	@see PSSigValidateSupportedProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigValidateProc)
	( PubSecEngine engine, PSSigValidateParams params );

/**
	Called to show a dialog box that shows validation status after 
	the signature is validated. 

	<p>If this procedure is <code>NULL</code> (which is recommended), PubSec 
	opens its own validation dialog. </p>

	@param engine The engine for which the validation status 
	is shown. 
	@param valParams A validation dialog box parameters structure. 
	The validation state resulting from the previous validation 
	operation is passed in the <code>sigValCab</code> field. The handler 
	can update the <code>dsPropType</code> field if the properties dialog box 
	should be opened next.
	@return kDSOk if successful, otherwise an exception code is returned. 
	@see PSSigAuthenticateProc 
	@see PSSigGetSigValueProc 
	@see PSSigPropDialogProc 
	@see PSSigValidateProc 
	@see PSSigValidateSupportedProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigValidateDialogProc)
	( PubSecEngine engine, PSSigValidateDialogParams valParams );

/**
	Called to display a dialog box that shows signature properties. 
	
	<p>If this procedure is <code>NULL</code> (which is recommended), PubSec 
	opens its own properties dialog. The default properties 
	dialog box includes buttons that allow the user to import and 
	to display certificates: </p>

	<ul>
	<li>The import button calls PSImportDataProc(). </li>
	<li>If the handler implements the kPSOpPerformDisplayCertList 
	operation (see PSPerformOperationProc()) the show-certificate 
	button can open the handler-provided display dialog. Otherwise, 
	the button opens the default certificate-display dialog. </li>
	</ul>
	
	@param engine The engine for which the validation status 
	is shown. 
	@param valParams (Modified by the method) A structure containing properties-dialog box 
	parameters and return values. The handler can 
	set the <code>dsPropType</code> to kSDPropViewVersion to request rollback 
	to this signature when the dialog box is closed.
	@return kDSOk if successful, otherwise an exception code is returned. 
	@see PSSigValidateDialogProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigPropDialogProc)
	( PubSecEngine engine, PSSigValidateDialogParams valParams );

/**
	Called to get the text result of validation. For most values 
	of <code>textType</code>, the handler should return <code>NULL</code>, causing PubSec 
	to use the default text strings (<code>"Valid"</code>, <code>"Invalid"</code>, or 
	<code>"Unknown"</code>, depending on the validity state). Handlers will 
	normally need to provide their own ID validity strings. 
	
	@param valCab The ASCab containing the validation result. 
	(See <code>sigValCab</code> in PSSigValidateParams.) 
	@param textType The type of result text to obtain for 
	a specific context. 
	@param index If the type is kDSSigValTextAP, it is the corresponding 
	index value. Otherwise it is ignored.
	@return The text result of validation as a new ASText object. 
	@see PSSigValidateProc 
	@see PSSigValidateDialogProc 
*/
typedef ACCBPROTO1 ASText (ACCBPROTO2 *PSSigValGetTextProc)
	( ASCab valCab, const DSSigValText textType, const ASInt32 index );

/**
	Creates the signature appearance that is put into the /AP 
	dictionary /N entry. 

	<p>It is recommended that you set this procedure to <code>NULL</code>, 
	which allows PubSec to use the default APHandler to generate 
	the XObj for the appearance. </p>

	@param engine The engine for which an appearance is created. 
	
	@param pOutXObj (Filled by the method) The XObject to 
	use for the signature appearance. 
	@param docParams A validation parameters structure containing 
	information that is needed to create the signature appearance, 
	such as the PDDoc and annotation. 
	@param sigType The signature type.
	@return kDSOk if successful, otherwise an exception code is returned. 
	@see PSGetLogoProc 
	@see PSSigValGetAPLabelProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSigCreateAPNXObjProc)
	( PubSecEngine engine, CosObj *pOutXObj, PSSigPDDocParams docParams, PSAPSigType sigType );

/**
	Gets custom artwork from the handler, to be used as a label 
	for a particular validity state. The artwork for standard 
	labels does not need to be specifically retrieved. If you 
	are not using dynamic signature appearances or not using 
	custom artwork, the handler need only handle the null label 
	case. 
	@param label A validity state, as returned by PSSigValGetAPLabelProc(), 
	for which to use this logo. If it is ASAtomNull, the logo is used 
	as an invariable watermark of the signature appearance. 
	
	@param pcLogo (Filled by the method) A string of the uncompressed 
	graphics stream for the logo artwork. 
	@param pRect (Filled by the method) The precise bounding 
	box that the artwork occupies.
	@see PSSigCreateAPNXObjProc 
	@see PSSigValGetAPLabelProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *PSGetLogoProc)
	( ASAtom label, const char* *pcLogo, const ASFixedRect* *pRect );

/**
	Called to get a name to use for a particular layer of signature 
	appearance. This is used when the signature appearance uses 
	the n1 and n3 layers for dynamic signature appearances. 
	Beginning in Acrobat 6.0, Acrobat is discouraging the use 
	of dynamic signature appearances and is instead showing 
	the signature validity as an icon that is rendered at run 
	time. 

	<p>Provide this procedure for handlers that need to be backward 
	compatible with earlier implementations that use custom 
	artwork. The procedure can be set to <code>NULL</code> when you are not using 
	dynamic signature appearances. </p>

	<p>If the value DSAPValid, DSAPDoubleValid, or DSAPInvalid 
	is returned, Acrobat uses standard labels. Otherwise Acrobat 
	calls PSGetLogoProc() to return logo artwork to use for the 
	XObject. A return value of ASAtomNull causes Acrobat to 
	use a blank XObject for the specified layer. </p>

	@param valCab An ASCab containing the signature validation 
	result for which the label is obtained. 
	@param layerNum The layer for which a label is obtained.
	@return The label of a signature appearance layer as an ASAtom. 
	
	@see PSGetLogoProc 
	@see PSSigCreateAPNXObjProc 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *PSSigValGetAPLabelProc)
	( ASCab valCab, const ASInt32 layerNum );

/**
	This function sends data of a particular type to a handler 
	to import into its own data store. This is call is executed 
	in response to data received (for example, through an FDF 
	file or through the signature dictionary). 

	<p>Acrobat calls PSGetBoolPropertyProc() to see if the relevant 
	data type is supported in the handler implementation. See 
	PSImportDataType. </p>

	@param engine The engine for which the data is exported. 
	
	@param params A structure that contains the data to be 
	imported. 
	@param bInUIAllowed When it is <code>true</code>, the call can invoke the 
	user interface dialogs if needed.
	@return A positive value on success. 
	@see PSExportDataProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSImportDataProc)
	( PubSecEngine engine, PSImportDataParams params, ASBool bInUIAllowed );

/**
	This function gets data of the specified type from a handler, 
	to be exported to an FDF or CMS file and possibly sent as 
	an email attachment. The function is called when exporting 
	to FDF, for example, in response to an FDF Data Exchange 
	certificate request. 

	<p>Acrobat calls PSGetBoolPropertyProc() to see if the relevant 
	data type is supported in the handler implementation. See 
	PSExportDataType. </p>

	@param engine The engine for which the data is exported. 
	
	@param dataType The type of data to be exported. 
	@param outCab The ASCab containing the data to be exported. 
	
	@param bInUIAllowed When it is <code>true</code>, the call can invoke the 
	user interface to export the data. 
	@return A positive value on success. 
	@see PSImportDataProc 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSExportDataProc)
	( PubSecEngine engine, PSExportDataType dataType, ASCab outCab, ASBool bInUIAllowed );

/**
	This procedure is required. It is called to open the provided 
	PKCS#7 cryptographic message service (CMS) enveloped data 
	object and return the data contained in it. 
	@param engine The engine for which the data is exported. 
	@param inCMSEnvelope The buffer that contains the enveloped data object.
	@param inCMSEnvelopeSize The size of the buffer pointed to by <code>inCMSEnvelope</code>
	@param pOutData The buffer containing the decrypted data, if successful.
	@param pOutDataSize The size of the buffer pointed to by <code>pOutData</code>.
	@param bInUIAllowed When it is <code>true</code>, the call can invoke the 
	user interface for anything required to open the envelope. For instance, 
	a login may be needed to access the user's private key.
	@return kDSTrue if the envelope was opened, kDSFalse if the envelope 
	could not be opened, or an error code in case of error. 
	
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSOpenCMSEnvelopeProc)
	( PubSecEngine engine, 
	  ASUns8* inCMSEnvelope, ASUns32 inCMSEnvelopeSize, 
	  ASUns8** pOutData, ASUns32* pOutDataSize, 
	  ASBool bInUIAllowed );

/** Open the provided PKCS#7 (CMS) Enveloped Data object and return the
   data contained in it.
   @param engine The engine for which the data is exported.
   @param params Contains the envelope data and fields for the handler to 
     return opened envelope data contents, and optionally, the session key
     and opening certificate.
   @param bInUIAllowed Indicates whether the handler can pop up any user interface to open the envelope. For
     instance, a login may be required to access the user's private key.
   @return kDSTrue if the envelope was opened, kDSFalse if the envelope could not be opened.
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSOpenCMSEnvelopeExProc)
	( PubSecEngine engine, 
	  PSOpenCMSEnvelopeParams params, 
	  ASBool bInUIAllowed );

/**
	Gets information about directory handlers in an engine that 
	is acting as a directory service provider. 
	@param engine The engine for which the information is 
	obtained. 
	@param outCertList (Filled by the method) An ASCab 
	containing an array of ASCab directory handlers.
	@param bInUIAllowed When it is <code>true</code>, the call can invoke the 
	user interface to display the directory handlers.
	@return A positive value on success. 
	@see PSGetDirInfo 
	@see PSGetDirList 
	@see PSSetDirInfo 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSGetImplicitRecipientsProc)
	( PubSecEngine engine, ASCab outCertList, ASBool bInUIAllowed );


/**
	Gets information about directory handlers in an engine that 
	is acting as a directory service provider. 
	@param engine The engine for which the information is 
	obtained. 
	@param outDirHandlerInfo (Filled by the method) A structure 
	containing an array of ASCab directory handlers.
	@return A positive value on success. 
	@see PSGetDirInfo 
	@see PSGetDirList 
	@see PSOpenConnection 
	@see PSSetDirInfo 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSGetDirHandlerInfo) 
	( PubSecEngine engine, DirHandlerInfo outDirHandlerInfo );

/**
	Gets a list of directories in an engine that is acting as 
	a directory service provider. 
	@param engine The engine for which the information is 
	obtained. 
	@param outDirList (Filled by the method) An ASCab containing 
	an array of DirectoryInfo ASCab objects.
	@return A positive value on success. 
	@see PSGetDirHandlerInfo 
	@see PSGetDirInfo 
	@see PSOpenConnection 
	@see PSSetDirInfo 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSGetDirList) 
	( PubSecEngine engine, DirectoryList outDirList );

/**
	Gets information about directories in an engine that is 
	acting as a directory service provider. 
	@param engine The engine for which the information is 
	obtained. 
	@param inDirID The unique identifier associated with the 
	directory. See DirHandlerInfo. 
	@param outDirInfo (Filled by the method) An ASCab containing 
	information about the directory.
	@return A positive value on success. 
	@see PSGetDirHandlerInfo 
	@see PSGetDirList 
	@see PSOpenConnection 
	@see PSSetDirInfo 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSGetDirInfo) 
	( PubSecEngine engine, ASAtom inDirID, DirectoryInfo outDirInfo );

/**
	Sets information about a directory in an engine that is 
	acting as a directory service provider. 
	@param engine The engine for which the information is 
	obtained. 
	@param inDirInfo An ASCab containing information about 
	the directory:
	<ul>
	<li>If the PROP_DirectoryInfo_ID value matches 
	one of the existing directories, that directory's information 
	is overwritten.</li>
	<li>If it does not match any existing directory, 
	a new directory is created.</li>
	</ul>
	@return kDSOk if successful, otherwise an exception code is returned. 
	@see PSGetDirHandlerInfo 
	@see PSGetDirInfo 
	@see PSGetDirList 
	@see PSOpenConnection 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSSetDirInfo) 
	( PubSecEngine engine, DirectoryInfo inDirInfo );

/**
	Opens a connection to a specified directory to use for authentication. 
	
	@param engine The engine for which the connection is opened. 
	
	@param inDirID The identifier for the directory to which 
	the connection is opened. 
	@param inAuthCtx Not currently supported. Pass as <code>NULL</code>. 
	
	@param inUI Determines whether the authentication user interface should be shown. 
	
	@param pOutConnection (Filled by the method) A pointer 
	to the new connection object.
	@return kDSTrue if the connection is opened, kDSFalse if it is not. 
	@see PSGetDirHandlerInfo 
	@see PSGetDirInfo 
	@see PSGetDirList 
	@see PSSetDirInfo 
*/
typedef ACCBPROTO1 DSRetCode (ACCBPROTO2 *PSOpenConnection) 
	( PubSecEngine engine, ASAtom inDirID, DirAuthenticationContext inAuthCtx, ASBool inUI, 
	  DirConnection* pOutConnection );

/** Ask the handler to report a summary on a signature that has just been signed by this handler. 	*/
typedef ACCBPROTO1 void (ACCBPROTO2 *PSSigSignReportProc) 
	( PubSecEngine engine, PSSigSignReportParams);


/** PubSecHandlerRec Definition. 
	See PSRegisterHandler for registration of PubSecHandlers.
	@see PSRegisterHandler
*/
typedef struct _t_PubSecHandlerRec {
	/** */
	ASSize_t size;
	/** Used internally. */
	_t_PubSecHandlerRec *next;
	/** Used internally. */
	DigSigHandler dsHandler;
	/** Used internally. */
	PDCryptHandler cryptHandler;
	/** Engine to use for user interface-based execution. */
	PubSecEngine engine;

	/* Engine constructor/destructor */
	/** */
	PSNewEngineProc					newEngine;
	/** */
	PSDestroyEngineProc				destroyEngine;

	/* Properties */
	/** */
	PSGetBoolPropertyProc			getBoolProperty;
	/** */
	PSGetAtomPropertyProc			getAtomProperty;
	/** */
	PSGetInt32PropertyProc			getInt32Property;
	/** */
	PSGetTextPropertyProc			getTextProperty;

	/* Engine acquire/release/performOperation */
	/** */
	PSSessionAcquireProc			sessionAcquire;
	/** */
	PSSessionReleaseProc			sessionRelease;
	/** */
	PSSessionReadyProc				sessionReady;
	/** */
	PSPerformOperationProc			performOperation;

	/* Signing methods */
	/** */
	PSSigGetSigPropertiesProc		sigGetSigProperties;
	/** */
	PSSigAuthenticateProc			sigAuthenticate;
	/** */
	PSSigGetSigValueProc			sigGetSigValue;
	
	/* Validation methods */
	/** */
	PSSigValidateSupportedProc		sigValidateSupported;
	/** */
	PSSigValidateProc				sigValidate;
	/** */
	PSSigValidateDialogProc			sigValidateDialog;
	/** */
	PSSigPropDialogProc				sigPropDialog;
	/** */
    PSSigValGetTextProc				sigValGetText;

	/* Signature appearance methods */
	/** */
	PSGetLogoProc					getLogo;
	/** */
    PSSigValGetAPLabelProc			sigValGetAPLabel;
	/** */
	PSSigCreateAPNXObjProc			sigCreateAPNXObj;

	/* Contact Exchange */
	/** */
	PSImportDataProc				importData;
	/** */
	PSExportDataProc				exportData;

	/* Encryption methods */
	/** */
	PSOpenCMSEnvelopeProc			cryptOpenCMSEnvelope;
	/** */
	PSGetImplicitRecipientsProc		cryptGetImplicitRecipients;

	/* Directory Service Provider methods */
	/** */
	PSGetDirHandlerInfo				 dirGetDirHandlerInfo;
	/** */
	PSGetDirList					 dirGetDirList; 
	/** */
	PSGetDirInfo					 dirGetDirInfo;
	/** */
	PSSetDirInfo					 dirSetDirInfo;
	/** */
	PSOpenConnection				 dirOpenConnection;

	/* Additional methods */
	/** */
	PSOpenCMSEnvelopeExProc			cryptOpenCMSEnvelopeEx;

	PSSigSignReportProc				sigSignReport;
} PubSecHandlerRec, *PubSecHandler;

/************************************************************************************
 * PubSecHFT - HFT index table
 ***********************************************************************************/


/* Enumerate the selectors */
#define PIPROC(returnType, name, params, ...)		name##_SEL,
enum
{
	PubSecHFTDUMMYBLANKSELECTOR,
#include "PubSecHFTProcs.h"
	PubSecHFTNUMSELECTORSPlusOne
};
#undef PIPROC
#define PubSecHFT_NUMSELECTORS (PubSecHFTNUMSELECTORSPlusOne - 1)

/* HFTEndEnum - do not alter/remove this line! */

/************************************************************************************
 * PubSecHFT - Declarations of structs used by prototypes
 ***********************************************************************************/

/* Top level entries in PSExportDataExchangeParamsRec.dataCab. */
#define PROP_ExportDataCab_CN					"cn"			/* Text, used to identify originator of FDF */
#define PROP_ExportDataCab_EMail				"EMail"			/* Text, request reply-email-address */
#define PROP_ExportDataCab_URL					"URL"			/* Text, request reply-URL */
#define PROP_ExportDataCab_Filter				"Filter"		/* Text, language independent name of the (pubsec) handler that generated this file */
#define PROP_ExportDataCab_Contacts				"Contacts"		/* A cab array of Contact cabs */
#define PROP_ExportDataCab_DirSettings			"DirSettings"	/* A cab array of DirSetting cabs */

/* Entries in Contact Cab */
#define PROP_ContactCab_CN						"cn"			/* Text, common name */
#define PROP_ContactCab_EMail					"EMail"			/* Text, email address */
#define PROP_ContactCab_O						"o"				/* Text, corporation */
#define PROP_ContactCab_ContactInfo				"ContactInfo"	/* Text, 'contact info', eg phone number, used to verify origin of cert */
#define PROP_ContactCab_CMS						"CMS"			/* Binary CMS object, in lieu of certificates */
#define PROP_ContactCab_Certs					"Certs"			/* A cab array of binary certificates, in lieu of CMS */
#define PROP_ContactCab_Trust					"Trust"			/* A cab array of trust flags associate with this contacts certificates */
#define PROP_ContactCab_Policy					"Policy"		/* A cab array of policy cabs associated with this contacts certificates */
#define PROP_ContactCab_Group					"Group"			/* Text, the name of a group, if this contact belongs to a group */
#define PROP_ContactCab_Contact					"Contact"		/* Text, the name of the contact, if this is an exported contact */

/* Entries in DirSetting Cab */
#define PROP_DirSettingCab_Type					"Type"			/* Text, always 'DirSetting' */
#define PROP_DirSettingCab_Attr					"Attr"			/* Cab containing DirectoryInfo entries as specified in the DirectoryHFT */

/* Entries in certificate's Policy cab */
#define PROP_CertPolicyCab_OID					"PolicyOID"		/* A cab array of Text policy OIDs in dotted notation */
#define PROP_CertPolicyCab_UFName				"PolicyUFName"	/* Text, a human-readable description for the OID */

/** Parameters for importing data from a file into PubSec. */
typedef struct _t_PSImportDataExchangeParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** The handler to use to accept the import data, if it accepts the specified type. */
	PubSecHandler psHandler;			
	/** The engine to use to accept the import data. If it is not supplied, the method uses the default (user interface) engine. */
	PubSecEngine psEngine;				
	/** The type of data to be imported. If data of this type is not found in the FDF, the operation fails. */
	PSExportDataType dataType;			
	/** The file system used for <code>filePath</code>. */
	ASFileSys fileSys;					
	/** The path of the file to be opened for import. */
	ASPathName filePath;				
} PSImportDataExchangeParamsRec, *PSImportDataExchangeParams;

/** Parameters for exporting data from PubSec to a file.
	<p>The <code>PSExportDataExchangeParamsRec.dataCab</code> format is as follows: A
   top level cab will contain lists of PROP_ExportDataCab_Contacts,
   PROP_ExportDataCab_DirSettings or whatever other data is to be
   included.  This top level cab can include entries for an email
   address (used as the return email address) and a common name (<code>cn</code>). It is
   recommended that the <code>cn</code> entry be set to the common name of the
   user; this will be used only in creating the file name for the FDF
   (or PKCS#7) file. If either the <code>cn</code> or email address is not provided,
   they will be fetched from the AVIdentity preference
   settings.</p> 
   
   <p>Contents of the individual list entries are added as
   CosDict objects to the FDF file with almost no filtering. The filtering
   is to add a /Type attribute and to turn /Certs entries into /CMS
   entries (meaning that a contact can contain a Certs entry that is a
   list of certificates). Refer to the FDF Data Exchange specification for
   details on attributes.  Each contact can include a list of certificates
   and an email address. Contacts that contain lists of certificates will
   have these lists turned into a CMS object because the FDF format
   supports only CMS. Contacts can directly provide the CMS object if
   they choose.  Each directory entry contains directory-specific
   information that can be converted to a CosDict before storing in
   the FDF file.  File entries give device-independent paths to files that are to be
   embedded.  PubSecHandler and PubSecEngine are used to specify the
   handler to use to sign the data exchange file (if it is signed at
   all).</p>

   <p>Example cab for exporting <code>MyContact</code>:</p>
		<p><code>dataCab : Cab</code></p>
		<p><code>"Contacts" : Cab</code></p>
			<p><code>"0" : Cab</code></p>
				<p><code>"EMail" : "jsmith@smithcorp.com"</code></p>
				<p><code>"Certs" : Cab</code></p>
					<p><code>"0" : binary end entity cert</code></p>
		<p><code>"cn" : "John Smith"</code></p>
		<p><code>"EMail" : "jsmith@smithcorp.com"</code></p>

   <p>Example cab for exporting directory settings:</p>
		<p><code>dataCab : Cab</code></p>
		<p><code>"DirSettings" : Cab</code></p>
			<p><code>"0" : Cab</code></p>
				<p><code>"Port" : 369</code></p>

	@see PSExportDataExchange 
*/
typedef struct _t_PSExportDataExchangeParamsRec {
	/** The size of the structure. */
	ASSize_t size;
	/** If exporting FDF, it is the handler to use to sign the FDF. If it is not supplied,
		the user is prompted for a handler. 
	*/
	PubSecHandler psHandler;			
	/** If exporting FDF, it is the engine to use to sign the FDF. If it is not supplied,
		the method uses the default (user interface) engine.
	*/
	PubSecEngine psEngine;				
	/** The type of data to be exported. It is one of the following values:

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD>kPSExportDataNone</TD><TD>Not specified.</TD></TR>
		<TR><TD>kPSExportDataMyContact</TD><TD>Export the user's own contact information (certificates for encryption and/or signing).</TD></TR>
		<TR><TD>kPSExportDataContacts</TD><TD>Export a list of contacts from an address book or directory that are to be shared.</TD></TR>
		<TR><TD>kPSExportDataDirSettings</TD><TD>Export a list of directory settings that can be used to help someone else configure his directory.</TD></TR>
		</TABLE>

	*/
	PSExportDataType dataType;			
	/** (Required) Data to export, or an empty ASCab if there is no data to export. The format is defined below. */
	ASCab dataCab;						
	/** The type of data to be requested. If it is supplied, the method adds a
		request to the FDF for this data type and forces the export format to
		be FDF. It has the same possible values as <code>dataType</code>.
	*/
	PSExportDataType requestType;		
	/** The destination type that specifies how data should be delivered.
		It is one of the following values:

		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD>kPSExportDestNone</TD><TD>Not specified, prompt the user (recommended).</TD></TR>
		<TR><TD>kPSExportDestFile</TD><TD>Save as unspecified file type, possibly prompting for the file type.</TD></TR>
		<TR><TD>kPSExportDestCMSFile</TD><TD>Save as CMS file.</TD></TR>
		<TR><TD>kPSExportDestFDFFile</TD><TD>Save as FDF file.</TD></TR>
		<TR><TD>kPSExportDestEMailFDF</TD><TD>Save an email FDF file.</TD></TR>
		<TR><TD>kPSExportDestCertURL</TD><TD>Send single certificate to URL.</TD></TR>
		</TABLE>
	*/
	PSExportDestType destType;			
} PSExportDataExchangeParamsRec, *PSExportDataExchangeParams;

/*
   */

/************************************************************************************
 * PubSecHFT
 ***********************************************************************************/
/* Create the prototypes */
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
	#include "PubSecHFTProcs.h"
#undef PIPROC

#define PSRegisterHandler (*((PSRegisterHandler_SELPROTO)(gPubSecHFT[PSRegisterHandler_SEL])))
#define PSUnregisterHandler (*((PSUnregisterHandler_SELPROTO)(gPubSecHFT[PSUnregisterHandler_SEL])))
#define PSCountEncryptedDocs (*((PSCountEncryptedDocs_SELPROTO)(gPubSecHFT[PSCountEncryptedDocs_SEL])))
#define PSCloseEncryptedDocs (*((PSCloseEncryptedDocs_SELPROTO)(gPubSecHFT[PSCloseEncryptedDocs_SEL])))
#define PSDataBufferEnum (*((PSDataBufferEnum_SELPROTO)(gPubSecHFT[PSDataBufferEnum_SEL])))
#define PSDataBufferDigest (*((PSDataBufferDigest_SELPROTO)(gPubSecHFT[PSDataBufferDigest_SEL])))
#define PSDataBufferReset (*((PSDataBufferReset_SELPROTO)(gPubSecHFT[PSDataBufferReset_SEL])))
#define PSSigValidatePDDocSigField (*((PSSigValidatePDDocSigField_SELPROTO)(gPubSecHFT[PSSigValidatePDDocSigField_SEL])))
#define DSAPFileAcquire (*((DSAPFileAcquire_SELPROTO)(gPubSecHFT[DSAPFileAcquire_SEL])))
#define DSAPFileRelease (*((DSAPFileRelease_SELPROTO)(gPubSecHFT[DSAPFileRelease_SEL])))
#define DSAPFileSave (*((DSAPFileSave_SELPROTO)(gPubSecHFT[DSAPFileSave_SEL])))
#define DSAPFileGetCount (*((DSAPFileGetCount_SELPROTO)(gPubSecHFT[DSAPFileGetCount_SEL])))
#define DSAPFileCanDeleteNthEntry (*((DSAPFileCanDeleteNthEntry_SELPROTO)(gPubSecHFT[DSAPFileCanDeleteNthEntry_SEL])))
#define DSAPFileGetNewNthName (*((DSAPFileGetNewNthName_SELPROTO)(gPubSecHFT[DSAPFileGetNewNthName_SEL])))
#define DSAPFileRemoveNthEntry (*((DSAPFileRemoveNthEntry_SELPROTO)(gPubSecHFT[DSAPFileRemoveNthEntry_SEL])))
#define DSAPFileEditNthEntry (*((DSAPFileEditNthEntry_SELPROTO)(gPubSecHFT[DSAPFileEditNthEntry_SEL])))
#define DSAPFileCopyNthEntry (*((DSAPFileCopyNthEntry_SELPROTO)(gPubSecHFT[DSAPFileCopyNthEntry_SEL])))
#define AABIsCertPresent (*((AABIsCertPresent_SELPROTO)(gPubSecHFT[AABIsCertPresent_SEL])))
#define AABGetCertTrust (*((AABGetCertTrust_SELPROTO)(gPubSecHFT[AABGetCertTrust_SEL])))
#define AABFindCertsByName (*((AABFindCertsByName_SELPROTO)(gPubSecHFT[AABFindCertsByName_SEL])))
#define AABGetTrustedCerts (*((AABGetTrustedCerts_SELPROTO)(gPubSecHFT[AABGetTrustedCerts_SEL])))
#define AABGetCertChain (*((AABGetCertChain_SELPROTO)(gPubSecHFT[AABGetCertChain_SEL])))
#define PSExportDataExchange (*((PSExportDataExchange_SELPROTO)(gPubSecHFT[PSExportDataExchange_SEL])))
#define PSImportDataExchange (*((PSImportDataExchange_SELPROTO)(gPubSecHFT[PSImportDataExchange_SEL])))
#define PSCertIssuedUnderTestCP (*((PSCertIssuedUnderTestCP_SELPROTO)(gPubSecHFT[PSCertIssuedUnderTestCP_SEL])))
#define AABIsCertUnderAdobeRoot (*((AABIsCertUnderAdobeRoot_SELPROTO)(gPubSecHFT[AABIsCertUnderAdobeRoot_SEL])))
#define PSInsertDocInEEnvelope (*((PSAddSecureAttachmentToDoc_SELPROTO)(gPubSecHFT[PSAddSecureAttachmentToDoc_SEL])))


#ifdef __cplusplus
}
#endif

#endif	// PUBSECHFT_H
 

