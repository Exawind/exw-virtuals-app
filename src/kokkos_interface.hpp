#ifndef KOKKOS_INTERFACE_H
#define KOKKOS_INTERFACE_H

#include "Kokkos_Macros.hpp"
#include "Kokkos_Core.hpp"

namespace exw_ngp {

#ifdef KOKKOS_ENABLE_CUDA
using MemSpace = Kokkos::CudaSpace;
using UVMSpace = Kokkos::CudaUVMSpace;
#elif defined(KOKKOS_ENABLE_HIP)
using MemSpace = Kokkos::HIPSpace;
using UVMSpace = Kokkos::HIPSpace;
#elif defined(KOKKOS_HAVE_OPENMP)
using MemSpace = Kokkos::OpenMP;
using UVMSpace = Kokkos::OpenMP;
#else
using MemSpace = Kokkos::HostSpace;
using UVMSpace = Kokkos::HostSpace;
#endif

using HostSpace = Kokkos::DefaultHostExecutionSpace;
using DeviceSpace = Kokkos::DefaultExecutionSpace;

template <typename T, typename MemorySpace = MemSpace>
inline T* kokkos_malloc_on_device(const std::string& debug_name)
{
    return static_cast<T*>(
        Kokkos::kokkos_malloc<MemorySpace>(debug_name, sizeof(T)));
}

template <typename MemorySpace=MemSpace>
inline void kokkos_free_on_device(void* ptr)
{
    Kokkos::kokkos_free<MemorySpace>(ptr);
}

} // namespace exw_ngp

#endif /* KOKKOS_INTERFACE_H */
