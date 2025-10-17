#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <utility>

class Car {
public:
    std::string license_plate;

    explicit Car(std::string plate) : license_plate(std::move(plate)) {
        std::cout << "[系统] 车辆 " << license_plate << " 已交给代客泊车服务。\n";
    }
    ~Car() {
        std::cout << "[系统] 车辆 " << license_plate << " 已被车主从泊车服务中取回。\n";
    }
    void drive() const {
        std::cout << "--> 正在驾驶车辆 " << license_plate << "...\n";
    }
};

class CarOwner {
public:
    std::string name;
    std::weak_ptr<Car> valet_ticket;

    explicit CarOwner(std::string  n) : name(std::move(n)) {}

    void retrieveCar() const {
        std::cout << "\n--- " << name << " 出示凭证，准备取车 ---\n";

        if (auto car_to_drive = valet_ticket.lock()) {
            std::cout << "凭证有效！服务生将车辆 " << car_to_drive->license_plate << " 开了过来。\n";
            std::cout << "  (取车瞬间，车辆的管理者数量/引用计数变为: " << car_to_drive.use_count() << ")\n";
            car_to_drive->drive();
            std::cout << name << " 将车开走。\n";
        } else {
            std::cout << "凭证已失效！服务生说：“抱歉，您的车已经不在我们的服务中了。”\n";
        }
    }
};

int main() {
    std::cout << "============ 场景一：正常取车 ============\n";
    {
        auto valet_service_ptr = std::make_shared<Car>("沪A-88888");
        CarOwner mr_wang("王先生");
        mr_wang.valet_ticket = valet_service_ptr;
        std::cout << "王先生拿到凭证后，车辆的管理者数量/引用计数为: " << valet_service_ptr.use_count() << "\n";
        mr_wang.retrieveCar();
    }

    std::cout << "\n============ 场景二：凭证失效 ============\n";
    std::weak_ptr<Car> expired_ticket;
    {
        auto valet_service_ptr_2 = std::make_shared<Car>("京B-66666");
        CarOwner mr_li("李先生");
        mr_li.valet_ticket = valet_service_ptr_2;
        expired_ticket = valet_service_ptr_2; // 我们也保留一张凭证用于演示
        std::cout << "李先生拿到凭证，车辆引用计数: " << valet_service_ptr_2.use_count() << "\n";
        std::cout << "......时间流逝，代客泊车服务结束了......\n";
    }

    CarOwner late_mr_li("迟到的李先生");
    late_mr_li.valet_ticket = expired_ticket;
    late_mr_li.retrieveCar();
}