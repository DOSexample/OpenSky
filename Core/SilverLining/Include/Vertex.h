// Copyright (c) 2009 Sundog Software, LLC All rights reserved worldwide.

#ifndef VERTEX_H
#define VERTEX_H

#include "Color.h"

// Comment this out to save memory if you know you'll never use HDR mode.
#define FLOATING_POINT_COLOR

namespace SilverLining
{

/** A single vertex containing a position, RGBA color, and 3D texture coordinates. */
class Vertex
{
public:
float x, y, z;
#ifdef FLOATING_POINT_COLOR
float r, g, b, a;
#else
unsigned int color;
#endif
float u, v, t;

/** Sets the 4-byte color of the vertex in the manner expected by the underlying Renderer,
   based on the 0-255 RGBA values provided. */
void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

/** Sets the u,v texture coordinates of the vertex in the manner expected by the
   underlying Renderer, based on the uv coordinates provided. The r texture coordinate
   is set to 0. */
void SetUV(float u, float v);

/** Sets the 4-byte color of the vertex in the manner expected by the underlying Renderer,
   based on the Color provided. */
void SetColor(const Color& c);
};

}

#endif
