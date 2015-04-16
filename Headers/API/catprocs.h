/*************************************************************************
 *
 * CatProcs.h
 *
 * Copyright (c) 2007 Adobe Systems Inc. All Rights Reserved.
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
 ************************************************************************/


/** Launch Catalog.
	If Catalog is already launched, its window is activated.
	@see CatalogGiveStatus 
	@see CatalogLoadIndex
*/
PIPROC ( void, CatalogActivate, (void), )

/** Opens an already existing index. If Catalog is not already 
	open, it is launched. 
	@param szIndex The full path of the index (including the .pdx 
	extension). If it is invalid, the method does nothing. 
	@return The status after the index definition dialog box is closed. If Catalog 
	is busy, it returns <code>CatalogBusy</code>. 
	@see CatalogActivate 
	@see CatalogPurgeIndex 
	@exception None
*/
PIPROC ( IndexStatus, CatalogLoadIndex, (char *szIndex), szIndex)


/**
	Builds an index. If Catalog is not already open, it is launched. 
	
	@param szIndex The destination path of the index (including 
	the .pdx extension). 
	@return The status after the build is done. If Catalog is busy, it returns 
	<code>CatalogBusy</code>. 
	@see CatalogActivate 
	@see CatalogLoadIndex 
	@see CatalogPurgeIndex 
*/
PIPROC ( IndexStatus, CatalogBuildIndex, (char *szIndex), szIndex)

/** Purges an already existing index.
	If Catalog is not already open, it is launched.
	@param szIndex IN The full path of the index (including the .pdx extension). If it is invalid, the method does nothing.
	@return The status after the purge is done. If Catalog is busy, it returns <code>CatalogBusy</code>.
	@see CatalogActivate 
	@see CatalogBuildIndex 
	@see CatalogPurgeIndex 
*/
PIPROC ( IndexStatus, CatalogPurgeIndex, (char *szIndex), szIndex)

/** Returns the current status of Catalog.
	@return The current status of Catalog.
*/
PIPROC ( CatalogStatus, CatalogGiveStatus, (void), )

