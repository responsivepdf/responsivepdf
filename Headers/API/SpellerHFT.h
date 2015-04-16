/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 2000-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 SpellerHFT.h

 - HFT definitions for Acrobat Spell Check procedures.

 - Acrobat Spelling plug-in provides a spell check API. To use the
   Spelling HFT, a plug-in must include the header file SpellerHFT.h,
   which includes Speller_Sel.h. The plug-in must also import the HFT
   using ASExtensionMgrGetHFT and assign the HFT returned by this call
   to a plug-in-defined global variable named gSpellerHFT.

   The easiest way to do this is to use the Init_SpellingHFT macro
   defined below.

*********************************************************************/

#ifndef _H_SpellerHFT
#define _H_SpellerHFT


#if __cplusplus
extern "C" {
#endif	/* __cplusplus */

extern HFT gSpellerHFT;

#include "Speller_Sel.h"


/*	Init_SpellingHFT
**	Use this to initialize and make the Spelling HFT functions available to your plug-in. 
*/
#define Init_SpellerHFT ASExtensionMgrGetHFT(ASAtomFromString(SpellerHFT_NAME), SpellerHFT_LATEST_VERSION)


/* =============================== */
/* === Spelling check services === */
/* =============================== */

/*
**	ASBool SpellCheck(AVDoc avd, const char* textBuffer, ASInt16* dialogResult, ASBool bLastBuffer, char** dictionaryArray, ASInt32 dictionaryCount)
**
**	Call the Spelling PI to have it check a text buffer and interact with the user.
**	This service will display the Spell Check dialog.
**
**	avd					- The current active document.
**	textBuffer			- The input text buffer to be checked for spelling.
**	dialogResult		- see enum SpellDialogResult for possible dialog results.
**						  When dialogResult == kSpellDone, the client should terminate any domain search loops.
**	bLastBuffer			- when this is true, the Spelling PI will close the dialog box when the end
**						  of the inTextBuffer is reached.  Otherwise, the dialog will stay open
**						  expecting another SpellCheck call form the same spelling client.
**	dictionaryArray		- optional char* array of dictionary names to be searched
**	dictionaryCount		- count of dictionary names in dictionaryArray
**
**	Returns:			- a new text buffed if the user made any changes to the inTextBuffer,
**						  otherwise NULL == no changes.
*/
#define SpellCheck (*((SpellCheck_SELPROTO)(gSpellerHFT[SpellCheck_SEL])))

/*
**	ASBool SpellCheckRTF(AVDoc avd, void* vReserved, ASText astPlainText, char** dictionaryArray, ASInt32 dictionaryCount, SCRTFChangeProc pRTFchangeProc, void* vClientData);
**
**	Check a text buffer and receive a call back for each change as the user interacts with the Spelling dialog.
**	This service will display the Spell Check dialog.
**
**	This service is the same as SpellCheck (above) except a call back procedure is used to see each change to the
**	plain text input buffer as it occurs.
**
**	avd					- The current active document.
**	vReserved			- reserved for future use.
**	astPlainText		- The input plain text buffer to be checked for spelling.
**	dictionaryArray		- optional char* array of dictionary names to be searched
**	dictionaryCount		- count of dictionary names in dictionaryArray
**	pRTFchangeProc		- change proc, called with each user change as it occurs, see SCRTFChangeProc in Speller_Sel.h
**	vClientData			- client data, passed back to caller's change proc
**
**	Returns:			- SpellDialogResult.
*/
#define SpellCheckRTF (*((SpellCheckRTF_SELPROTO)(gSpellerHFT[SpellCheckRTF_SEL])))

/*
**	ASBool SpellCheckText(const char* textbuffer, ASUns32* startOffset, ASUns32* endOffset, char** dictionaryArray, ASInt32 dictionaryCount)
**
**	Check the spelling of the words in a text buffer starting at startOffset and ending at endOffset.
**	This service DOES NOT display the Spell Check dialog.
**	Returns true if all the words in the range were in the current dictionaries.
**	Returns false and the startOffset and endOffset of the first misspelled word found in the text buffer.
**
**	textbuffer			- Text buffer to be checked for spelling.
**	startOffset			- Spelling PI returns the starting offset of the first misspelled word
**						  in the textBuffer.
**	endOffset			- Spelling PI returns the ending offset of the first misspelled word
**						  in the textBuffer.
**	dictionaryArray		- optional char* array of dictionary names to be searched
**	dictionaryCount		- count of dictionary names in dictionaryArray
**
**	Returns:			- true if all words in the buffer are correct, false if a misspelled word was found.
**
**	Notes: typically you would call this function when you want to silently check the spelling of a text buffer.
**	AcroForms uses this call to underline unknown words in a form text field.
*/
#define SpellCheckText (*((SpellCheckText_SELPROTO)(gSpellerHFT[SpellCheckText_SEL])))

/*
**	ASBool SpellCheckWord(AVDoc avd, const char* cWord, char** dictionaryArray, ASInt32 dictionaryCount, char** alternativeArray, ASInt32 *alternativeCount)
**
**	Call the Spelling PI to have it check a word.
**	This service DOES NOT display the Spell Check dialog.
**
**	avd					- The current active document.
**	textBuffer			- Text buffer containing the word to be checked for spelling.
**	wordLength			- length of text buffer.
**	dictionaryArray		- optional char* array of dictionary names to be searched
**	dictionaryCount		- count of dictionary names in dictionaryArray
**	alternativeArray	- optional pointer for a char* array of alternative spellings of an incorrect word if any
**						  NOTE: The caller is responsible for freeing this memory.
**	alternativeCount	- count of alternative words in alternativeArray
**
**	Returns:	- true if the word in the buffer is correct, false if the word is unknown.
**
**	Notes: typically you would call this function when you want to silently check the spelling of a word.
*/
#define SpellCheckWord (*((SpellCheckWord_SELPROTO)(gSpellerHFT[SpellCheckWord_SEL])))

/*
**	ASBool SpellCountKnownWords(const char* textBuffer, ASInt32 dictionaryCount, char** dictionaryArray, ASInt32* counterArray)
**
**	Call the Spelling PI to have it count the known words in a text buffer.
**	This service DOES NOT display the Spell Check dialog.
**
**	textBuffer			- Text buffer.
**	dictionaryCount		- count of dictionary names in dictionaryArray and counters in counterArray
**	dictionaryArray		- char* array of dictionary names to be searched
**	counterArray		- array of counters.  For each dictionary in dictionaryArray the Spelling PI
**						  will increment the corresponding counter in this array when a word is found in that
**						  dictionary.
**
**	Returns:	- index of dictionary with the highest correct count, -1 on error
**
**	Notes: typically you would call this function when you want to attempt to discover the language of a text buffer.
*/
#define SpellCountKnownWords (*((SpellCountKnownWords_SELPROTO)(gSpellerHFT[SpellCountKnownWords_SEL])))

/*
**	ASText SpellGetNextWord(ASText inBuffer, ASText outWord, ASInt32* nStart, ASInt32* nEnd, ASBool bFilter);
**
**	Scan a text buffer and return the next word.
**
**	inBuffer			- text buffer.
**	nStart				- character offset from start of buffer, if scan is successful the offset to the word start will be returned.
**	nEnd				- character offset to terminate the scan set to zero to scan to the end of the text buffer,
**						  If scan is successful the offset to the character past the last character of the word will be returned.
**						  To scan for the next word, set nStart to this new offset.
**	bFilter				- if true, apply standard ignore filters:	single character words,
**																	long words (48 characters max), 
**																	words that have digits, 
**																	all UPPERCASE, 
**																	Roman Numerals, 
**																	words that have non-roman unicode (CJK) characters
**
**	Returns:			- ASText with word if one was found.
*/
#define SpellGetNextWord (*((SpellGetNextWord_SELPROTO)(gSpellerHFT[SpellGetNextWord_SEL])))


/* ======================================= */
/* === Spelling client domain handling === */
/* ======================================= */

/*
**	ASBool SpellDomainNames(char** domainArray, ASInt32 *domainCount)
**
**	Returns an array of the current domain names.
**
**	domainArray			- the spelling plugin will allocate and return a char* array of the domain names
**						  NOTE: The caller is responsible for freeing this memory.
**	domainCount			- the spelling plugin will return the count of names in the array
**
**	Returns:			- true if successful; domain names if any are listed in the output domainArray.
*/
#define SpellDomainNames (*((SpellDomainNames_SELPROTO)(gSpellerHFT[SpellDomainNames_SEL])))

/*
**	ASBool SpellAddDomain(SpellCheckParamPtr scp)
**
**	Add a spelling domain (search scope) to the Spell Check dialog Search menu.
**
**	Returns:			- true if successful; domain name was added to the menu, false otherwise.
*/
#define SpellAddDomain (*((SpellAddDomain_SELPROTO)(gSpellerHFT[SpellAddDomain_SEL])))

/*
**	ASBool SpellRemoveDomain(SpellCheckParamPtr scp)
**
**	Remove a spelling domain (search scope) from the Spell Check dialog Search menu.
**
**	Returns:			- true if successful; domain name was removed to the menu, false if the domain was not in the menu.
*/
#define SpellRemoveDomain (*((SpellRemoveDomain_SELPROTO)(gSpellerHFT[SpellRemoveDomain_SEL])))


/* ==================================== */
/* === Spelling dictionary handling === */
/* ==================================== */

/*
**	ASBool SpellDictionaryNames(char** dictionaryArray, ASInt32 *dictionaryCount)
**
**	Returns an array of the currently available dictionary names.
**
**	dictionaryArray		- the spelling plugin will allocate and return a char* array of the dictionary names
**						  NOTE: The caller is responsible for freeing this memory.
**	dictionaryCount		- the spelling plugin will return the count of names in the array
**
**	Returns:			- true if successful; dictionary names if any are listed in the output dictionaryArray.
*/
#define SpellDictionaryNames (*((SpellDictionaryNames_SELPROTO)(gSpellerHFT[SpellDictionaryNames_SEL])))

/**	Add Dictionary	*** OBSOLETE *** **/
/*
**	ASBool SpellAddDictionary(char* cName, char *cFile, ASBool bShow)
**
**	*** OBSOLETE ***
**
**	Returns:			- false.
*/
#define SpellAddDictionary (*((SpellAddDictionary_SELPROTO)(gSpellerHFT[SpellAddDictionary_SEL])))

/*
**	ASBool SpellRemoveDictionary(char* cName)
**
**	*** OBSOLETE ***
**
**	Returns:			- false.
*/
#define SpellRemoveDictionary (*((SpellRemoveDictionary_SELPROTO)(gSpellerHFT[SpellRemoveDictionary_SEL])))


/* =========================================== */
/* === Spelling custom dictionary handling === */
/* =========================================== */

/*
**	ASBool SpellCustomDictionaryOpen(ASText astName, ASPathName filePath, ASBool bShow)
**
**	Open a custom dictionary file and add it to the list of available dictionaries.
**
**	astName				- the dictionary name to be used in the spelling dialogs and can be
**						  used as the input parameter to the SpellCheck, SpellCheckText, and SpellCheckWord methods.
**	filePath			- path of the dictionary file.
**	bShow				- when bShow is true, Spelling will combine the cName parameter with "User: " and show
**						  that name in all lists and menus.  For example if cName is "Test", Spelling will
**						  add "User: Test" to all lists and menus.  When bShow is false, Spelling will not show
**						  this custom dictionary in any lists or menus.
**
**	Returns:			- true if successful; the dictionary is now available for use.
*/
#define SpellCustomDictionaryOpen (*((SpellCustomDictionaryOpen_SELPROTO)(gSpellerHFT[SpellCustomDictionaryOpen_SEL])))

/*
**	ASBool SpellCustomDictionaryCreate(ASText astName, ASPathName folderPath, ASBool bShow)
**
**	Create a custom dictionary file and add it to the list of available dictionaries.
**
**	astName				- the dictionary name to be used in the spelling dialogs and can be
**						  used as the input parameter to the SpellCheck, SpellCheckText, and SpellCheckWord methods.
**	astLanguage			- one of the language codes returned by SpellLanguages.
**	bShow				- when bShow is true, Spelling will combine the cName parameter with "User: " and show
**						  that name in all lists and menus.  For example if cName is "Test", Spelling will
**						  add "User: Test" to all lists and menus.  When bShow is false, Spelling will not show
**						  this custom dictionary in any lists or menus.
**
**	Returns:			- true if successful; the dictionary is now available for use.
*/
#define SpellCustomDictionaryCreate (*((SpellCustomDictionaryCreate_SELPROTO)(gSpellerHFT[SpellCustomDictionaryCreate_SEL])))

/*
**	ASBool SpellCustomDictionaryClose(ASText astName)
**
**	This method will remove a custom dictionary that was opened via SpellCustomDictionaryOpen,
**	or created via SpellCustomDictionaryCreate.
**	cName must be the same name as was used with SpellCustomDictionaryOpen or SpellCustomDictionaryCreate.
**
**	astName				- the same dictionary name that was passed to SpellCustomDictionaryOpen or SpellCustomDictionaryCreate.
**
**	Returns:			- true if successful; the dictionary is no longer available for use.
*/
#define SpellCustomDictionaryClose (*((SpellCustomDictionaryClose_SELPROTO)(gSpellerHFT[SpellCustomDictionaryClose_SEL])))

/*
**	ASBool SpellCustomDictionaryDelete(ASText astName)
**
**	This method will delete a custom dictionary that was opened via SpellCustomDictionaryOpen,
**	or created via SpellCustomDictionaryCreate.
**	cName must be the same name as was used with SpellCustomDictionaryOpen or SpellCustomDictionaryCreate.
**	The delete will fail if the user does not have write permission to the dictionary file.
**
**	astName				- the same dictionary name that was passed to SpellCustomDictionaryOpen or SpellCustomDictionaryCreate.
**
**	Returns:			- true if successful; the dictionary is no longer available for use.
*/
#define SpellCustomDictionaryDelete (*((SpellCustomDictionaryDelete_SELPROTO)(gSpellerHFT[SpellCustomDictionaryDelete_SEL])))

/*
**	ASBool SpellCustomDictionaryExport(ASText astName, ASPathName folderPath, void* reserved)
**
**	Export an open custom dictionary file to the specified directory.
**	Export will fail if the user does not have read and write permissions to the dictionary folder.
**
**	astName				- the same dictionary name that was passed to SpellCustomDictionaryOpen or SpellCustomDictionaryCreate.
**	folderPath			- path of the directory where the exported custom dictionary file will be created.
**	reserved			- reserved for future use.
**
**	Returns:			- true if successful; the dictionary has been exported.
*/
#define SpellCustomDictionaryExport (*((SpellCustomDictionaryExport_SELPROTO)(gSpellerHFT[SpellCustomDictionaryExport_SEL])))


/* =================================== */
/* === Spelling Languages handling === */
/* =================================== */

/*
**	ASBool SpellLanguages(char*** languageArrayPtr, ASInt32 *languageCount)
**
**	Returns an array of the currently available dictionaries as an array of ISO 639-2 and 3166 language codes.
**
**	languageArray		- the spelling plugin will allocate and return a char* array of the language codes
**						  NOTE: The caller is responsible for freeing this memory.
**	languageCount		- the spelling plugin will return the count of language codes in the array
**
**	Returns:			- true if successful; language codes if any are listed in the output languageArray.
*/
#define SpellLanguages (*((SpellLanguages_SELPROTO)(gSpellerHFT[SpellLanguages_SEL])))

/*
**	ASBool SpellUserDictionaryOrder(char*** languageArrayPtr, ASInt32 *languageCount)
**
**	Returns the user's dictionary search order from the Spelling Preference Panel as an array of ISO 639-2 and 3166 language codes.
**
**	languageArray		- the spelling plugin will allocate and return a char* array of the language codes.
**						  The order in the list is the dictionary search order from the Spelling Preferences Panel.
**						  NOTE: The caller is responsible for freeing this memory.
**	languageCount		- the spelling plugin will return the count of codes in the array
**
**	Returns:			- true if successful; dictionary search order names are listed in the output languageArray.
*/
#define SpellUserLanguageOrder (*((SpellUserLanguageOrder_SELPROTO)(gSpellerHFT[SpellUserLanguageOrder_SEL])))

/*
**	ASBool SpellGetDocLanguageOrder(AVDoc avd, char*** languageArrayPtr, ASInt32 *languageCount)
**
**	Returns the document search order as an array of ISO 639-2 and 3166 language codes.
**	If this array is NULL then Spelling will use the order defined by the user in the Spelling Preference Panel.
**	Spelling will search the document order first followed by the users' order.
**
**	avd					- The document.
**	languageArray		- the spelling plugin will allocate and return a char* array of the language codes.
**						  The order in the list is the dictionary search order for this document.
**						  NOTE: The caller is responsible for freeing this memory.
**	languageCount		- the spelling plugin will return the count of codes in the array
**
**	Returns:			- true if successful; dictionary search order names are listed in the output languageArray.
*/
#define SpellGetDocLanguageOrder (*((SpellGetDocLanguageOrder_SELPROTO)(gSpellerHFT[SpellGetDocLanguageOrder_SEL])))

/*
**	ASBool SpellSetDocLanguageOrder(AVDoc avd, char** languageArray, ASInt32 languageCount)
**
**	Sets the document search order from an array of ISO 639-2 and 3166 language codes.
**	If this array is NULL then Spelling will use the order defined by the user in the Spelling Preference Panel.
**	Spelling will search the document order first followed by the users' order.
**
**	avd					- The document.
**	languageArray		- This required parameter is a char* array of ordered language codes to be searched
**						  before searching the list specified by the user in Spelling Preferences Panel.
**	languageCount		- number of language codes in the languageArray.
**						  Pass zero to clear the document order list.
**
**	Returns:			- true if successful; the dictionary search order for this document has been set.
*/
#define SpellSetDocLanguageOrder (*((SpellSetDocLanguageOrder_SELPROTO)(gSpellerHFT[SpellSetDocLanguageOrder_SEL])))


/* =================================== */
/* === Spelling user word handling === */
/* =================================== */

/*
**	ASBool SpellUserWords(char* cName, ASBool bAdded, char** wordArray, ASInt32 *wordCount)
**
**	Returns an array of the currently available dictionary names.
**
**	cName				- the dictionary name.  This must be on of the dictionaries from SpellDictionaryNames.
**	bAdded				- if true, the list of added words will be returned.  if false, the removed words list will be returned.
**	wordArray			- the spelling plugin will allocate and return a char* array of the user added/removed words
**						  NOTE: The caller is responsible for freeing this memory.
**	wordCount			- the spelling plugin will return the count of words in the array
**
**	Returns:			- true if successful; the user words if any are listed in the output wordArray.
*/
#define SpellUserWords (*((SpellUserWords_SELPROTO)(gSpellerHFT[SpellUserWords_SEL])))

/*
**	ASBool SpellAddWord(char* cName, char *cWord)
**
**	Add a word to a dictionary.
**
**	cName				- the dictionary name.  An array of the currently installed dictionaries can be
**						  obtained using SpellDictionaryNames.
**	cWord				- the word to be added to the cName dictionary.
**
**	Note:	Internally the Spelling plug-in will scan the user "Not-A-Word" dictionary and remove the word
**			if it is listed there.  Otherwise, the word is added to the user dictionary.
**			The actual dictionary is not modifed.
**
**	Returns:			- true if successful; the dictionary is now available for use.
*/
#define SpellAddWord (*((SpellAddWord_SELPROTO)(gSpellerHFT[SpellAddWord_SEL])))

/*
**	ASBool SpellRemoveWord(char* cName, char *cWord)
**
**	Remove a word from a dictionary.
**
**	cName				- the dictionary name.  An array of the currently installed dictionaries can be
**						  obtained using SpellDictionaryNames.
**	cWord				- the word to be removed to the cName dictionary.
**
**	Note:	Internally the Spelling plug-in will scan the user dictionary and remove the previously added
**			word if it is there.  Otherwise the word will be added to the user’s "Not-A-Word" dictionary.
**			The actual dictionary is not modifed.
**
**	Returns:			- true if successful; the dictionary is now available for use.
*/
#define SpellRemoveWord (*((SpellRemoveWord_SELPROTO)(gSpellerHFT[SpellRemoveWord_SEL])))

/*
**	Ignore a word in a document.
**
**	avd					- The document.
**	cWord				- the word to be ingored.  The input string is PDText which is either a big-endian
**						  Unicode string pre-pended with the bytes 0xFE 0xFF or a string with PDFDocEncoding.
**						  In either case the string is expected to have the appropriate NULL-termination.
**
**	Returns:			- true if successful; the word will be ignored.
*/
#define SpellIgnoreAll (*((SpellIgnoreAll_SELPROTO)(gSpellerHFT[SpellIgnoreAll_SEL])))


/* ======================================== */
/* === Spelling dictionary search order === */
/* ======================================== */

/*
**	ASBool SpellUserDictionaryOrder(char** dictionaryArray, ASInt32 *dictionaryCount)
**
**	Returns the user's dictionary search order from the Spelling Preference Panel.
**
**	dictionaryArray		- the spelling plugin will allocate and return a char* array of the dictionary names.
**						  The order in the list is the dictionary search order from the Spelling Preferences Panel.
**						  NOTE: The caller is responsible for freeing this memory.
**	dictionaryCount		- the spelling plugin will return the count of names in the array
**
**	Returns:			- true if successful; dictionary search order names are listed in the output dictionaryArray.
*/
#define SpellUserDictionaryOrder (*((SpellUserDictionaryOrder_SELPROTO)(gSpellerHFT[SpellUserDictionaryOrder_SEL])))

/*
**	ASBool SpellGetDocDictionaryOrder(AVDoc avd, char** dictionaryArray, ASInt32 *dictionaryCount)
**
**	Returns the document search order if any.  If this array is NULL then Spelling will use the order defined by the user
**	in the Spelling Preference Panel.  Spelling will search the document order first followed by the users' order.
**
**	avd					- The document.
**	dictionaryArray		- the spelling plugin will allocate and return a char* array of the dictionary names.
**						  The order in the list is the dictionary search order for this document.
**						  NOTE: The caller is responsible for freeing this memory.
**	dictionaryCount		- the spelling plugin will return the count of names in the array
**
**	Returns:			- true if successful; dictionary search order names are listed in the output dictionaryArray.
*/
#define SpellGetDocDictionaryOrder (*((SpellGetDocDictionaryOrder_SELPROTO)(gSpellerHFT[SpellGetDocDictionaryOrder_SEL])))

/*
**	ASBool SpellSetDocDictionaryOrder(AVDoc avd, char** dictionaryArray, ASInt32 dictionaryCount)
**
**	Sets the document search order.  If this array is NULL then Spelling will use the order defined by the user
**	in the Spelling Preference Panel.  Spelling will search the document order first followed by the users' order.
**
**	avd					- The document.
**	dictionaryArray		- This required parameter is a char* array of ordered dictionary names to be searched
**						  before searching the list specified by the user in Spelling Preferences Panel.
**	dictionaryCount		- number of dictionaries in the dictionaryArray.
**						  Pass zero to clear the document order list.
**
**	Returns:			- true if successful; the dictionary search order for this document has been set.
*/
#define SpellSetDocDictionaryOrder (*((SpellSetDocDictionaryOrder_SELPROTO)(gSpellerHFT[SpellSetDocDictionaryOrder_SEL])))

/**	Call the Spelling plug-in to have it hyphenate a word.

 	<p>Sets the document search order.  If this array is <code>NULL</code>, Spelling will use the order defined by the user
 	in the Spelling Preferences panel.  Spelling will search the document order first followed by the users' order.</p>
	
	@example
		<p><code>HyphenationRecordPtr hyphenArray = NULL; </code></p>
		<p><code>ASInt32 nHyphenations = SpellHyphenateWord(avd, cWord, <code>NULL</code>, 0, &hyphenArray); </code></p>
		<p><code>for (ASInt32 nIndex = 0; nIndex < nHyphenations; nIndex++) { </code></p>
		<p><code>	HyphenationRecordPtr pHyphenRecord = hyphenArray[nIndex]; </code></p>
		<p><code>	if (pHyphenRecord->eType == kHyphenType_preferred) { </code></p>
		<p><code>		char* cLeft = ASTextGetEncodedCopy(pHyphenRecord->astLeft, ASHostEncoding(PDGetHostEncoding())); </code></p>
		<p><code>		char* cRight = ASTextGetEncodedCopy(pHyphenRecord->astRight, ASHostEncoding(PDGetHostEncoding())); </code></p>
		<p><code>	} </code></p>
		<p><code>}	//  don't forget to free cLeft, cRight, each element of hyphenArray and the hyphenArray itself. </code></p>
		

 	@param avd IN The document.
	@param astWord IN ASText containing the word to be hyphenated.
 	@param dictionaryArray IN An optional array of dictionary names to be used for hyphenation.
 						  When provided, this dictionary list overrides the default dictionary list for this document.
 						  Use SpellDictionaryNames() to obtain a list of the currently available dictionaries.
 						  The dictionary names are PDText which is either a big-endian Unicode string prepended with the
 						  bytes <code>0xFE 0xFF</code>, or a string with PDFDocEncoding.  In either case the
 						  string is expected to have the appropriate <code>NULL</code>-termination.
 	@param dictionaryCount	IN A count of dictionary names in <code>dictionaryArray</code>
 	@param hyphenationArrayPtr IN An optional pointer for an an arrray of HyphenationRecord pointers, if any.
 						  Note that the caller is responsible for freeing this memory.
 
 	@return The count of hyphenations for this word.

	
#define SpellHyphenateWord (*((SpellHyphenateWord_SELPROTO)(gSpellerHFT[SpellHyphenateWord_SEL])))
*/

#if __cplusplus
}
#endif	/* __cplusplus */

#endif	/* _H_SpellerHFT */
