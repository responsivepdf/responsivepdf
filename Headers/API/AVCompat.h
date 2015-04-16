/*
** AVCompat.h
**
** Code to call old functions compatibly from current SDK
**
** If you are getting link errors saying you need some "CompatStub" routines, you need to make a decision.

** 1) If you want to run on older versions of Acrobat, add the AVCompat.cpp file to your project.  This file
** will accept calls using the current 32-bit values and structures and change them to 16-bit for calling
** older versions of Acrobat.

** 2) If you do not need to run on older versions of Acrobat, you need to change the minimum required 
** PI_ACROVIEW_VERSION to be higher than what you have (e.g. switch from AcroViewHFT_VERSION_5 to AcroViewHFT_VERSION_6)
** this is a #define typically set very early.

** This file is furnished to you by Adobe Systems Incorporated under the terms of the 
** Acrobat (r) Plug-ins Software Development Kit License Agreement.
** Copyright (C) 2001,2003,2006 Adobe Systems Inc.  All Rights Reserved.
**
*/

#ifndef _H_AVCompat
#define _H_AVCompat

#ifdef __cplusplus
extern "C" {
#endif

ACCB1 ASBool ACCB2 AVDocRegisterSelectionServerCompatStub(AVDocSelectionServer server);
ACCB1 AVDoc ACCB2 AVDocOpenFromFileCompatStub(ASPathName pathName, ASFileSys fileSys, const ASText tempTitle);
ACCB1 AVDoc ACCB2 AVDocOpenFromFileWithParamsCompatStub(ASPathName pathName, ASFileSys fileSys,
	const ASText tempTitle, AVDocOpenParams params);
ACCB1 AVDoc ACCB2 AVDocOpenFromPDDocCompatStub(PDDoc pdDoc, const ASText tempTitle);
ACCB1 AVDoc ACCB2 AVDocOpenFromPDDocWithParamsCompatStub(PDDoc pdDoc, const ASText tempTitle, AVDocOpenParams params);
ACCB1 AVDoc ACCB2 AVDocOpenFromASFileWithParamsCompatStub(ASFile file, const ASText tempTitle, AVDocOpenParams params);
ACCB1 void ACCB2 AVDocGetViewDefCompatStub(AVDoc doc, AVDocViewDef viewDef);
ACCB1 void ACCB2 AVDocSetViewDefCompatStub(AVDoc doc, AVDocViewDef viewDef);
ACCB1 void ACCB2 AVAppRegisterForPageViewDrawingCompatStub(AVPageViewDrawProc proc, void* data);
ACCB1 void ACCB2 AVAppRegisterForPageViewClicksCompatStub(AVPageViewClickProc clickProc, void* data);
ACCB1 void ACCB2 AVAppRegisterForPageViewAdjustCursorCompatStub(AVPageViewCursorProc cursorProc, void* data);
ACCB1 void ACCB2 AVPageViewInvertQuadCompatStub(AVPageView pageView, const Quad *quad, ASBool highlight);
ACCB1 void ACCB2 AVPageViewInvalidateRectCompatStub(AVPageView pageView, AVRect *area);
ACCB1 void ACCB2 AVPageViewGetMousePositionCompatStub(AVPageView pageView, AVDevCoord *x, AVDevCoord *y);
ACCB1 void ACCB2 AVPageViewGetMousePositionSnappedCompatStub(AVPageView pageView, AVDevCoord *x, AVDevCoord *y, AVDragType direction);
ACCB1 void ACCB2 AVPageViewInvertRectCompatStub(AVPageView pageView, const AVRect *rect, ASBool highlight);
ACCB1 void ACCB2 AVPageViewDrawRectOutlineCompatStub(AVPageView pageView, const AVRect *rect, AVDevSize lineWidth, ASFixedP dashArray, Int32 arrayLen);
ACCB1 void ACCB2 AVPageViewDrawRectCompatStub(AVPageView pageView, const AVRect *rect);
ACCB1 void ACCB2 AVPageViewGhostRectOutlineCompatStub(AVPageView pageView, const AVRect* rect);
ACCB1 void ACCB2 AVPageViewDrawCosObjCompatStub(AVPageView pageView, CosObj cosObj, const AVRect* rect);
ACCB1 void ACCB2 AVPageViewDrawCosObjExCompatStub(AVPageView pageView, CosObj cosObj, const AVRect* rect, ASFixedMatrix *matrix);
ACCB1 void ACCB2 AVPageViewInsetRectCompatStub(AVPageView pageView, const AVRect* rr, ASBool down);
ACCB1 void ACCB2 AVPageViewScrollToCompatStub(AVPageView pageView, AVDevCoord xOrigin, AVDevCoord yOrigin);
ACCB1 void ACCB2 AVPageViewScrollToRectCompatStub(AVPageView pageView, const AVRect *rect,
	ASBool favorLeft, ASBool favorTop, AVDevSize margin);
ACCB1 void ACCB2 AVPageViewGetApertureCompatStub(AVPageView pageView, AVRect *rect);
ACCB1 void ACCB2 AVPageViewGetGrayRectCompatStub(AVPageView pageView, AVRect* rect);
ACCB1 void ACCB2 AVAppRegisterLegacyToolBarPositionCompatStub(const char *toolBarName, ASBool external, AVToolBarPosition position);
ACCB1 void ACCB2 AVPageViewSnapPointCompatStub(AVPageView pageView, AVDevCoord *x, AVDevCoord *y, AVDragType direction);
ACCB1 void ACCB2 AVPageViewDragOutNewRectCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *resultRect);
ACCB1 ASInt32 ACCB2 AVPageViewDragOutNewRectSnappedCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *resultRect, AVCursor *cursorArray, ASInt16 nCursors);
ACCB1 void ACCB2 AVPageViewDragRectCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *startRect, AVRect *resultRect, Int32 dragType, AVRect *extrema);
ACCB1 ASInt32 ACCB2 AVPageViewDragRectSnappedCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *startRect, AVRect *resultRect, Int32 dragType, AVRect *extrema, AVCursor *cursorArray, ASInt16 nCursors);
ACCB1 void ACCB2 AVPageViewSnapRectCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVDevCoord xNow, AVDevCoord yNow, AVRect *startRect, AVRect *resultRect, ASInt32 handleType, ASUns32 modifiers, const AVRect *extrema);
ACCB1 AVMenuItem ACCB2 AVPageViewDoPopupMenuCompatStub(AVPageView pageView, AVMenu menu, AVDevCoord xHit, AVDevCoord yHit,
	ASBool rightMouse, ASInt32 choice);
