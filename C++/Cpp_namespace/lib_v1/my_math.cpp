#include "my_math.h"
#include <iostream>

namespace MyLib {
    inline namespace v1 {
        int add(int a, int b) {
            std::cout << "[LIB V1.0] Calling MyLib::v1::add(int, int)" << std::endl;
            return a + b;
        }
    }
}