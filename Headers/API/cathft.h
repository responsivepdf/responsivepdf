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

 CatHFT.h

 - Catalog of functions exported by Acrobat Catalog.

*********************************************************************/

#ifndef _H_CatHFT
#define _H_CatHFT

#define CatalogHFT_NAME			"Catalog"
#define CatalogRealHFT_NAME		("$"CatalogHFT_NAME)
#define CatalogHFT_LATEST_VERSION		(0L)
#define CatalogHFT_Error 1

#define Init_CatalogHFT ASExtensionMgrGetHFT(ASAtomFromString(CatalogHFT_NAME), CatalogHFT_LATEST_VERSION)

/* Extension name : "Catalog"*/

/* Enumerate the selectors */
#define PIPROC(returnType, name, params, ...) name##_SEL,
enum {
	CatalogBAD_SELECTOR,
	#include "catprocs.h"
	CatalogNUMSELECTORSplusOne
};
#undef PIPROC


/**
	Return values for the current state of Catalog.
	If Catalog is currently busy performing some operation, it returns the relevant 
	state, which could be <code>CatalogBuilding</code>, <code>CatalogPurging</code>, or <code>CatalogWaiting</code>.
*/
typedef enum
{
/** */
CatalogIdle = 0,
/** */
CatalogBuilding,
/** */
CatalogPurging,
/** */
CatalogWaiting
}
CatalogStatus;

/**
	Return values for the current state of the Index after a call to Purge, Build, or Load an index. 
*/
typedef enum
{
/** Input path is not correct, or Catalog was not able to load the index. */
	IndexInvalid = 0,
/** Catalog was unable to save the index at the given path. */
	IndexCouldNotBeSaved,
/** The build operation was valid and was completed. */
	IndexBuildDone,
/** The purge operation was valid and was completed. */
	IndexPurgeDone,
/** The index was loaded successfully. */
	IndexLoadDone,
/** Catalog is currently busy and could not process the request. */
	CatalogBusy,
/** */
	IndexJobAdded
} IndexStatus;


#define CatalogNUMSELECTORS (CatalogNUMSELECTORSplusOne - 1)

extern HFT gCatalogHFT;
extern ASBool SetUpCatalogHFTServer(void);

// ------------ Create the Prototypes ---------------
#define PIPROC(returnType, name, params, ...) typedef ACCBPROTO1 returnType (ACCBPROTO2 name##_PROTO)params;	
#include "catprocs.h"
#undef PIPROC

#define PIPROC(returnType, name, params, ...) typedef name##_PROTO *name##_SELPROTO;	
#include "catprocs.h"
#undef PIPROC

#define CatalogActivate	(*((CatalogActivate_SELPROTO)(gCatalogHFT[CatalogActivate_SEL])))
#define CatalogLoadIndex (*((CatalogLoadIndex_SELPROTO)(gCatalogHFT[CatalogLoadIndex_SEL])))
#define CatalogBuildIndex (*((CatalogBuildIndex_SELPROTO)(gCatalogHFT[CatalogBuildIndex_SEL])))
#define CatalogPurgeIndex (*((CatalogPurgeIndex_SELPROTO)(gCatalogHFT[CatalogPurgeIndex_SEL])))
#define CatalogGiveStatus (*((CatalogGiveStatus_SELPROTO)(gCatalogHFT[CatalogGiveStatus_SEL])))


#endif

