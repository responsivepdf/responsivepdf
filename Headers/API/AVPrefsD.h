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

 AVPrefsD.h

 - Defines AV_PREFERENCES, the list of AVAppPreferences.

*********************************************************************/

#ifndef AVPREFSD_H
#define AVPREFSD_H

/*	**ER 1/31/96
**	WARNING!
**  Do not ever add preferences to the middle of _t_APrefsType! Always append.
**  If you are not certain that you understand our preferences system,
**  find somebody who does who can help you.  Messing with the preferences
**  can cause a lot of problems, some of which can be subtle and hard to find.
**  Additionally, be sure to update AVExpt.h in the SDK so that plug-ins can
**  see your changes.
*/

/*	Items which are declared AVS are either strings or structures, both
**	of which require special handling when establishing defaults, etc.
**	Also, any item marked AVS requires modifications to the preferences
**	code on Mac. String items are stored in a separate record, and
**	non-string items require some special handling in SetProcIndep.
**	(We could avoid the later problem by separating AVS into two
**	defines, one for structures which can be copied as-is and one
**	for strings and other pointers. But not now.)
*/

/*
 * AVP(a, b)    does not quite cover all cases
 * AVX(a, b)    used only for avpShortMenus
 * AVS(a, b)    for prefs which are structures or strings
 *			    initializing defaults needs to be special-cased
 * AVU(a, b, c) used for obsolete preferences
 * AVPSTR(a)    used for char* strings
 * AVPVOIDP(a)  used for void* objects
 */

/* DO NOT ADD ANY PREFERENCES TO OR REMOVE ANY PREFERENCES FROM HERE -- these preferences used to use
** the original preference API.  This section is for retaining backwards compatibility 
** with the original API.
** 
** Use AVAppSetPref___() and AVAppGetPref___() for new preferences. 
**
** Ask someone if this isn't clear.  
*/


