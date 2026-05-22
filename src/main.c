#include <specseek.h>
#include <string.h>
#include <cpuid/parse/identifiers.h>
#include <cpuid/parse/cache.h>
#include <cpuid/parse/features.h>
#include <cpuid/parse/specifications.h>
#include <cpuid/parse/address_space.h>
#include <cpuid/parse/frequency.h>
#include <cpuid/parse/hypervisor.h>
#include <cpuid/parse/thermal.h>
#include <cpuid/parse/performance_monitor.h>


/// @brief will populate the identifier struct with vendor, brand, model, family and revision
/// @param identifier_struct pointer to caller identifier structure
void specseek_set_cpuid_identifiers(specseek_cpu_identifiers *identifier_struct){
    memcpy(identifier_struct->cpu_vendor_string,
                specseek_get_cpu_vendor_string(),
                sizeof(identifier_struct->cpu_vendor_string)
            );
    identifier_struct->cpu_vendor_type = specseek_get_cpu_vendor_type();

    memcpy(identifier_struct->cpu_brand_string,
                specseek_get_cpu_brand_string(),
                sizeof(identifier_struct->cpu_brand_string)
            );

    identifier_struct->cpu_model_base = specseek_get_cpu_base_model();
    identifier_struct->cpu_model_extended = specseek_get_cpu_extended_model();
    identifier_struct->cpu_model = specseek_get_cpu_model();

    identifier_struct->cpu_family_base = specseek_get_cpu_base_family();
    identifier_struct->cpu_family_extended = specseek_get_cpu_extended_family();
    identifier_struct->cpu_family = specseek_get_cpu_family();

    identifier_struct->cpu_revision = specseek_get_cpu_revision();
}

void specseek_set_cpuid_cache(specseek_cpu_cache *cpu_cache){
    specseek_cpu_cache discovered_cache = cpu_get_cache_info();
    cpu_cache->L1_data_cache = discovered_cache.L1_data_cache;
    cpu_cache->L1_instruction_cache = discovered_cache.L1_instruction_cache;
    cpu_cache->L2_cache = discovered_cache.L2_cache;
    cpu_cache->L3_cache = discovered_cache.L3_cache;
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

void specseek_set_cpuid_address_space(specseek_cpu_address_space *info){
    specseek_cpu_address_space discovered = specseek_get_cpu_address_space();
    info->physical_address_bits = discovered.physical_address_bits;
    info->virtual_address_bits  = discovered.virtual_address_bits;
}

void specseek_set_cpuid_frequency(specseek_cpu_frequency *info){
    specseek_cpu_frequency discovered = specseek_get_cpu_frequency();
    info->base_mhz = discovered.base_mhz;
    info->max_mhz  = discovered.max_mhz;
    info->bus_mhz  = discovered.bus_mhz;
}

void specseek_set_cpuid_hypervisor(specseek_cpu_hypervisor *info){
    specseek_cpu_hypervisor discovered = specseek_get_cpu_hypervisor();
    info->present = discovered.present;
    memcpy(info->vendor_string, discovered.vendor_string, HYPERVISOR_VENDOR_STRING_LENGTH);
}

void specseek_set_cpuid_thermal(specseek_cpu_thermal *info){
    specseek_cpu_thermal discovered = specseek_get_cpu_thermal();
    info->dts                    = discovered.dts;
    info->turbo_boost            = discovered.turbo_boost;
    info->arat                   = discovered.arat;
    info->hwp_feedback           = discovered.hwp_feedback;
    info->energy_efficient_turbo = discovered.energy_efficient_turbo;
}

void specseek_set_cpuid_perfmon(specseek_cpu_perfmon *info){
    specseek_cpu_perfmon discovered = specseek_get_cpu_perfmon();
    info->version               = discovered.version;
    info->general_counter_count = discovered.general_counter_count;
    info->general_counter_width = discovered.general_counter_width;
}