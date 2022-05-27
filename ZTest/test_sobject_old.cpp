#include "H01_Application.h"
#include "test_sobject_old.h"

MOTION_FOR_GXD motion1;
BOOL test_sobject_old::Load( void )
{
	if( mCheckValidState )
		return TRUE;
	if( !mDATA.Load( mFileName, TRUE, TRUE ) )
		return FALSE;
	mCheckValidState = TRUE;
	return TRUE;
}

void test_sobject_old::Draw( int tDrawSort, float tFrame, float tCoord[3], float tYAngle, float tHeightForCulling, test_motion* tMOTION )
{
	if( !tMOTION || !Load() ) return;

	TW2AddIn::MOTION2_FOR_GXD* tMotionPtr = tMOTION->GetMotionPointer();
	if( !tMotionPtr ) return;

	float tAngle[3] = { 0, tYAngle, 0 };

	tMotionPtr->GetMotion1VoidPtr(&motion1);

	if ( hRenderSobject25 )
	{
		mGXD.mGraphicDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );
		mGXD.mGraphicDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		mGXD.mGraphicDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		if ( TW2AddIn::mGXD.mPresentShaderProgramNumber )
		{
			TW2AddIn::mGXD.mPresentShaderProgramNumber = 0;
			TW2AddIn::mGXD.mGraphicDevice->SetVertexShader( 0 );
			TW2AddIn::mGXD.mGraphicDevice->SetPixelShader( 0 );
		}
		hRenderSobject25 = FALSE;
	}
	mDATA.Draw( tDrawSort, tFrame, tCoord, tAngle, 0.0f, NULL, TRUE, &motion1, tHeightForCulling, FALSE, NULL, FALSE );
}



#include "String.h"

extern test_motion tmot;
test_sobject_old tsob_old;
float tSOAngle[3] = { 90,90,0 };
void test_sobject_old_func()
{
	if ( !tsob_old.mCheckInitState )
	{
		//init motion file to load
		tmot.Init( "G03_GDATA\\D03_GMOTION\\001\\C001001002.MOTION" );
		//init sobject file to load
		//2.5 folder
		//006 only
		tsob_old.Init( "G03_GDATA\\D04_GSOBJECT\\006\\W001004015009.SOBJECT" );
	}

	if ( tmot.Load() && tsob_old.Load() )
	{
		float tFrame = GetNewFrame( tmot.GetTotalFrameNum() );
		float tCoord[3] = { 10,0,0 };

		tSOAngle[1] += 1.5;
		if( tSOAngle[1] > 360.0f )
			tSOAngle[1] = 0.0f;

		tsob_old.Draw( 1, tFrame, tCoord, tSOAngle[1], 20.0f, &tmot );
		tsob_old.Draw( 2, tFrame, tCoord, tSOAngle[1], 20.0f, &tmot );
	}
}

