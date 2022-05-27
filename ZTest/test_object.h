#pragma once

template<typename T>
class test_object
{
public:

	test_object( void )
	{
		mCheckValidState = FALSE;
		mCheckInitState = FALSE;
		mFileName[0] = '\0';
	}
	~test_object( void )
	{
		Free();
	}

	BOOL mCheckValidState;
	BOOL mCheckInitState;
	char mFileName[100];
	T mDATA;
	
	void Init( char* tFileName )
	{
		mCheckInitState = TRUE;
		mCheckValidState = FALSE;
		mDATA.Init();
		sprintf( mFileName, "%s", tFileName );
	}

	void Free( void )
	{
		mCheckValidState = FALSE;
		mDATA.Free();
	}

	BOOL Load( void )
	{
		return FALSE;
	}
};
