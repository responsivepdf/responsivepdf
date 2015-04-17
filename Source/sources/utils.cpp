#include "PIHeaders.h"

#include "utils.h"

ASAtom t_Mobile;
ASAtom t_Original;

CosObj PDFormFromPage(CosDoc targetDoc, PDPage pdp)
{
  if (targetDoc == NULL || pdp == NULL)
    ASRaise(GenError(genErrBadParm));

  ASInt32 pageNum = PDPageGetNumber(pdp);

  PDDoc lTempPDDoc = NULL;
  bool lReleasePage = false;

  CosObj lCosStream = CosNewNull();
  DURING
/*
    //create temp page for flattening when annotations are there
    if (PDPageGetNumAnnots(pdp) > 0)
    {
      PDPage lFlatPage = NULL;
      DURING
        PDDoc lSrcDoc = PDPageGetDoc(pdp);
      ASInt32 lPageNum = PDPageGetNumber(pdp);

      lTempPDDoc = PDDocCreate();
      PDDocInsertPages(lTempPDDoc, -1, lSrcDoc, lPageNum, 1, PDInsertAll, NULL, NULL, NULL, NULL);

      lFlatPage = PDDocAcquirePage(lTempPDDoc, 0);

//      if (!CAPUtils::PDPageFlatten(lFlatPage))
//        ASRaise(0);

      pdp = lFlatPage;
      lReleasePage = true;
      HANDLER
        if (lFlatPage)
          PDPageRelease(lFlatPage);
      END_HANDLER
    }
*/
    ///////////////////////////////////////////////////////////////////////
    // Create "Form XObject" from the source page
    CosObj theAttributesDict = CosNewDict( targetDoc, false, 8 );
    CosObj cObj = CosNewName( targetDoc, false, ASAtomFromString("XObject") );
    CosDictPut( theAttributesDict, ASAtomFromString("Type"), cObj );
    cObj = CosNewName( targetDoc, false, ASAtomFromString("Form") );
    CosDictPut( theAttributesDict, ASAtomFromString("Subtype"), cObj );
    cObj = CosNewInteger (targetDoc, false, 1);
    CosDictPut( theAttributesDict, ASAtomFromString("FormType"), cObj );
    cObj = CosNewName (targetDoc, false, ASAtomFromString("X"));
    CosDictPut( theAttributesDict, ASAtomFromString("Name"), cObj );

    // Copy the resources dict from the source page to the XObject
    CosObj lCosObjResource = CosNewNull();
    CosObj cosFromPage = PDPageGetCosObj(pdp);
    CosObj cosFromResource = CosDictGet(cosFromPage,ASAtomFromString("Resources"));
    CosObj cosPageParent = CosDictGet(cosFromPage,ASAtomFromString("Parent")); //parent
    while (CosObjEqual(cosFromResource, CosNewNull()) && !CosObjEqual(cosPageParent, CosNewNull())){
      cosFromResource = CosDictGet(cosPageParent,ASAtomFromString("Resources"));
      cosPageParent = CosDictGet(cosPageParent,ASAtomFromString("Parent"));
    }
    if (!CosObjEqual(cosFromResource, CosNewNull()))
      lCosObjResource = CosObjCopy (cosFromResource, targetDoc, true);
    if (!CosObjEqual(lCosObjResource, CosNewNull()))
      CosDictPut(theAttributesDict, ASAtomFromString("Resources"), lCosObjResource);

    // BBox from fromPage
    // do X object musi byt vlozeny cropbox - inak neoreze vkladanu stranku
    ASFixedRect bBox;
    PDPageGetCropBox(pdp,&bBox);
    cObj = CosNewArray (targetDoc, false, 4);
    CosArrayPut(cObj, 0, CosNewFixed(targetDoc, false, bBox.left));
    CosArrayPut(cObj, 1, CosNewFixed(targetDoc, false, bBox.top));
    CosArrayPut(cObj, 2, CosNewFixed(targetDoc, false, bBox.right));
    CosArrayPut(cObj, 3, CosNewFixed(targetDoc, false, bBox.bottom));
    CosDictPut( theAttributesDict, ASAtomFromString("BBox"), cObj );

    // Matrix
    ASFixedMatrix lMatrix = {fixedOne, fixedZero, fixedZero, fixedOne, fixedZero, fixedZero};
    ASFixedMatrix lPageMatrix;
    PDPageGetDefaultMatrix (pdp, &lPageMatrix);
    ASFixedMatrixConcat (&lMatrix, &lMatrix, &lPageMatrix);

    cObj = CosNewArray (targetDoc, false, 6);
    CosArrayPut(cObj, 0, CosNewFixed(targetDoc, false, lMatrix.a));
    CosArrayPut(cObj, 1, CosNewFixed(targetDoc, false, lMatrix.b));
    CosArrayPut(cObj, 2, CosNewFixed(targetDoc, false, lMatrix.c));
    CosArrayPut(cObj, 3, CosNewFixed(targetDoc, false, lMatrix.d));
    CosArrayPut(cObj, 4, CosNewFixed(targetDoc, false, lMatrix.h));
    CosArrayPut(cObj, 5, CosNewFixed(targetDoc, false, lMatrix.v));
    CosDictPut( theAttributesDict, ASAtomFromString("Matrix"), cObj );

    // Content
    char* lContentString = NULL;
    int len = 0;
    CosObj lCosContent = CosDictGet(cosFromPage, ASAtomFromString("Contents"));
    CosType cosContentType = CosObjGetType(lCosContent);
    CosObj lArrayEntry;
    if (cosContentType == CosArray)
    {
      for(ASInt32 i = 0 ;(i <= CosArrayLength(lCosContent)-1);i++)
      {
        lArrayEntry = CosArrayGet(lCosContent, i);
        if (AddContentStream(lArrayEntry, &lContentString, &len) == false)
          ASRaise(0);
      }
    }
    if (cosContentType == CosStream)
      if (AddContentStream(lCosContent, &lContentString, &len) == false)
        ASRaise(0);

    // Create stream
    ASInt32 length = len;
    char* lBuffer = (char*)(const unsigned char*)(lContentString);//->GetBuffer(length);
    ASStm asStm = ASMemStmRdOpen ((char*)lBuffer,length);
    lCosStream = CosNewStream( targetDoc,
      true,               // indirect
      asStm,              // stream
      0,                  // stmStartPos
      true,               // non decoding
      theAttributesDict,  // theAttributesDict
      CosNewNull(),       // encodeParams
      length) ;           // decodeLength

    if (lContentString)
      free(lContentString);
    lContentString = 0;
    len = 0;

    if (lTempPDDoc)
    {
      if (lReleasePage)
        PDPageRelease(pdp);
      PDDocClose(lTempPDDoc);
    }
    HANDLER
      END_HANDLER
      return lCosStream;
}

