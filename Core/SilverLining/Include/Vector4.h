// Copyright (c) 2004-2008  Sundog Software, LLC. All rights reserved worldwide.

/**
    \file Vector4.h
    \brief A simple 4D vector class.
 */

#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"

namespace SilverLining
{
/** A simple double-precision 4D vector class with no operations defined.
   Essentially a struct with constructors. */
class Vector4
{
public:
/** Constructs a Vector4 from the given x, y, z, and w values. */
Vector4(double px, double py, double pz, double pw) : x(px), y(py), z(pz), w(pw) {
}

/** Constructs a Vector4 from a Vector3, setting w to 1. */
Vector4(const Vector3& v3) : x(v3.x), y(v3.y), z(v3.z), w(1.0) {
}

/** Default constructor; initializes the Vector4 to (0, 0, 0, 1) */
Vector4() : x(0), y(0), z(0), w(1.0) {
}

/** The x, y, z, and w data members are public for convenience. */
double x, y, z, w;
};
}

#endif