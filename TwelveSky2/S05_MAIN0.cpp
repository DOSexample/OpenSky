#include "H01_Application.h"

MAIN mMAIN;

MAIN::MAIN()
{
}

BOOL MAIN::Init( void )
{
    mMainMode = 0;
    mSubMode = 0;
    mTicks = 0;
    Reset();
    //mLoginType = 1;
    mSOUND.Init();
    return 1;
}

void MAIN::Free( void )
{
    mSOUND.Free();
}

void MAIN::Start( void )
{
    //UTIL::AdjustViewEnvironment1();
    mMainMode = 1;
    mSubMode = 0;
    mTicks = 0;
    Reset();
    mSOUND.Free();
}

void MAIN::Reset( void )
{
    int i;

    mPOINTER.Set(0);
    //EDITBOX::Set(0);
    for ( i = 0; i < MAX_MAIN_CLICK_NUM; i++ )
        bIsClick[i] = FALSE;
}

void MAIN::Logic( float dTime )
{
    switch ( mMainMode )
    {
    case 1:
        Logic1( dTime );
        break;
    case 2:
        if ( mSubMode == 0 && ++mTicks < 25 )
        {
            mTicks = 25;
        }
        Logic2( dTime );
        break;
    case 3:
        Logic3( dTime );
        break;
    case 4:
        Logic4( dTime );
        break;
    case 5:
        Logic5( dTime );
        break;
    case 6:
        Logic6( dTime );
        //CInnerAuto::Update();//update auto hunt
        break;
    }
}

void MAIN::Draw( float dTime )
{
    switch ( mMainMode )
    {
    case 1:
        Draw1( dTime );
        break;
    case 2:
        Draw2( dTime );
        break;
    case 3:
        Draw3( dTime );
        break;
    case 4:
        Draw4( dTime );
        break;
    case 5:
        Draw5( dTime );
        break;
    case 6:
        Draw6( dTime );
        break;
    }
}

void MAIN::LBUTTONDOWN( int mX, int mY )
{
    switch ( mMainMode )
    {
    case 2:
        LBUTTONDOWN2( mX, mY );
        break;
    case 3:
        LBUTTONDOWN3( mX, mY );
        break;
    case 4:
        LBUTTONDOWN4( mX, mY );
        break;
    case 6:
        LBUTTONDOWN6( mX, mY );
        break;
    }
}

void MAIN::LBUTTONUP( int mX, int mY )
{
    switch ( mMainMode )
    {
    case 2:
        LBUTTONUP2( mX, mY );
        break;
    case 3:
        LBUTTONUP3( mX, mY );
        break;
    case 4:
        LBUTTONUP4( mX, mY );
        break;
    case 6:
        LBUTTONUP6( mX, mY );
        break;
    }
}

void MAIN::RBUTTONDOWN( int mX, int mY )
{
    switch ( mMainMode )
    {
    case 6:
        RBUTTONDOWN6( mX, mY );
        break;
    }
}

void MAIN::RBUTTONUP( int mX, int mY )
{
    switch ( mMainMode )
    {
    case 6:
        RBUTTONUP6( mX, mY );
        break;
    }
}

void MAIN::KEYBOARD( void )
{
    switch ( mMainMode )
    {
    case 6:
        KEYBOARD6();
        break;
    }
}
