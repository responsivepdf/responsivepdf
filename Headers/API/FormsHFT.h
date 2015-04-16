/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1996-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 FormsHFT.h

 - HFT definitions for Acrobat Form Plugin

*********************************************************************/

#ifndef _H_FormsHFT
#define _H_FormsHFT

/*****************************************************************************
  Selectors and types for all AcroForm HFT functions
*****************************************************************************/
#include "AF_Sel.h"
#include "AF_ExpT.h"

#if __cplusplus
extern "C" {
#endif	/* __cplusplus */

extern HFT gAcroFormHFT;

#if __cplusplus
}
#endif	/* __cplusplus */


#define Init_AcroFormHFT ASExtensionMgrGetHFT(ASAtomFromString(AcroFormHFT_NAME), AcroFormHFT_LATEST_VERSION)

/* this is provided as a service to plug-ins which had previously used
   the AcroForms HFT.  The AF (AcroForms) prefix will need to be
   present in future versions using the AcroForms HFT structures. */
#if AF_HFT_COMPATIBILE
#define PDDocLoadPDFields AFPDDocLoadPDFields
#define PDDocEnumPDFields AFPDDocEnumPDFields
#define PDDocGetPDFieldFromName AFPDDocGetPDFieldFromName
#define PDFieldFromCosObj AFPDFieldFromCosObj
#define PDFieldGetCosObj AFPDFieldGetCosObj
#define PDFieldIsValid AFPDFieldIsValid
#define PDFieldIsTerminal AFPDFieldIsTerminal
#define PDFieldGetValue AFPDFieldGetValue
#define PDFieldGetFlags AFPDFieldGetFlags
#define PDFieldGetName AFPDFieldGetName
#define PDFieldIsAnnot AFPDFieldIsAnnot
#define PDFieldSetValue AFPDFieldSetValue
#define PDFieldSetFlags AFPDFieldSetFlags
#define PDFieldSetOptions AFPDFieldSetOptions
#define PDFieldReset AFPDFieldReset
#endif /* AF_HFT_COMPATIBILE */



/* The following APIs are NOT availabe in Reader configuration */
#if !READER_PLUGIN
#define ExportAsFDF (*((ExportAsFDF_SELPROTO)(gAcroFormHFT[ExportAsFDF_SEL])))
#define ExportAsHtml (*((ExportAsHtml_SELPROTO)(gAcroFormHFT[ExportAsHtml_SEL])))
#define ImportAnFDF (*((ImportAnFDF_SELPROTO)(gAcroFormHFT[ImportAnFDF_SEL])))

#define ExportAsFDFEx (*((ExportAsFDFEx_SELPROTO)(gAcroFormHFT[ExportAsFDFEx_SEL])))
#define ExportAsHtmlEx (*((ExportAsHtmlEx_SELPROTO)(gAcroFormHFT[ExportAsHtmlEx_SEL])))
#define AssembleFormAndImportFDF (*((AssembleFormAndImportFDF_SELPROTO)(gAcroFormHFT[AssembleFormAndImportFDF_SEL])))
#define ExportAsFDFWithParams (*((ExportAsFDFWithParams_SELPROTO)(gAcroFormHFT[ExportAsFDFWithParams_SEL])))
#define AFPDFormFromPage (*((AFPDFormFromPage_SELPROTO)(gAcroFormHFT[AFPDFormFromPage_SEL])))
#define AFLayoutNew (*((AFLayoutNew_SELPROTO)(gAcroFormHFT[AFLayoutNew_SEL])))
#define AFLayoutDelete (*((AFLayoutDelete_SELPROTO)(gAcroFormHFT[AFLayoutDelete_SEL])))

