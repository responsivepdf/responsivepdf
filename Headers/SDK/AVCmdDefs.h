/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 2000-2003 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

*********************************************************************/

/**
 AVCmdDefs.h

 - Defines the AVCommand names, parameters, etc. to allow developers
   to drive the built-in AVCommands.

 - Built-in commands are organized into groups:
  - Comments Command Group
  - Document Command Group
  - JavaScript Command Group
  - Page Command Group
  - PDF Consultant Command Group
*/

/**
  For all commands

  kAVCommandUIPolicy
*/
#define kAVCommandUIPolicy "UIPolicy"

/*-----------------------------------
  Comments Command Group
-------------------------------------*/

/**
  Registered Names - Comments Group

  kAVCommandGroupComments
  kAVCommandDeleteAllComments
  kAVCommandSummarizeComments
*/
#define kAVCommandGroupComments "Comments"
#define kAVCommandDeleteAllComments "DeleteAll"
#define kAVCommandSummarizeComments "Summarize"

/**
  Parameters for Summarize Comments

  kCommentsCmdKeySortBy: ASInt32
  kCommentsCmdKeyOutputPath: ASPathName
  kCommentsCmdKeySaveWithOriginal: ASBool
    If true, the command writes the file to the path specified by
    the OutputPath parameter.
*/
#define kCommentsCmdKeySortBy "SortBy"
#define kCommentsCmdKeyOutputPath "OutputPath"
#define kCommentsCmdKeySaveWithOriginal "SaveInOriginalDir"

/**
  Enumeration for the "SortBy" parameter

  kAVSortByPage
  kAVSortByAuthor
  kAVSortByModDate
  kAVSortByType
*/
enum {
  kAVSortByPage = 1,
  kAVSortByAuthor = 3,
  kAVSortByModDate,
  kAVSortByType
};

enum {
  kAVFontSizeSmall = 1,
  kAVFontSizeMedium = 2,
  kAVFontSizeLarge = 3
};

/*-------------------------------------------------------
  Document Group
-------------------------------------------------------*/

/**
  Shared Command Parameters

  kDocCmdKeyLeaveAsIs: ASCab
    All values that are to be left untouched. If cabinet is not
    present, or a key is not present, it is assumed to be a valid
    value in the cab.
*/
#define kDocCmdKeyLeaveAsIs "LeaveAsIs"

/**
  Registered Names - Document Group

  kAVCommandGroupDocument
  kAVCommandAccessibilityCheck
    If keypages is selected page and AVDoc is NULL, the first page is processed.
  kAVCommandDocumentSummary
  kAVCommandEmbedAllThumbs
    No dialog shown
  kAVCommandExtractAsJpeg
  kAVCommandExtractAsPng
  kAVCommandExtractAsTiff
  kAVCommandPrint
    If UIPolicy is Interactive, the standard print dialog is displayed;
    otherwise the default print settings are used.
  kAVCommandRemovedEmbeddedThumbs
    No dialog shown
  kAVCommandSecurity
  kAVCommandSetOpenOptions
  kAVCommandAddHeadFoot
  kAVCommandFlattenOCGs
  kAVCommandMakeAccessible
*/
#define kAVCommandGroupDocument "Document"
#define kAVCommandAccessibilityCheck "AccessibilityCheck"
#define kAVCommandDocumentSummary "GeneralInfo"
#define kAVCommandEmbedAllThumbs "CreateAllThumbs"
#define kAVCommandExtractAsJpeg "ExtractAsJpeg"
#define kAVCommandExtractAsPng "ExtractAsPng"
#define kAVCommandExtractAsTiff "ExtractAsTiff"
#define kAVCommandPrint "Print"
#define kAVCommandRemovedEmbeddedThumbs "DeleteAllThumbs"
#define kAVCommandSecurity "DocSecurity"
#define kAVCommandSetOpenOptions "OpenInfo"
#define kAVCommandAddHeadFoot "HeadFootCmd"
#define kAVCommandFlattenOCGs "FlattenOCGs"
#define kAVCommandMakeAccessible "MakeAccessible"

