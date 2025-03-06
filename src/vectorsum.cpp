#include <stdlib.h>
#include <x86intrin.h>
#include <stdint.h>
#include <assert.h> 
#include <stdint.h>

using namespace std;

void AddVectorSSEAligned(const uint32_t* __restrict__ a, const uint32_t* __restrict__ b, uint32_t * __restrict__ out, uint32_t sz) {
    uint32_t i = 0;
    uint32_t aligned_size = sz & ~15;
    assert(sz >= 16);

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


    if ((sz & 8) !=0) {
        const __m128i a0 = _mm_load_si128((const __m128i*)&a[i + 0]);
        const __m128i a1 = _mm_load_si128((const __m128i*)&a[i + 4]);
        const __m128i b0 = _mm_load_si128((const __m128i*)&b[i + 0]);
        const __m128i b1 = _mm_load_si128((const __m128i*)&b[i + 4]);
        
        _mm_store_si128((__m128i*)&out[i + 4], _mm_add_epi32(a1, b1));
        _mm_store_si128((__m128i*)&out[i + 0], _mm_add_epi32(a0, b0));
        i+=8;
    }


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



    if ((sz & 8) !=0) {
        const __m128i a0 = _mm_loadu_si128((const __m128i*)&a[i + 0]);
        const __m128i a1 = _mm_loadu_si128((const __m128i*)&a[i + 4]);
        const __m128i b0 = _mm_loadu_si128((const __m128i*)&b[i + 0]);
        const __m128i b1 = _mm_loadu_si128((const __m128i*)&b[i + 4]);
        
        _mm_storeu_si128((__m128i*)&out[i + 4], _mm_add_epi32(a1, b1));
        _mm_storeu_si128((__m128i*)&out[i + 0], _mm_add_epi32(a0, b0));
        i+=8;
    }


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

