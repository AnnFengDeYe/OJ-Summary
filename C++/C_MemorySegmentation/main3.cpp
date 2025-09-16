#include <iostream>

void function_for_text_segment() {}
const int g_rodata_var = 10;
int g_data_var = 20;
int g_bss_var;

int main(int argc, char* argv[]) {

    int* heap_ptr = new int(30);

    // ===== 打印所有核心区域的内存地址 =====
    std::cout << "--- Memory Layout Analysis ---" << std::endl;
    uintptr_t text_addr   = (uintptr_t)function_for_text_segment;
    uintptr_t rodata_addr = (uintptr_t)&g_rodata_var;
    uintptr_t data_addr   = (uintptr_t)&g_data_var;
    uintptr_t bss_addr    = (uintptr_t)&g_bss_var;
    uintptr_t heap_addr   = (uintptr_t)heap_ptr;
    uintptr_t stack_addr  = (uintptr_t)&argv[0];

    std::cout << "1. .text address:    0x" << std::hex << text_addr << std::endl;
    std::cout << "2. .rodata address:  0x" << std::hex << rodata_addr << std::endl;
    std::cout << "3. .data address:    0x" << std::hex << data_addr << std::endl;
    std::cout << "4. .bss address:     0x" << std::hex << bss_addr << std::endl;
    std::cout << "5. Heap address:     0x" << std::hex << heap_addr << std::endl;
    std::cout << "6. Stack address:    0x" << std::hex << stack_addr << std::endl;
    std::cout << std::dec << std::endl;

    // ===== 验证与 ASLR =====
    std::cout << "--- Layout & ASLR Verification ---" << std::endl;

    // Part 1: 验证静态内存区内部的固定布局
    // 这个顺序是由链接器决定的，不受ASLR影响，结果始终为 true。
    std::cout << std::boolalpha;
    std::cout << "Static Area Rule (.text < .rodata < .data < .bss) Check: "
              << ((text_addr < rodata_addr) && (rodata_addr < data_addr) && (data_addr < bss_addr))
              << std::endl << std::endl;

    // Part 2: 观察各大区域间的相对位置
    // 这个顺序受 ASLR 影响，在不同系统或多次运行中可能不同。
    std::cout << "Major Areas Relative Position (can be randomized by ASLR):" << std::endl;
    std::cout << "  Stack < Heap?     " << (stack_addr < heap_addr) << std::endl;
    std::cout << "  Static memory < Stack ?     " << (bss_addr < stack_addr) << std::endl;
    std::cout << std::endl;

    delete heap_ptr;
    return 0;
}