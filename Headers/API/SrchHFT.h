/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1994-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 SrchHFT.h

 - Catalog of functions exported by Acrobat Search.

*********************************************************************/

#ifndef _H_SrchHFT
#define _H_SrchHFT

#include "SrchType.h"

/* Extension name : "Search" */

#define SearchHFT_NAME		"Search"
#define SearchHFT_LATEST_VERSION		(0L)

#define Init_SearchHFT ASExtensionMgrGetHFT(ASAtomFromString(SearchHFT_NAME), SearchHFT_LATEST_VERSION)

/* Enumerate the selectors */
#define PIPROC(returnType, name, params, ...)	name##_SEL,

typedef enum _SearchSelector {
	SearchBAD_SELECTOR,
	#include "SrchPrcs.h"
	SearchNUMSELECTORSplusOne
} SearchSelector;

#undef PIPROC

#define SearchNUMSELECTORS (SearchNUMSELECTORSplusOne - 1)


/* Define API/Function prototypes
*/
#define PIPROC(returnType, name, params, ...)	typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params; 
#include "SrchPrcs.h"
#undef PIPROC

extern HFT gSearchHFT;
extern ASBool SetUpSearchHFTServer(void);
#endif

