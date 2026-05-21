#pragma once
#include <specseek.h>

/// @brief discovers all supported CPU features via CPUID and returns a populated features struct
/// @return specseek_cpu_features struct with all supported flags set
specseek_cpu_features specseek_get_cpu_features(void);