#pragma once


extern ASAtom t_Mobile;
extern ASAtom t_Original;

CosObj PDFormFromPage(CosDoc targetDoc, PDPage pdp);
bool AddContentStream(CosObj stream, char** data, int * len);
ASBool PDPageInsertForm(PDPage page, CosObj inFormObj, ASAtom name, ASAtom ocName);
ASBool GetFormBBox(CosObj inFormObj, ASFixedRect* outBBox);

bool PrepareDesignWithContent(PDDoc pdDoc, ASAtom target, ASDouble zoom, bool thisFile);



