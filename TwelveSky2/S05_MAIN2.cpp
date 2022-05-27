#include "H01_Application.h"

void MAIN::Logic2( float dTime )
{
	if( mSubMode == 0 && ++mTicks >= 30 )
	{
		if (rand() % 2)
			mGroupBG = 2381;
		else
			mGroupBG = 2380;

		mSubMode = 1;
		mTicks = 0;
	}
}

#include <CString.h>
void MAIN::Draw2( float dTime )
{
    POINT Point;
    mGXD.BeginFor2D();
    GetCursorPos(&Point);
    ScreenToClient( hMainWindow, &Point );
    int mX = Point.x;
    int mY = Point.y;
    float sx2 = (float)mMYINFO.mScreenXSize / mMYINFO.mScreenXPosSize;
    float sy2 = (float)mMYINFO.mScreenYSize / mMYINFO.mScreenYPosSize;
    OutputDebugStringA( CString("").Sprintf( "scaleX=%f\n", sx2 ) );
    OutputDebugStringA( CString("").Sprintf( "scaleY=%f\n", sy2 ) );
    mGDATA.mUI_MAIN[mGroupBG].Display( 0, 0, sx2, sy2 );
    int hx2 = mMYINFO.mScreenXSize / 2;
    int hy2 = mMYINFO.mScreenYSize / 2;
    int sX = hx2 - mGDATA.mUI_MAIN[1785].GetXSize() / 2;
    int sY = hy2 - mGDATA.mUI_MAIN[1785].GetYSize() / 2;
    mGDATA.mUI_MAIN[1785].Display( sX, sY );
    mGXD.EndFor2D();
}

void MAIN::LBUTTONDOWN2( int mX, int mY )
{
}

void MAIN::LBUTTONUP2( int mX, int mY )
{
}

void MAIN::RBUTTONDOWN2( int mX, int mY )
{
}

void MAIN::RBUTTONUP2( int mX, int mY )
{
}

void MAIN::KEYBOARD2( void )
{
}