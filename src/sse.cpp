#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <stdint.h>
#include <assert.h> 
#include <stdint.h>
#include <array>
#include <vector>
#include <iostream>

using namespace std;

void AddVectorSSEAligned(const uint32_t* __restrict__ a, const uint32_t* __restrict__ b, uint32_t * __restrict__ out, uint32_t sz) {
    uint32_t i = 0;
    uint32_t aligned_size = sz & ~15;
    assert(sz >= 16);
    printf("%s aligned_size & ~15 = %x\n", __FUNCTION__, aligned_size);
    do {
        const __m128i a0 = _mm_load_si128((const __m128i*)(a + i + 0 ));
        const __m128i a1 = _mm_load_si128((const __m128i*)(a + i + 4 ));
        const __m128i a2 = _mm_load_si128((const __m128i*)(a + i + 8 ));
        const __m128i a3 = _mm_load_si128((const __m128i*)(a + i + 12));
        
        const __m128i b0 = _mm_load_si128((const __m128i*)(b + i + 0 ));
        const __m128i b1 = _mm_load_si128((const __m128i*)(b + i + 4 ));
        const __m128i b2 = _mm_load_si128((const __m128i*)(b + i + 8 ));
        const __m128i b3 = _mm_load_si128((const __m128i*)(b + i + 12));

        _mm_store_si128((__m128i*)&out[i + 0],  _mm_add_epi32(a0, b0));
        _mm_store_si128((__m128i*)&out[i + 4],  _mm_add_epi32(a1, b1));
        _mm_store_si128((__m128i*)&out[i + 8],  _mm_add_epi32(a2, b2));
        _mm_store_si128((__m128i*)&out[i + 12], _mm_add_epi32(a3, b3));

        i+=16;
    } while(i != aligned_size);

    printf("%s size & 8 = %x\n", __FUNCTION__, (sz & 8));
    if ((sz & 8) !=0) {
        const __m128i a0 = _mm_load_si128((const __m128i*)&a[i + 0]);
        const __m128i a1 = _mm_load_si128((const __m128i*)&a[i + 4]);
        const __m128i b0 = _mm_load_si128((const __m128i*)&b[i + 0]);
        const __m128i b1 = _mm_load_si128((const __m128i*)&b[i + 4]);
        
        _mm_store_si128((__m128i*)&out[i + 4], _mm_add_epi32(a1, b1));
        _mm_store_si128((__m128i*)&out[i + 0], _mm_add_epi32(a0, b0));
        i+=8;
    }

    printf("%s size & 7 = %x\n", __FUNCTION__, sz & 7);
    sz &=7;
    if (sz == 4) {
        const __m128i a0 = _mm_load_si128((const __m128i*)&a[i]);
        const __m128i b0 = _mm_load_si128((const __m128i*)&b[i]);
        _mm_store_si128((__m128i*)&out[i], _mm_add_epi32(a0, b0));
    } else if (sz == 2) {
        const __m128i a0 = _mm_loadl_epi64((const __m128i*)&a[i]);
        const __m128i b0 = _mm_loadl_epi64((const __m128i*)&b[i]);
        _mm_storel_epi64((__m128i*)&out[i], _mm_add_epi32(a0, b0));
    }
}


