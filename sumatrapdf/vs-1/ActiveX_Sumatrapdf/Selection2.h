#ifndef Selection2_h
#define Selection2_h

#include "Selection.h"
#include "TextSelection.h"
#include "TextSelection2.h"

class WindowInfo2;

struct RectI2
{
public:
	LONG Color;
	RectI rect;
	RectI2();
};

class SelectionOnPage2: public SelectionOnPage
{
public:
	SelectionOnPage2(LONG color = 0 ,WCHAR* text = NULL,int pageNo=0, RectD *rect=NULL):SelectionOnPage(pageNo,rect),Color(color),Text(text)
	{}

	RectI2 GetRect2(DisplayModel *dm);
	static Vec<SelectionOnPage2> *FromTextSelect2(Vec<TextSel2*> *textSel);

	LONG Color;
	WCHAR* Text;
};
void DeleteOldSelectionInfo2(WindowInfo2 *win2, bool alsoTextSel=false);
void PaintTransparentRectangles2(HDC hdc, RectI screenRc, Vec<RectI2>& rects, BYTE alpha=0x5f, int margin=1);
void PaintSelection2(WindowInfo *win, HDC hdc);
void UpdateTextSelection2(WindowInfo *win, Vec<TextSel2*> *result,bool select=true);

#endif