#include <cpuid/cpuid.h>
#include <cpuid/parse/features.h>
#include <specseek.h>

static int check_bit(unsigned int val, unsigned int bit) {
    return (val >> bit) & 1;
}

static void specseek_cpuid_feature_leaf_01(specseek_cpu_features *f) {
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x01, 0, &eax, &ebx, &ecx, &edx);

    // ECX
    f->sse3         = check_bit(ecx,  0);
    f->pclmulqdq    = check_bit(ecx,  1);
    f->dtes64       = check_bit(ecx,  2);
    f->monitor      = check_bit(ecx,  3);
    f->ds_cpl       = check_bit(ecx,  4);
    f->vmx          = check_bit(ecx,  5);
    f->smx          = check_bit(ecx,  6);
    f->eist         = check_bit(ecx,  7);
    f->tm2          = check_bit(ecx,  8);
    f->ssse3        = check_bit(ecx,  9);
    f->cnxt_id      = check_bit(ecx, 10);
    f->sdbg         = check_bit(ecx, 11);
    f->fma          = check_bit(ecx, 12);
    f->cx16         = check_bit(ecx, 13);
    f->xtpr         = check_bit(ecx, 14);
    f->pdcm         = check_bit(ecx, 15);
    f->pcid         = check_bit(ecx, 17);
    f->dca          = check_bit(ecx, 18);
    f->sse4_1       = check_bit(ecx, 19);
    f->sse4_2       = check_bit(ecx, 20);
    f->x2apic       = check_bit(ecx, 21);
    f->movbe        = check_bit(ecx, 22);
    f->popcnt       = check_bit(ecx, 23);
    f->tsc_deadline = check_bit(ecx, 24);
    f->aes          = check_bit(ecx, 25);
    f->xsave        = check_bit(ecx, 26);
    f->osxsave      = check_bit(ecx, 27);
    f->avx          = check_bit(ecx, 28);
    f->f16c         = check_bit(ecx, 29);
    f->rdrnd        = check_bit(ecx, 30);
    f->hypervisor   = check_bit(ecx, 31);

    // EDX
    f->fpu          = check_bit(edx,  0);
    f->vme          = check_bit(edx,  1);
    f->de           = check_bit(edx,  2);
    f->pse          = check_bit(edx,  3);
    f->tsc          = check_bit(edx,  4);
    f->msr          = check_bit(edx,  5);
    f->pae          = check_bit(edx,  6);
    f->mce          = check_bit(edx,  7);
    f->cx8          = check_bit(edx,  8);
    f->apic         = check_bit(edx,  9);
    f->sep          = check_bit(edx, 11);
    f->mtrr         = check_bit(edx, 12);
    f->pge          = check_bit(edx, 13);
    f->mca          = check_bit(edx, 14);
    f->cmov         = check_bit(edx, 15);
    f->pat          = check_bit(edx, 16);
    f->pse36        = check_bit(edx, 17);
    f->psn          = check_bit(edx, 18);
    f->clfsh        = check_bit(edx, 19);
    f->ds           = check_bit(edx, 21);
    f->acpi         = check_bit(edx, 22);
    f->mmx          = check_bit(edx, 23);
    f->fxsr         = check_bit(edx, 24);
    f->sse          = check_bit(edx, 25);
    f->sse2         = check_bit(edx, 26);
    f->ss           = check_bit(edx, 27);
    f->htt          = check_bit(edx, 28);
    f->tm           = check_bit(edx, 29);
    f->ia64         = check_bit(edx, 30);
    f->pbe          = check_bit(edx, 31);
}

