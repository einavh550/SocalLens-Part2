#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <cstring>

// Small shared helper so every class that stores a char* does its deep copy the
// same way, instead of repeating the same new[]/strcpy code in each file.
// Returns a heap-allocated copy of 'source' (an empty string for nullptr).
// The caller owns the result and must release it with delete[].
inline char* cloneString(const char* source)
{
    if (source == nullptr) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }
    int length = static_cast<int>(std::strlen(source));
    char* copy = new char[length + 1];
    std::memcpy(copy, source, length + 1); // +1 copies the '\0' terminator too
    return copy;
}

#endif // STRING_UTIL_H
