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

 AF_Sel.h

 - Selectors for all AcroForm HFT functions.

*********************************************************************/

#ifndef _H_AF_SEL
#define _H_AF_SEL

#include "AF_ExpT.h"

/* For creating selector (index to HFT) 
*/
#define PIPROC(returnType, name, params, ...)	name##_SEL,
#define NOPROC(name)	name##_SEL,

enum
{
	AcroFormFirst_SEL  = 0,
#include "FormsHFTProcs.h"
	AcroFormLast_SEL
};
#undef PIPROC
#undef NOPROC


#define AcroFormNum_SEL  AcroFormLast_SEL - 1
#define AcroFormHFT_NAME "Forms"
#define AcroFormHFT_LATEST_VERSION (0x00010002)

/* Define API/Function prototypes
*/
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
#define NOPROC(name)
#include "FormsHFTProcs.h"
#undef PIPROC
#undef NOPROC


#endif /* _H_AF_SEL  } */
