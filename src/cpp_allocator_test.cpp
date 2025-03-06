#include <stdlib.h>
#include <stdint.h>
#include <assert.h> 
#include <stdint.h>
#include <vector>

#include "dimensions.h"
#include "vectorsum.h"
#include "tests.h"

using namespace std;

void cpp_allocator_test() {
    std::vector<uint32_t> out_cpp, b_cpp, a_cpp;
    a_cpp.reserve(pow2elements);
    b_cpp.reserve(pow2elements);
    out_cpp.reserve(pow2elements);

    std::fill(a_cpp.begin(), a_cpp.end(), 1);
    std::fill(b_cpp.begin(), b_cpp.end(), 1);

    is_aligned(a_cpp.data(),sse2alignment);
    is_aligned(b_cpp.data(), sse2alignment);
    is_aligned(out_cpp.data(), sse2alignment);

    AddVectorSSEUnaligned(a_cpp.data(), b_cpp.data(), out_cpp.data(), pow2elements);
    is_sum_correct(a_cpp.data(), b_cpp.data(), out_cpp.data(), pow2elements);

    AddVectorSSEAligned(a_cpp.data(), b_cpp.data(), out_cpp.data(), pow2elements);
    is_sum_correct(a_cpp.data(), b_cpp.data(), out_cpp.data(), pow2elements);
}
