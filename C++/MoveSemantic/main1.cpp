#include <iostream>

int main() {
    int a = 1;
    int b = 2;
    int c = a + b;

    auto *pa = &a, *pb = &b, *pc = &c;
    std::cout << "address of variable a: "<< pa << std::endl;
    std::cout << "address of variable b: "<< pb << std::endl;
    std::cout << "address of variable c: "<< pa << std::endl;
    auto *pd = &1;
}
