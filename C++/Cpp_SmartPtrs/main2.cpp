#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Car {
    std::string name_;
public:
    explicit Car(std::string  name) : name_{std::move(name)} {
        std::cout << name_ << " (Car 构造函数)\n";
    }
    ~Car() {
        std::cout << "" << name_ << "没啦 (Car 析构函数)\n";
    }
    void drive() const {
        std::cout << "驾驶 " << name_ << " 出发！\n";
    }
};

void sell_car_to_friend(std::unique_ptr<Car> car_ownership) {
    std::cout << "[朋友]: 收到了车，所有权现在是我的了。\n";
    car_ownership->drive();
    std::cout << "[朋友]: 我用完车了。\n";
}

void demo_unique_ptr() {
    std::cout << "--- unique_ptr 场景：私家车的所有权转移 ---\n";
    auto my_car {std::make_unique<Car>("Tesla")};
    my_car->drive();
    std::cout << "[我]: 准备把车卖给朋友...\n";
//     sell_car_to_friend(my_car); // error
    sell_car_to_friend(std::move(my_car));

    if (!my_car) {
        std::cout << "[我]: 车已经不是我的了 (my_car 现在是 nullptr)。\n";
    }
}

int main() {
    demo_unique_ptr();
}