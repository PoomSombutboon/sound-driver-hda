#include <intrinsics.h>

extern int printk (const char * fmt, ...);

void __attribute__((noinline))
__do_backtrace (void ** fp, unsigned depth)
{
    if (!fp) {
        return;
    }
    
    printk("[%2u] RIP=%p RBP=%p\n", depth, *(fp+1), *fp);

    __do_backtrace(*fp, depth+1);
}



void 
print_gprs (void) 
{
    int i = 0;
    char * reg_names[9] = {"RAX", "RBX" , "RCX", "RDX", "RDI", "RSI", "RBP", "RSP", 0};
    void * reg_vals[8];

    asm volatile("movq %%rax, %[m]" : [m] "=m" (reg_vals[0]));
    asm volatile("movq %%rbx, %[m]" : [m] "=m" (reg_vals[1]));
    asm volatile("movq %%rcx, %[m]" : [m] "=m" (reg_vals[2]));
    asm volatile("movq %%rdx, %[m]" : [m] "=m" (reg_vals[3]));
    asm volatile("movq %%rdi, %[m]" : [m] "=m" (reg_vals[4]));
    asm volatile("movq %%rsi, %[m]" : [m] "=m" (reg_vals[5]));
    asm volatile("movq %%rbp, %[m]" : [m] "=m" (reg_vals[6]));
    asm volatile("movq %%rsp, %[m]" : [m] "=m" (reg_vals[7]));
    
    for (i = 0; i < 4; i++) {
        printk("%s=%8p  %s=%8p\n", reg_names[i], reg_vals[i], reg_names[i+1], reg_vals[i+1]);
    }
}
