#include "H01_Application.h"
#include "test_mobject.h"

BOOL test_mobject::Load()
{
	if( mCheckValidState )
		return TRUE;
	if( !mDATA.Load( mFileName, TRUE, TRUE ) )
		return FALSE;
	mCheckValidState = TRUE;
	return TRUE;
}

void test_mobject::Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], BOOL tLocalClient )
{
	if ( Load() )
	{
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
		mDATA.Draw( tDrawSort, tFrame, tCoord, tAngle, 0.0f, NULL, TRUE, 0 );
	}
}

int test_mobject::GetTotalFrameNum()
{
	if( Load() )
		return mDATA.mMesh->mFrameNum;
	return 0;
}









test_mobject tmob;
void test_mobject_func()
{
	if ( !tmob.mCheckInitState )
	{
		tmob.Init( "G03_GDATA\\D02_GMOBJECT\\003\\E202001.MOBJECT" );
	}

	float tFrame = GetNewFrame( tmob.GetTotalFrameNum() );
	float tCoord[3] = { -20,10,0 };
	float tAngle[3] = { 0,0,0 };

	tmob.Draw( 1, tFrame, tCoord, tAngle, TRUE );
	tmob.Draw( 2, tFrame, tCoord, tAngle, TRUE );
}

#include "String.h"

#include "test_motion.h"
#include "test_sobject.h"
extern test_motion tmot;
test_sobject tsob_coord;
void test_mobject_sobject_func()
{
	if ( !tsob_coord.mCheckInitState )
	{
		tsob_coord.Init( "G03_GDATA\\D04_GSOBJECT\\001\\C001009001.SOBJECT" );
	}
	if ( tmob.mCheckValidState && tmot.mCheckValidState && tsob_coord.Load() )
	{
		float tFrame = GetNewFrame( tmob.GetTotalFrameNum() );
		float tCoord[3] = { 0,0,0 };
		float tAngle[3] = { 0,0,0 };
		float tReturnCoord[3] = { 0,0,0 };
		
		//found: use for monster
		//tsob_coord.GetSObjectCoord( 1, tReturnCoord, tFrame, tCoord, tAngle[1], &tmot );
		//left coord, for marble, scepter
		//tsob_coord.GetSObjectCoord( 2, tReturnCoord, tFrame, tCoord, tAngle[1], &tmot );
		//right coord, for marble, scepter
		//tsob_coord.GetSObjectCoord( 3, tReturnCoord, tFrame, tCoord, tAngle[1], &tmot );
		//center coord, for halo, set effect
		tsob_coord.GetSObjectCoord( 4, tReturnCoord, tFrame, tCoord, tAngle[1], &tmot );

		tmob.Draw( 1, tFrame, tReturnCoord, tAngle, TRUE );
		tmob.Draw( 2, tFrame, tReturnCoord, tAngle, TRUE );
	}
}


