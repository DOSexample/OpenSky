#include "H01_Application.h"

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GIMAGE2D
//-------------------------------------------------------------------------------------------------
//CREATE
GIMAGE2D::GIMAGE2D( void )
{
	mCheckValidState = FALSE;
	mDATA.Init();
}
//INIT
void GIMAGE2D::Init( int tValue01, int tValue02, int tValue03 )
{
    switch ( tValue01 )
    {
    case 1:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\001\\001_%05d.IMG", tValue02 + 1 );
        break;
    case 2:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\002\\002_%05d.IMG", tValue02 + 1 );
        break;
    case 3:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\003\\003_%05d.IMG", tValue02 + 1 );
        break;
    case 4:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\004\\004_%05d.IMG", tValue02 + 1 );
        break;
    case 5:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\006\\006_%05d.IMG", tValue02 + 1 );
        break;
    case 6:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\007\\007_%03d%03d.IMG", tValue02 + 1, tValue03 + 1 );
        break;
    case 7:
        sprintf( mFileName, "G03_GDATA\\D01_GIMAGE2D\\008\\008_%05d.IMG", tValue02 + 1 );
        break;
    default:
        strcpy( mFileName, "" );
        break;
    }
}
//FREE
void GIMAGE2D::Free( void )
{
	mCheckValidState = FALSE;
	mDATA.Free();
}
//LOAD
BOOL GIMAGE2D::Load( void )
{
	TCHAR strFileExp[10] = {0,};

	if( mCheckValidState )
	{
		return TRUE;
	}
    if( !mDATA.Load( mFileName ) )
	{
		return FALSE;
	}
	mCheckValidState = TRUE;
	return TRUE;
}
//PROCESS_FOR_MEMORY
void GIMAGE2D::ProcessForMemory( float tPresentTime, float tValidTimeLength )
{
	if( !mCheckValidState )
	{
		return;
	}
	if( ( tPresentTime - mLastUsedTime ) > tValidTimeLength )
	{
		Free();
	}
}
//DISPLAY
void GIMAGE2D::Display( int sX, int sY )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	mDATA.Draw( sX, sY, FALSE, 0, 0, 0, 0 );
}
//DISPLAY
void GIMAGE2D::Display( int sX, int sY, WORD iX, WORD iY, WORD lX, WORD lY )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	mDATA.Draw( sX, sY, TRUE, iX, iY, lX, lY );
}
//DISPLAY
void GIMAGE2D::Display( int sX, int sY, float tScaleX, float tScaleY )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	mDATA.Draw( sX, sY, tScaleX, tScaleY );
}
//CHECK_IN
BOOL GIMAGE2D::CheckIn( int sX, int sY, int mX, int mY )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return FALSE;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	if( ( mX >= sX ) && ( mX < ( sX + (int) mDATA.mTextureInfo.Width ) ) && ( mY >= sY ) && ( mY < ( sY + (int) mDATA.mTextureInfo.Height ) ) )
	{
		return TRUE;
	}
	return FALSE;
}
//CHECK_IN
BOOL GIMAGE2D::CheckIn( int sX, int sY, int mWidth, int mHeight, int mX, int mY )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return FALSE;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	if( ( mX >= sX ) && ( mX < ( sX + mWidth ) ) && ( mY >= sY ) && ( mY < ( sY + mHeight ) ) )
	{
		return TRUE;
	}
	return FALSE;
}
//GET_X_SIZE
WORD GIMAGE2D::GetXSize( void )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return 0;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	return mDATA.mTextureInfo.Width;
}
//GET_Y_SIZE
WORD GIMAGE2D::GetYSize( void )
{
	if( !mCheckValidState )
	{
		if( !Load() )
		{
			return 0;
		}
		mCheckValidState = TRUE;
	}
	mLastUsedTime = hPresentElapsedSeconds;
	return mDATA.mTextureInfo.Height;
}
//-------------------------------------------------------------------------------------------------
