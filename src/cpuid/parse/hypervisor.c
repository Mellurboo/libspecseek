#include <cpuid/cpuid.h>
#include <cpuid/parse/hypervisor.h>
#include <specseek.h>
#include <string.h>

specseek_cpu_hypervisor specseek_get_cpu_hypervisor(void) {
    specseek_cpu_hypervisor info;
    memset(&info, 0, sizeof(info));

    /*
        The hypervisor present bit is ECX[31] of leaf 0x01. Bare-metal CPUs
        always return 0 here; hypervisors are required to set it.
    */
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x01, 0, &eax, &ebx, &ecx, &edx);

    if (!((ecx >> 31) & 1))
        return info;

    info.present = 1;

    //12-byte vendor string in the same layout as the standard vendor string at leaf 0x00
    cpuid(0x40000000, 0, &eax, &ebx, &ecx, &edx);

    memcpy(info.vendor_string + 0, &ebx, 4);
    memcpy(info.vendor_string + 4, &ecx, 4);
    memcpy(info.vendor_string + 8, &edx, 4);
    info.vendor_string[HYPERVISOR_VENDOR_STRING_LENGTH - 1] = '\0';

    return info;
}