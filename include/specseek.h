#pragma once

#define CPU_VENDOR_STRING_LENGTH    13
#define CPU_BRAND_STRING_LENGTH     49

typedef enum specseek_cpu_vendor{
    AMD,
    Intel,
    Unknown
} specseek_cpu_vendor_t;

typedef struct {    
    // Vendor & Processor Information
    specseek_cpu_vendor_t CPU_VENDOR_TYPE;

    char                CPU_VENDOR_STRING[CPU_VENDOR_STRING_LENGTH];
    char                CPU_BRAND_STRING[CPU_BRAND_STRING_LENGTH];

    // Model, Extended Model, Full Model
    unsigned int        CPU_MODEL;
    unsigned int        CPU_MODEL_BASE;
    unsigned int        CPU_MODEL_EXTENDED;

    // Family Information
    unsigned int        CPU_FAMILY;
    unsigned int        CPU_FAMILY_BASE;
    unsigned int        CPU_FAMILY_EXTENDED;

    // Revision
    unsigned int        CPU_REVISION;
} specseek_cpu_identifiers;

typedef struct {
    unsigned int L1_DATA_CACHE;
    unsigned int L1_INSTRUCTION_CACHE;
    unsigned int L2_CACHE;
    unsigned int L3_CACHE;
} specseek_cpu_cache;

typedef struct {
    // core information
    unsigned long        physical_core_count;
    unsigned long        threads_per_core;
    unsigned long        local_processor_count;

    // cache information
    specseek_cpu_cache  cpu_cache_statistics;
} specseek_cpu_specifications;

/// @brief will populate the identifier struct with vendor, brand, model, family and revision
/// @param identifier_struct pointer to caller identifier structure
void specseek_set_cpuid_identifiers(specseek_cpu_identifiers *identifier_struct);

/// @brief populates the cpu cache struct with cache size values from CPUID in KiB
/// @param cpu_cache pointer to caller cache struct
void specseek_set_cpuid_cache(specseek_cpu_cache *cpu_cache);