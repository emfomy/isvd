# iSVD
Integrated Singular Value Decomposition (iSVD)

## Information

### Git
* https://github.com/emfomy/isvd

### Documentation
* http://emfomy.github.io/isvd

### Author
* Mu Yang <<emfomy@gmail.com>>

## Requirements
* [CMake](https://cmake.org) 2.8+ (CMake 3+ recommended).
* C/C++ compiler with C99/C++98 standard support ([GCC](https://gcc.gnu.org) 4.4+ recommended).
* [BLAS](http://www.netlib.org/blas) & [LAPACK](http://www.netlib.org/lapack) library (Used for multi-core parallelization).
* MPI Library v2.2+ ([MPICH](http://www.mpich.org) or [OpenMPI](https://www.open-mpi.org)).

### Optional
* [Intel&reg; Math Kernel Library](https://software.intel.com/en-us/intel-mkl) (**Recommended** for better performance, used for BLAS & LAPACK).
* [MAGMA](http://icl.cs.utk.edu/magma/) 2+ (Used for BLAS & LAPACK with GPU support).
* [OpenMP](http://openmp.org) Library (**Recommended** for better performance, used for multi-thread parallelization).
* [Google Test Library](https://github.com/google/googletest) (Used for code testing).
* [DOxygen](http://www.stack.nl/~dimitri/doxygen/) (Used for documentation).

## Installation

Please use the following commands to create Makefiles

```
mkdir build
cd build
cmake <path-to-source>
```

### Options

Use the following command to set options

```
ccmake <path-to-source>
```

The following table are the main options

| Option                 | Detail                             | Note                           |
|------------------------|------------------------------------|--------------------------------|
| `ISVD_BLAS`            | the selection BLAS/LAPACK library. | Options: `BLAS/MKL`            |
| `ISVD_BUILD_DEMO`      | build demo codes.                  |                                |
| `ISVD_BUILD_DOC`       | build documentation.               |                                |
| `ISVD_BUILD_TEST`      | build unit tests.                  |                                |
| `ISVD_INDEX_TYPE`      | the selection index type.          | Options: `32/64`               |
| `ISVD_OMP`             | the selection OpenMP library.      | Options: `OFF/GOMP/IOMP`       |
| `ISVD_USE_GPU`         | enable GPU support.                |                                |
| `GTEST_ROOT`           | the root path of Google Test.      | Require `ISVD_BUILD_TEST`      |
| `INTEL_ROOT`           | the root path of Intel libraries.  | Require `ISVD_BLAS = MKL`      |
| `MKL_ROOT`             | the root path of Intel MKL.        | Require `ISVD_BLAS = MKL`      |
| `MPI_PROCS`            | the number of MPI processes.       | Only used in demo codes.       |
| `OMP_THRDS`            | the number of OpenMP threads.      | Only used in demo/check codes. |

### Makefile

The following table are the main make rules

| Command        | Detail                         |
|----------------|--------------------------------|
| `make all`     | build all binaries             |
| `make install` | install package                |
| `make check`   | build and run unit tests       |
| `make doc`     | build documentation            |
| `make help`    | display make-rules             |

### Definitions

* Define `ISVD_USE_ILP64` to use 64-bit integer.
* Define `ISVD_USE_MKL`   to enable Intel MKL.
<!-- * Define `ISVD_USE_GPU`   to enable GPU support. -->

## Q&amp;A

### How to set CMake options?

* Use `ccmake ..` or `ccmake <path-to-source>` in the `build` folder.
* Press `<Enter>` on the option you want to change, change it, and press `<Enter>` again.
* After changing the options, press `<c>` to configure, and press `<g>` to generate Makefiles if configured successfully.
* To quit without saving, press `<q>`.

### Why Intel MKL is not found?

* Source `mklvars.sh` in the `bin` folder of your Intel MKL to set the environment variables.

### Why Google Test is not found?

* Set `GTEST_ROOT` to a folder containing `include` and `lib` of Google Test.

### How to use 64-bit integer?

* Set `ISVD_USE_ILP64` with `ccmake`.
* If you want to compile directly, add `-DISVD_USE_ILP64` to compiler flag.
* Make sure your LAPACK&amp;BLAS / Intel MKL uses 64bit integer. Make sure you uses the correct library and flags of Intel MKL.

## Reference
* [Ting-Li Chen, Dawei D. Chang, Su-Yun Huang, Hung Chen, Chienyao Lin, Weichung Wang, “Integrating Multiple Random Sketches for Singular Value Decomposition”](https://arxiv.org/abs/1608.08285)
* [Mu Yang, “Highly Scalable Parallelism of Integrated Randomized Singular Value Decomposition with Big Data Applications”](http://doi.org/10.6342/NTU201702960)

## License
@include LICENSE.md
