#pragma once
#include <specseek.h>

/// @brief extracts the CPU Vendor from CPUID
/// @return constant char pointer to the 13 byte vendor string, null terminated
const char *specseek_get_cpu_vendor_string();

/// @brief extracts the CPU Vendor from CPUID
/// @return CPU Vendor Enum Type
specseek_cpu_vendor_t specseek_get_cpu_vendor_type();

/// @brief extracts the CPU Brand name from CPUID
/// @return constant char pointer to the 49 byte brand string, null terminated
const char *specseek_get_cpu_brand_string();

/// @brief extracts the CPU base model value from CPUID
/// @return const int base model value
unsigned int specseek_get_cpu_base_model();

/// @brief extracts the CPU base model value from CPUID
/// @return const int base model value
unsigned int specseek_get_cpu_extended_model();

/// @brief extracts the CPU base family value from CPUID
/// @return unsigned base family value
unsigned int specseek_get_cpu_base_family();

/// @brief extracts the CPU extended family value from CPUID
/// @return unsigned base family value
unsigned int specseek_get_cpu_extended_family();

/// @brief extracts the full model value from CPUID using the base and extended model with the family
/// @return unsigned int full model value
unsigned int specseek_get_cpu_model();

/// @brief extracts the full family value from CPUID using the base and extended family
/// @return unsigned int full family value
unsigned int specseek_get_cpu_family();

/// @brief extracts the revision value from CPUID
/// @return unsigned int revision
unsigned int specseek_get_cpu_revision();