/* AFLayoutCreateStream has been revved */
#define AFLayoutCreateStream (*((AFLayoutCreateStream_SELPROTO)(gAcroFormHFT[AFLayoutCreateStream_SEL])))
#define AFLayoutBorder (*((AFLayoutBorder_SELPROTO)(gAcroFormHFT[AFLayoutBorder_SEL])))
#define AFLayoutText (*((AFLayoutText_SELPROTO)(gAcroFormHFT[AFLayoutText_SEL])))
#define AFLayoutTextEx (*((AFLayoutTextEx_SELPROTO)(gAcroFormHFT[AFLayoutTextEx_SEL])))
#define AFLayoutIconText (*((AFLayoutIconText_SELPROTO)(gAcroFormHFT[AFLayoutIconText_SEL])))
#define AFImportAppearance (*((AFImportAppearance_SELPROTO)(gAcroFormHFT[AFImportAppearance_SEL])))
#define AFDrawText (*((AFDrawText_SELPROTO)(gAcroFormHFT[AFDrawText_SEL])))

#endif

/* The following APIs are availabe in Reader configuration */

#define IsPDDocAcroForm (*((IsPDDocAcroForm_SELPROTO)(gAcroFormHFT[IsPDDocAcroForm_SEL])))
#define AFPDDocLoadPDFields (*((AFPDDocLoadPDFields_SELPROTO)(gAcroFormHFT[AFPDDocLoadPDFields_SEL])))
#define AFPDDocEnumPDFields (*((AFPDDocEnumPDFields_SELPROTO)(gAcroFormHFT[AFPDDocEnumPDFields_SEL])))
#define AFPDDocGetPDFieldFromName (*((AFPDDocGetPDFieldFromName_SELPROTO)(gAcroFormHFT[AFPDDocGetPDFieldFromName_SEL])))
#define AFPDFieldFromCosObj (*((AFPDFieldFromCosObj_SELPROTO)(gAcroFormHFT[AFPDFieldFromCosObj_SEL])))
#define AFPDFieldGetCosObj (*((AFPDFieldGetCosObj_SELPROTO)(gAcroFormHFT[AFPDFieldGetCosObj_SEL])))
#define AFPDFieldIsValid (*((AFPDFieldIsValid_SELPROTO)(gAcroFormHFT[AFPDFieldIsValid_SEL])))
#define AFPDFieldIsTerminal (*((AFPDFieldIsTerminal_SELPROTO)(gAcroFormHFT[AFPDFieldIsTerminal_SEL])))
#define AFPDFieldGetValue (*((AFPDFieldGetValue_SELPROTO)(gAcroFormHFT[AFPDFieldGetValue_SEL])))
#define AFPDFieldGetFlags (*((AFPDFieldGetFlags_SELPROTO)(gAcroFormHFT[AFPDFieldGetFlags_SEL])))
#define AFPDFieldGetName (*((AFPDFieldGetName_SELPROTO)(gAcroFormHFT[AFPDFieldGetName_SEL])))
#define AFPDFieldIsAnnot (*((AFPDFieldIsAnnot_SELPROTO)(gAcroFormHFT[AFPDFieldIsAnnot_SEL])))
#define AFPDFieldSetValue (*((AFPDFieldSetValue_SELPROTO)(gAcroFormHFT[AFPDFieldSetValue_SEL])))
#define AFPDFieldSetFlags (*((AFPDFieldSetFlags_SELPROTO)(gAcroFormHFT[AFPDFieldSetFlags_SEL])))
#define AFPDFieldSetOptions (*((AFPDFieldSetOptions_SELPROTO)(gAcroFormHFT[AFPDFieldSetOptions_SEL])))
#define AFPDFieldReset (*((AFPDFieldReset_SELPROTO)(gAcroFormHFT[AFPDFieldReset_SEL])))

/* Not in Reader -  ExportAsFDF */
/* Not in Reader -  ExportAsHtml */
/* Not in Reader -  ImportAnFDF */

