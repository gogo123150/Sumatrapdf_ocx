/* Copyright 2013 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#ifndef TextSelection2_h
#define TextSelection2_h

#include "BaseEngine.h"
#include "TextSelection.h"

class WStrVec;

//struct TextSel2:public TextSel
//{
//	int *pstartPage, *pendPage;
//	int *pstartGlyph, *pendGlyph;
//};

struct TextSel2:public TextSel{
	bool  whole;
	LONG  Color;
	WCHAR* Text;

	TextSel2(){
		whole =false;
		len = 0;
		pages = NULL;
		rects = NULL;
		Color = 0;
		Text = NULL;
	}

	~TextSel2()
	{
		//str::ReplacePtr(&Text,NULL);

	}
};


class TextSelection2
{
public:
    TextSelection2(BaseEngine *engine, PageTextCache *textCache);
    ~TextSelection2();

    //bool IsOverGlyph(int pageNo, double x, double y);
    void StartAt(int pageNo, int glyphIx);
    void StartAt(int pageNo, double x, double y) {
        StartAt(pageNo, FindClosestGlyph(pageNo, x, y));
    }
    void SelectUpTo(int pageNo, int glyphIx);
    void SelectUpTo(int pageNo, double x, double y) {
        SelectUpTo(pageNo, FindClosestGlyph(pageNo, x, y));
    }
    //void SelectWordAt(int pageNo, double x, double y);
    //void CopySelection(TextSelection2 *orig);
    //WCHAR *ExtractText(WCHAR *lineSep);
    void Reset();

    TextSel2* result;

	Vec<TextSel2*> ResultVec;

    //void GetGlyphRange(int *fromPage, int *fromGlyph, int *toPage, int *toGlyph) const;
	void ResetResult(TextSel2* presult);
protected:
    int startPage, endPage;
    int startGlyph, endGlyph;

    BaseEngine *    engine;
    PageTextCache * textCache;

    int FindClosestGlyph(int pageNo, double x, double y);
    void FillResultRects(int pageNo, int glyph, int length, WStrVec *lines=NULL);
};

#endif
