#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>

class X {
private:
    char* image; // 模拟一个昂贵的资源
    static const size_t IMAGE_SIZE = 2048; // 2KB大小

public:
    // 默认构造函数
    X() {
//         std::cout << "Default constructor." << std::endl;
        image = new char[IMAGE_SIZE];
    }

    ~X() {
        delete[] image;
    }

    // ------------------- 拷贝语义 -------------------

    // 1. 复制构造函数 (昂贵的深度拷贝)
    X(const X& other) {
//        std::cout << "Copy constructor (expensive deep copy)." << std::endl;
        image = new char[IMAGE_SIZE];
        memcpy(this->image, other.image, IMAGE_SIZE);
    }

    // 2. 复制赋值运算符 (昂贵的深度拷贝)
    X& operator=(const X& other) {
//        std::cout << "Copy assignment (expensive deep copy)." << std::endl;
        if (this == &other) {
            return *this;
        }
        delete[] image; // 释放旧资源
        image = new char[IMAGE_SIZE];
        // 复制新资源
        memcpy(this->image, other.image, IMAGE_SIZE);
        return *this;
    }

    // ------------------- 移动语义 -------------------

    // 3. 移动构造函数 (高效的资源窃取)
    X(X&& other) noexcept {
//        std::cout << "Move constructor (cheap pointer swap)." << std::endl;
        this->image = other.image; // 1. 偷走源对象的指针
        other.image = nullptr;     // 2. 将源对象指针置空，避免它析构时释放资源
    }

    // 4. 移动赋值运算符 (高效的资源窃取)
    X& operator=(X&& other) noexcept {
        std::cout << "Move assignment (cheap pointer swap)." << std::endl;
        if (this == &other) {
            return *this;
        }
        delete[] image; // 释放自己的旧资源
        this->image = other.image; // 1. 偷走源对象的指针
        other.image = nullptr;     // 2. 将源对象指针置空
        return *this;
    }
};

// 一个返回大量 X 对象的函数
std::vector<X> make_bunch_of_x(size_t count) {
    std::vector<X> vec;
    vec.reserve(count); // 预分配内存，避免vector扩容时的额外开销
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(X()); // push_back 会创建临时对象，触发移动或拷贝
    }
    return vec;
}

int main() {
    const size_t NUM_OBJECTS = 10000;
    auto start_move = std::chrono::high_resolution_clock::now();

    std::vector<X> images = make_bunch_of_x(NUM_OBJECTS);

    auto end_move = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_move = end_move - start_move;

    std::cout << "\nRESULT WITH COPY: Vector has " << images.size() << " objects." << std::endl;
    std::cout << "TIME TAKEN: " << duration_move.count() << " ms\n" << std::endl;

    return 0;
}