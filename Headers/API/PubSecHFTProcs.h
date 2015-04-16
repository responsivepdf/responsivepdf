/*************************************************************************
* WARNING: All additions to this file must go at the end of the file.
* This file is #included to build a table of function pointers (an HFT).
* All components which make use of this HFT rely on the order and
* positioning of these functions (e.g. plug-ins). Adding entries in the 
* middle of this file or modifying existing entries will cause these 
* components to break.
**************************************************************************/

/*************************************************************************
 * PubSecHFTProcs.h
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
 *  11-May-2007 -- Created from PubSecHFT.h for Acrobat 9.0
 ************************************************************************/
/************************************************************************************
 * PubSecHFT - Prototype declarations
 ***********************************************************************************/

/* HFTBeginProto - do not alter/remove this line! */


/**
	Registers a handler with the PubSec HFT. The caller retains 
	ownership of the PubSecHandlerRec. 
	@param owner The handler's plug-in ExtensionID, assigned 
	at initialization. 
	@param psHandler The handler structure containing the 
	handler methods to register.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see PSUnregisterHandler 
*/
PIPROC(ASBool, PSRegisterHandler,
	( ExtensionID owner, PubSecHandler psHandler  ), owner, psHandler)


/**
	Unregisters a handler from the PubSec HFT. This does not 
	destroy the handler; the caller owns the PubSecHandlerRec. 
	
	@param psHandler The handler to unregister.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see PSRegisterHandler 
*/
PIPROC(void, PSUnregisterHandler,
	( PubSecHandler psHandler  ), psHandler)


/*************************************************************************
 * Doc Cache methods. PubSec keeps a list of all encrypted documents
 * that are open. For security reasons handlers will want these
 * documents to all be closed when a handler releases access to
 * critical resources, for example when logging out.
 ************************************************************************/

/**
	Returns the number of encrypted documents associated with 
	a PubSec engine. It returns separate values for documents that 
	need to be saved, and for those that do not need to be saved 
	and can be safely closed. 
	@param engine The engine for which the encrypted docs 
	are counted. 
	@param outNeedSave (Filled by the method) A pointer to 
	the number of encrypted documents associated with the engine 
	that need to be saved. 
	@param outCanClose (Filled by the method) A pointer to 
	the number of encrypted documents associated with the engine 
	that do not need to be saved and can be safely closed.
	@see PSCloseEncryptedDocs 
*/
PIPROC(void, PSCountEncryptedDocs,
	( PubSecEngine engine, ASUns32 *outNeedSave, ASUns32 *outCanClose ), engine, outNeedSave, outCanClose )


/**
	Closes all encrypted documents associated with a PubSec 
	engine, regardless of whether they need to be saved. 
	Use PSCountEncryptedDocs() to determine if there are any documents 
	that will need to be opened or saved. 

	<p>PubSec keeps a list of all open encrypted documents. For 
	security reasons, handlers will want all of these documents 
	to be closed when it releases access to critical resources, 
	(for example, when logging out). Use this method (rather than 
	closing the documents directly) so that PubSec can maintain 
	its cache correctly. </p>

	@param engine The engine for which the encrypted documents 
	are closed.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see PSCountEncryptedDocs 
*/
PIPROC(ASBool, PSCloseEncryptedDocs, ( PubSecEngine engine ), engine)

PIPROC(ASBool, PSSigValidatePDDocSigField, ( PSSigPDDocParams docParams  ), docParams)

/*************************************************************************
 * Signature operations
 ************************************************************************/

/**
	Validates a specified signature field in a PDDoc. For example, 
	you might call this from the validate button of a signature 
	properties dialog, or if any information used during validation 
	is changed. It does not bring up any user interface. 

	<p>A return value of <code>true</code> indicates that the validation operation 
	was successfully peformed, but does not provide any information 
	about the result of the validation (that is, the signature's 
	validity value). The method does not return validity information, 
	but simply updates the DigSig and PubSec validation caches. </p>
	@param docParams The validation parameters.
	@return <code>true</code> if the validation was successfully performed, <code>false</code> 
	otherwise. 
	
	@note This method cannot validate a signature whose cache 
	has not been updated or is <code>NULL</code>. In this case, use DigSigVerifySig(). 
*/

