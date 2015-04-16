/*************************************************************************
* WARNING: All additions to this file must go at the end of the file.
* This file is #included to build a table of function pointers (an HFT).
* All components which make use of this HFT rely on the order and
* positioning of these functions (e.g. plug-ins). Adding entries in the 
* middle of this file or modifying existing entries will cause these 
* components to break.
**************************************************************************/

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

TtsHFTProcs.h

 - for AcroTTS HFT functions.

*********************************************************************/

/** 
	Finalizes a speech section shutting down the speech engines used by the TTS object.
	AFTTSIsAvailable() should return <code>false</code> after that. Its use by a plug-in should not be 
	needed at any time, since AcroForms already handles TTS termination. Initialization of TTS 
	is also handled automatically. By calling any function below, AFTTSIsAvailable() should 
	then return <code>true</code>, in case a SAPI engine is installed on the system. 
*/
PIPROC(ASBool, AFTTSEnd, (void), )
/**
	Puts text into the queue to be performed by AFTTSTalk(). 
	@param textdata The text that will be put into the queue. 
	
	@param UseDefaultSpeaker Whether to use the default speaker.
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	
	@see AFTTSQSilence 
	@see AFTTSQSound 
*/
PIPROC(ASBool, AFTTSQueueTextData, (const char* textdata, ASBool UseDefaultSpeaker), textdata, UseDefaultSpeaker)
/**
	Sends whatever is in the queue to be spoken by the SAPI 
	TTS engine. If the text output had been paused, it resumes 
	playback of the queued text. 
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	
	@see AFTTSQueueTextData
*/
PIPROC(ASBool, AFTTSTalk, (void), )
/**
	Puts a sound into the queue. The sound can then be performed 
	by AFTTSTalk(). 
	@param soundName The sound name, which can be one of the following: 
	
	<ul>
	<li><code>ActionCopy</code></li> 
	<li><code>ActionCut</code></li> 
	<li><code>ActionDelete</code></li> 
	<li><code>ActionPaste</code></li> 
	<li><code>DocActive</code></li> 
	<li><code>DocClose</code></li> 
	<li><code>DocOpen</code></li> 
	<li><code>DocPrint</code></li> 
	<li><code>DocSave</code></li> 
	<li><code>KeyEnd</code></li> 
	<li><code>KeyHome</code></li> 
	<li><code>PageTurn</code></li>
	</ul>

	<p>This list can be augmented by adding sound files to the 
	<code>SoundCues</code> folder in Acrobat's installation, in 22kHz 16-bit 
	PCM .wav format.</p>

	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSQSilence 
	@see AFTTSQueueTextData Puts text into the queue to be performed by AFTTSTalk(). 
	@see AFTTSQSilence 
	@see AFTTSQSound 
*/
PIPROC(ASBool, AFTTSQSound, (const char* soundName), soundName)
/** Not implemented in 4.05. */
PIPROC(ASBool, AFTTSQTone, (ASUns32 frequency, ASUns32 duration), frequency, duration)

