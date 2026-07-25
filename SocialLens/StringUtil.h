#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <cstring>

inline char* cloneString(const char* source)
{
    if (source == nullptr) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }
    int length = static_cast<int>(std::strlen(source));
    char* copy = new char[length + 1];
    std::memcpy(copy, source, length + 1);
    return copy;
}

#endif

