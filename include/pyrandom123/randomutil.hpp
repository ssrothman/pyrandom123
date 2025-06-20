#ifndef PYRANDOM123_RANDOM_UTIL_H
#define PYRANDOM123_RANDOM_UTIL_H

#include <cmath>

static constexpr double EXP_M1 = std::exp(-1.);

template <uint32_t SIZE>
struct P1_CDF_STRUCT {
    double arr[SIZE];

    constexpr P1_CDF_STRUCT() : arr() {
        arr[0] = EXP_M1;

        double running_inv_factorial = 1;
        for (uint32_t i=1; i<SIZE; ++i){
            running_inv_factorial /= static_cast<double>(i);
            arr[i] = arr[i-1] + EXP_M1*running_inv_factorial;
        }
    }

    static constexpr uint32_t ARRSIZE = SIZE;
};

constexpr uint32_t MAX_POISSON = 16;
constexpr auto P1_CDF = P1_CDF_STRUCT<MAX_POISSON>();

inline uint32_t get_poisson1_from_one_float64(double rv){
    for(uint32_t i=0; i< MAX_POISSON; ++i){
        if (rv < P1_CDF.arr[i]){
            return i;
        }
    }
    return MAX_POISSON;
}

inline uint32_t get_poisson1_from_one_uint64(uint64_t rv){
    return get_poisson1_from_one_float64(float64_from_uint64(rv));
}

inline uint32_t get_poisson1_from_one_float32(float rv){
    return get_poisson1_from_one_float64(static_cast<double>(rv));
}

inline uint32_t get_poisson1_from_one_uint32(uint32_t rv){
    return get_poisson1_from_one_float32(float32_from_uint32(rv));
}

#endif
