#include <iostream>

int main() {
    int a = 0;
//    int &&b = a;
    int &&b = static_cast<int &&>(a);

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Value of b: " << b << std::endl;

    std::cout << "Address of a (&a): " << &a << std::endl;
    std::cout << "Address of b (&b): " << &b << std::endl; // 给出它所引用的对象的地址

    b = 100; // 通过别名 b 修改值
    std::cout << "After b = " << b << ", a is now: " << a << std::endl; // a 的值也变了

    return 0;
}