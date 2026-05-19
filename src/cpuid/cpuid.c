void __cpuid(
    unsigned long    leaf,
    unsigned long    subleaf,
    unsigned long*   eax,
    unsigned long*   ebx,
    unsigned long*   ecx,
    unsigned long*   edx
){
    asm volatile("cpuid"
                    : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                    : "a"(leaf), "c"(subleaf));
}