/**
	Queues a period of silence into the text. 
	@param duration The amount of silence in milliseconds.
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	
	@see AFTTSQSound 
	@see AFTTSQueueTextData 
*/
PIPROC(ASBool, AFTTSQSilence, (ASUns32 duration), duration)
/**
	Resumes playback of text on a paused TTS object. 
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	
	@see AFTTSPause
*/
PIPROC(ASBool, AFTTSResume, (void), )
/**
	Immediately pauses TTS output on a TTS object. Playback 
	of the remaining queued text can be resumed via AFTTSResume(). 
	
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSResume
	@see AFTTSQSound 
	@see AFTTSQueueTextData 
*/
PIPROC(ASBool, AFTTSPause, (void), )
/**
	Stops playback of currently queued text, and flushes the 
	queue. Playback of queued text cannot be resumed. 
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSReset 
	@see AFTTSQueueTextData
*/
PIPROC(ASBool, AFTTSStop, (void), )
/**
	Stops playback of the currently queued text, and flushes 
	the queue. It resets all the properties of the TTS object to 
	their default values. 

	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSStop
	@see AFTTSPause
	@note Text playback cannot be resumed via AFTTSResume(). 
*/
PIPROC(ASBool, AFTTSReset, (void), )
/**
	Gets the voice name of any of the available speakers in 
	the installed TTS engine. 
	@param index The index of the speaker.
	@return The name of the voice. 
	@see AFTTSSetSpeaker 
*/
PIPROC(char*, AFTTSGetVoiceName, (ASInt32 index), index)
/**
	Determines whether the TTS object is available and the Text-to-Speech 
	engine can be used. 

	@return <code>true</code> if the Text-to-Speech engine can be used, <code>false</code> otherwise. 
	@note Calling any method in this API causes the Forms plug-in 
	to initialize TTS automatically if an SAPI engine is installed 
	on the system. 
*/
PIPROC(ASBool, AFTTSIsAvailable, (void), )
/**
	Gets the name of the current speaker. 
	@return The name of the current speaker. 
	@see AFTTSSetSpeaker
*/
PIPROC(char*, AFTTSGetSpeaker, (void), )
/** Not implemented in 4.05. */
PIPROC(char*, AFTTSGetPunctuations, (void), )
/**
	Gets the speed at which text is being spoken by the TTS 
	engine. 
	@return The speed, in words per minute, at which text 
	is being spoken. 
	@see AFTTSSetSpeechRate
	@see AFTTSSetSpeaker 
*/
PIPROC(ASUns32, AFTTSGetSpeechRate, (void), )
/** Not implemented in 4.05. */
PIPROC(ASUns32, AFTTSGetCharacterScale, (void), )
/**
	Gets the volume for the speaker. 
	@return The volume. Valid values are from <code>0</code> (mute) to <code>10</code> (loudest). 
	The default is <code>5</code>. 
	@see AFTTSSetVolume

	@note Calling any method in this API causes the Forms plug-in 
	to initialize TTS automatically if an SAPI engine is installed 
	on the system. 
	
*/
PIPROC(ASUns32, AFTTSGetVolume, (void), )
/**
	Gets the baseline pitch for the voice of a speaker. 
	@return The baseline pitch. The valid range is from <code>0</code> to <code>10</code>, with 
	<code>5</code> being the default for the speaker. 
	@see AFTTSSetPitch
	Gets the name of the current speaker. 
	@see AFTTSSetSpeaker
*/
PIPROC(ASUns32, AFTTSGetPitch, (void), )
/**
	Gets the number of different speakers available to the current 
	TTS engine. 
	@return The number of speakers available. 
	@see AFTTSGetVoiceName
*/
PIPROC(ASUns32, AFTTSGetNumberOfVoices, (void), )
/**
	Sets the current voice. Valid values are any of those enumerated 
	via AFTTSGetVoiceName() and AFTTSGetNumberOfVoices(). 
	@param voiceName The speaker name.
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSGetSpeaker 
*/
PIPROC(ASBool, AFTTSSetSpeaker, (const char* voiceName), voiceName)
/** Not implemented in 4.05. */
PIPROC(ASBool, AFTTSSetPunctuations, (const char* punctuations), punctuations)
/**
	Sets the speed at which text is being spoken by the TTS 
	engine. 
	@param speed The speed in words per minute.
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSGetSpeechRate 
	@see AFTTSGetVolume 
*/
PIPROC(ASBool, AFTTSSetSpeechRate, (ASUns32 speed), speed)
/** Not implemented in 4.05. */
PIPROC(ASBool, AFTTSSetCharacterScale, (ASUns32 chrScale), chrScale)
/**
	Sets the speech volume. 
	@param volume The volume. Valid values are from <code>0</code> (mute) 
	to <code>10</code> (loudest).
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	@see AFTTSGetVolume 
*/
PIPROC(ASBool, AFTTSSetVolume, (ASUns32 volume), volume)
/**
	Sets the baseline pitch for the voice of a speaker. 
	@param pitch The baseline pitch. The valid range is from 
	<code>0</code> to <code>10</code>, with <code>5</code> being the default for the speaker.
	@return <code>true</code> if the speech engine is available, <code>false</code> otherwise. 
	
	@see AFTTSGetPitch 
	@see AFTTSGetSpeaker 
*/
PIPROC(ASBool, AFTTSSetPitch, (ASUns32 pitch), pitch)
/** Sets the function to be called when TTS finished speaking. <code>NULL</code> disables
   callbacks. */
PIPROC(void, AFTTSSetNotify, (AFTTSNotifyProc proc), proc)