/**
	Gets bytes of data to digest when signing or verifying, 
	in chunks of a specified size. It continues getting data chunks 
	until all of the data in the data buffer has been returned. 
	
	<p>A handler will use this call when computing its own data 
	digest, to get the next blob of bytes to digest. The <code>dataBuffer</code> 
	object keeps track of the bytes that have been returned, 
	of how many bytes remain to be returned, and of the byte 
	ranges of data to be provided. </p>

	<p>When signing or verifying a PDDoc, the data buffer object 
	is a PDDoc handle and the bytes returned will be those defined 
	by /ByteRange in the signature object dictionary. See the 
	PDF Reference for details. </p>

	<p>PSDataBufferDigest() uses this method when computing the digest for the data. </p>
	@param dataBuffer The buffer containing the data. 
	@param maxSize The maximum number of bytes to return in 
	the return buffer. 
	@param pReturnBuffer (Filled by the method) A pointer 
	to the buffer containing the current bytes to be processed. 
	If it is <code>NULL</code>, an error occurred and you should abort the enumeration. 
	
	@param pReturnSize (Filled by the method) A pointer to 
	the size in bytes of the return buffer. When it is <code>0</code>, do not process 
	the return buffer, but continue enumerating until the method 
	returns <code>false</code>. It is always less than <code>maxSize</code>.
	@return <code>true</code> as long as there is more data to process, <code>false</code> when 
	the end of the buffer is reached. 
	@see PSDataBufferReset
	@see PSDataBufferDigest 
*/
PIPROC(ASBool, PSDataBufferEnum,
	( PSDataBuffer dataBuffer, ASInt32 maxSize, ASUns8 **pReturnBuffer, ASInt32 *pReturnSize  ),
		dataBuffer, maxSize, pReturnBuffer, pReturnSize  )


/**
	Computes the digest for a set of data. A handler will use 
	this call to make PubSec compute the digest for a data buffer 
	when signing or verifying signatures. This method calls 
	PSDataBufferEnum() to get the bytes and computes an MD5 or 
	SHA-1 digest. 
	@param dataBuffer The buffer containing the data. 
	@param digestValue (Filled by the method) A pointer to 
	the digest value. The buffer must large enough for the requested 
	digest method:
	<ul>
	<li>For an MD5 digest, it must be at least 16 bytes.</li>
	<li>For an SHA-1 digest, it must be at least 20 bytes.</li>
	</ul>
	@param digestMethod The method to use to compute the digest.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see PSDataBufferReset
	@see PSDataBufferEnum 
*/
PIPROC(ASBool, PSDataBufferDigest,
	( PSDataBuffer dataBuffer, ASUns8* digestValue, DSDigestMethod digestMethod  ),
	dataBuffer, digestValue, digestMethod  )

/**
	Acquires the DSAP file and opens it, if it has not already 
	been acquired. 

	<p>PubSec calls this method to access a file, so a handler 
	does not need to acquire a DSAP file unless it needs to 
	access it for other reasons. </p>

	@param bResolveProblems When it is <code>true</code>, if there are problems 
	trying to open the file, PubSec opens a user interface that gives a 
	user the option to delete the corrupted file. 
	@param bCreate When it is <code>true</code>, if the file does not exist it 
	is created. It is normally <code>true</code>.
	@return <code>true</code> if the file was acquired and opened, <code>false</code> otherwise. 
	
	@see DSAPFileRelease 
*/
PIPROC(ASBool, DSAPFileAcquire, ( const ASBool bResolveProblems, const ASBool bCreate  ), bResolveProblems, bCreate  )


/**
	Closes the digital signature appearance (DSAP) file. 
	@see DSAPFileAcquire 
	@see DSAPFileSave
*/
PIPROC(void, DSAPFileRelease, (void), )


/**
	Saves the DSAP file if it is dirty, leaving it open. 
	@see DSAPFileRelease
*/
PIPROC(void, DSAPFileSave,(void), )

/**
	Gets the number of configured signature appearance entries 
	in the DSAP file, 
	@return The number of configured AP entries. 
	@see DSAPFileCanDeleteNthEntry
*/
PIPROC(ASInt32, DSAPFileGetCount, (void), )

/**
	Tests whether a signature appearance entry at a specified 
	index in the DSAP file can be edited or is read-only. 
	@param index The position of the entry to test. The first 
	entry is at index <code>0</code>. A negative value gets the default entry.
	@return <code>true</code> if the entry is editable, <code>false</code> otherwise. 
	@see DSAPFileGetCount 
	@see DSAPFileRemoveNthEntry 
*/
PIPROC(ASBool, DSAPFileCanDeleteNthEntry, ( const ASInt32 index  ), index)

