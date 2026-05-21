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
    unsigned long        logical_processor_count;

} specseek_cpu_specifications;

typedef struct {

    // leaf 0x01 ECX
    unsigned char sse3          : 1;
    unsigned char pclmulqdq     : 1;
    unsigned char dtes64        : 1;
    unsigned char monitor       : 1;
    unsigned char ds_cpl        : 1;
    unsigned char vmx           : 1;
    unsigned char smx           : 1;
    unsigned char eist          : 1;
    unsigned char tm2           : 1;
    unsigned char ssse3         : 1;
    unsigned char cnxt_id       : 1;
    unsigned char sdbg          : 1;
    unsigned char fma           : 1;
    unsigned char cx16          : 1;
    unsigned char xtpr          : 1;
    unsigned char pdcm          : 1;
    unsigned char pcid          : 1;
    unsigned char dca           : 1;
    unsigned char sse4_1        : 1;
    unsigned char sse4_2        : 1;
    unsigned char x2apic        : 1;
    unsigned char movbe         : 1;
    unsigned char popcnt        : 1;
    unsigned char tsc_deadline  : 1;
    unsigned char aes           : 1;
    unsigned char xsave         : 1;
    unsigned char osxsave       : 1;
    unsigned char avx           : 1;
    unsigned char f16c          : 1;
    unsigned char rdrnd         : 1;
    unsigned char hypervisor    : 1;

    // leaf 0x01 EDX
    unsigned char fpu           : 1;
    unsigned char vme           : 1;
    unsigned char de            : 1;
    unsigned char pse           : 1;
    unsigned char tsc           : 1;
    unsigned char msr           : 1;
    unsigned char pae           : 1;
    unsigned char mce           : 1;
    unsigned char cx8           : 1;
    unsigned char apic          : 1;
    unsigned char sep           : 1;
    unsigned char mtrr          : 1;
    unsigned char pge           : 1;
    unsigned char mca           : 1;
    unsigned char cmov          : 1;
    unsigned char pat           : 1;
    unsigned char pse36         : 1;
    unsigned char psn           : 1;
    unsigned char clfsh         : 1;
    unsigned char ds            : 1;
    unsigned char acpi          : 1;
    unsigned char mmx           : 1;
    unsigned char fxsr          : 1;
    unsigned char sse           : 1;
    unsigned char sse2          : 1;
    unsigned char ss            : 1;
    unsigned char htt           : 1;
    unsigned char tm            : 1;
    unsigned char ia64          : 1;
    unsigned char pbe           : 1;

    // leaf 0x07 subleaf 0 EBX
    unsigned char fsgsbase      : 1;
    unsigned char tsc_adjust    : 1;
    unsigned char sgx           : 1;
    unsigned char bmi1          : 1;
    unsigned char hle           : 1;
    unsigned char avx2          : 1;
    unsigned char fdp_excptn    : 1;
    unsigned char smep          : 1;
    unsigned char bmi2          : 1;
    unsigned char erms          : 1;
    unsigned char invpcid       : 1;
    unsigned char rtm           : 1;
    unsigned char pqm           : 1;
    unsigned char mpx           : 1;
    unsigned char pqe           : 1;
    unsigned char avx512f       : 1;
    unsigned char avx512dq      : 1;
    unsigned char rdseed        : 1;
    unsigned char adx           : 1;
    unsigned char smap          : 1;
    unsigned char avx512ifma    : 1;
    unsigned char clflushopt    : 1;
    unsigned char clwb          : 1;
    unsigned char pt            : 1;
    unsigned char avx512pf      : 1;
    unsigned char avx512er      : 1;
    unsigned char avx512cd      : 1;
    unsigned char sha           : 1;
    unsigned char avx512bw      : 1;
    unsigned char avx512vl      : 1;

    // leaf 0x07 subleaf 0 ECX
    unsigned char prefetchwt1   : 1;
    unsigned char avx512vbmi    : 1;
    unsigned char umip          : 1;
    unsigned char pku           : 1;
    unsigned char ospke         : 1;
    unsigned char waitpkg       : 1;
    unsigned char avx512vbmi2   : 1;
    unsigned char shstk         : 1;
    unsigned char gfni          : 1;
    unsigned char vaes          : 1;
    unsigned char vpclmulqdq    : 1;
    unsigned char avx512vnni    : 1;
    unsigned char avx512bitalg  : 1;
    unsigned char tme           : 1;
    unsigned char avx512vpopcntdq : 1;
    unsigned char la57          : 1;
    unsigned char rdpid         : 1;
    unsigned char kl            : 1;
    unsigned char cldemote      : 1;
    unsigned char movdiri       : 1;
    unsigned char movdir64b     : 1;
    unsigned char enqcmd        : 1;
    unsigned char sgx_lc        : 1;
    unsigned char pks           : 1;

    // leaf 0x07 subleaf 0 EDX
    unsigned char avx512_4vnniw : 1;
    unsigned char avx512_4fmaps : 1;
    unsigned char fsrm          : 1;
    unsigned char uintr         : 1;
    unsigned char avx512vp2intersect : 1;
    unsigned char srbds_ctrl    : 1;
    unsigned char md_clear      : 1;
    unsigned char rtm_always_abort : 1;
    unsigned char tsx_force_abort : 1;
    unsigned char serialize     : 1;
    unsigned char hybrid        : 1;
    unsigned char tsxldtrk      : 1;
    unsigned char pconfig       : 1;
    unsigned char lbr           : 1;
    unsigned char ibt           : 1;
    unsigned char amx_bf16      : 1;
    unsigned char avx512fp16    : 1;
    unsigned char amx_tile      : 1;
    unsigned char amx_int8      : 1;
    unsigned char ibrs_ibpb     : 1;
    unsigned char stibp         : 1;
    unsigned char l1d_flush     : 1;
    unsigned char ia32_arch_cap : 1;
    unsigned char ia32_core_cap : 1;
    unsigned char ssbd          : 1;

    // leaf 0x07 subleaf 1 EAX
    unsigned char sha512        : 1;
    unsigned char sm3           : 1;
    unsigned char sm4           : 1;
    unsigned char rao_int       : 1;
    unsigned char avx_vnni      : 1;
    unsigned char avx512_bf16   : 1;
    unsigned char lass          : 1;
    unsigned char cmpccxadd     : 1;
    unsigned char archperfmon_ext : 1;
    unsigned char fzrm          : 1;
    unsigned char fsrs          : 1;
    unsigned char rsrcs         : 1;
    unsigned char fred          : 1;
    unsigned char lkgs          : 1;
    unsigned char wrmsrns       : 1;
    unsigned char amx_fp16      : 1;
    unsigned char hreset        : 1;
    unsigned char avx_ifma      : 1;
    unsigned char lam           : 1;
    unsigned char msrlist       : 1;

    // leaf 0x80000001 ECX (AMD/Intel extended)
    unsigned char lahf_lm       : 1;
    unsigned char cmp_legacy    : 1;
    unsigned char svm           : 1;
    unsigned char extapic       : 1;
    unsigned char cr8_legacy    : 1;
    unsigned char abm           : 1;    // on intel they call thsi lzcnt
    unsigned char sse4a         : 1;
    unsigned char misalignsse   : 1;
    unsigned char prefetch3dnow : 1;
    unsigned char osvw          : 1;
    unsigned char ibs           : 1;
    unsigned char xop           : 1;
    unsigned char skinit        : 1;
    unsigned char wdt           : 1;
    unsigned char lwp           : 1;
    unsigned char fma4          : 1;
    unsigned char tce           : 1;
    unsigned char nodeid_msr    : 1;
    unsigned char tbm           : 1;
    unsigned char topoext       : 1;
    unsigned char perfctr_core  : 1;
    unsigned char perfctr_nb    : 1;
    unsigned char bpext         : 1;
    unsigned char ptsc          : 1;
    unsigned char perfctr_llc   : 1;
    unsigned char mwaitx        : 1;

    // leaf 0x80000001 EDX
    unsigned char syscall       : 1;
    unsigned char mp            : 1;
    unsigned char nx            : 1;
    unsigned char mmxext        : 1;
    unsigned char fxsr_opt      : 1;
    unsigned char pdpe1gb       : 1;
    unsigned char rdtscp        : 1;
    unsigned char lm            : 1;
    unsigned char amd3dnowext   : 1;
    unsigned char amd3dnow      : 1;

} specseek_cpu_features;

/// @brief will populate the identifier struct with vendor, brand, model, family and revision
/// @param identifier_struct pointer to caller identifier structure
void specseek_set_cpuid_identifiers(specseek_cpu_identifiers *identifier_struct);

/// @brief populates the cpu cache struct with cache size values from CPUID in KiB
/// @param cpu_cache pointer to caller cache struct
void specseek_set_cpuid_cache(specseek_cpu_cache *cpu_cache);

/// @brief populates the specifications struct with physical core count, threads per core, and logical processor count
/// @param specs pointer to caller specifications structure
void specseek_set_cpuid_specifications(specseek_cpu_specifications *specs);

/// @brief populates the features struct with supported CPU feature flags discovered via CPUID
/// @param features pointer to caller features structure
void specseek_set_cpuid_features(specseek_cpu_features *features);