void AddVectorSSEUnaligned(const uint32_t* __restrict__ a, const uint32_t* __restrict__ b, uint32_t * __restrict__ out, uint32_t sz) {
    uint32_t i = 0;
    uint32_t aligned_size = sz & ~15;
    assert(sz >= 16);
    printf("aligned_size & ~15 = %x\n", sz & ~15);
    uint32_t res = 0;
    do {
        res|=a[i] & a[i+4] & a[i+8] & a[i+12];
        const __m128i a0 = _mm_loadu_si128((const __m128i*)&a[i + 0]);
        const __m128i a1 = _mm_loadu_si128((const __m128i*)&a[i + 4]);
        const __m128i a2 = _mm_loadu_si128((const __m128i*)&a[i + 8]);
        const __m128i a3 = _mm_loadu_si128((const __m128i*)&a[i + 12]);
        
        const __m128i b0 = _mm_loadu_si128((const __m128i*)&b[i + 0]);
        const __m128i b1 = _mm_loadu_si128((const __m128i*)&b[i + 4]);
        const __m128i b2 = _mm_loadu_si128((const __m128i*)&b[i + 8]);
        const __m128i b3 = _mm_loadu_si128((const __m128i*)&b[i + 12]);

        _mm_storeu_si128((__m128i*)&out[i + 0],  _mm_add_epi32(a0, b0));
        _mm_storeu_si128((__m128i*)&out[i + 4],  _mm_add_epi32(a1, b1));
        _mm_storeu_si128((__m128i*)&out[i + 8],  _mm_add_epi32(a2, b2));
        _mm_storeu_si128((__m128i*)&out[i + 12], _mm_add_epi32(a3, b3));

        i+=16;
    } while(i != aligned_size);
    printf("%u\n", res);

    printf("size & 8 = %x\n", (sz & 8));
    if ((sz & 8) !=0) {
        const __m128i a0 = _mm_loadu_si128((const __m128i*)&a[i + 0]);
        const __m128i a1 = _mm_loadu_si128((const __m128i*)&a[i + 4]);
        const __m128i b0 = _mm_loadu_si128((const __m128i*)&b[i + 0]);
        const __m128i b1 = _mm_loadu_si128((const __m128i*)&b[i + 4]);
        
        _mm_storeu_si128((__m128i*)&out[i + 4], _mm_add_epi32(a1, b1));
        _mm_storeu_si128((__m128i*)&out[i + 0], _mm_add_epi32(a0, b0));
        i+=8;
    }

    printf("size & 7 = %x\n", sz & 7);
    sz &=7;
    if (sz == 4) {
        const __m128i a0 = _mm_loadu_si128((const __m128i*)&a[i]);
        const __m128i b0 = _mm_loadu_si128((const __m128i*)&b[i]);
        _mm_storeu_si128((__m128i*)&out[i], _mm_add_epi32(a0, b0));
    } else if (sz == 2) {
        const __m128i a0 = _mm_loadl_epi64((const __m128i*)&a[i]);
        const __m128i b0 = _mm_loadl_epi64((const __m128i*)&b[i]);
        _mm_storel_epi64((__m128i*)&out[i], _mm_add_epi32(a0, b0));
    }
}

template<typename T, auto aligntoV = alignof(T)>
inline void is_aligned(T * ptr, auto alignto = aligntoV) {
    assert(reinterpret_cast<uintptr_t>(ptr) % alignto == 0);
}

#define IS_ALIGNED(addr,size)   ((((size_t)(addr)) % (size)) == 0)

bool is_sum_correct(auto * a, auto * b, auto * out, size_t elements) {
    for (size_t i = 0; i < elements; ++i) {
        if (a[i] + b[i] != out[i]) {
            std::cout << "Incorrect sum of 2 elements at position " << i << std::endl; 
            return false;
        }
    }
    return true;
}

int main () {

    constexpr uint32_t elements = (2 << 22) +1;
    uint32_t sz = elements * sizeof(uint32_t);

    std::vector<uint32_t> out_cpp, b_cpp, a_cpp;
    a_cpp.reserve(elements);
    b_cpp.reserve(elements);
    out_cpp.reserve(elements);
    std::fill(a_cpp.begin(), a_cpp.end(), 1);
    std::fill(b_cpp.begin(), b_cpp.end(), 1);

    constexpr size_t sse2_alignment = 16;
    is_aligned(a_cpp.data(),sse2_alignment);
    is_aligned(b_cpp.data(), sse2_alignment);
    is_aligned(out_cpp.data(), sse2_alignment);

    AddVectorSSEUnaligned(a_cpp.data(), b_cpp.data(), out_cpp.data(), elements);
    is_sum_correct(a_cpp.data(), b_cpp.data(), out_cpp.data(), elements);

    AddVectorSSEAligned(a_cpp.data(), b_cpp.data(), out_cpp.data(), elements);
    is_sum_correct(a_cpp.data(), b_cpp.data(), out_cpp.data(), elements);

    uint32_t * a = static_cast<uint32_t*>(std::aligned_alloc(32, sz));
    uint32_t * b = static_cast<uint32_t*>(std::aligned_alloc(32, sz));
    uint32_t * out = static_cast<uint32_t*>(std::aligned_alloc(32, sz));

    assert(IS_ALIGNED(a, 32));
    assert(IS_ALIGNED(b, 32));
    assert(IS_ALIGNED(out, 32));

    printf("Out address range [%p - %p]\n", out, out + sz);
    printf("A address range [%p - %p]\n", a, a + sz);
    printf("B address range [%p - %p]\n", b, b + sz);

    AddVectorSSEUnaligned(a, b , out , elements);
    is_sum_correct(a, b, out, elements);
    
    AddVectorSSEAligned(a, b , out , elements);
    is_sum_correct(a, b, out, elements);

    free(a);
    free(b);
    free(out);

    a = static_cast<uint32_t*>(std::malloc(sz));
    b = static_cast<uint32_t*>(std::malloc(sz));
    out = static_cast<uint32_t*>(std::malloc(sz));

    AddVectorSSEUnaligned(a, b , out , elements);
    is_sum_correct(a, b, out, elements);
    
    AddVectorSSEAligned(a, b , out , elements);
    is_sum_correct(a, b, out, elements);

    free(a);
    free(b);
    free(out);

    return 0;
}
