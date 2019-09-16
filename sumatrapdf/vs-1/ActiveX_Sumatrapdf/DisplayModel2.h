#ifndef DisplayModel2_h
#define DisplayModel2_h

#include "DisplayModel.h"
#include "TextSearch2.h"

class DisplayModel2:public DisplayModel
{
public:
	TextSearch2 *    textSearch2;

	DisplayModel2(BaseEngine *engine, DocType engineType, DisplayModelCallback *dmCb):DisplayModel(engine,engineType,dmCb){
		textSearch2 = new TextSearch2(engine, textCache);
	}

	DisplayModel2::~DisplayModel2()
	{
		delete textSearch2;
	}
};

#endif