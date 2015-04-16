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

 AVCalls.h

 ******************************************************************************************
                        **** Instructions for Plugin Developers **** 
   (In the instructions below ~ is used to refer to the HFT this file is for.  For
     example this file would be called "~Calls.h")
  
   To use this file you must declare two global variables g~HFT and g~Version.  You can
   see them declared as extern about one page down from here.  Your plugin should set a 
   #define of PI_~_VERSION to some non zero value.  Suggested values are given below in
   the "for public use" section.  ~HFT_LATEST_VERSION is not recommended because you will 
   not be able to support backwards compatible versions.  Better is to use the lowest 
   ~HFT_VERSION you require.  Later versions are compatible with earlier versions so if 
   you require ~HFT_VERSION_4 your plugin will work with ~HFT_VERSION_5, ~HFT_VERSION_6, etc.
  
   You can support old versions, yet still use newer versions of this HFT by checking the 
   value of g~Version.  If you use the standard PiMain.c supplied in the SDK this will be
   set to the actual version of the HFT returned to you (For example, you require version 4,
   you are returned version 7 which is compatible; g~Version is set to 7).  You can write
   code that looks something like this:
     if (g~Version >= ~HFT_VERSION_5) 
        CallNewSpeedyCode();
     else {
        ACROASSERT(g~Version >= ~HFT_VERSION_4);  //PI_~_VERSION was defined as ~HFT_VERSION_4
        CallOldSlowCode();
     }
 ******************************************************************************************
                        **** Instructions for HFT Developer **** 
   (In the instructions below ~ is used to refer to the HFT this file is for.  For
     example this file would be called "~Calls.h")

   Most importantly, routines that have been released can never be deleted or changed.
   If you want to make a new version create a new call, add to the end of this file and
   increment the _~_LATEST_VERSION (note the leading underscore).  
   
   If this is the first new routine in a new version, you should change the _~_IS_BETA flag
   to 1.  Next, create a new ~_VERSION_# for plugins to use and set it to 
   ~HFT_LATEST_VERSION.  For example the last release of Acrobat was version 20.  Version 21
   is under development.  You add a new routine for version 21.  Increment _~HFT_LATEST_VERSION 
   to 0x00200001 and set _~_IS_BETA to 1.  Add "#define ~HFT_VERSION_21 ~HFT_LATEST_VERSION".  
   Add your routine and assert that g~Version >= ~HFT_VERSION_21.  Leave 
   _~_LAST_BETA_COMPATIBLE_VERSION unchanged (0x00200000 in our example).

   If the ~_IS_BETA flag is set to 1, you may change or delete the beta routines at will.
   Before checking in the modifications however, increment the _~HFT_LATEST_VERSION number.
   If the change is not compatible (delete, change, etc.) set _~_LAST_BETA_COMPATIBLE_VERSION equal
   to the new _~HFT_LATEST_VERSION.  If the change is compatible, leave the LAST_BETA version
   alone.

   Plugins that require a BETA HFT will be refused unless they ask for a beta version
   >= LAST_BETA_COMPATIBLE_VERSION and <= HFT_LATEST_VERSION.
   By incrementing the version number you ensure the plugin will refuse to load until it
   has been recompiled with your changes.  You also ensure plugins compiled with your changes
   will not load on older versions of Acrobat.  In other words in makes sure both sides are in sync.  

   Again, whenever you make a change to this file, you must increment _~HFT_LATEST_VERSION.
  
   Once the product reaches RC or similar milestone, change the _~_IS_BETA flag to 0, jump
   The _~HFT_LATEST_VERSION to the final version (0x00210000 in our example), do the same for
   _~_LAST_BETA_COMPATIBLE_VERSION, and set the 
   ~HFT_VERSION_# to the final version number (0x00210000 in our example).  Once the HFT
   has left beta, the routines cannot be changed and a new beta must ensue (beta for version
   22 in our example).

*********************************************************************/

#ifndef _H_AVCalls
#define _H_AVCalls

#if PLUGIN
#include "acroassert.h"
#endif

#include "AVVers.h" /* contains the version numbers for this file */

#ifndef CAN_EDIT
#define CAN_EDIT 1 /*assume we can edit */
#endif
#include "AVExpT.h"
#include "acroassert.h"

