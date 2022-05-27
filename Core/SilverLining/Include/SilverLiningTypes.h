// Copyright (c) 2009 Sundog Software, LLC. All rights reserved worldwide.

#ifndef SILVERLINING_TYPES_H
#define SILVERLINING_TYPES_H

// Change these if you want to integrate with your own memory manager.
#define SL_NEW new
#define SL_DELETE delete
#define SL_MALLOC malloc
#define SL_FREE free

/** Types of shaders, either a vertex or a fragment shader. */
enum ShaderTypes
{
    VERTEX_PROGRAM,
    FRAGMENT_PROGRAM
};

/** Blend modes for blending equation coefficients. */
enum BlendFactors
{
    ZERO,
    ONE,
    SRCCOLOR,
    INVSRCCOLOR,
    SRCALPHA,
    INVSRCALPHA,
    DSTCOLOR,
    INVDSTCOLOR,
    DSTALPHA,
    INVDSTALPHA,
    SRCALPHASAT,
    NUM_BLEND_FACTORS
};

namespace SilverLining
{
typedef unsigned short Index;
typedef void * IndexBufferHandle;
typedef void * VertexBufferHandle;
typedef void * ShaderHandle;
typedef void * TextureHandle;
typedef void * RenderTextureHandle;
typedef void * RenderTargetHandle;
typedef void * QueryHandle;
}

#endif
