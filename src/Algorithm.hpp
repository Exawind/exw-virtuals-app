#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <memory>
#include "Kernel.hpp"

namespace exw_ngp {

class Algorithm
{
public:
    using KernelPtrType = std::unique_ptr<Kernel>;
    using KernelVecType = std::vector<KernelPtrType>;

    Algorithm() = default;

    virtual ~Algorithm();

    virtual void execute();

    template <typename T, class... Args>
    void add_kernel(Args&&... args)
    {
        m_kernels.push_back(
            std::make_unique<T>(std::forward<Args>(args)...));
    }

private:
    KernelVecType m_kernels;
};

}

#endif /* ALGORITHM_H */
