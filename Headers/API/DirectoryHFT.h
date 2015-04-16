/*************************************************************************
 * DirectoryHFT.h
 *
 * Copyright (c) 2000-2006 Adobe Systems Inc. All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the
 * property of Adobe Systems Incorporated and its suppliers, if any.
 * The intellectual and technical concepts contained herein are
 * proprietary to Adobe Systems Incorporated and its suppliers and may
 * be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law.  Dissemination of this
 * information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Adobe Systems Inc.
 *
 * Description: Interface to Acrobat Directory Services
 *
 * 06-20-2002 sheretov -- Created
 ************************************************************************/

#ifndef DIR_SERVICES_HFT_H
#define DIR_SERVICES_HFT_H

#include "CoreExpT.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************
 * Error handling
 ***********************************************************************************/

/** @name Error handling */
 /*@{*/
/** */
typedef ASInt32 SecRetCode;
/** */
#define kSecTrue       1
/** */
#define kSecFalse      0
/** */
#define kSecOk         1
/** */
#define kSecError	  -1
/*@}*/

/** If a function returns <code>-1</code> or less, you can call a <code>GetLastError</code> appropriate to 
   the context and retrieve information about the last error.  That call may 
   return <code>NULL</code> which basically means "Unknown Error". Note that in the presence 
   of threads, the error information may become inaccurate. */
typedef struct _t_SecErrorInfo
{
	/** The size of this structure. */
	ASSize_t size;       
	/** The description of the error. */
	ASText   text;       
	/** Adobe use only. It must be set to <code>NULL</code> by external developers. */
	void*    reserved;   
} 
SecErrorInfoRec, *SecErrorInfo;

/** */
typedef struct _t_DirConnection* DirConnection;
/************************************************************************************
 * Rules for out-parameters
 ***********************************************************************************/

/* Consider the following function prototypes:

   void foo(ASBool* outResult);
   void bar(void** outResult);  
   void baz(ASCab outResult);

   - if(outResult==0) when the call is made, the caller is not interested in this 
     out parameter. The callee should not fail just because outResult is 0.

   - if(outResult!=0 && *outResult==0) when the call is made, the callee is 
     expected to allocate the result and the caller is responsible for its 
     deallocation.  One exception to this rule is when the callee wishes to 
     return an "empty value" (such as an empty ASText or ASCab), it will leave 
     *outResult==0.

   - if(outResult!=0 && *outResult!=0) when the call is made, the callee will 
     deallocate the *outResult if needed and replace it with a new value.

   - Raw memory and primitive structures (the ones that don't have any members that
     require deallocation) shall be deallocated with ASFree/miFree.  ASCabs ASTexts 
     and other known types shall be deallocated with their special routines 
     (ASTextDestroy(), ASCabDestroy(), etc.)

   - If a call fails, *outResult remains unchanged.
*/

/************************************************************************************
 * Directory Information format
 ***********************************************************************************/

/** A directory information structure contains configuration settings used to 
   establish a connection to a directory. Common top-level properties are 
   defined below. Note that the prefix <code>DirStdEntry_</code> is reserved for standard 
   entries and should not be used for entries specific to a particular directory.
   Optionally, this could contain other configuration information specific to 
   the directory. 
*/
typedef ASCab DirectoryInfo;

/* The name of this directory for display purposes.
   An example of this would be <code>"Adobe Employees"</code>.

   <p>TEXT, REQUIRED.</p> */
#define PROP_DirectoryInfo_Name "dirStdEntryName"

/* The ID. It is a unique atom that identifies the directory.
   An example of this would be <code>Adobe.PPKMS.LDAP.dir0</code>.
  <p> ATOM, REQUIRED.</p> */
#define PROP_DirectoryInfo_ID "dirStdEntryID"

/* The language independent name of the directory handler to be used 
   when connecting to this directory. This is required when there
   are multiple direcrtory handlers within a DSP. An example of this
   would be <code>Adobe.PPKMS.ADSI</code>.

   <p>ATOM, OPTIONAL.</p> */
#define PROP_DirectoryInfo_DirHandlerID "dirStdEntryPrefDirHandlerID"

/* The language independent name of the type of directory this represents. 
   This is required when you want to import or export entries. An example
   of this would be <code>LDAP, ADSI</code>.

   <p>ATOM, OPTIONAL.</p> */
#define PROP_DirectoryInfo_DirType "dirStdEntryDirType"

/* An integer that represent the version of the directory.

   <p>Integer, OPTIONAL.</p> */
#define PROP_DirectoryInfo_Version "dirStdEntryVersion"

/************************************************************************************
 * Directory Attributes
 ***********************************************************************************/

