#pragma once

/// @brief front facing CPUID for libspecseek
/// @param leaf CPUID Lead Value
/// @param subleaf CPUID Sub-Leaf Value
/// @param eax int eax register
/// @param ebx int ebx register
/// @param ecx int ecx register
/// @param edx int edx register
void cpuid(
    unsigned int    leaf,
    unsigned int    subleaf,
    unsigned int*   eax,
    unsigned int*   ebx,
    unsigned int*   ecx,
    unsigned int*   edx
);

/// @brief gets the max supported standard leaf this hardware implementation of CPUID supports
/// @param VOID
/// @return max supported leaf (STANDARD LEAF)
unsigned int specseek_cpu_get_max_supported_leaf(void);

/// @brief gets the max supported extended leaf this hardware implementation of CPUID supports
/// @param VOID
/// @return max supported leaf (EXTENDED LEAF)
unsigned int specseek_cpu_get_max_supported_extended_leaf(void);