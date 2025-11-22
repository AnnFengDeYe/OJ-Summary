#include "my_math.h"
#include <iostream>

int main() {
    std::cout << "--- Starting App_v2 (The New App) ---" << std::endl;

    double result_v2 = MyLib::add(10.5, 5.5);
    std::cout << "App_v2 (Default): " << result_v2 << std::endl;

    int result_v1 = MyLib::v1::add(10, 5);
    std::cout << "App_v2 (Explicit v1): " << result_v1 << std::endl;

    std::cout << "--- Exiting App_v2 ---" << std::endl;
}

