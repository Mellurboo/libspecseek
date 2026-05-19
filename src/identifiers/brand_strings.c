#include <cpuid/cpuid.h>
#include <string.h>

const char *specseek_get_vendor_string(){
    static char cpu_vendor_string[13];
    unsigned int eax, ebx, ecx, edx;
    __cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    memcpy(cpu_vendor_string + 0, &ebx, 4);
    memcpy(cpu_vendor_string + 4, &ebx, 4);
    memcpy(cpu_vendor_string + 8, &ebx, 4);
    cpu_vendor_string[13] = '\0';

    return cpu_vendor_string;
}