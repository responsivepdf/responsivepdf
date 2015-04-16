/*
** AVExpTObsolete2.h
**
** This file contains types used in former versions of Acrobat.  By defining ACRO_SDK_LEVEL
** to the latest version, you will use the latest types and routines.  These types are no longer
** used in any Acrobat source, but are provided here to allow existing plug-in code to compile
** without changes.  Backward compatibility can be maintained by adding AVCompat.cpp to your plugin
** which will handle passing current structures and callbacks to older versions of Acrobat.
**
** This file is furnished to you by Adobe Systems Incorporated under the terms of the 
** Acrobat (r) Plug-insSoftware Development Kit License Agreement.
** Copyright (C) 1994-2001,2003,2006-2007 Adobe Systems Inc.  All Rights Reserved.
*/

/*
** Note that all of the types are prefixed by "old"  The recommended type to use does not begin with "old"
** You should not use any of these types directly.  The AVExpT.h file will existing types to one or more old types
** if you do not have ACRO_SDK_LEVEL set to the latest version
*/


typedef struct {								/* Used for AVAppOpenDialog, AVAppSaveDialog, and AVAppChooseFolderDialog */
	ASSize_t    			size;   			/* Size of this record */
	AVOpenSaveDialogFlags	flags;
	AVWindow				parentWindow;		/* Parent window of dialog -- ignored on Mac */
	ASText					windowTitle;		/* Title of dialog - use for prompt. May be NULL for default title */
	ASText					actionButtonTitle;	/* Title of 'action' button ('Open', 'Save', or 'Choose'). May be NULL for default title */
	ASText					cancelButtonTitle;	/* Title of cancel button. May be NULL for default title */
	ASFileSys				initialFileSys;		/* May be NULL if flags does not contain kAVOpenSaveAllowForeignFileSystems */
	ASPathName				initialPathName;	/* Used to specify initial location/selection. May be NULL if default location/selection is acceptable */
	const char				*initialFileName;	/* Ignored (may be NULL) for Open and ChooseFolder. For Save, filename portion is used for edit field */
	AVFileFilterRec			**fileFilters;		/* Array of AVFileFilterRec*s. Ignored (may be NULL) for ChooseFolder. May be NULL for Open ONLY if kAVOpenSaveAllowAllFlag is set */
	AVArraySize				numFileFilters;		/* Number of AVFileFilterRec*s in fileFilters */
	AVOpenSaveDialogSettingsComputeEnabledProc	settingsComputeEnabledProc;
	AVOpenSaveDialogSettingsExecuteProc			settingsExecuteProc;
	void										*settingsProcData;
} oldAVOpenSaveDialogParamsRec, *oldAVOpenSaveDialogParams;

typedef struct _t_oldAVDocSelectionServer {

	ASSize_t 							size;	/* set this to sizeof(AVDocSelectionServerRec) */

	AVDocSelectionGetTypeProc				GetType;
	AVDocSelectionGettingSelectionProc		GettingSelection;
	AVDocSelectionAddedToSelectionProc		AddedToSelection;
	AVDocSelectionLosingSelectionProc		LosingSelection;
	AVDocSelectionRemovedFromSelectionProc	RemovedFromSelection;
	AVDocSelectionCanSelectAllProc			CanSelectAll;
	AVDocSelectionSelectAllProc				SelectAll;
	AVDocSelectionCanPropertiesProc			CanProperties;
	AVDocSelectionPropertiesProc			Properties;
	AVDocSelectionCanDeleteProc				CanDelete;
	AVDocSelectionDeleteProc				Delete;
	AVDocSelectionCanCopyProc				CanCopy;
	AVDocSelectionCopyProc					Copy;
	AVDocSelectionEnumSelectionProc			EnumSelection;
	AVDocSelectionShowSelectionProc			ShowSelection;
	AVDocSelectionCanCutProc				CanCut;
	AVDocSelectionCutProc					Cut;
	AVDocSelectionCanPasteProc				CanPaste;
	AVDocSelectionPasteProc					Paste;
	AVDocSelectionKeyDownProc				KeyDown;
	AVDocSelectionHighlightSelectionProc	HighlightSelection;
	AVDocSelectionGetSelectionTypeProc		GetSelectionType;
	AVDocSelectionEnumPageRangesProc		EnumPageRanges;
	oldAVDocSelectionGetAVRectProc			GetAVRect;
	oldAVDocSelectionShowMenuProc			ShowMenu;
} oldAVDocSelectionServerRec, *oldAVDocSelectionServer;

