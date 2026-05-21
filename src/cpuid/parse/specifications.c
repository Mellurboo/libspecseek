#include <cpuid/cpuid.h>
#include <cpuid/parse/identifiers.h>
#include <specseek.h>

/*
    Attempts to read core/thread topology from Intel leaf 0x0B
    Available on Nehalem and later Intel CPUs.
    Returns 1 on success, 0 if the leaf is unsupported or returns no data.
*/
static int intel_specifications(specseek_cpu_specifications *specs) {
    unsigned int eax, ebx, ecx, edx;

    if (specseek_cpu_get_max_supported_leaf() < 0x0B)
        return 0;

    cpuid(0x0B, 0, &eax, &ebx, &ecx, &edx);
    if (ebx == 0)
        return 0;

    unsigned int smt_logical = ebx & 0xFFFF;    // logical processors per core (SMT level)

    cpuid(0x0B, 1, &eax, &ebx, &ecx, &edx);
    unsigned int core_logical = ebx & 0xFFFF;   // logical processors per package (core level)

    if (smt_logical == 0 || core_logical == 0)
        return 0;

    specs->logical_processor_count = core_logical;
    specs->physical_core_count     = core_logical / smt_logical;
    specs->threads_per_core        = smt_logical;
    return 1;
}

/*
    leaf 0x01 gives logical processor count as seen by the APIC.
    On single-core chips this is 1. No physical core count is available this way, so we
    check the HTT flag (EDX bit 28) to make an educated guess on threads per core.
    Works on Pentium 4 and later.
*/
static int intel_specifications_legacy(specseek_cpu_specifications *specs) {
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x01, 0, &eax, &ebx, &ecx, &edx);

    unsigned int logical = (ebx >> 16) & 0xFF;
    if (logical == 0) logical = 1;

    int htt = (edx >> 28) & 0x1;

    specs->logical_processor_count = logical;
    specs->threads_per_core        = htt ? 2 : 1;
    specs->physical_core_count     = logical / specs->threads_per_core;
    if (specs->physical_core_count == 0) specs->physical_core_count = 1;
    return 1;
}

/*
    AMD Zen+ (2018+): leaf 0x8000001E reports threads per core directly.
    Combined with 0x80000008 for physical core count.
*/
static int amd_specifications(specseek_cpu_specifications *specs) {
    if (specseek_cpu_get_max_supported_extended_leaf() < 0x8000001E)
        return 0;

    unsigned int eax, ebx, ecx, edx;

    cpuid(0x80000008, 0, &eax, &ebx, &ecx, &edx);
    unsigned int physical_cores = (ecx & 0xFF) + 1;

    cpuid(0x8000001E, 0, &eax, &ebx, &ecx, &edx);
    unsigned int threads_per_core = ((ebx >> 8) & 0xFF) + 1;

    specs->physical_core_count     = physical_cores;
    specs->threads_per_core        = threads_per_core;
    specs->logical_processor_count = physical_cores * threads_per_core;
    return 1;
}

/*
    AMD legacy (Bulldozer, Phenom, Athlon): leaf 0x80000008 ECX[7:0] gives
    (core count - 1). No SMT info available this way so threads_per_core is
    inferred from the leaf 0x01 HTT flag, same as the Intel fallback.
*/
static int amd_specifications_legacy(specseek_cpu_specifications *specs) {
    if (specseek_cpu_get_max_supported_extended_leaf() < 0x80000008)
        return 0;

    unsigned int eax, ebx, ecx, edx;

    cpuid(0x80000008, 0, &eax, &ebx, &ecx, &edx);
    unsigned int physical_cores = (ecx & 0xFF) + 1;

    cpuid(0x01, 0, &eax, &ebx, &ecx, &edx);
    int htt = (edx >> 28) & 0x1;

    specs->physical_core_count     = physical_cores;
    specs->threads_per_core        = htt ? 2 : 1;
    specs->logical_processor_count = physical_cores * specs->threads_per_core;
    return 1;
}

specseek_cpu_specifications specseek_get_cpu_specifications(void) {
    specseek_cpu_specifications specs = {1, 1, 1};

    specseek_cpu_vendor_t vendor = specseek_get_cpu_vendor_type();

    if (vendor == Intel) {
        if (intel_specifications(&specs))        return specs;
        if (intel_specifications_legacy(&specs)) return specs;
    }

    if (vendor == AMD) {
        if (amd_specifications(&specs))          return specs;
        if (amd_specifications_legacy(&specs))   return specs;
        if (intel_specifications_legacy(&specs)) return specs;
    }

    if (intel_specifications(&specs))       return specs;
    if (amd_specifications(&specs))         return specs;
    if (amd_specifications_legacy(&specs))  return specs;
    intel_specifications_legacy(&specs);

    return specs;
}