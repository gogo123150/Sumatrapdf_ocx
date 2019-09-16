
#include "Search.cpp"
#include "Search2.h"
#include "TextSearch2.h"
#include "Selection2.h"
#include "DisplayModel2.h"
#include "WindowInfo2.h"

class FindThreadData2 :public FindThreadData
{	
public:
	FindThreadData2(WindowInfo& win, TextSearchDirection direction, WCHAR* str,LONG color,bool Whole,bool Cur,int page) :
	FindThreadData(win,direction,NULL),Color(color),whole(Whole),bcur(Cur),pageNo(page) {
		text.Set(str::Dup(str));
		wasModified = false;
	}

	LONG Color;
	bool whole; //whether search whole document
	bool bcur;  //if whole == false and bcur ,then search the current page.
	LONG pageNo;

};

class FindEndTask2 : public UITask {
	FindThreadData2 *ftd;
	Vec<TextSel2*> *textSel;
	ScopedHandle    thread;
	bool    wasModifiedCanceled;
	bool    loopedAround;
	WindowInfo *win;

public:
	FindEndTask2(WindowInfo *win, FindThreadData2 *ftd, Vec<TextSel2*> *textSel,
		bool wasModifiedCanceled, bool loopedAround=false) :
	win(win), ftd(ftd), textSel(textSel),
		thread(win->findThread), // close the find thread handle after execution
		loopedAround(loopedAround), wasModifiedCanceled(wasModifiedCanceled) { }
	~FindEndTask2() { 
		delete ftd; }

	virtual void Execute() {
		if (!WindowInfoStillValid(win))
			return;
		if (win->findThread != thread) {
			// Race condition: FindTextOnThread/AbortFinding was
			// called after the previous find thread ended but
			// before this FindEndTask could be executed
			return;
		}
		if (!win->IsDocLoaded()) {
			// the UI has already been disabled and hidden
		} else if (textSel) {
			UpdateTextSelection2(win,textSel, false);
			//win->dm->ShowResultRectToScreen(textSel);
			win->RepaintAsync();
		} else {
			// nothing found or search canceled
			DeleteOldSelectionInfo(win, true);
			win->RepaintAsync();
		}
		win->findThread = NULL;
	}
};

static DWORD WINAPI FindThread2(LPVOID data)
{
	FindThreadData2 *ftd = (FindThreadData2 *)data;
	assert(ftd && ftd->win && ftd->win->dm);
	WindowInfo *win = ftd->win;

	WindowInfo2 * win2 = reinterpret_cast<WindowInfo2*> (win);
	DisplayModel2* dm2 = reinterpret_cast<DisplayModel2*> (win->dm);
	TextSearch2* pts = dm2->textSearch2;
	pts->SetDirection(ftd->direction);
	
	//Vec<TextSel2*> *rect = pts->FindWholeTextInPage(ftd->text,ftd->Color,win->dm->CurrentPageNo());
	Vec<TextSel2*> *rect = NULL;
	if(ftd->whole)
		rect = pts->SearchText(ftd->text,ftd->Color);
	else if(ftd->bcur)
		rect = pts->SearchText(ftd->text,ftd->Color,false,win->dm->CurrentPageNo());
	else
		rect = pts->SearchText(ftd->text,ftd->Color,false,ftd->pageNo);

	bool loopedAround = false;

	// wait for FindTextOnThread to return so that
	// FindEndTask closes the correct handle to
	// the current find thread
	while (!win2->findThread2)
		Sleep(1);

	if (!win2->findCanceled2 && rect)
		uitask::Post(new FindEndTask2(win, ftd, rect, ftd->wasModified, loopedAround));
	else
		uitask::Post(new FindEndTask2(win, ftd, NULL, win2->findCanceled2));

	return 0;
}

void AbortFinding2(WindowInfo *win, bool hideMessage)
{
	WindowInfo2 * win2 = reinterpret_cast<WindowInfo2*> (win);
	if (win2->findThread2) {
		win2->findCanceled2 = true;
		WaitForSingleObject(win2->findThread2, INFINITE);
	}
	win2->findCanceled2 = false;

	if (hideMessage)
		win2->notifications->RemoveAllInGroup(NG_FIND_PROGRESS);
}

int FindTextOnThread2(WindowInfo* win, LPCTSTR word,LONG color,bool Whole,bool Cur,int page,TextSearchDirection direction, bool FAYT)
{
	WindowInfo2 * win2 = reinterpret_cast<WindowInfo2*> (win);
	AbortFinding2(win, true);
	
	WCHAR * wsInfo = NULL;
#ifdef  UNICODE 
	wsInfo = (WCHAR*)word;	
#else
	wsInfo = str::ToWideChar(word,0);	
#endif
	FindThreadData2 *ftd = new FindThreadData2(*win, direction, wsInfo,color,Whole,Cur,page);

	if (str::IsEmpty(ftd->text.Get())) {
		delete ftd;
		return -1;
	}

	win2->findThread2 = NULL;
	win2->findThread2 = CreateThread(NULL, 0, FindThread2, ftd, 0, 0);

	if (win2->findThread2) {
		//win2->findCanceled2 = true;
		WaitForSingleObject(win2->findThread2, INFINITE);
	}

	DisplayModel2* dm2 = reinterpret_cast<DisplayModel2*> (win->dm);
	TextSearch2* pts = dm2->textSearch2;
	return pts->GetSearchWordCount(wsInfo);
}

int OnSearchWord(WindowInfo *win,LPCTSTR word,LONG color,bool Whole  ,bool Cur ,int page)
{
	if (!win->IsDocLoaded() || !NeedsFindUI(win))
		return -1;

	WindowInfo2* win2 = reinterpret_cast<WindowInfo2*>(win);

	return FindTextOnThread2(win, word, color,Whole,Cur,page);	
}

void OnClearSearchWord(WindowInfo *win,LPCTSTR word)
{
	if (!win->IsDocLoaded() || !NeedsFindUI(win))
		return;

	WindowInfo2 * win2 = reinterpret_cast<WindowInfo2*> (win);
	DisplayModel2* dm2 = reinterpret_cast<DisplayModel2*> (win->dm);
	TextSearch2* pts = dm2->textSearch2;

	AbortFinding2(win, true);

#ifdef  UNICODE 
	pts->RemoveSearchWord(word);
#else
	WCHAR * wsInfo = str::ToWideChar(word,0);
	pts->RemoveSearchWord(wsInfo);
#endif

	UpdateTextSelection2(win,&pts->ResultVec, false);
	win->RepaintAsync();

}