#pragma once

#include <stdexcept>
#include <stdio.h>

class ChannelException : public std::runtime_error
{
public:
	ChannelException() : std::runtime_error("Number of channels must be 1, 3 or 4 when writing to image.") {}
};
