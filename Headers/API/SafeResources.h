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

 SafeResources.h

*********************************************************************/

#ifndef _H_SafeResources
#define _H_SafeResources

#include <Carbon/Carbon.h>

#ifdef __cplusplus

class StAcroResourceContext
{
public:
				StAcroResourceContext();
				StAcroResourceContext(short resFile);
	virtual		~StAcroResourceContext();

protected :
	short		mOldResFile;
	short		mCurResFile;
};

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

#if !AS_ARCH_64BIT

	pascal Handle SafeGet1Resource(ResType type, short resNum);

pascal Handle SafeGet1NamedResource(ResType type, ConstStr255Param name);

pascal Handle SafeGetResource(ResType type, short resNum);

pascal void SafeGetIndString(Str255 str, short strListID, short index);

pascal StringHandle SafeGetString(short strID);

pascal WindowRef SafeGetNewWindow(short windowID, void *wStorage, WindowRef behind);

pascal WindowRef SafeGetNewCWindow(short windowID, void *wStorage, WindowRef behind);

pascal DialogRef SafeGetNewDialog(short dialogID, void *dStorage, WindowRef behind);

pascal short SafeAlert(short alertID, ModalFilterUPP modalFilter);

pascal short SafeStopAlert(short alertID, ModalFilterUPP modalFilter);

pascal short SafeNoteAlert(short alertID, ModalFilterUPP modalFilter);

pascal short SafeCautionAlert(short alertID, ModalFilterUPP modalFilter);

pascal ControlHandle SafeGetNewControl(short ctrlID, WindowPtr window);

pascal CursHandle SafeGetCursor(short cursID);

pascal Handle SafeGetIcon(short iconID);

pascal OSErr SafeGetIconSuite(IconSuiteRef *theIconSuite, short theResID, IconSelectorValue selector);

pascal CIconHandle SafeGetCIcon(short iconID);

pascal PicHandle SafeGetPicture(short picID);

pascal PatHandle SafeGetPattern(short patternID);

pascal void SafeGetIndPattern(Pattern *thePat, short patternListID, short index);

pascal MenuHandle SafeGetMenu(short menuID);

pascal void SafeModalDialog(ModalFilterUPP modalFilter, short *itemHit);

/* While we still support the SetLocaleFile mechansim, */
/* we suggest you use Mac OS X's localization support  */
/* and bundle your plugin instead.                     */
void SetLocaleFile( UInt8 * langStr, OSType signature );

#endif /* AS_ARCH_64BIT */

#ifdef __cplusplus
}
#endif


#endif /* _H_SafeResources */
