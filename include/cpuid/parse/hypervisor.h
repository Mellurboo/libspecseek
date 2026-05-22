#pragma once
#include <specseek.h>

/// @brief checks for a hypervisor and reads its vendor string from leaf 0x40000000 if present
/// @return populated specseek_cpu_hypervisor struct
specseek_cpu_hypervisor specseek_get_cpu_hypervisor(void);