/**
  HeadFootCmd parameters

  kHeadFootCmdHeadFootCab
  kHeadFootCmdHeadFootCmdCab
  kHeadFootCmdHeadCab
  kHeadFootCmdFootCab
  kHeadFootCmdDefCharSet
  kHeadFootCmdDefFontName
  kHeadFootCmdEven
  kHeadFootCmdOdd
  kHeadFootCmdStart
  kHeadFootCmdEnd
  kHeadFootCmdLeftMargin
  kHeadFootCmdRightMargin
  kHeadFootCmdTopMargin
  kHeadFootCmdBottommargin
  kHeadFootCmdMakeOptional
  kHeadFootCmdLeftCab
  kHeadFootCmdCenterCab
  kHeadFootCmdRightCab
*/
#define kHeadFootCmdHeadFootCab "HeadFoot"
#define kHeadFootCmdHeadFootCmdCab "HeadFootCmd"
#define kHeadFootCmdHeadCab "HEADER"
#define kHeadFootCmdFootCab "FOOTER"
#define kHeadFootCmdDefCharSet "DefaultFontCharset"
#define kHeadFootCmdDefFontName "DefaultFontName"
#define kHeadFootCmdEven "Even"
#define kHeadFootCmdOdd "Odd"
#define kHeadFootCmdStart "START"
#define kHeadFootCmdEnd "END"
#define kHeadFootCmdLeftMargin "LeftMargin"
#define kHeadFootCmdRightMargin "RightMargin"
#define kHeadFootCmdTopMargin "TopMargin"
#define kHeadFootCmdBottommargin "BottomMargin"
#define kHeadFootCmdMakeOptional "MAKE_OPTIONAL"
#define kHeadFootCmdLeftCab "HeadFoot:Left"
#define kHeadFootCmdCenterCab "HeadFoot:Center"
#define kHeadFootCmdRightCab "HeadFoot:Right"

/**
  Accessibility Check Parameters

  kAccCheckCmdKeyCreateLog: ASBool - default is true
  kAccCheckCmdKeyPathText: ASText
    Log file destination. If FileSys is NULL, the log file is
    written to the destination directory. If PathText is not
    specified, the log is written to the same directory as the
    source document. If FileSys is supplied, the file is
    opened through that file system; otherwise the default is
    used.
  kAccCheckCmdKeyCreateComments: ASBool - default is flase
  kAccCheckCmdKeyAlternateText: kASValueBool - default is true
  kAccCheckCmdKeyLanguageSpecified: kASValueBool - default is true
  kAccCheckCmdKeyCharEncodings: kASValueBool - default is true
  kAccCheckCmdKeyFieldDescriptions: kASValueBool - default is true
  kAccCheckCmdKeyCheckStructure: kASValueBool - default is true
  kAccCheckCmdKeyPages: kASValueInteger
    Default is all pages. If keypages is selected page and avdoc
    is NULL, the first page is processed.
  kAccCheckCmdKeyFromPage: kASValueInteger - default is 0
  kAccCheckCmdKeyToPage: kASValueInteger - default is 0
  kAccCheckCmdKeyInBatch: kASValueBool
  kAccCheckCmdKeyHints
*/
#define kAccCheckCmdKeyCreateLog "OutputOurLog"
#define kAccCheckCmdKeyPathText "ChosenPathText"
#define kAccCheckCmdKeyCreateComments "AttachAnnots"
#define kAccCheckCmdKeyAlternateText "AltText"
#define kAccCheckCmdKeyLanguageSpecified "LangSpec"
#define kAccCheckCmdKeyCharEncodings "CharEnc"
#define kAccCheckCmdKeyFieldDescriptions "FieldNames"
#define kAccCheckCmdKeyCheckStructure "CheckStruct"
#define kAccCheckCmdKeyPages "Pages"
#define kAccCheckCmdKeyFromPage "FromPage"
#define kAccCheckCmdKeyToPage "ToPage"
#define kAccCheckCmdKeyInBatch "IsBatch"
#define kAccCheckCmdKeyHints "Hints"

/**
  Enumeration for the "Pages" parameter: kASValueInteger

  kAccCheckAllPages
  kAccCheckCurrentPage
  kAccCheckSelectedPages
*/
enum {
  kAccCheckAllPages,
  kAccCheckCurrentPage,
  kAccCheckSelectedPages
};

/**
  Document Summary Parameters.

  kDocInfoCmdKeyTitle: ASText
  kDocInfoCmdKeySubject: ASText
  kDocInfoCmdKeyAuthor: ASText
  kDocInfoCmdKeyKeywords: ASText
  kDocInfoCmdKeyBinding: ASText
*/
#define kDocInfoCmdKeyTitle "Title"
#define kDocInfoCmdKeySubject "Subject"
#define kDocInfoCmdKeyAuthor "Author"
#define kDocInfoCmdKeyKeywords "Keywords"
#define kDocInfoCmdKeyBinding "Binding"

