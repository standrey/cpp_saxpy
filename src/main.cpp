#include <stdlib.h>
#include <stdint.h>
#include <tests.h>

int main () {
    cpp_allocator_test();

    /*uint32_t * a = static_cast<uint32_t*>(std::aligned_alloc(32, sz));*/
    /*uint32_t * b = static_cast<uint32_t*>(std::aligned_alloc(32, sz));*/
    /*uint32_t * out = static_cast<uint32_t*>(std::aligned_alloc(32, sz));*/
    /**/
    /*assert(IS_ALIGNED(a, 32));*/
    /*assert(IS_ALIGNED(b, 32));*/
    /*assert(IS_ALIGNED(out, 32));*/
    /**/
    /**/
    /*AddVectorSSEUnaligned(a, b , out , elements);*/
    /*is_sum_correct(a, b, out, elements);*/
    /**/
    /*AddVectorSSEAligned(a, b , out , elements);*/
    /*is_sum_correct(a, b, out, elements);*/
    /**/
    /*free(a);*/
    /*free(b);*/
    /*free(out);*/
    /**/
    /*a = static_cast<uint32_t*>(std::malloc(sz));*/
    /*b = static_cast<uint32_t*>(std::malloc(sz));*/
    /*out = static_cast<uint32_t*>(std::malloc(sz));*/
    /**/
    /*AddVectorSSEUnaligned(a, b , out , elements);*/
    /*is_sum_correct(a, b, out, elements);*/
    /**/
    /*AddVectorSSEAligned(a, b , out , elements);*/
    /*is_sum_correct(a, b, out, elements);*/
    /**/
    /*free(a);*/
    /*free(b);*/
    /*free(out);*/
    /**/
    return 0;
}
