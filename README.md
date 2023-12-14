# Secure Transformer-based large scale model private inference via the SCI  Library

## Introduction
This directory contains the code for: 
- SecureFormer from ["SecureFormer"](https://google.com)<!--(https://eprint.iacr.org/2020/1002) -->
- 
## Required Packages
 - g++ (version >= 8)
 - cmake
 - make
 - libgmp-dev
 - libmpfr-dev
 - libssl-dev  
 - SEAL 3.3.2
 - Eigen 3.3

SEAL 3.3.2 and Eigen 3.3 are included in `extern/` and are automatically compiled and installed if not found. 
The other packages can be installed directly using `sudo apt-get install <package>` on Linux.

## Compilation

To compile the library:
```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=./install .. [-DBUILD_TESTS=ON] [-DBUILD_NETWORKS=OFF] [-DNO_REVEAL_OUTPUT=OFF]
cmake --build . --target install --parallel
```

To compile for secure AI validation so that outputs are not revealed at the end of 2PC, compile with `-DNO_REVEAL_OUTPUT=ON` flag:
```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=./install .. -DNO_REVEAL_OUTPUT=ON
cmake --build . --target install --parallel
```


## Running Tests & Networks

On successful compilation, the test and network binaries will be created in `build/bin/`.

Run the tests as follows to make sure everything works as intended:

`./<test> r=1 [port=port] & ./<test> r=2 [port=port]`

To run secure inference on networks:

```
./<network> r=1 [port=port] < <model_file> // Server
./<network> r=2 [ip=server_address] [port=port] < <image_file> // Client
```

# Acknowledgements

This library includes code from the following external repositories:

 - [EIGEN3][https://gitlab.com/libeigen/eigen/tree/603e213d13311af286c8c1abd4ea14a8bd3d204e] for matrix computes.
 - [Microsoft/SEAL](https://github.com/Microsoft/SEAL/tree/1d5c8169aa5aca9deb75c4079e53ea8d5e94007d) for cryptographic tools.
 - [EzPC/SCI](https://github.com/mpc-msri/EzPC/tree/master/SCI) for Framework building.