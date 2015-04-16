/*
** AVCompat.CPP
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
#include "CorCalls.h"
#include "ASCalls.h"
#include "ASExtraCalls.h"
#include "AVCalls.h"
#include "AVCompat.h"
#include "acroassert.h"

extern HFT gAcroViewHFT;
extern ASUns32 gAcroViewVersion;
#define OLDCALL(x) ((old##x##SELPROTO)(gAcroViewHFT[old##x##SEL]))
#if ACRO_SDK_LEVEL >= 0x00060000
inline ASInt16 StepDown(const ASInt32& x)
{
	if (x > ASMAXInt16 || x < ASMINInt16)
		ASRaise(GenError(genErrBadParm));
	return (ASInt16)x;
}
inline AVRect StepUp(const oldAVRect& oldr)
{
	AVRect r;
	r.left = oldr.left;
	r.right = oldr.right;
	r.top = oldr.top;
	r.bottom = oldr.bottom;
	return r;
}
inline oldAVRect StepDown(const AVRect& oldr)
{
	oldAVRect r;
	if (oldr.left > ASMAXInt16 || oldr.right > ASMAXInt16 || oldr.top > ASMAXInt16 || oldr.bottom > ASMAXInt16 ||
	    oldr.left < ASMINInt16 || oldr.right < ASMINInt16 || oldr.top < ASMINInt16 || oldr.bottom < ASMINInt16)
		ASRaise(GenError(genErrBadParm));
	r.left = (ASInt16)oldr.left;
	r.right = (ASInt16)oldr.right;
	r.top = (ASInt16)oldr.top;
	r.bottom = (ASInt16)oldr.bottom;
	return r;
}
/* can safely cast from one to the other since the only difference is what pointers are pointing at */
inline oldAVDocSelectionServer StepDown(const AVDocSelectionServer& s)
{
	ACROASSERT(s);
	s->size = sizeof(oldAVDocSelectionServerRec); //5.0 version of this routine will only take structs that are exact size
	return (oldAVDocSelectionServer)s;
}
inline AVDocSelectionServer StepUp(const oldAVDocSelectionServer& s)
{
	return (AVDocSelectionServer)s;
}
static void AVDocVD_to_oldAVDocVD(const AVDocViewDef& vd, oldAVDocViewDef newvd)
{
	ACROASSERT(newvd);
	ACROASSERT(vd);
	newvd->size = sizeof(*newvd);
	newvd->bringToFront = vd->bringToFront;
	newvd->usePageViewInfo = vd->usePageViewInfo;
	newvd->pageViewLayoutMode = vd->pageViewLayoutMode;
	newvd->pageViewPageNum = vd->pageViewPageNum;
	newvd->pageViewZoomType = vd->pageViewZoomType;
	newvd->pageViewZoom = vd->pageViewZoom;
	newvd->pageViewX = StepDown(vd->pageViewX);
	newvd->pageViewY = StepDown(vd->pageViewY);
	newvd->pageViewStartThread = vd->pageViewStartThread;
	newvd->pageViewThreadIndex = vd->pageViewThreadIndex;
	newvd->pageViewBead = vd->pageViewBead;
	newvd->useOverViewInfo = vd->useOverViewInfo;
	newvd->overViewMode = vd->overViewMode;
	newvd->overViewPos = vd->overViewPos;
	newvd->overViewX = vd->overViewX;
	newvd->overViewY = vd->overViewY;
	newvd->useWindowInfo = vd->useWindowInfo;
	newvd->windowFrame = StepDown(vd->windowFrame);
}
static void AVDocOP_to_oldAVDocOP(const AVDocOpenParams& p, oldAVDocOpenParams newp)
{
	ACROASSERT(p);
	ACROASSERT(newp);
	newp->size = sizeof(*newp);
	newp->useFrame = p->useFrame;
	newp->frame = StepDown(p->frame);
	newp->useVisible = p->useVisible;
	newp->visible = p->visible;
	newp->useServerType = p->useServerType;
	newp->serverType = p->serverType;
	newp->serverCreationData = p->serverCreationData;
	newp->useSourceDoc = p->useSourceDoc;
	newp->sourceDoc = p->sourceDoc;
	newp->useReadOnly = p->useReadOnly;
	newp->readOnly = p->readOnly;
	newp->useViewType = p->useViewType;
	newp->viewType = p->viewType;
	newp->useViewDef = p->useViewDef;

	if(newp->useViewDef) {
		ACROASSERT(p->viewDef);
		AVDocVD_to_oldAVDocVD(p->viewDef, newp->viewDef);
	}

	newp->usePermReqProc = p->usePermReqProc;
	newp->permReqProc = p->permReqProc;
}
static void AVOpenSaveDialogParams_to_oldAVOpenSaveDialogParams(const AVOpenSaveDialogParamsRec& newparams, oldAVOpenSaveDialogParamsRec& oldparams)
{
	oldparams.size = sizeof(oldparams);
	oldparams.flags = newparams.flags;
	oldparams.parentWindow = newparams.parentWindow;
	oldparams.windowTitle = newparams.windowTitle;
	oldparams.actionButtonTitle = newparams.actionButtonTitle;
	oldparams.cancelButtonTitle = newparams.actionButtonTitle;
	oldparams.initialFileSys = newparams.initialFileSys;
	oldparams.initialPathName = newparams.initialPathName;
	if(newparams.initialFileName != NULL)
		oldparams.initialFileName = ASTextGetEncoded(newparams.initialFileName, AVAppGetLanguageEncoding());
	else
		oldparams.initialFileName = NULL;
	oldparams.fileFilters = newparams.fileFilters;
	oldparams.numFileFilters = newparams.numFileFilters;
	oldparams.settingsComputeEnabledProc = newparams.settingsComputeEnabledProc;
	oldparams.settingsExecuteProc = newparams.settingsExecuteProc;
	oldparams.settingsProcData = newparams.settingsProcData;
}
ACCB1 AVDoc ACCB2 AVDocOpenFromFileCompatStub(ASPathName pathName, ASFileSys fileSys, const ASText tempTitle)
{
	const char *cTempTitle = ASTextGetEncoded(tempTitle, AVAppGetLanguageEncoding());
	return OLDCALL(AVDocOpenFromFile)(pathName,fileSys,const_cast<char*>(cTempTitle));
}

