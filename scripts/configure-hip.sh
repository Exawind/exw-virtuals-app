#!/bin/bash

exw_virtuals_configure ()
{
    local extra_args="$@"

    local cmake_cmd=(
        cmake
        -DCMAKE_CXX_COMPILER=$(which hipcc)
        -DCMAKE_C_COMPILER=$(which hipcc)
        -DKokkos_ENABLE_SERIAL=ON
        -DKokkos_ENABLE_OPENMP=OFF
        -DKokkos_ENABLE_CUDA=OFF
        -DKokkos_ENABLE_HIP=ON
        -DKokkos_ENABLE_OPENMPTARGET=OFF
        -DKokkos_ARCH_VEGA906=ON
        ${extra_args}
        ${EXW_VIRTUALS_SOURCE_DIR:-..}
    )

    echo "${cmake_cmd[@]}" | tee cmake_output.log
    eval "${cmake_cmd[@]}" |& tee -a cmake_output.log
}

exw_virtuals_configure "$@"
