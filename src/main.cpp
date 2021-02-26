#include <iostream>
#include <sstream>

#include "ngp_instance.hpp"
#ifdef EXAWIND_TEST_VIRTUALS
#include "Algorithm.hpp"
#endif

void print_kokkos_configuration()
{
    std::cout << "Kokkos configuration: " << std::endl;
#ifdef KOKKOS_ENABLE_SERIAL
    std::cout << "  Kokkos::Serial is available." << std::endl;
#endif
#ifdef KOKKOS_ENABLE_OPENMP
    std::cout << "  Kokkos:OpenMP is available" << std::endl;
#endif
#ifdef KOKKOS_ENABLE_CUDA
    std::cout << "  Kokkos:CUDA is available" << std::endl;
#endif
#ifdef KOKKOS_ENABLE_HIP
    std::cout << "  Kokkos:HIP is available" << std::endl;
#endif
#ifdef KOKKOS_ENABLE_OPENMPTARGET
    std::cout << "  Kokkos::OpenMPTarget is available" << std::endl;
#endif

#ifndef KOKKOS_ENABLE_OPENMPTARGET
    std::stringstream ss;
    Kokkos::DefaultExecutionSpace::print_configuration(ss);
    const std::string& sinfo = ss.str();
    if (!sinfo.empty()) {
        std::cout << "Kokkos default execution space: " << std::endl;
        std::cout << sinfo << std::endl;
    } else {
        std::cout << "Assuming default space = host space" << std::endl;
    }
    std::cout << std::endl;
#else
    std::cout << "Default execution space = " <<
              << Kokkos::DefaultExecutionSpace::name()
              << std::endl << std::endl;
#endif
}

void test_algorithm()
{
#ifdef EXAWIND_TEST_VIRTUALS
    exw_ngp::Algorithm alg;
    std::cout << "Testing Algorithm with virtual kernel execution" << std::endl;
    alg.add_kernel<exw_ngp::NodeKernel>(10.0);
    alg.add_kernel<exw_ngp::EdgeKernel>(20.0);
    alg.add_kernel<exw_ngp::ElemKernel>(30.0);
    std::cout << "  Registered 3 kernels" << std::endl;
    alg.execute();
#else
    std::cout << "ExaWind virtual functions were disabled at compile time. Exiting!"
              << std::endl;
#endif
}

int main(int argc, char** argv)
{
    Kokkos::initialize(argc, argv);
    {
        print_kokkos_configuration();
        test_algorithm();
    }
    Kokkos::finalize_all();
    return 0;
}