/**
  Shared Image Extraction Parameters.

  kExtractImgCmdKeyResolution: kASValueInteger
  kExtractImgCmdKeyColorSpace: kASValueInteger
  kExtractImgCmdKeyConvFormat: kASValueInteger
    Set to the format that you are exporting to.
  kExtractImgCmdKeyConfigured: kASValueBool
    Must be set to true to mark the command parameters as being in a valid state.
  kExtractImgCmdKeyOverwriteFiles: kASValueBool - default is true
    Whether files are overwritten. Default is true. If set to false, and output
    file is found to exist, alert is show if in batch; otherwise the user is
    given the option to overwrite.
  kExtractImgCmdKeyInBatch: kASValueBool - default is true
    Used to control the format of the settings dialog. true gets the dest folder
    info.
  kExtractImgCmdKeyDestDirectory: kASValuePathName
    Must be passed, or command returns an error. Default is the
    kAVSCUser/kAVSFDocuments folder
*/
#define kExtractImgCmdKeyResolution "Resolution"
#define kExtractImgCmdKeyColorSpace "ColorSpace"
#define kExtractImgCmdKeyConvFormat "ConversionFormat"
#define kExtractImgCmdKeyConfigured "Configured"
#define kExtractImgCmdKeyOverwriteFiles "Overwrite"
#define kExtractImgCmdKeyInBatch "Batch"
#define kExtractImgCmdKeyDestDirectory "DestDirectory"

/**
  Image Extraction Parameters - Format Specific.

  kExtractJpegCmdKeyCompression: kASValueInteger
  kExtractJpegCmdKeyFormat: kASValueInteger
  kExtractPngCmdKeyInterlace: kASValueInteger
  kExtractPngCmdKeyFilter: kASValueInteger
  kExtractTiffCmdKeyMonoCompression: kASValueInteger
  kExtractTiffCmdKeyColorCompression: kASValueInteger
*/
#define kExtractJpegCmdKeyCompression "Compression"
#define kExtractJpegCmdKeyFormat "Format"
#define kExtractPngCmdKeyInterlace "Interlace"
#define kExtractPngCmdKeyFilter "Filter"
#define kExtractTiffCmdKeyMonoCompression "MonoCompression"
#define kExtractTiffCmdKeyColorCompression "ColorCompression"

/**
  Enumeration for "ConversionFormat" parameter: kASValueInteger

  kImgConversionFormatTiff
  kImgConversionFormatJpeg
  kImgConversionFormatPng

  Default is appropriate value—JPEG, TIFF, PNG
*/
enum {
  kImgConversionFormatTiff = 1,
  kImgConversionFormatJpeg,
  kImgConversionFormatPng,
};

/**
  Enumeration for "Resolution" parameter: kASValueInteger

  kImgResolutionAuto = -1 - default
  kImgResolution72 = 72
  kImgResolution96 = 96
  kImgResolution150 = 150
  kImgResolution300 = 300
  kImgResolution600 = 600
*/
enum {
  kImgResolutionAuto = -1,
  kImgResolution72 = 72,
  kImgResolution96 = 96,
  kImgResolution150 = 150,
  kImgResolution300 = 300,
  kImgResolution600 = 600
};

/**
  Enumeration for "ColorSpace" parameter: kASValueInteger

  kColorSpaceAuto - default
  kColorSpaceRGB
  kColorSpaceGrayscale
  kColorSpaceMonochrome
*/
enum {
  kColorSpaceAuto = 1,
  kColorSpaceRGB,
  kColorSpaceGrayscale,
  kColorSpaceMonochrome
};

/**
  Enumeration for Tiff
    "MonoCompression" and
    "ColorCompression" parameters: kASValueInteger

  kTiffCompressionNone
  kTiffCompressionCCITT_G3
  kTiffCompressionCCITT_G4 - default for mono
  kTiffCompressionLzw - default for color
  kTiffCompressionZip
  kTiffCompressionJpegLow
  kTiffCompressionJpegMediumLow
  kTiffCompressionJpegMedium
  kTiffCompressionJpegMediumHigh
  kTiffCompressionJpegHigh
*/
enum {
  kTiffCompressionNone = 1,
  kTiffCompressionCCITT_G3,
  kTiffCompressionCCITT_G4,
  kTiffCompressionLzw,
  kTiffCompressionZip,
  kTiffCompressionJpegLow,
  kTiffCompressionJpegMediumLow,
  kTiffCompressionJpegMedium,
  kTiffCompressionJpegMediumHigh,
  kTiffCompressionJpegHigh
};

