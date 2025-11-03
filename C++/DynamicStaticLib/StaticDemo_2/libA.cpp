#include "libA.h"
#include "libB.h"  // 关键：libA 包含了 libB 的头文件
#include <iostream>

int funcA() {
    std::cout << " > [libA] funcA() 正在执行..." << std::endl;
    std::cout << " > [libA] 准备调用 funcB()..." << std::endl;

    // 关键：libA 在其实现中调用了 funcB()
    int b_result = funcB();

    std::cout << " > [libA] funcB() 调用完毕。" << std::endl;
    return b_result + 50;
}