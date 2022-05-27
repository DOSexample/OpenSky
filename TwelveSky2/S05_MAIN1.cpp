#include "H01_Application.h"

void MAIN::Logic1( float dTime )
{
    if ( mSubMode == 0 )
    {
        //if ( ++mTicks >= 90 )
        {
            Reset();
            mSubMode = 1;
            mTicks = 0;
        }
    }
    else if ( mSubMode >= 1 && mSubMode <= 33 )
    {
        if ( ++mTicks >= 3 )
        {
            mSubMode++;
            mTicks = 0;
        }
    }
    else if ( mSubMode == 34 )
    {
        if ( ++mTicks >= 90 )
        {
            mMainMode = 2;
            mSubMode = 0;
            mTicks = 0;
        }
    }
}

void MAIN::Draw1( float dTime )
{
    mGXD.BeginFor2D();
    if ( mSubMode > 0 )
    {
        int load = mSubMode + 797;
        if ( load > 830 )
            load = 830;
        int x = mMYINFO.mScreenXSize / 2;
        int y = mMYINFO.mScreenYSize / 2;
        int sX = x - mGDATA.mUI_MAIN[load].GetXSize() / 2;
        int sY = y - mGDATA.mUI_MAIN[load].GetYSize() / 2;
        mGDATA.mUI_MAIN[load].Display( sX, sY );
    }
    mGXD.EndFor2D();
}

void MAIN::LBUTTONDOWN1( int mX, int mY )
{
}

void MAIN::LBUTTONUP1( int mX, int mY )
{
}

void MAIN::RBUTTONDOWN1( int mX, int mY )
{
}

void MAIN::RBUTTONUP1( int mX, int mY )
{
}

void MAIN::KEYBOARD1( void )
{
}