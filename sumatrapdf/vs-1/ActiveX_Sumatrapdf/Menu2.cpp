#include "BaseUtil.h"
#include "Menu.h"

#include "AppPrefs.h"
#include "CmdLineParser.h"
#include "DisplayModel.h"
#include "EbookWindow.h"
#include "ExternalPdfViewer.h"
#include "Favorites.h"
#include "FileUtil.h"
#include "FileHistory.h"
#include "Selection.h"
#include "SumatraAbout.h"
#include "SumatraDialogs.h"
#include "SumatraPDF.h"
#include "Translations.h"
#include "WindowInfo.h"
#include "WinUtil.h"

// the whole menu is MF_NOT_FOR_CHM | MF_NOT_FOR_EBOOK_UI
static MenuDef menuDefContext2[] = {
	{ _TRN("&Copy Selection"),              IDM_COPY_SELECTION,         MF_REQ_ALLOW_COPY },
	{ _TRN("Copy &Link Address"),           IDM_COPY_LINK_TARGET,       MF_REQ_ALLOW_COPY },
	{ _TRN("Copy Co&mment"),                IDM_COPY_COMMENT,           MF_REQ_ALLOW_COPY },
	{ _TRN("Copy &Image"),                  IDM_COPY_IMAGE,             MF_REQ_ALLOW_COPY },
	{ SEP_ITEM,                             0,                          MF_REQ_ALLOW_COPY },
	{ _TRN("Select &All"),                  IDM_SELECT_ALL,             MF_REQ_ALLOW_COPY },
	{ SEP_ITEM,                             0,                          MF_PLUGIN_MODE_ONLY | MF_REQ_ALLOW_COPY },
	{ _TRN("Show &Bookmarks"),              IDM_VIEW_BOOKMARKS,         MF_PLUGIN_MODE_ONLY },
	{ _TRN("P&roperties"),                  IDM_PROPERTIES,             MF_PLUGIN_MODE_ONLY },
};

void OnContextMenu2(WindowInfo* win, int x, int y)
{
	assert(win->IsDocLoaded());
	if (!win->IsDocLoaded())
		return;

	PageElement *pageEl = win->dm->GetElementAtPos(PointI(x, y));
	ScopedMem<WCHAR> value(pageEl ? pageEl->GetValue() : NULL);
	CrashIf(value && !pageEl);
	RenderedBitmap *bmp = NULL;

	HMENU popup = BuildMenuFromMenuDef(menuDefContext2, dimof(menuDefContext2), CreatePopupMenu());
	if (!value || pageEl->GetType() != Element_Link)
		win::menu::Remove(popup, IDM_COPY_LINK_TARGET);
	if (!value || pageEl->GetType() != Element_Comment)
		win::menu::Remove(popup, IDM_COPY_COMMENT);
	if (!pageEl || pageEl->GetType() != Element_Image)
		win::menu::Remove(popup, IDM_COPY_IMAGE);

	if (!win->selectionOnPage)
		win::menu::SetEnabled(popup, IDM_COPY_SELECTION, false);
	//MenuUpdatePrintItem(win, popup, true);
	win::menu::SetEnabled(popup, IDM_VIEW_BOOKMARKS, win->dm->HasTocTree());
	win::menu::SetChecked(popup, IDM_VIEW_BOOKMARKS, win->tocVisible);

	POINT pt = { x, y };
	MapWindowPoints(win->hwndCanvas, HWND_DESKTOP, &pt, 1);
	INT cmd = TrackPopupMenu(popup, TPM_RETURNCMD | TPM_RIGHTBUTTON,
		pt.x, pt.y, 0, win->hwndFrame, NULL);
	switch (cmd) {
	case IDM_COPY_SELECTION:
	case IDM_SELECT_ALL:
	case IDM_VIEW_BOOKMARKS:
	case IDM_PROPERTIES:
		SendMessage(win->hwndFrame, WM_COMMAND, cmd, 0);
		break;

	case IDM_COPY_LINK_TARGET:
	case IDM_COPY_COMMENT:
		CopyTextToClipboard(value);
		break;

	case IDM_COPY_IMAGE:
		if (pageEl) {
			bmp = pageEl->GetImage();
			if (bmp)
				CopyImageToClipboard(bmp->GetBitmap());
			delete bmp;
		}
		break;
	}

	DestroyMenu(popup);
	delete pageEl;
}
