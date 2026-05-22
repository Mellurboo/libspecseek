#pragma once
#include <specseek.h>

/// @brief reads architectural performance monitoring capabilities from leaf 0x0A
/// @return populated specseek_cpu_perfmon struct
specseek_cpu_perfmon specseek_get_cpu_perfmon(void);