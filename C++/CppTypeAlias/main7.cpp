using IntPtr = int*;

using RawFuncType = IntPtr(void);

using FuncPtr = RawFuncType*;

FuncPtr myVar; // 等同于 int* (*myVar)(void);

int main () {

}