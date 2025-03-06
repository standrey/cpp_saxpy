#include <stdlib.h>
#include <stdint.h>
#include <assert.h> 

constexpr size_t pow2elements = (2 << 22);
constexpr size_t pow2sz = pow2elements * sizeof(uint32_t);
constexpr size_t sse2alignment = 16;

template<typename T, auto aligntoDefault = alignof(T)>
inline void is_aligned(T * ptr, auto alignto = aligntoDefault) {
    assert(reinterpret_cast<uintptr_t>(ptr) % alignto == 0);
}

#define IS_ALIGNED(addr,size)   ((((size_t)(addr)) % (size)) == 0)
