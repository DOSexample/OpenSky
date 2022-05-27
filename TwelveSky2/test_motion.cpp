#include "H01_Application.h"
#include "test_motion.h"

BOOL test_motion::Load( void )
{
	if( mCheckValidState )
		return TRUE;
	if( !mDATA.Load( mFileName, TRUE ) )
		return FALSE;
	mCheckValidState = TRUE;
	return TRUE;
}

int test_motion::GetTotalFrameNum( void )
{
	if( Load() )
		return mDATA.mFrameNum;
	return 0;
}

TW2AddIn::MOTION2_FOR_GXD* test_motion::GetMotionPointer( void )
{
	if ( Load() )
	{
		return &mDATA;
	}

	return NULL;
}