static void specseek_cpuid_feature_leaf_7_subleaf_0(specseek_cpu_features *f) {
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x07, 0, &eax, &ebx, &ecx, &edx);

    // EBX
    f->fsgsbase         = check_bit(ebx,  0);
    f->tsc_adjust       = check_bit(ebx,  1);
    f->sgx              = check_bit(ebx,  2);
    f->bmi1             = check_bit(ebx,  3);
    f->hle              = check_bit(ebx,  4);
    f->avx2             = check_bit(ebx,  5);
    f->fdp_excptn       = check_bit(ebx,  6);
    f->smep             = check_bit(ebx,  7);
    f->bmi2             = check_bit(ebx,  8);
    f->erms             = check_bit(ebx,  9);
    f->invpcid          = check_bit(ebx, 10);
    f->rtm              = check_bit(ebx, 11);
    f->pqm              = check_bit(ebx, 12);
    f->mpx              = check_bit(ebx, 14);
    f->pqe              = check_bit(ebx, 15);
    f->avx512f          = check_bit(ebx, 16);
    f->avx512dq         = check_bit(ebx, 17);
    f->rdseed           = check_bit(ebx, 18);
    f->adx              = check_bit(ebx, 19);
    f->smap             = check_bit(ebx, 20);
    f->avx512ifma       = check_bit(ebx, 21);
    f->clflushopt       = check_bit(ebx, 23);
    f->clwb             = check_bit(ebx, 24);
    f->pt               = check_bit(ebx, 25);
    f->avx512pf         = check_bit(ebx, 26);
    f->avx512er         = check_bit(ebx, 27);
    f->avx512cd         = check_bit(ebx, 28);
    f->sha              = check_bit(ebx, 29);
    f->avx512bw         = check_bit(ebx, 30);
    f->avx512vl         = check_bit(ebx, 31);

    // ECX
    f->prefetchwt1      = check_bit(ecx,  0);
    f->avx512vbmi       = check_bit(ecx,  1);
    f->umip             = check_bit(ecx,  2);
    f->pku              = check_bit(ecx,  3);
    f->ospke            = check_bit(ecx,  4);
    f->waitpkg          = check_bit(ecx,  5);
    f->avx512vbmi2      = check_bit(ecx,  6);
    f->shstk            = check_bit(ecx,  7);
    f->gfni             = check_bit(ecx,  8);
    f->vaes             = check_bit(ecx,  9);
    f->vpclmulqdq       = check_bit(ecx, 10);
    f->avx512vnni       = check_bit(ecx, 11);
    f->avx512bitalg     = check_bit(ecx, 12);
    f->tme              = check_bit(ecx, 13);
    f->avx512vpopcntdq  = check_bit(ecx, 14);
    f->la57             = check_bit(ecx, 16);
    f->rdpid            = check_bit(ecx, 22);
    f->kl               = check_bit(ecx, 23);
    f->cldemote         = check_bit(ecx, 25);
    f->movdiri          = check_bit(ecx, 27);
    f->movdir64b        = check_bit(ecx, 28);
    f->enqcmd           = check_bit(ecx, 29);
    f->sgx_lc           = check_bit(ecx, 30);
    f->pks              = check_bit(ecx, 31);

    // EDX
    f->avx512_4vnniw        = check_bit(edx,  2);
    f->avx512_4fmaps        = check_bit(edx,  3);
    f->fsrm                 = check_bit(edx,  4);
    f->uintr                = check_bit(edx,  5);
    f->avx512vp2intersect   = check_bit(edx,  8);
    f->srbds_ctrl           = check_bit(edx,  9);
    f->md_clear             = check_bit(edx, 10);
    f->rtm_always_abort     = check_bit(edx, 11);
    f->tsx_force_abort      = check_bit(edx, 13);
    f->serialize            = check_bit(edx, 14);
    f->hybrid               = check_bit(edx, 15);
    f->tsxldtrk             = check_bit(edx, 16);
    f->pconfig              = check_bit(edx, 18);
    f->lbr                  = check_bit(edx, 19);
    f->ibt                  = check_bit(edx, 20);
    f->amx_bf16             = check_bit(edx, 22);
    f->avx512fp16           = check_bit(edx, 23);
    f->amx_tile             = check_bit(edx, 24);
    f->amx_int8             = check_bit(edx, 25);
    f->ibrs_ibpb            = check_bit(edx, 26);
    f->stibp                = check_bit(edx, 27);
    f->l1d_flush            = check_bit(edx, 28);
    f->ia32_arch_cap        = check_bit(edx, 29);
    f->ia32_core_cap        = check_bit(edx, 30);
    f->ssbd                 = check_bit(edx, 31);
}