/**
	Gets a copy of the name of the specified signature appearance 
	entry in the DSAP file. Use this when building a list of 
	signatures for a user to choose from or edit. 
	@param index The position of the entry whose name to obtain. 
	The first entry is at index <code>0</code>. A negative value gets the 
	default entry.
	@return A copy of the name as an ASText object. 
	@see DSAPFileGetCount 
	Closes the digital signature appearance (DSAP) file. 
	@see DSAPFileAcquire 
	@see DSAPFileSave
*/
PIPROC(ASText, DSAPFileGetNewNthName, ( const ASInt32 index  ), index)

/**
	Deletes the specified signature appearance entry from the 
	DSAP file. 
	@param index The position of the entry to remove. The 
	first entry is at index <code>0</code>. A negative value gets the default 
	entry.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see DSAPFileCanDeleteNthEntry 
	@see DSAPFileGetCount 
*/
PIPROC(ASBool, DSAPFileRemoveNthEntry,	( const ASInt32 index ), index)

/**
	Opens the user interface that allows the user to edit the specified 
	signature appearance entry of the DSAP file. 
	@param previewData Data with which to create a signature 
	preview in the edit dialog. 
	@param index The position of the entry to edit. The first 
	entry is at index <code>0</code>. A negative value gets the default entry. 
	An index larger than the current number of entries creates 
	a new entry.
	@return <code>true</code> if successful (the changes to the entry were made and 
	saved), <code>false</code> otherwise. 
	@see DSAPFileCanDeleteNthEntry 
	@see DSAPFileCopyNthEntry 
*/
PIPROC(ASBool, DSAPFileEditNthEntry,
	( const APPreview previewData, const ASInt32 index ), previewData, index )

/**
	Creates a copy of the specified entry in the default DSAP 
	file and appends the copy to the end of the list of signature 
	appearances in the file. 

	<p>When you copy a default appearance entry, the copy is not 
	considered a default appearance entry. </p>
	@param index The position of the entry to copy. The first 
	entry is at index <code>0</code>. A negative value gets the default entry.
	@return <code>true</code> if the copy was successful and the appearance file 
	was successfully edited and saved, <code>false</code> otherwise. 
	@see DSAPFileCanDeleteNthEntry 
	@see DSAPFileEditNthEntry 
*/
PIPROC(ASBool, DSAPFileCopyNthEntry,	( const ASInt32 index  ), index)

/************************************************************************************
 * PubSec Acrobat Address Book (AAB) API
 ***********************************************************************************/

/**
	Finds the specified certificate in the Acrobat Address Book. 
	Use this method to distinguish a certificate that is not 
	found by AABGetCertTrust from one whose trust level is reported 
	as untrusted. 
	@param x509 The certificate identifier, as defined in 
	X.509 (RFC 3280). 
	@param size The size of the certificate pointed to by 
	<code>x509</code>.
	@return <code>true</code> if the certificate is found, <code>false</code> otherwise. 
	@see AABGetCertTrust 
*/
PIPROC(ASBool, AABIsCertPresent, ( const ASUns8* x509, ASInt32 size  ), x509, size )


/**
	Finds the specified certificate in the Acrobat Address Book 
	and returns the trust level. 
	@param inX509Cert The certificate identifier, as defined 
	in X.509 (RFC 3280). This is a generic 8-bit pointer to 
	the certificate data. 
	@param inX509CertSize The size in bytes of the X.509 certificate 
	pointed to by <code>inX509Cert</code>. 
	@param inCertChain An ASCab containing the certificate 
	chain for the certificate, with the trust level for each 
	certificate. It starts with the <code>inX509Cert</code> parameter's issuer at index 
	<code>0</code> and continues in the issuing order. Can be <code>NULL</code> if the 
	chain is not available. 
	@param inHelperCerts An ASCab containing an unordered 
	sequence of certificates that can be used to build the certificate 
	chain. If <code>inCertChain</code> is <code>NULL</code> and <code>inX509Cert</code> is not self-signed, 
	PubSec attempts to build a chain of certificates using a 
	default mechanism. A certificate ASCab contains an entry 
	for each certificate,with a 0-based index followed by the 
	X509 certificate as ASN1-encoded binary data. 
	For example:
	<p><code>{ ("0", cert1), ("1", cert2), ... }</code></p>

	@return The trust value for the specified certificate, if found. 
	If no certificate is found, it returns kPSSigTrustUntrusted. 
	To distinguish a certificate that is not found from one 
	whose trust level is reported as untrusted, use AABIsCertPresent(). 
	
	@see AABGetTrustedCerts 
	@see AABIsCertPresent 
*/
PIPROC(PSSigTrust, AABGetCertTrust,
	( const ASUns8* inX509Cert, ASInt32 inX509CertSize, ASCab inCertChain, ASCab inHelperCerts  ),
	inX509Cert, inX509CertSize, inCertChain, inHelperCerts  )

