/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1996-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 srchtype.h

*********************************************************************/

#ifndef _H_SrchType
#define _H_SrchType

/** The search is case-sensitive. 
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionCase			0x00000001L
/** Find not only the specified word, but other words that have the same stem (for
	example, <code>run</code> and <code>ran</code> have the same stem).
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionStemming		0x00000002L
/** Consider the proximity of
	results when using the <code>AND</code> operator to look for more
	than one word in a document. Without this option, <code>AND</code>ed
	terms can be anywhere in a document. Searching for
	<code>"red"</code> and <code>"blue"</code>, for example, finds a document where
	<code>"red"</code> is the first word on the first page and <code>"blue"</code> is
	the last word on the last page. With this option, however,
	<code>AND</code>ed terms must be within two or three pages of each
	other to be found. Also, the closer <code>AND</code>ed terms appear
	together, the higher the relevance ranking of the
	document that contains them. 
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionProximity	0x00000010L
/** Do not search the entire list of
	indices, but only the documents that matched the
	previous search. This is used to refine the results of the
	previous search.
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionRefine		0x00000020L
/**	
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionWholeWord	0x00000040L
/**	
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionIgnoreFH		0x00000080L

/**	
	@ingroup SearchWordOptionsFlags
*/
#define kWordOptionIgnoreDiacritics		0x00000100L

/** 
	The client must supply all the search word options in the scope parameter
	by doing an <code>OR</code> (<code>|</code>) operation on all options where the search needs to be executed.
	For example, if the client needs to search on attachments, and within attachments
	the search needs to be done on document text and XMP data, then it can be 
	specified as follows:

	<p><code>scope = kSearchDocumentText | kSearchDocumentXMP | kSearchPDFAttachments;</code></p>

	<p>In most cases, however, the client might want to search on all the places 
	possible, so it would suffice to write:</p>

	<p><code>scope = kSearchEveryWhere;</code></p>

	@ingroup SearchWordOptions
*/
typedef ASUns32 SearchWordOptions;
/** 
	@ingroup SearchWordOptions
*/
#define kSearchDocumentText		0x00000001L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchBookmarks		0x00000002L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchMarkup			0x00000004L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchDocumentXMP		0x00000008L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchSignatures		0x00000010L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchDocInfo			0x00000020L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchJPEGExif			0x00000040L
/**	
	By including the kSearchUserProperties option, you will ensure
	that the object level data is the same as that
	seen by the menu item Object Data Tool
	in Acrobat. This is <i>not</i> the metadata associated with
	individual COS level objects in the PDF document.

	@ingroup SearchWordOptions
*/
#define kSearchUserProperties	0x00000080L
/**     
	@ingroup SearchWordOptions
*/
#define kSearchPDFAttachments		0x00000100L
/**		
	@ingroup SearchWordOptions
*/
#define kSearchEveryWhere		ASMAXUns32



/** */
typedef ASUns32 SearchScope;

/** */
typedef enum
{
	/** */
	kSearchActiveDoc,
	/** */
	kSearchFolder,
	/** */
	kSearchIndex,
	/** */
	kSearchActiveIndexes
} SearchType;

/**	Search Match Options	*/
typedef enum 
{
/**		*/	
	kMatchPhrase,
/**		*/	
	kMatchAllWords,
/**		*/	
	kMatchAnyWords,
/**		*/	
	kBooleanQuery
} SearchMatchOption;

/** */
typedef struct _t_SearchQueryDataRec {
	/** The size of the data structure. It must be set to <code>sizeof(SearchQueryDataRec)</code>. */
	ASSize_t			size;		

	/** The text to be searched.  */
	ASText				query;		

	/** The location to search in. */
	SearchType			type;
	
	/** How the <i>query</i> text should be matched in the document. */
	SearchMatchOption	match;		

	/** The search options. */
	SearchWordOptions	options;	

	/** The content in the PDFs that should be searched. 
	    It should be an <code>OR</code> of values specified in SearchScope. */
	SearchScope			scope;		

	/** The path of the folder or index. 
	    It is required only when <code>type</code> is kSearchFolder or kSearchIndex. */
	ASPathName			path;		

	/** The ASFileSys of the folder or index. 
	    It is required only when <code>type</code> is kSearchFolder or kSearchIndex. */
	ASFileSys			fs;			

	/** The maximum number of documents to display in the Results window. If
		more documents than this have hits, only the first <code>maxDocs</code> are
		displayed. <code>maxDocs</code> must be no greater than <code>999</code>.
	*/
	ASUns16				maxDocs;	

	/** The page number to start the search; <code>0</code> is the first page. */
	ASUns32				startPage;

	/** The range of words for proximity searches. */
	ASUns32				proximityRange;
} SearchQueryDataRec;


/* opaque types for primitive types */
/** */
typedef void *SearchIndexListPtr;
/** */
typedef void *SearchIndexPtr;


/**	The index is available for searching.

	<p>Indices that are not available appear grayed out in the Search
	plug-in's user interface.</p>

	@ingroup SearchIndexFlags
*/
#define kIndexAvailableFlag		(1L << 0)
/**	The index is used for searching.

	<p>Indices that are selected appear with a filled in check box in the
	Search plug-in's user interface.</p>	

	@ingroup SearchIndexFlags
*/
#define kIndexSelectedFlag		(1L << 1)
/**	(Read only - cannot be set) 
	<p>The	index cannot be located; it does not exist.
	In practice, kIndexAvailableFlag should always be set.	</p>

	@ingroup SearchIndexFlags
*/
#define kIndexPtrInvalidFlag	(1L << 31)

#define kAddIndexFailed		((SearchIndexPtr)0)
#define kIndexExists		((SearchIndexPtr)-1)

/* deprecated */

/* parser types */
#define kParserSimple        0
#define kParserCQL           1


#endif

