#pragma once

//-------------------------------------------------------------------------------------------------
//CLASS_OF_FONTDATA
//-------------------------------------------------------------------------------------------------
//DEFINE
class FONTDATA
{

private :

	char mPath[MAX_PATH];

public :

	FONTDATA( void );

	BOOL Init( void );
	void Free( void );

};
//INSTANCE
extern FONTDATA mFONTDATA;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_POINTER
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_POINTER_NUM												9
//DEFINE
class POINTER
{

public :

	int mDataIndex;
	HCURSOR mDATA[MAX_POINTER_NUM];

	POINTER( void );

	BOOL Init( void );
	void Free( void );

	void Set( int tDataIndex );
	void Set( void );

};
//INSTANCE
extern POINTER mPOINTER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_FONTCOLOR
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_FONTCOLOR_NUM											120
#define MAX_FONTCOLOR_NUM2											7
//DEFINE
class FONTCOLOR
{

private :

	int mDataNum;
	int mDataNum2;
	D3DCOLOR mData[MAX_FONTCOLOR_NUM];
	D3DCOLOR mDataSys[MAX_FONTCOLOR_NUM2];

public :

	FONTCOLOR( void );

	BOOL Init( void );
	void Free( void );

	D3DCOLOR Return( int tDataNumber );
	D3DCOLOR ReturnSys( int tDataNumber );

};
//INSTANCE
extern FONTCOLOR mFONTCOLOR;
//-------------------------------------------------------------------------------------------------




