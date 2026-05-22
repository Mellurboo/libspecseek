#pragma once
#include <specseek.h>

/// @brief reads physical and virtual address bit widths from leaf 0x80000008
/// @return populated specseek_cpu_address_space struct
specseek_cpu_address_space specseek_get_cpu_address_space(void);