typedef struct _t_oldAVDocViewDef
{
	ASSize_t	size;

	ASBool		bringToFront;

	ASBool			usePageViewInfo;	/* pageview info */
	PDLayoutMode	pageViewLayoutMode;
	PDPageNumber	pageViewPageNum;
	AVZoomType 		pageViewZoomType;
	ASFixed 		pageViewZoom;
	ASInt16			pageViewX;
	ASInt16			pageViewY;

	ASBool			pageViewStartThread;
	AVPageIndex		pageViewThreadIndex;
	PDBead 			pageViewBead;

	ASBool		useOverViewInfo;	/* overview info */
	PDPageMode	overViewMode;			
	AVPixelOffset	overViewPos;   /*pixel position of overview */
	ASInt32		overViewX;
	ASInt32		overViewY;

	ASBool		useWindowInfo;		/* window info */
	oldAVRect		windowFrame;				

	ASBool			unused1;		/* obsolete */
	const char*		unused2;		/* obsolete */

} oldAVDocViewDefRec, *oldAVDocViewDef;

typedef struct _t_oldAVDocOpenParams
{
	ASSize_t		size;
	
	ASBool			useFrame;	/* Should the "frame" field be used? */
	oldAVRect		frame;		/* Frame rectangle of newly opened
								** AVDoc, in global screen coordinates
								*/
	
	ASBool			useVisible;	/* Should the "visible" field be used? */
	ASBool			visible;	/* Should the AVDoc be opened visibly, or
								** should it be hidden?
								*/
								
	ASBool			useServerType;			/* Should the "serverType" and "serverData" fields be used? */
	const char*		serverType;				/* Name of AVDoc server for this AVDoc */
	void*			serverCreationData;		/* serverData to be associated with above server */

	ASBool			useSourceDoc;			/* Should the "sourceDoc" field be used? */
	AVDoc			sourceDoc;				/* AVDoc whose window will be taken over by new document. */
											/* "sourceDoc" will be closed at the same time. */

	ASBool			useReadOnly;			/* Should the "readOnly" field be used? */
	ASBool			readOnly;				/* Open the document in read only mode */

	ASBool			useViewType;			/* Should the "viewType" field be used */
	const char* 	viewType;				/* type of view to open on document */

	ASBool			useViewDef;				/* Should the "viewDef" field be used? */
	oldAVDocViewDef	viewDef;				/* initial view to open two */
	
	ASBool			usePermReqProc;			/* Should the "permReqProc" field be used? */
	AVDocPermReqProc permReqProc;			/* Return PDPermReqDenied to deny a permission, or PDPermReqGranted to grant it. */ 
}
oldAVDocOpenParamsRec, *oldAVDocOpenParams;

