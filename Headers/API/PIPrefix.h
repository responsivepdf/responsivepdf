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

 PIPrefix.h

 - The bare minimum prefix file required to compile a Macintosh
   plug-in for the Acrobat Viewer.

*********************************************************************/

#ifndef _H_PIPrefix
#define _H_PIPrefix

/**
	Defines the platform-specific header file. It must be <code>"MacPlatform.h"</code> on the Mac OS and <code>"WINPLTFM.H"</code> on Windows.
	PLATFORM is automatically set by the header file.
*/
#define PLATFORM "MacPlatform.h"
/**
	Defines the platform-specific header file. It must be <code>"Plugin.h"</code> on the Mac OS and Windows.
	PRODUCT is automatically set by the header file.
*/
#define PRODUCT "Plugin.h"

#endif
