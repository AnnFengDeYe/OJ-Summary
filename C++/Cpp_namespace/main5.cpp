#include <iostream>

namespace foo {
    constexpr int magic_number = 42;
}

namespace bar {
    constexpr float magic_number = 3.14;
}

int main() {
    std::cout << foo::magic_number << '\n';
    std::cout << bar::magic_number << '\n';
}