  # C++智能指针

# scene 1 指针的诅咒

在C++ 的蛮荒时代，也就是在智能指针出现之前，程序员必须手动管理动态分配的内存：

```cpp
// 1. 申请内存
ResourceType* ptr = new ResourceType();

// 2. 使用资源
ptr->do_something();

// 3. 手动释放
delete ptr;
```

即首先申请内存资源，使用资源完成任务，任务结束后需要手动释放。但是这个过程充满了陷阱：

- **忘记 `delete`**：导致内存泄漏，程序长时间运行会耗尽系统资源。
- **重复 `delete`**：导致程序崩溃。
- **指针悬挂**：释放后继续使用一个无效的指针，导致未定义行为。
- **异常不安全**：如果在 `new` 和 `delete` 之间发生异常，`delete` 语句将不会被执行，同样导致内存泄漏。

即首先通过 `new` 申请资源，使用完毕后，再手动 `delete` 释放。这个过程看似简单，实则危机四伏。首要的风险是内存泄漏：任何一次**遗忘的 `delete`** 都会导致该块内存在进程的生命周期内永久丢失，无法被再次使用。其次，即便记得释放，也可能掉入**悬挂指针**的陷阱，即在 `delete` 后继续使用一个无效指针，这会导致未定义行为。此外，当释放内存的责任分工不清时，就可能发生**重复释放**，程序会立即崩溃。最后，是**异常安全**问题——`new` 和 `delete` 之间的任何异常都可能让释放操作被直接跳过，导致的内存泄漏无法通过常规的代码审查来预防（修）

# scene 2 RAII (资源获取即初始化)

为了解决指针的陷阱，C++ 的设计者 Bjarne Stroustrup 提出了一个极其重要的编程范式：**RAII (Resource Acquisition Is Initialization)**。即**将资源的生命周期与一个栈上对象的生命周期绑定在一起。**（人）

这里的资源指的是那些借出来必须要还的东西（人），比如使用new在堆上Heap申请的内存。**栈上对象**的生命周期管理是**自动的**，而**堆上资源**生命周期管理是**手动的**。绑定就是让**栈上对象**去管理**堆上资源**。相当于把手动、危险的工作，委托给这个自动可靠的栈上对象。（见C++内存模型）

来看一个RAII的实例，该实例对比分析了资源管理对象的不同初始化方式，以及这些方式如何直接影响其析构函数的调用，从而决定资源能否被成功释放。

```C++
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
```

代码定义了一个`MyObject`类。它的构造函数与析构函数分别打印“诞生”与“死亡”的消息，以此作为资源被成功分配与正确释放的直观展示。为保持代码风格的现代与一致，本示例中所有智能指针的初始化，均统一采用了 C++11 引入的花括号 `{}` 语法，即列表初始化 (List Initialization)。

在场景一 `stack_ptr_via_new` 函数的作用域内，`unique_ptr` 对象 `p1` 在栈上被实例化，并获得由 `new` 在堆上分配的 `MyObject` 资源的所有权。当执行流离开该作用域时，`p1` 的析构函数被确定性地调用，该析构函数会释放其管理的堆资源，从而实现了安全、自动的内存回收，完美诠释了RAII原则。

场景二的 `stack_ptr_via_make_unique` 函数展示了现代C++更推荐的实践。`unique_ptr` 对象 `p2` **同样**在栈上被实例化，但它通过性能更好更安全的 `std::make_unique` 辅助函数来封装资源的创建过程。在使用智能指针时都应优先使用make函数集（make_unique/make_shared）来进行创建。当执行流离开该作用域时，`p2` 的析构函数被确定性地调用并释放其管理的堆资源，这同样是RAII原则的完美应用。

