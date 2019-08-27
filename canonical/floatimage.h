/*!
    \file floatimage.h
    \brief Contains the definition of a floating-point image class with an arbitrary number of channels
    \author Wojciech Jarosz
    \author Zack Misso
*/
#pragma once

#include "common.h"
#include "array3D.h"
#include <string>

//! Floating point image
class FloatImage : public Array3D<Float>
{
public:
    //-----------------------------------------------------------------------
    //@{ \name Constructors, destructors, etc.
    //-----------------------------------------------------------------------
    FloatImage();
    FloatImage(int width, int height, int channels);
    FloatImage(const std::string & filename);
    FloatImage(const FloatImage &other);
    FloatImage & operator=(const FloatImage &other);
    void clear(Float v = 0.0f) {reset(v);}
    void clear(const std::vector<Float> & channelValues);
    //@}

    int channels() const {return m_sizeZ;}

    static void ratio(const FloatImage& one, const FloatImage& two, FloatImage& out, double exposure = 1.0);
    static double mean(const FloatImage& image);
    static double variance(const FloatImage& image);

    static void flipXAxis(const FloatImage& in, FloatImage& out);
    static void flipYAxis(const FloatImage& in, FloatImage& out);

    //-----------------------------------------------------------------------
    //@{ \name Image I/O.
    //-----------------------------------------------------------------------
    bool read(const std::string &name);
    bool write(const std::string &name) const;
    //@}
};
