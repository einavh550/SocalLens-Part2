#ifndef ARRAY_UTIL_H
#define ARRAY_UTIL_H

inline void** growPointerArray(void** items, int count, int newCapacity) {
    void** larger = new void*[newCapacity];
    for (int i = 0; i < count; ++i)
        larger[i] = items[i];
    delete[] items;
    return larger;
}

#endif