/**
  Enumeration for Jpeg "Compression" parameter: kASValueInteger

  kJpegCompressionLow
  kJpegCompressionMediumLow
  kJpegCompressionMedium - default
  kJpegCompressionMediumHigh
  kJpegCompressionHigh
*/
enum {
  kJpegCompressionLow = 1,
  kJpegCompressionMediumLow,
  kJpegCompressionMedium,
  kJpegCompressionMediumHigh,
  kJpegCompressionHigh
};

/**
  Enumeration for Jpeg "Format" parameter: ASValueInteger

  kJpegFormatBaseline - default
  kJpegFormatOptimized
  kJpegFormatProgressive3
  kJpegFormatProgressive4
  kJpegFormatProgressive5
*/
enum {
  kJpegFormatBaseline = 1,
  kJpegFormatOptimized,
  kJpegFormatProgressive3,
  kJpegFormatProgressive4,
  kJpegFormatProgressive5
};

/**
  Enumeration for Png "Interlace" parameter: kASValueInteger

  kPngInterlaceNone - default
  kPngInterlaceAdam7
*/
enum {
  kPngInterlaceNone = 1,
  kPngInterlaceAdam7
};

/**
  Enumeration for Png "Filter" parameter: kASValueInteger

  kPngFilterNone
  kPngFilterSub
  kPngFilterUp
  kPngFilterAverage
  kPngFilterPaeth
  kPngFilterAdaptive - default
*/
enum {
  kPngFilterNone = 1,
  kPngFilterSub,
  kPngFilterUp,
  kPngFilterAverage,
  kPngFilterPaeth,
  kPngFilterAdaptive
};

/**
  Security Parameters

  kDocSecurityCmdKeyHandler: kASValueAtom - default is ASAtomNull
  kDocSecurityCmdKeySettings: kASValueCab
*/
#define kDocSecurityCmdKeyHandler "CryptHandler"
#define kDocSecurityCmdKeySettings "SecuritySettings"

/**
  Set Open Options Parameters

  kOpenOptionsCmdKeyPageNum: kASValueText
  kOpenOptionsCmdKeyMagnification: kASValueText
    For example, "100%" : Open action
  kOpenOptionsCmdKeyPageLayout: kASValueInteger
    For example, PDLayoutSinglePage
  kOpenOptionsCmdKeyPageMode: kASValueInteger
    For example, PDUseThumbs
  kOpenOptionsCmdKeyFullScreen: kASValueBool
  kOpenOptionsCmdKeyHideToolbar: kASValueBool
  kOpenOptionsCmdKeyHideMenubar: kASValueBool
  kOpenOptionsCmdKeyHideWindowUI: kASValueBool
  kOpenOptionsCmdKeyFitWindow: kASValueBool
  kOpenOptionsCmdKeyCenterWindow: kASValueBool
  kOpenOptionsCmdKeyDisplayDocTitle: kASValueBool
*/
#define kOpenOptionsCmdKeyPageNum "PageNum"
#define kOpenOptionsCmdKeyMagnification "Magnification"
#define kOpenOptionsCmdKeyPageLayout "PageLayout"
#define kOpenOptionsCmdKeyPageMode "PageMode"
#define kOpenOptionsCmdKeyFullScreen "FullScreen"
#define kOpenOptionsCmdKeyHideToolbar "HideToolbar"
#define kOpenOptionsCmdKeyHideMenubar "HideMenubar"
#define kOpenOptionsCmdKeyHideWindowUI "HideWindowUI"
#define kOpenOptionsCmdKeyFitWindow "FitWindow"
#define kOpenOptionsCmdKeyCenterWindow "CenterWindow"
#define kOpenOptionsCmdKeyDisplayDocTitle "DisplayDocTitle"

/*-------------------------------------------------------
  JavaScript Command Group
-------------------------------------------------------*/

/**
  Registered Names - JavaScript

  kAVCommandGroupJavaScript
  kAVCommandExecuteJavaScript
*/
#define kAVCommandGroupJavaScript "JavaScript"
#define kAVCommandExecuteJavaScript "JavaScript"

/**
  Execute JavaScript Parameters

  kExecJavaScriptCode: kASValueText
  kExecJavaScriptName: kASValueText  (Not currently used)
*/
#define kExecJavaScriptCode "ScriptCode"
#define kExecJavaScriptName "ScriptName"

