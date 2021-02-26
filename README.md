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
