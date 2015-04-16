/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 2000-2003 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 PIHeaders.h

 - A general include file for Acrobat Headers. This file is included
   in the Macintosh precompiled header file "PIHeaders.pch".

*********************************************************************/
#ifndef _H_PIHEADERS
#define _H_PIHEADERS

#define NEW_PDFEDIT_HFTS 1
#define NEW_PDSEDIT_HFTS 1
#define PDMETADATA_HFT 1

#ifdef WIN_PLATFORM
#include "WinPIHeaders.h"
#endif
#ifdef MAC_PLATFORM
#include "MacPIHeaders.h"
#include "SafeResources.h"
#endif
#ifdef UNIX_PLATFORM
#include "UnixPIHeaders.h"
#endif

/* Pointer-integer conversion */
/* if the size of a pointer is not 32 bits,
 * then ASIntPtrSize is defined (in Environ.h) */
#ifdef ASIntPtrSize
#define ASPtrToInt32(_p) ((ASInt32)(ASIntPtrSize)(_p))
#define ASInt32ToPtr(_i) ((void*)(ASIntPtrSize)(_i))
#else
#define ASIntPtrSize ASInt32
#define ASPtrToInt32(_p) ((ASInt32)(_p))
#define ASInt32ToPtr(_i) ((void*)(_i))
#endif

#define ASPtrToInt(_p) ((ASIntPtrSize)(_p))
#define ASPtrToBool(_p) ((ASBool)ASPtrToInt(_p))
/* *********************** */

#include "PIExcept.h"
#include "Environ.h"
#if PLUGIN
#include "ASExpT.h"
#include "CoreExpT.h"
#endif
#include "AcroColorCalls.h"
#include "ASCalls.h"
#include "ASExtraCalls.h"
#include "AVCalls.h"
#include "CorCalls.h"
#include "CosCalls.h"
#include "DigSigHFT.h"
#include "FormsHFT.h"
#include "PagePDECntCalls.h"
#include "PDCalls.h"
#include "PDMetadataCalls.h"
#include "PDSReadCalls.h"
#include "PDSWriteCalls.h"
#include "PERCalls.h"
#include "PEWCalls.h"
#include "PSFCalls.h"
#include "SpellerHFT.h"
#include "SrchHFT.h"
#ifndef UNIX_PLATFORM
#include "TtsHFT.h"
#endif
#include "WLHFT.h"
#ifndef UNIX_PLATFORM
#include "CatHFT.h"
#endif
#include "ConsHFT.h"


// Acrobat 6.0 Headers
#include "AcroColorCalls.h"
#include "ASKey.h"
#include "CAVAlert.h"
#include "PSFCalls.h"
#include "PubSecHFT.h"

#ifdef WIN_PLATFORM
#include "WinCalls.h"
#endif
#ifdef MAC_PLATFORM
#include "MacCalls.h"
#endif



#ifdef UNIX_PLATFORM
#include "UnixCalls.h"
#endif

#endif