ACCB1 ASBool ACCB2 AVPageViewPointInTextCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDTextSelect pdText);
#define AVPageViewTrackTextCompatStub AVPageViewTrackTextHostCompatStub
ACCB1 PDTextSelect ACCB2 AVPageViewTrackTextHostCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDTextSelect current);
ACCB1 ASBool ACCB2 AVPageViewIsAnnotAtPointCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDAnnot *hitAnnot);
ACCB1 void ACCB2 AVPageViewGetAnnotRectCompatStub(AVPageView pageView, PDAnnot anAnnot, AVRect *rect);
ACCB1 void ACCB2 AVPageViewDrawAnnotSequenceCompatStub(AVPageView pv, PDAnnot an,const AVRect *bbox);
ACCB1 ASBool ACCB2 AVPageViewIsBeadAtPointCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDBead *beadP);
ACCB1 void ACCB2 AVPageViewDevicePointToPageCompatStub(AVPageView pageView, AVDevCoord x, AVDevCoord y, ASFixedPoint *p);
ACCB1 void ACCB2 AVPageViewRectToDeviceCompatStub(AVPageView pageView, const ASFixedRectP src, AVRect *dst);
ACCB1 void ACCB2 AVPageViewDeviceRectToPageCompatStub(AVPageView pageView, const AVRect *src, ASFixedRect *dst);
ACCB1 void ACCB2 AVPageViewDeviceRectToPageRZCompatStub(AVPageView pageView, Int32 flags, AVDevCoord xHot, AVDevCoord yHot, const AVRect *src, ASFixedRect *dst);
ACCB1 void ACCB2 AVPageViewPointToDeviceCompatStub(AVPageView pageView, const ASFixedPointP p, AVDevCoord *x, AVDevCoord *y);
ACCB1 AVDragTypeEx ACCB2 AVRectHandleHitTestCompatStub(const AVRect *rect, ASBool bMidpoints, AVDevCoord x, AVDevCoord y);
ACCB1 ASBool ACCB2 AVPageViewIsAnnotOfTypeAtPointCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, ASAtom annotType, ASBool belowOthers, PDAnnot *annot);
ACCB1 void ACCB2 AVPageViewSetAnnotLocationCompatStub(PDAnnot anAnnot, AVPageView pageView, AVDevCoord x, AVDevCoord y);
ACCB1 AVWindow ACCB2 AVWindowNewFromPlatformThingCompatStub(AVWindowLayer layer, Uns32 flags,
	AVWindowHandler handler, ASExtension owner, AVPlatformWindowRef platformThing);
