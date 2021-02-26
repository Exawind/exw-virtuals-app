#ifndef KERNEL_H
#define KERNEL_H

#include "kokkos_interface.hpp"
#include "ngp_instance.hpp"

namespace exw_ngp {

/** Base class for all computational kernels
 */
class Kernel
{
public:
    KOKKOS_DEFAULTED_FUNCTION
    Kernel() = default;

    KOKKOS_DEFAULTED_FUNCTION
    virtual ~Kernel() = default;

    virtual Kernel* create_on_device() = 0;

    virtual void free_on_device() = 0;

    KOKKOS_FUNCTION
    virtual double operator()() = 0;
};

/** Kernel that can be transferred to device
 *
 *  Use CRTP to track the exact type of data to be created on device using
 *  placement new.
 */
template <typename T>
class NGPKernel : public Kernel
{
public:
    KOKKOS_DEFAULTED_FUNCTION
    NGPKernel() = default;

    KOKKOS_DEFAULTED_FUNCTION
    virtual ~NGPKernel() = default;

    virtual Kernel* create_on_device() final
    {
        // Deallocate any existing instance to be safe
        free_on_device();
        // Create and copy instance to device
        m_device_copy = create<T>(*dynamic_cast<T*>(this));
        return m_device_copy;
    }

    virtual void free_on_device() final
    {
        if (m_device_copy != nullptr) {
            destroy<T>(dynamic_cast<T*>(m_device_copy));
            m_device_copy = nullptr;
        }
    }

    T* device_copy() const { return m_device_copy; }

private:
    T* m_device_copy{nullptr};
};

class NodeKernel : public NGPKernel<NodeKernel>
{
public:
    static constexpr double multiplier = 1.0;

    KOKKOS_DEFAULTED_FUNCTION
    NodeKernel() = default;

    KOKKOS_DEFAULTED_FUNCTION
    virtual ~NodeKernel() = default;

    NodeKernel(double data) : m_data(data) {}

    virtual double operator()() final
    {
        return multiplier * m_data;
    }

private:
    double m_data{1.0};
};

class EdgeKernel : public NGPKernel<EdgeKernel>
{
public:
    static constexpr double multiplier = 2.0;

    KOKKOS_DEFAULTED_FUNCTION
    EdgeKernel() = default;

    KOKKOS_DEFAULTED_FUNCTION
    virtual ~EdgeKernel() = default;

    EdgeKernel(double data) : m_data(data) {}

    virtual double operator()() final
    {
        return multiplier * m_data;
    }

private:
    double m_data{1.0};
};

class ElemKernel : public NGPKernel<ElemKernel>
{
public:
    static constexpr double multiplier = 3.0;

    KOKKOS_DEFAULTED_FUNCTION
    ElemKernel() = default;

    KOKKOS_DEFAULTED_FUNCTION
    virtual ~ElemKernel() = default;

    ElemKernel(double data) : m_data(data) {}

    virtual double operator()() final
    {
        return multiplier * m_data;
    }

private:
    double m_data{1.0};
};

} // namespace exw_ngp

#endif /* KERNEL_H */
