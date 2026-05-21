#pragma once
#include <specseek.h>

/// @brief gets physical core count, threads per core, and logical processor count
/// @param specs pointer to caller specifications structure
specseek_cpu_specifications specseek_get_cpu_specifications(void);