typedef struct _t_oldAVToolBarPosition {

	/** The size of this structure. Set it to <code>sizeof(AVToolBarPositionRec)</code>. */
	ASSize_t	size;

	/** Specifies that the toolbar is to be <i>in-doc</i> (not shared). If <code>inDoc</code> is <code>true</code>, <code>dockPosition</code> cannot be floating. */
	ASBool	inDoc;

	/** The edge of the document window or monitor to which to attach this toolbar. */
	AVToolBarDockPosition	dockPosition;

	/** If the toolbar is to be floating, you can group it with another toolbar by specifying a name 
		for the floating window. You can set this to a constant string. 
	*/
	const char *floatingWindowName;

	/** The stack on which to insert the toolbar. Make this <code>-1</code> to open a new stack on the left or top, or ASMAXInt32 
		to open a new stack on the right or bottom. 
	*/
	ASInt32 stackNum;

	/** The number of pixels from the top or left edge of the stack from which to position the toolbar. If 
		ASMAXInt32, the toolbar will be positioned snugly behind other toolbars on the stack. If <code>-1</code>, it will 
		be positioned at the front. 
	*/
	ASInt32 offset;

	/** If multiple positions specify an offset of <code>-1</code> or ASMAXInt32, this field is used to further order them. 
		It controls the order in which the bars will be placed, not the visual order on-screen. If, for example, 
		two bars have an offset of <code>-1</code>, the one associated with the value in the lower order field will be 
		positioned first at the front of the bar. Then the one associated by the value in the higher order field 
		will also be positioned at the front of the bar, but will push the first one to the right. 
	*/
	ASInt32 order;

	/** If the toolbar is not <code>inDoc</code> and <code>dockPosition</code> is floating, you may end up creating a new window. Here is its frame. */
	oldAVRect windowFrame;

	/** If a new window is called for, here is its layout. */
	AVToolBarLayout layout;

	/** Set this to <code>true</code> if the toolbar should be hidden by default. */
	ASBool hidden;

	/** Set this to <code>true</code> if the floating window in which the toolbar is located should be hidden by default. */
	ASBool windowHidden;

} oldAVToolBarPositionRec, *oldAVToolBarPosition;

typedef struct _t_oldAVAnnotHandler 
{
  	ASSize_t 	size;
	AVFlagBits32 flags;

	oldAVAnnotHandlerDoClickProc DoClick;
	oldAVAnnotHandlerAdjustCursorProc AdjustCursor;
	oldAVAnnotHandlerPtInAnnotViewBBoxProc PtInAnnotViewBBox;
	oldAVAnnotHandlerGetAnnotViewBBoxProc GetAnnotViewBBox; 
	AVAnnotHandlerNotifyAnnotRemovedFromSelectionProc NotifyAnnotRemovedFromSelection;
	AVAnnotHandlerNotifyAnnotAddedToSelectionProc NotifyAnnotAddedToSelection;
	AVAnnotHandlerDrawProc Draw;
	AVAnnotHandlerNewProc New;
	AVAnnotHandlerGetTypeProc GetType;
	AVAnnotHandlerNotifyDestroyProc NotifyDestroy;
	AVAnnotHandlerDoPropertiesProc DoProperties;
	AVAnnotHandlerDoKeyDownProc DoKeyDown;
	AVAnnotHandlerGetLayerProc GetLayer;
	AVAnnotHandlerCursorEnterProc CursorEnter;
	AVAnnotHandlerCursorExitProc CursorExit;
	AVAnnotHandlerCopyProc Copy;
	oldAVAnnotHandlerDoClickProc DoRightClick;
	AVAnnotHandlerGetInfoProc GetInfo;
	AVAnnotHandlerDeleteInfoProc DeleteInfo;
	AVAnnotHandlerCanPerformOpProc CanPerformOp;
	AVAnnotHandlerPerformOpProc PerformOp;
	AVAnnotHandlerDoKeyDownExProc DoKeyDownEx;
	oldAVAnnotHandlerDrawExProc DrawEx;
	AVAnnotHandlerGetFlagsProc GetFlags;
} oldAVAnnotHandlerRec;


typedef struct _t_oldAVTool 
{
  ASSize_t size;
  
  ActivateProcType Activate;
  DeactivateProcType Deactivate;
  oldDoClickProcType DoClick;
  oldAdjustCursorProcType AdjustCursor;
  DoKeyDownProcType DoKeyDown;
  GetTypeProcType GetType;
  IsPersistentProcType IsPersistent;
  AVCursorID cursorID;
  AVComputeEnabledProc ComputeEnabled;
  void *computeEnabledData;
  oldDoClickProcType DoRightClick;
  DoLeaveProcType DoLeave;
  GetSelectionServerProcType GetSelectionServer;

} oldAVToolRec;