场景三的 `heap_ptr_breaks_raii` 函数则是一个反面教材。`unique_ptr` 对象本身被错误地通过 `new` 创建在了堆上。因此，`auto` 关键字推导出的变量 `p3`，其类型不再是 `unique_ptr` 对象，而是一个 `std::unique_ptr<MyObject>*，即一个指向智能指针的原始指针。

这个操作形成了一个从栈到堆、再到堆的指针链：栈上的原始指针 `p3`，指向堆上的 `unique_ptr` 对象，该对象内部的指针又指向堆上的 `MyObject` 资源。

当执行流离开作用域时，仅有栈上的原始指针 `p3`被自动销毁。然而，销毁一个原始指针并不会释放它所指向的内存。这导致位于堆上的 `unique_p_tr` 对象变成了无人管理的孤儿”并被遗弃，其析构函数永远不会被自动调用。这违背了RAII的编程范式。由于管理者（`unique_ptr` 对象）自身的析构从未发生，它所管理的 `MyObject` 资源自然也无法被释放，造成了**双重内存泄漏**。RAII的自动性，完全依赖于管理对象自身生命周期的自动性。

可以看到，打印结果显示场景三的析构函数并没有调用。

# scene 3 智能指针概述

C++ 标准库<memory>中提供了三种用于实现资源自动管理（RAII）的智能指针。第一种是独占所有权的指针**unique_ptr**，在任何时刻，一个资源只能被一个 unique_ptr 所拥有。第二种是共享所有权指针**shared_ptr**，允许多个 shared_ptr 共同管理同一个资源，并通过内部的引用计数来跟踪拥有者数量。第三种是为解决循环引用的观察者指针**std::weak_ptr**，它提供对所管理资源的非拥有性弱引用，可以观察一个对象但不影响其引用计数（生命周期）。

注意，智能指针通常在栈上作为局部变量，它封装和管理着一个动态分配的默认在堆上的资源。

# scene 4 unique_ptr 独占与转移

`unique_ptr` 通过禁止拷贝、只允许移动(move)的方式，在编译期强制实现了独占所有权，且几乎没有任何额外的性能开销。

来看一个unique_ptr的代码实例

```C++
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

    std::unique_ptr<Car> my_car {std::make_unique<Car>("Tesla")};
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
```

你买了一辆新车，拥有它的独占所有权，使用一段时间后你决定把车卖给朋友，交接独占所有权，即move后检查自己是否还拥有这辆车。

```
sell_car_to_friend(my_car); 
```

如果不使用move直接进行交接是否可以呢？不可以，直接传递一个独占的unique_ptr会导致编译错误。编译器会告诉你 unique_ptr 的拷贝构造函数是deleted，被删除的。这正是独占的体现：C++ 语言在编译层面就禁止你复制 unique_ptr，从而保证了unique_ptr所有权的唯一性。

注意， 这里的`std::move` 只负责转换右值，把my_car从一个左值转换为即将销毁的临时对象来处理，移动由对象的移动构造函数或移动赋值运算符执行。更多关于左值/右值/移动语义的系统介绍，请移步我之前的视频。

此外，这里移动的是 `std::unique_ptr<Car>` 这个智能指针对象，而不是它所指向的 `Car` 对象本身。所以Car类里面是不需要实现移动函数的。使用的是` unique_ptr<Car>` 里面的移动构造函数。

深入源码一探究竟 确实是使用了` unique_ptr<Car>` 移动构造函数：

```cpp
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(unique_ptr&& __u) _NOEXCEPT
    : __ptr_(__u.release(), _VSTD::forward<deleter_type>(__u.get_deleter())) {}
