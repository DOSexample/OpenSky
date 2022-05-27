#pragma once

#include <TW2AddIn/Header.h>

#include "test_object.h"

class test_motion : public test_object<TW2AddIn::MOTION2_FOR_GXD>
{
public:

	virtual BOOL Load( void );
	int GetTotalFrameNum( void );

	TW2AddIn::MOTION2_FOR_GXD* GetMotionPointer( void );
};

