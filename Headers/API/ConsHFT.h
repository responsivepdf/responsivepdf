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

 ConsHFT.h

 - Catalog of functions exported by PDF Consultant.

*********************************************************************/

#ifndef __CONSHFT_H__
#define __CONSHFT_H__


#include "ConsExpT.h"
//#include "ASCalls.h"

//#include "CoreExpT.h"
//#include "PDExpT.h"
#include "ASExpT.h"
#include "AVExpT.h"


/* ****************************** HFT Stuff ************************************** */
#ifdef __cplusplus
extern "C"
{
#endif

extern HFT gConsultantHFT;

#define PDFCONSULTANT_HFT_NAME		"PDFConsultant"
#define PDFCONSULTANT_REAL_HFT_NAME	("$"PDFCONSULTANT_HFT_NAME)
#define PDFCONSULTANT_HFT_VER_1		0x00010000
#define PDFCONSULTANT_HFT_VER_2		0x00020000
#define PDFCONSULTANT_HFT_VER_3		0x00030000
#define PDFCONSULTANT_HFT_LATEST	PDFCONSULTANT_HFT_VER_3

#define Init_PDFConsultantHFT ASExtensionMgrGetHFT( ASAtomFromString( PDFCONSULTANT_HFT_NAME ), PDFCONSULTANT_HFT_LATEST )


#if PDFCONSULTANT_HFT_LATEST != 0


// ------------ Create the enum ---------------
#define PIPROC(returnType, name, params, ...) name##_SEL,
enum
{
	ConsultantBAD_SELECTOR = 0,
	#include "ConsHFTProcs.h"
	ConsultantNUMSELECTORSPlusOne
};
#undef PIPROC

#define ConsultantNUMSELECTORS ( ConsultantNUMSELECTORSPlusOne - 1 )


// ------------ Create the Prototypes ---------------
#define PIPROC(returnType, name, params, ...) typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##_SELPROTO)params;
	#include "ConsHFTProcs.h"
#undef PIPROC

#define ConsultantCreate ( *( ( ConsultantCreate_SELPROTO )( gConsultantHFT[ ConsultantCreate_SEL ] ) ) )
#define ConsultantDestroy ( *( ( ConsultantDestroy_SELPROTO )( gConsultantHFT[ ConsultantDestroy_SEL ] ) ) )
#define ConsultantTraverseFrom ( *( ( ConsultantTraverseFrom_SELPROTO )( gConsultantHFT[ ConsultantTraverseFrom_SEL ] ) ) )
#define ConsultantSuspend ( *( ( ConsultantSuspend_SELPROTO )( gConsultantHFT[ ConsultantSuspend_SEL ] ) ) )
#define ConsultantResume ( *( ( ConsultantResume_SELPROTO )( gConsultantHFT[ ConsultantResume_SEL ] ) ) )
#define ConsultantRegisterAgent ( *( ( ConsultantRegisterAgent_SELPROTO )( gConsultantHFT[ ConsultantRegisterAgent_SEL ] ) ) )
#define ConsultantSetStart ( *( ( ConsultantSetStart_SELPROTO )( gConsultantHFT[ ConsultantSetStart_SEL ] ) ) )
#define ConsultantNextObj ( *( ( ConsultantNextObj_SELPROTO )( gConsultantHFT[ ConsultantNextObj_SEL ] ) ) )
#define ConsultantGetPercentDone ( *( ( ConsultantGetPercentDone_SELPROTO )( gConsultantHFT[ ConsultantGetPercentDone_SEL ] ) ) )
#define ConsultantGetNumDirectVisited ( *( ( ConsultantGetNumDirectVisited_SELPROTO )( gConsultantHFT[ ConsultantGetNumDirectVisited_SEL ] ) ) )
#define ConsultantGetNumIndirectVisited ( *( ( ConsultantGetNumIndirectVisited_SELPROTO )( gConsultantHFT[ ConsultantGetNumIndirectVisited_SEL ] ) ) )
#define ConsultantGetNumUniqueIndirectsVisited ( *( ( ConsultantGetNumUniqueIndirectsVisited_SELPROTO )( gConsultantHFT[ ConsultantGetNumUniqueIndirectsVisited_SEL ] ) ) )
#define ConsStackGetCount ( *( ( ConsStackGetCount_SELPROTO )( gConsultantHFT[ ConsStackGetCount_SEL ] ) ) )
#define ConsStackIndexGetTypeCount ( *( ( ConsStackIndexGetTypeCount_SELPROTO )( gConsultantHFT[ ConsStackIndexGetTypeCount_SEL ] ) ) )
#define ConsStackIndexGetTypeAt ( *( ( ConsStackIndexGetTypeAt_SELPROTO )( gConsultantHFT[ ConsStackIndexGetTypeAt_SEL ] ) ) )
#define ConsStackIndexGetObj ( *( ( ConsStackIndexGetObj_SELPROTO )( gConsultantHFT[ ConsStackIndexGetObj_SEL ] ) ) )
#define ConsStackIndexIsDict ( *( ( ConsStackIndexIsDict_SELPROTO )( gConsultantHFT[ ConsStackIndexIsDict_SEL ] ) ) )
#define ConsStackIndexIsArray ( *( ( ConsStackIndexIsArray_SELPROTO )( gConsultantHFT[ ConsStackIndexIsArray_SEL ] ) ) )
#define ConsStackIndexGetDictKey ( *( ( ConsStackIndexGetDictKey_SELPROTO )( gConsultantHFT[ ConsStackIndexGetDictKey_SEL ] ) ) )
#define ConsStackIndexGetArrayIndex ( *( ( ConsStackIndexGetArrayIndex_SELPROTO )( gConsultantHFT[ ConsStackIndexGetArrayIndex_SEL ] ) ) )
#define PDFObjTypeGetSuperclass ( *( ( PDFObjTypeGetSuperclass_SELPROTO )( gConsultantHFT[ PDFObjTypeGetSuperclass_SEL ] ) ) )
// Version 3
#define ConsultantNeverVisitObj ( *( ( ConsultantNeverVisitObj_SELPROTO )( gConsultantHFT[ ConsultantNeverVisitObj_SEL ] ) ) )

#endif /* PDFCONSULTANT_HFT_LATEST != 0 */

#ifdef __cplusplus
}
#endif

#endif /* __CONSHFT_H__ */
