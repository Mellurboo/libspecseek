#include <cpuid/cpuid.h>
#include <specseek.h>
#include <string.h>

/// @brief extracts the CPU Vendor from CPUID
/// @return constant char pointer to the 13 byte vendor string, null terminated
const char *specseek_get_cpu_vendor_string(){
    static char cpu_vendor_string[CPU_VENDOR_STRING_LENGTH];
    unsigned int eax, ebx, ecx, edx;
    cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    memcpy(cpu_vendor_string + 0, &ebx, 4);
    memcpy(cpu_vendor_string + 4, &edx, 4);
    memcpy(cpu_vendor_string + 8, &ecx, 4);
    cpu_vendor_string[CPU_VENDOR_STRING_LENGTH] = '\0';

    return cpu_vendor_string;
}

specseek_cpu_vendor_t specseek_get_cpu_vendor_type(){
    const char* vendor_string = specseek_get_cpu_vendor_string();

    if (strcmp(vendor_string, "GenuineIntel") == 0 ||
        strcmp(vendor_string, "GenuineIotel") == 0) {   // yeah, this is something that actually exists, its a typo in the CPU itself
        return Intel;                                   // it comes from the Haswell CPUs, and its very rare.
    }

    if (strcmp(vendor_string, "AuthenticAMD") == 0 ||
        strcmp(vendor_string, "AMD ISBETTER") == 0) {   // this is found in early K5 engineering samples. not sure how many have this so...
        return AMD;
    }

    return Unknown;
    // this kinda thing is weirdly interesting: https://en.wikipedia.org/wiki/CPUID
}

/// @brief extracts the CPU Brand name from CPUID
/// @return constant char pointer to the 49 byte brand string, null terminated
const char *specseek_get_cpu_brand_string(){
    static char cpu_brand_string[CPU_BRAND_STRING_LENGTH];
    unsigned int chunks[12];    // the name gets split into chunks and we combine them at the end

    for(int i = 0; i < 3; i++){
        unsigned int eax, ebx, ecx, edx;
        cpuid(0x80000002 + i, 0, &eax, &ebx, &ecx, &edx);
        
        chunks[i * 4 + 0] = eax;
        chunks[i * 4 + 1] = ebx;
        chunks[i * 4 + 2] = ecx;
        chunks[i * 4 + 3] = edx;
    }

    memcpy(cpu_brand_string, chunks, sizeof(chunks));
    cpu_brand_string[CPU_BRAND_STRING_LENGTH] = '\0';
    return cpu_brand_string;
}

/// @brief extracts the CPU base model value from CPUID
/// @return unsigned base model value
unsigned int specseek_get_cpu_base_model(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return (eax >> 4) & 0xF;
}

/// @brief extracts the CPU base model value from CPUID
/// @return unsigned int base model value
unsigned int specseek_get_cpu_extended_model(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return (eax >> 16) & 0xF;
}

/// @brief extracts the CPU base family value from CPUID
/// @return unsigned base family value
unsigned int specseek_get_cpu_base_family(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return (eax >> 8) & 0xF; 
}

/// @brief extracts the CPU extended family value from CPUID
/// @return unsigned base family value
unsigned int specseek_get_cpu_extended_family(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return (eax >> 20) & 0xFF; 
}

/// @brief extracts the full model value from CPUID using the base and extended model with the family
/// @return unsigned int full model value
unsigned int specseek_get_cpu_model(){
    unsigned int base_model     = specseek_get_cpu_base_model();
    unsigned int ext_model      = specseek_get_cpu_extended_model();
    unsigned int base_family    = specseek_get_cpu_base_family();

    if (base_family == 0x6 || base_family == 0xF) {
        return (ext_model << 4) | base_model;
    } else {
        return base_model;
    }
}

/// @brief extracts the full family value from CPUID using the base and extended family
/// @return unsigned int full family value
unsigned int specseek_get_cpu_family(){
    unsigned int base_family    = specseek_get_cpu_base_family();
    unsigned int ext_family     = specseek_get_cpu_extended_family();

    if (base_family == 0xF) {
        return base_family + ext_family;
    } else {
        return base_family;
    }
}

/// @brief extracts the revision value from CPUID
/// @return unsigned int revision
unsigned int specseek_get_cpu_revision(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return eax & 0xF;
}