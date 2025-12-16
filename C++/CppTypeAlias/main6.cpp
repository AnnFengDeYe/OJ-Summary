# include <iostream>
const int n = 5;

using FuncPtr = int* (*)(void); // 定义元素类型

FuncPtr listA[5];   // 长度 5
FuncPtr listB[100]; // 长度 100

FuncPtr* dynamicArr = new FuncPtr[n]; // 动态数组

std::vector<FuncPtr> vec; // 甚至可以直接塞进 vector

int main () {

}