bool AddContentStream(CosObj stream, char** data, int * len)
{
  CosType cosContentType = CosObjGetType(stream);
  if (cosContentType != CosStream) return false;

  ASStm asStm = NULL;
  char* streamBuffer = NULL;
  bool lResult = false;
  DURING
    ASInt32 length = CosStreamLength(stream);
    if (length > 0)
    {
      asStm = CosStreamOpenStm (stream, cosOpenFiltered);
      streamBuffer=NULL;
      ASInt32 readLength=0, precitane=0;
      do
      {
        streamBuffer = (char *)realloc(streamBuffer,precitane+length+5);
        readLength = ASStmRead ((char*)(streamBuffer+precitane), 1, length, asStm);
        precitane += readLength;
//        streamBuffer[precitane]='\0';
      } while (readLength==length);

      (*data) = (char*)realloc((*data), *len + precitane + 5);
      memcpy( (*data) + (*len), streamBuffer, precitane);
      (*len) += precitane;

//      (*data)[precitane]='\0';
//      *len += precitane;
//      *buffer += (unsigned char*) streamBuffer;
      free(streamBuffer);
      lResult = true;
    }
  HANDLER
    lResult = false;
  END_HANDLER
    if (asStm != NULL) ASStmClose(asStm);
  asStm = NULL;
  return lResult;
}

