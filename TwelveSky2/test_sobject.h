#pragma once

#include <TW2AddIn/Header.h>
#include "test_object.h"
#include "test_motion.h"

//2.5 sobject
class test_sobject : public test_object<TW2AddIn::SOBJECT2_FOR_GXD>
{

public:

	virtual BOOL Load( void );

	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tYAngle, float tHeightForCulling, test_motion* tMOTION );

	void GetSObjectCoord( int tSkinIndex, float tReturnCoord[3], float tFrame, float tCoord[3], float tYAngle, test_motion* tMOTION );
};


extern void test_sobject_func();
