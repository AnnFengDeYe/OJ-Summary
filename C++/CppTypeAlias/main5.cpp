#include <iostream>

// 定义别名 FuncPtr：指向 "返回 int* 且无参数的函数" 的指针
// 这里的 (*)(void) 对应原式中的 (*var[5])(void) 部分
using FuncPtr = int* (*)(void);

FuncPtr var[5];

int main () {
    // 现代 C++ 写法：
    using FuncPtr = std::function<int*(void)>;
    // 变量定义方式完全不变：
    FuncPtr var[5];
}