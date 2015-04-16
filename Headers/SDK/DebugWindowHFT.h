/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1994-2003 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 DebugWindow.h

 - Catalog of functions exported by the SnippetRunner plug-in.

*********************************************************************/

#ifndef _H_DEBUGWINDOWHFT
#define _H_DEBUGWINDOWHFT

enum
{
	DebugWindowBAD_SELECTOR,
	DebugEmitStringSEL,
	DebugWindowNUMSELECTORSPlusOne
};

extern HFT gDebugWindowHFT;

#define DebugWindowNUMSELECTORS (DebugWindowNUMSELECTORSPlusOne - 1)

#define DebugWindowHFT_NAME "ADBE:DebugWindow"
#define DebugWindowHFT_LATEST_VERSION (0x00000002)
#define InitDebugWindowHFT ASExtensionMgrGetHFT (ASAtomFromString(DebugWindowHFT_NAME), DebugWindowHFT_LATEST_VERSION)

/* DebugEmitString
** Emits a string to the CommonInterface window.
** Strings with %% at start are treated as unicode (UCS-16)
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DebugEmitStringSELPROTO)(const char *msg);
#define DebugEmitString (*((DebugEmitStringSELPROTO)(gDebugWindowHFT[DebugEmitStringSEL])))

#endif
