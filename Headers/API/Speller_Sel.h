/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright 1994-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

  Speller_Sel.h
  
 - Selectors for all Spelling HFT functions.

*********************************************************************/

#ifndef _H_Speller_SEL
#define _H_Speller_SEL

/* For creating selector (index to HFT) 
*/
#ifdef PIPROC
#undef PIPROC
#endif
#define PIPROC(returnType, name, params, ...)	name##_SEL,

/* This defines enum for selectors
*/
typedef enum {	
	SpellerFirst_SEL = 0,
#include "SpellerHFTProcs.h"
	SpellerLast_SEL  
} SpellProcSelectors;
#undef PIPROC

#define SpellerNum_SEL				SpellerLast_SEL - 1
#define SpellerHFT_NAME				"Spell"
#define SpellerHFT_VERSION_1_1		0x00010001
#define SpellerHFT_VERSION_1_2		0x00010002
#define SpellerHFT_VERSION_1_3		0x00010003
#define SpellerHFT_LATEST_VERSION	SpellerHFT_VERSION_1_3

#define kSpellLastBuffer			true
#define kSpellNotLastBuffer			false
#define kSpellMaxName				48

/**  Possible results of the spell check when the SpellCheck() method is called.
	@see SpellCheck
*/
enum SpellDialogResult
{
	/**	The user clicked the Done button to dismiss the dialog box and
		did not complete the spell check, but may have made
		changes to the text buffer. 
	*/
	kSpellDone = 0,				
								
	/**	The user completed spell checking the input buffer, or all
		words were correct. A new text buffer is returned if
		corrections where made.
	*/
	kSpellCompleted,			
								
	/**	The spell check dialog box failed due to an internal error. */
	kSpellFailed = -1,			

	/**	*/
	kSpellResultLast	
};

/** SpellingDomainFlags
	Valid values for the <code>scFlags</code> field of the <code>SpellCheckParam</code> block. For Acrobat 5 and
	higher, all clients should set this field to kSpellFlagAllDomain. All other bits in this
	flag are reserved for future use. The spelling client's private data and flags can be stored in the
	<code>scClientData</code> field.
*/
enum SpellDomainFlags
{
	/**	Default domain behavior. */
	kSpellFlagNone		= 0x0000,	
	/**	For Acrobat 5 and later, all registered spelling domains
		should set this flag. Only the All domains are called by
		spelling when the user clicks the Start button on the
		Spell Check dialog box.
	*/
	kSpellFlagAllDomain	= 0x0001,
	/** Announce to the client that the spell dialog box has just been popped. */
	kSpellCheckStart	= 0x0002,
	/**	*/
	kSpellFlagLast		= 0xFFFF	
};


/**	This parameter block is used for communication between the Spelling plug-in and a client
plug-in. The client must allocate it, initialize all fields, and pass it to the Spelling plug-in
when adding a domain with SpellAddDomain(). Spelling passes it back to the client when
the SCEnableProc(), SCGetTextProc(), and SCCompletionProc() are called.
It is passed to the client's SCGetTextProc() from the Spelling plug-in when it needs to
request a text buffer from the client. After the user has completed the spell check on the
<code>scInBuffer</code>, this same parameter block is passed to the client's
SCCompletionProc() with the result of the spell check in <code>scOutBuffer</code>.
When the SCGetTextProc() is called, <code>scPageNum</code>, <code>scIndex</code> and <code>scAVDoc</code> are filled in
by the Spelling plugin.

<p>The SCGetTextProc should fill in <code>scInBuffer</code> and clear scOutBuffer if it is not
already <code>NULL</code>.</p>

<p>When the spell check is completed, SCCompletionProc() is called with <code>scOutBuffer</code> if
the user made changes to <code>scInBuffer</code>.</p>
Note that the spelling client is responsible for all memory allocated including the
<code>scOutBuffer</code> returned from the Spelling plug-in.
The client is responsible for all parameters except where indicated.
*/
typedef struct SpellCheckParam		SpellCheckParam;
/**	*/
typedef SpellCheckParam *			SpellCheckParamPtr;


/* ---- Spell Check CallBack Procs ---- */
/** */
typedef ACCBPROTO1 ASBool	(ACCBPROTO2 *SCInitProc)(void* clientData);
/**	*/
typedef ACCBPROTO1 void		(ACCBPROTO2 *SCTermProc)(void* clientData);

/**
	Called by the Spelling plug-in to determine whether the 
	Spelling menu items and toolbar button should be enabled. 
	An SCEnableProc() must be provided for each domain a plug-in 
	registers with SpellAddDomain(). 
	@param scp The Spelling plug-in passes this SpellCheckParam 
	parameter block (which the client set up in SpellAddDomain()) 
	to the SCEnableProc() after the spell check is complete. The 
	result of the spell check is in <code>scOutBuffer</code>.
	@return <code>true</code> if spell checking can be performed on 
	the <code>scName</code> domain. 
	@see SCCompletionProc 
	@see SCGetTextProc 
	@see SpellAddDomain 
	@see SpellRemoveDomain 
*/
typedef ACCBPROTO1 ASBool	(ACCBPROTO2 *SCEnableProc)(SpellCheckParamPtr scp);

