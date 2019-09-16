#include "BaseUtil.h"
#include "TextSearch2.h"

enum { SEARCH_PAGE, SKIP_PAGE };

#define SkipWhitespace(c) for (; str::IsWs(*(c)); (c)++)
// ignore spaces between CJK glyphs but not between Latin, Greek, Cyrillic, etc. letters
// cf. http://code.google.com/p/sumatrapdf/issues/detail?id=959
#define isnoncjkwordchar(c) (iswordchar(c) && (unsigned short)(c) < 0x2E80)

TextSearch2::TextSearch2(BaseEngine *engine, PageTextCache *textCache) :
    TextSelection2(engine, textCache),
    findText(NULL), anchor(NULL), pageText(NULL),
    caseSensitive(false), forward(true),
    matchWordStart(false), matchWordEnd(false),
    findPage(0), findIndex(0), lastText(NULL)
{
    findCache = AllocArray<BYTE>(this->engine->PageCount());
}

TextSearch2::~TextSearch2()
{
    Clear();
    free(findCache);
}

void TextSearch2::Reset()
{
    pageText = NULL;
    //TextSelection2::Reset();
}

void TextSearch2::SetText(const WCHAR *text)
{
    // search text starting with a single space enables the 'Match word start'
    // and search text ending in a single space enables the 'Match word end' option
    // (that behavior already "kind of" exists without special treatment, but
    // usually is not quite what a user expects, so let's try to be cleverer)
    this->matchWordStart = text[0] == ' ' && text[1] != ' ';
    this->matchWordEnd = str::EndsWith(text, L" ") && !str::EndsWith(text, L"  ");

    if (text[0] == ' ')
        text++;

    // don't reset anything if the search text hasn't changed at all
    if (str::Eq(this->lastText, text))
        return;

    this->Clear();
    this->lastText = str::Dup(text);
    this->findText = str::Dup(text);
	result->Text = str::Dup(text);

    // extract anchor string (the first word or the first symbol) for faster searching
    if (isnoncjkwordchar(*text)) {
        const WCHAR *end;
        for (end = text; isnoncjkwordchar(*end); end++)
            ;
        anchor = str::DupN(text, end - text);
    }
    // Adobe Reader also matches certain hard-to-type Unicode
    // characters when searching for easy-to-type homoglyphs
    // cf. http://forums.fofou.org/sumatrapdf/topic?id=2432337
    else if (*text == '-' || *text == '\'' || *text == '"')
        anchor = NULL;
    else
        anchor = str::DupN(text, 1);

    if (str::EndsWith(this->findText, L" "))
        this->findText[str::Len(this->findText) - 1] = '\0';

    memset(this->findCache, SEARCH_PAGE, this->engine->PageCount());
}

void TextSearch2::SetSensitive(bool sensitive)
{
    if (caseSensitive == sensitive)
        return;
    this->caseSensitive = sensitive;

    memset(this->findCache, SEARCH_PAGE, this->engine->PageCount());
}

void TextSearch2::SetDirection(TextSearchDirection direction)
{
    bool forward = FIND_FORWARD == direction;
    if (forward == this->forward)
        return;
    this->forward = forward;
    if (findText)
        findIndex += (int)str::Len(findText) * (forward ? 1 : -1);
}

//void TextSearch2::SetLastResult(TextSelection2 *sel)
//{
//    CopySelection(sel);
//
//    ScopedMem<WCHAR> selection(ExtractText(L" "));
//    str::NormalizeWS(selection);
//    SetText(selection);
//
//    findPage = min(startPage, endPage);
//    findIndex = (findPage == startPage ? startGlyph : endGlyph) + str::Len(findText);
//    pageText = textCache->GetData(findPage);
//    forward = true;
//}

