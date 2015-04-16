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
 Copyright (C) 1994-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 SrchPrcs.h

 - Catalog of functions exported by Acrobat Search.

*********************************************************************/

/**
	Superseded in Acrobat 6.0 by SearchExecuteQueryEx(), 
	which allows a broader range of search locations. 

	<p>Executes a specified query, using the set of indices currently 
	on the shelf. The search results are displayed in the Acrobat 
	Search plug-in's Results window. </p>

	@param cQuery The query. Its format is the same as what 
	a user would type into the Search query dialog, and depends 
	on the search language specified by <code>parserID</code>. 
	@param nParserID The search language used in the query. 
	It must be one of the following values (see SrchType.h):

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD>kParserSimple</TD><TD>Allows only simple phrase searches; it does not allow boolean searching.</TD></TR>
	<TR><TD>kParserCQL</TD><TD>Allows boolean searches using <code>AND</code>, <code>OR</code>, and <code>NOT</code>, as described in the Acrobat Search plug-in's online help file.</TD></TR>
	</TABLE>

	@param nSortCount The number of entries in the <code>sortSpec</code> 
	list. 
	@param cSortNames An array of strings, each specifying a 
	key whose value is used to sort the search results. The 
	first entry is the primary sort key, the second is the secondary 
	sort key, and so forth. Each string may be any field that 
	appears in the index, plus <code>Score</code> (which sorts results by 
	relevance ranking). Some common fields are <code>Title</code>, <code>ModificationDate</code>, 
	<code>CreationDate</code>, and <code>Keywords</code>. 
	@param bSortWays An array of boolean values indicating sort order, 
	corresponding to the array of sortSpecs with <code>true</code> meaning ascending and 
	<code>false</code> meaning descending.
	@param nWordOptions Search options. It must be an <code>OR</code> of the 
	following values (see SrchType.h): 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD>kWordOptionCase</TD><TD>The search is case-sensitive.</TD></TR>
	<TR><TD>kWordOptionStemming</TD><TD>Find not only the specified word, but other words that have the same stem (for example, <code>run</code> and <code>ran</code> have the same stem).</TD></TR>
	<TR><TD>kWordOptionProximity</TD><TD>Consider the proximity of results 
	when using the <code>AND</code> operator to look for more than one word 
	in a document. Without this option, <code>AND</code>ed terms can be anywhere 
	in a document. Searching for <code>"red"</code> and <code>"blue"</code>, for example, 
	finds a document where <code>"red"</code> is the first word on the first 
	page and <code>"blue"</code> is the last word on the last page. 
	With this option, however, <code>AND</code>ed terms must be within two 
	or three pages of each other to be found. Also, the closer 
	<code>AND</code>ed terms appear together, the higher the relevance ranking 
	of the document that contains them. </TD></TR>
	<TR><TD>kWordOptionRefine</TD><TD>Do not search the entire list of indices, but only the 
	documents that matched the previous search. This is used 
	to refine the results of the previous search. The manner 
	in which <code>wordOptions</code> is used depends on the value of <code>overrideWordOptions</code>.</TD></TR>
	</TABLE>

	@param bOverrideWordOptions Flag that indicates whether 
	<code>wordOptions</code> is <code>OR</code>ed with the search options set in the user 
	interface, or is used instead of them. If it is <code>0</code>, <code>wordOptions</code> is 
	<code>OR</code>ed with the user interface search options, and the resulting 
	value is used. If it is non-zero, <code>wordOptions</code> is used instead 
	of the user interface search options. 
	@param nMaxDocs The maximum number of documents to display 
	in the Results window. If more documents than this have 
	hits, only the first maxDocs are displayed. <code>maxDocs</code> must 
	be no greater than <code>9999</code>.
	@return <code>true</code> if successful, <code>false</code> otherwise. 
*/
PIPROC(ASInt32, SearchExecuteQuery, (char *cQuery, ASInt16 nParserID, ASUns16 nSortCount, char **cSortNames, ASBool *bSortWays, ASUns32 nWordOptions, ASBool bOverrideWordOptions, ASUns16 nMaxDocs), cQuery, nParserID, nSortCount, cSortNames, bSortWays, nWordOptions, bOverrideWordOptions, nMaxDocs)
/**
	Gets a list of the indices currently on the shelf. 
	@return The list of indices currently on the shelf. This value can 
	subsequently be used by other Search plug-in methods to 
	obtain information about a specific index, the number of 
	indices on the shelf, and so forth.
*/
PIPROC(SearchIndexListPtr, SearchGetIndexList, (void), )
/**
	Gets the number of indices currently on the shelf. 
	@param list The list of indices on the shelf, obtained 
	using SearchGetIndexList().
	@return The number of indices on the shelf. 
*/
PIPROC(ASUns32, SearchCountIndexList, (SearchIndexListPtr list), list)
/**
	Gets the <code>n</code>th index on the shelf. The index can be passed 
	to other Search plug-in methods to remove it from the 
	shelf, obtain its title, and so forth. 
	@param list The list of indices on the shelf, obtained 
	using SearchGetIndexList(). 
	@param n The index to get. The first index on the shelf 
	is index zero.
	@return The <code>n</code>th index on the shelf. This value may be used in subsequent 
	calls to remove the index, obtain its title, and so forth. 
	
*/
PIPROC(SearchIndexPtr, SearchGetNthIndex, (SearchIndexListPtr list, ASUns32 n), list, n)
/**
	Superseded by SearchGetIndexPathEx() in Acrobat 6.0. 

	<p>Gets the index that has the specified path. The index must 
	already be on the shelf. The index can be passed to other 
	Search plug-in methods to remove it from the shelf, 
	obtain its title, and so forth. </p>
	
	@param list The list of indices on the shelf, obtained 
	using SearchGetIndexList(). 
	@param fullPath A platform-dependent path to the index:
	<ul>
	<li>On Mac OS, it is of the form <code>MyDisk:TopFolder:BottomFolder:Strange.pdx</code>. </li>
	<li>On Windows, it is of the form <code>C:\\LVL1\\MYFILES\\INDEX</code>. The .PDX extension is automatically added to the 
	specified path name.</li>
	</ul>
	@return The specified index. This value may be used in subsequent 
	calls to remove the index, obtain its title, and so forth. 
*/
PIPROC(SearchIndexPtr, SearchGetIndexByPath, (SearchIndexListPtr list, char *fullPath), list, fullPath)
/**
	Superseded in Acrobat 6.0 by SearchAddIndexEx(). 

	<p>Adds a specified index to the shelf. </p>
	
	@param list The list of indices on the shelf, obtained 
	using SearchGetIndexList(). 
	@param fullPath A platform-dependent path to the index. 
	@param fullPath A platform-dependent path to the index:
	<ul>
	<li>On Mac OS, it is of the form <code>MyDisk:TopFolder:BottomFolder:Strange.pdx</code>. </li>
	<li>On Windows, it is of the form <code>C:\\LVL1\\MYFILES\\INDEX</code>. On UNIX and Windows, the .PDX extension is automatically added to the 
	specified path name.</li>
	</ul>
	@param flags Flags that indicate the state of the index. 
	It must be an <code>OR</code> of the following values (see SrchType.h): 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD>kIndexAvailableFlag</TD><TD>The index is available for searching. Indices that are not available appear grayed out in the Search plug-in's user interface.</TD></TR>
	<TR><TD>kIndexSelectedFlag</TD><TD>The index is used for searching. Indices that are selected appear with a filled in check box in the Search plug-in's user interface.</TD></TR>
	<TR><TD>kIndexPtrInvalidFlag</TD><TD>(Read only: cannot be set). The index cannot be located; it does not exist.</TD></TR>
	</TABLE>

	<p>In practice, kIndexAvailableFlag should always be set.</p>

	@return The index that was added. This value may be used in subsequent 
	calls to remove the index, obtain its title, and so forth. 
*/
PIPROC(SearchIndexPtr, SearchAddIndex, (SearchIndexListPtr list, char *fullPath, ASUns32 flags), list, fullPath, flags)
/**	Removes the specified index from the shelf.

    @param list IN The list of indices on the shelf, obtained using SearchGetIndexList().
	@param index IN The index to be removed. The index may be obtained using
					SearchGetIndexByPath(), SearchGetNthIndex(), or	SearchAddIndex().
*/
PIPROC(void, SearchRemoveIndex, (SearchIndexListPtr list, SearchIndexPtr index), list, index)
/**
	Gets the flags for a specified index. 
	@param index The index whose flags are to be obtained 
	(set). The index may be obtained using SearchGetIndexByPath(), 
	SearchGetNthIndex(), or SearchAddIndex(). 
	@return The flags returned are the actual values set, and may not 
	always be the same as the requested value. 
	It gets a list of the indices currently on the shelf. 

	<p>The list of indices currently on the shelf is returned. This value can 
	subsequently be used by other Search plug-in methods to 
	obtain information about a specific index, the number of 
	indices on the shelf, and so forth.</p>
*/
PIPROC(ASUns32, SearchGetIndexFlags, (SearchIndexPtr index), index)
/**
	Sets the flags for a specified index. 
	@param index The index whose flags are to be set. The 
	index may be obtained using SearchGetIndexByPath(), SearchGetNthIndex(), 
	or SearchAddIndex(). 
	@param flags Flags that indicate the status of the index. 
	<code>flags</code> must be an <code>OR</code> of the values (see SrchType.h): 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD>kIndexAvailableFlag</TD><TD>The index is available for searching. Indices that are not available appear grayed out in the Search plug-in's user interface.</TD></TR>
	<TR><TD>kIndexSelectedFlag</TD><TD>The index is used for searching. Indices that are selected appear with a filled in check box in the Search plug-in's user interface.</TD></TR>
	<TR><TD>kIndexPtrInvalidFlag</TD><TD>(Read only: cannot be set). The index cannot be located; it does not exist.</TD></TR>
	</TABLE>

	<p>In practice, kIndexAvailableFlag should always be set.</p>

	@return The flags returned are the actual values set, and may not 
	always be the same as the requested value. 
*/
PIPROC(ASUns32, SearchSetIndexFlags, (SearchIndexPtr index, ASUns32 flags), index, flags)
/**
	Superseded in Acrobat 6.0 by SearchGetIndexTitleEx(). 

	<p>Gets the title of a specified index. </p>
	
	@param index The index whose title is obtained. The index 
	may be obtained using SearchGetIndexByPath(), SearchGetNthIndex(), 
	or SearchAddIndex().
	@return The title of the specified index. 
*/
PIPROC(char *, SearchGetIndexTitle, (SearchIndexPtr index), index)
/**
	Superseded in Acrobat 6.0 by SearchGetIndexPathEx(). 

	Gets the platform-dependent path for a specified index. 
	
	@param index The index whose path is obtained. The index 
	may be obtained using SearchGetIndexByPath(), SearchGetNthIndex(), 
	or SearchAddIndex().
	@return A platform-dependent path to the index: 
	<ul>
	<li>On Windows, it is of the form <code>C:\\LVL1\\MYFILES\\INDEX</code>. The .PDX extension is automatically added to the 
	specified path name.</li>
	<li>On Mac OS, it is of the form <code>MyDisk:TopFolder:BottomFolder:Strange.pdx</code>. </li>
	</ul>
*/
PIPROC(char *, SearchGetIndexPath, (SearchIndexPtr index), index)
/**
	Supersedes SearchGetIndexPath() in Acrobat 6.0. 

	<p>Gets the index that has the specified path. The index must 
	already be on the shelf. The index can be passed to other 
	Search plug-in methods to remove it from the shelf, 
	obtain its title, and so forth. </p>

	@param list The list of indices on the shelf, obtained 
	using SearchGetIndexList(). 
	@param fileSys The file system on which the index is found. 
	
	@param indexPath The path to the index.
	@return The specified index. This value may be used in subsequent 
	calls to remove the index, obtain its title, and so forth. 
	
*/
PIPROC(SearchIndexPtr, SearchGetIndexByPathEx, (SearchIndexListPtr list, ASFileSys fileSys, ASPathName indexPath), list, fileSys, indexPath)
/**
	Supersedes SearchAddIndex() in Acrobat 6.0. 

	<p>Adds a specified index to the shelf, using the Acrobat 6.0 
	file system and path mechanism. </p>

	@param list The list of indices on the shelf, obtained 
	using SearchGetIndexList(). 
	@param fileSys The file system on which the index is found. 
	
	@param indexPath The path to the index. 
	@param flags Flags that indicate the state of the index. 
	It must be an <code>OR</code> of the following values (see SrchType.h): 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Value</TH><TH>Description</TH></TR>
	<TR><TD>kIndexAvailableFlag</TD><TD>The index is available for searching. Indices that are not available appear grayed out in the Search plug-in's user interface.</TD></TR>
	<TR><TD>kIndexSelectedFlag</TD><TD>The index is used for searching. Indices that are selected appear with a filled in check box in the Search plug-in's user interface.</TD></TR>
	<TR><TD>kIndexPtrInvalidFlag</TD><TD>(Read only: cannot be set). The index cannot be located; it does not exist.</TD></TR>
	</TABLE>

	<p>In practice, kIndexAvailableFlag should always be set.</p>

	@return The index that was added. This value may be used in subsequent 
	calls to remove the index, obtain its title, and so forth. 
	
	<p>It returns kAddIndexFailed if the specified index could not 
	be added to the shelf. It returns kIndexExists if the index 
	is already on the shelf.</p> 
*/
PIPROC(SearchIndexPtr, SearchAddIndexEx, (SearchIndexListPtr list, ASFileSys fileSys, ASPathName indexPath, ASUns32 flags), list, fileSys, indexPath, flags)
/**
	Supersedes SearchGetIndexTitle() in Acrobat 6.0. 

	<p>Gets the title of a specified index as an ASText object. </p>

	@param index The index whose title is obtained. The index 
	may be obtained using SearchGetIndexByPath(), SearchGetNthIndex(), 
	or SearchAddIndex().
	@return The title of the specified index as an ASText object. 
*/
PIPROC(ASText, SearchGetIndexTitleEx, (SearchIndexPtr index), index)
/**
	Supersedes SearchGetIndexPath() in Acrobat 6.0. 

	<p>Gets the path for a specified index as an ASPathName object. </p>

	@param index The index whose path is obtained. The index 
	may be obtained using SearchGetIndexByPath(), SearchGetNthIndex(), 
	or SearchAddIndex().
	@return The ASPathName object. 
*/
PIPROC(ASPathName, SearchGetIndexPathEx, (SearchIndexPtr index), index)
/**
	Gets the file system for a specified index as an ASFileSys 
	object. 
	@param index The index whose path is obtained. The index 
	may be obtained using SearchGetIndexByPath(), SearchGetNthIndex(), 
	or SearchAddIndex().
	@return The ASFileSys object. 	
*/
PIPROC(ASFileSys, SearchGetIndexFileSys, (SearchIndexPtr index), index)

/**
	Tests whether the search mechanism (Search5) for previous 
	Acrobat versions (prior to 6.0) is available for the current 
	system. When Search5 is available, you can search indexes 
	from Acrobat 5.0 and earlier. 
	@return <code>true</code> if legacy searches are available, <code>false</code> otherwise.
*/
PIPROC(ASBool, SearchIsLegacySearchAvailable, (void), )
/**
	Supersedes SearchExecuteQuery() in Acrobat 6.0. 

	<p>Executes a specified query, using the given set of search 
	parameters. The search results are displayed in the Acrobat 
	Search plug-in's Results window. </p>

	@param queryData A pointer to the structure containing 
	the search parameters. 
	@return <code>true</code> if successful, <code>false</code> otherwise. 
	@see maxDocs The maximum number of documents to display in the 
	Results window. If more documents than this have hits, only 
	the first maxDocs are displayed. <code>maxDocs</code> must be no greater 
	than <code>999</code>.
*/
PIPROC(ASBool, SearchExecuteQueryEx, (const SearchQueryDataRec *queryData), queryData)