/**
	Performs a lookup in the Acrobat Address Book by certificate 
	subject name. It returns all certificates that match the name 
	along with trust information associated with them. 

	<p>The returned ASCab contains: </p>
	<ul>
	<li>An entry for each certificate, with a 0-based index followed by the X509 certificate as ASN1-encoded binary data. </li> 
	<li>An entry with a key <code>Tn</code> containing the associated trust value of each certificate, where <code>n</code> corresponds to the certificate's index key. </li>
	</ul>

	<p>If a trust key is missing, the value should be assumed to 
	be untrusted. For example: </p>

	<p><code>{ ("0", cert1), ("1", cert2), ("T1", kPSSigTrustAuthenticDocuments) } </code></p>

	<p>In this case, <code>cert1</code> is untrusted, <code>cert2</code> is trusted for authentic documents. </p>

	@param inCertNameData The subject name of the certificates 
	to find. Specify a BER-encoded value of <code>ASN.1 type Name</code> 
	defined in X.509 (RFC 3280). 
	@param inCertNameSize The size of the certificate subject 
	name data. 
	@param outResults (Filled by the method) An ASCab containing 
	any certificates, and their trust information, found by the lookup.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see AABGetCertTrust 
	@see AABGetTrustedCerts 
*/
PIPROC(void, AABFindCertsByName,
	( const ASUns8* inCertNameData, ASInt32 inCertNameSize, ASCab outResults  ),
	inCertNameData, inCertNameSize, outResults  )

/**
	Finds the certificates with a specified level of trust in 
	the Acrobat Address Book. 
	@param inTrust The level of trust for which to find certificates. 
	It is a logical <code>OR</code> of PSSigTrust bit flags. 
	@param outResults (Filled by the method) An ASCab containing 
	the trusted certificates found in the AAB. A certificate 
	ASCab contains an entry for each certificate, with a 0-based 
	index followed by the X509 certificate as ASN1-encoded binary 
	data. For example: 
	<p><code>{ ("0", cert1), ("1", cert2), ... }</code></p>

	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see AABGetCertTrust 
*/
PIPROC(void, AABGetTrustedCerts,
	( PSSigTrust inTrust, ASCab outResults  ), inTrust, outResults  )

/**
	Finds the certificate chain for the specified certificate 
	in the Acrobat Address Book. 

	<p>A certificate ASCab contains an entry for each certificate,with 
	a 0-based index followed by the X509 certificate as ASN1-encoded 
	binary data. For example: </p>

	<p><code>{ ("0", cert1), ("1", cert2), ... } </code></p>

	@param inX509Cert The certificate identifier, as defined 
	in X.509 (RFC 3280). This is a generic 8-bit pointer to 
	the certificate data. 
	@param inX509CertSize The size in bytes of the X.509 certificate 
	pointed to by <code>inX509Cert</code>. 
	@param inTrustedCerts An ASCab containing the user's trusted 
	certificates. 
	@param inUntrustedCerts An ASCab containing additional 
	certificates needed to build the certificate chain. 
	@param outChain (Filled by the method) An ASCab containing 
	the certificate chain. The specified certificate itself 
	is at index <code>0</code>, followed by the chain certificates in issuing 
	order.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see AABGetTrustedCerts 
*/
PIPROC(ASBool, AABGetCertChain,
	( const ASUns8* inX509Cert, ASInt32 inX509CertSize, ASCab inTrustedCerts, ASCab inUntrustedCerts, ASCab outChain  ),
	inX509Cert, inX509CertSize, inTrustedCerts, inUntrustedCerts, outChain  )

/************************************************************************************
 * Import/Export Facilities
 * Use to import/export certificates, requests for certificates, etc to FDF
 * files or other file types. Includes support to export to a file or
 * to email.  Uses wizard-like user interface
 ***********************************************************************************/