// try to match "findText" from "start" with whitespace tolerance
// (ignore all whitespace except after alphanumeric characters)
int TextSearch2::MatchLen(const WCHAR *start) const
{
    const WCHAR *match = findText, *end = start;

    if (matchWordStart && start > pageText && iswordchar(start[-1]) && iswordchar(start[0]))
        return -1;

    if (!match)
        return -1;

    while (*match) {
        if (!*end)
            return -1;
        if (caseSensitive ? *match == *end : CharLower((LPWSTR)LOWORD(*match)) == CharLower((LPWSTR)LOWORD(*end)))
            /* characters are identical */;
        else if (str::IsWs(*match) && str::IsWs(*end))
            /* treat all whitespace as identical */;
        // TODO: Adobe Reader seems to have a more extensive list of
        //       normalizations - is there an easier way?
        else if (*match == '-' && (0x2010 <= *end && *end <= 0x2014))
            /* make HYPHEN-MINUS also match HYPHEN, NON-BREAKING HYPHEN,
               FIGURE DASH, EN DASH and EM DASH (but not the other way around) */;
        else if (*match == '\'' && (0x2018 <= *end && *end <= 0x201b))
            /* make APOSTROPHE also match LEFT/RIGHT SINGLE QUOTATION MARK */;
        else if (*match == '"' && (0x201c <= *end && *end <= 0x201f))
            /* make QUOTATION MARK also match LEFT/RIGHT DOUBLE QUOTATION MARK */;
        else
            return -1;
        match++;
        end++;
        // treat "??" and "? ?" differently, since '?' could have been a word
        // character that's just missing an encoding (and '?' is the replacement
        // character); cf. http://code.google.com/p/sumatrapdf/issues/detail?id=1574
        if (*match && !isnoncjkwordchar(*(match - 1)) && (*(match - 1) != '?' || *match != '?') ||
            str::IsWs(*(match - 1)) && str::IsWs(*(end - 1))) {
            SkipWhitespace(match);
            SkipWhitespace(end);
        }
    }

    if (matchWordEnd && end > pageText && iswordchar(end[-1]) && iswordchar(end[0]))
        return -1;

    return (int)(end - start);
}

static const WCHAR *GetNextIndex(const WCHAR *base, int offset, bool forward)
{
    const WCHAR *c = base + offset + (forward ? 0 : -1);
    if (c < base || !*c)
        return NULL;
    return c;
}

bool TextSearch2::FindTextInPage(int pageNo)
{
    if (str::IsEmpty(findText))
        return false;
    if (!pageNo)
        pageNo = findPage;
    findPage = pageNo;

    const WCHAR *found;
    int length;
    do {
        if (!anchor)
            found = GetNextIndex(pageText, findIndex, forward);
        else if (forward)
            found = (caseSensitive ? StrStr : StrStrI)(pageText + findIndex, anchor);
        else
            found = StrRStrI(pageText, pageText + findIndex, anchor);
        if (!found)
            return false;
        findIndex = (int)(found - pageText) + (forward ? 1 : 0);
        length = MatchLen(found);
    } while (length <= 0);

    int offset = (int)(found - pageText);
    StartAt(pageNo, offset);
    SelectUpTo(pageNo, offset + length);
    findIndex = offset + (forward ? length : 0);

    // try again if the found text is completely outside the page's mediabox
    if (result->len == 0)
        return FindTextInPage(pageNo);

    return true;
}

bool TextSearch2::FindStartingAtPage(int pageNo, ProgressUpdateUI *tracker)
{
    if (str::IsEmpty(findText))
        return false;

    int total = engine->PageCount();
    while (1 <= pageNo && pageNo <= total && (!tracker || !tracker->WasCanceled())) {
        if (tracker)
            tracker->UpdateProgress(pageNo, total);

        if (SKIP_PAGE == findCache[pageNo - 1]) {
            pageNo += forward ? 1 : -1;
            continue;
        }

        Reset();

        pageText = textCache->GetData(pageNo, &findIndex);
        if (pageText) {
            if (forward)
                findIndex = 0;
            if (FindTextInPage(pageNo))
                return true;
            findCache[pageNo - 1] = SKIP_PAGE;
        }

        pageNo += forward ? 1 : -1;
    }

    // allow for the first/last page to be included in the next search
    findPage = forward ? total + 1 : 0;

    return false;
}

