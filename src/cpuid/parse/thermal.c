#include <cpuid/cpuid.h>
#include <cpuid/parse/thermal.h>
#include <specseek.h>
#include <stdio.h>

specseek_cpu_thermal specseek_get_cpu_thermal(void) {
    specseek_cpu_thermal info = {0, 0, 0, 0, 0};

    if (specseek_cpu_get_max_supported_leaf() < 0x06)
        return info;

    unsigned int eax, ebx, ecx, edx;
    cpuid(0x06, 0, &eax, &ebx, &ecx, &edx);

    info.dts                   = (unsigned char)((eax >> 0) & 1);
    info.turbo_boost           = (unsigned char)((eax >> 1) & 1);
    info.arat                  = (unsigned char)((eax >> 2) & 1);
    info.hwp_feedback          = (unsigned char)((ecx >> 0) & 1);
    info.energy_efficient_turbo = (unsigned char)((ecx >> 3) & 1);

    return info;
}