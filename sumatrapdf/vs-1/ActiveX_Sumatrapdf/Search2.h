#ifndef Search2_h
#define Search2_h

#include "TextSearch.h"

class WindowInfo;

void AbortFinding2(WindowInfo *win, bool hideMessage);
int  FindTextOnThread2(WindowInfo* win, LPCTSTR word, LONG color = 0,bool Whole = true ,bool Cur = false ,int page = 1,TextSearchDirection direction=FIND_FORWARD, bool FAYT=false);
int  OnSearchWord(WindowInfo *win,LPCTSTR word,LONG color = 0,bool Whole = true ,bool Cur = false ,int page = 1);
void OnClearSearchWord(WindowInfo *win,LPCTSTR word);

#endif