#include "libA.h"
#include <iostream>

int main() {
    std::cout << "StaticLib Demo2" << std::endl;
    std::cout << "[Main] 程序启动。" << std::endl;
    std::cout << "[Main] 准备调用 funcA()..." << std::endl;

    int result = funcA();
    std::cout << "[Main] funcA() 调用完毕，结果: " << result << std::endl;
}