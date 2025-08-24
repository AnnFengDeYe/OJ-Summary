#include <iostream>

void swap_ptr(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swap_ref(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 1, b = 2, c = 3, d = 4;
    swap_ptr(&a, &b);
    std::cout << "After swap_ptr: "<< a << " " << b << std::endl;

    swap_ref(c, d);
    std::cout << "After swap_ref: "<< c << " " << d << std::endl;
}