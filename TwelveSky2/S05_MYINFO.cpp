#include "H01_Application.h"

MYINFO mMYINFO;
MYINFO::MYINFO( void )
{
}

BOOL MYINFO::Init( void )
{
    return TRUE;
}

void MYINFO::Free( void )
{
}

void MYINFO::AdjustScreenCoord( int tUINum, int sX, int sY, int *tX, int *tY )
{
    int sImgX = mGDATA.mUI_MAIN[tUINum].GetXSize() / 2;
    int sImgY = mGDATA.mUI_MAIN[tUINum].GetXSize() / 2;
    *tX = int( float( mScreenXSize * ( sX + sImgX ) ) / mScreenXPosSize ) - ( sImgX );
    *tY = int( float( mScreenYSize * ( sY + sImgY ) ) / mScreenYPosSize ) - ( sImgY );
}