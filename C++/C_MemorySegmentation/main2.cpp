int global_bss_A;
int global_bss_B = 0;
static int global_bss_C;
static int global_bss_D = 0;
int global_bss_array_E[4096];
int global_bss_array_F[4096] = {0};
int main()
{
    static int local_bss_G;
    static int local_bss_H = 0;
    static int local_bss_array_I[128];
    static int local_bss_array_J[128] = {0};
}