/*-------------------------------------------------------
  Page Command Group
-------------------------------------------------------*/

/**
  Registered Names - Page

  kAVCommandGroupPage
  kAVCommandCropPages
  kAVCommandDeletePages
    kPageCmdKeyEvenOdd not supported.
    kPageCmdKeyGroup default is kAVPagesFromTo.
    kAVPagesSelected must be combined with an AVDoc.
  kAVCommandInsertPages
  kAVCommandNumberPages
  kAVCommandRotatePages
*/
#define kAVCommandGroupPage "Page"
#define kAVCommandCropPages "CropPages"
#define kAVCommandDeletePages "DeletePages"
#define kAVCommandInsertPages "InsertPages"
#define kAVCommandNumberPages "NumberPages"
#define kAVCommandRotatePages "RotatePages"

/**
  Common Page Parameters.

  kPageCmdKeyGroup: kASValueInteger
  kPageCmdKeyEvenOdd: kASValueInteger
  kPageCmdKeyFrom: kASValueText
  kPageCmdKeyTo: kASValueText
*/
#define kPageCmdKeyGroup "Group"
#define kPageCmdKeyEvenOdd "EvenOdd"
#define kPageCmdKeyFrom "From"
#define kPageCmdKeyTo "To"

/**
  Enumeration for "Group" parameter: kASValueInteger

  kAVPagesAll
  kAVPagesSelected
  kAVPagesFromTo
*/
enum {
  kAVPagesAll,
  kAVPagesSelected,
  kAVPagesFromTo
};

/**
  Enumeration for "EvenOdd" parameter: kASValueInteger

  kAVPagesEvenOdd
  kAVPagesEven
  kAVPagesOdd
*/
enum {
  kAVPagesEvenOdd,
  kAVPagesEven,
  kAVPagesOdd
};

/**
  Crop Pages Parameters.

  - kPageCmdKeyGroup default is kAVPagesAll.
  - kPageCmdKeyEvenOdd default is kAVPagesEvenOdd.
  - If cropping to bounding box, the dimension params are ignored.

  kCropPagesCmdKeyCropType: kASValueInteger
  kCropPagesCmdKeyLeft: kASValueDouble - Default is 0.0
  kCropPagesCmdKeyRight: kASValueDouble - Default is 0.0
  kCropPagesCmdKeyTop: kASValueDouble - Default is 0.0
  kCropPagesCmdKeyBottom: kASValueDouble - Default is 0.0
*/
#define kCropPagesCmdKeyCropType "CropType"
#define kCropPagesCmdKeyLeft = "Left";
#define kCropPagesCmdKeyRight = "Right";
#define kCropPagesCmdKeyTop = "Top";
#define kCropPagesCmdKeyBottom = "Bottom";

/**
  Enumeration for "CropType" parameter: kASValueInteger

  kAVCropCustom - default
  kAVCropToBoundingBox
*/
enum {
  kAVCropCustom,
  kAVCropToBoundingBox,
};

/**
  Insert Pages Parameters.

  kInsertPagesCmdKeyInsertBefore: kASValueBool
    Default is false, meaning insert after.
  kInsertPagesCmdKeyPosition: kASValueInteger
  kInsertPagesCmdKeyPageString: kASValueText
  kInsertPagesCmdKeySrcFileName: kASValueText
  kInsertPagesCmdKeySourcePathNames: kASValueCab
*/
#define kInsertPagesCmdKeyInsertBefore "InsertBefore"
#define kInsertPagesCmdKeyPosition "Position"
#define kInsertPagesCmdKeyPageString "PageString"
#define kInsertPagesCmdKeySrcFileName "SrcFileName"
#define kInsertPagesCmdKeySourcePathNames "SourcePathNames"

/**
  Enumeration for "InsertBefore" parameter: kASValueInteger

  kAVPosRelativeToFirst
  kAVPosRelativeToLast
  kAVPosRelativeToPage - default
*/
enum {
  kAVPosRelativeToFirst = 1,
  kAVPosRelativeToLast,
  kAVPosRelativeToPage
};

/**
  Number Pages Parameters.

  - kPageCmdKeyGroup: Default is kAVPagesAll.
  - kPageCmdKeyEvenOdd: Default is kAVPagesEvenOdd.

  kNumberPagesCmdKeyStyle: kASValueInteger
  kNumberPagesCmdKeyStart: kASValueInteger - default is 1
  kNumberPagesCmdKeyMergePrevious: kASValueBool - default is false
  kNumberPagesCmdKeyPrefix: kASValueString - default is ""
*/
#define kNumberPagesCmdKeyStyle "Style"
#define kNumberPagesCmdKeyStart "Start"
#define kNumberPagesCmdKeyMergePrevious "MergePrevious"
#define kNumberPagesCmdKeyPrefix "Prefix"

