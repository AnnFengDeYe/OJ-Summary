#include <iostream>
#include <string>
#include <vector>
#include <utility> // 必须包含 <utility> 才能使用 std::move

int main() {
    std::string uploader_name = "安枫的叶";

    // 场景1：拷贝左值
    std::string uploader = uploader_name;
    std::cout << "After copy:" << std::endl;
    std::cout << "  uploader: " << uploader << std::endl;
    std::cout << "  uploader_name: " << uploader_name << std::endl;

    std::cout << "-------------------------" << std::endl;

    // 场景2：从左值移动
    std::string new_name = std::move(uploader_name);

    std::cout << "After move:" << std::endl;
    std::cout << "  new_name: " << new_name << std::endl;
    std::cout << "  uploader_name: " << uploader_name << std::endl;

    uploader_name = "Ann Feng";
    std::cout << "uploader name after re-assignment: " << uploader_name << std::endl;
}