/**
	Exports certificates, requests for certificates, and so 
	on, to FDF files or other file types, using a user interface wizard. 
	It includes support to export to a file or to email. 
	
	<p>The specified type of data is exported to a file and optionally 
	emailed to a destination that is chosen using the wizard: </p>

	<ul>
    <li>If the data is saved to a file and is the user's own contact information, it can be a PKCS#7 file (.p7c). </li>
	<li>If the data contains just one certificate and is saved to a file, it can be a raw certificate file (.cer). </li>
	<li>Otherwise, it is always an FDF file. </li>
	</ul>

	<p>It does not raise or throw exceptions. It displays an alert if it is unsuccessful. </p>
	
	@param params A structure containing the export parameters.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see PSImportDataExchange 
*/
PIPROC(ASBool, PSExportDataExchange,
	( PSExportDataExchangeParams params  ), params)

/**
	Imports FDF data from a file, using a user interface wizard. 
	The parameters structure specifies the type and location 
	of the data. This call is used, for example, by the Directory
	configuration dialog box to import directory settings from an 
	FDF file. 

	<p>When you use this call (rather than opening the FDF file 
	directly) the PubSec FDF handling code is used, which provided 
	support for FDF signature verification. PubSec opens the 
	FDF file, and then calls the handler's PSImportDataProc() using 
	the handler and engine specified in the parameters structure. </p>
	
	<p>The operation fails if the data is not of the specified 
	type. It does not raise or throw exceptions. It displays an alert if unsuccessful. </p>
	
	@param params A structure containing the import parameters.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see PSExportDataExchange 
*/
PIPROC(ASBool, PSImportDataExchange,
	( PSImportDataExchangeParams params  ), params)

/**
	Tests whether any certificate in a chain has been issued 
	under the Adobe Test Certificate Policy. 

	<p>If this function returns <code>true</code>, PubSec handlers are recommended 
	to provide feedback to the user regarding the test nature 
	of the certificate, which may render it untrustworthy. </p>
	@param inCertChain The certificate chain to test, as an 
	ASCab array. The first certificate is the end entity, and 
	certificates should follow in the issuing order. For example: 

	<p><code>{ ("0", cert1), ("1", cert2), ... }</code></p> 
	
	<p><code>certn</code> is an X509 certificate as ASN1-encoded binary data.</p>

	@return <code>true</code> if any certificate in the chain was issued under the Adobe Test Certificate Policy.
*/
PIPROC(ASBool, PSCertIssuedUnderTestCP,
	( ASCab inCertChain  ), inCertChain)

/**
	As functions PSDataBufferEnum() or PSDataBufferDigest() are stateful (for example, the <code>dataBuffer</code> 
	object keeps track of the bytes that have been returned), call this function whenever 
	the state maintained within the <code>dataBuffer</code> need to be re-initialized.
	@param dataBuffer The buffer containing the stateful information.
	@see PSDataBufferEnum 
	@see PSDataBufferDigest
*/
PIPROC(void, PSDataBufferReset,	( PSDataBuffer dataBuffer ), dataBuffer )


/**
	Tests whether any certificate in a chain has been issued
	under the Adobe Root Certificate Policy.

	@param inCertChain The certificate chain to test, as an 
	ASCab array. The first certificate is the end entity, and 
	certificates should follow in the issuing order. For example: 
	<p><code>{ ("0", cert1), ("1", cert2), ... }</code></p>

	@return <code>true</code> if any certificate in the chain was issued 
	under the Adobe Root Certificate Policy.
*/
PIPROC(ASBool, AABIsCertUnderAdobeRoot,
	( ASCab inCertChain  ), inCertChain)

/**
	Attach the a document to an eEnvelope using the specified 
	certificate data.

	<p> This function calls <code>addRecipientListCryptFilter</code> and 
	<code>importDataObject</code>.</p>

	@param inDIPath Path to the document to add and secure as an attachment 
	to <code>pdDoc</code>.
	@param szAttName The attachment's name. 
	@param inCertChain The certificate identifier. This is a generic 8-bit 
	pointer to the hex-encoded raw value of the certificate data. 
	@param inCertSize The size in bytes of the certificate pointed to by
	<code>inCertChain</code>.
	@param pdDoc The document provided by the caller to which <code>szAttName</code> 
	will be attached and secured.

	@return <code>true</code> if the the <code>pddAttachment</code> is 
	secured and attached properly to the <code>pdDoc</code>.

	@see addRecipientListCryptFilter
	@see importDataObject
*/
PIPROC(ASBool, PSAddSecureAttachmentToDoc,
	(ASText inDIPath, ASText inAttName,const ASUns8* inCertChain, ASInt32 inCertSize, PDDoc pdDoc),
	inDIPath, inAttName,inCertChain, inCertSize, pdDoc)