#define AV_PREFERENCES \
AVP(avpPrefsVersion, ASInt32) \
AVP(avpOpenDialogAtStartup, ASBool) \
AVP(avpShowSplashAtStartup, ASBool) \
AVP(avpShowToolBar, ASBool) \
AVP(avpRememberDialogs, ASBool) \
AVX(avpShortMenus, ASBool) /* omitted from AVPrefsRec, included in AVPrefsType */ \
AVP(avpDefaultOverviewType, PDPageMode) \
AVP(avpDefaultZoomScale, ASFixed) \
AVP(avpDefaultZoomType, AVZoomType) \
AVP(avpShowLargeImages, ASBool) \
AVP(avpGreekText, ASBool) \
AVP(avpGreekLevel, ASInt32) \
AVP(avpSubstituteFontType, PDSubstFontPref) \
AVP(avpDoCalibratedColor, ASBool) \
AVP(avpSkipWarnings, ASBool) \
AVP(avpPSLevel, ASInt32) \
AVP(avpShrinkToFit, ASBool) \
AVP(avpCaseSensitive, ASBool) \
AVP(avpWholeWords, ASBool) \
AVS(avpNoteColor, PDColorValueRec) \
AVPSTR(avpNoteLabel) /* MAX_NOTE_LABEL */ \
AVP(avpMaxThreadZoom, ASFixed) \
AVP(avpEnablePageCache, ASBool) \
AVS(avpFullScreenColor, PDColorValueRec) \
AVU(avpFullScrolling, ASBool, 1) /* AVU => obsolete */ \
AVP(avpMaxPageCacheZoom, ASFixed) \
AVP(avpMinPageCacheTicks, ASInt32) \
AVP(avpMaxPageCacheBytes, ASInt32) \
AVP(avpDrawMissingThumbs, ASBool) /* AVU => obsolete */ \
AVP(avpFullScreenChangeTimeDelay, ASInt32) \
AVP(avpFullScreenLoop, ASBool) \
AVP(avpThumbViewScale, ASFixed) \
AVP(avpThumbViewTimeout, ASInt32) \
AVPSTR(avpDestFitType) /* MAX_FIT_TYPE */ \
AVP(avpDestZoomInherit, ASBool) \
AVP(avpHighlightMode, ASInt32) \
AVP(avpDefaultSplitterPos, ASInt32) \
AVU(avpThreadIndicator, ASUns32, 2) /* AVU => obsolete */ \
AVP(avpMaxCosDocCache, ASInt32) \
AVP(avpPageUnits, PageUnitsType) \
AVPSTR(avpNoteFontName_Deprecated) /* MAX_FONT_NAME */ \
AVP(avpNoteFontSize_Deprecated, ASInt32) \
AVPSTR(avpRecentFile1) \
AVPSTR(avpRecentFile2) \
AVPSTR(avpRecentFile3) \
AVPSTR(avpRecentFile4) \
AVS(avpHighlightColor, PDColorValueRec) \
AVP(avpFullScreenUseTimer, ASBool) \
AVP(avpAntialiasText, ASBool) \
AVP(avpAntialiasLevel, ASInt32) \
AVP(avpPersistentCacheSize, ASInt32) \
AVP(avpPersistentCacheFolder, ASPathName) \
AVP(avpPageViewLayoutMode, PDLayoutMode) \
AVP(avpSaveAsLinearized, ASBool) \
AVP(avpMaxOpenDocuments, ASInt32) \
AVP(avpUseHostFont, ASBool) \
AVP(avpMarkHiddenPages, ASBool)				/* DON'T SAVE TO DISK */ \
AVPSTR(avpFullScreenTransitionType) \
AVP(avpFullScreenClick, ASBool) \
AVP(avpFullScreenEscape, ASBool) \
AVP(avpFullScreenCursor, ASInt32) \
AVP(avpOpenInPlace, ASBool) \
AVP(avpShowHiddenAnnots, ASBool)			/* DON'T SAVE TO DISK */ \
AVP(avpFullScreenUsePageTiming, ASBool)		/* DON'T SAVE TO DISK */ \
AVP(avpDownloadEntireFile, ASBool) \
AVP(avpEmitHalftones, ASBool) \
AVP(avpShowMenuBar, ASBool)					/* DON'T SAVE TO DISK */ \
AVP(avpIgnorePageClip, ASBool) \
AVP(avpMinimizeBookmarks, ASBool) \
AVP(avpShowAnnotSequence, ASBool) \
AVP(avpUseLogicalPageNumbers, ASBool) \
AVS(avpASExtensionDigCert, ASExtensionEncryptedDigitalCertificateRec) \
AVP(avpShowLeftToolBar, ASBool) \
AVP(avpAllowOpenFile, ASBool) \
AVPVOIDP(avpNoteLabelEncoding) \
AVP(avpBookmarkShowLocation, ASBool) \
AVP(avpUseLocalFonts, ASBool) \
AVPSTR(avpCurrCMM) \
AVP(avpBrowserIntegration, ASBool) \
AVP(avpBrowserCheck, ASBool) \
AVP(avpPrintAnnots, ASBool) \
AVP(avpSendFarEastFonts, ASBool) \
AVP(avpSuppressCSA, ASBool)	\
AVP(avpAntialiasGraphics, ASBool) \
AVP(avpSecureOpenFile, ASBool) \
AVP(avpPaperSize, ASInt32) \
AVP(avpTrustedMode, ASInt32) \
AVP(avpTrustedModeOverride, ASInt32) \
AVP(avpShowUnixEula,ASBool) \
AVP(avpCMS, ASUns32) \
AVP(avpCMM, ASUns32) \
AVPSTR(avpWorkingRGB) \
AVPSTR(avpWorkingCMYK) \
AVPSTR(avpWorkingGray) \
AVP(avpBlackPointCompensation, ASBool) \
AVP(avpHostBasedCM, ASBool) \
AVP(avpAntialiasImages, ASBool) \
AVP(avpDoUpdate, ASBool) \
AVP(avpUpdateFrequency, ASUns32) \
AVP(avpShowUpdateDialog, ASBool) \
AVP(avpLastAcrobatUpdateCheck, ASUns32) \
AVP(avpDisableAcrobatUpdate, ASBool) \
AVPSTR(avpOverrideAcrobatUpdateURL) \
AVP(avpLastWebServicesUpdateCheck, ASUns32) \
AVP(avpDisableWebServicesUpdate, ASBool) \
AVP(avpEnableDDR, ASBool) \
AVP(avpColorArtifactRemoval, ASInt32) \
AVP(avpGamma, ASInt32) \
AVP(avpDirectDraw, ASBool) \
AVP(avpSaveVM, ASBool) \
AVPSTR(avpColorSettingsFile) \
AVPSTR(avpPrinterSpace) \
AVP(avpAccessColorPolicy, ASInt32) \
AVP(avpAccessOverrideDocColors, ASBool) \
AVS(avpAccessTextColor, PDColorValueRec) \
AVS(avpAccessBackgroundColor, PDColorValueRec) \
AVP(avpShowGrid, ASBool) \
AVP(avpSnapToGrid, ASBool) \
AVP(avpGridWidth, ASFixed) \
AVP(avpGridHeight, ASFixed) \
AVP(avpGridSubdivisions, ASInt32) \
AVS(avpGridColor, PDColorValueRec) \
AVP(avpGridHOffset, ASFixed) \
AVP(avpGridVOffset, ASFixed) \
AVS(avpGridMinorColor, PDColorValueRec)\
AVP(avpAllowByteRangeRequests, ASBool) \
AVP(avpUsingAreaBoxNames, ASBool) \
AVP(avpSoftProof, ASBool) \
AVPSTR(avpProofingSpace)\
AVP(avpEmitTileMarks, ASInt32) \
AVP(avpSlugs, ASBool) \
AVP(avpShowOverprint, ASBool) \
AVP(avpPrintOverprint, ASBool) \
AVP(avpNoteOpacity, ASFixed) \
AVP(avpProofInkBlack, ASBool) \
AVP(avpProofPaperWhite, ASBool) \
AVP(avpOptimizeForSpeed, ASBool) \
AVP(avpAccessPageMode, ASBool) \
AVP(avpAccessMaxDocModePages, ASInt32) \
AVP(avpShowTransparencyGrid, ASBool) \
AVP(avpHoveringPopups, ASBool) \
AVP(avpFullScreenMonitor, ASInt32) \
AVP(avpOpenNewDocument, ASBool) \
AVP(avpOpenAsPDFFilterIndex, ASInt32) \
AVP(avpSaveAsFilterIndex, ASInt32)\
AVP(avpHideTabsCompletely, ASBool)\
AVP(avpPrintUsingWorkingSpaces, ASBool)\
AVP(avpDisplayRightsDialog, ASBool) \
AVP(avpCacheFormData, ASBool) \
AVP(avpEmitPostScriptXObjects, ASBool) \
AVP(avpWrapLongBookmarks, ASBool) \
AVP(avpAccessReadOrderOverride, ASBool) \
AVP(avpAccessReadOrder, ASInt32)  \
AVP(avpFullScreenIgnoreTrans, ASBool)  \
AVP(avpUsePenForInput, ASBool) \
AVP(avpUseSysSetting, ASBool) \
AVP(avpPixelsPerInch, ASInt32)

/* DO NOT ADD ANY PREFERENCES TO OR REMOVE ANY PREFERENCES FROM HERE -- these preferences used to use
** the original preference API.  This section is for retaining backwards compatibility 
** with the original API.
** 
** Use AVAppSetPref___() and AVAppGetPref___() for new preferences. 
**
** Ask someone if this isn't clear.  
*/

#endif /* AVPREFSD_H */