/* These are attribute names used in the "standard" connection functions 
   (DirSetStandardOutputOptions(), DirStandardSearch(), etc.)  These attribute names
   are used both as keys/property names (in representation of the search results) and
   as values (in representation of output settings). The attributes are stored as 
   ASText so as to enable easy conversion from JavaScript.
*/
#define ATTR_DirFirstName    "firstName"
#define ATTR_DirLastName     "lastName"
#define ATTR_DirFullName     "fullName"
#define ATTR_DirEmail        "email"
#define ATTR_DirCertificates "certificates"
// ATTR_AcceptCertWithoutCheck is set when the calling function will determine if the cert is applicable
#define ATTR_AcceptCertWithoutCheck "accept"
#define ATTR_DirPrefEncryptionCert "defaultEncryptCert"

/************************************************************************************
 * Connection Interface.
 ***********************************************************************************/

/** Group names are represented as text in an ASCab.  For example:
   <p><code>{ ("0", "friends"), ("1", "family"), ... } </code></p>
*/
typedef ASCab DirGroupList;
/**  Retrieves the list of groups that this connection supports.

	@return <code>kSecOk</code> is successful, <code>kSecError</code> otherwise.
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_getGroups)
	( DirConnection inConnection, DirGroupList outGroupList );

/*-----------------------------------------------------------------------------------
   The output options of a connection determine which directory attributes will be
   returned when a search is performed.  There are two calls for setting the output
   options, and they differ in the way the attributes are interpreted.  The default
   behavior for a new connection if output options have not been explicitly set, is
   as if DirSetStandardOutputOptions call with all "standard" attributes has been 
   made.
*/

/** A directory attribute collection is used to set output options of a directory 
   connection.  
   
   <p>The collection is represented in an ASCab as:</p>
      <p><code>{ ("0", "nameOfAttribute1"), ("1", "nameOfAttribute2"), ... } </code></p>
*/
typedef ASCab DirAttributes;

/** Special case:  The <code>ATTR_Certificates</code> attribute is intended to encompass all 
    certificate attributes a directory might have.  If <code>ATTR_Certificates</code> is requested,
    it may have to be translated into several attributes depending on the directory.
    @param inConnection The connection for which the output options are set.
    @param inRequestedAttrs Contains only <i>standard</i> attribute names defined as <code>ATTR_</code> 
    constants above.  These names will most likely need to be translated to ones 
    understood by specific directory types.  For example, in the case of a generic LDAP 
    directory, <code>ATTR_LastName</code> may be interpreted as <code>"sn"</code>.
	@param outUnsupportedAttrs Used to pass back the the names of attributes (from 
    <code>inRequestedAttrs</code>) that are not supported by the connection.
	@return <code>kOK</code> or <code>kSecError</code>
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_setStandardOutputOptions) 
	( DirConnection inConnection, 
	  DirAttributes inRequestedAttrs, DirAttributes outUnsupportedAttrs);

/** TBD
	@param inConnection The connection for which the output options are set.
	@param inRequestedAttrs Contains attribute names that are not translated.  Any 
    attribute names can be used as long as they are supported by the target directory.
	@param outUnsupportedAttrs Used to pass back the the names of attributes (from 
    <code>inRequestedAttrs</code>) that are not supported by the connection.
	@return <code>kSecOk</code> or <code>kSecError</code>
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_setCustomOutputOptions) 
	( DirConnection inConnection, 
	  DirAttributes inRequestedAttrs, DirAttributes outUnsupportedAttrs);

/*-----------------------------------------------------------------------------------
   Perform a search using a connection.  There are three different search functions,
   and although all three are optional, at least one should be implemented for a 
   connection to be usable.
*/

/** Directory search criteria are represented as a set of key/value pairs where the 
   keys are attribute names and the values are search strings applied to those 
   attributes.  A logical "AND" is implied when multiple search criteria are present.
   Unrecognized search criteria are ignored.
   
   @example <code>{ ("firstName", "John"), ("lastName", "S*") }</code> searches for people with 
   the first name "John" whose last name starts with letter 'S'.

   @note Special Case: For a <i>standard</i> search, the value of the <code>ATTR_Certificates</code> search 
   criterion shall be a list of certificates.  In order for a directory entry to 
   match the criterion, it must have all those certificates.
*/
typedef ASCab DirSearchCriteria;

/** Search and enumeration results are represented as a two-dimensional ASCab where 
   each "row" is itself an ASCab that contains attributes defined by SetOutputOptions 
   calls.

   @example 
   <p><code>{ ("0", { ("fullName", "John Doe"), ("email", "johndoe@yahoo.com") } ),</code></p>
   <p><code>("1", { ("fullName", "Jane Doe"), ("email", "janedoe@hotmail.com") } ) }</code></p>
   

   @note Special Case: If standard output options are used and <code>ATTR_Certificates</code> is 
   included, the <code>ATTR_Certificates</code> value in the <i>row</i> ASCab objects will be another ASCab,
   which stores all certificates associated with that directory entry.  
   
   @example <code>
   { ("0", { ("fullName", John Doe"), ("certificates", { ("0", encryptionCertBinaryValue),  ("1", signingCertBinaryValue) } ) } ) }
   </code>
*/
typedef ASCab DirResults;

