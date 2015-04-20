#ifndef MAC_PLATFORM
#include "PIHeaders.h"
#endif

#include "utils.h"
#include <vector>

#define btnAddFromCurrent "RESP:AddFromCurrent"
#define btnAddFromFile "RESP:AddFromFile"
#define btnDelete "RESP:Delete"
#define btnMerge "RESP:Merge"
#define btnPrefCollate "RESP:PrefCollate"

ACCB1 void ACCB2 MyPluginCommand(void *clientData)
{
  ASAtom type = (ASAtom)clientData;

  if (ASAtomFromString(btnPrefCollate) == type)
  {
//    AVAppSetPreference("RESP", !AVAppGetPrefBool("RESP", "Collate", true));
    return;
  }

  AVDoc avDoc = AVAppGetActiveDoc();
  if (avDoc == NULL) return;

  PDDoc pdDoc = AVDocGetPDDoc(avDoc);
  CosDoc cosDoc = PDDocGetCosDoc(pdDoc);
  ASInt32 numPages = PDDocGetNumPages(pdDoc);
  

  if (ASAtomFromString(btnAddFromCurrent) == type)
  {
    PrepareDesignWithContent(pdDoc, t_Mobile, .5, true);
    return;
  }

  if (ASAtomFromString(btnAddFromFile) == type)
  {
    PrepareDesignWithContent(pdDoc, t_Mobile, .5, false);
    return;
  }

  if (ASAtomFromString(btnMerge) == type)
  {

    //read Resp settings
    CosObj cosRoot = CosDocGetRoot(cosDoc);
    CosObj cosResp = CosDictGet(cosRoot, ASAtomFromString("Resp"));
    if (CosObjGetType(cosResp) != CosDict)
    {
      AVAlertNote("Missing Resp dictionary");
      return;
    }

    CosObj cosLayouts = CosDictGet(cosResp, ASAtomFromString("Layouts"));
    if (CosObjGetType(cosLayouts) != CosArray || CosArrayLength(cosLayouts) != 1)
    {
      AVAlertNote("Missing Resp Layout definition");
      return;
    }

    CosObj cosLayout = CosArrayGet(cosLayouts, 0);
    CosObj cosLayoutZoom = CosDictGet(cosLayout, ASAtomFromString("Zoom"));
    double zoom = CosDoubleValue(cosLayoutZoom);
    if (zoom <= 0)
    {
      AVAlertNote("Invalid layout zoom level");
      return;
    }

    PDDoc pdDoc2 = PDDocCreate();
    CosDoc cosDoc2 = PDDocGetCosDoc(pdDoc2);
    CosObj cosRoot2 = CosDocGetRoot(cosDoc2);

    //insert ocg
    CosObj cosOCProperties = CosNewDict(cosDoc2, true, 0);
    CosDictPut(cosRoot2, ASAtomFromString("OCProperties"), cosOCProperties);

    CosObj cosOCGs = CosNewArray(cosDoc2, true, 0);
    CosDictPut(cosOCProperties, ASAtomFromString("OCGs"), cosOCGs);   

    CosObj cosD = CosNewDict(cosDoc2, true, 0);
    CosDictPut(cosOCProperties, ASAtomFromString("D"), cosD);   

    CosObj cosOrder = CosNewArray(cosDoc2, true, 0);
    CosDictPut(cosD, ASAtomFromString("Order"), cosOrder);   

    CosObj cosAS = CosNewArray(cosDoc2, false, 0);
    CosDictPut(cosD, ASAtomFromString("AS"), cosAS);

    //AS dictionary
    CosObj cosAS0 = CosNewDict(cosDoc2, true, 0);
    CosArrayInsert(cosAS, 0, cosAS0);

    CosObj cosCategory = CosNewArray(cosDoc2, false, 0);
    CosDictPut(cosAS0, ASAtomFromString(("Category")), cosCategory);
    CosArrayInsert(cosCategory, 0, CosNewName(cosDoc2, false, ASAtomFromString("Zoom")));

    CosDictPut(cosAS0, ASAtomFromString("Event"), CosNewName(cosDoc2, false, ASAtomFromString("View")));

    CosObj cosASOCGs = CosNewArray(cosDoc2, true, 0);
    CosDictPut(cosAS0, ASAtomFromString("OCGs"), cosASOCGs);

    char str[1024];
    sprintf(str, "oc%d", 0);
    char str1[1024];
    sprintf(str1, "oc%d", 1);

    ASText text = ASTextFromScriptText(str, kASRomanScript);
    ASText text1 = ASTextFromScriptText(str1, kASRomanScript);
    PDOCG pdOCG = PDOCGCreate(pdDoc2, text);
    PDOCG pdOCG1 = PDOCGCreate(pdDoc2, text1);
    ASTextDestroy(text);
    ASTextDestroy(text1);

    CosObj cosOCG = PDOCGGetCosObj(pdOCG);
    {
      CosObj cosIntent = CosNewName(cosDoc2, false, ASAtomFromString("View"));
      CosDictPut(cosOCG, ASAtomFromString("Intent"), cosIntent);
      CosObj cosUsage = CosNewDict(cosDoc2, false, 0);
      CosDictPut(cosOCG, ASAtomFromString("Usage"), cosUsage);
      CosObj cosZoom = CosNewDict(cosDoc2, false, 0);
      CosDictPut(cosUsage, ASAtomFromString("Zoom"), cosZoom);
      CosDictPut(cosZoom, ASAtomFromString("min"), CosNewDouble(cosDoc2, false, zoom));
    }
    CosObj cosOCG1 = PDOCGGetCosObj(pdOCG1);
    {
      CosObj cosIntent = CosNewName(cosDoc2, false, ASAtomFromString("View"));
      CosDictPut(cosOCG1, ASAtomFromString("Intent"), cosIntent);
      CosObj cosUsage = CosNewDict(cosDoc2, false, 0);
      CosDictPut(cosOCG1, ASAtomFromString("Usage"), cosUsage);
      CosObj cosZoom = CosNewDict(cosDoc2, false, 0);
      CosDictPut(cosUsage, ASAtomFromString("Zoom"), cosZoom);
      CosDictPut(cosZoom, ASAtomFromString("max"), CosNewDouble(cosDoc2, false, zoom));
    }

    CosArrayInsert(cosOrder, CosArrayLength(cosOrder), cosOCG);
    CosArrayInsert(cosASOCGs, CosArrayLength(cosASOCGs), cosOCG);
    CosArrayInsert(cosOrder, CosArrayLength(cosOrder), cosOCG1);
    CosArrayInsert(cosASOCGs, CosArrayLength(cosASOCGs), cosOCG1);

    //prepare OCMD for annotations
    CosObj cosOCMD1 = CosNewDict(cosDoc2, true, 0);
    {
      CosDictPut(cosOCMD1, ASAtomFromString("Type"), CosNewName(cosDoc2, false, ASAtomFromString("OCMD")));
      CosObj cosOCGs = CosNewArray(cosDoc2, false, 0);
      CosArrayPut(cosOCGs, 0, cosOCG1);
      CosDictPut(cosOCMD1, ASAtomFromString("OCGs"), cosOCGs);
      CosDictPut(cosOCMD1, ASAtomFromString("P"), CosNewName(cosDoc2, false, ASAtomFromString("AllOn")));
    }

    for (int i = 0; i < PDDocGetNumPages(pdDoc); i+=2)
    {
      PDPage pdPage = PDDocAcquirePage(pdDoc, i);
      ASFixedRect mediaBox;
      PDPageGetMediaBox(pdPage, &mediaBox);
      PDRotate pageRotate = PDPageGetRotate(pdPage);
      PDPageRelease(pdPage);

      ASFixedRect mediaBox2 = {fixedZero, mediaBox.top-mediaBox.bottom, mediaBox.right-mediaBox.left, fixedZero};

      if (pageRotate == 90 || pageRotate == 270)
      {
        mediaBox2.top = mediaBox.right - mediaBox.left;
        mediaBox2.right = mediaBox.top - mediaBox.bottom;
      }

      PDPage pdPage2 = PDDocCreatePage(pdDoc2, PDDocGetNumPages(pdDoc2)-1, mediaBox2);

      pdPage = PDDocAcquirePage(pdDoc, i);
      CosObj obj = PDFormFromPage(cosDoc2, pdPage);
      PDPageInsertForm(pdPage2, obj, ASAtomFromString(str), ASAtomFromString(str));
      PDPageRelease(pdPage);

      pdPage = PDDocAcquirePage(pdDoc, i+1);
      CosObj obj1 = PDFormFromPage(cosDoc2, pdPage);
      PDPageInsertForm(pdPage2, obj1, ASAtomFromString(str1), ASAtomFromString(str1));

      //process annotations
      for (int j = 0; j < PDPageGetNumAnnots(pdPage); j++)
      {
        DURING
          PDAnnot annot = PDPageGetAnnot(pdPage, j);
          PDAnnot annot2 = CosNewNull();
          
          CosObj cosAnnot = PDAnnotGetCosObj(annot);

          bool copyAction = true;

          if (PDAnnotGetSubtype(annot) == ASAtomFromString("Link"))
          {
            ASFixedRect rect;
            PDAnnotGetRect(annot, &rect);
            annot2 = PDPageAddNewAnnot(pdPage2, PDPageGetNumAnnots(pdPage2)-1, ASAtomFromString("Link"), &rect);
          }
          else// if (PDAnnotGetSubtype(annot) == ASAtomFromString("Widget"))
          {
            ASFixedRect rect;
            PDAnnotGetRect(annot, &rect);

            //copy annotation indo dest page
            PDAnnotClipboardData data = NULL; 
            if (PDAnnotCanCopy(pdPage, annot) && (data = PDAnnotCopy(pdPage, annot)) != NULL)
            {
              ASFixedPoint center = {ASFixedDiv((rect.left+rect.right), fixedTwo), ASFixedDiv((rect.bottom+rect.top), fixedTwo)};
              annot2 = PDAnnotPaste(pdPage2, &center, data);
              PDAnnotDestroyClipboardData(data);
            }
          }

          CosObj cosAnnot2 = PDAnnotGetCosObj(annot2);

          if (CosDictKnown(cosAnnot, ASAtomFromString("A")))
          {
            DURING
              //copy annot action
              PDAction action = CosDictGet(cosAnnot, ASAtomFromString("A"));
              PDAction action2 = CosNewNull();

              if (PDActionGetSubtype(annot) == ASAtomFromString("GoTo"))
              {
                PDViewDestination dest = PDActionGetDest(action);
                if (PDViewDestIsValid(dest))
                {
                  dest = PDViewDestResolve(dest, pdDoc);
                  ASInt32 pageNum;
                  ASAtom fitType;
                  ASFixedRect destRect;
                  ASFixed destZoom;
                  PDViewDestGetAttr(dest, &pageNum, &fitType, &destRect, &destZoom);

                  //check if dest page points to current page (original or mobile)
                  if (pageNum == i || pageNum == i+1)
                  {
                    PDViewDestination viewDest2 = PDViewDestCreate(pdDoc2, pdPage2, fitType, &destRect, destZoom, 0);
                    action2 = PDActionNewFromDest(pdDoc2, viewDest2, pdDoc2);
                    CosDictPut(cosAnnot2, ASAtomFromString("A"), action2);
                  }
                }
              }

              if (!PDActionIsValid(action2))
              {
                //copy action
                PDActionClipboardData data = NULL;
                if (PDActionCanCopy(action) && (data = PDActionCopy(action)) != NULL)
                {
                  action2 = PDActionPaste(pdDoc2, data);
                  CosDictPut(cosAnnot2, ASAtomFromString("A"), action2);
                  PDActionDestroyClipboardData(data);
                }
              }
            HANDLER
            END_HANDLER
          }

          if (PDAnnotIsValid(annot2))
          {
            //insert OC reference
            CosObj cosAnnot2 = PDAnnotGetCosObj(annot2);
            CosDictPut(cosAnnot2, ASAtomFromString("OC"), cosOCMD1);
          }
        HANDLER
        END_HANDLER
      }

      PDPageRelease(pdPage);

      //OCProperties
      CosObj cosProperties = CosNewDict(cosDoc2, false, 0);

      CosDictPut(cosProperties, ASAtomFromString(str), cosOCG);
      CosDictPut(cosProperties, ASAtomFromString(str1), cosOCG1);

      CosObj cosPage2 = PDPageGetCosObj(pdPage2);
      PDPageRelease(pdPage2);

      CosObj cosResources = CosDictGet(cosPage2, ASAtomFromString("Resources"));
      CosDictPut(cosResources, ASAtomFromString("Properties"), cosProperties);
    }

    AVDocOpenFromPDDoc(pdDoc2, NULL);
  }

  return;
}

