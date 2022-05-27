#include "H01_Application.h"

GDATA mGDATA;
GDATA::GDATA( void )
{
}

BOOL GDATA::Init( void )
{
	int i = 0, j = 0, k = 0;
	
	for ( i = 0; i < MAX_GIMAGE2D_UI_MAIN_NUM; i++ )
	{
		mUI_MAIN[i].Init( 1, i, 0 );
	}

	return TRUE;
}

void GDATA::Free( void )
{
}