```

移动完成后，即归属权交接发生sell_car_to_friend函数的作用域中，离开该作用域后，此时归属权属于朋友的Car对象的析构函数被调用，在堆上的Car对象就会被销毁。

返回到demo_unique_ptr的作用域时，由于my_car已经不再拥有Car对象，此时为nullptr。

# scene 5 shared_ptr 共享与计数

std::shared_ptr 通过一个线程安全的引用计数器，实现了共享所有权模型。当指针被复制时，引用计数增加；当指针生命周期结束时，引用计数减少。仅当最后一个 shared_ptr 被销毁，引用计数归零时，才会释放底层管理的资源。

来看一个shared_ptr的代码实例。

可以将 std::shared_ptr 的生命周期想象成一趟公交车旅程。 Bus 对象就是公交车本身，而每一个 shared_ptr 都是一位共享旅程的“相关者”。公交车需要知道有多少个乘客，也就是引用计数。旅程开始时，由 dispatch_center 这位“司机”发车，此时引用计数为 1。

随后，乘客 A 和 B 相继上车，也获得了对这辆车的共享所有权，引用计数随之增长到 3。当两位乘客陆续到站下车后，引用计数降回 1，但请注意，公交车并不会因为没有乘客就返回总站。它仍在司机”dispatch_center 的管理之下。直到整个函数结束（ `demo_shared_ptr` ），这位最后的拥有者离开其作用域，引用计数最终归零，Bus 对象的生命周期才真正终结，被安全销毁。

```C++
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
```

在乘客A上车的 `passengers.push_back(dispatch_center);` 这一行设置断点，命中shared_ptr的拷贝构造函数，发现构造函数内部实现了引用计数

```cpp
    _LIBCPP_HIDE_FROM_ABI
    shared_ptr(const shared_ptr& __r) _NOEXCEPT
        : __ptr_(__r.__ptr_),
          __cntrl_(__r.__cntrl_)
    {
        if (__cntrl_)
            __cntrl_->__add_shared();
    }
```

在赋值语句 `late_passenger_c = dispatch_center;` 再次设置断点，命中shared_ptr的拷贝赋值函数，会发现其赋值运算符并未直接操作引用计数。它巧妙地运用了 ，其核心正是 shared_ptr(__r).swap(*this); 这一行代码。

这个过程可以分解为三步：首先，通过拷贝构造函数 shared_ptr(__r) 创建一个临时对象，此举复用了刚刚断点进入的拷贝构造函数的逻辑，使新资源的引用计数安全地增加。接着，swap(*this) 将当前对象与这个临时对象的内容进行交换，使得当前对象指向了新资源。最后，当该语句结束时，持有旧资源的临时对象被销毁，其析构函数会自动使旧资源的引用计数减少。

这里的旧资源是指在赋值操作**之前**，等号**左边**的 late_passenger_c 所管理的对象。**新资源** 是指等号**右边**的 dispatch_center 所管理的对象。

```cpp
    _LIBCPP_HIDE_FROM_ABI
    shared_ptr<_Tp>& operator=(const shared_ptr& __r) _NOEXCEPT
    {
        shared_ptr(__r).swap(*this);
        return *this;
    }
