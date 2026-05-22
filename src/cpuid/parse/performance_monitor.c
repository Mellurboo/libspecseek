#include <cpuid/cpuid.h>
#include <cpuid/parse/performance_monitor.h>
#include <specseek.h>

specseek_cpu_perfmon specseek_get_cpu_perfmon(void) {
    specseek_cpu_perfmon info = {0, 0, 0};

    // this is intel only, amd never implemented this into cpuid
    if (specseek_cpu_get_max_supported_leaf() < 0x0A)
        return info;

    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0A, 0, &eax, &ebx, &ecx, &edx);

    info.version               = (unsigned char)((eax >> 0) & 0xFF);
    info.general_counter_count = (unsigned char)((eax >> 8) & 0xFF);
    info.general_counter_width = (unsigned char)((eax >> 16) & 0xFF);

    return info;
}