/**
	This procedure is called by Spelling to request a text buffer 
	to be checked by the user in the Spelling dialog box. 
	@param scp The Spelling plug-in passes this SpellCheckParam 
	parameter block, which the client set up in SpellAddDomain(), 
	to the SCGetTextProc() to request a text buffer. The Spelling 
	plug-in will fill in the <code>scAVDoc</code>, <code>scPageNum</code>, and <code>scIndex</code> 
	members. SCGetTextProc() should return a text buffer in <code>scInBuffer</code>.
	@return This callback should pass back a text buffer to be checked 
	in the <code>scInBuffer</code> member of <code>scp</code>, and return <code>true</code>. Spelling 
	will call the client's SCCompletionProc() after the user has 
	processed this buffer. 

	<p>If there is no more data to be checked on this page, SCGetTextProc 
	should return <code>false</code> and set <code>scInBuffer</code> to <code>NULL</code>. </p>
	@see SCCompletionProc 
	@see SCEnableProc 
	@see SpellAddDomain 
	@see SpellRemoveDomain 
*/
typedef ACCBPROTO1 ASBool	(ACCBPROTO2 *SCGetTextProc)(SpellCheckParamPtr scp);

/**
	An SCCompletionProc() must be provided for each domain a plug-in 
	registers with SpellAddDomain(). It is called by the Spelling 
	plug-in when the user has completed the spell check. 
	@param scp The SpellCheckParam parameter block (which 
	the client set up in SpellAddDomain()) passed to the client 
	by the Spelling plug-in after the spell check of <code>scInBuffer</code> 
	is complete. This procedure will be called with <code>scOutBuffer</code> 
	filled in by the Spelling plug-in if the user made changes 
	to <code>scInBuffer</code> (<code>scOutBuffer</code> could be <code>NULL</code>).
	@return <code>true</code> if the changes were successfully committed. 

	@note In the current version of the Spelling plug-in, this 
	value is ignored. 
	@see SCEnableProc 
	@see SCGetTextProc 
	@see SpellAddDomain 
	@see SpellRemoveDomain 
*/
typedef ACCBPROTO1 ASBool	(ACCBPROTO2 *SCCompletionProc)(SpellCheckParamPtr scp);

/** Called by the Spelling plug-in each time <code>scOutBufferAStext</code> is about to change.
	An SCChangeProc() is optional.
	@param scp IN The SpellCheckParam parameter block (which the client set up in
	SpellAddDomain()) passed to the client by the Spelling plug-in when
	the user makes a change to the <code>scInBufferASText</code>.  When called, <code>scOutBufferAStext</code>
	is about to be changed and <code>scChangeStart</code> and <code>scChangeEnd</code> are
	set to the the character offsets of the change from the start of <code>scOutBufferAStext</code>,
	and <code>scChangeText</code> is the new text that will replace the current text in the range.
	@return TBD
	@exception None
	@see	SCEnableProc
	@see	SCGetTextProc
	@see	SpellAddDomain
	@see	SpellRemoveDomain
	@see	SCCompletionProc
*/
typedef ACCBPROTO1 ASBool	(ACCBPROTO2 *SCChangeProc)(SpellCheckParamPtr scp);

/**	Callback proc for SpellCheckRTF.
	This proc is called each time the user changes something in the original input buffer.
	This allows the caller of SpellCheckRTF() to track text changes to a rich text buffer and
	overlay the plain text change onto the rich text spans to perserve formatting.

	@param	vReserved IN	Reserved for future use.
	@param	astNewText IN	The new plain text of the change
	@param	nStartIndex IN	The character offset from the start of the current plain text buffer of the change start.
	@param	nEndIndex IN	The character offset from the start of the current plain text buffer of the change end.
	@param	vData IN		The client data.
	@return <code>true</code> to continue the dialog with user, <code>false</code> to terminate.
	@see	SpellCheckRTF
*/
typedef ACCBPROTO1 ASBool	(ACCBPROTO2 *SCRTFChangeProc)(void* vReserved, ASConstText astNewText, ASInt32 nStartIndex, ASInt32 nEndIndex, void *vData);

#define kSCparam_VERSION_1			0x0001
#define kSCparam_VERSION_2			0x0002			/* Acrobat 6 and earlier */
#define kSCparam_VERSION_3			0x0003			/* Acrobat 7: scMenuText added */
#define kSCparam_LATEST_VERSION		kSCparam_VERSION_3