```

这种**拷贝并交换 (copy-and-swap)** 的技巧巧妙地区分了两种行为：拷贝构造是“无中生有”，而拷贝赋值则是“以新换旧”。shared_ptr 正是通过复用构造与析构，优雅且安全地完成了赋值操作。

# scene 6 weak_ptr 观测与锁定

`weak_ptr` 是一种**非拥有的“观察者”指针**，它为解决 `shared_ptr` 的**循环引用**问题而设计。它不改变引用计数，但允许通过 `lock()` 方法在需要时安全地“升级”为 `shared_ptr` 进行访问。

weak_ptr 本身不控制对象的生命周期，因此也就不存在一个像 make_shared 或 make_unique 那样直接创建并拥有一个对象的工厂函数

来看一个weak_ptr的代码实例。

Car 是被管理的资源，main 函数中的 shared_ptr 是其生命周期的唯一所有者，表示代客泊车服务。CarOwner 类则是一个非拥有式的观察者，它通过其 weak_ptr 成员 valet_ticket 与 Car 建立一种非拥有式的链接。这种设计将二者的生命周期完全解耦，CarOwner 的存亡不影响 Car 对象，而 weak_ptr 则为 CarOwner 提供了一种在访问前安全检查资源是否依然存在的机制。

在场景一中，车主王先生获得的 valet_ticket 就是一个 weak_ptr。这张凭证的授予并不会增加车辆的管理者数量（引用计数），因为它仅仅是一个观察者（弱引用），而非所有权。

当王先生需要取车时，他调用 valet_ticket.lock()，这个动作就如同**出示凭证**。系统会安全地检查车辆是否还在。如果车辆仍在服务中，lock() 会成功并返回一个临时的 shared_ptr，让车主可以真正的行使所有权（开车）。

在场景二中，当唯一的 shared_ptr（代客泊车服务）终结时，车辆被自动销毁。此时，李先生手中的 weak_ptr 凭证虽然还存在，但已然失效。当他再用 lock() 尝试取车时就会失败。

```cpp
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
```

深入源码，可以看到在shared_ptr头文件，weak_ptr 的观察特性源于其与 shared_ptr 共享的**控制块（Control Block）**。

该控制块与被管理对象一同创建，并维护两种引用计数：决定对象生命周期的**强引用计数**（shared_ptr 的数量）和记录观察者数量的**弱引用计数**（weak_ptr 的数量）。weak_ptr 本质上是一个指向此控制块的非拥有式指针，它的存在仅增加弱引用计数，不影响对象的存亡。weak_ptr的 .lock() 方法会原子性地检查控制块中的强引用计数。若计数值大于零，意味着对象依然存活，.lock() 就会创建一个新的 shared_ptr 并返回，从而将“弱观察关系”提升为“强拥有关系”；若计数值为零，则返回一个空指针，有效避免了访问悬挂指针的风险。

# scene 7 循环引用

再来看一下在循环引用场景下weak_ptr是如何解决的

代码展示了shared_ptr 的一个典型陷阱：**循环引用 (Circular Reference)**。代码中创建了两个 Node 对象，A 和 B，它们各自内部的 partner 成员（一个 shared_ptr）强引用了对方。这形成了一个无法打破的“所有权闭环”：当 `{}` 作用域结束时，`nodeA` 和 `nodeB` 这两个栈上的智能指针被销毁，两个节点的引用计数都从2减为1。但因为节点A的内部还“抓着”节点B，节点B的内部也“抓着”节点A，两个对象的引用计数最终都停留在了 `1`，它们的引用计数永远无法归零，导致析构函数 `~Node()` 永远不会被调用，从而造成内存泄漏。

```cpp
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
```





解决方案就是打破这个“互相拥有”的链条。规定一种**非对称关系**：让其中一方的引用变为“弱引用”，即只观察、不拥有。

```Cpp
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
        auto nodeA = std::make_shared<GoodNode>("A");
        auto nodeB = std::make_shared<GoodNode>("B");

        std::cout << "创建后 -> NodeA count: " << nodeA.use_count()
                  << ", NodeB count: " << nodeB.use_count() << "\n";

        // 建立双向链接：A -> B (强), B -> A (弱)
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
```

当 `{}` 作用域结束时，将会**按声明顺序的逆序**来销毁栈上的局部变量。因此，`nodeB` 会先于 `nodeA` 被销毁。

栈上`nodeB` 是指向 `GoodNode("B")` 的一个 `shared_ptr`。它的销毁，使得 `GoodNode("B")` 对象的引用计数**从 2 降为 1**。因为引用计数仍为 `1`（`nodeA->next` 还指向它），所以 **`GoodNode("B")` 对象此时不会被销毁**。栈上`nodeA` 是指向 `GoodNode("A")` 的一个 `shared_ptr`。它的销毁，使得 `GoodNode("A")` 对象的引用计数**从 1 降为 0**。由于引用计数归零，`GoodNode("A")` 对象的析构函数 `~GoodNode()` 被调用。屏幕上打印出：**`节点 A 已销毁`**。

在销毁 `GoodNode("A")` 的过程中，它的所有成员变量也会被销毁。其成员 `next`（一个指向 `GoodNode("B")` 的 `shared_ptr`）被销毁。`next` 的销毁，使得 `GoodNode("B")` 对象的引用计数**从 1 降为 0**。由于引用计数归零，`GoodNode("B")` 对象的析构函数 `~GoodNode()` 被调用。屏幕上打印出：**`节点 B 已销毁`**。

反之，若B对A是强引用，A对B是弱引用，同样可以避免循环引用。

# 总结

这真的是一个工作量巨大的视频。记得一键三连 + 关注哦。

最后，我们以一个可爱的动画给C++的智能指针做一个总结吧

