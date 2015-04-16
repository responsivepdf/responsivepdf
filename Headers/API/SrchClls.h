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

 SrchClls.h

*********************************************************************/

#ifndef _H_SrchClls
#define _H_SrchClls

#ifdef DEBUG_EXTENSIONS
#undef PRODUCT
#define PRODUCT "Plugin.h"
#endif

#include "SrchType.h"
#include "SrchHFT.h"

#define SearchExecuteQuery (*((SearchExecuteQuery_SELPROTO)(gSearchHFT[SearchExecuteQuery_SEL])))
#define SearchGetIndexList (*((SearchGetIndexList_SELPROTO)(gSearchHFT[SearchGetIndexList_SEL])))
#define SearchCountIndexList (*((SearchCountIndexList_SELPROTO)(gSearchHFT[SearchCountIndexList_SEL])))
#define SearchGetNthIndex (*((SearchGetNthIndex_SELPROTO)(gSearchHFT[SearchGetNthIndex_SEL])))
#define SearchGetIndexByPath (*((SearchGetIndexByPath_SELPROTO)(gSearchHFT[SearchGetIndexByPath_SEL])))
#define SearchAddIndex (*((SearchAddIndex_SELPROTO)(gSearchHFT[SearchAddIndex_SEL])))
#define SearchRemoveIndex (*((SearchRemoveIndex_SELPROTO)(gSearchHFT[SearchRemoveIndex_SEL])))
#define SearchGetIndexFlags (*((SearchGetIndexFlags_SELPROTO)(gSearchHFT[SearchGetIndexFlags_SEL])))
#define SearchSetIndexFlags (*((SearchSetIndexFlags_SELPROTO)(gSearchHFT[SearchSetIndexFlags_SEL])))
#define SearchGetIndexTitle (*((SearchGetIndexTitle_SELPROTO)(gSearchHFT[SearchGetIndexTitle_SEL])))
#define SearchGetIndexPath (*((SearchGetIndexPath_SELPROTO)(gSearchHFT[SearchGetIndexPath_SEL])))

#define SearchGetIndexByPathEx (*((SearchGetIndexByPathEx_SELPROTO)(gSearchHFT[SearchGetIndexByPathEx_SEL])))
#define SearchAddIndexEx (*((SearchAddIndexEx_SELPROTO)(gSearchHFT[SearchAddIndexEx_SEL])))
#define SearchGetIndexTitleEx (*((SearchGetIndexTitleEx_SELPROTO)(gSearchHFT[SearchGetIndexTitleEx_SEL])))
#define SearchGetIndexPathEx (*((SearchGetIndexPathEx_SELPROTO)(gSearchHFT[SearchGetIndexPathEx_SEL])))
#define SearchGetIndexFileSys (*((SearchGetIndexFileSys_SELPROTO)(gSearchHFT[SearchGetIndexFileSys_SEL])))

#define SearchIsLegacySearchAvailable (*((SearchIsLegacySearchAvailable_SELPROTO)(gSearchHFT[SearchIsLegacySearchAvailable_SEL])))
#define SearchExecuteQueryEx  (*((SearchExecuteQueryEx_SELPROTO)(gSearchHFT[SearchExecuteQueryEx_SEL])))

#endif


