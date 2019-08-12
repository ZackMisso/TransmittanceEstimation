#pragma once

// This class is based off of code from Wojciech Jarosz

#include "../common.h"
#include <pcg32.h>

class Permutation {
public:
    Permutation();
    Permutation(uint32_t size);

    void initialize();
    void resize(uint32_t newSize);

    int32_t operator[](const uint32_t i) const;
    void shuffle(pcg32& rand);

    static unsigned int permute(unsigned int i, unsigned int l, unsigned int p);

    uint32_t getSize() const;

protected:
    std::vector<uint32_t> indices;
};