ACCB1 AVDoc ACCB2 AVDocOpenFromFileWithParamsCompatStub(ASPathName pathName, ASFileSys fileSys, 
	const ASText tempTitle, AVDocOpenParams params)
{
	const char *cTempTitle = ASTextGetEncoded(tempTitle, AVAppGetLanguageEncoding());
	
	oldAVDocOpenParamsRec op;
	oldAVDocViewDefRec vd;
	if (params) {
		op.viewDef = &vd;
		AVDocOP_to_oldAVDocOP(params, &op);
	}
	return OLDCALL(AVDocOpenFromFileWithParams)(pathName, fileSys, const_cast<char*>(cTempTitle), params? &op:NULL);
}
ACCB1 AVDoc ACCB2 AVDocOpenFromPDDocWithParamsCompatStub(PDDoc pdDoc, const ASText tempTitle, AVDocOpenParams params)
{
	const char *cTempTitle = ASTextGetEncoded(tempTitle, AVAppGetLanguageEncoding());
	
	oldAVDocOpenParamsRec op;
	oldAVDocViewDefRec vd;
	if (params) {
		op.viewDef = &vd;
		AVDocOP_to_oldAVDocOP(params, &op);
	}
	return OLDCALL(AVDocOpenFromPDDocWithParams)(pdDoc, const_cast<char*>(cTempTitle), params?&op:NULL);
}
ACCB1 AVDoc ACCB2 AVDocOpenFromPDDocCompatStub(PDDoc pdDoc, const ASText tempTitle)
{
	const char *cTempTitle = ASTextGetEncoded(tempTitle, AVAppGetLanguageEncoding());
	return OLDCALL(AVDocOpenFromPDDoc)(pdDoc, const_cast<char*>(cTempTitle));
}
ACCB1 AVDoc ACCB2 AVDocOpenFromASFileWithParamsCompatStub(ASFile file, const ASText tempTitle, AVDocOpenParams params)
{
	const char *cTempTitle = ASTextGetEncoded(tempTitle, AVAppGetLanguageEncoding());
	
	oldAVDocOpenParamsRec op;
	oldAVDocViewDefRec vd;
	if (params) {
		op.viewDef = &vd;
		AVDocOP_to_oldAVDocOP(params, &op);
	}
	return OLDCALL(AVDocOpenFromASFileWithParams)(file, const_cast<char*>(cTempTitle), params?&op:NULL);
}
ACCB1 void ACCB2 AVDocGetViewDefCompatStub(AVDoc doc, AVDocViewDef viewDef)
{
	oldAVDocViewDefRec vd;
	AVDocVD_to_oldAVDocVD(viewDef, &vd);
	OLDCALL(AVDocGetViewDef)(doc, &vd);
}
ACCB1 void ACCB2 AVDocSetViewDefCompatStub(AVDoc doc, AVDocViewDef viewDef)
{
	oldAVDocViewDefRec vd;
	AVDocVD_to_oldAVDocVD(viewDef, &vd);
	OLDCALL(AVDocSetViewDef)(doc, &vd); //sproc
}
typedef struct _t_ProcDataLinks
{
	struct _t_ProcDataLinks *next;
	void* proc;
	void* data;
} ProcDataLinksRec, *ProcDataLinkP;
static void UnregisterThisProc(ProcDataLinkP& linkP, void* proc)
{
	ProcDataLinkP prev = NULL;
	ProcDataLinkP current;
	ProcDataLinkP found=NULL;
	if (!linkP)
		return;
	if (linkP->proc == proc) {
		found = linkP;
		linkP = linkP->next; //remove from chain
	}
	else {
		current = linkP->next;
		prev = linkP;
		while(current && !found) {
			if (current->proc == proc) {
				found = current;
				prev->next = current->next; //remove from chain
			}
			else {
				prev = current;
				current = current->next;
			}
		}
	}
	if (found)
		ASfree(found);
}
static void CompatRegisterThisProc(ProcDataLinkP& linkP, void* proc, void* data)
{
	ProcDataLinkP item = (ProcDataLinkP) ASmalloc(sizeof(ProcDataLinksRec));
	//add to head
	item->proc = proc;
	item->data = data;
	item->next = linkP;
	linkP = item;
}
enum procKind {
	ePROC_DRAW=0, 
	ePROC_PAGEVIEW_CLICK, 
	ePROC_PAGEVIEW_ADJUST_CURSOR, 
	ePROC_WIN_MOUSE_DOWN, 
	ePROC_WIN_DRAW, 
	ePROC_WIN_WILLBERESIZED, 
	ePROC_WIN_ADJUST_CURSOR, 
	ePROC_WIN_DIDRESIZE, 

