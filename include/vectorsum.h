#include <stdint.h>

void AddVectorSSEAligned(const uint32_t* __restrict__ a, const uint32_t* __restrict__ b, uint32_t * __restrict__ out, uint32_t sz);
void AddVectorSSEUnaligned(const uint32_t* __restrict__ a, const uint32_t* __restrict__ b, uint32_t * __restrict__ out, uint32_t sz);
