#include <iostream>

using IntPredicate = bool(int);

IntPredicate* p;               // 传统的指针
std::function<IntPredicate> f; // 现代的容器

int main () {

}