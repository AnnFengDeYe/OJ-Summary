#include <iostream>

int main() {
    int a = 10, b = 20, c = 30, d = 40, e = 50;

    int *foo[5];// 声明一个指针数组

    foo[0] = &a; // 第一个元素指向变量a
    foo[1] = &b; // 第二个元素指向变量b
    foo[2] = &c;
    foo[3] = &d;
    foo[4] = &e;

    // foo[1] 是指向b的指针
    // *foo[1] 是通过指针访问b的值
    std::cout << "The value pointed to by foo[1] is: " << *foo[1] << std::endl; // 输出 20

    // 改变通过指针指向的值
    *foo[0] = 100;
    std::cout << "The new value of a is: " << a << std::endl; // 输出 100
}