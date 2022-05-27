#include "H01_Application.h"
#include "test_sobject.h"

BOOL test_sobject::Load( void )
{
	if( mCheckValidState )
		return TRUE;
	if( !mDATA.Load( mFileName, TRUE ) )
		return FALSE;
	mCheckValidState = TRUE;
	return TRUE;
}

void test_sobject::Draw( int tDrawSort, float tFrame, float tCoord[3], float tYAngle, float tHeightForCulling, test_motion* tMOTION )
{
	if( !tMOTION || !Load() ) return;

	TW2AddIn::MOTION2_FOR_GXD* tMotionPtr = tMOTION->GetMotionPointer();
	if( !tMotionPtr ) return;

	float tAngle[3] = { 0, tYAngle, 0 };
	float tScale[3] = { 1, 1, 1 };

	hRenderSobject25 = TRUE;
	mDATA.Draw( tHeightForCulling, tScale, tCoord, tAngle, tDrawSort, tMotionPtr, tFrame, NULL, NULL, NULL );
}

void test_sobject::GetSObjectCoord( int tSkinIndex, float tReturnCoord[3], float tFrame, float tCoord[3], float tYAngle, test_motion* tMOTION )
{
	if( !tMOTION || !Load() ) return;

	TW2AddIn::MOTION2_FOR_GXD* tMotionPtr = tMOTION->GetMotionPointer();
	if( !tMotionPtr ) return;
	
	float tAngle[3] = { 0, tYAngle, 0 };
	float tScale[3] = { 1, 1, 1 };
	mDATA.GetSkinCoord( tSkinIndex, tScale, tCoord, tAngle, tMotionPtr, tFrame, tReturnCoord );
}




#include "String.h"


test_motion tmot;
test_sobject tsob;
#include <vector>
std::vector<test_sobject*> tsob2;
void test_sobject_func()
{
	if ( !tsob.mCheckInitState )
	{
		//init motion file to load
		tmot.Init( "G03_GDATA\\D03_GMOTION\\001\\C001001002.MOTION" );
		//init sobject file to load
		//2.5 folder
		//001 - 005, 007 - 010
		tsob.Init( "G03_GDATA\\D04_GSOBJECT\\001\\C001003035.SOBJECT" );//body

		//hair
		tsob2.push_back( new test_sobject() );
		tsob2[0]->Init( "G03_GDATA\\D04_GSOBJECT\\001\\C001001002.SOBJECT" );

		//face
		tsob2.push_back( new test_sobject() );
		tsob2[1]->Init( "G03_GDATA\\D04_GSOBJECT\\001\\C001002001.SOBJECT" );
		
		//foot
		tsob2.push_back( new test_sobject() );
		tsob2[2]->Init( "G03_GDATA\\D04_GSOBJECT\\001\\C001004035.SOBJECT" );
	}

	if ( tmot.Load() && tsob.Load() )
	{
		float tFrame = GetNewFrame( tmot.GetTotalFrameNum() );
		float tCoord[3] = { 0,0,0 };
		float tAngle[3] = { 0,0,0 };

		tsob.Draw( 1, tFrame, tCoord, tAngle[1], 20.0f, &tmot );
		tsob.Draw( 2, tFrame, tCoord, tAngle[1], 20.0f, &tmot );

		for (int i = 0; i < (int)tsob2.size(); i++ ) {
			tsob2[i]->Draw( 1, tFrame, tCoord, tAngle[1], 20.0f, &tmot );
			tsob2[i]->Draw( 2, tFrame, tCoord, tAngle[1], 20.0f, &tmot );
		}
	}
}

