#include "BaseUtil.h"
#include "Selection2.h"

#include "Notifications.h"
#include "SumatraPDF.h"
#include "Toolbar.h"
#include "Translations.h"
#include "uia/Provider.h"
#include "WindowInfo.h"
#include "WinUtil.h"
#include "TextSelection.h"
#include "DisplayModel2.h"
#include "WindowInfo2.h"

#define COL_SELECTION2_RECT      RGB(0xF5, 0xFC, 0x0C)

RectI2::RectI2()
{
	Color = COL_SELECTION2_RECT;
	rect = RectI();
}

RectI2 SelectionOnPage2::GetRect2(DisplayModel *dm)
{
	// if the page is not visible, we return an empty rectangle
	PageInfo *pageInfo = dm->GetPageInfo(pageNo);
	if (!pageInfo || pageInfo->visibleRatio <= 0.0)
		return RectI2();

	RectI2 tmpRectI2;
	tmpRectI2.Color = Color < 0 || Color > 0xFFFFFF ?COL_SELECTION2_RECT : Color;
	tmpRectI2.rect  = dm->CvtToScreen(pageNo, rect);
	return tmpRectI2;
}

Vec<SelectionOnPage2> *SelectionOnPage2::FromTextSelect2(Vec<TextSel2*> *textSel)
{
	int count = 0;
	for(int i = 0;i<textSel->Count();i++)
		count+= textSel->At(i)->len;

	if(count == 0)
		return NULL;

	Vec<SelectionOnPage2> *sel = new Vec<SelectionOnPage2>(count);

	for(int k = 0;k<textSel->Count();k++)
	{
		TextSel2* tmptextSel = textSel->At(k);

		for (int i = tmptextSel->len - 1; i >= 0; i--) {
			RectD rect = tmptextSel->rects[i].Convert<double>();
			sel->Append(SelectionOnPage2(tmptextSel->Color,tmptextSel->Text,tmptextSel->pages[i], &rect));
		}

	}
	sel->Reverse();

	if (sel->Count() == 0) {
		delete sel;
		return NULL;
	}
	return sel;
}

void DeleteOldSelectionInfo2(WindowInfo2 *win2, bool alsoTextSel)
{
	delete win2->selectionOnPage2;
	win2->selectionOnPage2 = NULL;
	win2->showSelection2 = false;

	if (alsoTextSel && win2->IsDocLoaded())
	{
		DisplayModel2* dm2 = reinterpret_cast<DisplayModel2*> (win2->dm);
		TextSelection2* ts2 = reinterpret_cast<TextSelection2*> (dm2->textSearch2);
		ts2->Reset();		
	}
}

void PaintTransparentRectangles2(HDC hdc, RectI screenRc, Vec<RectI2>& rects, BYTE alpha, int margin)
{
	using namespace Gdiplus;

	screenRc.Inflate(margin, margin);
	for (size_t i = 0; i < rects.Count(); i++) {
		GraphicsPath path(FillModeWinding);
		RectI rc = rects.At(i).rect.Intersect(screenRc);
		if (!rc.IsEmpty())
			path.AddRectangle(rc.ToGdipRect());

		LONG selectionColor = rects.At(i).Color;
		// fill path (and draw optional outline margin)
		Graphics gs(hdc);
		Color c(alpha, GetRValue(selectionColor), GetGValue(selectionColor), GetBValue(selectionColor));
		SolidBrush tmpBrush(c);
		gs.FillPath(&tmpBrush, &path);
		if (margin) {
			path.Outline(NULL, 0.2f);
			Pen tmpPen(Color(alpha, 0, 0, 0), (REAL)margin);
			gs.DrawPath(&tmpPen, &path);
		}
	}
}

void PaintSelection2(WindowInfo *win, HDC hdc)
{
	Vec<RectI2> rects;
	WindowInfo2 * win2 = reinterpret_cast<WindowInfo2*> (win);

	for (size_t i = 0; i < win2->selectionOnPage2->Count(); i++)
		rects.Append(win2->selectionOnPage2->At(i).GetRect2(win->dm));


	PaintTransparentRectangles2(hdc, win->canvasRc, rects);
}

void UpdateTextSelection2(WindowInfo *win, Vec<TextSel2*> *result, bool select)
{
	WindowInfo2 * win2 = reinterpret_cast <WindowInfo2*> (win);
	assert(win->IsDocLoaded());
	if (!win->IsDocLoaded()) return;

	if (select) {
		int pageNo = win->dm->GetPageNoByPoint(win->selectionRect.BR());
		if (win->dm->ValidPageNo(pageNo)) {
			PointD pt = win->dm->CvtFromScreen(win->selectionRect.BR(), pageNo);
			win->dm->textSelection->SelectUpTo(pageNo, pt.x, pt.y);
		}
	}

	DeleteOldSelectionInfo2(win2);
	win2->selectionOnPage2 = SelectionOnPage2::FromTextSelect2(result);
	win2->showSelection2 = win2->selectionOnPage2 != NULL;

	if (win->uia_provider)
		win->uia_provider->OnSelectionChanged();
}