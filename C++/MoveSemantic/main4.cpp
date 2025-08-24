#include <iostream>

int main() {
//    int &a = 7;
    const int &x = 11;
    std::cout << "Address of const int variable x is " << &x << std::endl;
}