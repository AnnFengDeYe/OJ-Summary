#include <iostream>

int main() {
    int (*bar)[5];

    // 指向二维数组的一行
    int matrix[2][5] = {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10}
    };

    // 让bar指向matrix的第一行
    bar = &matrix[0]; // 或者直接写 bar = matrix;
    std::cout << "First element of the first row: " << (*bar)[0] << std::endl; // 输出 1

    // 让bar指向matrix的第二行
    bar++;
    std::cout << "First element of the second row: " << (*bar)[0] << std::endl; // 输出 6

    return 0;
}