//#if CAN_EDIT
#ifdef __cplusplus
extern "C" {
#endif

#if PLUGIN
#include "NSelExpT.h"
#endif

#define EXTERNAL_AVPROCS_USER 1 /* External user of AVProcs.h header file */

#define HAS_MENUBAR 1
#define HAS_FULL_SCREEN 1
#define HAS_MENUS 1
#define CAN_SELECT_GRAPHICS 1
	
#if !PLUGIN

	/* Static link */
   #define NPROC(returnType, name, params)		\
		ACEX1 returnType ACEX2 name params;
   #define SPROC(returnType, name, params, stubProc) \
  		extern ACEX1 returnType ACEX2 stubProc params;
	
   #define ANPROC NPROC
   #define PROC NPROC
   #define NOPROC(name)
   #define UPROC PROC
   #define UNPROC NPROC
   #define USPROC SPROC
#if CAN_EDIT
   #define XNPROC NPROC
   #define XPROC NPROC
   #define XSPROC NPROC
#else
   #define XNPROC NOPROC
   #define XPROC NOPROC
   #define XSPROC NOPROC
#endif

   #include "AVProcs.h"

   #undef NPROC
   #undef ANPROC
   #undef SPROC
   #undef PROC
   #undef NOPROC
   #undef XNPROC
   #undef XPROC
   #undef XSPROC
   #undef UPROC
   #undef UNPROC
   #undef USPROC

	/* These functions have a different name internally */
	#define AVAppEnumActionHandlers AVAppEnumSupportedActions
	#define AVAppRegisterNotification AVExtensionMgrRegisterNotification
	#define AVAppUnregisterNotification AVExtensionMgrUnregisterNotification
	#define AVPageViewGoBack AVPageViewDoGoBack
	#define AVPageViewGoForward AVPageViewDoGoForward
	#define oldAVAppRegisterForPageViewDrawing oldAVPageViewRegisterForDrawing
	#define AVAppUnregisterForPageViewDrawing AVPageViewUnregisterForDrawing
	#define oldAVAppRegisterForPageViewClicks oldAVPageViewRegisterForClicks
	#define AVAppUnregisterForPageViewClicks AVPageViewUnregisterForClicks
	#define oldAVAppRegisterForPageViewAdjustCursor oldAVPageViewRegisterForAdjustCursor
	#define AVAppUnregisterForPageViewAdjustCursor AVPageViewUnregisterForAdjustCursor
#if !MAC_PLATFORM || (MAC_PLATFORM && !AS_ARCH_64BIT)
	/* Deprecated */
	#define AVPageViewAcquireMachinePort AVPageViewGetMachinePort
	/* Deprecated */
	#define AVPageViewReleaseMachinePort AVPageViewFreeMachinePort
#endif
	#define oldAVPageViewPointToDevice oldAVPagePointToDevice
	#define oldAVPageViewDevicePointToPage oldAVPageDevicePointToPage
	#define oldAVPageViewRectToDevice oldAVPageRectToDevice
	#define oldAVPageViewDeviceRectToPage oldAVPageDeviceRectToPage
	#define oldAVPageViewTrackText oldAVPageViewTrackTextHost
	#define oldAVDocSetViewDef oldAVDocUseViewDef
	#define oldAVPageViewDeviceRectToPageRZ oldAVPageDeviceRectToPageRZ
	#define oldAVPageViewSnapRect oldAVPageViewGridSnapRect
	#define AVAppRegisterForPageViewAdjustCursor AVPageViewRegisterForAdjustCursor
	#define AVAppRegisterForPageViewClicks AVPageViewRegisterForClicks
	#define AVAppRegisterForPageViewDrawing AVPageViewRegisterForDrawing
	#define AVDocSetViewDef AVDocUseViewDef
	#define AVPageViewRectToDevice AVPageRectToDevice
	#define AVPageViewDeviceRectToPage AVPageDeviceRectToPage
	#define AVPageViewDevicePointToPage AVPageDevicePointToPage
	#define AVPageViewTrackText AVPageViewTrackTextHost
	#define AVPageViewDeviceRectToPageRZ AVPageDeviceRectToPageRZ
	#define AVPageViewSnapRect AVPageViewGridSnapRect
	#define AVPageViewPointToDevice AVPagePointToDevice
	#define AVDocSetViewDefEx AVDocUseViewDefEx
	#define AVAppRegisterForPageViewRightClicks AVPageViewRegisterForRightClicks
	#define AVAppUnregisterForPageViewRightClicks AVPageViewUnregisterForRightClicks
	#define AVAppUnregisterForPageViewDrawingEx AVPageViewUnregisterForDrawingEx

#endif /* !PLUGIN */

#if PLUGIN

	/* HFT version */
   #include "PIRequir.h"
	
	/* Enumerate the selectors */
   #define NPROC(returnType, name, params)			\
		name##SEL, 
   #define SPROC(returnType, name, params, stubProc) \
		name##SEL, 
   #define NOPROC(name)	\
			name##SEL, 
   #define PROC NPROC
   #define ANPROC NPROC
   #define XNPROC NPROC
   #define XPROC NPROC
   #define XSPROC SPROC
   #define UPROC NPROC
   #define UNPROC NPROC
   #define USPROC SPROC
	
	enum {
		AVBAD_SELECTOR, 
		#include "AVProcs.h"
		AVNUMSELECTORSplusOne
	};
	
   #define AVNUMSELECTORS (AVNUMSELECTORSplusOne - 1)
	
	/* Create the prototypes */
   #undef NPROC
   #undef ANPROC
   #undef SPROC
   #undef PROC
   #undef NOPROC
   #undef XNPROC
   #undef XPROC
   #undef XSPROC
   #undef UPROC
   #undef UNPROC
   #undef USPROC
	
   #define NPROC(returnType, name, params)		\
		typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##SELPROTO)params;
   #define SPROC(returnType, name, params, stubProc) \
		typedef ACCBPROTO1 returnType (ACCBPROTO2 *name##SELPROTO)params;
   #define PROC NPROC	
   #define ANPROC NPROC
#if READER_PLUGIN
   /* Force an error for Exchange procs */
   #define XNPROC(returnType, name, params)
   #define XPROC(returnType, name, params)
   #define XSPROC(returnType, name, params, stubProc)
   #define UPROC(returnType, name, params) 
   #define UNPROC(returnType, name, params) 
   #define USPROC(returnType, name, params, stubProc) 
#else
   #define XNPROC NPROC
   #define XPROC NPROC
   #define XSPROC SPROC
   #define UPROC NPROC
   #define UNPROC NPROC
   #define USPROC SPROC
#endif
   #define NOPROC(name)	
	
   #include "AVProcs.h"

   #undef NPROC
   #undef ANPROC
   #undef SPROC
   #undef PROC
   #undef NOPROC
   #undef XNPROC
   #undef XPROC
   #undef XSPROC	
   #undef UPROC
   #undef UNPROC
   #undef USPROC

#if PI_ACROVIEW_VERSION != 0

extern HFT gAcroViewHFT;
extern ASVersion gAcroViewVersion;

/* declare a routine name to require version >= level.  Routine is indexed from HFT */
#define AVROUTINE(level, name) (ACROASSERT(gAcroViewVersion >=level), *((name##SELPROTO)(gAcroViewHFT[name##SEL])))

#if !STATIC_HFT

/* check SDK level.  If user is using OLD SDK map calls to old routines.  If user is supporting old and new calls
   use AVCOMPAT_ROUTINE to check current level and call new routine, or call compatstub to use old routine.
   If user is only using current routines, map calls to current routines
   Note that this macro makes use of the assumption that the old routine will be renamed to "oldroutine".  A new
   macro will have to be constructed to handle 3 level routines and a maybe call the next oldest "old2routine" or 
   something. */
#if !defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)
/* caller only knows about old routine, and uses old calling convention.  Map name to "old" routine and call directly */
/* multiaware routines still only have one HFT entry, but need special code when supporting multiple versions */
/*  this special code is located in the AVCompat.cpp file */
#define DECLARE_MULTIAVROUTINE(oldlev, newlev, name) AVROUTINE(oldlev, old##name)
#define DECLARE_MULTIAWAREAVROUTINE(oldlev, newlev, name) AVROUTINE(oldlev, name)

#elif defined(PI_ACROVIEW_VERSION) && (PI_ACROVIEW_VERSION < AcroViewHFT_VERSION_6)

/* declare a routine name that has an older version, the first version (oldest) calls nameCompatStub, the second (new) calls directly to the HFT */
#define AVCOMPAT_ROUTINE(first, second, name) (ACROASSERT(gAcroViewVersion >=first), \
	gAcroViewVersion >=second? AVROUTINE(second, name) :name##CompatStub) 
#include "AVCompat.h"
#define DECLARE_MULTIAVROUTINE(oldlev, newlev, name) AVCOMPAT_ROUTINE(oldlev, newlev, name)
#define DECLARE_MULTIAWAREAVROUTINE DECLARE_MULTIAVROUTINE

#else /*(PI_ACROVIEW_VERSION >= AcroViewHFT_VERSION_6)*/

/* support only new calling convention, no support for older AV routines */
#define DECLARE_MULTIAVROUTINE(oldlev, newlev, name) AVROUTINE(newlev, name)
#define DECLARE_MULTIAWAREAVROUTINE DECLARE_MULTIAVROUTINE

#endif /*(PI_ACROVIEW_VERSION >= AcroViewHFT_VERSION_6)*/

/* AVActionHandlerGetType */
#define AVActionHandlerGetType AVROUTINE(AcroViewHFT_VERSION_2, AVActionHandlerGetType)

/* AVActionHandlerGetUIName */
#define AVActionHandlerGetUIName AVROUTINE(AcroViewHFT_VERSION_2, AVActionHandlerGetUIName)

/* AVActionHandlerGetProcs */
#define AVActionHandlerGetProcs AVROUTINE(AcroViewHFT_VERSION_2, AVActionHandlerGetProcs)

/* AVAlert */
#define AVAlert AVROUTINE(AcroViewHFT_VERSION_2, AVAlert)

/* AVAlertNote */
#define AVAlertNote AVROUTINE(AcroViewHFT_VERSION_2, AVAlertNote)

/* AVAlertConfirm */
#define AVAlertConfirm AVROUTINE(AcroViewHFT_VERSION_2, AVAlertConfirm)

/* AVAppGetVersion */
#define AVAppGetVersion AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetVersion)

/* AVAppGetLanguage */
#define AVAppGetLanguage AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetLanguage)

/* AVAppGetName */
#define AVAppGetName AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetName)

/* AVAppGetCancelProc */
#define AVAppGetCancelProc AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetCancelProc)

/* AVAppCanQuit */
#define AVAppCanQuit AVROUTINE(AcroViewHFT_VERSION_2, AVAppCanQuit)

/* AVAppGetActiveDoc */
#define AVAppGetActiveDoc AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetActiveDoc)

/* AVAppGetNumDocs */
#define AVAppGetNumDocs AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetNumDocs)

/* AVAppEnumDocs */
#define AVAppEnumDocs AVROUTINE(AcroViewHFT_VERSION_2, AVAppEnumDocs)

/* AVAppGetDocProgressMonitor */
#define AVAppGetDocProgressMonitor AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetDocProgressMonitor)

/* AVAppGetMenubar */
#define AVAppGetMenubar AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetMenubar)

/* AVAppGetActiveTool */
#define AVAppGetActiveTool AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetActiveTool)

/* AVAppGetLastActiveTool */
#define AVAppGetLastActiveTool AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetLastActiveTool)

/* AVAppGetDefaultTool */
#define AVAppGetDefaultTool AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetDefaultTool)

/* AVAppSetActiveTool */
#define AVAppSetActiveTool AVROUTINE(AcroViewHFT_VERSION_2, AVAppSetActiveTool)

/* AVAppGetToolByName */
#define AVAppGetToolByName AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetToolByName)

/* AVAppEnumTools */
#define AVAppEnumTools AVROUTINE(AcroViewHFT_VERSION_2, AVAppEnumTools)

/* AVAppRegisterTool */
#define AVAppRegisterTool DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppRegisterTool)

/* AVAppGetAnnotHandlerByName */
#define AVAppGetAnnotHandlerByName AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetAnnotHandlerByName)

/* AVAppEnumAnnotHandlers */
#define AVAppEnumAnnotHandlers AVROUTINE(AcroViewHFT_VERSION_2, AVAppEnumAnnotHandlers)

/* AVAppRegisterAnnotHandler */
#define AVAppRegisterAnnotHandler DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppRegisterAnnotHandler)

/* AVAppRegisterAnnotHandler */
#define AVAppUnregisterAnnotHandler AVROUTINE(AcroViewHFT_VERSION_10, AVAppUnregisterAnnotHandler)

/* AVAppGetActionHandlerByType */
#define AVAppGetActionHandlerByType AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetActionHandlerByType)

/* AVAppEnumActionHandlers */
#define AVAppEnumActionHandlers AVROUTINE(AcroViewHFT_VERSION_2, AVAppEnumActionHandlers)

/* AVAppRegisterActionHandler */
#define AVAppRegisterActionHandler AVROUTINE(AcroViewHFT_VERSION_2, AVAppRegisterActionHandler)

/* AVAppGetPreference */
#define AVAppGetPreference AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetPreference)

/* AVAppSetPreference */
#define AVAppSetPreference AVROUTINE(AcroViewHFT_VERSION_2, AVAppSetPreference)

/* AVAppBeginFullScreen */
#define AVAppBeginFullScreen AVROUTINE(AcroViewHFT_VERSION_2, AVAppBeginFullScreen)

/* AVAppEndFullScreen */
#define AVAppEndFullScreen AVROUTINE(AcroViewHFT_VERSION_2, AVAppEndFullScreen)

/* AVAppDoingFullScreen */
#define AVAppDoingFullScreen AVROUTINE(AcroViewHFT_VERSION_2, AVAppDoingFullScreen)

/* AVAppBeginModal */
#define AVAppBeginModal AVROUTINE(AcroViewHFT_VERSION_2, AVAppBeginModal)

/* AVAppModalWindowIsOpen */
#define AVAppModalWindowIsOpen AVROUTINE(AcroViewHFT_VERSION_2, AVAppModalWindowIsOpen)

/* AVAppEndModal */
#define AVAppEndModal AVROUTINE(AcroViewHFT_VERSION_2, AVAppEndModal)

/* AVAppRegisterIdleProc */
#define AVAppRegisterIdleProc AVROUTINE(AcroViewHFT_VERSION_2, AVAppRegisterIdleProc)

/* AVAppUnregisterIdleProc */
#define AVAppUnregisterIdleProc AVROUTINE(AcroViewHFT_VERSION_2, AVAppUnregisterIdleProc)

/* AVAppRegisterNotification */
#define AVAppRegisterNotification AVROUTINE(AcroViewHFT_VERSION_2, AVAppRegisterNotification)

/* AVAppUnregisterNotification */
#define AVAppUnregisterNotification AVROUTINE(AcroViewHFT_VERSION_2, AVAppUnregisterNotification)

/* AVDocOpenFromFile */
#define AVDocOpenFromFile DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVDocOpenFromFile)

/* AVDocOpenFromFileWithParams */
#define AVDocOpenFromFileWithParams DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVDocOpenFromFileWithParams)

/* AVDocOpenFromPDDoc */
#define AVDocOpenFromPDDoc DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVDocOpenFromPDDoc)

/* AVDocOpenFromPDDocWithParams */
#define AVDocOpenFromPDDocWithParams DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVDocOpenFromPDDocWithParams)

/* AVDocOpenFromFileWithParamString */
#define AVDocOpenFromFileWithParamString AVROUTINE(AcroViewHFT_VERSION_6, AVDocOpenFromFileWithParamString)

/* AVDocOpenFromPDDocWithParamString */
#define AVDocOpenFromPDDocWithParamString AVROUTINE(AcroViewHFT_VERSION_6, AVDocOpenFromPDDocWithParamString)

/* AVDocOpenFromASFileWithParamString */
#define AVDocOpenFromASFileWithParamString AVROUTINE(AcroViewHFT_VERSION_6, AVDocOpenFromASFileWithParamString)

/* AVDocClose */
#define AVDocClose AVROUTINE(AcroViewHFT_VERSION_2, AVDocClose)

/* AVDocGetPDDoc */
#define AVDocGetPDDoc AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetPDDoc)

/* AVDocGetPageView */
#define AVDocGetPageView AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetPageView)

/* AVDocGetAVWindow */
#define AVDocGetAVWindow AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetAVWindow)

/* AVDocGetViewMode */
#define AVDocGetViewMode AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetViewMode)

/* AVDocSetViewMode */
#define AVDocSetViewMode AVROUTINE(AcroViewHFT_VERSION_2, AVDocSetViewMode)

/* AVDocGetSplitterPosition */
#define AVDocGetSplitterPosition AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetSplitterPosition)

/* AVDocSetSplitterPosition */
#define AVDocSetSplitterPosition AVROUTINE(AcroViewHFT_VERSION_2, AVDocSetSplitterPosition)

/* AVDocPrintPages */
#define AVDocPrintPages AVROUTINE(AcroViewHFT_VERSION_2, AVDocPrintPages)

/* AVDocGetSelectionType */
#define AVDocGetSelectionType AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetSelectionType)

/* AVDocGetSelection */
#define AVDocGetSelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetSelection)

/* AVDocSetSelection */
#define AVDocSetSelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocSetSelection)

/* AVDocDeleteSelection */
#define AVDocDeleteSelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocDeleteSelection)

/* AVDocClearSelection */
#define AVDocClearSelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocClearSelection)

/* AVDocCopySelection */
#define AVDocCopySelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocCopySelection)

/* AVDocEnumSelection */
#define AVDocEnumSelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocEnumSelection)

/* AVDocDoSelectionProperties */
#define AVDocDoSelectionProperties AVROUTINE(AcroViewHFT_VERSION_2, AVDocDoSelectionProperties)

/* AVDocShowSelection */
#define AVDocShowSelection AVROUTINE(AcroViewHFT_VERSION_2, AVDocShowSelection)

/* AVDocGetSelectionServerByType */
#define AVDocGetSelectionServerByType AVROUTINE(AcroViewHFT_VERSION_2, AVDocGetSelectionServerByType)

/* AVDocRegisterSelectionServer */
#define AVDocRegisterSelectionServer DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVDocRegisterSelectionServer)

/* AVDocPerformAction */
#define AVDocPerformAction AVROUTINE(AcroViewHFT_VERSION_2, AVDocPerformAction)

/* AVMenubarShow */
#define AVMenubarShow AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarShow)

/* AVMenubarHide */
#define AVMenubarHide AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarHide)

/* AVMenubarGetNumMenus */
#define AVMenubarGetNumMenus AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarGetNumMenus)

/* AVMenubarAcquireMenuByName */
#define AVMenubarAcquireMenuByName AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarAcquireMenuByName)

/* AVMenubarAcquireMenuByIndex */
#define AVMenubarAcquireMenuByIndex AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarAcquireMenuByIndex)

/* AVMenubarAcquireMenuByPredicate */
#define AVMenubarAcquireMenuByPredicate AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarAcquireMenuByPredicate)

/* AVMenubarAcquireMenuItemByName */
#define AVMenubarAcquireMenuItemByName AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarAcquireMenuItemByName)

/* AVMenubarAcquireMenuItemByPredicate */
#define AVMenubarAcquireMenuItemByPredicate AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarAcquireMenuItemByPredicate)

/* AVMenubarGetMenuIndex */
#define AVMenubarGetMenuIndex AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarGetMenuIndex)

/* AVMenubarAddMenu */
#define AVMenubarAddMenu AVROUTINE(AcroViewHFT_VERSION_2, AVMenubarAddMenu)

/* AVMenuNew */
#define AVMenuNew AVROUTINE(AcroViewHFT_VERSION_2, AVMenuNew)

/* AVMenuAcquire */
#define AVMenuAcquire AVROUTINE(AcroViewHFT_VERSION_2, AVMenuAcquire)

/* AVMenuRelease */
#define AVMenuRelease AVROUTINE(AcroViewHFT_VERSION_2, AVMenuRelease)

/* AVMenuRemove */
#define AVMenuRemove AVROUTINE(AcroViewHFT_VERSION_2, AVMenuRemove)

/* AVMenuGetName */
#define AVMenuGetName AVROUTINE(AcroViewHFT_VERSION_2, AVMenuGetName)

/* AVMenuGetTitle */
#define AVMenuGetTitle AVROUTINE(AcroViewHFT_VERSION_2, AVMenuGetTitle)


/* AVMenuGetNumMenuItems */
#define AVMenuGetNumMenuItems AVROUTINE(AcroViewHFT_VERSION_2, AVMenuGetNumMenuItems)

/* AVMenuAcquireMenuItemByIndex */
#define AVMenuAcquireMenuItemByIndex AVROUTINE(AcroViewHFT_VERSION_2, AVMenuAcquireMenuItemByIndex)

/* AVMenuGetMenuItemIndex */
#define AVMenuGetMenuItemIndex AVROUTINE(AcroViewHFT_VERSION_2, AVMenuGetMenuItemIndex)

/* AVMenuGetParentMenubar */
#define AVMenuGetParentMenubar AVROUTINE(AcroViewHFT_VERSION_2, AVMenuGetParentMenubar)

/* AVMenuGetParentMenuItem */
#define AVMenuGetParentMenuItem AVROUTINE(AcroViewHFT_VERSION_2, AVMenuGetParentMenuItem)

/* AVMenuAddMenuItem */
#define AVMenuAddMenuItem AVROUTINE(AcroViewHFT_VERSION_2, AVMenuAddMenuItem)

/* AVMenuItemNew */
#define AVMenuItemNew AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemNew)

/* AVMenuItemAcquire */
#define AVMenuItemAcquire AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemAcquire)

/* AVMenuItemRelease */
#define AVMenuItemRelease AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemRelease)

/* AVMenuItemRemove */
#define AVMenuItemRemove AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemRemove)

/* AVMenuItemGetName */
#define AVMenuItemGetName AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemGetName)

/* AVMenuItemGetTitle */
#define AVMenuItemGetTitle AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemGetTitle)

/* AVMenuItemSetTitle */
#define AVMenuItemSetTitle AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemSetTitle)

/* AVMenuItemGetShortcut */
#define AVMenuItemGetShortcut AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemGetShortcut)

/* AVMenuItemGetLongOnly */
#define AVMenuItemGetLongOnly AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemGetLongOnly)

/* AVMenuItemSetExecuteProc */
#define AVMenuItemSetExecuteProc AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemSetExecuteProc)

/* AVMenuItemSetComputeEnabledProc */
#define AVMenuItemSetComputeEnabledProc AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemSetComputeEnabledProc)

/* AVMenuItemSetComputeMarkedProc */
#define AVMenuItemSetComputeMarkedProc AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemSetComputeMarkedProc)

/* AVMenuItemAcquireSubmenu */
#define AVMenuItemAcquireSubmenu AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemAcquireSubmenu)

/* AVMenuItemIsEnabled */
#define AVMenuItemIsEnabled AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemIsEnabled)

/* AVMenuItemIsMarked */
#define AVMenuItemIsMarked AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemIsMarked)

/* AVMenuItemExecute */
#define AVMenuItemExecute AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemExecute)

/* AVMenuItemGetParentMenu */
#define AVMenuItemGetParentMenu AVROUTINE(AcroViewHFT_VERSION_2, AVMenuItemGetParentMenu)

/* AVPageViewGetAVDoc */
#define AVPageViewGetAVDoc AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetAVDoc)

/* AVPageViewGetAperture */
#define AVPageViewGetAperture DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewGetAperture)

/* AVPageViewGetPage */
#define AVPageViewGetPage AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetPage)

/* AVPageViewGetZoom */
#define AVPageViewGetZoom AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetZoom)

/* AVPageViewGetZoomType */
#define AVPageViewGetZoomType AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetZoomType)

/* AVPageViewGetPageNum */
#define AVPageViewGetPageNum AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetPageNum)

/* AVPageViewGetColor */
#define AVPageViewGetColor AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetColor)

/* AVPageViewSetColor */
#define AVPageViewSetColor AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewSetColor)

/* AVPageViewBeginOperation */
#define AVPageViewBeginOperation AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewBeginOperation)

/* AVPageViewEndOperation */
#define AVPageViewEndOperation AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewEndOperation)

/* AVPageViewGoTo */
#define AVPageViewGoTo AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGoTo)

/* AVPageViewZoomTo */
#define AVPageViewZoomTo AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewZoomTo)

/* AVPageViewScrollTo */
#define AVPageViewScrollTo DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewScrollTo)

/* AVPageViewScrollToRect */
#define AVPageViewScrollToRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewScrollToRect)

/* AVPageViewReadPageUp */
#define AVPageViewReadPageUp AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewReadPageUp)

/* AVPageViewReadPageDown */
#define AVPageViewReadPageDown AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewReadPageDown)

/* AVPageViewGoBack */
#define AVPageViewGoBack AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGoBack)

/* AVPageViewGoForward */
#define AVPageViewGoForward AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGoForward)

/* AVPageViewToViewDest */
#define AVPageViewToViewDest AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewToViewDest)

/* AVPageViewInvalidateRect */
#define AVPageViewInvalidateRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewInvalidateRect)

/* AVPageViewDrawNow */
#define AVPageViewDrawNow AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewDrawNow)

/* AVPageViewInvertRect */
#define AVPageViewInvertRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewInvertRect)

/* AVPageViewInvertRectOutline */
#define AVPageViewInvertRectOutline AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewInvertRectOutline)

/* AVPageViewDrawRectOutline */
#define AVPageViewDrawRectOutline DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewDrawRectOutline)

/* AVPageViewDrawRect */
#define AVPageViewDrawRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewDrawRect)

/* AVPageViewGetMousePosition */
#define AVPageViewGetMousePosition DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewGetMousePosition)

/* AVPageViewDragOutNewRect */
#define AVPageViewDragOutNewRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewDragOutNewRect)

/* AVPageViewDragRect */
#define AVPageViewDragRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewDragRect)

/* AVAppRegisterForPageViewDrawing */
#define AVAppRegisterForPageViewDrawing DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppRegisterForPageViewDrawing)

/* AVAppUnregisterForPageViewDrawing */
/* note: still only uses one HFT entry, but compat layer needs to be notified about unregister before version 6*/
#define AVAppUnregisterForPageViewDrawing DECLARE_MULTIAWAREAVROUTINE(AcroViewHFT_VERSION_2,AcroViewHFT_VERSION_6, AVAppUnregisterForPageViewDrawing)

/* AVAppUnregisterForPageViewDrawingEx */
#define AVAppUnregisterForPageViewDrawingEx AVROUTINE(AcroViewHFT_VERSION_6, AVAppUnregisterForPageViewDrawingEx)

/* AVAppRegisterForPageViewClicks */
#define AVAppRegisterForPageViewClicks DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppRegisterForPageViewClicks)

/* AVAppUnregisterForPageViewClicks */
/* note: still only uses one HFT entry, but compat layer needs to be notified about unregister before version 6*/
#define AVAppUnregisterForPageViewClicks DECLARE_MULTIAWAREAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppUnregisterForPageViewClicks)

/* AVAppRegisterForPageViewAdjustCursor */
#define AVAppRegisterForPageViewAdjustCursor DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppRegisterForPageViewAdjustCursor)

/* AVAppUnregisterForPageViewAdjustCursor */
/* note: still only uses one HFT entry, but compat layer needs to be notified about unregister before version 6*/
#define AVAppUnregisterForPageViewAdjustCursor DECLARE_MULTIAWAREAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVAppUnregisterForPageViewAdjustCursor)

/* AVPageViewIsAnnotAtPoint */
#define AVPageViewIsAnnotAtPoint DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewIsAnnotAtPoint)

/* AVPageViewGetAnnotRect */
#define AVPageViewGetAnnotRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewGetAnnotRect)

/* AVPageViewSetAnnotLocation */
#define AVPageViewSetAnnotLocation DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewSetAnnotLocation)
 
/* AVPageViewStartReadingThread */
#define AVPageViewStartReadingThread AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewStartReadingThread)

/* AVPageViewGetThreadIndex */
#define AVPageViewGetThreadIndex AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetThreadIndex)

/* AVPageViewGetActiveBead */
#define AVPageViewGetActiveBead AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetActiveBead)

/* AVPageViewIsBeadAtPoint */
#define AVPageViewIsBeadAtPoint DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewIsBeadAtPoint)

#if !MAC_PLATFORM || (MAC_PLATFORM && !AS_ARCH_64BIT)
/* AVPageViewAcquireMachinePort */
/* Deprecated.  Use AVPageViewAcquireDrawContext instead */
#define AVPageViewAcquireMachinePort AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewAcquireMachinePort)

/* AVPageViewReleaseMachinePort */
/* Deprecated.  Use AVPageViewReleaseDrawContext instead */
#define AVPageViewReleaseMachinePort AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewReleaseMachinePort)
#endif

/* AVPageViewGetPageToDevMatrix */
#define AVPageViewGetPageToDevMatrix AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetPageToDevMatrix)

/* AVPageViewGetDevToPageMatrix */
#define AVPageViewGetDevToPageMatrix AVROUTINE(AcroViewHFT_VERSION_2, AVPageViewGetDevToPageMatrix)

/* AVPageViewPointToDevice */
#define AVPageViewPointToDevice DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewPointToDevice)

/* AVPageViewDevicePointToPage */
#define AVPageViewDevicePointToPage DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewDevicePointToPage)

/* AVPageViewRectToDevice */
#define AVPageViewRectToDevice DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewRectToDevice)

/* AVPageViewDeviceRectToPage */
#define AVPageViewDeviceRectToPage DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVPageViewDeviceRectToPage)

/* AVSysGetModifiers */
#define AVSysGetModifiers AVROUTINE(AcroViewHFT_VERSION_2, AVSysGetModifiers)

/* AVSysMouseIsStillDown */
#define AVSysMouseIsStillDown AVROUTINE(AcroViewHFT_VERSION_2, AVSysMouseIsStillDown)

/* AVSysBeep */
#define AVSysBeep AVROUTINE(AcroViewHFT_VERSION_2, AVSysBeep)

/* AVSysGetStandardCursor */
#define AVSysGetStandardCursor AVROUTINE(AcroViewHFT_VERSION_2, AVSysGetStandardCursor)

/* AVSysSetCursor */
#define AVSysSetCursor AVROUTINE(AcroViewHFT_VERSION_2, AVSysSetCursor)

/* AVSysGetCursor */
#define AVSysGetCursor AVROUTINE(AcroViewHFT_VERSION_2, AVSysGetCursor)



/* AVToolGetType */
#define AVToolGetType AVROUTINE(AcroViewHFT_VERSION_2, AVToolGetType)

/* AVToolIsPersistent */
#define AVToolIsPersistent AVROUTINE(AcroViewHFT_VERSION_2, AVToolIsPersistent)

/* AVWindowNew */
#define AVWindowNew DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2,AcroViewHFT_VERSION_6, AVWindowNew)

/* AVWindowNewFromPlatformThing */
#define AVWindowNewFromPlatformThing DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowNewFromPlatformThing)

/* AVWindowDestroy */
#define AVWindowDestroy AVROUTINE(AcroViewHFT_VERSION_2, AVWindowDestroy)

/* AVWindowUserClose */
#define AVWindowUserClose AVROUTINE(AcroViewHFT_VERSION_2, AVWindowUserClose)

/* AVWindowMaximize */
#define AVWindowMaximize AVROUTINE(AcroViewHFT_VERSION_2, AVWindowMaximize)

/* AVWindowShow */
#define AVWindowShow AVROUTINE(AcroViewHFT_VERSION_2, AVWindowShow)

/* AVWindowHide */
#define AVWindowHide AVROUTINE(AcroViewHFT_VERSION_2, AVWindowHide)

/* AVWindowIsVisible */
#define AVWindowIsVisible AVROUTINE(AcroViewHFT_VERSION_2, AVWindowIsVisible)

/* AVWindowGetPlatformThing */
#define AVWindowGetPlatformThing AVROUTINE(AcroViewHFT_VERSION_2, AVWindowGetPlatformThing)

/* AVWindowGetOwnerData */
#define AVWindowGetOwnerData AVROUTINE(AcroViewHFT_VERSION_2, AVWindowGetOwnerData)

/* AVWindowSetOwnerData */
#define AVWindowSetOwnerData AVROUTINE(AcroViewHFT_VERSION_2, AVWindowSetOwnerData)

/* AVWindowGetTitle */
#define AVWindowGetTitle DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowGetTitle)

/* AVWindowSetTitle */
#define AVWindowSetTitle DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowSetTitle)

/* AVWindowGetFrame */
#define AVWindowGetFrame DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowGetFrame)

/* AVWindowSetFrame */
#define AVWindowSetFrame DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowSetFrame)

/* AVWindowGetInterior */
#define AVWindowGetInterior DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowGetInterior)

/* AVWindowBringToFront */
#define AVWindowBringToFront AVROUTINE(AcroViewHFT_VERSION_2, AVWindowBringToFront)

/* AVWindowInvalidateRect */
#define AVWindowInvalidateRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2, AcroViewHFT_VERSION_6, AVWindowInvalidateRect)

/* AVWindowDrawNow */
#define AVWindowDrawNow AVROUTINE(AcroViewHFT_VERSION_2, AVWindowDrawNow)

/* AVWindowSetWantsKey */
#define AVWindowSetWantsKey AVROUTINE(AcroViewHFT_VERSION_2, AVWindowSetWantsKey)

/* AVWindowIsKey */
#define AVWindowIsKey AVROUTINE(AcroViewHFT_VERSION_2, AVWindowIsKey)

/* AVWindowBecomeKey */
#define AVWindowBecomeKey AVROUTINE(AcroViewHFT_VERSION_2, AVWindowBecomeKey)

/* AVWindowResignKey */
#define AVWindowResignKey AVROUTINE(AcroViewHFT_VERSION_2, AVWindowResignKey)

/* AVGrafSelectCreate */
#define AVGrafSelectCreate AVROUTINE(AcroViewHFT_VERSION_2, AVGrafSelectCreate)

/* AVGrafSelectDestroy */
#define AVGrafSelectDestroy AVROUTINE(AcroViewHFT_VERSION_2, AVGrafSelectDestroy)

/* AVGrafSelectGetBoundingRect */
#define AVGrafSelectGetBoundingRect AVROUTINE(AcroViewHFT_VERSION_2, AVGrafSelectGetBoundingRect)

/* AVCryptDoStdSecurity */
#define AVCryptDoStdSecurity AVROUTINE(AcroViewHFT_VERSION_2, AVCryptDoStdSecurity)

/* AVCryptGetPassword */
#define AVCryptGetPassword AVROUTINE(AcroViewHFT_VERSION_2, AVCryptGetPassword)

/* AVDocDoSave */
#define AVDocDoSave AVROUTINE(AcroViewHFT_VERSION_2, AVDocDoSave)

/* 
** If you need to use AVDocGetClientName(), AVDocSetClientName(), or AVPageViewGetText() 
** from within your plug-in, you will need to bump up the value of PI_ACROVIEW_VERSION 
** in PIRequir.h to 0x00020001.
*/

/* AVDocGetClientName */
#define AVDocGetClientName AVROUTINE(AcroViewHFT_VERSION_2_1, AVDocGetClientName)

/* AVDocSetClientName */
#define AVDocSetClientName AVROUTINE(AcroViewHFT_VERSION_2_1, AVDocSetClientName)

/* AVDocGetPageText */
#define AVDocGetPageText AVROUTINE(AcroViewHFT_VERSION_2_1, AVDocGetPageText)


/* 
** If you need to use these calls from within your plug-in, you will need to bump up
** the value of PI_ACROVIEW_VERSION in PIRequir.h to 0x00020002.
*/


#if PLUGIN  //Plugins may use the toolbar API to manipulate items in the tools panel

#define AVAppGetToolBarByName AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetLegacyToolBarByName)
#define AVAppGetToolBar AVROUTINE(AcroViewHFT_VERSION_2, AVAppGetLegacyToolBar)
#define AVAppRegisterToolBarPosition DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5,AcroViewHFT_VERSION_6, AVAppRegisterLegacyToolBarPosition)

/* AVToolBarGetFrame (obsolete) */
#define AVToolBarGetFrame AVROUTINE(AcroViewHFT_VERSION_2, oldAVLegacyToolBarGetFrame)

/* AVToolBarGetButtonByName */
#define AVToolBarGetButtonByName AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolBarGetButtonByName)

/* AVToolBarEnumButtons */
#define AVToolBarEnumButtons AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolBarEnumButtons)

/* AVToolBarAddButton */
#define AVToolBarAddButton AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolBarAddButton)

/* AVToolBarGetNumButtons */
#define AVToolBarGetNumButtons AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolBarGetNumButtons)

/* AVToolBarIsRoomFor */
#define AVToolBarIsRoomFor AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolBarIsRoomFor)

/* AVToolBarUpdateButtonStates */
#define AVToolBarUpdateButtonStates AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolBarUpdateButtonStates)

/* AVToolButtonNew */
#define AVToolButtonNew AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonNew)

/* AVToolButtonDestroy */
#define AVToolButtonDestroy AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonDestroy)

/* AVToolButtonRemove */
#define AVToolButtonRemove AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonRemove)

/* AVToolButtonIsSeparator */
#define AVToolButtonIsSeparator AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonIsSeparator)

/* AVToolButtonGetName */
#define AVToolButtonGetName AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonGetName)

/*  */
#define AVToolButtonExecute AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonExecute)

/* AVToolButtonSetExecuteProc */
#define AVToolButtonSetExecuteProc AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonSetExecuteProc)

/* AVToolButtonSetComputeEnabledProc */
#define AVToolButtonSetComputeEnabledProc AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonSetComputeEnabledProc)

/* AVToolButtonSetComputeMarkedProc */
#define AVToolButtonSetComputeMarkedProc AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonSetComputeMarkedProc)

/* AVToolButtonIsEnabled */
#define AVToolButtonIsEnabled AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonIsEnabled)

/* AVToolButtonIsMarked */
#define AVToolButtonIsMarked AVROUTINE(AcroViewHFT_VERSION_2, AVLegacyToolButtonIsMarked)

#define AVToolButtonSetHelpText AVROUTINE(AcroViewHFT_VERSION_2_2, AVLegacyToolButtonSetHelpText)
#define AVToolButtonSetHelpTextWithASText AVROUTINE(AcroViewHFT_VERSION_10, AVLegacyToolButtonSetHelpTextWithASText)

#define AVToolButtonSetExternal AVROUTINE(AcroViewHFT_VERSION_2_2, AVLegacyToolButtonSetExternal)
#define AVToolBarNewFlyout AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolBarNewFlyout)
#define AVToolButtonSetFlyout AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolButtonSetFlyout)
#define AVToolButtonGetFlyout AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolButtonGetFlyout)

#define AVToolButtonSetMenu AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolButtonSetMenu)
#define AVToolButtonGetMenu AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolButtonGetMenu)

#define AVToolButtonSetIcon AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolButtonSetIcon)
#define AVToolButtonGetIcon AVROUTINE(AcroViewHFT_VERSION_4, AVLegacyToolButtonGetIcon)

//	tool button animation support...
#define AVToolButtonAddAnimationIcon AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonAddAnimationIcon)
#define AVToolButtonGetAnimationIconCount AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonGetAnimationIconCount)
#define AVToolButtonStartAnimation AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonStartAnimation)
#define AVToolButtonStopAnimation AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonStopAnimation)
#define AVToolButtonIsAnimationRunning AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonIsAnimationRunning)
#define AVToolButtonSetAnimationPeriod AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonSetAnimationPeriod)
#define AVToolButtonGetAnimationPeriod AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonGetAnimationPeriod)
#define AVToolButtonRemoveAnimationIcons AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonRemoveAnimationIcons)

/* sets the Mega Tooltip compute proc*/
#define AVToolButtonSetComputeTooltipProc AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonSetComputeTooltipProc)
/* sets routine to be called before regular tooltip */
#define AVToolButtonSetNotifyTooltipProc AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonSetNotifyTooltipProc)

#define AVToolButtonSetLabelText AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonSetLabelText)
#define AVToolButtonGetLabelText AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonGetLabelText)
/* AVToolButtonSetComputeVisibleProc */
#define AVToolButtonSetComputeVisibleProc AVROUTINE(AcroViewHFT_VERSION_6, AVLegacyToolButtonSetComputeVisibleProc)
#define AVToolButtonSetMenuIcon AVROUTINE(AcroViewHFT_VERSION_8, AVLegacyToolButtonSetMenuIcon)
#define AVToolBarAddButtonEx AVROUTINE(AcroViewHFT_VERSION_9, AVLegacyToolBarAddButtonEx)
#define AVToolBarNew AVROUTINE(AcroViewHFT_VERSION_5, AVLegacyToolBarNew)
#define AVToolBarNewWithASText AVROUTINE(AcroViewHFT_VERSION_10, AVLegacyToolBarNewWithASText)

#endif

#define AVPageViewTrackText DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVPageViewTrackText)

#define AVPageViewHighlightText AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewHighlightText)

#define AVPageViewInvalidateText AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewInvalidateText)


#define AVPageViewPointInText DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVPageViewPointInText)

#define AVPageViewGetFirstVisiblePageNum AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewGetFirstVisiblePageNum)

#define AVPageViewGetLastVisiblePageNum AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewGetLastVisiblePageNum)

#define AVPageViewPageNumIsVisible AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewPageNumIsVisible)

#define AVPageViewSetPageNum AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewSetPageNum)

#define AVPageViewGetSelectedAnnotPageNum AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewGetSelectedAnnotPageNum)

#define AVDocSendAuxData AVROUTINE(AcroViewHFT_VERSION_2_2, AVDocSendAuxData)

#define AVHasAuxDataHandler AVROUTINE(AcroViewHFT_VERSION_2_2, AVHasAuxDataHandler)

#if ACRO_SDK_LEVEL >= 0x00090000
#define AVRegisterAuxDataHandler AVROUTINE(AcroViewHFT_VERSION_9, AVRegisterAuxDataHandler)
#else
#define AVRegisterAuxDataHandler AVROUTINE(AcroViewHFT_VERSION_2_2, oldAVRegisterAuxDataHandler)
#endif

#define AVUnregisterAuxDataHandler AVROUTINE(AcroViewHFT_VERSION_2_2, AVUnregisterAuxDataHandler)

#define AVDocPrintPagesWithParams DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVDocPrintPagesWithParams)

#define AVPageViewDrawCosObj DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVPageViewDrawCosObj)

#define AVDocSetDead AVROUTINE(AcroViewHFT_VERSION_2_2, AVDocSetDead)

#define AVAppIsIdle AVROUTINE(AcroViewHFT_VERSION_2_2, AVAppIsIdle)

#define AVDocOpenFromASFileWithParams DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVDocOpenFromASFileWithParams)

#define AVPageViewGetNextView AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewGetNextView)

#define AVDocGetViewDef DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVDocGetViewDef)

#define AVDocSetViewDef DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVDocSetViewDef)

#define AVWindowHandlePlatformEvent AVROUTINE(AcroViewHFT_VERSION_2_2, AVWindowHandlePlatformEvent)

#define AVWindowGetCursorAtPoint AVROUTINE(AcroViewHFT_VERSION_2_2, AVWindowGetCursorAtPoint)

#define AVDocDoActionPropsDialog AVROUTINE(AcroViewHFT_VERSION_2_2, AVDocDoActionPropsDialog)

#define AVAppGetTransHandlerByType AVROUTINE(AcroViewHFT_VERSION_2_2, AVAppGetTransHandlerByType)

#define AVAppEnumTransHandlers AVROUTINE(AcroViewHFT_VERSION_2_2, AVAppEnumTransHandlers)

#define AVAppRegisterTransHandler AVROUTINE(AcroViewHFT_VERSION_2_2, AVAppRegisterTransHandler)

#define AVDocDoSaveAs AVROUTINE(AcroViewHFT_VERSION_2_2, AVDocDoSaveAs)

#define AVPageViewSetLayoutMode AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewSetLayoutMode)

#define AVPageViewGetLayoutMode AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewGetLayoutMode)

#define AVPageViewInsetRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_2, AcroViewHFT_VERSION_6, AVPageViewInsetRect)

#define AVDocIsExternal AVROUTINE(AcroViewHFT_VERSION_2_2, AVDocIsExternal)

#define AVPageViewUseThisDestination AVROUTINE(AcroViewHFT_VERSION_2_2, AVPageViewUseThisDestination)

#define AVAuthOpen AVROUTINE(AcroViewHFT_VERSION_2_2, AVAuthOpen)


/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_ACROVIEW_VERSION in PIRequir.h to
** 0x00020003.
*/

#define AVDocCopyAnnot AVROUTINE(AcroViewHFT_VERSION_2_3, AVDocCopyAnnot)

#define AVDocCopyAnnotCommon AVROUTINE(AcroViewHFT_VERSION_2_3, AVDocCopyAnnotCommon)

#define AVDocCopyAction AVROUTINE(AcroViewHFT_VERSION_2_3, AVDocCopyAction)

#define AVDocCopyActionCommon AVROUTINE(AcroViewHFT_VERSION_2_3, AVDocCopyActionCommon)

#define AVDocCopyAdditionalActions AVROUTINE(AcroViewHFT_VERSION_2_3, AVDocCopyAdditionalActions)

#define AVPageViewDrawCosObjEx DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_2_3, AcroViewHFT_VERSION_6, AVPageViewDrawCosObjEx)

/* AVPageViewToDestInfo */
#define AVPageViewToDestInfo AVROUTINE(AcroViewHFT_VERSION_2_3, AVPageViewToDestInfo)

/* AVPageViewUseDestInfo */
#define AVPageViewUseDestInfo AVROUTINE(AcroViewHFT_VERSION_2_3, AVPageViewUseDestInfo)

/* AVDestInfoDestroy */
#define AVDestInfoDestroy AVROUTINE(AcroViewHFT_VERSION_2_3, AVDestInfoDestroy)


/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_AcroViewHFT_VERSION in PIRequir.h to
** 0x00040000.
*/


/* AVPageViewDrawAnnotSequence */
#define AVPageViewDrawAnnotSequence DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_4, AcroViewHFT_VERSION_6, AVPageViewDrawAnnotSequence)

/* AVDocDoPrint */
#define AVDocDoPrint AVROUTINE(AcroViewHFT_VERSION_4, AVDocDoPrint)

/* AVDocDoSaveAsWithParams */
#define AVDocDoSaveAsWithParams AVROUTINE(AcroViewHFT_VERSION_4, AVDocDoSaveAsWithParams)

#define AVAnnotHandlerGetInfo AVROUTINE(AcroViewHFT_VERSION_4, AVAnnotHandlerGetInfo)
#define AVAnnotHandlerDeleteInfo AVROUTINE(AcroViewHFT_VERSION_4, AVAnnotHandlerDeleteInfo)
#define AVAnnotHandlerGetAnnotInfo AVROUTINE(AcroViewHFT_VERSION_4, AVAnnotHandlerGetAnnotInfo)
#define AVAnnotHandlerDeleteAnnotInfo AVROUTINE(AcroViewHFT_VERSION_4, AVAnnotHandlerDeleteAnnotInfo)

#define AVPageViewDoPopupMenu DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_4, AcroViewHFT_VERSION_6, AVPageViewDoPopupMenu)

#define AVPageViewTransformRectRZ AVROUTINE(AcroViewHFT_VERSION_4, AVPageViewTransformRectRZ)
#define AVPageViewAppearanceGetAVMatrix AVROUTINE(AcroViewHFT_VERSION_4, AVPageViewAppearanceGetAVMatrix)

/* AVPageViewGetVisibleAnnotPage */
#define AVPageViewGetVisibleAnnotPage AVROUTINE(AcroViewHFT_VERSION_4, AVPageViewGetVisibleAnnotPage)

/* AVPageViewInvertQuad */
#define AVPageViewInvertQuad DECLARE_MULTIAWAREAVROUTINE(AcroViewHFT_VERSION_4, AcroViewHFT_VERSION_6, AVPageViewInvertQuad)

/* AVSysAllocTimeStringFromTimeRec / AVSysTimeASTextFromTimeRec */
#define AVSysAllocTimeStringFromTimeRec AVROUTINE(AcroViewHFT_VERSION_4, AVSysAllocTimeStringFromTimeRec)
#define AVSysTimeASTextFromTimeRec AVROUTINE( AcroViewHFT_VERSION_8, AVSysTimeASTextFromTimeRec )

/* AVAppHandlePlatformEvent */
#define AVAppHandlePlatformEvent AVROUTINE(AcroViewHFT_VERSION_4, AVAppHandlePlatformEvent)

/* AVDocSetReadOnly */
#define AVDocSetReadOnly AVROUTINE(AcroViewHFT_VERSION_4, AVDocSetReadOnly)

/* AVDocIsReadOnly */
#define AVDocIsReadOnly AVROUTINE(AcroViewHFT_VERSION_4, AVDocIsReadOnly)

/* AVPageViewShowControl */
#define AVPageViewShowControl AVROUTINE(AcroViewHFT_VERSION_4, AVPageViewShowControl)

/* AVPageViewDeviceRectToPageRZ */
#define AVPageViewDeviceRectToPageRZ DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_4, AcroViewHFT_VERSION_6, AVPageViewDeviceRectToPageRZ)

#define AVDocAlert AVROUTINE(AcroViewHFT_VERSION_4, AVDocAlert)
#define AVDocAlertNote AVROUTINE(AcroViewHFT_VERSION_4, AVDocAlertNote)
#define AVDocAlertConfirm AVROUTINE(AcroViewHFT_VERSION_4, AVDocAlertConfirm)
#define AVDocAlertYesNo AVROUTINE(AcroViewHFT_VERSION_4, AVDocAlertYesNo)

#define AVMenubarAddHiddenMenu AVROUTINE(AcroViewHFT_VERSION_4, AVMenubarAddHiddenMenu)
#define AVMenuIsHiddenOnMenubar AVROUTINE(AcroViewHFT_VERSION_4, AVMenuIsHiddenOnMenubar)

#define AVAppOpenHelpFile AVROUTINE(AcroViewHFT_VERSION_4, AVAppOpenHelpFile)
#define AVAppOpenHelpFileWithParams AVROUTINE(AcroViewHFT_VERSION_6, AVAppOpenHelpFileWithParams)
#define AVAppHelpShowContents AVROUTINE(AcroViewHFT_VERSION_6, AVAppHelpShowContents)
#define AVAppHelpSearch AVROUTINE(AcroViewHFT_VERSION_6, AVAppHelpSearch)
#define AVAppHelpShowIndex AVROUTINE(AcroViewHFT_VERSION_6, AVAppHelpShowIndex)
#define AVPageViewGetGrayRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_4, AcroViewHFT_VERSION_6, AVPageViewGetGrayRect)

#define AVDocSelectionEnumPageRanges AVROUTINE(AcroViewHFT_VERSION_4, AVDocSelectionEnumPageRanges)

#define AVDocDoCopyAs AVROUTINE(AcroViewHFT_VERSION_4, AVDocDoCopyAs)


/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_ACROVIEW_VERSION in PIRequir.h to
** 0x00040005.
*/


/* AVWindowGetMinMaxSize */
#define AVWindowGetMinMaxSize DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_4_5, AcroViewHFT_VERSION_6, AVWindowGetMinMaxSize)

/* AVWindowSetMinMaxSize */
#define AVWindowSetMinMaxSize DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_4_5, AcroViewHFT_VERSION_6, AVWindowSetMinMaxSize)

/* AVAppRegisterForPageViewKeyDown */
#define AVAppRegisterForPageViewKeyDown AVROUTINE(AcroViewHFT_VERSION_4_5, AVAppRegisterForPageViewKeyDown)

/* AVAppUnregisterForPageViewKeyDown */
#define AVAppUnregisterForPageViewKeyDown AVROUTINE(AcroViewHFT_VERSION_4_5, AVAppUnregisterForPageViewKeyDown)


/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_ACROVIEW_VERSION in PIRequir.h to
** 0x00050000.
*/

#define AVAppRegisterToPDFHandler AVROUTINE(AcroViewHFT_VERSION_5, AVAppRegisterToPDFHandler)
#define AVAppRegisterFromPDFHandler AVROUTINE(AcroViewHFT_VERSION_5, AVAppRegisterFromPDFHandler)
#define AVConversionEnumToPDFConverters AVROUTINE(AcroViewHFT_VERSION_5, AVConversionEnumToPDFConverters)
#define AVConversionEnumFromPDFConverters AVROUTINE(AcroViewHFT_VERSION_5, AVConversionEnumFromPDFConverters)
#define AVConversionConvertToPDFWithHandler AVROUTINE(AcroViewHFT_VERSION_5, AVConversionConvertToPDFWithHandler)
#define AVConversionConvertFromPDFWithHandler AVROUTINE(AcroViewHFT_VERSION_5, AVConversionConvertFromPDFWithHandler)
#define AVConversionConvertToPDF AVROUTINE(AcroViewHFT_VERSION_5, AVConversionConvertToPDF)

#define AVCommandNew AVROUTINE(AcroViewHFT_VERSION_5, AVCommandNew)

#define AVCommandDestroy AVROUTINE(AcroViewHFT_VERSION_5, AVCommandDestroy)

#define AVCommandGetName AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetName)

#define AVCommandGetStatus AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetStatus)

#define AVCommandGetCab AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetCab)

#define AVCommandPutCab AVROUTINE(AcroViewHFT_VERSION_5, AVCommandPutCab)

#define AVCommandSetParams AVROUTINE(AcroViewHFT_VERSION_5, AVCommandSetParams)

#define AVCommandGetParams AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetParams)

#define AVCommandSetConfig AVROUTINE(AcroViewHFT_VERSION_5, AVCommandSetConfig)

#define AVCommandGetConfig AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetConfig)

#define AVCommandGetProps AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetProps)

#define AVCommandSetInputs AVROUTINE(AcroViewHFT_VERSION_5, AVCommandSetInputs)

#define AVCommandGetInputs AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetInputs)

#define AVCommandShowDialog AVROUTINE(AcroViewHFT_VERSION_5, AVCommandShowDialog)

#define AVCommandWork AVROUTINE(AcroViewHFT_VERSION_5, AVCommandWork)

#define AVCommandCancel AVROUTINE(AcroViewHFT_VERSION_5, AVCommandCancel)

#define AVCommandReset AVROUTINE(AcroViewHFT_VERSION_5, AVCommandReset)

#define AVCommandGetUIPolicy AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetUIPolicy)

#define AVCommandGetAVDoc AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetAVDoc)

#define AVCommandGetPDDoc AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetPDDoc)

#define AVCommandGetReportProc AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetReportProc)

#define AVCommandGetProgressMonitor AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetProgressMonitor)

#define AVCommandGetCancelProc AVROUTINE(AcroViewHFT_VERSION_5, AVCommandGetCancelProc)

#define AVAppRegisterCommandHandler AVROUTINE(AcroViewHFT_VERSION_5, AVAppRegisterCommandHandler)

#define AVAppFindCommandHandlerByName AVROUTINE(AcroViewHFT_VERSION_5, AVAppFindCommandHandlerByName)

#define AVAppRegisterGlobalCommand AVROUTINE(AcroViewHFT_VERSION_5, AVAppRegisterGlobalCommand)

#define AVAppFindGlobalCommandByName AVROUTINE(AcroViewHFT_VERSION_5, AVAppFindGlobalCommandByName)

#define AVAppUnregisterGlobalCommand AVROUTINE(AcroViewHFT_VERSION_5, AVAppUnregisterGlobalCommand)

#define AVCommandExecute AVROUTINE(AcroViewHFT_VERSION_5, AVCommandExecute)

#define AVAppOpenDialog DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVAppOpenDialog)

#define AVAppSaveDialog DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVAppSaveDialog)

#define AVAppChooseFolderDialog DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVAppChooseFolderDialog)

#define AVAcquireSpecialFolderPathName AVROUTINE(AcroViewHFT_VERSION_5, AVAcquireSpecialFolderPathName)

#define AVAcquireSpecialFilePathName AVROUTINE(AcroViewHFT_VERSION_5, AVAcquireSpecialFilePathName)

#define AVPageViewGetFocusAnnot AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewGetFocusAnnot)

#define AVPageViewSetFocusAnnot AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewSetFocusAnnot)

#define AVPageViewClearFocusAnnot AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewClearFocusAnnot)

#define AVPageViewIsFocusAnnot AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewIsFocusAnnot)

#define AVUtilGetBaseNameAndExtensionByPathName AVROUTINE(AcroViewHFT_VERSION_5, AVUtilGetBaseNameAndExtensionByPathName)

#define AVUtilGetBaseNameAndExtensionByString AVROUTINE(AcroViewHFT_VERSION_5, AVUtilGetBaseNameAndExtensionByString)

#define AVIdentityGetText AVROUTINE(AcroViewHFT_VERSION_5, AVIdentityGetText)

#define AVIdentitySetText AVROUTINE(AcroViewHFT_VERSION_5, AVIdentitySetText)

#define AVPageViewFocusAnnotPerformOp AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewFocusAnnotPerformOp)

#define AVPageViewFilterKeyDownForFocusAnnot AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewFilterKeyDownForFocusAnnot)

#define AVPageViewGhostRectOutline DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewGhostRectOutline)

#define AVPageViewSnapPoint DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewSnapPoint)

#define AVPageViewSnapPointEx AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewSnapPointEx)

#define AVPageViewGetMousePositionSnapped DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewGetMousePositionSnapped)

#define AVPageViewDragOutNewRectSnapped DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewDragOutNewRectSnapped)

#define AVPageViewDragRectSnapped DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewDragRectSnapped)

#define AVPageViewDragRectSnappedEx AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewDragRectSnappedEx)

#define AVRectHandleHitTest DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVRectHandleHitTest)

#define AVPageViewDrawRectOutlineWithHandles DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewDrawRectOutlineWithHandles)

#define AVPageViewIsAnnotOfTypeAtPoint DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewIsAnnotOfTypeAtPoint)

#define AVWindowCenter AVROUTINE(AcroViewHFT_VERSION_5, AVWindowCenter)

#define AVDocFromPDDoc AVROUTINE(AcroViewHFT_VERSION_5, AVDocFromPDDoc)

#define AVPageViewSnapRect DECLARE_MULTIAVROUTINE(AcroViewHFT_VERSION_5, AcroViewHFT_VERSION_6, AVPageViewSnapRect)

#define AVAppGetReportProc AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetReportProc)

#define AVDocIsDead AVROUTINE(AcroViewHFT_VERSION_5, AVDocIsDead)

#define AVAppGetPrefBool AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefBool)

#define AVAppGetPrefInt AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefInt)

#define AVAppGetPrefAtom AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefAtom)

#define AVAppGetPrefDouble AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefDouble)

#define AVAppGetPrefString AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefString)

#define AVAppGetPrefText AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefText)

#define AVAppGetPrefCab AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefCab)

#define AVAppGetPrefPathName AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetPrefPathName)

#define AVAlertWithParams AVROUTINE(AcroViewHFT_VERSION_5, AVAlertWithParams)

#define AVDocPerformActionEx AVROUTINE(AcroViewHFT_VERSION_5, AVDocPerformActionEx)

#define AVExtensionGetNumPlugIns AVROUTINE(AcroViewHFT_VERSION_5, AVExtensionGetNumPlugIns)

#define AVExtensionAcquireInfo AVROUTINE(AcroViewHFT_VERSION_5, AVExtensionAcquireInfo)

#define AVExtensionReleaseInfo AVROUTINE(AcroViewHFT_VERSION_5, AVExtensionReleaseInfo)

#define AVPageViewDeviceToInfo AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewDeviceToInfo)

#define AVPageViewInfoToDevice AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewInfoToDevice)

#define AVPageViewPointToInfo AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewPointToInfo)

#define AVPageViewInfoToPoint AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewInfoToPoint)

#define AVPageViewUpdateInfoPanel AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewUpdateInfoPanel)

#define AVAppGetLanguageEncoding AVROUTINE(AcroViewHFT_VERSION_5, AVAppGetLanguageEncoding)

#define AVAlertResetPrefs AVROUTINE(AcroViewHFT_VERSION_5, AVAlertResetPrefs)

#define AVAlertSetPref AVROUTINE(AcroViewHFT_VERSION_5, AVAlertSetPref)

#define AVAlertGetPref AVROUTINE(AcroViewHFT_VERSION_5, AVAlertGetPref)

#define AVPageViewScrollToAnnot AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewScrollToAnnot)

#define AVSysSetWaitCursor AVROUTINE(AcroViewHFT_VERSION_5, AVSysSetWaitCursor)

#define AVDocPermRequest AVROUTINE(AcroViewHFT_VERSION_5, AVDocPermRequest)

#define AVPageViewSuspendOffscreenDrawing AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewSuspendOffscreenDrawing)

#define AVPageViewResumeOffscreenDrawing AVROUTINE(AcroViewHFT_VERSION_5, AVPageViewResumeOffscreenDrawing)

#define AVAppDidOrWillSwitchForDialog AVROUTINE(AcroViewHFT_VERSION_5, AVAppDidOrWillSwitchForDialog)

#define AVAppYieldToOtherApps AVROUTINE(AcroViewHFT_VERSION_5, AVAppYieldToOtherApps)

#define AVWindowEnsureInBounds AVROUTINE(AcroViewHFT_VERSION_5, AVWindowEnsureInBounds)

/* PI_ACROVIEW_VERSION >= 0x00050001		5.0SP1 */

/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_ACROVIEW_VERSION in PIRequir.h to
** 0x00050001.
*/

/* AVMenuClone */
#define AVMenuClone AVROUTINE(AcroViewHFT_VERSION_5_1, AVMenuClone)

/* PI_ACROVIEW_VERSION >= AcroViewHFT_VERSION_6		6.0 Newport */
/* 
** If you need to use these calls from within your plug-in, you will
** need to bump up the value of PI_ACROVIEW_VERSION in PIRequir.h to
** AcroViewHFT_VERSION_6.
*/

/* PI_ACROVIEW_VERSION >= AcroViewHFT_VERSION_6		6 */
#define AVAppGetUUID AVROUTINE(AcroViewHFT_VERSION_6, AVAppGetUUID)

#define AVSysGetIconFromFilename AVROUTINE(AcroViewHFT_VERSION_6, AVSysGetIconFromFilename)
#define AVSysGetIconFromMimeType AVROUTINE(AcroViewHFT_VERSION_6, AVSysGetIconFromMimeType)
#define AVSysGetIconFromTypeAndCreator AVROUTINE(AcroViewHFT_VERSION_6, AVSysGetIconFromTypeAndCreator)

#define AVConversionConvertStreamToPDFWithHandler AVROUTINE(AcroViewHFT_VERSION_6, AVConversionConvertStreamToPDFWithHandler)
#define AVConversionConvertStreamFromPDFWithHandler AVROUTINE(AcroViewHFT_VERSION_6, AVConversionConvertStreamFromPDFWithHandler)
#define AVConversionConvertStreamFromStructNodeWithHandler AVROUTINE(AcroViewHFT_VERSION_6, AVConversionConvertStreamFromStructNodeWithHandler)
#define AVConversionConvertStreamToPDF AVROUTINE(AcroViewHFT_VERSION_6, AVConversionConvertStreamToPDF)

/* AVMenuDoPopUp */
#define AVMenuDoPopUp AVROUTINE(AcroViewHFT_VERSION_6, AVMenuDoPopUp)

#define AVDocGetNumPageViews AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetNumPageViews)
#define AVDocGetNthPageView  AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetNthPageView)

/* AVMenu and AVMenuItem variants that use ASText instead of char* */
#define AVMenuNewWithASText AVROUTINE(AcroViewHFT_VERSION_6, AVMenuNewWithASText)
#define AVMenuGetTitleAsASText AVROUTINE(AcroViewHFT_VERSION_6, AVMenuGetTitleAsASText)
#define AVMenuItemNewWithASText AVROUTINE(AcroViewHFT_VERSION_6, AVMenuItemNewWithASText)
#define AVMenuItemGetTitleAsASText AVROUTINE(AcroViewHFT_VERSION_6, AVMenuItemGetTitleAsASText)
#define AVMenuItemSetTitleWithASText AVROUTINE(AcroViewHFT_VERSION_6, AVMenuItemSetTitleWithASText)

#define AVUtilGetBaseNameAndExtensionEx AVROUTINE(AcroViewHFT_VERSION_6, AVUtilGetBaseNameAndExtensionEx)

#define AVAcquireSpecialFilePathNameWithASText AVROUTINE(AcroViewHFT_VERSION_6, AVAcquireSpecialFilePathNameWithASText)

#define AVPageViewSetVisibleInks AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewSetVisibleInks)
#define AVPageViewSetInkPreview AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewSetInkPreview)
#define AVPageViewGetNumVisibleInks AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewGetNumVisibleInks)
#define AVPageViewGetVisibleInks AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewGetVisibleInks)
#define AVPageViewGetPixelInformationAtPoint AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewGetPixelInformationAtPoint)

/* AVUndo stuff */
#define AVUndoNew AVROUTINE(AcroViewHFT_VERSION_6, AVUndoNew)
#define AVUndoSetData AVROUTINE(AcroViewHFT_VERSION_6, AVUndoSetData)
#define AVUndoGetData AVROUTINE(AcroViewHFT_VERSION_6, AVUndoGetData)
#define AVUndoGetAVDoc AVROUTINE(AcroViewHFT_VERSION_6, AVUndoGetAVDoc)
#define AVUndoGetType AVROUTINE(AcroViewHFT_VERSION_6, AVUndoGetType)
#define AVDocClearUndos AVROUTINE(AcroViewHFT_VERSION_6, AVDocClearUndos)
#define AVDocGetTopUndo AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetTopUndo)
#define AVDocGetTopUndoAndRedo AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetTopUndoAndRedo)
#define AVDocBeginUndoOperation AVROUTINE(AcroViewHFT_VERSION_6, AVDocBeginUndoOperation)
#define AVDocEndUndoOperation AVROUTINE(AcroViewHFT_VERSION_6, AVDocEndUndoOperation)

/* AVPageViewDrawNowWithTransition */
#define AVPageViewDrawNowWithTransition AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewDrawNowWithTransition)

#define AVDocPrintSeparations AVROUTINE(AcroViewHFT_VERSION_6, AVDocPrintSeparations)
#define AVWindowDoModal AVROUTINE(AcroViewHFT_VERSION_6, AVWindowDoModal)
#define AVWindowEndModal AVROUTINE(AcroViewHFT_VERSION_6, AVWindowEndModal)
#define AVSysGetUsePenForInput AVROUTINE(AcroViewHFT_VERSION_6, AVSysGetUsePenForInput)

/* Cab-based ViewDefEx calls */
#define AVDocGetViewDefEx AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetViewDefEx)
#define AVDocSetViewDefEx AVROUTINE(AcroViewHFT_VERSION_6, AVDocSetViewDefEx)
#define AVDocUseViewDefEx AVROUTINE(AcroViewHFT_VERSION_6, AVDocUseViewDefEx)

/* AVMenuClone */
#define AVMenuItemClone AVROUTINE(AcroViewHFT_VERSION_6, AVMenuItemClone)

/* AVAppGetLanguage */
#define AVAppGetLanguageWithParams AVROUTINE(AcroViewHFT_VERSION_6, AVAppGetLanguageWithParams)

/* AVIconBundle6 APIs */
#define AVAppCreateIconBundle6 AVROUTINE(AcroViewHFT_VERSION_6, AVAppCreateIconBundle6)

/* AVWindowGetBorderWidths */
#define AVWindowGetBorderWidths AVROUTINE(AcroViewHFT_VERSION_6, AVWindowGetBorderWidths)

/* AVPageViewDrawPolygon */
#define AVPageViewDrawPolygon AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewDrawPolygon)

/* AVPageViewDrawPolygonOutline */
#define AVPageViewDrawPolygonOutline AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewDrawPolygonOutline)

/* AVAppRegisterHowToPanel */
#define AVAppRegisterHowToPanel AVROUTINE(AcroViewHFT_VERSION_6, AVAppRegisterHowToPanel)

/* AVAppSetHowToPanelAutoShowText */
#define AVAppSetHowToPanelAutoShowText AVROUTINE(AcroViewHFT_VERSION_6, AVAppSetHowToPanelAutoShowText)

/* AVAppGetHowToPanelAutoShow */
#define AVAppGetHowToPanelAutoShow AVROUTINE(AcroViewHFT_VERSION_6, AVAppGetHowToPanelAutoShow)

/* AVAppSetHowToPanelAutoShow */
#define AVAppSetHowToPanelAutoShow AVROUTINE(AcroViewHFT_VERSION_6, AVAppSetHowToPanelAutoShow)

/* AVAppAutoShowHowToPanel */
#define AVAppAutoShowHowToPanel AVROUTINE(AcroViewHFT_VERSION_6, AVAppAutoShowHowToPanel)

/* AVMenuItemSetComputeVisibleProc */
#define AVMenuItemSetComputeVisibleProc AVROUTINE(AcroViewHFT_VERSION_6, AVMenuItemSetComputeVisibleProc)

/* AVMenuItemIsVisible */
#define AVMenuItemIsVisible AVROUTINE(AcroViewHFT_VERSION_6, AVMenuItemIsVisible)

/* AVAppRegisterHowToPanel */
#define AVAppSetHowToPanelComputeVisibleProc AVROUTINE(AcroViewHFT_VERSION_6, AVAppSetHowToPanelComputeVisibleProc)

/* AVAppRegisterForContextMenuAddition */
#define AVAppRegisterForContextMenuAddition AVROUTINE(AcroViewHFT_VERSION_6, AVAppRegisterForContextMenuAddition)

/* AVPageViewGetPageToDevScaling */
#define AVPageViewGetPageToDevScaling AVROUTINE(AcroViewHFT_VERSION_6, AVPageViewGetPageToDevScaling)

/* AVDocGetActiveTool */
#define AVDocGetActiveTool AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetActiveTool)

/* AVDocSetActiveTool */
#define AVDocSetActiveTool AVROUTINE(AcroViewHFT_VERSION_6, AVDocSetActiveTool)

/* AVAppRegisterForPageViewRighClicks */
#define AVAppRegisterForPageViewRightClicks AVROUTINE(AcroViewHFT_VERSION_6, AVAppRegisterForPageViewRightClicks)

/* AVAppUnregisterForPageViewRightClicks */
/* note: still only uses one HFT entry, but compat layer needs to be notified about unregister before version 6*/
#define AVAppUnregisterForPageViewRightClicks AVROUTINE(AcroViewHFT_VERSION_6, AVAppUnregisterForPageViewRightClicks)

/* AVDocIsSlow */
#define AVDocIsSlow AVROUTINE(AcroViewHFT_VERSION_6, AVDocIsSlow)

/* AVWindowGetDesktopBounds */
#define AVWindowGetDesktopBounds AVROUTINE(AcroViewHFT_VERSION_6, AVWindowGetDesktopBounds)

/* AVDocGetServerType */
#define AVDocGetServerType AVROUTINE(AcroViewHFT_VERSION_6, AVDocGetServerType)

/* AVPageViewSetWireframeDrawing */
#define AVPageViewSetWireframeDrawing AVROUTINE(AcroViewHFT_VERSION_7, AVPageViewSetWireframeDrawing)

/* AVPageViewGetWireframeDrawing */
#define AVPageViewGetWireframeDrawing AVROUTINE(AcroViewHFT_VERSION_7, AVPageViewGetWireframeDrawing)

/* AVAppShouldKeyDeleteObject */
#define AVAppShouldKeyDeleteObject AVROUTINE(AcroViewHFT_VERSION_7, AVAppShouldKeyDeleteObject)

/* AVAppRegisterLateInitProc */
#define AVAppRegisterLateInitProc AVROUTINE(AcroViewHFT_VERSION_7, AVAppRegisterLateInitProc)

/* AVDocGetBookmarks */
#define AVDocGetBookmarks AVROUTINE(AcroViewHFT_VERSION_7, AVDocGetBookmarks)

#define AVDocGetLastActiveTool AVROUTINE(AcroViewHFT_VERSION_7, AVDocGetLastActiveTool)

#define AVDocGetNumWindows AVROUTINE( AcroViewHFT_VERSION_7, AVDocGetNumWindows )
#define AVDocGetNthWindow AVROUTINE( AcroViewHFT_VERSION_7, AVDocGetNthWindow )

#define AVPageViewGetAVWindow AVROUTINE( AcroViewHFT_VERSION_7, AVPageViewGetAVWindow )

#define AVDocDoAnnotProperties AVROUTINE( AcroViewHFT_VERSION_7, AVDocDoAnnotProperties )

#define AVSysTrackMouse AVROUTINE( AcroViewHFT_VERSION_8, AVSysTrackMouse )

#define AVDocSaveOptimized AVROUTINE( AcroViewHFT_VERSION_8, AVDocSaveOptimized )

#define AVGetOptimizerPresets AVROUTINE( AcroViewHFT_VERSION_8, AVGetOptimizerPresets )

#define AVGetOptimizerParamsForPreset AVROUTINE( AcroViewHFT_VERSION_8, AVGetOptimizerParamsForPreset )

#define AVAppGetAnnotAppearancePadding AVROUTINE( AcroViewHFT_VERSION_8, AVAppGetAnnotAppearancePadding )

#define AVMenuItemIsScriptable AVROUTINE(AcroViewHFT_VERSION_8, AVMenuItemIsScriptable)

#define AVDocApplyRedactions AVROUTINE(AcroViewHFT_VERSION_9, AVDocApplyRedactions)
#define AVListenForCustomNotification AVROUTINE(AcroViewHFT_VERSION_9, AVListenForCustomNotification)

#define AVUnlistenForCustomNotification AVROUTINE(AcroViewHFT_VERSION_9, AVUnlistenForCustomNotification)

#define AVBroadcastCustomNotification AVROUTINE(AcroViewHFT_VERSION_9, AVBroadcastCustomNotification)

/* If you add, delete, or modify procs listed in this file please read the instructions at the top about how to properly change the version number */

#endif /* !STATIC_HFT */

/* ASCallbackCreateNotification
** Type-checking notification callback creation.  Will cause a compiler
** error if the proc's signature does not match the signature of the given
** notification (if DEBUG is 1).
*/
#define ASCallbackCreateNotification(nsel, proc)	ASCallbackCreateProto(nsel##NPROTO, proc)

#define AVAppBeginSave AVROUTINE(AcroViewHFT_VERSION_9, AVAppBeginSave)
#define AVAppEndSave AVROUTINE(AcroViewHFT_VERSION_9, AVAppEndSave)
#define AVAppCancelSave AVROUTINE(AcroViewHFT_VERSION_9, AVAppCancelSave)
#define AVPageViewGetInkPreview AVROUTINE(AcroViewHFT_VERSION_9, AVPageViewGetInkPreview)


#define AVPageViewAcquireDrawContext AVROUTINE(AcroViewHFT_VERSION_10, AVPageViewAcquireDrawContext)
#define AVPageViewReleaseDrawContext AVROUTINE(AcroViewHFT_VERSION_10, AVPageViewReleaseDrawContext)

#define AVConversionAppendToPDFWithHandler AVROUTINE(AcroViewHFT_VERSION_11, AVConversionAppendToPDFWithHandler)
#define AVConversionGetConversionQueueStatusWithHandler AVROUTINE(AcroViewHFT_VERSION_11, AVConversionGetConversionQueueStatusWithHandler)
#define AVConversionToPDFSetSettings AVROUTINE(AcroViewHFT_VERSION_11, AVConversionToPDFSetSettings)

#define AVDocIsInProtectedView AVROUTINE(AcroViewHFT_VERSION_11, AVDocIsInProtectedView)

#endif /* PI_ACROVIEW_VERSION != 0 */

#endif /* PLUGIN */


#ifdef __cplusplus
}
#endif
//#endif /* CAN_EDIT*/
#endif /* !defined(_H_AVCalls) */