ACCB1 ASBool ACCB2 MyPluginIsEnabled(void *clientData)
{
  ASAtom type = (ASAtom)clientData;

  if (ASAtomFromString(btnPrefCollate) == type)
  {
    return false;
  }

  // always enabled.
  return AVAppGetActiveDoc() != NULL;
}

ACCB1 ASBool ACCB2 MyPluginIsMarked(void *clientData)
{
  DURING
    ASAtom type = (ASAtom)clientData;
    if (ASAtomFromString(btnPrefCollate) == type)
    {
      E_RETURN(AVAppGetPrefBool("RESP", "Collate", true));
    }
  HANDLER
  END_HANDLER
  return false;
}


/////////////////////////////////////////////////////
//pi sdk callbacks

ACCB1 ASBool ACCB2 PluginExportHFTs(void)
{
	return true;
}

ACCB1 ASBool ACCB2 PluginImportReplaceAndRegister(void)
{
	return true;
}

ACCB1 ASBool ACCB2 PluginInit(void)
{

  t_Mobile = ASAtomFromString("Mobile");
  t_Original = ASAtomFromString("Original");

  AVMenubar menubar = AVAppGetMenubar();
  AVMenu volatile commonMenu = NULL;

  if (!menubar)
    return false;

  AVMenuItem menuItem = NULL;

  DURING
    commonMenu = AVMenuNew ("&Responsive PDF", "RESP:ResponsivePdf", gExtensionID);
    AVMenubarAddMenu(menubar, commonMenu, APPEND_MENU);		

    //new layout from original
    menuItem = AVMenuItemNew ("Add &Mobile Layout From Current Content", btnAddFromCurrent, NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuItemSetExecuteProc (menuItem, ASCallbackCreateProto(AVExecuteProc, MyPluginCommand), (void *)ASAtomFromString(btnAddFromCurrent));
    AVMenuItemSetComputeEnabledProc (menuItem, ASCallbackCreateProto(AVComputeEnabledProc, MyPluginIsEnabled), (void *)ASAtomFromString(btnAddFromCurrent));
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);
    
    //new layout from file
    menuItem = AVMenuItemNew ("Add Mobile Layout From &File", btnAddFromFile, NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuItemSetExecuteProc (menuItem, ASCallbackCreateProto(AVExecuteProc, MyPluginCommand), (void *)ASAtomFromString(btnAddFromFile));
    AVMenuItemSetComputeEnabledProc (menuItem, ASCallbackCreateProto(AVComputeEnabledProc, MyPluginIsEnabled), (void *)ASAtomFromString(btnAddFromFile));
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);
/*
    //delete layout
    menuItem = AVMenuItemNew ("Re&move Mobile Layout", btnDelete, NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuItemSetExecuteProc (menuItem, ASCallbackCreateProto(AVExecuteProc, MyPluginCommand), (void*)ASAtomFromString(btnDelete));
    AVMenuItemSetComputeEnabledProc (menuItem, ASCallbackCreateProto(AVComputeEnabledProc, MyPluginIsEnabled), (void*)ASAtomFromString(btnDelete));
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);
*/
    //separator
    menuItem = AVMenuItemNew ("-", "RESP:Separator", NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);

    //create responsive pdf
    menuItem = AVMenuItemNew ("&Create Responsive PDF", btnMerge, NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuItemSetExecuteProc (menuItem, ASCallbackCreateProto(AVExecuteProc, MyPluginCommand), (void*)ASAtomFromString(btnMerge));
    AVMenuItemSetComputeEnabledProc (menuItem, ASCallbackCreateProto(AVComputeEnabledProc, MyPluginIsEnabled), (void*)ASAtomFromString(btnMerge));
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);
/*
    //separator
    menuItem = AVMenuItemNew ("-", "RESP:Separator", NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);

    menuItem = AVMenuItemNew ("Co&llate Pages in Design View", btnPrefCollate, NULL, true, NO_SHORTCUT, 0, NULL, gExtensionID);
    AVMenuItemSetExecuteProc (menuItem, ASCallbackCreateProto(AVExecuteProc, MyPluginCommand), (void*)ASAtomFromString(btnPrefCollate));
    AVMenuItemSetComputeMarkedProc(menuItem, ASCallbackCreateProto(AVComputeEnabledProc, MyPluginIsMarked), (void*)ASAtomFromString(btnPrefCollate));
    AVMenuItemSetComputeEnabledProc (menuItem, ASCallbackCreateProto(AVComputeEnabledProc, MyPluginIsEnabled), (void*)ASAtomFromString(btnPrefCollate));
    AVMenuAddMenuItem(commonMenu, menuItem, APPEND_MENUITEM);
    AVMenuItemRelease(menuItem);
*/
    AVMenuRelease(commonMenu);

  HANDLER
    if (commonMenu)
      AVMenuRelease (commonMenu);
  return false;
  END_HANDLER


  return true;
}

