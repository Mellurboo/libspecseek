#include <cpuid/cpuid.h>
#include <cpuid/parse/address_space.h>
#include <specseek.h>

specseek_cpu_address_space specseek_get_cpu_address_space(void) {
    specseek_cpu_address_space info = {0, 0};

    if (specseek_cpu_get_max_supported_extended_leaf() < 0x80000008)
        return info;

    unsigned int eax, ebx, ecx, edx;
    cpuid(0x80000008, 0, &eax, &ebx, &ecx, &edx);

    info.physical_address_bits = (unsigned char)((eax >> 0) & 0xFF);
    info.virtual_address_bits  = (unsigned char)((eax >> 8) & 0xFF);

    return info;
}