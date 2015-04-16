/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 2000-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 ConsExpT.h

*********************************************************************/

#ifndef __CONSEXPT_H__
#define __CONSEXPT_H__

#include "ASExpT.h"
#include "CosExpT.h"
#include "ConsObTp.h"

/**
	A type corresponding to the <code>enum</code> defined in <code>ConsObTp.h</code>. This 
	type is used to refer to specific object types in PDF. It is specifically used by Agents to make 
	object requests of the framework, and is used by the framework 
	to report the types of objects found. 
	@see PDFObjTypeGetSuperclass 
	@see ConsAgentObjFoundCallback
*/

typedef ASUns32	PDFObjType;

/**
	An opaque traversal stack object. The <code>ConsStackXXX</code> methods 
	allow retrieval of individual members of the <code>PDFObjType</code> 
	and <code>CosObj</code> stacks associated with a Consultant object. 
	@see ConsStackGetCount 
	@see ConsStackIndexGetArrayIndex 
	@see ConsStackIndexGetDictKey 
	@see ConsStackIndexGetObj 
	@see ConsStackIndexGetTypeAt 
	@see ConsStackIndexGetTypeCount 
	@see ConsStackIndexIsArray 
	@see ConsStackIndexIsDict 
	@see ConsAgentObjFoundCallback
*/
typedef struct tagConsStack* ConsStack;

/**
	The opaque type to allow programs to retain handles to create 
	PDF Consultant and Accessibility Checker objects. 
	@see numerous
*/

typedef struct tagConsultant* Consultant;


/** Bit flags that instruct the Consultant about how to handle a found object.
	A logical <code>OR</code> of these values should be returned by the <code>ObjFound</code> callback. 
	@see ConsAgentObjFoundCallback
*/

enum tagConsultantAgentAction
{
	/** The Consultant makes no changes to the current object. Use
		this if the Agent is only gathering information or if the Agent
		is in charge of making all the modifications itself.
	*/
	AC_NOCHANGE		= 0,
	/** Instructs the Consultant to replace this occurence of the
		current object in the document with the one retured via the
		<code>pObjToReturn</code> parameter to the <code>ObjFound</code> callback. You
		can optionally combine this with <code>AC_REVISIT</code> or
		<code>AC_CHANGEALL</code>.
	*/
	AC_REPLACE		= 1,
	/** Instructs the Consultant to remove this occurence of the
		current object in the document. You can optionally combine
		this with <code>OD_REVISIT</code> or <code>OD_CHANGEALL</code>.
	*/
	AC_REMOVE		= 2,
	/** Instructs the Consultant to visit this object again if it is
		encountered again. You can combine this with any flag except
		<code>OD_NEVERREVISIT</code> or <code>OD_CHANGEALL</code>.
	*/
	AC_REVISIT		= 4,
	/** Instructs the Consultant that under no circumstances should
		the object be revisited, regardless of whether it is reclassified
		when encountered again. It is only applicable in the mode in
		which the Consultant pays attention to object classification
		when determining whether an obect has already been visited.
	*/
	AC_NEVERREVISIT	= 8,
	/** You must use this in conjunction with either <code>OD_REPLACE</code> or
		<code>OD_REMOVE</code>. It instructs the Consultant to silently perform the
		desired operation on all instances of the current object,
		without calling the <code>ObjFound</code> callback again for this object.
	*/
	AC_CHANGEALL	= 16
};

typedef ASUns32 ConsultantAgentAction;

/**
	The Consultant calls this method when it is ready to finish 
	a cycle. You should perform any document modifications assigned 
	to your Agent at this point. 
*/

typedef void ( *ConsAgentPostProcessCallback )( struct tagConsultantAgent* );


/**
	Returns a set of flags instructing the Consultant as to 
	how to handle the current object. The Consultant calls this 
	method when it recognizes the current object as a type which 
	an Agent has declared to be <i>interesting</i>. 
	@param agent The agent containing the callback. 
	@param hObj The object the Consultant has just encountered, 
	which has matched one of the types in any of the registered 
	Agent's array of interesting types. 
	@param pObjTypeHierarchy A list of the object type classifications 
	this object met. The array runs from index <code>0</code>, the most specific 
	object classification, to index <code>iSizeObjHierarchy</code>, the most 
	general. 
	@param iSizeObjHierarchy The size of the type array. 
	@param Stack A reference to the Consultant's traversal 
	stack, which allows read-only access to parents of the current 
	object as well as their respective types. 
	@param pObjToReturn If present, an object the Consultant 
	uses to replace the current object in the document.
	@return A logical <code>OR</code> of bit flags that instruct the Consultant how 
	to handle the current object (for example, remove it, replace it, ignore 
	it, and so on). 
*/

typedef ConsultantAgentAction ( *ConsAgentObjFoundCallback )( struct tagConsultantAgent*, CosObj, const PDFObjType*, ASUns32, ConsStack, CosObj* );


