// Copyright (c) 2004-2008  Sundog Software, LLC. All rights reserved worldwide.

/**
    \file Color.h
    \brief A class that defines an RGBA color and operations on it.
 */

#ifndef COLOR_H
#define COLOR_H

#include "Atmosphere.h"
#include <stdio.h>
#include <iostream>

namespace SilverLining
{
/** A RGBA color, where each component is represented as a float from 0-1. */
class Color
{
public:
/** Default constructor, initializes to black with no translucency. */
Color() : r(0), g(0), b(0), a(1) {
}

/** Constructor that takes in RGBA single-precision values that range from 0-1. */
Color(float red, float green, float blue, float alpha) : r(red), g(green),
    b(blue), a(alpha) {
}

/** Constructor that takes in RGB single-precision values that range from 0-1.
   The alpha component is assumed to be 1.0. */
Color(float red, float green, float blue) : r(red), g(green), b(blue), a(1) {
}

/** Constructor that takes in RGBA double-precision values that range from 0-1. */
Color(double red, double green, double blue, double alpha) : r((float)red),
    g((float)green), b((float)blue), a((float)alpha) {
}

/** Constructor that takes in RGB double-precision values that range from 0-1.
   The alpha component is assumed to be 1.0. */
Color(double red, double green, double blue) : r((float)red), g((float)green),
    b((float)blue), a(1.0f) {
}

/** Constructor that takes in RGBA integer values that range from 0-1. */
Color(int red, int green, int blue, int alpha) : r((float)red),
    g((float)green), b((float)blue), a((float)alpha) {
}

/** Constructor that takes in RGB integer values that range from 0-1.
   The alpha component is assumed to be 1.0. */
Color(int red, int green, int blue) : r((float)red), g((float)green),
    b((float)blue), a(1.0f) {
}

/** Multiplication operator; multiplies each rgb component of the Color by a constant. */
Color operator * (float f) const {
    return (Color(r*f, g*f, b*f, a));
}

/** Multiplication operator; multiplies two Colors together on a per-component basis. */
Color operator * (const Color& c) const {
    return (Color(r*c.r, g*c.g, b*c.b, a*c.a));
}

/** Addition operator; adds two colors together on a per-component basis. */
Color operator + (const Color& c) const {
    return (Color(r + c.r, g + c.g, b + c.b, a + c.a));
}

/** If any component of the Color exceeds 1.0, every component will be scaled down
   uniformly such that the maximum color component equals 1.0. */
void ScaleToUnitOrLess() {
    if (!Atmosphere::GetHDREnabled())
    {
        float minC = 0;
        if (r < minC) minC = r;
        if (g < minC) minC = g;
        if (b < minC) minC = b;
        minC = -minC;

        r += minC;
        g += minC;
        b += minC;

        float maxC = r;
        if (g > maxC) maxC = g;
        if (b > maxC) maxC = b;
        if (maxC > 1.0) {
            r /= maxC;
            g /= maxC;
            b /= maxC;
        }
    }
}

/** Clamps each color component to be within the range [0, 1.0]. */
void ClampToUnitOrLess() {
    if (!Atmosphere::GetHDREnabled())
    {
        if (r > 1.0) r = 1.0;
        if (g > 1.0) g = 1.0;
        if (b > 1.0) b = 1.0;
        if (a > 1.0) a = 1.0;

        if (r < 0.0) r = 0.0;
        if (g < 0.0) g = 0.0;
        if (b < 0.0) b = 0.0;
        if (a < 0.0) a = 0.0;
    }
}

/** Convert the RGB color to a grayscale value. */
Color ToGrayscale() const {
    float gray = r * 0.299f + g * 0.587f + b * 0.114f;
    return Color(gray, gray, gray);
}

/** Save this color to disk. */
void Serialize(std::ostream& s) const
{
    s.write((char *)&r, sizeof(float));
    s.write((char *)&g, sizeof(float));
    s.write((char *)&b, sizeof(float));
    s.write((char *)&a, sizeof(float));
}

/** Restore this color from disk. */
void Unserialize(std::istream& s)
{
    s.read((char *)&r, sizeof(float));
    s.read((char *)&g, sizeof(float));
    s.read((char *)&b, sizeof(float));
    s.read((char *)&a, sizeof(float));
}

// data members public for convenience.
float r, g, b, a;
};
}

#endif