#ifndef WindowInfo2_h
#define WindowInfo2_h

#include "WindowInfo.h"
#include "Selection2.h"

class WindowInfo2 : public WindowInfo
{
public:
	WindowInfo2(HWND hwnd):WindowInfo(hwnd),selectionOnPage2(NULL),showSelection2(false),findThread2(NULL), findCanceled2(false){}
	~WindowInfo2();

	//LONG            selectioncolor;
	bool            showSelection2;

    /* selection rectangle in screen coordinates
     * while selecting, it represents area which is being selected */
   // RectI           selectionRect2;

	/* after selection is done, the selected area is converted
     * to user coordinates for each page which has not empty intersection with it */
    Vec<SelectionOnPage2> *selectionOnPage2;

	HANDLE          findThread2;
	bool            findCanceled2;
};

#endif