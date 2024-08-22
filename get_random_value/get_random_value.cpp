#include <cstdlib>

#include "get_random_value.h"

int get_random_value(int start, int end) {
    return std::rand() % (end - start + 1) + start;
}