typedef struct _t_oldAVWindowHandler
{
	ASSize_t size;
	oldAVWindowMouseDownProc MouseDown;
	AVWindowWillCloseProc WillClose;
	AVWindowDidCloseProc DidClose;
	AVWindowDidActivateProc DidActivate;
	AVWindowDidBecomeKeyProc DidBecomeKey;
	AVWindowKeyDownProc KeyDown;
	AVWindowWillResignKeyProc WillResignKey;
	AVWindowWillDeactivateProc WillDeactivate;
	oldAVWindowDrawProc Draw;
	oldAVWindowWillBeResizedProc WillBeResized;
	AVWindowPerformEditOpProc PerformEditOp;
	AVWindowCanPerformEditOpProc CanPerformEditOp;
	oldAVWindowAdjustCursorProc AdjustCursor;
	oldAVWindowDidResizeProc DidResize;
	AVWindowDestroyPlatformThingProc DestroyPlatformThing;
} oldAVWindowHandlerRec;

#if !defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)
//changed use of AVRect32 to AVRect
typedef struct _t_AVDocPrintParams {
	ASSize_t size;							/* set this to be the size of this struct */

	/* One and only one of the following booleans must be set:
		interactive			- puts up a print dialog and print status window while printing
		embedded			- renders one page scaled to the size specified by embeddedRect
		emitToPrinter		- non-interactive output to a printer without a print dialog or status window
		emitToFile			- non-interactive output to a file. Used to emit color separations or EPS.
	*/

	ASBool interactive;						/* if true, display dialogs; else, perform without dialogs */
	ASBool cancelDialog;					/* if interactive false, forces cancel dialog to appear */

	/* firstPage, lastPage, psLevel, binaryOk and shrinkToFit are used if 
	** emitToPrinter or emitToFile are true.
	*/
	ASInt32 firstPage;						/* first page to be printed; zero-based; if -1, then all pages are printed */
	ASInt32 lastPage;						/* last page to be printed; if firstPage is -1, this page is ignored */
	ASInt32 psLevel;						/* if printing to PostScript, 1 means emit as level 1, 2 means level 2 */
	ASBool binaryOK;						/* set to true if a binary channel to the printer is supported */
	ASBool shrinkToFit;						/* if true, the page is scaled to fit the printer page size */

	/* fileSysName and filePathName are used if emitToPrinter or emitToFile is true.
	**
	** If emitToPrinter is true, and filePathName is non-NULL, then the system printer driver
	** is used to emit the output stream to the file. This is implemented for Windows only.
	*/
	ASAtom fileSysName;						/* see filePathName */
	ASPathName filePathName;				/* if non-NULL, is a platform path for the specified fileSysName, 
												or, if fileSysName is ASAtomNull, it is one of the following:
													on Windows: a C-string path name;
													on Macintosh: a FSSpecPtr.
													on Unix: a C-string path name.
											*/ 

	/* printerSpec is optionally used if interactive, embedded or emitToPrinter is true.
	** If NULL, then a default system printer is used.
	*/
	ASPlatformPrinterSpec printerSpec;		/* may be NULL. If non-NULL, is a platform specific. See type above */

	ASBool embedded;						/* If true, then this an embedded view of a page that is to be printed.
											** firstPage and lastPage must be the same.
											** embeddedRect specifies the location in the page where
											** the view of the page is to appear.
											** embeddedRect is in device coordinates for the current printer.
											** The printer must be specified as an HDC or CGrafPtr.
											*/
	AVRect32 embeddedRect;					/* see "embedded" above */

	ASBool emitToPrinter;					/* If true, use the system printer driver for output.
											** If filePathName is specified, uses the driver to 
											** create the file.
											*/

	/* Parameters for emission of PS Level 1 Color Separations and EPS, or vanilla PS.
	** Creates and writes to filePathName (may not be NULL).
	** Does NOT use system printer driver.
	** Only has partial font emitting capabilities on some platforms:
	** 	Mac:	embedded and system Type 1 fonts only; no TrueType or substitution fonts.
	**	Win:	embedded and system Type 1 fonts only; no TrueType or substitution fonts.
	**	UNIX:	all fonts
	*/
	ASBool emitToFile;
	ASBool doColorSeparations;				/* Perform level 1 TN #5054 color separations */
	ASEnum8 emitFileOption;					/* file output options: PS, EPS, preview */
	ASEnum8 emitFontOption;					/* font output options: none, embedded Type 1, etc. */

	/* More emit options. */
	ASUns32	emitFlags;						/* such as kAVEmitHalftones */

	/* Support for multiple page ranges */
	PDPageRange *ranges;
	AVTSmallArraySize numRanges;
	/* control over TrueType --> Type 1 conversion for PostScript printing */
	ASBool TTasT42;			/* true means send TrueType fonts as TrueType fonts (level 3 and most level 2 PS printers,
	false means convert TT to T1, typically ONLY desirable for Level 1 PS where no TT handling was present */
	ASBool	printAsImage;					/* true means print pages as image */
	ASBool	printerHasFarEastFonts;			/* true means don't down load far east fonts to printer. */
	ASBool reverse;				/* print from lastPage to firstPage */
	ASInt32				pageSpec;	/* PDAllPages, PDEvenPagesOnly, or PDOddPagesOnly */
	ASInt32		transparencyLevel;	
	/* 1: "The entire page will be rasterized. Use this setting for printing 
		or exporting complex pages with many transparent objects. Ideal for fast 
		output at low resolution; higher resolution will yield higher quality but 
		increase processing time. Size of saved files or print spool files may be large.

	   2: "Maintains simpler vector objects, but rasterizes more complex areas involving 
	   transparency. Ideal for artwork with only a few transparent objects. Some printers 
	   may yield rough transitions between bordering vector and raster objects and make 
	   hairlines appear thicker. Appropriate for low-memory systems.

	   3: "Maintains most objects as vector data, but rasterizes very complex transparent 
		regions. Generally the best setting for printing and exporting most pages. 
		With some printers, improves transition issues between bordering vector and raster objects.

	   4: "Maintains most of the page content as vectors, rasterizing only extremely complex areas. 
	Produces high quality output that is generally resolution-independent. Higher occurrences of 
	transparent regions will increase processing time. With some printers improves transition issues 
	between bordering vector and raster objects.

	   5: "The entire page is printed or exported as vector data, to the greatest extent possible. This 
	   produces the highest quality resolution-independent output. Processing of complex pages may be 
	   very time and memory intensive.

  */
  char destProfile[256];		/* Color profile for destination. */
} AVDocPrintParamsRec;
#endif /*!defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)*/


