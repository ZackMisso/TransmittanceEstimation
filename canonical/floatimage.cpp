/*!
    modified version of code from Wojciech Jarosz
*/

#include "floatimage.h"
#include "util.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ext/stb/stb_image_write.h"

using namespace std;

namespace
{

string getExtension(const string &filename)
{
	if (filename.find_last_of(".") != string::npos)
		return filename.substr(filename.find_last_of(".") + 1);
	return "";
}

float byteToFloat(const unsigned char in)
{
	return in / 255.0f;
}

unsigned char floatToByte(float in)
{
	return int(255.0f * Util::clamp(in, 0.0f, 1.0f));
}

}

FloatImage::FloatImage() : Array3D<Float>()
{
	// empty
}

FloatImage::FloatImage(int width, int height, int channels) :
	Array3D<Float>(width, height, channels)
{
	// empty
}

FloatImage::FloatImage(const string &filename) : Array3D<Float>()
{
	read(filename);
}

FloatImage::FloatImage(const FloatImage &in) : Array3D<Float>()
{
	resize(in.width(), in.height(), in.depth());
	m_data = in.m_data;
}

FloatImage &FloatImage::operator=(const FloatImage &in)
{
	m_data = in.m_data;
	m_sizeX = in.m_sizeX;
	m_sizeY = in.m_sizeY;
	m_sizeZ = in.m_sizeZ;
	m_strideZ = in.m_strideZ;
	return *this;
}

void FloatImage::clear(const vector<Float> &channelValues)
{
	for (int z = 0; z < sizeZ(); ++z)
		for (int y = 0; y < sizeY(); ++y)
			for (int x = 0; x < sizeX(); ++x)
				operator()(x, y, z) = channelValues[z];
}

bool FloatImage::read(const string &filename)
{
	int n, w, h;

	try
	{
		if (stbi_is_hdr(filename.c_str()))
		{
			float *floatPixels = stbi_loadf(filename.c_str(), &w, &h, &n, 3);
			if (floatPixels)
			{
				resize(w, h, 3);

				for (int x = 0; x < w; x++)
					for (int y = 0; y < h; y++)
						for (int c = 0; c < 3; c++)
							operator()(x, y, c) = floatPixels[3 * (x + y * w) + c];

				stbi_image_free(floatPixels);
				return true;
			}
			else
				throw runtime_error("Could not load HDR image.");
		}
		else
		{
			unsigned char *bytePixels = stbi_load(filename.c_str(), &w, &h, &n, 3);
			if (bytePixels)
			{
				resize(w, h, 3);

				for (int x = 0; x < w; x++)
					for (int y = 0; y < h; y++)
						for (int c = 0; c < 3; c++)
							operator()(x, y, c) = byteToFloat(bytePixels[3 * (x + y * w) + c]);

				stbi_image_free(bytePixels);
				return true;
			}
			else
				throw runtime_error("Could not load LDR image.");
		}
	}
	catch (const exception &e)
	{
		cerr << "Image decoder error in FloatImage::read(...) for file: \"" << filename << "\":\n\t"
		     << stbi_failure_reason() << endl;
		return false;
	}
}

