#pragma once
#include <specseek.h>

/// @brief reads thermal and power management feature flags from leaf 0x06
/// @return populated specseek_cpu_thermal struct
specseek_cpu_thermal specseek_get_cpu_thermal(void);
