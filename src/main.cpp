#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "pyrandom123/typeconversion.hpp"
#include "pyrandom123/randomutil.hpp"

#include <Random123/philox.h>
#include <Random123/threefry.h>
#include <Random123/ars.h>

namespace py = pybind11;

struct uint2x32_t {
    uint32_t A, B;
};

struct uint2x64_t {
    uint64_t A, B;
};

uint2x32_t philox2x32_get_2x32(uint64_t counter, uint32_t key){
    using RNG = r123::Philox2x32;
    RNG rng;
    typename RNG::ctr_type c = {{
        (uint32_t)(counter & 0xffffffff), 
        (uint32_t)((counter << 32) & 0xffffffff)
    }};
    typename RNG::ukey_type uk = {{key}};
    typename RNG::key_type k = uk;
    typename RNG::ctr_type rand = rng(c, k);
    return {rand[0], rand[1]};
}

uint64_t philox2x32_get_uint64(uint64_t counter, uint32_t key){
    auto rand = philox2x32_get_2x32(counter, key);
    return uint64_from_2xuint32(rand.A, rand.B);
}

uint2x32_t threefry2x32_get_2x32(uint64_t counter, uint64_t key){
    using RNG = r123::Threefry2x32;
    RNG rng;
    typename RNG::ctr_type c = {{
        (uint32_t)(counter & 0xffffffff), 
        (uint32_t)((counter << 32) & 0xffffffff)
    }};
    typename RNG::ukey_type uk = {{
        (uint32_t)(key & 0xffffffff), 
        (uint32_t)((key << 32) & 0xffffffff)
    }};
    typename RNG::key_type k = uk;
    typename RNG::ctr_type rand = rng(c, k);
    return {rand[0], rand[1]};
}

uint64_t threefry2x32_get_uint64(uint64_t counter, uint64_t key){
    auto rand = threefry2x32_get_2x32(counter, key);
    return uint64_from_2xuint32(rand.A, rand.B);
}

PYBIND11_MODULE(_core, m) {
    //declare 2x32 and 2x64 data types
    PYBIND11_NUMPY_DTYPE(uint2x32_t, A, B);
    PYBIND11_NUMPY_DTYPE(uint2x64_t, A, B);

    py::class_<uint2x32_t>(m, "uint2x32")
        .def(py::init<uint32_t, uint32_t>())
        .def_readonly("A", &uint2x32_t::A)
        .def_readonly("B", &uint2x32_t::B);

    py::class_<uint2x64_t>(m, "uint2x64")
        .def(py::init<uint64_t, uint64_t>())
        .def_readonly("A", &uint2x64_t::A)
        .def_readonly("B", &uint2x64_t::B);

    py::module util = m.def_submodule("util");
    
    util.def("uint64_to_float64", &float64_from_uint64);
    util.def("uint64_to_float64", py::vectorize(float64_from_uint64));

    util.def("float64_to_poisson1", &get_poisson1_from_one_float64);
    util.def("float64_to_poisson1", py::vectorize(get_poisson1_from_one_float64));

    util.def("uint64_to_poisson1", &get_poisson1_from_one_uint64);
    util.def("uint64_to_poisson1", py::vectorize(get_poisson1_from_one_uint64));

    util.def("uint32_to_float32", &float32_from_uint32);
    util.def("uint32_to_float32", py::vectorize(float32_from_uint32));

    util.def("float32_to_poisson1", &get_poisson1_from_one_float32);
    util.def("float32_to_poisson1", py::vectorize(get_poisson1_from_one_float32));

    util.def("uint32_to_poisson1", &get_poisson1_from_one_uint32);
    util.def("uint32_to_poisson1", py::vectorize(get_poisson1_from_one_uint32));

    py::module philox2x32 = m.def_submodule("philox2x32");

    philox2x32.def("get_uint64", &philox2x32_get_uint64);
    philox2x32.def("get_uint64", py::vectorize(philox2x32_get_uint64));

    philox2x32.def("get_uint2x32", &philox2x32_get_2x32);
    philox2x32.def("get_uint2x32", py::vectorize(philox2x32_get_2x32));

    py::module threefry2x32 = m.def_submodule("threefry2x32");

    threefry2x32.def("get_uint64", &threefry2x32_get_uint64);
    threefry2x32.def("get_uint64", py::vectorize(threefry2x32_get_uint64));

    threefry2x32.def("get_uint2x32", &threefry2x32_get_2x32);
    threefry2x32.def("get_uint2x32", py::vectorize(threefry2x32_get_2x32));
}