/** TBD
	@param inConnection The connection that is used to perform the search.
	@param inSearchCriteria Search criteria to be used. The only <i>standard</i> attribute
    names defined as <code>ATTR_</code> constants above are present. These names most likely 
    will need to be translated to ones understood by specific directory types.  
    For example, in the case of a generic LDAP directory, <code>ATTR_LastName</code> may be 
    interpreted as <code>"sn"</code>.
	@param inGroup Specifies the group, which should be searched. <code>NULL</code> means that all 
    groups should be searched.
	@param outResults Points to the results of the search.
	@return <code>kSecOk</code> or <code>kSecError</code>
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_standardSearch)
	( DirConnection inConnection, 
	  DirSearchCriteria inSearchCriteria, 
	  ASText inGroup, 
	  DirResults outResults );

/* TBD
	@param inConnection The connection that is used to perform the search.
	@param inSearchCriteria Search criteria to be used.  The attribute names are not 
    translated. Any attribute names can be used as long as they are supported 
    by the target directory.
	@param inGroup Specifies the group, which should be searched. <code>NULL</code> means that all 
    groups should be searched.
	@param outResults Points to the results of the search.
	@return <code>kSecOk</code> or <code>kSecError</code>
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_customSearch)
	( DirConnection inConnection, 
	  DirSearchCriteria inSearchCriteria, 
	  ASText inGroup, 
	  DirResults outResults );

/** Pops up a custom user interface that allows the user to set search criteria and execute the 
	search.
	@param inConnection The connection that is used to perform the search.
	@param inGroup Specifies the group, which should be searched. <code>NULL</code> means that all 
	groups should be searched.
	@param outResults Points to the results of the search.
	@return <code>kSecOk</code> or <code>kSecError</code>
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_customUISearch)
	( DirConnection inConnection, 
	  ASText inGroup, 
	  DirResults outResults );

/** Retrieve all entries in the specified groups. If that would take too long, return
	<code>kDirDirectoryTooLargeToList</code>.  This may be used in the user interface to immediately display 
	the contents of a small directory or group, so responsiveness is important.
	@param inConnection The connection that is used to list directory entries.
	@param inGroup Specifies the group, which should be listed. <code>NULL</code> means that all 
	groups should be listed.
	@param outResults Points to the results of the enumeration.
	@return <code>kSecOk</code>, <code>kDirDirectoryTooLargeToList</code>, or <code>kSecError</code>
*/

#define kDirDirectoryTooLargeToList 2

/** TBD */
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_list)
	( DirConnection inConnection, 
	  ASText inGroup, 
	  DirResults outResults );

/** Closes the specified directory connection.
*/
typedef ACCBPROTO1 void (ACCBPROTO2 *DirConnection_close) 
	( DirConnection inConnection );

/** Retrieves information about the directory associated with the connection.
	@param inConnection A directory connection object.
	@param outDirInfo A Cab file containing the directory information.
	@return <code>kSecOk</code> or <code>kSecError</code>
*/
typedef ACCBPROTO1 SecRetCode (ACCBPROTO2 *DirConnection_getDirInfo) 
	( DirConnection inConnection, DirectoryInfo outDirInfo );

/** Retrieves information about the last error that occurred in the specified 
	connection.
*/
typedef ACCBPROTO1 SecErrorInfo (ACCBPROTO2 *DirConnection_getLastError) 
	( DirConnection inConnection );

/** A directory connection object structure. 
*/
typedef struct _t_DirConnection 
{
	/** The size of this data structure. */
	ASSize_t size; 
	/** The data to be passed in. */
	void* clientData;

	/** */
	DirConnection_close                      close;
	/** */
	DirConnection_getLastError               getLastError;
	/** */
	DirConnection_getDirInfo                 getDirInfo;
	/** */
	DirConnection_getGroups                  getGroups;

	/** */
	DirConnection_setStandardOutputOptions   setStandardOutputOptions;
	/** */
	DirConnection_setCustomOutputOptions     setCustomOutputOptions;

	/* Although all four of these methods are optional, at least one must be present
	   for a connection to be usable: */
	/** */
	DirConnection_standardSearch             standardSearch;
	/** */
	DirConnection_customSearch               customSearch;
	/** */
	DirConnection_customUISearch             customUISearch;
	/** */
	DirConnection_list                       list;

}
DirConnectionRec, *DirConnectionHandler;

#ifdef __cplusplus
}
#endif

#endif /* DIR_SERVICES_HFT_H */
