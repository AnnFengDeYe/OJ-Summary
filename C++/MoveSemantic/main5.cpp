#include <iostream>
class X {
public:
    X() {
        std::cout << "Default constructor called." << std::endl;
    }

    X(const X& other) {     // 复制构造函数
        std::cout << "Copy constructor called." << std::endl;
    }

    X& operator=(const X& other) {     // 复制赋值运算符
        std::cout << "Copy assignment operator called." << std::endl;
        return *this;
    }
    ~X() {}
};

X make_x() {
    std::cout << "--- Entering make_x function ---" << std::endl;
    return X(); // 创建并返回一个 X 的临时对象 注意：这里现代编译器会使用 RVO (返回值优化)
}

int main() {
    std::cout << "1. X x1;" << std::endl;
    X x1; // 调用默认构造函数

    std::cout << "\n2. X x2(x1);" << std::endl;
    X x2(x1); // 调用复制构造函数

    std::cout << "\n3. X x3(make_x());" << std::endl;
    X x3(make_x()); // 调用 make_x() 函数来初始化 x3

    std::cout << "\n4. x3 = make_x();" << std::endl;
    x3 = make_x();
}