#ifndef Toolbar2_h
#define Toolbar2_h

class WindowInfo;

void CreateToolbar2(WindowInfo *win);
void ToolbarUpdateStateForWindow2(WindowInfo *win, bool showHide);
void UpdateToolbarButtonsToolTipsForWindow2(WindowInfo *win);
void UpdateToolbarFindText2(WindowInfo *win);
void UpdateToolbarPageText2(WindowInfo *win, int pageCount, bool updateOnly=false);
void UpdateFindbox2(WindowInfo* win);
void ShowOrHideToolbarGlobally2();
//void UpdateToolbarState2(WindowInfo *win);

#endif
