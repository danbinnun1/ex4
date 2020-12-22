#pragma once
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/param.h>

#ifdef __cplusplus
extern "C" {
#endif
uint32_t
calculate_crc32c(uint32_t crc32c,
    const unsigned char *buffer,
    unsigned int length);

#ifdef __cplusplus
}
#endif