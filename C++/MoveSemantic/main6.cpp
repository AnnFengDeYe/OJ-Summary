#include <iostream>

int main() {
    int a = 0;
    int &b = a;
    int &&c = 2;

    std::cout << "value of lvalue reference: " << b <<std::endl;
    std::cout << "value of rvalue reference: " << c <<std::endl;
}