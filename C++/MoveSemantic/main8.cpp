#include <iostream>

int main() {
    int a = 0;
    //    int &&b = a;
    int &&b = static_cast<int &&>(a);
}