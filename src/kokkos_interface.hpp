#ifndef KOKKOS_INTERFACE_H
#define KOKKOS_INTERFACE_H

#include "Kokkos_Macros.hpp"
#include "Kokkos_Core.hpp"

namespace exw_ngp {

using HostSpace = Kokkos::DefaultHostExecutionSpace;
using DeviceSpace = Kokkos::DefaultExecutionSpace;

#ifdef KOKKOS_ENABLE_CUDA
using MemSpace = Kokkos::CudaSpace;
using UVMSpace = Kokkos::CudaUVMSpace;
#else
using MemSpace = Kokkos::DefaultExecutionSpace::memory_space;
using UVMSpace = Kokkos::DefaultExecutionSpace::memory_space;
#endif

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
