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

 WinExpT.h

 - Types required to use the Windows HFT.

*********************************************************************/

#ifndef _H_WIN_EXPT
#define _H_WIN_EXPT

#include <oaidl.h>

#ifdef __cplusplus
extern "C" {
#endif
  
typedef ACCBPROTO1 ASAtom(ACCBPROTO2 *COMServerGetNameProcType)(void);
typedef ACCBPROTO1 ASAtom(ACCBPROTO2 *COMServerGetNameProcTypeEx)(void* clientData);
//you can use either IDispatch call, depending on if you need to have your COMServer clientData passed back
typedef ACCBPROTO1 IDispatch*(ACCBPROTO2 *COMServerGetIDispatchProcType)(void);
typedef ACCBPROTO1 IDispatch*(ACCBPROTO2 *COMServerGetIDispatchProcTypeEx)(void* clientData);

// Try to minimize C4786 compiler warnings 
#if _DEBUG
#define _t_COMServer _CSvr
#endif

typedef struct _t_COMServer {
	ASSize_t size;
	COMServerGetNameProcType		GetName;
	COMServerGetIDispatchProcType	GetIDispatch;  

	COMServerGetNameProcTypeEx		GetNameEx; //if not null this is called instead of GetName
	COMServerGetIDispatchProcTypeEx	GetIDispatchEx; //if not null this is called instead of GetIDispatch
	void*							clientData; //passed back to the Ex routines
} COMServerRec, *COMServer;


#ifdef __cplusplus
}
#endif

#endif /* _H_WIN_EXPT */