	kPROCKIND_COUNT
};
ProcDataLinkP gProcList[kPROCKIND_COUNT]={0};
ACCB1 void ACCB2 CompatDoPageViewDrawCB(AVPageView pageView, oldAVRect* updateRect, void*data);
ACCB1 void ACCB2 CompatDoPageViewDrawCB(AVPageView pageView, oldAVRect* updateRect, void*data)
{
	ACROASSERT(updateRect);
	AVRect ur = StepUp(*updateRect);
	for (ProcDataLinkP i = gProcList[ePROC_DRAW];i!=NULL;i = i->next)
		((AVPageViewDrawProc)i->proc)(pageView, &ur, i->data);
}
static ACCB1 ASBool ACCB2 CompatDoPageViewClicksCB(AVPageView pageView, ASInt16 x, ASInt16 y, AVFlagBits16 flags, AVTCount clickNo, void*data)
{
	ASBool handled = false;
	for (ProcDataLinkP i = gProcList[ePROC_PAGEVIEW_CLICK];i!=NULL && !handled;i = i->next)
		handled = ((AVPageViewClickProc)i->proc)(pageView, x, y, flags, clickNo, i->data);
	return handled;
}
static ACCB1 ASBool ACCB2 CompatAnnotDoLClick(oldAVAnnotHandler annotHandler, PDAnnot hitAnnot, AVPageView pageView, 
					ASInt16 xHit, ASInt16 yHit, 	ASInt16 flags, ASInt16 clickNo)
{
	//annotHandler points to a valid AVAnnotHandler type since this got assigned in an AVAnnotHandler routine
	ACROASSERT(annotHandler);
	ACROASSERT(((AVAnnotHandler)annotHandler)->DoClick);
	return ((AVAnnotHandler)annotHandler)->DoClick(((AVAnnotHandler)annotHandler), hitAnnot, pageView, xHit, yHit, flags, clickNo);
}
static ACCB1 ASBool ACCB2 CompatAnnotDoRClick(oldAVAnnotHandler annotHandler, PDAnnot hitAnnot, AVPageView pageView, 
					ASInt16 xHit, ASInt16 yHit, 	ASInt16 flags, ASInt16 clickNo)
{
	//annotHandler points to a valid AVAnnotHandler type since this got assigned in an AVAnnotHandler routine
	ACROASSERT(annotHandler);
	ACROASSERT(((AVAnnotHandler)annotHandler)->DoRightClick);
	return ((AVAnnotHandler)annotHandler)->DoRightClick(((AVAnnotHandler)annotHandler), hitAnnot, pageView, xHit, yHit, flags, clickNo);
}
static ACCB1 ASBool ACCB2 CompatAnnotAdjustCursor(oldAVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView, ASInt16 xHit, ASInt16 yHit)
{
	//annotHandler points to a valid AVAnnotHandler type since this got assigned in an AVAnnotHandler routine
	ACROASSERT(annotHandler);
	ACROASSERT(((AVAnnotHandler)annotHandler)->AdjustCursor);
	return ((AVAnnotHandler)annotHandler)->AdjustCursor(((AVAnnotHandler)annotHandler), anAnnot, pageView, xHit, yHit);
}
static ACCB1 void ACCB2 CompatGetAnnotViewBBox(oldAVAnnotHandler annotHandler, AVPageView pageView, 
					   PDAnnot anAnnot, oldAVRect *bbox)
{
	//annotHandler points to a valid AVAnnotHandler type since this got assigned in an AVAnnotHandler routine
	AVRect rect;
	ACROASSERT(annotHandler);
	ACROASSERT(((AVAnnotHandler)annotHandler)->GetAnnotViewBBox);
	((AVAnnotHandler)annotHandler)->GetAnnotViewBBox(((AVAnnotHandler)annotHandler), pageView, anAnnot, &rect);
	*bbox = StepDown(rect);
}
static ACCB1 ASBool ACCB2 CompatPtInAnnotViewBBox(oldAVAnnotHandler annotHandler, AVPageView pageView, 
                   PDAnnot anAnnot, ASInt16 xHit, ASInt16 yHit)
{
	//annotHandler points to a valid AVAnnotHandler type since this got assigned in an AVAnnotHandler routine
	ACROASSERT(annotHandler);
	ACROASSERT(((AVAnnotHandler)annotHandler)->PtInAnnotViewBBox);
	return ((AVAnnotHandler)annotHandler)->PtInAnnotViewBBox(((AVAnnotHandler)annotHandler), pageView, anAnnot, xHit, yHit);
}
static ACCB1 void ACCB2 CompatAnnotDrawEx(oldAVAnnotHandler annotHandler, PDAnnot anAnnot, AVPageView pageView, oldAVRect *updateRect)
{
	//annotHandler points to a valid AVAnnotHandler type since this got assigned in an AVAnnotHandler routine
	ACROASSERT(annotHandler);
	ACROASSERT(updateRect);
	ACROASSERT(((AVAnnotHandler)annotHandler)->DrawEx);
	AVRect r = StepUp(*updateRect);
	((AVAnnotHandler)annotHandler)->DrawEx(((AVAnnotHandler)annotHandler), anAnnot, pageView, &r);
}

static ACCB1 ASBool ACCB2 CompatAVDocSelectionShowMenuProc(AVDoc doc, void *data, ASInt16 x, ASInt16 y)
{
	AVDocSelectionServer ss= AVDocGetSelectionServerByType( AVDocGetSelectionType( doc ) );
	return ss->ShowMenu(doc, data, x, y);
}
static ACCB1 ASBool ACCB2 CompatAVDocSelectionGetAVRectProc(AVDoc doc, PDPageNumber pageNo, oldAVRect* rect, void* data)
{
	ASBool res;
	AVRect r;
	AVDocSelectionServer ss= AVDocGetSelectionServerByType( AVDocGetSelectionType( doc ) );
	res = ss->GetAVRect(doc, pageNo, &r, data);
	*rect = StepDown(r);
	return res;
}


static ACCB1 ASBool ACCB2 CompatToolDoClick(oldAVTool tool, AVPageView pageView, ASInt16 xHit, ASInt16 yHit, 
					ASInt16 flags, ASInt16 clickNo)
{
	//tool points to a valid AVTool struct
	ACROASSERT(tool);
	ACROASSERT(((AVTool)tool)->DoClick);
	return ((AVTool)tool)->DoClick(((AVTool)tool), pageView, xHit, yHit, flags, clickNo);
}
static ACCB1 ASBool ACCB2 CompatToolDoRClick(oldAVTool tool, AVPageView pageView, ASInt16 xHit, ASInt16 yHit, 
					ASInt16 flags, ASInt16 clickNo)
{
	//tool points to a valid AVTool struct
	ACROASSERT(tool);
	ACROASSERT(((AVTool)tool)->DoRightClick);
	return ((AVTool)tool)->DoRightClick(((AVTool)tool), pageView, xHit, yHit, flags, clickNo);
}
static ACCB1 ASBool ACCB2 CompatToolAdjustCursor(oldAVTool tool, AVPageView pageView, ASInt16 x, ASInt16 y)
{
	//tool points to a valid AVTool struct
	ACROASSERT(tool);
	ACROASSERT(((AVTool)tool)->AdjustCursor);
	return ((AVTool)tool)->AdjustCursor(((AVTool)tool), pageView, x, y);
}