#if !defined(ACRO_SDK_LEVEL)  || (ACRO_SDK_LEVEL < 0x00060000)
typedef oldAVOpenSaveDialogParamsRec AVOpenSaveDialogParamsRec;
typedef oldAVOpenSaveDialogParams AVOpenSaveDialogParams;
typedef oldAVDocSelectionServerRec AVDocSelectionServerRec;
typedef oldAVDocViewDefRec AVDocViewDefRec;
typedef oldAVDocOpenParamsRec AVDocOpenParamsRec;
typedef oldAVDocOpenParams AVDocOpenParams;
typedef oldAVToolBarPositionRec AVToolBarPositionRec;
typedef oldAVToolBarPosition AVToolBarPosition;
typedef oldAVAnnotHandlerDrawExProc AVAnnotHandlerDrawExProc;
typedef oldAVAnnotHandlerDoClickProc AVAnnotHandlerDoClickProc;
typedef oldAVAnnotHandlerAdjustCursorProc AVAnnotHandlerAdjustCursorProc;
typedef oldAVAnnotHandlerPtInAnnotViewBBoxProc AVAnnotHandlerPtInAnnotViewBBoxProc;
typedef oldAVAnnotHandlerGetAnnotViewBBoxProc AVAnnotHandlerGetAnnotViewBBoxProc;
typedef oldAVAnnotHandlerRec AVAnnotHandlerRec;
typedef oldAVToolRec AVToolRec;
typedef oldAVWindowHandlerRec AVWindowHandlerRec;
#endif
