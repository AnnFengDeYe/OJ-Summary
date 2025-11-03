#include <iostream>
#include "my_add.h"
#include "my_multiply.h"

int main() {
    std::cout << "StaticLib Demo1" << std::endl;
    std::cout << "  " << add(10, 5) << std::endl;
    std::cout << "  " << multiply(10, 5) << std::endl;
}