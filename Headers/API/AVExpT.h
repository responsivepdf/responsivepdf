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

 AVExpt.h

 - Types, macros, structures, etc. required to use the AcroView HFT.

   The functions and types can be thought of those that are current and those that are
   obsolete.  Code written using obsolete functions will still compile and work, but those
   definitions have been moved out of this files and into AVExpTObsolete1.h and 
   AVExpTObsolete2.h which are included by this file.
*********************************************************************/

#ifndef _H_AVExpT
#define _H_AVExpT

#include "CoreExpT.h"
#include "ASExpT.h"
#include "PDExpT.h"
#include "AVPrefsD.h"	/* Using AV_PREFERENCES */
#include "ASExtraExpT.h"

#if WIN_PLATFORM
#ifndef _WINDOWS_ /* Check if 32-bit MFC already included <windows.h> */
#define WINDOWS <windows.h>
#include WINDOWS
#endif /* _WINDOWS_ */

#elif MAC_PLATFORM
#if __OBJC__
#include <AppKit/AppKit.h>
#endif
#include <CoreServices/CoreServices.h>
#if !AS_ARCH_64BIT
#include <ApplicationServices/ApplicationServices.h>
#endif /* AS_ARCH_64BIT */
#elif UNIX_PLATFORM
#ifndef X11X
#define X11X <X11/X.h>
#include X11X
#include <X11/Xlib.h>
#endif /* X11X */

#elif OS2_PLATFORM
#define INCL_WIN
#define INCL_DOS
#define OS2  <os2.h>
#include OS2
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************\
|*																					*|
|*								Notification Types									*|
|*																					*|
\************************************************************************************/
#ifndef _T_NSELECTOR
#define _T_NSELECTOR
typedef ASInt32 NSelector; 	/* Selector for HNT functions */
#define BAD_NSELECTOR		(-1)
#endif

/************************************************************************************\
|*																					*|
|*									AVApp											*|
|*																					*|
\************************************************************************************/
/* 
** AV Application Preferences data type, see AVAppGetPreference()/AVAppSetPreference().
*/
enum {
#define AVP(a, b) a,
#define AVX AVP
#define AVS AVP
#define AVPVOIDP(a) a,
#define AVPSTR(a) a,
#if PLUGIN
#define AVU(a, b, c) avpUnused##c,
#else
#define AVU(a, b, c) a,
#endif
	AV_PREFERENCES
	avpNumPrefs
#undef AVP
#undef AVX
#undef AVS
#undef AVU
#undef AVPVOIDP
#undef AVPSTR
};

#ifndef _T_AVPREFSTYPE
#define _T_AVPREFSTYPE
#if WIN_PLATFORM

/*
 To allow AVPrefsType to run up to 255 entries while still
   maintaining its original size it has been changed from an ASEnum8
   to an ASUns8 on Mac and Unix. On Windows it's alwasy been a 16-bit
   value (even though it's defined as ASEnum8) and so will remain
   unchanged to ensure that the size remains constant.

   You may wonder why ASEnum8 yields a 16-bit value on Window but an
   8-bit value on other platform.  This is due to a historical mix-up
   that's best left in the past.
*/
/**
	A structure containing values that specify the Acrobat viewer's 
	preferences settings. It can contain up to 255 entries. 
	It contains bit-flag ASUns32 constants for use with AVDocPrintParams(). 
	@see AVAppGetPreference 
	@see AVAppSetPreference 
	
*/
typedef ASEnum8 AVPrefsType;
#else
typedef ASUns8 AVPrefsType;
#endif
#endif /* _T_AVPREFSTYPE */

/**
	Constants used to specify measurement units in AVPrefsType. 
	
	Do not set the <code>avpPageUnits</code> preference to any value larger 
	than <code>Picas</code>. 
	@see AVAppGetPreference 
	@see AVAppSetPreference 
*/
typedef enum _t_PageUnitsType {
	/** */
	Points,
	/** */
	Inches,		
	/** */
	Millimeters,	
	/** */
	Centimeters,
	/** Do not set <code>avpPageUnits</code> preference any larger than this value. */
	Picas,			
	/** Used only for kKeyPrefsDisplayMeasure preference. */
	Feet,		
	/** Used only for kKeyPrefsDisplayMeasure preference. */
	Yards,
	/** Used only for kKeyPrefsDisplayMeasure preference. */
	Meters,
	/** Used only for kKeyPrefsDisplayMeasure preference. */
	Kilometers,
	/** Used only for kKeyPrefsDisplayMeasure preference. */
	Miles,
	/** Used only for kKeyPrefsDisplayMeasure preference. */
	Custom
} PageUnitsType;

/* These types are provided to abstract the bitwise implementation.  Thus, the same source
   could be compiled to different implementations for 16-bit, 32-bit, Win, Mac, Unix, etc. */

/**
	A pixel offset value for use in an AVDoc view definition. 
	
	@see AVDocGetViewDef
*/
typedef ASInt16 AVPixelOffset;  

/**
	An array size value for AV methods. 
	@see AVAppChooseFolderDialog 
	@see AVAppOpenDialog 
	@see AVAppSaveDialog 
	@see AVExtensionAcquireInfo 
	@see AVExtensionGetNumPlugIns 

*/
typedef ASUns16 AVArraySize; 

/**
	A flag-bits value for use in callback procedures. 
	@see AVAnnotHandlerDoClickProc 
	@see AVAnnotHandlerDoKeyDownExProc 
	@see AVAnnotHandlerDoKeyDownProc 
	@see AVDocSelectionKeyDownProc 
	@see AVPageViewClickProc 
	@see AVPageViewKeyDownProc 
*/
typedef ASInt16 AVFlagBits16;

/**
	A flag-bits value for use in callback procedures. 
	@see AVAnnotHandlerGetFlagsProc 
	@see AVIconHandlerGetFlagsProc 
	@see AVPageViewAppearanceGetAVMatrix 
	@see AVSysGetModifiers 
	@see AVWindowNew 
	@see AVWindowNewFromPlatformThing
*/
typedef ASUns32 AVFlagBits32;

/** Not used. */
typedef ASInt16 AVMouseEventCode;

/**
	A key code value for use in key-down callback procedures. 
	
	@see AVAnnotHandlerDoKeyDownExProc 
	@see AVAnnotHandlerDoKeyDownProc 
	@see AVDocSelectionKeyDownProc 
	@see AVPageViewKeyDownProc 
*/
typedef ASUns16 AVKeyCode;

/** A signed <code>int</code> for historical reasons. */
typedef ASInt16 AVPriority; 

/** A version-number part. */
typedef ASUns16 AVVersionNumPart; 

/** The number of bytes. */
typedef ASUns32 AVBufferSize; 

/** AVDragType or <code>-1</code> for <code>err</code>. */
typedef ASInt16 AVDragTypeEx; 

/**
	A menu index value that indicates a user's choice in a popup menu. It uses negative indices for errors.
	@see AVMenubarAcquireMenuByIndex 
	@see AVMenubarGetMenuIndex 
	@see AVMenubarAddMenu 
	@see AVMenuAcquireMenuItemByIndex 
	@see AVMenuGetMenuItemIndex 
	@see AVMenuAddMenuItem 
	@see AVPageViewDoPopupMenu
*/
typedef ASInt32 AVMenuIndex; 

/** Not used. */
typedef ASInt32 AVIconType;

/**
	A filter index value for AV methods. It uses <code>0+</code> for valid values, <code>-1</code> for all others.
	@see AVAppOpenDialog 
	@see AVAppSaveDialog
*/
typedef ASInt16 AVFilterIndex; 

/**
	A page index value for use in an AVDoc view definition. 
	It uses <code>0+</code> for valid values, <code>-1</code> for invalid or non-applicable values.
	
	@see AVDocGetViewDef
*/
typedef ASInt32 AVPageIndex; 

/** Uses <code>0+</code> for valid values. */
typedef ASInt32 AVCursorID; 

/* These types are signed for historical reasons.  They may change to unsigned in the future. */
/* When possible use the equivalent unsigned type above. */

/**
	The number of items (not the number of bytes) in an array, 
	for use in page view methods. 
	@see AVAppGetNumDocs 
	@see AVDocGetClientName 
	@see AVMenubarGetNumMenus 
	@see AVMenuGetNumMenuItems 
	@see AVMenuGetTitle 
	@see AVMenuItemGetTitle 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewDrawRectOutlineWithHandles 
	@see AVPageViewGetThreadIndex 
	@see AVToolBarGetNumButtons 
	@see AVUtilGetBaseNameAndExtensionByPathName 
	@see AVUtilGetBaseNameAndExtensionByString 
	@see AVActionGetInstructionsProc 
	@see AVActionGetButtonTextProc 
	@see AVActionGetStringOneTextProc 
	@see AVActionGetStringTwoTextProc
*/
typedef ASInt32 AVTArraySize;  

/**
	The number of bytes in a buffer, for use in page view methods. 
	
	@see AVAppGetNumDocs
*/
typedef ASInt32 AVTBufferSize; 

/**
	An array size value for use in page view methods. 
	@see AVPageViewDragOutNewRectSnapped 
	@see AVPageViewDragRectSnapped 
*/
typedef ASInt16 AVTSmallArraySize;  

/**
	A flag-bits value for use in page view methods. 
	@see AVPageViewDeviceRectToPageRZ 
	@see AVPageViewDragOutNewRectSnapped 
	@see AVPageViewDragRectSnapped 
	@see AVPageViewDragRectSnappedEx
*/
typedef ASInt32 AVTFlagBits; 

/**
	A flag-bits value for use in tool button methods. 
	@see AVToolButtonSetExternal
*/
typedef ASUns16 AVTFlagBits16; 

/**
	A click-number value for use in page view callback procedures. 
	
	@see AVPageViewClickProc 
	@see AVPageViewKeyDownProc
*/
typedef ASInt16 AVTCount; 

/* A signed <code>int</code> for historical reasons. */
/**
	A version number part. 
	@see AVAppGetVersion
*/
typedef ASInt16 AVTVersionNumPart; 

#if (!defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)) && !AS_ARCH_64BIT
typedef ASInt16 AVSDKDependentInteger;
#else
typedef ASInt32 AVSDKDependentInteger;
#endif

/**
	A size in the page view's device space. 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewScrollToRect 
*/
typedef AVSDKDependentInteger AVDevSize;

/** 
	An AVDevCoord contains an x or y coordinate in the page view's
	device space. 
*/
typedef AVSDKDependentInteger AVDevCoord;

/**
	An x or y coordinate in the window's space. (0,0) is at 
	the top left, and units are in pixels. 
	@see AVWindowAdjustCursorProc 
	@see AVWindowMouseDownProc
*/
typedef AVSDKDependentInteger AVWindowCoord;

/**
	An x or y coordinate in the screen space. (0,0) is at the 
	top left of the main monitor. 
*/
typedef AVSDKDependentInteger AVScreenCoord;


/************************************************************************************\
|*																					*|
|*								    AVIcon											*|
|*																					*|
\************************************************************************************/

/**
	An icon on a menu item or toolbar button. 
	
	<p>On Windows this is an <code>HBITMAP</code> or an AVIconBundle.</p>
	@ingroup AVIcon
	@see AVMenuItemNew 
	@see AVToolButtonGetIcon 
	@see AVToolButtonNew 
	@see AVToolButtonSetIcon 
*/
typedef const char * AVIconID;
typedef void * AVIcon;

#if WIN_PLATFORM

	/** 
		@ingroup AVIcon
	*/
	typedef HICON			AVIconBundleIconRef;
#elif MAC_PLATFORM
	/** 
		@ingroup AVIcon
	*/
#if AS_ARCH_64BIT
	typedef void*			AVIconBundleIconRef;
#else
	typedef IconSuiteRef	AVIconBundleIconRef;
#endif
#else
	/** 
		@ingroup AVIcon
	*/
	typedef void*			AVIconBundleIconRef;
#endif /* WIN_PLATFORM */


/**
	An icon bundle allows you to gather up multiple icons and 
	present them to Acrobat as a single AVIcon. For example, 
	when creating a toolbar button you can pass in an icon bundle 
	specifying both gray and color icons; the gray icon will 
	be used to draw the button in its normal state, and the color 
	icon will be used to draw the button when the pointer is 
	over it. 

	<p>The format for icon bundles is platform-specific (primarily 
	since the format for AVIcon objects is platform-specific). On Windows 
	the icons can be specified using <code>HICON</code>s, not <code>HBITMAP</code>s. On 
	Mac OS, they are <code>IconSuiteRef</code> resources. Both 
	platforms support the PNG format.</p> 

	<p>The tags at the front are there so the implementation can 
	determine with certainty that the information 
	passed in is an icon bundle and not an Acrobat 4-compatible 
	AVIcon. </p>

	@ingroup AVIcon
*/
typedef struct _t_AVIconBundleRec {

	/** Set to <code>AVIC</code> (for example, <code>bundle.tag1 = 'AVIC'</code>).  */
	ASUns32				tag1;		

	/** Set to <code>ONBU</code> (for example, <code>bundle.tag2 = 'ONBU'</code>). */
	ASUns32				tag2;		

	/** Set to the version of the application (for example, <code>0x00050000</code> for Acrobat 5.0). */
	ASInt32				version;	

	/** Defined according to the AVIconBundleRef <code>typedef</code>. */ 
	AVIconBundleIconRef	grayIcon;

	/** Defined according to the AVIconBundleRef <code>typedef</code>. */
	AVIconBundleIconRef	colorIcon;
} AVIconBundleRec, *AVIconBundle;



/** 
	@ingroup AVIcon
*/
enum {
	/** 
		@ingroup AVIcon
	*/
	kAVIconColor,
	/** 
		@ingroup AVIcon
	*/
	kAVIconGrayscale,
	/** 
		@ingroup AVIcon
	*/
	kAVIconHighContrast
};
typedef ASEnum16 AVIconColorFormat;

/** */
enum
{
#ifdef MAC_PLATFORM
	/** 16x16 icon reference 
		@ingroup AVIcon
	*/
    kAVIconMacIconRef16,  
    /** 32x32 icon reference 
		@ingroup AVIcon
	*/
    kAVIconMacIconRef32, 
    /** 128x128 icon reference 
		@ingroup AVIcon
	*/
    kAVIconMacIconRef128, 
#endif
	/** 
		@ingroup AVIcon
	*/
    kAVIconPNG,

    /** 
	 @ingroup AVIcon
	 DEPRECATED -- Only use kAVIconPNG in A10 or later
	 */
    kAVIconLayered	
};

/**
	Constants that specify a data format for an AVIconBundle6. 
	
	@ingroup AVIcon
	@see AVAppCreateIconBundle6
*/
typedef ASEnum16 AVIconDataFormat;


/**
	An icon bundle allows you to gather up multiple icons and 
	present them to Acrobat as a single AVIcon. For example, 
	when creating a toolbar button you can pass in an icon bundle 
	specifying both gray and color icons; the gray icon will 
	be used to draw the button in its normal state, the color 
	icon will be used to draw the button when the pointer is 
	over it. The format for icon bundles is platform-specific 
	(primarily since the format for AVIcons is platform-specific). 
	On Windows the icons are specified using <code>HICON</code>s, not <code>HBITMAP</code>s. 
	On Mac OS, they are IconSuiteRef resources. 
	The tags at the front are there so the implementation can 
	determine with certainty that the information 
	passed in is an icon bundle and not an Acrobat 4-compatible 
	AVIcon. 

	@ingroup AVIcon

	@note This form of the icon bundle is new in Acrobat 6.0. 
	
*/
typedef struct _t_AVIconBundleRec6 AVIconBundleRec6, *AVIconBundle6;


/**
	Flags returned by <code>AVIconHandler->getFlags()</code>. 

	@ingroup AVIcon
*/
#define AVICON_DONT_CACHE 1

/**
	A callback for AVIconHandler that retrieves the measurements 
	of the icon. All icons in the bundle are assumed to be the 
	same size. 

	@ingroup AVIcon

	@param bundle The icon bundle for which the icon size 
	is measured. 
	@param w (Filled by the method) The icon width in pixels. 
	@param h (Filled by the method) The icon height in pixels. 
	@see AVAppCreateIconBundle6 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVIconHandlerMeasureProc)(AVIconBundle6 bundle, ASInt32 *w, ASInt32 *h);

/**
	A callback for AVIconHandler. It opens a stream so that a 
	drawing function can read the data contained in the icon 
	set. 

	@ingroup AVIcon

	@param bundle The icon bundle for which the stream is 
	opened. 
	@param colorFormat The color format for the icon bundle.
	@return The stream object. 
	@see AVAppCreateIconBundle6 
*/
typedef ACCBPROTO1 ASStm (ACCBPROTO2 *AVIconHandlerOpenStmProc)(AVIconBundle6 bundle, AVIconColorFormat colorFormat);

/**
	A callback for AVIconHandler. It returns the flags value for 
	the icon. 

	@ingroup AVIcon

	@param bundle The icon bundle for which the flags are 
	obtained. The following flags are defined: <code>AVICON_DONT_CACHE=1</code>.
	@return The flags value. 
	@see AVAppCreateIconBundle6 
*/
typedef ACCBPROTO1 AVFlagBits32 (ACCBPROTO2 *AVIconHandlerGetFlagsProc)(AVIconBundle6 bundle);

/**
	A callback for AVIconHandler. It releases the icon object. 
	
	@ingroup AVIcon

	@param bundle The icon bundle that is released.
	@see AVAppCreateIconBundle6 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVIconHandlerReleaseProc)(AVIconBundle6 bundle);


/** 
	@ingroup AVIcon
*/
typedef struct _t_AVIconHandlerRec {
	/** The size of the structure. Set it to <code>sizeof(AVIconHandlerRec)</code>. */
	ASInt32 size;
	/** A pointer to user-defined data passed to the callback. */
	void* clientData;
	/** */
	AVIconHandlerMeasureProc Measure;
	/** */
	AVIconHandlerOpenStmProc OpenStm;
	/** */
	AVIconHandlerGetFlagsProc GetFlags;
	/** */
	AVIconHandlerReleaseProc Release;
} AVIconHandlerRec, *AVIconHandler;


/** 
	An icon bundle allows you to gather up multiple icons and present them to Acrobat as a
	single AVIcon. For example, when creating a toolbar button you can pass in an icon
	bundle specifying both gray and color icons; the gray icon will be used to draw the button
	in its normal state, the color icon will be used to draw the button when the pointer is over
	it. The format for icon bundles is platform-specific (primarily since the format for AVIcon objects
	is platform-specific). On Windows the icons are specified using <code>HICON</code>s, not <code>HBITMAP</code>s. On
	Mac OS, they are IconSuiteRef resources. The tags at the front are there so
	the implementation can determine with certainty that the information
	passed in is an icon bundle and not an Acrobat 4-compatible AVIcon.

	@ingroup AVIcon

	@note This form of the icon bundle is new in Acrobat 6.0.
*/
struct _t_AVIconBundleRec6 {
	/** Set to <code>AVIC</code> (for example, <code>bundle.tag1 = 'AVIC'</code>) */
	ASUns32					tag1;
	/** Set to <code>ONBU</code> (for example, <code>bundle.tag2 = 'ONBU'</code>) */
	ASUns32					tag2;
	/** Set to the version of the application (for example, <code>0x00060000</code> for Acrobat 6.0) */
	ASInt32					version;
	/** The icon handler. */
	AVIconHandler			handler;
	/** A pointer to the icon data record structure. */
	void					*iconData;
    /** A pointer to the icon data record structure for the high Resolution version of the icon. */
    void                    *iconDataHighResolution;
};


/**
	A data record for an AVIconBundle6. 

	@ingroup AVIcon
	@see AVAppCreateIconBundle6 
*/
typedef struct _t_AVIconData {
	/** A data stream containing the binary-encoded data. */
	ASStm					dataStm;
	/** The color this icon represents. */
	AVIconColorFormat		eColorFormat; 
} AVIconDataRec, *AVIconData;


/************************************************************************************\
|*																					*|
|*								  AVPageView										*|
|*																					*|
\************************************************************************************/
#ifndef _T_AVPAGEVIEW
#define _T_AVPAGEVIEW

#ifdef __cplusplus
class AVPageViewObj;
/** */
typedef AVPageViewObj* AVPageView;
#else

/**
	The area of the Acrobat viewer's window that displays the contents of a document
	page. Every AVDoc has an AVPageView and vice versa. It contains references to the
	PDDoc and PDPage objects for the document being displayed.
	@see AVDocGetPageView
	@see AVPageViewAppearanceGetAVMatrix 
	@see AVPageViewAcquireMachinePort 
	@see AVPageViewReleaseMachinePort
	@see AVPageViewGetActiveBead 
	@see AVPageViewGetAnnotRect 
	@see AVPageViewSetAnnotLocation
	@see AVPageViewGetAperture 
	@see AVPageViewGetAVDoc 
	@see AVPageViewGetColor 
	@see AVPageViewSetColor
	@see AVPageViewShowControl
	@see AVPageViewGetDevToPageMatrix
	@see AVPageViewGetFirstVisiblePageNum
	@see AVPageViewGetFocusAnnot 
	@see AVPageViewSetFocusAnnot
	@see AVPageViewGetLastVisiblePageNum
	@see AVPageViewGetLayoutMode 
	@see AVPageViewSetLayoutMode
	@see AVPageViewGetMousePosition
	@see AVPageViewGetMousePositionSnapped
	@see AVPageViewGetNextView
	@see AVPageViewGetPage
	@see AVPageViewGetPageNum 
	@see AVPageViewSetPageNum
	@see AVPageViewGoBack
	@see AVPageViewGoForward
	@see AVPageViewGoTo
	@see AVPageViewGetPageToDevMatrix
	@see AVPageViewGetSelectedAnnotPageNum
	@see AVPageViewGetThreadIndex
	@see AVPageViewGetVisibleAnnotPage
	@see AVPageViewGetZoom 
	@see AVPageViewZoomTo
	@see AVPageViewGetZoomType 
	@see AVPageViewDeviceRectToPageRZ
	@see AVPageViewDrawCosObj
	@see AVPageViewDragRect
	@see AVPageViewDrawNow
	@see AVPageViewDrawRect
	@see AVPageViewDrawRectOutline
	@see AVPageViewHighlightText
	@see AVPageViewInsetRect
	@see AVPageViewInvalidateRect
	@see AVPageViewInvalidateText
	@see AVPageViewInvertRect
	@see AVPageViewInvertRectOutline
	@see AVPageViewInvertQuad
	@see AVPageViewIsBeadAtPoint
	@see AVPageViewPageNumIsVisible
	@see AVPageViewPointInText
	@see AVPageViewReadPageDown
	@see AVPageViewReadPageUp
	@see AVPageViewGoForward
	@see AVPageViewGoTo
	@see AVPageViewGetPageToDevMatrix
	@see AVPageViewGetSelectedAnnotPageNum
	@see AVPageViewGetThreadIndex
	@see AVPageViewGetVisibleAnnotPage
	@see AVPageViewGetZoom 
	@see AVPageViewZoomTo
	@see AVPageViewGetZoomType
	@see AVPageViewDeviceRectToPageRZ
	@see AVPageViewDrawCosObj
	@see AVPageViewDragRect
	@see AVPageViewDrawNow
	@see AVPageViewDrawRect
	@see AVPageViewDrawRectOutline
	@see AVPageViewHighlightText
	@see AVPageViewInsetRect
	@see AVPageViewInvalidateRect
	@see AVPageViewInvalidateText
	@see AVPageViewInvertRect
	@see AVPageViewInvertRectOutline
	@see AVPageViewInvertQuad
	@see AVPageViewIsBeadAtPoint
	@see AVPageViewPageNumIsVisible
	@see AVPageViewPointInText
	@see AVPageViewReadPageDown
	@see AVPageViewReadPageUp
	@see AVPageViewAcquireDrawContext
*/
typedef struct _t_AVPageView *AVPageView;
#endif /* __cplusplus */

#endif /* _T_AVPAGEVIEW */


#if WIN_PLATFORM

/* we have to use this old definition because the Windows 3.0 GM build
   did not pick up the new definition below. */

/**
	Constants that specify the zoom strategy that Acrobat is 
	to follow. 
	@see AVPageViewZoomTo 
	@see AVPageViewGetZoomType 
*/
typedef enum _t_AVZoomType {

	/** No variable zoom (the zoom is a fixed value such as <code>1.0</code> for 100%). */
	AVZoomNoVary,				

	/** Fits the page to the window. */
	AVZoomFitPage,				

	/** Fits the page width to the window. */
	AVZoomFitWidth,					

	/** Fits the page height to the window. */
	AVZoomFitHeight,			

	/** Fits the width of the portion of the page upon which marks are made to the window. */
	AVZoomFitVisibleWidth,		

	/** Uses the page's preferred zoom. */
	AVZoomPreferred,				

	/** (New in Acrobat 5.0) Reflow page to window width. */
	AVZoomReflowWidth			
} AVZoomType;

#else


/** 

*/
enum {
	/** No variable zoom. */
	AVZoomNoVary,					
	/** Fit page to window. */
	AVZoomFitPage,					
	/** Fit page width to the window. */
	AVZoomFitWidth,					
	/** Fit page height to the window. */
	AVZoomFitHeight,				
	/** Fit visible width to the window. */
	AVZoomFitVisibleWidth,			
	/** Use the page's preferred zoom. */
	AVZoomPreferred,				
	/** Reflow the page to the window width. */
	AVZoomReflowWidth				
};
typedef ASEnum8 AVZoomType;

#endif


/**
	(Acrobat 5.0 and later) Used with AVPageViewShowControl() to allow a plug-in author 
	to turn on and off the controls shown in the status area 
	at the bottom of a page view.
	@see AVPageViewShowControl 
*/
enum {

	/** The zoom control. */
	kAVPageViewZoomControl,

	/** The page flip control. */
	kAVPageViewPageFlipControls,

	/** The page number control. */
	kAVPageViewPageNumberControl,

	/** The page size control. */
	kAVPageViewPageSizeControl,

	/** The splitter bar control. */
	kAVPageViewSplitterBar,

	/** The horizontal scroll. */
	kAVPageViewHorizontalScrollBar,

	/** The vertical scroll. */
	kAVPageViewVerticalScrollBar,

	/** The gray border control. */
	kAVPageViewGrayBorder
};
typedef ASEnum16 AVPageViewControlID;

#if WIN_PLATFORM

/**
	The <code>HWND</code> is that of the document window's AVPageView region 
	(the portion of the window in which the PDF file's pages 
	are drawn). 
	@see AVPageViewAcquireMachinePort
*/
typedef struct _t_WinPort {

	/** */
	HWND	hWnd;

	/** */
	HDC		hDC;
} WinPortRec, *WinPort;
#endif

#if UNIX_PLATFORM
typedef struct _t_UnixPort {
	Window drawable;
	Display *display;
	Screen *screen;
	GC gc;
	ASInt32 originX;
	ASInt32 originY;
} UnixPortRec, *UnixPort;
#endif

#if OS2_ENV
typedef struct _t_OS2Port {
	HWND	hWnd;
	HPS	hPS;
} OS2PortRec, *OS2Port;
#endif


/** The view has been scrolled. 
	@ingroup AVPageViewDidChangeFlags
*/
#define PAGEVIEW_UPDATE_SCROLL		1

/** The page number has changed. 
	@ingroup AVPageViewDidChangeFlags
*/
#define PAGEVIEW_UPDATE_PAGENUM		2

/** A new view has been created. 
	@ingroup AVPageViewDidChangeFlags
*/
#define PAGEVIEW_UPDATE_PAGESIZE	4

/** The zoom has been changed. 
	@ingroup AVPageViewDidChangeFlags
*/
#define PAGEVIEW_UPDATE_ZOOM		8


/** Constants identifying mouse events in <code>AVMouseInfoRec.event</code>. */
enum {

	/** */
	kAVLeftButtonDown = 1,

	/** */
	kAVLeftButtonUp,

	/** */
	kAVLeftButtonClick,

	/** */
	kAVLeftButtonDblClick,

	/** */
	kAVRightButtonDown,

	/** */
	kAVRightButtonUp,

	/** */
	kAVRightButtonClick,

	/** */
	kAVRightButtonDblClick,

	/** */
	kAVMouseMove,

	/** */
	kAVMouseEnter,

	/** */
	kAVMouseLeave
};
typedef ASEnum16 AVMouseEvent;

#ifndef _T_AVDOC
#define _T_AVDOC


/** A view of a PDF document in a window. There is one AVDoc per displayed document.
	Unlike a PDDoc, an AVDoc has a window associated with it.
	@see AVAppGetActiveDoc
	@see AVAppEnumDocs
	@see AVDocOpenFromASFileWithParams
	@see AVDocOpenFromFile
	@see AVDocOpenFromFileWithParams
	@see AVDocOpenFromPDDoc
	@see AVDocOpenFromPDDocWithParams
	@see AVPageViewGetAVDoc
	@see AVDocClose
	@see AVAppEnumDocs
	@see AVDocEnumSelection
	@see AVDocDoActionPropsDialog
	@see AVDocDoCopyAs
	@see AVDocDoPrint
	@see AVDocDoSaveAs
	@see AVDocDoSaveAsWithParams
	@see AVDocDoSelectionProperties
	@see AVDocGetAVWindow 
	@see AVDocGetClientName 
	@see AVDocSetClientName
	@see AVDocGetPageText 
	@see AVDocGetPageView 
	@see AVDocGetPDDoc 
	@see AVDocClearSelection
	@see AVDocDeleteSelection
	@see AVDocShowSelection
	@see AVDocGetSelection 
	@see AVDocSetSelection
	@see AVDocGetSelectionServerByType
	@see AVDocGetSelectionType
	@see AVDocGetSplitterPosition 
	@see AVDocSetSplitterPosition
	@see AVDocGetViewDef 
	@see AVDocSetViewDef
	@see AVDocGetViewMode 
	@see AVDocSetViewMode
	@see AVDocIsExternal
	@see AVDocPerformAction
	@see AVDocRegisterSelectionServer
	@see AVDocSetDead
	@see AVDocIsReadOnly 
	@see AVDocSetReadOnly
*/

#ifdef __cplusplus
class AVBaseDocument;
typedef AVBaseDocument* AVDoc;
#else
typedef struct _t_AVDoc *AVDoc;
#endif // __cplusplus

#endif /* _T_AVDOC */

#include "AVExpTObsolete1.h"  /* types for old versions of Acrobat */

/* 
** AcroView defines a coordinate system in which (0,0) is at the top,
** x increases to the right, and y increases down (the same as GDI and
** Quickdraw but opposite PostScript).  An AVRect is defined so that
** its top is above its bottom, but this means that 0 < top < bottom.
*/

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A data structure representing a rectangle (a quadrilateral 
	having only horizontal and vertical sides). 

	<p>The AcroView coordinate system is defined so that (0,0) 
	is at the top, x increases to the right, and y increases 
	down (the same as GDI and QuickDraw but opposite to the 
	PostScript language). An AVRect is defined so that its top 
	is above its bottom, but this means that <code>0 < top < bottom</code>.</p> 
	

	@note The types of numeric coordinate values have changed in 
	Acrobat 6.0. These types are conditionally compiled as ASInt16 
	or ASInt32 depending on the Acrobat version level. 
*/
typedef struct AVRect {

	/** */
	AVSDKDependentInteger left;

	/** */
	AVSDKDependentInteger top;

	/** */
	AVSDKDependentInteger right;

	/** */
	AVSDKDependentInteger bottom;
} AVRect, *AVRectP;
#endif

/**
	A data structure representing a rectangle (a quadrilateral 
	having only horizontal and vertical sides) in a page view's 
	device space. 
	@see AVPageViewDragOutNewRect 
	@see AVPageViewDragOutNewRectSnapped 
	@see AVPageViewDragRect 
	@see AVPageViewDragRectSnapped 
	@see AVPageViewDragRectSnappedEx 
	@see AVPageViewDrawAnnotSequence 
	@see AVPageViewDrawRect 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewDrawRectOutlineWithHandles 
	@see AVPageViewGetAnnotRect 
	@see AVPageViewGetAperture 
	@see AVPageViewInvalidateRect 
	@see AVPageViewInvertRect 
	@see AVPageViewInvertRectOutline 
	@see AVPageViewScrollToRect 
	@see AVPageViewSnapRect 
	@see AVRectHandleHitTest 
	@see AVAnnotHandlerDrawExProc 
	@see AVAnnotHandlerGetAnnotViewBBoxProc 
	@see AVPageViewDrawRectOutline 
	@see AVPageViewScrollToRect 
*/
typedef AVRect AVDevRect;
/* The _T_AVDEVRECT macro prevents AVDevRectP from being multiply defined */
/* AVDevRectP is also defined in PINotify.h */
#ifndef _T_AVDEVRECT
#define _T_AVDEVRECT
typedef AVRectP AVDevRectP;
#endif /* _T_AVDEVRECT */

/**
	A data structure representing a rectangle (a quadrilateral 
	having only horizontal and vertical sides) in a window's 
	coordinate space. 
	@see AVWindowGetInterior 
	@see AVWindowInvalidateRect 
	@see AVWindowDrawProc 
*/
typedef AVRect AVWindowRect;

/**
	A data structure representing a rectangle (a quadrilateral 
	having only horizontal and vertical sides) in a screen's 
	coordinate space. 
	@see AVWindowGetFrame 
	@see AVWindowSetFrame 
	@see AVWindowDidResizeProc 
	@see AVWindowWillBeResizedProc 
*/
typedef AVRect AVScreenRect;


/** */
typedef struct _t_AVPoint
{
	/** */
	ASInt32	h;
	/** */
	ASInt32 v;
} AVPoint;

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A user-supplied callback that is called whenever the AVPageView 
	is drawn. This callback is registered using AVAppRegisterForPageViewDrawing(). 
	@param pageView The AVPageView to redraw. 
	@param updateRect The rectangle enclosing the region to 
	redraw. 
	@param data User-supplied data that was passed in the 
	call to AVAppRegisterForPageViewDrawing().
	@see AVAppRegisterForPageViewDrawing 
	@see AVAppUnregisterForPageViewDrawing 
	
	@note The numeric types have changed in Acrobat 6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVPageViewDrawProc)(AVPageView pageView, AVDevRect* updateRect, void*data);

/**
	A user-supplied callback that is called whenever there is 
	a mouse click in its AVPageView. This callback is registered 
	using AVAppRegisterForPageViewClicks(). 
	@param pageView IN/OUT The AVPageView in which the click occurred. 
	@param x IN/OUT The click's x-coordinate. 
	@param y IN/OUT The click's y-coordinate. 
	@param flags IN/OUT Modifier keys that are held down while the 
	mouse was clicked. They must be an <code>OR</code> of the Modifier Keys 
	value. 
	@param clickNo IN/OUT <code>1</code> for single click, <code>2</code> for double-click, <code>3</code> 
	for triple-click. 
	@param data IN/OUT User-supplied data that was passed in the call 
	to AVAppRegisterForPageViewClicks(). 
	@return <code>true</code> if the callback handles the mouse click, <code>false</code> if it 
	does not and the click should be passed on to the next click 
	handler. 
	@see AVAppRegisterForPageViewClicks 
	@see AVAppUnregisterForPageViewClicks 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVPageViewClickProc)(AVPageView pageView, AVDevCoord x, AVDevCoord y, AVFlagBits16 flags, AVTCount clickNo, void*data);

/**
	A user-supplied callback that is called whenever the cursor 
	is moved. This callback is registered using AVAppRegisterForPageViewAdjustCursor(). 
	@param pageView The AVPageView in which the cursor is 
	located. 
	@param x The cursor's x-coordinate. 
	@param y The cursor's y-coordinate. 
	@param data User-supplied data that was passed in the 
	call to AVAppRegisterForPageViewAdjustCursor().
	@return <code>true</code> if the callback handled the cursor movement, <code>false</code> 
	if it did not and the cursor handler should be allowed to do so. 
	
	@see AVAppRegisterForPageViewAdjustCursor 
	@see AVAppUnregisterForPageViewAdjustCursor 
	
	@note The coordinate numeric types have changed in Acrobat 
	6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVPageViewCursorProc)(AVPageView pageView, AVDevCoord x, AVDevCoord y, void* data);
#endif

/**
	Called whenever there is a key down in its AVPageView. This 
	callback is registered using AVAppRegisterForPageViewKeyDown(). 
	@param pageView The AVPageView in which the keystroke 
	occurred. 
	@param keyCode An ASCII code representing the key that 
	was pressed. In some cases a different code results from 
	a key combination (for example, a <b>Control+key</b> combination 
	results in an ASCII code that is less than or equal to (<=) <code>31</code>). 
	@param flags Modifier keys that are held down while the 
	key was pressed. They must be an <code>OR</code> of the Modifier Keys 
	value. 
	@param data User-supplied data that was passed in the 
	call to AVAppRegisterForPageViewKeyDown().
	@return <code>false</code> to process the keydown event, <code>true</code> otherwise. 
	@see AVAppRegisterForPageViewKeyDown 
	@see AVAppUnregisterForPageViewKeyDown 
	
	@note The numeric argument types have changed in Acrobat 
	6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVPageViewKeyDownProc)(AVPageView pageView, AVKeyCode keyCode, AVFlagBits16 flags, void* data);

/**
	A callback for AVDocGetPageText(). Text is passed to it in the 
	specified format. 
	@param format IN/OUT Text format. See the description of the format 
	parameter of AVDocGetPageText() for a list of the allowed 
	types. 
	@param buf IN/OUT The text. 
	@param bufLen IN/OUT Length of <code>buf</code> in bytes. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVDocGetPageText(). 
	@see AVDocGetPageText 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVTextCopyProc)(ASAtom format, void *buf, AVTBufferSize bufLen, void *clientData);

/************************************************************************************\
|*																					*|
|*									AVMenu											*|
|*																					*|
\************************************************************************************/


/** A menu in the Acrobat viewer's menu bar. Plug-ins can create new menus, add menu
	items at any location in any menu, and remove menu items. Deleting an AVMenu
	removes it from the menu bar (if it was attached) and deletes all the menu items it
	contains.
	@see AVMenuAcquire
	@see AVMenuNew
	@see AVMenuItemAcquireSubmenu
	@see AVMenuItemGetParentMenu
	@see AVMenubarAcquireMenuByName
	@see AVMenubarAcquireMenuByIndex
	@see AVMenubarAcquireMenuByPredicate
	@see AVMenuRelease
	@see AVMenuRemove
	@see AVMenuAddMenuItem
	@see AVMenuGetMenuItemIndex 
	@see AVMenuGetName 
	@see AVMenuGetNumMenuItems 
	@see AVMenuGetParentMenubar 
	@see AVMenuGetParentMenuItem 
	@see AVMenuGetTitle
*/
typedef struct _t_AVMenu *AVMenu;


/**
	A callback that is called for each menu enumerated by AVMenubarAcquireMenuByPredicate(). 
	The first menu for which this callback returns <code>true</code> is acquired. 
	
	@param menu IN/OUT The current menu in the enumeration. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVMenubarAcquireMenuByPredicate(). 
	@return <code>true</code> to acquire the current menu and halt enumeration, <code>false</code> 
	to continue enumeration. 
	@see AVMenubarAcquireMenuByPredicate 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVMenuPredicate)(AVMenu menu, void *clientData);

/**
	Called after a context menu has been created but before 
	it is shown to the user. The callback can add menu items 
	to or remove menu items from the menu. The client must register 
	the callback using AVAppRegisterForContextMenuAddition(). 

	<p>This callback should not raise an error. </p>
	@param menuName The menu name. 
	
	<p>Possible values:</p>
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD>Page</TD><TD>The standard context menu for an AVPageView.</TD></TR>
	<TR><TD>Select</TD><TD>The context menu for selected text.</TD></TR>
	</TABLE>

	@param menu The menu object. 
	@param menuData The menu data as an AVDoc pointer. 
	@param clientData User-supplied data that was passed in 
	the call to AVAppRegisterForContextMenuAddition().
	@see AVAppRegisterForContextMenuAddition 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVContextMenuAdditionProc)
	(ASAtom menuName, AVMenu menu, void *menuData, void *clientData);

/************************************************************************************\
|*																					*|
|*								  AVMenubar											*|
|*																					*|
\************************************************************************************/


/** The Acrobat viewer's menu bar and a list of all menus. There is only one AVMenubar.
	Plug-ins can add new menus to or remove any menu from the menu bar. The menu bar
	can be hidden from the user's view.
	@see AVAppGetMenubar the standard way to obtain the menubar.
	@see AVMenuGetParentMenubar
	@see AVMenubarAddMenu
	@see AVMenuRemove
	@see AVMenubarAcquireMenuByIndex
	@see AVMenubarAcquireMenuByName 
	@see AVMenubarAcquireMenuByPredicate
	@see AVMenubarAcquireMenuItemByName 
	@see AVMenubarAcquireMenuItemByPredicate
	@see AVMenubarGetMenuIndex
	@see AVMenubarGetNumMenus
	@see AVMenuItemRemove
	@see AVMenubarHide
	@see AVMenubarShow
*/
typedef struct _t_AVMenubar *AVMenubar;

#define BAD_MENUITEM_INDEX (-1)
#define PREPEND_MENUITEM (-2)
#define APPEND_MENUITEM (9999)

#define BAD_MENU_INDEX (-1)
#define PREPEND_MENU (-2)
#define APPEND_MENU (9999)

#define NO_SHORTCUT	('\0')

/************************************************************************************\
|*																					*|
|*								  AVMenuItem										*|
|*																					*|
\************************************************************************************/

/** A menu item under a menu in the Acrobat viewer. It has a number of attributes,
	including a name, a keyboard shortcut, a procedure to execute when the menu item is
	selected, a procedure to compute whether the menu item is enabled, a
	procedure to compute whether the menu item is check marked, and whether or
	not it has a submenu.
	@see AVMenuItemNew
	@see AVMenuItemAcquire
	@see AVMenubarAcquireMenuByName
	@see AVMenubarAcquireMenuItemByPredicate
	@see AVMenuAcquireMenuItemByIndex
	@see AVMenuGetParentMenuItem
	@see AVMenuItemRelease
	@see AVMenuItemRemove
	@see AVMenuGetMenuItemIndex 
	@see AVMenuItemAcquireSubmenu
	@see AVMenuItemGetLongOnly
	@see AVMenuItemGetName
	@see AVMenuItemGetParentMenu
	@see AVMenuItemGetShortcut
	@see AVMenuItemGetTitle AVMenuItemSetTitle
	@see AVMenuItemIsEnabled
	@see AVMenuItemIsMarked
	@see AVMenuItemSetComputeEnabledProc
	@see AVMenuItemSetComputeMarkedProc
	@see AVMenuItemSetComputeVisibleProc
	@see AVMenuItemSetExecuteProc
*/
typedef struct _t_AVMenuItem *AVMenuItem;

/**
	A callback that is called whenever a menu item or toolbar 
	button is executed. It implements whatever the menu item 
	or toolbar button does (for example, opening a file or initiating 
	a search). 

	<p>This method may also be called from an external application 
	displaying a PDF file in its window, using the ExternalDocServerCreationData 
	structure. </p>
	@param data IN/OUT User-supplied data that was passed when AVMenuItemSetExecuteProc() 
	or AVToolButtonSetExecuteProc() were called. 
	@see AVMenuItemSetExecuteProc 
	@see AVToolButtonSetExecuteProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVExecuteProc)(void *data);

/**
	A callback that is used to determine whether a menu item, 
	toolbar button, or tool is enabled. If used for a tool, 
	it is one of the optional callbacks for AVTool. 

	<p>This procedure is called every time the menu or toolbar 
	button is displayed, so it should not do compute-time-intensive 
	processing. It is called before the menu item or toolbar 
	button is displayed, or before a tool is activated. If it 
	returns <code>false</code>, the menu item, toolbar button, or tool is 
	disabled; otherwise it is enabled. If this callback is <code>NULL</code>, 
	the menu item, toolbar button, or tool is always enabled. </p>
	
	<p>Each menu item, toolbar button, or tool can have its own 
	AVComputeEnabledProc(), or they can be shared. </p>

	@param data User-supplied data that was passed in the 
	call to AVMenuItemSetComputeEnabledProc() or AVToolButtonSetComputeEnabledProc().
	@return <code>true</code> if the menu item, toolbar button, or tool is enabled, 
	<code>false</code> otherwise. 
	@see AVMenuItemSetComputeEnabledProc 
	@see AVToolButtonSetComputeEnabledProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVComputeEnabledProc)(void *data);

/**
	A callback that is used to determine whether a menu 
	item or toolbar button is marked (a marked menu item has 
	a check mark next to it, and a marked toolbar button appears 
	selected). It is called before the menu item or toolbar 
	button is displayed. If it returns <code>false</code>, the menu item 
	of toolbar button is not marked; otherwise it is marked. 
	
	<p>Each menu item and toolbar button can have is own AVComputeMarkedProc, 
	or they can be shared.</p> 
	@param data IN/OUT User-supplied data that was passed in the call 
	to AVMenuItemSetComputeMarkedProc() or AVToolButtonSetComputeMarkedProc(). 
	
	@return <code>true</code> if the menu item or toolbar button is marked, <code>false</code> 
	otherwise. 
	@see AVMenuItemSetComputeMarkedProc 
	@see AVToolButtonSetComputeMarkedProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVComputeMarkedProc)(void *data);

/**
	A callback that is used to determine whether a toolbar button, 
	menu item, or HowTo panel is visible when its parent is 
	opened. It is called before the item is displayed. If it 
	returns <code>true</code>, the item is visible; otherwise it is not visible. 
	
	<p>Each toolbar button, menu item, or HowTo panel can have 
	its own visibility procedure, or they can be shared. </p>

	<p>Because the procedure is called whenever the item is displayed, 
	it should not do any resource-intensive computing. </p>
	@param data User-supplied data that was passed in the 
	call to AVMenuItemSetComputeVisibleProc(), AVToolButtonSetComputeVisibleProc(), 
	or AVAppSetHowToPanelComputeVisibleProc().
	@return <code>true</code> if the item is visible, <code>false</code> otherwise. 
	@see AVAppSetHowToPanelComputeVisibleProc 
	@see AVMenuItemSetComputeVisibleProc 
	@see AVToolButtonSetComputeVisibleProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVComputeVisibleProc)(void *data);


/**
	A callback that is called for each menu item enumerated by 
	AVMenubarAcquireMenuItemByPredicate(). The first menu item 
	for which this callback returns <code>true</code> is acquired. 
	@param menuItem IN/OUT The current menu item in the enumeration. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVMenubarAcquireMenuItemByPredicate(). 
	@return <code>true</code> to acquire the current menu item and halt enumeration, 
	<code>false</code> to continue enumeration. 
	@see AVMenubarAcquireMenuItemByPredicate 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVMenuItemPredicate)(AVMenuItem menuItem, void *clientData);


/**
	A callback that is used to get the mega-tooltip help text
	for a toolbar button. 

	<p>It is called whenever the mouse hovers long enough to display
	the mega-tooltip. </p>

	<p>Each toolbar button can have its own AVGetTooltipProc(), or
	they can be shared.</p> 
	@param data IN/OUT User-supplied data that was passed in the call 
	to AVToolButtonSetGetTooltipProc() or AVToolButtonSetComputeEnabledProc(). 
	@param enabled IN Specifies whether the button is enabled.
	
	@return <code>true</code> if the menu item, toolbar button, or tool is enabled, 
	<code>false</code> otherwise. 
	@see AVMenuItemSetComputeEnabledProc 
	@see AVToolButtonSetComputeEnabledProc 
*/
typedef ACCBPROTO1 ASText (ACCBPROTO2 *AVComputeTooltipProc)(void *data, ASBool enabled);


/**
	A callback that is called whenever the mouse hovers long enough 
	to display the tooltip text. It returns text that is displayed 
	in the tooltip. 

	<p>Each toolbar button can have its own tooltip procedure, 
	or they can be shared. </p>
	@param data User-supplied data that was passed in the 
	call to AVToolButtonSetNotifyTooltipProc().
	@see AVToolButtonSetNotifyTooltipProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVNotifyTooltipProc)(void *data);


/************************************************************************************\
|*																					*|
|*									AVDoc											*|
|*																					*|
\************************************************************************************/


/**
	A callback used by AVAppEnumDocs(). It is called once for each 
	open AVDoc. 
	@param doc IN/OUT The current document. Do not close this AVDoc 
	in this callback function. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVAppEnumDocs(). 
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 	
	@see AVAppEnumDocs 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocEnumProc)(AVDoc doc, void *clientData);

/**
	A user-supplied callback that is passed in the call to AVDocEnumSelection. 
	It is called once for each 'item' in the selection. 

	<p>AVDocEnumSelection() calls the AVDocSelectionEnumSelectionProc() 
	for the current selection's server to actually enumerate 
	the selection. </p>
	@param doc The document whose selection is enumerated. 
	
	@param clientData User-supplied data that was passed in 
	the call to AVDocEnumSelection(). 
	@param aSelectedObject The selected item currently being 
	enumerated. The format of the data is up to the selection 
	server. See AVDocSetSelection() for a list of the data formats 
	for the Acrobat viewer's built-in selection servers.
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	
	@see AVDocEnumSelection 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVSelectionEnumProc)(AVDoc doc, void *clientData, void *aSelectedObject);

/**
	A user-supplied callback that is passed in the call to AVDocSelectionEnumPageRanges(). 
	It is called once for each page in the selection, and consecutive 
	pages are grouped into a single page range. 
	@param doc The document whose selection is enumerated. 
	
	@param clientData User-supplied data that was passed in 
	the call to AVDocSelectionEnumPageRanges(). 
	@param firstPage The first page in a consecutive range 
	of pages with a selection. 
	@param lastPage The first page in a consecutive range 
	of pages with a selection.
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	
	@see AVDocEnumSelection 
	@see AVDocSelectionEnumPageRanges 

	@note The page number numeric type has changed in Acrobat 6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVSelectionPageRangeEnumProc)(
	AVDoc doc, void *clientData, PDPageNumber firstPage, PDPageNumber lastPage);

/**
	A callback for <code>AVDocSelectionServer</code>. It returns the selection 
	type this server handles (for example, <code>'Text'</code> or <code>'Bookmark'</code>). 
	This information is used so that the Acrobat viewer knows 
	which selection server to call. 
	@return The selection type this selection server handles. 
	@see AVDocGetSelectionServerByType 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *AVDocSelectionGetTypeProc)( void);

/**
	A callback for <code>AVDocSelectionServer</code>. It is called when the 
	selection is set (for example, via <code>AVDocSetSelection()</code>). 

	<p>In addition to its other functionality, this callback must also highlight 
	the specified selection, if requested, using 
	the selection server's <code>AVDocSelectionHighlightSelectionProc()</code> callback. </p>
	@param doc IN/OUT The document containing the selection. 
	@param selData IN/OUT The selection data being added. 
	@param highlight IN/OUT If <code>true</code>, highlight the selection, <code>false</code> 
	otherwise. 
	@see AVDocSetSelection 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionGettingSelectionProc)(AVDoc doc, void *selData, ASBool highlight);

/**
	A callback for <code>AVDocSelectionServer</code> that adds the specified item 
	to the selection, highlights it, and returns the new selection 
	containing the newly-added item. 
	@param doc IN/OUT The document containing the data to add to the 
	selection. 
	@param curData IN/OUT Data representing the current selection. 
	Its format is specific to the selection server. 
	@param addData IN/OUT The item to add to the selection. 
	@param highlight IN/OUT <code>true</code> if the selection should be highlighted 
	(because it has not already been highlighted), <code>false</code> if 
	the selection should not be highlighted (because it has 
	already been highlighted by whatever called this callback). 
	See <code>AVDocSetSelection()</code> for additional information on highlighting. 
	
	@return New selection data containing all current selections (that 
	is, the previous selection plus the newly-added selection), 
	or <code>NULL</code> if failure occurred. If the selection server allows only 
	a single item to be selected at a time, clear the previous 
	selection, highlight the selection specified by <code>addData</code> 
	(if <code>highlight</code> is <code>true</code>), and simply return <code>addData</code>. 
	@see AVDocSelectionRemovedFromSelectionProc 
*/
typedef ACCBPROTO1 void* (ACCBPROTO2 *AVDocSelectionAddedToSelectionProc)( AVDoc doc, void *curData, void *addData, ASBool highlight);

/**
	<p>A callback for <code>AVDocSelectionServer</code>. This method is called 
	by <code>AVDocClearSelection</code> (among others), to let the selection 
	server responsible for the old selection do whatever cleanup 
	it needs. </p>

	<p>In addition to its other functionality, it 
	must de-highlight the specified selection (if requested), 
	using the selection server's AVDocSelectionHighlightSelectionProc() 
	callback. </p>
	@param doc The document whose selection is cleared. 
	@param selData The current selection data. 
	@param highlight If <code>true</code>, the selection specified by <code>selData</code> 
	should be de-highlighted, <code>false</code> otherwise.
	@see AVDocClearSelection 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionLosingSelectionProc)( AVDoc doc, void* selData, ASBool highlight);

/**
	A callback for <code>AVDocSelectionServer</code> that de-highlights the old 
	item given in <code>remData</code>, and returns a new <code>curData</code> or <code>NULL</code> 
	if failure occurred. 
	@param doc IN/OUT The document in which an item is removed from 
	the selection. 
	@param curData IN/OUT The current selection data. 
	@param remData IN/OUT The item to remove from the selection. The 
	content and format of <code>selData</code> differs for each selection 
	server, and are decided by the selection server's implementors. 
	@param highlight IN/OUT If <code>true</code>, the item removed should be de-
	highlighted. If <code>false</code>, it should not. 
	@return The new selection data after the specified item has been 
	removed. 
	@see AVDocSelectionAddedToSelectionProc 
*/
typedef ACCBPROTO1 void* (ACCBPROTO2 *AVDocSelectionRemovedFromSelectionProc)( AVDoc doc, void *curData, void *remData, ASBool highlight);

/**
	A callback for <code>AVDocSelectionServer</code>. It is used to determine 
	whether the current selection type can perform a <i>select 
	all</i> operation. This controls whether the Select All menu 
	item is enabled. 
	@param doc The document containing the current selection. 
	@param selData The current selection's data.
	@return <code>true</code> if <i>select all</i> can be performed on the current selection 
	type, <code>false</code> otherwise. 
	@see AVDocSelectionSelectAllProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanSelectAllProc)( AVDoc doc, void* selData);

/**
	A callback for <code>AVDocSelectionServer</code> that selects all items of 
	the current type. 
	@param doc IN/OUT The document in which the Select All is performed. 
	@param selData IN/OUT The current selection data in <code>doc</code>. 
	@return The new selection data after all items of the specified 
	type have been selected. 
	@see AVDocSelectionCanSelectAllProc 
*/
typedef ACCBPROTO1 void* (ACCBPROTO2 *AVDocSelectionSelectAllProc)( AVDoc doc, void* selData);

/**
	A callback for <code>AVDocSelectionServer</code>. It is used to determine 
	whether the current selection has user-specified properties. 
	This controls whether the Properties menu item is enabled. 
	
	<p>The Properties menu item will not be enabled if the selection 
	server does not have a AVDocSelectionPropertiesProc() callback.</p> 
	
	@param doc The document containing the current selection. 
	@param selData The current selection data.
	@return <code>true</code> if the current selection has a Properties user interface, <code>false</code> 
	otherwise. 
	@see AVDocDoSaveAsWithParams 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanPropertiesProc)( AVDoc doc, void* selData);

/**
	(Optional) A callback for <code>AVDocSelectionServer</code> that displays the 
	<b>set properties</b> user interface, if any, for the selection 
	server and lets the user set the server's properties. This 
	callback is not needed unless the selection server has properties 
	that can be set by the user (for example, text highlight 
	color). This callback is called by AVDocDoSaveAsWithParams(). 
	@param doc IN/OUT The document in which the selection server's 
	properties are set. 
	@param selData IN/OUT The current selection data. 
	@see AVDocDoSaveAsWithParams 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionPropertiesProc)( AVDoc doc, void* selData);

/**
	A callback for <code>AVDocSelectionServer</code>. It is used to determine 
	whether the current selection can be deleted. This controls, 
	for example, whether the Delete menu item is enabled. 

	<p>The Delete menu item is only enabled if the selection server's 
	AVDocSelectionCanDeleteProc() returns <code>true</code> and the selection 
	server has an AVDocSelectionDeleteProc(). </p>
	@param doc The document containing the current selection. 	
	@param selData The current selection data.
	@return <code>true</code> if the current selection can be deleted, <code>false</code> otherwise. 
	@see AVDocSelectionCanDeleteProc 
	@see AVDocDeleteSelection 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanDeleteProc)( AVDoc doc, void* selData);

/**
	A callback for <code>AVDocSelectionServer</code>. It deletes the current selection. 
	
	@param doc IN/OUT Document whose selection is deleted. 
	@param selData IN/OUT The current selection in <code>doc</code>. 
	@return <code>true</code> if the data was actually deleted, <code>false</code> otherwise. 
	@see AVDocDeleteSelection 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionDeleteProc)( AVDoc doc, void* selData);

/**
	A callback for <code>AVDocSelectionServer</code>. It is used to determine 
	whether the current selection can be copied. This 
	controls, for example, whether the Copy menu item 
	is enabled. 

	<p>The Copy menu item is only enabled if the selection server's 
	AVDocSelectionCanCopyProc() returns <code>true</code> and the selection 
	server has an AVDocSelectionCopyProc(). </p>
	@param doc IN/OUT The document containing the selection. 
	@param selData IN/OUT The current selection data. 
	@return <code>true</code> if the current selection can be copied, <code>false</code> otherwise. 
	@see AVDocSelectionCopyProc 
	@see AVDocCopySelection 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanCopyProc)( AVDoc doc, void* selData);

/**
	A callback for <code>AVDocSelectionServer</code>. It copies the selected 
	item to the clipboard. The Acrobat viewer will have already 
	cleared the clipboard and placed some private data onto 
	it, in order to identify the selection server that put 
	data on the clipboard. Because of this, a plug-in must 
	not clear the clipboard, and should only add its private data. 
	In addition, if the current selection can be reasonably 
	represented as text, plug-ins are strongly encouraged to 
	place a text representation of the selection onto the clipboard, 
	in addition to their own private format. 
	@param doc IN/OUT The document whose selection is copied. 
	@param selData IN/OUT The current selection data in <code>doc</code>. 
	@return <code>true</code> if the data was actually copied, <code>false</code> otherwise. 
	@see AVDocCopySelection 
	@see UnixAppClipboardGetItemId 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCopyProc)( AVDoc doc, void* selData);

/**
	(Optional) A callback for <code>AVDocSelectionServer</code>. It is called by 
	AVDocEnumSelection(). This callback enumerates the current 
	selection, calling the specified AVSelectionEnumProc() for 
	each item in the selection (the selection server is free 
	to decide what constitutes an item). 

	<p>If omitted, the selection is enumerated by calling <code>proc</code> 
	once, passing the entire selection to it. </p>
	@param doc IN/OUT The document whose selection is enumerated. 	
	@param data IN/OUT The current selection in <code>doc</code>. 
	@param proc IN/OUT The procedure to call for each item in the 
	selection. This callback must halt enumeration if <code>proc</code> returns 
	<code>false</code>, and continue enumeration if <code>proc</code> returns <code>true</code>. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVDocEnumSelection(). Pass this as the client data 
	each time <code>proc</code> is called. 
	@see AVDocSelectionEnumPageRangesProc 
	@see AVDocEnumSelection 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionEnumSelectionProc)( AVDoc doc, void *data, AVSelectionEnumProc proc, void *clientData);

/**
	A callback for <code>AVDocSelectionServer</code>. It changes the view (for 
	example, by scrolling the current page or moving to the 
	appropriate page) so that the current selection is visible. 
	
	@param doc IN/OUT The document whose selection is displayed. 
	@param data IN/OUT The current selection data in <code>doc</code>. 
	@see AVDocShowSelection 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionShowSelectionProc)( AVDoc doc, void *data);

/**
	A callback for <code>AVDocSelectionServer</code>. It is used to determine 
	whether the current selection can be cut. This controls, 
	for example, whether the Cut menu item is enabled. 

	<p>The Cut menu item is only enabled if the selection server's 
	AVDocSelectionCanCutProc() returns <code>true</code> and the selection 
	server has an AVDocSelectionCutProc(). </p>
	@param doc The document containing the current selection. 	
	@param data The current selection data.
	@return <code>true</code> if the current selection can be cut, <code>false</code> otherwise. 	
	@see AVDocSelectionCutProc 
	@see AVDocSelectionCanPasteProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanCutProc)( AVDoc doc, void* data);

/**
	A callback for <code>AVDocSelectionServer</code>. It cuts the current selection. 
	See the discussion under AVDocSelectionCopyProc() for information 
	on how the selection server must use the clipboard. 
	@param doc IN/OUT Document whose selection is cut. 
	@param data IN/OUT The current selection data in <code>doc</code>. 
	@return <code>true</code> if the data was actually cut, <code>false</code> otherwise. 
	@see UnixAppClipboardGetItemId 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCutProc)( AVDoc doc, void* data);

/**
	A callback for <code>AVDocSelectionServer</code>. It is used to determine 
	whether the current selection can be pasted. This 
	controls, for example, whether the Paste menu item 
	is enabled. 

	<p>The Paste menu item is only enabled if the selection server's 
	AVDocSelectionCanPasteProc() returns <code>true</code> and the selection 
	server has an AVDocSelectionPasteProc(). </p>
	@param doc IN/OUT The document into which the selection is pasted. 	
	@return <code>true</code> if the data currently on the clipboard can be pasted, 
	<code>false</code> otherwise. 
	@see AVDocSelectionPasteProc 
	@see AVDocSelectionCanCutProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanPasteProc)( AVDoc doc );

/**
	A callback for <code>AVDocSelectionServer</code>. It pastes the current selection 
	from the clipboard. 
	@param doc IN/OUT The document into whose selection the clipboard 
	is pasted. 
	@see AVDocSelectionCutProc 
	@see AVDocSelectionCanPasteProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionPasteProc)( AVDoc doc );

/**
	(Optional) A callback for <code>AVDocSelectionServer</code>. It handles a 
	key press. It is needed only if the selection server processes 
	key presses. 
	@param doc The document in which the click occurred. 
	@param data The current selection data for <code>doc</code>. 
	@param key The key that was pressed. 
	@param flags Modifier keys that were pressed with <code>key</code>. 
	It must be an <code>OR</code> of the Modifier Keys values.
	@return <code>true</code> if it the keypress was handled, <code>false</code> if it was not 
	and therefore needs to be passed to the next procedure in 
	the key handling chain. 

	@note The <code>key</code> and <code>flags</code> numeric types changed in Acrobat 6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionKeyDownProc)( AVDoc doc, void* data, AVKeyCode key, AVFlagBits16 flags);

/**
	(Previously known as <code>AVDocHighlightSelectionProc</code>) Callback 
	for <code>AVDocSelectionServer</code>. It highlights the selection. This 
	method is unnecessary if the selection type highlights itself 
	(as in the case of annotations). 
	@param doc The document containing the selection. 
	@param data The current selection data. Its content and 
	organization are decided by the selection server for the current 
	selection type.
	@see AVDocSelectionHighlightSelectionExProc 
	@see AVDocSelectionGettingSelectionProc 
	@see AVDocSelectionLosingSelectionProc 

	@note Superseded by <code>AVDocSelectionHighlightSelectionExProc</code> 
	in Acrobat 6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionHighlightSelectionProc)(AVDoc doc, void* data);

/* When this call is made you should highlight your selection. It is
   normally called when an update event is being processed for a page
   view. The page view passed into this call is the one being updated
   and might not be the active page view returned by AVDocGetPageView().
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionHighlightSelectionExProc)(AVDoc doc, AVPageView pageView, void* data);

/**
	A callback for <code>AVDocSelectionServer</code>. It provides a way for 
	a single selection server to register different selection 
	types based on the selection data. If this callback is not 
	supplied, the selection type defaults to the return value 
	from AVDocSelectionGetTypeProc(). 

	<p>This callback does not affect existing selection servers. </p>
	
	@param doc IN/OUT The document containing the selection. 
	@param data IN/OUT The current selection data. Its content and 
	organization are decided by the selection server for the current 
	selection type. 
	@see AVDocSelectionGetTypeProc 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *AVDocSelectionGetSelectionTypeProc)(AVDoc doc, void* data);

/**
	A callback for <code>AVDocSelectionServer</code>. It allows enumeration 
	of the set of pages the selection covers. 
	@param doc IN/OUT The document containing the selection. 
	@param selectionData IN/OUT The current selection data. Its content 
	and organization are decided by the selection server for the current 
	selection type. 
	@param enumProc IN/OUT The current selection data. Its content 
	and organization are decided by the selection server for the current 
	selection type. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVDocSelectionEnumPageRanges(). 
	@see AVDocSelectionEnumSelectionProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionEnumPageRangesProc)(
	AVDoc doc, void *selectionData,
	AVSelectionPageRangeEnumProc enumProc, void *clientData);

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	Called to identify the bounding rectangle of a selection. 
	It is used by the Info palette to display the width and height 
	of the selection. 

	<p>Rectangle coordinates are in device space. </p>
	@param doc The document containing the selection. 
	@param pageNo The number of the page containing the bounding 
	rectangle. 
	@param rect (Filled by the callback) The bounding rectangle 
	of the selection. 
	@param data Server-dependent selection data.
	@return <code>true</code> if the bounding rect was successfully determined, <code>false</code> 
	otherwise. 

	@note The page number numeric type has changed in Acrobat 6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionGetAVRectProc)(AVDoc doc, PDPageNumber pageNo, AVDevRect* rect, void* data);

/**
	Called to request that the selection server display a context 
	menu appropriate for the current selection. 

	<p>The given coordinates provide a suggested location for displaying 
	the menu and are in device space for the current AVPageView. </p>
	
	@param doc The document containing the selection. 
	@param data Server-dependent selection data. 
	@param x The x-coordinate of the point specifying the 
	upper left corner of the menu. 
	@param y The y-coordinate of the point specifying the 
	upper left corner of the menu.
	@return <code>true</code> if the server showed the menu successfully, <code>false</code> otherwise. 
	
	@note The coordinate types have changed in Acrobat 6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionShowMenuProc)(AVDoc doc, void *data, AVDevCoord x, AVDevCoord y);
#endif

/**
	A callback for <code>AVDocSelectionServer</code> that gets a quad-based 
	region for the selection. 
	@param doc The document containing the selection. 
	@param data The current selection data. Its content and 
	organization are decided by the selection server for the current 
	selection type. 
	@param pageNum The page number of the selection. 
	@param quads (Filled by the method.) A pointer to an array 
	of quads, or <code>NULL</code>. If it is non-<code>NULL</code>, the selection server allocates 
	an array of ASFixedQuad objects in user space describing the selection, 
	and stores a pointer to the array at <code>*quad</code>. If <code>NULL</code>, the 
	selection server returns the number of quads in the selection 
	without allocating an array. 
	@return The number of quads in the selection. 

	@note This procedure is new in Acrobat 6.0. 
*/
typedef ACCBPROTO1 ASArraySize (ACCBPROTO2 *AVDocSelectionAcquireQuadsProc)(AVDoc doc, void *data, ASInt32 pageNum, ASFixedQuad **quads);

/**
	Determines whether a selection can be pasted.
	@param doc The document containing the selection. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionCanPasteFromPlatformProc)( AVDoc doc );

/**
	Paste the selection.
	@param doc The document containing the selection. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVDocSelectionPasteFromPlatformProc)( AVDoc doc );

/**
	(Optional) A callback for <code>AVDocSelectionServer</code>. It handles a 
	key press using Unicode values. It is needed only if the selection server
	processes key presses. 

	<p>If this callback is provided, all key events will be passed to
	it; the <code>KeyDown</code> callback will never be called.</p>

	<p>The application may pass several Unicode characters to the
	<code>UnicodeKeyDown</code> callback. For example, if the user invokes
	an IME to compose a string of text, the entire text string
	may be passed to the <code>UnicodeKeyDown</code> callback at once. This
	behavior may also vary across platforms. If the callback
	returns <code>true</code> the application assumes the selection server
	processed all of the characters; if the callback returns
	<code>false</code> the viewer assumes the selection server processed
	none of the characters.</p>

	@param doc The document in which the keyboard event occurred. 
	@param data The current selection data for <code>doc</code>. 
	@param numUTF16Vals The number of UTF-16 values being passed.
	@param utf16Vals The host-endian UTF-16 values.
	@param flags Modifier keys that were pressed with <code>key</code>. 
	It must be an <code>OR</code> of the Modifier Keys values.
	@return <code>true</code> if it the keypress was handled, <code>false</code> if it was not 
	and therefore needs to be passed to the next procedure in 
	the key handling chain.
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVDocSelectionUnicodeKeyDownProc)( AVDoc doc, void* data, ASCount numUTF16Vals, const ASUTF16Val* utf16Vals, AVFlagBits16 flags);

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A data structure containing callbacks that implement a selection 
	server. The callbacks implement the selection server functions. 
	For example, they can add an item to the selection, remove an item 
	from the selection, or copy the current selection to the clipboard. 
	
	@see AVDocRegisterSelectionServer 
	@see AVDocGetSelectionServerByType 
*/
typedef struct _t_AVDocSelectionServer {


	/** The size of the data structure. It must be set to <code>sizeof(AVDocSelectionServerRec)</code>.*/
	ASSize_t 							size;	

	/** Obsolete.  Use the Type field instead. */
	AVDocSelectionGetTypeProc				GetType;

	/** Highlight the seclection. */
	AVDocSelectionGettingSelectionProc		GettingSelection;

	/** Add the item to the selection. */
	AVDocSelectionAddedToSelectionProc		AddedToSelection;

	/** De-highlight the selection. */
	AVDocSelectionLosingSelectionProc		LosingSelection;

	/** Remove the item from the selection. */
	AVDocSelectionRemovedFromSelectionProc	RemovedFromSelection;

	/** Determine whether the current selection type can perform a <i>select all</i> operation. */
	AVDocSelectionCanSelectAllProc			CanSelectAll;

	/** Select all items of the current type. */
	AVDocSelectionSelectAllProc				SelectAll;

	/** Determine whether the current selection has user-specified properties. */
	AVDocSelectionCanPropertiesProc			CanProperties;

	/** Display the <b>set properties</b> user interface. */
	AVDocSelectionPropertiesProc			Properties;

	/** Determine whether the current selection can be deleted. */
	AVDocSelectionCanDeleteProc				CanDelete;

	/** Delete the current selection. */
	AVDocSelectionDeleteProc				Delete;

	/** Determine whether the current selection can be copied. */
	AVDocSelectionCanCopyProc				CanCopy;

	/** Copy the selected item to the clipboard. */
	AVDocSelectionCopyProc					Copy;

	/** Enumerates the current selection. */
	AVDocSelectionEnumSelectionProc			EnumSelection;

	/** Change the view so that the current selection is visible. */
	AVDocSelectionShowSelectionProc			ShowSelection;

	/** Determine whether the current selection can be cut. */
	AVDocSelectionCanCutProc				CanCut;

	/** Cut the current selection. */
	AVDocSelectionCutProc					Cut;

	/** Determine whether the current selection can be pasted. */
	AVDocSelectionCanPasteProc				CanPaste;

	/** Paste the current selection from the clipboard. */
	AVDocSelectionPasteProc					Paste;

	/** Handles a key press. */
	AVDocSelectionKeyDownProc				KeyDown;

	/** Highlight the selection. */
	AVDocSelectionHighlightSelectionProc	HighlightSelection;

	/** Get the selection type so that a single selection server can register different selection 
	types based on the selection data. */
	AVDocSelectionGetSelectionTypeProc		GetSelectionType;

	/** Allow enumeration of the set of pages the selection covers. */
	AVDocSelectionEnumPageRangesProc		EnumPageRanges;

	/** Deprecated. */
	oldAVDocSelectionGetAVRectProc			oldGetAVRect; 

	/** Deprecated. */
	oldAVDocSelectionShowMenuProc			oldShowMenu; 

	/** Identify the bounding rectangle of a selection. */
	AVDocSelectionGetAVRectProc				GetAVRect;

	/** Request that the selection server display a context 
	menu appropriate for the current selection. */
	AVDocSelectionShowMenuProc				ShowMenu;

	/** Highlight the selection. */
	AVDocSelectionHighlightSelectionExProc	HighlightSelectionEx;

	/** Get a quad-based region for the selection. */
	AVDocSelectionAcquireQuadsProc			AcquireQuads;

	/** Determine whether a selection can be pasted. */
	AVDocSelectionCanPasteFromPlatformProc		CanPasteFromPlatform;

	/** Paste the selection. */
	AVDocSelectionPasteFromPlatformProc			PasteFromPlatform;
	
	/** Handles a key press using Unicode values. */
	AVDocSelectionUnicodeKeyDownProc			UnicodeKeyDown;

	/** The selection type. */
	ASAtom										Type;

} AVDocSelectionServerRec, *AVDocSelectionServer;
#endif



/* Keys for the new Cab-based <code>ViewDef</code>; for use with the <code>ViewDefEx</code> methods */

/** <code>boolean</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyBringToFront		"bringToFront"				

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewLayoutMode	"pageViewLayoutMode"	

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewPageNum		"pageViewPageNum"		

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewZoomType	"pageViewZoomType"		

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewZoom		"pageViewZoom"			

/** <code>int</code> */
#define kAVDocViewDefKeyPageViewX			"pageViewX"				

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewY			"pageViewY"			

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewStartThread	"pageViewStartThread"		

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewThreadIndex	"pageViewThreadIndex"	

/** binary: <code>PDBead</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyPageViewBead		"pageViewBead"				

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyOverViewMode		"overViewMode"			

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyOverViewPos			"overViewPos"			

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyOverViewX			"overViewX"				

/** <code>int</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyOverViewY			"overViewY"			

/** binary: <code>AVRect</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyWindowFrame			"windowFrame"		

/** binary: <code>AVRect</code> 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyWindowMaximized		"windowMaximized"		

/** cab 
  	@ingroup AVDocViewDef
*/
#define kAVDocViewDefKeyOCGStates			"ocgStates"				


#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A structure that defines a view of a document, including page, 
	zoom, and so on. 
	@see AVDocGetViewDef 
	@see AVDocSetViewDef 

	@note Numeric types have changed in Acrobat 6.0, and the 
	AVDocGetViewDef() and AVDocSetViewDef() methods have been superseded 
	by AVDocGetViewDefEx() and AVDocSetViewDefEx(). 

	@ingroup AVDocViewDef
*/
typedef struct _t_AVDocViewDef
{

	/** The size of the data structure. It must be set to <code>sizeof( AVDocViewDef)</code>. */
	ASSize_t	size;


	/** If <code>true</code>, bring the window to the front; if <code>false</code>, do not bring the window to the front. */
	ASBool		bringToFront;


	/** If <code>true</code>, use the next 6 page view fields. If <code>false</code>, do not use them. */
	ASBool			usePageViewInfo;	/* pageview info */

	/** The page layout mode; it must be one of PDLayoutMode. 
		@see PDLayoutMode 
	*/
	PDLayoutMode	pageViewLayoutMode;

	/** The page number. */
	PDPageNumber	pageViewPageNum;

	/** The zoom type; it must be one of AVZoomType. 
		@see AVZoomType 
	*/
	AVZoomType 		pageViewZoomType;

	/** The zoom factor; it is used if <code>pageViewZoomType</code> is AVZoomNoVary. Use zero to inherit the zoom. */
	ASFixed 		pageViewZoom;

	/** The x-coordinate to scroll to. */
	AVDevCoord			pageViewX;

	/** The y-coordinate to scroll to. */
	AVDevCoord			pageViewY;


	/** If <code>true</code>, use the next two article thread fields. If <code>false</code>, do not use them. */
	ASBool			pageViewStartThread;

	/** The current thread index. */
	AVPageIndex		pageViewThreadIndex;

	/** The current PDBead. */
	PDBead 			pageViewBead;


	/** If <code>true</code>, use the next four view fields. If <code>false</code>, do not use them. */
	ASBool		useOverViewInfo;	

	/** The PDPageMode to use. 
		@see PDPageMode 
	*/
	PDPageMode	overViewMode;			

	/** The position of the splitter. */
	AVPixelOffset	overViewPos;   

	/** The x-coordinate to scroll to in the bookmark or thumbnail pane.*/
	ASInt32		overViewX;

	/** The y-coordinate to scroll to in the bookmark or thumbnail pane. */
	ASInt32		overViewY;

	/** If <code>true</code>, use the <code>windowFrame</code> field. If <code>false</code>, do not use it.*/
	ASBool		useWindowInfo;	

	/** The new window frame in which to display the document.*/
	AVScreenRect	windowFrame;				

	/** Is the window frame maximized. */
	ASBool			windowMaximized;

	/** Currently unused. */
	const char*		unused2;		/* obsolete */

} AVDocViewDefRec, *AVDocViewDef;

#endif


/**
	A data structure representing a destination in a PDF document. 
	An AVDestInfo carries all the information that a PDViewDestination 
	can. It is used for ensuring that cross-document links in external 
	windows act as expected, so a client can go to a destination 
	without building it via PDViewDestCreate(), which does not 
	work on read-only documents. 
	@see AVPageViewToDestInfo 
	@see AVPageViewUseDestInfo 
	@see AVDestInfoDestroy 
*/
typedef struct _t_AVDestInfo
{

	/** The size of the data structure. It must be set to <code>sizeof(AVDestInfo)</code>.*/
	ASSize_t		size;
	

	/** The named destination associated with this destination. If this is non-<code>NULL</code>, the other attributes 
	are ignored. This destination may contain multi-byte characters.*/
	const char*		namedDest;

	/** The length of <code>namedDest</code> in bytes. */
	AVTArraySize   nameLength;

	/** The page number of the destination view. */
	PDPageNumber	pageNum;

	/** The fit type of the destination view. It must be one of View Destination Fit Types. 
  		@ref ViewDestinationFitTypes
	*/
	ASAtom			fitType;

	/** A rectangle enclosing the destination view. */
	ASFixedRect		destRect;

	/** The zoom factor of the destination view. Use zero to inherit the zoom. */
	ASFixed			zoom;
	
} AVDestInfoRec, *AVDestInfo;


/**
	A callback that can be associated with an AVDoc when it 
	is opened (via an AVDocOpenParamsRec). It can restrict the 
	set operations allowed on the document. When AVDocPermRequest() 
	is called, this callback must be consulted to deny or grant 
	the permission. If it denies permission, AVDocPermRequest() 
	will also deny permission. If it grants permission, the 
	security handler for the document will be consulted to determine 
	the result of AVDocPermRequest(). This callback can only deny 
	permissions allowed by the security handler; it cannot grant 
	permissions that the security handler does not grant. 
	@param doc IN/OUT The current document. 
	@param obj IN/OUT Description of target object. 
	@param opr IN/OUT Description of target operation. 
	@return The status. 
*/
typedef ACCBPROTO1 PDPermReqStatus (ACCBPROTO2 *AVDocPermReqProc)(AVDoc doc, PDPermReqObj obj, PDPermReqOpr opr);


/************************************************************************************\
|*																					*|
|*									AVWindow										*|
|*																					*|
\************************************************************************************/
#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	Creates and manages windows. Plug-ins should use AVWindows for their own
	dialog boxes, floating palettes, and so on, to ensure that those windows work well with
	the Acrobat viewer. For example, under Windows they are hidden when the Acrobat
	viewer is turned into an icon. Once your plug-in creates an AVWindow, it is free to use
	platform-dependent code to put whatever you would like in the window.
	@see AVWindowNew
	@see AVWindowNewFromPlatformThing
	@see AVDocGetAVWindow
	@see AVWindowDestroy
	@see AVWindowUserClose
	@see AVWindowDrawNow
	@see AVWindowGetFrame 
	@see AVWindowSetFrame
	@see AVWindowGetInterior 
	@see AVWindowGetOwnerData 
	@see AVWindowSetOwnerData
	@see AVWindowGetPlatformThing 
	@see AVWindowGetTitle 
	@see AVWindowSetTitle
	@see AVWindowIsKey 
	@see AVWindowBecomeKey
	@see AVWindowSetWantsKey
	@see AVWindowResignKey
	@see AVWindowBringToFront
	@see AVWindowIsVisible 
	@see AVWindowShow
	@see AVWindowHide
	@see AVWindowInvalidateRect
	@see AVWindowMaximize
*/
#ifndef _T_AVWINDOW
#define _T_AVWINDOW

#ifdef __cplusplus
class AVBaseWindow;
typedef AVBaseWindow* AVWindow;
#else
typedef struct _t_AVWindow *AVWindow;
#endif // __cplusplus

#endif // _T_AVWINDOW

#endif // ACRO_SDK_LEVEL


#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	Parameter to control the security mode in which document is opened.
	If <code>kDoNotForce</code> (the default mode), Acrobat applies it's own logic.
	If <code>kForceOpenInProtectedView</code>, PDF will be opened in Protected View only.
	If <code>kForceOpenAsTrusted</code>, PDF will be opened in trusted mode only.
*/

typedef enum _t_AVDocForceOpenOption
{
#if WIN_ENV
	kDoNotForce, 
	kForceOpenInProtectedView,	
	kForceOpenAsTrusted
#else
	kDoNotForce
#endif
} AVDocForceOpenOption;

/**
	Parameters used when opening a file. 

	<p>In UNIX, it is not possible to set the frame of the <code>NULL</code> 
	document (that is, the window to show when no document is 
	open) using this data structure. </p>
	@see AVAppOpenHelpFileWithParams 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDocWithParams
*/

typedef struct _t_AVDocOpenParams
{

	/** The size of the data structure. It must be set to <code>sizeof( AVDocOpenParamsRec)</code>. */
	ASSize_t		size;
	

	/** If <code>true</code>, <code>frame</code> is used to specify the size 
		and location of the window into which the document is opened. 
		If <code>false</code>, <code>frame</code> is ignored and the default frame is used 
		instead. See also <code>visible</code>. 
	*/
	ASBool			useFrame;	

	/** An AVRect specifying the size and location 
		of the window into which the document is opened. On Mac 
		OS, the coordinates are global screen coordinates. On Windows, 
		the coordinates are MDI client coordinates. See also <code>visible</code>.
	*/
	AVScreenRect    frame;		
	

	/** If <code>true</code>, <code>visible</code> is used to determine 
		whether the window is visible after the document 
		is opened. If <code>false</code>, <code>visible</code> is ignored. See also <code>visible</code>.
	*/
	ASBool			useVisible;	

	/** Specifies the window's visibility. If <code>visible</code> 
		is <code>false</code> and <code>useVisible</code> is <code>true</code>, <code>frame</code> is ignored regardless 
		of the setting of <code>useFrame</code>. On Mac OS, if <code>true</code>, the document 
		is opened into a visible window. If <code>false</code>, the document 
		is opened into a hidden window. On Windows, if <code>true</code>, the 
		document is opened in a visible window. If <code>false</code>, the document 
		is opened in a minimized window. 
	*/
	ASBool			visible;		

	/** Indicates whether the <code>serverType</code> and <code>serverCreationData</code> fields are used. */
	ASBool			useServerType;			

	/** The name of the AVDoc server for this AVDoc: 
		<code>EXTERNAL</code> means the AVDoc server for an external window. 
	*/
	const char*		serverType;				

	/** Platform-dependent server data 
		to associate with the AVDoc server. For a <code>serverType</code> of 
		<code>EXTERNAL</code>, it must be of type <code>ExternalDocServerCreationData</code>.
	*/
	void*			serverCreationData;		


	/** Indicates whether the <code>sourceDoc</code> field is used. */
	ASBool			useSourceDoc;		

	/** An AVDoc whose window will be taken over 
		by a new document. <code>sourceDoc</code> will be closed at the same time.
	*/
	AVDoc			sourceDoc;				
											
	/** Indicates whether the <code>readOnly</code> field is used. */
	ASBool			useReadOnly;		

	/** If <code>true</code>, open the document in read-only mode. */
	ASBool			readOnly;			

	/** Indicates whether the <code>viewType</code> field is used. */
	ASBool			useViewType;			

	/** The type of view to open for the document. 

	<p>Permissible values:</p>
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD><code>"AVPageView"</code></TD><TD>Displays only the AVPageView, which is the window that displays the PDF file. It does not 
	display scrollbars, the toolbar, or the bookmark or thumbnails pane. Annotations, such as links, are active.</TD></TR>
	<TR><TD><code>"AVDocView"</code></TD><TD>Displays the AVPageView, scrollbars, and bookmark and thumbnails pane. Annotations, such as 
	links, are active.</TD></TR>
	<TR><TD><code>"AVExternalView"</code></TD><TD>Displays the AVPageView, scrollbars, toolbar, and bookmark or thumbnails pane. Annotations, 
	such as links, are active.</TD></TR>
	<TR><TD><code>"AVEmbeddedView"</code></TD><TD>Embeds the PDF file in an external document such as an HTML file. It shows the first page of the PDF 
	file. No scrollbars are visible. The toolbar and bookmark or thumbnails pane are visible. Annotations, such as links, are neither 
	displayed nor active.</TD></TR>
	</TABLE>

	*/
	const char* 	viewType;				

	/** Indicates whether the <code>viewDef</code> field is used. */
	ASBool			useViewDef;				

	/** Initial view with which to open the document. It must be an AVDocViewDef. */
	AVDocViewDef	viewDef;			
	
	/** A <code>boolean</code> indicating whether the <code>permReqProc</code> field be used. */
	ASBool			usePermReqProc;			

	/** Returns PDPermReqDenied to deny a permission, PDPermReqGranted to grant one. */
	AVDocPermReqProc permReqProc;			

	/** An expanded and more flexible version of the <code>viewDef</code> field. If both are specified, the older AVDocViewDef takes precedence. */
	ASCab			 openActions;			
											
	/** Indicates whether to suppress any non-alert dialog boxes that may be triggered by opening the document. */
	ASBool			suppressDialogs;

	/** 
		A PDF 1.7+ file may contain a collection dictionary that specifies a target
		document, which is an embedded file within the host document that should be
		opened instead of the host. Assuming the caller is opening a collection
		document that specifies such a target document, the following applies:
	 
		<ul>
			<li>
				<p>If <code>useCollectionPref</code> is set to <code>false</code>, then 
				<code>collectionPref</code> is ignored, and:</p>
				<ul>
					<li>
			 			AVDocOpenFromFileWithParams() will open the target document, honoring the 
						collection dictionary.
					</li>
					<li>
			 			AVDocOpenFromPDDocWithParams() will open the host document, ignoring the 
						collection dictionary.
					</li>
				</ul>
			</li>
			<li>
				If <code>useCollectionPref</code> is <code>true</code> and <code>collectionPref</code> is 
				<code>true</code>, then all APIs will open the target document, honoring the collection 
				dictionary.
			</li>
			<li>
				If <code>useCollectionPref</code> is <code>true</code> and <code>collectionPref</code> is 
				<code>false</code>, then all APIs will open the host document, ignoring the collection 
				dictionary.
			</li>
		</ul>
	 
		<p>AVDocOpenFromFileWithParams() and AVDocOpenFromPDDocWithParams() exhibit different default 
		behavior since the expectation around opening an AVDoc from a file versus a PDDoc is different; 
		a caller would be surprised if AVDocOpenFromPDDoc() did not return an AVDoc for that same PDDoc.
		The caller should generally set <code>useCollectionPref</code> to <code>false</code> unless 
		special behavior is required.</p>
	*/
	ASBool			useCollectionPref;
	ASBool			collectionPref;

	/** If <code>true</code>, <code>minimize</code> is used to determine 
		whether the window is minimized after the document 
		is opened. If <code>false</code>, <code>minimize</code> is ignored. See also <code>minimize</code>.
	*/
	ASBool			useMinimize;	

	/** Specifies the window's minimize state. 
	*/
	ASBool			minimize;	

	/**
	  DEPRECATED in Acrobat 11. Use forceOpenOption.
	 */
	ASBool			forceOpenProtectedView ;

	/** This parameter controls the mode in which PDF will open. */
	AVDocForceOpenOption	forceOpenOption;
}
AVDocOpenParamsRec, *AVDocOpenParams;

#endif

/* Data types for "EXTERNAL" serverType documents */

/**
	A callback in ExternalDocServerCreationData. It is called when a 
	cross-document link is clicked in an AVDoc in an external 
	application's window. 
	@param path Path to document to which the link points. 
	@param fileSys The ASFileSys with which to open the document. 
	@param viewDef The AVDocViewDef with which to open the document. 
	@param srcDoc The AVDoc that contains the cross-document 
	link. 
	@param data User-supplied data that was passed in the 
	call to CrossDocLinkProc().
	@return The AVDoc for the new document. 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef ACCBPROTO1 AVDoc (ACCBPROTO2 *CrossDocLinkProc)(ASPathName path, ASFileSys fileSys, AVDocViewDef viewDef, AVDoc srcDoc, void* data);

/**
	(Unused) Callback in ExternalDocServerCreationData for opening 
	PDF files in external windows. 
	@param msg IN/OUT A message for the external application. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVSetMessageProc(). 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVSetMessageProc)(char* msg, void* clientData);

/**
	Callback in ExternalDocServerCreationData to return focus 
	to the browser displaying the document. 
	@param clientData IN/OUT User-supplied data. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVSetFocusProc)(void* clientData);

/**
	A callback in ExternalDocServerCreationData. It is called when a 
	cross-document link is clicked in an AVDoc in an external 
	application's window. 
	@param path IN/OUT The path to the document to which the link points. 
	@param fileSys IN/OUT The ASFileSys with which to open the document. 
	@param viewDef IN/OUT The AVDocViewDef with which to open the document. 
	@param destInfo IN/OUT A destination in a PDF document. 
	@param srcDoc IN/OUT The AVDoc that contains the cross-document 
	link. 
	@param data IN/OUT User-supplied data that was passed in the call 
	to CrossDocLinkProc(). 
	@return The AVDoc for the new document. 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef ACCBPROTO1 AVDoc (ACCBPROTO2 *CrossDocLinkWithDestProc)(
	ASPathName		path,
	ASFileSys 		fileSys,
	AVDocViewDef 	viewDef,
	AVDestInfo		destInfo,
	AVDoc			srcDoc,
	void* 			data);

#if WIN_PLATFORM
/** */
typedef HWND ExternalDocWindowData;

#elif MAC_PLATFORM


/**
	(Mac OS only) Data for an external window. A platform-dependent 
	structure used in ExternalDocWindowData when opening an 
	AVDoc with AVDocOpenFromASFileWithParamString(), AVDocOpenFromASFileWithParams(), 
	or AVDocOpenFromPDDocWithParams(). 

	<p>Coordinates specified in this structure are in application 
	space. Use AVRectToRect() to translate from user space to 
	device space coordinates, then use Mac OS <code>GlobalToLocal</code> 
	function to translate from device space coordinates to application 
	space coordinates. </p>
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef struct _t_ExternalDocWindowRefData
{
	/** View */
#if __OBJC__
	NSView 	*pluginView;
#else
	void*	*pluginView;
#endif

	/** The x-displacement in application space coordinates 
		from the application's window to the AVPageView in which 
		Acrobat renders the PDF file.
	*/
	ASUns32		*x;

	/** The y-displacement in application space coordinates 
		from the application's window to the AVPageView in which 
		Acrobat renders the PDF file.
	*/
	ASUns32		*y;

	/** The width of the external window, specified in device space units. */
	ASUns32		*width;

	/** The height of the external window, specified in device space units. */
	ASUns32		*height;

	/** The x-displacement in application space coordinates from the AVPageView in which Acrobat renders the PDF file 
		to the actual PDF file page. It should usually be <code>0</code>.
	*/
	ASInt32	*portx;

	/** The y-displacement in application space coordinates from the AVPageView in which Acrobat renders the PDF file 
		to the actual PDF file page. Should usually be <code>0</code>.
	*/
	ASInt32 *porty;

} ExternalDocWindowRefDataRec, *ExternalDocWindowRefData;


#if !AS_ARCH_64BIT
/**
	(Mac OS only) A callback in ExternalDocWindowData for opening 
	PDF files in external windows. It is called for a mouse-related 
	event, such as mouse down or mouse movement. 
	@param curs A handle to the cursor. It is a <code>CursHandle</code>. 
	@param clientData User-supplied data that was passed in 
	ExternalDocWindowData.
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVSetCursorProc)(CursHandle curs, void* clientData);
#endif

/**
	Data for an AVDoc in an external window. It is a platform-dependent 
	structure used in ExternalDocServerCreationData when opening 
	an AVDoc with AVDocOpenFromASFileWithParamString(), AVDocOpenFromASFileWithParams(), 
	or AVDocOpenFromPDDocWithParams(). 

	<p>On Mac OS, a plug-in must handle events that affect the 
	window, such as resize and mouse events. </p>
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef struct _t_ExternalDocWindowData
{

	/** A pointer to external window data. It must be of type ExternalDocWindowRefData. */
	ExternalDocWindowRefDataRec	*ref;


#if !AS_ARCH_64BIT
	/** A callback for handling mouse-related events, such as mouse down or mouse movement.*/
	AVSetCursorProc		setCursor;
#endif

	/** Optional client-specified data.  */
	void*							setCursorProcData;
	
} ExternalDocWindowDataRec, *ExternalDocWindowData;

#elif UNIX_PLATFORM

typedef Window ExternalDocWindowData;

#elif OS2_PLATFORM

typedef HWND ExternalDocWindowData;

#endif

/**
	Data for an AVDoc in an external window. It is a platform-dependent 
	structure used in AVDocOpenParams when opening an AVDoc 
	with AVDocOpenFromASFileWithParamString(), AVDocOpenFromASFileWithParams(), 
	or AVDocOpenFromPDDocWithParams(). 
	@see AVDocOpenFromASFileWithParamString 
	@see AVDocOpenFromASFileWithParams 
	@see AVDocOpenFromPDDocWithParams 
*/
typedef struct _t_ExternalDocServerCreationData
{
	/** The size of the data structure. It must be set to <code>sizeof(ExternalDocServerCreationData Rec)</code>. */
	ASSize_t 					size;

	/** A platform-dependent structure of type ExternalDocWindowData representing a window. 

	<p>Operating system detail:</p>
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Description</TH></TR>
	<TR><TD>Mac OS</TD><TD>The ExternalDocWindowData structure is used.</TD></TR>
	<TR><TD>Windows</TD><TD><code>HWND</code> is cast as ExternalDocWindowData.</TD></TR>
	<TR><TD>UNIX</TD><TD><code>Widget</code> is cast as ExternalDocWindowData.</TD></TR>
	</TABLE>
	*/
	ExternalDocWindowData 		platformWindow;

	/** An optional callback. It is called when the Acrobat button (if present) is clicked in the external 
		application.
	*/
	AVExecuteProc				acrobatProc;

	/** Client-specified data for <code>acrobatProc</code>. */
	void* 						acrobatProcData;

	/** A callback of type CrossDocLinkProc. */
	CrossDocLinkProc			crossDocLinkProc;

	/** Client-specified data for <code>crossDocLinkProc</code>. */
	void*						crossDocLinkProcData;

	/** Currently unused. */
	AVSetMessageProc			setMessage;

	/** Currently unused. Client-specified data for <code>setMessage</code>. */
	void*						setMessageProcData;

	/** A callback to call when a cross-document link occurs. */
	CrossDocLinkWithDestProc	crossDocLinkWithDestProc;

	/** Client-specified data for <code>crossDocLinkWithDestProc</code>.*/
	void*						crossDocLinkWithDestData;


	/** (New in Acrobat 5.0) A callback to call when Acrobat returns focus to the browser displaying 
		the document.
	*/
	AVSetFocusProc			setFocus;

	/** (New in Acrobat 5.0) Client-specified data for <code>setFocus</code>. */
	void*						setFocusProcData;

	/** (New in Acrobat 7.0) Used for extended TAB handling in the browser. */
	AVSetFocusProc			setFocusSHIFTTAB;
	/** (New in Acrobat 7.0) Used for extended TAB handling in the browser. */
	void*					setFocusSHIFTTABProcData;

	/** (New in Acrobat 7.0) Used for extended TAB handling in the browser. */
	AVSetFocusProc			setFocusCTRLTAB;
	/** (New in Acrobat 7.0) Used for extended TAB handling in the browser. */
	void*					setFocusCTRLTABProcData;

} ExternalDocServerCreationDataRec, *ExternalDocServerCreationData;


/**
	Constant values indicating the type of document server being 
	used for a document. 
	@see AVDocGetServerType 
*/
typedef enum _t_AVDocServerType {
	/** Unknown server type. */
	AVDocServerUnknown,				
	/** The default document server (used for most documents). */
	AVDocServerDefault,	
	/** The same as the default document server. */
	AVDocServerInternal = AVDocServerDefault,				
	/** Used for external documents, shown in a web browser. */
	AVDocServerExternal,				
	/** A server used for documents displayed in the help window. */
	AVDocServerHelp					
} AVDocServerType;

/**
   Specifies a special value for
   AVDocSetSplitterPosition() and AVDocGetSplitterPosition().
   
   @see AVDocSetSplitterPosition
   @see AVDocGetSplitterPosition
*/
#define kAVDocSplitterPinnedLeft (0)
/**
   Specifies a special value for
   AVDocSetSplitterPosition() and AVDocGetSplitterPosition().
   
   @see AVDocSetSplitterPosition
   @see AVDocGetSplitterPosition
*/
#define kAVDocSplitterPinnedRight (ASMAXInt16)

/************************************************************************************\
|*																					*|
|*								AVAnnotHandler										*|
|*																					*|
\************************************************************************************/

/* Flags returned by <code>AVAnnotHandler->GetFlags()</code>. */
#define AV_ANNOT_POPUPISREADONLY			0x0001
#define AV_ANNOT_SHOW_OFFSCREEN_INDICATOR	0x0002
#define AV_ANNOT_SUPPORTS_REPLIES			0x0004
#define AV_ANNOT_SUPPRESS_POPUP				0x0008

/*------------------------------------------------------------------------
   The layer parameter of Annotation Handlers defines the draw order and (in reverse)
   the order of mouse hit detection.  Valid ranges are fixedZero - fixedPositiveInfinity.
   Notice that any form of non-update driven drawing (like during a DoClick method) 
   can make an annotation in a lower level appear to be above those in higher levels.
 ------------------------------------------------------------------------*/
/** Links live at this level. */  
#define LINK_LAYER			fixedOne		
/** Closed notes live here, with open notes just above. */
#define NOTE_LAYER			fixedThree		
/** Set this bit of <code>flags</code> to prevent the standard text selection tool from inverting your annotation. */
#define ANNOT_CLIP_TEXT_SELECTION	0x0001	
/** Set this bit of <code>flags</code> to prevent the standard "shift-key ignores annotations" behavior. */
#define ANNOT_WANTS_SHIFT_KEY		0x0002	
											

/**
	A structure used to describe information for a particular 
	annotation type. 
	@see AVAnnotHandlerDeleteInfoProc 
	@see AVAnnotHandlerGetInfoProc 
	@see AVAnnotHandlerGetInfo 
*/
typedef struct _AVAnnotHandlerInfoRec {

	/** The size of the data structure. It must be set to <code>sizeof(AVAnnotHandlerInfoRec)</code>. */
	ASSize_t size;

	/** The user interface name of the annotation type in the host encoding. */
	unsigned char *cName;	

	/** A platform-dependent bitmap used as the annotation icon. If it is <code>NULL</code>, the annotation 
		manager uses the unknown annotation icon for the annotation. 
	*/
	void *vBitmap;			
} AVAnnotHandlerInfoRec, *AVAnnotHandlerInfo;

/* UI friendly name is in host encoding. Bitmap is platform dependent, if set
** to null, the annotation manager uses the Unknown annotation icon. */
#define AVAnnotHandlerInfoInit(x)				\
	do { \
	memset(x, 0, sizeof(AVAnnotHandlerInfoRec));	\
	x->size = sizeof(AVAnnotHandlerInfoRec); \
	}while(0)

/* Operations we can ask an annotation to perform */

/**
	<p>An enumeration detailing operations to which the annotation can be requested to respond.</p>

	<p>Operation codes containing the word <code>"Do"</code> are sent to
	notify the annotation handler of a significant event.
	All other operation codes are sent to tell the annotation
	to perform a specific action.</p>

	@see AVPageViewFocusAnnotPerformOp 
*/
enum {
	/** Accept input focus. */
	kAVAnnotAcceptFocus,		
	/** Lost the input focus. */
	kAVAnnotLostFocus,			
	/** The user presses Enter while in focus. */
	kAVAnnotDefaultAction,		 
	/** Show a context menu for the annotation. */
	kAVAnnotShowMenu,			
	/** The focus is temporarily lost; it may be restored. */
	kAVAnnotSuspendFocus,		
	/** The focus has been restored. */
	kAVAnnotResumeFocus,
	/** The page the annotation is on has become the current page. */
	kAVAnnotDoPageHasOpened,
	/** The page the annotation is on is no longer the current page. */
	kAVAnnotDoPageHasClosed,
	/** The page this annotation is on has become visible to the user. */
	kAVAnnotDoPageIsInView,
	/** The page this annotation is on is no longer visible to the user. */
	kAVAnnotDoPageIsNotInView
};
#ifndef _T_AVANNOTOP
#define _T_AVANNOTOP
typedef ASEnum16 AVAnnotOp;
#endif /* _T_AVANNOTOP */

/* Additional information passed to the annotation when performing an
   operation. For some operations a <code>NULL</code> will be passed; in others a
   pointer to an AVAnnotOpData structure will be passed.
*/
#if (ACRO_SDK_LEVEL >= 0x00060000)
/** Constants that specify how an annotation operation request was triggered.
	@see AVPageViewFocusAnnotPerformOp
*/
typedef enum {
	/** The first entry for <code>memset</code> of AVAnnotOpDataRec to <code>0</code>. */
	kAVAnnotUnknown = 0, 
	/** An operation triggered by a mouse click. */
	kAVAnnotClick,
	/** An operation triggered by a Tab key press. */
	kAVAnnotTab
} AVAnnotOpReason;

/**
	Additional information passed to the annotation when performing 
	an operation. For some operations a <code>NULL</code> will be passed; 
	in others a pointer to an AVAnnotOpData structure will be 
	passed. 

	@note The coordinate numeric type has changed in Acrobat 6.0. 
	@see AVPageViewSetFocusAnnot 
*/
typedef struct _t_AVAnnotOpData {
	/** Set by Acrobat to the size of this record. */
	ASSize_t size;
	/** If the operation is kAVAnnotShowMenu, this value provides the default location of the menu in AV device coordinates (<code>x</code>). */
	AVDevCoord x;
	/** If the operation is kAVAnnotShowMenu, this value provides the default location of the menu in AV device coordinates (<code>y</code>) */
	AVDevCoord y;
	/** Used by Forms and Annots to determine when an annotation is getting focus via a mouse click.*/
	void * clientData;
	/** The reason for this operation */
	AVAnnotOpReason reason;
	/** The page number this annotation is on. */
	ASInt32	pageNum;
} AVAnnotOpDataRec, *AVAnnotOpData;
#endif

  /* Concrete instantiation of an annot handler object. Annot handler implementations will
     usually "subclass" this by pass a ptr to struct with an AVAnnotHandlerRec as
     its first member to AVAppRegisterAnnotHandler, cast as an AVAnnotHandler.
   */

/* AVAnnotHandlerEnumProc -- used by AVAppEnumAnnotHandlers.
** If the proc returns <code>false</code>, the enumeration will terminate.
*/
#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A data structure containing callbacks that implement an annotation 
	handler. The callbacks implement the annotation handler 
	functions. For example, they can be used to draw the annotation and highlight the 
	annotation when it is selected. The data specifies properties 
	of the annotation, such as text selection behavior. 
	
	<p>Appearance drawing is new as of Acrobat 6.0. If the handler 
	implements the GetAppearance() or GetAppearanceEx() callback, the new
	drawing style is used. If the GetAppearance() callback returns <code>false</code> or 
	is not implemented, the viewer calls the drawing procedure 
	(DrawEx() if present, Draw() otherwise) to draw the annotation 
	using Acrobat 5.0-style drawing. </p>

	<p>For the new style of appearance drawing, the viewer calls 
	the handler's BeginAppearanceDrawing() callback, then draws 
	the appearance object. If the drawing operation completes 
	without errors, it call the the handler's BeginAppearanceDrawing() 
	callback; if an error occurs or the operation is cancelled, 
	it calls the CancelAppearanceDrawing() callback. This can 
	happen if, for example, the user switches to another page 
	before the drawing is completed. </p>

	<p>The handler must not destroy or modify the appearance object 
	while it is being drawn. It can do so only after the EndAppearanceDrawing() 
	or CancelAppearanceDrawing() callback is exercised. </p>
	@see AVAnnotHandlerEnumProc 
	@see PDAnnotHandlerDeleteAnnotInfoProc 
	@see PDAnnotHandlerGetAnnotInfoFlagsProc 
	@see PDAnnotHandlerGetAnnotInfoProc 
	@see PDAnnotHandlerGetTypeProc 
	@see AVAppRegisterAnnotHandler 
	@see AVAppGetAnnotHandlerByName 
	@see AVDocCopyAnnot 

	@note The types of numeric values in callbacks have changed 
	in Acrobat 6.0. 
*/
typedef struct _t_AVAnnotHandler *AVAnnotHandler;

/**
	Called to request that the annotation appearance be drawn. 
	
	@param annotHandler IN/OUT The annotation handler responsible 
	for this annotation. 
	@param anAnnot IN/OUT The annotation. 
	@param pageView IN/OUT The AVPageView in which the annotation 
	is located. 
	@param updateRect IN/OUT The portion of the annotation's bounding 
	rectangle that should be drawn. 
	@return <code>true</code> if the callback completed drawing successfully, <code>false</code> 
	otherwise. 
	@see AVAnnotHandlerDrawProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerDrawExProc)(
	AVAnnotHandler annotHandler, 
	PDAnnot anAnnot, 
	AVPageView pageView,
	AVDevRect *updateRect);

/**
	Deprecated in Acrobat 6.0. Use AVAnnotHandlerDoClickExProc(). 
	
	<p>(Optional) A callback for AVAnnotHandler. It handles both 
	left and right mouse button clicks within the annotation. 
	If <code>NULL</code>, the annotation behaves as if the callback returned 
	<code>false</code>. </p>
	@param annotHandler The annotation handler responsible 
	for this annotation. 
	@param hitAnnot The annotation in which the mouse was 
	clicked. 
	@param pageView The AVPageView in which the annotation 
	is located. 
	@param xHit The x-coordinate of the mouse click. 
	@param yHit The y-coordinate of the mouse click. 
	@param flags Indicates which modifier keys are pressed. 
	It must be an <code>OR</code> of the Modifier Keys values. 
	@param clickNo <code>1</code> if this is a single click, <code>2</code> if this is a double 
	click, <code>3</code> if this is a triple click.
	@return <code>true</code> if the callback handled the mouse click, <code>false</code> if it 
	did not. If the callback does not handle the click, it is 
	passed to any annotation at the same location in lower layers. 
	
	@see AVAnnotHandlerDoKeyDownExProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerDoClickProc)(AVAnnotHandler annotHandler, PDAnnot hitAnnot,
                     AVPageView pageView,
					AVDevCoord xHit, AVDevCoord yHit,
					AVFlagBits16 flags,
					AVTCount clickNo);

/**
	Deprecated in Acrobat 6.0. Use AVAnnotHandlerAdjustCursorExProc(). 
	
	<p>(Optional) A callback for AVAnnotHandler. It controls the 
	cursor shape when the cursor is within the annotation. If 
	<code>NULL</code>, the annotation behaves as if the AdjustCursor() callback 
	returned <code>false</code>. </p>
	@param annotHandler The annotation handler responsible 
	for this annotation. 
	@param anAnnot The annotation containing the cursor. 
	@param pageView The AVPageView in which the annotation 
	is located. 
	@param xHit The cursor's current x-coordinate. 
	@param yHit The cursor's current y-coordinate.
	@return <code>true</code> if the callback handled the adjust cursor event, <code>false</code> 
	otherwise. The callback would return <code>false</code>, for example, 
	if the annotation is irregularly shaped and the cursor is 
	not currently over the real annotation, even though it is 
	within the rectangular bounding box that the Acrobat viewer 
	uses to specify annotations. 
	@see AVAnnotHandlerAdjustCursorExProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerAdjustCursorProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot,
  					AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit);

/**
	A callback for AVAnnotHandler. It is called by AVPageViewIsAnnotAtPoint() 
	to determine whether a point is within an annotation. The 
	annotation handler is free to determine what it means for 
	the point to be <i>in</i> the annotation. For example, if the 
	annotation appears only as the outline of a circle, the 
	point may be <i>in</i> the annotation only when it is near the 
	border of the circle, but not when it is elsewhere within the circle. 
	@param annotHandler The annotation handler responsible 
	for this annotation. 
	@param pageView The AVPageView in which the annotation 
	appears. 
	@param anAnnot The annotation being tested. 
	@param xHit The x-coordinate of the point to test. 
	@param yHit The y-coordinate of the point to test.
	@return <code>true</code> if the point is in the annotation, <code>false</code> otherwise. 

	@note The coordinate numeric types have changed in Acrobat 
	6.0. 
	@see AVPageViewIsAnnotAtPoint 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerPtInAnnotViewBBoxProc)(AVAnnotHandler annotHandler, AVPageView pageView,
                   PDAnnot anAnnot, AVDevCoord xHit, AVDevCoord yHit);
                  

/**
	A callback for AVAnnotHandler. It returns the rectangle enclosing 
	the annotation on the screen. 
	@param annotHandler IN/OUT The annotation handler responsible 
	for the annotation. 
	@param pageView IN/OUT The AVPageView in which the annotation 
	is located. 
	@param anAnnot IN/OUT The annotation whose bounding box is returned. 
	
	@param bbox IN/OUT (Filled by the callback) The annotation's bounding 
	rectangle. 
	@see AVAnnotHandlerPtInAnnotViewBBoxProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerGetAnnotViewBBoxProc)(AVAnnotHandler annotHandler, AVPageView pageView,
                   PDAnnot anAnnot, AVDevRect *bbox); 
#endif /* (ACRO_SDK_LEVEL >= 0x00060000) */


/**
	A callback for AVAppEnumAnnotHandlers(). It is called once for 
	each annotation handler currently registered with the Acrobat 
	viewer (see AVAppRegisterAnnotHandler()). 
	@param annotHandler IN/OUT The annotation handler. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVAppEnumAnnotHandlers. 
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 	
	@see AVAppEnumAnnotHandlers 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerEnumProc)(AVAnnotHandler annotHandler, void *clientData);


/**
	(Optional) A callback for AVAnnotHandler. It is called when 
	an annotation is removed from the selection, and should 
	un-highlight the annotation. Set it to <code>NULL</code> if omitted. 
	@param annotHandler IN/OUT The annotation handler responsible 
	for the annotation that was removed from the selection. 
	
	@param anAnnot IN/OUT The annotation that was removed from the 
	selection. 
	@param pageView IN/OUT The AVPageView in which the annotation 
	appears. 
	@see AVDocClearSelection 
	@see AVDocSetSelection 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerNotifyAnnotRemovedFromSelectionProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);                                 

/**
	(Optional) A callback for AVAnnotHandler. It is called when 
	an annotation is added to the selection, and should highlight 
	the annotation. Set it to <code>NULL</code> if it is omitted. 

	<p>To allow only a single annotation to be selected at a time, keep 
	a global variable containing the selected annotation and, 
	on each invocation of NotifyAnnotAddedToSelection(), first 
	deselect the current selection, if any (that is, if selectedAnnot 
	is non-<code>NULL</code>), call its AVAnnotHandlerNotifyAnnotRemovedFromSelectionProc(), select 
	the new annotation, and set <code>selectedAnnot</code>. Of course, <code>RemovedFrom</code> 
	should set <code>selectedAnnot</code> to <code>NULL</code>. </p>
	@param annotHandler IN/OUT The annotation handler responsible 
	for the annotation that was added to the selection. 
	@param anAnnot IN/OUT The annotation that was added to the selection. 	
	@param pageView IN/OUT The AVPageVIew containing the annotation 
	that was added to the selection. 
	@see AVDocSetSelection 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerNotifyAnnotAddedToSelectionProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);                                 

/**
	Deprecated in Acrobat 6.0. Use AVAnnotHandlerDrawExProc(). 
	
	<p>(Optional) A callback for AVAnnotHandler that draws the annotation. 
	Set it to <code>NULL</code> if the annotation handler has no <code>Draw</code> method.</p> 
	
	<p>If the annotation has an appearance (AP) entry, use this 
	information to draw the annotation. Read the annotation's 
	appearance state (AS) entry to determine which appearance 
	to use. Then read the Cos stream for the appropriate appearance 
	and display it with AVPageViewDrawCosObj(). </p>
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation to draw. 
	@param pageView The AVPageView containing the annotation.
	@see AVAnnotHandlerDrawExProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerDrawProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);   

/**
	(Unused) A callback for AVAnnotHandler. It allows the annotation 
	handler to add any attributes to the annotation object to 
	make sure the new annotation is in a valid initial state 
	for its subclass. 
	@param annotHandler The annotation handler. 
	@param anAnnot The annotation to modify. 
	@param pageView The AVPageView in which the annotation 
	is located.
	@return <code>true</code> if the new annotation handler is in a valid initial 
	state for its subclass, <code>false</code> otherwise. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerNewProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);       

/**
	(Required) A callback for AVAnnotHandler. It returns an ASAtom 
	indicating the annotation type for which the handler is 
	responsible. This corresponds to the annotation's Subtype 
	key in the PDF file. 

	<p>This is the method that AVAppGetAnnotHandlerByName() uses 
	to find the correct handler. </p>
	@param annotHandler IN/OUT The annotation handler whose type is 
	returned. 
	@return The annotation type for which this handler is responsible. 
	
	@see AVAppRegisterAnnotHandler 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *AVAnnotHandlerGetTypeProc)(AVAnnotHandler annotHandler);

/**
	Currently unused. 
	@param annotHandler IN/OUT The annotation handler. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerNotifyDestroyProc)(AVAnnotHandler annotHandler);

/**
	Deprecated in Acrobat 6.0. Use AVAnnotHandlerDoPropertiesExProc(). 
	
	<p>(Optional) A callback for AVAnnotHandler. It displays whatever 
	user interface it wishes to allow a user to change an annotation's 
	properties. Set it to <code>NULL</code> if the annotation type has no 
	user-specified properties. </p>

	<p>It is called when the user selects the Properties item from 
	the Edit menu while an annotation of this type is selected. 
	If <code>NULL</code>, the Properties menu item is dimmed when a corresponding 
	object is selected. </p>
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose properties are set. 
	@param doc The document containing the annotation.
	@see AVAnnotHandlerDoPropertiesExProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerDoPropertiesProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVDoc doc);

/**
	Deprecated in Acrobat 6.0. Use AVAnnotHandlerDoKeyDownExProc(). 
	
	<p>(Optional) A callback for AVAnnotHandler. It is called to 
	handle key presses in the annotation. If <code>NULL</code>, it is as 
	if the callback returned <code>false</code>. </p>

	<p>It is called when there is a key-down event and the annotation 
	is selected, and the active tool does not want the event. </p>
	@param annotHandler The handler responsible for this annotation. 	
	@param anAnnot The annotation in which the key press occurred. 
	@param key The key that was pressed. 
	@param flags Indicates which modifier keys are pressed. 
	It must be an <code>OR</code> of the Modifier Keys values.
	@return <code>true</code> if the callback handled the key press, <code>false</code> otherwise. 
	@see AVAnnotHandlerDoKeyDownExProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerDoKeyDownProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVKeyCode key, AVFlagBits16 flags);

/**
	Deprecated in Acrobat 6.0. Use AVAnnotHandlerGetLayerExProc(). 
	
	<p>A callback for AVAnnotHandler. It returns the annotation's 
	layer. The layer need not be a constant. For example, the 
	Acrobat viewer's built-in text annotations have a different 
	layer depending on whether they are opened or closed. This 
	ensures that a closed text annotation never appears on top 
	of an open text annotation. </p>
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose layer is returned.
	@return The annotation's layer. 
	@see AVAnnotHandlerGetLayerExProc 
*/
typedef ACCBPROTO1 ASFixed (ACCBPROTO2 *AVAnnotHandlerGetLayerProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot);

/**
	(Optional) A callback for AVAnnotHandler. It is called whenever 
	the cursor moves over an annotation handled by this annotation 
	handler. 
	@param annotHandler IN/OUT The annotation handler responsible 
	for this annotation. 
	@param anAnnot IN/OUT The annotation. 
	@param pageView IN/OUT The AVPageView in which the annotation 
	is located. 
	@see AVAnnotHandlerCursorExitProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerCursorEnterProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);

/**
	(Optional) A callback for AVAnnotHandler. It is called whenever 
	the cursor moves off an annotation handled by this annotation 
	handler. 
	@param annotHandler IN/OUT The annotation handler responsible 
	for this annotation. 
	@param anAnnot IN/OUT The annotation from which the cursor is exiting. 	
	@param pageView IN/OUT The AVPageView in which the annotation 
	is located. 
	@see AVAnnotHandlerCursorEnterProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerCursorExitProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);

/**
	(Optional) A callback for AVAnnotHandler. It is called upon to copy 
	an annotation, possibly to another document. Annotation 
	handlers should provide this callback to allow for copying 
	their annotations. It is called by AVDocCopyAnnot(). 
	@param annotHandler The annotation handler responsible 
	for this annotation. 
	@param fromDoc The document whose annotation is copied. 	
	@param anAnnot The annotation to copy. 
	@param toDoc The document to which the annotation is copied.
	@return The newly created PDAnnot copy. 
	@see AVDocCopyAnnot 
*/
typedef ACCBPROTO1 PDAnnot (ACCBPROTO2 *AVAnnotHandlerCopyProc)(AVAnnotHandler annotHandler, AVDoc fromDoc, PDAnnot anAnnot, AVDoc toDoc);

/* Acrobat 4.0 additions. */

/**
	(Optional) A callback for AVAnnotHandler. It gets information 
	associated with an annotation. 

	<p>To effectively use a PDAnnotHandler associated with an annotation, 
	its AVAnnotHandler must have its AVAnnotHandlerGetInfoProc() 
	and AVAnnotHandlerDeleteInfoProc() callbacks defined. </p>
	@param avanh IN/OUT The annotation handler responsible for this 
	annotation. 
	@return Information associated with the annotation. 
	@see AVAnnotHandlerDeleteInfoProc 
	@see AVAppRegisterAnnotHandler 
*/
typedef ACCBPROTO1 AVAnnotHandlerInfo (ACCBPROTO2 *AVAnnotHandlerGetInfoProc)(AVAnnotHandler avanh);

/**
	(Optional) A callback for AVAnnotHandler. It deletes information 
	associated with an annotation. 

	<p>To effectively use a PDAnnotHandler associated with an annotation, 
	its AVAnnotHandler must have its AVAnnotHandlerGetInfoProc() 
	and AVAnnotHandlerDeleteInfoProc() callbacks defined. </p>
	@param avanh IN/OUT The annotation handler responsible for this 
	annotation. 
	@param info IN/OUT Information associated with the annotation. 
	@see AVAnnotHandlerGetInfoProc 
	@see PDAnnotHandlerDeleteAnnotInfoProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerDeleteInfoProc)(AVAnnotHandler avanh, AVAnnotHandlerInfo info);

/* Acrobat 5.0 additions */

/**
	Called to determine if this annotation can perform the specified 
	operation. 
	@param annotHandler IN/OUT The annotation handler responsible 
	for this annotation. 
	@param annot IN/OUT The annotation. 
	@param pageView IN/OUT The AVPageView in which the annotation 
	is located. 
	@param annotOp IN/OUT The operation to be performed. 
	@param opData IN/OUT The data associated with the operation. 
	@return <code>true</code> if the operation can be performed, <code>false</code> otherwise. 
	@see AVAnnotHandlerPerformOpProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerCanPerformOpProc)(
	AVAnnotHandler annotHandler,
	PDAnnot annot,
	AVPageView pageView,
	AVAnnotOp annotOp,
	AVAnnotOpData opData);

/**
	Called to initiate the operation. 
	@param annotHandler IN/OUT The annotation handler responsible 
	for this annotation. 
	@param annot IN/OUT The annotation. 
	@param pageView IN/OUT The AVPageView in which the annotation 
	is located. 
	@param annotOp IN/OUT The operation to be performed. 
	@param opData IN/OUT The data associated with the operation. 
	@return <code>true</code> if the operation is performed, <code>false</code> otherwise. 
	@see AVAnnotHandlerCanPerformOpProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerPerformOpProc)(
	AVAnnotHandler annotHandler,
	PDAnnot annot,
	AVPageView pageView,
	AVAnnotOp annotOp,
	AVAnnotOpData opData);

/**
	Called for each keystroke received when an annotation has 
	focus. 
	@param annotHandler The annotation handler responsible 
	for this annotation. 
	@param annot The annotation. 
	@param pageView The AVPageView in which the annotation 
	is located. 
	@param key The operation to be performed. 
	@param flags Indicates which modifier keys are pressed. 
	See Modifier Keys.
	@return <code>true</code> if the callback handled the keystroke, <code>false</code> otherwise. 
	@see AVAnnotHandlerDoKeyDownProc 

	@note The <code>key</code> and <code>flags</code> numeric types have changed in Acrobat 
	6.0. This supersedes AVAnnotHandlerDoKeyDownProc(). 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerDoKeyDownExProc)(
	AVAnnotHandler annotHandler,
	PDAnnot annot,
	AVPageView pageView,
	AVKeyCode key,
	AVFlagBits16 flags);

/**
	A callback for AVAnnotHandler. It returns the flags value 
	for the annotation on the screen. 
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose flags value is returned.
	@return The flags value. 
	@see AVAnnotHandlerGetAppearanceProc 
*/
typedef ACCBPROTO1 AVFlagBits32 (ACCBPROTO2 *AVAnnotHandlerGetFlagsProc)(
	AVAnnotHandler annotHandler, 
	PDAnnot anAnnot);

/* Acrobat 6.0 additions */

/* Fill in the apprObj with a CosObj representing a Form field and
   return 'true' and the viewer will position and draw the appearance
   for you.

   On entry, *flags will be set to reflect the annot's
   NoZoom and NoRotate bits. You can modify those bits and they will take
   effect when the appearance is drawn e.g. if you clear the NoZoom bit
   the appearance will be drawn as if the original annot did not have the
   NoZoom bit set.

   You can also OR in any combination of the following bits;

   DrawNow - indicates that you want you do not want the appearance to
   be drawn at intervals.

   Smooth - indicates that the appearance should be smoothed
   (anti-aliased) when drawn.

   Selected - indicates the appareance should be drawn with
   a selection visual around it. If you set this flag you should
   call AVAppGetAnnotAppearancePadding() and pad the annotation's
   view bounding box by that many pixels on all sides. This will
   provide space for the selection visual.

   Return 'false' and your Draw or DrawEx callback will be exercised
   to draw the annotation instead.
*/
#define kAVAppearanceDrawNow	0x01
#define kAVAppearanceNoZoom		0x02
#define kAVAppearanceNoRotate	0x04
#define kAVAppearanceSmooth		0x08
#define kAVAppearanceSelected	0x10
/**
	A callback for AVAnnotHandler. It fills in a CosObj representing 
	a Form field. Upon return, the annotation appearance is 
	drawn according to the returned flag values 

	<p>Appearance drawing is new in Acrobat 6.0. If the handler 
	implements this method and it returns <code>true</code>, the new drawing 
	style is used. If this function returns <code>false</code>, the viewer 
	calls the drawing procedure to draw the annotation appearance. 
	See AVAnnotHandler. </p>

	<p>The handler must not destroy or modify the appearance object 
	while it is being drawn. It can do so only after the EndAppearanceDrawing() 
	or CancelAppearanceDrawing() callback is exercised.</p> 
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param annot The annotation whose appearance is drawn. 
	@param flags A pointer to an <code>OR</code> of the AVAnnot Appearance 
	Flags. On entry, Acrobat modifies the flags to reflect the 
	annotation's current NoZoom and NoRotate bits. The method 
	can modify these to change the viewer's drawing behavior 
	for this annotation. The modifications take effect when 
	the appearance is drawn, for example, if the callback clears 
	the NoZoom bit, the appearance is drawn as if the original 
	annotation did not have that bit set. 
	@param pageView The page view in which the annotation 
	is drawn. 
	@param apprObj (Filled by the method) A CosObj representing 
	a Form field. 
	@return <code>true</code> to tell the viewer to position and draw the annotation 
	appearance, <code>false</code> to call the DrawEx() or Draw() procedure. 
	
	@see AVAnnotHandlerAppearanceDrawingProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerGetAppearanceProc)(
	AVAnnotHandler annotHandler,
	PDAnnot annot, ASUns32 *flags,
	AVPageView pageView,
	CosObj *apprObj);


/**
	A callback for AVAnnotHandler that draws the appearance of 
	the annotation for the given page view. Use this prototype 
	for three callbacks: BeginAppearanceDrawing(), FinishAppearanceDrawing(), 
	and CancelAppearanceDrawing(). 

	<p>If the viewer must abandon the drawing of the appearance, 
	it calls the CancelAppearanceDrawing() callback. If the viewer 
	succeeds in drawing the appearance, it calls the FinishAppearanceDrawing() 
	callback. In either case, the handler can destroy the appearance 
	object. See AVAnnotHandler. </p>

	<p>If the annotation sets the <code>kAVAppearanceSelected</code> flag,
	the viewer will draw a selection visual around the appearance object.
	To make room for the selection visual, the annotation handler should
	call AVAppGetAnnotAppearancePadding() and expand the annotation's view
	bounding box by that number of pixels, to avoid having the selection
	visual clipped.</p>

	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param annot The annotation whose appearance is drawn. 
	@param pageView The page view containing the annotation. 
	@param annotRect A pointer to a rectangle in the page 
	view's device space that contains the currently drawn appearance. 
	The procedure must not modify this object. 
	@param updateRect A pointer to a rectangle in the page 
	view's device space that contains the newly drawn appearance. 
	The procedure must not modify this object. As an optimization, 
	the handler can avoid drawing anything outside this rectangle, 
	which the viewer will clip.
	@see AVAnnotHandlerGetAppearanceProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerAppearanceDrawingProc)(
	AVAnnotHandler annotHandler,
	PDAnnot annot,
	AVPageView pageView,
	const AVDevRect* annotRect,
	const AVDevRect* updateRect);

/**
	(Optional) A callback for AVAnnotHandler. It displays whatever 
	user interface it wishes to allow a user to change an annotation's 
	properties. Set it to <code>NULL</code> if the annotation type has no 
	user-specified properties. 

	<p>It is called when the user selects the Properties item from 
	the Edit menu while an annotation of this type is selected. 
	If <code>NULL</code>, the Properties menu item is dimmed when a corresponding 
	object is selected. </p>
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose properties are set. 
	@param pageView The page view containing the annotation.
	@see AVAnnotHandlerDoPropertiesProc 

	@note Supersedes AVAnnotHandlerDoPropertiesProc() in Acrobat 
	6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVAnnotHandlerDoPropertiesExProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);

/**
	A callback for AVAnnotHandler. It returns the annotation's 
	layer. The layer need not be a constant. For example, the 
	Acrobat viewer's built-in text annotations have a different 
	layer depending on whether they are opened or closed. This 
	ensures that a closed text annotation never appears on top 
	of an open text annotation. 
	
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose layer is returned. 
	@param pageView The page view containing the annotation.
	@return The annotation's layer. 
	@see AVAnnotHandlerGetLayerProc 

	@note Introduced in Acrobat 6.0. Supersedes AVAnnotHandlerGetLayerProc(). 
*/
typedef ACCBPROTO1 ASFixed (ACCBPROTO2 *AVAnnotHandlerGetLayerExProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView);


/**
	Parameters that describe where and how a mouse click occurred, 
	for the use of click-handling callback procedures. 
	@see AVAnnotHandlerDoClickExProc 
*/
typedef struct _t_AVClickParams
{
	/** The size of this structure. */
	ASSize_t size;
	/** The x-coordinate of the mouse click. */
	AVDevCoord xHit;
	/** The y-coordinate of the mouse click. */
	AVDevCoord yHit;
	/** Indicates which modifier keys are pressed. It must be an <code>OR</code> of the Modifier Keys values. */
	AVFlagBits16 flags;
	/** <code>1</code> if this is a single click, <code>2</code> if this is a double click, <code>3</code> if this is a triple click. */
	AVTCount clickNo;
	/** The tool type that received the click event.*/
	ASAtom toolType;
} AVClickParamsRec, *AVClickParams;


/**
	Parameters that describe where and how a cursor event occurred, 
	for the use of cursor handling callback procedures. 
	@see AVAnnotHandlerAdjustCursorExProc 
*/
typedef struct _t_AVAdjustCursorParams
{
	/** The size of this structure. */
	ASSize_t size;
	/** The x-coordinate of the cursor. */
	AVDevCoord xHit;
	/** The y-coordinate of the cursor. */
	AVDevCoord yHit;
	/** The tool type that received the cursor event */
	ASAtom toolType;
} AVAdjustCursorParamsRec, *AVAdjustCursorParams;

/** (Optional) A callback for AVAnnotHandler. It handles both left and right mouse button
	clicks within the annotation. If <code>NULL</code>, the annotation behaves as if the callback returned
	<code>false</code>.
	@param annotHandler IN/OUT The annotation handler responsible for this annotation.
	@param hitAnnot IN/OUT The annotation in which the mouse was clicked.
	@param pageView IN/OUT The AVPageView in which the annotation is located.
	@param clickParams IN/OUT The parameters for the click position and properties.
	@return <code>true</code> if the callback handled the mouse click, <code>false</code> if it did not. If the callback does not
	handle the click, it is passed to any annotation at the same location in lower layers.
	@see AVAnnotHandlerDoClickProc
	@note Introduced in Acrobat 6.0. Supersedes AVAnnotHandlerDoClickProc().
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerDoClickExProc)(AVAnnotHandler annotHandler, PDAnnot hitAnnot,
                    AVPageView pageView,
					AVClickParams clickParams);
/** (Optional) A callback for AVAnnotHandler. It controls the cursor shape when the cursor is
	within the annotation. If <code>NULL</code>, the annotation behaves as if the AdjustCursor() callback
	returned <code>false</code>.
	@param annotHandler The annotation handler responsible for this annotation.
	@param anAnnot The annotation containing the cursor.
	@param pageView The AVPageView in which the annotation is located.
	@param params The parameters structure containing the cursor's current x- and y-coordinates.
	@return <code>true</code> if the callback handled the adjust cursor event, <code>false</code> otherwise. The callback would
	return <code>false</code>, for example, if the annotation is irregularly shaped and the cursor is not
	currently over the real annotation even though it is within the rectangular bounding box
	that the Acrobat viewer uses to specify annotations.
	@see AVAnnotHandlerAdjustCursorProc
	@note Introduced in Acrobat 6.0. Supersedes AVAnnotHandlerAdjustCursorProc().
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerAdjustCursorExProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot,
  					AVPageView pageView, AVAdjustCursorParams params);

/* Acrobat 7.0 additions */

/** The type of accessibility string to be obtained */
enum {
	/** The name and brief description. */
	kAVAnnotAccName,

	/** The content (or content description). */
	kAVAnnotAccValue,

	/** The description of the default action. */
	kAVAnnotAccDefaultAction
};
typedef ASEnum8 AVAnnotAccStrType;

/**
	A callback for AVAnnotHandler.  It gets the accessibility string 
	associated with an annotation. 
	@param annotHandler The annotation handler responsible for the annotation.
	@param anAnnot The annotation whose accessibility string is returned.
	@param pageNum The page number on which the annotation is drawn.
	@param strType The type of accessibility string.
	@param accString The accessibility string.
	@return <code>true</code> if the new annotation handler has set 
	<code>accString</code> successfully, <code>false</code> otherwise. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerGetAccessibilityStringProc)(AVAnnotHandler annotHandler, 
					PDAnnot anAnnot, PDPageNumber pageNum, AVAnnotAccStrType strType, ASText accString);


typedef enum {
	kAVTabOrderFirst,
	kAVTabOrderLast,
	kAVTabOrderNext,
	kAVTabOrderPrev
} AVPageViewTabOrder;

/**
	A callback for AVAnnotHandler. It allows the annotation 
	handler to determine which annot is next in the tab order.
	@param annotHandler The annotation handler. 
	@param anAnnot Annotation to direct tab order. 
	@param pageView The AVPageView in which the annotation 
	is located.
	@param tabOrder The type of tab order to follow.
	@param tabToAnnot The annot to tab to.
	@param tabToPageNo Indicates the page number to tab to.
	@return <code>true</code> if the new annotation handler has set
	the annot to tab to, <code>false</code> otherwise. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerGetAnnotInTabOrderProc)(AVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView, 
						AVPageViewTabOrder tabOrder, PDAnnot * tabToAnnot, ASInt32 * tabToPageNo );       

/* Acrobat 8.0 additions */

/**
	A callback for AVAnnotHandler. It returns information about
	auxiliary icons for the annotation on the screen. 
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose flags value is returned.
	@param pageView The page view associated with the annotation.
	@return The number of auxiliary icons associated with the annotation.
	@see AVAnnotHandlerGetAuxIconsProc
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVAnnotHandlerGetAuxIconCountProc)(
	AVAnnotHandler annotHandler, 
	PDAnnot anAnnot,
	AVPageView pageView);

/**
	A callback for AVAnnotHandler. It returns information about
	auxiliary icons for the annotation on the screen. 
	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param anAnnot The annotation whose flags value is returned.
	@param pageView The pageview associated with the annotation.
	@return <code>NULL</code> or an AS allocated array of AVIconBundle6 objects followed
	by at least one <code>NULL</code> pointer (calling GetAuxIconCount() is
	therefore not strictly necessary).
	@see AVAnnotHandlerGetAuxIconCountProc
*/
typedef ACCBPROTO1 AVIconBundle6 *(ACCBPROTO2 *AVAnnotHandlerGetAuxIconsProc)(
	AVAnnotHandler annotHandler, 
	PDAnnot anAnnot,
	AVPageView pageView);

#if (ACRO_SDK_LEVEL >= 0x00060000)
/**
*/
typedef struct _t_AVAnnotAppearanceData {
	/** Set by the viewer to the size of the structure. The
	    annotation handler can query this to determine if a
		field is in the structure and can be set.*/
	ASSize_t size;
	/** The annotation handler must provide an appearance object. */
	CosObj appearanceObject;
	/** The annotation handler can optionally provide a separate
		appearance for drawing the selection visual. The selection
		visual will surround the shape of this object. If no selection
		object is provided, <code>appearanceObject</code> will be used to draw
		the selection visual. */
	CosObj selectedShapeAppearanceObj;
} AVAnnotAppearanceDataRec;

/**
	A callback for AVAnnotHandler. It fills in a structure representing 
	an annotation's appearance. Upon return, the annotation appearance is 
	drawn according to the returned flag values 

	<p>If this callback is present, it will be called and the
	<code>GetAppearance()</code> callback will not be called.</p>

	<p>This callback works identically to the <code>GetAppearance()</code>
	callback, but allows the annotation handler to provide additional
	information. If the <code>kAVAppearanceSelected</code> flag is set,
	this callback can optionally provide a separate appearance object
	to be used to draw the selection marks around the annotation.</p>

	@param annotHandler The annotation handler responsible 
	for the annotation. 
	@param annot The annotation whose appearance is drawn. 
	@param flags A pointer to an <code>OR</code> of the AVAnnot Appearance 
	Flags. On entry, Acrobat modifies the flags to reflect the 
	annotation's current <code>NoZoom</code> and <code>NoRotate</code> bits. The method 
	can modify these to change the viewer's drawing behavior 
	for this annotation. The modifications take effect when 
	the appearance is drawn, for example, if the callback clears 
	the <code>NoZoom</code> bit, the appearance is drawn as if the original 
	annotation did not have that bit set. 
	@param pageView The page view in which the annotation 
	is drawn. 
	@param appearanceData (Filled by the method) A structure the annotation
	handler can fill to provide appearance information to the viewer.

	@return <code>true</code> for the viewer to position and draw the annotation 
	appearance, <code>false</code> to call the DrawEx() or Draw() procedure. 
	
	@see AVAnnotHandlerAppearanceDrawingProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAnnotHandlerGetAppearanceExProc)(
	AVAnnotHandler annotHandler,
	PDAnnot annot,
	ASUns32 *flags,
	AVPageView pageView,
	AVAnnotAppearanceDataRec* appearanceData);
#endif

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A data structure containing callbacks that implement an annotation 
	handler. The callbacks implement the annotation handler 
	functions. For example, they can draw the annotation or highlight the 
	annotation when it is selected. The data specifies properties 
	of the annotation (for example, text selection behavior). 

	<p>Appearance drawing is new in Acrobat 6.0. If the handler 
	implements the GetAppearance() callback, the new drawing style 
	is used. If the GetAppearance() callback returns <code>false</code> or 
	is not implemented, the viewer calls the drawing procedure 
	(DrawEx() if present, Draw() otherwise) to draw the annotation 
	using Acrobat 5.0-style drawing.</p> 

	<p>For the new style of appearance drawing, the viewer calls 
	the handler's BeginAppearanceDrawing() callback, then draws 
	the appearance object. If the drawing operation completes 
	without errors, it call the the handler's BeginAppearanceDrawing() 
	callback; if an error occurs, or the operation is canceled, 
	it calls the CancelAppearanceDrawing() callback. This can 
	happen if, for example, the user switches to another page 
	before the drawing is completed.</p> 

	<p>The handler must not destroy or modify the appearance object 
	while it is being drawn. It can do so only after the EndAppearanceDrawing() 
	or CancelAppearanceDrawing() callback has executed. </p>
	@see AVAnnotHandlerEnumProc 
	@see PDAnnotHandlerDeleteAnnotInfoProc 
	@see PDAnnotHandlerGetAnnotInfoFlagsProc 
	@see PDAnnotHandlerGetAnnotInfoProc 
	@see PDAnnotHandlerGetTypeProc 
	@see AVAppRegisterAnnotHandler 
	@see AVAppGetAnnotHandlerByName 
	@see AVDocCopyAnnot 

	@note Types of numeric values in callbacks have changed 
	in Acrobat 6.0. 
*/
typedef struct _t_AVAnnotHandler 
{

	/** The size of the data structure. It must be set to <code>sizeof( AVAnnotHandlerRec)</code>. */
	ASSize_t 	size;

	/** A collection of flags that affect the annotation's behavior. The flags may be OR-ed together. 

		<p>Permissible flags:</p>
		<TABLE rules="all" cellspacing="1">
		<TR><TH>Flag</TH><TH>Description</TH></TR>
		<TR><TD>ANNOT_CLIP_TEXT_SELECTION</TD><TD>If this flag is set, text selection in the main document 
		never selects text within the annotation (that is, the annotation behaves like the Acrobat viewer's 
		text annotation). If this flag is not set, text selection in the main document can select text within 
		the annotation (that is, the annotation behaves like the Acrobat viewer's link annotation).</TD></TR>
		<TR><TD>ANNOT_WANTS_SHIFT_KEY</TD><TD>This flag is set to prevent the standard shift-key ignores 
		annotation's behavior.</TD></TR>
		</TABLE>
	
		@note These flags are not the ones used in PDAnnotArray. 
	*/
	AVFlagBits32 flags;


	/** Deprecated */
	oldAVAnnotHandlerDoClickProc oldDoClick; 

	/** Deprecated */
	oldAVAnnotHandlerAdjustCursorProc oldAdjustCursor; 

	/** Deprecated */
	oldAVAnnotHandlerPtInAnnotViewBBoxProc oldPtInAnnotViewBBox; 

	/** Deprecated */
	oldAVAnnotHandlerGetAnnotViewBBoxProc oldGetAnnotViewBBox;  

	/**  */
	AVAnnotHandlerNotifyAnnotRemovedFromSelectionProc NotifyAnnotRemovedFromSelection;

	/** */
	AVAnnotHandlerNotifyAnnotAddedToSelectionProc NotifyAnnotAddedToSelection;

	/** Deprecated */
	AVAnnotHandlerDrawProc Draw; 

	/** */
	AVAnnotHandlerNewProc New;

	/** */
	AVAnnotHandlerGetTypeProc GetType;

	/** */
	AVAnnotHandlerNotifyDestroyProc NotifyDestroy;

	/** */
	AVAnnotHandlerDoPropertiesProc DoProperties;

	/** */
	AVAnnotHandlerDoKeyDownProc DoKeyDown;

	/** */
	AVAnnotHandlerGetLayerProc GetLayer;

	/** */
	AVAnnotHandlerCursorEnterProc CursorEnter;

	/** */
	AVAnnotHandlerCursorExitProc CursorExit;

	/** */
	AVAnnotHandlerCopyProc Copy;

	/** Deprecated */
	oldAVAnnotHandlerDoClickProc oldDoRightClick; 

	/** */
	AVAnnotHandlerGetInfoProc GetInfo;

	/** */
	AVAnnotHandlerDeleteInfoProc DeleteInfo;

	/** */
	AVAnnotHandlerCanPerformOpProc CanPerformOp;

	/** */
	AVAnnotHandlerPerformOpProc PerformOp;

	/** */
	AVAnnotHandlerDoKeyDownExProc DoKeyDownEx;

	/** Deprecated */
	oldAVAnnotHandlerDrawExProc oldDrawEx; 

	/** */
	AVAnnotHandlerGetFlagsProc GetFlags;

	/** */
	AVAnnotHandlerDoClickProc DoClick;

	/** */
	AVAnnotHandlerAdjustCursorProc AdjustCursor;

	/** */
	AVAnnotHandlerPtInAnnotViewBBoxProc PtInAnnotViewBBox;

	/** */
	AVAnnotHandlerGetAnnotViewBBoxProc GetAnnotViewBBox; 

	/** */
	AVAnnotHandlerDoClickProc DoRightClick;

	/** */
	AVAnnotHandlerDrawExProc DrawEx; 

	/** */
	AVAnnotHandlerGetAppearanceProc GetAppearance;

	/** */
	AVAnnotHandlerAppearanceDrawingProc BeginAppearanceDrawing;

	/** */
	AVAnnotHandlerAppearanceDrawingProc FinishAppearanceDrawing;

	/** */
	AVAnnotHandlerAppearanceDrawingProc CancelAppearanceDrawing;

	/** */
	AVAnnotHandlerDoPropertiesExProc DoPropertiesEx;

	/** */
	AVAnnotHandlerGetLayerExProc GetLayerEx;

	/** */
	AVAnnotHandlerDoClickExProc DoClickEx;

	/** */
	AVAnnotHandlerDoClickExProc DoRightClickEx;

	/** */
	AVAnnotHandlerAdjustCursorExProc AdjustCursorEx;
	
	/** */
	AVAnnotHandlerGetAccessibilityStringProc GetAccessibilityString;

	/** */
	AVAnnotHandlerGetAnnotInTabOrderProc GetAnnotInTabOrder;

	/** */
	AVAnnotHandlerGetAuxIconCountProc GetAuxIconCount;

	/** */
	AVAnnotHandlerGetAuxIconsProc GetAuxIcons;

	/** */
	AVAnnotHandlerGetAppearanceExProc GetAppearanceEx;
} AVAnnotHandlerRec;
#endif /* (ACRO_SDK_LEVEL >= 0x00060000) */


/**
	A callback that is called periodically when the Acrobat viewer 
	is otherwise idle. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVAppRegisterIdleProc(). 
	@see AVAppRegisterIdleProc 
	@see AVAppUnregisterIdleProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVIdleProc)(void *clientData);


/************************************************************************************\
|*																					*|
|*									AVSys											*|
|*																					*|
\************************************************************************************/

/**
	A data structure representing the cursor.  
	@see AVSysGetCursor 
	@see AVSysGetStandardCursor 
	@see AVSysSetCursor 
	@see cursorID for a list of already defined cursor shapes.
*/
typedef struct _t_AVCursor *AVCursor;


/** @ingroup cursorID */
#define ARROW_CURSOR			   	0

/** @ingroup cursorID */
#define IBEAM_CURSOR 			   	1

/** @ingroup cursorID */
#define GROWLEFTRIGHT_CURSOR		33
	
/** @ingroup cursorID */
#define HIGHLIGHT_CURSOR			34
	
/** @ingroup cursorID */
#define GROWTOPBOTTOM_CURSOR		35
	
/** @ingroup cursorID */
#define CROPTOOL_CURSOR				36
	
/** @ingroup cursorID */
#define CROPTOOL_SCISSORS_CURSOR	37

	/** @ingroup cursorID */
#define CROSSHAIR_CURSOR 			1000

/** @ingroup cursorID */
#define BOX_IBEAM_CURSOR 			1001

/** @ingroup cursorID */
#define HAND_CURSOR 	 			1002

/** @ingroup cursorID */
#define ZOOM_IN_CURSOR	 			1003

/** @ingroup cursorID */
#define ZOOM_OUT_CURSOR	 			1004

/** @ingroup cursorID */
#define ZOOM_MAX_CURSOR	 			1005

/** @ingroup cursorID */
#define ZOOM_DRAG_CURSOR	 		1006

/** @ingroup cursorID */
#define GROW_CURSOR		 			1008

/** @ingroup cursorID */
#define BAR_IBEAM_CURSOR 			1011

/** @ingroup cursorID */
#define FIST_CURSOR		 			1012

/** @ingroup cursorID */
#define LINK_CURSOR		 			1100

/** @ingroup cursorID */
#define MOVEPAGE_CURSOR	 			1111

/** @ingroup cursorID */
#define WAIT_CURSOR		 			1112

/** @ingroup cursorID */
#define COPYPAGE_CURSOR	 			1113

/** @ingroup cursorID */
#define MOVEPAGES_CURSOR 			1114

/** @ingroup cursorID */
#define COPYPAGES_CURSOR 			1115

/** @ingroup cursorID */
#define REPLACEPAGE_CURSOR			1116

/** @ingroup cursorID */
#define REPLACEPAGES_CURSOR			1117

/** @ingroup cursorID */
#define NOP_CURSOR 					1118

/** @ingroup cursorID */
#define THREAD_CURSOR 				1119

/** @ingroup cursorID */
#define WORDFINDER_CURSOR 			1201

/** @ingroup cursorID */
#define HAND_THREAD_CURSOR			1202

/** @ingroup cursorID */
#define HIDDEN_CURSOR 				1203

/** @ingroup cursorID */
#define GROWTOPLEFT_CURSOR 			1204

/** @ingroup cursorID */
#define GROWBOTTOMLEFT_CURSOR 		1205

/** @ingroup cursorID */
#define MOVE_CURSOR 				1206

/** @ingroup cursorID */
#define HAND_THREAD_UP_CURSOR 		1207

/** @ingroup cursorID */
#define HAND_THREAD_END_CURSOR 		1208

/** @ingroup cursorID */
#define HAND_THREAD_UP_END_CURSOR 	1209

/** @ingroup cursorID */
#define HAND_THREAD_BEGIN_CURSOR 	1210

/** @ingroup cursorID */
#define THREAD_CONNECT_CURSOR		1211

/** @ingroup cursorID */
#define THREAD_END_CURSOR 			1212

/** @ingroup cursorID */
#define VERT_IBEAM_CURSOR 			1213

/** @ingroup cursorID */
#define DRAGLEFTRIGHT_CURSOR		1214

/** @ingroup cursorID */
#define DRAGUPDOWN_CURSOR			1215

/** @ingroup cursorID */
#define VERTBEAMNOBAR_CURSOR		1216

/** @ingroup cursorID */
#define GROW_4WAY_CURSOR			1217

/** @ingroup cursorID */
#define MEASURE_CURSOR				1300

/** @ingroup cursorID */
#define MEASURECLOSE_CURSOR			1301

/** @ingroup cursorID */
#define LOUPE_CURSOR				1302

/** @ingroup cursorID */
#define SELECTOBJECT_CURSOR			1303

/** @ingroup cursorID */
#define TABLE_CURSOR				1304

/** @ingroup cursorID */
#define TOUCHUPOBJ_CURSOR			1305 

/** @ingroup cursorID */
#define CROSSHAIR_ADD_CURSOR 		1306

/** @ingroup cursorID */
#define CROSSHAIR_SUBTRACT_CURSOR 	1307

/** @ingroup cursorID */
#define CROSSHAIR_3D_CURSOR 		1308

/** @ingroup cursorID */
#define MOVE_3D_CURSOR 				1309

/** @ingroup cursorID */
#define IBEAM_3D_CURSOR				1310

/** @ingroup cursorID */
#define NOTE_3D_CURSOR				1311

/** @ingroup cursorID */
#define SCALEALL_3D_CURSOR			1312

/** @ingroup cursorID */
#define TEXTMARQUEE_3D_CURSOR		1313

/** @ingroup cursorID */
#define NEXTPAGE_CURSOR				1314
/** @ingroup cursorID */
#define PREVPAGE_CURSOR				1315
/** @ingroup cursorID */
#define SCROLL_CURSOR				1316

/** @ingroup KeyStates */
#define AV_SHIFT		1

/** @ingroup KeyStates */
#define AV_CONTROL		2

/** @ingroup KeyStates */
#define AV_COMMAND		4

/** @ingroup KeyStates */
#define AV_OPTION		8

/** This value can mean right-Alt, right-Ctrl or Enter on enhanced keyboards. 
	@ingroup KeyStates
*/
#define AV_EXTENDED 	16 

/** This value means that the cursor is inverted, or the <i>eraser</i> side of a pen input device is being used. 
	@ingroup KeyStates
*/
#define AV_INVERTED 	32 

/** @ingroup KeyStates */
#define AV_SPACE		64

/** @ingroup KeyStates */
#define AV_CAPS			128

/** The pen is used as input device. 
	@ingroup KeyStates
*/
#define AV_PENINUSE		256 


/************************************************************************************\
|*																					*|
|*									AVTool											*|
|*																					*|
\************************************************************************************/

#if (ACRO_SDK_LEVEL >= 0x00060000)


/**
	A data structure for a tool. It contains callbacks that implement 
	the tool's functions (for example, handling mouse clicks 
	and controlling the cursor shape). 
	
	<p>It handles key presses and mouse clicks in the content region of an AVPageView.
	AVTool objects do not handle mouse clicks in other parts of the viewer's window, such as in
	the bookmark pane. At any time, there is one active tool.</p>
	@see AVAppGetActiveTool 
	@see AVAppSetActiveTool 
	@see AVAppGetDefaultTool 
	@see AVAppGetLastActiveTool 
	@see AVAppGetToolByName 
	@see AVAppRegisterTool 
	@see AVToolGetType 
	@see AVToolIsPersistent
*/
typedef struct _t_AVTool *AVTool;

/**
	(Optional) A callback for AVTool. This callback controls the 
	cursor shape when the tool is the active tool. 

	<p>If omitted, the cursor specified in the tool's <code>cursorID</code> 
	field is used. </p>
	@param tool IN/OUT The currently active tool. 
	@param pageView IN/OUT The page view in which the cursor is currently 
	located. 
	@param x IN/OUT The x-coordinate of the current cursor location. 
	@param y IN/OUT The y-coordinate of the current cursor location. 
	@return <code>true</code> if you handled the cursor shape (you do not allow 
	underlying layers to handle it), <code>false</code> if you did (you do allow underlying layers to handle it). 
	@see AVAppRegisterTool 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AdjustCursorProcType)(AVTool tool, AVPageView pageView, AVDevCoord x, AVDevCoord y);

/**
	A callback for AVTool. It handles mouse clicks when the tool 
	is active. For Mac OS, this handles button or option-button 
	mouse clicks. For Windows, this handles right or left button 
	mouse clicks. 
	@param tool The tool. 
	@param pageView The AVPageView in which the click occurred. 
	@param xHit The click's x-coordinate. 
	@param yHit The click's y-coordinate. 
	@param flags Modifier keys that were held down while clicking. 
	It must be an <code>OR</code> of the Modifier Keys values. 
	@param clickNo <code>1</code> if it is a single click, <code>2</code> if it is a double click, <code>3</code> 
	if it is a triple click.
	@return <code>true</code> if the callback handled the click, <code>false</code> if it did 
	not and the click should be passed to the next click handling 
	procedure. 
	@see DoKeyDownProcType 

	@note The numeric argument types have changed in Acrobat 6.0. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DoClickProcType)(AVTool tool, AVPageView pageView,
					AVDevCoord xHit, AVDevCoord yHit,
					AVFlagBits16 flags,
					AVTCount clickNo);


#endif /* (ACRO_SDK_LEVEL >= 0x00060000) */

/** A callback for AVTool. It is called when this tool has become the active tool. It is allowed to call
	AVAppGetActiveTool() from within this method or from DeactivateProcType(); it
	will return this tool object. Call AVAppGetLastActiveTool() to get the formerly active
	tool object (its DeactivateProcType() method will already have been called).
	@param tool IN/OUT The tool to activate. 
	@param persistent IN/OUT <code>true</code> if it should remain active through an
	arbitrary number of <i>operations</i> (whatever that means for a 
	particular tool) rather than performing a single action 
	(<i>one shot</i>) and then restoring the previously active tool, 
	<code>false</code> otherwise. 
	@see DeactivateProcType
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *ActivateProcType)(AVTool tool, ASBool persistent);

/**
	A callback for AVTool. It is called when the tool will no longer 
	be the active tool. 
	@param tool IN/OUT The tool to deactivate. 
	@see ActivateProcType 
	@see AVAppSetActiveTool 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DeactivateProcType)(AVTool tool);

/**
	A callback for AVTool. It handles key presses when the tool is 
	active. 
	@param tool IN/OUT The tool. 
	@param key IN/OUT The key that was pressed. 
	@param flags IN/OUT Modifier keys that were also pressed. It must 
	be an <code>OR</code> of the Modifier Keys values. 
	@return <code>true</code> if the callback handled the key press, <code>false</code> if it 
	did not and the key press should be passed to the key press handling procedure. 
	@see DoClickProcType 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *DoKeyDownProcType)(AVTool tool, AVKeyCode key, AVFlagBits16 flags);

/**
	A callback for AVTool. It returns the tool's name. 
	@param tool IN/OUT The tool. 
	@return The ASAtom corresponding to the tool's name. 
	@see AVAppGetToolByName 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *GetTypeProcType)(AVTool tool);

/**
	A callback for AVTool. It indicates whether the tool should 
	stay active after it has been used or is a one-shot 
	tool. 

	<p>The Acrobat viewer does not contain any code to enforce 
	a tool's request to be persistent; it is up to each tool 
	to be a good citizen. For example, if a tool is not persistent, 
	after that tool is used once it should get the previously 
	active tool (using AVAppGetLastActiveTool()) and check whether 
	that tool should be persistent (using AVToolIsPersistent()). 
	If so, set the active tool to that tool. If not, set the 
	active tool to the default tool (obtained using AVAppGetDefaultTool()). </p>
	@param tool The tool.
	@return <code>true</code> if the tool should be persistent, <code>false</code> otherwise. 
	@see AVToolIsPersistent 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *IsPersistentProcType)(AVTool tool);

/**
	A callback for AVTool. It is called when the tool leaves the page 
	view (when the cursor is moved out of the page view). 
	@param tool IN/OUT The tool. 
	@param pageView IN/OUT The AVPageView that the tool left. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DoLeaveProcType)(AVTool tool, AVPageView pageView);

/**
	A callback for AVTool. It gets the selection server associated 
	with the tool, if any. 
	@param tool IN/OUT The tool. 
	@param doc IN/OUT The active AVDoc. 
	@return The selection server associated with this tool. It returns 
	<code>NULL</code> if the tool has no selection server. 
*/
typedef ACCBPROTO1 AVDocSelectionServer (ACCBPROTO2 *GetSelectionServerProcType)(AVTool tool, AVDoc doc);

/**
	An AVToolRec callback. If provided, it is called at shutdown time 
	to allow the tool to free dynamic memory. 
	@param tool The tool to be destroyed.
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVToolDestroyProc)(AVTool tool);

/**
	A callback for AVToolRec. If provided, it is called when text describing 
	the tool needs to be displayed. 
	@param tool The tool.
	@return The text object. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVToolGetLabelProc)(AVTool tool, ASText label);

/**
	A callback for AVToolRec. If provided, it is called when a static 
	tool icon is needed. This icon should be similar to, but 
	not the same as the tool button icon for this tool. 
	@param tool The tool.
	@return The icon object. 
*/
typedef ACCBPROTO1 AVIcon (ACCBPROTO2 *AVToolGetLabelIconProc)(AVTool tool);

/**
	(Acrobat 10.0 and later) 
	A callback for AVToolRec. If provided, it is called when a tooltip 
	is needed. 
	@param tool The tool.
	@return The tooltip text object. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVToolGetToolTipProc)(AVTool tool, ASText tip);



/**
	(Acrobat 7.0 and later) Describes the direction of mouse wheel movement.
	
	@see HandleMouseWheelScroll 
*/
enum {

	/** */
	AVToolMouseWheelUp,

	/** */
	AVToolMouseWheelDown
};

typedef ASEnum16 AVToolMouseWheelDirection;

/**
	A callback for AVTool. Handles mouse wheel scroll events when 
	the tool is active. 

	@param tool			The tool. 
	@param pageView		The AVPageView in which the click occurred. 
	@param direction	The direction of the mouse wheel movement. 
	@param numLines		The number of lines moved. 
	@param flags		Modifier keys that were held down while wheeling. It must be an <code>OR</code> of the Modifier Keys values. 

	@return <code>true</code> if the callback handled the click, <code>false</code> if it did 
	not and the wheel should be passed to the next wheel handling 
	procedure. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *HandleMouseWheelScrollProc)(AVTool tool, AVPageView pageView, 
																   AVToolMouseWheelDirection direction, 
																   AVTCount numLines, AVFlagBits16 flags);


/* Concrete instantiation of a tool object. Tool implementations will
   usually "subclass" this by pass a ptr to struct with an AVToolRec as
   its first member to AVAppRegisterTool, cast as an AVTool.
*/

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A data structure for a tool. It contains callbacks that implement 
	the tool's functions (for example, handling mouse clicks 
	and controlling the cursor shape). 
	@see AVAppGetActiveTool 
	@see AVAppSetActiveTool 
	@see AVAppGetDefaultTool 
	@see AVAppGetLastActiveTool 
	@see AVAppGetToolByName 
	@see AVAppRegisterTool 
	@see AVToolGetType 
	@see AVToolIsPersistent
*/
typedef struct _t_AVTool 
{

	/** The size of the data structure. It must be set to <code>sizeof(AVToolRec)</code>. */
  ASSize_t size;
  

	/** This method is called when this tool has become the active tool. It
        is allowed to call AVAppGetActiveTool() from within this
        method or from Deactivate(); it will return this tool object. Call
        AVAppGetLastActiveTool() to get the formerly active tool object 
        (its Deactivate() method will already have been called).  

		<p>If <code>persistent</code> is <code>true</code> and has meaning for this tool,
        it means that the tool should remain active through an arbitrary number of <i>operations</i>
        (whatever that means for a particular tool), rather than
        performing a single action (as a <i>one shot</i>) and then restoring
        the previously active tool. If <code>persistent</code> is <code>false</code>, 
        the opposite is implied.</p>
	*/
  ActivateProcType Activate;

 	/** */
  DeactivateProcType Deactivate;

	/** Deprecated. Use DoClick(). */
  oldDoClickProcType oldDoClick; 

	/** Deprecated. Use AdjustCursor(). */
  oldAdjustCursorProcType oldAdjustCursor; 

	/** */
  DoKeyDownProcType DoKeyDown;

	/** */
  GetTypeProcType GetType;

	/** Returns <code>true</code> if the tool is persistent at this time (this may be <code>false</code>
       even though Active was called with <code>persistent = true</code>, or vice-versa).
       If it is <code>NULL</code>, AVToolIsPersistent() will return <code>true</code>.
	*/
  IsPersistentProcType IsPersistent;
 

  /** A default cursor, used if the tool does not have an AdjustCursorProcType() callback. 
	It is ignored if AdjustCursor() is non-<code>NULL</code>; if AdjustCursor() is <code>NULL</code>, the
    default AdjustCursor() implementation will set the cursor to the
    result of calling <code>AVSysGetStandardCursor(cursorId)</code> unless a
    hit annotation sets the cursor. The default AdjustCursor()
    is appropriate for most tool implementations. See the ZoomTool implementation for
    an example of a private AdjustCursor() implementation.
  */
  AVCursorID cursorID;

 	/** Returns <code>true</code> if the tool is enabled (<i>legal</i>).
		It is <i>legal</i> if the front-most document permits the tool's operation.
		It will only be called if there is a front-most document.
		If it is <code>NULL</code>, the tool is always enabled.
	*/
  AVComputeEnabledProc ComputeEnabled;

	/** User-supplied data to pass to the tool's AVComputeEnabledProc() callback each time it is called. */
  void *computeEnabledData;


	/** Deprecated. */
  oldDoClickProcType oldDoRightClick; 

	/** */
  DoLeaveProcType DoLeave;


	/** */
  GetSelectionServerProcType GetSelectionServer;

	/** */
  DoClickProcType DoClick;

	/** */
  AdjustCursorProcType AdjustCursor;

	/** */
  DoClickProcType DoRightClick;


	/** clientData - use to store pointer to private data or store your *this* pointer */
  void *clientData;

	/** */
  AVToolDestroyProc Destroy;

	/** obsolete */
  oldAVToolGetLabelProc oldGetLabel;

	/** */
  AVToolGetLabelIconProc GetLabelIcon;

	/** */
  HandleMouseWheelScrollProc HandleMouseWheel;

	/** Return a label for use in buttons or menus */
  AVToolGetLabelProc GetLabel;

    /** Return a tooltip for use in buttons or menus */
  AVToolGetToolTipProc GetToolTip;

} AVToolRec;

#endif /* (ACRO_SDK_LEVEL >= 0x00060000) */

/**
	A callback for AVAppEnumTools(). It is called once for each 
	tool. 
	@param tool IN/OUT The tool currently being enumerated. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVAppEnumTools(). 
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	@see AVAppEnumTools 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVToolEnumProc)(AVTool tool, void *clientData);


/************************************************************************************\
|*																					*|
|*									AVToolBar										*|
|*																					*|
\************************************************************************************/
#ifdef __cplusplus
class AVToolBarObj;
typedef AVToolBarObj *AVToolBar;
#else
typedef struct _t_AVToolBar *AVToolBar;
#endif

/************************************************************************************\
|*																					*|
|*								AVToolButton										*|
|*																					*|
\************************************************************************************/

/* bit-field values for toolbuttons */

/** 
	Indicates that the toolbar button is visible only in the viewer's toolbar.
 	@ingroup ToolButtonFlags
*/
#define TOOLBUTTON_INTERNAL 1

/** 
 	Indicates that the toolbar button is visible only in the toolbar of an external application 
 	(such as a web browser).
 	@ingroup ToolButtonFlags
*/
#define TOOLBUTTON_EXTERNAL 2

/**
	A button in the Acrobat viewer's toolbar. Like menu items, the procedure that executes
	when the button is clicked can be set by a plug-in. Although not required, there is
	generally a menu item corresponding to each button, allowing users to select a
	function using either the button or the menu item. Buttons are added to the toolbar by
	specifying which existing button they appear before or after.
	@see AVToolBarGetButtonByName
	@see AVToolButtonNew
	@see AVToolBarEnumButtons
	@see AVToolButtonDestroy
	@see AVToolButtonRemove
	@see AVToolBarEnumButtons
	@see AVToolButtonGetFlyout 
	@see AVToolButtonSetFlyout
	@see AVToolButtonGetIcon 
	@see AVToolButtonSetIcon
	@see AVToolButtonGetMenu 
	@see AVToolButtonSetMenu
	@see AVToolButtonIsEnabled 
	@see AVToolButtonIsMarked 
	@see AVToolButtonIsSeparator 
	@see AVToolButtonSetComputeEnabledProc
	@see AVToolButtonSetComputeMarkedProc
	@see AVToolButtonSetExecuteProc
	@see AVToolButtonSetExternal
	@see AVToolButtonSetHelpText
*/
#ifdef __cplusplus
class AVToolButtonObj;
typedef AVToolButtonObj *AVToolButton;
#else
typedef struct _t_AVToolButton *AVToolButton;
#endif

/**
	A structure used to describe how a tool button should be inserted into a given toolbar.
	@see AVToolArAddButtonEx
	@since PI_ACROVIEW_VERSION >= 0x00090000
*/
typedef struct _t_AVToolBarAddButtonParamsRec
{
	/** Set to <code>sizeof(AVToolBarAddButtonParamsRec)</code>. */
	ASSize_t size;

	/** Set to a reference button that you want your button to be inserted next to */
	AVToolButton neighborButton;
	/** Set to <code>true</code> to insert your button before (left of) the reference button */
	ASBool before;

	/** Set to <code>true</code> to insert your button as hidden by default */
	ASBool hiddenDefault;
} AVToolBarAddButtonParamsRec, *AVToolBarAddButtonParams;

/**
	A callback for AVToolBarEnumButtons(). It is called once for 
	each toolbar button. 
	@param button IN/OUT The toolbar button currently being enumerated. 
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVToolBarEnumButtons(). 
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	@see AVToolBarEnumButtons 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVToolButtonEnumProc)(AVToolButton button, void *clientData);


/**
	Constants that specify the layer in which a newly-created 
	AVWindow is to appear. 
	@see AVWindowNew 
	@see AVWindowNewFromPlatformThing 
*/

typedef ASInt32 AVWindowLayer;

/** @ingroup AVWindowLayerFlags */
#define AVWLunknown						0

/** A regular window, such as a document window. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLnonfloating					1	

/** A floating window, such as a palette. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLfloating					2		

/** A modal dialog box. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLmodal						3		

/** (New in Acrobat 5.0) A popup window without a caption, a one-pixel border and drop shadow. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLpopup						4		

/** (Internal use only) A toolbar window. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLtoolbar						5		

/** (Internal use only) A help window. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLhelp						6	

/** A window that occupies the same layer as popup menus, and has no title bar decorations. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLmenu						7

/** A top level window that has no user interface except a frame. 
	@ingroup AVWindowLayerFlags
*/
#define AVWLtopmost						8
/** The window is resizeable. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_RESIZEABLE		0x80000000	

/** The window has a close box. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_HASCLOSEBOX		0x40000000	

/** The window has a zoom box. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_HASZOOMBOX		0x20000000		

/** The window has a minimize box. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_HASMINIMIZEBOX	0x04000000		

/** The window has a drag bar. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_HASDRAGBAR		0x02000000	

/** The window has a small title bar. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_SMALLTITLEBAR		0x01000000	

/** <i>Auxiliary</i> windows pass unhandled menu commands to the frontmost document
	window.  For example, the Find dialog box is <i>auxiliary</i> since menu items such as Save and 
	Close should still be enabled.  A window that does not purport to operate on
	the topmost document window (for example, an "Establish Connection to Library of Congress"
	dialog box) would probably not be auxiliary.
  	@ingroup AVWindowFlags
*/
#define AVWIN_AUXILIARY			0x10000000

/**   	@ingroup AVWindowFlags
		AVWIN_WANTSKEY is deprecated and ignored.
*/
#define AVWIN_WANTSKEY			0x08000000

/** The window hides itself when focus is lost. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_TRANSIENT			0x00800000

/** The window sizes itself to fit its child views. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_FORMFIT			0x00400000

/** The default internal document window for the platform.
    It must be combined with <code>AVWLnonfloating</code>.
    This overrides <i>all</i> other flags. 
*/
#define AVWIN_INTERNAL_DOC		0x00200000

/** The window does not have decorations such as borders, captions or edges. 
  	@ingroup AVWindowFlags
*/
#define AVWIN_UNDECORATED		0x00100000

/** The window should have the PDF icon associated with it 
  	@ingroup AVWindowFlags
*/
#define AVWIN_PDFICON			0x00200000

/************************************************************************************\
|*																					*|
|*								 AVWindowHandler									*|
|*																					*|
\************************************************************************************/


#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A callback for AVWindowHandler. Mouse clicks in the AVWindow 
	are dispatched through this callback. 
	@param win The window in which the click occurred. 
	@param x The click's x-coordinate. 
	@param y The click's y-coordinate. 
	@param platformEvent A platform-specific event record. On Mac OS, it is 
	a pointer to an EventRecord. On the UNIX operating system it is an <code>eventPtr</code>.
	@see AVWindowKeyDownProc 

	@note The coordinate numeric types have changed in Acrobat 
	6.0. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowMouseDownProc)(AVWindow win, AVWindowCoord x, AVWindowCoord y, void *platformEvent);

/**
	A callback for AVWindowHandler. It is called whenever the window 
	needs to refresh some part of its interior. It should redraw 
	the contents of the specified rectangle. 
	@param win IN/OUT The window whose content is redrawn. 
	@param rect IN/OUT The region of <code>win</code> to redraw. 
	@see AVWindowDrawNow 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDrawProc)(AVWindow win, const AVWindowRect *rect);

/**
	A callback for AVWindowHandler. It is called when the window is 
	about to resize. 
	@param win IN/OUT The window to resize. 
	@param newFrame IN/OUT A rectangle specifying the size to which 
	the window will be resized. This callback may change the 
	new frame size. 
	@return <code>true</code> to permit the resizing, <code>false</code> to abort it. 
	@see AVWindowSetFrame 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVWindowWillBeResizedProc)(AVWindow win, AVScreenRect *newFrame);

/**
	A callback for AVWindowHandler. It is called periodically while 
	the cursor is over the AVWindow (if the window is active). 
	Use this to adjust the cursor's appearance. 
	@param win IN/OUT The window containing the cursor. 
	@param x IN/OUT The cursor's x-coordinate. 
	@param y IN/OUT The cursor's y-coordinate. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowAdjustCursorProc)(AVWindow win, AVWindowCoord x, AVWindowCoord y);

/**
	A callback for AVWindowHandler. It is called after the window has 
	been resized. 
	@param win IN/OUT The window that was resized. 
	@param newFrame IN/OUT A rectangle specifying the window's new size 
	and location. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidResizeProc)(AVWindow win, const AVScreenRect *newFrame);

/**
	A callback for AVWindowHandler. It is called after the window has 
	been maximized. 
	@param win IN/OUT The window that was maximized. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidMaximizeProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called after the window has 
	been collapsed. 
	@param win IN/OUT The window that was collapsed. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidCollapseProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called after the window has 
	been resized. 
	@param win IN/OUT The window that was resized. 
	@param newFrame IN/OUT Rectangle specifying the window's new size 
	and location. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidMoveProc)(AVWindow win, const AVScreenRect *newFrame);
#endif /* (ACRO_SDK_LEVEL >= 0x00060000) */

/**
	A callback for AVWindowHandler. The window is about to close. 
	@param win IN/OUT The window to close. 
	@param quitting IN/OUT If <code>true</code>, the application is trying to quit. 
	@return <code>true</code> if the window should close, <code>false</code> to abort the operation. 	
	@see AVWindowUserClose 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVWindowWillCloseProc)(AVWindow win, ASBool quitting);

/**
	A callback for AVWindowHandler. It is called immediately after the 
	window has been closed, but before it has been freed. You 
	may want to explicitly destroy the window in this routine. 
	See also AVWindowWillCloseProc. 
	@param win IN/OUT The window that was closed. 
	@see AVWindowWillCloseProc 
	@see AVWindowUserClose 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidCloseProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called after the window has 
	been activated. The window being activated will not always 
	become the front-most window. 
	@param win IN/OUT The window being activated. 
	@see AVWindowWillDeactivateProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidActivateProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called after the window becomes 
	the key window. 
	@param win IN/OUT The window becoming the key 
	window. 
	@see AVWindowWillResignKeyProc 
	@see AVWindowSetWantsKey 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDidBecomeKeyProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called to handle keystrokes 
	when this is the key window. 
	@param win IN/OUT The window. 
	@param key IN/OUT The key that was pressed. 
	@param platformEvent IN/OUT A platform-specific event record. On Mac OS, it is 
	a pointer to an EventRecord. On the UNIX operating system it is an <code>eventPtr</code>. 
	@see AVWindowMouseDownProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowKeyDownProc)(AVWindow win, char key, void *platformEvent);

/**
	A callback for AVWindowHandler. It is called before the window ceases 
	to be the key window. 
	@param win IN/OUT The window to resign its key status. 
	@see AVWindowDidBecomeKeyProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowWillResignKeyProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called before the window becomes 
	deactivated or hidden. 
	@param win IN/OUT The window that will be deactivated. 
	@see AVWindowDidActivateProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowWillDeactivateProc)(AVWindow win);

/**
	A callback for AVWindowHandler. It is called when the user has chosen 
	an Edit menu item and the corresponding AVWindowCanPerformEditOpProc() 
	returned <code>true</code>. 
	@param win IN/OUT The window that the Edit menu item is to act 
	on. 
	@param editOp IN/OUT An ASAtom specifying the edit operation. 
	It must be an ASAtom corresponding to one the strings: 
	<ul>
		<li>
			<code>"Cut"</code>
		</li>
		<li>
			<code>"Copy"</code>
		</li>
		<li>
			<code>"Paste"</code>
		</li>
		<li>
			<code>"Clear"</code>
		</li>
		<li>
			<code>"SelectAll"</code>
		</li>
		<li>
			<code>"Undo"</code>
		</li>
	</ul>
	@see AVWindowCanPerformEditOpProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowPerformEditOpProc)(AVWindow win, ASAtom editOp);

/**
	A callback for AVWindowHandler. It is called before showing the 
	Edit menu, to determine whether to enable the Edit menu 
	item corresponding to the given ASAtom. 
	@param win The current window. 
	@param editOp ASAtom specifying the edit operation. It must 
	be an ASAtom corresponding to one the strings: 
	<ul>
		<li>
			<code>"Cut"</code>
		</li>
		<li>
			<code>"Copy"</code>
		</li>
		<li>
			<code>"Paste"</code>
		</li>
		<li>
			<code>"Clear"</code>
		</li>
		<li>
			<code>"SelectAll"</code>
		</li>
		<li>
			<code>"Undo"</code>
		</li>
	</ul>

	@return <code>true</code> if the specified operation can be performed, <code>false</code> 
	otherwise. 
	@see AVWindowPerformEditOpProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVWindowCanPerformEditOpProc)(AVWindow win, ASAtom editOp);

/**
	A callback for AVWindowHandler. It is called when it is time to dispose 
	of the <code>platformThing</code> for the window passed to AVWindowNewFromPlatformThing(). 
	@param win The window. 
	@param platformThing The platform-specific object (<code>WindowPtr</code> 
	on Mac OS, an <code>HWND</code> on Windows, and a <code>Widget</code> on UNIX) that 
	was used for this window.
	@see AVWindowNewFromPlatformThing 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVWindowDestroyPlatformThingProc)(AVWindow win, void *platformThing);
#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A data structure containing callbacks that implement a window 
	handler. The callbacks implement the window handler functions. 
	For example, they can resize the window, draw its contents, handle 
	mouse clicks, and handle key presses. <code>NULL</code> values are acceptable; 
	default behavior is used in such cases. 
	@see AVWindowNew 
	@see AVWindowNewFromPlatformThing 
*/
typedef struct _t_AVWindowHandler
{
	/** The size of the data structure. It must be set to <code>sizeof(AVWindowHandlerRec)</code>. */
	ASSize_t size;

	/** Mouse clicks in the AVWindow are dispatched through this callback.*/
	AVWindowMouseDownProc MouseDown;

	/** 
		The window is about to close.  It returns <code>true</code> if the window should
		close, <code>false</code> to abort the operation.  If <code>quitting</code> is <code>true</code>,
		the application is in the middle of trying to quit.
	*/
	AVWindowWillCloseProc WillClose;

	/** 
		Called immediately after the window has closed, but before it has
		been freed (if one-shot).
	*/
	AVWindowDidCloseProc DidClose;

	/** Called after the window becomes the frontmost, active window.*/
	AVWindowDidActivateProc DidActivate;

	/** Called after the window becomes the key window. */
	AVWindowDidBecomeKeyProc DidBecomeKey;

	/** Called to handle keystrokes when this is the key window. */
	AVWindowKeyDownProc KeyDown;

	/** Called before the window ceases to be the key window. */
	AVWindowWillResignKeyProc WillResignKey;
	
	/** Called before the window becomes deactivated or hidden. */
	AVWindowWillDeactivateProc WillDeactivate;

	/**
		Called whenever the window needs to refresh some part of its
		interior.
	*/
	AVWindowDrawProc Draw;

	/**
		The window is about to be resized in accordance with the
		given rectangle.  This callback may alter the contents
		of <code>newFrame</code> to change the new frame size.  Returning <code>false</code>
		aborts the operation.
	*/
	AVWindowWillBeResizedProc WillBeResized;

	/**
		Called when the user has chosen an Edit menu item corresponding
		to the given ASAtom, assuming the corresponding CanPerformEditProc()
		returned <code>true</code>.
	*/
	AVWindowPerformEditOpProc PerformEditOp;
	
	/**
		Called before showing the menus to determine whether a given
		Edit menu item corresponding to the given ASAtom should be enabled.
	*/
	AVWindowCanPerformEditOpProc CanPerformEditOp;
	
	/**
		Called periodically while the cursor is over the AVWindow (if active).
		Use this to adjust the cursor's appearance.
	*/
	AVWindowAdjustCursorProc AdjustCursor;
	
	/**
		Called after a window is resized.
	*/
	AVWindowDidResizeProc DidResize;

	/**
		Called during DestroyWindow() when it is time to dispose
		of the <code>platformThing</code> for the window passed into
		AVWindowNewFromPlatformThing().
	*/
	AVWindowDestroyPlatformThingProc DestroyPlatformThing;

	/**
		Called after a window is maximized.
	*/
	AVWindowDidMaximizeProc DidMaximize;

	/**
		Called after a window is collapsed.
	*/
	AVWindowDidCollapseProc DidCollapse;
	
	/**
		Called after a window is moved.
	*/
	AVWindowDidMoveProc DidMove;
} AVWindowHandlerRec, *AVWindowHandler;
#endif
/************************************************************************************\
|*																					*|
|*									AVGrafSelect									*|
|*																					*|
\************************************************************************************/
typedef struct _t_AVGrafSelect *AVGrafSelect;

/************************************************************************************\
|*																					*|
|*									AVAlert											*|
|*																					*|
\************************************************************************************/

/** @ingroup AVAlertIcons */
#define ALERT_NOICON				0

/** @ingroup AVAlertIcons */
#define ALERT_STOP					1

/** @ingroup AVAlertIcons */
#define ALERT_CAUTION				2

/** @ingroup AVAlertIcons */
#define ALERT_NOTE					3

/** @ingroup AVAlertIcons */
#define ALERT_QUESTION				4


/** Alert Types */
enum {

	/** */
	kAVAlertTypeNone = 0,

	/** */
	kAVAlertTypeOk,

	/** */
	kAVAlertTypeOkCancel,

	/** */
	kAVAlertTypeYesNo,

	/** */
	kAVAlertTypeYesNoCancel
};
typedef ASEnum16 AVAlertType;


/**
	A data structure containing information about a button used 
	in an Alert dialog box. 
	@see AVAlertWithParams 
*/
typedef struct AVAlertButtonInfo {

	/** Pass <code>true</code> to show the button. */
	ASBool show;

	/** If non-<code>NULL</code> this text is used as the button caption, otherwise the default is used. The default values 
	for <code>button1</code>, <code>button2</code> and <code>button3</code> are <code>"OK"</code>, <code>"Cancel"</code>, and <code>""</code> respectively.*/
	ASText title;	
} AVAlertButtonInfo;


/**
	A data structure containing information about a checkbox used 
	in an Alert dialog box. 
	@see AVAlertWithParams 
*/
typedef struct AVAlertCheckBoxInfo {

	/** Pass <code>true</code> to show the button. */
	ASBool show;	

	/** If non-<code>NULL</code> this text is used as the checkbox caption, otherwise the default is used. The default value 
		for the checkbox is <code>"Do not show this message again"</code>.
	*/
	ASText title;

	/** Pass <code>true</code> to initially check the box. The chosen value is returned in this parameter. */
	ASBool value;	
} AVAlertCheckBoxInfo;

/* AVAlertParams -- passed into AVAlertWithParams
*/

/**
	A data structure containing information about the format of 
	an Alert dialog box.
	@see AVAlertWithParams 
*/
typedef struct _t_AVAlertParams
{

	/** The size of the structure. It must be set to <code>sizeof(AVAlertParamsRec)</code>. */
	ASSize_t 			size;
	

	/** The AVDoc that is the modal parent of the alert dialog box. It may be <code>NULL</code>. The <code>parentDoc</code> can be <code>NULL</code>, 
		in which case the alert dialog box' parent is the currently active doc, if there is one. The <code>parentDoc</code> is a no-op on 
		Mac OS. 
	*/
	AVDoc				parentDoc;

	/** The title of the dialog box. It may be <code>NULL</code>, in which case the default title, <code>"Adobe Acrobat"</code>, is used. */
	ASText				windowTitle;

	/** The icon to display. It must be one of the AVAlert Icons. 
		@ref AVAlertIcons
	*/
	AVIconType			iconType;

	/** The message to display. */
	ASText				message;

	/** Set to <code>true</code> to trigger a beep when the dialog box is shown. */
	ASBool				beep;

	/** An AVAlertButtonInfo structure describing the dialog box' buttons. Any or all of these buttons may be <code>NULL</code>. If all 
		are <code>NULL</code>, the dialog box is shown with an OK button. 
	*/
	AVAlertButtonInfo	button1;

	/** An AVAlertButtonInfo structure describing the dialog box' buttons. Any or all of these buttons may be <code>NULL</code>. If all 
		are <code>NULL</code>, the dialog box is shown with an OK button. 
	*/
	AVAlertButtonInfo	button2;

	/** An AVAlertButtonInfo structure describing the dialog box' buttons. Any or all of these buttons may be <code>NULL</code>. If all 
		are <code>NULL</code>, the dialog box is shown with an OK button. 
	*/
	AVAlertButtonInfo	button3;

	/** An AVAlertCheckBoxInfo structure describing the dialog box' checkbox. It may be <code>NULL</code>. */
	AVAlertCheckBoxInfo	checkbox;

	/** The type of the alert. */
	AVAlertType			alertType;
	
	/** The window to be the parent of the alert. It is ignored if <code>parentDoc</code> is non-<code>NULL</code>. It is ignored on Mac OS. */
	AVWindow			parentWindow;
}
AVAlertParamsRec, *AVAlertParams;

/************************************************************************************\
|*																																									*|
|*									AVAction																												*|
|*																																									*|
\************************************************************************************/

/*
** opaque action handler object: see AVAction.h
*/

/** Carries out an action. When the Acrobat viewer executes an action, it looks for the
	action handler with a type matching that of the action it is trying to execute. The
	Acrobat viewer invokes the matching handler to perform the action. If no match is
	found, the Acrobat viewer ignores the user action.
	@see AVAppGetActionHandlerByType
	@see AVAppEnumActionHandlers
	@see AVAppEnumActionHandlers
	@see AVAppGetActionHandlerByType 
	@see AVActionHandlerGetProcs 
	@see AVActionHandlerGetType 
	@see AVActionHandlerGetUIName
*/
typedef struct _t_AVActionHandler *AVActionHandler;

/*
** definition of action handler procs object used by AVAppRegisterActionHandler, also see AVActnIm.h
*/
typedef struct _t_AVActionHandlerProcs *AVActionHandlerProcs;


/**
	A callback used by AVAppEnumActionHandlers(). It is called once 
	for each action handler. 
	@param type The action handler's name. 
	@param userName The action's name, as it appears in the 
	Acrobat viewer's user interface. 
	@param clientData User-supplied data that was passed in 
	the call to AVAppEnumActionHandlers().
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	@see AVActionHandlerGetProcs 
	@see AVAppEnumActionHandlers 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVActionEnumProc)(ASAtom type, char *userName, void *clientData);

/* An implementer of an action handler should fill out the functions in
 * this struct and call AVAppRegisterActionHandler.
 */

#define PDACTION_DESC_BUF_SIZE 256


/**
	A callback for AVActionHandlerProcs(). It performs the action. 	
	@param actionHandlerObj IN/OUT User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action IN/OUT The action to perform. 
	@param doc IN/OUT The document in which the action is located. 
	@see AVActionGetInstructionsProc 
	@see AVActionPerformExProc 
*/
typedef ACCBPROTO1 void	(ACCBPROTO2 *AVActionPerformProc)(void *actionHandlerObj, PDAction action, AVDoc doc);

/**
	A callback for AVActionHandlerProcs(). It displays a user interface 
	that allows a user to set the action's properties. For example, 
	for a Launch action, set the file to launch; for a GoTo 
	action, select the destination page/zoom coordinates). 
	@param actionHandlerObj IN/OUT User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action IN/OUT The action whose properties are set. 
	@param doc IN/OUT The document in which the action is located. 
	@see AVActionHandlerGetProcs 
	@see AVActionDoPropertiesEx
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVActionDoPropertiesProc)(void *actionHandlerObj, PDAction action, AVDoc doc);

/**
	(Required) A callback for AVActionHandlerProcs(). This required 
	function is called as soon as the user selects the action 
	from the action types popup menu. It allows an action handler 
	to populate a newly created action's <code>actionDict</code>. At the 
	time this method is called, the information needed to completely 
	specify an action is often not yet available. As a result, 
	this method is generally a good place to populate the <code>actionDict</code> 
	with default values. 
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param actionDict The action dictionary to populate with default 
	values. 
	@param doc The document in which the action is located.
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 void	(ACCBPROTO2 *AVActionFillActionDictProc)(void *actionHandlerObj, CosObj actionDict, AVDoc doc);

/**
	A callback for AVActionHandlerProcs(). This optional function 
	should store into buffer a <code>NULL</code>-terminated C string that 
	contains localized instructions for the action creation/properties 
	dialog box. 
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action The action whose instructions are returned. 
	@param buffer (Filled by the callback) The instruction 
	text. 
	@param bufLen The length of <code>buffer</code> in bytes. 
	@param doc The document in which the action is located.
	@return The number of characters copied into <code>buffer</code>. 
	@see AVActionPerformExProc 
	@see AVActionPerformProc 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 AVTArraySize	(ACCBPROTO2 *AVActionGetInstructionsProc)(void *actionHandlerObj, PDAction action, char *buffer, AVTArraySize bufLen, AVDoc doc);

/**
	A callback for AVActionHandlerProcs. This optional function 
	should store into <code>buffer</code> a <code>NULL</code>-terminated C string that 
	is a localized string for the edit action button in the 
	action dialog box. 

	<p>For example, the Acrobat viewer's built-in <code>OpenFile</code> action 
	returns <code>"Select File"</code> for this string. </p>
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action The action whose button text is returned. 
	@param buffer (Filled by the callback) The button text. 
	@param bufLen The length of <code>buffer</code> in bytes. 
	@param doc The document in which the action is located.
	@return The number of characters copied into <code>buffer</code>. 
	@see AVActionGetStringOneTextProc 
	@see AVActionGetStringTwoTextProc 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 AVTArraySize	(ACCBPROTO2 *AVActionGetButtonTextProc)(void *actionHandlerObj, PDAction action, char *buffer, AVTArraySize bufLen, AVDoc doc);

/**
	(Optional) A callback for AVActionHandlerProcs(). This function 
	should store into <code>buffer</code> a <code>NULL</code>-terminated C string that 
	is a localized string placed above the edit action button 
	in the action dialog box. A <code>NULL</code> proc will cause the button 
	to hide. 

	<p>For example, the Acrobat viewer's built-in <code>OpenFile</code> action 
	returns <code>"File N: \<the current filename\>"</code> for this string. </p>
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action The action whose <code>"string 1"</code> text is returned. 
	@param buffer (Filled by the callback) The string text 
	appearing above the button. 
	@param bufLen Length of <code>buffer</code> in bytes. 
	@param doc The document in which the action is located.
	@return The number of characters copied into <code>buffer</code>. 
	@see AVActionGetButtonTextProc 
	@see AVActionGetStringTwoTextProc 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 AVTArraySize	(ACCBPROTO2 *AVActionGetStringOneTextProc)(void *actionHandlerObj, PDAction action, char *buffer, AVTArraySize bufLen, AVDoc doc);

/**
	A callback for AVActionHandlerProcs(). This optional function 
	should store into buffer a <code>NULL</code>-terminated C string which 
	is a localized string placed below the edit action button 
	in the action dialog box. 

	<p>For example, the Acrobat viewer's built-in <code>OpenFile</code> action 
	returns nothing for this string, but the built-in <code>GoToView</code> 
	action returns a description of the current zoom type. </p>
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action The action whose "string 2" text is returned. 
	@param buffer (Filled by the callback) The string text 
	appearing below the button. 
	@param bufLen Length of <code>buffer</code> in bytes. 
	@param doc The document in which the action is located.
	@return The number of characters copied into <code>buffer</code>. 
	@see AVActionGetButtonTextProc 
	@see AVActionGetStringOneTextProc 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 AVTArraySize	(ACCBPROTO2 *AVActionGetStringTwoTextProc)(void *actionHandlerObj, PDAction action, char *buffer, AVTArraySize bufLen, AVDoc doc);

/**
	(Optional) A callback for AVActionHandlerProcs(). It is called upon 
	to copy an action, possibly to another document. Action 
	handlers should provide this callback to allow for copying 
	their actions. It is called by AVDocCopyAction(). 
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param fromDoc The document whose action is copied. 
	@param anAction The action to copy. 
	@param toDoc The document to which the action is copied.
	@return The newly created PDAction copy. 
	@see AVDocCopyAction 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 PDAction (ACCBPROTO2 *AVActionCopyProc)(void *actionHandlerObj, AVDoc fromDoc, PDAction anAction, AVDoc toDoc);

/**
	Optional callback for AVActionHandlerProcs(). It is called to get 
	informational details to present to the user. The handler 
	can provide one or more ASText strings which are added to 
	the ASCab provided by the caller. Generally, each string 
	should form a single informational item, often provided 
	in a <code>"key: value"</code> format. The caller will organize the strings 
	into a list that is presented in the user interface. 
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param doc The document in which the action is located. 
	@param action The action whose details are returned. 
	@param details (Filled by the callback) The ASCab to populate 
	with the informational details, provided as ASText strings.
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVActionGetDetailsProc)(void *actionHandlerObj, AVDoc doc, PDAction action, ASCab details);

/**
	This structure gives the action handler some context in			
	terms of its execution. It specifies the <code>" parent"</code> object, 
	which initiated the action, and the trigger type of the 
	action. Trigger names should correspond to the key used 
	in the AA dictionary of the file. 
	@see AVActionPerformExProc 
*/
typedef struct _AVActionContextRec {

	/** The size of this record. It must be set to <code>sizeof(AVActionContextRec)</code>. */
	ASSize_t size;	

	/** The object that is performing the action, such as a bookmark or annotation. */
	CosObj co;		

	/** The type of the object, using these defines: 
	
		<p><code>#define AVTRIGGERTYPE_DOC ASAtomFromString("Doc") </code></p>
		<p><code>#define AVTRIGGERTYPE_DEST ASAtomFromString("Dest") </code></p>
		<p><code>#define AVTRIGGERTYPE_PAGE ASAtomFromString("Page") </code></p>
		<p><code>#define AVTRIGGERTYPE_LINK ASAtomFromString("Link") </code></p>
		<p><code>#define AVTRIGGERTYPE_ANNOT ASAtomFromString("Annot") </code></p>
		<p><code>#define AVTRIGGERTYPE_BOOKMARK ASAtomFromString("Bookmark")</code></p> 
	
	*/
	ASAtom asaType;	

	/** The trigger name for the object, using these defines: 
	
		<p><code>#define AVTRIGGER_MOUSEUP ASAtomFromString("Mouse Up") </code></p>
		<p><code>#define AVTRIGGER_OPEN ASAtomFromString("Open")</code> </p>
		<p><code>#define AVTRIGGER_CLOSE ASAtomFromString("Close") </code></p>
	
	*/
	ASAtom asaKey;	
} AVActionContextRec, *AVActionContext;

#define AVTRIGGERTYPE_DOC			ASAtomFromString("Doc")
#define AVTRIGGERTYPE_DEST			ASAtomFromString("Dest")
#define AVTRIGGERTYPE_PAGE			ASAtomFromString("Page")
#define AVTRIGGERTYPE_LINK			ASAtomFromString("Link")
#define AVTRIGGERTYPE_ANNOT			ASAtomFromString("Annot")
#define AVTRIGGERTYPE_BOOKMARK		ASAtomFromString("Bookmark")
#define AVTRIGGER_MOUSEUP			ASAtomFromString("Mouse Up")
#define AVTRIGGER_OPEN				ASAtomFromString("Open")
#define AVTRIGGER_CLOSE				ASAtomFromString("Close")
#define AVTRIGGER_SHOW				ASAtomFromString("Show")
#define AVTRIGGER_HIDE				ASAtomFromString("Hide")


/**
	A callback for AVActionHandlerProcs(). If defined, it is called 
	instead of AVActionPerformProc(). It is passed the context 
	of an action, which provides information on what triggered 
	the action. 
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param action An action to perform. 
	@param doc The document in which the action is located. 
	@param context The context of the action.
	@see AVActionPerformProc 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 void	(ACCBPROTO2 *AVActionPerformExProc)(void *actionHandlerObj, PDAction action, AVDoc doc, AVActionContext context);

/**
	A callback for AVActionHandlerProcs. If defined, it is called 
	instead of DoProperties(). 

	<p>It is called to allow the user to view or edit the properties 
	for an array of actions. Typically this presents a modal 
	OK/Cancel dialog box to the user. The dialog box should graphically 
	denote properties that do not have the same value for every 
	action in the array by using an <i>indeterminant</i> state. For 
	example, if the action has a flag property that is set to 
	<code>true</code> for one action and <code>false</code> for another, instead of <code>"true"</code> 
	or <code>"false"</code>, the dialog box could show the string <code>"&lt;varies&gt;"</code> 
	for that property. The user will still be able to change 
	the <code>"&lt;varies&gt;"</code> string to either <code>true</code> or <code>false</code>, which would 
	apply the new value to every action in the array. </p>
	@param actionHandlerObj User-supplied data that was passed 
	when the action handler was registered using AVAppRegisterActionHandler(). 
	@param doc The document in which the actions are located. 
	@param actions An array of actions whose properties are 
	set. 
	@param numActions The number of actions in the array.
	@return <code>true</code> if the actions were changed, <code>false</code> if unchanged. 
	@see AVActionHandlerGetProcs 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVActionDoPropertiesExProc)(void *actionHandlerObj, AVDoc doc, PDAction *actions, ASArraySize numActions);

/** A data structure containing callbacks that implement an action handler. The callbacks
	implement the action handler functions. For example, they can display user interface text,
	request the action's properties from the user, and perform the action.
	@see AVAppRegisterActionHandler
	@see AVActionHandlerGetProcs
	@see AVDocCopyAction
*/
typedef struct _t_AVActionHandlerProcs {

	/** The size of the data structure. It must be set to <code>sizeof(AVActionHandlerProcsRec)</code>. */
	ASSize_t size;

	/** */
	AVActionPerformProc Perform;

	/** */
	AVActionDoPropertiesProc DoProperties;

	/** */
	AVActionFillActionDictProc FillActionDict;

	/** */
	AVActionGetInstructionsProc GetInstructions;

	/** */
	AVActionGetButtonTextProc GetButtonText;

	/** */
	AVActionGetStringOneTextProc GetStringOneText;

	/** */
	AVActionGetStringTwoTextProc GetStringTwoText;

	/** */
	AVActionCopyProc Copy;

	/** */
	AVActionPerformExProc PerformEx;

	/** */
	AVActionDoPropertiesExProc DoPropertiesEx;

	/** */
	AVActionGetDetailsProc GetDetails;

} AVActionHandlerProcsRec;


/************************************************************************************\
|*																					*|
|*									AVAuxData										*|
|*																					*|
\************************************************************************************/


/**
	(Optional) A callback for AVAuxDataHandler. It is called to 
	process auxiliary data sent to the AVDoc using AVDocSendAuxData(). 
	This callback must process the data appropriately for whatever 
	<code>auxDataType</code> is sent. 

	<p>If <code>NULL</code>, default behavior is used. </p>
	@param auxDataType IN/OUT Specifies the type of <code>auxData</code>. This 
	determines how <code>auxData</code> is interpreted. 
	@param auxData IN/OUT The auxiliary data. 
	@param auxDataLen IN/OUT The length of <code>auxData</code> in bytes. 
	@param avDoc IN/OUT The document with which the auxiliary data 
	is associated. 
	@return <code>true</code> if the data is acted upon, <code>false</code> if nothing is done. 	
	@see AVDocSendAuxData 
*/
#if (ACRO_SDK_LEVEL >= 0x00090000)
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVAuxDataPerformProc)(ASAtom auxDataType, void *auxData, AVTBufferSize auxDataLen, AVDoc avDoc, void* clientData);
#endif

/**
	A data structure containing callbacks and data representing 
	an auxiliary data handler. <code>NULL</code> values are acceptable; in such cases default behavior is used.
	@see AVDocSendAuxData 
	@see AVHasAuxDataHandler 
	@see AVRegisterAuxDataHandler 
*/
#if (ACRO_SDK_LEVEL >= 0x00090000)
typedef struct _t_AVAuxDataHandler {                                          

	/** The size of the data structure. It must be set to <code>sizeof(AVAuxDataHandlerRec)</code>. */
	ASSize_t size;

	oldAVAuxDataPerformProc oldPerformProc; /* obsolete */
	/** Called with auxiliary data when a client calls AVDocSendAuxData(). This proc should perform whatever 
		action is required for the auxiliary data.
	*/
	AVAuxDataPerformProc PerformProc; 
} AVAuxDataHandlerRec, *AVAuxDataHandler;                                     
#endif

/************************************************************************************\
|*																					*|
|*									AVDocPrintParams								*|
|*																					*|
\************************************************************************************/

/* AVRect32 only needed for support of 32-bit coordinates before Acrobat 6, preferred method is to use AVRect with ACRO_SDK_LEVEL >= 0x00060000 */
#if (ACRO_SDK_LEVEL >= 0x00060000)
typedef AVRect AVRect32;

/**
	<p>A data structure representing a rectangle (a quadrilateral 
	having only horizontal and vertical sides). </p>

	<p>The AcroView coordinate system is defined so that (0,0) 
	is at the top, <code>x</code> increases to the right, and <code>y</code> increases 
	down (the same as GDI and QuickDraw but opposite to the 
	PostScript language). An AVRect32 is defined so that its 
	top is above its bottom, but this means that <code>0 < top < bottom</code>. </p>
	

	@note This structure supports 32 bit coordinates in versions 
	prior to Acrobat 6.0. For version 6.0 and later, AVRect 
	is preferred. 
*/
typedef AVRectP AVRect32P;

/* Define a platform specification for a printer */


#if UNIX_PLATFORM

typedef struct _t_ASPlatformPrinterSpec {
	/** The size of the data structure. It must be set to <code>sizeof(ASPlatformPrinterSpecRec)</code>.
	*/
	ASSize_t size;
	/** A print command, such as <code>"lp -dMyPrinter -n4"</code>. If <code>printerName</code> is
		<code>NULL</code>, a default print command is used. The Acrobat viewer's built-in
		default is <code>"lp"</code> on most UNIX systems, and <code>"lpr"</code> on Sun operating systems. This should
		print to the system's default printer. Some UNIX systems also use
		the environment variable <code>LPDEST</code> or <code>PRINTER</code>. See the
		documentation for your platform to determine whether this is the
		case.
	*/
	char *printerName;	
	/* Currently unused. */
	ASUns8 *baseAddr;				
	/* Currently unused. */
	AVBufferSize rowBytes; 
	/* Currently unused. */
	AVBufferSize depth;		
	/* Currently unused. */
	AVRect bounds;            
} ASPlatformPrinterSpecRec, *ASPlatformPrinterSpec;
#endif /*UNIX_PLATFORM*/
#endif

/* Define a platform specification for a printer */

#if MAC_PLATFORM
#define kPrinterSpecNameLen 256	
typedef struct _t_ASPlatformPrinterSpec {
	/** The size of the data structure. It must be set to
		<code>sizeof(ASPlatformPrinterSpecRec)</code>.
	*/
	ASSize_t size;
#if !AS_ARCH_64BIT
	/** The port to print to. */
	CGrafPtr *cGrafPtr;	
#endif
	/** The best known resolution of the current printer. */
	short	hRes, vRes;	
	/** The name of the printer. */
	UniChar printerName[kPrinterSpecNameLen];
} ASPlatformPrinterSpecRec, *ASPlatformPrinterSpec;
#endif


#if WIN_PLATFORM
#define kPrinterSpecNameLen 221  // Making this 221 as the maximum number of characters that we were able to enter in the printer name text box (in printers properties) is 220.

#define kPrinterSpecUnicodeNameLen 221	


/**
	A data structure representing a platform specification for 
	a printer. It is used in AVDocPrintParams. 
	@see AVDocPrintPagesWithParams 
*/
typedef struct _t_ASPlatformPrinterSpec {
	/** The size of the data structure. It must be set to <code>sizeof(ASPlatformPrinterSpecRec)</code>. */
	ASSize_t size;							

	/* The following should be provided for full, non-interative printing */

	/** See <code>Windows.h</code> <code>DEVNAMES</code> for a description of these fields. 
	   This <code>char</code> name is deprecated; please use the Unicode version <code>driverNameW</code>.
	*/
	char driverName[kPrinterSpecNameLen];

	/** The name of the printer. For example, it can be <code>"HPPCL"</code>, <code>"HP LaserJet 4"</code>, or <code>"LPT1"</code>.  
	  This <code>char</code> name is deprecated; please use the Unicode version <code>printerNameW</code>.
	*/
	char printerName[kPrinterSpecNameLen];	

	/** The port to print to. 
	This <code>char</code> name is deprecated; please use the Unicode version <code>portNameW</code>.
	*/
	char portName[kPrinterSpecNameLen];		 

	/* The following must be provided for embedded printing */

	/** This must be <code>true</code> of Windows 32-bit platforms; optional for Windows 16-bit platforms. */
	ASBool		createMetaFile;			

	/** The path name for the metafile. It is only required if <code>createMetaFile</code> is <code>true</code>. 
	This <code>char</code> name is deprecated; please use the Unicode version <code>metaFileNameW</code>.
	*/
	char		metaFileName[260];		

	/** An <code>HDC</code> for embedded printing on Windows 16-bit platforms, unused on Windows 32-bit platforms. */
	ASInt32		win16Hdc;				

	/** The horizontal resolution of printer. For example, a value of <code>300</code> means 300 dpi. */
	ASInt32		hRes;					

	/** The vertical resolution of printer. For example, a value of <code>300</code> means 300 dpi. */
	ASInt32		vRes;					

	/**  The color depth of the device; its value is typically <code>1</code>, <code>8</code>, or <code>24</code>. This determines the depth of images created for the 
		printer. You may specify <code>24</code> when printing to a monochrome printer. The driver is expected to convert to the printer 
		depth. It is not used if <code>isPostScript</code> is <code>true</code>.
	*/
	ASInt32		colorDepth;				


	/** Set to <code>true</code> if printing to a PostScript printer. */
	ASBool		isPostScript;			

	/** Unicode names of the driver. When both <code>driverName</code> and <code>driverNameW</code> are valid, the Unicode name is used. */
	ASUns16 driverNameW[kPrinterSpecUnicodeNameLen];

	/** Unicode names of the printer. When both <code>printerName</code> and <code>printerNameW</code> are valid, the Unicode name is used. */
	ASUns16 printerNameW[kPrinterSpecUnicodeNameLen];	

	/** Unicode names of the port. When both <code>portName</code> and <code>portNameW</code> are valid, the Unicode name is used. */
	ASUns16 portNameW[kPrinterSpecUnicodeNameLen];		 

	/** Unicode path name for the metafile. When both <code>metaFileName</code> and <code>metaFileNameW</code> are valid, the Unicode name is used.  */
	ASUns16	metaFileNameW[260];		

} ASPlatformPrinterSpecRec, *ASPlatformPrinterSpec;
#endif

#if OS2_PLATFORM
#define kPrinterSpecNameLen 64	/* room for 64 chars */
typedef struct _t_ASPlatformPrinterSpec {
	ASSize_t size;							/* set this to be the size of this struct */

	/* The following should be provided for full, non-interative printing */
	char driverName[kPrinterSpecNameLen];	/* See Windows.h DEVNAMES for a description of these fields */
	char printerName[kPrinterSpecNameLen];	/* For example, {"HPPCL", "HP LaserJet 4", "LPT1:"}, or, */
	char portName[kPrinterSpecNameLen];		/* 				{"HP LaserJet 4/4M PS", "\\PCCAROUSEL\4PLUS", "\\PCCAROUSEL\4PLUS"} */ 

	/* The following must be provided for embedded printing */
	ASBool		createMetaFile;			/* Must be <code>true</code> if Win32; may be optional for Win16 (pending testing). */
	char		metaFileName[260];		/* Pathname for the metafile. Only required if createMetaFile is <code>true</code>. */
	ASInt32		win16Hdc;				/* for possible use in Win16 */
	ASInt32		hRes;					/* horizontal resolution of printer, e.g. 300 dpi */
	ASInt32		vRes;					/* vertical resolution of printer, e.g. 300 dpi */
	ASInt32		colorDepth;				/* Color depth of device; typically 1, 8 or 24.
										** This determines the depth of images created for the 
										** printer. You may specify 24 when printing to 
										** a monochrome printer. The driver is expected to
										** convert to the printer depth.
										** Not used if isPostScript.
										*/
	ASBool		isPostScript;			/* Set to <code>true</code> if printing to PS printer. */
	ASInt32	psHeight;			/* Printer Presentation space height */
} ASPlatformPrinterSpecRec, *ASPlatformPrinterSpec;
#endif


enum {

	/** A PS file. 
  		@ingroup emitFileOption
	*/
	kAVEmitFilePS,           

	/** An EPS file with no preview. 
	  		@ingroup emitFileOption
	*/
	kAVEmitFileEPSNoPrev,     
	/** With Acrobat 10, PICT previews for EPS files are no longer
	supported. TIFF previews are still supported, use kAVEmitFileEPSPreview
	to request a preview for Mac and Windows 
	*/
	
	kAVEmitFileEPSPreview

	/** An EPS file with standard preview. Deprecated for Acrobat 10
  		@ingroup emitFileOption
	*/
//	kAVEmitFileEPSMacStdPrev, 

	/** An EPS file with extended preview. Deprecated for Acrobat 10
  		@ingroup emitFileOption
	*/
//	kAVEmitFileEPSMacExtPrev  
};


/** 
	The following enumeration is deprecated. It is maintained
	solely for backward compatibility.
*/
enum {

	/** Embed no fonts. 
  		@ingroup emitFontOption
	*/
	kAVEmitFontNoFonts,        

	/** Embed all Type 1 embedded fonts. 
  		@ingroup emitFontOption
	*/
	kAVEmitFontAllEmbType1,    

	/**
		Constants that specify tile marking styles for AVDocPrintTileData(), 
		used in AVDocPrintParams. 
		@see AVDocPrintPagesWithParams
  		@ingroup emitFontOption
	*/
	kAVEmitFontAllType1      
};

/** Constants that specify tile marking styles for AVDocPrintTileData(), 
	used in AVDocPrintParams. 
	@see AVDocPrintPagesWithParams
*/
enum {
	/** */
	kAVTileMarkNone =0,
	/** */
	kAVTileMarkWestern,
	/** Obsolete: Acrobat 7.0 and later support only one 'kAVTileMarkWestern' tile mark. */
	kAVTileMarkEastern
};
typedef ASEnum16 AVTileMark;

/** The new EmitFont enumeration covers
	all font types, not just Type 1.
*/
enum {
	/** Emit all embedded fonts. */
	kAVEmitFontEmbeddedFonts = 1, 
	/** Emit all fonts. */
	kAVEmitFontAllFonts        	   
};


/** Constants that specify page size types for AVDocPrintParams, 
	introduced in Acrobat 6.0. If the <code>pageSize</code> field is not 
	set, the old field <code>shrinkToFit</code> is used instead. 
	@see AVDocPrintPagesWithParams
*/
enum {

	/** Uninitialized. */
	kAVPageSizeUninitialized =0,

	/** Perform no adjusting for size; pages are cropped by the printer. */
	kAVPageSizeNone,

	/** Fit to paper. */
	kAVPageSizeFitToPaper,

	/** Shrink large pages. */
	kAVPageSizeShrinkLargePages,

	/** Tile large pages. */
	kAVPageSizeTileLargePages,

	/** Tile all pages. */
	kAVPageSizeTileAllPages,

	/** N-up printing mode. */
	kAVPageSizeNup,

	/** Booklet printing mode. */
	kAVPageSizeBooklet,

	/** Custom Scale. */
	kAVPageSizeCustom
};
typedef ASEnum16 AVPageSize;


/** Constants that specify color forcing values for <code>AVDocPrintOverrideData</code>, 
	used in AVDocPrintParams. 

	<p>Use <code>AVForceColor</code> when a print driver incorrectly handles 
	conversion of color to grayscale or monochrome. This overrides 
	the Windows printerspec <code>colorDepth</code> value. As of 1/1/02, 
	only WinFax is known to need this setting since it incorrectly 
	converts all colors to black. </p>
	@see AVDocPrintPagesWithParams
*/
enum {

	/** Do not force color conversions. */
	kAVForceColorNone =0,  

	/** Force color to grayscale. */
	kAVForceColorToGrayscale,

	/** Force color to monochrome. */
	kAVForceColorToMonochrome
};
typedef ASEnum16 AVColorForcing;

/**
	Constants that determine whether to let Acrobat decide whether 
	to use a feature or force Acrobat to use or 
	not to use the feature. It is used in AVDocPrintOverrideData(), 
	which is used in AVDocPrintParams. 
	@see AVDocPrintPagesWithParams 
*/
enum {
	/** Let Acrobat decide whether to use a feature. */
	kAVuseAuto =0,  
	/** Force Acrobat to use a feature, even if Acrobat determines that it will not work. */
	kAVuse, 
	/** Do not use a feature, even if Acrobat determines that it will work.*/
	kAVnoUse 
};
typedef ASEnum16 AVUseValue;

/** Font and resource policy values for AVDocPrintParams. */
enum {

	/**	Send fonts and resources to the first page on which they are used. 
		Pages must be printed in the order in which they are created. Fonts are 
		downloaded in the global VM. Fonts and resources are removed 
		when they are no longer needed. 
	*/
	kAVResPolicySendAtStart, 

	/**	Send fonts and resources to each page on which they are used. Fonts 
		are downloaded in the local VM.
	*/
	kAVResPolicySendByRange,

	/** Send fonts and resources to each page on which they are used. 
		Fonts are downloaded in the local VM.
    */
	kAVResPolicySendPerPage
};
typedef ASEnum16 AVResourcePolicy;

/** N-up printing page order for AVDocPrintNupData (used by AVDocPrintParams). */
enum {
	/** Pages are placed from left to right, and then from top to bottom. */
	kAVnUpPageOrderHorizontal,
	/** Pages are placed from right to left, and then from top to bottom. */
	kAVnUpPageOrderHorizontalRev,
	/** Pages are placed from top to bottom, and then from left to right. */
	kAVnUpPageOrderVertical,
	/** Pages are placed from top to bottom, and then from right to left. */
	kAVnUpPageOrderVerticalRev
};
typedef ASEnum16 AVnUpPageOrder;

/** Booklet printing binding direction (used by AVDocPrintNupData() in the AVDocPrintParams structure). */
enum {
	/** Typical left-side binding for text with left-to-right reading direction. 
		The paper is divided vertically in landscape mode. 
	*/
	kAVBookletBinding_Left,
	/** Right-side binding for text with vertical or right-to-left reading direction. 
		The paper is divided vertically in landscape mode. 
	*/
	kAVBookletBinding_Right,
	/** Left-side binding for text with left-to-right reading direction. 
		The paper is divided vertically in portrait mode. 
	*/
	kAVBookletBinding_LeftTall,
	/** Right-side binding for text with vertical or right-to-left reading direction. 
		The paper is divided vertically in portrait mode. 
	*/
	kAVBookletBinding_RightTall
};
typedef ASEnum16 AVBookletBinding;

/** Booklet printing page duplex printing subset mode. */
enum {
	/** Print pages on both sides. */
	kAVBooklet_BothSides,
	/** Print pages on front sides only. */
	kAVBooklet_FrontSideOnly,
	/** Print pages on back sides only. */
	kAVBooklet_BackSideOnly
};
typedef ASEnum16 AVBookletDuplexMode;

/** Emit the halftones specified in the document. 
  	@ingroup EmitFlags
*/
#define	kAVEmitHalftones			0x00000001	

/** Raise an error on images that 
	cannot be represented in EPS files, following the separation 
	conventions in <i>Technical Note # 5044, Color Separation Conventions 
	for PostScript Language Programs</i>.
  	@ingroup EmitFlags
*/
#define kAVEmitSeparableImagesOnly	0x00000002 

/** Do not emit the cropbox page clip. 
  	@ingroup EmitFlags
*/
#define	kAVSuppressCropClip			0x00000004	

/** Do not emit the transfer functions in the document.
  	@ingroup EmitFlags
*/
#define	kAVSuppressTransfer			0x00000008	

/** Do not emit the BlackGeneration in the document. 
  	@ingroup EmitFlags
*/
#define	kAVSuppressBG				0x00000010	

/** Do not emit the UnderColorRemovals in the document. 
  	@ingroup EmitFlags
*/
#define	kAVSuppressUCR				0x00000020	

/** If the field is set, calls to AVDocPrintPagesWithParams() generate PostScript that suppresses printer-based font substitution 
	for CJK fonts.
  	@ingroup EmitFlags
*/
#define kAVSuppressCJKFontSubst		0x00000040 

/** (New for 5.0) Do not rotate the page. 
  	@ingroup EmitFlags
*/
#define kAVSuppressRotate			0x00000080  

/** (New for 5.0) Do not center the page. 
  	@ingroup EmitFlags
*/
#define kAVSuppressCenter			0x00000100  

/** (New for 5.0) Do not emit text annotations. 
  	@ingroup EmitFlags
*/
#define kAVSuppressAnnots			0x00000200  

/** (New for 5.0) Enable setPageSize(), choose the paper tray by PDF page size. 
  	@ingroup EmitFlags
*/
#define kAVSetPageSize				0x00000400  

/** (New for 5.0) Attempt to reduce the amount of VM used on PostScript printers. 
  	@ingroup EmitFlags
*/
#define kAVSaveVM					0x00000800  

/** (New for 5.0) (PostScript only) If set, PostScript is optimized for speed, otherwise pages must be independent.
  	@ingroup EmitFlags
*/
#define kAVOptimizeForSpeed			0x00001000 

/** (New for 5.0) When printing via the Windows Dynamic Data Exchange (DDE), alerts are not generated; <code>false</code> is returned. 
  	@ingroup EmitFlags
*/
#define kAVSilent					0x00002000	

/** (New for 5.0) Emits a clip to the BoundingBox for EPS. 
  	@ingroup EmitFlags
*/
#define kAVEmitBBoxClip				0x00004000 
/* #define kAVEmitTransferFuncs		0x00008000	- obsolete, use kAVSuppressTransfer */

/* #define kAVPrintICCColorsAsDevice	0x00010000	- obsolete */

/** (New for 5.0) When set, the print path behaves as if the user had clicked the Apply Overprint Preview 
	checkbox in the Advanced print dialog box.
  	@ingroup EmitFlags
*/
#define kAVApplyOverPrint			0x00020000	

/** (New for 5.0) When set, the print path behaves as if the user had clicked the Apply Working 
	Color Spaces checkbox in the Advanced print dialog box.
  	@ingroup EmitFlags
*/
#define kAVApplyWorkingColorSpaces	0x00040000	

/** (PostScript only) Include the PostScript XObjects' content in the output. 
  	@ingroup EmitFlags
*/
#define kAVEmitPostScriptXObjects	0x00080000 

/** Emit only form fields; this takes precedence over kAVSuppressAnnots. 
  	@ingroup EmitFlags
*/
#define kAVEmitFormFieldsOnly		0x00100000 

/** Use the <code>softProofing</code> settings before doing color management. 
  	@ingroup EmitFlags
*/
#define kAVApplySoftProofSettings   0x00200000 

/** When emitting forms, use the <code>execform</code> operator. 
  	@ingroup EmitFlags
*/
#define kAVEmitFormsAsPSForms		0x00400000	

/** When emitting JPEG2000 images, use the maximum available resolution. 
  	@ingroup EmitFlags
*/
#define kAVMaxJP2KRes				0x00800000	

/** Emit TrapNet annots, even if suppress annotations is on. 
  	@ingroup EmitFlags
*/
#define kAVTrapAnnots				0x01000000	

/** Emit the printer's mark annotations, even if suppress annotations is on.  The default is off. 
  	@ingroup EmitFlags
*/
#define kAVPrintersMarks			0x02000000	

/** Provide control over the emission of the <code>setflat</code> operator. 
  	@ingroup EmitFlags
*/
#define	kAVEmitFlatness				0x04000000

/** Emit CJK TrueType fonts as CID Type 2 fonts. 
  	@ingroup EmitFlags
*/
#define	kAVEmitCJKTTAsType2			0x08000000

/** Soft proofing: simulate ink black and paper white when doing soft proofing. 
  	@ingroup EmitFlags
*/
#define kAVSimulateInkBlack         0x10000000
/** 
  	@ingroup EmitFlags
*/
#define kAVSimulatePaperWhite       0x20000000

/** Emit document and stamp annotations only. 
  	@ingroup EmitFlags
*/
#define kAVEmitStampsOnly			0x40000000




enum {	/* marksStyleType */
	/** No flags implies InDesign style printer marks. 
  		@ingroup EmitFlags
	*/
	kAVDefaultMarkType = 0,		/* Acrobat defaults to InDesign style marks */
  	/** @ingroup EmitFlags */
	kAVInDesignJ1MarkType,		/* InDesignJ1 */
  	/** @ingroup EmitFlags */
	kAVInDesignJ2MarkType,		/* InDesignJ2 */
  	/** @ingroup EmitFlags */
	kAVIllustratorMarkType,  	/* Illustrator */
  	/** @ingroup EmitFlags */
	kAVIllustratorJ,			/* IllustratorJ */
  	/** @ingroup EmitFlags */
	kAVQuarkXPress,				/* QuarkXPress */
  	/** @ingroup EmitFlags */
	kLastMarkType				/* placeholder for custom marks file */
};

/* flags to fill in marksFlags field */
/**	Emit crop marks. 
  		@ingroup EmitFlags
*/
#define kAVCropMarks			0x00000001	
/**	Emit trim marks. 
  		@ingroup EmitFlags
*/
#define kAVTrimMarks			0x00000002
/**	Emit bleed marks. 
  		@ingroup EmitFlags
*/
#define kAVBleedMarks			0x00000004
/**	Emit registration marks. 
  		@ingroup EmitFlags
*/
#define kAVRegMarks			0x00000008
/**	Emit color bar marks. 
  		@ingroup EmitFlags
*/
#define kAVColorBarMarks			0x00000010
/**	Emit page information marks. 
  		@ingroup EmitFlags
*/
#define kAVPageInfoMarks			0x00000020

/**	Emit Eastern style marks (the default is Western style). 
	@note Deprecated in Acrobat 7, replaced by the <code>marksStyle</code> field 
  	@ingroup EmitFlags
*/
#define kAVEasternStyleMarks		0x00000040
/**
	For AVDocPrintParams - used in the call AVDocPrintPagesWithParams().
	@ingroup EmitFlags
*/
typedef struct _t_AVDocPrintTileData {
	/** Set this to be the size of this <code>struct</code>. */
	ASSize_t size;							
	/** The distance that tiles overlap in points. */
	ASUns32 overlap;  
	/** A value of <code>1.0</code> indicates normal scale. */
	ASFixed scale; 
	/** */
	ASBool label;
	/** Uses the AVTileMark enum. */
	AVTileMark markType;  
} AVDocPrintTileDataRec, *AVDocPrintTileData;

/** N-up and booklet printing options for AVDocPrintParams. It is used in the call to AVDocPrintPagesWithParams().
	@ingroup EmitFlags 
*/
typedef struct _t_AVDocPrintNupData {
	/** Set this to be the size of this <code>struct</code>. */
	ASSize_t	size;
	/** The number of pages on the horizontal direction of the page.
	    The total number of pages per sheet is <code>(numPagesPerSheetH * numPagesPerSheetV)</code>.
		It is ignored if the page scaling mode, <code>pageSize</code>, is kAVPageSizeBooklet. 
	*/
	ASInt32		numPagesPerSheetH;
	/** The number of pages on the vertical direction of the page.
	    The total number of pages per sheet is <code>(numPagesPerSheetH * numPagesPerSheetV)</code>.
		It is ignored if the page scaling mode, <code>pageSize</code>, is kAVPageSizeBooklet. 
	*/
	ASInt32		numPagesPerSheetV;
	/** N-up page order.
		It is ignored if the page scaling mode, <code>pageSize</code>, is kAVPageSizeBooklet. 
	*/
	AVnUpPageOrder	pageOrder;
	/** Print page borders during N-up printing. */
	ASBool		pageBorder;
	/** Automatically rotate each page to match the page orientation to the available paper area. */
	ASBool		autoRotate;

	/** Booklet page binding direction.
		It is ignored if the page scaling mode, <code>pageSize</code>, is not kAVPageSizeBooklet. 
	*/
	AVBookletBinding	bookletBinding;
	/** Booklet duplex printing mode.
		It is ignored if the page scaling mode, <code>pageSize</code>, is not kAVPageSizeBooklet. 
	*/
	AVBookletDuplexMode	bookletDuplexMode;
	/** Booklet subset printing range: the first sheet (a valid sheet number starts from <code>0</code>).
		If this value is <code>-1</code>, it represents the last sheet number.
		The default value is <code>0</code>.
		It is ignored if the page scaling mode, <code>pageSize</code>, is not kAVPageSizeBooklet. 
	*/
	ASInt32				bookletSubsetFrom;
	/** Booklet subset printing range: the last sheet (a valid sheet number starts from <code>0</code>).
		If this value is <code>-1</code>, it represents the last sheet number.
		The default value is <code>-1</code>.
		It is ignored if the page scaling mode, <code>pageSize</code>, is not kAVPageSizeBooklet. 
	*/
	ASInt32				bookletSubsetTo;
} AVDocPrintNupDataRec, *AVDocPrintNupData;

/**
	Constants that specify rasterization methods to use for 
	printing. These are used in AVDocPrintRasterizeData(), which is used 
	in AVDocPrintParams. 
	@see AVDocPrintPagesWithParams
	@ingroup EmitFlags
*/
enum {
	/** No flags 
		@ingroup EmitFlags
	*/
	kAVRasterizeNoFlags					= 0,	
	/** 
		@ingroup EmitFlags
	*/
	kAVRasterizeAllTextToOutlines		= 1 << 0,	
	/** 
		@ingroup EmitFlags
	*/
	kAVRasterizeAllStrokesToOutlines	= 1 << 1,
	/** 
		@ingroup EmitFlags
	*/
	kAVRasterizeAllowComplexClipRegions	= 1 << 2,	
	/** 
		@ingroup EmitFlags
	*/
	kAVRasterizePreserveOverprint		= 1 << 3
};
typedef ASUns32 AVRasterizeFlags;

/** @ingroup EmitFlags */
#define kPrintMinDPI 1
/** @ingroup EmitFlags */
#define kPrintMaxDPI 9600
/** @ingroup EmitFlags */
#define kPrintDefaultDPI	1200
/** @ingroup EmitFlags */
#define kPrintMinGradDPI 1
/** @ingroup EmitFlags */
#define kPrintMaxGradDPI 9600
/** @ingroup EmitFlags */
#define kPrintDefaultGradDPI 300


/**
	A structure specifying rasterization parameters used by AVDocPrintParams. 
	The constant DPI values are defined in AVExpT.h. 
	@see AVDocPrintPagesWithParams
	@ingroup EmitFlags
*/
typedef struct _t_AVDocPrintRasterizeData {
	/** The size of the data structure. It must be set to 
		<code>sizeof(AVDocPrintRasterizeData)</code>. 
	*/
	ASSize_t size;							
	/** An <code>OR</code> of the bit flags that control the rasterization 
		method to use for printing. 
	*/
	AVRasterizeFlags flags; 
	/** The degree of transparency in the range 
		<code>1</code> to <code>100</code>, where <code>1</code> means all raster, and <code>100</code> means preserve 
		as much transparency data as possible. 
	*/
	ASInt32 transparency; 
	/** The DPI for bitmaps. The default is <code>300</code>. 
		This value is also used when <code>printAsImage</code> is <code>true</code>. 
	*/
	ASUns32 bitmapResolution; 
	/** The DPI for the gradient's interior to 
		the object (not the edges). It can generally be lower than the 
		<code>bitmapResolution</code>. The default is <code>150</code>.
	*/
	ASUns32 gradientResolution; 
	/** The default is <code>300</code>. */
	ASUns32 printAsImageResolution;	
} AVDocPrintRasterizeDataRec, *AVDocPrintRasterizeData;

/**
	A structure specifying override parameters used by AVDocPrintParams. 	
	@see AVDocPrintPagesWithParams 
	@ingroup EmitFlags
*/
typedef struct _t_AVDocPrintOverrideData {
	/** The size of the data structure. It must be set to <code>sizeof(AVDocPrintOverrideDataRec)</code>. */
	ASSize_t size;					
	/** Determines whether to use color forcing. The default 
		is AVColorForceNone. It can be used to send 1-bit or 8-bit 
		data to the printer, instead of 24-bit data. It is ignored on Mac OS. 
	*/
	AVColorForcing colorOverride;
	/** Determines whether to allow the viewer to decide 
		if it should use the printer's PostScript Color Rendering 
		Dictionary. The default is kAVuseAuto, which is normally <code>true</code>. 
		It is <code>false</code> when the printer is listed as broken, which occurs in 
		these cases: 

		<ul>
			<li>
				When printer-based color management is used, 
				printers whose CRD is incorrect produce light gray or peach 
				for white expressed in an ICC color space.
			</li>
			<li>
				The CRDs for Xerox Phaser 740 and Xerox DocuPrint N2125 
				are known to be incorrect, and this may be so for others, 
				especially in these printer families. It is possible to 
				change the printer defaults such as listing additional printers, 
				or to remove a printer from the broken list 
				if the driver is fixed. Contact Adobe technical support 
				for details.
			</li>
		</ul>
	*/
	AVUseValue usePrinterCRD; 
	/** Determines whether to allow the viewer to 
		decide if it should use T1 color conversion (that is, convert 
		Type1 fonts to more efficient font representations) for 
		better performance. It is ignored on Mac OS. The default is kAVuseAuto, 
		which is normally <code>true</code>, except in cases where the printer 
		cannot handle optimized fonts and needs full, slow, Type1 
		fonts. Only the Windows 16-bit HP LJ 4siMX 
		driver is known to be in this category. It is possible to 
		change the printer defaults such as listing additional printers, 
		or to remove a printer from the broken list 
		if the driver if fixed. Contact Adobe technical support 
		for details.
	*/
	AVUseValue useT1Conversion; 
} AVDocPrintOverrideDataRec, *AVDocPrintOverrideData;

/**
	A structure that specifies how to print a document. It specifies rasterization parameters 
	used by AVDocPrintParams. The constant DPI values are defined in AVExpT.h. 

	@see AVDocPrintPagesWithParams 
	@see AVDocPrintPagesWithParams 
  	@ingroup EmitFlags
*/
typedef struct _t_AVDocPrintParams *AVDocPrintParams;
#if (ACRO_SDK_LEVEL >= 0x00060000)

/* The AVPrintDuplexType enumeration was added for Acrobat 8. */
enum {
/** @ingroup AVPrintDuplexType */
kAVPrintDuplexDontCare = 0,
/** @ingroup AVPrintDuplexType */
kAVPrintDuplexSimplex = 1, 
/** @ingroup AVPrintDuplexType */
kAVPrintDuplexFlipLongEdge = 2,
/** @ingroup AVPrintDuplexType */
kAVPrintDuplexFlipShortEdge = 3
};
typedef ASEnum8 AVPrintDuplexType;


#define kPrintUserNoteLen 256
/**
	A structure that specifies how to print a document. 
	@see AVDocPrintPagesWithParams 
  	@ingroup EmitFlags
*/
typedef struct _t_AVDocPrintParams {

	/** The size of the data structure. It must be set to <code>sizeof(AVDocPrintParamsRec)</code>. */
	ASSize_t size;	

	/** Displays a Print dialog box and print status window while 
		printing. It is mutually exclusive with <code>embedded</code>, <code>emitToPrinter</code>, and <code>emitToFile</code>. */
	ASBool interactive;						

	/** If <code>interactive</code> is <code>false</code> and <code>cancelDialog</code> is <code>true</code>, a Cancel dialog box appears.*/
	ASBool cancelDialog;					

	/** The first page to be printed; a zero-based value. It is used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>.  If <code>-1</code>, all pages are printed. */
	ASInt32 firstPage;						

	/** The last page to be printed. It is used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>. If <code>firstPage</code> is <code>-1</code>, this page is ignored. */
	ASInt32 lastPage;						

	/** Used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>. 
	If printing to PostScript, <code>2</code> means level 2, <code>3</code> means level 3. 
	@note With Acrobat 7, level 1 is no longer supported. Attempts to print with <code>psLevel</code> equal to <code>1</code> will
	generate a bad parameter exception. No output will be generated.
	*/
	ASInt32 psLevel;						

	/** Used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>. It is set to <code>true</code> if a binary channel to the printer is supported. */
	ASBool binaryOK;						

	/** Deprecated. Use <code>pageSize</code> instead.
	<p>Used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>. 
	If <code>pageSize</code> is uninitialized and this is <code>true</code>, 
	the page is shrunk or expanded to fit the printer page size.</p> */
	ASBool shrinkToFit;	

	/** The file system name; see <code>filePathName</code>. 
		It is used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>. 
		For the operation of printing to a printer (<code>emitToPrinter = true</code>), 
		if <code>filePathName</code> is specified, <code>fileSysName</code> must be the name of the
		default file system. You can get the file system's name from the ASFileSysGetFileSysNameProc() callback
		in the ASFileSysRec of the file system you are using.
	*/
	ASAtom fileSysName;					

	/** Used if <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>. 
		If non-<code>NULL</code>, <code>filePathName</code> is a platform path for the 
		specified <code>fileSysName</code>, or, if <code>fileSysName</code> is
		ASAtomNull, it is one of the following: 
		
		<p>Possible types:</p>
		<TABLE rules="all" cellspacing="1">
		<TR><TH>Operating System</TH><TH>Type</TH></TR>
		<TR><TD>Windows</TD><TD>A C-string path name.</TD></TR>
		<TR><TD>Mac OS</TD><TD>An FSSpecPtr.</TD></TR>
		<TR><TD>UNIX</TD><TD>A C-string path name.</TD></TR>
		</TABLE>

		<p>If <code>emitToPrinter</code> is <code>true</code> and <code>filePathName</code> is non-<code>NULL</code>, 
		the system printer driver is used to emit the output stream to the file. 
		This is implemented for Windows only.</p>
	*/
	ASPathName filePathName;			

	/** Optionally used if <code>interactive</code>, <code>embedded</code>, or <code>emitToPrinter</code> is <code>true</code>. 
		If it is <code>NULL</code>, a default system printer is used. 
		If it is non-<code>NULL</code>, <code>printerSpec</code> is a platform-specific value. 
		It must be an ASPlatformPrinterSpec.
	*/
	ASPlatformPrinterSpec printerSpec;	

	/** <code>true</code> if it is an embedded view of a page to print, <code>false</code>
		otherwise. It is mutually exclusive with <code>interactive</code>, <code>emitToPrinter</code>, and <code>emitToFile</code>.
		<code>firstPage</code> only is used.  The last page is ignored.
		The printer must be specified as a metafile or a <code>CGrafPtr</code>.
	*/
	ASBool embedded;	

	/** The size of the embedded output in device units. */
	AVRect embeddedRect;				

	/** If <code>true</code>, use the system printer driver for output. 
		If <code>filePathName</code> is specified, it uses the driver to create
		the file. It raises genErrBadParm if an invalid parameter is provided 
		(for example, printing to PDFWriter, Distiller, or to a printer that has been un-installed). 
		It is mutually exclusive with <code>interactive</code>, <code>embedded</code> and <code>emitToFile</code>.
	*/
	ASBool emitToPrinter;					

	/* Parameters for emission of PS Level 1 Color Separations and EPS, or vanilla PS.
	** Creates and writes to filePathName (may not be <code>NULL</code>).
	** Does NOT use system printer driver.
	** Only has partial font emitting capabilities on some platforms:
	** 	Mac:	embedded and system Type 1 fonts only; no TrueType or substitution fonts.
	**	Win:	embedded and system Type 1 fonts only; no TrueType or substitution fonts.
	**	UNIX:	all fonts
	*/

	/** If <code>true</code>, emit non-interactive output to a file. It is used to emit color separations or EPS. This flag cannot be used
		with the Adobe Reader. It is mutually exclusive with <code>interactive</code>, <code>embedded</code> and <code>emitToPrinter</code>. 
		@product_exclude RDR
	*/
	ASBool emitToFile;

	/** Perform level 1 color separations. See <i>Color Separation Conventions for PostScript Language Programs, Technical Note #5044</i>. */
	ASBool doColorSeparations;				

	/** File output options: PostScript or EPS, with or without a preview. 

		<p>Possible values:</p>
		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD>kAVEmitFilePS</TD><TD>PostScript file.</TD></TR>
		<TR><TD>kAVEmitFileEPSNoPrev</TD><TD>EPS file with no preview.</TD></TR>
		<TR><TD>kAVEmitFileEPSMacStdPrev</TD><TD>EPS file with standard preview.</TD></TR>
		<TR><TD>kAVEmitFileEPSMacExtPrev</TD><TD>EPS file with extended preview.</TD></TR>
		</TABLE>
	*/
	ASEnum8 emitFileOption;					

	/** Font output options. It must be one of EmitFontOptions.
		@ref EmitFontOptions
	*/
	ASEnum8 emitFontOption;					

	/* More emit options. */

	/** Additional emit options, such as kAVEmitHalftones. It must be one of the Emit Flags.
		@ref EmitFlags
	*/
	ASUns32	emitFlags;					

	/** Must be a PDPageRange. It takes precedence over the <code>firstPage</code> and <code>lastPage</code> members. */
	PDPageRange *ranges; 

	/** The range of pages to print. */
	AVTSmallArraySize numRanges;
	/* control over TrueType --> Type 1 conversion for PostScript printing */

	/** If <code>true</code>, send TrueType fonts as TrueType fonts (level 3 and most level 2 PostScript printers). 
		If <code>false</code>, convert TrueType to Type 1. 
		This is typically only desirable for Level 1 PostScript where no TrueType handling is present.
	*/
	ASBool TTasT42;			

	/** If <code>true</code>, print pages as an image. */
	ASBool	printAsImage;					

	/** If <code>true</code>, do not download Far East fonts to the printer. */
	ASBool	printerHasFarEastFonts;			

	/** Print from <code>lastPage</code> to <code>firstPage</code>. */
	ASBool reverse;				

	/** Indicates odd, even, or all pages to be printed within the range. 
	It is only meaningful when the <code>firstPage</code> and <code>lastPage</code> parameters are used. 
	It can be either PDAllPages, PDEvenPagesOnly, or PDOddPagesOnly.*/
	ASInt32				pageSpec;

	/** Deprecated. Set to <code>0</code> and use <code>rasterData</code> instead.
		The transparency level reflects the pull-down on the Advanced print dialog box for 
		controlling how much rasterization should be performed when flattening transparent objects 
		during printing.

		<p>Possible values:</p>
		<TABLE rules="all" cellspacing="1">
		<TR><TH>Value</TH><TH>Description</TH></TR>
		<TR><TD><code>1</code></TD><TD>The entire page will be rasterized. Use this setting for printing or exporting complex pages with many
			transparent objects. It is ideal for fast output at low resolution; higher resolution will yield higher quality but
			increase processing time. The size of saved files or print spool files may be large.</TD></TR>
		<TR><TD><code>2</code></TD><TD>It maintains simpler vector objects, but rasterizes more complex areas involving transparency. It is ideal for
			artwork with only a few transparent objects. Some printers may yield rough transitions between bordering
			vector and raster objects and make hairlines appear thicker. It is appropriate for low memory systems.</TD></TR>
		<TR><TD><code>3</code></TD><TD>It maintains most objects as vector data, but rasterizes very complex transparent regions. It is generally the best
			setting for printing and exporting most pages. With some printers, it improves transition issues between
			bordering vector and raster objects.</TD></TR>
		<TR><TD><code>4</code></TD><TD>It maintains most of the page content as vectors, rasterizing only extremely complex areas. It produces
			high quality output that is generally resolution-independent. Higher occurrences of transparent regions
			will increase processing time. With some printers, it improves transition issues between bordering vector
			and raster objects.</TD></TR>
		<TR><TD><code>5</code></TD><TD>The entire page is printed or exported as vector data, to the greatest extent possible. This produces the
			highest quality resolution-independent output. Processing of complex pages may be very time- and
			memory-intensive.</TD></TR>
		</TABLE>
	*/
	ASInt32		transparencyLevel;	

	/** Represents the name of the destination profile to use when doing host-based color management.
	*/
	char destProfile[256];

	/** */
	AVPageSize pageSize;

	/** If <code>NULL</code>, it uses default values. */
	AVDocPrintTileData tileData;  

	/** If <code>NULL</code>, it uses default values.  */
	AVDocPrintRasterizeData rasterData; 

	/** If <code>NULL</code>, it uses default values.  */
	AVDocPrintOverrideData overrideData;

	/** The area (in pts) of the page(s) to print.  If <code>NULL</code>, print the whole page. */
	ASFixedRect	*selectRect;


	/** The optional content context to use. If <code>NULL</code>, use the current on-screen OC state, but apply print-
		specific AutoState changes from the default <code>occonfig</code> object's AS entry 
	*/
	PDOCContext ocContext; 
	/** A short note to the user that appears in the print dialog box. */
	ASUTF16Val  userNote[kPrintUserNoteLen]; 


	/** A font and resource Policy, such as kAVResPolicySendAtStart. It must be one of AVResourcePolicy.
		@see AVResourcePolicy 
	*/
	AVResourcePolicy resPolicy; 
	/** Determines which printer marks should be emitted, such as kAVCropMarks and so on. */
	ASUns32 marksFlags;

	/** N-up printing control parameters. If <code>NULL</code>, it uses default values. */
	AVDocPrintNupData nUpData;

	/** When <code>marksFlags</code> is non-zero, use <code>marksStyle</code> to determine which printer mark style to use.
	See <code>marksStyleType</code> (makes kAVEasternStyleMarks obsolete) */	
	ASInt32 marksStyle;
	
	/** Determines whether the user cancelled the print dialog box. */
	ASBool printDialogWasCancelled;
	
	/** The parent window of the dialog box (ignored on the Mac platform). It may be <code>NULL</code>. */
	AVWindow parentWindow;		

    /** Represents the name of the proofing profile when doing proofing. */
    char proofProfile[256];
	char *ppdPath;
	/** If <code>markStyle >= kLastMarkType</code>, <code>customMarksFileName</code> should be a valid file name 
	representing a valid .mrk file for custom printer marks. */
	ASPathName customMarksFileName;	
	/** Specify the number of copies with which to prepopulate the print dialog box. It may be ignored in certain cases. */
	ASInt32 numCopies;
	/** Specify the duplex request. */
	AVPrintDuplexType duplexType;
} AVDocPrintParamsRec;
#endif

/** @ingroup EmitFlags */
typedef struct _t_AVDocPrintSepsParams *AVDocPrintSepsParams;

#if (ACRO_SDK_LEVEL >= 0x00060000)

/* The AVPrintTrapType enumeration was added for Acrobat 8. */
enum {
/** @ingroup EmitFlags */
kAVPrintTrapNone = 0x01,
/** @ingroup EmitFlags */
kAVPrintTrapOnHost = 0x02, /* NOT SUPPORTED in Acrobat 7 */
/** @ingroup EmitFlags */
kAVPrintTrapInRIP = 0x04	/* requires in-RIP separations to be on */
};
typedef ASEnum8 AVPrintTrapType;
/**
	A structure specifying color separation printing parameters 
	used by AVDocPrintSeparations(). 
	@see AVDocPrintSeparations 
	@ingroup EmitFlags 
*/
typedef struct _t_AVDocPrintSepsParams 
{
	/** The size of the data structure. It must be set to <code>sizeof(AVDocPrintSepsParamsRec)</code>. */
	ASSize_t size;
	/** The document for which to print color separations.  */
	AVDoc avDoc;
	/** <code>firstPage</code>, <code>lastPage</code>, <code>psLevel</code>, <code>binaryOk</code>, and <code>shrinkToFit</code> are used if 
	    <code>emitToPrinter</code> or <code>emitToFile</code> is <code>true</code>.
	*/
	/** The first page to be printed. The first page number is <code>0</code>. If <code>-1</code>, all pages are printed. */
	ASInt32 firstPage;						
	/** The last page to be printed. This is ignored if the <code>firstPage</code> is <code>-1</code>. */
	ASInt32 lastPage;						

	/** The method creates an output file for each plate for each 
		page, using the <code>fileSysName</code> for the 
		file system, and the <code>filePathName</code> as the root file name 
		for each file. It appends the page number followed by the colorant 
		name to each output file name. If <code>filePathName</code> is not a 
		valid path name to a file to which Acrobat can open and write, 
		the method raises an exception using the value returned 
		by ASFileSysOpenFile().
	*/
	ASAtom fileSysName;					
	/** The method creates an output file for each plate for each 
		page, using the <code>fileSysName</code> for the 
		file system, and the <code>filePathName</code> as the root file name 
		for each file. It appends the page number followed by the colorant 
		name to each output file name. If <code>filePathName</code> is not a 
		valid path name to a file to which Acrobat can open and write, 
		the method raises an exception using the value returned 
		by ASFileSysOpenFile().
	*/
	ASPathName filePathName;
	
	/* Parameters for emission of PS Level 1 Color Separations and EPS, or vanilla PS.
	** Creates and writes to filePathName (may not be <code>NULL</code>).
	** Does NOT use system printer driver.
	** Only has partial font emitting capabilities on some platforms:
	** 	Mac:	embedded and system Type 1 fonts only; no TrueType or substitution fonts.
	**	Win:	embedded and system Type 1 fonts only; no TrueType or substitution fonts.
	**	UNIX:	all fonts
	*/
	/** Not used. */
	ASEnum8 emitFileOption;					
	
	/* More emit options. */
	/** Additional emit options. It must be one of the Emit Flags. 
		@ref EmitFlags
	*/
	ASUns32	emitFlags;		
	
	/** Not used. */
	AVPageSize pageSize;
	/** <code>NULL</code> uses default values. */
	AVDocPrintRasterizeData rasterData; /* If <code>NULL</code>, it uses default values */
	/** <code>NULL</code> uses default values.  */
	AVDocPrintOverrideData overrideData; /* If <code>NULL</code>, it uses default values */
	/** The separations specification parameter structure. */
	PDHostSepsSpec sepsSpec;
	/** If <code>true</code>, generate in-RIP seps. */
	ASBool inRip;					
	/** For Acrobat 8, <code>trapType</code> controls the type of trapping desired.
		@see AVPrintTrapType 
	*/
	ASInt32 trapType;

	/** Optionally used if <code>interactive</code>, <code>embedded</code>, or <code>emitToPrinter</code> is <code>true</code>. 
		If it is <code>NULL</code>, a default system printer is used. 
		If it is non-<code>NULL</code>, <code>printerSpec</code> is a platform-specific value. 
		It must be an ASPlatformPrinterSpec.
	*/
	ASPlatformPrinterSpec printerSpec;	

}
AVDocPrintSepsParamsRec;

#endif

/************************************************************************************\
|*																					*|
|*									Transition Stuff								*|
|*																					*|
\************************************************************************************/


/**
	A data structure containing callbacks that implement a transition 
	handler. The callbacks implement the transition handler 
	functions. 
	@see AVAppRegisterTransHandler 
*/
typedef struct _t_AVTransHandler *AVTransHandler;

/**
	A platform-dependent data structure for a transition. 

	<p>In general, a transition port specifies a bitmap and a rectangle 
	describing the portion of the bitmap affected by the transition. 
	The transition handler's AVTransHandlerExecuteProc() callback 
	must copy all the bits from the source port's bitmap within 
	the source port's rectangle to the area in the destination 
	port's bitmap described by the destination port's rectangle. 
	The source and destination ports' rectangles are guaranteed 
	to be equal in size. </p>
	@see AVTransHandlerExecuteProc 
*/
typedef struct _t_AVTransitionPort {
	/** */
	void 	 		*reserved;
	/** Reserved. Do not alter. */
	AVRect32		rect32;		
#if WIN_PLATFORM

	/** */
	HDC			hDC;

	/** */
	RECT		rect;
#elif MAC_PLATFORM
	int			Acrobat8ForMacDoesNotSupportTheAVTransitionPort;
	int			PleaseContactDeveloperSupportIfThisIsAnIssueForYou;
#elif UNIX_PLATFORM
	void*		port;
	void*		rect;
#elif OS2_PLATFORM
	HPS		hPS;
	RECTL		rect;
#endif
} AVTransitionPortRec, *AVTransitionPort;
	


/**
	A callback for AVTransHandler. It gets the transition type serviced 
	by this handler. The handler for a given transition is found 
	by comparing the result of PDTransGetSubtype() to the value 
	returned by the registered transition handler's AVTransHandlerGetTypeProc() 
	callbacks. 
	@param avth IN/OUT The transition handler. 
	@return The type of transition handler, which may be one of the types 
	provided in the Acrobat viewer or a new type registered 
	by a plug-in. 
	@see PDTransGetSubtype 

*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *AVTransHandlerGetTypeProc)(AVTransHandler avth);


/**
	A callback for AVTransHandler. It executes the specified transition. 
	The transition handler is responsible for copying the pixels 
	specified by <code>srcTP</code> to the location specified by <code>dstTP</code>. In 
	the process, the handler can create any visual effect you 
	desire, as long as the source pixels are eventually copied 
	over the destination pixels in the end. 

	<p>The handler should, if possible, execute the visual effect 
	in the number of seconds specified by duration. </p>

	<p>The implementation will ensure that the source and destination 
	rectangles are the same size, though their corners may not 
	coincide. </p>
	@param avth IN/OUT The transition handler. 
	@param trans IN/OUT The transition to execute. 
	@param srcTP IN/OUT Source transition port. 
	@param dstTP IN/OUT Destination transition port. 
	@param duration IN/OUT Duration of the transition, in seconds. 
	
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVTransHandlerExecuteProc)(AVTransHandler avth, PDTrans trans,	AVTransitionPort srcTP, AVTransitionPort dstTP, ASFixed duration);


/**
	A callback for AVTransHandler. It retrieves the user interface 
	name for an existing PDTrans. For example, if the transition 
	type is <code>'Wipe'</code> and the direction is <code>180</code>, AVTransHandlerGetUINameProc() 
	would return <code>"Wipe Left"</code>, localized. 

	<p>A transition handler can handle several distinct transitions. 
	For example, the <code>"Wipe"</code> transition handler can create four 
	distinct effects: wipe left, wipe right, wipe up, and wipe 
	down. </p>

	<p>The transition setting dialog box creates a separate user
	interface entry for each distinct transition. It determines 
	both the number and names of the distinct transition types 
	by repeatedly calling each transition handler's AVTransHandlerGetUINameProc() 
	callback, starting with an item number of <code>0</code> and increasing 
	until the AVTransHandlerGetUINameProc() callback returns an 
	empty string. </p>

	<p>The string returned by AVTransHandlerGetUINameProc() should 
	be localized. </p>

	<p>The AVTransHandlerGetUINameProc() is used to enumerate the 
	entire list of supported transition effects that the handler 
	wishes to display in the popup menu. For example, <code>"Wipe 
	Left"</code> for <code>item == 0</code>, <code>"Wipe Right"</code> for <code>item == 1</code>, and so 
	on). </p>
	@param avth IN/OUT The transition handler. 
	@param trans IN/OUT The transition whose name is obtained. 
	@param buffer IN/OUT (Filled by the callback) The user interface 
	name of the transition. 
	@param bufLen IN/OUT The length of <code>buffer</code> in bytes. 
	@return The number of characters copied into <code>buffer</code>. 
	@see AVTransHandlerGetItemUINameProc 
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVTransHandlerGetUINameProc)(AVTransHandler avth, PDTrans trans, char* buffer, ASInt32 bufLen);


/**
	A callback for AVTransHandler. 

	<p>A transition handler can handle several distinct transitions. 
	For example, the <code>Wipe</code> transition handler can create four 
	distinct effects: wipe left, wipe right, wipe up, and wipe 
	down. </p>

	<p>The transition setting dialog box should create a separate 
	user interface entry for each distinct transition. It determines 
	both the number and names of the distinct transition types 
	by repeatedly calling each transition handler's AVTransHandlerGetItemUINameProc() 
	callback, starting with an item number of <code>0</code> and increasing 
	until AVTransHandlerGetItemUINameProc ()returns an empty string. </p>

	<p>Thus, when the transaction handler is selected from the list, 
	this callback is called. The transition handler should fill 
	in the Type and S fields. AVTransHandlerGetItemUINameProc() 
	should fill in any default values. This information is passed 
	into the AVTransHandlerDoPropertiesProc() in the form of a 
	PDTrans if that callback exists. </p>
	@param avth IN/OUT The transition handler. 
	@param item IN/OUT The item number. 
	@param buffer IN/OUT (Filled by the callback) The name of the 
	transition in the user interface. This string should be 
	localized. 
	@param bufLen IN/OUT Length of <code>buffer</code> in bytes. 
	@return The number of characters copied into <code>buffer</code>. 
	@see AVTransHandlerGetUINameProc 
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVTransHandlerGetItemUINameProc)(AVTransHandler avth, ASInt32 item, char* buffer, ASInt32 bufLen);

/**
	A callback for AVTransHandler.

	<p>A transition has different variations but the same type of action.
	For example, the Wipe transition handler can create four 
	distinct effects: wipe left, wipe right, wipe up, and wipe 
	down. </p>

	<p>The transition setting dialog box should create a list of effects
	for each distinct transition. It will determine the variation according to the
	transition type (for example, left, right, up, down).</p>

	<p>When the application is building the user interface, the dialog box will call
	GetItemDirectionUIName() repeatedly for the name of the effect.</p>
	@param avth IN/OUT The transition handler.
	@param item IN/OUT The item number.
	@param buffer (Filled by the callback) The name of the 
	variation in the user interface.
	@see AVTransHandlerGetItemUINameProc
*/

typedef ACCBPROTO1 void (ACCBPROTO2 *AVTransHandlerGetItemDirectionUINameProc)(AVTransHandler avth, ASInt32 item, ASText buffer);

/**
	A callback for AVTransHandler.

	<p>A transition has different variations but the same type of action.
	For example, the Wipe transition handler can create four 
	distinct effects: wipe left, wipe right, wipe up, and wipe 
	down. </p>

	<p>For some of these effects, there is an opposite effect.
	For example, Push Left is the opposite of Push Right.</p>

	<p>When the application is building the user interface, the dialog box will call
	GetBiDirEnabled() to check if the transition type's effects have an opposite effect.</p>

	@param avth IN/OUT The transition handler.
	@return A boolean value that determines whether the transition can use a bidirectional setting.
*/

typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVTransHandlerGetBiDirEnabledProc)(void);

/**
	A callback for AVTransHandler.

	<p>When a transition is being performed, the animation can slow down at the end of 
	the transition.</p>

	<p>When the application is building the user interface, the dialog box will call
	GetSmoothActionEnabled() to check if the transition type's effects have an opposite effect.</p>

	@param avth IN/OUT The transition handler.
	@return A boolean value that determines whether the transition can use a smooth action setting.
*/

typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVTransHandlerGetSmoothActionEnabledProc)(void);

/**

	Returns the canonical name for the item. It should return ASAtomNull if the item number is invalid.
	This was added in Acrobat 5.0 so that different transitions could be handled in a language-independent manner. 
	If this call is not implemented, then it is acceptable to generate a 
	synthetic name from the transition type and the item index.
	For example, the <code>"Glitter"</code> trans handler should return a canonical name such as <code>"GlitterDown"</code>. 
	If this call is not implemented, then the name will be the trans handler type <code>"Glitter"</code>, 
	plus a period, plus the item number (for example, <code>"Glitter.0"</code>). 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *AVTransHandlerGetItemNameProc)(AVTransHandler avth, ASInt32 item);

/** 
*/
typedef ACCBPROTO1 ASAtom (ACCBPROTO2 *AVTransHandlerGetNameProc)(AVTransHandler avth, PDTrans trans);


/**
	A callback for AVTransHandler. This method should set default 
	values in the transition dictionary, <code>transDict</code>. 

	<p>As soon as the handler is selected from the list, AVTransHandlerInitTransDictProc() 
	is called. This function should fill in the Type and S fields 
	of <code>transDict</code>. AVTransHandlerInitTransDictProc() should also 
	fill in any default values. This information is passed to 
	AVTransHandlerDoPropertiesProc() in the form of a PDTrans 
	if AVTransHandlerDoPropertiesProc() exists. </p>

	<p>Normally the Type and S fields are filled in when the transition 
	is created via PDTransNewFromCosDoc(). The implementation 
	then calls AVTransHandlerInitTransDictProc() and AVTransHandlerCompleteTransDictProc() 
	immediately on the newly created PDTrans. </p>
	@param avth The transition handler. 
	@param transDict The transition dictionary to set.
	@see AVTransHandlerCompleteTransDictProc 
	@see PDTransNewFromCosDoc 
*/
typedef ACCBPROTO1 void	(ACCBPROTO2 *AVTransHandlerInitTransDictProc)(AVTransHandler avth, CosObj transDict);

/**
	A callback for AVTransHandler. This method is called after 
	the user has selected a distinct transition. The transition 
	handler must fill in any dictionary items necessary to create 
	the effect specified by the <code>uiName</code> passed in. For example, 
	if the <code>Wipe</code> transition handler is passed a <code>uiName</code> of 
	<code>"Wipe Left"</code>, it would set the Dir key in <code>transDict</code> to the 
	value <code>180</code>. 

	<p>AVTransHandlerCompleteTransDictProc() should fill in standard 
	information like direction, dimension, motion, and so forth 
	(information gathered entirely from the user interface name). Other 
	specific information should be filled in by AVTransHandlerDoPropertiesProc. </p>
	
	@param avth IN/OUT The transition handler. 
	@param name IN/OUT The user interface name of the transition. 
	@param transDict IN/OUT The transition dictionary to set. 
	@see AVTransHandlerDoPropertiesProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVTransHandlerCompleteTransDictProc)(AVTransHandler avth, const char *name, CosObj transDict);

/**
	A callback for AVTransHandler. This method is called when 
	the user clicks the button in the transition settings dialog box. 
	This allows the transition to bring up its own custom dialog box 
	allowing the user to further specify the desired transition 
	effect. 

	<p>Once the user selects a transition effect from the popup 
	menu, the viewer immediately creates a transition (using 
	PDTransNewFromCosDoc() or PDTransNew()), and calls AVTransHandlerInitTransDictProc() 
	and AVTransHandlerCompleteTransDictProc(). If the handler 
	provides both an AVTransHandlerDoPropertiesProc() and AVTransHandlerGetButtonTextProc() 
	callbacks, the dialog box displays a button. When the user 
	clicks on the button, the viewer calls the handler's AVTransHandlerDoPropertiesProc() 
	callback. <code>DoProperties</code> is responsible for making any needed 
	alterations to the transition; <code>InitTransDict</code> and <code>CompleteTransDict</code> 
	are not called after <code>DoProperties</code>. </p>

	<p>After the user clicks OK in the dialog box, <code>trans</code> is filled 
	in using the supplied data. </p>
	@param avth IN/OUT The transition handler. 
	@param name IN/OUT The user interface name for the transition 
	handled by <code>avth</code>. 
	@param trans IN/OUT The PDTrans to initialize. 
	@see AVTransHandlerCompleteTransDictProc 
	@see AVTransHandlerInitTransDictProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVTransHandlerDoPropertiesProc)(AVTransHandler avth, const char *name, PDTrans trans);

/**
	(Unused) A callback for AVTransHandler. 
	@param avth IN/OUT The transition handler. 
	@param buffer IN/OUT (Filled by the callback) The instruction 
	text. 
	@param bufLen IN/OUT Length of <code>buffer</code> in bytes. 
	@return The number of characters copied into <code>buffer</code>. 
	@see AVActionGetInstructionsProc 
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVTransHandlerGetInstructionsProc)(AVTransHandler avth, char *buffer, ASInt32 bufLen);

/**
	A callback for AVTransHandler. It gets a localized string that 
	appears in the button on the transition settings dialog 
	box. If AVTransHandlerGetButtonTextProc() is <code>NULL</code> or the string 
	it returns is empty, no button will appear. 
	@param avth IN/OUT The transition handler. 
	@param buffer IN/OUT (Filled by the callback) The button text. 
	
	@param bufLen IN/OUT Length of <code>buffer</code> in bytes. 
	@return The number of characters copied into <code>buffer</code>. 
	@see AVTransHandlerDoPropertiesProc 
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVTransHandlerGetButtonTextProc)(AVTransHandler avth, char *buffer, ASInt32 bufLen);

/**
	A callback for AVTransHandler. Gets a localized string that 
	appears above the button on the transition settings dialog 
	box. 
	@param avth IN/OUT The transition handler. 
	@param buffer IN/OUT (Filled by the callback) The string text 
	appearing above the button. 
	@param bufLen IN/OUT Length of <code>buffer</code> in bytes. 
	@return The number of characters copied into <code>buffer</code>. 
	@see AVTransHandlerGetStringTwoTextProc 
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVTransHandlerGetStringOneTextProc)(AVTransHandler avth, char *buffer, ASInt32 bufLen);

/**
	A callback for AVTransHandler. It gets a localized string that 
	appears below the button on the transition settings dialog 
	box. 
	@param avth IN/OUT The transition handler. 
	@param buffer IN/OUT (Filled by the callback) The string text 
	appearing below the button. 
	@param bufLen IN/OUT Length of <code>buffer</code> in bytes. 
	@return The number of characters copied into <code>buffer</code>. 
	@see AVTransHandlerGetStringOneTextProc 
*/
typedef ACCBPROTO1 ASInt32 (ACCBPROTO2 *AVTransHandlerGetStringTwoTextProc)(AVTransHandler avth, char *buffer, ASInt32 bufLen);


/**
	A data structure containing callbacks that implement a transition 
	handler. The callbacks implement the transition handler 
	functions. 
	@see AVAppRegisterTransHandler 
*/
typedef struct _t_AVTransHandler
{

	/** The size of the data structure. It must be set to <code>sizeof(AVTransHandlerRec)</code>. */
	ASSize_t 							size;

	/** Return the transition handler type (for example, <code>"Wipe"</code>). */
	AVTransHandlerGetTypeProc			GetType; 

	/** Given this PDTrans, execute this transition. */
	AVTransHandlerExecuteProc			Execute; 

	/** Given this PDTrans, determine the <code>UIName</code>. */
	AVTransHandlerGetUINameProc			GetUIName; 

	/** Return the <code>UIName</code> for the Nth item, <code>NULL</code> if N is invalid. */
	AVTransHandlerGetItemUINameProc		GetItemUIName; 

	/** Fill this <code>dict</code> with generic information if necessary. */
	AVTransHandlerInitTransDictProc		InitTransDict; 

	/** Fill this <code>dict</code> with specific, standard information. */
	AVTransHandlerCompleteTransDictProc	CompleteTransDict; 

	/** The proc to bring up the user interface window. Fill in the PDTrans for non-standard plug-ins that have additional information. */
	AVTransHandlerDoPropertiesProc		DoProperties; 

	/** <code>message1</code> for non-standard plug-ins that have additional information. */
	AVTransHandlerGetInstructionsProc	GetInstructions; 

	/** Button text for non-standard plug-ins that have additional information. */
	AVTransHandlerGetButtonTextProc 	GetButtonText; 

	/** <code>message2</code> for non-standard plug-ins that have additional information. */
	AVTransHandlerGetStringOneTextProc 	GetStringOneText; 

	/** <code>message3</code> for non-standard plug-ins that have additional information. */
	AVTransHandlerGetStringTwoTextProc 	GetStringTwoText;

	/** Acrobat 5: given this PDTrans, determine its LI name. This is used for non-standard plug-ins that have additional information. */
	AVTransHandlerGetNameProc			GetName;	

	/** Acrobat 5: return the LI name for the Nth item, ASAtomNull if N is invalid. This is used for non-standard plug-ins that have additional information. */
	AVTransHandlerGetItemNameProc		GetItemName;	

	/** Acrobat 6: determine if this transition is OK to use with the Random transition. This is used for non-standard plug-ins that have additional information. */
	ASBool								discludeFromRandom; 

	/** Acrobat 7: Determine if this transition is OK to set through the user interface.  Certain effects, such as /Fly, do not make sense in the general case. */
	ASBool								discludeFromUI;

	/** Acrobat 8 */
	AVTransHandlerGetItemDirectionUINameProc	GetItemDirectionUIName;

	/** Acrobat 8: Determines whether this transition has a bidirectional counterpart. */
	AVTransHandlerGetBiDirEnabledProc			GetBiDirEnabled;

	/** Acrobat 8: Determines whether this transition uses Smooth Action. */
	AVTransHandlerGetSmoothActionEnabledProc	GetSmoothActionEnabled;

} AVTransHandlerRec;


/**
	A callback for AVAppEnumTransHandlers. It is called once for 
	each transition handler. 
	@param avth IN/OUT The transition handler. 
	@param vClientData IN/OUT User-supplied data that was passed in 
	the call to AVAppEnumTransHandlers(). 
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	
	@see AVAppEnumTransHandlers 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVTransHandlerEnumProc)(AVTransHandler avth, void *vClientData);

#if !MAC_PLATFORM || (MAC_PLATFORM && !AS_ARCH_64BIT)
/*------------------------------------------------------------------------------
	System Font Stuff (Mac only)
    DEPRECATED
------------------------------------------------------------------------------*/
/* AVSystemFont flags bitfield values */


/** Type 1 font. 
  	@ingroup AVSystemFontFlags
*/
#define kFontIsType1		0x0001

/** Multiple Master font. 
  	@ingroup AVSystemFontFlags
*/
#define kFontIsMMMaster		0x0002

/** Multiple Master font (a completely specified instance).
  	@ingroup AVSystemFontFlags
*/
#define kFontIsMMInstance	0x0004

/** TrueType font. 
  	@ingroup AVSystemFontFlags
*/
#define kFontIsTrueType		0x0008

/** Character ID Type 0 font. 
  	@ingroup AVSystemFontFlags
*/
#define kFontIsCIDFontType0	0x0010

/**  OCF Type 1 font. 
  	@ingroup AVSystemFontFlags
*/
#define kFontIsOCFType1		0x0020

/**
	(Mac OS only, present only in Acrobat 3.0 or later) System 
	font. 
	@see AVAppEnumSystemFonts 
*/
typedef struct _t_AVSystemFont {

	/** Mac OS FOND id. */
	short fondID;	

	/** Mac OS style value: <code>normal</code>, <code>italic</code>, <code>bold</code>, or <code>bold | italic</code>. */
	short styleID;	

	/** Must be one of the AVSystemFont <code>Flags</code>. 
		@see AVSystemFontFlags 
	*/
	ASUns32 flags;	

	/** PostScript name or TrueType-styled name. */
	ASAtom pdfFontName;	
} AVSystemFontRec, *AVSystemFont;

/**
	(Mac OS only). A callback for AVAppEnumSystemFonts(). It 
	is called once for each system font. 
	@param systemFont IN/OUT The AVSystemFont currently being enumerated. 
	
	@param clientData IN/OUT User-supplied data that was passed in 
	the call to AVAppEnumSystemFonts(). 
	@return <code>true</code> to continue enumeration, <code>false</code> to halt enumeration. 
	
	@see AVAppEnumSystemFonts 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVSystemFontEnumProc)(AVSystemFont systemFont, void *clientData);
#endif /* #if !MAC_PLATFORM || (MAC_PLATFORM && !AS_ARCH_64BIT) */


/**
	A structure used by AVDocDoSaveAsWithParams() containing parameters 
	that a client wishing to save a file might want to specify. 
	It is passed in by address to AVDocDoSaveAsWithParams() with 
	a size field so that current clients replacing AVDocDoSaveAsWithParams() 
	will not break in the future if new open specifications are 
	provided. 
	@see AVDocDoSaveAsWithParams 
*/
typedef struct _t_AVDocSaveParams
{
	/** The size of the data structure. It must be set to <code>sizeof(AVDocSaveParamsRec)</code>. */
	ASSize_t 		size;

	/** Use the standard file Save dialog box. */
	ASBool			useSaveDialog;

	/** (Acrobat 5.0 and later) Do not use "convert from PDF" handlers. */
	ASBool			dontAllowConversions;

	/** The ID of the default filter (<code>NULL</code> means PDF). */
	const char		*filterID;

	/** Bypass the dialog box and use the default path, etc. */
	ASBool			useDefaults;
}
AVDocSaveParamsRec, *AVDocSaveParams;



/**
	A structure that contains a progress monitor, a cancel procedure, 
	and an error report procedure. 
	@see AVConversionConvertToPDFWithHandler 
	@see AVConversionConvertFromPDFWithHandler 
	@see AVConversionConvertToPDF 
*/
typedef struct _t_AVStatusMonitorProcs {

	/** The size of this structure. Set it to <code>sizeof(AVStatusMonitorProcsRec)</code>. */
	ASSize_t			size;


	/** (May be <code>NULL</code>) The progress monitor. In general, clients of this structure test members for <code>NULL</code>. If a member 
		is found, they do not do anything. 
	*/
	ASProgressMonitor	progMon;

	/** The progress monitor client data that was acquired with the progress monitor. */
	void				*progMonClientData;

	/**
	This call has been replaced by ASCancelProc(). 

	<p>This is a callback to check for cancelling operations. A <code>CancelProc</code>
	is typically passed to some method that takes a long time 
	to complete. At frequent intervals, the method calls the 
	<code>CancelProc</code>. If it returns <code>true</code>, then the method cancels 
	its operation; if it returns <code>false</code>, it continues.</p> 
	@param clientData User-supplied data that was passed to 
	the <code>CancelProc</code>.
	@return <code>true</code> if the processing is cancelled, <code>false</code> otherwise. 
	@see PDFLPrintCancelProc (Only available with PDF Library SDK) 
	
	@see AVAppGetCancelProc 
	*/
	ASCancelProc		cancelProc;

	/** The cancellation procedure client data that was acquired with the cancellation procedure. */
	void				*cancelProcClientData;

	/** (May be <code>NULL</code>) The report procedure. In general, clients of this structure test members for <code>NULL</code>. 
		If a member is found, they do not do anything.
	*/
	ASReportProc		reportProc;

	/** The report procedure client data that was acquired with the report procedure.*/
	void				*reportProcClientData;
} AVStatusMonitorProcsRec, *AVStatusMonitorProcs;

/*********************************************************
 * AVOpenSaveDialog definitions
 *********************************************************/


/**
	A structure to handle file types and/or extensions in open 
	and save dialog boxes. 
	@see AVAppChooseFolderDialog 
	@see AVAppOpenDialog 
	@see AVAppSaveDialog 
*/
typedef struct _t_AVFileDescRec{

	/** A string up to 32 characters in length, for file extension. Use <code>\ 0</code> on Windows for do not care (ignored on Windows only 
		if <code>\\0</code> is used). 
	*/
	char	extension[32];

	/** File type (used on Mac OS only). Use <code>0</code> for do not care. */
	ASUns32	macFileType;

	/** File creator (used on Mac OS only). Use <code>0</code> for do not care. */
	ASUns32	macFileCreator;
} AVFileDescRec;

/*
Examples of AVFileDescRec's:

HTMLFileDesc1:
"html"		- extension
'TEXT'	- type
0		- creator

HTMLFileDesc2:
"htm"	- extension
'TEXT'	- type
0		- creator

TextFileDesc1:
""		- extension
'TEXT'	- type
0		- creator

TextFileDesc2:
"txt"	- extension
'TEXT'	- type
0		- creator
*/


/**
	A structure to hold a series of file type descriptors that 
	form a file filter for an open or save dialog box. 
	@see Various 
	@see AVAppChooseFolderDialog 
	@see AVAppOpenDialog 
	@see AVAppSaveDialog 
*/
typedef struct _t_AVFileFilterRec {

	/** Localized string describing this filter. It is the name that appears in the open or save dialog box. */
	ASText			filterDescription;

	/** An array of AVFileDescRec objects. A single AVFileFilterRec can have as many AVFileDescRec objects as needed. On Windows, the 
	file name is concatenated with the extension string of the relevant AVFileDescRec in the Open and Save dialog boxes. On 
	Mac OS, the <code>fileDescription</code> string is used in the File Open and Save dialog boxes, and the AVFileDescRec objects are used 
	to filter which files are displayed when that AVFileFilterRec is selected. */
	AVFileDescRec	*fileDescs;

	/** The number of AVFileDescRec objects in <code>fileDescs</code>. */
	AVArraySize		numFileDescs;
} AVFileFilterRec;

/**
	An enumerated list of open and save dialog box flags. 
*/
enum {

	/** Use the "All Files (*.*)" file filter for the dialog box. It is meaningful only for an open dialog box.*/
	kAVOpenSaveAllowAllFlag					= 1 << 0,	

	/** Allow multiple files to be opened through this dialog box. It is meaningful only for an open dialog box. */
	kAVOpenSaveAllowMultiple				= 1 << 1,	

	/** Allow file systems other than the default to be used to open the file(s). */
	kAVOpenSaveAllowForeignFileSystems		= 1 << 2,

	/** Adds a Settings button to the dialog box. It is meaningful for open and save dialog boxes. */
	kAVOpenSaveAllowSettingsButton			= 1 << 3,	

	/** This is meaningful only for Open dialog boxes with more than one passed filter.  */
	kAVOpenSaveMergeTogetherPassedFilters	= 1 << 4,

	/** Do not add the Make New Folder push button. It is only meaningful for the Browse For Folder dialog box. **/
	kAVBrowseForFolderNoNewFolderButton			= 1 << 5,

	/** Do Not Allow opening files from Cloud.**/
	kAVDoNotAllowCloudConnections				= 1 << 6,

	/** Allow Acrobat.com Entry points **/
	kAVAllowADCAccess					= 1 << 7
};
typedef ASUns32 AVOpenSaveDialogFlags;


/**
	A client can provide this optional callback if you wish 
	to control whether the settings button in the open or save 
	dialog box is enabled or disabled. If you do not provide 
	this callback function, then the state of the settings button, 
	enabled or disabled, will be determined by whether the conversion 
	handler has a settings proc. 
	@param currentFilter IN/OUT The currently selected filter in the 
	dialog box. 
	@param data IN/OUT <code>void*</code> of <code>clientData</code>, which is the last member 
	of the AVOpenSaveDialogParamsRec structure. 
	@return <code>true</code> if the Settings button should be enabled, <code>false</code> otherwise. 
	
	@see AVOpenSaveDialogSettingsExecuteProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVOpenSaveDialogSettingsComputeEnabledProc)(AVFileFilterRec *currentFilter, void *data);

/**
	A client provides this optional callback to decide what 
	action is taken when the user clicks on the settings button. 
	The function is called back with the currently selected 
	filter.  
	
	@param currentFilter IN/OUT The currently selected filter in the 
	dialog box. 
	@param data IN/OUT <code>void*</code> of <code>clientData</code>, which is the last member 
	of the AVOpenSaveDialogParamsRec structure. 
	@return A boolean value.
	@see AVOpenSaveDialogSettingsComputeEnabledProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVOpenSaveDialogSettingsExecuteProc)(AVFileFilterRec *currentFilter, void *data);

#if (ACRO_SDK_LEVEL >= 0x00060000)

/**
	A structure defining the properties and callbacks related 
	to a file open/save dialog box. It is used for AVAppOpenDialog(), AVAppSaveDialog(), and AVAppChooseFolderDialog().
	@see AVAppOpenDialog 
	@see AVAppSaveDialog 
	@see AVAppChooseFolderDialog 
*/
typedef struct {								
	/** The size of this structure. Set it to <code>sizeof(AVOpenSaveDialogParamsRec)</code>. */
	ASSize_t    								size;   		

	/** A bitwise <code>OR</code> of the AVOpenSaveDialogFlags. */
	AVOpenSaveDialogFlags						flags;

	/** The parent window of the dialog box (ignored on Mac OS). It may be <code>NULL</code>. */
	AVWindow									parentWindow;		

	/** The title of the dialog box that is used for the prompt. It may be <code>NULL</code> for the default title. */
	ASText										windowTitle;	

	/** The title of the action button (Open, Save, or Choose). It may be <code>NULL</code> for the default title. */
	ASText										actionButtonTitle;	

	/** The title of the cancel button. It may be <code>NULL</code> for the default title. */
	ASText										cancelButtonTitle;	

	/** May be <code>NULL</code> if <code>flags</code> does not contain kAVOpenSaveAllowForeignFileSystems. */
	ASFileSys									initialFileSys;		

	/** Used to specify the initial location or selection. It may be <code>NULL</code> if the default location or selection is acceptable. */
	ASPathName									initialPathName;

	/** Ignored (may be <code>NULL</code>) for Open and ChooseFolder. For Save, the file name portion is used for the edit 
		field. It may be <code>NULL</code> on Windows, but is required on Mac OS. 
	*/
	ASText										initialFileName;	

	/** An array of AVFileFilterRec objects. It is ignored (may be <code>NULL</code>) for ChooseFolder. It may be <code>NULL</code> for Open <i>only</i> 
		if kAVOpenSaveAllowAllFlag is set. 
	*/
	AVFileFilterRec								**fileFilters;	

	/** The number of AVFileFilterRec objects in <code>fileFilters</code>. */
	AVArraySize									numFileFilters;		

	/** (Optional) Called to determine whether the Settings button should be enabled. 
		It may be <code>NULL</code>. It is ignored if kAVOpenSaveAllowSettingsButton is not set. 
	*/
	AVOpenSaveDialogSettingsComputeEnabledProc	settingsComputeEnabledProc;

	/** Called when the user clicks on the (enabled) Settings button. It may be <code>NULL</code>. It is ignored if 
		kAVOpenSaveAllowSettingsButton is not set.
	*/
	AVOpenSaveDialogSettingsExecuteProc			settingsExecuteProc;

	/** Data that is passed to the <code>settingsExecuteProc</code> callback. It is ignored if kAVOpenSaveAllowSettingsButton is not 
		set. 
	*/
	void										*settingsProcData;
} AVOpenSaveDialogParamsRec, *AVOpenSaveDialogParams;
#endif


/*********************************************************
 * AVAcquireSpecial definitions
 *********************************************************/

/*	AVAcquireSpecialFolderPathName and AVAcquireSpecialFilePathName. Use
	these routines to get a path to special folders that exist on the system.

	Valid combinations of cat/fld for these functions are detailed here:	
						kAVSCUser							kAVSCApp
	kAVSFRoot			User directory (1)					Viewer directory (9)
	kAVSFEBooks			User eBook license files (RMF) (2)	N/A
	kAVSFPreferences	User preferences (3)				N/A
	kAVSFSequences		User defined batch sequences (4)	App batch sequences (10)
	kAVSFDocuments		User documents (5)					N/A
	kAVSFJavaScript		User JavaScripts (6)				App JavaScripts (11)
	kAVSFStamps			User stamps folder (7)				App stamps folder (12)
	kAVSFDictionaries	User installed spelling dicts (8)	App installed dicts (13)
	kAVSFPlugIns		N/A									Plug-ins folder (14)
	kAVSFHelp			N/A									Help folder (15)
	kAVSFTemp			Temporary folder (16)				N/A									
	kAVSFMessages		User Messages folder (17)			Default Messages folder (18)
	kAVSFHelpLocale		Downloaded Adobe Reader Help (19)			Help Locale folder (20)
	kAVSFTouchUpFind	N/A									App TouchUp find folder (21)
	kAVSFOrganizerDatabase	Organizer Database directory	N/A
	kAVSFNavigators		User navigators						App navigators (multi-lingual)
	kAVSFNavigatorsLocalized	N/A							App navigators (localized)
	kAVSFMultimediaSkins	User multimedia skins			App multimedia skins
	kAVSFServices		User Services (22)					N/A
	kAVSFUICustomization User UI Customizations (23)		App UI Customizations (localized) (24)

	(1) User directory
		Windows: Documents and Settings/<user>/Application Data/Acrobat
	(2) User eBook license files (RMF)
		License files used by WebBUY to indicate ownership/rights of particular 
		PDF documents.
		Windows: Documents and Settings/<user>/Application Data/Acrobat/EBook
	(3) User preferences
		Should contain files full of preferences (e.g. ini or Mac prefs files).
		Generally we do not want the user mucking with these. If a plug-in wants to 
		provide regular preferences it should use the miIni.c interface which would
		map to pref files in this folder on the Mac and the registry on Windows.
		Windows: Documents and Settings/<user>/Application Data/Acrobat/Preferences
	(4) User batch sequences
		Custom batch scripts that the user has written/defined and saved.
		Windows: Documents and Settings/<user>/Application Data/Acrobat/Sequences
	(5) User documents
		The viewer and all plug-ins should default to opening and saving in this folder.
		Windows: Documents and Settings/<user>/My Documents
	(6) User JavaScripts
		JavaScripts written by the user (.js files) that are loaded at application launch.
		These are editable directly by the user and as such are not usually found in
		the same folder as kAVSFEBooks, kAVSFPreferences, or kAVSFSequences.
		Windows: Documents and Settings/<user>/My Documents/Acrobat/JavaScript
	(7) User stamps
		Custom rubber stamps that the user creates are stored in this folder.
		Windows: Documents and Settings/<user>/My Documents/Acrobat/Stamps
	(8) User dictionaries
		User installed dictionaries for the spell checker.
		Windows: Documents and Settings/<user>/My Documents/Dictionaries
	(9) Viewer root
		Location of the application. Sometimes needed to sniff for DLLs and other files
		that live at this level.
		Windows: Program Files/Adobe/Acrobat 5.0/<viewer>
	(10)Application batch sequences
		Batch sequences that are shipped with the product as examples.
		Windows: Program Files/Adobe/Acrobat 5.0/<viewer>/Sequences/<locale>
	(11)Application JavaScripts
		JavaScripts that are shipped with the product (AForm.js, AFString<lang>.js, Annots.js)
		Windows: Program Files/Adobe/Acrobat 5.0/<viewer>/plug-ins/EScript/JavaScripts
	(12)Application stamps
		Stamps that are shipped with the product.
		Windows: Program Files/Adobe/Acrobat 5.0/<viewer>/plug-ins/Annotations/Stamps
	(13)Application Dictionaries
		Dictionaries that are shipped with the product.
		Windows: Program Files/Adobe/Acrobat 5.0/<viewer>/plug-ins/Spelling/Dictionaries
	(14)Application plug-ins
		Where plug-ins are stored.
		Windows: Program Files/Adobe/Acrobat 5.0/<viewer>/plug-ins
	(15)Application help
		Windows: Program Files/Adobe/Acrobat 5.0/Help
	(16)Temp folder
		Windows: Windows\Temp
	(17)User Messages folder
		Windows: Documents and Settings/<user>/Application Data/Acrobat/Messages
	(18)App Messages folder
	    Windows: Program Files/Adobe/Acrobat 5.0/Messages
	(19)Downloaded Adobe Reader Help folder
		Used to store the full reader help file on systems that lock out access to 
		the application help folder.
		Windows: Documents and Settings/<user>/Application Data/Acrobat/Help/<Locale>
	(20)Application help locale
		Windows: Program Files/Adobe/Acrobat 5.0/Help/<Locale>
	(21)Application TouchUp/Find folder
		Where TouchUp stores find XML files.
		Windows: "Program Files/Adobe/Acrobat 5.0/<viewer>/plugins/TouchUp/Find"
	(22)User Services
		Where the service plugins (i.e. SPA) are dowmloaded
		Windows: Documents and Settings/<user>/Application Data/Acrobat/Services
	(23)User UI Customization
		Where files that control sets of user defined UI components are stored
		Windows: Documents and Settings/<user>/Application Data/Acrobat/UICustomization
	(24)App UI Customization
		Where files that provide additional arrangements of UI components are stored
		Windows: Program Files/Adobe/Acrobat 11.0/Acrobat/UICustomization/<locale>
*/


/**
	Categories of special folders on the system. Used with folder 
	types to locate folders. Note that some combinations of 
	AVSpecialCategory and AVSpecialFolder are not valid. See 
	AVSpecialError for a list of valid combinations. 
	@see AVAcquireSpecialFilePathName 
	@see AVAcquireSpecialFolderPathName 
*/
typedef enum {

	/** User folders. */
	kAVSCUser,

	/** Application folders. */
	kAVSCApp,
	
	/** Local (to this machine) domain */
	kAVSCLocal,

	/** Often used to tag the end of an enumeration with a specific value. */
	kAVSCLast
} AVSpecialCategory;


/**
	Special folder types on the system. It is used with folder categories 
	to locate folders. Note that some combinations of AVSpecialCategory 
	and AVSpecialFolder are not valid. See AVSpecialError for a list of valid 
	combinations. 
	@see AVAcquireSpecialFilePathName 
	@see AVAcquireSpecialFolderPathName 
*/
typedef enum {

	/** Viewer root: the location of the application. It is sometimes 
		needed to sniff for DLLs and other files that live at this 
		level.
	*/
	kAVSFRoot,

	/** User eBook license files (RMF) used by WebBUY to indicate ownership/rights of particular 
		PDF documents. 

	*/
	kAVSFEBooks,

	/** User preferences folder. It should contain preferences files (for example, ini or Mac OS prefs 
		files). Generally you do not want the user touching these. If a plug-in provides regular 
		preferences, it should use the <code>miIni.c</code> interface, which would map to pref files in this folder on 
		Mac OS and the registry on Windows. 
	*/
	kAVSFPreferences,

	/** User-defined batch sequences: Custom batch scripts that the 
		user has written/defined and saved. 
		Application batch sequences: Batch sequences that are shipped with the 
		product as examples.
	*/
	kAVSFSequences,

	/** User documents folder The viewer and all plug-ins should default to opening and saving in 
		this folder. 
		
	*/
	kAVSFDocuments,

	/** User JavaScripts folder: JavaScript (.js) files written by the user that are loaded at 
		application launch. These are editable directly by the user and as such are not usually found in 
		the same folder as kAVSFEBooks, kAVSFPreferences, or kAVSFSequences. 
		
	*/
	kAVSFJavaScript,

	/** User stamps folder: Custom rubber stamps created by the user are stored in this folder. 
		<p>Application stamps folder: Stamps that are shipped with the product. </p>
	*/
	kAVSFStamps,

	/** User-installed dictionaries: User-installed dictionaries for the spell checker. 
		<p>Application-installed dictionaries: Dictionaries that are shipped with the product. </p>
	*/
	kAVSFDictionaries,

	/** The application plug-ins folder where plug-ins are stored. 
		The kAVSCUser and kAVSCLocal domains are recommended.  kAVSCApp domain is deprecated.
	*/
	kAVSFPlugIns,

	/** Suite Pea plug-ins folder. */
	kAVSFSPPlugIns,

	/** Help folder Application help. 
	*/
	kAVSFHelp,

	/** Temporary folder. 
	*/
	kAVSFTemp,

	/** User messages/application messages folder.
	*/
	kAVSFMessages,

	/** PDFL resource folder. */
	kAVSFResource,

	/** Update folder. */
	kAVSFUpdate,

	/** Downloaded Adobe Reader Help folder: 
		
		<p>Used to store the full Adobe Reader Help file on systems that lock out access to the application Help 
		folder.</p> 
	*/
	kAVSFHelpLocale,

	/*** New for Acrobat 6.0 ***/
	/** */
	kAVSFAuthoring,

	/** */
	kAVSFSecurity,

	/** */
	kAVSFLocalRoot,

	/** */
	kAVSFLocalCache,

	/** <DEPRECATED > */
	kAVSFTasks,

	/** Linguistics Library (LILO) files shared among all Adobe applications. 
	*/
	kAVSFLinguistics,

	/** <p>Mapping Tables for the SaveAsXML plug-in.</p>
	*/
	kAVSFMappingTables,

	/** Used to create a new PDF file from the document template.
		User templates folder: Custom template files that the user creates are stored in this folder. 	
		<p>Application doc template folder: Doc templates that are shipped with the product. </p>
	*/
	kAVSFDocTemplates,

	/** User desktop folder. 
	*/
	kAVSFDesktop,
	/** Common PrintSpt folder for storing custom printer marks files. 
		<p>InDesign CS puts its custom marks files there, which is why the Viewer looks there as well.</p>
	*/
	kAVSFPrintSupport,

	/** */
	kAVSFGettingStarted,

	/** The TouchUp/Find Application plugin folder where TouchUp stores XML files. 
	*/
	kAVSFTouchUpFind,

	/** The folder where the Organizer database files are to be located. 
	*/
	kAVSFOrganizerDatabase,
	
	/** Used to create a PDF file envelope containing a secure attachment.
	*/
	kAVSFHostedServicesTemplates,

    /** Swatchbooks. */
    kAVSFSwatchbooks,

	/** Application's localized stamps folder: localized application stamps are stored in this folder. 
		<p>Application localized stamps folder: localized stamps that are shipped with the product.</p>
	*/
	kAVSFStampsLocale,

	/** Acrobat 10 navigators are stored in this folder
	*/
	kAVSFNavigators,

	/** Strings for Acrobat 10 navigators are stored in this folder. The navigators are stored in
		'kAVSFNavigators' folder. This folder is not used for custom navigators.
	*/
	kAVSFNavigatorsLocalized,

	/** Application multimedia skins folder: Multimedia skins that are shipped with the product.</p>
	*/
	kAVSFMultimediaSkins,
	
	/** Doc settings root */
	kAVSFDocSettings,
	
	/** DocSettings/CombineFiles */
	kAVSFDocSettingsCombineFiles,

	/** DocSettings/Redaction */
	kAVSFDocSettingsRedaction,
	
	/** Application resources */
	kAVSFApplicationResources,

	/** FileInfo */
	kAVSFFileInfo,
	
	/** Distiller job options
		Not avaialble on Windows (registry)
	*/
	kAVSFJobOptions,
	
	/** SWF's
		Not avaialble on Windows (SWF's are resources on Windows, files on Mac)
	*/
	kAVSFSWF,
	
	/** Built-in plug-ins */
	kAVSFBuiltInPlugIns,
	
	/** IDTemplates */
	kAVSFIDTemplates,

	/** Service plug-ins (SPA) */
	kAVSFServices,	/* need separate location for different products */
	kAVSFServicesRdr,
	kAVSFServicesStd,
	kAVSFServicesPro,

	/** pointer to where locales are stored (does NOT include locale itself) */
	kAVSFApplicationAllLocales,
	
	/** User and application defined UI Customization files */
	kAVSFUICustomization,

	/** Often used to tag the end of an enumeration with a specific value. */
	kAVSFLast
} AVSpecialFolder;


/**
	Operation status codes for the special folder methods. 
	@see AVAcquireSpecialFilePathName 
	@see AVAcquireSpecialFolderPathName 
*/
typedef enum {

	/** No error. */
	kAVSEOkay,				

	/** Invalid category/ folder combination. */
	kAVSEInvalidCombination,

	/** File or directory does not exist. */
	kAVSEDoesntExist,		

	/** File system error: directory could not be created. */
	kAVSECouldntCreate,		

	/** Some other generic error. */
	kAVSEError					
} AVSpecialError;

/*********************************************************
 * AVConversionHandler definitions
 *********************************************************/

/* Default UniqueID's for conversion handlers */
#define PDF_FILEFILTERREC_UNIQUEID "com.adobe.acrobat.pdf"
#define FDF_FILEFILTERREC_UNIQUEID "com.adobe.acrobat.fdf"


/**
	The user-defined data that is supplied when a conversion 
	handler is registered with the conversion server. This data 
	is provided to all AVConversionHandler callbacks. 
	@see AVConversionDefaultSettingsProc 
	@see AVConversionParamDescProc 
	@see AVConversionSettingsDialogProc 
	@see AVConversionConvertFromPDFProc 
	@see AVConversionConvertToPDFProc 
*/
typedef struct _t_AVConversionClientData *AVConversionClientData;

/**
	An enumerated list of flags that can be passed to AVConversionConvertTo/FromPDF to allow non-default behavior.
*/
enum {

	/** No flags. */
	kAVConversionNoFlags			= 0,		

	/** Asynchronous conversion is allowed. */
	kAVConversionAsyncOkay			= 1 << 0,	

	/** Pop the settings dialog box, if one is provided for this conversion handler. */
	kAVConversionPopSettingsDialog	= 1 << 1,	

	/** Interactive mode. Indicates converter can pop additional dialog boxes if necessary. */
	kAVConversionInteractive		= 1 << 2,	

	/** Do not overwrite the existing files <i>except</i> for the source file. This flag is only used in batch mode. */
	kAVConversionDontOverwrite		= 1 << 3
};
typedef ASUns32 AVConversionFlags;


/**
	Enumerated data type used to describe the status of a conversion 
	operation. 
	@see ASFileSysGetItemPropsProc 
	@see ASFileSysFirstFolderItemProc 
	@see ASFileSysNextFolderItemProc 
	@see ASFileSysGetItemProps 
	@see ASFileSysFirstFolderItem 
	@see ASFileSysNextFolderItem 
*/
enum {

	/** The conversion failed. */
	kAVConversionFailed,	

	/** The conversion succeeded. */
	kAVConversionSuccess,	

	/** The conversion will continue asynchronously. */
	kAVConversionSuccessAsync,	

	/** The conversion was cancelled. */
	kAVConversionCancelled		
};
typedef ASEnum16 AVConversionStatus;


/**
	Called to get the default settings for the conversion operation. 	

	<p>It is the caller's responsibility to release the resources 
	associated with the returned ASCab. </p>
	@param uniqueID IN/OUT A string that represents the filterDescription 
	parameter of the AVFileFilterRec for the conversion handler. 
	
	@param clientData IN/OUT The user-defined data that is provided 
	to all AVConversionHandler callbacks. 
	@return An ASCab containing the default settings for the conversion 
	operation, <code>NULL</code> to indicate none. 
*/
typedef ACCBPROTO1 ASCab (ACCBPROTO2 *AVConversionDefaultSettingsProc)
	(const char *uniqueID, AVConversionClientData clientData);

/**
    Called to set the handler's conversion settings.
    An ASCab containing the conversion settings is passed in.

    @param settings The ASCab containing the conversion settings
    @param clientData The user-defined data that is provided 
	to all AVConversion callbacks.
    @return <code>true</code> if settings were valid and have been set, <code>false</code> otherwise. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVConversionSetSettingsProc)
	(ASCab settings, AVConversionClientData clientData);

/**
	Called to obtain conversion parameter information. 
	@param settings IN/OUT A read-only ASCab containing the requested 
	parameters. 
	@param paramDesc IN/OUT (Filled by the callback) The parameter 
	descriptions (ASText objects) stored under numeric keys 
	starting with the key <code>" 1"</code>. 
	@example <code>key=" 1", value=" Title: API Reference"</code> (ASText object).
	@param clientData IN/OUT The user-defined data that is provided 
	to all AVConversion callbacks. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVConversionParamDescProc)
	(const ASCab settings, ASCab paramDesc, AVConversionClientData clientData);

/**
	Called to request the handler to display its settings dialog box, 
	if it has one. An ASCab containing conversion settings is 
	passed in to fill in the dialog box. 

	<p>The implementation should use these settings. Be sure to 
	use this cabinet of settings rather than defaults since 
	the batch framework may provide different settings. </p>

	<p>If the user commits changes, the settings should be stored 
	in the ASCab that was provided. </p>

	<p>For 'ConvertToPDF' handlers, two keys are present in the 
	settings ASCab: </p>
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Key</TH><TH>Description</TH></TR>
	<TR><TD>ASPathName</TD><TD>The path to the input file.</TD></TR>
	<TR><TD>ASFileSys</TD><TD>The associated file system.</TD></TR>
	</TABLE>

	<p>For 'ConvertFromPDF' handlers, three keys are present 
	in the settings ASCab: </p>
	<TABLE rules="all" cellspacing="1">
	<TR><TH>Key</TH><TH>Description</TH></TR>
	<TR><TD>PDDoc</TD><TD>The input PDDoc.</TD></TR>
	<TR><TD>ASPathName</TD><TD>The output path.</TD></TR>
	<TR><TD>ASFileSys</TD><TD>The associated file system.</TD></TR>
	</TABLE>

	@param settings The ASCab used to populate the dialog box. 	
	@param clientData The user-defined data that is provided 
	to all AVConversion callbacks.
	@return <code>true</code> to proceed with the conversion, <code>false</code> otherwise. 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVConversionSettingsDialogProc)
	(ASCab settings, AVConversionClientData clientData);

/**
	Called to convert a non-PDF file to a PDF file. 
	@param inSettings An ASCab containing the settings for the 
	conversion operation. It can be <code>NULL</code>. The implementation should 
	use these settings rather than defaults since the batch 
	framework may have provided custom settings.
	@param flags Indicates any non-default behavior to apply 
	to the conversion. By default, conversions are synchronous, 
	non-interactive, and do not display a settings dialog box. The 
	conversion framework will automatically call your settings 
	dialog box if kAVConversionSyncPopSettingsDialog is set. Do 
	not pop your settings dialog box in your convert proc.
	@param inPath The location of the input file. 
	@param inFileSys The file system from which path was obtained. 	
	@param outPDDoc The output PDDoc. The implementation should 
	not clean up this PDDoc: Acrobat will do this. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>. If an error occurs during conversion, the implementation 
	should not raise or throw an error but instead report the 
	error using the <code>reportProc</code>, if it is available. 
	@param clientData The user-defined data that is provided 
	to all AVConversionHandler callbacks. 
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertFromPDFProc 
	@see AVConversionConvertToPDFWithHandler 
*/
typedef ACCBPROTO1 AVConversionStatus (ACCBPROTO2 *AVConversionConvertToPDFProc)(
	ASCab						inSettings,
	AVConversionFlags			flags,
	ASPathName					inPath,
	ASFileSys					inFileSys,
	PDDoc						*outPDDoc,
	AVStatusMonitorProcs		statusMonitor,
	AVConversionClientData		clientData);

/**
	Called to convert a non-PDF file to a PDF file.
	@param inSettings IN/OUT An ASCab containing the settings for the conversion
	operation. It can be <code>NULL</code>. The implementation should use these
	settings rather than defaults since the batch framework may
	have provided custom settings.
	@param flags IN/OUT Bit flags for any non-default behavior to apply to the conversion.
	By default, conversions are synchronous, non-interactive, and
	do not display a settings dialog box. The conversion framework calls
	your settings dialog box if
	kAVConversionSyncPopSettingsDialog is set; this
	procedure should not open the settings dialog box.
	@param stream IN/OUT The input stream.
	@param metaData IN/OUT An ASCab containing metadata about the input stream, such
	as a key url containing the URL of HTML data. It can be <code>NULL</code>.
	@param outPDDoc IN/OUT The output PDDoc. The implementation should not clean up
	this PDDoc: Acrobat will do this.
	@param statusMonitor IN/OUT Contains the progress monitor, cancel proc, and error reporting
	proc to be used by the converter. It can be <code>NULL</code>. If an error
	occurs during conversion, the implementation should not raise
	or throw an error but instead report the error using the
	<code>reportProc</code>, if it is available.
	@param clientData IN/OUT The user-defined data that is provided to all
	AVConversionHandler callbacks.
*/
typedef ACCBPROTO1 AVConversionStatus (ACCBPROTO2 *AVConversionConvertStreamToPDFProc)(
	ASCab						inSettings,
	AVConversionFlags			flags,
	ASStm						stream,
	ASCab						metaData,
	PDDoc						*outPDDoc,
	AVStatusMonitorProcs		statusMonitor,
	AVConversionClientData		clientData);

/**
	Called to convert a non-PDF file to a PDF file and then append to an existing PDF file. 
	@param inSettings An ASCab containing the settings for the 
	conversion operation. It can be <code>NULL</code>. The implementation should 
	use these settings rather than defaults since the batch 
	framework may have provided custom settings.
	@param flags Indicates any non-default behavior to apply 
	to the conversion. By default, conversions are synchronous, 
	non-interactive, and do not display a settings dialog box. The 
	conversion framework will automatically call your settings 
	dialog box if kAVConversionSyncPopSettingsDialog is set. Do 
	not pop your settings dialog box in your convert proc.
	@param inPath The location of the input file. 
	@param inFileSys The file system from which path was obtained. 	
	@param outPDDoc The output PDDoc. The implementation should 
	not clean up this PDDoc: Acrobat will do this. 
	@param statusMonitor Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>. If an error occurs during conversion, the implementation 
	should not raise or throw an error but instead report the 
	error using the <code>reportProc</code>, if it is available. 
	@param clientData The user-defined data that is provided 
	to all AVConversionHandler callbacks. 
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertFromPDFProc 
	@see AVConversionConvertToPDFWithHandler 
*/
typedef ACCBPROTO1 AVConversionStatus (ACCBPROTO2 *AVConversionAppendToPDFProc)(
	ASCab						inSettings,
	AVConversionFlags			flags,
	ASPathName					inPath,
	ASFileSys					inFileSys,
	PDDoc						outPDDoc,
	AVStatusMonitorProcs		statusMonitor,
	AVConversionClientData		clientData);

/**
	Called to get Number of Pending Conversions in the conversion queue.
	@return Number of Pending Conversions in the conversion queue.
*/
typedef ACCBPROTO1 ASUns32 (ACCBPROTO2 *AVConversionGetQueueStatusProc)(
	AVConversionClientData		clientData);

/**
	Called to convert a PDF file to another file format. 
	@param inSettings IN/OUT An ASCab containing the settings for the 
	conversion operation. It can be <code>NULL</code>. The implementation should 
	use these settings rather than defaults since the batch 
	framework may have provided custom settings. 
	@param flags IN/OUT Indicates any non-default behavior to apply 
	to the conversion. By default, conversions are synchronous, 
	non-interactive, and do not display a settings dialog box. The 
	conversion framework will automatically call your settings 
	dialog box if kAVConversionSyncPopSettingsDialog is set. Do 
	not pop your settings dialog box in your convert proc. 
	@param inPDDoc IN/OUT The document that is to be converted. 
	@param outPath IN/OUT The desired location for the output file. 
	@param outFileSys IN/OUT The file system from which path was obtained. 	
	@param statusMonitor IN/OUT Contains the progress monitor, cancel 
	proc, and error reporting proc to be used by the converter. 
	It can be <code>NULL</code>. If an error occurs during conversion, the implementation 
	should not raise or throw an error but instead report the 
	error using the <code>reportProc</code>, if it is available. The report 
	proc member of the status monitor can be <code>NULL</code>, so developers 
	should check for that condition before calling it. 
	@param clientData IN/OUT The user-defined data that is provided 
	to all AVConversionHandler callbacks. 
	@return One of the AVConversionStatus codes. 
	@see AVConversionConvertToPDFProc 
	@see AVConversionConvertFromPDFWithHandler 
*/
typedef ACCBPROTO1 AVConversionStatus (ACCBPROTO2 *AVConversionConvertFromPDFProc)(
	ASCab						inSettings,
	AVConversionFlags			flags,
	PDDoc						inPDDoc,
	ASPathName					outPath,
	ASFileSys					outFileSys,
	AVStatusMonitorProcs		statusMonitor,
	AVConversionClientData		clientData);


/**
	Called to convert a PDF file to another file format.  It must return an AVConversionStatus
	indicating success, failure, or cancel.
	@param inSettings IN/OUT An ASCab of settings which can be <code>NULL</code>.  The converter must use these settings
	rather than default ones since the Batch framework may have provided custom settings.
	@param flags IN/OUT Indicates any non-default behavior to apply to the conversion.  By default, conversions
	are synchronous, non-interactive, and do not display a settings dialog box.  The conversion framework
	will automatically call your settings dialog box if kAVConversionSyncPopSettingsDialog is set. Do not
	pop your settings dialog box in your convert proc.
	@param inPDDoc IN/OUT The input PDDoc that will be converted.
	@param stream IN/OUT An output ASStm.
	@param metaData IN/OUT An empty ASCab in which metadata may be placed. For example, for HTML data, there might
	be a key "url" which contains the URL of the HMTL data.
	@param statusMonitor IN/OUT Contains the progress monitor, cancel proc, and error reporting proc that the
	converter should use.  This can be <code>NULL</code>.  If an error occurs during conversion, the converter
	should not raise or throw an error but instead report the error using the <code>reportProc</code>, if it is
	available.
	@param clientData IN/OUT provided to all AVConversionHandler callbacks.
	@return One of the AVConversionStatus codes. 
*/
typedef ACCBPROTO1 AVConversionStatus (ACCBPROTO2 *AVConversionConvertStreamFromPDFProc)(
	ASCab						inSettings,
	AVConversionFlags			flags,
	PDDoc						inPDDoc,
	ASStm						stream,
	ASCab						metaData,
	AVStatusMonitorProcs		statusMonitor,
	AVConversionClientData		clientData);

/**
	An opaque object representing a node in a document structure tree.
	@see AVConversionConvertStreamFromStructNodeProc
	@see AVConversionConvertStreamFromStructNodeWithHandler
*/
typedef struct _t_AVStructNode*	AVStructNode;

/**
	Called to convert a structure subtree rooted at a given node to a stream.
	@param inSettings An ASCab containing the settings for the conversion
	operation. It can be <code>NULL</code>. The implementation should use these
	settings rather than defaults since the batch framework may
	have provided custom settings.
	@param flags Bit flags for any non-default behavior to apply to the conversion.
	By default, conversions are synchronous, non-interactive, and
	do not display a settings dialog box. The conversion framework calls
	your settings dialog box if
	kAVConversionSyncPopSettingsDialog is set; this
	procedure should not open the settings dialog box.
	@param inStructNode The structure node to be converted.
	@param stream The output stream.
	@param metaData An ASCab containing metadata about the input stream, such
	as a key url containing the URL of HTML data. It can be <code>NULL</code>.
	@param statusMonitor Contains the progress monitor, cancel proc, and error reporting
	proc to be used by the converter. It can be <code>NULL</code>. If an error
	occurs during conversion, the implementation should not raise
	or throw an error but instead report the error using the
	<code>reportProc</code>, if it is available.
	@param clientData The user-defined data that is provided to all AVConversionHandler callbacks.
	@return AVConversionStatus indicating success, failure, or cancel. 
*/
typedef ACCBPROTO1 AVConversionStatus (ACCBPROTO2 *AVConversionConvertStreamFromStructNodeProc)(
	ASCab						inSettings,
	AVConversionFlags			flags,
	AVStructNode				inStructNode,
	ASStm						stream,
	ASCab						metaData,
	AVStatusMonitorProcs		statusMonitor,
	AVConversionClientData		clientData);

/**
	A MIME-type string for PDF conversion.
	@see AVConversionFromPDFHandler
	@see AVConversionToPDFHandler
	@see AVAppRegisterFromPDFHandler
	@see AVAppRegisterToPDFHandler
*/
typedef char	AVConversionMimeTypeString[256];


/**
	A data structure containing callbacks that implement the 'ToPDF' 
	handler's functionality and data that describes the handler's 
	conversion capabilities. 
	@see AVConversionToPDFEnumProc 
	@see AVAppRegisterToPDFHandler 
*/
typedef struct _t_AVConversionToPDFHandler {

	/** An AVFileFilterRec that describes the types of files that this filter can convert. See the descriptions
		of AVFileFilterRec and AVFileDescRec for more details.
		@see AVFileFilterRec
		@see AVFileDescRec
	*/
	AVFileFilterRec					convFilter;

	/** The size of the data structure. It must be set to <code>sizeof(AVConversionFromPDFHandlerRec)</code>. */
	ASSize_t						size;

	/** A unique identifier for the conversion handler. It should be of the form <code>com.companyname.productname.type</code>. 
		See PDF_FILEFILTERREC_UNIQUEID and FDF_FILEFILTERREC_UNIQUEID in AVExpT.h. 
	*/
	char							uniqueID[256];

	/** <code>true</code> if the converter can perform synchronous conversion, <code>false</code> if the converter only does asynchronous 
		conversion. This capability is required for the handler to be accessible from the batch framework. 
	*/
	ASBool							canDoSync;

	/** Unused.  Set to zero.
	*/
	AVPriority						priority;

	/** An AVConversionDefaultSettingsProc() that is called when the handler is registered with the conversion 
		server. It can be <code>NULL</code>. 
	*/
	AVConversionDefaultSettingsProc	defaultSettings;

    /** An AVConversionSetSettingsProc() that is called to set the conversion settings for the handler.
        It can be <code>NULL</code>.
    */
    AVConversionSetSettingsProc     setSettings;

	/** An AVConversionParamDescProc() that is called when a parameter description of this handler is requested. 
		It can be <code>NULL</code>. 
	*/
	AVConversionParamDescProc		parameterDescription;

	/** An AVConversionSettingsDialogProc() that is called when the batch framework or the open dialog box requests 
		a settings dialog box for this handler. It can be <code>NULL</code>. 
	*/
	AVConversionSettingsDialogProc	settingsDialog;

	/** An AVConversionConvertToPDFProc() that is called to perform the conversion operation. */
	AVConversionConvertToPDFProc	convert;

	/** An AVConversionAppendToPDFProc() that is called to perform an append operation */
	AVConversionAppendToPDFProc		append;

	/** An AVConversionGetQueueStatusProc() that is called to get number of conversions in the conversion queue. */
	AVConversionGetQueueStatusProc	getQueueStatus;

	/** Provided to all AVConversion callbacks. */
	AVConversionClientData			clientData;

	/** Added with Acrobat 6. A string containing MIME types 
	that can be handled by the <code>convertStream</code> callback. */
	AVConversionMimeTypeString		*streamMimeTypes;

	/** Added with Acrobat 6. The number of MIME types in 
	<code>streamMimeTypes</code>. */
	AVArraySize						numStreamMimeTypes;

	/** Added with Acrobat 6. */
	AVConversionConvertStreamToPDFProc	convertStream;
	/** Added with Acrobat 9.  Unused.  Set to zero*/
	AVConversionClientData			reserved;
} AVConversionToPDFHandlerRec, *AVConversionToPDFHandler;

/**
	A data structure containing callbacks that implement the 'FromPDF' 
	handler's functionality and data that describes the handler's 
	conversion capabilities. 
	@see AVConversionFromPDFEnumProc 
	@see AVAppRegisterFromPDFHandler 
*/
typedef struct _t_AVConversionFromPDFHandler {

	/** An AVFileFilterRec that describes the types of files that this filter can convert. See the descriptions 
		of AVFileFilterRec and AVFileDescRec for more details. 
		@see AVFileFilterRec
		@see AVFileDescRec
	*/
	AVFileFilterRec					convFilter;

	/** The size of the data structure. It must be set to <code>sizeof(AVConversionFromPDFHandlerRec)</code>. */
	ASSize_t						size;

	/** A unique identifier for the conversion handler. It should be of the form <code>com.companyname.productname.type</code>. 
		See PDF_FILEFILTERREC_UNIQUEID and FDF_FILEFILTERREC_UNIQUEID in AVExpT.h. 
	*/
	char							uniqueID[256];

	/** <code>true</code> if the converter can perform synchronous conversion, <code>false</code> if the converter only does asynchronous 
		conversion. This capability is required for the handler to be accessible from the batch framework. 
	*/
	ASBool							canDoSync;

	/** Unused.  Set to zero.
	*/
	AVPriority							priority;

	/** An AVConversionDefaultSettingsProc() that is called when the handler is registered with the conversion 
		server. It can be <code>NULL</code>. 
	*/
	AVConversionDefaultSettingsProc	defaultSettings;

	/** An AVConversionParamDescProc() that is called when a parameter description of this handler is 
		requested. It can be <code>NULL</code>. 
	*/
	AVConversionParamDescProc		parameterDescription;

	/** An AVConversionSettingsDialogProc() that is called when the batch framework or the open dialog box requests 
		a settings dialog box for this handler. It can be <code>NULL</code>.
	*/
	AVConversionSettingsDialogProc	settingsDialog;

	/** An AVConversionConvertFromPDFProc() that is called to perform the conversion operation. */
	AVConversionConvertFromPDFProc	convert;

	/** Provided to all AVConversion callbacks. */
	AVConversionClientData			clientData;

	/** Added with Acrobat 6.0. It is a string containing MIME types 
	that can be handled by the <code>convertStream</code> callback.  */
	AVConversionMimeTypeString		*streamMimeTypes;

	/** Added with Acrobat 6. It is the number of MIME types in 
	<code>streamMimeTypes</code>.  */
	AVArraySize						numStreamMimeTypes;

	/** Added with Acrobat 6. The stream-conversion handler procedure.  */
	AVConversionConvertStreamFromPDFProc		convertStream;

	/** Added with Acrobat 6. The structure-node-to-stream 
	conversion handler procedure. */
	AVConversionConvertStreamFromStructNodeProc	convertStructNode;
} AVConversionFromPDFHandlerRec, *AVConversionFromPDFHandler;


/**
	The user-defined data that is supplied to either of the 
	conversion handler enumeration routines. 
	@see AVConversionFromPDFEnumProc 
	@see AVConversionToPDFEnumProc 
	@see AVConversionEnumFromPDFConverters 
	@see AVConversionEnumToPDFConverters 
*/
typedef struct _t_AVConversionEnumProcData *AVConversionEnumProcData;

/**
	Called once for each AVConversionToPDFHandler registered 
	with Acrobat, or until the callback returns <code>false</code> to halt 
	the enumeration. 
	@param handler IN/OUT The AVConversionToPDFHandler. 
	@param data IN/OUT User-defined data passed to the call to AVConversionEnumToPDFConverters(). 
	
	@return <code>true</code> to continue the enumeration, <code>false</code> otherwise. 
	@see AVConversionFromPDFEnumProc 
	@see AVConversionEnumToPDFConverters 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVConversionToPDFEnumProc)(AVConversionToPDFHandler handler, AVConversionEnumProcData data);

/**
	Called once for each AVConversionFromPDFHandler registered 
	with Acrobat, or until the callback returns <code>false</code> to halt 
	the enumeration. 
	@param handler IN/OUT The AVConversionFromPDFHandler. 
	@param data IN/OUT User-defined data passed to the call to AVConversionEnumFromPDFConverters.() 
	
	@return <code>true</code> to continue the enumeration, <code>false</code> otherwise. 
	@see AVConversionToPDFEnumProc 
	@see AVConversionEnumFromPDFConverters 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVConversionFromPDFEnumProc)(AVConversionFromPDFHandler handler, AVConversionEnumProcData data);

/*********************************************************
 * AVIdentity definitions
 *********************************************************/

/**
	An enumerated data type used to identify the properties of 
	a user's identity. 
	@see AVIdentityGetText 
	@see AVIdentitySetText 
*/
typedef enum { 

	/** */
	kAVILoginName, 

	/** */
	kAVIName, 

	/** */
	kAVICorporation, 

	/** */
	kAVIEMail, 

	/** */
	kAVIDepartment,
	
	/** */
	kAVITitle,

	/** */
	kAVIFirstName,

	/** */
	kAVILastName,

	/** */
	kAVICorporationAbbr,

	/** */
	kAVILast
} AVIdentity;

/*********************************************************
 * AVCommand definitions
 *********************************************************/


/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyASFileSys		"ASFileSys"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyASPathName		"ASPathName"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyPDDoc			"PDDoc"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyAVDoc			"AVDoc"

/** If possible, use kAVCommandKeyBaseFileNameASText instead. 
	@ingroup AVCommandStringConstants 
*/
#define kAVCommandKeyBaseFileName	"BaseFileName" 

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyBaseFileNameASText	"BaseFileNameASText"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyOrigExtension	"OrigExtension"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyGenericTitle	"GenericTitle"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyTitle			"Title"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyParams			"Params"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyParamsDesc		"ParamsDesc"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyCanDescribeParams	"CanDescribeParams"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyCanBatch		"CanBatch"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyCanShowDialog	"CanShowDialog"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyGroupTitle		"GroupTitle"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyIsStatus       "IsStatus"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyFireWhenModal  "FireWhenModal"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyNeedPause		"NeedPause"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyCanPause		"CanPause"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyInstructions	"Instructions"

/** @ingroup AVCommandStringConstants */
#define kAVCommandKeyScreenName		"ScreenName"

/**
	An enumerated list of status codes that can be returned 
	by various AVCommand methods. 
	@see AVCommandGetStatus 
*/
enum {

	/** Not working, but ready to work. */
	kAVCommandReady,	

	/** Still working. */
	kAVCommandWorking,	

	/** Done working. */
	kAVCommandDone,		

	/** Cancelled. */
	kAVCommandCanceled,	

	/** In error. */
	kAVCommandInError,

	/** Cancelled in favor of running this command (with the current parameters) in a sequence of multiple files. */
	kAVCommandCanceledForMultiple,

	/** Command not executed due to lack of objects on which the command to be executed. */
	kAVCommandNotExecuted,

	/** Paused. */
	kAVCommandPaused
};
typedef ASEnum16 AVCommandStatus;


/**
	An enumeration detailing how the command is expected to 
	interact with the user. 
	@see AVCommandGetUIPolicy 
*/
enum {
	/** Fully interactive. Gather parameters based on the currently active document at the time 
		the dialog box is displayed. Display errors and warnings. 
	*/
	kAVCommandUIInteractive = 0,	

	/** Interactive but under the control of the sequencing user interface. When showing 
		a dialog box, use the parameters passed in, rather than the parameters gathered from the document. 
	*/
	kAVCommandUISemiInteractive = 1,

	/** Display errors but no other	dialog boxes. */
	kAVCommandUIErrorsOnly = 2,	

	/** Never display a dialog box. */
	kAVCommandUISilent = 3		
};
typedef ASEnum16 AVCommandUIPolicy;


/** An AVCommand represents an action that the user can perform on the
	current document or the current selection in the current document.
	Specifically, an AVCommand represents a command which can be added
	to a command sequence and executed either interactively or via
	batch processing.
*/
typedef struct _t_AVCommandRec *AVCommand;


/**
	Initialize the command handler. It is called once for each command 
	handler registered. 
	@param handlerName IN/OUT The name of the command handler. 
	@return <code>true</code> if initialization succeeds, <code>false</code> otherwise. 
	@see AVCmdHandlerTermProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVCmdHandlerInitProc)
	(ASAtom handlerName);


/**
	Terminate the handler. It is called once for each handler registered 
	when Acrobat shuts down. It is called before clients are unloaded. 
	
	@param handlerName The name of the handler being terminated.
	@see AVCmdHandlerInitProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVCmdHandlerTermProc)
	(ASAtom handlerName);

/**
	A callback for AVCommandHandlerRec. The application maintains 
	a global list of commands that the user can choose from 
	when building a batch sequence. During the initialization 
	sequence, all registered command handlers are asked to build 
	and register all the commands that the handler wants to include 
	in the global command list. This is done by calling the 
	command handler's <code>RegisterCommands</code> callback, if it is not 
	<code>NULL</code>. 
	@param handlerName IN/OUT The name of the command handler. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVRegisterCommandsProc)
	(ASAtom handlerName);

/**
	Called after a command is created. The command handler can 
	establish default parameters and so forth for the newly 
	created command. 
	@param cmd IN/OUT The command that was created. 
	@see AVCommandDestroyProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVCommandCreatedProc)
	(AVCommand cmd);

/**
	Called before a command is destroyed. The command handler 
	should free any memory allocated by the command. 
	@param cmd IN/OUT The command being destroyed. 
	@see AVCommandCreatedProc 
	@see AVCommandDestroy 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVCommandDestroyProc)
	(AVCommand cmd);

/**
	Called to set a cabinet within a command. It is used in the <code>SetParams</code> 
	member of the AVCommandHandlerRec structure. The command 
	handler should copy any information from the cabinet into 
	the command. It must not destroy or modify the cabinet. 
	
	@param cmd IN/OUT The command. 
	@param cab IN/OUT The cabinet to store. 
	@return One of the AVCommandStatus codes. 
	@see AVCommandResetProc 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandSetProc)
	(AVCommand cmd, ASCab cab);

/**
	Retrieves a cabinet from a command. It is used in the 
	<code>GetParams</code> and <code>GetProps</code> members of the AVCommandHandlerRec 
	structure. When retrieving command parameters, the handler 
	should first remove any existing items from <code>theCab</code> using 
	ASCabMakeEmpty(), and then copy all parameter values from the 
	command into <code>theCab</code>. When retrieving properties, the command 
	handler should replace any entries in <code>theCab</code> with key names 
	it recognizes with copies of the command-specific properties. 
	@param cmd IN/OUT The command whose procedure is being retrieved. 
	@param theCab IN/OUT (Filled by the callback) The appropriate 
	command cabinet. 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVCommandGetProc)
	(AVCommand cmd, ASCab theCab);

/**
	Displays the command's parameter setting dialog box and allows 
	the user to alter the parameters. 
	@param cmd The command whose parameter setting dialog box 
	is displayed.
	@return One of the AVCommandStatus codes. 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandShowDialogProc)
	(AVCommand cmd);


/**
	Do some work. If it does not finish its work, return kAVCommandWorking. 
	If it does finish its work, return kAVCommandDone. If the 
	user cancels the operation, return kAVCommandCanceled. If 
	an error occurs, return kAVCommandInError. 

	<p>In most cases this method performs its work until it returns 
	kAVCommandDone, but in some cases it may be called on to 
	cancel or reset before its work is done.</p> 
	@param cmd IN/OUT The command doing some work. 
	@return One of the AVCommandStatus codes. 
	@see AVCommandWork 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandWorkProc)
	(AVCommand cmd);

/**
	Stop working and clean up as though the command executed 
	to completion. 
	@param cmd IN/OUT The command being cancelled. 
	@return One of the AVCommandStatus codes. 
	@see AVCommandGetCancelProc 
	@see AVCommandCancel 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandCancelProc)
	(AVCommand cmd);

/**
	Stops working, clears any errors, and tries to get back into 
	a Ready state. For many commands this is equivalent to cancelling. 
	
	@param cmd IN/OUT The command being reset. 
	@return One of the AVCommandStatus codes. 
	@see AVCommandSetProc 
	@see AVCommandReset 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandResetProc)
	(AVCommand cmd);

/**
	Every command in a sequence has its <code>Preflight</code> callback 
	called before the sequence is executed. If any of the <code>Preflight</code> 
	callbacks returns an error, the sequence is aborted. 

	<p>Preflights and Postflights are good for getting user data 
	or preparing the command at the beginning of the sequence. 
	For example, you could use the Preflight to ask what password 
	the 'Add Security' command should use. This is important 
	since you only want to ask once (not for every file), and 
	you do not want to store the password in the sequence file 
	(or the command's persistent parameters).</p> 

	<ul>
		<li>Sequence Begins </li>
		<li>AVCommandPreflightSequenceProc() for all commands are called </li>
		<li>Open File # 1 </li>
		<li>AVCommandPreflightFileProcs() for all commands are called </li>
		<li>Execute all commands on given file </li>
		<li>AVCommandPostflightFileProcs for all commands are called </li>
		<li>Close File # 1 </li>
		<li>Open File # 2 </li>
		<li>... (repeat pre/post file procs) </li>
		<li>Close last file </li>
		<li>AVCommandPostflightSequenceProcs for all commands are called. </li>
		<li>Sequence ends </li>
	</ul>

	@param cmd IN/OUT The command. 
	@return One of the AVCommandStatus codes. 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandPreflightSequenceProc)
	(AVCommand cmd);


/**
	Every command in a sequence has its <code>Preflight</code> callback 
	called after each file has been opened to be processed but 
	before any commands have been executed on that file. If 
	any of the <code>Preflight</code> callbacks returns an error, the sequence 
	is aborted. 

	<p>Preflights and Postflights are good for getting user data 
	or preparing the command at the beginning of the sequence. 
	For example, you could use the Preflight to ask what password 
	the 'Add Security' command should use. This is important 
	since you only want to ask once (not for every file), and 
	you do not want to store the password in the sequence file 
	(or the command's persistent parameters).</p> 

	<p>See AVCommandPreflightSequenceProc() for the order in which 
	the AVCommand Pre/Postflight callbacks are called. </p>
	@param cmd The command. 
	@param doc The PDDoc.
	@return One of the AVCommandStatus codes. 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandPreflightFileProc)
	(AVCommand cmd, PDDoc doc);


/**
	Every command in a sequence has its <code>Postflight</code> command 
	callback called after all commands in a given sequence have 
	been executed but before the file is closed. 

	<p>Preflights and Postflights are good for getting user data 
	or preparing the command at the beginning of the sequence. 
	For example, you could use the Preflight to ask what password 
	the 'Add Security' command should use. This is important 
	since you only want to ask once (not for every file), and 
	you do not want to store the password in the sequence file 
	(or the command's persistent parameters).</p> 

	<p>See AVCommandPreflightSequenceProc() for the order in which 
	the AVCommand Pre/Postflight callbacks are called. </p>
	@param cmd The command. 
	@param doc The PDDoc.
	@return One of the AVCommandStatus codes. 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandPostflightFileProc)
	(AVCommand cmd, PDDoc doc);


/**
	Every command in a sequence has its <code>Postflight</code> command 
	callback called after the sequence is executed. 

	<p>Preflights and Postflights are good for getting user data 
	or preparing the command at the beginning of the sequence. 
	For example, you could use the Preflight to ask what password 
	the 'Add Security' command should use. This is important 
	since you only want to ask once (not for every file), and 
	you do not want to store the password in the sequence file 
	(or the command's persistent parameters).</p> 

	<p>See AVCommandPreflightSequenceProc() for the order in which 
	the AVCommand Pre/Postflight callbacks are called. </p>
	@param cmd The command.
	@return One of the AVCommandStatus codes. 
*/
typedef ACCBPROTO1 AVCommandStatus (ACCBPROTO2 *AVCommandPostflightSequenceProc)
	(AVCommand cmd);

/**
	A set of callbacks that perform the actions required of 
	a command. 
*/
typedef struct _t_AVCommandHandler
{

	/** The size of the structure. Set it to <code>sizeof(AVCommandHandlerRec)</code>. */
	ASSize_t					size;

	/** Called once for each handler registered. */
	AVCmdHandlerInitProc		Initialize;

	/** Called once for each handler registered when Acrobat shuts down. It is called before plug-ins are unloaded */
	AVCmdHandlerTermProc		Terminate;

	/** The application maintains a global list of commands that you can choose from when building 
		your own command. During the initialization sequence, all registered command handlers are asked 
		to build and register all the commands that the handler wants to include in the global command list. 
	*/
	AVRegisterCommandsProc		RegisterCommands;

	/** Called after a command is created. The command handler can establish default parameters and so forth 
		for the newly created command. 
	*/
	AVCommandCreatedProc		Created;

	/** Called before a command is destroyed. The command handler should free any memory allocated by the 
		command, and so on. 
	*/
	AVCommandDestroyProc		Destroy;

	/** Called to set the command's parameters. */
	AVCommandSetProc			SetParams;

	/** Called to retrieve the command's parameters. */
	AVCommandGetProc			GetParams;

	/** Called to retrieve command properties. */
	AVCommandGetProc			GetProps;

	/** Displays the command's parameter setting dialog box and allows the user to alter the parameters. */
	AVCommandShowDialogProc		ShowDialog;

	/** Do some work. If the command does not finish the work, return kAVCommandWorking. If the command 
		finishes the work, return kAVCommandDone. If the user cancels the operation, return 
		kAVCommandCanceled. If an error occurs, return kAVCommandInError. In most cases the work procedure 
		will be called until you return kAVCommandDone, but in some cases, you may be called upon to Cancel or 
		Reset before the work is done. 
	*/
	AVCommandWorkProc			Work;

	/** Stop working and pretend it reached a point where all work was done. */
	AVCommandCancelProc		  	Cancel;

	/** Stop working, clear any errors, and try to get back into a ready state. For many commands 
		this is equivalent to cancelling.
	*/
	AVCommandResetProc			Reset;


	/** See the sequence description in the callback reference. */
	AVCommandPreflightSequenceProc	PreflightSequence;


	/** See the sequence description in the callback reference. */
	AVCommandPreflightFileProc		PreflightFile;


	/** See the sequence description in the callback reference. */
	AVCommandPostflightFileProc		PostflightFile;


	/** See the sequence description in the callback reference. */
	AVCommandPostflightSequenceProc	PostflightSequence;

	/** Reserved for internal use. It must be <code>NULL</code>. */
	void *reserved;
} AVCommandHandlerRec;
typedef AVCommandHandlerRec *AVCommandHandler;


/**
	Enumerates the commands for moving and changing the size 
	of a rectangle. 
	@see AVRectHandleHitTest 
*/
enum {

	/** Move the whole rectangle. */
	kAVDragRect,				

	/** Top left corner. */
	kAVDragTopLeft,				

	/** Top right corner. */
	kAVDragTopRight,			

	/** Bottom right corner. */
	kAVDragBottomRight,			

	/** Bottom left corner. */
	kAVDragBottomLeft,			

	/** Top middle. */
	kAVDragTopMiddle,			

	/** Right middle. */
	kAVDragRightMiddle,			

	/** Bottom middle. */
	kAVDragBottomMiddle,		

	/** Left middle. */
	kAVDragLeftMiddle,			

	/** Snap to top left. */
	kAVDragSnapToTopLeft,		

	/** Snap to top. */
	kAVDragSnapToTop,			

	/** Snap to top right. */
	kAVDragSnapToTopRight,		

	/** Snap to right. */
	kAVDragSnapToRight,			

	/** Snap to bottom right. */
	kAVDragSnapToBottomRight,	

	/** Snap to bottom. */
	kAVDragSnapToBottom,		

	/** Snap to bottom left. */
	kAVDragSnapToBottomLeft,	

	/** Snap to left. */
	kAVDragSnapToLeft			
};
typedef ASEnum8 AVDragType;


/**
	An enumerated list of the types of AVRect handles. 
*/
enum {

	/** No handle. */
	kAVRectHandleNone,			

	/** Top left. */
	kAVRectHandleTopLeft,		

	/** Top right. */
	kAVRectHandleTopRight,		

	/** Bottom right. */
	kAVRectHandleBottomRight,	

	/** Bottom left. */
	kAVRectHandleBottomLeft,	

	/** Top middle. */
	kAVRectHandleTopMiddle,		

	/** Right middle. */
	kAVRectHandleRightMiddle,	

	/** Bottom middle. */
	kAVRectHandleBottomMiddle,	

	/** Left middle. */
	kAVRectHandleLeftMiddle		
};
typedef ASEnum8 AVRectHandleType;


/**
	The parameters for AVPageViewDragRectSnappedEx(), which supersedes 
	AVPageViewDragRectSnapped() in Acrobat 6.0. In addition to 
	the parameters allowed by the earlier method, the new version 
	allows you to specify your own drawing procedure. 
*/
typedef struct _t_AVDragRectParams {

	/** Set by the caller to <code>sizeof(AVDragRectParamsRec)</code>. */
	ASSize_t size;					

	/** The page view where the drag occurs. */
	AVPageView pageView;			

	/** The starting x-coordinate in device space. */
	ASInt32 xStart;					

	/** The starting y-coordinate in device space. */
	ASInt32 yStart;					

	/** The initial rect in page space.  */
	ASFixedRect *startRect;			

	/** The resulting rect in page space. */
	ASFixedRect *resultRect;		

	/** The desired drag type, which is typically the result of AVRectHandleHitTest(). */
	AVDragType dragType;		

	/** The device-space drag bounds. */
	AVDevRect *extrema;			

	/** Pass <code>NULL</code> for default cursors. */
	AVCursor *cursorArray;		

	/** The number of cursors in <code>cursorArray</code>. */
	ASInt32 nCursors;				

	/** Pass <code>NULL</code> for the default Acrobat proc. */
	AVPageViewDrawProc drawProc;

	/** The device space minimum rectangle. This rectangle is used as a lower
	    bound during a resize operation. The exact position of the rectangle is
		not important. The rectangles <code>[0,0,10,20]</code> and <code>[100,100,110,120]</code> are considered
		identical since they have the same width and height. */
	AVDevRect *minRect;

} AVDragRectParamsRec, *AVDragRectParams;


/* Definitions for Accessibility */

/**
	Definitions specifying the manner in which the background 
	and text colors are chosen when viewing a document. 
	@see AVAppSetPreference 
*/
enum {

	/** Use the colors specified within the document. */
	kAVAccessUseDocumentColors,

	/** Use the colors specified by the operating system preferences. */
	kAVAccessUseSystemColors,

	/** Use the colors specified by the Acrobat preferences. */
	kAVAccessUsePreferenceColors,

	/** */
	kAVAccessForceSystemColors,
	
	/** Use accessible high-contrast colors. **/
	kAVAccessUseHiContGreenBlack,
	kAVAccessUseHiContYellowBlack,
	kAVAccessUseHiContWhiteBlack,
	kAVAccessUseHiContBlackWhite

};
typedef ASEnum8 AVAccessColorPolicy;


/** Content reading orders used for accessibility support. 
	kAVAccessInferredReadOrder, kAVAccessTBLRReadOrder, and kAVAccessWordyReadOrder 
	can be used as values for the Reading Order preference. kAVAccessTaggedReadOrder
	and kAVAccessUndefinedReadOrder are used internally for managing the states of
	documents. */
enum {

	/** Run MakeAccessible to generate a temporary structure. */
	kAVAccessInferredReadOrder,

	/** Use Wordy's Top-to-Bottom, Left-to-Right order. */
	kAVAccessTBLRReadOrder,

	/** Use Wordy's Print Stream order. */
	kAVAccessWordyReadOrder,

	/** Use the structure tree. */
	kAVAccessTaggedReadOrder,

	/** The reading order is undetermined. */
	kAVAccessUndefinedReadOrder
};
typedef ASEnum8 AVAccessReadOrder;


/**
	An enumerated list of toolbar positions for registering 
	the preferred position of a toolbar. 
	@see AVAppRegisterToolBarPosition 
*/
enum {

	/** */
	kAVToolBarDockTop,

	/** */
	kAVToolBarDockBottom,

	/** */
	kAVToolBarDockLeft,

	/** */
	kAVToolBarDockRight,

	/** */
	kAVToolBarFloating
};
typedef ASEnum8 AVToolBarDockPosition;


/**
	An enumerated list of toolbar layouts. 
	@see AVAppRegisterToolBarPosition 
*/
enum {

	/** */
	kAVToolBarHorizontal,

	/** */
	kAVToolBarVertical,

	/** */
	kAVToolBarTwoColumn
};
typedef ASEnum8 AVToolBarLayout;

#if (ACRO_SDK_LEVEL >= 0x00060000)
/**
	A structure that describes the position of a toolbar. 
	@see AVAppRegisterToolBarPosition 

*/
typedef struct _t_AVToolBarPosition {

	/** The size of this structure. Set it to <code>sizeof(AVToolBarPositionRec)</code>. */
	ASSize_t	size;

	/** Specifies that the toolbar is to be <i>in-doc</i> (not shared). If <code>inDoc</code> is <code>true</code>, <code>dockPosition</code> cannot be floating. */
	ASBool	inDoc;

	/** The edge of the document window or monitor to which to attach this toolbar. */
	AVToolBarDockPosition	dockPosition;

	/** If the toolbar is to be floating, you can group it with another toolbar by specifying a name 
		for the floating window. You can set this to a constant string. 
	*/
	const char *floatingWindowName;

	/** The stack on which to insert the toolbar. Make this <code>-1</code> to open a new stack on the left or top, or ASMAXInt32 
		to open a new stack on the right or bottom. 
	*/
	ASInt32 stackNum;

	/** The number of pixels from the top or left edge of the stack from which to position the toolbar. If 
		ASMAXInt32, the toolbar will be positioned snugly behind other toolbars on the stack. If <code>-1</code>, it will 
		be positioned at the front. 
	*/
	ASInt32 offset;

	/** If multiple positions specify an offset of <code>-1</code> or ASMAXInt32, this field is used to further order them. 
		It controls the order in which the bars will be placed, not the visual order on the screen. If, for example, 
		two bars have an offset of <code>-1</code>, the one associated with the value in the lower order field will be 
		positioned first at the front of the bar. Then the one associated by the value in the higher order field 
		will also be positioned at the front of the bar, but will push the first one to the right. 
	*/
	ASInt32 order;

	/** If the toolbar is not <code>inDoc</code> and <code>dockPosition</code> is floating, you may end up creating a new window. Here is its frame. */
	AVScreenRect windowFrame;

	/** If a new window is called for, here is its layout. */
	AVToolBarLayout layout;

	/** Set this to <code>true</code> if the toolbar should be hidden by default. */
	ASBool hidden;

	/** Set this to <code>true</code> if the floating window in which the toolbar is located should be hidden by default. */
	ASBool windowHidden;

} AVToolBarPositionRec, *AVToolBarPosition;
#endif


/**
	Describes the preferred monitor to use when going full-screen 
	on a multi-monitor system. 
*/
enum {

	/** Use the monitor with the largest intersection. */
	kAVFullScreenLargestIntersection,

	/** Use the monitor with the most colors. */
	kAVFullScreenMostColors,

	/** Use the monitor with the widest screen. */
	kAVFullScreenWidest,

	/** Use the monitor with the tallest screen. */
	kAVFullScreenTallest,

	/** Use the monitor with the largest screen. */
	kAVFullScreenLargest,

	/** Use the monitor with the main screen. */
	kAVFullScreenMain,

	/** Enum terminator.*/
	kAVFullScreen_END_ENUM
};
typedef ASEnum8 AVFullScreenMonitor;


/**
	A data structure containing information about a client loaded 
	by the viewer. 
	@see AVExtensionAcquireInfo 
	@see AVExtensionReleaseInfo 

	@note For third-party (non-Adobe) clients, only <code>asaName</code>, 
	<code>bLoaded</code>, and <code>bCertified</code> are valid. 
*/
typedef struct _AVExtensionInfoRec {

	/** The registered name of the plug-in. */
	ASAtom asaName;					

	/** Always <code>true</code>, indicating that the plug-in was loaded. */
	ASBool bLoaded;					

	/** <code>true</code> if the plug-in is certified, <code>false</code> otherwise. */
	ASBool bCertified;				

	/** The major and minor versions of the plug-in. */
	AVVersionNumPart nMajorVersion, nMinorVersion;

	/** The creation timestamp on the plug-in. */
	char *cDate;						

	/** The path to the plug-in. */
	ASPathName aspFile;					

	/** A description of the plug-in. It may be <code>NULL</code>. */
	char *cDescription;					

	/** The legal text associated with the plug-in. It may be <code>NULL</code>. */
	char *cLegal;						

	/** The dependencies of the plug-in. */
	char *cDependencies;				
} AVExtensionInfoRec, *AVExtensionInfo;


/**
	Constants for use with AVPageViewUpdateInfoPanel(). 
	@see AVPageViewUpdateInfoPanel 
*/
enum {

	/** The plug-in is assuming control over the output of the info panel. */
	kAVInfoPanelLock,

	/** The plug-in is transferring control back to Acrobat to update the info panel. */
	kAVInfoPanelUnlock,

	/** The plug-in is passing the values that should be displayed in the info panel to Acrobat. */
	kAVInfoPanelRect
};
typedef ASEnum8 AVInfoPanelUpdateType;

/*********************************************************
 * AVBatch definitions
 *********************************************************/

#ifndef _T_AVBATCHCONTEXT
#define _T_AVBATCHCONTEXT

/**
	Placeholder only. Not currently implemented. 
*/
typedef struct _t_AVBatchContext *AVBatchContext;

#endif /* _T_AVBATCHCONTEXT */

/** For use with AVAppGetUUID(). */
enum
{

	/** The UUID for this user <i>for this install</i>. */
	kAVAppUserUUID,

	/** The UUID for the currently executing session.  */
	kAVAppSessionUUID 
};
typedef ASEnum8 AVAppUUIDType;


/** Icon types for AVSysGetIconFromFilename() and so on. */
enum
{

	/** */
	kAVSysSmallIcon,

	/** */
	kAVSysLargeIcon,
	
	/** */
	kAVSysHugeIcon
};
typedef ASEnum8 AVSysIconType;

#include "AVExpTObsolete2.h"  //types for old versions of Acrobat

/*******************************************************************************
 * AVSimpleSelProcs definitions - Simple Selection Server for PDFindSupport API
 *******************************************************************************/

#define AVSIMPLESEL_TYPE	"SimpleSelectHub"
/* AVSIMPLESEL_TYPE is the main selection type of the Simple Selection Servers that
   are registered by AVRegisterSimpleHiliteProc(). This selection type should be
   used in AVDocSetSelection() to identify the selection should be handled by the
   Simple Selection Server. The actual (selection) object type is deteremined by
   the client selection type stored in the AVSimpleSelObj and a corresponding hilite
   function is called by the Simple Selection Server.
   Example:
			void HiliteMyObject(AVDoc doc, MyObject data)
			{
				AVSimpleSelObj	selObject;
				selObject = AVSimpleSelObjCreate(ASAtomFromString("ABCD_MySelType"), &data, sizeof(data));
				AVDocSetSelection(doc, ASAtomFromString(AVSIMPLESEL_TYPE), selObject, <code>true</code>);
				AVDocShowSelection(doc);
			}
*/
/** */
typedef struct _t_AVSimpleSelObj	*AVSimpleSelObj;

/* Callback functions for text highlight, de-highlight, and destroy selection object.  */
/** */
typedef ACCBPROTO1 void (ACCBPROTO2 *AVSimpleSelHiliteProc)(AVSimpleSelObj selObj, AVDoc doc);
/** */
typedef ACCBPROTO1 void (ACCBPROTO2 *AVSimpleSelDeHiliteProc)(AVSimpleSelObj selObj, AVDoc doc);
/** */
typedef ACCBPROTO1 void (ACCBPROTO2 *AVSimpleSelDataDestroyProc)(AVSimpleSelObj selObj);

/** */
typedef struct _t_AVSimpleSelProcs {
	/** Set to <code>sizeof(AVSimpleSelProcsRec)</code>. */
	ASSize_t					size;			
	/** The sub-selection type. */
	const char					*type;			
	/** */
	AVSimpleSelHiliteProc		hiliteProc;
	/** */
	AVSimpleSelDeHiliteProc		deHiliteProc;
	/** */
	AVSimpleSelDataDestroyProc	destroyProc;
} AVSimpleSelProcsRec, *AVSimpleSelProcs;

/************************************************************************************\
|*																					*|
|*								  AVStatusItem										*|
|*																					*|
\************************************************************************************/
/** */
typedef struct _t_AVStatusItem *AVStatusItem;

/************************************************************************************\
|*																					*|
|*									 Undo 											*|
|*																					*|
\************************************************************************************/
/* Undo/redo stuff */
/** An opaque data type to be used with <code>AVUndo</code> APIs. */
typedef struct _t_AVUndo *AVUndo;	

/**
	Private data for use by callbacks in the AVUndoHandler. 
	
	@see AVUndoGetData 
	@see AVUndoNew 
	@see AVUndoSetData
*/
typedef void* AVUndoHandlerData;

/**
	A callback for AVUndoHandler. It is called when the user initiates 
	an Undo or Redo command. Use this to verify that the undo 
	record is still valid and the operation can be performed. 
	
	@param undo The undo record.
	@return <code>true</code> if the operation can be performed, <code>false</code> otherwise. 
	@see AVUndoExecuteProc 
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVUndoVerifyProc)
	(AVUndo undo);

/**
	A callback for AVUndoHandler. It is called when the undo object 
	is no longer needed. Use this to free any dynamic data that 
	was associated with the object by the handler. 
	@param undo The undo record.
	@see AVDocClearUndos 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVUndoReleaseProc)
	(AVUndo undo);

/* Performs the AVUndo. */
/** A callback for AVUndoHandler. It is called when the user initiates an Undo or Redo command
	and the AVUndoVerifyProc returns <code>true</code>. Use this to perform the requested operation.
	@param undo IN/OUT The undo record.
	@return <code>true</code> if the requested operation is performed successfully, <code>false</code> otherwise.
	@see AVUndoVerifyProc
*/
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *AVUndoExecuteProc)
	(AVUndo undo);

/**
	A callback for AVUndoHandler. It is called when the user initiates 
	an Undo or Redo command and the AVUndoVerifyProc() returns 
	true. Use this to return the user interface title string for the undo 
	record. 
	@param undo The undo record. 
	@param title (Filled by the method) The user interface title string 
	for the undo record, as a text object.
	@see AVUndoVerifyProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVUndoGetTitleProc)
	(AVUndo undo, ASText title);

/**
	A callback type for AVUndoHandler. The <code>beginUndoRedo</code> procedure 
	is called when the user initiates an Undo or Redo command 
	and the AVUndoVerifyProc() returns <code>true</code>. The <code>endUndoRedo</code> procedure 
	is called when execution of the operation is complete. Use 
	callbacks of this type to notify the handler that an undo 
	or redo operation is beginning or ending. 

	<p>These callbacks are optional. They can be used to allocate 
	and deallocate memory for the operations, for example, or, 
	when grouping undo records, to suspend user interface updates during 
	the operation. </p>
	@param doc The document containing the undo record. 
	@param bUndo <code>true</code> if the user initiated an undo operation, 
	<code>false</code> if it is a redo operation.
	@see AVUndoGetTitleProc 
	@see AVUndoExecuteProc 
	@see AVUndoVerifyProc 
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *AVUndoBeginEndProc)
	(AVDoc doc, ASBool bUndo);

/**
	Contains a callback procedure for an AVUndo record that performs 
	the undo and redo operations. 
	@see AVDocBeginUndoOperation 
	@see AVDocClearUndos 
	@see AVDocEndUndoOperation 
	@see AVDocGetTopUndo 
	@see AVUndoGetType 
	@see AVUndoNew 
*/
typedef struct _t_AVUndoHandler {
	/** The size of the data structure. It must be set to <code>sizeof(AVUndoHandlerRec)</code>. */
	ASSize_t	size;
	/** The type of the undo record. It can be any client-defined string. It can be
	matched for retrieval by AVDocGetTopUndo(). 
	*/
	const char *type;
	/** */
	AVUndoVerifyProc		VerifyUndo;
	/** */
	AVUndoExecuteProc		Undo;
	/** */
	AVUndoVerifyProc		VerifyRedo;
	/** */
	AVUndoExecuteProc		Redo;
	/** */
	AVUndoGetTitleProc		GetUndoTitle;
	/** */
	AVUndoGetTitleProc		GetRedoTitle;
	/** */
	AVUndoReleaseProc		Release;
	/** */
	AVUndoBeginEndProc		BeginUndoRedo;
	/** */
	AVUndoBeginEndProc		EndUndoRedo;
} AVUndoHandlerRec, *AVUndoHandler;

/**
	An ink value for use in color separation methods. 
	@see AVPageViewGetPixelInformationAtPoint
*/
typedef struct AVInkValue
{
	/** */
    ASAtom         inkName;
    /** */
    float          value;
} AVInkValue;

// If a command handler implements these properties
// a toolbar button or menu item can be generated
// from them directly using AVMenuItemFromCommand
// or AVToolButtonFromCommand.
#define kAVMenuKeyName "Menu:Name"
#define kAVMenuKeyTitle "Menu:Title"
#define kAVMenuKeyTitleChanges "Menu:TitleChanges"
#define kAVMenuKeyIcon "Menu:Icon"
#define kAVMenuKeyEnabled "Menu:Enabled"
#define kAVMenuKeyMarked "Menu:Marked"
#define kAVMenuKeyVisible "Menu:Visible"
#define kAVMenuKeyShortcut "Menu:Shortcut"
#define kAVMenuKeyShortcutFlags "Menu:ShortcutFlags"
#define kAVMenuKeyHelpText "Menu:HelpText"

#define kAVToolButtonKeyName "ToolButton:Name"
#define kAVToolButtonKeyIcon "ToolButton:Icon"
#define kAVToolButtonKeyMenuIcon "ToolButton:MenuIcon"
#define kAVToolButtonKeyEnabled "ToolButton:Enabled"
#define kAVToolButtonKeyMarked "ToolButton:Marked"
#define kAVToolButtonKeyVisible "ToolButton:Visible"
#define kAVToolButtonKeyShortcut "ToolButton:Shortcut"
#define kAVToolButtonKeyHelpText "ToolButton:HelpText"
#define kAVToolButtonKeyExternal "ToolButton:External"
#define kAVToolButtonKeyInternal "ToolButton:Internal"
#define kAVToolButtonKeyMenu "ToolButton:Menu"
#define kAVToolButtonKeyLabel "ToolButton:Label"
#define kAVToolButtonKeyLabelPriority "ToolButton:LabelPriority"

/**
	A set of priority values for a tool bar button label text. 
	The priority determines the preference order in which labels 
	are shown when a toolbar is too short to hold all of the 
	button labels. 
	@see AVToolButtonGetLabelText 
	@see AVToolButtonSetLabelText
*/
enum {
	/** */
	kAVButtonPriorityOffExtraLow = 100,
	/** */
	kAVButtonPriorityOffLow = 200,
	/** */
	kAVButtonPriorityOffNormal = 300,
	/** */
	kAVButtonPriorityOffHigh = 400,
	/** */
	kAVButtonPriorityOffExtraHigh = 500,

	/** */
	kAVButtonPriorityOnExtraLow = 600,
	/** */
	kAVButtonPriorityOnLow = 700,
	/** */
	kAVButtonPriorityOnNormal = 800,
	/** */
	kAVButtonPriorityOnHigh = 900,
	/** */
	kAVButtonPriorityOnExtraHigh = 1000,
	
	/** */
	kAVButtonPriorityAlwaysOn = 1100
};
typedef ASEnum16 AVToolButtonLabelPriority;

// If a command returns these properties it will automatically
// be included as a Task in the task bar. It must also implement
// the properties required to create a toolbar button, described
// above.
#define kAVCommandKeyIsTask "IsTask"
#define kAVTaskKeyToolBarName "Task:Toolbar"
#define kAVTaskKeyDoesWork "Task:DoesWork"
#define kAVTaskKeyButtonOrder "Task:ButtonOrder"
#define kAVTaskKeyHowToPanelName "Task:HowToPanel"
#define kAVTaskKeyButtonDefaultUserVisible "Task:ButtonDefaultUserVisible"

/** */
enum {
	/** */
	kAcrobatBasicsSortKey = 100,
	/** */
	kAVCreateSortKey = 200,
	/** */
	kAVCombineSortKey = 250,
	/** */
	kAVExportSortKey = 275,
	/** */
	kAVSecureSortKey = 300,
	/** */
	kAVSignSortKey = 400,
	/** */
	kAVFormSortKey = 500,
	/** */
	kAVReviewAndCommentSortKey = 600,
	/** */
	kAV3DSortKey = 650,
	/** */
	kAVEngineeringToolsSortKey = 700,
	/** */
	kAVPrintProductionSortKey = 800,
	/** */
	kAVHowToSortKey = ASMAXUns32
};
typedef ASUns32 AVHowToTopicSortKey;

/** This enumerates the order of the built-in task buttons. */
enum {
	/** */
	kAVeBookTaskOrder = 100,
	/** */
	kAVNewDocumentTaskOrder = 200,
	/** */
	kAVCombineFilesTaskOrder = 300,
	/** */
	kAVCollabTasksTaskOrder = 350,
	/** */
	kAVExportTaskOrder = 400,
	/** */
	kAVMeetingTaskOrder = 500,
	/** */
	kAVSecureTaskOrder = 600,
	/** */
	kAVSignTaskOrder = 700,
	/** */
	kAVFormTaskOrder = 800,
	/** */
	kAVMultimediaTaskOrder = 850,
	/** */
	kAVReviewAndCommentTaskOrder = 900,
	/** */
	kAVSendForReviewTaskOrder = 1000,
	/** */
	kAVPictureTasksTaskOrder = 1100,

};
typedef ASEnum16 AVTaskOrderNumbers;

/** This enumerates the order of the toolbars listed in the Tools menu. */
enum {
	/** */
	kAVCommentingMenuOrder = 100,
	/** No longer used, as of the Acrobat 8.0 release. */
	kAVAdvCommentingMenuOrder = 200,
	/** */
	kAVSelectionMenuOrder = 300,
	/** */
	kAVZoomMenuOrder = 400,
	/** */
	kAVNavigationMenuOrder = 500,
	/** */
	kAVAdvEditingMenuOrder = 600,
	/** */
	kAVMeasuringMenuOrder = 700,
	/** */
	kAVRotateViewMenuOrder = 800,
	/** */
	kAVFindMenuOrder = 900,
	/** */
	kAVEndMenuOrder = kASMAXEnum16
};
typedef ASEnum16 AVToolsMenuOrderNumbers;

// If a command handler implements these properties, doc status
// icons can be generated from the AVCommand.
#define kAVDocStatusKeyName "DocStatus:Name"
#define kAVDocStatusKeyTipText "DocStatus:TipText"
#define kAVDocStatusKeyHelpText "DocStatus:HelpText"
#define kAVDocStatusKeyAlwaysInformText "DocStatus:PrefText"
#define kAVDocStatusKeySmallIcon "DocStatus:SmallIcon"
#define kAVDocStatusKeyLargeIcon "DocStatus:LargeIcon"
#define kAVDocStatusKeyDefaultsToChecked "DocStatus:DefaultsToChecked"

// If a command returns these properties, it will automatically
// be queried when the document status display is updated.
#define kAVCommandKeyIsDocStatus "IsDocStatus"

/**
	Constants that specify language format values for use in 
	AVAppLanguageParams. 
	@see AVAppGetLanguageWithParams
*/
enum {
 /** */
 kAVAppLanguage_RFC1766,
 /** */
 kAVAppLanguage_LCID,
 /** */
 kAVAppLanguage_ISO4Char,	
 /** */
 kAVAppLanguage_RFC3066Bis,
 /** */
 kAVAppLanguage_ISO4Variant,
 /** */
 kAVAppLanguage_EFIPrint,
 /** */
 kAVAppLanguage_MaxSelector
};
typedef ASEnum16 AVAppLanguageFormat;

/**
	Constants that specify if the call to AVAppGetLanguageWithParams()
	applies to the application or to the fallback language.
*/
enum {
      kAVAppLanguage_app,
      kAVAppLanguage_fallback,
      kAVAppLanguage_langpack
};
typedef ASEnum16 AVAppLanguageSelector;


#define kMaxLanguageNameLen 27
/** A data structure containing language format information in which to return the language in
	use for an application.
*/
typedef struct _AVAppLanguageParamsRec {
	/** The size of the data structure. It must be set to <code>sizeof(AVAppLanguageParamsRec)</code>.*/
	ASSize_t size;
	/** The format in which to specify the language.*/
	AVAppLanguageFormat kLangFormat;
	/** The returned language value in the specified format. For
		details of language values, see Language Codes.
		@ref LanguageCodes
	*/
	char szAVAppLanguage[kMaxLanguageNameLen];
	
	AVAppLanguageSelector kLangSelector;

	ASInt32 langID;

} AVAppLanguageParamsRec, *AVAppLanguageParams;

/** Constants used to define the set of bookmarks retrieved by AVDocGetBookmarks(). More than
	one constant can be passed into the API by <code>OR</code>'ing them. 
	@example <code>kAVBookmarkFilterSelected | kAVBookmarkFilterFocus</code>
*/
enum {
 kAVBookmarkFilterSelected = 1,
 kAVBookmarkFilterFocus = 2
};
typedef ASEnum16 AVBookmarkFilter;


/**
	Describes the paragraph direction. 
*/
enum {

	kAVParagraphDirectionLeftToRight,

	kAVParagraphDirectionRightToLeft,

	kAVParagraphDirectionSameAsDocument,

	/** Enum terminator.*/
	kAVParagraphDirection_END_ENUM
};
typedef ASEnum8 kAVParagraphDirection;

/* Section name and keys to be used with AVAppGetPref routines  */
/** International section name. */
#define kSectionPrefsIntl				"Intl"
/** Key name for Target Language on Re-Launch. */
#define kKeyPrefsIntlTargetLanguage		"IntlTargetLanguage"
/** Key name for paragraph direction. */
#define kKeyPrefsIntlParagraphDir		"ParaDir"
/** Key name for "enable Right to left Options". */
#define kKeyPrefsIntlRTLUI				"RTLUI"
/** Key name for "enable Digits UI". */
#define kKeyPrefsIntlDigitsUI			"DigitsUI"
/** Key name for "Current Keyboard Mode for Digits". */
#define kKeyPrefsIntlNationalDigits		"National"
/** Key name for "enable UI Mirroring options" */
#define kIsUIMirrored					"IsUIMirrored"
/** Key name for "enable direction switching for PDFEdit(content editing) context menu" */
#define kKeyPrefsTouchUpComplexScript			"ComplexScript"
/** Key name for "enable default paragraph direction for PDFEdit(content editing)" */
#define kKeyPrefsTouchUpParagraphDirection		"ParagraphDirection"
/** Key name for "enable Hindi digit option for PDFEdit(content editing)" */
#define kKeyPrefsTouchUpHindiDigit				"HindiDigit"
/** Key name for "enable Ligature option for PDFEdit(content editing)" */
#define kKeyPrefsTouchUpLigature				"Ligature"

/* Structures to be used with the AVDocSaveOptimized routine */
// Downsampling algorithms: algorithms supported by the PDF Optimizer
/**
	@product_exclude RDR
*/
enum
{
	kPDFOptNoDownsampling=0, // disable downsampling of Image XObjects
	kPDFOptAverage,			 // Average downsampling
	kPDFOptSubsampling,		 // Subsampling
	kPDFOptBicubic			 // Bicubic downsampling
};
typedef ASEnum16 PDFOptDownsamplingAlgo;

// Compression algorithms: algorithms supported by the PDF Optimizer.
/**
	@product_exclude RDR
*/
enum
{
	kPDFOptNoRecompression=0,// disable re-compression of image XObjects. It 
	// will retain the original filters.
	kPDFOptJpeg2000,		 // available for color and grayscale images
	kPDFOptJpeg,			 // available for color and grayscale images
	kPDFOptFlate,			 // available for color, grayscale & monochrome images
	kPDFOptJBIG2,			 // available for monochrome images
	kPDFOptCCITT3,			 // available for monochrome images
	kPDFOptCCITT4,			 // available for monochrome images
	kPDFOptRunLength		 // available for monochrome images
};
typedef ASEnum16 PDFOptCompressionAlgo;

// Compression quality: levels of compression to be applied to specified compression 
// filters. 
// For JBIG2 specifying any value other than kPDFOptLossless implies the application 
// of lossy compression. [XXX: if it is felt that bit flags would provide for a 
// more appropriate implementation, we could switch to those]
// For the filters not specified here, compression quality is ignored.
/**
	@product_exclude RDR
*/
enum
{
	kPDFOptMinimumQlty=0,	// meaningful for JBIG2, Jpeg and Jpeg2000
	kPDFOptLowQlty,			// meaningful for JBIG2, Jpeg and Jpeg2000
	kPDFOptMediumQlty,		// meaningful for JBIG2, Jpeg and Jpeg2000
	kPDFOptHighQlty,		// meaningful for JBIG2, Jpeg and Jpeg2000
	kPDFOptMaximumQlty,		// meaningful for JBIG2, Jpeg and Jpeg2000
	kPDFOptLossless			// meaningful for JBIG2 and Jpeg2000
};
typedef ASEnum16 PDFOptCompressionQlty;

/** Image optimization options 
	@product_exclude RDR
*/
typedef struct _t_PDFOptImageOptions
{
	/** The size of the data structure. It must be set to <code>sizeof(PDFOptImageOptionsRec)</code>. */
	ASSize_t				size;

	/** The downsampling algorithm to be used on the image.
		@see PDFOptDownsamplingAlgo
	*/
	PDFOptDownsamplingAlgo  enmDownsamplingAlgo;

	/** Downsample to the specified ppi. */
	ASInt32					ppiDownsampleTo;	

	/** Downsample only if the image is above this ppi. */
	ASInt32					ppiDownsampleAbove;

	/** Compression algorithms: recompress using this algorithm. The rules for filter 
		availability for an image type should be followed.
		@see PDFOptCompressionAlgo
	*/
	PDFOptCompressionAlgo	enmCompressionAlgo; 

	/** Compression quality: recompress to this quality level. It is ignored if it is not relevant 
		for the filter type.
		@see PDFOptCompressionQlty
	*/
	PDFOptCompressionQlty	enmCompressionQlty;

	/** Use this tile size if compressing using JPEG2000. It is ignored for other filters.
		Its value should lie between <code>128</code> and <code>2048</code>. */
	ASInt32					nTileSize;
} PDFOptImageOptionsRec, *PDFOptImageOptions;

/** Transparency flattening options */
typedef struct _t_PDFOptFlattenTransparencyOptions
{
	/** The size of the data structure. It must be set to <code>sizeof(PDFOptFlattenTransparencyOptionsRec)</code>. */
	ASSize_t				size;

	/** The percentage of vector information that is to be preserved. Lower values will 
		cause higher rasterization of vectors.
		<p>Being a percentage, its value should lie between <code>0</code> and <code>100</code>.</p> 
	*/
	ASInt32					pctRasterVectorBalance;

	/** Specfies the pixels per inch for flattening edges of atomic regions.
		Its value should lie between 1 and 9600.
	*/
	ASInt32					ppiLineArtAndText;

	/** Specfies the pixels per inch for flattening the interiors of atomic regions.
		Its value should lie between 1 and 1200.
	*/
	ASInt32					ppiGradientAndMesh;

	/** If <code>true</code>, it outputs text outlines instead of native text. */
	ASBool					bConvertText;

	/** If <code>true</code>, it converts strokes to outlines. */
	ASBool					bConvertStrokes;

	/** If <code>true</code>, it ensures that boundaries between vector and rasterized artwork fall along 
		object paths. */
	ASBool					bClipComplexRegions;

	/** If <code>true</code>, it preserves overprint. */
	ASBool					bPreserveOverprint;
}PDFOptFlattenTransparencyOptionsRec, *PDFOptFlattenTransparencyOptions;

// Acrobat compatibility version: The Acrobat version to make the PDF compatible with.
/**
	@product_exclude RDR
*/
enum
{
	kPDFOptRetainVersion=0,
	kPDFOptAcrobat4,
	kPDFOptAcrobat5,
	kPDFOptAcrobat6,
	kPDFOptAcrobat7,
	kPDFOptAcrobat8,
	kPDFOptAcrobat9,
	kPDFOptAcrobat10
};
typedef ASEnum16 PDFOptPDFVersion;

// Object compression options
/**
	@product_exclude RDR
*/
enum
{
	kPDFOptUntouchedCompression=0,  // available for Acrobat 6 or above compatibility
	kPDFOptFullCompression,			// available for Acrobat 6 or above compatibility
	kPDFOptPartialCompression,		// available for all versions of Acrobat
	kPDFOptRemoveCompression		// available for all versions of Acrobat
};
typedef ASEnum16 PDFOptObjectCompression;

/**
	@product_exclude RDR
*/
typedef struct _t_PDFOptParams
{
	/** The size of the data structure. It must be set to <code>sizeof(PDFOptParamsRec)</code>. */
	ASSize_t		size;

	/** The path to which the file is to be saved. */
	ASPathName		asPathDest;

	/** The file system. If it is <code>NULL</code>, uses the <code>fileSys</code> of the document's current backing file.
	*/
	ASFileSys		fileSys;

	/** The progress monitor. Use AVAppGetDocProgressMonitor() to obtain the default. 
		It may be <code>NULL</code>.
		@see AVAppGetDocProgressMonitor
	*/
	ProgressMonitor progMon;

	/** A pointer to user-supplied data to pass to <code>progMon</code> each time it is called. It must be
		<code>NULL</code> if <code>progMon</code> is <code>NULL</code>. */
	void *			progMonClientData;

	/** Acrobat compatibility version.
		@see PDFOptPDFVersion
	*/
	PDFOptPDFVersion enmAcrobatVersion;

	/** Image optimization options for color XObjects. The structure should be filled up 
		keeping in mind the algorithms supported by color images.
		@see PDFOptImageOptionsRec
	*/
	PDFOptImageOptionsRec	imageOptionsColor;

	/** Image optimization options for grayscale XObjects. The structure should be filled 
		up keeping in mind the algorithms supported by grayscale images.
		@see PDFOptImageOptionsRec
	*/
	PDFOptImageOptionsRec	imageOptionsGrayscale;

	/** Image optimization options for monochrome XObjects. The structure should be filled 
		up keeping in mind the algorithms supported by monochrome images.
		@see PDFOptImageOptionsRec
	*/
	PDFOptImageOptionsRec	imageOptionsMonochrome;

	/** An array of PDFont objects. It is a list of fonts that should be unembedded. It may be <code>NULL</code>.
	*/
	PDFont					*arrPDFontsToUnembed;

	/** The length of the <code>arrPDFontsToUnembed</code> array.
	*/
	ASInt32					cPDFontsToUnembed;

	/** A pointer to PDFOptFlattenTransparencyOptions. It specifies options to flatten 
		transparent regions of the document.
		It can be <code>NULL</code>, in which case transparent regions will be preserved.
		@see PDFOptFlattenTransparencyOptionsRec
	*/
	PDFOptFlattenTransparencyOptions pdfOptFlattenTransparencyOptions;

	/** If <code>true</code>, it removes form submissions, import actions, and reset actions. */
	ASBool					bRemoveFormActions;

	/** If <code>true</code>, it flattens form fields. */
	ASBool					bFlattenFormFields;

	/** If <code>true</code>, it removes JavaScript actions. */
	ASBool					bRemoveJavascriptActions;

	/** If <code>true</code>, it removes alternate images. */
	ASBool					bRemoveAlternateImages;

	/** If <code>true</code>, it removes embedded thumbnails.*/ 
	ASBool					bRemoveThumbnails;

	/** If <code>true</code>, it removes document tags.*/
	ASBool					bRemoveDocumentTags;

	/** If <code>true</code>, it attempts to merge lines made to look like curves into a single curve. */
	ASBool					bSmoothenLines;

	/** If <code>true</code>, it attempts to merge fragments of an image into a single image. */
	ASBool					bMergeImageFragments;

	/** If <code>true</code>, it removes embedded print settings from the document. */
	ASBool					bRemovePrintSettings;

	/** If <code>true</code>, it removes all embedded search indexes from the document. */
	ASBool					bRemoveSrchIndex;

	/** If <code>true</code>, it removes all bookmarks from the document. */
	ASBool					bRemoveBookmarks;

	/** If <code>true</code>, it removes comments and form widgets. */
	ASBool					bRemoveCommentsAndWidgets;

	/** If <code>true</code>, it removes document information and metadata. */
	ASBool					bRemoveDocInfoAndMetadata;

	/** If <code>true</code>, it removes object data. */
	ASBool					bRemoveObjectData;

	/** If <code>true</code>, it removes file attachments. */
	ASBool					bRemoveFileAttachments;

	/** If <code>true</code>, it removes external cross references. */
	ASBool					bRemoveCrossRefs;

	/** If <code>true</code>, it removes private data of other applications. */
	ASBool					bRemovePrivateData;

	/** If <code>true</code>, it deletes hidden layers and flattens visible layers. */
	ASBool					bFlattenVisibleLayers;

	/** Object compression options. Its value should be among the values 
		supported by the acrobatVersion option.
		@see PDFOptObjectCompression
	*/
	PDFOptObjectCompression enmObjectCompression;

	/** If <code>true</code>, it encodes all unencoded streams with the Flate filter. */
	ASBool					bUnencodedToFlate;

	/** If <code>true</code>, it reencodes all LZW encoded streams with the Flate filter.*/
	ASBool					bLZWToFlate;

	/** If <code>true</code>, it removes all invalid bookmarks. */
	ASBool					bRemoveInvalidBookmarks;

	/** If <code>true</code>, it removes all invalid links. */
	ASBool					bRemoveInvalidLinks;

	/** If <code>true</code>, it removes all unreferenced named destinations. */
	ASBool					bRemoveUnreferencedNamedDests;

	/** If <code>true</code>, it optimizes the file for fast web view.*/
	ASBool					bLinearize;

	/** If <code>true</code>, image optimization operations would be applied only if they 
	lead to a reduction in image size. The exception will be cases where recompression is 
	required due to version incompatibility. **/
	ASBool					bSkipIrreducibleImages;

	/** If <code>true</code>, all embedded fonts will be subsetted. **/
	ASBool					bSubsetEmbeddedFonts;

	/** If <code>true</code>, content streams of all pages in the file are optimized. **/
	ASBool					bOptimizeContentStms;

} PDFOptParamsRec, *PDFOptParams;

typedef void (*PluginExecProc)(void*);

typedef struct {
	ASUns32 size;
	union {
		const char* menuID;
		const char* notification;
		ASAtom buttonID;
	};
} ExecProcData;

typedef struct {
	ASUns32 size; //size of the final struct.  A notification may contain more data but will always have at least the notification name
	const char* notification;  //the name of the notification
} AVNotificationDataRec, *AVNotificationData;
typedef void (*AVCustomNotificationProc)(AVNotificationData data, void* clientData);

// File Save Handle (refer AVAppBeginSave/AVAppEndSave/AVAppCancelSave for usage)
typedef void *	AVAppFileSaveHandle;


/** constants for requesting Draw Context type for AVPageViewAcquireDrawContext */
typedef enum _t_DrawContextType {
#if WIN_PLATFORM
	/** Windows only: HWND */
	kWinHWNDType,
	/** Windows only: HDC */
	kWinHDCType
#endif
#if MAC_PLATFORM
	/** Mac only: CGContext */
	kMacCGContextType	
#endif
#if UNIX_PLATFORM
	/** Unix only: Widget */
	kUnixWidgetType
#endif

} DrawContextType;

/* AVPlatformWindowRef */
typedef struct _t_AVPlatformWindowRef *AVPlatformWindowRef;

/* ADMWindowRef */
typedef struct _t_ADMWindowRef *ADMWindowRef;

#ifdef __cplusplus
}
#endif

#endif /* _H_AVExpT */