ASBool PDPageInsertForm(PDPage page, CosObj inFormObj, ASAtom name, ASAtom ocName)
{
  DURING
    CosObj lPageObj = PDPageGetCosObj(page);

    CosDoc lCosDoc = CosObjGetDoc(lPageObj);

    char lBuffer[1024];
    if (ocName != ASAtomNull)
      sprintf(lBuffer, "q /OC /%s BDC /%s Do EMC Q ", ASAtomGetString(ocName), ASAtomGetString(name));
    else
      sprintf(lBuffer, "q /%s Do Q ", ASAtomGetString(ocName), ASAtomGetString(name));

    ASStm lStm = ASMemStmRdOpen(lBuffer, (ASInt32)strlen(lBuffer));
    CosObj lCosContent = CosNewStream(lCosDoc, true, lStm, 0, false, CosNewNull(), CosNewNull(), -1);
    ASStmClose(lStm);

    CosObj cosContents = CosDictGet(lPageObj, ASAtomFromString("Contents"));
    CosType type = CosObjGetType(cosContents);
    if (type == CosDict || type == CosNull)
    {
      CosObj cosContents2 = CosNewArray(lCosDoc, true, 0);
      CosDictPut(lPageObj, ASAtomFromString("Contents"), cosContents2);

      if (type == CosDict)
        CosArrayInsert(cosContents2, 0, cosContents);

      cosContents = cosContents2;
    }

    if (CosObjGetType(cosContents) == CosArray)
      CosArrayInsert(cosContents, CosArrayLength(cosContents), lCosContent);

    ASFixedRect lFormBBox;
    if (GetFormBBox(inFormObj, &lFormBBox))
    {
      ASFixedRect lPageBBox = {fixedZero, fixedZero, lFormBBox.right-lFormBBox.left, lFormBBox.top-lFormBBox.bottom};
  //    PDPageSetMediaBox(page, lPageBBox);
  //    PDPageSetCropBox(page, lPageBBox);
    }

    CosObj lCosRecources = CosDictGet(lPageObj, ASAtomFromString("Resources"));
    if (CosObjGetType(lCosRecources) != CosDict)
    {
      lCosRecources = CosNewDict(lCosDoc, false, 0);
      CosDictPut(lPageObj, ASAtomFromString("Resources"), lCosRecources);
    }
    CosObj lCosXObject = CosDictGet(lCosRecources, ASAtomFromString("XObject"));
    if (CosObjGetType(lCosXObject) != CosDict)
    {
      lCosXObject = CosNewDict(lCosDoc, false, 0);
      CosDictPut(lCosRecources, ASAtomFromString("XObject"), lCosXObject);
    }
    CosDictPut(lCosXObject, name, inFormObj);

    E_RETURN(true);
  HANDLER
  END_HANDLER
  return false;
}

ASBool GetFormBBox(CosObj inFormObj, ASFixedRect* outBBox)
{
  DURING
    if (CosObjGetType(inFormObj) == CosStream)
    {
      CosObj lDictObj = CosStreamDict(inFormObj);

      CosObj lCosBBox = CosDictGet(lDictObj, ASAtomFromString("BBox"));
      ASFixedRect lFormBBox = {	CosFixedValue(CosArrayGet(lCosBBox, 0)), CosFixedValue(CosArrayGet(lCosBBox, 3)),
        CosFixedValue(CosArrayGet(lCosBBox, 2)), CosFixedValue(CosArrayGet(lCosBBox, 1))};

      CosObj lCosMatrix = CosDictGet(lDictObj, ASAtomFromString("Matrix"));
      ASFixedMatrix lFormMatrix = {	CosFixedValue(CosArrayGet(lCosMatrix, 0)), CosFixedValue(CosArrayGet(lCosMatrix, 1)),
        CosFixedValue(CosArrayGet(lCosMatrix, 2)), CosFixedValue(CosArrayGet(lCosMatrix, 3)),
        CosFixedValue(CosArrayGet(lCosMatrix, 4)), CosFixedValue(CosArrayGet(lCosMatrix, 5))};

      ASFixedMatrixTransformRect(&lFormBBox, &lFormMatrix, &lFormBBox);

      memcpy(outBBox, &lFormBBox, sizeof(ASFixedRect));

      E_RETURN(true);
    }
    HANDLER
      END_HANDLER

      return false;
}

bool PrepareDesignWithCurrentContent(PDDoc pdDoc, ASAtom target, ASDouble zoom)
{
  DURING
    ASInt32 numPages = PDDocGetNumPages(pdDoc);
    CosDoc cosDoc = PDDocGetCosDoc(pdDoc);

    CosObj cosRoot = CosDocGetRoot(cosDoc);
    CosObj cosResp = CosDictGet(cosRoot, ASAtomFromString("Resp"));
    if (CosObjGetType(cosResp) != CosDict)
    {
      cosResp = CosNewDict(cosDoc, true, 0);
      CosDictPut(cosRoot, ASAtomFromString("Resp"), cosResp);
    }

    CosObj cosRespLayouts = CosDictGet(cosResp, ASAtomFromString("Layouts"));
    if (CosObjGetType(cosRespLayouts) != CosArray)
    {
      //insert layouts
      cosRespLayouts = CosNewArray(cosDoc, false, 0);
      CosDictPut(cosResp, ASAtomFromString("Layouts"), cosRespLayouts);
    }

    //insert new layout
    CosObj cosLayout = CosNewDict(cosDoc, true, 0);
    CosArrayInsert(cosRespLayouts, 0, cosLayout);
    CosDictPut(cosLayout, ASAtomFromString("Zoom"), CosNewDouble(cosDoc, false, .4));
    CosDictPut(cosLayout, ASAtomFromString("Name"), CosNewName(cosDoc, false, target));
    
    for (int i = numPages - 1; i >= 0; i--)
    {
      //insert new page with the content of the original page
      PDDocInsertPages(pdDoc, i, pdDoc, i, 1, 0, NULL, NULL, NULL, NULL);
    }

  HANDLER
    return false;
  END_HANDLER

  return true;
}