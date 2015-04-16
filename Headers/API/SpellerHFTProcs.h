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

/*	Init_SpellingHFT
**	Use this to initialize and make the Spelling HFT functions available to your plug-in. 
*/
#if !defined(Init_SpellerHFT)
#define Init_SpellerHFT ASExtensionMgrGetHFT(ASAtomFromString(SpellerHFT_NAME), SpellerHFT_LATEST_VERSION)
#endif

/* =============================== */
/* === Spelling check services === */
/* =============================== */

PIPROC(char*, SpellCheck, (AVDoc avd, const char* textBuffer, ASInt16* dialogResult, ASBool bReserved, char** dictionaryArray, ASInt32 dictionaryCount), avd, textBuffer, dialogResult, bReserved, dictionaryArray, dictionaryCount)
PIPROC(ASBool, SpellCheckText,(AVDoc avd, const char* textBuffer, ASUns32* startOffset, ASUns32* endOffset, char** dictionaryArray, ASInt32 dictionaryCount),avd, textBuffer, startOffset, endOffset, dictionaryArray, dictionaryCount)
PIPROC(ASBool, SpellCheckWord, (AVDoc avd, const char* cWord, char** dictionaryArray, ASInt32 dictionaryCount, char*** alternativeArrayPtr, ASInt32 *alternativeCount), avd, cWord, dictionaryArray, dictionaryCount, alternativeArrayPtr, alternativeCount)

PIPROC(ASBool, SpellDomainNames, (char*** domainArrayPtr, ASInt32 *domainCount), domainArrayPtr, domainCount)
PIPROC(ASBool, SpellAddDomain, (SpellCheckParamPtr scp), scp)
PIPROC(ASBool, SpellRemoveDomain, (SpellCheckParamPtr scp), scp)

PIPROC(ASBool, SpellDictionaryNames, (char*** dictionaryArrayPtr, ASInt32 *dictionaryCount), dictionaryArrayPtr, dictionaryCount)
PIPROC(ASBool, SpellAddDictionary, (char* cName, char *cFile, ASBool bShow), cName, cFile, bShow)
PIPROC(ASBool, SpellRemoveDictionary, (char* cName), cName)

PIPROC(ASBool, SpellUserWords, (ASBool bAdded, char*** wordArrayPtr, ASInt32 *wordCount), bAdded, wordArrayPtr, wordCount)
PIPROC(ASBool, SpellAddWord, (char *cWord), cWord)
PIPROC(ASBool, SpellRemoveWord, (char *cWord), cWord)

PIPROC(ASBool, SpellUserDictionaryOrder, (char*** dictionaryArrayPtr, ASInt32 *dictionaryCount), dictionaryArrayPtr, dictionaryCount)
PIPROC(ASBool, SpellGetDocDictionaryOrder, (AVDoc avd, char*** dictionaryArrayPtr, ASInt32 *dictionaryCount), avd, dictionaryArrayPtr, dictionaryCount)
PIPROC(ASBool, SpellSetDocDictionaryOrder, (AVDoc avd, char** dictionaryArray, ASInt32 dictionaryCount), avd, dictionaryArray, dictionaryCount)

PIPROC(ASInt32, SpellCountKnownWords, (const char* textBuffer, ASInt32 dictionaryCount, char** dictionaryArray, ASInt32* counterArray), textBuffer, dictionaryCount, dictionaryArray, counterArray)

PIPROC(ASBool, SpellIgnoreAll, (AVDoc avd, char *cWord), avd, cWord)

PIPROC(ASInt32, SpellHyphenateWord,	(AVDoc avd, const ASText astWord, char** dictionaryArray, ASInt32 dictionaryCount, HyphenationRecordPtr* hyphenationArrayPtr), avd, astWord, dictionaryArray, dictionaryCount, hyphenationArrayPtr)

PIPROC(ASText, SpellGetNextWord, (ASConstText inBuffer, ASInt32* nStart, ASInt32* nEnd, ASBool bFilter), inBuffer, nStart, nEnd, bFilter)

PIPROC(ASInt32, SpellCheckRTF, (AVDoc avd, void* vReserved, ASText astPlainText, char** dictionaryArray, ASInt32 dictionaryCount, SCRTFChangeProc pRTFchangeProc, void* vClientData),avd, vReserved, astPlainText, dictionaryArray, dictionaryCount, pRTFchangeProc, vClientData)

PIPROC(ASBool, SpellLanguages, (char*** languageArrayPtr, ASInt32 *languageCount), languageArrayPtr, languageCount)
PIPROC(ASBool, SpellUserLanguageOrder, (char*** languageArrayPtr, ASInt32 *languageCount), languageArrayPtr, languageCount)
PIPROC(ASBool, SpellGetDocLanguageOrder, (AVDoc avd, char*** languageArrayPtr, ASInt32 *languageCount), avd, languageArrayPtr, languageCount)
PIPROC(ASBool, SpellSetDocLanguageOrder, (AVDoc avd, char** languageArray, ASInt32 languageCount), avd, languageArray, languageCount)

PIPROC(ASBool, SpellCustomDictionaryClose, (ASText astName), astName)
PIPROC(ASBool, SpellCustomDictionaryCreate, (ASText astName, ASText astLanguage, ASBool bShow), astName, astLanguage, bShow)
PIPROC(ASBool, SpellCustomDictionaryDelete, (ASText astName), astName)
PIPROC(ASBool, SpellCustomDictionaryExport,(ASText astName, ASPathName folderPath, void* reserved), astName, folderPath, reserved)
PIPROC(ASBool, SpellCustomDictionaryOpen, (ASText astName, ASPathName filePath, ASBool bShow), astName, filePath, bShow)


