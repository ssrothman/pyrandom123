#ifndef PYRANDOM123_TYPE_CONVERSION_H
#define PYRANDOM123_TYPE_CONVERSION_H

inline uint64_t uint64_from_2xuint32(uint32_t a, uint32_t b){
  return static_cast<uint64_t>(a) + (static_cast<uint64_t>(b) << 32);
}

inline float float32_from_uint32(uint32_t a){
    return static_cast<float>(a) / static_cast<float>(UINT32_MAX);
}

inline double float64_from_uint64(uint64_t a){
    return static_cast<double>(a) / static_cast<double>(UINT64_MAX);
}

#endif