/*
    Leaf 0x07 subleaf 1 reports newer features: SHA-512, AVX-VNNI, AVX-512-BF16 etc.
    EAX reports the max subleaf so we check that before querying subleaf 1.
*/
static void specseek_cpuid_feature_leaf_7_subleaf_1(specseek_cpu_features *f) {
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x07, 0, &eax, &ebx, &ecx, &edx);
    if (eax < 1) return;

    cpuid(0x07, 1, &eax, &ebx, &ecx, &edx);

    f->sha512           = check_bit(eax,  0);
    f->sm3              = check_bit(eax,  1);
    f->sm4              = check_bit(eax,  2);
    f->rao_int          = check_bit(eax,  3);
    f->avx_vnni         = check_bit(eax,  4);
    f->avx512_bf16      = check_bit(eax,  5);
    f->lass             = check_bit(eax,  6);
    f->cmpccxadd        = check_bit(eax,  7);
    f->archperfmon_ext  = check_bit(eax,  8);
    f->fzrm             = check_bit(eax, 10);
    f->fsrs             = check_bit(eax, 11);
    f->rsrcs            = check_bit(eax, 12);
    f->fred             = check_bit(eax, 17);
    f->lkgs             = check_bit(eax, 18);
    f->wrmsrns          = check_bit(eax, 19);
    f->amx_fp16         = check_bit(eax, 21);
    f->hreset           = check_bit(eax, 22);
    f->avx_ifma         = check_bit(eax, 23);
    f->lam              = check_bit(eax, 26);
    f->msrlist          = check_bit(eax, 27);
}

static void specseek_cpuid_feature_leaf_80000001(specseek_cpu_features *f) {
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x80000001, 0, &eax, &ebx, &ecx, &edx);

    // ECX
    f->lahf_lm          = check_bit(ecx,  0);
    f->cmp_legacy       = check_bit(ecx,  1);
    f->svm              = check_bit(ecx,  2);
    f->extapic          = check_bit(ecx,  3);
    f->cr8_legacy       = check_bit(ecx,  4);
    f->abm              = check_bit(ecx,  5);
    f->sse4a            = check_bit(ecx,  6);
    f->misalignsse      = check_bit(ecx,  7);
    f->prefetch3dnow    = check_bit(ecx,  8);
    f->osvw             = check_bit(ecx,  9);
    f->ibs              = check_bit(ecx, 10);
    f->xop              = check_bit(ecx, 11);
    f->skinit           = check_bit(ecx, 12);
    f->wdt              = check_bit(ecx, 13);
    f->lwp              = check_bit(ecx, 15);
    f->fma4             = check_bit(ecx, 16);
    f->tce              = check_bit(ecx, 17);
    f->nodeid_msr       = check_bit(ecx, 19);
    f->tbm              = check_bit(ecx, 21);
    f->topoext          = check_bit(ecx, 22);
    f->perfctr_core     = check_bit(ecx, 23);
    f->perfctr_nb       = check_bit(ecx, 24);
    f->bpext            = check_bit(ecx, 26);
    f->ptsc             = check_bit(ecx, 27);
    f->perfctr_llc      = check_bit(ecx, 28);
    f->mwaitx           = check_bit(ecx, 29);

    // EDX
    f->syscall          = check_bit(edx, 11);
    f->mp               = check_bit(edx, 19);
    f->nx               = check_bit(edx, 20);
    f->mmxext           = check_bit(edx, 22);
    f->fxsr_opt         = check_bit(edx, 25);
    f->pdpe1gb          = check_bit(edx, 26);
    f->rdtscp           = check_bit(edx, 27);
    f->lm               = check_bit(edx, 29);
    f->amd3dnowext      = check_bit(edx, 30);
    f->amd3dnow         = check_bit(edx, 31);
}

specseek_cpu_features specseek_get_cpu_features(void) {
    specseek_cpu_features f = {0};

    unsigned int max_leaf     = specseek_cpu_get_max_supported_leaf();
    unsigned int max_ext_leaf = specseek_cpu_get_max_supported_extended_leaf();

    if (max_leaf >= 0x01)
        specseek_cpuid_feature_leaf_01(&f);

    if (max_leaf >= 0x07)
        specseek_cpuid_feature_leaf_7_subleaf_0(&f);

    if (max_leaf >= 0x07)
        specseek_cpuid_feature_leaf_7_subleaf_1(&f);

    if (max_ext_leaf >= 0x80000001)
        specseek_cpuid_feature_leaf_80000001(&f);

    return f;
}