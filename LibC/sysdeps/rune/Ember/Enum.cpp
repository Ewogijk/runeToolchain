#include <Ember/Enum.h>


size_t e_strlen(const char* str) {
    size_t size = 0;
    while (*str != '\0') {
        size++;
        ++str;
    }
    return size;
}


int e_memcmp(const void* lhs, const void* rhs, const size_t count) {
    const auto* l = (unsigned char*)lhs;
    const auto* r = (unsigned char*)rhs;

    for (size_t i = 0; i < count; i++) {
        if (l[i] < r[i])
            return -1;
        else if (l[i] > r[i])
            return 1;
    }
    return 0;
}
