#include <iostream>

int x = 1;

int get_val() {
    return x;
}

void set_val(int val) {
    int *p = &val;
//    std::cout << "Formal Parameter is a lvalue. Its address: " << p << std::endl;
    x = val;
}

int main() {
    int y = get_val();
//    int z = &get_val();
    set_val(2);


    auto *p = &"annfeng";
    std::cout << "Address of const char string *p is " << p << std::endl;
}