/** Spell Check parameters
	This parameter block is used for communication between the Spelling plug-in and a
	client plug-in. The client must allocate it, initialize all fields, and pass it to the Spelling
	plug-in when adding a domain with SpellAddDomain. Spelling passes it back to the
	client when the SCEnableProc(), SCGetTextProc(), and SCCompletionProc() are
	called.
	
	<p>It is passed to the client's SCGetTextProc() from the Spelling plug-in when it needs to
	request a text buffer from the client. After the user has completed the spell check on
	the <code>scInBuffer</code>, this same parameter block is passed to the client's
	SCCompletionProc() with the result of the spell check in <code>scOutBuffer</code>.
	When the SCGetTextProc() is called, <code>scPageNum</code>, <code>scIndex</code> and <code>scAVDoc</code> are filled
	in by the Spelling plugin.</p>

	<p>The SCGetTextProc should fill in <code>scInBuffer</code> and clear <code>scOutBuffer</code> if it is not
	already <code>NULL</code>.</p>

	<p>When the spell check is completed, SCCompletionProc() is called with <code>scOutBuffer</code>
	if the user made changes to <code>scInBuffer</code>.</p>

	Note that the spelling client is responsible for all memory allocated including the
	<code>scOutBuffer</code> returned from the Spelling plug-in.
	The client is responsible for all parameters except where indicated.
*/
struct SpellCheckParam {
	/** Version number of this structure (kSCparam_LATEST_VERSION). */
	ASInt16 			scVersion;				
	/** Domain control flags; see SpellDomainFlags. It should normally be set to kSpellFlagAllDomain. */
	ASInt16 			scFlags;				
	/** This name will be returned by SpellDomainNames(). */
	char 				scName[kSpellMaxName];	

	/** */
	SCEnableProc		scEnableProc;			

	/** */
	SCGetTextProc		scGetTextProc;		
	/** */
	SCCompletionProc	scCompletionProc;		

	/** (Passed by Spelling plug-in) The active AVDoc during this Spell Check session. */
	AVDoc				scAVDoc;				
	/** (Passed by Spelling plug-in) The 0-based PDDoc page number of <code>scAVDoc</code>. */
	ASInt32 			scPageNum;				
	/** (Passed by Spelling plug-in) The 0-based index of this domain item.
		The Spelling plug-in will set <code>scIndex</code> to zero to start or restart, and request the first text buffer from
		this domain on <code>scPageNum</code>.

		<p>The Spelling plug-in will increment <code>scIndex</code> after each call to <code>scGetTextProc</code>.
		The client can increment <code>scIndex</code> if desired to track non-sequential domain items. </p>
	*/
	ASInt32 			scIndex;				
	/** The text buffer from the client to the Spelling plug-in when scGetTextProc() is called by the Spelling plug-in. */
	char * 				scInBuffer;				
	/** (Passed by Spelling plug-in) The buffer returned from the
		Spelling plug-in to scCompletionProc().
		Note that the client must release this memory. 
	*/
	char * 				scOutBuffer;			
	/** Can be used by the client to store private state data. The
		client is responsible for allocating memory where necessary. 
	*/
	void *				scClientData;			

/* new with version kSCparam_VERSION_2... */
	/** The text buffer from the client to the Spelling plug-in when <code>scGetTextProc</code> is called by the Spelling plug-in. 
		Note that the client must release this memory. 
	*/
	ASText				scInBufferASText;		
	/** Returned buffer from Spelling PI to scCompletionProc(). 
		@note This memory is owned by the Spelling plug-in. Do not free it. 
	*/
	ASConstText			scOutBufferAStext;		
	/** This optional callback will be invoked each time <code>scOutBufferAStext</code> is about to change. */
	SCChangeProc		scChangeProc;			
	/** New text that will replace the text from scChangeStart to <code>scChangeEnd</code>.  
		@note This memory is owned by the Spelling plug-in. Do not free it. 
	*/
	ASConstText			scChangeText;			
	/** Character offset of the start of the change when scChangeProc() is called */
	ASInt32				scChangeStart;			
	/** Character offset of the end of the change when scChangeProc() is called */
	ASInt32				scChangeEnd;

	/*new with version kSCparam_VERSION_3... */
	/** The menu title in case this is the only enabled domain (for example, <b>"In Form Fields..."</b> or <b>"In Comments..."</b>). */
	ASConstText			scMenuTitle;
};

/* ================================== */
/* === Hyphenation check services === */
/* ================================== */

/** The types of hyphenations. */
enum {
	/**		*/
	kHyphen_all = -1,				
	/**		*/
	kHyphenType_preferred = 0,
	/**		*/
	kHyphenType_normal,
	/**		*/
	kHyphenType_nonpreferred
};
typedef ASEnum16 eHyphenType;

/**
	The hyphenation record.
	<p>One of these is returned by HyphenateWord() in the optional hyphenation array for each known hyphenation.</p>
*/
struct _t_HyphenationRecord {
	/** The type of hyphenation: preferred, normal, or non-preferred. */
	eHyphenType			eType;					
	/** The hyphen index. The hyphen should follow this character. */
	ASInt32				nPosition;				
	/** The word part before the hyphen. */
	ASText				astLeft;				
	/** The word part after the hyphen. */
	ASText				astRight;				
};
/** */
typedef struct _t_HyphenationRecord		HyphenationRecord;
/** */
typedef HyphenationRecord *				HyphenationRecordPtr;

/* ======================================= */
/* ======== Spelling HFT services ======== */
/* ======================================= */

/* Define API/Function prototypes
*/
#ifdef PIPROC
#undef PIPROC
#endif
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
#include "SpellerHFTProcs.h"
#undef PIPROC

#endif	/* _H_Speller_SEL */
