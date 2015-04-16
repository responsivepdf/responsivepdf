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
 Copyright (C) 2000-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

**********************************************************************/


/**
	Allocates and intializes a new Consultant object. Use the 
	returned object to call the other Consultant API functions. 
	When you are finished with this object, you must destroy 
	it using the ConsultantDestroy() function. 
	<p>An Acrobat exception is raised on failure. </p>
	@param pPercentDoneCallBack A function pointer to be called back with progress 
	updates. It may be <code>NULL</code>.
	@return The Consultant object that was created. 
	@see ConsultantDestroy 
*/
PIPROC ( Consultant, ConsultantCreate, ( ConsAgentPercentDoneCallback pPercentDoneCallBack ), pPercentDoneCallBack)

/* ConsultantDestroy

   Halts traversal by the given Consultant, detatches all Agents, and destroys it.
   Must be called on all Consultants created via ConsultantCreate.

   Raises on failure.
*/
/**
	Detaches all Agents and destroys the given Consultant object, 
	invalidating its handle. You must never call this on a Consultant 
	that is currently running. 
	<p>An Acrobat exception is raised on failure. </p>
	@param hConsultantToDestroy A valid Consultant object 
	handle as returned by ConsultantCreate(). The handle is invalid 
	after the call returns.
*/
PIPROC ( void, ConsultantDestroy, ( Consultant hConsultantToDestroy ), hConsultantToDestroy)

/**
	Starts the given Consultant object traversing at the given 
	Cos object. It traverses and processes all objects beneath 
	<code>obj</code>, classifying the types of objects based on the fact that 
	<code>obj</code> is of the given <code>ObjType</code>. 

	<p>It is never allowed to destroy a Consultant object that is 
	currently executing a call to ConsultantTraverseFrom(). To 
	properly destroy a running Consultant, you must first call ConsultantSuspend(). 
	ConsultantTraverseFrom() raises an exception under 
	any other conditions, and may also raise an exception as 
	the result of a registered Agent's raising an exception 
	during the operation.</p> 

	<p>An Acrobat exception is raised if the Consultant has been started 
	and is not in a suspended state.</p> 

	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate(). It is the Consultant with which the Agent 
	will be registered. 
	@param hObj The object at which to start traversal. 
	@param kObjType The object type of the specified start 
	object. It may be <code>PT_NULL</code>, in which case the Consultant attempts 
	to determine the type of the object itself. You should specify 
	a value other than <code>PT_NULL</code> whenever possible.

*/
PIPROC ( void, ConsultantTraverseFrom, ( Consultant hConsultant, CosObj hObj, PDFObjType kObjType ), hConsultant, hObj, kObjType )

/**
	Registers the given agent with the given consultant, so 
	that the agent is called when the consultant encounters 
	objects of interest. 

	<p>An Acrobat exception is raised if the Consultant has been started 
	and is not in a suspended state. </p>

	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate(). It is the Consultant with which the Agent 
	will be registered. 
	@param pAgent The Agent to register, of a 
	type derived from the <code>ConsultantAgentObj</code> base class. 
	@param kFlag A flag indicating the mode in which the Consultant 
	should operate. 
*/
PIPROC ( void, ConsultantRegisterAgent, ( Consultant hConsultant, const ConsultantAgent* pAgent, RegAgentFlag kFlag ), hConsultant, pAgent, kFlag )

/**
	Resets the suspended Consultant and starts a new traversal 
	from the given starting object. 

	<p>If you do not know the type of the object, the Consultant 
	will attempt to determine it. This function does not return 
	until the entire path beneath the starting object has been 
	traversed. The Consultant passes to the registered Agents 
	all objects it encounters that have been registered as <i>interesting</i>. </p>
	
	<p>An Acrobat exception is raised if the Consultant has been started 
	and is not in a suspended state. </p>

	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate(). It is the Consultant with which the Agent 
	will be registered. 
	@param hObjStart The object at which to restart traversal. 
	Usually, for traversing an entire document, this is the 
	Catalog. 
	@param kInitType The object type of the specified start 
	object. It may be <code>PT_NULL</code>, in which case the Consultant attempts 
	to determine the type of the object itself. You should specify 
	a value other than <code>PT_NULL</code> whenever possible In most cases, 
	for traversing the entire document, the starting object 
	is the Catalog so the type is <code>PT_CATALOG</code>.
*/
PIPROC ( void, ConsultantSetStart, ( Consultant hConsultant, CosObj hObjStart, PDFObjType kInitType ), hConsultant, hObjStart, kInitType )

