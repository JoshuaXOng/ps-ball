#include "math_utils.hpp"

void MathUtils::memoryLeak() {
    int* pointer = new int(5);
    return;
}