//TextSel *TextSearch2::FindFirst(int page, const WCHAR *text, ProgressUpdateUI *tracker)
//{
//    SetText(text);
//
//    if (FindStartingAtPage(page, tracker))
//        return &result;
//    return NULL;
//}
//
//TextSel *TextSearch2::FindNext(ProgressUpdateUI *tracker)
//{
//    CrashIf(!findText);
//    if (!findText)
//        return NULL;
//
//    if (tracker) {
//        if (tracker->WasCanceled())
//            return NULL;
//        tracker->UpdateProgress(findPage, engine->PageCount());
//    }
//
//    if (FindTextInPage())
//        return &result;
//    if (FindStartingAtPage(findPage + (forward ? 1 : -1), tracker))
//        return &result;
//    return NULL;
//}

Vec<TextSel2*> *TextSearch2::FindWholeTextInPage(const WCHAR *text,LONG color,int pageNo)
{
	for(ULONG i = 0;i < ResultVec.Count();i++)
	{
		TextSel2* tmpresult = ResultVec.At(i);
		if(tmpresult && str::EqI(text,tmpresult->Text) && tmpresult->len > 0 && *tmpresult->pages == pageNo )
		{
			tmpresult->Color = color;
			return &ResultVec;
		}
	}
	
	result = new TextSel2();
	result->Color = color;
	SetText(text);
	
	if(!FindStartingAtPage(pageNo, NULL))
	{
		ResetResult(result);
		delete result;
		result = NULL;
		return NULL;
	}

	while(FindTextInPage(pageNo));
	
	ResultVec.Append(result);

	return &ResultVec;
}


Vec<TextSel2*> *TextSearch2::SearchText(const WCHAR *text,LONG color,bool whole,  int pageNo)
{
	Reset();

	for(ULONG i = 0;i < ResultVec.Count();i++)
	{
		TextSel2* tmpresult = ResultVec.At(i);
		if(tmpresult && str::EqI(text,tmpresult->Text) && tmpresult->len > 0 )//&& *tmpresult->pages == pageNo )
		{
			if(tmpresult->whole == whole && (whole == true ||*tmpresult->pages == pageNo ))
			{
				tmpresult->Color = color;
				return &ResultVec;
			}
			
			ResultVec.RemoveAt(i);
			ResetResult(tmpresult);
			delete tmpresult;
			tmpresult = NULL;
			break;
		}
	}

	result = new TextSel2();
	result->Color = color;
	SetText(text);


	/*if (str::IsEmpty(findText))
	return false;*/
	if(whole)
	{
		int total = engine->PageCount();

		// allow for the first/last page to be included in the search
		findPage = forward ? total + 1 : 0;

		
		while (1 <= pageNo && pageNo <= total  )
		{
			/*if (SKIP_PAGE == findCache[pageNo - 1]) {
				pageNo += forward ? 1 : -1;
				continue;
			}*/		

			pageText = textCache->GetData(pageNo, &findIndex);
			if (pageText) {
				if (forward)
					findIndex = 0;

				//int cnt = result->len;

				while(FindTextInPage(pageNo));


				/*if(cnt == result->len)
					findCache[pageNo - 1] = SKIP_PAGE;*/
			}

			pageNo += forward ? 1 : -1;
		}
	}
	else
	{
		pageText = textCache->GetData(pageNo, &findIndex);
		if (pageText) {
			if (forward)
				findIndex = 0;

			while(FindTextInPage(pageNo));
		}
	}

	/*if(!FindStartingAtPage(pageNo, NULL))
	{
	ResetResult(result);
	delete result;
	result = NULL;
	return NULL;
	}

	while(FindTextInPage(pageNo));*/

	ResultVec.Append(result);

	return &ResultVec;

}

void TextSearch2::RemoveSearchWord(const WCHAR *text)
{
	for(ULONG i = 0;i < ResultVec.Count();i++)
	{
		TextSel2* tmpresult = ResultVec.At(i);
		if(tmpresult && str::EqI(text,tmpresult->Text) && tmpresult->len > 0 )
		{
			ResultVec.RemoveAt(i);
			ResetResult(tmpresult);
			delete tmpresult;
			tmpresult = NULL;
			break;
		}
	}
}

LONG TextSearch2::GetSearchWordCount(const WCHAR *text)
{
	for(ULONG i = 0;i < ResultVec.Count();i++)
	{
		TextSel2* tmpresult = ResultVec.At(i);
		if(tmpresult && str::EqI(text,tmpresult->Text) && tmpresult->len > 0 )
		{
			return tmpresult->len;
		}
	}

	return 0;
}