/** The Consultant calls this method with progress updates. It can display a progress bar.
	@param fPercentDone A number between <code>0</code> and <code>100</code>, indicating the percent of the current
	document that the Consultant has processed so far.
*/

typedef void ( *ConsAgentPercentDoneCallback )( ASReal fPercentDone );


/**
	During traversal, the Consultant checks the Agent's list 
	of object types of interest to see if the Agent is interested 
	in the current object, and it calls the callback function 
	pointers when objects of interest are found and when traversal 
	is complete. 

	<p>All Agents should be C++ classes derived from the <code>ConsultantAgentObj</code> 
	class (found in agentobj.h) which can be converted (via 
	a C++ cast operator) to a pointer to this structure type. 
	Wherever the Consultant HFT calls for a <code>(struct Agent*)</code>, 
	you can pass the class with no conversion. </p>
	@see ConsultantRegisterAgent 
	@see ConsAgentObjFoundCallback  
*/

typedef struct tagPDFObjID
{
	CosID			objID;
	CosGeneration	objGen;
}	PDFObjID;

typedef struct tagConsultantAgent
{
	/** The size of the data structure. Set it to <code>sizeof(Agent)</code>. */
	ASSize_t						Size;			
	/** An array of object types of interest. */
	const PDFObjType*				pFindObjects;	
	/** The number of object types in the <code>pFindObjects</code> array. */
	ASUns32							NumFindObjects; 
	/** A callback procedure for post-processing. */
	ConsAgentPostProcessCallback	PostProcess;    
	/** A callback procedure for when an object is found. */
	ConsAgentObjFoundCallback		ObjFound;       
	/** Indicates if the Agent also wants to be called
		back for subclasses of types in <code>pFindObjects</code>.
	*/
	ASBool							WantSubclasses;
	const CosObj*					pFindObjectIDs;	  /* List of objects of interest*/
	ASUns32							NumFindObjectIDs; /* Count of above list */
	ConsAgentObjFoundCallback		ObjIDFound;       /* Callback when object of a specific ID is found */
}	ConsultantAgent;


#ifdef __cplusplus

/**	When PDF Consultant Agent code is written in C++, it is strongly recommended 
	that the class below be used as an interface definition for the Agent itself.
	The functionality is provided within this base class to cast to the simple
	C-callable Agent class above, so this class simply provides a cleaner
	way to implement an Agent. */
class ConsultantAgentObj
{
	protected:
		/*	The "shell" in which a C-calling convention can actually pass
			around an instance of the class. Via the overloaded
			(Agent) cast operator, the class can make itself look like
			the ConsultantAgent struct defined above, while maintaining 
			all of its class/instance information */
		typedef struct tagAgentShell
		{
			ConsultantAgent		BaseAgent;
			ConsultantAgentObj*	pAgentClass;

		}	AgentShell;

		AgentShell m_AgentShell;

	public:
		/** Called by the Consultant when it has completed its traversal. */
		virtual void PostProcess( void ) = 0;


		/**
			Bit flags that instruct the Consultant about how to handle 
			a found object. A logical <code>OR</code> of these values should be returned 
			by the <code>ObjFound</code> callback. 
		*/
		virtual ConsultantAgentAction ObjFound( CosObj Obj, const PDFObjType* pObjTypeHierarchy, 
					const ASUns32 iSizeObjHierarchy, ConsStack Stack, CosObj* pObjRet ) = 0;
		
		/**	The constructor initializes the internal structure so that it is available
			for outside access. The array of requested objects is <i>copied</i> into the
			member storage variables. This is to ease the burden of constructing
			an Agent. */
		ConsultantAgentObj( const PDFObjType* pRequestedObjs, ASUns32 iNumRequestedObjs, ASBool bWantSubclasses = true )
		{
			m_AgentShell.pAgentClass = this;
			m_AgentShell.BaseAgent.Size				= sizeof( m_AgentShell.BaseAgent );
			m_AgentShell.BaseAgent.pFindObjects		= pRequestedObjs;
			m_AgentShell.BaseAgent.NumFindObjects	= iNumRequestedObjs;
			m_AgentShell.BaseAgent.PostProcess		= ( ConsAgentPostProcessCallback )DoPostProcess;
			m_AgentShell.BaseAgent.ObjFound			= ( ConsAgentObjFoundCallback )DoObjFound;
			m_AgentShell.BaseAgent.WantSubclasses	= bWantSubclasses;
			m_AgentShell.BaseAgent.pFindObjectIDs	= NULL;
			m_AgentShell.BaseAgent.NumFindObjectIDs = 0;
			m_AgentShell.BaseAgent.ObjIDFound		= NULL;

		};

		/** The destructor for the class. */
		virtual ~ConsultantAgentObj( void ) { };

		/**	Provides automatic conversion to a C-language and hence C-callable <code>struct</code> (for HFT's and so on). */
		operator const ConsultantAgent* ( void ) const { return ( const ConsultantAgent* )&m_AgentShell; }
		operator ConsultantAgent* ( void ) const { return ( ConsultantAgent* )&m_AgentShell; }