static ACCB1 ASBool ACCB2 CompatDoPageViewCursorCB(AVPageView pageView, ASInt16 x, ASInt16 y, void* data)
{
	ASBool handled = false;
	for (ProcDataLinkP i = gProcList[ePROC_PAGEVIEW_ADJUST_CURSOR];i!=NULL && !handled;i = i->next)
		handled = ((AVPageViewCursorProc)i->proc)(pageView, x, y, i->data);
	return handled;
}
static ACCB1 void ACCB2 CompatAVWindowMouseDownProc(AVWindow win, ASInt16 x, ASInt16 y, void *platformEvent)
{
	for (ProcDataLinkP i = gProcList[ePROC_WIN_MOUSE_DOWN];i!=NULL;i = i->next)
		if (i->data == win) {
			((AVWindowMouseDownProc)i->proc)(win, x, y, platformEvent);
			return;
		}
	ACROASSERT(false); //should never happen
}
static ACCB1 void ACCB2 CompatAVWindowDrawProc(AVWindow win, const oldAVRect *rect)
{
	ACROASSERT(rect);
	AVRect r = StepUp(*rect);
	for (ProcDataLinkP i = gProcList[ePROC_WIN_DRAW];i!=NULL;i = i->next)
		if (i->data == win) {
			((AVWindowDrawProc)i->proc)(win, &r);
			return;
		}
	ACROASSERT(false); //should never happen
}
static ACCB1 ASBool ACCB2 CompatAVWindowWillBeResizedProc(AVWindow win, oldAVRect *newFrame)
{
	ASBool res;
	ACROASSERT(newFrame);
	AVRect r = StepUp(*newFrame);
	for (ProcDataLinkP i = gProcList[ePROC_WIN_WILLBERESIZED];i!=NULL;i = i->next)
		if (i->data == win) {
			res = ((AVWindowWillBeResizedProc)i->proc)(win, &r);
			*newFrame = StepDown(r);
			return res;
		}
	ACROASSERT(false); //should never happen
	return true;
}
static ACCB1 void ACCB2 CompatAVWindowAdjustCursorProc(AVWindow win, ASInt16 x, ASInt16 y)
{
	for (ProcDataLinkP i = gProcList[ePROC_WIN_ADJUST_CURSOR];i!=NULL;i = i->next)
		if (i->data == win) {
			((AVWindowAdjustCursorProc)i->proc)(win, x, y);
			return;
		}
	ACROASSERT(false); //should never happen
}
static ACCB1 void ACCB2 CompatAVWindowDidResizeProc(AVWindow win, const oldAVRect *newFrame)
{
	ACROASSERT(newFrame);
	AVRect r = StepUp(*newFrame);
	for (ProcDataLinkP i = gProcList[ePROC_WIN_DIDRESIZE];i!=NULL;i = i->next)
		if (i->data == win) {
			((AVWindowDidResizeProc)i->proc)(win, &r);
			return;
		}
	ACROASSERT(false); //should never happen
}

ACCB1 ASBool ACCB2 AVDocRegisterSelectionServerCompatStub(AVDocSelectionServer server)
{
	ACROASSERT(server);
	if (server->GetAVRect) {
		server->oldGetAVRect = CompatAVDocSelectionGetAVRectProc;
	}
	if (server->ShowMenu) {
		server->oldShowMenu = CompatAVDocSelectionShowMenuProc;
	}
	oldAVDocSelectionServer s= StepDown(server);
	return OLDCALL(AVDocRegisterSelectionServer)(s);
}

ACCB1 void ACCB2 AVAppRegisterForPageViewDrawingCompatStub(AVPageViewDrawProc drawproc, void* data)
{
	if (!gProcList[ePROC_DRAW])
		OLDCALL(AVAppRegisterForPageViewDrawing)(CompatDoPageViewDrawCB, NULL);  
	CompatRegisterThisProc(gProcList[ePROC_DRAW], (void *) drawproc, data);
}
ACCB1 void ACCB2 AVAppRegisterForPageViewClicksCompatStub(AVPageViewClickProc clickproc, void* data)
{
	if (!gProcList[ePROC_PAGEVIEW_CLICK])
		OLDCALL(AVAppRegisterForPageViewClicks)(CompatDoPageViewClicksCB, NULL);  
	CompatRegisterThisProc(gProcList[ePROC_PAGEVIEW_CLICK], (void *) clickproc, data);
}
ACCB1 void ACCB2 AVAppRegisterForPageViewAdjustCursorCompatStub(AVPageViewCursorProc cursorProc, void* data)
{
	if (!gProcList[ePROC_PAGEVIEW_ADJUST_CURSOR])
		OLDCALL(AVAppRegisterForPageViewAdjustCursor)(CompatDoPageViewCursorCB, NULL);  
	CompatRegisterThisProc(gProcList[ePROC_PAGEVIEW_ADJUST_CURSOR], (void *) cursorProc, data);
}
ACCB1 void ACCB2 AVAppUnregisterForPageViewDrawingCompatStub(AVPageViewDrawProc proc)
{
	UnregisterThisProc(gProcList[ePROC_DRAW], (void*) proc);
	if (!gProcList[ePROC_DRAW])
		AVROUTINE(AcroViewHFT_VERSION_2, AVAppUnregisterForPageViewDrawing)((AVPageViewDrawProc) CompatDoPageViewDrawCB);  //call original sproc
}
ACCB1 void ACCB2 AVAppUnregisterForPageViewClicksCompatStub(AVPageViewClickProc proc)
{
	UnregisterThisProc(gProcList[ePROC_PAGEVIEW_CLICK], (void*) proc);
	if (!gProcList[ePROC_PAGEVIEW_CLICK])
		AVROUTINE(AcroViewHFT_VERSION_2, AVAppUnregisterForPageViewClicks)((AVPageViewClickProc) CompatDoPageViewClicksCB);
}
ACCB1 void ACCB2 AVAppUnregisterForPageViewAdjustCursorCompatStub(AVPageViewCursorProc proc)
{
	UnregisterThisProc(gProcList[ePROC_PAGEVIEW_ADJUST_CURSOR], (void*) proc);
	if (!gProcList[ePROC_PAGEVIEW_ADJUST_CURSOR])
		AVROUTINE(AcroViewHFT_VERSION_2, AVAppUnregisterForPageViewAdjustCursor)((AVPageViewCursorProc) CompatDoPageViewCursorCB);
}

