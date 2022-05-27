#pragma once

#include <d3dx9.h>


inline D3DXVECTOR3* WINAPI D3DXVec3Normalize( D3DVECTOR *pOut, CONST D3DVECTOR*pV )
{
    return ::D3DXVec3Normalize( (D3DXVECTOR3*)pOut, (D3DXVECTOR3*)pV );
}

inline D3DXVECTOR3* WINAPI D3DXVec3TransformCoord( D3DXVECTOR3 *pOut, CONST float *pV, CONST D3DXMATRIX *pM )
{
    return ::D3DXVec3TransformCoord( pOut, (D3DXVECTOR3*)pV, pM );
}

inline D3DXVECTOR3* WINAPI D3DXVec3TransformCoord( float *pOut, CONST float *pV, CONST D3DXMATRIX *pM )
{
    return ::D3DXVec3TransformCoord( (D3DXVECTOR3*)pOut, (D3DXVECTOR3*)pV, pM );
}

inline D3DXVECTOR3* WINAPI D3DXVec3TransformCoord( float *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM )
{
    return ::D3DXVec3TransformCoord( (D3DXVECTOR3*)pOut, (D3DXVECTOR3*)pV, pM );
}

inline D3DXVECTOR3* WINAPI D3DXVec3TransformNormal( float *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM )
{
    return ::D3DXVec3TransformNormal( (D3DXVECTOR3*)pOut, pV, pM );
}

inline D3DXVECTOR3* WINAPI D3DXVec3TransformNormal( float *pOut, CONST float *pV, CONST D3DXMATRIX *pM )
{
    return ::D3DXVec3TransformNormal( (D3DXVECTOR3*)pOut, (D3DXVECTOR3*)pV, pM );
}