ACCB1 ASBool ACCB2 PluginUnload(void)
{
	return true;
}

ASAtom GetExtensionName()
{
	return ASAtomFromString("TOTO:JE:ResponsivePdf");
}


ACCB1 ASBool ACCB2 PIHandshake(Uns32 handshakeVersion, void *handshakeData)
{
	if (handshakeVersion == HANDSHAKE_V0200) {
		/* Cast handshakeData to the appropriate type */
		PIHandshakeData_V0200 *hsData = (PIHandshakeData_V0200 *)handshakeData;

		/* Set the name we want to go by */
		hsData->extensionName = GetExtensionName();

		/* If you export your own HFT, do so in here */
		hsData->exportHFTsCallback = (void*)ASCallbackCreateProto(PIExportHFTsProcType, &PluginExportHFTs);

		/*
		** If you import plug-in HFTs, replace functionality, and/or want to register for notifications before
		** the user has a chance to do anything, do so in here.
		*/
		hsData->importReplaceAndRegisterCallback = (void*)ASCallbackCreateProto(PIImportReplaceAndRegisterProcType,
																		 &PluginImportReplaceAndRegister);

		/* Perform your plug-in's initialization in here */
		hsData->initCallback = (void*)ASCallbackCreateProto(PIInitProcType, &PluginInit);

		/* Perform any memory freeing or state saving on "quit" in here */
		hsData->unloadCallback = (void*)ASCallbackCreateProto(PIUnloadProcType, &PluginUnload);

		/* All done */
		return true;

	} /* Each time the handshake version changes, add a new "else if" branch */

	/*
	** If we reach here, then we were passed a handshake version number we don't know about.
	** This shouldn't ever happen since our main() routine chose the version number.
	*/
	return false;
}

