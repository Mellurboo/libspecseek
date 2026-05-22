#include <cpuid/cpuid.h>
#include <cpuid/parse/identifiers.h>
#include <specseek.h>
#include <string.h>

specseek_cpu_cache cpu_get_cache_info(void) {
    unsigned int eax, ebx, ecx, edx;
    specseek_cpu_cache info         = {0, 0, 0, 0};
    specseek_cpu_vendor_t vendor    = specseek_get_cpu_vendor_type();

    /*
        Intel leaf 0x04: Pentium 4 and Later
    */
    if (vendor == Intel && specseek_cpu_get_max_supported_leaf() >= 0x04) {
        unsigned int level = 0;
        while (1) {
            cpuid(0x04, level, &eax, &ebx, &ecx, &edx);
            unsigned int cache_type = eax & 0x1F;
            if (cache_type == 0) break;

            unsigned int cache_level = (eax >> 5) & 0x7;
            unsigned int ways        = ((ebx >> 22) & 0x3FF) + 1;
            unsigned int partitions  = ((ebx >> 12) & 0x3FF) + 1;
            unsigned int line_size   = (ebx & 0xFFF) + 1;
            unsigned int sets        = ecx + 1;
            unsigned int size_kb     = (ways * partitions * line_size * sets) / 1024;

            switch (cache_level) {
                case 1:
                    if      (cache_type == 1) info.L1_data_cache = size_kb;
                    else if (cache_type == 2) info.L1_instruction_cache = size_kb;
                    break;
                case 2: info.L2_cache = size_kb; break;
                case 3: info.L3_cache = size_kb; break;
            }
            level++;
        }
        return info;
    }

    /*
        AMD Zen+, same as intel but uses a different leaf, catches unknown vendors and will
        fall back to the legacy pre-zen cache layout if it finishes this procedure with no data
    */
    if ((vendor == AMD || vendor != Intel) && specseek_cpu_get_max_supported_extended_leaf() >= 0x8000001D) {
        unsigned int level = 0;
        while (1) {
            cpuid(0x8000001D, level, &eax, &ebx, &ecx, &edx);
            unsigned int cache_type = eax & 0x1F;
            if (cache_type == 0) break;

            unsigned int cache_level = (eax >> 5) & 0x7;
            unsigned int ways        = ((ebx >> 22) & 0x3FF) + 1;
            unsigned int partitions  = ((ebx >> 12) & 0x3FF) + 1;
            unsigned int line_size   = (ebx & 0xFFF) + 1;
            unsigned int sets        = ecx + 1;
            unsigned int size_kb     = (ways * partitions * line_size * sets) / 1024;

            switch (cache_level) {
                case 1:
                    if      (cache_type == 1) info.L1_data_cache = size_kb;
                    else if (cache_type == 2) info.L1_instruction_cache = size_kb;
                    break;
                case 2: info.L2_cache = size_kb; break;
                case 3: info.L3_cache = size_kb; break;
            }
            level++;
        }
        if (info.L1_data_cache || info.L1_instruction_cache || info.L2_cache || info.L3_cache)
            return info;
    }

    /*
        Pre-Zen Legcay AMD
        (Bulldozer, Phenom, Athlon) and will handle vms that stub this with zeros
    */
    if (specseek_cpu_get_max_supported_extended_leaf() >= 0x80000005) {
        cpuid(0x80000005, 0, &eax, &ebx, &ecx, &edx);
        info.L1_data_cache = (ecx >> 24) & 0xFF;
        info.L1_instruction_cache = (edx >> 24) & 0xFF;
    }

    if (specseek_cpu_get_max_supported_extended_leaf() >= 0x80000006) {
        cpuid(0x80000006, 0, &eax, &ebx, &ecx, &edx);
        info.L2_cache = (ecx >> 16) & 0xFFFF;
        info.L3_cache = ((edx >> 18) & 0x3FFF) * 512;
    }

    return info;
}