/**
	Instructs the Consultant to process the next object in the 
	current traversal. It assumes that the Consultant has been 
	suspended and reset with calls to ConsultantSuspend() and 
	ConsultantSetStart(). This function does not un-suspend a Consultant, 
	so you can call it repeatedly. It returns after all registered 
	Agents have processed the object. 

	<p>An Acrobat exception is raised if you call it on a running 
	Consultant. </p>

	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
	@return <code>true</code> if the process is done or there has been a problem, 
	<code>false</code> otherwise. 
*/
PIPROC ( ASBool, ConsultantNextObj, ( Consultant hConsultant ),  hConsultant)

/**
	Returns an estimate (from <code>0</code> to <code>100</code>) of what percentage of 
	the current document has been processed by the Consultant. 
	You can call this function at any time. 
	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
	@return A number from <code>0</code> to <code>100</code>. 
*/
PIPROC ( ASReal, ConsultantGetPercentDone, ( Consultant hConsultant ),  hConsultant)

/**
	Returns the number of direct objects that the Consultant 
	has processed so far. This count may include some objects 
	twice, depending on revisitation of objects. This count is 
	reset on calls to ConsultantTraverseFrom() and ConsultantSetStart().	
	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
	@return The number of direct objects the Consultant has visited 
	so far. 
*/
PIPROC ( ASUns32, ConsultantGetNumDirectVisited, ( Consultant hConsultant ),  hConsultant)

/**
	Returns the number of indirect objects that the Consultant 
	has processed so far. This count may include some objects 
	twice, depending on revisitation of objects. This count is 
	reset on calls to ConsultantTraverseFrom() and ConsultantSetStart().
	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
	@return The number of indirect objects the Consultant has visited 
	so far. 
*/
PIPROC ( ASUns32, ConsultantGetNumIndirectVisited, ( Consultant hConsultant ),  hConsultant)

/**
	Suspends the Consultant, even if it is currently executing 
	a call to ConsultantCreate() or ConsultantResume(). This function 
	causes currently executing calls to ConsultantTraverseFrom() 
	to return. It is allowed to call this function from within 
	the ScrubPercentDoneCallback() passed to the Consultant on 
	ConsultantCreate(). Calls to ConsultantTraverseFrom() that are 
	currently in progress will return when ConsultantSuspend() 
	is called. 

	<p>To resume, call ConsultantResume(). </p>

	<ul>
	<li>You can call ConsultantNextObj() on a suspended Consultant, 
	which removes the suspension and causes the Consultant to 
	process the next object. </li>
	<li>You can destroy a Consultant that has been suspended. </li>
	<li>If you call ConsultantTraverseFrom() on a suspended Consultant, 
	it will reset the operation of the Consultant, but the Consultant 
	will remain in a suspended state and will not process the 
	document further. </li>
	</ul>

	<p>This function does nothing if you call it on a Consultant 
	object that is already suspended, or if it was never started. </p>
	
	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
*/
PIPROC ( void, ConsultantSuspend, ( Consultant hConsultant ), hConsultant )

/**
	Resumes a previously suspended Consultant at the point in 
	the traversal where it stopped. This function does not return 
	from traversing and notifying Agents until the traversal 
	is complete or ConsultantSuspend() is called. The function 
	does nothing if the Consultant object is already running 
	or has not been started. 
	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
*/
PIPROC ( void, ConsultantResume, ( Consultant hConsultant ), hConsultant )

/**
	Returns the number of objects currently on Consultant's 
	traversal stack. The stack includes the objects that the 
	Consultant has visited on its path to the current object, 
	meaning all parents of the current object but 
	not the object itself. 

	<p>An Acrobat exception is raised on error. </p>

	@param hConsultant The Consultant's traversal stack.
	@return The number of objects on the Consultant.'s traversal stack. 
*/
PIPROC ( ASUns32, ConsStackGetCount, ( ConsStack hConsultant ),  hConsultant)

/**
	Gets the the Cos object at the given index into the stack. 
	
	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The point at which to find the object.
	@return The object at the specified point in the Consultant's traversal 
	stack. 
*/
PIPROC ( CosObj, ConsStackIndexGetObj, ( ConsStack hConsultant, ASUns32 iIndex ), hConsultant, iIndex )

