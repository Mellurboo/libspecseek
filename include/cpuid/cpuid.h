#pragma once

void __cpuid(
    unsigned long    leaf,
    unsigned long    subleaf,
    unsigned long*   eax,
    unsigned long*   ebx,
    unsigned long*   ecx,
    unsigned long*   edx
);