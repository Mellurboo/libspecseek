#include <cpuid/cpuid.h>
#include <cpuid/parse/frequency.h>
#include <specseek.h>

specseek_cpu_frequency specseek_get_cpu_frequency(void) {
    specseek_cpu_frequency info = {0, 0, 0};

    //only meaningful on Intel Skylake (2015) and later
    if (specseek_cpu_get_max_supported_leaf() < 0x16)
        return info;

    unsigned int eax, ebx, ecx, edx;
    cpuid(0x16, 0, &eax, &ebx, &ecx, &edx);

    info.base_mhz = eax & 0xFFFF;
    info.max_mhz  = ebx & 0xFFFF;
    info.bus_mhz  = ecx & 0xFFFF;

    return info;
}