/**
	Gets the size of the type hierarchy at the given index into 
	the stack. 
	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The object in question.
	@return The size of the type hierarchy. 
	It tests whether the given index into the stack is a <code>CosArray</code>. 	
	@return <code>true</code> if the object found at the index point is an array, 
	<code>false</code> otherwise. 
*/
PIPROC ( ASUns32, ConsStackIndexGetTypeCount, ( ConsStack hConsultant, ASUns32 iIndex ),  hConsultant, iIndex)

/**
	Gets a type from the type array at each index in the stack. 
	Since there are potentially multiple types for each object, 
	you can access the type classifications one at a time. 
	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The position in the stack of the object in 
	question. 
	@param iTypeIndex The type classification of the object. 
	<code>0</code> is the most specific type classification. The higher the 
	number, the more general the type classification.
	@return One type of an object at a particular location in the traversal 
	stack. 
*/
PIPROC ( PDFObjType, ConsStackIndexGetTypeAt, ( ConsStack hConsultant, ASUns32 iIndex, ASUns32 iTypeIndex ), hConsultant, iIndex, iTypeIndex )

/**
	Tests whether the object at the given index into the stack 
	is a <code>CosDict</code> object. 
	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The index in the stack where the object in question 
	is located.
	@return <code>true</code> if the object found at the index point is a dictionary, 
	<code>false</code> otherwise. 
*/
PIPROC ( ASBool, ConsStackIndexIsDict, ( ConsStack hConsultant, ASUns32 iIndex ), hConsultant, iIndex )

/**
	Tests whether the given index into the stack is a <code>CosArray</code>. 
	
	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The index in the stack where the object in question 
	is located.
	@return <code>true</code> if the object found at the index point is an array, 
	<code>false</code> otherwise. 
*/
PIPROC ( ASBool, ConsStackIndexIsArray, ( ConsStack hConsultant, ASUns32 iIndex ), hConsultant, iIndex )

/**
	Gets the key string atom of the object at the given index 
	into the stack (that is, the key that led from the given 
	object to the next object in the traversal). It is only 
	valid to call this function on an index if ConsStackIndexIsDict() 
	returns <code>true</code> for that index. 
	
	<p>An Acrobat exception is raised on error. </p>

	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The index in the stack where the object in question 
	is located.
	@return The key that led from the object at the given index in the 
	stack to the next object in the Consultant's traversal path. 
*/
PIPROC ( ASAtom, ConsStackIndexGetDictKey, ( ConsStack hConsultant, ASUns32 iIndex ), hConsultant, iIndex )

/**
	Gets the array index of the object at the given index into 
	the stack (that is, the index that led from the given object 
	to the next object in the traversal). It is only valid to 
	call this function on an index if ConsStackIndexIsArray() 
	returns <code>true</code> for that index. 
	@param hConsultant The Consultant's traversal stack. 
	@param iIndex The index in the stack where the object in question 
	is located.
	@return The array index that led from the object at the given index 
	in the stack to the next object in the Consultant's traversal 
	path. 
*/
PIPROC ( ASUns32, ConsStackIndexGetArrayIndex, ( ConsStack hConsultant, ASUns32 iIndex ), hConsultant, iIndex )

/**
	Gets the superclass, if any, of the given <code>PDFObjType</code>. 
	@param kType The type that might have a superclass.
	@return The superclass of the given type, or <code>DT_NULL</code> if no superclass 
	exists. 
*/
PIPROC ( PDFObjType, PDFObjTypeGetSuperclass, ( PDFObjType kType ), kType )

/**
	Returns the number of unique indirect objects that the Consultant 
	has processed so far. This count is reset on calls to ConsultantTraverseFrom() 
	and ConsultantSetStart(). Visited objects are not counted 
	more than once,  if an object is revisited, the count is 
	not incremented. 
	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
	@return The number of unique indirect objects the Consultant has 
	visited so far. 
*/
PIPROC ( ASUns32, ConsultantGetNumUniqueIndirectsVisited, ( Consultant hConsultant ),  hConsultant)

// Version 3
/**
	Instructs the Consultant to never walk through the supplied object.
	This function can (should) be called before traversing, so that you
	can ignore subtrees (such as the StructTree).
	This function does not un-suspend a Consultant, so you can call it
	repeatedly. It marks the object as Visited and NeverRevisit.
	This is a pre-traverse call, since marking an object as AC_NEVERREVISIT
	only occurs AFTER the object has been visited in post-order modes.

	@param hConsultant A valid Consultant object handle as returned 
	by ConsultantCreate().
*/
PIPROC ( void, ConsultantNeverVisitObj, ( Consultant hConsultant, CosObj hObj ),  hConsultant, hObj)





