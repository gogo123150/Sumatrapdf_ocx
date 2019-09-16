#ifndef TextSearch2_h
#define TextSearch2_h

#include <windows.h>
#include "TextSelection2.h"
#include "TextSearch.h"

class TextSearch2 : public TextSelection2
{
public:
	TextSearch2(BaseEngine *engine, PageTextCache *textCache);
	~TextSearch2();

	void SetSensitive(bool sensitive);
	void SetDirection(TextSearchDirection direction);
	//void SetLastResult(TextSelection2 *sel);
	//TextSel *FindFirst(int page, const WCHAR *text, ProgressUpdateUI *tracker=NULL);
	//TextSel *FindNext(ProgressUpdateUI *tracker=NULL);

	// note: the result might not be a valid page number!
	int GetCurrentPageNo() const { return findPage; }

	Vec<TextSel2*> *FindWholeTextInPage(const WCHAR *text,LONG color,int pageNo = 0);

	Vec<TextSel2*> *SearchText(const WCHAR *text,LONG color,bool whole = true,  int pageNo = 1);

	void RemoveSearchWord(const WCHAR *text);

	LONG GetSearchWordCount(const WCHAR *text);

protected:
	WCHAR *findText;
	WCHAR *anchor;
	int findPage;
	bool forward;
	bool caseSensitive;
	// these two options are implicitly set when the search text begins
	// resp. ends in a single space (many users already search that way),
	// combining them yields a 'Whole words' search
	bool matchWordStart;
	bool matchWordEnd;

	void SetText(const WCHAR *text);
	bool FindTextInPage(int pageNo = 0);
	bool FindStartingAtPage(int pageNo, ProgressUpdateUI *tracker);
	int MatchLen(const WCHAR *start) const;

	void Clear()
	{
		str::ReplacePtr(&findText, NULL);
		str::ReplacePtr(&anchor, NULL);
		str::ReplacePtr(&lastText, NULL);
		Reset();
	}
	void Reset();

private:
	const WCHAR *pageText;
	int findIndex;

	WCHAR *lastText;
	BYTE *findCache;
};

#endif