bool FloatImage::write(const string &filename) const
{
	if (channels() != 1 && channels() != 3 && channels() != 4)
		throw ChannelException();

	string extension = getExtension(filename);
	transform(extension.begin(),
	          extension.end(),
	          extension.begin(),
	          ::tolower);
	try
	{
		if (extension == "hdr")
		{
			// stbi_write_hdr expects color channels for a single pixel to be adjacent in memory
			vector<float> floatPixels(height() * width() * 3, 1.0f);
			for (int x = 0; x < width(); x++)
				for (int y = 0; y < height(); y++)
					for (int c = 0; c < channels(); c++)
						floatPixels[c + x * 3 + y * 3 * width()] = operator()(x, y, c);

			if (!stbi_write_hdr(filename.c_str(), width(), height(), channels(), &floatPixels[0]))
				throw runtime_error("Could not write HDR image.");
		}
		else if (extension == "png" ||
			extension == "bmp" ||
			extension == "tga" ||
			extension == "jpg" || extension == "jpeg")
		{
			int outputChannels = 4;
			vector<unsigned char> bytePixels(height() * width() * outputChannels, 255);
			int c;
			for (int x = 0; x < width(); x++)
				for (int y = 0; y < height(); y++)
				{
					for (c = 0; c < channels(); c++)
						bytePixels[c + x * outputChannels + y * outputChannels * width()] =
							floatToByte(operator()(x, y, c));

					for (; c < 3; c++)
						// Only executes when there is one channel
						bytePixels[c + x * outputChannels + y * outputChannels * width()] =
							floatToByte(operator()(x, y, 0));
				}

			if (extension == "png")
			{
				if (!stbi_write_png(filename.c_str(), width(), height(),
				                    outputChannels, &bytePixels[0],
				                    sizeof(unsigned char) * width() * outputChannels))
					throw runtime_error("Could not write PNG image.");
			}
			else if (extension == "bmp")
			{
				if (!stbi_write_bmp(filename.c_str(), width(), height(), outputChannels, &bytePixels[0]))
					throw runtime_error("Could not write BMP image.");
			}
			else if (extension == "tga")
			{
				if (!stbi_write_tga(filename.c_str(), width(), height(), outputChannels, &bytePixels[0]))
					throw runtime_error("Could not write TGA image.");
			}
			else if (extension == "jpg" || extension == "jpeg")
			{
				if (!stbi_write_jpg(filename.c_str(), width(), height(), outputChannels, &bytePixels[0], 100))
					throw runtime_error("Could not write JPG image.");
			}
		}
        else if (extension == "txt")
        {
            // since hdr write is bugged I am added this to convert to exrs in pbrt
            std::ofstream file(filename);
            file << width() << "\n";
            file << height() << "\n";
            file << depth() << "\n";

            for (int i = 0; i < size(); ++i)
            {
                file << operator()(i) << "\n";
            }
        }
		else
			throw invalid_argument("Could not determine desired file type from extension.");
	}
	catch (const exception &e)
	{
		// if there's an error, display it
		cerr << "Error in FloatImage::write(...) for file:  \"" << filename << "\":\n\t" << e.what() << endl;
	}

	return true;
}

void FloatImage::ratio(const FloatImage& one, const FloatImage& two, FloatImage& out, double exposure) {
    if (one.width() != two.width() || one.height() != two.height() || one.depth() != two.depth()) {
        cout << "ERROR: Input images are of different sizes" << endl;
        return;
    }

    for (int i = 0; i < one.height(); ++i) {
        for (int j = 0; j < one.width(); ++j) {
            for (int k = 0; k < one.depth(); ++k) {
                if (one(j, i, k) == 0.0) {
                    out(j, i, k) = 0.0;
                } else {
                    out(j, i, k) = two(j, i, k) / one(j, i, k) * exposure;
                }
            }
        }
    }
}

double FloatImage::mean(const FloatImage& image) {
    double mean = 0.0;

    for (int i = 0; i < image.size(); ++i) {
        mean += image(i);
    }

    mean /= double(image.size());

    return mean;
}

double FloatImage::variance(const FloatImage& image) {
    double mean = FloatImage::mean(image);
    double variance = 0.0;

    for (int i = 0; i < image.size(); ++i) {
        variance += (image(i) - mean) * (image(i) - mean);
    }

    variance /= double(image.size() - 1);

    return variance;
}

void FloatImage::flipXAxis(const FloatImage& in, FloatImage& out) {
    for (int i = 0; i < in.height(); ++i) {
        for (int j = 0; j < in.width(); ++j) {
            out(in.width() - j - 1, i, 0) = in(j, i, 0);
            out(in.width() - j - 1, i, 1) = in(j, i, 1);
            out(in.width() - j - 1, i, 2) = in(j, i, 2);
        }
    }
}

void FloatImage::flipYAxis(const FloatImage& in, FloatImage& out) {
    for (int i = 0; i < in.height(); ++i) {
        for (int j = 0; j < in.width(); ++j) {
            out(j, in.height() - i - 1, 0) = in(j, i, 0);
            out(j, in.height() - i - 1, 1) = in(j, i, 1);
            out(j, in.height() - i - 1, 2) = in(j, i, 2);
        }
    }
}
