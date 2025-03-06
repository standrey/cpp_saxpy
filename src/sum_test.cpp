#include <stdlib.h>
#include <stdint.h>
#include <assert.h> 
#include <stdint.h>
#include <iostream>

#include "dimensions.h"
#include "vectorsum.h"

bool is_sum_correct(auto * a, auto * b, auto * out, size_t elements) {
    for (size_t i = 0; i < elements; ++i) {
        if (a[i] + b[i] != out[i]) {
            std::cout << "Incorrect sum of two elements at position " << i << std::endl; 
            return false;
        }
    }
    return true;
}
