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

 Environ.h

 - This file checks for the existence of a PLATFORM macro and, if it
   exists, #includes the file it points to. Said file should define
   the macros listed below in accordance with the development platform,
   runtime environment and runtime OS.

   Same now applies for the PRODUCT macro.

*********************************************************************/

#ifndef _H_Environ
#define _H_Environ

#ifndef PLATFORM
#ifdef WIN_ENV
#define PLATFORM "winpltfm.h"
#elif __OS2__
#define PLATFORM "os2pltfm.h"
#elif defined(unix) || defined(__unix)
 #define PLATFORM "UnixPlatform.h"
#else
#error You must define the PLATFORM macro
#endif
#endif

#include PLATFORM

#define qWR 1

#ifndef MAC_ENV
#ifdef MAC_PLATFORM
#define MAC_ENV 1		/* MAC_ENV is an archaic synonym for MAC_PLATFORM */
#endif
#endif

#ifndef ACCB1
#error PLATFORM failed to #define ACCB1
#endif

#ifndef ACCB2
#error PLATFORM failed to #define ACCB2
#endif

#ifndef ACCBPROTO1
#error PLATFORM failed to #define ACCBPROTO1
#endif

#ifndef ACCBPROTO2
#error PLATFORM failed to #define ACCBPROTO2
#endif

#ifndef PRODUCT
#if defined(WIN_ENV) || defined(UNIX_PLATFORM) || defined(OS2_PLATFORM)
#define PRODUCT "Plugin.h"
#else
#error You must define the PRODUCT macro
#endif
#endif

#include PRODUCT

#endif

