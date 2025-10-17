#include <iostream>
#include <memory>

class MyObject {
public:
    MyObject() { std::cout << "  [堆] MyObject 诞生 (构造函数)\n"; }
    ~MyObject() { std::cout << "  [堆] MyObject 死亡 (析构函数)\n"; }
    void greet() { std::cout << "  -> MyObject 说你好!\n"; }
};

// 场景1：正确用法 - unique_ptr对象在栈上，通过 new 初始化
void stack_ptr_via_new() {
    std::cout << "--- 场景1：栈上 unique_ptr, 通过 new 初始化 ---\n";
    std::unique_ptr<MyObject> p1{new MyObject{}};
    std::cout << "unique_ptr 对象 p1 在栈上创建完毕。\n";
    p1->greet();
}

// 场景2：推荐用法 - unique_ptr对象在栈上，通过 make_unique 初始化
void stack_ptr_via_make_unique() {
    std::cout << "\n--- 场景2：栈上 unique_ptr, 通过 make_unique 初始化 ---\n";
    auto p2{std::make_unique<MyObject>()};
    std::cout << "unique_ptr 对象 p2 在栈上创建完毕。\n";
    p2->greet();
}

// 场景3：错误用法 - unique_ptr对象本身在堆上，破坏了RAII
void heap_ptr_breaks_raii() {
    std::cout << "\n--- 场景3：堆上 unique_ptr, 破坏 RAII ---\n";
    auto p3{new std::unique_ptr<MyObject>{new MyObject{}}};
    std::cout << "指向 unique_ptr 的原始指针 p3 在栈上创建完毕。\n";
    (*p3)->greet();
}

int main() {
    stack_ptr_via_new();
    stack_ptr_via_make_unique();
    heap_ptr_breaks_raii();
}