ACCB1 void ACCB2 AVPageViewInvertQuadCompatStub(AVPageView pageView, const Quad *quad, ASBool highlight)
{
	oldQuad q;
	if (quad) {
		q.tlh = StepDown(quad->tlh);
		q.tlv = StepDown(quad->tlv);
		q.trh = StepDown(quad->trh);
		q.trv = StepDown(quad->trv);
		q.blh = StepDown(quad->blh);
		q.blv = StepDown(quad->blv);
		q.brh = StepDown(quad->brh);
		q.brv = StepDown(quad->brv);
	}
	AVROUTINE(AcroViewHFT_VERSION_4, AVPageViewInvertQuad)(pageView, quad? (Quad*)&q : NULL, highlight);
}
ACCB1 void ACCB2 AVPageViewInvalidateRectCompatStub(AVPageView pageView, AVRect *area)
{
	oldAVRect r;
	if (area)
		r = StepDown(*area);
	OLDCALL(AVPageViewInvalidateRect)(pageView, area? &r:NULL);
}
ACCB1 void ACCB2 AVPageViewGetMousePositionCompatStub(AVPageView pageView, AVDevCoord *x, AVDevCoord *y)
{
	ACROASSERT(x);
	ACROASSERT(y);
	ASInt16 x16, y16;
	OLDCALL(AVPageViewGetMousePosition)(pageView, &x16, &y16);
	*x = x16;
	*y = y16;
}
ACCB1 void ACCB2 AVPageViewGetMousePositionSnappedCompatStub(AVPageView pageView, AVDevCoord *x, AVDevCoord *y, AVDragType direction)
{
	ACROASSERT(x);
	ACROASSERT(y);
	ASInt16 x16, y16;
	OLDCALL(AVPageViewGetMousePositionSnapped)(pageView, &x16, &y16, direction);
	*x = x16;
	*y = y16;
}
ACCB1 void ACCB2 AVPageViewInvertRectCompatStub(AVPageView pageView, const AVRect *rect, ASBool highlight)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewInvertRect)(pageView, &r, highlight);
}
ACCB1 void ACCB2 AVPageViewDrawRectOutlineCompatStub(AVPageView pageView, const AVRect *rect, AVDevSize lineWidth, ASFixedP dashArray, Int32 arrayLen)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewDrawRectOutline)(pageView, &r, StepDown(lineWidth), dashArray, arrayLen);
}
ACCB1 void ACCB2 AVPageViewDrawRectCompatStub(AVPageView pageView, const AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewDrawRect)(pageView, &r);
}
ACCB1 void ACCB2 AVPageViewGhostRectOutlineCompatStub(AVPageView pageView, const AVRect* rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewGhostRectOutline)(pageView, &r);
}
ACCB1 void ACCB2 AVPageViewDrawCosObjCompatStub(AVPageView pageView, CosObj cosObj, const AVRect* rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewDrawCosObj)(pageView, cosObj, &r);
}
ACCB1 void ACCB2 AVPageViewDrawCosObjExCompatStub(AVPageView pageView, CosObj cosObj, const AVRect* rect, ASFixedMatrix *matrix)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewDrawCosObjEx)(pageView, cosObj, &r, matrix);
}
ACCB1 void ACCB2 AVPageViewInsetRectCompatStub(AVPageView pageView, const AVRect* rr, ASBool down)
{
	ACROASSERT(rr);
	oldAVRect r = StepDown(*rr);
	OLDCALL(AVPageViewInsetRect)(pageView, &r, down);
}
ACCB1 void ACCB2 AVPageViewScrollToCompatStub(AVPageView pageView, AVDevCoord xOrigin, AVDevCoord yOrigin)
{
	OLDCALL(AVPageViewScrollTo)(pageView, StepDown(xOrigin), StepDown(yOrigin));
}
ACCB1 void ACCB2 AVPageViewScrollToRectCompatStub(AVPageView pageView, const AVRect *rect, 
	ASBool favorLeft, ASBool favorTop, AVDevSize margin)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewScrollToRect)(pageView, &r, favorLeft, favorTop, StepDown(margin));
}

ACCB1 void ACCB2 AVPageViewGetApertureCompatStub(AVPageView pageView, AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r;
	OLDCALL(AVPageViewGetAperture)(pageView, &r);
	*rect = StepUp(r);
}
ACCB1 void ACCB2 AVPageViewGetGrayRectCompatStub(AVPageView pageView, AVRect* rect)
{
	ACROASSERT(rect);
	oldAVRect r;
	OLDCALL(AVPageViewGetGrayRect)(pageView, &r);
	*rect = StepUp(r);
}
ACCB1 void ACCB2 AVAppRegisterLegacyToolBarPositionCompatStub(const char *toolBarName, ASBool external, AVToolBarPosition position)
{

	oldAVToolBarPositionRec oldposition;
	oldposition.inDoc = position->inDoc;
	oldposition.dockPosition = position->dockPosition;
	oldposition.floatingWindowName = position->floatingWindowName;
	oldposition.stackNum = position->stackNum;
	oldposition.offset = position->offset;
	oldposition.order = position->order;
	oldposition.windowFrame =  StepDown(position->windowFrame);
	oldposition.layout = position->layout;
	oldposition.hidden = position->hidden;
	oldposition.windowHidden = position->windowHidden;
	oldposition.size = sizeof(oldposition);
	OLDCALL(AVAppRegisterLegacyToolBarPosition)(toolBarName,external,&oldposition);
}

