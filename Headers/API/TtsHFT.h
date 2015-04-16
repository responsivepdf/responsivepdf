/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1998-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 TTSHFT.h

 - HFT definitions for Acrobat TTS procedures.

 - The Acrobat Forms plug-in now provides a speech server API
   implemented over SAPI (Windows Speech API) to deal with
   text-to-speech conversion in accessibility for people with visual
   and reading disabilities, and document vocalization issues in Acrobat.

   It exports another HFT in parallel to its common AcroForms HFT. To
   use the AcroTTS HFT, a plug-in must include the header file
   TTSHFT.H, which includes AFTTS_SEL.H. Plug-ins must also import the
   HFT using ASExtensionMgrGetHFT and assign the HFT returned by this
   call to a plug-in-defined global variable named gAcroTTSHFT.

   The easiest way to do this is to use the Init_AcroTTSHFT macro
   defined in TTSHFT.h.

*********************************************************************/

#ifndef _H_TTSHFT
#define _H_TTSHFT

/*****************************************************************************
  Selectors for all AcroForms TTS HFT functions.
*****************************************************************************/
#include "AFTTS_Sel.h"

#if __cplusplus
extern "C" {
#endif	/* __cplusplus */

extern HFT gAcroTTSHFT;

#if __cplusplus
}
#endif	/* __cplusplus */

/** Use this to initialize and make the TTS HFT functions available to your plug-in. */
#define Init_AcroTTSHFT ASExtensionMgrGetHFT(ASAtomFromString(AcroTTSHFT_NAME), AcroTTSHFT_LATEST_VERSION)

#define AFTTSEnd (*((AFTTSEnd_SELPROTO)(gAcroTTSHFT[AFTTSEnd_SEL])))

#define AFTTSQueueTextData (*((AFTTSQueueTextData_SELPROTO)(gAcroTTSHFT[AFTTSQueueTextData_SEL])))

#define AFTTSTalk (*((AFTTSTalk_SELPROTO)(gAcroTTSHFT[AFTTSTalk_SEL])))

#define AFTTSQSound (*((AFTTSQSound_SELPROTO)(gAcroTTSHFT[AFTTSQSound_SEL])))

#define AFTTSQTone (*((AFTTSQTone_SELPROTO)(gAcroTTSHFT[AFTTSQTone_SEL])))

#define AFTTSQSilence (*((AFTTSQSilence_SELPROTO)(gAcroTTSHFT[AFTTSQSilence_SEL])))

#define AFTTSResume (*((AFTTSResume_SELPROTO)(gAcroTTSHFT[AFTTSResume_SEL])))

#define AFTTSPause (*((AFTTSPause_SELPROTO)(gAcroTTSHFT[AFTTSPause_SEL])))

#define AFTTSStop (*((AFTTSStop_SELPROTO)(gAcroTTSHFT[AFTTSStop_SEL])))

#define AFTTSReset (*((AFTTSReset_SELPROTO)(gAcroTTSHFT[AFTTSReset_SEL])))

#define AFTTSGetVoiceName (*((AFTTSGetVoiceName_SELPROTO)(gAcroTTSHFT[AFTTSGetVoiceName_SEL])))

#define AFTTSIsAvailable (*((AFTTSIsAvailable_SELPROTO)(gAcroTTSHFT[AFTTSIsAvailable_SEL])))

#define AFTTSGetSpeaker (*((AFTTSGetSpeaker_SELPROTO)(gAcroTTSHFT[AFTTSGetSpeaker_SEL])))

#define AFTTSGetPunctuations (*((AFTTSGetPunctuations_SELPROTO)(gAcroTTSHFT[AFTTSGetPunctuations_SEL])))

#define AFTTSGetSpeechRate (*((AFTTSGetSpeechRate_SELPROTO)(gAcroTTSHFT[AFTTSGetSpeechRate_SEL])))

#define AFTTSGetCharacterScale (*((AFTTSGetCharacterScale_SELPROTO)(gAcroTTSHFT[AFTTSGetCharacterScale_SEL])))

#define AFTTSGetVolume (*((AFTTSGetVolume_SELPROTO)(gAcroTTSHFT[AFTTSGetVolume_SEL])))

#define AFTTSGetPitch (*((AFTTSGetPitch_SELPROTO)(gAcroTTSHFT[AFTTSGetPitch_SEL])))

#define AFTTSGetNumberOfVoices (*((AFTTSGetNumberOfVoices_SELPROTO)(gAcroTTSHFT[AFTTSGetNumberOfVoices_SEL])))

#define AFTTSSetSpeaker (*((AFTTSSetSpeaker_SELPROTO)(gAcroTTSHFT[AFTTSSetSpeaker_SEL])))

#define AFTTSSetPunctuations (*((AFTTSSetPunctuations_SELPROTO)(gAcroTTSHFT[AFTTSSetPunctuations_SEL])))

#define AFTTSSetSpeechRate (*((AFTTSSetSpeechRate_SELPROTO)(gAcroTTSHFT[AFTTSSetSpeechRate_SEL])))

#define AFTTSSetCharacterScale (*((AFTTSSetCharacterScale_SELPROTO)(gAcroTTSHFT[AFTTSSetCharacterScale_SEL])))

#define AFTTSSetVolume (*((AFTTSSetVolume_SELPROTO)(gAcroTTSHFT[AFTTSSetVolume_SEL])))

#define AFTTSSetPitch (*((AFTTSSetPitch_SELPROTO)(gAcroTTSHFT[AFTTSSetPitch_SEL])))

#define AFTTSSetNotify (*((AFTTSSetNotify_SELPROTO)(gAcroTTSHFT[AFTTSSetNotify_SEL])))

#endif
