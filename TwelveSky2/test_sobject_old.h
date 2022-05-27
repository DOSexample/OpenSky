#pragma once

#include <GXD/Header.h>
#include "test_object.h"
#include "test_motion.h"

//2.0 sobject | Weapon Enchant Effect | Wing Enchant Effect
class test_sobject_old : public test_object<SOBJECT_FOR_GXD>
{

public:

	virtual BOOL Load( void );

	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tYAngle, float tHeightForCulling, test_motion* tMOTION );

};


extern void test_sobject_old_func();