ACCB1 void ACCB2 AVPageViewSnapPointCompatStub(AVPageView pageView, AVDevCoord *x, AVDevCoord *y, AVDragType direction)
{
	ACROASSERT(x);
	ACROASSERT(y);
	ASInt16 x1 = StepDown(*x);
	ASInt16 y1 = StepDown(*y);
	OLDCALL(AVPageViewSnapPoint)(pageView, &x1, &y1, direction);
	*x = x1;
	*y = y1;
}
ACCB1 void ACCB2 AVPageViewDragOutNewRectCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *resultRect)
{
	ACROASSERT(resultRect);
	oldAVRect r;
	OLDCALL(AVPageViewDragOutNewRect)(pageView, StepDown(xStart), StepDown(yStart), &r);
	*resultRect = StepUp(r);
}
ACCB1 ASInt32 ACCB2 AVPageViewDragOutNewRectSnappedCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, 
												  AVRect *resultRect, AVCursor *cursorArray, ASInt16 nCursors)
{
	ACROASSERT(resultRect);
	ASInt32 res;
	oldAVRect r;
	res = OLDCALL(AVPageViewDragOutNewRectSnapped)(pageView, StepDown(xStart), StepDown(yStart), &r, cursorArray, nCursors);
	*resultRect = StepUp(r);
	return res;
}
ACCB1 void ACCB2 AVPageViewDragRectCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *startRect, AVRect *resultRect, Int32 dragType, AVRect *extrema)
{
	ACROASSERT(startRect);
	ACROASSERT(resultRect);
	oldAVRect sr = StepDown(*startRect);
	oldAVRect rr;
	oldAVRect er;
	if (extrema)
		er = StepDown(*extrema);
	OLDCALL(AVPageViewDragRect)(pageView, StepDown(xStart), StepDown(yStart), &sr, &rr, dragType, extrema? &er : NULL);
	*resultRect = StepUp(rr);
}
ACCB1 ASInt32 ACCB2 AVPageViewDragRectSnappedCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVRect *startRect, 
											AVRect *resultRect, Int32 dragType, AVRect *extrema, AVCursor *cursorArray, ASInt16 nCursors)
{
	ACROASSERT(startRect);
	ACROASSERT(resultRect);
	ASInt32 res;
	oldAVRect sr = StepDown(*startRect);
	oldAVRect rr;
	oldAVRect er;
	if (extrema)
		er = StepDown(*extrema);
	res = OLDCALL(AVPageViewDragRectSnapped)(pageView, StepDown(xStart), StepDown(yStart), &sr, &rr, dragType, extrema? &er : NULL, cursorArray, nCursors);
	*resultRect = StepUp(rr);
	return res;
}
ACCB1 void ACCB2 AVPageViewSnapRectCompatStub(AVPageView pageView, AVDevCoord xStart, AVDevCoord yStart, AVDevCoord xNow, AVDevCoord yNow, 
								  AVRect *startRect, AVRect *resultRect, ASInt32 handleType, ASUns32 modifiers, const AVRect *extrema)
{
	ACROASSERT(startRect);
	ACROASSERT(resultRect);
	oldAVRect sr = StepDown(*startRect);
	oldAVRect rr;
	oldAVRect er;
	if (extrema)
		er = StepDown(*extrema);
	OLDCALL(AVPageViewSnapRect)(pageView, StepDown(xStart), StepDown(yStart), StepDown(xNow), StepDown(yNow), &sr, &rr, handleType, modifiers, extrema? &er : NULL);
	*resultRect = StepUp(rr);
}

ACCB1 AVMenuItem ACCB2 AVPageViewDoPopupMenuCompatStub(AVPageView pageView, AVMenu menu, 	AVDevCoord xHit, AVDevCoord yHit, 
										   ASBool rightMouse, ASInt32 choice)
{
	return OLDCALL(AVPageViewDoPopupMenu)(pageView, menu, StepDown(xHit), StepDown(yHit), rightMouse, choice);
}
ACCB1 ASBool ACCB2 AVPageViewPointInTextCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDTextSelect pdText)
{
	return OLDCALL(AVPageViewPointInText)(pageView, StepDown(xHit), StepDown(yHit), pdText);
}

ACCB1 PDTextSelect ACCB2 AVPageViewTrackTextHostCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDTextSelect current)
{
	return OLDCALL(AVPageViewTrackText)(pageView, StepDown(xHit), StepDown(yHit), current); //sproc
}

ACCB1 ASBool ACCB2 AVPageViewIsAnnotAtPointCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDAnnot *hitAnnot)
{
	return OLDCALL(AVPageViewIsAnnotAtPoint)(pageView, StepDown(xHit), StepDown(yHit), hitAnnot);
}

ACCB1 void ACCB2 AVPageViewGetAnnotRectCompatStub(AVPageView pageView, PDAnnot anAnnot, AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r;
	OLDCALL(AVPageViewGetAnnotRect)(pageView, anAnnot, &r);
	*rect = StepUp(r);
}
ACCB1 void ACCB2 AVPageViewDrawAnnotSequenceCompatStub(AVPageView pv, PDAnnot an, const AVRect *bbox)
{
	ACROASSERT(bbox);
	oldAVRect r = StepDown(*bbox);
	OLDCALL(AVPageViewDrawAnnotSequence)(pv, an, &r);
}
ACCB1 ASBool ACCB2 AVPageViewIsBeadAtPointCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, PDBead *beadP)
{
	return OLDCALL(AVPageViewIsBeadAtPoint)(pageView, StepDown(xHit), StepDown(yHit), beadP);
}
ACCB1 void ACCB2 AVPageViewDevicePointToPageCompatStub(AVPageView pageView, AVDevCoord x, AVDevCoord y, ASFixedPoint *p)
{
	OLDCALL(AVPageViewDevicePointToPage)(pageView, StepDown(x), StepDown(y), p);
}
ACCB1 void ACCB2 AVPageViewRectToDeviceCompatStub(AVPageView pageView, const ASFixedRectP src, AVRect *dst)
{
	ACROASSERT(dst);
	oldAVRect r;
	OLDCALL(AVPageViewRectToDevice)(pageView, src, &r);
	*dst = StepUp(r);
}
ACCB1 void ACCB2 AVPageViewDeviceRectToPageCompatStub(AVPageView pageView, const AVRect *src, ASFixedRect *dst)
{
	ACROASSERT(src);
	oldAVRect r = StepDown(*src);
	OLDCALL(AVPageViewDeviceRectToPage)(pageView, &r, dst);
}

