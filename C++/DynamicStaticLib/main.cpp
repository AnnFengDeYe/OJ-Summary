#include <iostream>
#define NUM 10
#define SQUARE(x) ((x)*(x))
#define DEBUG

int main() {
    int result = SQUARE(NUM); // 宏将在这里被展开

#ifdef DEBUG
    std::cout << "Debug" << std::endl;
#endif
}
