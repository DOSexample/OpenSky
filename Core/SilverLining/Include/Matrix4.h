// Copyright (c) 2004-2008  Sundog Software, LLC All rights reserved worldwide.

/**
    \file Matrix4.h
    \brief An implementation of a 4x4 matrix and some simple operations on it.
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector4.h"

namespace SilverLining
{
/** An implementation of a 4x4 matrix and some simple operations on it. */
class Matrix4
{
public:
/** Default constructor; initializes the matrix to an identity transform. */
Matrix4()
{
    elem[0][0] = 1;
    elem[0][1] = 0;
    elem[0][2] = 0;
    elem[0][3] = 0;
    elem[1][0] = 0;
    elem[1][1] = 1;
    elem[1][2] = 0;
    elem[1][3] = 0;
    elem[2][0] = 0;
    elem[2][1] = 0;
    elem[2][2] = 1;
    elem[2][3] = 0;
    elem[3][0] = 0;
    elem[3][1] = 0;
    elem[3][2] = 0;
    elem[3][3] = 1;
}

/** This constructor allows you to initialize the matrix as you please. */
Matrix4(double e11, double e12, double e13, double e14,
        double e21, double e22, double e23, double e24,
        double e31, double e32, double e33, double e34,
        double e41, double e42, double e43, double e44)
{
    elem[0][0] = e11;
    elem[0][1] = e12;
    elem[0][2] = e13;
    elem[0][3] = e14;
    elem[1][0] = e21;
    elem[1][1] = e22;
    elem[1][2] = e23;
    elem[1][3] = e24;
    elem[2][0] = e31;
    elem[2][1] = e32;
    elem[2][2] = e33;
    elem[2][3] = e34;
    elem[3][0] = e41;
    elem[3][1] = e42;
    elem[3][2] = e43;
    elem[3][3] = e44;
}

/** Initializes the matrix from an array of 16 double-precision values (row-major). */
Matrix4(double *m)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            elem[row][col] = *m++;
        }
    }
}

/** Destructor. */
~Matrix4() {
}

/** Multiplies two matrices together. */
Matrix4 operator * (const Matrix4& mat) const;

/** Transform a point by the matrix. */
Vector4 operator * (const Vector4& vec) const;

/** Transform a point by the matrix. */
Vector3 operator * (const Vector3& vec) const;

/** Multiplies a 1x3 vector by a matrix, yielding a 1x3 vector. */
friend Vector4 operator * (const Vector4& vec, const Matrix4& mat);

/** Transposes the matrix in-place. */
void Transpose()
{
    Matrix4 m = *this;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            elem[row][col] = m.elem[col][row];
        }
    }
}

/** Retrieves a pointer into the requested row of the matrix. */
double *GetRow(int row)
{
    if (row < 4)
    {
        return elem[row];
    }
    else
    {
        return 0;
    }
}

/// Data members are public for convenience.
double elem[4][4];
};
}

#endif