ACCB1 void ACCB2 AVPageViewDeviceRectToPageRZCompatStub(AVPageView pageView, Int32 flags, AVDevCoord xHot, AVDevCoord yHot, const AVRect *src, 
										ASFixedRect *dst)
{
	ACROASSERT(src);
	oldAVRect r = StepDown(*src);
	OLDCALL(AVPageViewDeviceRectToPageRZ)(pageView, flags, StepDown(xHot), StepDown(yHot), &r, dst); //sproc
}

ACCB1 void ACCB2 AVPageViewPointToDeviceCompatStub(AVPageView pageView, const ASFixedPointP p, AVDevCoord *x, AVDevCoord *y)
{
	ACROASSERT(x);
	ACROASSERT(y);
	ASInt16 x1;
	ASInt16 y1;
	OLDCALL(AVPageViewPointToDevice)(pageView, p, &x1, &y1);
	*x = x1;
	*y = y1;
}
ACCB1 AVDragTypeEx ACCB2 AVRectHandleHitTestCompatStub(const AVRect *rect, ASBool bMidpoints, AVDevCoord x, AVDevCoord y)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	return OLDCALL(AVRectHandleHitTest)(&r, bMidpoints, StepDown(x), StepDown(y));
}
ACCB1 void ACCB2 AVAppRegisterAnnotHandlerCompatStub(AVAnnotHandler handler)
{
	ACROASSERT(handler);
	if (handler->DoClick )
		handler->oldDoClick = CompatAnnotDoLClick;
	if (handler->AdjustCursor )
		handler->oldAdjustCursor = CompatAnnotAdjustCursor;
	if (handler->PtInAnnotViewBBox )
		handler->oldPtInAnnotViewBBox = CompatPtInAnnotViewBBox;
	if (handler->GetAnnotViewBBox )
		handler->oldGetAnnotViewBBox = CompatGetAnnotViewBBox;
	if (handler->DoRightClick )
		handler->oldDoRightClick = CompatAnnotDoRClick;
	if (handler->DrawEx )
		handler->oldDrawEx = CompatAnnotDrawEx;
	OLDCALL(AVAppRegisterAnnotHandler)(handler);  //call original sproc
}
ACCB1 void ACCB2 AVAppRegisterToolCompatStub(AVTool tool)
{
	ACROASSERT(tool);
	if (tool->DoClick) 
		tool->oldDoClick = CompatToolDoClick;
	if (tool->DoRightClick) 
		tool->oldDoRightClick = CompatToolDoRClick;
	if (tool->AdjustCursor) 
		tool->oldAdjustCursor = CompatToolAdjustCursor;
	OLDCALL(AVAppRegisterTool)(tool);  //call original sproc
}
ACCB1 ASBool ACCB2 AVPageViewIsAnnotOfTypeAtPointCompatStub(AVPageView pageView, AVDevCoord xHit, AVDevCoord yHit, ASAtom annotType, ASBool belowOthers, PDAnnot *annot)
{
	return OLDCALL(AVPageViewIsAnnotOfTypeAtPoint)(pageView, StepDown(xHit), StepDown(yHit), annotType, belowOthers, annot);
}
ACCB1 void ACCB2 AVPageViewSetAnnotLocationCompatStub(PDAnnot anAnnot, AVPageView pageView, AVDevCoord x, AVDevCoord y)
{
	OLDCALL(AVPageViewSetAnnotLocation)(anAnnot, pageView, StepDown(x), StepDown(y));
}
static void FixupWindowHandler(AVWindowHandler handler)
{
	if (!handler)
		return; //easy to fixup null handlers
	if (handler->MouseDown) {
		ACROASSERT(handler->MouseDown != (AVWindowMouseDownProc)CompatAVWindowMouseDownProc); //expected a 32-bit callback, not the swapped in 16-bit compatible version
		CompatRegisterThisProc(gProcList[ePROC_WIN_MOUSE_DOWN], (void *) (handler->MouseDown), handler);
		handler->MouseDown = (AVWindowMouseDownProc)CompatAVWindowMouseDownProc;
	}
	if (handler->Draw) {
		ACROASSERT(handler->Draw != (AVWindowDrawProc)CompatAVWindowDrawProc); //expected a 32-bit callback, not the swapped in 16-bit compatible version
		CompatRegisterThisProc(gProcList[ePROC_WIN_DRAW], (void *) (handler->Draw), handler);
		handler->Draw = (AVWindowDrawProc)CompatAVWindowDrawProc;
	}
	if (handler->WillBeResized) {
		ACROASSERT(handler->WillBeResized != (AVWindowWillBeResizedProc)CompatAVWindowWillBeResizedProc); //expected a 32-bit callback, not the swapped in 16-bit compatible version
		CompatRegisterThisProc(gProcList[ePROC_WIN_WILLBERESIZED], (void *) (handler->WillBeResized), handler);
		handler->WillBeResized = (AVWindowWillBeResizedProc)CompatAVWindowWillBeResizedProc;
	}
	if (handler->AdjustCursor) {
		ACROASSERT(handler->AdjustCursor != (AVWindowAdjustCursorProc)CompatAVWindowAdjustCursorProc); //expected a 32-bit callback, not the swapped in 16-bit compatible version
		CompatRegisterThisProc(gProcList[ePROC_WIN_ADJUST_CURSOR], (void *) (handler->AdjustCursor), handler);
		handler->AdjustCursor = (AVWindowAdjustCursorProc)CompatAVWindowAdjustCursorProc;
	}
	if (handler->DidResize) {
		ACROASSERT(handler->DidResize != (AVWindowDidResizeProc)CompatAVWindowDidResizeProc); //expected a 32-bit callback, not the swapped in 16-bit compatible version
		CompatRegisterThisProc(gProcList[ePROC_WIN_DIDRESIZE], (void *) (handler->DidResize), handler);
		handler->DidResize = (AVWindowDidResizeProc)CompatAVWindowDidResizeProc;
	}
}
ACCB1 AVWindow ACCB2 AVWindowNewFromPlatformThingCompatStub(AVWindowLayer layer, Uns32 flags, 
	AVWindowHandler handler, ASExtension owner, AVPlatformWindowRef platformThing)
{
	FixupWindowHandler(handler);
	return OLDCALL(AVWindowNewFromPlatformThing)(layer, flags, (oldAVWindowHandler)handler, owner, platformThing);
}

