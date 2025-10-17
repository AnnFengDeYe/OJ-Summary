#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Node {
    std::string name;
    std::shared_ptr<Node> partner; // 指向伙伴的强引用

    explicit Node(std::string  n) : name(std::move(n)) { std::cout << "节点 " << name << " 已创建\n"; }
    ~Node() { std::cout << "节点 " << name << " 已销毁\n"; }
};

void demonstrate_problem() {
    std::cout << "--- 使用 shared_ptr 导致的循环引用问题 ---\n";
    {
        auto nodeA { std::make_shared<Node>("A") }; // A的引用计数为 1
        auto nodeB { std::make_shared<Node>("B") }; // B的引用计数为 1
        std::cout << "创建后 -> A count: " << nodeA.use_count() << ", B count: " << nodeB.use_count() << "\n";

        nodeA->partner = nodeB; // B的引用计数变为 2
        nodeB->partner = nodeA; // A的引用计数变为 2
        std::cout << "互相引用后 -> A count: " << nodeA.use_count() << ", B count: " << nodeB.use_count() << "\n";
    }

    std::cout << "!!! 函数已结束，但没有析构函数被调用，内存泄漏发生 !!!\n";
}

int main() {
    demonstrate_problem();
}