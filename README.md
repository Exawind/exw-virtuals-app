# ExaWind device virtual function mini-app

This repository contains a minimal example of device virtual functions used in
[exawind/nalu-wind](https://github.com/exawind/nalu-wind) codebase. The core
physics kernels are implemented in as sub-classes of `Kernel` and `Algorithm` is
the driver that holds a vector of user-registered computational kernels as
pointers to the base class. These instances are created on device using
_placement new_ and run on device.

## Building and testing

You'll need a recent version of C++ compiler (that supports C++14 standard).
Depending on the target GPU backend device, you'll also need appropriate CUDA,
HIP, or Intel compilers. The project uses CMake to configure and build code.
Please use CMake v3.17.0 or later.

Example CMake configure scripts are provided in `./scripts` directory. 

```
# Clone codebase
git clone --recurse-submodules https://github.com/exawind/exw-virtuals.git

# Create build directory
cd exw-virtuals

# Configure and build for host
mkdir build_host
cd build_host

# CMake configure step
../scripts/configure-host.sh 
# compile
make -j 8
# Run executable
./exw_virtuals
```

### CMake options

- `EXAWIND_TEST_VIRTUALS` (default: ON) Enables device virtual test classes. Set
  `OFF` to test basic build on AMD HIP/Intel.
  
- `EXAWIND_USE_EXTERNAL_KOKKOS` (default: OFF): Provide an external installation
  of Kokkos instead of using the submodule. You should still provide appropriate
  compilers and compiler options to CMake.

## Current status

**as of Feb. 26, 2021**

- Will compile and execute fine on host (GCC, Intel, LLVM/Clang) compilers. 

- Will compile and execute fine on NVIDIA CUDA (v10.2.89 or later)

- Generates compile time errors in AMD HIP

- Generates compile time errors in Intel OneAPI SYCL/dpcpp

- Generates runtime segfault with Intel OpenMP target

To test builds on AMD HIP or Intel OneAPI, you can disable virtual functions
with the following configuration option:

```
# For AMD HIP
../scripts/configure-hip.sh -DEXAWIND_TEST_VIRTUALS=OFF

# For Intel OneAPI SYCL/DPC++
../scripts/configure-intel-sycl.sh -DEXAWIND_TEST_VIRTUALS=OFF
```
