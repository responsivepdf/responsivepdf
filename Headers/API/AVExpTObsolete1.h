/*
** AVExpTObsolete.h
**
** This file contains types used in former versions of Acrobat.  By defining ACRO_SDK_LEVEL
** to the latest version, you will use the latest types and routines.  Some of these types are no longer
** used in any Acrobat source while others may have been redefined. These are provided here to allow 
** existing plug-in code to compile without changes.  Backward compatibility can be maintained by adding
** AVCompat.cpp to your plugin which will handle passing current structures and callbacks to older
** versions of Acrobat.
**
** This file is furnished to you by Adobe Systems Incorporated under the terms of the 
** Acrobat (r) Plug-insSoftware Development Kit License Agreement.
** Copyright (C) 1994-2001,2003,2006 Adobe Systems Inc.  All Rights Reserved.
*/

/* Unused, but preserved here to ensure legacy plugins still compile */
enum
{
	kAVFavToolsFlagOkInternal	= 1 << 0,	// It is ok for the tool to be a favorite in a non-external situation
	kAVFavToolsFlagOkExternal	= 1 << 1	// It is ok for the tool to be a favorite in an external situation (eg: the web browser)
};

typedef AVTFlagBits AVFavToolFlags;

/*
** Note that all of the types are prefixed by "old"  The recommended type to use does not begin with "old"
** You should not use any of these types directly.  The AVExpT.h file will map types to one or more old types
** if you do not have ACRO_SDK_LEVEL set to the latest version
*/
/* oldAVRect provided for backward compatibility only, use AVRect */
typedef struct oldAVRect {
	ASInt16 left;
	ASInt16 top;
	ASInt16 right;
	ASInt16 bottom;
} oldAVRect, *oldAVRectP;

/* oldQuad provided for backward compatibility only, use Quad */
typedef struct _t_oldQuad {
	/** */
	ASInt16 tlh, tlv;
	/** */
	ASInt16 trh, trv;
	/** */
	ASInt16 blh, blv;
	/** */
	ASInt16 brh, brv;
} oldQuad;

typedef ASInt32 AVlCoord;  /* use AVDevCoord instead, unless you need to support the 3 32-bit calls prior to Acrobat 6.0 AND are using ACRO_SDK_LEVEL=1*/
typedef ASInt32 AVlDragType; /* only used in obsolete calls.  Use AVDragType instead */

#if !defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)
typedef struct _t_oldAVDocSelectionServer *AVDocSelectionServer;
typedef struct _t_oldAVAnnotHandler *AVAnnotHandler;
typedef struct _t_oldAVTool *AVTool;
typedef struct _t_oldAVWindowHandler *AVWindowHandler;
typedef struct _t_oldAVDocViewDef *AVDocViewDef;
typedef struct _t_oldAVWindow *AVWindow;
typedef oldAVRect AVRect;
typedef oldAVRectP AVRectP;

typedef struct _t_AVRect32 {
	ASInt32 left;
	ASInt32 top;
	ASInt32 right;
	ASInt32 bottom;
} AVRect32, *AVRect32P;

#if UNIX_PLATFORM
typedef struct _t_ASPlatformPrinterSpec {
	ASSize_t size;							/* set this to be the size of this struct */
	char *printerName;						/* name of a printer */
	/* If baseAddr is non-NULL, then print a bitmap image to the baseAddr */
	ASUns8 *baseAddr;				
	AVBufferSize rowBytes;
	AVBufferSize depth;		
	AVRect32 bounds;
} ASPlatformPrinterSpecRec, *ASPlatformPrinterSpec;
#endif /* UNIX_PLATFORM */

typedef struct _t_AVAnnotOpData {
	/* Set by the viewer to the size of this record. */
	ASSize_t size;

	/* If the operation is kAVAnnotShowMenu, provides the default
	   location of the menu in AV device coordinates.
	*/
	ASInt32 x;
	ASInt32 y;

	void * clientData;

} AVAnnotOpDataRec, *AVAnnotOpData;

#define kAVEmitTransferFuncs 0x8000	/* emit transfer functions in PDF, use kAVSuppressTransfer before or after 5.0, both on 5.0 */
/** (5.0 only) When set, this flag causes special handling of one- and four-component ICC profiles, 
	the same as that done when the Print ICC colors as Device colors checkbox is set in the Advanced print dialog. 
	@note Do not convert the ICC profile to a color space array when printing PostScript with PostScript color management on. 
*/
#define kAVPrintICCColorsAsDevice	0x00010000

#endif

typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVPageViewDrawProc)(AVPageView pageView, oldAVRect* updateRect, void*data);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVPageViewClickProc)(AVPageView pageView, ASInt16 x, ASInt16 y, AVFlagBits16 flags, AVTCount clickNo, void*data);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVPageViewCursorProc)(AVPageView pageView, ASInt16 x, ASInt16 y, void* data);

typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVDocSelectionGetAVRectProc)(AVDoc doc, PDPageNumber pageNo, oldAVRect* rect, void* data);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVDocSelectionShowMenuProc)(AVDoc doc, void *data, ASInt16 x, ASInt16 y);

typedef struct _t_oldAVAnnotHandler *oldAVAnnotHandler;

typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVAnnotHandlerDoClickProc)(oldAVAnnotHandler annotHandler, PDAnnot hitAnnot,
                     AVPageView pageView,
					ASInt16 xHit, ASInt16 yHit,
					AVFlagBits16 flags,
					AVTCount clickNo);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVAnnotHandlerAdjustCursorProc)(oldAVAnnotHandler annotHandler, PDAnnot anAnnot,
  					AVPageView pageView, ASInt16 xHit, ASInt16 yHit);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVAnnotHandlerPtInAnnotViewBBoxProc)(oldAVAnnotHandler annotHandler, AVPageView pageView,
                   PDAnnot anAnnot, ASInt16 xHit, ASInt16 yHit);
                   
typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVAnnotHandlerGetAnnotViewBBoxProc)(oldAVAnnotHandler annotHandler, AVPageView pageView,
                   PDAnnot anAnnot, oldAVRect *bbox); 

typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVAnnotHandlerDrawExProc)(
	oldAVAnnotHandler annotHandler, 
	PDAnnot anAnnot, 
	AVPageView pageView,
	oldAVRect *updateRect);


typedef struct _t_oldAVTool *oldAVTool;
// although oldAVToolGetLabelProc is deprecated, it is available for use to modern plugins to provide tool labels to legacy plugins
#if (ACRO_SDK_LEVEL >= 0x00060000)
typedef struct _t_AVTool *AVTool;
typedef ACCBPROTO1 ASConstText (ACCBPROTO2 *oldAVToolGetLabelProc)(AVTool tool);
#endif

typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAdjustCursorProcType)(oldAVTool tool, AVPageView pageView, ASInt16 x, ASInt16 y);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldDoClickProcType)(oldAVTool tool, AVPageView pageView,
					ASInt16 xHit, ASInt16 yHit,
					AVFlagBits16 flags,
					AVTCount clickNo);

typedef struct _t_oldAVWindowHandler *oldAVWindowHandler;
typedef struct _t_oldAVWindow *oldAVWindow;
typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVWindowMouseDownProc)(oldAVWindow win, ASInt16 x, ASInt16 y, void *platformEvent);
typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVWindowDrawProc)(oldAVWindow win, const oldAVRect *rect);
typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVWindowWillBeResizedProc)(oldAVWindow win, oldAVRect *newFrame);
typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVWindowAdjustCursorProc)(oldAVWindow win, ASInt16 x, ASInt16 y);
typedef ACCBPROTO1 void (ACCBPROTO2 *oldAVWindowDidResizeProc)(oldAVWindow win, const oldAVRect *newFrame);

#if !defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)
typedef oldAVPageViewDrawProc AVPageViewDrawProc;
typedef oldAVPageViewClickProc AVPageViewClickProc;
typedef oldAVPageViewCursorProc AVPageViewCursorProc;

typedef oldAVDocSelectionGetAVRectProc AVDocSelectionGetAVRectProc;
typedef oldAVDocSelectionShowMenuProc AVDocSelectionShowMenuProc;

typedef oldAdjustCursorProcType AdjustCursorProcType;
typedef oldDoClickProcType DoClickProcType;

typedef oldAVWindowMouseDownProc AVWindowMouseDownProc;
typedef oldAVWindowDrawProc AVWindowDrawProc;
typedef oldAVWindowWillBeResizedProc AVWindowWillBeResizedProc;
typedef oldAVWindowAdjustCursorProc AVWindowAdjustCursorProc;
typedef oldAVWindowDidResizeProc AVWindowDidResizeProc;
#endif

typedef ACCBPROTO1 ASBool (ACCBPROTO2 *oldAVAuxDataPerformProc)(ASAtom auxDataType, void *auxData, AVTBufferSize auxDataLen, AVDoc avDoc);

typedef struct _t_oldAVAuxDataHandler {                                          

	/** The size of the data structure. It must be set to <code>sizeof(AVAuxDataHandlerRec)</code>. */
	ASSize_t size;

	/** Called with auxiliary data when a client calls AVDocSendAuxData(). This proc should perform whatever 
		action is required for the auxiliary data.
	*/
	oldAVAuxDataPerformProc PerformProc; 
} oldAVAuxDataHandlerRec, *oldAVAuxDataHandler;                                     
#if !defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00090000)
typedef oldAVAuxDataPerformProc AVAuxDataPerformProc;
typedef oldAVAuxDataHandlerRec AVAuxDataHandlerRec;
typedef oldAVAuxDataHandler AVAuxDataHandler;
#endif
