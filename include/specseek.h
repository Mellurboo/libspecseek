#pragma once

typedef struct {    
    // Vendor & Processor Information
    char                CPU_VENDOR_STRING[13];
    char                CPU_BRAND_STRING[49];

    // Model, Extended Model
    unsigned long        CPU_MODEL_BASE;
    unsigned long        CPU_MODEL_EXTENDED;

    // Family Information
    unsigned long        CPU_FAMILY_BASE;
    unsigned long        CPU_FAMILY_EXTENDED;

    // Revision
    unsigned long        CPU_REVISION;
} specseek_cpu_identifiers;

typedef struct {
    unsigned int L1_DATA_CACHE;
    unsigned int l1_INSTRUCTION_CACHE;
    unsigned int L2_CACHE;
    unsigned int l3_CACHE;
} specseek_cpu_cache;

typedef struct {
    // core information
    unsigned long        physical_core_count;
    unsigned long        threads_per_core;
    unsigned long        local_processor_count;

    // cache information
    specseek_cpu_cache  cpu_cache_statistics;
} specseek_cpu_specifications;