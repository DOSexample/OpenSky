#include "H01_Application.h"

//-------------------------------------------------------------------------------------------------
//CLASS_OF_FONTDATA
//-------------------------------------------------------------------------------------------------
//INSTANCE
FONTDATA mFONTDATA;
//CREATE
FONTDATA::FONTDATA( void )
{
	mPath[0] = '\0';
}
//INIT
BOOL FONTDATA::Init( void )
{
	char tPath[MAX_PATH];

	//local font .ttf
	strcpy( tPath, "G01_GFONT\\TS2.FONT" );
	if( PathFileExists( tPath ) == FALSE )
	{
		return FALSE;
	}
	if( AddFontResource( tPath ) == 0 )
	{
		return FALSE;
	}
	strcpy( mPath, tPath );
	return TRUE;
}
//FREE
void FONTDATA::Free( void )
{
	if( strcmp( mPath, "" ) == 0 )
	{
		return;
	}
	RemoveFontResource( mPath );
	mPath[0] = '\0';
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_POINTER
//-------------------------------------------------------------------------------------------------
//INSTANCE
POINTER mPOINTER;
//CREATE
POINTER::POINTER( void )
{
	int index01;

	mDataIndex = 0;
	for( index01 = 0 ; index01 < MAX_POINTER_NUM ; index01++ )
	{
		mDATA[index01] = NULL;
	}
}
//INIT
BOOL POINTER::Init( void )
{
	int index01;

	mDataIndex = 0;
	mDATA[0] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR01 ) );
	mDATA[1] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR02 ) );
	mDATA[2] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR03 ) );
	mDATA[3] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR04 ) );
	mDATA[4] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR05 ) );
	mDATA[5] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR06 ) );
	mDATA[6] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR07 ) );
	mDATA[7] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR08 ) );
	mDATA[8] = LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR09 ) );
	for( index01 = 0 ; index01 < MAX_POINTER_NUM ; index01++ )
	{
		if( mDATA[index01] == NULL )
		{
			return FALSE;
		}
	}
	return TRUE;
}
//FREE
void POINTER::Free( void )
{
	int index01;

	mDataIndex = 0;
	for( index01 = 0 ; index01 < MAX_POINTER_NUM ; index01++ )
	{
		if( mDATA[index01] )
		{
			DestroyCursor( mDATA[index01] );
			mDATA[index01] = NULL;
		}
	}
}
//SET
void POINTER::Set( int tDataIndex )
{
	if( ( tDataIndex < 0 ) || ( tDataIndex > ( MAX_POINTER_NUM - 1 ) ) )
	{
		return;
	}
	mDataIndex = tDataIndex;
}
//SET
void POINTER::Set( void )
{
	SetCursor( mDATA[mDataIndex] );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_FONTCOLOR
//-------------------------------------------------------------------------------------------------
//INSTANCE
FONTCOLOR mFONTCOLOR;
//CREATE
FONTCOLOR::FONTCOLOR( void )
{
}
//INIT
BOOL FONTCOLOR::Init( void )
{
	mDataNum = MAX_FONTCOLOR_NUM;
	mDataNum2 = MAX_FONTCOLOR_NUM2;
	mData[ 0] = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	mData[ 1] = D3DCOLOR_RGBA( 255,   0,   0, 255 );
	mData[ 2] = D3DCOLOR_RGBA( 255, 255,   0, 255 );
	mData[ 3] = D3DCOLOR_RGBA(   0,   0, 255, 255 );
	mData[ 4] = D3DCOLOR_RGBA( 198, 184, 148, 255 );
	mData[ 5] = D3DCOLOR_RGBA( 144, 178, 129, 255 );
	mData[ 6] = D3DCOLOR_RGBA( 208, 192,  93, 255 );
	mData[ 7] = D3DCOLOR_RGBA( 118, 220,  69, 255 );
	mData[ 8] = D3DCOLOR_RGBA( 141, 207, 244, 255 );
	mData[ 9] = D3DCOLOR_RGBA( 137, 202, 157, 255 );
	mData[10] = D3DCOLOR_RGBA( 137, 153, 112, 255 );
	mData[11] = D3DCOLOR_RGBA( 216, 187, 149, 255 );
	mData[12] = D3DCOLOR_RGBA( 139, 191,  56, 255 );
	mData[13] = D3DCOLOR_RGBA( 172, 167, 159, 255 );
	mData[14] = D3DCOLOR_RGBA( 168, 164,   0, 255 );
	mData[15] = D3DCOLOR_RGBA(   0, 105,  63, 255 );
	mData[16] = D3DCOLOR_RGBA(   0, 109, 105, 255 );
	mData[17] = D3DCOLOR_RGBA(   0,  68, 119, 255 );
	mData[18] = D3DCOLOR_RGBA(  38,   7,  81, 255 );
	mData[19] = D3DCOLOR_RGBA( 109,   0,  38, 255 );
	mData[20] = D3DCOLOR_RGBA( 203, 185, 156, 255 );
	mData[21] = D3DCOLOR_RGBA( 237, 237, 237, 255 );
	mData[22] = D3DCOLOR_RGBA(  91,  55,  20, 255 );
	mData[23] = D3DCOLOR_RGBA( 209, 156,  43, 255 );
	mData[24] = D3DCOLOR_RGBA( 140,  56, 143, 255 );
	mData[25] = D3DCOLOR_RGBA( 249, 158, 108, 255 );
	mData[26] = D3DCOLOR_RGBA( 153, 153, 204, 255 );
	mData[27] = D3DCOLOR_RGBA( 166, 213, 157, 255 );
	mData[28] = D3DCOLOR_RGBA( 140, 230, 145, 255 );
	mData[29] = D3DCOLOR_RGBA(  63, 187, 239, 255 );
	mData[30] = D3DCOLOR_RGBA( 217, 217, 217, 255 );
	mData[31] = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	mData[32] = D3DCOLOR_RGBA( 146, 208,  80, 255 );
	mData[33] = D3DCOLOR_RGBA( 247, 150,  70, 255 );
	mData[34] = D3DCOLOR_RGBA(   0, 112, 192, 255 );
	mData[35] = D3DCOLOR_RGBA( 112,  48, 160, 255 );
	mData[36] = D3DCOLOR_RGBA( 255, 255,   0, 255 );
	mData[37] = D3DCOLOR_RGBA( 255, 102, 255, 255 );
	mData[38] = D3DCOLOR_RGBA( 141, 179, 226, 255 );
	mData[39] = D3DCOLOR_RGBA(  53, 224, 255, 255 );
	mData[40] = D3DCOLOR_RGBA(  51, 216, 153, 255 );
	mData[41] = D3DCOLOR_RGBA( 230, 163, 234, 255 );
	mData[42] = D3DCOLOR_RGBA( 221, 196, 160, 255 );
	mData[43] = D3DCOLOR_RGBA( 170, 170, 170, 255 );
	mDataSys[0] = D3DCOLOR_RGBA( 0, 0, 15, 0 );
	mDataSys[1] = D3DCOLOR_RGBA( 0, 0,  1, 0 );
	mDataSys[2] = D3DCOLOR_RGBA( 0, 0, 40, 0 );
	mDataSys[3] = D3DCOLOR_RGBA( 0, 0, 39, 0 );
	mDataSys[4] = D3DCOLOR_RGBA( 0, 0, 36, 0 );
	mDataSys[5] = D3DCOLOR_RGBA( 0, 0, 37, 0 );
	mDataSys[6] = D3DCOLOR_RGBA( 0, 0, 38, 0 );


	return TRUE;
}
//FREE
void FONTCOLOR::Free( void )
{
}
//RETURN
D3DCOLOR FONTCOLOR::Return( int tDataNumber )
{
	if( ( tDataNumber < 1 ) || ( tDataNumber > mDataNum ) )
	{
		return D3DCOLOR_RGBA( 0, 0, 0, 255 );
	}
	return mData[( tDataNumber - 1 )];
}
//RETURN_SYS_COLOR
D3DCOLOR FONTCOLOR::ReturnSys( int tDataNumber )
{
	if( ( tDataNumber < 1 ) || ( tDataNumber > mDataNum2 ) )
	{
		return D3DCOLOR_RGBA( 0, 0, 0, 255 );
	}
	return mDataSys[( tDataNumber - 1 )];
}
//-------------------------------------------------------------------------------------------------
