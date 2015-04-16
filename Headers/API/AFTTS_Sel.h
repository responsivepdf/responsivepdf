/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1998-2008 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 AFTTS_Sel.h

 - Selectors for all AcroTTS HFT functions.

*********************************************************************/

#ifndef _H_AFTTS_SEL
#define _H_AFTTS_SEL


/** Notification callback for TTS routines.
	@see AFTTSSetNotify
*/
typedef ACCB1 void (ACCB2 AFTTSNotifyProc)();


/* For creating selector (index to HFT) 
*/
#define PIPROC(returnType, name, params, ...)	name##_SEL,

enum 
{ 
	AcroTTSFirst_SEL = 0,
#include "TTSHFTProcs.h"
	AcroTTSLast_SEL 
};
#undef PIPROC

#define AcroTTSNum_SEL  AcroTTSLast_SEL - 1
#define AcroTTSHFT_NAME "TTS"
#define AcroTTSHFT_LATEST_VERSION (0x00010012)

/* Define API/Function prototypes
*/
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
#include "TTSHFTProcs.h"
#undef PIPROC

#endif /* _H_AFTTS_SEL  } */
