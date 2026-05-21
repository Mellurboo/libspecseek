#include <specseek.h>
#include <string.h>
#include <cpuid/parse/identifiers.h>
#include <cpuid/parse/cache.h>
#include <cpuid/parse/specifications.h>
#include <cpuid/parse/features.h>


/// @brief will populate the identifier struct with vendor, brand, model, family and revision
/// @param identifier_struct pointer to caller identifier structure
void specseek_set_cpuid_identifiers(specseek_cpu_identifiers *identifier_struct){
    memcpy(identifier_struct->CPU_VENDOR_STRING,
                specseek_get_cpu_vendor_string(),
                sizeof(identifier_struct->CPU_VENDOR_STRING)
            );
    identifier_struct->CPU_VENDOR_TYPE = specseek_get_cpu_vendor_type();

    memcpy(identifier_struct->CPU_BRAND_STRING,
                specseek_get_cpu_brand_string(),
                sizeof(identifier_struct->CPU_BRAND_STRING)
            );

    identifier_struct->CPU_MODEL_BASE = specseek_get_cpu_base_model();
    identifier_struct->CPU_MODEL_EXTENDED = specseek_get_cpu_extended_model();
    identifier_struct->CPU_MODEL = specseek_get_cpu_model();

    identifier_struct->CPU_FAMILY_BASE = specseek_get_cpu_base_family();
    identifier_struct->CPU_FAMILY_EXTENDED = specseek_get_cpu_extended_family();
    identifier_struct->CPU_FAMILY = specseek_get_cpu_family();

    identifier_struct->CPU_REVISION = specseek_get_cpu_revision();
}

void specseek_set_cpuid_cache(specseek_cpu_cache *cpu_cache){
    specseek_cpu_cache discovered_cache = cpu_get_cache_info();
    cpu_cache->L1_DATA_CACHE = discovered_cache.L1_DATA_CACHE;
    cpu_cache->L1_INSTRUCTION_CACHE = discovered_cache.L1_INSTRUCTION_CACHE;
    cpu_cache->L2_CACHE = discovered_cache.L2_CACHE;
    cpu_cache->L3_CACHE = discovered_cache.L3_CACHE;
}

void specseek_set_cpuid_specifications(specseek_cpu_specifications *specs){
    specseek_cpu_specifications discovered_specs = specseek_get_cpu_specifications();
    specs->physical_core_count     = discovered_specs.physical_core_count;
    specs->threads_per_core        = discovered_specs.threads_per_core;
    specs->logical_processor_count = discovered_specs.logical_processor_count;
}

void specseek_set_cpuid_features(specseek_cpu_features *features){
    specseek_cpu_features discovered_features = specseek_get_cpu_features();
    *features = discovered_features;
}