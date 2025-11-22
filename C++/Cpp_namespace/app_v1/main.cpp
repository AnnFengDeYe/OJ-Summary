#include "my_math.h"
#include <iostream>

int main() {
    std::cout << "--- Starting App_v1 (The Old App) ---" << std::endl;

    int result = MyLib::add(10, 5);

    std::cout << "App_v1 Result: " << result << std::endl;
    std::cout << "--- Exiting App_v1 ---" << std::endl;
    return 0;
}