#pragma once
#include <specseek.h>

/// @brief reads base, max, and bus frequencies from leaf 0x16 (Intel Skylake+ only)
/// @return populated specseek_cpu_frequency struct, all fields zero if unsupported
specseek_cpu_frequency specseek_get_cpu_frequency(void);