ACCB1 AVWindow ACCB2 AVWindowNewCompatStub(AVWindowLayer layer, Uns32 flags, AVWindowHandler handler,
	ASExtension owner);
ACCB1 void ACCB2 AVWindowSetMinMaxSizeCompatStub(AVWindow win, const AVRect *rect);
ACCB1 void ACCB2 AVWindowGetMinMaxSizeCompatStub(AVWindow win, AVRect *rect);
ACCB1 void ACCB2 AVWindowInvalidateRectCompatStub(AVWindow win, const AVRect *rect);
ACCB1 void ACCB2 AVWindowGetInteriorCompatStub(AVWindow win, AVRect *rect);
ACCB1 void ACCB2 AVWindowGetTitleCompatStub(AVWindow win, ASText title);
ACCB1 void ACCB2 AVWindowSetTitleCompatStub(AVWindow win, const ASText title);
ACCB1 void ACCB2 AVWindowSetFrameCompatStub(AVWindow win, const AVRect *rect);
ACCB1 void ACCB2 AVWindowGetFrameCompatStub(AVWindow win, AVRect *rect);
ACCB1 void ACCB2 AVPageViewDrawRectOutlineWithHandlesCompatStub(AVPageView pageView, const AVRect *rect, ASBool bMidpoints, ASBool bThin, ASFixed *dashArray, ASInt32 arrayLen);  
ACCB1 ASBool ACCB2 AVAppOpenDialogCompatStub(AVOpenSaveDialogParams dialogParams, ASFileSys *outFileSys, ASPathName **outASPathNames, ASUns16 *outNumASPathNames, ASInt16 *ioChosenFilterIndex);
ACCB1 ASBool ACCB2 AVAppSaveDialogCompatStub(AVOpenSaveDialogParams dialogParams, ASFileSys	*outFileSys, ASPathName	*outASPathName, ASInt16 *ioChosenFilterIndex);
ACCB1 ASBool ACCB2 AVAppChooseFolderDialogCompatStub(AVOpenSaveDialogParams dialogParams, ASFileSys *outFileSys, ASPathName *outASPathName);
ACCB1 void ACCB2 AVDocPrintPagesWithParamsCompatStub(AVDoc doc, AVDocPrintParams paramsIn);

/* these routines are needed to convert callbacks to 16 bit, the HFT is still the same */
ACCB1 void ACCB2 AVAppUnregisterForPageViewDrawingCompatStub(AVPageViewDrawProc proc);
ACCB1 void ACCB2 AVAppUnregisterForPageViewClicksCompatStub(AVPageViewClickProc proc);
ACCB1 void ACCB2 AVAppUnregisterForPageViewAdjustCursorCompatStub(AVPageViewCursorProc proc);
ACCB1 void ACCB2 AVAppRegisterAnnotHandlerCompatStub(AVAnnotHandler handler);
ACCB1 void ACCB2 AVAppRegisterToolCompatStub(AVTool tool);

#ifdef __cplusplus
}
#endif

#endif /* _H_AVCompat */