ACCB1 AVWindow ACCB2 AVWindowNewCompatStub(AVWindowLayer layer, Uns32 flags, AVWindowHandler handler, 
	ASExtension owner)
{
	FixupWindowHandler(handler);
	return OLDCALL(AVWindowNew)(layer, flags, (oldAVWindowHandler)handler, owner);
}
ACCB1 void ACCB2 AVWindowSetMinMaxSizeCompatStub(AVWindow win, const AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVWindowSetMinMaxSize)(win, &r);
}
ACCB1 void ACCB2 AVWindowGetMinMaxSizeCompatStub(AVWindow win, AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVWindowGetMinMaxSize)(win, &r);
}
ACCB1 void ACCB2 AVWindowInvalidateRectCompatStub(AVWindow win, const AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVWindowInvalidateRect)(win, &r);
}
ACCB1 void ACCB2 AVWindowGetInteriorCompatStub(AVWindow win, AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r;
	OLDCALL(AVWindowGetInterior)(win, &r);
	*rect = StepUp(r);
}
ACCB1 void ACCB2 AVWindowGetTitleCompatStub(AVWindow win, ASText title)
{
	ACROASSERT(title);
	char cTitle[1024] = "";
	OLDCALL(AVWindowGetTitle)(win, cTitle, sizeof(cTitle));
	ASTextSetEncoded(title, cTitle, AVAppGetLanguageEncoding());
}
ACCB1 void ACCB2 AVWindowSetTitleCompatStub(AVWindow win, const ASText title)
{
	ACROASSERT(title);
	const char *cTitle = ASTextGetEncoded(title, AVAppGetLanguageEncoding());
	OLDCALL(AVWindowSetTitle)(win, cTitle);
}
ACCB1 void ACCB2 AVWindowSetFrameCompatStub(AVWindow win, const AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVWindowSetFrame)(win, &r);
}
ACCB1 void ACCB2 AVWindowGetFrameCompatStub(AVWindow win, AVRect *rect)
{
	ACROASSERT(rect);
	oldAVRect r;
	OLDCALL(AVWindowGetFrame)(win, &r);
	*rect = StepUp(r);
}
ACCB1 void ACCB2 AVPageViewDrawRectOutlineWithHandlesCompatStub(AVPageView pageView, const AVRect *rect, ASBool bMidpoints, ASBool bThin, ASFixed *dashArray, ASInt32 arrayLen)
{
	ACROASSERT(rect);
	oldAVRect r = StepDown(*rect);
	OLDCALL(AVPageViewDrawRectOutlineWithHandles)(pageView, &r, bMidpoints, bThin, dashArray, arrayLen);
}
ACCB1 ASBool ACCB2 AVAppOpenDialogCompatStub(AVOpenSaveDialogParams dialogParams, ASFileSys *outFileSys, ASPathName **outASPathNames, ASUns16 *outNumASPathNames, ASInt16 *ioChosenFilterIndex)
{
	ACROASSERT(dialogParams);
	oldAVOpenSaveDialogParamsRec oldParams;
	AVOpenSaveDialogParams_to_oldAVOpenSaveDialogParams(*dialogParams, oldParams);
	return OLDCALL(AVAppOpenDialog)(&oldParams, outFileSys, outASPathNames, outNumASPathNames, ioChosenFilterIndex);
}
ACCB1 ASBool ACCB2 AVAppSaveDialogCompatStub(AVOpenSaveDialogParams dialogParams, ASFileSys	*outFileSys, ASPathName	*outASPathName, ASInt16 *ioChosenFilterIndex)
{
	ACROASSERT(dialogParams);
	oldAVOpenSaveDialogParamsRec oldParams;
	AVOpenSaveDialogParams_to_oldAVOpenSaveDialogParams(*dialogParams, oldParams);
	return OLDCALL(AVAppSaveDialog)(&oldParams, outFileSys, outASPathName, ioChosenFilterIndex);
}
ACCB1 ASBool ACCB2 AVAppChooseFolderDialogCompatStub(AVOpenSaveDialogParams dialogParams, ASFileSys *outFileSys, ASPathName *outASPathName)
{
	ACROASSERT(dialogParams);
	oldAVOpenSaveDialogParamsRec oldParams;
	AVOpenSaveDialogParams_to_oldAVOpenSaveDialogParams(*dialogParams, oldParams);
	return OLDCALL(AVAppChooseFolderDialog)(&oldParams, outFileSys, outASPathName);
}
ACCB1 void ACCB2 AVDocPrintPagesWithParamsCompatStub(AVDoc doc, AVDocPrintParams paramsIn)
{
	//kAVEmitTransferFuncs (0x8000) phased out.  Set to opposite of kAVSuppressTransfer
	ACROASSERT(paramsIn);
	if (paramsIn->emitFlags & kAVSuppressTransfer)
		paramsIn->emitFlags &= ~(0x8000);
	else
		paramsIn->emitFlags |= (0x8000);
	AVROUTINE(AcroViewHFT_VERSION_2_2, AVDocPrintPagesWithParams)(doc,paramsIn);  //call original
}
#endif //ACRO_SDK_LEVEL >= 0x00060000
