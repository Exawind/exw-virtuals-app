#!/bin/bash

exw_virtuals_configure ()
{
    local extra_args="$@"

    local cmake_cmd=(
        cmake
        -DCMAKE_CXX_COMPILER=$(which icpx)
        -DCMAKE_C_COMPILER=$(which icx)
        -DKokkos_ENABLE_SERIAL=ON
        -DKokkos_ENABLE_OPENMP=OFF
        -DKokkos_ENABLE_CUDA=OFF
        -DKokkos_ENABLE_HIP=OFF
        -DKokkos_ENABLE_OPENMPTARGET=ON
        -DKokkos_ARCH_INTEL_GEN=ON
        ${extra_args}
        ${EXW_VIRTUALS_SOURCE_DIR:-..}
    )

    echo "${cmake_cmd[@]}" | tee cmake_output.log
    eval "${cmake_cmd[@]}" |& tee -a cmake_output.log
}

exw_virtuals_configure "$@"
