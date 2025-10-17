#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct GoodNode {
    std::string name;
    std::shared_ptr<GoodNode> next;      // 对下一个节点的强引用
    std::weak_ptr<GoodNode> prev;        // 对前一个节点的弱引用

    explicit GoodNode(std::string  n) : name(std::move(n)) { std::cout << "节点 " << name << " 已创建\n"; }
    ~GoodNode() { std::cout << "节点 " << name << " 已销毁\n"; }
};  

void demonstrate_solution() {
    std::cout << "\n--- 使用 weak_ptr 打破循环引用 ---\n";
    {
        auto nodeA {std::make_shared<GoodNode>("A")};
        auto nodeB {std::make_shared<GoodNode>("B")};

        std::cout << "创建后 -> NodeA count: " << nodeA.use_count()
                  << ", NodeB count: " << nodeB.use_count() << "\n";

        // 建立双向链接：1 -> 2 (强), 2 -> 1 (弱)
        nodeA->next = nodeB;
        nodeB->prev = nodeA;

        std::cout << "互相引用后 -> Node1 count: " << nodeA.use_count()
                  << ", Node2 count: " << nodeB.use_count() << "\n";
    }

    std::cout << "函数已结束，所有节点都应被成功销毁。\n";
}

int main() {
    demonstrate_solution();
}