		/**	Functions that do not depend on the class' <code>this</code> pointer being present. So,
			these can be called from C or from an HFT. Hence, they require an
			active agent as a parameter. */
		static void DoPostProcess( ConsultantAgent* pAgent ) { ( ( AgentShell* )pAgent )->pAgentClass->PostProcess(); };

		/** A callback called when an object is found. */
		static ASInt32 DoObjFound( ConsultantAgent* pAgent, CosObj Obj, const PDFObjType* pObjTypeHierarchy, 
									const ASUns32 iSizeObjHierarchy, ConsStack Stack, CosObj* pObjRet )
		{
			return ( ( AgentShell* )pAgent )->pAgentClass->ObjFound( Obj, pObjTypeHierarchy, iSizeObjHierarchy, Stack, pObjRet );
		};

};

/* 7/14/2008 - Change from PDFObjID to CosObj in the RequestedObjID list */
class ConsultantObjIDAgentObj : public ConsultantAgentObj
{
	public:
		/* Called by the Consultant when it finds an object whose identifier is of interest to the agent. */
		virtual ConsultantAgentAction ObjIDFound( CosObj Obj, const PDFObjType* pObjTypeHierarchy, 
					const ASUns32 iSizeObjHierarchy, ConsStack Stack, CosObj* pObjRet ) = 0;

		ConsultantObjIDAgentObj( const PDFObjType* pRequestedObjs, ASUns32 iNumRequestedObjs, 
							const CosObj* pRequestedObjIDs, ASUns32 iNumRequestedObjIDs,
							ASBool bWantSubclasses = true )
							:ConsultantAgentObj(pRequestedObjs, iNumRequestedObjs, bWantSubclasses)
		{
			m_AgentShell.BaseAgent.pFindObjectIDs	= pRequestedObjIDs;
			m_AgentShell.BaseAgent.NumFindObjectIDs = iNumRequestedObjIDs;
			m_AgentShell.BaseAgent.ObjIDFound		= ( ConsAgentObjFoundCallback )DoObjIDFound;
		};

		static ASInt32 DoObjIDFound( ConsultantAgent* pAgent, CosObj Obj, const PDFObjType* pObjTypeHierarchy, 
									const ASUns32 iSizeObjHierarchy, ConsStack Stack, CosObj* pObjRet )
		{
			return ( (ConsultantObjIDAgentObj*) ( ( AgentShell* )pAgent )->pAgentClass)->ObjIDFound( Obj, pObjTypeHierarchy, iSizeObjHierarchy, Stack, pObjRet );
		};
};

#endif /* __cplusplus */


/** Modes that an agent <i>must</i> pass to the PDF Consultant to define behavior
   when the <code>RegisterAgent</code> function is called. 

   <p>It is important to note that the Consultant framework can only be in 
   one mode at a time. If multiple agents register with different modes, 
   the last mode to be assigned is the one that is eventually used. As always, 
   group similar agents together to avoid conflicts such as this. </p>
*/

#define REQUIRES_CLASSIFY	128		/* A bit set for all modes that require
									   the Consultant to keep track of object
									   type classification. */

/** 
	Constants that specify an operation mode for the Consultant. This value determines
	whether and how often the Consultant should revisit objects that have been previously
	encountered.
*/
enum tagRegAgentFlag
{
	/** Revisit unknown objects only. Once the object is of a known type,
	   that object is no longer visited. Visit all objects of known types 
	   only once (unless an agent returns <code>OD_REVISIT</code> for the object). */
	REG_ONLYREVISITUNKNOWN = 0,

	/** Do not revisit objects of any type, whether or not they are
	   later encountered with a new classification at some point. 
	   Only revisit an object if an agent returns <code>OD_REVISIT</code> for 
	   the object.  */
	REG_REVISITNONE,

	/** Revisit an object whenever it is encountered again with a new 
	   classification (regardless of whether the new classification is
	   as an unknown type). */
	REG_REVISITRECLASS_ALL = REQUIRES_CLASSIFY, /* From here on in the enum,
												   all modes require that the
												   Consultant save object type
												   classification info. */

	/** Revisit an object whenever it is encountered again with a new
	   classification, but always revisit objects classified as 
	   <i>unknown</i> (even if the object has previously been encountered and 
	   classified as unknown). */
	REG_REVISITRECLASS_ALWAYSUNKNOWN,

	/*	Revisit all objects at least once, and more if client returns <code>AC_REVISIT</code>. At least one node in the
	    Cos graph rooted at a certain <code>CosObj</code> must return <code>AC_REVISIT</code> if that <code>CosObj</code> is to be revisited. It makes
		sense only in the <code>POSTORDER</code> scrubber traversal mode.
		It avoids infinite cycles by making sure that the node that is about to be visited is not already
		on the traversal stack. */
	REG_REVISIT_ONDEMAND = 0x00000100
};

typedef ASUns32	RegAgentFlag;

#endif /* __CONSEXPT_H__ */
