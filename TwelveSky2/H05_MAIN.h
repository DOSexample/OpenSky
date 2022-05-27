#pragma once

#define MAX_MAIN_MODE_NUM           6
#define MAX_MAIN_CLICK_NUM          150
class MAIN
{
public:
    int mMainMode;
    int mSubMode;
    DWORD mTicks;
    BOOL bIsClick[MAX_MAIN_CLICK_NUM];
    SOUNDDATA_FOR_GXD mSOUND;

    int mGroupBG;

public:

    MAIN();
    
    BOOL Init( void );
    void Free( void );
    void Start( void );
    void Reset( void );
    void Logic( float dTime );
    void Draw( float dTime );
    void LBUTTONDOWN( int mX, int mY );
    void LBUTTONUP( int mX, int mY );
    void RBUTTONDOWN( int mX, int mY );
    void RBUTTONUP( int mX, int mY );
    void KEYBOARD( void );

    
    void Logic1( float dTime );
    void Draw1( float dTime );    
    void LBUTTONDOWN1( int mX, int mY );
    void LBUTTONUP1( int mX, int mY );
    void RBUTTONDOWN1( int mX, int mY );
    void RBUTTONUP1( int mX, int mY );
    void KEYBOARD1( void );
    

    void Logic2( float dTime );
    void Draw2( float dTime );    
    void LBUTTONDOWN2( int mX, int mY );
    void LBUTTONUP2( int mX, int mY );
    void RBUTTONDOWN2( int mX, int mY );
    void RBUTTONUP2( int mX, int mY );
    void KEYBOARD2( void );

    
    void Logic3( float dTime );
    void Draw3( float dTime );    
    void LBUTTONDOWN3( int mX, int mY );
    void LBUTTONUP3( int mX, int mY );
    void RBUTTONDOWN3( int mX, int mY );
    void RBUTTONUP3( int mX, int mY );
    void KEYBOARD3( void );

    void Logic4( float dTime );
    void Draw4( float dTime );    
    void LBUTTONDOWN4( int mX, int mY );
    void LBUTTONUP4( int mX, int mY );
    void RBUTTONDOWN4( int mX, int mY );
    void RBUTTONUP4( int mX, int mY );
    void KEYBOARD4( void );
    

    void Logic5( float dTime );
    void Draw5( float dTime );    
    void LBUTTONDOWN5( int mX, int mY );
    void LBUTTONUP5( int mX, int mY );
    void RBUTTONDOWN5( int mX, int mY );
    void RBUTTONUP5( int mX, int mY );
    void KEYBOARD5( void );

    
    void Logic6( float dTime );
    void Draw6( float dTime );    
    void LBUTTONDOWN6( int mX, int mY );
    void LBUTTONUP6( int mX, int mY );
    void RBUTTONDOWN6( int mX, int mY );
    void RBUTTONUP6( int mX, int mY );
    void KEYBOARD6( void );
};

extern MAIN mMAIN;


#define MAX_USER_ID_LENGTH                  14
#define MAX_USER_PW_LENGTH                  33
class MYINFO
{
public:

    float mScreenXPosSize;
    float mScreenYPosSize;
    int mScreenSort;
    int mScreenXSize;
    int mScreenYSize;


    char uID[MAX_USER_ID_LENGTH];
    char uPW[MAX_USER_PW_LENGTH];



public:







    MYINFO( void );

    BOOL Init( void );
    void Free( void );

    void AdjustScreenCoord( int tUINum, int sX, int sY, int *tX, int *tY );
};

extern MYINFO mMYINFO;