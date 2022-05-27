#pragma once

#include <GXD/Header.h>
#include "test_object.h"

class test_mobject : public test_object<MOBJECT_FOR_GXD>
{
public:

	virtual BOOL Load( void );
	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], BOOL tLocalClient );
	int GetTotalFrameNum();
};

extern void test_mobject_func();
extern void test_mobject_sobject_func();

