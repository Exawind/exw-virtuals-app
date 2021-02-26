#include "Algorithm.hpp"

namespace exw_ngp {

Algorithm::~Algorithm()
{
    // Release device pointers if any
    for (auto& kern: m_kernels) {
        kern->free_on_device();
    }
}

void Algorithm::execute()
{
    const size_t num_kernels = m_kernels.size();
    if (num_kernels < 1) {
        std::cout << "Algorithm has no kernels registered. Exiting" << std::endl;
        return;
    }

    auto ngp_kernels = create_ngp_view<Kernel>(m_kernels);
    double device_total = 0.0;
    Kokkos::parallel_reduce(num_kernels, KOKKOS_LAMBDA (int i, double& sum) {
            Kernel* kernel = ngp_kernels(i);
            sum += (*kernel)();
        }, device_total);

    double host_total = 0.0;
    for (auto& kern: m_kernels) {
        host_total += (*kern)();
    }

    constexpr double eps = 1.0e-12;
    const double diff = std::abs(device_total - host_total);
    if (diff > eps) {
        std::cout << "ERROR: Mismatch between host/device executions\n"
                  << "  host value = " << host_total
                  << "\n  device value = " << device_total
                  << std::endl;
    } else {
        std::cout << "Algorithm execution succeeded on device space"
                  << std::endl;
    }
}

}
