/*
	CS 89/189 Computational Aspects of Digital Photography C++ basecode.

	Adapted from MIT's 6.815/6.865 basecode, written and designed by:
		Frédo Durand
		Katherine L. Bouman
		Gaurav Chaurasia
		Adrian Vasile Dalca
		Neal Wadhwa

	With additions & modifications by
		Wojciech Jarosz
	for Dartmouth's CS 89/189.
*/

#pragma once

#include <stdexcept>
#include <stdio.h>

class DivideByZeroException : public std::runtime_error
{
public:
	DivideByZeroException() : std::runtime_error("Divisor is zero") {}
};

class MismatchedDimensionsException : public std::runtime_error
{
public:
	MismatchedDimensionsException() : std::runtime_error("Image dimensions are not the same.") {}
};

class NegativeDimensionException : public std::runtime_error
{
public:
	NegativeDimensionException() : std::runtime_error("Array dimensions must be nonnegative.") {}
};

class ChannelException : public std::runtime_error
{
public:
	ChannelException() : std::runtime_error("Number of channels must be 1, 3 or 4 when writing to image.") {}
};

class OutOfBoundsException : public std::runtime_error
{
public:
	OutOfBoundsException() : std::runtime_error("Index is out of the array bounds.") {}
};
