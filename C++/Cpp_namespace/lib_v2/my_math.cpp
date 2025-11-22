#include "my_math.h"
#include <iostream>

namespace MyLib {
    namespace v1 {
        int add(int a, int b) {
            std::cout << "[LIB V2.0] Calling MyLib::v1::add(int, int)" << std::endl;
            return a + b;
        }
    }

    inline namespace v2 {
        double add(double a, double b) {
            std::cout << "[LIB V2.0] Calling MyLib::v2::add(double, double)" << std::endl;
            return a + b;
        }
    }
}