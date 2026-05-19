#include <specseek.h>
#include <string.h>
#include <identifiers/identifiers.h>

void specseek_get_cpuid_identifiers(specseek_cpu_identifiers *identifier_struct){
    memcpy(identifier_struct->CPU_VENDOR_STRING,
                specseek_get_vendor_string(),
                sizeof(identifier_struct->CPU_VENDOR_STRING)
            );
}