/**
  Enumeration for "Style" parameter.

  kPageLabelStyleNone - default
  kPageLabelStyleDecimal
  kPageLabelStyleRomanLower
  kPageLabelStyleRomanUpper
  kPageLabelStyleAlphaLower
  kPageLabelStyleAlphaUpper
*/
enum {
  kPageLabelStyleNone = 1,
  kPageLabelStyleDecimal,
  kPageLabelStyleRomanLower,
  kPageLabelStyleRomanUpper,
  kPageLabelStyleAlphaLower,
  kPageLabelStyleAlphaUpper
};

/**
  Rotate Pages Parameters.

  - kPageCmdKeyGroup default is kAVPagesAll.
  - kPageCmdKeyEvenOdd default is kAVPagesEvenOdd.

  kRotatePagesCmdKeyDegrees: kASValueInteger - default is pdRotate90
  kRotatePagesCmdKeyAction: kASValueInteger
*/
#define kRotatePagesCmdKeyDegrees "Degrees"
#define kRotatePagesCmdKeyAction "Action"

/**
  Enumeration for "Action" parameter: kASValueInteger

   kAVRotateLandscapePages
   kAVRotatePortraitPages
   kAVRotateEveryPage - default
*/
enum {
  kAVRotateLandscapePages,
  kAVRotatePortraitPages,
  kAVRotateEveryPage
};

/*-------------------------------------------------------
  PDF Consultant Command Group
-------------------------------------------------------*/

/**
  Registered Names - Comments Group.

  kAVCommandGroupConsultant "PDF Consultant"
  kAVCommandAuditSpace
    Entirely interactive
  kAVCommandDetectAndRemove "VirusCheck"
  kAVCommandOptimizeSpace "SpaceReductionAgent"
*/
#define kAVCommandGroupConsultant "PDF Consultant"
#define kAVCommandAuditSpace "SpaceAuditAgent"
#define kAVCommandDetectAndRemove "VirusCheck"
#define kAVCommandOptimizeSpace "SpaceReductionAgent"

/**
  OptimizeSpace Parameters.

  kOptSpaceCmdKeyRemoveBmarks: kASValueBool - default is true
  kOptSpaceCmdKeyRemoveLinks: kASValueBool - default is true
  kOptSpaceCmdKeyRemoveDests: kASValueBool - default is true
  kOptSpaceCmdKeyDestConversionType: kASValueInteger
*/
#define kOptSpaceCmdKeyRemoveBmarks "KillBrokenBookmarks"
#define kOptSpaceCmdKeyRemoveLinks "KillBrokenLinkAnnots"
#define kOptSpaceCmdKeyRemoveDests "KillUnusedNamedDests"
#define kOptSpaceCmdKeyDestConversionType "ConversionType"

/**
  Enumeration for "ConversionType" parameter: kASValueInteger

  kOptSpaceRemoveUnused - default
  kOptSpaceConvertIfSpaceSaved
  kOptSpaceConvertAll
*/
enum {
  kOptSpaceRemoveUnused,
  kOptSpaceConvertIfSpaceSaved,
  kOptSpaceConvertAll
};

/**
  DetectAndRemove Parameters

  kVirusCheckCmdKeyOptions: kASValueCab - default is stuff
  kVirusCheckCmdKeyNumOptions: kASValueInteger - default is 5
  kVirusCheckCmdKeyRemove: kASValueBool - default is false
*/
#define kVirusCheckCmdKeyOptions "SelectedOptions"
#define kVirusCheckCmdKeyNumOptions "NumOptions"
#define kVirusCheckCmdKeyRemove "ShouldRepair"
#define kVirusCheckCmdKeyJavaScript "idcJavaScript"
#define kVirusCheckCmdKeyAltImage "idcAltImage"
#define kVirusCheckCmdKeyFileEmbed "idcFileEmbed"
#define kVirusCheckCmdKeyAllAnnots "idcAllAnnots"
#define kVirusCheckCmdKeyExternalRefs "idcExternalRefs"
#define kVirusCheckCmdKeyMultiMedia "idcMultiMedia"
#define kVirusCheckCmdKeyFormActions "idcForm"