#define ResetForm (*((ResetForm_SELPROTO)(gAcroFormHFT[ResetForm_SEL])))
#define AcroFormRegisterObserver (*((AcroFormRegisterObserver_SELPROTO)(gAcroFormHFT[AcroFormRegisterObserver_SEL])))
#define AcroFormUnregisterObserver (*((AcroFormUnregisterObserver_SELPROTO)(gAcroFormHFT[AcroFormUnregisterObserver_SEL])))
#define AFGetScriptingContext (*((AFGetScriptingContext_SELPROTO)(gAcroFormHFT[AFGetScriptingContext_SEL])))
/* Not in Reader -  ExportAsFDFEx */
/* Not in Reader -  ExportAsHtmlEx */
/* Not in Reader -  AssembleFormAndImportFDF */
/* Not in Reader -  ExportAsFDFWithParams */
/* Not in Reader -  AFPDFormFromPage */

/* AFLayoutNew has been revved */
#define AFLayoutNew (*((AFLayoutNew_SELPROTO)(gAcroFormHFT[AFLayoutNew_SEL])))
#define AFLayoutDelete (*((AFLayoutDelete_SELPROTO)(gAcroFormHFT[AFLayoutDelete_SEL])))

/* AFLayoutCreateStream has been revved */
/* Not in Reader -  AFLayoutCreateStream */
/* Not in Reader -  AFLayoutBorder */
/* Not in Reader -  AFLayoutText */
/* Not in Reader -  AFLayoutTextEx */
/* Not in Reader -  AFLayoutIconText */
#define AFPDFieldValueChanged (*((AFPDFieldValueChanged_SELPROTO)(gAcroFormHFT[AFPDFieldValueChanged_SEL])))
#define AFPDWidgetGetRotation (*((AFPDWidgetGetRotation_SELPROTO)(gAcroFormHFT[AFPDWidgetGetRotation_SEL])))
#define AFPDFieldGetDefaultTextAppearance (*((AFPDFieldGetDefaultTextAppearance_SELPROTO)(gAcroFormHFT[AFPDFieldGetDefaultTextAppearance_SEL])))
#define AFPDFieldSetDefaultTextAppearance (*((AFPDFieldSetDefaultTextAppearance_SELPROTO)(gAcroFormHFT[AFPDFieldSetDefaultTextAppearance_SEL])))
/* AFPDFieldGetDefaultTextAppearanceEx and AFPDFieldSetDefaultTextAppearanceEx new in Acrobat 7.0 */
#define AFPDFieldGetDefaultTextAppearanceEx (*((AFPDFieldGetDefaultTextAppearanceEx_SELPROTO)(gAcroFormHFT[AFPDFieldGetDefaultTextAppearanceEx_SEL])))
#define AFPDFieldSetDefaultTextAppearanceEx (*((AFPDFieldSetDefaultTextAppearanceEx_SELPROTO)(gAcroFormHFT[AFPDFieldSetDefaultTextAppearanceEx_SEL])))
#define AFPDWidgetGetBorder (*((AFPDWidgetGetBorder_SELPROTO)(gAcroFormHFT[AFPDWidgetGetBorder_SEL])))
#define AFPDWidgetSetBorder (*((AFPDWidgetSetBorder_SELPROTO)(gAcroFormHFT[AFPDWidgetSetBorder_SEL])))
#define AFPDWidgetGetAreaColors (*((AFPDWidgetGetAreaColors_SELPROTO)(gAcroFormHFT[AFPDWidgetGetAreaColors_SEL])))
#define AFPDWidgetSetAreaColors (*((AFPDWidgetSetAreaColors_SELPROTO)(gAcroFormHFT[AFPDWidgetSetAreaColors_SEL])))

/* Not in Reader -  AFImportAppearance */
/* Not in Reader -  AFImportAppearanceEx */
#define AFGetScriptingContextEx (*((AFGetScriptingContextEx_SELPROTO)(gAcroFormHFT[AFGetScriptingContextEx_SEL])))
#define AFExecuteThisScript (*((AFExecuteThisScript_SELPROTO)(gAcroFormHFT[AFExecuteThisScript_SEL])))
#define AFCalculateFields (*((AFCalculateFields_SELPROTO)(gAcroFormHFT[AFCalculateFields_SEL])))
#define AFGetDefaultFieldSize (*((AFGetDefaultFieldSize_SELPROTO)(gAcroFormHFT[AFGetDefaultFieldSize_SEL])))

#endif
