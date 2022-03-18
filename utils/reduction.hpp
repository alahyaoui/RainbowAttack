#ifndef REDUCTION_H
#define REDUCTION_H

#define SIZE 16

#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>

namespace rainbow {

inline void toHex(const char *text, unsigned char *bytes) {
    unsigned int temp;
    for (int i = 0; i < SIZE; i++) {
        std::sscanf(text + 2 * i, "%2x", &temp);
        bytes[i] = temp;
    }
}

/**
 * @brief Reduces the given hash to a possible alphanumeric password.
 *
 * TODO: it should be possible to have a reduction of a size between 5 and 8;
 *
 * The reduction is inspired by the one found in this github repository...
 * https://github.com/jfmengels/rainbowtable/blob/dd7bdf498dd5ea9fc1fee96078d607
 * 91c2ab2d1e/RainbowTable.cpp
 *
 * @param hash is the given sha256 hash.
 * @param column is the column of the given hash in the rainbow table.
 * @return the reduction of the given hash.
 */
inline std::string reduce(const std::string hash, unsigned column, unsigned length) {
    std::string reduction;
    int current;
    const char * chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                         "abcdefghijklmnopqrstuvwxyz"
                         "0123456789";
    unsigned char bytes[SIZE];
    toHex(hash.c_str(), bytes);
    for (unsigned i = 0; i < length; i++) {
        current = bytes[(i + column) % SIZE];
        reduction += chars[current % 62];
    }
    return reduction;
}

}

#endif
