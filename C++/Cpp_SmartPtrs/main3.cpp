#include <iostream>
#include <memory>
#include <vector>

class Bus {
public:
    Bus() { std::cout << "公交车 #101 发车 (Bus 构造函数)\n"; }
    ~Bus() { std::cout << "公交车 #101 返回总站 (Bus 析构函数)\n"; }
};

void demo_shared_ptr() {
    std::cout << "\n--- shared_ptr 场景：一辆公交车与它的乘客们 ---\n";

    auto dispatch_center {std::make_shared<Bus>()};
    std::cout << "1. 运营开始，当前引用计数: " << dispatch_center.use_count() << "\n\n";

    std::vector<std::shared_ptr<Bus> > passengers {};
    std::cout << "乘客 A 和 B 上车...\n";
    passengers.push_back(dispatch_center); // 触发拷贝构造
    passengers.push_back(dispatch_center); // 触发拷贝构造
    std::cout << "2. 两位乘客上车后，当前引用计数: " << dispatch_center.use_count() << "\n\n";

    std::shared_ptr<Bus> late_passenger_c {};
    std::cout << "一位迟到的乘客 C 准备上车...\n";
    late_passenger_c = dispatch_center; // 触发拷贝赋值
    std::cout << "3. 乘客 C 上车后，当前引用计数: " << late_passenger_c.use_count() << "\n\n";

    std::cout << "--- 乘客开始下车 ---\n";
    std::cout << "乘客 A 下车...\n";
    passengers.pop_back();
    std::cout << "4. 乘客 A 下车后，当前引用计数: " << dispatch_center.use_count() << "\n";
    std::cout << "乘客 C 也下车了...\n";
    late_passenger_c = nullptr; // 再次赋值，使其放弃拥有权
    std::cout << "5. 乘客 C 下车后，当前引用计数: " << dispatch_center.use_count() << "\n";

    std::cout << "乘客 B 下车...\n";
    passengers.pop_back();
    std::cout << "6. 所有乘客都已下车，但调度中心仍在，当前引用计数: " << dispatch_center.use_count() << "\n";

    std::cout << "公交车继续运营...\n";
}

int main() {
    demo_shared_ptr();
}