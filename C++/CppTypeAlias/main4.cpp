#ifdef _WIN64
using WindowHandle = unsigned long long;
#else
using WindowHandle = unsigned long;
#endif

void InitializeWindow(WindowHandle handle);

int main () {

}